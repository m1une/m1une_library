#ifndef M1UNE_MATH_RATIONAL_HPP
#define M1UNE_MATH_RATIONAL_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <compare>
#include <concepts>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace m1une {
namespace math {

namespace rational_detail {

template <class T>
concept IntegerLike =
    std::signed_integral<T> ||
    (!std::integral<T> && std::copyable<T> && requires(T first, T second) {
        T(0);
        T(1);
        { -first } -> std::same_as<T>;
        { first + second } -> std::same_as<T>;
        { first - second } -> std::same_as<T>;
        { first * second } -> std::same_as<T>;
        { first / second } -> std::same_as<T>;
        { first % second } -> std::same_as<T>;
        { first += second } -> std::same_as<T&>;
        { first -= second } -> std::same_as<T&>;
        { first /= second } -> std::same_as<T&>;
        { first == second } -> std::convertible_to<bool>;
        { first < second } -> std::convertible_to<bool>;
    });

}  // namespace rational_detail

template <rational_detail::IntegerLike T = long long>
struct Rational {
    static_assert(!std::signed_integral<T> || sizeof(T) <= sizeof(long long));

   private:
    static constexpr bool BUILTIN_INTEGER = std::signed_integral<T>;
    using Wide = std::conditional_t<BUILTIN_INTEGER, __int128_t, T>;
    using Magnitude = std::conditional_t<BUILTIN_INTEGER, __uint128_t, T>;

    T _numerator;
    T _denominator;

    static constexpr Magnitude magnitude(Wide value) {
        if constexpr (BUILTIN_INTEGER) {
            if (value < 0) {
                return static_cast<Magnitude>(-(value + 1)) + 1;
            }
            return static_cast<Magnitude>(value);
        } else {
            return value < 0 ? -value : value;
        }
    }

    static constexpr Magnitude gcd(Magnitude first, Magnitude second) {
        while (second != 0) {
            Magnitude remainder = first % second;
            first = second;
            second = remainder;
        }
        return first;
    }

    static constexpr T narrow(Wide value) {
        if constexpr (BUILTIN_INTEGER) {
            assert(Wide(std::numeric_limits<T>::min()) <= value);
            assert(value <= Wide(std::numeric_limits<T>::max()));
            return static_cast<T>(value);
        } else {
            return value;
        }
    }

    constexpr void assign_normalized(Wide numerator, Wide denominator) {
        assert(denominator != 0);
        if (numerator == 0) {
            _numerator = 0;
            _denominator = 1;
            return;
        }

        Magnitude divisor = gcd(magnitude(numerator), magnitude(denominator));
        numerator /= static_cast<Wide>(divisor);
        denominator /= static_cast<Wide>(divisor);
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        _numerator = narrow(numerator);
        _denominator = narrow(denominator);
    }

    static constexpr Rational from_wide(Wide numerator, Wide denominator) {
        Rational result;
        result.assign_normalized(numerator, denominator);
        return result;
    }

    static std::pair<long double, long long> decimal_scientific(const T& value) {
        std::ostringstream output;
        output << value;
        const std::string text = output.str();
        std::size_t begin = 0;
        int sign = 1;
        if (!text.empty() && (text[0] == '-' || text[0] == '+')) {
            if (text[0] == '-') sign = -1;
            begin = 1;
        }
        while (begin < text.size() && text[begin] == '0') ++begin;
        if (begin == text.size()) return std::make_pair(0.0L, 0LL);

        constexpr int DIGITS = std::numeric_limits<long double>::digits10 + 1;
        const std::size_t used = std::min<std::size_t>(DIGITS, text.size() - begin);
        long double significand = 0;
        for (std::size_t i = 0; i < used; ++i) {
            assert('0' <= text[begin + i] && text[begin + i] <= '9');
            significand = significand * 10 + (text[begin + i] - '0');
        }
        for (std::size_t i = 1; i < used; ++i) significand /= 10;
        const long long exponent = static_cast<long long>(text.size() - begin - 1);
        return std::make_pair(sign * significand, exponent);
    }

   public:
    constexpr Rational() : _numerator(0), _denominator(1) {}

    constexpr Rational(T integer) : _numerator(integer), _denominator(1) {}

    template <std::integral U>
        requires std::constructible_from<T, U> &&
                 (!std::same_as<std::remove_cv_t<U>, T>)
    constexpr Rational(U integer) : Rational(T(integer)) {}

    constexpr Rational(T numerator, T denominator) {
        assign_normalized(Wide(numerator), Wide(denominator));
    }

    constexpr T numerator() const {
        return _numerator;
    }

    constexpr T denominator() const {
        return _denominator;
    }

    constexpr bool is_integer() const {
        return _denominator == 1;
    }

    constexpr int sign() const {
        return (_numerator > 0) - (_numerator < 0);
    }

    constexpr Rational reciprocal() const {
        assert(_numerator != 0);
        return from_wide(Wide(_denominator), Wide(_numerator));
    }

    constexpr Rational abs() const {
        return _numerator < 0 ? -*this : *this;
    }

    constexpr long double to_long_double() const
        requires requires(const T& value) { static_cast<long double>(value); }
    {
        return static_cast<long double>(_numerator) / static_cast<long double>(_denominator);
    }

