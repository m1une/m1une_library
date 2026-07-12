---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/heap/double_ended_priority_queue.test.cpp
    title: verify/ds/heap/double_ended_priority_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/heap/double_ended_priority_queue.hpp\"\n\n\n\n#include\
    \ <bit>\n#include <cassert>\n#include <cstddef>\n#include <functional>\n#include\
    \ <initializer_list>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// Min-max heap supporting access to both extremes of a\
    \ total ordering.\ntemplate <class T, class Compare = std::less<T>>\nclass DoubleEndedPriorityQueue\
    \ {\n   private:\n    std::vector<T> _values;\n    [[no_unique_address]] Compare\
    \ _compare;\n\n    static std::size_t parent(std::size_t index) {\n        return\
    \ (index - 1) / 2;\n    }\n\n    static std::size_t grandparent(std::size_t index)\
    \ {\n        return (index - 3) / 4;\n    }\n\n    static bool is_min_level(std::size_t\
    \ index) {\n        const int level = int(std::bit_width(index + 1)) - 1;\n  \
    \      return level % 2 == 0;\n    }\n\n    void bubble_up_min(std::size_t index)\
    \ {\n        while (index >= 3) {\n            const std::size_t ancestor = grandparent(index);\n\
    \            if (!_compare(_values[index], _values[ancestor])) break;\n      \
    \      std::swap(_values[index], _values[ancestor]);\n            index = ancestor;\n\
    \        }\n    }\n\n    void bubble_up_max(std::size_t index) {\n        while\
    \ (index >= 3) {\n            const std::size_t ancestor = grandparent(index);\n\
    \            if (!_compare(_values[ancestor], _values[index])) break;\n      \
    \      std::swap(_values[index], _values[ancestor]);\n            index = ancestor;\n\
    \        }\n    }\n\n    std::size_t minimum_descendant(std::size_t index) const\
    \ {\n        std::size_t result = _values.size();\n        const std::size_t first_child\
    \ = index * 2 + 1;\n        const std::size_t first_grandchild = index * 4 + 3;\n\
    \        for (std::size_t candidate = first_child;\n             candidate < _values.size()\
    \ && candidate < first_child + 2;\n             candidate++) {\n            if\
    \ (result == _values.size() ||\n                _compare(_values[candidate], _values[result]))\
    \ {\n                result = candidate;\n            }\n        }\n        for\
    \ (std::size_t candidate = first_grandchild;\n             candidate < _values.size()\
    \ && candidate < first_grandchild + 4;\n             candidate++) {\n        \
    \    if (result == _values.size() ||\n                _compare(_values[candidate],\
    \ _values[result])) {\n                result = candidate;\n            }\n  \
    \      }\n        return result;\n    }\n\n    std::size_t maximum_descendant(std::size_t\
    \ index) const {\n        std::size_t result = _values.size();\n        const\
    \ std::size_t first_child = index * 2 + 1;\n        const std::size_t first_grandchild\
    \ = index * 4 + 3;\n        for (std::size_t candidate = first_child;\n      \
    \       candidate < _values.size() && candidate < first_child + 2;\n         \
    \    candidate++) {\n            if (result == _values.size() ||\n           \
    \     _compare(_values[result], _values[candidate])) {\n                result\
    \ = candidate;\n            }\n        }\n        for (std::size_t candidate =\
    \ first_grandchild;\n             candidate < _values.size() && candidate < first_grandchild\
    \ + 4;\n             candidate++) {\n            if (result == _values.size()\
    \ ||\n                _compare(_values[result], _values[candidate])) {\n     \
    \           result = candidate;\n            }\n        }\n        return result;\n\
    \    }\n\n    void trickle_down_min(std::size_t index) {\n        while (true)\
    \ {\n            const std::size_t descendant = minimum_descendant(index);\n \
    \           if (descendant == _values.size()) return;\n            if (parent(descendant)\
    \ == index) {\n                if (_compare(_values[descendant], _values[index]))\
    \ {\n                    std::swap(_values[descendant], _values[index]);\n   \
    \             }\n                return;\n            }\n            if (!_compare(_values[descendant],\
    \ _values[index])) return;\n            std::swap(_values[descendant], _values[index]);\n\
    \            const std::size_t descendant_parent = parent(descendant);\n     \
    \       if (_compare(_values[descendant_parent], _values[descendant])) {\n   \
    \             std::swap(_values[descendant_parent], _values[descendant]);\n  \
    \          }\n            index = descendant;\n        }\n    }\n\n    void trickle_down_max(std::size_t\
    \ index) {\n        while (true) {\n            const std::size_t descendant =\
    \ maximum_descendant(index);\n            if (descendant == _values.size()) return;\n\
    \            if (parent(descendant) == index) {\n                if (_compare(_values[index],\
    \ _values[descendant])) {\n                    std::swap(_values[descendant],\
    \ _values[index]);\n                }\n                return;\n            }\n\
    \            if (!_compare(_values[index], _values[descendant])) return;\n   \
    \         std::swap(_values[descendant], _values[index]);\n            const std::size_t\
    \ descendant_parent = parent(descendant);\n            if (_compare(_values[descendant],\
    \ _values[descendant_parent])) {\n                std::swap(_values[descendant_parent],\
    \ _values[descendant]);\n            }\n            index = descendant;\n    \
    \    }\n    }\n\n    void restore_after_push(std::size_t index) {\n        if\
    \ (index == 0) return;\n        const std::size_t ancestor = parent(index);\n\
    \        if (is_min_level(index)) {\n            if (_compare(_values[ancestor],\
    \ _values[index])) {\n                std::swap(_values[ancestor], _values[index]);\n\
    \                bubble_up_max(ancestor);\n            } else {\n            \
    \    bubble_up_min(index);\n            }\n        } else {\n            if (_compare(_values[index],\
    \ _values[ancestor])) {\n                std::swap(_values[ancestor], _values[index]);\n\
    \                bubble_up_min(ancestor);\n            } else {\n            \
    \    bubble_up_max(index);\n            }\n        }\n    }\n\n    std::size_t\
    \ maximum_index() const {\n        assert(!_values.empty());\n        if (_values.size()\
    \ == 1) return 0;\n        if (_values.size() == 2 || !_compare(_values[1], _values[2]))\
    \ return 1;\n        return 2;\n    }\n\n   public:\n    DoubleEndedPriorityQueue()\
    \ = default;\n\n    explicit DoubleEndedPriorityQueue(Compare compare)\n     \
    \   : _compare(std::move(compare)) {}\n\n    DoubleEndedPriorityQueue(std::initializer_list<T>\
    \ values,\n                             Compare compare = Compare())\n       \
    \ : DoubleEndedPriorityQueue(std::move(compare)) {\n        for (const T& value\
    \ : values) push(value);\n    }\n\n    template <class Iterator>\n    DoubleEndedPriorityQueue(Iterator\
    \ first, Iterator last,\n                             Compare compare = Compare())\n\
    \        : DoubleEndedPriorityQueue(std::move(compare)) {\n        while (first\
    \ != last) {\n            push(*first);\n            ++first;\n        }\n   \
    \ }\n\n    std::size_t size() const {\n        return _values.size();\n    }\n\
    \n    bool empty() const {\n        return _values.empty();\n    }\n\n    const\
    \ T& min() const {\n        assert(!empty());\n        return _values[0];\n  \
    \  }\n\n    const T& max() const {\n        return _values[maximum_index()];\n\
    \    }\n\n    void clear() {\n        _values.clear();\n    }\n\n    template\
    \ <class... Args>\n    void emplace(Args&&... args) {\n        _values.emplace_back(std::forward<Args>(args)...);\n\
    \        restore_after_push(_values.size() - 1);\n    }\n\n    void push(const\
    \ T& value) {\n        emplace(value);\n    }\n\n    void push(T&& value) {\n\
    \        emplace(std::move(value));\n    }\n\n    void pop_min() {\n        assert(!empty());\n\
    \        if (_values.size() == 1) {\n            _values.pop_back();\n       \
    \     return;\n        }\n        _values[0] = std::move(_values.back());\n  \
    \      _values.pop_back();\n        trickle_down_min(0);\n    }\n\n    void pop_max()\
    \ {\n        assert(!empty());\n        const std::size_t index = maximum_index();\n\
    \        if (index == _values.size() - 1) {\n            _values.pop_back();\n\
    \            return;\n        }\n        _values[index] = std::move(_values.back());\n\
    \        _values.pop_back();\n        trickle_down_max(index);\n    }\n\n    const\
    \ Compare& comparator() const {\n        return _compare;\n    }\n};\n\ntemplate\
    \ <class T, class Compare = std::less<T>>\nusing MinMaxHeap = DoubleEndedPriorityQueue<T,\
    \ Compare>;\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_HEAP_DOUBLE_ENDED_PRIORITY_QUEUE_HPP\n#define M1UNE_DS_HEAP_DOUBLE_ENDED_PRIORITY_QUEUE_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <cstddef>\n#include <functional>\n\
    #include <initializer_list>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// Min-max heap supporting access to both extremes\
    \ of a total ordering.\ntemplate <class T, class Compare = std::less<T>>\nclass\
    \ DoubleEndedPriorityQueue {\n   private:\n    std::vector<T> _values;\n    [[no_unique_address]]\
    \ Compare _compare;\n\n    static std::size_t parent(std::size_t index) {\n  \
    \      return (index - 1) / 2;\n    }\n\n    static std::size_t grandparent(std::size_t\
    \ index) {\n        return (index - 3) / 4;\n    }\n\n    static bool is_min_level(std::size_t\
    \ index) {\n        const int level = int(std::bit_width(index + 1)) - 1;\n  \
    \      return level % 2 == 0;\n    }\n\n    void bubble_up_min(std::size_t index)\
    \ {\n        while (index >= 3) {\n            const std::size_t ancestor = grandparent(index);\n\
    \            if (!_compare(_values[index], _values[ancestor])) break;\n      \
    \      std::swap(_values[index], _values[ancestor]);\n            index = ancestor;\n\
    \        }\n    }\n\n    void bubble_up_max(std::size_t index) {\n        while\
    \ (index >= 3) {\n            const std::size_t ancestor = grandparent(index);\n\
    \            if (!_compare(_values[ancestor], _values[index])) break;\n      \
    \      std::swap(_values[index], _values[ancestor]);\n            index = ancestor;\n\
    \        }\n    }\n\n    std::size_t minimum_descendant(std::size_t index) const\
    \ {\n        std::size_t result = _values.size();\n        const std::size_t first_child\
    \ = index * 2 + 1;\n        const std::size_t first_grandchild = index * 4 + 3;\n\
    \        for (std::size_t candidate = first_child;\n             candidate < _values.size()\
    \ && candidate < first_child + 2;\n             candidate++) {\n            if\
    \ (result == _values.size() ||\n                _compare(_values[candidate], _values[result]))\
    \ {\n                result = candidate;\n            }\n        }\n        for\
    \ (std::size_t candidate = first_grandchild;\n             candidate < _values.size()\
    \ && candidate < first_grandchild + 4;\n             candidate++) {\n        \
    \    if (result == _values.size() ||\n                _compare(_values[candidate],\
    \ _values[result])) {\n                result = candidate;\n            }\n  \
    \      }\n        return result;\n    }\n\n    std::size_t maximum_descendant(std::size_t\
    \ index) const {\n        std::size_t result = _values.size();\n        const\
    \ std::size_t first_child = index * 2 + 1;\n        const std::size_t first_grandchild\
    \ = index * 4 + 3;\n        for (std::size_t candidate = first_child;\n      \
    \       candidate < _values.size() && candidate < first_child + 2;\n         \
    \    candidate++) {\n            if (result == _values.size() ||\n           \
    \     _compare(_values[result], _values[candidate])) {\n                result\
    \ = candidate;\n            }\n        }\n        for (std::size_t candidate =\
    \ first_grandchild;\n             candidate < _values.size() && candidate < first_grandchild\
    \ + 4;\n             candidate++) {\n            if (result == _values.size()\
    \ ||\n                _compare(_values[result], _values[candidate])) {\n     \
    \           result = candidate;\n            }\n        }\n        return result;\n\
    \    }\n\n    void trickle_down_min(std::size_t index) {\n        while (true)\
    \ {\n            const std::size_t descendant = minimum_descendant(index);\n \
    \           if (descendant == _values.size()) return;\n            if (parent(descendant)\
    \ == index) {\n                if (_compare(_values[descendant], _values[index]))\
    \ {\n                    std::swap(_values[descendant], _values[index]);\n   \
    \             }\n                return;\n            }\n            if (!_compare(_values[descendant],\
    \ _values[index])) return;\n            std::swap(_values[descendant], _values[index]);\n\
    \            const std::size_t descendant_parent = parent(descendant);\n     \
    \       if (_compare(_values[descendant_parent], _values[descendant])) {\n   \
    \             std::swap(_values[descendant_parent], _values[descendant]);\n  \
    \          }\n            index = descendant;\n        }\n    }\n\n    void trickle_down_max(std::size_t\
    \ index) {\n        while (true) {\n            const std::size_t descendant =\
    \ maximum_descendant(index);\n            if (descendant == _values.size()) return;\n\
    \            if (parent(descendant) == index) {\n                if (_compare(_values[index],\
    \ _values[descendant])) {\n                    std::swap(_values[descendant],\
    \ _values[index]);\n                }\n                return;\n            }\n\
    \            if (!_compare(_values[index], _values[descendant])) return;\n   \
    \         std::swap(_values[descendant], _values[index]);\n            const std::size_t\
    \ descendant_parent = parent(descendant);\n            if (_compare(_values[descendant],\
    \ _values[descendant_parent])) {\n                std::swap(_values[descendant_parent],\
    \ _values[descendant]);\n            }\n            index = descendant;\n    \
    \    }\n    }\n\n    void restore_after_push(std::size_t index) {\n        if\
    \ (index == 0) return;\n        const std::size_t ancestor = parent(index);\n\
    \        if (is_min_level(index)) {\n            if (_compare(_values[ancestor],\
    \ _values[index])) {\n                std::swap(_values[ancestor], _values[index]);\n\
    \                bubble_up_max(ancestor);\n            } else {\n            \
    \    bubble_up_min(index);\n            }\n        } else {\n            if (_compare(_values[index],\
    \ _values[ancestor])) {\n                std::swap(_values[ancestor], _values[index]);\n\
    \                bubble_up_min(ancestor);\n            } else {\n            \
    \    bubble_up_max(index);\n            }\n        }\n    }\n\n    std::size_t\
    \ maximum_index() const {\n        assert(!_values.empty());\n        if (_values.size()\
    \ == 1) return 0;\n        if (_values.size() == 2 || !_compare(_values[1], _values[2]))\
    \ return 1;\n        return 2;\n    }\n\n   public:\n    DoubleEndedPriorityQueue()\
    \ = default;\n\n    explicit DoubleEndedPriorityQueue(Compare compare)\n     \
    \   : _compare(std::move(compare)) {}\n\n    DoubleEndedPriorityQueue(std::initializer_list<T>\
    \ values,\n                             Compare compare = Compare())\n       \
    \ : DoubleEndedPriorityQueue(std::move(compare)) {\n        for (const T& value\
    \ : values) push(value);\n    }\n\n    template <class Iterator>\n    DoubleEndedPriorityQueue(Iterator\
    \ first, Iterator last,\n                             Compare compare = Compare())\n\
    \        : DoubleEndedPriorityQueue(std::move(compare)) {\n        while (first\
    \ != last) {\n            push(*first);\n            ++first;\n        }\n   \
    \ }\n\n    std::size_t size() const {\n        return _values.size();\n    }\n\
    \n    bool empty() const {\n        return _values.empty();\n    }\n\n    const\
    \ T& min() const {\n        assert(!empty());\n        return _values[0];\n  \
    \  }\n\n    const T& max() const {\n        return _values[maximum_index()];\n\
    \    }\n\n    void clear() {\n        _values.clear();\n    }\n\n    template\
    \ <class... Args>\n    void emplace(Args&&... args) {\n        _values.emplace_back(std::forward<Args>(args)...);\n\
    \        restore_after_push(_values.size() - 1);\n    }\n\n    void push(const\
    \ T& value) {\n        emplace(value);\n    }\n\n    void push(T&& value) {\n\
    \        emplace(std::move(value));\n    }\n\n    void pop_min() {\n        assert(!empty());\n\
    \        if (_values.size() == 1) {\n            _values.pop_back();\n       \
    \     return;\n        }\n        _values[0] = std::move(_values.back());\n  \
    \      _values.pop_back();\n        trickle_down_min(0);\n    }\n\n    void pop_max()\
    \ {\n        assert(!empty());\n        const std::size_t index = maximum_index();\n\
    \        if (index == _values.size() - 1) {\n            _values.pop_back();\n\
    \            return;\n        }\n        _values[index] = std::move(_values.back());\n\
    \        _values.pop_back();\n        trickle_down_max(index);\n    }\n\n    const\
    \ Compare& comparator() const {\n        return _compare;\n    }\n};\n\ntemplate\
    \ <class T, class Compare = std::less<T>>\nusing MinMaxHeap = DoubleEndedPriorityQueue<T,\
    \ Compare>;\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_HEAP_DOUBLE_ENDED_PRIORITY_QUEUE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/heap/double_ended_priority_queue.hpp
  requiredBy: []
  timestamp: '2026-07-13 05:54:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/heap/double_ended_priority_queue.test.cpp
