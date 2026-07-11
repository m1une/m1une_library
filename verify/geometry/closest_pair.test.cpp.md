---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/closest_pair.hpp
    title: Closest Pair of Points
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/closest_pair
    links:
    - https://judge.yosupo.jp/problem/closest_pair
  bundledCode: "#line 1 \"verify/geometry/closest_pair.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/closest_pair\"\n\n#line 1 \"geometry/closest_pair.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <optional>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#include\
    \ <concepts>\n#include <cassert>\n#include <type_traits>\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
    \ && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate <Coordinate T>\nusing\
    \ wide_type = std::conditional_t<std::integral<T>, __int128_t, long double>;\n\
    \ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\n    constexpr\
    \ Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value) : x(x_value),\
    \ y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr Point(const\
    \ Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n\n    constexpr Point& operator+=(const Point& other) {\n        x += other.x;\n\
    \        y += other.y;\n        return *this;\n    }\n\n    constexpr Point& operator-=(const\
    \ Point& other) {\n        x -= other.x;\n        y -= other.y;\n        return\
    \ *this;\n    }\n\n    constexpr Point operator+() const {\n        return *this;\n\
    \    }\n\n    constexpr Point operator-() const {\n        return Point(-x, -y);\n\
    \    }\n\n    friend constexpr Point operator+(Point left, const Point& right)\
    \ {\n        return left += right;\n    }\n\n    friend constexpr Point operator-(Point\
    \ left, const Point& right) {\n        return left -= right;\n    }\n\n    friend\
    \ constexpr bool operator==(const Point&, const Point&) = default;\n\n    friend\
    \ constexpr bool operator<(const Point& left, const Point& right) {\n        if\
    \ (left.x != right.x) return left.x < right.x;\n        return left.y < right.y;\n\
    \    }\n};\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator*(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ * Result(scalar),\n        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate\
    \ <typename Scalar, Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator*(Scalar scalar, const Point<T>& point) {\n    return point * scalar;\n\
    }\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ / Result(scalar),\n        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> dot(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a,\
    \ const Point<T>& b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y)\
    \ - W(a.y) * W(b.x);\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n\
    \    const Point<T>& origin,\n    const Point<T>& a,\n    const Point<T>& b\n\
    ) {\n    using W = wide_type<T>;\n    W ax = W(a.x) - W(origin.x);\n    W ay =\
    \ W(a.y) - W(origin.y);\n    W bx = W(b.x) - W(origin.x);\n    W by = W(b.y) -\
    \ W(origin.y);\n    return ax * by - ay * bx;\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> norm2(const Point<T>& point) {\n    return dot(point, point);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> distance2(const Point<T>&\
    \ a, const Point<T>& b) {\n    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n\
    \    W dy = W(a.y) - W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double norm(const Point<T>& point) {\n    return std::hypot(\n    \
    \    static_cast<long double>(point.x),\n        static_cast<long double>(point.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& a,\
    \ const Point<T>& b) {\n    return std::hypot(\n        static_cast<long double>(a.x)\
    \ - static_cast<long double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long\
    \ double>(b.y)\n    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\n\
    requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\nconstexpr Point<long\
    \ double> internal_division_point(\n    const Point<T>& a,\n    const Point<T>&\
    \ b,\n    M m,\n    N n\n) {\n    long double first_ratio = static_cast<long double>(m);\n\
    \    long double second_ratio = static_cast<long double>(n);\n    long double\
    \ denominator = first_ratio + second_ratio;\n    assert(denominator != 0);\n \
    \   Point<long double> first(a);\n    Point<long double> direction = Point<long\
    \ double>(b) - first;\n    return first + direction * (first_ratio / denominator);\n\
    }\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> external_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio -\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr int sign(wide_type<T> value, long double eps = 1e-12L) {\n   \
    \ if constexpr (std::integral<T>) {\n        return (value > 0) - (value < 0);\n\
    \    } else {\n        return (value > eps) - (value < -eps);\n    }\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ bool collinear(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps)\
    \ == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> rotate(const Point<T>&\
    \ point, long double angle) {\n    long double cosine = std::cos(angle);\n   \
    \ long double sine = std::sin(angle);\n    return Point<long double>(\n      \
    \  static_cast<long double>(point.x) * cosine -\n            static_cast<long\
    \ double>(point.y) * sine,\n        static_cast<long double>(point.x) * sine +\n\
    \            static_cast<long double>(point.y) * cosine\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> normalized(const Point<T>& point) {\n   \
    \ long double length = norm(point);\n    assert(length != 0);\n    return Point<long\
    \ double>(\n        static_cast<long double>(point.x) / length,\n        static_cast<long\
    \ double>(point.y) / length\n    );\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 10 \"geometry/closest_pair.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\ntemplate <Coordinate T>\nstruct ClosestPair {\n    int first;\n\
    \    int second;\n    wide_type<T> distance_squared;\n};\n\n// Returns two distinct\
    \ original indices with minimum Euclidean distance.\ntemplate <Coordinate T>\n\
    std::optional<ClosestPair<T>> closest_pair(\n    const std::vector<Point<T>>&\
    \ points\n) {\n    const int n = int(points.size());\n    if (n < 2) return std::nullopt;\n\
    \n    struct IndexedPoint {\n        Point<T> point;\n        int index;\n   \
    \ };\n\n    std::vector<IndexedPoint> ordered;\n    ordered.reserve(n);\n    for\
    \ (int index = 0; index < n; index++) {\n        ordered.push_back(IndexedPoint{points[index],\
    \ index});\n    }\n    std::sort(\n        ordered.begin(),\n        ordered.end(),\n\
    \        [](const IndexedPoint& first, const IndexedPoint& second) {\n       \
    \     if (first.point < second.point) return true;\n            if (second.point\
    \ < first.point) return false;\n            return first.index < second.index;\n\
    \        }\n    );\n\n    std::optional<ClosestPair<T>> duplicate_result;\n  \
    \  for (int first = 0; first < n;) {\n        int last = first + 1;\n        while\
    \ (last < n && ordered[last].point == ordered[first].point) last++;\n        if\
    \ (last - first >= 2) {\n            int first_index = ordered[first].index;\n\
    \            int second_index = ordered[first + 1].index;\n            std::pair<int,\
    \ int> candidate(first_index, second_index);\n            if (\n             \
    \   !duplicate_result ||\n                candidate < std::pair(\n           \
    \         duplicate_result->first,\n                    duplicate_result->second\n\
    \                )\n            ) {\n                duplicate_result = ClosestPair<T>{\n\
    \                    first_index,\n                    second_index,\n       \
    \             wide_type<T>(0)\n                };\n            }\n        }\n\
    \        first = last;\n    }\n    if (duplicate_result) return duplicate_result;\n\
    \n    std::optional<ClosestPair<T>> result;\n    auto consider = [&result, &points](int\
    \ first, int second) {\n        if (second < first) std::swap(first, second);\n\
    \        wide_type<T> squared = distance2(points[first], points[second]);\n  \
    \      std::pair<int, int> candidate(first, second);\n        if (\n         \
    \   !result ||\n            squared < result->distance_squared ||\n          \
    \  (\n                squared == result->distance_squared &&\n               \
    \ candidate < std::pair(result->first, result->second)\n            )\n      \
    \  ) {\n            result = ClosestPair<T>{first, second, squared};\n       \
    \ }\n    };\n    consider(ordered[0].index, ordered[1].index);\n\n    auto by_y\
    \ = [](const IndexedPoint& first, const IndexedPoint& second) {\n        if (first.point.y\
    \ != second.point.y) {\n            return first.point.y < second.point.y;\n \
    \       }\n        if (first.point.x != second.point.x) {\n            return\
    \ first.point.x < second.point.x;\n        }\n        return first.index < second.index;\n\
    \    };\n\n    std::vector<IndexedPoint> buffer(n);\n    auto solve = [&](auto&&\
    \ self, int left, int right) -> void {\n        if (right - left <= 3) {\n   \
    \         for (int first = left; first < right; first++) {\n                for\
    \ (int second = first + 1; second < right; second++) {\n                    consider(ordered[first].index,\
    \ ordered[second].index);\n                }\n            }\n            std::sort(ordered.begin()\
    \ + left, ordered.begin() + right, by_y);\n            return;\n        }\n\n\
    \        int middle = (left + right) / 2;\n        T middle_x = ordered[middle].point.x;\n\
    \        self(self, left, middle);\n        self(self, middle, right);\n     \
    \   std::merge(\n            ordered.begin() + left,\n            ordered.begin()\
    \ + middle,\n            ordered.begin() + middle,\n            ordered.begin()\
    \ + right,\n            buffer.begin() + left,\n            by_y\n        );\n\
    \        std::copy(\n            buffer.begin() + left,\n            buffer.begin()\
    \ + right,\n            ordered.begin() + left\n        );\n\n        int strip_size\
    \ = 0;\n        for (int index = left; index < right; index++) {\n           \
    \ using W = wide_type<T>;\n            W dx = W(ordered[index].point.x) - W(middle_x);\n\
    \            if (result->distance_squared < dx * dx) continue;\n\n           \
    \ for (int previous = strip_size - 1; previous >= 0; previous--) {\n         \
    \       W dy = W(ordered[index].point.y) - W(buffer[previous].point.y);\n    \
    \            if (result->distance_squared < dy * dy) break;\n                consider(ordered[index].index,\
    \ buffer[previous].index);\n            }\n            buffer[strip_size++] =\
    \ ordered[index];\n        }\n    };\n    solve(solve, 0, n);\n    return result;\n\
    }\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 4 \"verify/geometry/closest_pair.test.cpp\"\
    \n\n#line 6 \"verify/geometry/closest_pair.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 11 \"verify/geometry/closest_pair.test.cpp\"\n\nnamespace\
    \ {\n\nusing Point = m1une::geometry::Point<long long>;\nusing Result = m1une::geometry::ClosestPair<long\
    \ long>;\n\nstd::optional<Result> brute_force(const std::vector<Point>& points)\
    \ {\n    std::optional<Result> result;\n    for (int first = 0; first < int(points.size());\
    \ first++) {\n        for (int second = first + 1; second < int(points.size());\
    \ second++) {\n            __int128_t squared =\n                m1une::geometry::distance2(points[first],\
    \ points[second]);\n            if (\n                !result ||\n           \
    \     squared < result->distance_squared ||\n                (\n             \
    \       squared == result->distance_squared &&\n                    std::pair(first,\
    \ second) <\n                        std::pair(result->first, result->second)\n\
    \                )\n            ) {\n                result = Result{first, second,\
    \ squared};\n            }\n        }\n    }\n    return result;\n}\n\nvoid check(const\
    \ std::vector<Point>& points) {\n    auto expected = brute_force(points);\n  \
    \  auto actual = m1une::geometry::closest_pair(points);\n    assert(expected.has_value()\
    \ == actual.has_value());\n    if (!actual) return;\n    assert(actual->first\
    \ == expected->first);\n    assert(actual->second == expected->second);\n    assert(actual->distance_squared\
    \ == expected->distance_squared);\n}\n\nvoid fixed_test() {\n    check({});\n\
    \    check({Point(3, 4)});\n    check({Point(0, 0), Point(10, 0)});\n    check({Point(2,\
    \ 3), Point(2, 3), Point(2, 3)});\n    check({\n        Point(0, 0),\n       \
    \ Point(1, 0),\n        Point(1, 1),\n        Point(0, 1),\n    });\n    check({\n\
    \        Point(-8, 0),\n        Point(-3, 0),\n        Point(4, 0),\n        Point(5,\
    \ 0),\n        Point(20, 0),\n    });\n\n    using FloatingPoint = m1une::geometry::Point<long\
    \ double>;\n    std::vector<FloatingPoint> floating_points;\n    floating_points.emplace_back(0.0L,\
    \ 0.0L);\n    floating_points.emplace_back(0.5L, 0.0L);\n    floating_points.emplace_back(4.0L,\
    \ 4.0L);\n    auto floating_answer = m1une::geometry::closest_pair(floating_points);\n\
    \    assert(floating_answer.has_value());\n    assert(floating_answer->first ==\
    \ 0);\n    assert(floating_answer->second == 1);\n    assert(floating_answer->distance_squared\
    \ == 0.25L);\n}\n\nvoid randomized_test() {\n    std::uint64_t state = 119;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 800; trial++) {\n        int size = int(random() % 31);\n        std::vector<Point>\
    \ points;\n        points.reserve(size);\n        for (int index = 0; index <\
    \ size; index++) {\n            points.emplace_back(\n                static_cast<long\
    \ long>(random() % 41) - 20,\n                static_cast<long long>(random()\
    \ % 41) - 20\n            );\n        }\n        check(points);\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    fixed_test();\n    randomized_test();\n\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ test_count;\n    std::cin >> test_count;\n    while (test_count--) {\n     \
    \   int n;\n        std::cin >> n;\n        std::vector<Point> points(n);\n  \
    \      for (Point& point : points) std::cin >> point.x >> point.y;\n\n       \
    \ auto answer = m1une::geometry::closest_pair(points);\n        assert(answer.has_value());\n\
    \        std::cout << answer->first << ' ' << answer->second << '\\n';\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/closest_pair\"\n\n#include\
    \ \"../../geometry/closest_pair.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nnamespace {\n\nusing Point = m1une::geometry::Point<long long>;\nusing Result\
    \ = m1une::geometry::ClosestPair<long long>;\n\nstd::optional<Result> brute_force(const\
    \ std::vector<Point>& points) {\n    std::optional<Result> result;\n    for (int\
    \ first = 0; first < int(points.size()); first++) {\n        for (int second =\
    \ first + 1; second < int(points.size()); second++) {\n            __int128_t\
    \ squared =\n                m1une::geometry::distance2(points[first], points[second]);\n\
    \            if (\n                !result ||\n                squared < result->distance_squared\
    \ ||\n                (\n                    squared == result->distance_squared\
    \ &&\n                    std::pair(first, second) <\n                       \
    \ std::pair(result->first, result->second)\n                )\n            ) {\n\
    \                result = Result{first, second, squared};\n            }\n   \
    \     }\n    }\n    return result;\n}\n\nvoid check(const std::vector<Point>&\
    \ points) {\n    auto expected = brute_force(points);\n    auto actual = m1une::geometry::closest_pair(points);\n\
    \    assert(expected.has_value() == actual.has_value());\n    if (!actual) return;\n\
    \    assert(actual->first == expected->first);\n    assert(actual->second == expected->second);\n\
    \    assert(actual->distance_squared == expected->distance_squared);\n}\n\nvoid\
    \ fixed_test() {\n    check({});\n    check({Point(3, 4)});\n    check({Point(0,\
    \ 0), Point(10, 0)});\n    check({Point(2, 3), Point(2, 3), Point(2, 3)});\n \
    \   check({\n        Point(0, 0),\n        Point(1, 0),\n        Point(1, 1),\n\
    \        Point(0, 1),\n    });\n    check({\n        Point(-8, 0),\n        Point(-3,\
    \ 0),\n        Point(4, 0),\n        Point(5, 0),\n        Point(20, 0),\n   \
    \ });\n\n    using FloatingPoint = m1une::geometry::Point<long double>;\n    std::vector<FloatingPoint>\
    \ floating_points;\n    floating_points.emplace_back(0.0L, 0.0L);\n    floating_points.emplace_back(0.5L,\
    \ 0.0L);\n    floating_points.emplace_back(4.0L, 4.0L);\n    auto floating_answer\
    \ = m1une::geometry::closest_pair(floating_points);\n    assert(floating_answer.has_value());\n\
    \    assert(floating_answer->first == 0);\n    assert(floating_answer->second\
    \ == 1);\n    assert(floating_answer->distance_squared == 0.25L);\n}\n\nvoid randomized_test()\
    \ {\n    std::uint64_t state = 119;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 800; trial++) {\n        int size = int(random()\
    \ % 31);\n        std::vector<Point> points;\n        points.reserve(size);\n\
    \        for (int index = 0; index < size; index++) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 41) - 20,\n               \
    \ static_cast<long long>(random() % 41) - 20\n            );\n        }\n    \
    \    check(points);\n    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_test();\n\
    \    randomized_test();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int test_count;\n    std::cin >> test_count;\n    while (test_count--) {\n\
    \        int n;\n        std::cin >> n;\n        std::vector<Point> points(n);\n\
    \        for (Point& point : points) std::cin >> point.x >> point.y;\n\n     \
    \   auto answer = m1une::geometry::closest_pair(points);\n        assert(answer.has_value());\n\
    \        std::cout << answer->first << ' ' << answer->second << '\\n';\n    }\n\
    }\n"
  dependsOn:
  - geometry/closest_pair.hpp
  - geometry/point.hpp
  isVerificationFile: true
  path: verify/geometry/closest_pair.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 20:28:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/closest_pair.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/closest_pair.test.cpp
- /verify/verify/geometry/closest_pair.test.cpp.html
title: verify/geometry/closest_pair.test.cpp
---
