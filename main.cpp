//
// Created by Brayhan De Aza on 5/4/26.
//

#include "yogi/Yogi.h"


int main(const int argc, const char *argv[]) {
    try {
        const yogi::Yogi yogi(argc, argv);
        yogi.print();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}