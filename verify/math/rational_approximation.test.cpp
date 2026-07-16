#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation"

#include "../../math/rational_approximation.hpp"

#include <cassert>
#include <cstdint>
#include <numeric>
#include <utility>

#include "../../utilities/fast_io.hpp"

namespace {

using Fraction = std::pair<uint64_t, uint64_t>;

bool less(const Fraction& first, const Fraction& second) {
    if (second.second == 0) return first.second != 0;
    if (first.second == 0) return false;
    return static_cast<__uint128_t>(first.first) * second.second <
           static_cast<__uint128_t>(second.first) * first.second;
}

std::pair<Fraction, Fraction> brute(
    uint64_t maximum,
    uint64_t numerator,
    uint64_t denominator
) {
    Fraction lower(0, 1);
    Fraction upper(1, 0);
    for (uint64_t a = 1; a <= maximum; a++) {
        for (uint64_t b = 1; b <= maximum; b++) {
            if (std::gcd(a, b) != 1) continue;
            const bool below =
                static_cast<__uint128_t>(a) * denominator <=
                static_cast<__uint128_t>(numerator) * b;
            const bool above =
                static_cast<__uint128_t>(numerator) * b <=
                static_cast<__uint128_t>(a) * denominator;
            Fraction candidate(a, b);
            if (below && less(lower, candidate)) lower = candidate;
            if (above && less(candidate, upper)) upper = candidate;
        }
    }
    return {lower, upper};
}

void test_exhaustive() {
    for (uint64_t maximum = 1; maximum <= 10; maximum++) {
        for (uint64_t numerator = 1; numerator <= 12; numerator++) {
            for (uint64_t denominator = 1; denominator <= 12; denominator++) {
                auto expected = brute(maximum, numerator, denominator);
                auto actual = m1une::math::rational_approximation(
                    maximum, numerator, denominator
                );
                assert(actual.lower == expected.first);
                assert(actual.upper == expected.second);
            }
        }
    }

    auto small = m1une::math::rational_approximation(1LL, 1LL, 2LL);
    assert(small.lower == Fraction(0, 1));
    assert(small.upper == Fraction(1, 1));
    auto large = m1une::math::rational_approximation(1LL, 2LL, 1LL);
    assert(large.lower == Fraction(1, 1));
    assert(large.upper == Fraction(1, 0));
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_exhaustive();

    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        uint64_t maximum, numerator, denominator;
        fast_input >> maximum >> numerator >> denominator;
        auto result = m1une::math::rational_approximation(
            maximum, numerator, denominator
        );
        fast_output << result.lower.first << ' ' << result.lower.second << ' '
                    << result.upper.first << ' ' << result.upper.second << '\n';
    }
}
