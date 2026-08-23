#ifndef M1UNE_MATH_GAUSSIAN_INTEGER_HPP
#define M1UNE_MATH_GAUSSIAN_INTEGER_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <tuple>
#include <utility>

namespace m1une {
namespace math {

template <std::signed_integral T = long long>
struct GaussianInteger {
    static_assert(sizeof(T) <= sizeof(long long));

    using value_type = T;
    using norm_type = __uint128_t;

    T real;
    T imag;

   private:
    using wide_type = __int128_t;

    struct SignedMagnitude {
        norm_type magnitude;
        bool negative;
    };

    static constexpr norm_type magnitude(T value) {
        const wide_type wide = value;
        if (wide < 0) {
            return static_cast<norm_type>(-(wide + 1)) + 1;
        }
        return static_cast<norm_type>(wide);
    }

    static constexpr SignedMagnitude signed_value(T value) {
        return SignedMagnitude{magnitude(value), value < 0};
    }

    static constexpr SignedMagnitude negate(SignedMagnitude value) {
        if (value.magnitude != 0) value.negative = !value.negative;
        return value;
    }

    static constexpr SignedMagnitude add_signed(
        SignedMagnitude first,
        SignedMagnitude second
    ) {
        if (first.negative == second.negative) {
            return SignedMagnitude{
                first.magnitude + second.magnitude,
                first.negative
            };
        }
        if (first.magnitude < second.magnitude) {
            return SignedMagnitude{
                second.magnitude - first.magnitude,
                second.negative
            };
        }
        return SignedMagnitude{
            first.magnitude - second.magnitude,
            first.magnitude == second.magnitude ? false : first.negative
        };
    }

    static constexpr SignedMagnitude product(T first, T second) {
        const norm_type result = magnitude(first) * magnitude(second);
        return SignedMagnitude{
            result,
            result != 0 && ((first < 0) != (second < 0))
        };
    }

    static constexpr T narrow(SignedMagnitude value) {
        const norm_type maximum =
            static_cast<norm_type>(std::numeric_limits<T>::max());
        if (!value.negative) {
            assert(value.magnitude <= maximum);
            return static_cast<T>(value.magnitude);
        }

        assert(value.magnitude <= maximum + 1);
        if (value.magnitude == maximum + 1) {
            return std::numeric_limits<T>::min();
        }
        return static_cast<T>(-static_cast<wide_type>(value.magnitude));
    }

    static constexpr std::pair<SignedMagnitude, SignedMagnitude>
    product_components(
        const GaussianInteger& first,
        const GaussianInteger& second
    ) {
        const SignedMagnitude product_real = add_signed(
            product(first.real, second.real),
            negate(product(first.imag, second.imag))
        );
        const SignedMagnitude product_imag = add_signed(
            product(first.real, second.imag),
            product(first.imag, second.real)
        );
        return {product_real, product_imag};
    }

    static constexpr T round_ratio(
        SignedMagnitude numerator,
        norm_type denominator
    ) {
        assert(denominator != 0);
        norm_type quotient = numerator.magnitude / denominator;
        const norm_type remainder = numerator.magnitude % denominator;
        if (remainder + remainder >= denominator) quotient++;
        return narrow(SignedMagnitude{quotient, numerator.negative});
    }

   public:
    constexpr GaussianInteger() : real(0), imag(0) {}

    constexpr GaussianInteger(T real_) : real(real_), imag(0) {}

    constexpr GaussianInteger(T real_, T imag_)
        : real(real_), imag(imag_) {}

    constexpr bool is_zero() const {
        return real == 0 && imag == 0;
    }

    constexpr bool is_unit() const {
        return norm() == 1;
    }

    constexpr norm_type norm() const {
        const norm_type real_magnitude = magnitude(real);
        const norm_type imag_magnitude = magnitude(imag);
        return real_magnitude * real_magnitude +
               imag_magnitude * imag_magnitude;
    }

    constexpr GaussianInteger conjugate() const {
        return GaussianInteger(real, narrow(negate(signed_value(imag))));
    }

    constexpr GaussianInteger normalizing_unit() const {
        if (is_zero() || (0 < real && 0 <= imag)) {
            return GaussianInteger(1, 0);
        }
        if (0 < real) return GaussianInteger(0, 1);
        if (real < 0 && imag <= 0) return GaussianInteger(-1, 0);
        if (real < 0) return GaussianInteger(0, -1);
        if (0 < imag) return GaussianInteger(0, -1);
        return GaussianInteger(0, 1);
    }

    constexpr GaussianInteger normalized() const {
        return normalizing_unit() * *this;
    }

