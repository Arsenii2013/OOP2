#include <iostream>
#include <memory>
#include "skip_list.hpp"

int main() {
    /*
    std::cout << "Hello, World!" << std::endl;
    SkipList<int, int> a{};
    std::pair<const int, int> pair1(1, 12);
    std::pair<const int, int> pair2(2, 34);
    std::pair<const int, int> pair3(3, 56);
    std::pair<const int, int> pair4(4, 78);
    std::cout << (*a.insert(pair1)).second << ' '  << std::endl;
    std::cout << (*a.insert(pair2)).second << ' '  << std::endl;
    std::cout << (*a.insert(pair4)).second << ' '  << std::endl;
    std::cout << (*a.insert(pair3)).second << ' '  << std::endl;
    std::cout << a[1] << a[2] << a[3] << a[4] << std::endl;
    a.erase(2);
    a.erase(++a.begin());
    auto iter = a.begin();
    for(; iter != a.end(); iter++){
        std::cout << (*iter).first << ' ' << (*iter).second << std::endl;
    }*/
    std::vector<int*> a(12);
    std::cout<< a.size() << std::endl;
    return 0;
}
