---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: utilities/bigint.hpp
    title: BigInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/centroid.test.cpp
    title: verify/geometry/centroid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/lattice_point_count.test.cpp
    title: verify/geometry/lattice_point_count.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ geometry/lattice_point_count.hpp: line 28: unable to process #include in #if\
    \ / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_GEOMETRY_LATTICE_POINT_COUNT_HPP\n#define M1UNE_GEOMETRY_LATTICE_POINT_COUNT_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <limits>\n#include <type_traits>\n#include <utility>\n#include\
    \ <vector>\n\n#ifndef M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST\n#if defined(__has_include)\n\
    #if __has_include(<boost/multiprecision/cpp_int.hpp>)\n#define M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST\
    \ 1\n#else\n#define M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST 0\n#endif\n#else\n\
    #define M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST 0\n#endif\n#endif\n\n#if\
    \ M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST\n#include <boost/multiprecision/cpp_int.hpp>\n\
    #else\n#include \"../utilities/bigint.hpp\"\n#endif\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\ntemplate <class T>\nstruct LinearInequality {\n    T a;\n    T\
    \ b;\n    T c;\n};\n\nnamespace lattice_point_count_detail {\n\n#if M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST\n\
    using Integer = boost::multiprecision::int256_t;\n\ninline Integer signed_int128_max()\
    \ {\n    return (Integer(1) << 127) - 1;\n}\n\ninline __int128_t to_int128(const\
    \ Integer& value) {\n    assert(0 <= value);\n    return static_cast<__int128_t>(value);\n\
    }\n#else\nusing Integer = ::m1une::utilities::BigInt;\n\ninline Integer signed_int128_max()\
    \ {\n    Integer result = 1;\n    for (int bit = 0; bit < 127; ++bit) result *=\
    \ 2;\n    result -= 1;\n    return result;\n}\n\ninline __int128_t to_int128(const\
    \ Integer& value) {\n    assert(0 <= value);\n    __uint128_t result = 0;\n  \
    \  for (\n        int index = static_cast<int>(value.a.size()) - 1;\n        index\
    \ >= 0;\n        --index\n    ) {\n        result = result * Integer::BASE + static_cast<unsigned>(value.a[index]);\n\
    \    }\n    return static_cast<__int128_t>(result);\n}\n#endif\n\nstruct Fraction\
    \ {\n    Integer numerator = 0;\n    Integer denominator = 1;\n\n    Fraction()\
    \ = default;\n\n    Fraction(Integer numerator_value, Integer denominator_value)\n\
    \        : numerator(numerator_value), denominator(denominator_value) {\n    \
    \    assert(denominator != 0);\n        if (denominator < 0) {\n            numerator\
    \ = -numerator;\n            denominator = -denominator;\n        }\n    }\n};\n\
    \ninline bool operator<(const Fraction& left, const Fraction& right) {\n    return\
    \ left.numerator * right.denominator <\n           right.numerator * left.denominator;\n\
    }\n\ninline bool operator==(const Fraction& left, const Fraction& right) {\n \
    \   return left.numerator * right.denominator ==\n           right.numerator *\
    \ left.denominator;\n}\n\ninline bool operator<=(const Fraction& left, const Fraction&\
    \ right) {\n    return !(right < left);\n}\n\nstruct Bound {\n    // -1 is negative\
    \ infinity, 0 is finite, and 1 is positive infinity.\n    int infinity = 0;\n\
    \    Fraction value;\n\n    static Bound negative_infinity() {\n        Bound\
    \ result;\n        result.infinity = -1;\n        return result;\n    }\n\n  \
    \  static Bound positive_infinity() {\n        Bound result;\n        result.infinity\
    \ = 1;\n        return result;\n    }\n\n    static Bound finite(const Fraction&\
    \ fraction) {\n        Bound result;\n        result.value = fraction;\n     \
    \   return result;\n    }\n};\n\ninline bool operator<(const Bound& left, const\
    \ Bound& right) {\n    if (left.infinity != right.infinity) {\n        return\
    \ left.infinity < right.infinity;\n    }\n    if (left.infinity != 0) return false;\n\
    \    return left.value < right.value;\n}\n\ninline bool operator==(const Bound&\
    \ left, const Bound& right) {\n    if (left.infinity != right.infinity) return\
    \ false;\n    return left.infinity != 0 || left.value == right.value;\n}\n\ninline\
    \ bool operator<=(const Bound& left, const Bound& right) {\n    return !(right\
    \ < left);\n}\n\ninline Bound maximum(const Bound& left, const Bound& right) {\n\
    \    return left < right ? right : left;\n}\n\ninline Bound minimum(const Bound&\
    \ left, const Bound& right) {\n    return right < left ? right : left;\n}\n\n\
    struct Line {\n    // Represents (slope_numerator * x + intercept_numerator) /\
    \ denominator.\n    Integer slope_numerator;\n    Integer intercept_numerator;\n\
    \    Integer denominator;\n};\n\ninline bool slope_less(const Line& left, const\
    \ Line& right) {\n    return left.slope_numerator * right.denominator <\n    \
    \       right.slope_numerator * left.denominator;\n}\n\ninline bool same_slope(const\
    \ Line& left, const Line& right) {\n    return left.slope_numerator * right.denominator\
    \ ==\n           right.slope_numerator * left.denominator;\n}\n\ninline bool intercept_less(const\
    \ Line& left, const Line& right) {\n    return left.intercept_numerator * right.denominator\
    \ <\n           right.intercept_numerator * left.denominator;\n}\n\ninline Fraction\
    \ intersection(const Line& left, const Line& right) {\n    Integer numerator =\n\
    \        left.intercept_numerator * right.denominator -\n        right.intercept_numerator\
    \ * left.denominator;\n    Integer denominator =\n        right.slope_numerator\
    \ * left.denominator -\n        left.slope_numerator * right.denominator;\n  \
    \  assert(denominator > 0);\n    return Fraction(numerator, denominator);\n}\n\
    \nstruct Envelope {\n    std::vector<Line> lines;\n    // starts[i] is the finite\
    \ x-coordinate where lines[i] becomes maximal.\n    // starts[0] is unused because\
    \ lines[0] starts at negative infinity.\n    std::vector<Fraction> starts;\n};\n\
    \ninline Envelope maximum_envelope(std::vector<Line> lines) {\n    std::sort(\n\
    \        lines.begin(),\n        lines.end(),\n        [](const Line& left, const\
    \ Line& right) {\n            if (!same_slope(left, right)) return slope_less(left,\
    \ right);\n            return intercept_less(right, left);\n        }\n    );\n\
    \n    std::vector<Line> unique;\n    for (const Line& line : lines) {\n      \
    \  if (unique.empty() || !same_slope(unique.back(), line)) {\n            unique.push_back(line);\n\
    \        }\n    }\n\n    Envelope result;\n    for (const Line& line : unique)\
    \ {\n        Fraction start;\n        while (!result.lines.empty()) {\n      \
    \      start = intersection(result.lines.back(), line);\n            if (\n  \
    \              result.lines.size() == 1 ||\n                result.starts.back()\
    \ < start\n            ) {\n                break;\n            }\n          \
    \  result.lines.pop_back();\n            result.starts.pop_back();\n        }\n\
    \        result.lines.push_back(line);\n        if (result.lines.size() == 1)\
    \ {\n            result.starts.emplace_back();\n        } else {\n           \
    \ result.starts.push_back(start);\n        }\n    }\n    return result;\n}\n\n\
    inline Bound segment_start(const Envelope& envelope, std::size_t index) {\n  \
    \  if (index == 0) return Bound::negative_infinity();\n    return Bound::finite(envelope.starts[index]);\n\
    }\n\ninline Bound segment_end(const Envelope& envelope, std::size_t index) {\n\
    \    if (index + 1 == envelope.lines.size()) {\n        return Bound::positive_infinity();\n\
    \    }\n    return Bound::finite(envelope.starts[index + 1]);\n}\n\ninline Integer\
    \ floor_div(Integer numerator, const Integer& denominator) {\n    assert(denominator\
    \ > 0);\n    Integer quotient = numerator / denominator;\n    Integer remainder\
    \ = numerator % denominator;\n    if (remainder < 0) quotient -= 1;\n    return\
    \ quotient;\n}\n\ninline Integer ceil_div(Integer numerator, const Integer& denominator)\
    \ {\n    return -floor_div(-numerator, denominator);\n}\n\ninline Integer floor_sum(\n\
    \    Integer count,\n    Integer modulus,\n    Integer multiplier,\n    Integer\
    \ constant\n) {\n    assert(count >= 0);\n    assert(modulus > 0);\n\n    Integer\
    \ answer = 0;\n    Integer quotient = floor_div(multiplier, modulus);\n    answer\
    \ += quotient * count * (count - 1) / 2;\n    multiplier -= quotient * modulus;\n\
    \n    quotient = floor_div(constant, modulus);\n    answer += quotient * count;\n\
    \    constant -= quotient * modulus;\n\n    while (true) {\n        if (multiplier\
    \ >= modulus) {\n            answer += count * (count - 1) / 2 * (multiplier /\
    \ modulus);\n            multiplier %= modulus;\n        }\n        if (constant\
    \ >= modulus) {\n            answer += count * (constant / modulus);\n       \
    \     constant %= modulus;\n        }\n\n        Integer maximum = multiplier\
    \ * count + constant;\n        if (maximum < modulus) break;\n        count =\
    \ maximum / modulus;\n        constant = maximum % modulus;\n        std::swap(modulus,\
    \ multiplier);\n    }\n    return answer;\n}\n\ninline std::pair<Bound, Bound>\
    \ feasible_projection(\n    const Envelope& lower,\n    const Envelope& negative_upper,\n\
    \    Bound domain_lower,\n    Bound domain_upper,\n    bool& feasible\n) {\n \
    \   Bound result_lower = Bound::positive_infinity();\n    Bound result_upper =\
    \ Bound::negative_infinity();\n    std::size_t lower_index = 0;\n    std::size_t\
    \ upper_index = 0;\n\n    while (\n        lower_index < lower.lines.size() &&\n\
    \        upper_index < negative_upper.lines.size()\n    ) {\n        Bound lower_end\
    \ = segment_end(lower, lower_index);\n        Bound upper_end = segment_end(negative_upper,\
    \ upper_index);\n        Bound left = maximum(\n            maximum(\n       \
    \         segment_start(lower, lower_index),\n                segment_start(negative_upper,\
    \ upper_index)\n            ),\n            domain_lower\n        );\n       \
    \ Bound right = minimum(minimum(lower_end, upper_end), domain_upper);\n\n    \
    \    const Line& lower_line = lower.lines[lower_index];\n        const Line& upper_line\
    \ = negative_upper.lines[upper_index];\n        Integer slope =\n            lower_line.slope_numerator\
    \ * upper_line.denominator +\n            upper_line.slope_numerator * lower_line.denominator;\n\
    \        Integer intercept =\n            lower_line.intercept_numerator * upper_line.denominator\
    \ +\n            upper_line.intercept_numerator * lower_line.denominator;\n\n\
    \        if (slope > 0) {\n            right = minimum(\n                right,\n\
    \                Bound::finite(Fraction(-intercept, slope))\n            );\n\
    \        } else if (slope < 0) {\n            left = maximum(\n              \
    \  left,\n                Bound::finite(Fraction(-intercept, slope))\n       \
    \     );\n        } else if (intercept > 0) {\n            left = Bound::positive_infinity();\n\
    \            right = Bound::negative_infinity();\n        }\n\n        if (left\
    \ <= right) {\n            if (!feasible) {\n                result_lower = left;\n\
    \                result_upper = right;\n                feasible = true;\n   \
    \         } else {\n                result_lower = minimum(result_lower, left);\n\
    \                result_upper = maximum(result_upper, right);\n            }\n\
    \        }\n\n        if (lower_end == upper_end) {\n            ++lower_index;\n\
    \            ++upper_index;\n        } else if (lower_end < upper_end) {\n   \
    \         ++lower_index;\n        } else {\n            ++upper_index;\n     \
    \   }\n    }\n    return {result_lower, result_upper};\n}\n\ninline Integer sum_floor_of_negative(\n\
    \    const Envelope& envelope,\n    Integer first_x,\n    Integer last_x\n) {\n\
    \    Integer answer = 0;\n    for (std::size_t index = 0; index < envelope.lines.size();\
    \ ++index) {\n        Integer left = first_x;\n        Integer right = last_x;\n\
    \        if (index > 0) {\n            left = std::max(\n                left,\n\
    \                ceil_div(\n                    envelope.starts[index].numerator,\n\
    \                    envelope.starts[index].denominator\n                )\n \
    \           );\n        }\n        if (index + 1 < envelope.lines.size()) {\n\
    \            right = std::min(\n                right,\n                ceil_div(\n\
    \                    envelope.starts[index + 1].numerator,\n                 \
    \   envelope.starts[index + 1].denominator\n                ) - 1\n          \
    \  );\n        }\n        if (right < left) continue;\n\n        const Line& line\
    \ = envelope.lines[index];\n        Integer count = right - left + 1;\n      \
    \  Integer multiplier = -line.slope_numerator;\n        Integer constant = -line.intercept_numerator\
    \ + multiplier * left;\n        answer += floor_sum(\n            count,\n   \
    \         line.denominator,\n            multiplier,\n            constant\n \
    \       );\n    }\n    return answer;\n}\n\n}  // namespace lattice_point_count_detail\n\
    \n// Counts integer pairs (x, y) satisfying every closed inequality\n// a * x\
    \ + b * y <= c. The real feasible region must be bounded.\ntemplate <class T>\n\
    __int128_t count_lattice_points(\n    const std::vector<LinearInequality<T>>&\
    \ inequalities\n) {\n    static_assert(\n        std::is_integral_v<T> && std::is_signed_v<T>\
    \ && sizeof(T) <= 8,\n        \"count_lattice_points requires a signed integer\
    \ type of at most 64 bits\"\n    );\n    namespace detail = lattice_point_count_detail;\n\
    \    using detail::Bound;\n    using detail::Envelope;\n    using detail::Fraction;\n\
    \    using detail::Integer;\n    using detail::Line;\n\n    std::vector<Line>\
    \ lower_lines;\n    std::vector<Line> negative_upper_lines;\n    Bound domain_lower\
    \ = Bound::negative_infinity();\n    Bound domain_upper = Bound::positive_infinity();\n\
    \n    for (const LinearInequality<T>& inequality : inequalities) {\n        Integer\
    \ a = inequality.a;\n        Integer b = inequality.b;\n        Integer c = inequality.c;\n\
    \        if (b < 0) {\n            lower_lines.push_back(Line{a, -c, -b});\n \
    \       } else if (b > 0) {\n            negative_upper_lines.push_back(Line{a,\
    \ -c, b});\n        } else if (a > 0) {\n            domain_upper = detail::minimum(\n\
    \                domain_upper,\n                Bound::finite(Fraction(c, a))\n\
    \            );\n        } else if (a < 0) {\n            domain_lower = detail::maximum(\n\
    \                domain_lower,\n                Bound::finite(Fraction(c, a))\n\
    \            );\n        } else if (c < 0) {\n            return 0;\n        }\n\
    \    }\n\n    if (domain_upper < domain_lower) return 0;\n    // Without both\
    \ y-envelopes, every feasible x-column is unbounded.\n    assert(!lower_lines.empty()\
    \ && !negative_upper_lines.empty());\n\n    Envelope lower = detail::maximum_envelope(std::move(lower_lines));\n\
    \    Envelope negative_upper =\n        detail::maximum_envelope(std::move(negative_upper_lines));\n\
    \n    bool feasible = false;\n    auto projection = detail::feasible_projection(\n\
    \        lower,\n        negative_upper,\n        domain_lower,\n        domain_upper,\n\
    \        feasible\n    );\n    if (!feasible) return 0;\n    assert(projection.first.infinity\
    \ == 0);\n    assert(projection.second.infinity == 0);\n\n    Integer first_x\
    \ = detail::ceil_div(\n        projection.first.value.numerator,\n        projection.first.value.denominator\n\
    \    );\n    Integer last_x = detail::floor_div(\n        projection.second.value.numerator,\n\
    \        projection.second.value.denominator\n    );\n    if (last_x < first_x)\
    \ return 0;\n    assert(first_x >= std::numeric_limits<long long>::min());\n \
    \   assert(first_x <= std::numeric_limits<long long>::max());\n    assert(last_x\
    \ >= std::numeric_limits<long long>::min());\n    assert(last_x <= std::numeric_limits<long\
    \ long>::max());\n\n    Integer answer = last_x - first_x + 1;\n    answer +=\
    \ detail::sum_floor_of_negative(\n        negative_upper,\n        first_x,\n\
    \        last_x\n    );\n    answer += detail::sum_floor_of_negative(lower, first_x,\
    \ last_x);\n\n    assert(answer >= 0);\n    assert(answer <= detail::signed_int128_max());\n\
    \    return detail::to_int128(answer);\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GEOMETRY_LATTICE_POINT_COUNT_HPP\n"
  dependsOn:
  - utilities/bigint.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: geometry/lattice_point_count.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/lattice_point_count.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/lattice_point_count.hpp
layout: document
title: Lattice-Point Count
---

## Overview

`count_lattice_points` counts the integer grid points in a bounded region
described by closed linear inequalities. Each constraint has the form

$$
a x + b y \leq c,
$$

where all three coefficients are signed integers. The calculation is exact:
rational boundary intersections and points on the boundary do not involve
floating-point tolerances.

The implementation constructs the piecewise-rational lower and upper envelopes
of the constraints. It finds the feasible projection onto the x-axis, then
sums each envelope piece with Euclidean floor-sum. It does not iterate over the
coordinate range.

## Interface

```cpp
template <class T>
struct LinearInequality {
    T a;
    T b;
    T c;
};

template <class T>
__int128_t count_lattice_points(
    const std::vector<LinearInequality<T>>& inequalities
);
```

| Member / Function | Description | Complexity |
| --- | --- | --- |
| `LinearInequality<T>{a, b, c}` | Represents the closed constraint $ax+by\leq c$. | $O(1)$ |
| `count_lattice_points(inequalities)` | Returns the number of integer pairs satisfying every constraint. | $O(N\log N+N\log C)$ time and $O(N)$ memory |

Here $N$ is `inequalities.size()`, and $C$ is the magnitude of the coefficients
and feasible coordinates. The logarithmic factor after envelope construction
comes from floor-sum.

`T` must be a signed integer type of at most 64 bits. The real feasible region
must be bounded, even when it is empty, a point, or a segment. In particular,
a bounded nonempty region has both a lower and an upper y-envelope. The integer
x-coordinates in its projection must fit `long long`, and the returned count
must fit signed `__int128`. These conditions are checked by assertions where
possible.

When `<boost/multiprecision/cpp_int.hpp>` is available, the internal exact
integer backend uses `boost::multiprecision::int256_t`. Otherwise it falls back
to the library's local `BigInt`. Define
`M1UNE_GEOMETRY_LATTICE_POINT_COUNT_USE_BOOST` to `0` before including this
header to force the fallback backend.

All inequalities are closed, so boundary grid points are included. A
constraint with `a == 0` and `b == 0` is either redundant when `c >= 0` or
makes the result zero when `c < 0`. The function does not mutate its input.

## Example

```cpp
#include "geometry/lattice_point_count.hpp"

#include <iostream>
#include <vector>

int main() {
    using m1une::geometry::LinearInequality;
    using m1une::geometry::count_lattice_points;

    // x >= 0, y >= 0, and x + y <= 2.
    std::vector<LinearInequality<long long>> constraints;
    constraints.push_back(LinearInequality<long long>{-1, 0, 0});
    constraints.push_back(LinearInequality<long long>{0, -1, 0});
    constraints.push_back(LinearInequality<long long>{1, 1, 2});

    long long answer = static_cast<long long>(
        count_lattice_points(constraints)
    );
    std::cout << answer << "\n";  // 6
}
```
