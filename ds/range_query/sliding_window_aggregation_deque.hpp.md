---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
    title: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/sliding_window_aggregation_deque.hpp\"\n\n\
    \n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 10 \"ds/range_query/sliding_window_aggregation_deque.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A deque supporting the ordered product\
    \ of all elements in amortized O(1).\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct SlidingWindowAggregationDeque {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Entry {\n        T value;\n        T product;\n    };\n\
    \n    // The back of _front is the front of the deque. _back is in deque order.\n\
    \    std::vector<Entry> _front;\n    std::vector<Entry> _back;\n\n    void rebalance(bool\
    \ need_front) {\n        assert(empty() == false);\n\n        std::vector<T> values;\n\
    \        values.reserve(size());\n        for (auto iter = _front.rbegin(); iter\
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
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_DEQUE_HPP\n#define\
    \ M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_DEQUE_HPP 1\n\n#include <cassert>\n\
    #include <cstddef>\n#include <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A deque supporting the ordered product\
    \ of all elements in amortized O(1).\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct SlidingWindowAggregationDeque {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Entry {\n        T value;\n        T product;\n    };\n\
    \n    // The back of _front is the front of the deque. _back is in deque order.\n\
    \    std::vector<Entry> _front;\n    std::vector<Entry> _back;\n\n    void rebalance(bool\
    \ need_front) {\n        assert(empty() == false);\n\n        std::vector<T> values;\n\
    \        values.reserve(size());\n        for (auto iter = _front.rbegin(); iter\
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
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_DEQUE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/range_query/sliding_window_aggregation_deque.hpp
  requiredBy: []
  timestamp: '2026-07-13 04:43:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
documentation_of: ds/range_query/sliding_window_aggregation_deque.hpp
layout: document
title: Sliding Window Aggregation Deque
---

## Overview

`SlidingWindowAggregationDeque<Monoid>` maintains a deque and the monoid product
of all its elements. It is the double-ended version of sliding window
aggregation (SWAG): elements can be inserted or removed at either end.

The deque is stored in two aggregate stacks. When one stack is empty, the
elements are split approximately in half between the stacks. This gives
amortized constant-time updates while keeping the total product available in
constant time.

`SwagDeque<Monoid>` is a shorter alias.

## Template Requirements

`Monoid` must satisfy `m1une::monoid::IsMonoid`. Its `value_type` must be
copy-constructible, and `Monoid::op(a, b)` must be associative with identity
`Monoid::id()`.

The product follows deque order:

$$
a_0 \mathbin{\mathrm{op}} a_1 \mathbin{\mathrm{op}} \cdots
\mathbin{\mathrm{op}} a_{n-1}.
$$

The monoid does not need to be commutative.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SlidingWindowAggregationDeque()` | Constructs an empty deque. | $O(1)$ |
| `SlidingWindowAggregationDeque(const std::vector<T>& values)` | Constructs a deque containing `values` in order. | $O(N)$ |
| `SlidingWindowAggregationDeque(std::vector<T>&& values)` | Constructs a deque containing `values` in order, moving the values. | $O(N)$ |
| `void push_front(T value)` | Inserts `value` at the front. | Amortized $O(1)$ |
| `void push_back(T value)` | Inserts `value` at the back. | Amortized $O(1)$ |
| `void pop_front()` | Removes the front element. | Amortized $O(1)$ |
| `void pop_back()` | Removes the back element. | Amortized $O(1)$ |
| `const T& front()` | Returns the front element. | Amortized $O(1)$ |
| `const T& back()` | Returns the back element. | Amortized $O(1)$ |
| `T prod() const`, `T all_prod() const` | Returns the ordered product, or the identity when empty. | $O(1)$ |
| `std::size_t size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the deque is empty. | $O(1)$ |
| `void clear()` | Removes every element. | $O(N)$ |
| `void reserve(std::size_t capacity)` | Reserves both internal stacks. | $O(N)$ |

`pop_front`, `pop_back`, `front`, and `back` require a nonempty deque.

## Example

This maintains a string under updates at both ends:

```cpp
#include "ds/range_query/sliding_window_aggregation_deque.hpp"

#include <iostream>
#include <string>

struct Concat {
    using value_type = std::string;

    static value_type id() {
        return "";
    }

    static value_type op(const value_type& left, const value_type& right) {
        return left + right;
    }
};

int main() {
    m1une::ds::SwagDeque<Concat> deque;
    deque.push_back("b");
    deque.push_front("a");
    deque.push_back("c");
    std::cout << deque.prod() << "\n";  // abc

    deque.pop_front();
    std::cout << deque.prod() << "\n";  // bc
}
```
