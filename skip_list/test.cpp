#include "gtest/gtest.h"
#include "skip_list.hpp"
/*
TEST(Node, Creation) {
    {
        Node<int, int> empty;
        EXPECT_ANY_THROW((void)empty.get_value());
        EXPECT_EQ(false, empty);
        EXPECT_ANY_THROW(empty.next(level_t(1)));
    }
    {
        int a = 1, b = 2;
        Node<int, int> node1(a, b);
        EXPECT_EQ(1, node1.get_value().first);
        EXPECT_EQ(2, node1.get_value().second);
        EXPECT_EQ(true, node1);
        EXPECT_ANY_THROW(node1.next(1));
    }
    {
        Node<int, int> node1(1, 2);
        EXPECT_EQ(1, node1.get_value().first);
        EXPECT_EQ(2, node1.get_value().second);
        EXPECT_EQ(true, node1);
        EXPECT_ANY_THROW(node1.next(1));
    }
}


TEST(Node, EQ) {
    {
        Node<int, int> node1(1, 2);
        int a = 1, b = 2;
        Node<int, int> node2(a, b);
        EXPECT_TRUE(node1 == node2);
        EXPECT_FALSE(node1 != node2);
    }
    {
        Node<int, int> node1(1, 2);
        Node<int, int> node2(2, 3);
        EXPECT_FALSE(node1 == node2);
        EXPECT_TRUE(node1 != node2);
    }
    {
        std::vector links{std::make_shared<Node<int, int>>(1, 2),
                          std::make_shared<Node<int, int>>(2, 3),
                          std::make_shared<Node<int, int>>(3, 4),
                          std::make_shared<Node<int, int>>(4, 5)};
        Node<int, int> statement(1, 2,
                                 std::allocator<std::pair<const int, int>>(),
                                 links);
        Node<int, int> equal(1, 2,
                             std::allocator<std::pair<const int, int>>(),
                             links);
        Node<int, int> not_equal(1, 2,
                             std::allocator<std::pair<const int, int>>(),
                             {nullptr, nullptr, nullptr, nullptr});
        EXPECT_TRUE(statement == equal);
        EXPECT_FALSE(statement != equal);
        EXPECT_TRUE(statement != not_equal);
        EXPECT_FALSE(statement == not_equal);
    }
}*/
class OneNodeAllocator : std::allocator<std::pair<const int, int>>{
public:
    using type = std::pair<const int, int>;
    using value_type = std::pair<const int, int>;
    using Traits = std::allocator_traits<OneNodeAllocator>;
    using size_type = void;
    using difference_type = void;
    using pointer = std::add_pointer_t<std::pair<const int, int>>;
    using const_pointer = std::add_const_t<std::add_pointer_t<std::pair<const int, int>>>;
    using reference = std::add_lvalue_reference_t<std::pair<const int, int>>;
    using const_reference = std::add_const_t<std::add_lvalue_reference_t<std::pair<const int, int>>>;
    std::pair<const int, int> *pair;
    OneNodeAllocator(){
        pair = new std::pair<const int, int>;
    }

    OneNodeAllocator(const OneNodeAllocator& other){
        pair = other.pair;
    }

    ~OneNodeAllocator(){
    }

    std::pair<const int, int> *allocate(int cnt) const{
        if(cnt != 1){
            throw std::runtime_error("bad alloc");
        }
        return pair;
    }

    void deallocate(std::pair<const int, int> * prt, int cnt) const{
        if(prt != pair || cnt != 1){
            throw std::runtime_error("bad dealloc");
        }
    }

    void del(){
        delete pair;
    }
};

/*
TEST(Node, NotStandartAlloc) {
    OneNodeAllocator alloc;
    Node<int, int, OneNodeAllocator> node1(1, 2, alloc, {});
    EXPECT_EQ(*alloc.pair, node1.get_value());
    alloc.del();
}*/

