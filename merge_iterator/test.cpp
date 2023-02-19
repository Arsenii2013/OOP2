#include "gtest/gtest.h"
#include "merge_iterator_concept.hpp"
#include "merge_iterator_noconcept.hpp"

#include <functional>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <vector>

// emty inishializer
namespace Concept {

    TEST(CREATION, EMPTY) {
        std::vector<int> a{};
        auto it = a.begin();
        MergingIterator test({IteratorPair{it, it}, IteratorPair{it, it}});
        auto end = MergingIterator<decltype(it)>();
        EXPECT_EQ(end, test);
        EXPECT_ANY_THROW(++test);
    }

    TEST(DIFSIZES, 2) {
//std::iterator<std::input_iterator_tag, int> it;
        std::vector<int> a{4, 2, 0};
        std::vector<int> b{3, 1, 0, -1};
        std::vector<int> expect{4, 3, 2, 1, 0, 0, -1};
        std::vector<int> result;
        MergingIterator test({IteratorPair{a.begin(), a.end()}, IteratorPair{b.begin(), b.end()}});
        std::copy(test, MergingIterator<decltype(a.begin())>(), std::back_inserter(result));
        EXPECT_TRUE(test != MergingIterator<decltype(a.begin())>());
        EXPECT_EQ(expect, result);
    }

    TEST(DIFSIZES, 3) {
//std::iterator<std::input_iterator_tag, int> it;
        std::vector<int> a{4, 2, 0};
        std::vector<int> b{3, 1, 0, -1};
        std::vector<int> c{17, 11};
        std::vector<int> expect{17, 11, 4, 3, 2, 1, 0, 0, -1};
        std::vector<int> result;
        auto it = a.begin();
        it++;
        MergingIterator test(
                {IteratorPair{a.begin(), a.end()},
                 IteratorPair{b.begin(), b.end()},
                 IteratorPair{c.begin(), c.end()}});

        std::copy(test, MergingIterator<decltype(a.begin())>(), std::back_inserter(result));
        EXPECT_EQ(expect, result);
    }

    TEST(DIFTYPES, VECTOR_ITERATOR) {
//std::iterator<std::input_iterator_tag, int> it;
        std::vector<int> a{4, 2, 0};
        std::vector<int> b{3, 1, 0, -1};
        std::vector<int> expect{4, 3, 2, 1, 0, 0, -1};
        std::vector<int> result;
        auto it = a.begin();
        it++;
        MergingIterator test(
                {IteratorPair{a.begin(), a.end()},
                 IteratorPair{b.begin(), b.end()}});

        std::copy(test, MergingIterator<decltype(a.begin())>(), std::back_inserter(result));
        EXPECT_EQ(expect, result);
    }

    TEST(DIFTYPES, LIST_ITERATOR) {
        std::list<int> a{4, 2, 0};
        std::list<int> b{3, 1, 0, -1};
        std::list<int> expect{4, 3, 2, 1, 0, 0, -1};
        std::list<int> result;
        auto it = a.begin();
        it++;
        MergingIterator test(
                {IteratorPair{a.begin(), a.end()},
                 IteratorPair{b.begin(), b.end()}});

        std::copy(test, MergingIterator<decltype(a.begin())>(), std::back_inserter(result));
        EXPECT_EQ(expect, result);
    }


    TEST(DIFTYPES, MERGE_ITERATOR) {
        std::vector<int> a{4, 2, 0};
        std::vector<int> b{3, 1, 0, -1};
        std::vector<int> expect{ 4, 4, 3, 3, 2, 2, 1, 1, 0, 0, 0, 0, -1, -1 };
        std::vector<int> result;
        auto it = a.begin();
        it++;
        MergingIterator test1(
                {IteratorPair{a.begin(), a.end()},
                 IteratorPair{b.begin(), b.end()}});
        MergingIterator test2(
                {IteratorPair{a.begin(), a.end()},
                IteratorPair{b.begin(), b.end()}});

        MergingIterator test3(
                {IteratorPair{test1, MergingIterator<decltype(a.begin())>()},
                IteratorPair{test2, MergingIterator<decltype(a.begin())>()}});
        EXPECT_TRUE(test1 == test2);
        std::copy(test3, MergingIterator<MergingIterator<decltype(a.begin())>>(), std::back_inserter(result));
        EXPECT_EQ(expect, result);
    }

    TEST(COMPARE, LAMBDA) {
        std::vector<int> a{4, 2, 0};
        std::vector<int> b{3, 1, 0, -1};
        std::vector<int> expect{4, 3, 2, 1, 0, 0, -1};
        std::vector<int> result;
        auto it = a.begin();
        it++;
        MergingIterator test(
                {IteratorPair{a.begin(), a.end()},
                 IteratorPair{b.begin(), b.end()}}, [](const int a, const int b) -> bool{ return a < b;});

        std::copy(test, decltype(test)(), std::back_inserter(result));
        EXPECT_EQ(expect, result);
    }
    bool compare(int a, int b){
        return a < b;
    }

    TEST(COMPARE, FUNCTION) {
        std::vector<int> a{4, 2, 0};
        std::vector<int> b{3, 1, 0, -1};
        std::vector<int> expect{4, 3, 2, 1, 0, 0, -1};
        std::vector<int> result;
        auto it = a.begin();
        it++;
        MergingIterator test(
                {IteratorPair{a.begin(), a.end()},
                 IteratorPair{b.begin(), b.end()}}, compare);

        std::copy(test, MergingIterator<decltype(a.begin()), bool (*)(int, int)>(), std::back_inserter(result));
        EXPECT_EQ(expect, result);
    }
}