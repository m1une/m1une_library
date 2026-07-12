---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/heap/double_ended_priority_queue.hpp
    title: Double-Ended Priority Queue
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/double_ended_priority_queue
    links:
    - https://judge.yosupo.jp/problem/double_ended_priority_queue
  bundledCode: "#line 1 \"verify/ds/heap/double_ended_priority_queue.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <functional>\n#include <iostream>\n\
    #include <iterator>\n#include <set>\n#include <vector>\n\n#line 1 \"ds/heap/double_ended_priority_queue.hpp\"\
    \n\n\n\n#include <bit>\n#line 6 \"ds/heap/double_ended_priority_queue.hpp\"\n\
    #include <cstddef>\n#line 8 \"ds/heap/double_ended_priority_queue.hpp\"\n#include\
    \ <initializer_list>\n#include <utility>\n#line 11 \"ds/heap/double_ended_priority_queue.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Min-max heap supporting access to\
    \ both extremes of a total ordering.\ntemplate <class T, class Compare = std::less<T>>\n\
    class DoubleEndedPriorityQueue {\n   private:\n    std::vector<T> _values;\n \
    \   [[no_unique_address]] Compare _compare;\n\n    static std::size_t parent(std::size_t\
    \ index) {\n        return (index - 1) / 2;\n    }\n\n    static std::size_t grandparent(std::size_t\
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
    \ Compare>;\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"verify/ds/heap/double_ended_priority_queue.test.cpp\"\
    \n\nnamespace {\n\nvoid test_fixed() {\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue = {3, 1, 7, 7, -2};\n    assert(queue.size() == 5);\n    assert(queue.min()\
    \ == -2);\n    assert(queue.max() == 7);\n\n    queue.pop_min();\n    assert(queue.min()\
    \ == 1);\n    queue.pop_max();\n    assert(queue.max() == 7);\n    queue.pop_max();\n\
    \    assert(queue.max() == 3);\n    queue.emplace(10);\n    assert(queue.max()\
    \ == 10);\n\n    m1une::ds::MinMaxHeap<int, std::greater<int>> reversed;\n   \
    \ reversed.push(2);\n    reversed.push(8);\n    reversed.push(5);\n    assert(reversed.min()\
    \ == 8);\n    assert(reversed.max() == 2);\n    reversed.clear();\n    assert(reversed.empty());\n\
    }\n\nvoid test_randomized() {\n    uint64_t state = 0x92d68ca2ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    m1une::ds::DoubleEndedPriorityQueue<int> queue;\n\
    \    std::multiset<int> expected;\n    for (int operation = 0; operation < 300000;\
    \ operation++) {\n        const int type = expected.size() < 1000 ? 0 : int(random()\
    \ % 3);\n        if (type == 0) {\n            const int value = int(random()\
    \ % 2001) - 1000;\n            queue.push(value);\n            expected.insert(value);\n\
    \        } else if (type == 1) {\n            assert(queue.min() == *expected.begin());\n\
    \            queue.pop_min();\n            expected.erase(expected.begin());\n\
    \        } else {\n            auto iterator = std::prev(expected.end());\n  \
    \          assert(queue.max() == *iterator);\n            queue.pop_max();\n \
    \           expected.erase(iterator);\n        }\n\n        assert(queue.size()\
    \ == expected.size());\n        assert(queue.empty() == expected.empty());\n \
    \       if (!expected.empty()) {\n            assert(queue.min() == *expected.begin());\n\
    \            assert(queue.max() == *std::prev(expected.end()));\n        }\n \
    \   }\n\n    bool remove_minimum = false;\n    while (!expected.empty()) {\n \
    \       remove_minimum = !remove_minimum;\n        if (remove_minimum) {\n   \
    \         assert(queue.min() == *expected.begin());\n            queue.pop_min();\n\
    \            expected.erase(expected.begin());\n        } else {\n           \
    \ auto iterator = std::prev(expected.end());\n            assert(queue.max() ==\
    \ *iterator);\n            queue.pop_max();\n            expected.erase(iterator);\n\
    \        }\n    }\n    assert(queue.empty());\n}\n\n}  // namespace\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ test_fixed();\n    test_randomized();\n\n    int initial_size, query_count;\n\
    \    std::cin >> initial_size >> query_count;\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue;\n    for (int i = 0; i < initial_size; i++) {\n        int value;\n \
    \       std::cin >> value;\n        queue.push(value);\n    }\n    while (query_count--)\
    \ {\n        int type;\n        std::cin >> type;\n        if (type == 0) {\n\
    \            int value;\n            std::cin >> value;\n            queue.push(value);\n\
    \        } else if (type == 1) {\n            std::cout << queue.min() << '\\\
    n';\n            queue.pop_min();\n        } else {\n            std::cout <<\
    \ queue.max() << '\\n';\n            queue.pop_max();\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <functional>\n#include <iostream>\n\
    #include <iterator>\n#include <set>\n#include <vector>\n\n#include \"../../../ds/heap/double_ended_priority_queue.hpp\"\
    \n\nnamespace {\n\nvoid test_fixed() {\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue = {3, 1, 7, 7, -2};\n    assert(queue.size() == 5);\n    assert(queue.min()\
    \ == -2);\n    assert(queue.max() == 7);\n\n    queue.pop_min();\n    assert(queue.min()\
    \ == 1);\n    queue.pop_max();\n    assert(queue.max() == 7);\n    queue.pop_max();\n\
    \    assert(queue.max() == 3);\n    queue.emplace(10);\n    assert(queue.max()\
    \ == 10);\n\n    m1une::ds::MinMaxHeap<int, std::greater<int>> reversed;\n   \
    \ reversed.push(2);\n    reversed.push(8);\n    reversed.push(5);\n    assert(reversed.min()\
    \ == 8);\n    assert(reversed.max() == 2);\n    reversed.clear();\n    assert(reversed.empty());\n\
    }\n\nvoid test_randomized() {\n    uint64_t state = 0x92d68ca2ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    m1une::ds::DoubleEndedPriorityQueue<int> queue;\n\
    \    std::multiset<int> expected;\n    for (int operation = 0; operation < 300000;\
    \ operation++) {\n        const int type = expected.size() < 1000 ? 0 : int(random()\
    \ % 3);\n        if (type == 0) {\n            const int value = int(random()\
    \ % 2001) - 1000;\n            queue.push(value);\n            expected.insert(value);\n\
    \        } else if (type == 1) {\n            assert(queue.min() == *expected.begin());\n\
    \            queue.pop_min();\n            expected.erase(expected.begin());\n\
    \        } else {\n            auto iterator = std::prev(expected.end());\n  \
    \          assert(queue.max() == *iterator);\n            queue.pop_max();\n \
    \           expected.erase(iterator);\n        }\n\n        assert(queue.size()\
    \ == expected.size());\n        assert(queue.empty() == expected.empty());\n \
    \       if (!expected.empty()) {\n            assert(queue.min() == *expected.begin());\n\
    \            assert(queue.max() == *std::prev(expected.end()));\n        }\n \
    \   }\n\n    bool remove_minimum = false;\n    while (!expected.empty()) {\n \
    \       remove_minimum = !remove_minimum;\n        if (remove_minimum) {\n   \
    \         assert(queue.min() == *expected.begin());\n            queue.pop_min();\n\
    \            expected.erase(expected.begin());\n        } else {\n           \
    \ auto iterator = std::prev(expected.end());\n            assert(queue.max() ==\
    \ *iterator);\n            queue.pop_max();\n            expected.erase(iterator);\n\
    \        }\n    }\n    assert(queue.empty());\n}\n\n}  // namespace\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ test_fixed();\n    test_randomized();\n\n    int initial_size, query_count;\n\
    \    std::cin >> initial_size >> query_count;\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue;\n    for (int i = 0; i < initial_size; i++) {\n        int value;\n \
    \       std::cin >> value;\n        queue.push(value);\n    }\n    while (query_count--)\
    \ {\n        int type;\n        std::cin >> type;\n        if (type == 0) {\n\
    \            int value;\n            std::cin >> value;\n            queue.push(value);\n\
    \        } else if (type == 1) {\n            std::cout << queue.min() << '\\\
    n';\n            queue.pop_min();\n        } else {\n            std::cout <<\
    \ queue.max() << '\\n';\n            queue.pop_max();\n        }\n    }\n}\n"
  dependsOn:
  - ds/heap/double_ended_priority_queue.hpp
  isVerificationFile: true
  path: verify/ds/heap/double_ended_priority_queue.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 05:54:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/heap/double_ended_priority_queue.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/heap/double_ended_priority_queue.test.cpp
- /verify/verify/ds/heap/double_ended_priority_queue.test.cpp.html
title: verify/ds/heap/double_ended_priority_queue.test.cpp
---
