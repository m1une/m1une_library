---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/alien_trick.hpp
    title: Alien Trick
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
  bundledCode: "#line 1 \"verify/algo/dp_optimization/alien_trick.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"algo/dp_optimization/alien_trick.hpp\"\n\n\n\n\
    #line 5 \"algo/dp_optimization/alien_trick.hpp\"\n#include <concepts>\n#include\
    \ <numeric>\n#include <type_traits>\n#line 9 \"algo/dp_optimization/alien_trick.hpp\"\
    \n\nnamespace m1une {\nnamespace dp {\n\nnamespace detail {\n\ntemplate <std::integral\
    \ Penalty, std::integral Count, class Oracle>\nPenalty alien_trick_penalty(Penalty\
    \ lower, Penalty upper, Count target_count, Oracle& oracle) {\n    assert(lower\
    \ <= upper);\n    assert(oracle(lower).second >= target_count);\n    assert(oracle(upper).second\
    \ <= target_count);\n\n    while (lower < upper) {\n        Penalty middle = std::midpoint(lower,\
    \ upper);\n        if (middle == lower) ++middle;\n        if (oracle(middle).second\
    \ >= target_count) {\n            lower = middle;\n        } else {\n        \
    \    upper = middle - 1;\n        }\n    }\n    return lower;\n}\n\n}  // namespace\
    \ detail\n\n// Recovers the minimum value among solutions using exactly `target_count`\n\
    // items. The oracle minimizes value + penalty * count and breaks ties in favor\n\
    // of the larger count.\ntemplate <std::integral Penalty, std::integral Count,\
    \ class Oracle>\nauto alien_trick_minimize(Penalty lower, Penalty upper, Count\
    \ target_count, Oracle oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower,\
    \ upper, target_count, oracle);\n    auto result = oracle(penalty);\n    using\
    \ Value = std::remove_cvref_t<decltype(result.first)>;\n    return result.first\
    \ - static_cast<Value>(penalty) * static_cast<Value>(target_count);\n}\n\n// Recovers\
    \ the maximum value among solutions using exactly `target_count`\n// items. The\
    \ oracle maximizes value - penalty * count and breaks ties in favor\n// of the\
    \ larger count.\ntemplate <std::integral Penalty, std::integral Count, class Oracle>\n\
    auto alien_trick_maximize(Penalty lower, Penalty upper, Count target_count, Oracle\
    \ oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count,\
    \ oracle);\n    auto result = oracle(penalty);\n    using Value = std::remove_cvref_t<decltype(result.first)>;\n\
    \    return result.first + static_cast<Value>(penalty) * static_cast<Value>(target_count);\n\
    }\n\n}  // namespace dp\n}  // namespace m1une\n\n\n#line 11 \"verify/algo/dp_optimization/alien_trick.test.cpp\"\
    \n\nnamespace {\n\nvoid test_minimize() {\n    for (int test = 0; test < 200;\
    \ test++) {\n        int n = 1 + test % 30;\n        std::vector<long long> exact(n\
    \ + 1);\n        exact[0] = (test * 17) % 31 - 15;\n        long long slope =\
    \ -100 - test;\n        for (int count = 1; count <= n; count++) {\n         \
    \   slope += 1 + (test * 13 + count * 7) % 8;\n            exact[count] = exact[count\
    \ - 1] + slope;\n        }\n\n        auto oracle = [&exact](long long penalty)\
    \ {\n            std::pair<long long, int> best;\n            best.first = std::numeric_limits<long\
    \ long>::max();\n            best.second = -1;\n            for (int count = 0;\
    \ count < int(exact.size()); count++) {\n                long long value = exact[count]\
    \ + penalty * count;\n                if (value < best.first\n               \
    \     || (value == best.first && best.second < count)) {\n                   \
    \ best.first = value;\n                    best.second = count;\n            \
    \    }\n            }\n            return best;\n        };\n\n        for (int\
    \ target = 0; target <= n; target++) {\n            long long answer = m1une::dp::alien_trick_minimize(\n\
    \                -1000LL,\n                1000LL,\n                target,\n\
    \                oracle\n            );\n            assert(answer == exact[target]);\n\
    \        }\n    }\n}\n\nvoid test_maximize() {\n    for (int test = 0; test <\
    \ 200; test++) {\n        int n = 1 + test % 30;\n        std::vector<long long>\
    \ exact(n + 1);\n        exact[0] = (test * 19) % 37 - 18;\n        long long\
    \ slope = 100 + test;\n        for (int count = 1; count <= n; count++) {\n  \
    \          slope -= 1 + (test * 11 + count * 5) % 8;\n            exact[count]\
    \ = exact[count - 1] + slope;\n        }\n\n        auto oracle = [&exact](long\
    \ long penalty) {\n            std::pair<long long, int> best;\n            best.first\
    \ = std::numeric_limits<long long>::lowest();\n            best.second = -1;\n\
    \            for (int count = 0; count < int(exact.size()); count++) {\n     \
    \           long long value = exact[count] - penalty * count;\n              \
    \  if (best.first < value\n                    || (best.first == value && best.second\
    \ < count)) {\n                    best.first = value;\n                    best.second\
    \ = count;\n                }\n            }\n            return best;\n     \
    \   };\n\n        for (int target = 0; target <= n; target++) {\n            long\
    \ long answer = m1une::dp::alien_trick_maximize(\n                -1000LL,\n \
    \               1000LL,\n                target,\n                oracle\n   \
    \         );\n            assert(answer == exact[target]);\n        }\n    }\n\
    }\n\nvoid test_tie_breaking() {\n    std::vector<long long> exact = {12, 8, 4,\
    \ 0};\n    auto oracle = [&exact](int penalty) {\n        std::pair<long long,\
    \ int> best;\n        best.first = std::numeric_limits<long long>::max();\n  \
    \      best.second = -1;\n        for (int count = 0; count < int(exact.size());\
    \ count++) {\n            long long value = exact[count] + 1LL * penalty * count;\n\
    \            if (value < best.first\n                || (value == best.first &&\
    \ best.second < count)) {\n                best.first = value;\n             \
    \   best.second = count;\n            }\n        }\n        return best;\n   \
    \ };\n\n    for (int target = 0; target < int(exact.size()); target++) {\n   \
    \     assert(m1une::dp::alien_trick_minimize(\n                   -20,\n     \
    \              20,\n                   target,\n                   oracle\n  \
    \             )\n               == exact[target]);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_minimize();\n    test_maximize();\n    test_tie_breaking();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../../algo/dp_optimization/alien_trick.hpp\"\
    \n\nnamespace {\n\nvoid test_minimize() {\n    for (int test = 0; test < 200;\
    \ test++) {\n        int n = 1 + test % 30;\n        std::vector<long long> exact(n\
    \ + 1);\n        exact[0] = (test * 17) % 31 - 15;\n        long long slope =\
    \ -100 - test;\n        for (int count = 1; count <= n; count++) {\n         \
    \   slope += 1 + (test * 13 + count * 7) % 8;\n            exact[count] = exact[count\
    \ - 1] + slope;\n        }\n\n        auto oracle = [&exact](long long penalty)\
    \ {\n            std::pair<long long, int> best;\n            best.first = std::numeric_limits<long\
    \ long>::max();\n            best.second = -1;\n            for (int count = 0;\
    \ count < int(exact.size()); count++) {\n                long long value = exact[count]\
    \ + penalty * count;\n                if (value < best.first\n               \
    \     || (value == best.first && best.second < count)) {\n                   \
    \ best.first = value;\n                    best.second = count;\n            \
    \    }\n            }\n            return best;\n        };\n\n        for (int\
    \ target = 0; target <= n; target++) {\n            long long answer = m1une::dp::alien_trick_minimize(\n\
    \                -1000LL,\n                1000LL,\n                target,\n\
    \                oracle\n            );\n            assert(answer == exact[target]);\n\
    \        }\n    }\n}\n\nvoid test_maximize() {\n    for (int test = 0; test <\
    \ 200; test++) {\n        int n = 1 + test % 30;\n        std::vector<long long>\
    \ exact(n + 1);\n        exact[0] = (test * 19) % 37 - 18;\n        long long\
    \ slope = 100 + test;\n        for (int count = 1; count <= n; count++) {\n  \
    \          slope -= 1 + (test * 11 + count * 5) % 8;\n            exact[count]\
    \ = exact[count - 1] + slope;\n        }\n\n        auto oracle = [&exact](long\
    \ long penalty) {\n            std::pair<long long, int> best;\n            best.first\
    \ = std::numeric_limits<long long>::lowest();\n            best.second = -1;\n\
    \            for (int count = 0; count < int(exact.size()); count++) {\n     \
    \           long long value = exact[count] - penalty * count;\n              \
    \  if (best.first < value\n                    || (best.first == value && best.second\
    \ < count)) {\n                    best.first = value;\n                    best.second\
    \ = count;\n                }\n            }\n            return best;\n     \
    \   };\n\n        for (int target = 0; target <= n; target++) {\n            long\
    \ long answer = m1une::dp::alien_trick_maximize(\n                -1000LL,\n \
    \               1000LL,\n                target,\n                oracle\n   \
    \         );\n            assert(answer == exact[target]);\n        }\n    }\n\
    }\n\nvoid test_tie_breaking() {\n    std::vector<long long> exact = {12, 8, 4,\
    \ 0};\n    auto oracle = [&exact](int penalty) {\n        std::pair<long long,\
    \ int> best;\n        best.first = std::numeric_limits<long long>::max();\n  \
    \      best.second = -1;\n        for (int count = 0; count < int(exact.size());\
    \ count++) {\n            long long value = exact[count] + 1LL * penalty * count;\n\
    \            if (value < best.first\n                || (value == best.first &&\
    \ best.second < count)) {\n                best.first = value;\n             \
    \   best.second = count;\n            }\n        }\n        return best;\n   \
    \ };\n\n    for (int target = 0; target < int(exact.size()); target++) {\n   \
    \     assert(m1une::dp::alien_trick_minimize(\n                   -20,\n     \
    \              20,\n                   target,\n                   oracle\n  \
    \             )\n               == exact[target]);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_minimize();\n    test_maximize();\n    test_tie_breaking();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - algo/dp_optimization/alien_trick.hpp
  isVerificationFile: true
  path: verify/algo/dp_optimization/alien_trick.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 14:26:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/dp_optimization/alien_trick.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/dp_optimization/alien_trick.test.cpp
- /verify/verify/algo/dp_optimization/alien_trick.test.cpp.html
title: verify/algo/dp_optimization/alien_trick.test.cpp
---