documentation_of: ds/heap/double_ended_priority_queue.hpp
layout: document
title: Double-Ended Priority Queue
---

## Overview

`DoubleEndedPriorityQueue<T, Compare>` is a min-max heap stored in one
contiguous array. It inserts values and removes either extreme in logarithmic
time, while reading both extremes takes constant time.

Unlike an implementation made from two lazily synchronized heaps, this
structure stores each element once and never accumulates stale entries. It uses
$O(N)$ memory even if insertions and removals are interleaved for a long time.

`MinMaxHeap<T, Compare>` is an alias for the same type.

## Ordering

`Compare` defines the ordering and defaults to `std::less<T>`:

* `min()` returns the first element in the `Compare` ordering.
* `max()` returns the last element in the `Compare` ordering.
* Equal values are stored separately, so the structure behaves as a multiset.

With the default comparator these are the usual numeric minimum and maximum.
With `std::greater<T>`, their roles are reversed.

## Interface

```cpp
template <class T, class Compare = std::less<T>>
class DoubleEndedPriorityQueue {
public:
    DoubleEndedPriorityQueue();
    explicit DoubleEndedPriorityQueue(Compare compare);
    DoubleEndedPriorityQueue(
        std::initializer_list<T> values,
        Compare compare = Compare()
    );

    template <class Iterator>
    DoubleEndedPriorityQueue(
        Iterator first,
        Iterator last,
        Compare compare = Compare()
    );

    std::size_t size() const;
    bool empty() const;
    const T& min() const;
    const T& max() const;

    void clear();

    template <class... Args>
    void emplace(Args&&... args);

    void push(const T& value);
    void push(T&& value);
    void pop_min();
    void pop_max();

    const Compare& comparator() const;
};

template <class T, class Compare = std::less<T>>
using MinMaxHeap = DoubleEndedPriorityQueue<T, Compare>;
```

