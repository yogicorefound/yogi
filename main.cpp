//
// Created by Brayhan De Aza on 5/4/26.
//

#include <iostream>
#include "yogi/Yogi.h"

int main(const int argc, const char *argv[]) {
    try {
        const yogi::Yogi yogi(argc, argv);
        // yogi.print();

        // or use it to invoke the linker:
        const std::string linker = LLD_PATH;
        const std::string cmd = linker + " -o output input.o";
        std::system(cmd.c_str());

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}