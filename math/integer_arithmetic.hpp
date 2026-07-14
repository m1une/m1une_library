#ifndef M1UNE_MATH_INTEGER_ARITHMETIC_HPP
#define M1UNE_MATH_INTEGER_ARITHMETIC_HPP 1

#include <cassert>
#include <concepts>
#include <limits>
#include <optional>
#include <type_traits>

namespace m1une {
namespace math {

namespace integer_arithmetic_detail {

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr std::optional<T> checked_multiply(T first, T second) {
    constexpr T minimum = std::numeric_limits<T>::min();
    constexpr T maximum = std::numeric_limits<T>::max();

    if constexpr (std::unsigned_integral<T>) {
        if (second != 0 && maximum / second < first) return std::nullopt;
    } else {
        if (0 < first) {
            if (0 < second) {
                if (maximum / second < first) return std::nullopt;
            } else if (second < minimum / first) {
                return std::nullopt;
            }
        } else if (first < 0) {
            if (0 < second) {
                if (first < minimum / second) return std::nullopt;
            } else if (second < maximum / first) {
                return std::nullopt;
            }
        }
    }
    return T(first * second);
}

template <std::unsigned_integral T>
constexpr bool kth_power_leq(T base, unsigned exponent, T limit) {
    assert(exponent > 0);
    if (base <= 1) return base <= limit;

    const T multiplication_limit = limit / base;
    T product = 1;
    for (unsigned i = 0; i < exponent; i++) {
        if (product > multiplication_limit) return false;
        product *= base;
    }
    return true;
}

}  // namespace integer_arithmetic_detail

// Returns floor(sqrt(value)) exactly, without floating-point arithmetic.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr T isqrt(T value) {
    if constexpr (std::signed_integral<T>) assert(0 <= value);
    if (value <= 1) return value;

    T low = 1;
    T high = value / 2 + 1;
    while (low < high) {
        T middle = low + (high - low + 1) / 2;
        if (middle <= value / middle) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr T floor_sqrt(T value) {
    return isqrt(value);
}

// Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
constexpr T ceil_sqrt(T value) {
    T result = isqrt(value);
    if (result == 0) return 0;
    if (result != 0 && value / result == result && value % result == 0) {
        return result;
    }
    return result + 1;
}

// Returns floor(value^(1 / degree)) exactly, without floating-point arithmetic.
template <std::integral T, std::integral Degree>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Degree>, bool>
)
constexpr T floor_kth_root(T value, Degree degree) {
    if constexpr (std::signed_integral<T>) {
        assert(0 <= value);
        if (value < 0) return T();
    }
    assert(0 < degree);
    if (degree <= 0) return T();
    if (value <= 1 || degree == 1) return value;
    if (degree == 2) return isqrt(value);

    using U = std::make_unsigned_t<T>;
    using UDegree = std::make_unsigned_t<Degree>;
    constexpr int digits = std::numeric_limits<U>::digits;
    const UDegree unsigned_degree = static_cast<UDegree>(degree);
    if (unsigned_degree >= static_cast<UDegree>(digits)) return T(1);
    const unsigned exponent = static_cast<unsigned>(unsigned_degree);
    const U unsigned_value = static_cast<U>(value);

    int bit_width = 0;
    for (U remaining = unsigned_value; remaining != 0; remaining >>= 1) {
        bit_width++;
    }
    const int root_bits =
        (bit_width + static_cast<int>(exponent) - 1) /
        static_cast<int>(exponent);

    U low = 1;
    U high = U(1) << root_bits;
    while (high - low > 1) {
        const U middle = low + (high - low) / 2;
        if (
            integer_arithmetic_detail::kth_power_leq(
                middle, exponent, unsigned_value
            )
        ) {
            low = middle;
        } else {
            high = middle;
        }
    }
    return static_cast<T>(low);
}

// Returns base^exponent, or nullopt when the result does not fit in T.
template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr std::optional<T> checked_ipow(T base, Exponent exponent) {
    T result = 1;
    while (exponent != 0) {
        if (exponent & 1) {
            auto product =
                integer_arithmetic_detail::checked_multiply(result, base);
            if (!product.has_value()) return std::nullopt;
            result = *product;
        }
        exponent >>= 1;
        if (exponent != 0) {
            auto square =
                integer_arithmetic_detail::checked_multiply(base, base);
            if (!square.has_value()) return std::nullopt;
            base = *square;
        }
    }
    return result;
}

template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr std::optional<T> checked_integer_pow(T base, Exponent exponent) {
    return checked_ipow(base, exponent);
}

// Returns base^exponent. The result must be representable by T.
template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr T ipow(T base, Exponent exponent) {
    std::optional<T> result = checked_ipow(base, exponent);
    assert(result.has_value());
    return result.value_or(T());
}

template <std::integral T, std::unsigned_integral Exponent>
requires(
    !std::same_as<std::remove_cv_t<T>, bool>
    && !std::same_as<std::remove_cv_t<Exponent>, bool>
)
constexpr T integer_pow(T base, Exponent exponent) {
    return ipow(base, exponent);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_INTEGER_ARITHMETIC_HPP
