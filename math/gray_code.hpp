#ifndef M1UNE_MATH_GRAY_CODE_HPP
#define M1UNE_MATH_GRAY_CODE_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <vector>

namespace m1une {
namespace math {

// Converts a binary value to its binary-reflected Gray code.
template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
constexpr UInt gray_encode(UInt value) noexcept {
    return value ^ (value >> 1);
}

// Converts a binary-reflected Gray code to the corresponding binary value.
template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
constexpr UInt gray_decode(UInt code) noexcept {
    for (int shift = 1; shift < std::numeric_limits<UInt>::digits;
         shift <<= 1) {
        code ^= code >> shift;
    }
    return code;
}

// Returns all bit_count-bit binary-reflected Gray codes in traversal order.
template <std::unsigned_integral UInt = std::uint64_t>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
std::vector<UInt> gray_code_sequence(int bit_count) {
    constexpr int uint_digits = std::numeric_limits<UInt>::digits;
    constexpr int size_digits = std::numeric_limits<std::size_t>::digits;
    assert(0 <= bit_count);
    assert(bit_count <= uint_digits);
    assert(bit_count < size_digits);
    if (bit_count < 0 || uint_digits < bit_count || size_digits <= bit_count) {
        return {};
    }

    const std::size_t size = std::size_t(1) << bit_count;
    std::vector<UInt> result(size);
    for (std::size_t index = 0; index < size; ++index) {
        result[index] = gray_encode(static_cast<UInt>(index));
    }
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_GRAY_CODE_HPP