## Complexity

| Method | Description | Complexity |
| --- | --- | --- |
| Default/comparator constructor | Creates an empty queue. | $O(1)$ |
| Initializer-list/range constructor | Inserts all $N$ supplied values. | $O(N\log N)$ |
| `push(value)` | Inserts one value. | $O(\log N)$ |
| `emplace(args...)` | Constructs and inserts one value. | $O(\log N)$ |
| `min()` | Returns the minimum without removing it. | $O(1)$ |
| `max()` | Returns the maximum without removing it. | $O(1)$ |
| `pop_min()` | Removes one minimum value. | $O(\log N)$ |
| `pop_max()` | Removes one maximum value. | $O(\log N)$ |
| `size()` | Returns the number of stored values. | $O(1)$ |
| `empty()` | Returns whether the queue is empty. | $O(1)$ |
| `clear()` | Removes every value. | $O(N)$ |
| `comparator()` | Returns the comparator. | $O(1)$ |

The data structure uses $O(N)$ memory. `min`, `max`, `pop_min`, and `pop_max`
require a nonempty queue. Queries do not mutate the structure; both removal
methods do.

## Example

```cpp
#include "ds/heap/double_ended_priority_queue.hpp"

#include <iostream>

int main() {
    m1une::ds::DoubleEndedPriorityQueue<int> queue = {5, 2, 8, 2};

    std::cout << queue.min() << '\n';  // 2
    queue.pop_min();
    std::cout << queue.max() << '\n';  // 8
    queue.pop_max();

    queue.push(10);
    std::cout << queue.max() << '\n';  // 10
}
```
