---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/rational_approximation.test.cpp
    title: verify/math/rational_approximation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/rational_approximation.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nstruct RationalApproximationResult\
    \ {\n    using fraction_type = std::pair<T, T>;\n\n    fraction_type lower;\n\
    \    fraction_type upper;\n};\n\nnamespace rational_approximation_detail {\n\n\
    using Wide = __uint128_t;\n\nstruct Fraction {\n    Wide numerator;\n    Wide\
    \ denominator;\n};\n\ninline bool equal(\n    const Fraction& fraction,\n    Wide\
    \ numerator,\n    Wide denominator\n) {\n    return fraction.numerator * denominator\
    \ ==\n           numerator * fraction.denominator;\n}\n\ninline Wide coordinate_bound(\n\
    \    Wide maximum,\n    Wide offset,\n    Wide step\n) {\n    return step == 0\
    \ ? maximum : (maximum - offset) / step;\n}\n\ninline Fraction multiply_add(\n\
    \    const Fraction& first,\n    Wide multiplier,\n    const Fraction& second\n\
    ) {\n    return {\n        first.numerator * multiplier + second.numerator,\n\
    \        first.denominator * multiplier + second.denominator\n    };\n}\n\n} \
    \ // namespace rational_approximation_detail\n\n// Returns the closest reduced\
    \ fractions below and above numerator/denominator\n// whose positive numerator\
    \ and denominator are both at most maximum.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nRationalApproximationResult<T> rational_approximation(\n    T maximum,\n\
    \    T numerator,\n    T denominator\n) {\n    assert(maximum > 0);\n    assert(numerator\
    \ > 0);\n    assert(denominator > 0);\n    static_assert(sizeof(T) <= sizeof(uint64_t));\n\
    \n    using rational_approximation_detail::Fraction;\n    using rational_approximation_detail::Wide;\n\
    \    using rational_approximation_detail::coordinate_bound;\n    using rational_approximation_detail::equal;\n\
    \    using rational_approximation_detail::multiply_add;\n\n    const Wide limit\
    \ = static_cast<std::make_unsigned_t<T>>(maximum);\n    const Wide target_numerator\
    \ =\n        static_cast<std::make_unsigned_t<T>>(numerator);\n    const Wide\
    \ target_denominator =\n        static_cast<std::make_unsigned_t<T>>(denominator);\n\
    \    Fraction lower{0, 1};\n    Fraction upper{1, 0};\n\n    while (true) {\n\
    \        Wide lower_multiplier = limit;\n        lower_multiplier = std::min(\n\
    \            lower_multiplier,\n            coordinate_bound(limit, lower.numerator,\
    \ upper.numerator)\n        );\n        lower_multiplier = std::min(\n       \
    \     lower_multiplier,\n            coordinate_bound(limit, lower.denominator,\
    \ upper.denominator)\n        );\n        const Wide lower_slack =\n         \
    \   target_numerator * lower.denominator -\n            lower.numerator * target_denominator;\n\
    \        const Wide lower_step =\n            upper.numerator * target_denominator\
    \ -\n            target_numerator * upper.denominator;\n        assert(lower_step\
    \ != 0);\n        lower_multiplier = std::min(\n            lower_multiplier,\
    \ lower_slack / lower_step\n        );\n        lower = multiply_add(upper, lower_multiplier,\
    \ lower);\n        if (equal(lower, target_numerator, target_denominator)) {\n\
    \            upper = lower;\n            break;\n        }\n\n        Wide upper_multiplier\
    \ = limit;\n        upper_multiplier = std::min(\n            upper_multiplier,\n\
    \            coordinate_bound(limit, upper.numerator, lower.numerator)\n     \
    \   );\n        upper_multiplier = std::min(\n            upper_multiplier,\n\
    \            coordinate_bound(limit, upper.denominator, lower.denominator)\n \
    \       );\n        const Wide upper_slack =\n            upper.numerator * target_denominator\
    \ -\n            target_numerator * upper.denominator;\n        const Wide upper_step\
    \ =\n            target_numerator * lower.denominator -\n            lower.numerator\
    \ * target_denominator;\n        assert(upper_step != 0);\n        upper_multiplier\
    \ = std::min(\n            upper_multiplier, upper_slack / upper_step\n      \
    \  );\n        upper = multiply_add(lower, upper_multiplier, upper);\n       \
    \ if (equal(upper, target_numerator, target_denominator)) {\n            lower\
    \ = upper;\n            break;\n        }\n\n        if (lower_multiplier == 0\
    \ && upper_multiplier == 0) break;\n    }\n\n    RationalApproximationResult<T>\
    \ result;\n    result.lower = {\n        static_cast<T>(lower.numerator),\n  \
    \      static_cast<T>(lower.denominator)\n    };\n    result.upper = {\n     \
    \   static_cast<T>(upper.numerator),\n        static_cast<T>(upper.denominator)\n\
    \    };\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MATH_RATIONAL_APPROXIMATION_HPP\n#define M1UNE_MATH_RATIONAL_APPROXIMATION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstdint>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct RationalApproximationResult {\n    using fraction_type = std::pair<T,\
    \ T>;\n\n    fraction_type lower;\n    fraction_type upper;\n};\n\nnamespace rational_approximation_detail\
    \ {\n\nusing Wide = __uint128_t;\n\nstruct Fraction {\n    Wide numerator;\n \
    \   Wide denominator;\n};\n\ninline bool equal(\n    const Fraction& fraction,\n\
    \    Wide numerator,\n    Wide denominator\n) {\n    return fraction.numerator\
    \ * denominator ==\n           numerator * fraction.denominator;\n}\n\ninline\
    \ Wide coordinate_bound(\n    Wide maximum,\n    Wide offset,\n    Wide step\n\
    ) {\n    return step == 0 ? maximum : (maximum - offset) / step;\n}\n\ninline\
    \ Fraction multiply_add(\n    const Fraction& first,\n    Wide multiplier,\n \
    \   const Fraction& second\n) {\n    return {\n        first.numerator * multiplier\
    \ + second.numerator,\n        first.denominator * multiplier + second.denominator\n\
    \    };\n}\n\n}  // namespace rational_approximation_detail\n\n// Returns the\
    \ closest reduced fractions below and above numerator/denominator\n// whose positive\
    \ numerator and denominator are both at most maximum.\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nRationalApproximationResult<T>\
    \ rational_approximation(\n    T maximum,\n    T numerator,\n    T denominator\n\
    ) {\n    assert(maximum > 0);\n    assert(numerator > 0);\n    assert(denominator\
    \ > 0);\n    static_assert(sizeof(T) <= sizeof(uint64_t));\n\n    using rational_approximation_detail::Fraction;\n\
    \    using rational_approximation_detail::Wide;\n    using rational_approximation_detail::coordinate_bound;\n\
    \    using rational_approximation_detail::equal;\n    using rational_approximation_detail::multiply_add;\n\
    \n    const Wide limit = static_cast<std::make_unsigned_t<T>>(maximum);\n    const\
    \ Wide target_numerator =\n        static_cast<std::make_unsigned_t<T>>(numerator);\n\
    \    const Wide target_denominator =\n        static_cast<std::make_unsigned_t<T>>(denominator);\n\
    \    Fraction lower{0, 1};\n    Fraction upper{1, 0};\n\n    while (true) {\n\
    \        Wide lower_multiplier = limit;\n        lower_multiplier = std::min(\n\
    \            lower_multiplier,\n            coordinate_bound(limit, lower.numerator,\
    \ upper.numerator)\n        );\n        lower_multiplier = std::min(\n       \
    \     lower_multiplier,\n            coordinate_bound(limit, lower.denominator,\
    \ upper.denominator)\n        );\n        const Wide lower_slack =\n         \
    \   target_numerator * lower.denominator -\n            lower.numerator * target_denominator;\n\
    \        const Wide lower_step =\n            upper.numerator * target_denominator\
    \ -\n            target_numerator * upper.denominator;\n        assert(lower_step\
    \ != 0);\n        lower_multiplier = std::min(\n            lower_multiplier,\
    \ lower_slack / lower_step\n        );\n        lower = multiply_add(upper, lower_multiplier,\
    \ lower);\n        if (equal(lower, target_numerator, target_denominator)) {\n\
    \            upper = lower;\n            break;\n        }\n\n        Wide upper_multiplier\
    \ = limit;\n        upper_multiplier = std::min(\n            upper_multiplier,\n\
    \            coordinate_bound(limit, upper.numerator, lower.numerator)\n     \
    \   );\n        upper_multiplier = std::min(\n            upper_multiplier,\n\
    \            coordinate_bound(limit, upper.denominator, lower.denominator)\n \
    \       );\n        const Wide upper_slack =\n            upper.numerator * target_denominator\
    \ -\n            target_numerator * upper.denominator;\n        const Wide upper_step\
    \ =\n            target_numerator * lower.denominator -\n            lower.numerator\
    \ * target_denominator;\n        assert(upper_step != 0);\n        upper_multiplier\
    \ = std::min(\n            upper_multiplier, upper_slack / upper_step\n      \
    \  );\n        upper = multiply_add(lower, upper_multiplier, upper);\n       \
    \ if (equal(upper, target_numerator, target_denominator)) {\n            lower\
    \ = upper;\n            break;\n        }\n\n        if (lower_multiplier == 0\
    \ && upper_multiplier == 0) break;\n    }\n\n    RationalApproximationResult<T>\
    \ result;\n    result.lower = {\n        static_cast<T>(lower.numerator),\n  \
    \      static_cast<T>(lower.denominator)\n    };\n    result.upper = {\n     \
    \   static_cast<T>(upper.numerator),\n        static_cast<T>(upper.denominator)\n\
    \    };\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MATH_RATIONAL_APPROXIMATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/rational_approximation.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-16 21:30:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/rational_approximation.test.cpp
documentation_of: math/rational_approximation.hpp
layout: document
title: Rational Approximation
---

## Overview

`rational_approximation` brackets a positive rational number by the closest
reduced fractions whose numerators and denominators are both bounded.

For positive `maximum`, `numerator`, and `denominator`, it returns:

* the largest reduced $a/b\leq numerator/denominator$ with
  $1\leq a,b\leq maximum$, or `0/1` if none exists;
* the smallest reduced $c/d\geq numerator/denominator$ with
  $1\leq c,d\leq maximum$, or `1/0` if none exists.

The algorithm walks the Stern--Brocot interval with maximal run lengths. It
uses only exact unsigned 128-bit intermediate arithmetic and does not use
floating point.

## Interface

```cpp
template <std::integral T>
struct RationalApproximationResult {
    using fraction_type = std::pair<T, T>;

    fraction_type lower;
    fraction_type upper;
};

template <std::integral T>
RationalApproximationResult<T> rational_approximation(
    T maximum,
    T numerator,
    T denominator
);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `result.lower` | Pair `(numerator, denominator)` for the lower bound. | $O(1)$ access |
| `result.upper` | Pair `(numerator, denominator)` for the upper bound. | $O(1)$ access |
| `rational_approximation(maximum, numerator, denominator)` | Computes both closest bounded fractions. | $O(\log \max(maximum,numerator,denominator))$ time and $O(1)$ memory |

`T` may be a signed or unsigned integral type other than `bool`, with at most 64
bits. All three arguments must be positive. Returned ordinary fractions are
reduced; `0/1` and `1/0` are boundary sentinels and are not members of the
positive bounded set.

## Example

```cpp
#include "math/rational_approximation.hpp"

#include <cassert>
#include <utility>

int main() {
    auto result = m1une::math::rational_approximation(5LL, 7LL, 10LL);

    assert(result.lower == std::pair<long long, long long>(2, 3));
    assert(result.upper == std::pair<long long, long long>(3, 4));
}
```
