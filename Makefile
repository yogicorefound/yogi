.PHONY: build run grammar clean test run-tests

MODULES_DIR := $(CURDIR)/src/modules

test: clean grammar runtime run-tests
build: clean grammar runtime run

run:
	@cd ./build && cmake ..
	@cd ./build && make -j
	@cd ./build && ./yogi ../inputs/main.io
	@cd ./build && ./app

dev:
	@cd ./build && cmake .. -DENABLE_TESTING_FOR_TYPES_HINTS=OFF
	@cd ./build && make -j
	@cd ./build && ./yogi ../inputs/dev.io


run-tests:
	@cd ./build && cmake .. -DENABLE_TESTING=ON
	@cd ./build && make -j run-tests


grammar:
	@cd ./compiler/antlr/tokens && antlr -Dlanguage=Cpp Tokens.g4 -o ../generated/ -visitor
	@cd ./compiler/antlr/grammars && antlr -Dlanguage=Cpp Grammar.g4 -o ../generated/ -visitor

clean:
	@rm -rf build gen .idea && mkdir "build"
	@cd ./compiler/antlr && rm -rf generated .antlr *.tokens *.tokens.txt
	@cd ./compiler/antlr/tokens && rm -rf generated .antlr *.tokens *.tokens.txt

runtime:
	@clang++ -std=c++20 -O3 -emit-llvm -c \
	$(shell find $(MODULES_DIR) -type f -name "*.cpp") \
	-I $(MODULES_DIR) -o $(MODULES_DIR)/runtime.bc


setup: submodules setup_llvm setup_antlr setup_uno_algo


# Setup LLVM
LLVM_DIR := $(CURDIR)/libs/llvm-project/build
setup_llvm:
	@rm -rf $(LLVM_DIR) ./libs/llvm-custom
	@cd ./libs/llvm-project && mkdir "build"
	@cd $(LLVM_DIR) && cmake -G Ninja ../llvm \
	  -DCMAKE_BUILD_TYPE=Release \
	  -DLLVM_ENABLE_PROJECTS="lld" \
	  -DLLVM_TARGETS_TO_BUILD="X86;AArch64" \
	  -DLLVM_ENABLE_RTTI=ON \
	  -DLLVM_ENABLE_ASSERTIONS=ON \
	  -DCMAKE_INSTALL_PREFIX=$(LLVM_DIR)/llvm-custom
	@cd $(LLVM_DIR) && ninja
	@cd $(LLVM_DIR) && ninja install

# Setup ANTLR
ANTLR_DIR := $(CURDIR)/libs/antlr4/runtime/Cpp
setup_antlr:
	@rm -rf $(ANTLR_DIR)/build
	@cd $(ANTLR_DIR) && mkdir "build"

	@cd $(ANTLR_DIR) && cmake -G Ninja -B build
	@cd $(ANTLR_DIR) && cmake --build build

#Uno-Algorithm
UNI_ALGO_DIR := $(CURDIR)/libs/uno-algo
setup_uno_algo:
	@rm -rf $(UNI_ALGO_DIR)/build
	@cd $(UNI_ALGO_DIR) && mkdir "build"

	@cd $(UNI_ALGO_DIR) && cmake -G Ninja -B build
	@cd $(UNI_ALGO_DIR) && cmake --build build


submodules:
	@git submodule update --init --recursive






















