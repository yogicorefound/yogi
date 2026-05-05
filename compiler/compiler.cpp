//
// Created by Brayhan De Aza on 5/4/26.
//


#include <iostream>
#include "wrapper/wrapper.h"

int main(const int argc, const char* argv[]) {

    try {
        yogi::Yogi yogi(argc, argv);
        yogi.compile();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}