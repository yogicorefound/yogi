//
// Created by Brayhan De Aza on 5/4/26.
//

#include "yogi/Yogi.h"

int main(const int argc, const char *argv[]) {
    try {
        const yogi::Yogi yogi(argc, argv);
        yogi.print();

        std::cout << LLD_PATH << std::endl;  // prints the path

        // or use it to invoke the linker:
        std::string linker = LLD_PATH;
        std::string cmd = linker + " -o output input.o";
        std::system(cmd.c_str());

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}