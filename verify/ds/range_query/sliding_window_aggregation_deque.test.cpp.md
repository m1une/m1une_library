---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sliding_window_aggregation_deque.hpp
    title: Sliding Window Aggregation Deque
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/deque_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/deque_operate_all_composite
  bundledCode: "#line 1 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#line 1 \"ds/range_query/sliding_window_aggregation_deque.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ group monoids.\n// A type satisfying this concept must also obey commutativity\
    \ and inverse laws.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 10 \"ds/range_query/sliding_window_aggregation_deque.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A deque supporting the ordered product of all elements\
    \ in amortized O(1).\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SlidingWindowAggregationDeque\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Entry\
    \ {\n        T value;\n        T product;\n    };\n\n    // The back of _front\
    \ is the front of the deque. _back is in deque order.\n    std::vector<Entry>\
    \ _front;\n    std::vector<Entry> _back;\n\n    void rebalance(bool need_front)\
    \ {\n        assert(empty() == false);\n\n        std::vector<T> values;\n   \
    \     values.reserve(size());\n        for (auto iter = _front.rbegin(); iter\
    \ != _front.rend(); ++iter) {\n            values.push_back(std::move(iter->value));\n\
    \        }\n        for (Entry& entry : _back) values.push_back(std::move(entry.value));\n\
    \n        _front.clear();\n        _back.clear();\n\n        const std::size_t\
    \ front_size = need_front ? (values.size() + 1) / 2 : values.size() / 2;\n   \
    \     for (std::size_t index = front_size; index > 0; --index) {\n           \
    \ push_front(std::move(values[index - 1]));\n        }\n        for (std::size_t\
    \ index = front_size; index < values.size(); ++index) {\n            push_back(std::move(values[index]));\n\
    \        }\n    }\n\n    void ensure_front() {\n        if (_front.empty()) rebalance(true);\n\
    \    }\n\n    void ensure_back() {\n        if (_back.empty()) rebalance(false);\n\
    \    }\n\n   public:\n    SlidingWindowAggregationDeque() = default;\n\n    explicit\
    \ SlidingWindowAggregationDeque(const std::vector<T>& values) {\n        reserve(values.size());\n\
    \        for (const T& value : values) push_back(value);\n    }\n\n    explicit\
    \ SlidingWindowAggregationDeque(std::vector<T>&& values) {\n        reserve(values.size());\n\
    \        for (T& value : values) push_back(std::move(value));\n    }\n\n    std::size_t\
    \ size() const {\n        return _front.size() + _back.size();\n    }\n\n    bool\
    \ empty() const {\n        return _front.empty() && _back.empty();\n    }\n\n\
    \    void reserve(std::size_t capacity) {\n        _front.reserve(capacity);\n\
    \        _back.reserve(capacity);\n    }\n\n    void clear() {\n        _front.clear();\n\
    \        _back.clear();\n    }\n\n    void push_front(T value) {\n        T product\
    \ = _front.empty() ? value : Monoid::op(value, _front.back().product);\n     \
    \   _front.push_back(Entry{\n            std::move(value),\n            std::move(product),\n\
    \        });\n    }\n\n    void push_back(T value) {\n        T product = _back.empty()\
    \ ? value : Monoid::op(_back.back().product, value);\n        _back.push_back(Entry{\n\
    \            std::move(value),\n            std::move(product),\n        });\n\
    \    }\n\n    void pop_front() {\n        assert(!empty());\n        ensure_front();\n\
    \        _front.pop_back();\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        ensure_back();\n        _back.pop_back();\n    }\n\n    const T& front()\
    \ {\n        assert(!empty());\n        ensure_front();\n        return _front.back().value;\n\
    \    }\n\n    const T& back() {\n        assert(!empty());\n        ensure_back();\n\
    \        return _back.back().value;\n    }\n\n    // Returns the product in deque\
    \ order, or the identity when empty.\n    T prod() const {\n        if (_front.empty())\
    \ {\n            return _back.empty() ? Monoid::id() : _back.back().product;\n\
    \        }\n        if (_back.empty()) return _front.back().product;\n       \
    \ return Monoid::op(_front.back().product, _back.back().product);\n    }\n\n \
    \   T all_prod() const {\n        return prod();\n    }\n};\n\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nusing SwagDeque = SlidingWindowAggregationDeque<Monoid>;\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n#include <cstdint>\n#include <deque>\n#include <iostream>\n#include <string>\n\
    #line 11 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\n\
    \nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n    static\
    \ value_type id() {\n        return \"\";\n    }\n\n    static value_type op(const\
    \ value_type& left, const value_type& right) {\n        return left + right;\n\
    \    }\n};\n\nconstexpr long long mod = 998244353;\n\nstruct Affine {\n    struct\
    \ value_type {\n        long long a;\n        long long b;\n    };\n\n    static\
    \ value_type id() {\n        return value_type{1, 0};\n    }\n\n    static value_type\
    \ op(const value_type& first, const value_type& second) {\n        return value_type{\n\
    \            second.a * first.a % mod,\n            (second.a * first.b + second.b)\
    \ % mod,\n        };\n    }\n};\n\nvoid test_fixed() {\n    m1une::ds::SwagDeque<Concat>\
    \ deque;\n    assert(deque.empty());\n    assert(deque.prod().empty());\n\n  \
    \  deque.reserve(10);\n    deque.push_back(\"b\");\n    deque.push_front(\"a\"\
    );\n    deque.push_back(\"c\");\n    deque.push_front(\"z\");\n    assert(deque.size()\
    \ == 4);\n    assert(deque.front() == \"z\");\n    assert(deque.back() == \"c\"\
    );\n    assert(deque.prod() == \"zabc\");\n\n    deque.pop_front();\n    deque.pop_back();\n\
    \    assert(deque.front() == \"a\");\n    assert(deque.back() == \"b\");\n   \
    \ assert(deque.all_prod() == \"ab\");\n\n    deque.clear();\n    assert(deque.empty());\n\
    \n    std::vector<std::string> values = {\"x\", \"y\", \"z\"};\n    m1une::ds::SlidingWindowAggregationDeque<Concat>\
    \ built(values);\n    assert(built.prod() == \"xyz\");\n    built.pop_back();\n\
    \    built.pop_back();\n    assert(built.front() == \"x\");\n    assert(built.back()\
    \ == \"x\");\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 904;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    m1une::ds::SwagDeque<Concat>\
    \ deque;\n    std::deque<std::string> expected;\n    for (int operation = 0; operation\
    \ < 50000; ++operation) {\n        int type = expected.empty() ? int(random()\
    \ % 2) : int(random() % 4);\n        if (type == 0) {\n            std::string\
    \ value(1, char('a' + random() % 5));\n            deque.push_front(value);\n\
    \            expected.push_front(value);\n        } else if (type == 1) {\n  \
    \          std::string value(1, char('a' + random() % 5));\n            deque.push_back(value);\n\
    \            expected.push_back(value);\n        } else if (type == 2) {\n   \
    \         deque.pop_front();\n            expected.pop_front();\n        } else\
    \ {\n            deque.pop_back();\n            expected.pop_back();\n       \
    \ }\n\n        assert(deque.size() == expected.size());\n        assert(deque.empty()\
    \ == expected.empty());\n        std::string product;\n        for (const std::string&\
    \ value : expected) product += value;\n        assert(deque.prod() == product);\n\
    \        if (!expected.empty()) {\n            assert(deque.front() == expected.front());\n\
    \            assert(deque.back() == expected.back());\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    int query_count;\n    std::cin >> query_count;\n    m1une::ds::SwagDeque<Affine>\
    \ deque;\n    while (query_count--) {\n        int type;\n        std::cin >>\
    \ type;\n        if (type == 0 || type == 1) {\n            Affine::value_type\
    \ function;\n            std::cin >> function.a >> function.b;\n            if\
    \ (type == 0) {\n                deque.push_front(function);\n            } else\
    \ {\n                deque.push_back(function);\n            }\n        } else\
    \ if (type == 2) {\n            deque.pop_front();\n        } else if (type ==\
    \ 3) {\n            deque.pop_back();\n        } else {\n            long long\
    \ x;\n            std::cin >> x;\n            auto function = deque.prod();\n\
    \            std::cout << (function.a * x + function.b) % mod << '\\n';\n    \
    \    }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#include \"../../../ds/range_query/sliding_window_aggregation_deque.hpp\"\n\
    \n#include <cassert>\n#include <cstdint>\n#include <deque>\n#include <iostream>\n\
    #include <string>\n#include <vector>\n\nnamespace {\n\nstruct Concat {\n    using\
    \ value_type = std::string;\n\n    static value_type id() {\n        return \"\
    \";\n    }\n\n    static value_type op(const value_type& left, const value_type&\
    \ right) {\n        return left + right;\n    }\n};\n\nconstexpr long long mod\
    \ = 998244353;\n\nstruct Affine {\n    struct value_type {\n        long long\
    \ a;\n        long long b;\n    };\n\n    static value_type id() {\n        return\
    \ value_type{1, 0};\n    }\n\n    static value_type op(const value_type& first,\
    \ const value_type& second) {\n        return value_type{\n            second.a\
    \ * first.a % mod,\n            (second.a * first.b + second.b) % mod,\n     \
    \   };\n    }\n};\n\nvoid test_fixed() {\n    m1une::ds::SwagDeque<Concat> deque;\n\
    \    assert(deque.empty());\n    assert(deque.prod().empty());\n\n    deque.reserve(10);\n\
    \    deque.push_back(\"b\");\n    deque.push_front(\"a\");\n    deque.push_back(\"\
    c\");\n    deque.push_front(\"z\");\n    assert(deque.size() == 4);\n    assert(deque.front()\
    \ == \"z\");\n    assert(deque.back() == \"c\");\n    assert(deque.prod() == \"\
    zabc\");\n\n    deque.pop_front();\n    deque.pop_back();\n    assert(deque.front()\
    \ == \"a\");\n    assert(deque.back() == \"b\");\n    assert(deque.all_prod()\
    \ == \"ab\");\n\n    deque.clear();\n    assert(deque.empty());\n\n    std::vector<std::string>\
    \ values = {\"x\", \"y\", \"z\"};\n    m1une::ds::SlidingWindowAggregationDeque<Concat>\
    \ built(values);\n    assert(built.prod() == \"xyz\");\n    built.pop_back();\n\
    \    built.pop_back();\n    assert(built.front() == \"x\");\n    assert(built.back()\
    \ == \"x\");\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 904;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    m1une::ds::SwagDeque<Concat>\
    \ deque;\n    std::deque<std::string> expected;\n    for (int operation = 0; operation\
    \ < 50000; ++operation) {\n        int type = expected.empty() ? int(random()\
    \ % 2) : int(random() % 4);\n        if (type == 0) {\n            std::string\
    \ value(1, char('a' + random() % 5));\n            deque.push_front(value);\n\
    \            expected.push_front(value);\n        } else if (type == 1) {\n  \
    \          std::string value(1, char('a' + random() % 5));\n            deque.push_back(value);\n\
    \            expected.push_back(value);\n        } else if (type == 2) {\n   \
    \         deque.pop_front();\n            expected.pop_front();\n        } else\
    \ {\n            deque.pop_back();\n            expected.pop_back();\n       \
    \ }\n\n        assert(deque.size() == expected.size());\n        assert(deque.empty()\
    \ == expected.empty());\n        std::string product;\n        for (const std::string&\
    \ value : expected) product += value;\n        assert(deque.prod() == product);\n\
    \        if (!expected.empty()) {\n            assert(deque.front() == expected.front());\n\
    \            assert(deque.back() == expected.back());\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    int query_count;\n    std::cin >> query_count;\n    m1une::ds::SwagDeque<Affine>\
    \ deque;\n    while (query_count--) {\n        int type;\n        std::cin >>\
    \ type;\n        if (type == 0 || type == 1) {\n            Affine::value_type\
    \ function;\n            std::cin >> function.a >> function.b;\n            if\
    \ (type == 0) {\n                deque.push_front(function);\n            } else\
    \ {\n                deque.push_back(function);\n            }\n        } else\
    \ if (type == 2) {\n            deque.pop_front();\n        } else if (type ==\
    \ 3) {\n            deque.pop_back();\n        } else {\n            long long\
    \ x;\n            std::cin >> x;\n            auto function = deque.prod();\n\
    \            std::cout << (function.a * x + function.b) % mod << '\\n';\n    \
    \    }\n    }\n}\n"
  dependsOn:
  - ds/range_query/sliding_window_aggregation_deque.hpp
  - monoid/concept.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 04:43:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
- /verify/verify/ds/range_query/sliding_window_aggregation_deque.test.cpp.html
title: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
---
