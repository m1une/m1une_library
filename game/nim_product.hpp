#ifndef M1UNE_GAME_NIM_PRODUCT_HPP
#define M1UNE_GAME_NIM_PRODUCT_HPP 1

#include <array>
#include <cassert>
#include <cstdint>
#include <limits>

namespace m1une {
namespace game {
namespace internal {

inline uint64_t nim_product_small(uint64_t x, uint64_t y) {
    if (x < 2 || y < 2) return x * y;

    int shift = 1;
    const uint64_t largest = x | y;
    while ((uint64_t(1) << (shift * 2)) <= largest) shift *= 2;
    const uint64_t mask = (uint64_t(1) << shift) - 1;
    const uint64_t x_high = x >> shift;
    const uint64_t x_low = x & mask;
    const uint64_t y_high = y >> shift;
    const uint64_t y_low = y & mask;

    const uint64_t high_product = nim_product_small(x_high, y_high);
    const uint64_t low_product = nim_product_small(x_low, y_low);
    const uint64_t mixed_product =
        nim_product_small(x_high ^ x_low, y_high ^ y_low);
    return ((mixed_product ^ low_product) << shift) ^ low_product
           ^ nim_product_small(high_product, uint64_t(1) << (shift - 1));
}

inline const std::array<uint8_t, 1 << 16>& nim_product_8_table() {
    static const auto table = [] {
        std::array<uint8_t, 1 << 16> result{};
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 256; ++y) {
                result[(x << 8) | y] = uint8_t(nim_product_small(x, y));
            }
        }
        return result;
    }();
    return table;
}

inline uint64_t nim_product_8(uint64_t x, uint64_t y) {
    return nim_product_8_table()[(x << 8) | y];
}

template <int Bits>
inline uint64_t nim_product_fixed(uint64_t x, uint64_t y) {
    if constexpr (Bits == 8) {
        return nim_product_8(x, y);
    } else {
        constexpr int shift = Bits / 2;
        constexpr uint64_t mask = (uint64_t(1) << shift) - 1;
        const uint64_t x_high = x >> shift;
        const uint64_t x_low = x & mask;
        const uint64_t y_high = y >> shift;
        const uint64_t y_low = y & mask;

        const uint64_t high_product =
            nim_product_fixed<shift>(x_high, y_high);
        const uint64_t low_product = nim_product_fixed<shift>(x_low, y_low);
        const uint64_t mixed_product = nim_product_fixed<shift>(
            x_high ^ x_low,
            y_high ^ y_low
        );
        return ((mixed_product ^ low_product) << shift) ^ low_product
               ^ nim_product_fixed<shift>(
                   high_product,
                   uint64_t(1) << (shift - 1)
               );
    }
}

}  // namespace internal

inline uint64_t nim_product(uint64_t x, uint64_t y) {
    return internal::nim_product_fixed<64>(x, y);
}

inline uint64_t nim_power(uint64_t base, uint64_t exponent) {
    uint64_t result = 1;
    while (exponent != 0) {
        if (exponent & 1) result = nim_product(result, base);
        base = nim_product(base, base);
        exponent >>= 1;
    }
    return result;
}

inline uint64_t nim_inverse(uint64_t value) {
    assert(value != 0);
    return nim_power(value, std::numeric_limits<uint64_t>::max() - 1);
}

inline uint64_t nim_quotient(uint64_t numerator, uint64_t denominator) {
    assert(denominator != 0);
    return nim_product(numerator, nim_inverse(denominator));
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_NIM_PRODUCT_HPP