    constexpr std::pair<GaussianInteger, GaussianInteger> divmod(
        const GaussianInteger& divisor
    ) const {
        const norm_type divisor_norm = divisor.norm();
        assert(divisor_norm != 0);

        const SignedMagnitude numerator_real = add_signed(
            product(real, divisor.real),
            product(imag, divisor.imag)
        );
        const SignedMagnitude numerator_imag = add_signed(
            product(imag, divisor.real),
            negate(product(real, divisor.imag))
        );
        const GaussianInteger quotient(
            round_ratio(numerator_real, divisor_norm),
            round_ratio(numerator_imag, divisor_norm)
        );

        const auto product = product_components(quotient, divisor);
        const GaussianInteger remainder(
            narrow(add_signed(signed_value(real), negate(product.first))),
            narrow(add_signed(signed_value(imag), negate(product.second)))
        );
        assert(remainder.norm() < divisor_norm);
        return {quotient, remainder};
    }

    constexpr GaussianInteger operator+() const {
        return *this;
    }

    constexpr GaussianInteger operator-() const {
        return GaussianInteger(
            narrow(negate(signed_value(real))),
            narrow(negate(signed_value(imag)))
        );
    }

    constexpr GaussianInteger& operator+=(const GaussianInteger& other) {
        real = narrow(add_signed(signed_value(real), signed_value(other.real)));
        imag = narrow(add_signed(signed_value(imag), signed_value(other.imag)));
        return *this;
    }

    constexpr GaussianInteger& operator-=(const GaussianInteger& other) {
        real = narrow(add_signed(
            signed_value(real),
            negate(signed_value(other.real))
        ));
        imag = narrow(add_signed(
            signed_value(imag),
            negate(signed_value(other.imag))
        ));
        return *this;
    }

    constexpr GaussianInteger& operator*=(const GaussianInteger& other) {
        const auto result = product_components(*this, other);
        real = narrow(result.first);
        imag = narrow(result.second);
        return *this;
    }

    constexpr GaussianInteger& operator/=(const GaussianInteger& other) {
        *this = divmod(other).first;
        return *this;
    }

    constexpr GaussianInteger& operator%=(const GaussianInteger& other) {
        *this = divmod(other).second;
        return *this;
    }

    friend constexpr GaussianInteger operator+(
        GaussianInteger left,
        const GaussianInteger& right
    ) {
        return left += right;
    }

    friend constexpr GaussianInteger operator-(
        GaussianInteger left,
        const GaussianInteger& right
    ) {
        return left -= right;
    }

    friend constexpr GaussianInteger operator*(
        GaussianInteger left,
        const GaussianInteger& right
    ) {
        return left *= right;
    }

    friend constexpr GaussianInteger operator/(
        GaussianInteger left,
        const GaussianInteger& right
    ) {
        return left /= right;
    }

    friend constexpr GaussianInteger operator%(
        GaussianInteger left,
        const GaussianInteger& right
    ) {
        return left %= right;
    }

    friend constexpr bool operator==(
        const GaussianInteger& first,
        const GaussianInteger& second
    ) = default;
};

template <std::signed_integral T>
constexpr bool gaussian_divides(
    const GaussianInteger<T>& divisor,
    const GaussianInteger<T>& value
) {
    if (divisor.is_zero()) return value.is_zero();
    return (value % divisor).is_zero();
}

template <std::signed_integral T>
constexpr bool gaussian_associates(
    const GaussianInteger<T>& first,
    const GaussianInteger<T>& second
) {
    return first.normalized() == second.normalized();
}

template <std::signed_integral T>
constexpr GaussianInteger<T> gaussian_gcd(
    GaussianInteger<T> first,
    GaussianInteger<T> second
) {
    while (!second.is_zero()) {
        first %= second;
        std::swap(first, second);
    }
    return first.normalized();
}

template <std::signed_integral T>
constexpr std::tuple<
    GaussianInteger<T>,
    GaussianInteger<T>,
    GaussianInteger<T>
> extended_gaussian_gcd(
    GaussianInteger<T> first,
    GaussianInteger<T> second
) {
    using G = GaussianInteger<T>;
    G old_remainder = first;
    G remainder = second;
    G old_first_coefficient(1);
    G first_coefficient(0);
    G old_second_coefficient(0);
    G second_coefficient(1);

    while (!remainder.is_zero()) {
        const G quotient = old_remainder / remainder;

        G next = old_remainder - quotient * remainder;
        old_remainder = remainder;
        remainder = next;

        next = old_first_coefficient - quotient * first_coefficient;
        old_first_coefficient = first_coefficient;
        first_coefficient = next;

        next = old_second_coefficient - quotient * second_coefficient;
        old_second_coefficient = second_coefficient;
        second_coefficient = next;
    }

    const G unit = old_remainder.normalizing_unit();
    return {
        unit * old_remainder,
        unit * old_first_coefficient,
        unit * old_second_coefficient
    };
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_GAUSSIAN_INTEGER_HPP
