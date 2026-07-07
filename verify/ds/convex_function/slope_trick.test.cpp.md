---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/convex_function/slope_trick.hpp
    title: Slope Trick
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
  bundledCode: "#line 1 \"verify/ds/convex_function/slope_trick.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n#line 1 \"ds/convex_function/slope_trick.hpp\"\n\n\n\n#line 5 \"ds/convex_function/slope_trick.hpp\"\
    \n#include <functional>\n#include <optional>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#line 11 \"ds/convex_function/slope_trick.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct SlopeTrickArgmin {\n \
    \   std::optional<T> left;\n    std::optional<T> right;\n};\n\ntemplate <class\
    \ T>\nclass SlopeTrick {\n    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);\n\
    \n    T _minimum = T();\n    T _left_offset = T();\n    T _right_offset = T();\n\
    \    std::priority_queue<T> _left;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> _right;\n\n    T left_top() const {\n        return _left.top()\
    \ + _left_offset;\n    }\n\n    T right_top() const {\n        return _right.top()\
    \ + _right_offset;\n    }\n\n    void push_left(T value) {\n        _left.push(value\
    \ - _left_offset);\n    }\n\n    void push_right(T value) {\n        _right.push(value\
    \ - _right_offset);\n    }\n\n   public:\n    SlopeTrick() = default;\n\n    T\
    \ minimum() const {\n        return _minimum;\n    }\n\n    int breakpoint_count()\
    \ const {\n        return int(_left.size() + _right.size());\n    }\n\n    SlopeTrickArgmin<T>\
    \ argmin() const {\n        SlopeTrickArgmin<T> result;\n        if (!_left.empty())\
    \ result.left = left_top();\n        if (!_right.empty()) result.right = right_top();\n\
    \        return result;\n    }\n\n    void add_constant(T value) {\n        _minimum\
    \ += value;\n    }\n\n    void add_x_minus_a(T a) {\n        if (!_left.empty()\
    \ && left_top() > a) {\n            T old = left_top();\n            _minimum\
    \ += old - a;\n            _left.pop();\n            push_left(a);\n         \
    \   push_right(old);\n        } else {\n            push_right(a);\n        }\n\
    \    }\n\n    void add_a_minus_x(T a) {\n        if (!_right.empty() && right_top()\
    \ < a) {\n            T old = right_top();\n            _minimum += a - old;\n\
    \            _right.pop();\n            push_right(a);\n            push_left(old);\n\
    \        } else {\n            push_left(a);\n        }\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_left() {\n        _left = std::priority_queue<T>();\n    }\n\n    void\
    \ clear_right() {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n\n    void min_plus_convolve(SlopeTrick\
    \ other) {\n        SlopeTrick result;\n        result._minimum = _minimum + other._minimum;\n\
    \n        while (!_left.empty() && !other._left.empty()) {\n            result.push_left(left_top()\
    \ + other.left_top());\n            _left.pop();\n            other._left.pop();\n\
    \        }\n        while (!_right.empty() && !other._right.empty()) {\n     \
    \       result.push_right(right_top() + other.right_top());\n            _right.pop();\n\
    \            other._right.pop();\n        }\n        *this = std::move(result);\n\
    \    }\n};\n\ntemplate <class T>\nSlopeTrick<T> min_plus_convolution(SlopeTrick<T>\
    \ first,\n                                   SlopeTrick<T> second) {\n    first.min_plus_convolve(std::move(second));\n\
    \    return first;\n}\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 10 \"verify/ds/convex_function/slope_trick.test.cpp\"\n\nusing SlopeTrick =\
    \ m1une::ds::SlopeTrick<long long>;\n\nconstexpr int coordinate_limit = 300;\n\
    constexpr long long inf = std::numeric_limits<long long>::max() / 4;\n\nint index_of(int\
    \ x) {\n    return x + coordinate_limit;\n}\n\nvoid check_values(const SlopeTrick&\
    \ slope, const std::vector<long long>& value) {\n    long long expected_minimum\
    \ = *std::min_element(value.begin(), value.end());\n    assert(slope.minimum()\
    \ == expected_minimum);\n    for (int x = -100; x <= 100; x++) {\n        assert(slope.evaluate(x)\
    \ == value[index_of(x)]);\n    }\n\n    auto range = slope.argmin();\n    int\
    \ first = -coordinate_limit;\n    while (first <= coordinate_limit && value[index_of(first)]\
    \ != expected_minimum) first++;\n    int last = coordinate_limit;\n    while (last\
    \ >= -coordinate_limit && value[index_of(last)] != expected_minimum) last--;\n\
    \    if (range.left.has_value()) assert(*range.left == first);\n    if (range.right.has_value())\
    \ assert(*range.right == last);\n}\n\nvoid test_basic() {\n    SlopeTrick slope;\n\
    \    assert(slope.minimum() == 0);\n    assert(!slope.argmin().left.has_value());\n\
    \    assert(!slope.argmin().right.has_value());\n\n    slope.add_abs(3);\n   \
    \ slope.add_x_minus_a(-2);\n    slope.add_a_minus_x(7);\n    slope.add_constant(5);\n\
    \    assert(slope.minimum() == 14);\n    assert(slope.evaluate(3) == 14);\n  \
    \  auto range = slope.argmin();\n    assert(range.left == std::optional<long long>(3));\n\
    \    assert(range.right == std::optional<long long>(3));\n    assert(slope.breakpoint_count()\
    \ == 4);\n\n    SlopeTrick right_hinge;\n    right_hinge.add_x_minus_a(5);\n \
    \   assert(!right_hinge.argmin().left.has_value());\n    assert(right_hinge.argmin().right\
    \ == std::optional<long long>(5));\n\n    SlopeTrick left_hinge;\n    left_hinge.add_a_minus_x(-4);\n\
    \    assert(left_hinge.argmin().left == std::optional<long long>(-4));\n    assert(!left_hinge.argmin().right.has_value());\n\
    }\n\nvoid test_operations_against_explicit_function() {\n    for (int test = 0;\
    \ test < 80; test++) {\n        SlopeTrick slope;\n        std::vector<long long>\
    \ value(coordinate_limit * 2 + 1, 0);\n\n        for (int operation = 0; operation\
    \ < 80; operation++) {\n            int type = (test * 11 + operation * 7) % 8;\n\
    \            int a = (test * 17 + operation * 13) % 61 - 30;\n\n            if\
    \ (type == 0) {\n                long long constant = (test + operation * 3) %\
    \ 17 - 8;\n                slope.add_constant(constant);\n                for\
    \ (auto& current : value) current += constant;\n            } else if (type ==\
    \ 1) {\n                slope.add_x_minus_a(a);\n                for (int x =\
    \ -coordinate_limit; x <= coordinate_limit; x++) {\n                    value[index_of(x)]\
    \ += std::max(0, x - a);\n                }\n            } else if (type == 2)\
    \ {\n                slope.add_a_minus_x(a);\n                for (int x = -coordinate_limit;\
    \ x <= coordinate_limit; x++) {\n                    value[index_of(x)] += std::max(0,\
    \ a - x);\n                }\n            } else if (type == 3) {\n          \
    \      slope.add_abs(a);\n                for (int x = -coordinate_limit; x <=\
    \ coordinate_limit; x++) {\n                    value[index_of(x)] += std::abs(x\
    \ - a);\n                }\n            } else if (type == 4) {\n            \
    \    int delta = (test + operation) % 7 - 3;\n                slope.shift(delta);\n\
    \                std::vector<long long> next(value.size(), inf);\n           \
    \     for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n        \
    \            int source = x - delta;\n                    if (-coordinate_limit\
    \ <= source && source <= coordinate_limit) {\n                        next[index_of(x)]\
    \ = value[index_of(source)];\n                    }\n                }\n     \
    \           value.swap(next);\n            } else if (type == 5) {\n         \
    \       int left = (test + operation * 2) % 4 - 3;\n                int right\
    \ = left + 1 + (test * 3 + operation) % 4;\n                slope.shift(left,\
    \ right);\n                std::vector<long long> next(value.size(), inf);\n \
    \               for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n\
    \                    for (int y = x - right; y <= x - left; y++) {\n         \
    \               if (-coordinate_limit <= y && y <= coordinate_limit) {\n     \
    \                       next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);\n\
    \                        }\n                    }\n                }\n       \
    \         value.swap(next);\n            } else if (type == 6) {\n           \
    \     slope.prefix_minimum();\n                long long best = inf;\n       \
    \         for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n    \
    \                best = std::min(best, value[index_of(x)]);\n                \
    \    value[index_of(x)] = best;\n                }\n            } else {\n   \
    \             slope.suffix_minimum();\n                long long best = inf;\n\
    \                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {\n\
    \                    best = std::min(best, value[index_of(x)]);\n            \
    \        value[index_of(x)] = best;\n                }\n            }\n      \
    \      check_values(slope, value);\n        }\n    }\n}\n\nvoid test_merge() {\n\
    \    for (int test = 0; test < 100; test++) {\n        SlopeTrick first;\n   \
    \     SlopeTrick second;\n        for (int i = 0; i < 20; i++) {\n           \
    \ int a = (test * 7 + i * 11) % 41 - 20;\n            int b = (test * 13 + i *\
    \ 5) % 41 - 20;\n            if (i % 3 == 0) {\n                first.add_abs(a);\n\
    \                second.add_abs(b);\n            } else if (i % 3 == 1) {\n  \
    \              first.add_x_minus_a(a);\n                second.add_a_minus_x(b);\n\
    \            } else {\n                first.add_a_minus_x(a);\n             \
    \   second.add_x_minus_a(b);\n            }\n        }\n        first.add_constant(test\
    \ - 50);\n        second.add_constant(30 - test);\n        first.shift(-2, 1);\n\
    \        second.shift(3);\n        if (test % 2 == 0) first.clear_right();\n \
    \       if (test % 3 == 0) second.clear_left();\n\n        std::vector<long long>\
    \ expected(201);\n        for (int x = -100; x <= 100; x++) {\n            expected[x\
    \ + 100] = first.evaluate(x) + second.evaluate(x);\n        }\n        first.merge(second);\n\
    \        for (int x = -100; x <= 100; x++) {\n            assert(first.evaluate(x)\
    \ == expected[x + 100]);\n        }\n    }\n}\n\nvoid test_min_plus_convolution()\
    \ {\n    constexpr int brute_limit = 500;\n\n    for (int test = 0; test < 120;\
    \ test++) {\n        SlopeTrick first;\n        SlopeTrick second;\n\n       \
    \ for (int i = 0; i < 18; i++) {\n            int a = (test * 17 + i * 11) % 51\
    \ - 25;\n            int b = (test * 23 + i * 7) % 51 - 25;\n\n            if\
    \ (i % 4 == 0) {\n                first.add_abs(a);\n                second.add_abs(b);\n\
    \            } else if (i % 4 == 1) {\n                first.add_x_minus_a(a);\n\
    \                second.add_a_minus_x(b);\n            } else if (i % 4 == 2)\
    \ {\n                first.add_a_minus_x(a);\n                second.add_x_minus_a(b);\n\
    \            } else {\n                first.add_constant(a - b);\n          \
    \      second.add_constant(b - a / 2);\n            }\n\n            if (i % 7\
    \ == 3) first.shift(-2, 3);\n            if (i % 7 == 5) second.shift(1);\n  \
    \      }\n\n        if (test % 4 == 0) first.prefix_minimum();\n        if (test\
    \ % 5 == 0) first.suffix_minimum();\n        if (test % 6 == 0) second.prefix_minimum();\n\
    \        if (test % 7 == 0) second.suffix_minimum();\n\n        SlopeTrick assigned\
    \ = first;\n        assigned.min_plus_convolve(second);\n        SlopeTrick returned\
    \ = m1une::ds::min_plus_convolution(first, second);\n\n        assert(assigned.minimum()\
    \ == first.minimum() + second.minimum());\n        auto first_range = first.argmin();\n\
    \        auto second_range = second.argmin();\n        auto result_range = assigned.argmin();\n\
    \        if (first_range.left && second_range.left) {\n            assert(result_range.left);\n\
    \            assert(*result_range.left == *first_range.left + *second_range.left);\n\
    \        } else {\n            assert(!result_range.left);\n        }\n      \
    \  if (first_range.right && second_range.right) {\n            assert(result_range.right);\n\
    \            assert(*result_range.right == *first_range.right + *second_range.right);\n\
    \        } else {\n            assert(!result_range.right);\n        }\n\n   \
    \     for (int x = -100; x <= 100; x++) {\n            long long expected = inf;\n\
    \            for (int y = -brute_limit; y <= brute_limit; y++) {\n           \
    \     expected =\n                    std::min(expected, first.evaluate(y) + second.evaluate(x\
    \ - y));\n            }\n            assert(assigned.evaluate(x) == expected);\n\
    \            assert(returned.evaluate(x) == expected);\n        }\n    }\n}\n\n\
    int main() {\n    test_basic();\n    test_operations_against_explicit_function();\n\
    \    test_merge();\n    test_min_plus_convolution();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n#include \"../../../ds/convex_function/slope_trick.hpp\"\n\nusing SlopeTrick\
    \ = m1une::ds::SlopeTrick<long long>;\n\nconstexpr int coordinate_limit = 300;\n\
    constexpr long long inf = std::numeric_limits<long long>::max() / 4;\n\nint index_of(int\
    \ x) {\n    return x + coordinate_limit;\n}\n\nvoid check_values(const SlopeTrick&\
    \ slope, const std::vector<long long>& value) {\n    long long expected_minimum\
    \ = *std::min_element(value.begin(), value.end());\n    assert(slope.minimum()\
    \ == expected_minimum);\n    for (int x = -100; x <= 100; x++) {\n        assert(slope.evaluate(x)\
    \ == value[index_of(x)]);\n    }\n\n    auto range = slope.argmin();\n    int\
    \ first = -coordinate_limit;\n    while (first <= coordinate_limit && value[index_of(first)]\
    \ != expected_minimum) first++;\n    int last = coordinate_limit;\n    while (last\
    \ >= -coordinate_limit && value[index_of(last)] != expected_minimum) last--;\n\
    \    if (range.left.has_value()) assert(*range.left == first);\n    if (range.right.has_value())\
    \ assert(*range.right == last);\n}\n\nvoid test_basic() {\n    SlopeTrick slope;\n\
    \    assert(slope.minimum() == 0);\n    assert(!slope.argmin().left.has_value());\n\
    \    assert(!slope.argmin().right.has_value());\n\n    slope.add_abs(3);\n   \
    \ slope.add_x_minus_a(-2);\n    slope.add_a_minus_x(7);\n    slope.add_constant(5);\n\
    \    assert(slope.minimum() == 14);\n    assert(slope.evaluate(3) == 14);\n  \
    \  auto range = slope.argmin();\n    assert(range.left == std::optional<long long>(3));\n\
    \    assert(range.right == std::optional<long long>(3));\n    assert(slope.breakpoint_count()\
    \ == 4);\n\n    SlopeTrick right_hinge;\n    right_hinge.add_x_minus_a(5);\n \
    \   assert(!right_hinge.argmin().left.has_value());\n    assert(right_hinge.argmin().right\
    \ == std::optional<long long>(5));\n\n    SlopeTrick left_hinge;\n    left_hinge.add_a_minus_x(-4);\n\
    \    assert(left_hinge.argmin().left == std::optional<long long>(-4));\n    assert(!left_hinge.argmin().right.has_value());\n\
    }\n\nvoid test_operations_against_explicit_function() {\n    for (int test = 0;\
    \ test < 80; test++) {\n        SlopeTrick slope;\n        std::vector<long long>\
    \ value(coordinate_limit * 2 + 1, 0);\n\n        for (int operation = 0; operation\
    \ < 80; operation++) {\n            int type = (test * 11 + operation * 7) % 8;\n\
    \            int a = (test * 17 + operation * 13) % 61 - 30;\n\n            if\
    \ (type == 0) {\n                long long constant = (test + operation * 3) %\
    \ 17 - 8;\n                slope.add_constant(constant);\n                for\
    \ (auto& current : value) current += constant;\n            } else if (type ==\
    \ 1) {\n                slope.add_x_minus_a(a);\n                for (int x =\
    \ -coordinate_limit; x <= coordinate_limit; x++) {\n                    value[index_of(x)]\
    \ += std::max(0, x - a);\n                }\n            } else if (type == 2)\
    \ {\n                slope.add_a_minus_x(a);\n                for (int x = -coordinate_limit;\
    \ x <= coordinate_limit; x++) {\n                    value[index_of(x)] += std::max(0,\
    \ a - x);\n                }\n            } else if (type == 3) {\n          \
    \      slope.add_abs(a);\n                for (int x = -coordinate_limit; x <=\
    \ coordinate_limit; x++) {\n                    value[index_of(x)] += std::abs(x\
    \ - a);\n                }\n            } else if (type == 4) {\n            \
    \    int delta = (test + operation) % 7 - 3;\n                slope.shift(delta);\n\
    \                std::vector<long long> next(value.size(), inf);\n           \
    \     for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n        \
    \            int source = x - delta;\n                    if (-coordinate_limit\
    \ <= source && source <= coordinate_limit) {\n                        next[index_of(x)]\
    \ = value[index_of(source)];\n                    }\n                }\n     \
    \           value.swap(next);\n            } else if (type == 5) {\n         \
    \       int left = (test + operation * 2) % 4 - 3;\n                int right\
    \ = left + 1 + (test * 3 + operation) % 4;\n                slope.shift(left,\
    \ right);\n                std::vector<long long> next(value.size(), inf);\n \
    \               for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n\
    \                    for (int y = x - right; y <= x - left; y++) {\n         \
    \               if (-coordinate_limit <= y && y <= coordinate_limit) {\n     \
    \                       next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);\n\
    \                        }\n                    }\n                }\n       \
    \         value.swap(next);\n            } else if (type == 6) {\n           \
    \     slope.prefix_minimum();\n                long long best = inf;\n       \
    \         for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n    \
    \                best = std::min(best, value[index_of(x)]);\n                \
    \    value[index_of(x)] = best;\n                }\n            } else {\n   \
    \             slope.suffix_minimum();\n                long long best = inf;\n\
    \                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {\n\
    \                    best = std::min(best, value[index_of(x)]);\n            \
    \        value[index_of(x)] = best;\n                }\n            }\n      \
    \      check_values(slope, value);\n        }\n    }\n}\n\nvoid test_merge() {\n\
    \    for (int test = 0; test < 100; test++) {\n        SlopeTrick first;\n   \
    \     SlopeTrick second;\n        for (int i = 0; i < 20; i++) {\n           \
    \ int a = (test * 7 + i * 11) % 41 - 20;\n            int b = (test * 13 + i *\
    \ 5) % 41 - 20;\n            if (i % 3 == 0) {\n                first.add_abs(a);\n\
    \                second.add_abs(b);\n            } else if (i % 3 == 1) {\n  \
    \              first.add_x_minus_a(a);\n                second.add_a_minus_x(b);\n\
    \            } else {\n                first.add_a_minus_x(a);\n             \
    \   second.add_x_minus_a(b);\n            }\n        }\n        first.add_constant(test\
    \ - 50);\n        second.add_constant(30 - test);\n        first.shift(-2, 1);\n\
    \        second.shift(3);\n        if (test % 2 == 0) first.clear_right();\n \
    \       if (test % 3 == 0) second.clear_left();\n\n        std::vector<long long>\
    \ expected(201);\n        for (int x = -100; x <= 100; x++) {\n            expected[x\
    \ + 100] = first.evaluate(x) + second.evaluate(x);\n        }\n        first.merge(second);\n\
    \        for (int x = -100; x <= 100; x++) {\n            assert(first.evaluate(x)\
    \ == expected[x + 100]);\n        }\n    }\n}\n\nvoid test_min_plus_convolution()\
    \ {\n    constexpr int brute_limit = 500;\n\n    for (int test = 0; test < 120;\
    \ test++) {\n        SlopeTrick first;\n        SlopeTrick second;\n\n       \
    \ for (int i = 0; i < 18; i++) {\n            int a = (test * 17 + i * 11) % 51\
    \ - 25;\n            int b = (test * 23 + i * 7) % 51 - 25;\n\n            if\
    \ (i % 4 == 0) {\n                first.add_abs(a);\n                second.add_abs(b);\n\
    \            } else if (i % 4 == 1) {\n                first.add_x_minus_a(a);\n\
    \                second.add_a_minus_x(b);\n            } else if (i % 4 == 2)\
    \ {\n                first.add_a_minus_x(a);\n                second.add_x_minus_a(b);\n\
    \            } else {\n                first.add_constant(a - b);\n          \
    \      second.add_constant(b - a / 2);\n            }\n\n            if (i % 7\
    \ == 3) first.shift(-2, 3);\n            if (i % 7 == 5) second.shift(1);\n  \
    \      }\n\n        if (test % 4 == 0) first.prefix_minimum();\n        if (test\
    \ % 5 == 0) first.suffix_minimum();\n        if (test % 6 == 0) second.prefix_minimum();\n\
    \        if (test % 7 == 0) second.suffix_minimum();\n\n        SlopeTrick assigned\
    \ = first;\n        assigned.min_plus_convolve(second);\n        SlopeTrick returned\
    \ = m1une::ds::min_plus_convolution(first, second);\n\n        assert(assigned.minimum()\
    \ == first.minimum() + second.minimum());\n        auto first_range = first.argmin();\n\
    \        auto second_range = second.argmin();\n        auto result_range = assigned.argmin();\n\
    \        if (first_range.left && second_range.left) {\n            assert(result_range.left);\n\
    \            assert(*result_range.left == *first_range.left + *second_range.left);\n\
    \        } else {\n            assert(!result_range.left);\n        }\n      \
    \  if (first_range.right && second_range.right) {\n            assert(result_range.right);\n\
    \            assert(*result_range.right == *first_range.right + *second_range.right);\n\
    \        } else {\n            assert(!result_range.right);\n        }\n\n   \
    \     for (int x = -100; x <= 100; x++) {\n            long long expected = inf;\n\
    \            for (int y = -brute_limit; y <= brute_limit; y++) {\n           \
    \     expected =\n                    std::min(expected, first.evaluate(y) + second.evaluate(x\
    \ - y));\n            }\n            assert(assigned.evaluate(x) == expected);\n\
    \            assert(returned.evaluate(x) == expected);\n        }\n    }\n}\n\n\
    int main() {\n    test_basic();\n    test_operations_against_explicit_function();\n\
    \    test_merge();\n    test_min_plus_convolution();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/convex_function/slope_trick.hpp
  isVerificationFile: true
  path: verify/ds/convex_function/slope_trick.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 17:18:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/convex_function/slope_trick.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/convex_function/slope_trick.test.cpp
- /verify/verify/ds/convex_function/slope_trick.test.cpp.html
title: verify/ds/convex_function/slope_trick.test.cpp
---
