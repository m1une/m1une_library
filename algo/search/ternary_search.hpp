#ifndef M1UNE_ALGO_SEARCH_TERNARY_SEARCH_HPP
#define M1UNE_ALGO_SEARCH_TERNARY_SEARCH_HPP 1

#include <cassert>
#include <concepts>

namespace m1une {
namespace algo {

template <std::integral Int, class F>
Int ternary_search_argmin(Int left, Int right, F f) {
    assert(left < right);
    while (right - left > 3) {
        const Int third = (right - left) / 3;
        const Int middle_left = left + third;
        const Int middle_right = right - third;
        if (f(middle_right) < f(middle_left)) {
            left = middle_left + 1;
        } else {
            right = middle_right;
        }
    }

    Int best = left;
    auto best_value = f(best);
    for (Int x = left + 1; x < right; ++x) {
        auto value = f(x);
        if (value < best_value) {
            best = x;
            best_value = value;
        }
    }
    return best;
}

template <std::integral Int, class F>
Int ternary_search_argmax(Int left, Int right, F f) {
    assert(left < right);
    while (right - left > 3) {
        const Int third = (right - left) / 3;
        const Int middle_left = left + third;
        const Int middle_right = right - third;
        if (f(middle_left) < f(middle_right)) {
            left = middle_left + 1;
        } else {
            right = middle_right;
        }
    }

    Int best = left;
    auto best_value = f(best);
    for (Int x = left + 1; x < right; ++x) {
        auto value = f(x);
        if (best_value < value) {
            best = x;
            best_value = value;
        }
    }
    return best;
}

template <class F>
double real_ternary_search_argmin(double left, double right, F f, int iterations = 100) {
    assert(left <= right);
    assert(0 <= iterations);
    for (int i = 0; i < iterations; ++i) {
        const double middle_left = (left * 2.0 + right) / 3.0;
        const double middle_right = (left + right * 2.0) / 3.0;
        if (f(middle_right) < f(middle_left)) {
            left = middle_left;
        } else {
            right = middle_right;
        }
    }
    return (left + right) / 2.0;
}

template <class F>
double real_ternary_search_argmax(double left, double right, F f, int iterations = 100) {
    assert(left <= right);
    assert(0 <= iterations);
    for (int i = 0; i < iterations; ++i) {
        const double middle_left = (left * 2.0 + right) / 3.0;
        const double middle_right = (left + right * 2.0) / 3.0;
        if (f(middle_left) < f(middle_right)) {
            left = middle_left;
        } else {
            right = middle_right;
        }
    }
    return (left + right) / 2.0;
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_SEARCH_TERNARY_SEARCH_HPP
