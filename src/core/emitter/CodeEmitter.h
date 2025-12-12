//
// Created by Brayhan De Aza on 11/27/25.
//

#ifndef CROMIO_CODE_EMITTER_H
#define CROMIO_CODE_EMITTER_H

#include <llvm/IR/Module.h>
#include <string>
#include <vector>

namespace cromio::lowering {
    class CodeEmitter {
       public:
        // Generate LLVM bitcode into a vector of bytes (in memory)
        static std::vector<uint8_t> toMemory(const llvm::Module& module);

        // Write LLVM bitcode to a .bc file
        static void toFile(const llvm::Module& module, const std::string& filename);

        // Generate compiled object code into a vector of bytes (in memory)
        static std::vector<uint8_t> toObjectInMemory(llvm::Module* module);

        // Write compiled object code to a .o file (object file, not executable)
        static void toObjectFile(llvm::Module* module, const std::string& outputPath);

        // Create an executable binary from LLVM module
        static void toExecutable(llvm::Module* module, const std::string& outputPath);
    };

} // namespace cromio::lowering

#endif // CROMIO_CODE_EMITTER_H