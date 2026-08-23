---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/gcd_of_gaussian_integers.test.cpp
    title: verify/math/gcd_of_gaussian_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/gaussian_integer.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <tuple>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral\
    \ T = long long>\nstruct GaussianInteger {\n    static_assert(sizeof(T) <= sizeof(long\
    \ long));\n\n    using value_type = T;\n    using norm_type = __uint128_t;\n\n\
    \    T real;\n    T imag;\n\n   private:\n    using wide_type = __int128_t;\n\n\
    \    struct SignedMagnitude {\n        norm_type magnitude;\n        bool negative;\n\
    \    };\n\n    static constexpr norm_type magnitude(T value) {\n        const\
    \ wide_type wide = value;\n        if (wide < 0) {\n            return static_cast<norm_type>(-(wide\
    \ + 1)) + 1;\n        }\n        return static_cast<norm_type>(wide);\n    }\n\
    \n    static constexpr SignedMagnitude signed_value(T value) {\n        return\
    \ SignedMagnitude{magnitude(value), value < 0};\n    }\n\n    static constexpr\
    \ SignedMagnitude negate(SignedMagnitude value) {\n        if (value.magnitude\
    \ != 0) value.negative = !value.negative;\n        return value;\n    }\n\n  \
    \  static constexpr SignedMagnitude add_signed(\n        SignedMagnitude first,\n\
    \        SignedMagnitude second\n    ) {\n        if (first.negative == second.negative)\
    \ {\n            return SignedMagnitude{\n                first.magnitude + second.magnitude,\n\
    \                first.negative\n            };\n        }\n        if (first.magnitude\
    \ < second.magnitude) {\n            return SignedMagnitude{\n               \
    \ second.magnitude - first.magnitude,\n                second.negative\n     \
    \       };\n        }\n        return SignedMagnitude{\n            first.magnitude\
    \ - second.magnitude,\n            first.magnitude == second.magnitude ? false\
    \ : first.negative\n        };\n    }\n\n    static constexpr SignedMagnitude\
    \ product(T first, T second) {\n        const norm_type result = magnitude(first)\
    \ * magnitude(second);\n        return SignedMagnitude{\n            result,\n\
    \            result != 0 && ((first < 0) != (second < 0))\n        };\n    }\n\
    \n    static constexpr T narrow(SignedMagnitude value) {\n        const norm_type\
    \ maximum =\n            static_cast<norm_type>(std::numeric_limits<T>::max());\n\
    \        if (!value.negative) {\n            assert(value.magnitude <= maximum);\n\
    \            return static_cast<T>(value.magnitude);\n        }\n\n        assert(value.magnitude\
    \ <= maximum + 1);\n        if (value.magnitude == maximum + 1) {\n          \
    \  return std::numeric_limits<T>::min();\n        }\n        return static_cast<T>(-static_cast<wide_type>(value.magnitude));\n\
    \    }\n\n    static constexpr std::pair<SignedMagnitude, SignedMagnitude>\n \
    \   product_components(\n        const GaussianInteger& first,\n        const\
    \ GaussianInteger& second\n    ) {\n        const SignedMagnitude product_real\
    \ = add_signed(\n            product(first.real, second.real),\n            negate(product(first.imag,\
    \ second.imag))\n        );\n        const SignedMagnitude product_imag = add_signed(\n\
    \            product(first.real, second.imag),\n            product(first.imag,\
    \ second.real)\n        );\n        return {product_real, product_imag};\n   \
    \ }\n\n    static constexpr T round_ratio(\n        SignedMagnitude numerator,\n\
    \        norm_type denominator\n    ) {\n        assert(denominator != 0);\n \
    \       norm_type quotient = numerator.magnitude / denominator;\n        const\
    \ norm_type remainder = numerator.magnitude % denominator;\n        if (remainder\
    \ + remainder >= denominator) quotient++;\n        return narrow(SignedMagnitude{quotient,\
    \ numerator.negative});\n    }\n\n   public:\n    constexpr GaussianInteger()\
    \ : real(0), imag(0) {}\n\n    constexpr GaussianInteger(T real_) : real(real_),\
    \ imag(0) {}\n\n    constexpr GaussianInteger(T real_, T imag_)\n        : real(real_),\
    \ imag(imag_) {}\n\n    constexpr bool is_zero() const {\n        return real\
    \ == 0 && imag == 0;\n    }\n\n    constexpr bool is_unit() const {\n        return\
    \ norm() == 1;\n    }\n\n    constexpr norm_type norm() const {\n        const\
    \ norm_type real_magnitude = magnitude(real);\n        const norm_type imag_magnitude\
    \ = magnitude(imag);\n        return real_magnitude * real_magnitude +\n     \
    \          imag_magnitude * imag_magnitude;\n    }\n\n    constexpr GaussianInteger\
    \ conjugate() const {\n        return GaussianInteger(real, narrow(negate(signed_value(imag))));\n\
    \    }\n\n    constexpr GaussianInteger normalizing_unit() const {\n        if\
    \ (is_zero() || (0 < real && 0 <= imag)) {\n            return GaussianInteger(1,\
    \ 0);\n        }\n        if (0 < real) return GaussianInteger(0, 1);\n      \
    \  if (real < 0 && imag <= 0) return GaussianInteger(-1, 0);\n        if (real\
    \ < 0) return GaussianInteger(0, -1);\n        if (0 < imag) return GaussianInteger(0,\
    \ -1);\n        return GaussianInteger(0, 1);\n    }\n\n    constexpr GaussianInteger\
    \ normalized() const {\n        return normalizing_unit() * *this;\n    }\n\n\
    \    constexpr std::pair<GaussianInteger, GaussianInteger> divmod(\n        const\
    \ GaussianInteger& divisor\n    ) const {\n        const norm_type divisor_norm\
    \ = divisor.norm();\n        assert(divisor_norm != 0);\n\n        const SignedMagnitude\
    \ numerator_real = add_signed(\n            product(real, divisor.real),\n   \
    \         product(imag, divisor.imag)\n        );\n        const SignedMagnitude\
    \ numerator_imag = add_signed(\n            product(imag, divisor.real),\n   \
    \         negate(product(real, divisor.imag))\n        );\n        const GaussianInteger\
    \ quotient(\n            round_ratio(numerator_real, divisor_norm),\n        \
    \    round_ratio(numerator_imag, divisor_norm)\n        );\n\n        const auto\
    \ product = product_components(quotient, divisor);\n        const GaussianInteger\
    \ remainder(\n            narrow(add_signed(signed_value(real), negate(product.first))),\n\
    \            narrow(add_signed(signed_value(imag), negate(product.second)))\n\
    \        );\n        assert(remainder.norm() < divisor_norm);\n        return\
    \ {quotient, remainder};\n    }\n\n    constexpr GaussianInteger operator+() const\
    \ {\n        return *this;\n    }\n\n    constexpr GaussianInteger operator-()\
    \ const {\n        return GaussianInteger(\n            narrow(negate(signed_value(real))),\n\
    \            narrow(negate(signed_value(imag)))\n        );\n    }\n\n    constexpr\
    \ GaussianInteger& operator+=(const GaussianInteger& other) {\n        real =\
    \ narrow(add_signed(signed_value(real), signed_value(other.real)));\n        imag\
    \ = narrow(add_signed(signed_value(imag), signed_value(other.imag)));\n      \
    \  return *this;\n    }\n\n    constexpr GaussianInteger& operator-=(const GaussianInteger&\
    \ other) {\n        real = narrow(add_signed(\n            signed_value(real),\n\
    \            negate(signed_value(other.real))\n        ));\n        imag = narrow(add_signed(\n\
    \            signed_value(imag),\n            negate(signed_value(other.imag))\n\
    \        ));\n        return *this;\n    }\n\n    constexpr GaussianInteger& operator*=(const\
    \ GaussianInteger& other) {\n        const auto result = product_components(*this,\
    \ other);\n        real = narrow(result.first);\n        imag = narrow(result.second);\n\
    \        return *this;\n    }\n\n    constexpr GaussianInteger& operator/=(const\
    \ GaussianInteger& other) {\n        *this = divmod(other).first;\n        return\
    \ *this;\n    }\n\n    constexpr GaussianInteger& operator%=(const GaussianInteger&\
    \ other) {\n        *this = divmod(other).second;\n        return *this;\n   \
    \ }\n\n    friend constexpr GaussianInteger operator+(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left +=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator-(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left -=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator*(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left *=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator/(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left /=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator%(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left %=\
    \ right;\n    }\n\n    friend constexpr bool operator==(\n        const GaussianInteger&\
    \ first,\n        const GaussianInteger& second\n    ) = default;\n};\n\ntemplate\
    \ <std::signed_integral T>\nconstexpr bool gaussian_divides(\n    const GaussianInteger<T>&\
    \ divisor,\n    const GaussianInteger<T>& value\n) {\n    if (divisor.is_zero())\
    \ return value.is_zero();\n    return (value % divisor).is_zero();\n}\n\ntemplate\
    \ <std::signed_integral T>\nconstexpr bool gaussian_associates(\n    const GaussianInteger<T>&\
    \ first,\n    const GaussianInteger<T>& second\n) {\n    return first.normalized()\
    \ == second.normalized();\n}\n\ntemplate <std::signed_integral T>\nconstexpr GaussianInteger<T>\
    \ gaussian_gcd(\n    GaussianInteger<T> first,\n    GaussianInteger<T> second\n\
    ) {\n    while (!second.is_zero()) {\n        first %= second;\n        std::swap(first,\
    \ second);\n    }\n    return first.normalized();\n}\n\ntemplate <std::signed_integral\
    \ T>\nconstexpr std::tuple<\n    GaussianInteger<T>,\n    GaussianInteger<T>,\n\
    \    GaussianInteger<T>\n> extended_gaussian_gcd(\n    GaussianInteger<T> first,\n\
    \    GaussianInteger<T> second\n) {\n    using G = GaussianInteger<T>;\n    G\
    \ old_remainder = first;\n    G remainder = second;\n    G old_first_coefficient(1);\n\
    \    G first_coefficient(0);\n    G old_second_coefficient(0);\n    G second_coefficient(1);\n\
    \n    while (!remainder.is_zero()) {\n        const G quotient = old_remainder\
    \ / remainder;\n\n        G next = old_remainder - quotient * remainder;\n   \
    \     old_remainder = remainder;\n        remainder = next;\n\n        next =\
    \ old_first_coefficient - quotient * first_coefficient;\n        old_first_coefficient\
    \ = first_coefficient;\n        first_coefficient = next;\n\n        next = old_second_coefficient\
    \ - quotient * second_coefficient;\n        old_second_coefficient = second_coefficient;\n\
    \        second_coefficient = next;\n    }\n\n    const G unit = old_remainder.normalizing_unit();\n\
    \    return {\n        unit * old_remainder,\n        unit * old_first_coefficient,\n\
    \        unit * old_second_coefficient\n    };\n}\n\n}  // namespace math\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_GAUSSIAN_INTEGER_HPP\n#define M1UNE_MATH_GAUSSIAN_INTEGER_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <limits>\n\
    #include <tuple>\n#include <utility>\n\nnamespace m1une {\nnamespace math {\n\n\
    template <std::signed_integral T = long long>\nstruct GaussianInteger {\n    static_assert(sizeof(T)\
    \ <= sizeof(long long));\n\n    using value_type = T;\n    using norm_type = __uint128_t;\n\
    \n    T real;\n    T imag;\n\n   private:\n    using wide_type = __int128_t;\n\
    \n    struct SignedMagnitude {\n        norm_type magnitude;\n        bool negative;\n\
    \    };\n\n    static constexpr norm_type magnitude(T value) {\n        const\
    \ wide_type wide = value;\n        if (wide < 0) {\n            return static_cast<norm_type>(-(wide\
    \ + 1)) + 1;\n        }\n        return static_cast<norm_type>(wide);\n    }\n\
    \n    static constexpr SignedMagnitude signed_value(T value) {\n        return\
    \ SignedMagnitude{magnitude(value), value < 0};\n    }\n\n    static constexpr\
    \ SignedMagnitude negate(SignedMagnitude value) {\n        if (value.magnitude\
    \ != 0) value.negative = !value.negative;\n        return value;\n    }\n\n  \
    \  static constexpr SignedMagnitude add_signed(\n        SignedMagnitude first,\n\
    \        SignedMagnitude second\n    ) {\n        if (first.negative == second.negative)\
    \ {\n            return SignedMagnitude{\n                first.magnitude + second.magnitude,\n\
    \                first.negative\n            };\n        }\n        if (first.magnitude\
    \ < second.magnitude) {\n            return SignedMagnitude{\n               \
    \ second.magnitude - first.magnitude,\n                second.negative\n     \
    \       };\n        }\n        return SignedMagnitude{\n            first.magnitude\
    \ - second.magnitude,\n            first.magnitude == second.magnitude ? false\
    \ : first.negative\n        };\n    }\n\n    static constexpr SignedMagnitude\
    \ product(T first, T second) {\n        const norm_type result = magnitude(first)\
    \ * magnitude(second);\n        return SignedMagnitude{\n            result,\n\
    \            result != 0 && ((first < 0) != (second < 0))\n        };\n    }\n\
    \n    static constexpr T narrow(SignedMagnitude value) {\n        const norm_type\
    \ maximum =\n            static_cast<norm_type>(std::numeric_limits<T>::max());\n\
    \        if (!value.negative) {\n            assert(value.magnitude <= maximum);\n\
    \            return static_cast<T>(value.magnitude);\n        }\n\n        assert(value.magnitude\
    \ <= maximum + 1);\n        if (value.magnitude == maximum + 1) {\n          \
    \  return std::numeric_limits<T>::min();\n        }\n        return static_cast<T>(-static_cast<wide_type>(value.magnitude));\n\
    \    }\n\n    static constexpr std::pair<SignedMagnitude, SignedMagnitude>\n \
    \   product_components(\n        const GaussianInteger& first,\n        const\
    \ GaussianInteger& second\n    ) {\n        const SignedMagnitude product_real\
    \ = add_signed(\n            product(first.real, second.real),\n            negate(product(first.imag,\
    \ second.imag))\n        );\n        const SignedMagnitude product_imag = add_signed(\n\
    \            product(first.real, second.imag),\n            product(first.imag,\
    \ second.real)\n        );\n        return {product_real, product_imag};\n   \
    \ }\n\n    static constexpr T round_ratio(\n        SignedMagnitude numerator,\n\
    \        norm_type denominator\n    ) {\n        assert(denominator != 0);\n \
    \       norm_type quotient = numerator.magnitude / denominator;\n        const\
    \ norm_type remainder = numerator.magnitude % denominator;\n        if (remainder\
    \ + remainder >= denominator) quotient++;\n        return narrow(SignedMagnitude{quotient,\
    \ numerator.negative});\n    }\n\n   public:\n    constexpr GaussianInteger()\
    \ : real(0), imag(0) {}\n\n    constexpr GaussianInteger(T real_) : real(real_),\
    \ imag(0) {}\n\n    constexpr GaussianInteger(T real_, T imag_)\n        : real(real_),\
    \ imag(imag_) {}\n\n    constexpr bool is_zero() const {\n        return real\
    \ == 0 && imag == 0;\n    }\n\n    constexpr bool is_unit() const {\n        return\
    \ norm() == 1;\n    }\n\n    constexpr norm_type norm() const {\n        const\
    \ norm_type real_magnitude = magnitude(real);\n        const norm_type imag_magnitude\
    \ = magnitude(imag);\n        return real_magnitude * real_magnitude +\n     \
    \          imag_magnitude * imag_magnitude;\n    }\n\n    constexpr GaussianInteger\
    \ conjugate() const {\n        return GaussianInteger(real, narrow(negate(signed_value(imag))));\n\
    \    }\n\n    constexpr GaussianInteger normalizing_unit() const {\n        if\
    \ (is_zero() || (0 < real && 0 <= imag)) {\n            return GaussianInteger(1,\
    \ 0);\n        }\n        if (0 < real) return GaussianInteger(0, 1);\n      \
    \  if (real < 0 && imag <= 0) return GaussianInteger(-1, 0);\n        if (real\
    \ < 0) return GaussianInteger(0, -1);\n        if (0 < imag) return GaussianInteger(0,\
    \ -1);\n        return GaussianInteger(0, 1);\n    }\n\n    constexpr GaussianInteger\
    \ normalized() const {\n        return normalizing_unit() * *this;\n    }\n\n\
    \    constexpr std::pair<GaussianInteger, GaussianInteger> divmod(\n        const\
    \ GaussianInteger& divisor\n    ) const {\n        const norm_type divisor_norm\
    \ = divisor.norm();\n        assert(divisor_norm != 0);\n\n        const SignedMagnitude\
    \ numerator_real = add_signed(\n            product(real, divisor.real),\n   \
    \         product(imag, divisor.imag)\n        );\n        const SignedMagnitude\
    \ numerator_imag = add_signed(\n            product(imag, divisor.real),\n   \
    \         negate(product(real, divisor.imag))\n        );\n        const GaussianInteger\
    \ quotient(\n            round_ratio(numerator_real, divisor_norm),\n        \
    \    round_ratio(numerator_imag, divisor_norm)\n        );\n\n        const auto\
    \ product = product_components(quotient, divisor);\n        const GaussianInteger\
    \ remainder(\n            narrow(add_signed(signed_value(real), negate(product.first))),\n\
    \            narrow(add_signed(signed_value(imag), negate(product.second)))\n\
    \        );\n        assert(remainder.norm() < divisor_norm);\n        return\
    \ {quotient, remainder};\n    }\n\n    constexpr GaussianInteger operator+() const\
    \ {\n        return *this;\n    }\n\n    constexpr GaussianInteger operator-()\
    \ const {\n        return GaussianInteger(\n            narrow(negate(signed_value(real))),\n\
    \            narrow(negate(signed_value(imag)))\n        );\n    }\n\n    constexpr\
    \ GaussianInteger& operator+=(const GaussianInteger& other) {\n        real =\
    \ narrow(add_signed(signed_value(real), signed_value(other.real)));\n        imag\
    \ = narrow(add_signed(signed_value(imag), signed_value(other.imag)));\n      \
    \  return *this;\n    }\n\n    constexpr GaussianInteger& operator-=(const GaussianInteger&\
    \ other) {\n        real = narrow(add_signed(\n            signed_value(real),\n\
    \            negate(signed_value(other.real))\n        ));\n        imag = narrow(add_signed(\n\
    \            signed_value(imag),\n            negate(signed_value(other.imag))\n\
    \        ));\n        return *this;\n    }\n\n    constexpr GaussianInteger& operator*=(const\
    \ GaussianInteger& other) {\n        const auto result = product_components(*this,\
    \ other);\n        real = narrow(result.first);\n        imag = narrow(result.second);\n\
    \        return *this;\n    }\n\n    constexpr GaussianInteger& operator/=(const\
    \ GaussianInteger& other) {\n        *this = divmod(other).first;\n        return\
    \ *this;\n    }\n\n    constexpr GaussianInteger& operator%=(const GaussianInteger&\
    \ other) {\n        *this = divmod(other).second;\n        return *this;\n   \
    \ }\n\n    friend constexpr GaussianInteger operator+(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left +=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator-(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left -=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator*(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left *=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator/(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left /=\
    \ right;\n    }\n\n    friend constexpr GaussianInteger operator%(\n        GaussianInteger\
    \ left,\n        const GaussianInteger& right\n    ) {\n        return left %=\
    \ right;\n    }\n\n    friend constexpr bool operator==(\n        const GaussianInteger&\
    \ first,\n        const GaussianInteger& second\n    ) = default;\n};\n\ntemplate\
    \ <std::signed_integral T>\nconstexpr bool gaussian_divides(\n    const GaussianInteger<T>&\
    \ divisor,\n    const GaussianInteger<T>& value\n) {\n    if (divisor.is_zero())\
    \ return value.is_zero();\n    return (value % divisor).is_zero();\n}\n\ntemplate\
    \ <std::signed_integral T>\nconstexpr bool gaussian_associates(\n    const GaussianInteger<T>&\
    \ first,\n    const GaussianInteger<T>& second\n) {\n    return first.normalized()\
    \ == second.normalized();\n}\n\ntemplate <std::signed_integral T>\nconstexpr GaussianInteger<T>\
    \ gaussian_gcd(\n    GaussianInteger<T> first,\n    GaussianInteger<T> second\n\
    ) {\n    while (!second.is_zero()) {\n        first %= second;\n        std::swap(first,\
    \ second);\n    }\n    return first.normalized();\n}\n\ntemplate <std::signed_integral\
    \ T>\nconstexpr std::tuple<\n    GaussianInteger<T>,\n    GaussianInteger<T>,\n\
    \    GaussianInteger<T>\n> extended_gaussian_gcd(\n    GaussianInteger<T> first,\n\
    \    GaussianInteger<T> second\n) {\n    using G = GaussianInteger<T>;\n    G\
    \ old_remainder = first;\n    G remainder = second;\n    G old_first_coefficient(1);\n\
    \    G first_coefficient(0);\n    G old_second_coefficient(0);\n    G second_coefficient(1);\n\
    \n    while (!remainder.is_zero()) {\n        const G quotient = old_remainder\
    \ / remainder;\n\n        G next = old_remainder - quotient * remainder;\n   \
    \     old_remainder = remainder;\n        remainder = next;\n\n        next =\
    \ old_first_coefficient - quotient * first_coefficient;\n        old_first_coefficient\
    \ = first_coefficient;\n        first_coefficient = next;\n\n        next = old_second_coefficient\
    \ - quotient * second_coefficient;\n        old_second_coefficient = second_coefficient;\n\
    \        second_coefficient = next;\n    }\n\n    const G unit = old_remainder.normalizing_unit();\n\
    \    return {\n        unit * old_remainder,\n        unit * old_first_coefficient,\n\
    \        unit * old_second_coefficient\n    };\n}\n\n}  // namespace math\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_MATH_GAUSSIAN_INTEGER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/gaussian_integer.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-08-24 03:45:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/gcd_of_gaussian_integers.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/gaussian_integer.hpp
layout: document
title: Gaussian Integer
---

## Overview

`GaussianInteger<T>` represents an exact number `a + b i` with integral real
and imaginary parts. Gaussian integers form a Euclidean domain under the norm

$$
N(a + b i) = a^2 + b^2.
$$

The type provides ordinary arithmetic, conjugation, exact nearest-quotient
Euclidean division, canonical associates, divisibility tests, GCD, and extended
GCD. All calculations are integral; division never uses floating point.

```cpp
#include "math/gaussian_integer.hpp"
```

## Template Requirements

`T` must be a standard signed integral type no wider than `long long`. The
default is `long long`. Coordinates returned by arithmetic and extended GCD
must remain representable by `T`; debug builds assert this condition.

Products, norms, and division numerators use exact 128-bit intermediates. The
public `norm_type` is `__uint128_t`, so the norm of every pair of 64-bit
coordinates is representable.

## Representation and Fields

| Member | Meaning |
| --- | --- |
| `value_type` | Alias for `T`. |
| `norm_type` | Unsigned 128-bit norm type. |
| `real` | Real coordinate `a`. |
| `imag` | Imaginary coordinate `b`. |

Equality compares both coordinates exactly.

## Euclidean Division

For a nonzero divisor `d`, `z.divmod(d)` returns `(q, r)` satisfying

$$
z = qd + r, \qquad N(r) < N(d).
$$

The real and imaginary coordinates of the exact complex quotient are rounded
to their nearest integers. Exact half-integer ties are rounded away from zero;
any consistent nearest choice gives a valid Euclidean remainder.

Consequently, `/` is Euclidean nearest-quotient division, not division in the
complex field. `%` returns its matching remainder. Division by zero is invalid
and asserted.

## Canonical Associates

The units are `1`, `-1`, `i`, and `-i`. Multiplying by a unit does not change
divisibility, so a nonzero Gaussian GCD has four associates.

`normalized()` chooses the unique associate with positive real part and
nonnegative imaginary part. Zero remains zero. `gaussian_gcd` and
`extended_gaussian_gcd` return this canonical associate, making their output
deterministic.

## Interface

All members and free functions are in `m1une::math`.

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Default constructor | `GaussianInteger()` | Constructs zero. | $O(1)$ |
| Real constructor | `GaussianInteger(T real)` | Constructs a real Gaussian integer. | $O(1)$ |
| Coordinate constructor | `GaussianInteger(T real, T imag)` | Constructs `real + imag * i`. | $O(1)$ |
| `is_zero` | `bool is_zero() const` | Tests equality with zero. | $O(1)$ |
| `is_unit` | `bool is_unit() const` | Tests whether the norm is one. | $O(1)$ |
| `norm` | `norm_type norm() const` | Returns `real * real + imag * imag`. | $O(1)$ |
| `conjugate` | `GaussianInteger conjugate() const` | Returns `real - imag * i`. | $O(1)$ |
| `normalizing_unit` | `GaussianInteger normalizing_unit() const` | Returns the unit that moves the value to its canonical associate. | $O(1)$ |
| `normalized` | `GaussianInteger normalized() const` | Returns the canonical associate. | $O(1)$ |
| `divmod` | `std::pair<GaussianInteger, GaussianInteger> divmod(const GaussianInteger& divisor) const` | Returns the Euclidean quotient and remainder. | $O(1)$ |
| Unary plus | `GaussianInteger operator+() const` | Returns the unchanged value. | $O(1)$ |
| Unary minus | `GaussianInteger operator-() const` | Negates both coordinates. | $O(1)$ |
| Compound addition | `GaussianInteger& operator+=(const GaussianInteger& other)` | Adds `other`. | $O(1)$ |
| Compound subtraction | `GaussianInteger& operator-=(const GaussianInteger& other)` | Subtracts `other`. | $O(1)$ |
| Compound multiplication | `GaussianInteger& operator*=(const GaussianInteger& other)` | Multiplies by `other`. | $O(1)$ |
| Compound division | `GaussianInteger& operator/=(const GaussianInteger& other)` | Replaces the value by its Euclidean quotient by `other`. | $O(1)$ |
| Compound remainder | `GaussianInteger& operator%=(const GaussianInteger& other)` | Replaces the value by its Euclidean remainder modulo `other`. | $O(1)$ |
| Binary addition | `friend GaussianInteger operator+(GaussianInteger left, const GaussianInteger& right)` | Returns `left + right`. | $O(1)$ |
| Binary subtraction | `friend GaussianInteger operator-(GaussianInteger left, const GaussianInteger& right)` | Returns `left - right`. | $O(1)$ |
| Binary multiplication | `friend GaussianInteger operator*(GaussianInteger left, const GaussianInteger& right)` | Returns `left * right`. | $O(1)$ |
| Binary division | `friend GaussianInteger operator/(GaussianInteger left, const GaussianInteger& right)` | Returns the Euclidean quotient. | $O(1)$ |
| Binary remainder | `friend GaussianInteger operator%(GaussianInteger left, const GaussianInteger& right)` | Returns the Euclidean remainder. | $O(1)$ |
| Equality | `friend bool operator==(const GaussianInteger& first, const GaussianInteger& second)` | Compares both coordinates. | $O(1)$ |

| Free function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `gaussian_divides` | `bool gaussian_divides(const GaussianInteger<T>& divisor, const GaussianInteger<T>& value)` | Tests `divisor` dividing `value`; zero divides only zero. | $O(1)$ |
| `gaussian_associates` | `bool gaussian_associates(const GaussianInteger<T>& first, const GaussianInteger<T>& second)` | Tests equality up to multiplication by a unit. | $O(1)$ |
| `gaussian_gcd` | `GaussianInteger<T> gaussian_gcd(GaussianInteger<T> first, GaussianInteger<T> second)` | Returns the canonical greatest common divisor. | $O(\log(\min(N(first), N(second)) + 1))$ |
| `extended_gaussian_gcd` | `std::tuple<GaussianInteger<T>, GaussianInteger<T>, GaussianInteger<T>> extended_gaussian_gcd(GaussianInteger<T> first, GaussianInteger<T> second)` | Returns `(g, x, y)` with `first * x + second * y == g`, where `g` is canonical. | $O(\log(\min(N(first), N(second)) + 1))$ |

The zero pair has GCD zero. For `gaussian_divides`, the convention that zero
divides zero follows directly from the existence of a Gaussian integer `z`
with `0 = 0 * z`.

## Example

```cpp
#include "math/gaussian_integer.hpp"

#include <iostream>

int main() {
    using G = m1une::math::GaussianInteger<long long>;

    G first(5, 7);
    G second(2, -1);
    auto [quotient, remainder] = first.divmod(second);

    G gcd = m1une::math::gaussian_gcd(first, second);
    std::cout << quotient.real << ' ' << quotient.imag << '\n';
    std::cout << remainder.real << ' ' << remainder.imag << '\n';
    std::cout << gcd.real << ' ' << gcd.imag << '\n';
}
```
