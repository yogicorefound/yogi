// Created by Brayhan De Aza on 11/25/25.
//

#include "IR.h"
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "llvm/IR/Verifier.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Linker/Linker.h"

namespace cromio::lowering {
    IR::IR(const std::string& moduleName) {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>(moduleName, *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
    }

    bool IR::linkModule(std::unique_ptr<llvm::Module> other) const {
        llvm::Linker linker(*module);

        // Link into *this->module
        if (constexpr llvm::Linker::Flags flags = llvm::Linker::Flags::None; linker.linkInModule(std::move(other), flags))
            return false; // error

        return true; // success
    }

    llvm::Type* IR::mapDataType(const std::string& typeName) const {
        // Integer
        if (typeName == "int")
            return builder->getInt32Ty(); // default `int` -> i32
        if (typeName == "int8")
            return builder->getInt8Ty();
        if (typeName == "int16")
            return builder->getInt16Ty();
        if (typeName == "int32")
            return builder->getInt32Ty();
        if (typeName == "int64")
            return builder->getInt64Ty();

        // Float
        if (typeName == "float")
            return builder->getDoubleTy(); // default float -> double
        if (typeName == "float32")
            return builder->getFloatTy();
        if (typeName == "float64")
            return builder->getDoubleTy();

        // Boolean
        if (typeName == "bool")
            return builder->getInt1Ty();
        if (typeName == "none")
            return builder->getInt8Ty();
        if (typeName == "str")
            return llvm::PointerType::get(*context, 0); // correct pointer-to-i8 for C strings

        // fallback: 64-bit integer
        return builder->getInt64Ty();
    }

    llvm::Value* IR::promoteToDouble(llvm::Value* v) const {
        if (v->getType()->isDoubleTy())
            return v;

        if (v->getType()->isIntegerTy())
            return builder->CreateSIToFP(v, builder->getDoubleTy(), "int_to_double");

        throw std::runtime_error("Cannot promote value to double");
    }

    llvm::Type* IR::inferType(const json& node) const {
        const std::string kind = node.value("kind", "");

        // Literals: prefer node["type"] when present
        if (kind == "FloatLiteral") {
            const std::string t = node.value("type", std::string("float"));
            return mapDataType(t);
        }

        if (kind == "IntegerLiteral") {
            const std::string t = node.value("type", std::string("int"));
            return mapDataType(t);
        }

        if (kind == "BooleanLiteral")
            return builder->getInt1Ty();
        if (kind == "NoneLiteral")
            return builder->getInt8Ty();
        if (kind == "StringLiteral" || kind == "StringFormatted")
            return llvm::PointerType::get(*context, 0); // correct pointer-to-i8 for C strings

        // VariableDeclaration
        if (kind == "VariableDeclaration") {
            if (!node.contains("DataType") || !node["DataType"].contains("value"))
                throw std::runtime_error("VariableDeclaration missing DataType");

            const std::string dtype = node["DataType"].value("value", "int");
            return mapDataType(dtype);
        }

        // Binary Expression: compute resulting type
        if (kind == "Expression") {
            llvm::Type* LT = inferType(node["left"]);
            llvm::Type* RT = inferType(node["right"]);

            // If either is double/float prefer double if any is double
            if (LT->isDoubleTy() || RT->isDoubleTy())
                return builder->getDoubleTy();

            if (LT->isFloatTy() || RT->isFloatTy()) {
                // if one is float (32) and the other is integer -> float
                if (LT->isFloatTy() || RT->isFloatTy())
                    return builder->getFloatTy();
            }

            // If both integer types, pick the wider integer bitwidth
            if (LT->isIntegerTy() && RT->isIntegerTy()) {
                const auto* LIT = llvm::cast<llvm::IntegerType>(LT);
                const auto* RIT = llvm::cast<llvm::IntegerType>(RT);
                const unsigned Lbits = LIT->getBitWidth();
                const unsigned Rbits = RIT->getBitWidth();
                const unsigned maxBits = Lbits > Rbits ? Lbits : Rbits;

                return builder->getIntNTy(maxBits);
            }

            throw std::runtime_error("Unsupported operand types in Expression");
        }

        throw std::runtime_error("Unknown node kind in inferType: " + kind);
    }

    llvm::Value* IR::literal(const json& node) const {
        const std::string kind = node.value("kind", "");

        if (kind == "FloatLiteral") {
            // For FloatLiteral, "value" contains the actual float number
            if (!node.contains("value"))
                throw std::runtime_error("FloatLiteral missing value field");

            const std::string t = node.value("type", std::string("float"));
            const llvm::Type* ty = mapDataType(t);
            const double val = node.value("value", 0.0);
            if (ty->isDoubleTy())
                return llvm::ConstantFP::get(builder->getDoubleTy(), val);
            if (ty->isFloatTy())
                return llvm::ConstantFP::get(builder->getFloatTy(), static_cast<float>(val));
            return llvm::ConstantFP::get(builder->getDoubleTy(), val);
        }

        if (kind == "IntegerLiteral") {
            // For IntegerLiteral, "value" contains the actual integer number
            if (!node.contains("value"))
                throw std::runtime_error("IntegerLiteral missing value field");

            const std::string t = node.value("type", std::string("int"));
            llvm::Type* ty = mapDataType(t);
            const long long v = node.value("value", 0LL);
            if (ty->isIntegerTy()) {
                const auto* it = llvm::cast<llvm::IntegerType>(ty);
                return llvm::ConstantInt::get(it->getContext(), llvm::APInt(it->getBitWidth(), static_cast<uint64_t>(v), true));
            }
            return llvm::ConstantInt::get(builder->getInt32Ty(), v, true);
        }

        if (kind == "BooleanLiteral")
            return llvm::ConstantInt::get(builder->getInt1Ty(), node.value("value", false) ? 1 : 0);

        if (kind == "NoneLiteral")
            return llvm::ConstantInt::get(builder->getInt8Ty(), 0);

        if (kind == "StringLiteral" || kind == "StringFormatted") {
            return builder->CreateGlobalString(node.value("value", ""), "str");
        }

        // IdentifierLiteral
        if (kind == "IdentifierLiteral") {
            const std::string name = node.value("value", "");
            if (name.empty())
                throw std::runtime_error("IdentifierLiteral missing value");

            const auto it = symbols.find(name);
            if (it == symbols.end())
                throw std::runtime_error("Undefined identifier (IdentifierLiteral): " + name);

            llvm::AllocaInst* alloc = it->second;
            return builder->CreateLoad(alloc->getAllocatedType(), alloc, name + ".load");
        }

        throw std::runtime_error("Unknown literal type: " + kind);
    }

    llvm::Value* IR::expression(const json& node) {
        const std::string kind = node.value("kind", "");

        // If the node is a literal, delegate to literal()
        // NOTE: Added "IdentifierLiteral" to this list!
        if (kind == "FloatLiteral" || kind == "IntegerLiteral" || kind == "IdentifierLiteral" || // <-- This was missing!
            kind == "VariableIdentifier" || kind == "BooleanLiteral" || kind == "NoneLiteral" || kind == "StringLiteral" || kind == "StringFormatted") {
            return literal(node);
        }

        // VariableIdentifier (keeping this for backward compatibility)
        if (kind == "VariableIdentifier") {
            const std::string name = node.value("value", "");
            if (name.empty())
                throw std::runtime_error("VariableIdentifier missing name");

            const auto it = symbols.find(name);
            if (it == symbols.end())
                throw std::runtime_error("Undefined variable: " + name);

            llvm::AllocaInst* alloc = it->second;
            return builder->CreateLoad(alloc->getAllocatedType(), alloc, name + ".load");
        }

        // Binary Expression
        if (kind == "Expression") {
            if (!node.contains("left") || !node.contains("right") || !node.contains("operator"))
                throw std::runtime_error("Malformed Expression node (missing left/right/operator)");

            llvm::Value* L = expression(node["left"]);
            llvm::Value* R = expression(node["right"]);
            const std::string op = node.value("operator", "");

            if (!L || !R)
                throw std::runtime_error("Subexpression produced null");

            // FLOATING POINT OPERATIONS
            if (L->getType()->isDoubleTy() || R->getType()->isDoubleTy()) {
                L = promoteToDouble(L);
                R = promoteToDouble(R);

                if (op == "+")
                    return builder->CreateFAdd(L, R, "fadd");
                if (op == "-")
                    return builder->CreateFSub(L, R, "fsub");
                if (op == "*")
                    return builder->CreateFMul(L, R, "fmul");
                if (op == "/")
                    return builder->CreateFDiv(L, R, "fdiv");
                if (op == "%")
                    return builder->CreateFRem(L, R, "frem");

                throw std::runtime_error("Unsupported operator for double: " + op);
            }

            // If either operand is float (32-bit)
            if (L->getType()->isFloatTy() || R->getType()->isFloatTy()) {
                if (!L->getType()->isFloatingPointTy())
                    L = builder->CreateSIToFP(L, builder->getFloatTy(), "int_to_float");
                if (!R->getType()->isFloatingPointTy())
                    R = builder->CreateSIToFP(R, builder->getFloatTy(), "int_to_float");

                if (op == "+")
                    return builder->CreateFAdd(L, R, "fadd");
                if (op == "-")
                    return builder->CreateFSub(L, R, "fsub");
                if (op == "*")
                    return builder->CreateFMul(L, R, "fmul");
                if (op == "/")
                    return builder->CreateFDiv(L, R, "fdiv");
                if (op == "%")
                    return builder->CreateFRem(L, R, "frem");

                throw std::runtime_error("Unsupported operator for float: " + op);
            }

            // INTEGER OPERATIONS
            if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy()) {
                const auto* Lit = llvm::cast<llvm::IntegerType>(L->getType());
                const auto* Rit = llvm::cast<llvm::IntegerType>(R->getType());

                const unsigned maxBits = std::max(Lit->getBitWidth(), Rit->getBitWidth());
                llvm::IntegerType* opType = builder->getIntNTy(maxBits);

                if (Lit->getBitWidth() < maxBits) {
                    if (Lit->getBitWidth() == 1)
                        L = builder->CreateZExt(L, opType, "zext_l");
                    else
                        L = builder->CreateSExt(L, opType, "sext_l");
                }
                if (Rit->getBitWidth() < maxBits) {
                    if (Rit->getBitWidth() == 1)
                        R = builder->CreateZExt(R, opType, "zext_r");
                    else
                        R = builder->CreateSExt(R, opType, "sext_r");
                }

                if (op == "+")
                    return builder->CreateAdd(L, R, "addtmp");
                if (op == "-")
                    return builder->CreateSub(L, R, "subtmp");
                if (op == "*")
                    return builder->CreateMul(L, R, "multmp");
                if (op == "/")
                    return builder->CreateSDiv(L, R, "divtmp");
                if (op == "%")
                    return builder->CreateSRem(L, R, "modtmp");

                throw std::runtime_error("Unsupported integer operator: " + op);
            }

            throw std::runtime_error("Unsupported operand types in Expression: " + op);
        }

        if (kind == "VariableDeclaration")
            throw std::runtime_error("VariableDeclaration cannot appear inside an expression");

        throw std::runtime_error("Invalid expression node: " + kind);
    }

