//
// Created by Brayhan De Aza on 5/12/26.
//

#include "Linker.h"

#include <vector>
#include <string>
#include <unistd.h>
#include <filesystem>

namespace yogi::compiler::core::linker {
    // std::string writeObjectFile(const std::string &name,
    //     const std::vector<uint8_t> &data) {
    //
    //     std::filesystem::path path = std::filesystem::temp_directory_path() / (name + ".o");
    //
    //     std::ofstream out(path, std::ios::binary);
    //     out.write(reinterpret_cast<const char *>(data.data()), data.size());
    //     out.close();
    //
    //     return path.string();
    // }

    void Linker::link() {
        std::vector<char *> args = {
            const_cast<char *>(LLD_PATH),
            const_cast<char *>("main.o"),
            const_cast<char *>("utils.o"),
            const_cast<char *>("auth.o"),
            const_cast<char *>("-o"),
            const_cast<char *>("output"),
            nullptr
        };

        execvp(args[0], args.data());

        // only reached if exec fails
        perror("ld.lld failed");
    }



}