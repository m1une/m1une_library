#ifndef M1UNE_UTILITIES_DETAIL_FIXED_INT_HPP
#define M1UNE_UTILITIES_DETAIL_FIXED_INT_HPP 1

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace m1une {
namespace utilities {
namespace detail {

// A signed two's-complement integer whose arithmetic wraps modulo 2^Bits.
// Public aliases select contest-friendly fixed widths in int*.hpp.
template <std::size_t Bits>
class FixedInt {
    static_assert(Bits >= 64);
    static_assert(Bits % 64 == 0);

   private:
    static constexpr std::size_t limb_count = Bits / 64;
    using LimbArray = std::array<std::uint64_t, limb_count>;

   public:
    static constexpr std::size_t bit_width = Bits;

    constexpr FixedInt() = default;

    template <std::integral Integer>
    constexpr FixedInt(Integer value) {
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

    explicit FixedInt(std::string_view text) { read(text); }

    FixedInt& operator=(std::string_view text) {
        read(text);
        return *this;
    }

    void read(std::string_view text) {
        if (text.empty()) {
            throw std::invalid_argument("empty fixed-width integer");
        }
        const bool negative = text.front() == '-';
        std::size_t position =
            (text.front() == '-' || text.front() == '+') ? 1 : 0;
        if (position == text.size()) {
            throw std::invalid_argument("invalid fixed-width integer");
        }

        FixedInt result;
        for (; position < text.size(); ++position) {
            const char digit = text[position];
            if (digit < '0' || digit > '9') {
                throw std::invalid_argument("invalid fixed-width integer");
            }
            result.multiply_unsigned_small(10);
            result += FixedInt(static_cast<unsigned>(digit - '0'));
        }
        *this = negative ? -result : result;
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

    constexpr FixedInt operator+() const { return *this; }

    constexpr FixedInt operator-() const {
        FixedInt result;
        result.limbs_ = limbs_;
        negate_unsigned(result.limbs_);
        return result;
    }

    constexpr FixedInt& operator+=(const FixedInt& other) {
        __uint128_t carry = 0;
        for (std::size_t index = 0; index < limb_count; ++index) {
            const __uint128_t current =
                __uint128_t(limbs_[index]) + other.limbs_[index] + carry;
            limbs_[index] = static_cast<std::uint64_t>(current);
            carry = current >> 64;
        }
        return *this;
    }

    constexpr FixedInt& operator-=(const FixedInt& other) {
        return *this += -other;
    }

    constexpr FixedInt& operator*=(const FixedInt& other) {
        LimbArray product{};
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

    constexpr FixedInt& multiply_small(std::uint64_t value) {
        multiply_unsigned_small(value);
        return *this;
    }

    constexpr FixedInt& operator/=(const FixedInt& other) {
        return *this = divmod(*this, other).first;
    }

    constexpr FixedInt& operator%=(const FixedInt& other) {
        return *this = divmod(*this, other).second;
    }

    std::string to_string() const {
        if (is_zero()) return "0";
        const bool negative = is_negative();
        LimbArray magnitude = unsigned_magnitude();

        constexpr std::size_t chunk_capacity =
            (Bits * 30103 / 100000 + 9) / 9;
        std::array<std::uint32_t, chunk_capacity> chunks{};
        std::size_t chunk_count = 0;
        while (!magnitude_is_zero(magnitude)) {
            chunks[chunk_count++] = static_cast<std::uint32_t>(
                divide_unsigned_by_small(magnitude, 1000000000)
            );
        }

        std::string result;
        result.reserve(chunk_count * 9 + negative);
        if (negative) result.push_back('-');
        result += std::to_string(chunks[chunk_count - 1]);
        char digits[9];
        while (--chunk_count != 0) {
            std::uint32_t chunk = chunks[chunk_count - 1];
            for (int index = 8; index >= 0; --index) {
                digits[index] = static_cast<char>('0' + chunk % 10);
                chunk /= 10;
            }
            result.append(digits, 9);
        }
        return result;
    }

    friend constexpr std::pair<FixedInt, FixedInt> divmod(
        const FixedInt& dividend,
        const FixedInt& divisor
    ) {
        if (divisor.is_zero()) {
            throw std::domain_error("fixed-width integer division by zero");
        }

        const bool quotient_negative =
            dividend.is_negative() != divisor.is_negative();
        const bool remainder_negative = dividend.is_negative();
        auto [quotient_limbs, remainder_limbs] = divide_unsigned(
            dividend.unsigned_magnitude(), divisor.unsigned_magnitude()
        );

        FixedInt quotient;
        FixedInt remainder;
        quotient.limbs_ = quotient_limbs;
        remainder.limbs_ = remainder_limbs;
        if (quotient_negative) quotient = -quotient;
        if (remainder_negative) remainder = -remainder;
        return std::make_pair(quotient, remainder);
    }

    friend constexpr std::pair<FixedInt, std::int64_t> divmod_small(
        const FixedInt& dividend,
        std::uint32_t divisor
    ) {
        if (divisor == 0) {
            throw std::domain_error("fixed-width integer division by zero");
        }

        LimbArray quotient_limbs = dividend.unsigned_magnitude();
        const std::uint64_t unsigned_remainder =
            divide_unsigned_by_small(quotient_limbs, divisor);
        FixedInt quotient;
        quotient.limbs_ = quotient_limbs;
        if (dividend.is_negative()) quotient = -quotient;
        const std::int64_t remainder = dividend.is_negative()
                                           ? -std::int64_t(unsigned_remainder)
                                           : std::int64_t(unsigned_remainder);
        return std::make_pair(quotient, remainder);
    }

    friend constexpr std::int64_t mod_small(
        const FixedInt& dividend,
        std::uint32_t divisor
    ) {
        if (divisor == 0) {
            throw std::domain_error("fixed-width integer division by zero");
        }
        const bool negative = dividend.is_negative();
        const std::uint64_t remainder = negative
                                            ? remainder_unsigned_by_small(
                                                  dividend.unsigned_magnitude(),
                                                  divisor
                                              )
                                            : remainder_unsigned_by_small(
                                                  dividend.limbs_, divisor
                                              );
        return negative ? -std::int64_t(remainder)
                        : std::int64_t(remainder);
    }

    friend constexpr FixedInt operator+(
        FixedInt first,
        const FixedInt& second
    ) {
        return first += second;
    }

    friend constexpr FixedInt operator-(
        FixedInt first,
        const FixedInt& second
    ) {
        return first -= second;
    }

    friend constexpr FixedInt operator*(
        FixedInt first,
        const FixedInt& second
    ) {
        return first *= second;
    }

    friend constexpr FixedInt operator/(
        FixedInt first,
        const FixedInt& second
    ) {
        return first /= second;
    }

    friend constexpr FixedInt operator%(
        FixedInt first,
        const FixedInt& second
    ) {
        return first %= second;
    }

    friend constexpr bool operator==(
        const FixedInt& first,
        const FixedInt& second
    ) = default;

    friend constexpr bool operator<(
        const FixedInt& first,
        const FixedInt& second
    ) {
        const bool first_negative = first.is_negative();
        const bool second_negative = second.is_negative();
        if (first_negative != second_negative) return first_negative;
        return compare_unsigned(first.limbs_, second.limbs_) < 0;
    }

    friend constexpr bool operator!=(
        const FixedInt& first,
        const FixedInt& second
    ) {
        return !(first == second);
    }

    friend constexpr bool operator>(
        const FixedInt& first,
        const FixedInt& second
    ) {
        return second < first;
    }

    friend constexpr bool operator<=(
        const FixedInt& first,
        const FixedInt& second
    ) {
        return !(second < first);
    }

    friend constexpr bool operator>=(
        const FixedInt& first,
        const FixedInt& second
    ) {
        return !(first < second);
    }

    friend std::ostream& operator<<(
        std::ostream& output,
        const FixedInt& value
    ) {
        return output << value.to_string();
    }

    friend std::istream& operator>>(
        std::istream& input,
        FixedInt& value
    ) {
        std::string text;
        if (input >> text) value.read(text);
        return input;
    }

   private:
    LimbArray limbs_{};

    constexpr LimbArray unsigned_magnitude() const {
        LimbArray result = limbs_;
        if (is_negative()) negate_unsigned(result);
        return result;
    }

    constexpr void multiply_unsigned_small(std::uint64_t value) {
        __uint128_t carry = 0;
        for (std::size_t index = 0; index < limb_count; ++index) {
            const __uint128_t current =
                __uint128_t(limbs_[index]) * value + carry;
            limbs_[index] = static_cast<std::uint64_t>(current);
            carry = current >> 64;
        }
    }

    static constexpr void negate_unsigned(LimbArray& value) {
        for (std::uint64_t& limb : value) limb = ~limb;
        for (std::size_t index = 0; index < limb_count; ++index) {
            if (++value[index] != 0) break;
        }
    }

    static constexpr int compare_unsigned(
        const LimbArray& first,
        const LimbArray& second
    ) {
        for (std::size_t offset = 0; offset < limb_count; ++offset) {
            const std::size_t index = limb_count - 1 - offset;
            if (first[index] != second[index]) {
                return first[index] < second[index] ? -1 : 1;
            }
        }
        return 0;
    }

    static constexpr void subtract_unsigned(
        LimbArray& first,
        const LimbArray& second
    ) {
        std::uint64_t borrow = 0;
        for (std::size_t index = 0; index < limb_count; ++index) {
            const std::uint64_t previous = first[index];
            first[index] -= second[index] + borrow;
            const bool addition_overflow =
                borrow != 0 && second[index] == ~std::uint64_t(0);
            borrow = addition_overflow ||
                     previous < second[index] + borrow;
        }
    }

    static constexpr void shift_left_one(LimbArray& value) {
        std::uint64_t carry = 0;
        for (std::size_t index = 0; index < limb_count; ++index) {
            const std::uint64_t next_carry = value[index] >> 63;
            value[index] = (value[index] << 1) | carry;
            carry = next_carry;
        }
    }

    static constexpr std::pair<LimbArray, LimbArray> divide_unsigned(
        const LimbArray& dividend,
        const LimbArray& divisor
    ) {
        LimbArray quotient{};
        LimbArray remainder{};
        for (std::size_t offset = 0; offset < Bits; ++offset) {
            const std::size_t bit = Bits - 1 - offset;
            shift_left_one(remainder);
            remainder[0] |=
                (dividend[bit / 64] >> (bit % 64)) & std::uint64_t(1);
            if (compare_unsigned(remainder, divisor) >= 0) {
                subtract_unsigned(remainder, divisor);
                quotient[bit / 64] |= std::uint64_t(1) << (bit % 64);
            }
        }
        return std::make_pair(quotient, remainder);
    }

    static bool magnitude_is_zero(const LimbArray& value) {
        for (const std::uint64_t limb : value) {
            if (limb != 0) return false;
        }
        return true;
    }

    static constexpr std::uint64_t divide_unsigned_by_small(
        LimbArray& value,
        std::uint32_t divisor
    ) {
        std::uint64_t remainder = 0;
        for (std::size_t offset = 0; offset < limb_count; ++offset) {
            const std::size_t index = limb_count - 1 - offset;
            const std::uint64_t high =
                (remainder << 32) | (value[index] >> 32);
            const std::uint64_t quotient_high = high / divisor;
            remainder = high % divisor;
            const std::uint64_t low =
                (remainder << 32) | std::uint32_t(value[index]);
            const std::uint64_t quotient_low = low / divisor;
            remainder = low % divisor;
            value[index] = (quotient_high << 32) | quotient_low;
        }
        return remainder;
    }

    static constexpr std::uint64_t remainder_unsigned_by_small(
        const LimbArray& value,
        std::uint32_t divisor
    ) {
        std::uint64_t remainder = 0;
        for (std::size_t offset = 0; offset < limb_count; ++offset) {
            const std::size_t index = limb_count - 1 - offset;
            remainder = ((remainder << 32) | (value[index] >> 32)) % divisor;
            remainder =
                ((remainder << 32) | std::uint32_t(value[index])) % divisor;
        }
        return remainder;
    }

};

}  // namespace detail
}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_DETAIL_FIXED_INT_HPP
