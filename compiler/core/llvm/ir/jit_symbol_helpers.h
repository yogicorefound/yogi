#pragma once

#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/Mangling.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/Support/Error.h"

namespace jit_helpers {

/// Register a single native function as an absolute JIT symbol.
///
/// Example:
///   registerSymbol(*LLJIT, "create_string", &create_string);
template <typename FuncPtr>
llvm::Error registerSymbol(llvm::orc::LLJIT& JIT,
                           llvm::StringRef Name,
                           FuncPtr Func)
{
    auto& ES     = JIT.getExecutionSession();
    auto& Dylib  = JIT.getMainJITDylib();

    llvm::orc::MangleAndInterner Mangle(ES, JIT.getDataLayout());

    return Dylib.define(
        llvm::orc::absoluteSymbols({
            {
                Mangle(Name),
                llvm::orc::ExecutorSymbolDef(
                    llvm::orc::ExecutorAddr::fromPtr(
                        reinterpret_cast<void*>(Func)),
                    llvm::JITSymbolFlags::Exported |
                    llvm::JITSymbolFlags::Callable
                )
            }
        })
    );
}

/// Register multiple native functions at once using an initializer list.
///
/// Example:
///   registerSymbols(*LLJIT, {
///       {"create_string", (void*) &create_string},
///       {"destroy_string", (void*) &destroy_string},
///   });
inline llvm::Error registerSymbols(
    llvm::orc::LLJIT& JIT,
    std::initializer_list<std::pair<llvm::StringRef, void*>> Symbols)
{
    auto& ES    = JIT.getExecutionSession();
    auto& Dylib = JIT.getMainJITDylib();

    llvm::orc::MangleAndInterner Mangle(ES, JIT.getDataLayout());
    llvm::orc::SymbolMap SymMap;

    for (auto& [Name, Ptr] : Symbols) {
        SymMap[Mangle(Name)] = llvm::orc::ExecutorSymbolDef(
            llvm::orc::ExecutorAddr::fromPtr(Ptr),
            llvm::JITSymbolFlags::Exported |
            llvm::JITSymbolFlags::Callable
        );
    }

    return Dylib.define(llvm::orc::absoluteSymbols(std::move(SymMap)));
}

/// Convenience wrapper that calls llvm::cantFail on registerSymbol.
/// Use only when you are certain registration cannot fail.
template <typename FuncPtr>
void registerSymbolOrDie(llvm::orc::LLJIT& JIT,
                         llvm::StringRef Name,
                         FuncPtr Func)
{
    llvm::cantFail(registerSymbol(JIT, Name, Func));
}

/// Convenience wrapper that calls llvm::cantFail on registerSymbols.
/// Use only when you are certain registration cannot fail.
inline void registerSymbolsOrDie(
    llvm::orc::LLJIT& JIT,
    std::initializer_list<std::pair<llvm::StringRef, void*>> Symbols)
{
    llvm::cantFail(registerSymbols(JIT, std::move(Symbols)));
}

} // namespace jit_helpers