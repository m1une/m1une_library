---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/rational.test.cpp
    title: verify/math/rational.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/stern_brocot_tree.test.cpp
    title: verify/math/stern_brocot_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/yosupo_stern_brocot_tree.test.cpp
    title: verify/math/yosupo_stern_brocot_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/rational.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <compare>\n#include <concepts>\n#include\
    \ <iostream>\n#include <limits>\n#include <sstream>\n#include <string>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace math {\n\n\
    namespace rational_detail {\n\ntemplate <class T>\nconcept IntegerLike =\n   \
    \ std::signed_integral<T> ||\n    (!std::integral<T> && std::copyable<T> && requires(T\
    \ first, T second) {\n        T(0);\n        T(1);\n        { -first } -> std::same_as<T>;\n\
    \        { first + second } -> std::same_as<T>;\n        { first - second } ->\
    \ std::same_as<T>;\n        { first * second } -> std::same_as<T>;\n        {\
    \ first / second } -> std::same_as<T>;\n        { first % second } -> std::same_as<T>;\n\
    \        { first += second } -> std::same_as<T&>;\n        { first -= second }\
    \ -> std::same_as<T&>;\n        { first /= second } -> std::same_as<T&>;\n   \
    \     { first == second } -> std::convertible_to<bool>;\n        { first < second\
    \ } -> std::convertible_to<bool>;\n    });\n\n}  // namespace rational_detail\n\
    \ntemplate <rational_detail::IntegerLike T = long long>\nstruct Rational {\n \
    \   static_assert(!std::signed_integral<T> || sizeof(T) <= sizeof(long long));\n\
    \n   private:\n    static constexpr bool BUILTIN_INTEGER = std::signed_integral<T>;\n\
    \    using Wide = std::conditional_t<BUILTIN_INTEGER, __int128_t, T>;\n    using\
    \ Magnitude = std::conditional_t<BUILTIN_INTEGER, __uint128_t, T>;\n\n    T _numerator;\n\
    \    T _denominator;\n\n    static constexpr Magnitude magnitude(Wide value) {\n\
    \        if constexpr (BUILTIN_INTEGER) {\n            if (value < 0) {\n    \
    \            return static_cast<Magnitude>(-(value + 1)) + 1;\n            }\n\
    \            return static_cast<Magnitude>(value);\n        } else {\n       \
    \     return value < 0 ? -value : value;\n        }\n    }\n\n    static constexpr\
    \ Magnitude gcd(Magnitude first, Magnitude second) {\n        while (second !=\
    \ 0) {\n            Magnitude remainder = first % second;\n            first =\
    \ second;\n            second = remainder;\n        }\n        return first;\n\
    \    }\n\n    static constexpr T narrow(Wide value) {\n        if constexpr (BUILTIN_INTEGER)\
    \ {\n            assert(Wide(std::numeric_limits<T>::min()) <= value);\n     \
    \       assert(value <= Wide(std::numeric_limits<T>::max()));\n            return\
    \ static_cast<T>(value);\n        } else {\n            return value;\n      \
    \  }\n    }\n\n    constexpr void assign_normalized(Wide numerator, Wide denominator)\
    \ {\n        assert(denominator != 0);\n        if (numerator == 0) {\n      \
    \      _numerator = 0;\n            _denominator = 1;\n            return;\n \
    \       }\n\n        Magnitude divisor = gcd(magnitude(numerator), magnitude(denominator));\n\
    \        numerator /= static_cast<Wide>(divisor);\n        denominator /= static_cast<Wide>(divisor);\n\
    \        if (denominator < 0) {\n            numerator = -numerator;\n       \
    \     denominator = -denominator;\n        }\n        _numerator = narrow(numerator);\n\
    \        _denominator = narrow(denominator);\n    }\n\n    static constexpr Rational\
    \ from_wide(Wide numerator, Wide denominator) {\n        Rational result;\n  \
    \      result.assign_normalized(numerator, denominator);\n        return result;\n\
    \    }\n\n    static std::pair<long double, long long> decimal_scientific(const\
    \ T& value) {\n        std::ostringstream output;\n        output << value;\n\
    \        const std::string text = output.str();\n        std::size_t begin = 0;\n\
    \        int sign = 1;\n        if (!text.empty() && (text[0] == '-' || text[0]\
    \ == '+')) {\n            if (text[0] == '-') sign = -1;\n            begin =\
    \ 1;\n        }\n        while (begin < text.size() && text[begin] == '0') ++begin;\n\
    \        if (begin == text.size()) return std::make_pair(0.0L, 0LL);\n\n     \
    \   constexpr int DIGITS = std::numeric_limits<long double>::digits10 + 1;\n \
    \       const std::size_t used = std::min<std::size_t>(DIGITS, text.size() - begin);\n\
    \        long double significand = 0;\n        for (std::size_t i = 0; i < used;\
    \ ++i) {\n            assert('0' <= text[begin + i] && text[begin + i] <= '9');\n\
    \            significand = significand * 10 + (text[begin + i] - '0');\n     \
    \   }\n        for (std::size_t i = 1; i < used; ++i) significand /= 10;\n   \
    \     const long long exponent = static_cast<long long>(text.size() - begin -\
    \ 1);\n        return std::make_pair(sign * significand, exponent);\n    }\n\n\
    \   public:\n    constexpr Rational() : _numerator(0), _denominator(1) {}\n\n\
    \    constexpr Rational(T integer) : _numerator(integer), _denominator(1) {}\n\
    \n    template <std::integral U>\n        requires std::constructible_from<T,\
    \ U> &&\n                 (!std::same_as<std::remove_cv_t<U>, T>)\n    constexpr\
    \ Rational(U integer) : Rational(T(integer)) {}\n\n    constexpr Rational(T numerator,\
    \ T denominator) {\n        assign_normalized(Wide(numerator), Wide(denominator));\n\
    \    }\n\n    constexpr T numerator() const {\n        return _numerator;\n  \
    \  }\n\n    constexpr T denominator() const {\n        return _denominator;\n\
    \    }\n\n    constexpr bool is_integer() const {\n        return _denominator\
    \ == 1;\n    }\n\n    constexpr int sign() const {\n        return (_numerator\
    \ > 0) - (_numerator < 0);\n    }\n\n    constexpr Rational reciprocal() const\
    \ {\n        assert(_numerator != 0);\n        return from_wide(Wide(_denominator),\
    \ Wide(_numerator));\n    }\n\n    constexpr Rational abs() const {\n        return\
    \ _numerator < 0 ? -*this : *this;\n    }\n\n    constexpr long double to_long_double()\
    \ const\n        requires requires(const T& value) { static_cast<long double>(value);\
    \ }\n    {\n        return static_cast<long double>(_numerator) / static_cast<long\
    \ double>(_denominator);\n    }\n\n    long double to_long_double() const\n  \
    \      requires(!requires(const T& value) { static_cast<long double>(value); })\n\
    \    {\n        const auto [numerator, numerator_exponent] = decimal_scientific(_numerator);\n\
    \        const auto [denominator, denominator_exponent] = decimal_scientific(_denominator);\n\
    \        return numerator / denominator *\n               std::pow(10.0L, numerator_exponent\
    \ - denominator_exponent);\n    }\n\n    explicit constexpr operator long double()\
    \ const\n        requires requires(const T& value) { static_cast<long double>(value);\
    \ }\n    {\n        return to_long_double();\n    }\n\n    explicit operator long\
    \ double() const\n        requires(!requires(const T& value) { static_cast<long\
    \ double>(value); })\n    {\n        return to_long_double();\n    }\n\n    constexpr\
    \ T trunc() const {\n        return _numerator / _denominator;\n    }\n\n    constexpr\
    \ T floor() const {\n        T quotient = _numerator / _denominator;\n       \
    \ if (_numerator < 0 && _numerator % _denominator != 0) quotient -= T(1);\n  \
    \      return quotient;\n    }\n\n    constexpr T ceil() const {\n        T quotient\
    \ = _numerator / _denominator;\n        if (0 < _numerator && _numerator % _denominator\
    \ != 0) quotient += T(1);\n        return quotient;\n    }\n\n    constexpr Rational\
    \ operator+() const {\n        return *this;\n    }\n\n    constexpr Rational\
    \ operator-() const {\n        return from_wide(-Wide(_numerator), Wide(_denominator));\n\
    \    }\n\n    constexpr Rational& operator+=(const Rational& other) {\n      \
    \  Magnitude common =\n            gcd(static_cast<Magnitude>(_denominator), static_cast<Magnitude>(other._denominator));\n\
    \        Wide left_scale = Wide(other._denominator) / static_cast<Wide>(common);\n\
    \        Wide right_scale = Wide(_denominator) / static_cast<Wide>(common);\n\
    \        assign_normalized(Wide(_numerator) * left_scale + Wide(other._numerator)\
    \ * right_scale,\n                          Wide(_denominator) * left_scale);\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator-=(const Rational&\
    \ other) {\n        return *this += -other;\n    }\n\n    constexpr Rational&\
    \ operator*=(const Rational& other) {\n        Magnitude first_gcd = gcd(magnitude(Wide(_numerator)),\
    \ static_cast<Magnitude>(other._denominator));\n        Magnitude second_gcd =\
    \ gcd(magnitude(Wide(other._numerator)), static_cast<Magnitude>(_denominator));\n\
    \        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *\n\
    \                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),\n\
    \                          (Wide(_denominator) / static_cast<Wide>(second_gcd))\
    \ *\n                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator/=(const Rational&\
    \ other) {\n        return *this *= other.reciprocal();\n    }\n\n    friend constexpr\
    \ Rational operator+(Rational left, const Rational& right) {\n        return left\
    \ += right;\n    }\n\n    friend constexpr Rational operator-(Rational left, const\
    \ Rational& right) {\n        return left -= right;\n    }\n\n    friend constexpr\
    \ Rational operator*(Rational left, const Rational& right) {\n        return left\
    \ *= right;\n    }\n\n    friend constexpr Rational operator/(Rational left, const\
    \ Rational& right) {\n        return left /= right;\n    }\n\n    friend constexpr\
    \ bool operator==(const Rational& left, const Rational& right) {\n        return\
    \ left._numerator == right._numerator && left._denominator == right._denominator;\n\
    \    }\n\n    friend constexpr std::strong_ordering operator<=>(const Rational&\
    \ left, const Rational& right) {\n        Wide first = Wide(left._numerator) *\
    \ Wide(right._denominator);\n        Wide second = Wide(right._numerator) * Wide(left._denominator);\n\
    \        if (first < second) return std::strong_ordering::less;\n        if (second\
    \ < first) return std::strong_ordering::greater;\n        return std::strong_ordering::equal;\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& output, const Rational&\
    \ value) {\n        output << value._numerator;\n        if (value._denominator\
    \ != 1) {\n            output << '/' << value._denominator;\n        }\n     \
    \   return output;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ input, Rational& value) {\n        std::string token;\n        if (!(input >>\
    \ token)) return input;\n\n        std::size_t slash = token.find('/');\n    \
    \    if (slash != std::string::npos && token.find('/', slash + 1) != std::string::npos)\
    \ {\n            input.setstate(std::ios::failbit);\n            return input;\n\
    \        }\n\n        T numerator = 0;\n        T denominator = 1;\n        std::istringstream\
    \ numerator_input(token.substr(0, slash));\n        if (!(numerator_input >> numerator)\
    \ || numerator_input.peek() != std::char_traits<char>::eof()) {\n            input.setstate(std::ios::failbit);\n\
    \            return input;\n        }\n        if (slash != std::string::npos)\
    \ {\n            std::istringstream denominator_input(token.substr(slash + 1));\n\
    \            if (!(denominator_input >> denominator) ||\n                denominator_input.peek()\
    \ != std::char_traits<char>::eof()) {\n                input.setstate(std::ios::failbit);\n\
    \                return input;\n            }\n        }\n        value = Rational(numerator,\
    \ denominator);\n        return input;\n    }\n};\n\ntemplate <rational_detail::IntegerLike\
    \ T>\nconstexpr Rational<T> abs(const Rational<T>& value) {\n    return value.abs();\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_RATIONAL_HPP\n#define M1UNE_MATH_RATIONAL_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <compare>\n#include\
    \ <concepts>\n#include <iostream>\n#include <limits>\n#include <sstream>\n#include\
    \ <string>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace rational_detail {\n\ntemplate <class T>\nconcept\
    \ IntegerLike =\n    std::signed_integral<T> ||\n    (!std::integral<T> && std::copyable<T>\
    \ && requires(T first, T second) {\n        T(0);\n        T(1);\n        { -first\
    \ } -> std::same_as<T>;\n        { first + second } -> std::same_as<T>;\n    \
    \    { first - second } -> std::same_as<T>;\n        { first * second } -> std::same_as<T>;\n\
    \        { first / second } -> std::same_as<T>;\n        { first % second } ->\
    \ std::same_as<T>;\n        { first += second } -> std::same_as<T&>;\n       \
    \ { first -= second } -> std::same_as<T&>;\n        { first /= second } -> std::same_as<T&>;\n\
    \        { first == second } -> std::convertible_to<bool>;\n        { first <\
    \ second } -> std::convertible_to<bool>;\n    });\n\n}  // namespace rational_detail\n\
    \ntemplate <rational_detail::IntegerLike T = long long>\nstruct Rational {\n \
    \   static_assert(!std::signed_integral<T> || sizeof(T) <= sizeof(long long));\n\
    \n   private:\n    static constexpr bool BUILTIN_INTEGER = std::signed_integral<T>;\n\
    \    using Wide = std::conditional_t<BUILTIN_INTEGER, __int128_t, T>;\n    using\
    \ Magnitude = std::conditional_t<BUILTIN_INTEGER, __uint128_t, T>;\n\n    T _numerator;\n\
    \    T _denominator;\n\n    static constexpr Magnitude magnitude(Wide value) {\n\
    \        if constexpr (BUILTIN_INTEGER) {\n            if (value < 0) {\n    \
    \            return static_cast<Magnitude>(-(value + 1)) + 1;\n            }\n\
    \            return static_cast<Magnitude>(value);\n        } else {\n       \
    \     return value < 0 ? -value : value;\n        }\n    }\n\n    static constexpr\
    \ Magnitude gcd(Magnitude first, Magnitude second) {\n        while (second !=\
    \ 0) {\n            Magnitude remainder = first % second;\n            first =\
    \ second;\n            second = remainder;\n        }\n        return first;\n\
    \    }\n\n    static constexpr T narrow(Wide value) {\n        if constexpr (BUILTIN_INTEGER)\
    \ {\n            assert(Wide(std::numeric_limits<T>::min()) <= value);\n     \
    \       assert(value <= Wide(std::numeric_limits<T>::max()));\n            return\
    \ static_cast<T>(value);\n        } else {\n            return value;\n      \
    \  }\n    }\n\n    constexpr void assign_normalized(Wide numerator, Wide denominator)\
    \ {\n        assert(denominator != 0);\n        if (numerator == 0) {\n      \
    \      _numerator = 0;\n            _denominator = 1;\n            return;\n \
    \       }\n\n        Magnitude divisor = gcd(magnitude(numerator), magnitude(denominator));\n\
    \        numerator /= static_cast<Wide>(divisor);\n        denominator /= static_cast<Wide>(divisor);\n\
    \        if (denominator < 0) {\n            numerator = -numerator;\n       \
    \     denominator = -denominator;\n        }\n        _numerator = narrow(numerator);\n\
    \        _denominator = narrow(denominator);\n    }\n\n    static constexpr Rational\
    \ from_wide(Wide numerator, Wide denominator) {\n        Rational result;\n  \
    \      result.assign_normalized(numerator, denominator);\n        return result;\n\
    \    }\n\n    static std::pair<long double, long long> decimal_scientific(const\
    \ T& value) {\n        std::ostringstream output;\n        output << value;\n\
    \        const std::string text = output.str();\n        std::size_t begin = 0;\n\
    \        int sign = 1;\n        if (!text.empty() && (text[0] == '-' || text[0]\
    \ == '+')) {\n            if (text[0] == '-') sign = -1;\n            begin =\
    \ 1;\n        }\n        while (begin < text.size() && text[begin] == '0') ++begin;\n\
    \        if (begin == text.size()) return std::make_pair(0.0L, 0LL);\n\n     \
    \   constexpr int DIGITS = std::numeric_limits<long double>::digits10 + 1;\n \
    \       const std::size_t used = std::min<std::size_t>(DIGITS, text.size() - begin);\n\
    \        long double significand = 0;\n        for (std::size_t i = 0; i < used;\
    \ ++i) {\n            assert('0' <= text[begin + i] && text[begin + i] <= '9');\n\
    \            significand = significand * 10 + (text[begin + i] - '0');\n     \
    \   }\n        for (std::size_t i = 1; i < used; ++i) significand /= 10;\n   \
    \     const long long exponent = static_cast<long long>(text.size() - begin -\
    \ 1);\n        return std::make_pair(sign * significand, exponent);\n    }\n\n\
    \   public:\n    constexpr Rational() : _numerator(0), _denominator(1) {}\n\n\
    \    constexpr Rational(T integer) : _numerator(integer), _denominator(1) {}\n\
    \n    template <std::integral U>\n        requires std::constructible_from<T,\
    \ U> &&\n                 (!std::same_as<std::remove_cv_t<U>, T>)\n    constexpr\
    \ Rational(U integer) : Rational(T(integer)) {}\n\n    constexpr Rational(T numerator,\
    \ T denominator) {\n        assign_normalized(Wide(numerator), Wide(denominator));\n\
    \    }\n\n    constexpr T numerator() const {\n        return _numerator;\n  \
    \  }\n\n    constexpr T denominator() const {\n        return _denominator;\n\
    \    }\n\n    constexpr bool is_integer() const {\n        return _denominator\
    \ == 1;\n    }\n\n    constexpr int sign() const {\n        return (_numerator\
    \ > 0) - (_numerator < 0);\n    }\n\n    constexpr Rational reciprocal() const\
    \ {\n        assert(_numerator != 0);\n        return from_wide(Wide(_denominator),\
    \ Wide(_numerator));\n    }\n\n    constexpr Rational abs() const {\n        return\
    \ _numerator < 0 ? -*this : *this;\n    }\n\n    constexpr long double to_long_double()\
    \ const\n        requires requires(const T& value) { static_cast<long double>(value);\
    \ }\n    {\n        return static_cast<long double>(_numerator) / static_cast<long\
    \ double>(_denominator);\n    }\n\n    long double to_long_double() const\n  \
    \      requires(!requires(const T& value) { static_cast<long double>(value); })\n\
    \    {\n        const auto [numerator, numerator_exponent] = decimal_scientific(_numerator);\n\
    \        const auto [denominator, denominator_exponent] = decimal_scientific(_denominator);\n\
    \        return numerator / denominator *\n               std::pow(10.0L, numerator_exponent\
    \ - denominator_exponent);\n    }\n\n    explicit constexpr operator long double()\
    \ const\n        requires requires(const T& value) { static_cast<long double>(value);\
    \ }\n    {\n        return to_long_double();\n    }\n\n    explicit operator long\
    \ double() const\n        requires(!requires(const T& value) { static_cast<long\
    \ double>(value); })\n    {\n        return to_long_double();\n    }\n\n    constexpr\
    \ T trunc() const {\n        return _numerator / _denominator;\n    }\n\n    constexpr\
    \ T floor() const {\n        T quotient = _numerator / _denominator;\n       \
    \ if (_numerator < 0 && _numerator % _denominator != 0) quotient -= T(1);\n  \
    \      return quotient;\n    }\n\n    constexpr T ceil() const {\n        T quotient\
    \ = _numerator / _denominator;\n        if (0 < _numerator && _numerator % _denominator\
    \ != 0) quotient += T(1);\n        return quotient;\n    }\n\n    constexpr Rational\
    \ operator+() const {\n        return *this;\n    }\n\n    constexpr Rational\
    \ operator-() const {\n        return from_wide(-Wide(_numerator), Wide(_denominator));\n\
    \    }\n\n    constexpr Rational& operator+=(const Rational& other) {\n      \
    \  Magnitude common =\n            gcd(static_cast<Magnitude>(_denominator), static_cast<Magnitude>(other._denominator));\n\
    \        Wide left_scale = Wide(other._denominator) / static_cast<Wide>(common);\n\
    \        Wide right_scale = Wide(_denominator) / static_cast<Wide>(common);\n\
    \        assign_normalized(Wide(_numerator) * left_scale + Wide(other._numerator)\
    \ * right_scale,\n                          Wide(_denominator) * left_scale);\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator-=(const Rational&\
    \ other) {\n        return *this += -other;\n    }\n\n    constexpr Rational&\
    \ operator*=(const Rational& other) {\n        Magnitude first_gcd = gcd(magnitude(Wide(_numerator)),\
    \ static_cast<Magnitude>(other._denominator));\n        Magnitude second_gcd =\
    \ gcd(magnitude(Wide(other._numerator)), static_cast<Magnitude>(_denominator));\n\
    \        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *\n\
    \                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),\n\
    \                          (Wide(_denominator) / static_cast<Wide>(second_gcd))\
    \ *\n                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator/=(const Rational&\
    \ other) {\n        return *this *= other.reciprocal();\n    }\n\n    friend constexpr\
    \ Rational operator+(Rational left, const Rational& right) {\n        return left\
    \ += right;\n    }\n\n    friend constexpr Rational operator-(Rational left, const\
    \ Rational& right) {\n        return left -= right;\n    }\n\n    friend constexpr\
    \ Rational operator*(Rational left, const Rational& right) {\n        return left\
    \ *= right;\n    }\n\n    friend constexpr Rational operator/(Rational left, const\
    \ Rational& right) {\n        return left /= right;\n    }\n\n    friend constexpr\
    \ bool operator==(const Rational& left, const Rational& right) {\n        return\
    \ left._numerator == right._numerator && left._denominator == right._denominator;\n\
    \    }\n\n    friend constexpr std::strong_ordering operator<=>(const Rational&\
    \ left, const Rational& right) {\n        Wide first = Wide(left._numerator) *\
    \ Wide(right._denominator);\n        Wide second = Wide(right._numerator) * Wide(left._denominator);\n\
    \        if (first < second) return std::strong_ordering::less;\n        if (second\
    \ < first) return std::strong_ordering::greater;\n        return std::strong_ordering::equal;\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& output, const Rational&\
    \ value) {\n        output << value._numerator;\n        if (value._denominator\
    \ != 1) {\n            output << '/' << value._denominator;\n        }\n     \
    \   return output;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ input, Rational& value) {\n        std::string token;\n        if (!(input >>\
    \ token)) return input;\n\n        std::size_t slash = token.find('/');\n    \
    \    if (slash != std::string::npos && token.find('/', slash + 1) != std::string::npos)\
    \ {\n            input.setstate(std::ios::failbit);\n            return input;\n\
    \        }\n\n        T numerator = 0;\n        T denominator = 1;\n        std::istringstream\
    \ numerator_input(token.substr(0, slash));\n        if (!(numerator_input >> numerator)\
    \ || numerator_input.peek() != std::char_traits<char>::eof()) {\n            input.setstate(std::ios::failbit);\n\
    \            return input;\n        }\n        if (slash != std::string::npos)\
    \ {\n            std::istringstream denominator_input(token.substr(slash + 1));\n\
    \            if (!(denominator_input >> denominator) ||\n                denominator_input.peek()\
    \ != std::char_traits<char>::eof()) {\n                input.setstate(std::ios::failbit);\n\
    \                return input;\n            }\n        }\n        value = Rational(numerator,\
    \ denominator);\n        return input;\n    }\n};\n\ntemplate <rational_detail::IntegerLike\
    \ T>\nconstexpr Rational<T> abs(const Rational<T>& value) {\n    return value.abs();\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_RATIONAL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/rational.hpp
  requiredBy:
  - math/all.hpp
  - math/stern_brocot_tree.hpp
  timestamp: '2026-08-13 00:26:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/stern_brocot_tree.test.cpp
  - verify/math/yosupo_stern_brocot_tree.test.cpp
  - verify/math/rational.test.cpp
documentation_of: math/rational.hpp
layout: document
title: Rational Number
---

## Overview

`Rational<T>` represents an exact fraction using either a signed built-in
integral type or an integer-like class such as
[`utilities::BigInt`](../utilities/bigint.md).

Every value is normalized:

* numerator and denominator are coprime,
* the denominator is positive,
* zero is represented as `0/1`.

The default underlying type is `long long`.

## Construction

```cpp
Rational<T>();
Rational<T>(integer);
Rational<T>(numerator, denominator);
```

The denominator must be nonzero. Integer construction is implicit, so ordinary
integers can be mixed with rationals in arithmetic expressions.

Built-in `T` must be signed and no wider than `long long`. A custom `T` must be
copyable, constructible from `0` and `1`, and support signed comparison and the
usual exact integer arithmetic operations (`+`, `-`, `*`, `/`, and `%`).

## Complexity Notation

* `N` is the maximum storage size of a numerator, denominator, or intermediate.
* `C(N)`, `M(N)`, `D(N)`, and `G(N)` are the costs of copying, multiplying,
  dividing, and computing a gcd with `T`, respectively.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `numerator() const` | Returns the normalized numerator. | $O(C(N))$ |
| `denominator() const` | Returns the positive normalized denominator. | $O(C(N))$ |
| `is_integer() const` | Returns whether the denominator is one. | $O(1)$ |
| `sign() const` | Returns `-1`, `0`, or `1`. | $O(1)$ |
| `reciprocal() const` | Returns the reciprocal; requires a nonzero value. | $O(G(N) + D(N))$ |
| `abs() const` | Returns the absolute value. | $O(G(N) + D(N))$ |
| `trunc() const` | Rounds toward zero. | $O(D(N))$ |
| `floor() const` | Returns the mathematical floor. | $O(D(N))$ |
| `ceil() const` | Returns the mathematical ceiling. | $O(D(N))$ |
| `to_long_double() const` | Returns a floating-point approximation. | $O(1)$ for built-ins; $O(N)$ for custom types |

Arithmetic operators `+`, `-`, `*`, and `/`, their compound forms, unary signs,
equality, and three-way comparison are supported.

For built-in types, operations use `__int128_t` intermediates. The final
normalized numerator and denominator, and every intermediate widened
calculation, must be representable. Custom integer-like types are used directly,
so `Rational<BigInt>` provides unbounded exact intermediates. Arithmetic reduces
common or cross factors before multiplication when possible.

Construction takes $O(G(N) + D(N))$. Each arithmetic operation takes
$O(G(N) + M(N) + D(N))$; addition and subtraction also perform linear-time
addition on `T`. Comparison takes $O(M(N))$. For built-in types, Euclidean gcd
is logarithmic in the numeric magnitude and the other primitive operations are
$O(1)$.

## Input and Output

Output uses `numerator/denominator`, omitting `/1` for integers.

Input accepts either an integer or a fraction with no spaces around the slash:

```text
5
-7/12
```

## Example

```cpp
#include "math/rational.hpp"

#include <iostream>

int main() {
    using Fraction = m1une::math::Rational<long long>;

    Fraction first(2, 3);
    Fraction second(5, 6);
    Fraction result = first + second;

    std::cout << result << "\n";        // 3/2
    std::cout << result.floor() << "\n"; // 1
}
```

For unbounded fractions, instantiate the same interface with `BigInt`:

```cpp
#include "math/rational.hpp"
#include "utilities/bigint.hpp"

using BigInt = m1une::utilities::BigInt;
using BigFraction = m1une::math::Rational<BigInt>;

BigFraction value(BigInt("100000000000000000000"), BigInt(3));
BigFraction reciprocal = value.reciprocal();
```
