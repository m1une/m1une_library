#ifndef M1UNE_ALGO_ENUMERATION_SUBMASK_HPP
#define M1UNE_ALGO_ENUMERATION_SUBMASK_HPP 1

#include <cassert>
#include <concepts>
#include <limits>
#include <type_traits>

namespace m1une {
namespace algo {

namespace internal {

template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
UInt submask_low_bits(int bit_count) {
    constexpr int digits = std::numeric_limits<UInt>::digits;
    assert(0 <= bit_count && bit_count <= digits);
    if (bit_count == digits) return ~UInt(0);
    return (UInt(1) << bit_count) - UInt(1);
}

}  // namespace internal

template <std::unsigned_integral UInt, class F>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
void for_each_submask(UInt mask, F f) {
    UInt submask = mask;
    while (true) {
        f(submask);
        if (submask == 0) break;
        submask = (submask - 1) & mask;
    }
}

template <std::unsigned_integral UInt, class F>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
void for_each_nonzero_submask(UInt mask, F f) {
    for (UInt submask = mask; submask != 0; submask = (submask - 1) & mask) {
        f(submask);
    }
}

template <std::unsigned_integral UInt, class F>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
void for_each_supermask(UInt mask, int bit_count, F f) {
    const UInt universe = internal::submask_low_bits<UInt>(bit_count);
    assert((mask & ~universe) == 0);
    const UInt free_bits = universe ^ mask;
    for_each_submask(free_bits, [&](UInt added_bits) {
        f(mask | added_bits);
    });
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_ENUMERATION_SUBMASK_HPP