TEST(SkipList, Creation) {}
   // {
       /* SkipList<int, int> list;
        EXPECT_EQ(list.size(), 0);
        EXPECT_TRUE(list.empty());
        EXPECT_ANY_THROW(list[0]);
        EXPECT_ANY_THROW(list.at(0));
    }
    {
        SkipList<int, int, std::greater<int>> list{std::greater<int>{}, std::allocator<std::pair<const int, int>>{}};
        EXPECT_EQ(list.size(), 0);
        EXPECT_TRUE(list.empty());
        EXPECT_ANY_THROW(list[0]);
        EXPECT_ANY_THROW(list.at(0));
    }
    {
        SkipList<int, int> list1;
        auto list = list1;
        EXPECT_EQ(list.size(), 0);
        EXPECT_TRUE(list.empty());
        EXPECT_ANY_THROW(list[0]);
        EXPECT_ANY_THROW(list.at(0));
    }
}

TEST(SkipList, Insert) {
    {
        SkipList<int, int> list;
        EXPECT_EQ((*list.insert({1, 2})).second, 2);
        std::pair<const int, int> pair1(3, 4);
        EXPECT_TRUE((*list.insert(pair1)) == pair1);
        EXPECT_EQ(list[1], 2);
        EXPECT_EQ(list[3], 4);
        EXPECT_EQ(list.size(), 2);
    }
    {
        SkipList<int, int, std::greater<int>> list{std::greater<int>{}, std::allocator<std::pair<const int, int>>{}};
        EXPECT_EQ((*list.insert({1, 2})).second, 2);
        std::pair<const int, int> pair1(3, 4);
        EXPECT_TRUE((*list.insert(pair1)) == pair1);
        EXPECT_EQ(list[1], 2);
        EXPECT_EQ(list[3], 4);
        EXPECT_EQ(list.size(), 2);
    }
}

TEST(SkipList, Erase) {
    {
        SkipList<int, int> list;
        list.insert({1, 2});
        list.insert({2, 3});
        list.insert({3, 4});
        list.insert({4, 5});
        list.erase(3);
        EXPECT_ANY_THROW(list[3]);
        EXPECT_EQ(list.size(), 3);
        list.erase(list.begin());
        EXPECT_ANY_THROW(list[1]);
        EXPECT_EQ(list.size(), 2);
        list.erase(2);
        list.erase(4);
        EXPECT_EQ(list.size(), 0);
        EXPECT_TRUE(list.empty());
    }
    {
        SkipList<int, int, std::greater<int>> list{std::greater<int>{}, std::allocator<std::pair<const int, int>>{}};
        list.insert({1, 2});
        list.insert({2, 3});
        list.insert({3, 4});
        list.insert({4, 5});
        list.erase(3);
        EXPECT_ANY_THROW(list[3]);
        EXPECT_EQ(list.size(), 3);
        list.erase(list.begin());
        EXPECT_ANY_THROW(list[4]);
        EXPECT_EQ(list.size(), 2);
        list.erase(1);
        list.erase(2);
        EXPECT_EQ(list.size(), 0);
        EXPECT_TRUE(list.empty());
    }
}

TEST(SkipList, Clear) {
    SkipList<int, int> list;
    list.insert({1, 2});
    list.insert({2, 3});
    list.insert({3, 4});
    list.insert({4, 5});
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(SkipList, Swap) {
    SkipList<int, int> list1;
    list1.insert({1, 2});
    list1.insert({2, 3});
    list1.insert({3, 4});
    list1.insert({4, 5});
    SkipList<int, int> list2;
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 0);
    list1.swap(list2);
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2[1], 2);
    EXPECT_EQ(list2[2], 3);
    EXPECT_EQ(list2[3], 4);
    EXPECT_EQ(list2[4], 5);
}

TEST(SkipList, Find) {
    SkipList<int, int> list;
    list.insert({1, 2});
    list.insert({2, 3});
    list.insert({3, 4});
    list.insert({4, 5});
    EXPECT_EQ(list.find(1)->second, 2);
    EXPECT_EQ(list.find(2)->second, 3);
    EXPECT_EQ(list.find(3)->second, 4);
    EXPECT_EQ(list.find(4)->second, 5);
}
/*
TEST(SkipList, NotStandartAlloc) {
    OneNodeAllocator alloc;
    SkipList<int, int, std::less<int>, OneNodeAllocator> list(std::less<int>(), alloc);
    EXPECT_EQ((*list.insert({1, 2})).second, 2);
    std::pair<const int, int> pair1(3, 4);
    EXPECT_TRUE((*list.insert(pair1)) == pair1);
    EXPECT_ANY_THROW(list[1]); // все верно, втавке второй ноды значения лежащие в первой поменяются
    EXPECT_EQ(list[3], 4);
    alloc.del();
}*/
/*
TEST(Iterator, Empty){
    SkipList<int, int> list;
    EXPECT_EQ(list.begin(), list.end());
    EXPECT_ANY_THROW(list.begin()++);
    EXPECT_ANY_THROW(list.end()++);
    EXPECT_ANY_THROW(*(list.begin()));
    EXPECT_ANY_THROW(*(list.end()));
}

TEST(Iterator, Iter){
    {
        SkipList<int, int> list;
        list.insert({1, 2});
        list.insert({2, 3});
        list.insert({3, 4});
        list.insert({4, 5});
        auto it = list.begin();
        std::pair<const int, int> a{1, 2};
        EXPECT_EQ(it->second, 2);
        it++;
        EXPECT_EQ(it->second, 3);
        it++;
        EXPECT_EQ(it->second, 4);
        it++;
        EXPECT_EQ(it->second, 5);
        it++;
        EXPECT_EQ(it, list.end());
    }
    {
        SkipList<int, int, std::greater<int>> list;
        list.insert({1, 2});
        list.insert({2, 3});
        list.insert({3, 4});
        list.insert({4, 5});
        auto it = list.begin();
        EXPECT_EQ(it->second, 5);
        it++;
        EXPECT_EQ(it->second, 4);
        it++;
        EXPECT_EQ(it->second, 3);
        it++;
        EXPECT_EQ(it->second, 2);
        it++;
        EXPECT_EQ(it, list.end());
    }
}

TEST(Iterator, EQ){
    {
        SkipList<int, int> list;
        list.insert({1, 2});
        list.insert({2, 3});
        list.insert({3, 4});
        list.insert({4, 5});
        auto it = list.begin();
        EXPECT_EQ(it, list.begin());
        EXPECT_NE(it, list.end());
    }
    {
        SkipList<int, int> list1;
        list1.insert({1, 2});
        SkipList<int, int> list2;
        list2.insert({1, 2});
        EXPECT_NE(list1.begin(), list2.begin());
        EXPECT_EQ(list1.end(), list2.end());
    }
}*/

