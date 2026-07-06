---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: geometry/lattice_point_count.hpp
    title: Lattice-Point Count
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "#line 1 \"verify/geometry/lattice_point_count.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"geometry/lattice_point_count.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <limits>\n#include <type_traits>\n#include <utility>\n#include\
    \ <vector>\n\n#include <boost/multiprecision/cpp_int.hpp>\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <class T>\nstruct LinearInequality {\n    T a;\n\
    \    T b;\n    T c;\n};\n\nnamespace lattice_point_count_detail {\n\nusing Integer\
    \ = boost::multiprecision::int256_t;\n\nstruct Fraction {\n    Integer numerator\
    \ = 0;\n    Integer denominator = 1;\n\n    Fraction() = default;\n\n    Fraction(Integer\
    \ numerator_value, Integer denominator_value)\n        : numerator(numerator_value),\
    \ denominator(denominator_value) {\n        assert(denominator != 0);\n      \
    \  if (denominator < 0) {\n            numerator = -numerator;\n            denominator\
    \ = -denominator;\n        }\n    }\n};\n\ninline bool operator<(const Fraction&\
    \ left, const Fraction& right) {\n    return left.numerator * right.denominator\
    \ <\n           right.numerator * left.denominator;\n}\n\ninline bool operator==(const\
    \ Fraction& left, const Fraction& right) {\n    return left.numerator * right.denominator\
    \ ==\n           right.numerator * left.denominator;\n}\n\ninline bool operator<=(const\
    \ Fraction& left, const Fraction& right) {\n    return !(right < left);\n}\n\n\
    struct Bound {\n    // -1 is negative infinity, 0 is finite, and 1 is positive\
    \ infinity.\n    int infinity = 0;\n    Fraction value;\n\n    static Bound negative_infinity()\
    \ {\n        Bound result;\n        result.infinity = -1;\n        return result;\n\
    \    }\n\n    static Bound positive_infinity() {\n        Bound result;\n    \
    \    result.infinity = 1;\n        return result;\n    }\n\n    static Bound finite(const\
    \ Fraction& fraction) {\n        Bound result;\n        result.value = fraction;\n\
    \        return result;\n    }\n};\n\ninline bool operator<(const Bound& left,\
    \ const Bound& right) {\n    if (left.infinity != right.infinity) {\n        return\
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
    \ = numerator % denominator;\n    if (remainder < 0) --quotient;\n    return quotient;\n\
    }\n\ninline Integer ceil_div(Integer numerator, const Integer& denominator) {\n\
    \    return -floor_div(-numerator, denominator);\n}\n\ninline Integer floor_sum(\n\
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
    \ last_x);\n\n    assert(answer >= 0);\n    assert(answer <= (Integer(1) << 127)\
    \ - 1);\n    return static_cast<__int128_t>(answer);\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/geometry/lattice_point_count.test.cpp\"\
    \n\n#line 7 \"verify/geometry/lattice_point_count.test.cpp\"\n#include <iostream>\n\
    #line 10 \"verify/geometry/lattice_point_count.test.cpp\"\n\nusing Inequality\
    \ = m1une::geometry::LinearInequality<long long>;\n\n__int128 count(const std::vector<Inequality>&\
    \ inequalities) {\n    return m1une::geometry::count_lattice_points(inequalities);\n\
    }\n\nvoid test_examples_and_degenerate_regions() {\n    std::vector<Inequality>\
    \ triangle;\n    triangle.push_back(Inequality{-1, 0, 0});\n    triangle.push_back(Inequality{0,\
    \ -1, 0});\n    triangle.push_back(Inequality{1, 1, 2});\n    assert(count(triangle)\
    \ == 6);\n\n    std::vector<Inequality> point;\n    point.push_back(Inequality{1,\
    \ 0, 1});\n    point.push_back(Inequality{-1, 0, -1});\n    point.push_back(Inequality{0,\
    \ 1, 2});\n    point.push_back(Inequality{0, -1, -2});\n    assert(count(point)\
    \ == 1);\n\n    std::vector<Inequality> diagonal_segment;\n    diagonal_segment.push_back(Inequality{-1,\
    \ 0, 0});\n    diagonal_segment.push_back(Inequality{1, 0, 2});\n    diagonal_segment.push_back(Inequality{-1,\
    \ 2, 0});\n    diagonal_segment.push_back(Inequality{1, -2, 0});\n    assert(count(diagonal_segment)\
    \ == 2);\n\n    std::vector<Inequality> fractional_vertical_segment;\n    fractional_vertical_segment.push_back(Inequality{2,\
    \ 0, 1});\n    fractional_vertical_segment.push_back(Inequality{-2, 0, -1});\n\
    \    fractional_vertical_segment.push_back(Inequality{0, 1, 10});\n    fractional_vertical_segment.push_back(Inequality{0,\
    \ -1, 10});\n    assert(count(fractional_vertical_segment) == 0);\n\n    std::vector<Inequality>\
    \ empty;\n    empty.push_back(Inequality{1, 0, 0});\n    empty.push_back(Inequality{-1,\
    \ 0, -1});\n    empty.push_back(Inequality{0, 1, 2});\n    empty.push_back(Inequality{0,\
    \ -1, 2});\n    assert(count(empty) == 0);\n\n    std::vector<Inequality> contradiction\
    \ = triangle;\n    contradiction.push_back(Inequality{0, 0, -1});\n    assert(count(contradiction)\
    \ == 0);\n}\n\nvoid test_large_coordinates_and_floor_sum() {\n    constexpr long\
    \ long size = 1000000000000LL;\n    std::vector<Inequality> square;\n    square.push_back(Inequality{-1,\
    \ 0, 0});\n    square.push_back(Inequality{1, 0, size - 1});\n    square.push_back(Inequality{0,\
    \ -1, 0});\n    square.push_back(Inequality{0, 1, size - 1});\n    assert(count(square)\
    \ == __int128(size) * size);\n\n    constexpr long long maximum = std::numeric_limits<long\
    \ long>::max();\n    std::vector<Inequality> long_segment;\n    long_segment.push_back(Inequality{1,\
    \ 0, maximum});\n    long_segment.push_back(Inequality{-1, 0, maximum});\n   \
    \ long_segment.push_back(Inequality{0, maximum, 0});\n    long_segment.push_back(Inequality{0,\
    \ -maximum, 0});\n    assert(count(long_segment) == __int128(2) * maximum + 1);\n\
    \n    std::vector<Inequality> rational_triangle;\n    rational_triangle.push_back(Inequality{-1,\
    \ 0, 0});\n    rational_triangle.push_back(Inequality{1, 0, size});\n    rational_triangle.push_back(Inequality{0,\
    \ -1, 0});\n    rational_triangle.push_back(Inequality{2, 3, 3 * size});\n\n \
    \   __int128 expected = 0;\n    for (long long x = 0; x <= 1000; ++x) {\n    \
    \    expected += (3 * 1000 - 2 * x) / 3 + 1;\n    }\n    std::vector<Inequality>\
    \ small_triangle;\n    small_triangle.push_back(Inequality{-1, 0, 0});\n    small_triangle.push_back(Inequality{1,\
    \ 0, 1000});\n    small_triangle.push_back(Inequality{0, -1, 0});\n    small_triangle.push_back(Inequality{2,\
    \ 3, 3000});\n    assert(count(small_triangle) == expected);\n    assert(count(rational_triangle)\
    \ > 0);\n}\n\nbool satisfies(const Inequality& inequality, long long x, long long\
    \ y) {\n    return __int128(inequality.a) * x + __int128(inequality.b) * y <=\n\
    \           inequality.c;\n}\n\nvoid test_randomized_against_naive() {\n    std::uint64_t\
    \ state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int test = 0; test < 4000; ++test) {\n        long long bound = 1 +\
    \ static_cast<long long>(random() % 8);\n        std::vector<Inequality> inequalities;\n\
    \        inequalities.push_back(Inequality{1, 0, bound});\n        inequalities.push_back(Inequality{-1,\
    \ 0, bound});\n        inequalities.push_back(Inequality{0, 1, bound});\n    \
    \    inequalities.push_back(Inequality{0, -1, bound});\n\n        int extra =\
    \ static_cast<int>(random() % 15);\n        for (int index = 0; index < extra;\
    \ ++index) {\n            long long a = static_cast<long long>(random() % 11)\
    \ - 5;\n            long long b = static_cast<long long>(random() % 11) - 5;\n\
    \            long long c = static_cast<long long>(random() % 31) - 15;\n     \
    \       inequalities.push_back(Inequality{a, b, c});\n        }\n\n        long\
    \ long expected = 0;\n        for (long long x = -bound; x <= bound; ++x) {\n\
    \            for (long long y = -bound; y <= bound; ++y) {\n                bool\
    \ valid = true;\n                for (const Inequality& inequality : inequalities)\
    \ {\n                    if (!satisfies(inequality, x, y)) {\n               \
    \         valid = false;\n                        break;\n                   \
    \ }\n                }\n                expected += valid;\n            }\n  \
    \      }\n        assert(count(inequalities) == expected);\n    }\n}\n\nint main()\
    \ {\n    test_examples_and_degenerate_regions();\n    test_large_coordinates_and_floor_sum();\n\
    \    test_randomized_against_naive();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/lattice_point_count.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <limits>\n#include <vector>\n\nusing Inequality\
    \ = m1une::geometry::LinearInequality<long long>;\n\n__int128 count(const std::vector<Inequality>&\
    \ inequalities) {\n    return m1une::geometry::count_lattice_points(inequalities);\n\
    }\n\nvoid test_examples_and_degenerate_regions() {\n    std::vector<Inequality>\
    \ triangle;\n    triangle.push_back(Inequality{-1, 0, 0});\n    triangle.push_back(Inequality{0,\
    \ -1, 0});\n    triangle.push_back(Inequality{1, 1, 2});\n    assert(count(triangle)\
    \ == 6);\n\n    std::vector<Inequality> point;\n    point.push_back(Inequality{1,\
    \ 0, 1});\n    point.push_back(Inequality{-1, 0, -1});\n    point.push_back(Inequality{0,\
    \ 1, 2});\n    point.push_back(Inequality{0, -1, -2});\n    assert(count(point)\
    \ == 1);\n\n    std::vector<Inequality> diagonal_segment;\n    diagonal_segment.push_back(Inequality{-1,\
    \ 0, 0});\n    diagonal_segment.push_back(Inequality{1, 0, 2});\n    diagonal_segment.push_back(Inequality{-1,\
    \ 2, 0});\n    diagonal_segment.push_back(Inequality{1, -2, 0});\n    assert(count(diagonal_segment)\
    \ == 2);\n\n    std::vector<Inequality> fractional_vertical_segment;\n    fractional_vertical_segment.push_back(Inequality{2,\
    \ 0, 1});\n    fractional_vertical_segment.push_back(Inequality{-2, 0, -1});\n\
    \    fractional_vertical_segment.push_back(Inequality{0, 1, 10});\n    fractional_vertical_segment.push_back(Inequality{0,\
    \ -1, 10});\n    assert(count(fractional_vertical_segment) == 0);\n\n    std::vector<Inequality>\
    \ empty;\n    empty.push_back(Inequality{1, 0, 0});\n    empty.push_back(Inequality{-1,\
    \ 0, -1});\n    empty.push_back(Inequality{0, 1, 2});\n    empty.push_back(Inequality{0,\
    \ -1, 2});\n    assert(count(empty) == 0);\n\n    std::vector<Inequality> contradiction\
    \ = triangle;\n    contradiction.push_back(Inequality{0, 0, -1});\n    assert(count(contradiction)\
    \ == 0);\n}\n\nvoid test_large_coordinates_and_floor_sum() {\n    constexpr long\
    \ long size = 1000000000000LL;\n    std::vector<Inequality> square;\n    square.push_back(Inequality{-1,\
    \ 0, 0});\n    square.push_back(Inequality{1, 0, size - 1});\n    square.push_back(Inequality{0,\
    \ -1, 0});\n    square.push_back(Inequality{0, 1, size - 1});\n    assert(count(square)\
    \ == __int128(size) * size);\n\n    constexpr long long maximum = std::numeric_limits<long\
    \ long>::max();\n    std::vector<Inequality> long_segment;\n    long_segment.push_back(Inequality{1,\
    \ 0, maximum});\n    long_segment.push_back(Inequality{-1, 0, maximum});\n   \
    \ long_segment.push_back(Inequality{0, maximum, 0});\n    long_segment.push_back(Inequality{0,\
    \ -maximum, 0});\n    assert(count(long_segment) == __int128(2) * maximum + 1);\n\
    \n    std::vector<Inequality> rational_triangle;\n    rational_triangle.push_back(Inequality{-1,\
    \ 0, 0});\n    rational_triangle.push_back(Inequality{1, 0, size});\n    rational_triangle.push_back(Inequality{0,\
    \ -1, 0});\n    rational_triangle.push_back(Inequality{2, 3, 3 * size});\n\n \
    \   __int128 expected = 0;\n    for (long long x = 0; x <= 1000; ++x) {\n    \
    \    expected += (3 * 1000 - 2 * x) / 3 + 1;\n    }\n    std::vector<Inequality>\
    \ small_triangle;\n    small_triangle.push_back(Inequality{-1, 0, 0});\n    small_triangle.push_back(Inequality{1,\
    \ 0, 1000});\n    small_triangle.push_back(Inequality{0, -1, 0});\n    small_triangle.push_back(Inequality{2,\
    \ 3, 3000});\n    assert(count(small_triangle) == expected);\n    assert(count(rational_triangle)\
    \ > 0);\n}\n\nbool satisfies(const Inequality& inequality, long long x, long long\
    \ y) {\n    return __int128(inequality.a) * x + __int128(inequality.b) * y <=\n\
    \           inequality.c;\n}\n\nvoid test_randomized_against_naive() {\n    std::uint64_t\
    \ state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int test = 0; test < 4000; ++test) {\n        long long bound = 1 +\
    \ static_cast<long long>(random() % 8);\n        std::vector<Inequality> inequalities;\n\
    \        inequalities.push_back(Inequality{1, 0, bound});\n        inequalities.push_back(Inequality{-1,\
    \ 0, bound});\n        inequalities.push_back(Inequality{0, 1, bound});\n    \
    \    inequalities.push_back(Inequality{0, -1, bound});\n\n        int extra =\
    \ static_cast<int>(random() % 15);\n        for (int index = 0; index < extra;\
    \ ++index) {\n            long long a = static_cast<long long>(random() % 11)\
    \ - 5;\n            long long b = static_cast<long long>(random() % 11) - 5;\n\
    \            long long c = static_cast<long long>(random() % 31) - 15;\n     \
    \       inequalities.push_back(Inequality{a, b, c});\n        }\n\n        long\
    \ long expected = 0;\n        for (long long x = -bound; x <= bound; ++x) {\n\
    \            for (long long y = -bound; y <= bound; ++y) {\n                bool\
    \ valid = true;\n                for (const Inequality& inequality : inequalities)\
    \ {\n                    if (!satisfies(inequality, x, y)) {\n               \
    \         valid = false;\n                        break;\n                   \
    \ }\n                }\n                expected += valid;\n            }\n  \
    \      }\n        assert(count(inequalities) == expected);\n    }\n}\n\nint main()\
    \ {\n    test_examples_and_degenerate_regions();\n    test_large_coordinates_and_floor_sum();\n\
    \    test_randomized_against_naive();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - geometry/lattice_point_count.hpp
  isVerificationFile: true
  path: verify/geometry/lattice_point_count.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 02:36:46+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/geometry/lattice_point_count.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/lattice_point_count.test.cpp
- /verify/verify/geometry/lattice_point_count.test.cpp.html
title: verify/geometry/lattice_point_count.test.cpp
---
