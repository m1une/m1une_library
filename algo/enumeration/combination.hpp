#ifndef M1UNE_ALGO_ENUMERATION_COMBINATION_HPP
#define M1UNE_ALGO_ENUMERATION_COMBINATION_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace m1une {
namespace algo {

namespace internal {

template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
UInt combination_low_bits(int bit_count) {
    constexpr int digits = std::numeric_limits<UInt>::digits;
    assert(0 <= bit_count && bit_count <= digits);
    if (bit_count == digits) return ~UInt(0);
    return (UInt(1) << bit_count) - UInt(1);
}

}  // namespace internal

template <std::unsigned_integral UInt = std::uint64_t>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
UInt first_combination_mask(int bit_count, int choose) {
    constexpr int digits = std::numeric_limits<UInt>::digits;
    assert(0 <= choose && choose <= bit_count && bit_count <= digits);
    if (choose == 0) return UInt(0);
    if (choose == bit_count) return internal::combination_low_bits<UInt>(bit_count);
    return (UInt(1) << choose) - UInt(1);
}

template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
bool next_combination_mask(UInt& mask, int bit_count) {
    const UInt universe = internal::combination_low_bits<UInt>(bit_count);
    assert((mask & ~universe) == 0);
    if (mask == 0) return false;

    const UInt lowest = mask & (~mask + UInt(1));
    const UInt ripple = mask + lowest;
    if (ripple == 0 || (ripple & ~universe) != 0) return false;

    const UInt next = (((ripple ^ mask) >> 2) / lowest) | ripple;
    if ((next & ~universe) != 0) return false;
    mask = next;
    return true;
}

template <std::unsigned_integral UInt = std::uint64_t, class F>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
void for_each_combination_mask(int bit_count, int choose, F f) {
    constexpr int digits = std::numeric_limits<UInt>::digits;
    assert(0 <= choose && choose <= bit_count && bit_count <= digits);
    UInt mask = first_combination_mask<UInt>(bit_count, choose);
    while (true) {
        f(mask);
        if (!next_combination_mask(mask, bit_count)) break;
    }
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_ENUMERATION_COMBINATION_HPP