    llvm::AllocaInst* IR::createEntryBlockAlloca(llvm::Function* function, llvm::Type* type, const std::string& name) {
        llvm::IRBuilder tmpBuilder(&function->getEntryBlock(), function->getEntryBlock().begin());
        return tmpBuilder.CreateAlloca(type, nullptr, name);
    }

    llvm::Value* IR::variableAssignment(const json& node) {
        if (!node.contains("Identifier") || !node.contains("value"))
            throw std::runtime_error("Malformed VariableAssignment node");

        const std::string name = node["Identifier"].value("value", "");
        if (name.empty())
            throw std::runtime_error("VariableAssignment missing Identifier");

        const auto it = symbols.find(name);
        if (it == symbols.end())
            throw std::runtime_error("Assign to undefined variable: " + name);

        llvm::AllocaInst* slot = it->second;
        llvm::Type* varType = slot->getAllocatedType();

        llvm::Value* rhs = expression(node["value"]);
        if (!rhs)
            throw std::runtime_error("Variable assignment RHS produced null");

        // Convert if necessary
        if (rhs->getType() != varType) {
            // integer -> float
            if (rhs->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                // Use unsigned conversion for booleans, signed for others
                if (rhs->getType()->getIntegerBitWidth() == 1)
                    rhs = builder->CreateUIToFP(rhs, varType, "assign_bool_to_fp");
                else
                    rhs = builder->CreateSIToFP(rhs, varType, "assign_int_to_fp");
            } else if (rhs->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                rhs = builder->CreateFPToSI(rhs, varType, "assign_fp_to_int");
            } else if (rhs->getType()->isIntegerTy() && varType->isIntegerTy()) {
                // extend/truncate integers as needed
                const auto* Rit = llvm::cast<llvm::IntegerType>(rhs->getType());
                if (auto* Vt = llvm::cast<llvm::IntegerType>(varType); Rit->getBitWidth() < Vt->getBitWidth()) {
                    // Zero-extend for booleans (i1), sign-extend for other integers
                    if (Rit->getBitWidth() == 1)
                        rhs = builder->CreateZExt(rhs, Vt, "assign_zext");
                    else
                        rhs = builder->CreateSExt(rhs, Vt, "assign_sext");
                } else if (Rit->getBitWidth() > Vt->getBitWidth())
                    rhs = builder->CreateTrunc(rhs, Vt, "assign_trunc");
            } else if (rhs->getType()->isPointerTy() && varType->isPointerTy()) {
                rhs = builder->CreateBitCast(rhs, varType, "assign_bitcast");
            } else {
                throw std::runtime_error("Cannot convert assignment RHS to variable type for: " + name);
            }
        }

        builder->CreateStore(rhs, slot);
        return rhs;
    }

