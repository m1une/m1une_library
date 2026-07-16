#ifndef M1UNE_MATH_SQUAREFREE_COUNT_HPP
#define M1UNE_MATH_SQUAREFREE_COUNT_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

#include "integer_arithmetic.hpp"

namespace m1une {
namespace math {

namespace squarefree_count_detail {

inline std::vector<int> mobius_prefix(int limit) {
    std::vector<std::int8_t> mobius(limit + 1, 0);
    if (limit >= 1) mobius[1] = 1;
    {
        std::vector<int> primes;
        std::vector<bool> composite(limit + 1, false);
        for (int value = 2; value <= limit; value++) {
            if (!composite[value]) {
                primes.push_back(value);
                mobius[value] = -1;
            }
            for (int prime : primes) {
                if (prime > limit / value) break;
                const int product = prime * value;
                composite[product] = true;
                if (value % prime == 0) {
                    mobius[product] = 0;
                    break;
                }
                mobius[product] = static_cast<std::int8_t>(-mobius[value]);
            }
        }
    }

    std::vector<int> prefix(limit + 1, 0);
    for (int value = 1; value <= limit; value++) {
        prefix[value] = prefix[value - 1] + mobius[value];
    }
    return prefix;
}

}  // namespace squarefree_count_detail

// Returns the number of square-free positive integers not greater than n.
inline uint64_t count_squarefree(uint64_t n) {
    if (n == 0) return 0;

    const uint64_t split = std::max<uint64_t>(1, floor_kth_root(n, 5U));
    const uint64_t sieve_limit_u64 = isqrt(n / split);
    assert(
        sieve_limit_u64 <=
        static_cast<uint64_t>(std::numeric_limits<int>::max())
    );
    const int sieve_limit = static_cast<int>(sieve_limit_u64);
    const std::vector<int> mertens =
        squarefree_count_detail::mobius_prefix(sieve_limit);

    __int128_t direct_sum = 0;
    for (int divisor = 1; divisor <= sieve_limit; divisor++) {
        direct_sum += static_cast<__int128_t>(
            n / static_cast<uint64_t>(divisor) /
            static_cast<uint64_t>(divisor)
        ) * (mertens[divisor] - mertens[divisor - 1]);
    }

    std::vector<std::int64_t> large_mertens;
    large_mertens.reserve(split - 1);
    std::int64_t large_mertens_sum = 0;
    for (uint64_t index = split; index-- > 1;) {
        const uint64_t argument = isqrt(n / index);
        const uint64_t square_root = isqrt(argument);
        std::int64_t value = 1;

        const uint64_t small_quotient_limit =
            argument / (square_root + 1);
        for (uint64_t quotient = 1;
             quotient <= small_quotient_limit;
             quotient++) {
            const uint64_t multiplicity =
                argument / quotient - argument / (quotient + 1);
            value -= static_cast<std::int64_t>(multiplicity) *
                     mertens[static_cast<int>(quotient)];
        }
        for (uint64_t divisor = 2; divisor <= square_root; divisor++) {
            const uint64_t quotient = argument / divisor;
            if (quotient <= sieve_limit_u64) {
                value -= mertens[static_cast<int>(quotient)];
            } else {
                const uint64_t previous_argument =
                    index * divisor * divisor;
                assert(previous_argument < split);
                const uint64_t position = split - previous_argument - 1;
                assert(position < large_mertens.size());
                value -= large_mertens[position];
            }
        }
        large_mertens.push_back(value);
        large_mertens_sum += value;
    }

    const std::int64_t grouped_sum =
        large_mertens_sum -
        static_cast<std::int64_t>(split - 1) * mertens[sieve_limit];
    const __int128_t answer = direct_sum + grouped_sum;
    assert(answer >= 0);
    assert(answer <= std::numeric_limits<uint64_t>::max());
    return static_cast<uint64_t>(answer);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_SQUAREFREE_COUNT_HPP
