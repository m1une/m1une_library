---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/lattice_point_count.hpp
    title: Lattice-Point Count
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
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ geometry/lattice_point_count.hpp: line 28: unable to process #include in #if\
    \ / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/lattice_point_count.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include \"../../utilities/fast_io.hpp\"\n#include <limits>\n#include <vector>\n\
    \nusing Inequality = m1une::geometry::LinearInequality<long long>;\n\n__int128\
    \ count(const std::vector<Inequality>& inequalities) {\n    return m1une::geometry::count_lattice_points(inequalities);\n\
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
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_examples_and_degenerate_regions();\n    test_large_coordinates_and_floor_sum();\n\
    \    test_randomized_against_naive();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - geometry/lattice_point_count.hpp
  - utilities/bigint.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/lattice_point_count.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 20:24:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/lattice_point_count.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/lattice_point_count.test.cpp
- /verify/verify/geometry/lattice_point_count.test.cpp.html
title: verify/geometry/lattice_point_count.test.cpp
---