    long double to_long_double() const
        requires(!requires(const T& value) { static_cast<long double>(value); })
    {
        const auto [numerator, numerator_exponent] = decimal_scientific(_numerator);
        const auto [denominator, denominator_exponent] = decimal_scientific(_denominator);
        return numerator / denominator *
               std::pow(10.0L, numerator_exponent - denominator_exponent);
    }

    explicit constexpr operator long double() const
        requires requires(const T& value) { static_cast<long double>(value); }
    {
        return to_long_double();
    }

    explicit operator long double() const
        requires(!requires(const T& value) { static_cast<long double>(value); })
    {
        return to_long_double();
    }

    constexpr T trunc() const {
        return _numerator / _denominator;
    }

    constexpr T floor() const {
        T quotient = _numerator / _denominator;
        if (_numerator < 0 && _numerator % _denominator != 0) quotient -= T(1);
        return quotient;
    }

    constexpr T ceil() const {
        T quotient = _numerator / _denominator;
        if (0 < _numerator && _numerator % _denominator != 0) quotient += T(1);
        return quotient;
    }

    constexpr Rational operator+() const {
        return *this;
    }

    constexpr Rational operator-() const {
        return from_wide(-Wide(_numerator), Wide(_denominator));
    }

    constexpr Rational& operator+=(const Rational& other) {
        Magnitude common =
            gcd(static_cast<Magnitude>(_denominator), static_cast<Magnitude>(other._denominator));
        Wide left_scale = Wide(other._denominator) / static_cast<Wide>(common);
        Wide right_scale = Wide(_denominator) / static_cast<Wide>(common);
        Wide numerator =
            Wide(_numerator) * left_scale + Wide(other._numerator) * right_scale;

        // With both operands already reduced, every factor shared by the new
        // numerator and denominator must divide `common`.  Restricting the
        // second gcd to that value avoids a full-size gcd against the product
        // of both denominators, which is especially important for BigInt.
        Magnitude reduction = common == Magnitude(1)
                                  ? Magnitude(1)
                                  : gcd(magnitude(numerator), common);
        if (reduction != Magnitude(1)) {
            numerator /= static_cast<Wide>(reduction);
        }
        Wide remaining_denominator = Wide(other._denominator);
        if (reduction != Magnitude(1)) {
            remaining_denominator /= static_cast<Wide>(reduction);
        }
        _numerator = narrow(numerator);
        _denominator = narrow(right_scale * remaining_denominator);
        return *this;
    }

    constexpr Rational& operator-=(const Rational& other) {
        return *this += -other;
    }

    constexpr Rational& operator*=(const Rational& other) {
        Magnitude first_gcd = gcd(magnitude(Wide(_numerator)), static_cast<Magnitude>(other._denominator));
        Magnitude second_gcd = gcd(magnitude(Wide(other._numerator)), static_cast<Magnitude>(_denominator));
        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *
                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),
                          (Wide(_denominator) / static_cast<Wide>(second_gcd)) *
                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));
        return *this;
    }

    constexpr Rational& operator/=(const Rational& other) {
        return *this *= other.reciprocal();
    }

    friend constexpr Rational operator+(Rational left, const Rational& right) {
        return left += right;
    }

    friend constexpr Rational operator-(Rational left, const Rational& right) {
        return left -= right;
    }

    friend constexpr Rational operator*(Rational left, const Rational& right) {
        return left *= right;
    }

    friend constexpr Rational operator/(Rational left, const Rational& right) {
        return left /= right;
    }

    friend constexpr bool operator==(const Rational& left, const Rational& right) {
        return left._numerator == right._numerator && left._denominator == right._denominator;
    }

    friend constexpr std::strong_ordering operator<=>(const Rational& left, const Rational& right) {
        Wide first = Wide(left._numerator) * Wide(right._denominator);
        Wide second = Wide(right._numerator) * Wide(left._denominator);
        if (first < second) return std::strong_ordering::less;
        if (second < first) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    friend std::ostream& operator<<(std::ostream& output, const Rational& value) {
        output << value._numerator;
        if (value._denominator != 1) {
            output << '/' << value._denominator;
        }
        return output;
    }

    friend std::istream& operator>>(std::istream& input, Rational& value) {
        std::string token;
        if (!(input >> token)) return input;

        std::size_t slash = token.find('/');
        if (slash != std::string::npos && token.find('/', slash + 1) != std::string::npos) {
            input.setstate(std::ios::failbit);
            return input;
        }

        T numerator = 0;
        T denominator = 1;
        std::istringstream numerator_input(token.substr(0, slash));
        if (!(numerator_input >> numerator) || numerator_input.peek() != std::char_traits<char>::eof()) {
            input.setstate(std::ios::failbit);
            return input;
        }
        if (slash != std::string::npos) {
            std::istringstream denominator_input(token.substr(slash + 1));
            if (!(denominator_input >> denominator) ||
                denominator_input.peek() != std::char_traits<char>::eof()) {
                input.setstate(std::ios::failbit);
                return input;
            }
        }
        value = Rational(numerator, denominator);
        return input;
    }
};

template <rational_detail::IntegerLike T>
constexpr Rational<T> abs(const Rational<T>& value) {
    return value.abs();
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_RATIONAL_HPP
