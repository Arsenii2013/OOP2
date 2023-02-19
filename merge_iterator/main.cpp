#include <iostream>
#include "merge_iterator_concept.hpp"
#include <iterator>
#include <vector>
using namespace std;

int main() {
    std::vector a{1, 1, 1, 1};
    auto it = a.begin();
    //*it;
    //MergingIterator(it, it, it, it);
    //MergingIterator<std::iterator<std::output_iterator_tag, int>>();
    cout << "Hello world";
    return 0;
}
