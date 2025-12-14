//
// Created by Brayhan De Aza on 11/27/25.
//

#include <cromio.h>
int* age = nullptr;
int main(const int argc, const char* argv[]) {
    try {
        cromio::Cromio cromio(argc, argv);
        cromio.compile();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}