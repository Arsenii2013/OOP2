//
// Created by sescer on 23.10.22.
//

#ifndef SAMPLER_FLOATING_HPP
#define SAMPLER_FLOATING_HPP

namespace Floating {
    template<std::floating_point T>
    const T default_epsilon = 0.000001F;

    template<std::floating_point T>
    bool less(T x1, T x2, T epsilon = default_epsilon<T>) {
        return x1 + epsilon < x2;
    }

    template<std::floating_point T>
    bool greater(T x1, T x2, T epsilon = default_epsilon<T>) {
        return x1 > x2 + epsilon;
    }

    template<std::floating_point T>
    bool equal(T x1, T x2, T epsilon = default_epsilon<T>) {
        return abs(x1 - x2) < epsilon;
    }
}
#endif //SAMPLER_FLOATING_HPP
