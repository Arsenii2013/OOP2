#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "floating.hpp"

struct Point final {
    double x{0}, y{0};
};

namespace No_concept {
    template<typename T>
    struct has_operator {
    private:
        static void detect(...);

        template<typename U>
        static decltype(std::declval<U>()(0.)) detect(const U &);

    public:
        static constexpr bool value = std::is_same_v<double, decltype(detect(std::declval<T>()))>;
    };

    template<typename T>
    inline constexpr bool has_operator_v = has_operator<T>::value;


    class Sampler final {
    private:
        std::vector<Point> samples;
    public:
        Sampler() = default;

        template<typename FuncT, std::enable_if_t<has_operator_v<FuncT>, int> = 0>
        Sampler(const FuncT &function, const double start, const double stop, const double step) {
            init(function, start, stop, step);
        }

        template<typename FuncT>
        typename std::enable_if_t<has_operator_v<FuncT>>
        init(const FuncT &function, const double start, const double stop, const double step) {
            if (Floating::equal(step, 0.) ||
                Floating::less((stop - start) / step, 0.)) {
                throw std::invalid_argument("you cannot go around that gap in that direction");
            }
            samples.clear();

            for (double current = start;
                 (current < stop && step > 0) || (current > stop && step < 0); current += step) {
                samples.push_back(Point{current, function(current)});
            }

        }

        [[nodiscard]]const Point &operator[](std::size_t index) const {
            if (index >= samples.size()) {
                throw std::out_of_range("Attempt to access outside the array");
            }
            return samples[index];
        }

        [[nodiscard]] std::size_t size() const noexcept {
            return samples.size();
        }
    };
}

namespace Concept {
    template<class FuncT>
    concept FunctionDoubleDouble =requires(FuncT func, const double x) {
        { func(x) } -> std::same_as<double>;
    };

    class Sampler final {
    private:
        std::vector<Point> samples;
    public:
        Sampler() = default;

        template<FunctionDoubleDouble FuncT>
        Sampler(const FuncT &function, const double start, const double stop, const double step) {
            init(function, start, stop, step);
        }

        template<FunctionDoubleDouble FuncT>
        void init(const FuncT &function, const double start, const double stop, const double step) {
            if (Floating::equal(step, 0.) ||
                Floating::less((stop - start) / step, 0.)) {
                throw std::invalid_argument("you cannot go around that gap in that direction");
            }
            samples.clear();

            double current = start;
            while ((current < stop && step > 0) || (current > stop && step < 0)) {
                samples.push_back(Point{current, function(current)});
                current += step;
            }
        }

        [[nodiscard]]const Point &operator[](std::size_t index) const {
            if (index >= samples.size()) {
                throw std::out_of_range("Attempt to access outside the array");
            }
            return samples[index];
        }

        [[nodiscard]]std::size_t size() const {
            return samples.size();
        }
    };
}
