//
// DictionaryVisitor.cpp - AST version
//

#include "DictionaryVisitor.h"
#include "ast/nodes/nodes.h"

namespace cromio::visitor {
    using namespace cromio::visitor::nodes;

    Position makeStart(const antlr4::ParserRuleContext* ctx) {
        return {ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    }

    Position makeEnd(const antlr4::ParserRuleContext* ctx) {
        return {ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
    }

    std::any DictionaryVisitor::visitDictionaryDeclaration(Grammar::DictionaryDeclarationContext* ctx) {
        // Extract the type information
        const auto typeAny = visit(ctx->dictionaryDeclarationType());
        const auto typeNode = std::any_cast<std::shared_ptr<DictionaryTypeNode>>(typeAny);

        // Create DictionaryDeclarationNode
        auto* decl = new DictionaryDeclarationNode(ctx->IDENTIFIER()->getText(), typeNode->keyType, typeNode->valueType, makeStart(ctx), makeEnd(ctx));

        // Visit assignment items
        for (auto* child : ctx->dictionaryAssignmentBody()) {
            auto anyPair = visit(child);
            auto pairNode = std::any_cast<std::shared_ptr<DictionaryPairNode>>(anyPair);

            decl->pairs.push_back(*pairNode);
        }

        decl->size = decl->pairs.size();

        return std::shared_ptr<DictionaryDeclarationNode>(decl);
    }

    std::any DictionaryVisitor::visitDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext* ctx) {
        const auto keyAny = visit(ctx->literal());
        const auto valAny = visit(ctx->expression());
        const auto keyNode = keyAny;
        const auto valueNode = valAny;

        auto* pair = new DictionaryPairNode(keyNode, valueNode, makeStart(ctx), makeEnd(ctx));
        return std::shared_ptr<DictionaryPairNode>(pair);
    }

    std::any DictionaryVisitor::visitDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext* ctx) {
        const auto keyAny = visit(ctx->dictionaryTypeElement(0));
        const auto valueAny = visit(ctx->dictionaryTypeElement(1));
        const auto keyNode = std::any_cast<std::shared_ptr<DataTypeNode>>(keyAny);
        const auto valueNode = std::any_cast<std::shared_ptr<DataTypeNode>>(valueAny);

        auto* node = new DictionaryTypeNode(keyNode->typeName, valueNode->typeName, makeStart(ctx), makeEnd(ctx));
        return std::shared_ptr<DictionaryTypeNode>(node);
    }

    std::any DictionaryVisitor::visitDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext* ctx) {
        const std::string type = ctx->dictionaryDataType()->getText() + "[]";
        if (ctx->expression()) {
            auto sizeAny = visit(ctx->expression());
            // store expression raw; semantic phase will validate
        }

        auto* node = new DataTypeNode(type, makeStart(ctx), makeEnd(ctx));
        return std::shared_ptr<DataTypeNode>(node);
    }

    std::any DictionaryVisitor::visitDictionaryTypeElement(Grammar::DictionaryTypeElementContext* ctx) {
        if (ctx->dictionaryDeclarationTypeArray()) {
            return visit(ctx->dictionaryDeclarationTypeArray());
        }
        return visit(ctx->dictionaryDataType());
    }

    std::any DictionaryVisitor::visitDictionaryDataType(Grammar::DictionaryDataTypeContext* ctx) {
        auto* node = new DataTypeNode(ctx->getText(), makeStart(ctx), makeEnd(ctx));

        return std::shared_ptr<DataTypeNode>(node);
    }

} // namespace cromio::visitor