    llvm::Value* IR::variableDeclaration(const json& node) {
        if (!node.contains("DataType") || !node.contains("Identifier") || !node.contains("value"))
            throw std::runtime_error("Malformed VariableDeclaration node");

        // Extract identifier name
        std::string variableName;
        if (node["Identifier"].contains("value")) {
            variableName = node["Identifier"].value("value", "");
        } else {
            throw std::runtime_error("VariableDeclaration Identifier missing 'value' field");
        }

        if (variableName.empty())
            throw std::runtime_error("VariableDeclaration has empty identifier name");

        // Extract data type
        std::string dataType = "int";
        if (node["DataType"].contains("value")) {
            dataType = node["DataType"].value("value", "int");
        }

        llvm::Type* varType = mapDataType(dataType);

        llvm::Function* currentFn = builder->GetInsertBlock()->getParent();
        if (!currentFn)
            throw std::runtime_error("Must be inside a function to declare variable");

        // Create alloca in entry block
        llvm::AllocaInst* allocaInst = createEntryBlockAlloca(currentFn, varType, variableName);
        symbols[variableName] = allocaInst;

        // Evaluate initializer expression
        llvm::Value* initVal = expression(node["value"]);
        if (!initVal)
            throw std::runtime_error("Variable initializer produced null");

        // Convert initializer to variable type if necessary
        if (initVal->getType() != varType) {
            // Integer to floating point
            if (initVal->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                // Use unsigned conversion for booleans, signed for others
                if (initVal->getType()->getIntegerBitWidth() == 1)
                    initVal = builder->CreateUIToFP(initVal, varType, "init_bool_to_fp");
                else
                    initVal = builder->CreateSIToFP(initVal, varType, "init_int_to_fp");
            }
            // Floating point to integer
            else if (initVal->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                initVal = builder->CreateFPToSI(initVal, varType, "init_fp_to_int");
            }
            // Integer to integer (different widths)
            else if (initVal->getType()->isIntegerTy() && varType->isIntegerTy()) {
                const auto* initType = llvm::cast<llvm::IntegerType>(initVal->getType());

                if (const auto* targetType = llvm::cast<llvm::IntegerType>(varType); initType->getBitWidth() < targetType->getBitWidth()) {
                    // Zero-extend for booleans (i1), sign-extend for other integers
                    if (initType->getBitWidth() == 1)
                        initVal = builder->CreateZExt(initVal, varType, "init_zext");
                    else
                        initVal = builder->CreateSExt(initVal, varType, "init_sext");
                } else if (initType->getBitWidth() > targetType->getBitWidth()) {
                    // Truncate for narrower type
                    initVal = builder->CreateTrunc(initVal, varType, "init_trunc");
                }
            }
            // Pointer to pointer
            else if (initVal->getType()->isPointerTy() && varType->isPointerTy()) {
                initVal = builder->CreateBitCast(initVal, varType, "init_bitcast");
            } else {
                throw std::runtime_error("Cannot convert initializer to variable type for: " + variableName);
            }
        }

        // Store the initialized value
        builder->CreateStore(initVal, allocaInst);
        return allocaInst;
    }

