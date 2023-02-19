#include "gtest/gtest.h"
#include "sampler.hpp"

#include <functional>
#include <algorithm>
#include <stdexcept>


TEST(Floating, Less) {
    EXPECT_TRUE(Floating::less(5., 10.));
    EXPECT_FALSE(Floating::less(0., 0.));
    EXPECT_FALSE(Floating::less(1., 0., 2.));
    EXPECT_FALSE(Floating::less(0., 1., 2.));
}

TEST(Floating, greater) {
    EXPECT_TRUE(Floating::greater(10., 5.));
    EXPECT_FALSE(Floating::greater(0., 0.));
    EXPECT_FALSE(Floating::greater(0., 1., 2.));
    EXPECT_FALSE(Floating::greater(1., 0., 2.));
}

TEST(Floating, equal) {
    EXPECT_FALSE(Floating::equal(10., 5.));
    EXPECT_TRUE(Floating::equal(0., 0.));
    EXPECT_TRUE(Floating::equal(0., 1., 2.));
    EXPECT_TRUE(Floating::equal(1., 0., 2.));
}

using namespace No_concept;

TEST(CREATION, EMPTY) {
    Sampler s{};
    EXPECT_EQ(0, s.size());
}


double linear(double x) {
    return 2 * x;
}

bool operator==(const std::pair<double, double> &p1, const Point &p2) {
    return p1.first == p2.x && p1.second == p2.y;
}
TEST(USAGE, EMPTY) {
    EXPECT_NO_THROW(Sampler(linear, 0, 0, 1));
    Sampler s{linear, 0, 0, 1};
    EXPECT_EQ(0, s.size());
    EXPECT_ANY_THROW(s[0]);
}

TEST(USAGE, FRORWARD) {
    Sampler s{linear, 0, 10, 1};
    std::vector<std::pair<double, double>> expected{{0, 0},
                                                    {1, 2},
                                                    {2, 4},
                                                    {3, 6},
                                                    {4, 8},
                                                    {5, 10},
                                                    {6, 12},
                                                    {7, 14},
                                                    {8, 16},
                                                    {9, 18}};
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}

TEST(USAGE, BACKWARD) {
    Sampler s{linear, 10, 0, -1};
    std::vector<std::pair<double, double>> expected{{1,  2},
                                                    {2,  4},
                                                    {3,  6},
                                                    {4,  8},
                                                    {5,  10},
                                                    {6,  12},
                                                    {7,  14},
                                                    {8,  16},
                                                    {9,  18},
                                                    {10, 20}};
    std::reverse(expected.begin(), expected.end());
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}

TEST(USAGE, FRORWARD_NEG) {
    Sampler s{linear, -10, 0, 1};
    std::vector<std::pair<double, double>> expected{{-10, -20},
                                                    {-9,  -18},
                                                    {-8,  -16},
                                                    {-7,  -14},
                                                    {-6,  -12},
                                                    {-5,  -10},
                                                    {-4,  -8},
                                                    {-3,  -6},
                                                    {-2,  -4},
                                                    {-1,  -2}};
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}

TEST(USAGE, BACKWARD_NEG) {
    Sampler s{linear, 0, -10, -1};
    std::vector<std::pair<double, double>> expected{{-9, -18},
                                                    {-8, -16},
                                                    {-7, -14},
                                                    {-6, -12},
                                                    {-5, -10},
                                                    {-4, -8},
                                                    {-3, -6},
                                                    {-2, -4},
                                                    {-1, -2},
                                                    {0,  0}};
    std::reverse(expected.begin(), expected.end());
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}

TEST(USAGE, WRONG) {
    EXPECT_THROW(Sampler(linear, 10, 0, 1), std::invalid_argument);

    EXPECT_THROW(Sampler(linear, 0, 10, -1), std::invalid_argument);

    EXPECT_THROW(Sampler(linear, 0, 10, 0), std::invalid_argument);
}

TEST(DIFFTYPES, DOUBLEDOUBLE) {
    Sampler s{linear, 0, 10, 1};
    std::vector<std::pair<double, double>> expected{{0, 0},
                                                    {1, 2},
                                                    {2, 4},
                                                    {3, 6},
                                                    {4, 8},
                                                    {5, 10},
                                                    {6, 12},
                                                    {7, 14},
                                                    {8, 16},
                                                    {9, 18}};
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}

TEST(DIFFTYPES, STDFUNCTION) {
    Sampler s{std::function<double(double)>{linear}, 0, 10, 1};
    std::vector<std::pair<double, double>> expected{{0, 0},
                                                    {1, 2},
                                                    {2, 4},
                                                    {3, 6},
                                                    {4, 8},
                                                    {5, 10},
                                                    {6, 12},
                                                    {7, 14},
                                                    {8, 16},
                                                    {9, 18}};
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}

TEST(DIFFTYPES, LAMBDA) {
    auto lin = [](double x) { return 2 * x; };
    Sampler s{lin, 0, 10, 1};
    std::vector<std::pair<double, double>> expected{{0, 0},
                                                    {1, 2},
                                                    {2, 4},
                                                    {3, 6},
                                                    {4, 8},
                                                    {5, 10},
                                                    {6, 12},
                                                    {7, 14},
                                                    {8, 16},
                                                    {9, 18}};
    for (int i = 0; i < expected.size(); i++)
        EXPECT_EQ(expected[i], s[i]);
}
