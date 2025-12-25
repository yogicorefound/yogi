//
// Created by Brayhan De Aza on 11/27/25.
//

#include "includes/yogi/yogi.h"

int* age = nullptr;
int main(const int argc, const char* argv[]) {
    try {
        yogi::Yogi yogi(argc, argv);
        yogi.compile();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}