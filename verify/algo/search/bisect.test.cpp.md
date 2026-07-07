---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/bisect.hpp
    title: Bisect
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
  bundledCode: "#line 1 \"verify/algo/search/bisect.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <cmath>\n\
    #include <iostream>\n\n#line 1 \"algo/search/bisect.hpp\"\n\n\n\n#include <numeric>\n\
    \nnamespace m1une {\nnamespace algo {\n\ntemplate <typename F>\nlong long first_true(long\
    \ long ng, long long ok, F pred) {\n    auto distance = [](long long a, long long\
    \ b) {\n        return a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b)\
    \ - a;\n    };\n    while (distance(ng, ok) > 1) {\n        long long mid = std::midpoint(ng,\
    \ ok);\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n  \
    \          ng = mid;\n        }\n    }\n    return ok;\n}\n\ntemplate <typename\
    \ F>\nlong long last_true(long long ok, long long ng, F pred) {\n    auto distance\
    \ = [](long long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a)\
    \ - b : static_cast<__int128_t>(b) - a;\n    };\n    while (distance(ok, ng) >\
    \ 1) {\n        long long mid = std::midpoint(ok, ng);\n        if (pred(mid))\
    \ {\n            ok = mid;\n        } else {\n            ng = mid;\n        }\n\
    \    }\n    return ok;\n}\n\ntemplate <typename F>\ndouble real_first_true(double\
    \ ng, double ok, F pred, int iterations = 80) {\n    for (int i = 0; i < iterations;\
    \ ++i) {\n        double mid = (ng + ok) / 2.0;\n        if (pred(mid)) {\n  \
    \          ok = mid;\n        } else {\n            ng = mid;\n        }\n   \
    \ }\n    return ok;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 8 \"verify/algo/search/bisect.test.cpp\"\n\nvoid test_bisect() {\n    long long\
    \ n = 100;\n    long long first = m1une::algo::first_true(0, n + 1, [&](long long\
    \ x) {\n        return x * x >= n;\n    });\n    assert(first == 10);\n\n    long\
    \ long last = m1une::algo::last_true(n + 1, 0, [&](long long x) {\n        return\
    \ x * x >= n;\n    });\n    assert(last == 10);\n\n    double root = m1une::algo::real_first_true(0.0,\
    \ 2.0, [](double x) {\n        return x * x >= 2.0;\n    });\n    assert(std::abs(root\
    \ * root - 2.0) < 1e-12);\n}\n\nint main() {\n    test_bisect();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cmath>\n#include <iostream>\n\n#include \"../../../algo/search/bisect.hpp\"\
    \n\nvoid test_bisect() {\n    long long n = 100;\n    long long first = m1une::algo::first_true(0,\
    \ n + 1, [&](long long x) {\n        return x * x >= n;\n    });\n    assert(first\
    \ == 10);\n\n    long long last = m1une::algo::last_true(n + 1, 0, [&](long long\
    \ x) {\n        return x * x >= n;\n    });\n    assert(last == 10);\n\n    double\
    \ root = m1une::algo::real_first_true(0.0, 2.0, [](double x) {\n        return\
    \ x * x >= 2.0;\n    });\n    assert(std::abs(root * root - 2.0) < 1e-12);\n}\n\
    \nint main() {\n    test_bisect();\n\n    long long a, b;\n    std::cin >> a >>\
    \ b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/search/bisect.hpp
  isVerificationFile: true
  path: verify/algo/search/bisect.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/search/bisect.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/search/bisect.test.cpp
- /verify/verify/algo/search/bisect.test.cpp.html
title: verify/algo/search/bisect.test.cpp
---
