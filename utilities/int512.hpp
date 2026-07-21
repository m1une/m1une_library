#ifndef M1UNE_UTILITIES_INT512_HPP
#define M1UNE_UTILITIES_INT512_HPP 1

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <type_traits>

namespace m1une {
namespace utilities {

// A fixed-width signed integer with two's-complement, modulo-2^512
// arithmetic. This deliberately provides only the operations needed by exact
// high-degree predicates and other small fixed-width calculations.
class Int512 {
   private:
    static constexpr std::size_t limb_count = 8;

   public:
    static constexpr std::size_t bit_width = 512;

    constexpr Int512() = default;

    template <std::integral Integer>
    constexpr Int512(Integer value) {
        static_assert(sizeof(Integer) <= sizeof(std::uint64_t));
        if constexpr (std::signed_integral<Integer>) {
            const std::uint64_t extension =
                value < 0 ? ~std::uint64_t(0) : std::uint64_t(0);
            limbs_.fill(extension);
            limbs_[0] = static_cast<std::uint64_t>(
                static_cast<std::int64_t>(value)
            );
        } else {
            limbs_[0] = static_cast<std::uint64_t>(value);
        }
    }

    constexpr bool is_zero() const {
        for (const std::uint64_t limb : limbs_) {
            if (limb != 0) return false;
        }
        return true;
    }

    constexpr bool is_negative() const {
        return (limbs_.back() >> 63) != 0;
    }

    constexpr int sign() const {
        if (is_zero()) return 0;
        return is_negative() ? -1 : 1;
    }

    constexpr Int512 operator+() const { return *this; }

    constexpr Int512 operator-() const {
        Int512 result;
        for (std::size_t index = 0; index < limb_count; ++index) {
            result.limbs_[index] = ~limbs_[index];
        }
        result.add_one();
        return result;
    }

    constexpr Int512& operator+=(const Int512& other) {
        __uint128_t carry = 0;
        for (std::size_t index = 0; index < limb_count; ++index) {
            const __uint128_t current =
                __uint128_t(limbs_[index]) + other.limbs_[index] + carry;
            limbs_[index] = static_cast<std::uint64_t>(current);
            carry = current >> 64;
        }
        return *this;
    }

    constexpr Int512& operator-=(const Int512& other) {
        return *this += -other;
    }

    constexpr Int512& operator*=(const Int512& other) {
        std::array<std::uint64_t, limb_count> product{};
        for (std::size_t first = 0; first < limb_count; ++first) {
            __uint128_t carry = 0;
            for (
                std::size_t second = 0;
                first + second < limb_count;
                ++second
            ) {
                const std::size_t position = first + second;
                const __uint128_t current =
                    __uint128_t(limbs_[first]) * other.limbs_[second] +
                    product[position] + carry;
                product[position] = static_cast<std::uint64_t>(current);
                carry = current >> 64;
            }
        }
        limbs_ = product;
        return *this;
    }

    std::string to_string() const {
        if (is_zero()) return "0";
        const bool negative = is_negative();
        std::array<std::uint64_t, limb_count> magnitude = limbs_;
        if (negative) negate_unsigned(magnitude);

        std::string result;
        while (!magnitude_is_zero(magnitude)) {
            const unsigned digit = divide_unsigned_by_ten(magnitude);
            result.push_back(static_cast<char>('0' + digit));
        }
        if (negative) result.push_back('-');
        std::reverse(result.begin(), result.end());
        return result;
    }

    friend constexpr Int512 operator+(Int512 first, const Int512& second) {
        return first += second;
    }

    friend constexpr Int512 operator-(Int512 first, const Int512& second) {
        return first -= second;
    }

    friend constexpr Int512 operator*(Int512 first, const Int512& second) {
        return first *= second;
    }

    friend constexpr bool operator==(
        const Int512& first,
        const Int512& second
    ) = default;

    friend constexpr bool operator<(
        const Int512& first,
        const Int512& second
    ) {
        const bool first_negative = first.is_negative();
        const bool second_negative = second.is_negative();
        if (first_negative != second_negative) return first_negative;
        for (std::size_t offset = 0; offset < limb_count; ++offset) {
            const std::size_t index = limb_count - 1 - offset;
            if (first.limbs_[index] != second.limbs_[index]) {
                return first.limbs_[index] < second.limbs_[index];
            }
        }
        return false;
    }

    friend constexpr bool operator!=(
        const Int512& first,
        const Int512& second
    ) {
        return !(first == second);
    }

    friend constexpr bool operator>(
        const Int512& first,
        const Int512& second
    ) {
        return second < first;
    }

    friend constexpr bool operator<=(
        const Int512& first,
        const Int512& second
    ) {
        return !(second < first);
    }

    friend constexpr bool operator>=(
        const Int512& first,
        const Int512& second
    ) {
        return !(first < second);
    }

    friend std::ostream& operator<<(
        std::ostream& output,
        const Int512& value
    ) {
        return output << value.to_string();
    }

   private:
    std::array<std::uint64_t, limb_count> limbs_{};

    constexpr void add_one() {
        for (std::size_t index = 0; index < limb_count; ++index) {
            if (++limbs_[index] != 0) break;
        }
    }

    static void negate_unsigned(
        std::array<std::uint64_t, limb_count>& value
    ) {
        for (std::uint64_t& limb : value) limb = ~limb;
        for (std::size_t index = 0; index < limb_count; ++index) {
            if (++value[index] != 0) break;
        }
    }

    static bool magnitude_is_zero(
        const std::array<std::uint64_t, limb_count>& value
    ) {
        for (const std::uint64_t limb : value) {
            if (limb != 0) return false;
        }
        return true;
    }

    static unsigned divide_unsigned_by_ten(
        std::array<std::uint64_t, limb_count>& value
    ) {
        __uint128_t remainder = 0;
        for (std::size_t offset = 0; offset < limb_count; ++offset) {
            const std::size_t index = limb_count - 1 - offset;
            const __uint128_t current =
                (remainder << 64) | value[index];
            value[index] = static_cast<std::uint64_t>(current / 10);
            remainder = current % 10;
        }
        return static_cast<unsigned>(remainder);
    }
};

using i512 = Int512;

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_INT512_HPP
