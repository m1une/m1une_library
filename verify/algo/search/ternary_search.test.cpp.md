---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/ternary_search.hpp
    title: Ternary Search
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
  bundledCode: "#line 1 \"verify/algo/search/ternary_search.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <cmath>\n\
    #include <iostream>\n\n#line 1 \"algo/search/ternary_search.hpp\"\n\n\n\n#line\
    \ 5 \"algo/search/ternary_search.hpp\"\n#include <concepts>\n\nnamespace m1une\
    \ {\nnamespace algo {\n\ntemplate <std::integral Int, class F>\nInt ternary_search_argmin(Int\
    \ left, Int right, F f) {\n    assert(left < right);\n    while (right - left\
    \ > 3) {\n        const Int third = (right - left) / 3;\n        const Int middle_left\
    \ = left + third;\n        const Int middle_right = right - third;\n        if\
    \ (f(middle_right) < f(middle_left)) {\n            left = middle_left + 1;\n\
    \        } else {\n            right = middle_right;\n        }\n    }\n\n   \
    \ Int best = left;\n    auto best_value = f(best);\n    for (Int x = left + 1;\
    \ x < right; ++x) {\n        auto value = f(x);\n        if (value < best_value)\
    \ {\n            best = x;\n            best_value = value;\n        }\n    }\n\
    \    return best;\n}\n\ntemplate <std::integral Int, class F>\nInt ternary_search_argmax(Int\
    \ left, Int right, F f) {\n    assert(left < right);\n    while (right - left\
    \ > 3) {\n        const Int third = (right - left) / 3;\n        const Int middle_left\
    \ = left + third;\n        const Int middle_right = right - third;\n        if\
    \ (f(middle_left) < f(middle_right)) {\n            left = middle_left + 1;\n\
    \        } else {\n            right = middle_right;\n        }\n    }\n\n   \
    \ Int best = left;\n    auto best_value = f(best);\n    for (Int x = left + 1;\
    \ x < right; ++x) {\n        auto value = f(x);\n        if (best_value < value)\
    \ {\n            best = x;\n            best_value = value;\n        }\n    }\n\
    \    return best;\n}\n\ntemplate <class F>\ndouble real_ternary_search_argmin(double\
    \ left, double right, F f, int iterations = 100) {\n    assert(left <= right);\n\
    \    assert(0 <= iterations);\n    for (int i = 0; i < iterations; ++i) {\n  \
    \      const double middle_left = (left * 2.0 + right) / 3.0;\n        const double\
    \ middle_right = (left + right * 2.0) / 3.0;\n        if (f(middle_right) < f(middle_left))\
    \ {\n            left = middle_left;\n        } else {\n            right = middle_right;\n\
    \        }\n    }\n    return (left + right) / 2.0;\n}\n\ntemplate <class F>\n\
    double real_ternary_search_argmax(double left, double right, F f, int iterations\
    \ = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n    for\
    \ (int i = 0; i < iterations; ++i) {\n        const double middle_left = (left\
    \ * 2.0 + right) / 3.0;\n        const double middle_right = (left + right * 2.0)\
    \ / 3.0;\n        if (f(middle_left) < f(middle_right)) {\n            left =\
    \ middle_left;\n        } else {\n            right = middle_right;\n        }\n\
    \    }\n    return (left + right) / 2.0;\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n\n#line 8 \"verify/algo/search/ternary_search.test.cpp\"\n\nvoid test_integer_ternary_search()\
    \ {\n    auto convex = [](long long x) {\n        return (x - 7) * (x - 7) + 3;\n\
    \    };\n    assert(m1une::algo::ternary_search_argmin<long long>(-100, 101, convex)\
    \ == 7);\n\n    auto plateau = [](int x) {\n        if (x < 3) return 3 - x;\n\
    \        if (5 < x) return x - 5;\n        return 0;\n    };\n    assert(m1une::algo::ternary_search_argmin<int>(-10,\
    \ 10, plateau) == 3);\n\n    auto concave = [](int x) {\n        return -(x +\
    \ 2) * (x + 2) + 10;\n    };\n    assert(m1une::algo::ternary_search_argmax<int>(-20,\
    \ 20, concave) == -2);\n}\n\nvoid test_real_ternary_search() {\n    auto convex\
    \ = [](double x) {\n        return (x - 1.5) * (x - 1.5);\n    };\n    double\
    \ xmin = m1une::algo::real_ternary_search_argmin(-10.0, 10.0, convex);\n    assert(std::abs(xmin\
    \ - 1.5) < 1e-9);\n\n    auto concave = [](double x) {\n        return -(x + 0.25)\
    \ * (x + 0.25);\n    };\n    double xmax = m1une::algo::real_ternary_search_argmax(-10.0,\
    \ 10.0, concave);\n    assert(std::abs(xmax + 0.25) < 1e-9);\n}\n\nint main()\
    \ {\n    test_integer_ternary_search();\n    test_real_ternary_search();\n\n \
    \   long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cmath>\n#include <iostream>\n\n#include \"../../../algo/search/ternary_search.hpp\"\
    \n\nvoid test_integer_ternary_search() {\n    auto convex = [](long long x) {\n\
    \        return (x - 7) * (x - 7) + 3;\n    };\n    assert(m1une::algo::ternary_search_argmin<long\
    \ long>(-100, 101, convex) == 7);\n\n    auto plateau = [](int x) {\n        if\
    \ (x < 3) return 3 - x;\n        if (5 < x) return x - 5;\n        return 0;\n\
    \    };\n    assert(m1une::algo::ternary_search_argmin<int>(-10, 10, plateau)\
    \ == 3);\n\n    auto concave = [](int x) {\n        return -(x + 2) * (x + 2)\
    \ + 10;\n    };\n    assert(m1une::algo::ternary_search_argmax<int>(-20, 20, concave)\
    \ == -2);\n}\n\nvoid test_real_ternary_search() {\n    auto convex = [](double\
    \ x) {\n        return (x - 1.5) * (x - 1.5);\n    };\n    double xmin = m1une::algo::real_ternary_search_argmin(-10.0,\
    \ 10.0, convex);\n    assert(std::abs(xmin - 1.5) < 1e-9);\n\n    auto concave\
    \ = [](double x) {\n        return -(x + 0.25) * (x + 0.25);\n    };\n    double\
    \ xmax = m1une::algo::real_ternary_search_argmax(-10.0, 10.0, concave);\n    assert(std::abs(xmax\
    \ + 0.25) < 1e-9);\n}\n\nint main() {\n    test_integer_ternary_search();\n  \
    \  test_real_ternary_search();\n\n    long long a, b;\n    std::cin >> a >> b;\n\
    \    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/search/ternary_search.hpp
  isVerificationFile: true
  path: verify/algo/search/ternary_search.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/search/ternary_search.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/search/ternary_search.test.cpp
- /verify/verify/algo/search/ternary_search.test.cpp.html
title: verify/algo/search/ternary_search.test.cpp
---