    std::unique_ptr<llvm::Module> IR::loadBitcode(const std::string& path, llvm::LLVMContext& context) {
        llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> mb = llvm::MemoryBuffer::getFile(path);
        if (!mb)
            return nullptr; // silently ignore if file can't be opened

        llvm::Expected<std::unique_ptr<llvm::Module>> modOrErr = llvm::parseBitcodeFile(mb.get()->getMemBufferRef(), context);

        if (!modOrErr)
            return nullptr; // silently ignore parse errors

        return std::move(*modOrErr);
    }

    llvm::Value* IR::arrayDeclaration(const json& node) {
        if (!node.contains("Type") || !node.contains("Identifier") || !node.contains("value"))
            throw std::runtime_error("Malformed ArrayDeclaration node");

        const std::string arrayName = node["Identifier"].value("value", "");
        const std::string dataType = node["Type"].value("value", "int");

        llvm::Type* elementType = mapDataType(dataType);

        // Determine array size
        int arraySize = 0;
        if (node.contains("Type") && node["Type"].contains("size")) {
            if (const std::string sizeVal = node["Type"]["size"]; sizeVal == "auto") {
                if (!node["value"].contains("items") || !node["value"]["items"].is_array())
                    throw std::runtime_error("ArrayAssignment items missing for auto-size array");

                arraySize = node["value"]["items"].size();
            } else {
                arraySize = std::stoi(sizeVal);
            }
        } else {
            throw std::runtime_error("ArrayDeclaration missing ArraySize");
        }

        // Allocate array in entry block
        llvm::ArrayType* arrType = llvm::ArrayType::get(elementType, arraySize);
        llvm::Function* currentFn = builder->GetInsertBlock()->getParent();
        if (!currentFn)
            throw std::runtime_error("Must be inside a function to declare array");

        llvm::AllocaInst* allocaInst = createEntryBlockAlloca(currentFn, arrType, arrayName);
        symbols[arrayName] = allocaInst;

        // Initialize array elements if provided
        if (node["value"].contains("items") && node["value"]["items"].is_array()) {
            int idx = 0;
            for (const auto& item : node["value"]["items"]) {
                llvm::Value* val = expression(item);

                // Get element pointer
                llvm::Value* gep = builder->CreateGEP(arrType, allocaInst, {builder->getInt32(0), builder->getInt32(idx)}, arrayName + "_idx" + std::to_string(idx));

                // Cast if necessary
                if (val->getType() != elementType) {
                    // bool -> int (i1 -> i8/i32/i64/etc)
                    if (val->getType()->isIntegerTy(1) && elementType->isIntegerTy() && elementType->getIntegerBitWidth() > 1) {
                        val = builder->CreateZExt(val, elementType, "bool_to_int");
                    }
                    // int -> bool (i32 -> i1)
                    else if (val->getType()->isIntegerTy() && val->getType()->getIntegerBitWidth() > 1 && elementType->isIntegerTy(1)) {
                        val = builder->CreateICmpNE(val, llvm::ConstantInt::get(val->getType(), 0), "int_to_bool");
                    }
                    // int <-> int
                    else if (val->getType()->isIntegerTy() && elementType->isIntegerTy()) {
                        const auto* vIt = llvm::cast<llvm::IntegerType>(val->getType());

                        if (const auto* tIt = llvm::cast<llvm::IntegerType>(elementType); vIt->getBitWidth() < tIt->getBitWidth())
                            val = builder->CreateSExt(val, elementType, "elem_sext");

                        else if (vIt->getBitWidth() > tIt->getBitWidth())
                            val = builder->CreateTrunc(val, elementType, "elem_trunc");
                    }
                    // int <-> float
                    else if (val->getType()->isIntegerTy() && elementType->isFloatingPointTy())
                        val = builder->CreateSIToFP(val, elementType, "elem_int_to_fp");
                    else if (val->getType()->isFloatingPointTy() && elementType->isIntegerTy())
                        val = builder->CreateFPToSI(val, elementType, "elem_fp_to_int");
                    else
                        throw std::runtime_error("Cannot convert array element type");
                }

                builder->CreateStore(val, gep);
                idx++;
            }
        }

        return allocaInst;
    }

