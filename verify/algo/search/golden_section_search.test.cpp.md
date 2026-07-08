---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/golden_section_search.hpp
    title: Golden Section Search
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
  bundledCode: "#line 1 \"verify/algo/search/golden_section_search.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include\
    \ <cmath>\n#include <iostream>\n#include <random>\n#include <vector>\n\n#line\
    \ 1 \"algo/search/golden_section_search.hpp\"\n\n\n\n#line 5 \"algo/search/golden_section_search.hpp\"\
    \n#include <concepts>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #line 10 \"algo/search/golden_section_search.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\nnamespace detail {\n\ntemplate <std::integral Int, class F, class\
    \ Compare>\nInt integer_golden_section_search(Int left, Int right, F f, Compare\
    \ comp) {\n    assert(left < right);\n\n    using UInt = std::make_unsigned_t<Int>;\n\
    \    using Uint128 = unsigned __int128;\n    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right)\
    \ - static_cast<UInt>(left));\n\n    auto add_offset = [left](Uint128 offset)\
    \ -> Int {\n        if constexpr (std::signed_integral<Int>) {\n            if\
    \ (left < 0) {\n                const Uint128 negative_count = static_cast<Uint128>(-(left\
    \ + 1)) + 1;\n                if (offset < negative_count) {\n               \
    \     return static_cast<Int>(left + static_cast<Int>(offset));\n            \
    \    }\n                return static_cast<Int>(offset - negative_count);\n  \
    \          }\n        }\n        return static_cast<Int>(left + static_cast<Int>(offset));\n\
    \    };\n\n    using Value = std::decay_t<decltype(f(left))>;\n    struct Evaluated\
    \ {\n        Uint128 pos;\n        const Value* value;\n    };\n\n    Uint128\
    \ fib0 = 1;\n    Uint128 fib1 = 1;\n    Uint128 fib2 = 2;\n    int k = 2;\n  \
    \  while (fib2 < n) {\n        fib0 = fib1;\n        fib1 = fib2;\n        fib2\
    \ = fib0 + fib1;\n        ++k;\n    }\n\n    std::vector<std::pair<Uint128, Value>>\
    \ cache;\n    cache.reserve(static_cast<unsigned>(k) + 4);\n\n    auto find_cached\
    \ = [&](Uint128 pos) -> const Value* {\n        for (const auto& [cached_pos,\
    \ value] : cache) {\n            if (cached_pos == pos) return &value;\n     \
    \   }\n        return nullptr;\n    };\n\n    auto advance_fibonacci = [&]() {\n\
    \        const Uint128 old0 = fib0;\n        const Uint128 old1 = fib1;\n    \
    \    fib0 = old1 - old0;\n        fib1 = old0;\n        fib2 = old1;\n       \
    \ --k;\n    };\n\n    auto eval = [&](Uint128 pos) -> Evaluated {\n        if\
    \ (pos >= n) return Evaluated{pos, nullptr};\n        if (const Value* value =\
    \ find_cached(pos)) return Evaluated{pos, value};\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return Evaluated{pos, &cache.back().second};\n\
    \    };\n\n    auto get_value = [&](Uint128 pos) -> const Value& {\n        if\
    \ (const Value* value = find_cached(pos)) return *value;\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return cache.back().second;\n    };\n\n    auto\
    \ scan = [&](Uint128 scan_left, Uint128 scan_right) -> Int {\n        Int best\
    \ = add_offset(scan_left);\n        const Value* best_value = &get_value(scan_left);\n\
    \        for (Uint128 pos = scan_left + 1; pos <= scan_right; ++pos) {\n     \
    \       Int x = add_offset(pos);\n            const Value& value = get_value(pos);\n\
    \            if (comp(value, *best_value)) {\n                best = x;\n    \
    \            best_value = &value;\n            }\n        }\n        return best;\n\
    \    };\n\n    if (n <= 3) return scan(0, n - 1);\n\n    auto better = [&](const\
    \ Evaluated& a, const Evaluated& b) -> bool {\n        if ((a.value != nullptr)\
    \ != (b.value != nullptr)) return a.value != nullptr;\n        if (a.value ==\
    \ nullptr) return false;\n        return comp(*a.value, *b.value);\n    };\n\n\
    \    Uint128 left_pos = 0;\n    Uint128 right_pos = fib2 - 1;\n    Uint128 x1\
    \ = left_pos + fib0 - 1;\n    Uint128 x2 = left_pos + fib1 - 1;\n    Evaluated\
    \ y1 = eval(x1);\n    Evaluated y2 = eval(x2);\n\n    while (k > 2) {\n      \
    \  if (better(y2, y1)) {\n            left_pos = x1 + 1;\n            x1 = x2;\n\
    \            y1 = y2;\n            advance_fibonacci();\n            if (k ==\
    \ 2) break;\n            x2 = left_pos + fib1 - 1;\n            y2 = eval(x2);\n\
    \        } else {\n            right_pos = x2;\n            x2 = x1;\n       \
    \     y2 = y1;\n            advance_fibonacci();\n            if (k == 2) break;\n\
    \            x1 = left_pos + fib0 - 1;\n            y1 = eval(x1);\n        }\n\
    \    }\n\n    const Uint128 last_valid = n - 1;\n    if (right_pos > last_valid)\
    \ right_pos = last_valid;\n    assert(left_pos <= right_pos);\n    return scan(left_pos,\
    \ right_pos);\n}\n\n}  // namespace detail\n\ntemplate <std::integral Int, class\
    \ F>\nInt golden_section_search_argmin(Int left, Int right, F f) {\n    return\
    \ detail::integer_golden_section_search(left, right, f, [](const auto& a, const\
    \ auto& b) { return a < b; });\n}\n\ntemplate <std::integral Int, class F>\nInt\
    \ golden_section_search_argmax(Int left, Int right, F f) {\n    return detail::integer_golden_section_search(left,\
    \ right, f, [](const auto& a, const auto& b) { return b < a; });\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmin(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y2 < y1) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y2 < y1) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmax(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y1 < y2) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y1 < y2) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n#line 10 \"verify/algo/search/golden_section_search.test.cpp\"\
    \n\ntemplate <class F>\nint naive_argmin(int left, int right, F f) {\n    int\
    \ best = left;\n    auto best_value = f(best);\n    for (int x = left + 1; x <\
    \ right; ++x) {\n        auto value = f(x);\n        if (value < best_value) {\n\
    \            best = x;\n            best_value = value;\n        }\n    }\n  \
    \  return best;\n}\n\ntemplate <class F>\nint naive_argmax(int left, int right,\
    \ F f) {\n    int best = left;\n    auto best_value = f(best);\n    for (int x\
    \ = left + 1; x < right; ++x) {\n        auto value = f(x);\n        if (best_value\
    \ < value) {\n            best = x;\n            best_value = value;\n       \
    \ }\n    }\n    return best;\n}\n\nvoid test_integer_argmin() {\n    auto convex\
    \ = [](long long x) {\n        return (x - 7) * (x - 7) + 3;\n    };\n    assert(m1une::algo::golden_section_search_argmin<long\
    \ long>(-100, 101, convex) == 7);\n\n    auto plateau = [](int x) {\n        if\
    \ (x < 3) return 3 - x;\n        if (5 < x) return x - 5;\n        return 0;\n\
    \    };\n    assert(m1une::algo::golden_section_search_argmin<int>(-10, 10, plateau)\
    \ == 3);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n   \
    \ assert(m1une::algo::golden_section_search_argmin<int>(-7, 9, increasing) ==\
    \ -7);\n}\n\nvoid test_integer_argmax() {\n    auto concave = [](int x) {\n  \
    \      return -(x + 2) * (x + 2) + 10;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-20,\
    \ 20, concave) == -2);\n\n    auto plateau = [](int x) {\n        if (x < -4)\
    \ return x + 4;\n        if (1 < x) return 1 - x;\n        return 0;\n    };\n\
    \    assert(m1une::algo::golden_section_search_argmax<int>(-20, 20, plateau) ==\
    \ -4);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-7,\
    \ 9, increasing) == 8);\n}\n\nvoid test_random_integer_arrays() {\n    std::mt19937_64\
    \ rng(20260709);\n    for (int tc = 0; tc < 1000; ++tc) {\n        int n = static_cast<int>(rng()\
    \ % 200) + 1;\n        int low = static_cast<int>(rng() % n);\n        int high\
    \ = low + static_cast<int>(rng() % (n - low));\n\n        std::vector<long long>\
    \ min_values(n);\n        long long value = 0;\n        for (int i = low - 1;\
    \ i >= 0; --i) {\n            value += static_cast<long long>(rng() % 7) + 1;\n\
    \            min_values[i] = value;\n        }\n        value = 0;\n        for\
    \ (int i = high + 1; i < n; ++i) {\n            value += static_cast<long long>(rng()\
    \ % 7) + 1;\n            min_values[i] = value;\n        }\n\n        int base\
    \ = static_cast<int>(rng() % 1000) - 500;\n        auto min_f = [&](int x) {\n\
    \            return min_values[x - base];\n        };\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, min_f);\n        assert(xmin == naive_argmin(base, base + n, min_f));\n\
    \n        std::vector<long long> max_values(n);\n        for (int i = 0; i < n;\
    \ ++i) max_values[i] = -min_values[i];\n        auto max_f = [&](int x) {\n  \
    \          return max_values[x - base];\n        };\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, max_f);\n        assert(xmax == naive_argmax(base, base + n, max_f));\n\
    \    }\n}\n\nvoid test_integer_evaluation_reuse() {\n    for (int n = 1; n <=\
    \ 300; ++n) {\n        int base = -n / 2;\n        int center = base + n / 3;\n\
    \        auto value_at = [center](int x) {\n            return x < center ? center\
    \ - x : x - center;\n        };\n\n        std::vector<int> count(n);\n      \
    \  auto f = [&](int x) {\n            int index = x - base;\n            assert(count[index]\
    \ == 0);\n            ++count[index];\n            return value_at(x);\n     \
    \   };\n\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, f);\n        assert(xmin == naive_argmin(base, base + n, value_at));\n\
    \n        std::fill(count.begin(), count.end(), 0);\n        auto g = [&](int\
    \ x) {\n            int index = x - base;\n            assert(count[index] ==\
    \ 0);\n            ++count[index];\n            return -value_at(x);\n       \
    \ };\n        auto max_value_at = [&](int x) {\n            return -value_at(x);\n\
    \        };\n\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, g);\n        assert(xmax == naive_argmax(base, base + n, max_value_at));\n\
    \    }\n}\n\nvoid test_real_argmin() {\n    auto convex = [](double x) {\n   \
    \     return (x - 2.75) * (x - 2.75);\n    };\n    double x = m1une::algo::golden_section_search_argmin(-100.0,\
    \ 100.0, convex);\n    assert(std::abs(x - 2.75) < 1e-9);\n\n    auto increasing\
    \ = [](double x) {\n        return x;\n    };\n    double left = m1une::algo::golden_section_search_argmin(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(left + 3.0) < 1e-9);\n}\n\nvoid test_real_argmax()\
    \ {\n    auto concave = [](double x) {\n        return -(x + 0.5) * (x + 0.5);\n\
    \    };\n    double x = m1une::algo::golden_section_search_argmax(-100.0, 100.0,\
    \ concave);\n    assert(std::abs(x + 0.5) < 1e-9);\n\n    auto increasing = [](double\
    \ x) {\n        return x;\n    };\n    double right = m1une::algo::golden_section_search_argmax(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(right - 8.0) < 1e-9);\n}\n\nvoid test_evaluation_count()\
    \ {\n    int zero_iteration_calls = 0;\n    auto f0 = [&](double x) {\n      \
    \  ++zero_iteration_calls;\n        return x * x;\n    };\n    double midpoint\
    \ = m1une::algo::golden_section_search_argmin(-2.0, 4.0, f0, 0);\n    assert(midpoint\
    \ == 1.0);\n    assert(zero_iteration_calls == 0);\n\n    int calls = 0;\n   \
    \ auto f = [&](double x) {\n        ++calls;\n        return (x - 1.0) * (x -\
    \ 1.0);\n    };\n    m1une::algo::golden_section_search_argmin(-5.0, 5.0, f, 37);\n\
    \    assert(calls == 38);\n}\n\nvoid test_random_quadratics() {\n    std::mt19937_64\
    \ rng(20260708);\n    std::uniform_real_distribution<double> center_dist(-1000.0,\
    \ 1000.0);\n    std::uniform_real_distribution<double> width_dist(0.1, 1000.0);\n\
    \    std::uniform_real_distribution<double> coef_dist(0.1, 10.0);\n\n    for (int\
    \ tc = 0; tc < 1000; ++tc) {\n        double center = center_dist(rng);\n    \
    \    double left_width = width_dist(rng);\n        double right_width = width_dist(rng);\n\
    \        double coef = coef_dist(rng);\n        double left = center - left_width;\n\
    \        double right = center + right_width;\n\n        auto convex = [=](double\
    \ x) {\n            double dx = x - center;\n            return coef * dx * dx;\n\
    \        };\n        double expected_min = center;\n        double xmin = m1une::algo::golden_section_search_argmin(left,\
    \ right, convex, 120);\n        assert(std::abs(xmin - expected_min) < 1e-8);\n\
    \n        auto concave = [=](double x) {\n            double dx = x - center;\n\
    \            return -coef * dx * dx;\n        };\n        double expected_max\
    \ = center;\n        double xmax = m1une::algo::golden_section_search_argmax(left,\
    \ right, concave, 120);\n        assert(std::abs(xmax - expected_max) < 1e-8);\n\
    \    }\n}\n\nint main() {\n    test_integer_argmin();\n    test_integer_argmax();\n\
    \    test_random_integer_arrays();\n    test_integer_evaluation_reuse();\n   \
    \ test_real_argmin();\n    test_real_argmax();\n    test_evaluation_count();\n\
    \    test_random_quadratics();\n\n    long long a, b;\n    std::cin >> a >> b;\n\
    \    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cmath>\n#include <iostream>\n#include <random>\n#include <vector>\n\n\
    #include \"../../../algo/search/golden_section_search.hpp\"\n\ntemplate <class\
    \ F>\nint naive_argmin(int left, int right, F f) {\n    int best = left;\n   \
    \ auto best_value = f(best);\n    for (int x = left + 1; x < right; ++x) {\n \
    \       auto value = f(x);\n        if (value < best_value) {\n            best\
    \ = x;\n            best_value = value;\n        }\n    }\n    return best;\n\
    }\n\ntemplate <class F>\nint naive_argmax(int left, int right, F f) {\n    int\
    \ best = left;\n    auto best_value = f(best);\n    for (int x = left + 1; x <\
    \ right; ++x) {\n        auto value = f(x);\n        if (best_value < value) {\n\
    \            best = x;\n            best_value = value;\n        }\n    }\n  \
    \  return best;\n}\n\nvoid test_integer_argmin() {\n    auto convex = [](long\
    \ long x) {\n        return (x - 7) * (x - 7) + 3;\n    };\n    assert(m1une::algo::golden_section_search_argmin<long\
    \ long>(-100, 101, convex) == 7);\n\n    auto plateau = [](int x) {\n        if\
    \ (x < 3) return 3 - x;\n        if (5 < x) return x - 5;\n        return 0;\n\
    \    };\n    assert(m1une::algo::golden_section_search_argmin<int>(-10, 10, plateau)\
    \ == 3);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n   \
    \ assert(m1une::algo::golden_section_search_argmin<int>(-7, 9, increasing) ==\
    \ -7);\n}\n\nvoid test_integer_argmax() {\n    auto concave = [](int x) {\n  \
    \      return -(x + 2) * (x + 2) + 10;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-20,\
    \ 20, concave) == -2);\n\n    auto plateau = [](int x) {\n        if (x < -4)\
    \ return x + 4;\n        if (1 < x) return 1 - x;\n        return 0;\n    };\n\
    \    assert(m1une::algo::golden_section_search_argmax<int>(-20, 20, plateau) ==\
    \ -4);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-7,\
    \ 9, increasing) == 8);\n}\n\nvoid test_random_integer_arrays() {\n    std::mt19937_64\
    \ rng(20260709);\n    for (int tc = 0; tc < 1000; ++tc) {\n        int n = static_cast<int>(rng()\
    \ % 200) + 1;\n        int low = static_cast<int>(rng() % n);\n        int high\
    \ = low + static_cast<int>(rng() % (n - low));\n\n        std::vector<long long>\
    \ min_values(n);\n        long long value = 0;\n        for (int i = low - 1;\
    \ i >= 0; --i) {\n            value += static_cast<long long>(rng() % 7) + 1;\n\
    \            min_values[i] = value;\n        }\n        value = 0;\n        for\
    \ (int i = high + 1; i < n; ++i) {\n            value += static_cast<long long>(rng()\
    \ % 7) + 1;\n            min_values[i] = value;\n        }\n\n        int base\
    \ = static_cast<int>(rng() % 1000) - 500;\n        auto min_f = [&](int x) {\n\
    \            return min_values[x - base];\n        };\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, min_f);\n        assert(xmin == naive_argmin(base, base + n, min_f));\n\
    \n        std::vector<long long> max_values(n);\n        for (int i = 0; i < n;\
    \ ++i) max_values[i] = -min_values[i];\n        auto max_f = [&](int x) {\n  \
    \          return max_values[x - base];\n        };\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, max_f);\n        assert(xmax == naive_argmax(base, base + n, max_f));\n\
    \    }\n}\n\nvoid test_integer_evaluation_reuse() {\n    for (int n = 1; n <=\
    \ 300; ++n) {\n        int base = -n / 2;\n        int center = base + n / 3;\n\
    \        auto value_at = [center](int x) {\n            return x < center ? center\
    \ - x : x - center;\n        };\n\n        std::vector<int> count(n);\n      \
    \  auto f = [&](int x) {\n            int index = x - base;\n            assert(count[index]\
    \ == 0);\n            ++count[index];\n            return value_at(x);\n     \
    \   };\n\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, f);\n        assert(xmin == naive_argmin(base, base + n, value_at));\n\
    \n        std::fill(count.begin(), count.end(), 0);\n        auto g = [&](int\
    \ x) {\n            int index = x - base;\n            assert(count[index] ==\
    \ 0);\n            ++count[index];\n            return -value_at(x);\n       \
    \ };\n        auto max_value_at = [&](int x) {\n            return -value_at(x);\n\
    \        };\n\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, g);\n        assert(xmax == naive_argmax(base, base + n, max_value_at));\n\
    \    }\n}\n\nvoid test_real_argmin() {\n    auto convex = [](double x) {\n   \
    \     return (x - 2.75) * (x - 2.75);\n    };\n    double x = m1une::algo::golden_section_search_argmin(-100.0,\
    \ 100.0, convex);\n    assert(std::abs(x - 2.75) < 1e-9);\n\n    auto increasing\
    \ = [](double x) {\n        return x;\n    };\n    double left = m1une::algo::golden_section_search_argmin(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(left + 3.0) < 1e-9);\n}\n\nvoid test_real_argmax()\
    \ {\n    auto concave = [](double x) {\n        return -(x + 0.5) * (x + 0.5);\n\
    \    };\n    double x = m1une::algo::golden_section_search_argmax(-100.0, 100.0,\
    \ concave);\n    assert(std::abs(x + 0.5) < 1e-9);\n\n    auto increasing = [](double\
    \ x) {\n        return x;\n    };\n    double right = m1une::algo::golden_section_search_argmax(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(right - 8.0) < 1e-9);\n}\n\nvoid test_evaluation_count()\
    \ {\n    int zero_iteration_calls = 0;\n    auto f0 = [&](double x) {\n      \
    \  ++zero_iteration_calls;\n        return x * x;\n    };\n    double midpoint\
    \ = m1une::algo::golden_section_search_argmin(-2.0, 4.0, f0, 0);\n    assert(midpoint\
    \ == 1.0);\n    assert(zero_iteration_calls == 0);\n\n    int calls = 0;\n   \
    \ auto f = [&](double x) {\n        ++calls;\n        return (x - 1.0) * (x -\
    \ 1.0);\n    };\n    m1une::algo::golden_section_search_argmin(-5.0, 5.0, f, 37);\n\
    \    assert(calls == 38);\n}\n\nvoid test_random_quadratics() {\n    std::mt19937_64\
    \ rng(20260708);\n    std::uniform_real_distribution<double> center_dist(-1000.0,\
    \ 1000.0);\n    std::uniform_real_distribution<double> width_dist(0.1, 1000.0);\n\
    \    std::uniform_real_distribution<double> coef_dist(0.1, 10.0);\n\n    for (int\
    \ tc = 0; tc < 1000; ++tc) {\n        double center = center_dist(rng);\n    \
    \    double left_width = width_dist(rng);\n        double right_width = width_dist(rng);\n\
    \        double coef = coef_dist(rng);\n        double left = center - left_width;\n\
    \        double right = center + right_width;\n\n        auto convex = [=](double\
    \ x) {\n            double dx = x - center;\n            return coef * dx * dx;\n\
    \        };\n        double expected_min = center;\n        double xmin = m1une::algo::golden_section_search_argmin(left,\
    \ right, convex, 120);\n        assert(std::abs(xmin - expected_min) < 1e-8);\n\
    \n        auto concave = [=](double x) {\n            double dx = x - center;\n\
    \            return -coef * dx * dx;\n        };\n        double expected_max\
    \ = center;\n        double xmax = m1une::algo::golden_section_search_argmax(left,\
    \ right, concave, 120);\n        assert(std::abs(xmax - expected_max) < 1e-8);\n\
    \    }\n}\n\nint main() {\n    test_integer_argmin();\n    test_integer_argmax();\n\
    \    test_random_integer_arrays();\n    test_integer_evaluation_reuse();\n   \
    \ test_real_argmin();\n    test_real_argmax();\n    test_evaluation_count();\n\
    \    test_random_quadratics();\n\n    long long a, b;\n    std::cin >> a >> b;\n\
    \    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/search/golden_section_search.hpp
  isVerificationFile: true
  path: verify/algo/search/golden_section_search.test.cpp
  requiredBy: []
  timestamp: '2026-07-09 00:39:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/search/golden_section_search.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/search/golden_section_search.test.cpp
- /verify/verify/algo/search/golden_section_search.test.cpp.html
title: verify/algo/search/golden_section_search.test.cpp
---
