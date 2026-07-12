---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree_2d.hpp
    title: Fenwick Tree 2D
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n#line\
    \ 1 \"ds/range_query/fenwick_tree_2d.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T, class X\
    \ = int, class Y = X>\nclass FenwickTree2D {\n   public:\n    using value_type\
    \ = T;\n    using point_type = std::pair<X, Y>;\n    using weighted_point_type\
    \ = std::tuple<X, Y, T>;\n\n   private:\n    std::vector<point_type> _points;\n\
    \    std::vector<X> _xs;\n    std::vector<std::vector<Y>> _ys;\n    std::vector<std::vector<T>>\
    \ _data;\n\n    static std::vector<point_type> normalize_points(\n        std::vector<point_type>\
    \ points\n    ) {\n        std::sort(points.begin(), points.end());\n        points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n        return points;\n    }\n\n    T prefix_sum_by_x_count(int\
    \ x_count, const Y& y_upper) const {\n        T result{};\n        for (int x_index\
    \ = x_count; x_index > 0; x_index -= x_index & -x_index) {\n            const\
    \ std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n\
    \                std::lower_bound(ys.begin(), ys.end(), y_upper) - ys.begin()\n\
    \            );\n            const std::vector<T>& data = _data[std::size_t(x_index)];\n\
    \            while (y_index > 0) {\n                result += data[std::size_t(y_index)];\n\
    \                y_index -= y_index & -y_index;\n            }\n        }\n  \
    \      return result;\n    }\n\n    T prefix_sum(const X& x_upper, const Y& y_upper)\
    \ const {\n        const int x_count = int(\n            std::lower_bound(_xs.begin(),\
    \ _xs.end(), x_upper) - _xs.begin()\n        );\n        return prefix_sum_by_x_count(x_count,\
    \ y_upper);\n    }\n\n   public:\n    FenwickTree2D() : _ys(1), _data(1) {}\n\n\
    \    explicit FenwickTree2D(std::vector<point_type> points) {\n        build(std::move(points));\n\
    \    }\n\n    explicit FenwickTree2D(\n        const std::vector<weighted_point_type>&\
    \ points\n    ) {\n        build(points);\n    }\n\n    void build(std::vector<point_type>\
    \ points) {\n        _points = normalize_points(std::move(points));\n        _xs.clear();\n\
    \        _xs.reserve(_points.size());\n        for (const auto& [x, y] : _points)\
    \ {\n            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        const int x_size = int(_xs.size());\n        _ys.assign(std::size_t(x_size\
    \ + 1), {});\n        for (const auto& [x, y] : _points) {\n            int x_index\
    \ = int(\n                std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n\
    \            ) + 1;\n            while (x_index <= x_size) {\n               \
    \ _ys[std::size_t(x_index)].push_back(y);\n                x_index += x_index\
    \ & -x_index;\n            }\n        }\n\n        _data.assign(std::size_t(x_size\
    \ + 1), {});\n        for (int x_index = 1; x_index <= x_size; x_index++) {\n\
    \            std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            std::sort(ys.begin(),\
    \ ys.end());\n            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\
    \            _data[std::size_t(x_index)].assign(ys.size() + 1, T{});\n       \
    \ }\n    }\n\n    void build(const std::vector<weighted_point_type>& points) {\n\
    \        std::vector<point_type> coordinates;\n        coordinates.reserve(points.size());\n\
    \        for (const auto& [x, y, value] : points) {\n            (void)value;\n\
    \            coordinates.emplace_back(x, y);\n        }\n        build(std::move(coordinates));\n\
    \        for (const auto& [x, y, value] : points) add(x, y, value);\n    }\n\n\
    \    int size() const {\n        return int(_points.size());\n    }\n\n    bool\
    \ empty() const {\n        return _points.empty();\n    }\n\n    int x_size()\
    \ const {\n        return int(_xs.size());\n    }\n\n    const std::vector<X>&\
    \ xs() const {\n        return _xs;\n    }\n\n    bool contains_point(const X&\
    \ x, const Y& y) const {\n        return std::binary_search(_points.begin(), _points.end(),\
    \ point_type(x, y));\n    }\n\n    void add(const X& x, const Y& y, const T& value)\
    \ {\n        assert(contains_point(x, y));\n        int x_index = int(\n     \
    \       std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n        ) +\
    \ 1;\n        while (x_index <= int(_xs.size())) {\n            const std::vector<Y>&\
    \ ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n          \
    \      std::lower_bound(ys.begin(), ys.end(), y) - ys.begin()\n            ) +\
    \ 1;\n            std::vector<T>& data = _data[std::size_t(x_index)];\n      \
    \      while (y_index < int(data.size())) {\n                data[std::size_t(y_index)]\
    \ += value;\n                y_index += y_index & -y_index;\n            }\n \
    \           x_index += x_index & -x_index;\n        }\n    }\n\n    T sum(const\
    \ X& x_upper, const Y& y_upper) const {\n        return prefix_sum(x_upper, y_upper);\n\
    \    }\n\n    T sum(\n        const X& x_lower,\n        const X& x_upper,\n \
    \       const Y& y_lower,\n        const Y& y_upper\n    ) const {\n        assert(!(x_upper\
    \ < x_lower));\n        assert(!(y_upper < y_lower));\n        return prefix_sum(x_upper,\
    \ y_upper) -\n               prefix_sum(x_lower, y_upper) -\n               prefix_sum(x_upper,\
    \ y_lower) +\n               prefix_sum(x_lower, y_lower);\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <map>\n#line 12 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\
    \n\nnamespace {\n\nusing Point = std::pair<int, int>;\n\nlong long rectangle_sum(\n\
    \    const std::map<Point, long long>& values,\n    int x_lower,\n    int x_upper,\n\
    \    int y_lower,\n    int y_upper\n) {\n    long long result = 0;\n    for (const\
    \ auto& [point, value] : values) {\n        if (x_lower <= point.first && point.first\
    \ < x_upper &&\n            y_lower <= point.second && point.second < y_upper)\
    \ {\n            result += value;\n        }\n    }\n    return result;\n}\n\n\
    void test_edge_cases() {\n    m1une::ds::FenwickTree2D<long long> empty;\n   \
    \ assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.sum(10,\
    \ 20) == 0);\n    assert(empty.sum(-10, 10, -20, 20) == 0);\n\n    std::vector<std::tuple<int,\
    \ int, long long>> weighted{\n        {2, 3, 4},\n        {2, 3, 5},\n       \
    \ {-1, 7, 6}\n    };\n    m1une::ds::FenwickTree2D<long long> fenwick(weighted);\n\
    \    assert(fenwick.size() == 2);\n    assert(fenwick.x_size() == 2);\n    assert(fenwick.contains_point(2,\
    \ 3));\n    assert(!fenwick.contains_point(2, 4));\n    assert(fenwick.sum(2,\
    \ 3, 3, 4) == 9);\n    assert(fenwick.sum(100, 100) == 15);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0xc75b921e4a630df8ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 200; trial++) {\n        std::vector<Point>\
    \ points;\n        for (int index = 0; index < 50; index++) {\n            points.emplace_back(int(random()\
    \ % 21) - 10, int(random() % 21) - 10);\n        }\n        m1une::ds::FenwickTree2D<long\
    \ long> fenwick(points);\n        std::map<Point, long long> expected;\n     \
    \   for (const Point& point : points) expected[point] = 0;\n        assert(fenwick.size()\
    \ == int(expected.size()));\n\n        std::vector<Point> distinct_points;\n \
    \       for (const auto& [point, value] : expected) {\n            (void)value;\n\
    \            distinct_points.push_back(point);\n        }\n\n        for (int\
    \ operation = 0; operation < 500; operation++) {\n            if ((random() &\
    \ 1) == 0) {\n                const Point point =\n                    distinct_points[std::size_t(random()\
    \ % distinct_points.size())];\n                const long long value = static_cast<long\
    \ long>(random() % 101) - 50;\n                fenwick.add(point.first, point.second,\
    \ value);\n                expected[point] += value;\n            } else {\n \
    \               int x_lower = int(random() % 25) - 12;\n                int x_upper\
    \ = int(random() % 25) - 12;\n                int y_lower = int(random() % 25)\
    \ - 12;\n                int y_upper = int(random() % 25) - 12;\n            \
    \    if (x_upper < x_lower) std::swap(x_lower, x_upper);\n                if (y_upper\
    \ < y_lower) std::swap(y_lower, y_upper);\n                assert(\n         \
    \           fenwick.sum(x_lower, x_upper, y_lower, y_upper) ==\n             \
    \       rectangle_sum(expected, x_lower, x_upper, y_lower, y_upper)\n        \
    \        );\n                assert(\n                    fenwick.sum(x_upper,\
    \ y_upper) ==\n                    rectangle_sum(expected, -100, x_upper, -100,\
    \ y_upper)\n                );\n            }\n        }\n    }\n}\n\nstruct Query\
    \ {\n    int type;\n    int first;\n    int second;\n    int third;\n    int fourth;\n\
    \    long long value;\n};\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n\
    \    test_randomized();\n\n    int point_count, query_count;\n    std::cin >>\
    \ point_count >> query_count;\n    std::vector<std::tuple<int, int, long long>>\
    \ initial(\n        static_cast<std::size_t>(point_count)\n    );\n    std::vector<Point>\
    \ points;\n    points.reserve(static_cast<std::size_t>(point_count + query_count));\n\
    \    for (auto& [x, y, weight] : initial) {\n        std::cin >> x >> y >> weight;\n\
    \        points.emplace_back(x, y);\n    }\n\n    std::vector<Query> queries(static_cast<std::size_t>(query_count));\n\
    \    for (Query& query : queries) {\n        std::cin >> query.type;\n       \
    \ if (query.type == 0) {\n            std::cin >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            std::cin >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::FenwickTree2D<long long> fenwick(std::move(points));\n\
    \    for (const auto& [x, y, weight] : initial) fenwick.add(x, y, weight);\n\n\
    \    for (const Query& query : queries) {\n        if (query.type == 0) {\n  \
    \          fenwick.add(query.first, query.second, query.value);\n        } else\
    \ {\n            std::cout << fenwick.sum(\n                query.first,\n   \
    \             query.third,\n                query.second,\n                query.fourth\n\
    \            ) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../../ds/range_query/fenwick_tree_2d.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <map>\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace {\n\nusing Point = std::pair<int,\
    \ int>;\n\nlong long rectangle_sum(\n    const std::map<Point, long long>& values,\n\
    \    int x_lower,\n    int x_upper,\n    int y_lower,\n    int y_upper\n) {\n\
    \    long long result = 0;\n    for (const auto& [point, value] : values) {\n\
    \        if (x_lower <= point.first && point.first < x_upper &&\n            y_lower\
    \ <= point.second && point.second < y_upper) {\n            result += value;\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    m1une::ds::FenwickTree2D<long\
    \ long> empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n \
    \   assert(empty.sum(10, 20) == 0);\n    assert(empty.sum(-10, 10, -20, 20) ==\
    \ 0);\n\n    std::vector<std::tuple<int, int, long long>> weighted{\n        {2,\
    \ 3, 4},\n        {2, 3, 5},\n        {-1, 7, 6}\n    };\n    m1une::ds::FenwickTree2D<long\
    \ long> fenwick(weighted);\n    assert(fenwick.size() == 2);\n    assert(fenwick.x_size()\
    \ == 2);\n    assert(fenwick.contains_point(2, 3));\n    assert(!fenwick.contains_point(2,\
    \ 4));\n    assert(fenwick.sum(2, 3, 3, 4) == 9);\n    assert(fenwick.sum(100,\
    \ 100) == 15);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0xc75b921e4a630df8ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 200; trial++) {\n        std::vector<Point> points;\n        for (int index\
    \ = 0; index < 50; index++) {\n            points.emplace_back(int(random() %\
    \ 21) - 10, int(random() % 21) - 10);\n        }\n        m1une::ds::FenwickTree2D<long\
    \ long> fenwick(points);\n        std::map<Point, long long> expected;\n     \
    \   for (const Point& point : points) expected[point] = 0;\n        assert(fenwick.size()\
    \ == int(expected.size()));\n\n        std::vector<Point> distinct_points;\n \
    \       for (const auto& [point, value] : expected) {\n            (void)value;\n\
    \            distinct_points.push_back(point);\n        }\n\n        for (int\
    \ operation = 0; operation < 500; operation++) {\n            if ((random() &\
    \ 1) == 0) {\n                const Point point =\n                    distinct_points[std::size_t(random()\
    \ % distinct_points.size())];\n                const long long value = static_cast<long\
    \ long>(random() % 101) - 50;\n                fenwick.add(point.first, point.second,\
    \ value);\n                expected[point] += value;\n            } else {\n \
    \               int x_lower = int(random() % 25) - 12;\n                int x_upper\
    \ = int(random() % 25) - 12;\n                int y_lower = int(random() % 25)\
    \ - 12;\n                int y_upper = int(random() % 25) - 12;\n            \
    \    if (x_upper < x_lower) std::swap(x_lower, x_upper);\n                if (y_upper\
    \ < y_lower) std::swap(y_lower, y_upper);\n                assert(\n         \
    \           fenwick.sum(x_lower, x_upper, y_lower, y_upper) ==\n             \
    \       rectangle_sum(expected, x_lower, x_upper, y_lower, y_upper)\n        \
    \        );\n                assert(\n                    fenwick.sum(x_upper,\
    \ y_upper) ==\n                    rectangle_sum(expected, -100, x_upper, -100,\
    \ y_upper)\n                );\n            }\n        }\n    }\n}\n\nstruct Query\
    \ {\n    int type;\n    int first;\n    int second;\n    int third;\n    int fourth;\n\
    \    long long value;\n};\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n\
    \    test_randomized();\n\n    int point_count, query_count;\n    std::cin >>\
    \ point_count >> query_count;\n    std::vector<std::tuple<int, int, long long>>\
    \ initial(\n        static_cast<std::size_t>(point_count)\n    );\n    std::vector<Point>\
    \ points;\n    points.reserve(static_cast<std::size_t>(point_count + query_count));\n\
    \    for (auto& [x, y, weight] : initial) {\n        std::cin >> x >> y >> weight;\n\
    \        points.emplace_back(x, y);\n    }\n\n    std::vector<Query> queries(static_cast<std::size_t>(query_count));\n\
    \    for (Query& query : queries) {\n        std::cin >> query.type;\n       \
    \ if (query.type == 0) {\n            std::cin >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            std::cin >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::FenwickTree2D<long long> fenwick(std::move(points));\n\
    \    for (const auto& [x, y, weight] : initial) fenwick.add(x, y, weight);\n\n\
    \    for (const Query& query : queries) {\n        if (query.type == 0) {\n  \
    \          fenwick.add(query.first, query.second, query.value);\n        } else\
    \ {\n            std::cout << fenwick.sum(\n                query.first,\n   \
    \             query.third,\n                query.second,\n                query.fourth\n\
    \            ) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/fenwick_tree_2d.hpp
  isVerificationFile: true
  path: verify/ds/range_query/fenwick_tree_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 05:35:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/fenwick_tree_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/fenwick_tree_2d.test.cpp
- /verify/verify/ds/range_query/fenwick_tree_2d.test.cpp.html
title: verify/ds/range_query/fenwick_tree_2d.test.cpp
---