    void IR::loadAndLinkModulesFromFolder() const {
        const std::string folderPath = "../modules"; // adjust as needed

        if (!std::filesystem::exists(folderPath))
            return; // folder doesn't exist, silently ignore

        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (!entry.is_regular_file())
                continue;

            const std::string path = entry.path().string();

            // Only process .bc files
            if (entry.path().extension() != ".bc")
                continue;

            try {
                if (auto extMod = loadBitcode(path, *context); !linkModule(std::move(extMod))) {
                    llvm::errs() << "Warning: Failed to link module: " << path << "\n";
                    continue; // skip this module
                }

                llvm::errs() << "Linked module: " << path << "\n";

            } catch (...) {
                llvm::errs() << "Warning: Skipping module (load/link failed): " << path << "\n";
                // continue silently
            }
        }
    }

    llvm::Module* IR::generate(const json& ast) {
        // Load & link external modules automatically
        loadAndLinkModulesFromFolder();

        // Then generate the AST normally
        program(ast);
        return module.get();
    }

    llvm::Value* IR::program(const json& node) {
        if (node.value("kind", "") != "Program")
            throw std::runtime_error("Top-level node must be Program");

        auto& body = node["Body"];
        if (!body.is_array())
            throw std::runtime_error("Program Body missing");

        // Create main function with i32 return type
        llvm::Type* retType = builder->getInt32Ty();

        auto* fnType = llvm::FunctionType::get(retType, false);
        auto* fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, "main", module.get());

        auto* entry = llvm::BasicBlock::Create(*context, "entry", fn);
        builder->SetInsertPoint(entry);

        // Iterate statements
        for (const auto& stmt : body) {
            if (const std::string kind = stmt.value("kind", ""); kind == "VariableDeclaration")
                variableDeclaration(stmt);
            else if (kind == "ArrayDeclaration")
                arrayDeclaration(stmt);
            else if (kind == "VariableReAssignment")
                variableAssignment(stmt);
            else
                expression(stmt);
        }

        // Default return 0 (i32)
        builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

        if (llvm::verifyFunction(*fn, &llvm::errs()))
            throw std::runtime_error("IR verification failed");

        return fn;
    }
} // namespace cromio::lowering