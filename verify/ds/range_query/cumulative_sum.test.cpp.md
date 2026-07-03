---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/cumulative_sum.hpp
    title: Cumulative Sum (1D, 2D, 3D)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"verify/ds/range_query/cumulative_sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <random>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"ds/range_query/cumulative_sum.hpp\"\n\n\n\n#line 5 \"ds/range_query/cumulative_sum.hpp\"\
    \n#include <cstddef>\n#line 7 \"ds/range_query/cumulative_sum.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// Static one-dimensional cumulative sums.\ntemplate\
    \ <typename T>\nstruct CumulativeSum1D {\n   private:\n    std::vector<T> _prefix;\n\
    \n   public:\n    CumulativeSum1D() : _prefix(1, T{}) {}\n\n    explicit CumulativeSum1D(const\
    \ std::vector<T>& values)\n        : _prefix(values.size() + 1, T{}) {\n     \
    \   for (std::size_t i = 0; i < values.size(); ++i) {\n            _prefix[i +\
    \ 1] = _prefix[i] + values[i];\n        }\n    }\n\n    int size() const {\n \
    \       return int(_prefix.size()) - 1;\n    }\n\n    bool empty() const {\n \
    \       return size() == 0;\n    }\n\n    // Returns the sum of [0, r).\n    T\
    \ sum(int r) const {\n        assert(0 <= r && r <= size());\n        return _prefix[r];\n\
    \    }\n\n    // Returns the sum of [l, r).\n    T sum(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= size());\n        return _prefix[r] -\
    \ _prefix[l];\n    }\n};\n\n// The unsuffixed name is an alias for the one-dimensional\
    \ structure.\ntemplate <typename T>\nusing CumulativeSum = CumulativeSum1D<T>;\n\
    \n// Static two-dimensional cumulative sums over a rectangular row-major grid.\n\
    template <typename T>\nstruct CumulativeSum2D {\n   private:\n    int _height;\n\
    \    int _width;\n    std::vector<T> _prefix;\n\n    std::size_t index(int y,\
    \ int x) const {\n        return std::size_t(y) * std::size_t(_width + 1) + std::size_t(x);\n\
    \    }\n\n   public:\n    CumulativeSum2D() : _height(0), _width(0), _prefix(1,\
    \ T{}) {}\n\n    explicit CumulativeSum2D(const std::vector<std::vector<T>>& values)\n\
    \        : _height(int(values.size())),\n          _width(values.empty() ? 0 :\
    \ int(values.front().size())),\n          _prefix(\n              std::size_t(_height\
    \ + 1) * std::size_t(_width + 1), T{}\n          ) {\n        for (const auto&\
    \ row : values) {\n            assert(int(row.size()) == _width);\n        }\n\
    \n        for (int y = 1; y <= _height; ++y) {\n            for (int x = 1; x\
    \ <= _width; ++x) {\n                _prefix[index(y, x)] =\n                \
    \    values[y - 1][x - 1] + _prefix[index(y - 1, x)]\n                    + _prefix[index(y,\
    \ x - 1)] - _prefix[index(y - 1, x - 1)];\n            }\n        }\n    }\n\n\
    \    int height() const {\n        return _height;\n    }\n\n    int width() const\
    \ {\n        return _width;\n    }\n\n    bool empty() const {\n        return\
    \ _height == 0 || _width == 0;\n    }\n\n    // Returns the sum of [0, y) x [0,\
    \ x).\n    T sum(int y, int x) const {\n        assert(0 <= y && y <= _height);\n\
    \        assert(0 <= x && x <= _width);\n        return _prefix[index(y, x)];\n\
    \    }\n\n    // Returns the sum of [y1, y2) x [x1, x2).\n    T sum(int y1, int\
    \ y2, int x1, int x2) const {\n        assert(0 <= y1 && y1 <= y2 && y2 <= _height);\n\
    \        assert(0 <= x1 && x1 <= x2 && x2 <= _width);\n        return _prefix[index(y2,\
    \ x2)] - _prefix[index(y1, x2)]\n               - _prefix[index(y2, x1)] + _prefix[index(y1,\
    \ x1)];\n    }\n};\n\n// Static three-dimensional cumulative sums over a rectangular\
    \ z-y-x grid.\ntemplate <typename T>\nstruct CumulativeSum3D {\n   private:\n\
    \    int _depth;\n    int _height;\n    int _width;\n    std::vector<T> _prefix;\n\
    \n    std::size_t index(int z, int y, int x) const {\n        return (std::size_t(z)\
    \ * std::size_t(_height + 1) + std::size_t(y))\n                   * std::size_t(_width\
    \ + 1)\n               + std::size_t(x);\n    }\n\n   public:\n    CumulativeSum3D()\n\
    \        : _depth(0), _height(0), _width(0), _prefix(1, T{}) {}\n\n    explicit\
    \ CumulativeSum3D(\n        const std::vector<std::vector<std::vector<T>>>& values\n\
    \    )\n        : _depth(int(values.size())),\n          _height(values.empty()\
    \ ? 0 : int(values.front().size())),\n          _width(\n              values.empty()\
    \ || values.front().empty()\n                  ? 0\n                  : int(values.front().front().size())\n\
    \          ),\n          _prefix(\n              std::size_t(_depth + 1) * std::size_t(_height\
    \ + 1)\n                  * std::size_t(_width + 1),\n              T{}\n    \
    \      ) {\n        for (const auto& plane : values) {\n            assert(int(plane.size())\
    \ == _height);\n            for (const auto& row : plane) {\n                assert(int(row.size())\
    \ == _width);\n            }\n        }\n\n        for (int z = 1; z <= _depth;\
    \ ++z) {\n            for (int y = 1; y <= _height; ++y) {\n                for\
    \ (int x = 1; x <= _width; ++x) {\n                    _prefix[index(z, y, x)]\
    \ =\n                        values[z - 1][y - 1][x - 1]\n                   \
    \     + _prefix[index(z - 1, y, x)]\n                        + _prefix[index(z,\
    \ y - 1, x)]\n                        + _prefix[index(z, y, x - 1)]\n        \
    \                - _prefix[index(z - 1, y - 1, x)]\n                        -\
    \ _prefix[index(z - 1, y, x - 1)]\n                        - _prefix[index(z,\
    \ y - 1, x - 1)]\n                        + _prefix[index(z - 1, y - 1, x - 1)];\n\
    \                }\n            }\n        }\n    }\n\n    int depth() const {\n\
    \        return _depth;\n    }\n\n    int height() const {\n        return _height;\n\
    \    }\n\n    int width() const {\n        return _width;\n    }\n\n    bool empty()\
    \ const {\n        return _depth == 0 || _height == 0 || _width == 0;\n    }\n\
    \n    // Returns the sum of [0, z) x [0, y) x [0, x).\n    T sum(int z, int y,\
    \ int x) const {\n        assert(0 <= z && z <= _depth);\n        assert(0 <=\
    \ y && y <= _height);\n        assert(0 <= x && x <= _width);\n        return\
    \ _prefix[index(z, y, x)];\n    }\n\n    // Returns the sum of [z1, z2) x [y1,\
    \ y2) x [x1, x2).\n    T sum(int z1, int z2, int y1, int y2, int x1, int x2) const\
    \ {\n        assert(0 <= z1 && z1 <= z2 && z2 <= _depth);\n        assert(0 <=\
    \ y1 && y1 <= y2 && y2 <= _height);\n        assert(0 <= x1 && x1 <= x2 && x2\
    \ <= _width);\n        return _prefix[index(z2, y2, x2)] - _prefix[index(z1, y2,\
    \ x2)]\n               - _prefix[index(z2, y1, x2)] - _prefix[index(z2, y2, x1)]\n\
    \               + _prefix[index(z1, y1, x2)] + _prefix[index(z1, y2, x1)]\n  \
    \             + _prefix[index(z2, y1, x1)] - _prefix[index(z1, y1, x1)];\n   \
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 10 \"verify/ds/range_query/cumulative_sum.test.cpp\"\
    \n\nvoid test_empty() {\n    m1une::ds::CumulativeSum1D<long long> sum1;\n   \
    \ m1une::ds::CumulativeSum2D<long long> sum2;\n    m1une::ds::CumulativeSum3D<long\
    \ long> sum3;\n    assert(sum1.empty());\n    assert(sum2.empty());\n    assert(sum3.empty());\n\
    \    assert(sum1.sum(0) == 0);\n    assert(sum2.sum(0, 0) == 0);\n    assert(sum3.sum(0,\
    \ 0, 0) == 0);\n    assert(sum1.sum(0, 0) == 0);\n    assert(sum2.sum(0, 0, 0,\
    \ 0) == 0);\n    assert(sum3.sum(0, 0, 0, 0, 0, 0) == 0);\n}\n\nvoid test_2d()\
    \ {\n    std::mt19937 rng(123456789);\n    for (int iteration = 0; iteration <\
    \ 100; ++iteration) {\n        const int height = int(rng() % 7);\n        const\
    \ int width = int(rng() % 7);\n        std::vector<std::vector<long long>> values(\n\
    \            height, std::vector<long long>(width)\n        );\n        for (auto&\
    \ row : values) {\n            for (long long& value : row) value = int(rng()\
    \ % 21) - 10;\n        }\n\n        m1une::ds::CumulativeSum2D<long long> sums(values);\n\
    \        assert(sums.height() == height);\n        assert(sums.width() == (height\
    \ == 0 ? 0 : width));\n\n        for (int y1 = 0; y1 <= height; ++y1) {\n    \
    \        for (int y2 = y1; y2 <= height; ++y2) {\n                for (int x1\
    \ = 0; x1 <= sums.width(); ++x1) {\n                    for (int x2 = x1; x2 <=\
    \ sums.width(); ++x2) {\n                        long long expected = 0;\n   \
    \                     for (int y = y1; y < y2; ++y) {\n                      \
    \      for (int x = x1; x < x2; ++x) {\n                                expected\
    \ += values[y][x];\n                            }\n                        }\n\
    \                        assert(sums.sum(y1, y2, x1, x2) == expected);\n     \
    \               }\n                }\n            }\n        }\n    }\n}\n\nvoid\
    \ test_3d() {\n    std::mt19937 rng(987654321);\n    for (int iteration = 0; iteration\
    \ < 100; ++iteration) {\n        const int depth = int(rng() % 5);\n        const\
    \ int height = int(rng() % 5);\n        const int width = int(rng() % 5);\n  \
    \      std::vector<std::vector<std::vector<long long>>> values(\n            depth,\n\
    \            std::vector<std::vector<long long>>(\n                height, std::vector<long\
    \ long>(width)\n            )\n        );\n        for (auto& plane : values)\
    \ {\n            for (auto& row : plane) {\n                for (long long& value\
    \ : row) value = int(rng() % 21) - 10;\n            }\n        }\n\n        m1une::ds::CumulativeSum3D<long\
    \ long> sums(values);\n        assert(sums.depth() == depth);\n        assert(sums.height()\
    \ == (depth == 0 ? 0 : height));\n        assert(sums.width() == (depth == 0 ||\
    \ height == 0 ? 0 : width));\n\n        for (int query = 0; query < 200; ++query)\
    \ {\n            int z1 = int(rng() % (sums.depth() + 1));\n            int z2\
    \ = int(rng() % (sums.depth() + 1));\n            int y1 = int(rng() % (sums.height()\
    \ + 1));\n            int y2 = int(rng() % (sums.height() + 1));\n           \
    \ int x1 = int(rng() % (sums.width() + 1));\n            int x2 = int(rng() %\
    \ (sums.width() + 1));\n            if (z1 > z2) std::swap(z1, z2);\n        \
    \    if (y1 > y2) std::swap(y1, y2);\n            if (x1 > x2) std::swap(x1, x2);\n\
    \n            long long expected = 0;\n            for (int z = z1; z < z2; ++z)\
    \ {\n                for (int y = y1; y < y2; ++y) {\n                    for\
    \ (int x = x1; x < x2; ++x) {\n                        expected += values[z][y][x];\n\
    \                    }\n                }\n            }\n            assert(sums.sum(z1,\
    \ z2, y1, y2, x1, x2) == expected);\n        }\n    }\n}\n\nint main() {\n   \
    \ test_empty();\n    test_2d();\n    test_3d();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    if (!(std::cin >> n >> q)) return\
    \ 0;\n    std::vector<long long> values(n);\n    for (long long& value : values)\
    \ std::cin >> value;\n\n    m1une::ds::CumulativeSum<long long> sums(values);\n\
    \    while (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        std::cout\
    \ << sums.sum(l, r) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../../ds/range_query/cumulative_sum.hpp\"\n\
    \nvoid test_empty() {\n    m1une::ds::CumulativeSum1D<long long> sum1;\n    m1une::ds::CumulativeSum2D<long\
    \ long> sum2;\n    m1une::ds::CumulativeSum3D<long long> sum3;\n    assert(sum1.empty());\n\
    \    assert(sum2.empty());\n    assert(sum3.empty());\n    assert(sum1.sum(0)\
    \ == 0);\n    assert(sum2.sum(0, 0) == 0);\n    assert(sum3.sum(0, 0, 0) == 0);\n\
    \    assert(sum1.sum(0, 0) == 0);\n    assert(sum2.sum(0, 0, 0, 0) == 0);\n  \
    \  assert(sum3.sum(0, 0, 0, 0, 0, 0) == 0);\n}\n\nvoid test_2d() {\n    std::mt19937\
    \ rng(123456789);\n    for (int iteration = 0; iteration < 100; ++iteration) {\n\
    \        const int height = int(rng() % 7);\n        const int width = int(rng()\
    \ % 7);\n        std::vector<std::vector<long long>> values(\n            height,\
    \ std::vector<long long>(width)\n        );\n        for (auto& row : values)\
    \ {\n            for (long long& value : row) value = int(rng() % 21) - 10;\n\
    \        }\n\n        m1une::ds::CumulativeSum2D<long long> sums(values);\n  \
    \      assert(sums.height() == height);\n        assert(sums.width() == (height\
    \ == 0 ? 0 : width));\n\n        for (int y1 = 0; y1 <= height; ++y1) {\n    \
    \        for (int y2 = y1; y2 <= height; ++y2) {\n                for (int x1\
    \ = 0; x1 <= sums.width(); ++x1) {\n                    for (int x2 = x1; x2 <=\
    \ sums.width(); ++x2) {\n                        long long expected = 0;\n   \
    \                     for (int y = y1; y < y2; ++y) {\n                      \
    \      for (int x = x1; x < x2; ++x) {\n                                expected\
    \ += values[y][x];\n                            }\n                        }\n\
    \                        assert(sums.sum(y1, y2, x1, x2) == expected);\n     \
    \               }\n                }\n            }\n        }\n    }\n}\n\nvoid\
    \ test_3d() {\n    std::mt19937 rng(987654321);\n    for (int iteration = 0; iteration\
    \ < 100; ++iteration) {\n        const int depth = int(rng() % 5);\n        const\
    \ int height = int(rng() % 5);\n        const int width = int(rng() % 5);\n  \
    \      std::vector<std::vector<std::vector<long long>>> values(\n            depth,\n\
    \            std::vector<std::vector<long long>>(\n                height, std::vector<long\
    \ long>(width)\n            )\n        );\n        for (auto& plane : values)\
    \ {\n            for (auto& row : plane) {\n                for (long long& value\
    \ : row) value = int(rng() % 21) - 10;\n            }\n        }\n\n        m1une::ds::CumulativeSum3D<long\
    \ long> sums(values);\n        assert(sums.depth() == depth);\n        assert(sums.height()\
    \ == (depth == 0 ? 0 : height));\n        assert(sums.width() == (depth == 0 ||\
    \ height == 0 ? 0 : width));\n\n        for (int query = 0; query < 200; ++query)\
    \ {\n            int z1 = int(rng() % (sums.depth() + 1));\n            int z2\
    \ = int(rng() % (sums.depth() + 1));\n            int y1 = int(rng() % (sums.height()\
    \ + 1));\n            int y2 = int(rng() % (sums.height() + 1));\n           \
    \ int x1 = int(rng() % (sums.width() + 1));\n            int x2 = int(rng() %\
    \ (sums.width() + 1));\n            if (z1 > z2) std::swap(z1, z2);\n        \
    \    if (y1 > y2) std::swap(y1, y2);\n            if (x1 > x2) std::swap(x1, x2);\n\
    \n            long long expected = 0;\n            for (int z = z1; z < z2; ++z)\
    \ {\n                for (int y = y1; y < y2; ++y) {\n                    for\
    \ (int x = x1; x < x2; ++x) {\n                        expected += values[z][y][x];\n\
    \                    }\n                }\n            }\n            assert(sums.sum(z1,\
    \ z2, y1, y2, x1, x2) == expected);\n        }\n    }\n}\n\nint main() {\n   \
    \ test_empty();\n    test_2d();\n    test_3d();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    if (!(std::cin >> n >> q)) return\
    \ 0;\n    std::vector<long long> values(n);\n    for (long long& value : values)\
    \ std::cin >> value;\n\n    m1une::ds::CumulativeSum<long long> sums(values);\n\
    \    while (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        std::cout\
    \ << sums.sum(l, r) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/cumulative_sum.hpp
  isVerificationFile: true
  path: verify/ds/range_query/cumulative_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-03 14:46:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/cumulative_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/cumulative_sum.test.cpp
- /verify/verify/ds/range_query/cumulative_sum.test.cpp.html
title: verify/ds/range_query/cumulative_sum.test.cpp
---
