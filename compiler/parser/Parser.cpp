//
// Created by Brayhan De Aza on 5/12/26.
//

#include "Parser.h"


namespace yogi::compiler::parser {
    Parser::ModuleGraph Parser::discoverModulesPaths(const std::string &filePath, std::unordered_set<std::string> &visited) {
        ModuleGraph graph;

        const auto normalizedPath = std::filesystem::weakly_canonical(filePath).string();

        if (visited.contains(normalizedPath)) {
            return {};
        }

        visited.insert(normalizedPath);

        if (std::ifstream file(normalizedPath); !file) {
            std::cerr << "Error: Could not open file " << normalizedPath << std::endl;
            std::exit(1);
        }

        const auto ast = Compiler::scan(normalizedPath);
        const auto modules = std::any_cast<visitor::nodes::ModulesPathsNode>(ast);
        const auto currentDirectory = std::filesystem::path(normalizedPath).parent_path();

        std::vector<std::string> imports;

        for (const auto &module: modules.modules) {
            const auto resolvedPath = std::filesystem::weakly_canonical(currentDirectory / module.path).string();

            imports.push_back(resolvedPath);

            // recursively merge child graph
            auto childGraph = discoverModulesPaths(resolvedPath, visited);

            // merge child graph into current graph
            graph.insert(childGraph.begin(), childGraph.end());
        }

        // store current node
        graph[normalizedPath] = imports;

        return graph;
    }

    std::vector<std::string> Parser::buildExecutionOrder(const ModuleGraph &sccGraph) {
        std::unordered_map<std::string, int> indegree;
        std::queue<std::string> q;
        std::vector<std::string> order;

        // -------------------------------------------------
        // Initialize ALL nodes
        // -------------------------------------------------
        for (const auto &[node, deps]: sccGraph) {
            indegree.try_emplace(node, 0);

            for (const auto &dep: deps) {
                indegree.try_emplace(dep, 0);
            }
        }

        // -------------------------------------------------
        // Build indegree
        // -------------------------------------------------
        for (const auto &[node, deps]: sccGraph) {
            for (const auto &dep: deps) {
                indegree[dep]++;
            }
        }

        // -------------------------------------------------
        // Push nodes with indegree 0
        // -------------------------------------------------
        for (const auto &[node, deg]: indegree) {
            if (deg == 0) {
                q.push(node);
            }
        }

        // -------------------------------------------------
        // Kahn topological sort
        // -------------------------------------------------
        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            order.push_back(node);

            if (!sccGraph.contains(node)) {
                continue;
            }

            for (const auto &neighbor: sccGraph.at(node)) {
                indegree[neighbor]--;

                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return order;
    }

    Parser::Components Parser::build(const ModuleGraph &graph) {
        std::unordered_map<std::string, int> index;
        std::unordered_map<std::string, int> lowLink;
        std::unordered_set<std::string> onStack;
        std::stack<std::string> stack;
        Components components;
        int currentIndex = 0;

        // -------------------------------------------------
        // DFS helper
        // -------------------------------------------------
        std::function<void(const std::string &)> dfs = [&](const std::string &node) {
            index[node] = currentIndex;
            lowLink[node] = currentIndex;

            currentIndex++;

            stack.push(node);
            onStack.insert(node);

            // ---------------------------------------------
            // Explore neighbors
            // ---------------------------------------------
            if (graph.contains(node)) {
                for (const auto &neighbor
                     : graph.at(node)) {

                    if (!index.contains(neighbor)) {
                        dfs(neighbor);

                        lowLink[node] = std::min(
                            lowLink[node],
                            lowLink[neighbor]
                        );
                    } else if (
                        onStack.contains(neighbor)
                    ) {
                        lowLink[node] = std::min(
                            lowLink[node],
                            index[neighbor]
                        );
                    }
                }
            }

            // ---------------------------------------------
            // Root SCC found
            // ---------------------------------------------
            if (lowLink[node] == index[node]) {
                std::vector<std::string> component;

                while (true) {
                    auto top = stack.top();

                    stack.pop();

                    onStack.erase(top);

                    component.push_back(top);

                    if (top == node) {
                        break;
                    }
                }

                components.push_back(
                    std::move(component)
                );
            }
        };

        // -------------------------------------------------
        // Start DFS
        // -------------------------------------------------
        for (const auto &node: graph | std::views::keys) {
            if (!index.contains(node)) {
                dfs(node);
            }
        }

        return components;
    }

    Parser::ModuleGraph Parser::buildSCCDAG(
        const ModuleGraph &graph,
        const Components &components
    ) {
        std::unordered_map<std::string, int> nodeToSCC;
        ModuleGraph dag;

        // -------------------------------------------------
        // Build node -> SCC map
        // -------------------------------------------------
        for (int i = 0; i < components.size(); ++i) {
            for (const auto &node: components[i]) {
                nodeToSCC[node] = i;
            }
        }

        // -------------------------------------------------
        // Initialize ALL SCC nodes
        // -------------------------------------------------
        for (int i = 0; i < components.size(); ++i) {
            dag[std::to_string(i)] = {};
        }

        // -------------------------------------------------
        // Build DAG edges
        // provider -> consumer
        // -------------------------------------------------
        for (const auto &[node, deps]: graph) {
            const auto consumerIt = nodeToSCC.find(node);

            if (consumerIt == nodeToSCC.end()) {
                continue;
            }

            int consumer = consumerIt->second;

            for (const auto &dep: deps) {
                const auto providerIt = nodeToSCC.find(dep);

                if (providerIt == nodeToSCC.end()) {
                    continue;
                }

                int provider = providerIt->second;

                if (provider == consumer) {
                    continue;
                }

                auto &edges = dag[std::to_string(provider)];
                auto consumerId = std::to_string(consumer);

                if (
                    std::find(
                        edges.begin(),
                        edges.end(),
                        consumerId
                    ) == edges.end()
                ) {
                    edges.push_back(consumerId);
                }
            }
        }

        return dag;
    }

    std::unordered_map<std::string, visitor::nodes::ProgramNode> Parser::parseModules(const std::unordered_map<std::string, std::vector<std::string> > &dependencyGraph, std::unordered_set<std::string> &visited) {
        std::unordered_map<std::string, visitor::nodes::ProgramNode> asts;

        // -------------------------------------------------
        // Compile current module
        // -------------------------------------------------
        Compiler compiler;
        for (const auto &path: dependencyGraph | std::views::keys) {
            // -------------------------------------------------
            // Prevent duplicate parsing
            // -------------------------------------------------
            if (visited.contains(path)) {
                continue;
            }

            visited.insert(path);

            const auto ast = compiler.compile(path);
            const auto program = std::any_cast<visitor::nodes::ProgramNode>(ast);

            asts.emplace(path, std::move(program));
        }

        return asts;
    }

    void Parser::print(const std::unordered_map<std::string, std::vector<std::string> > &graph) {
        json j;

        for (const auto &[file, imports]: graph) {
            j[file] = {
                {"imports", imports}
            };
        }

        std::cout << j.dump(2) << std::endl;
    }


}