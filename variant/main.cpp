#include <iostream>
#include "variant.hpp"
#include <vector>
#include <string>

int main() {
    Variant<std::string, int> b(In_place_index<0>, "aboba");
    Variant<std::string, int> c(In_place_index<0>, "aboba");
    //Get<0>(b) = 49;
    std::cout << Get<0>(b) << std::endl;
    b.emplace<int>(12);
    //std::cout << Get<0>(b) << std::endl;
    std::cout << Get<int>(b) << std::endl;
    //std::cout << (b == c) << std::endl;
}
