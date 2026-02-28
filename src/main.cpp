#include <iostream>
#include <string>
#include "static_vector.hpp"

int main() {
    StaticVector<std::string, 3> vec;

    vec.emplace_back("Hello");
    vec.emplace_back("Embedded");
    vec.emplace_back("World");

    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }

    vec.pop_back();

    std::cout << "Size: " << vec.size() << std::endl;

    return 0;
}
