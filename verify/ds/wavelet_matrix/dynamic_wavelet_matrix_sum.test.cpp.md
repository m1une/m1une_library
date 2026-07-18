---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
    title: Dynamic Wavelet Matrix
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
    title: Dynamic Wavelet Matrix with Sums
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\
    \n#line 1 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <bit>\n#include <cassert>\n#include\
    \ <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/wavelet_matrix/dynamic_wavelet_matrix.hpp\"\
    \n\n\n\n#line 15 \"ds/wavelet_matrix/dynamic_wavelet_matrix.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\nnamespace dynamic_wavelet_matrix_detail {\n\n// A\
    \ dynamic bit vector stored as an implicit treap of small packed chunks.\nclass\
    \ DynamicRankBitVector {\n   public:\n    struct AccessRankResult {\n        bool\
    \ value;\n        int ones_before;\n    };\n\n    struct EraseRankResult {\n \
    \       bool value;\n        int ones_before;\n    };\n\n    struct RankPair {\n\
    \        int left_ones;\n        int right_ones;\n    };\n\n   private:\n    static\
    \ constexpr int word_bits = 64;\n    static constexpr int chunk_words = 4;\n \
    \   static constexpr int chunk_capacity = word_bits * chunk_words;\n    static\
    \ constexpr int minimum_chunk_size = chunk_capacity / 2;\n\n    struct Node {\n\
    \        std::array<std::uint64_t, chunk_words> bits{};\n        std::uint32_t\
    \ priority = 0;\n        int left = 0;\n        int right = 0;\n        int subtree_size\
    \ = 0;\n        int subtree_ones = 0;\n        std::uint16_t length = 0;\n   \
    \     std::uint16_t chunk_ones = 0;\n    };\n\n    std::vector<Node> _nodes;\n\
    \    std::vector<int> _free_nodes;\n    int _root = 0;\n    std::uint32_t _random_state\
    \ = 1;\n\n    int size_of(int node) const {\n        return _nodes[node].subtree_size;\n\
    \    }\n\n    int ones_of(int node) const {\n        return _nodes[node].subtree_ones;\n\
    \    }\n\n    std::uint32_t next_priority() {\n        _random_state ^= _random_state\
    \ << 13;\n        _random_state ^= _random_state >> 17;\n        _random_state\
    \ ^= _random_state << 5;\n        if (_random_state == 0) _random_state = 1;\n\
    \        return _random_state;\n    }\n\n    void update(int node) {\n       \
    \ if (node == 0) return;\n        _nodes[node].subtree_size =\n            size_of(_nodes[node].left)\
    \ + int(_nodes[node].length) +\n            size_of(_nodes[node].right);\n   \
    \     _nodes[node].subtree_ones =\n            ones_of(_nodes[node].left) + int(_nodes[node].chunk_ones)\
    \ +\n            ones_of(_nodes[node].right);\n    }\n\n    bool local_get(int\
    \ node, int position) const {\n        return (_nodes[node].bits[position / word_bits]\
    \ >>\n                (position % word_bits)) &\n               1U;\n    }\n\n\
    \    void local_set(int node, int position, bool value) {\n        std::uint64_t\
    \ mask =\n            std::uint64_t(1) << (position % word_bits);\n        std::uint64_t&\
    \ word = _nodes[node].bits[position / word_bits];\n        if (value) {\n    \
    \        word |= mask;\n        } else {\n            word &= ~mask;\n       \
    \ }\n    }\n\n    int local_rank1(int node, int right) const {\n        int full_words\
    \ = right / word_bits;\n        int result = 0;\n        for (int word = 0; word\
    \ < full_words; word++) {\n            result += std::popcount(_nodes[node].bits[word]);\n\
    \        }\n        int remainder = right % word_bits;\n        if (remainder\
    \ != 0) {\n            result += std::popcount(\n                _nodes[node].bits[full_words]\
    \ &\n                ((std::uint64_t(1) << remainder) - 1)\n            );\n \
    \       }\n        return result;\n    }\n\n    void clear_unused_bits(int node)\
    \ {\n        int length = _nodes[node].length;\n        int word = length / word_bits;\n\
    \        int remainder = length % word_bits;\n        if (word < chunk_words)\
    \ {\n            if (remainder == 0) {\n                _nodes[node].bits[word]\
    \ = 0;\n            } else {\n                _nodes[node].bits[word] &=\n   \
    \                 (std::uint64_t(1) << remainder) - 1;\n                word++;\n\
    \            }\n            for (; word < chunk_words; word++) {\n           \
    \     _nodes[node].bits[word] = 0;\n            }\n        }\n    }\n\n    void\
    \ local_insert(int node, int position, bool value) {\n        Node& current =\
    \ _nodes[node];\n        assert(0 <= position && position <= current.length);\n\
    \        assert(current.length < chunk_capacity);\n\n        int first_word =\
    \ position / word_bits;\n        int offset = position % word_bits;\n        for\
    \ (int word = chunk_words - 1; word > first_word; word--) {\n            current.bits[word]\
    \ =\n                (current.bits[word] << 1) |\n                (current.bits[word\
    \ - 1] >> (word_bits - 1));\n        }\n        std::uint64_t lower_mask =\n \
    \           offset == 0 ? 0 : (std::uint64_t(1) << offset) - 1;\n        current.bits[first_word]\
    \ =\n            (current.bits[first_word] & lower_mask) |\n            ((current.bits[first_word]\
    \ & ~lower_mask) << 1);\n        if (value) {\n            current.bits[first_word]\
    \ |= std::uint64_t(1) << offset;\n        }\n        current.length++;\n     \
    \   current.chunk_ones += value;\n        clear_unused_bits(node);\n        update(node);\n\
    \    }\n\n    bool local_erase(int node, int position) {\n        Node& current\
    \ = _nodes[node];\n        assert(0 <= position && position < current.length);\n\
    \        bool value = local_get(node, position);\n        int first_word = position\
    \ / word_bits;\n        int offset = position % word_bits;\n        std::uint64_t\
    \ lower_mask =\n            offset == 0 ? 0 : (std::uint64_t(1) << offset) - 1;\n\
    \        std::uint64_t shifted =\n            offset == word_bits - 1\n      \
    \          ? 0\n                : (current.bits[first_word] >> (offset + 1)) <<\
    \ offset;\n        std::uint64_t carry =\n            first_word + 1 < chunk_words\n\
    \                ? (current.bits[first_word + 1] & 1U) << (word_bits - 1)\n  \
    \              : 0;\n        current.bits[first_word] =\n            (current.bits[first_word]\
    \ & lower_mask) | shifted | carry;\n        for (int word = first_word + 1; word\
    \ < chunk_words; word++) {\n            std::uint64_t next_carry =\n         \
    \       word + 1 < chunk_words\n                    ? (current.bits[word + 1]\
    \ & 1U) << (word_bits - 1)\n                    : 0;\n            current.bits[word]\
    \ = (current.bits[word] >> 1) | next_carry;\n        }\n        current.length--;\n\
    \        current.chunk_ones -= value;\n        clear_unused_bits(node);\n    \
    \    update(node);\n        return value;\n    }\n\n    int new_node() {\n   \
    \     int node;\n        if (_free_nodes.empty()) {\n            node = int(_nodes.size());\n\
    \            _nodes.emplace_back();\n        } else {\n            node = _free_nodes.back();\n\
    \            _free_nodes.pop_back();\n            _nodes[node] = Node();\n   \
    \     }\n        _nodes[node].priority = next_priority();\n        return node;\n\
    \    }\n\n    int new_node(const std::vector<std::uint8_t>& bits, int first, int\
    \ last) {\n        int node = new_node();\n        _nodes[node].length = std::uint16_t(last\
    \ - first);\n        for (int position = first; position < last; position++) {\n\
    \            if (bits[position]) {\n                local_set(node, position -\
    \ first, true);\n                _nodes[node].chunk_ones++;\n            }\n \
    \       }\n        update(node);\n        return node;\n    }\n\n    void recycle_node(int\
    \ node) {\n        assert(node != 0);\n        _nodes[node] = Node();\n      \
    \  _free_nodes.push_back(node);\n    }\n\n    int merge(int left, int right) {\n\
    \        if (left == 0 || right == 0) return left != 0 ? left : right;\n     \
    \   if (_nodes[left].priority > _nodes[right].priority) {\n            _nodes[left].right\
    \ = merge(_nodes[left].right, right);\n            update(left);\n           \
    \ return left;\n        }\n        _nodes[right].left = merge(left, _nodes[right].left);\n\
    \        update(right);\n        return right;\n    }\n\n    int rotate_right(int\
    \ tree) {\n        int result = _nodes[tree].left;\n        _nodes[tree].left\
    \ = _nodes[result].right;\n        _nodes[result].right = tree;\n        update(tree);\n\
    \        update(result);\n        return result;\n    }\n\n    int rotate_left(int\
    \ tree) {\n        int result = _nodes[tree].right;\n        _nodes[tree].right\
    \ = _nodes[result].left;\n        _nodes[result].left = tree;\n        update(tree);\n\
    \        update(result);\n        return result;\n    }\n\n    int extract_leftmost(int\
    \ tree, int& extracted) {\n        if (_nodes[tree].left == 0) {\n           \
    \ extracted = tree;\n            int result = _nodes[tree].right;\n          \
    \  _nodes[tree].right = 0;\n            update(tree);\n            return result;\n\
    \        }\n        _nodes[tree].left = extract_leftmost(_nodes[tree].left, extracted);\n\
    \        update(tree);\n        return tree;\n    }\n\n    int extract_rightmost(int\
    \ tree, int& extracted) {\n        if (_nodes[tree].right == 0) {\n          \
    \  extracted = tree;\n            int result = _nodes[tree].left;\n          \
    \  _nodes[tree].left = 0;\n            update(tree);\n            return result;\n\
    \        }\n        _nodes[tree].right = extract_rightmost(_nodes[tree].right,\
    \ extracted);\n        update(tree);\n        return tree;\n    }\n\n    void\
    \ assign_concatenation(\n        int destination,\n        int first,\n      \
    \  int second,\n        int begin,\n        int length\n    ) {\n        std::array<std::uint64_t,\
    \ chunk_words> bits{};\n        int ones = 0;\n        int first_length = _nodes[first].length;\n\
    \        for (int position = 0; position < length; position++) {\n           \
    \ int source_position = begin + position;\n            bool value = source_position\
    \ < first_length\n                             ? local_get(first, source_position)\n\
    \                             : local_get(\n                                 \
    \  second,\n                                   source_position - first_length\n\
    \                               );\n            if (value) {\n               \
    \ bits[position / word_bits] |=\n                    std::uint64_t(1) << (position\
    \ % word_bits);\n                ones++;\n            }\n        }\n        _nodes[destination].bits\
    \ = bits;\n        _nodes[destination].length = std::uint16_t(length);\n     \
    \   _nodes[destination].chunk_ones = std::uint16_t(ones);\n        update(destination);\n\
    \    }\n\n    int rebalance(int node) {\n        if (_nodes[node].length >= minimum_chunk_size)\
    \ return node;\n\n        if (_nodes[node].right != 0) {\n            int neighbor\
    \ = 0;\n            _nodes[node].right =\n                extract_leftmost(_nodes[node].right,\
    \ neighbor);\n            int total = _nodes[node].length + _nodes[neighbor].length;\n\
    \            if (total <= chunk_capacity) {\n                assign_concatenation(node,\
    \ node, neighbor, 0, total);\n                recycle_node(neighbor);\n      \
    \      } else {\n                int left_length = total / 2;\n              \
    \  std::array<std::uint8_t, chunk_capacity * 2> values{};\n                for\
    \ (int i = 0; i < _nodes[node].length; i++) {\n                    values[i] =\
    \ local_get(node, i);\n                }\n                int old_length = _nodes[node].length;\n\
    \                for (int i = 0; i < _nodes[neighbor].length; i++) {\n       \
    \             values[old_length + i] = local_get(neighbor, i);\n             \
    \   }\n                std::vector<std::uint8_t> packed(values.begin(), values.begin()\
    \ + total);\n                assign_from_values(node, packed, 0, left_length);\n\
    \                assign_from_values(neighbor, packed, left_length, total);\n \
    \               _nodes[node].right = merge(neighbor, _nodes[node].right);\n  \
    \          }\n            update(node);\n            return node;\n        }\n\
    \n        if (_nodes[node].left != 0) {\n            int neighbor = 0;\n     \
    \       _nodes[node].left =\n                extract_rightmost(_nodes[node].left,\
    \ neighbor);\n            int total = _nodes[neighbor].length + _nodes[node].length;\n\
    \            std::array<std::uint8_t, chunk_capacity * 2> values{};\n        \
    \    for (int i = 0; i < _nodes[neighbor].length; i++) {\n                values[i]\
    \ = local_get(neighbor, i);\n            }\n            int neighbor_length =\
    \ _nodes[neighbor].length;\n            for (int i = 0; i < _nodes[node].length;\
    \ i++) {\n                values[neighbor_length + i] = local_get(node, i);\n\
    \            }\n            std::vector<std::uint8_t> packed(values.begin(), values.begin()\
    \ + total);\n            if (total <= chunk_capacity) {\n                assign_from_values(node,\
    \ packed, 0, total);\n                recycle_node(neighbor);\n            } else\
    \ {\n                int left_length = total / 2;\n                assign_from_values(neighbor,\
    \ packed, 0, left_length);\n                assign_from_values(node, packed, left_length,\
    \ total);\n                _nodes[node].left = merge(_nodes[node].left, neighbor);\n\
    \            }\n            update(node);\n        }\n        return node;\n \
    \   }\n\n    void assign_from_values(\n        int node,\n        const std::vector<std::uint8_t>&\
    \ values,\n        int first,\n        int last\n    ) {\n        _nodes[node].bits.fill(0);\n\
    \        _nodes[node].length = std::uint16_t(last - first);\n        _nodes[node].chunk_ones\
    \ = 0;\n        for (int i = first; i < last; i++) {\n            if (values[i])\
    \ {\n                local_set(node, i - first, true);\n                _nodes[node].chunk_ones++;\n\
    \            }\n        }\n        update(node);\n    }\n\n    int prefix_rank1_impl(int\
    \ tree, int right) const {\n        int result = 0;\n        while (tree != 0\
    \ && right != 0) {\n            int left_size = size_of(_nodes[tree].left);\n\
    \            if (right <= left_size) {\n                tree = _nodes[tree].left;\n\
    \                continue;\n            }\n            result += ones_of(_nodes[tree].left);\n\
    \            right -= left_size;\n            int take = std::min(right, int(_nodes[tree].length));\n\
    \            result += local_rank1(tree, take);\n            right -= take;\n\
    \            if (right == 0) break;\n            tree = _nodes[tree].right;\n\
    \        }\n        return result;\n    }\n\n    RankPair rank1_pair_impl(int\
    \ tree, int left, int right) const {\n        if (left == right) {\n         \
    \   int ones = prefix_rank1_impl(tree, left);\n            return RankPair{ones,\
    \ ones};\n        }\n        if (tree == 0 || right == 0) return RankPair{0, 0};\n\
    \n        int left_size = size_of(_nodes[tree].left);\n        int chunk_end =\
    \ left_size + _nodes[tree].length;\n        if (right <= left_size) {\n      \
    \      return rank1_pair_impl(_nodes[tree].left, left, right);\n        }\n  \
    \      if (chunk_end <= left) {\n            int base =\n                ones_of(_nodes[tree].left)\
    \ + _nodes[tree].chunk_ones;\n            RankPair result = rank1_pair_impl(\n\
    \                _nodes[tree].right,\n                left - chunk_end,\n    \
    \            right - chunk_end\n            );\n            result.left_ones +=\
    \ base;\n            result.right_ones += base;\n            return result;\n\
    \        }\n\n        int left_ones;\n        if (left <= left_size) {\n     \
    \       left_ones = prefix_rank1_impl(_nodes[tree].left, left);\n        } else\
    \ {\n            left_ones = ones_of(_nodes[tree].left) +\n                  \
    \      local_rank1(tree, left - left_size);\n        }\n\n        int right_ones;\n\
    \        if (right <= chunk_end) {\n            right_ones = ones_of(_nodes[tree].left)\
    \ +\n                         local_rank1(tree, right - left_size);\n        }\
    \ else {\n            right_ones = ones_of(_nodes[tree].left) +\n            \
    \             _nodes[tree].chunk_ones +\n                         prefix_rank1_impl(\n\
    \                             _nodes[tree].right,\n                          \
    \   right - chunk_end\n                         );\n        }\n        return\
    \ RankPair{left_ones, right_ones};\n    }\n\n    int insert_impl(\n        int\
    \ tree,\n        int position,\n        bool value,\n        int& ones_before\n\
    \    ) {\n        if (tree == 0) {\n            int node = new_node();\n     \
    \       local_insert(node, 0, value);\n            return node;\n        }\n\n\
    \        int left_size = size_of(_nodes[tree].left);\n        int length = _nodes[tree].length;\n\
    \        if (position < left_size) {\n            _nodes[tree].left = insert_impl(\n\
    \                _nodes[tree].left,\n                position,\n             \
    \   value,\n                ones_before\n            );\n            update(tree);\n\
    \            if (_nodes[_nodes[tree].left].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_right(tree);\n            }\n            return\
    \ tree;\n        }\n        if (position > left_size + length) {\n           \
    \ ones_before +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = insert_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                value,\n    \
    \            ones_before\n            );\n            update(tree);\n        \
    \    if (_nodes[_nodes[tree].right].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_left(tree);\n            }\n            return\
    \ tree;\n        }\n\n        int local_position = position - left_size;\n   \
    \     ones_before += ones_of(_nodes[tree].left) +\n                       local_rank1(tree,\
    \ local_position);\n        if (length < chunk_capacity) {\n            local_insert(tree,\
    \ local_position, value);\n            return tree;\n        }\n\n        std::vector<std::uint8_t>\
    \ values(chunk_capacity);\n        for (int i = 0; i < chunk_capacity; i++) {\n\
    \            values[i] = local_get(tree, i);\n        }\n        int right_chunk\
    \ = new_node();\n        int middle = chunk_capacity / 2;\n        assign_from_values(tree,\
    \ values, 0, middle);\n        assign_from_values(right_chunk, values, middle,\
    \ chunk_capacity);\n        if (local_position <= middle) {\n            local_insert(tree,\
    \ local_position, value);\n        } else {\n            local_insert(right_chunk,\
    \ local_position - middle, value);\n        }\n\n        int old_right = _nodes[tree].right;\n\
    \        _nodes[tree].right = 0;\n        update(tree);\n        return merge(merge(tree,\
    \ right_chunk), old_right);\n    }\n\n    int erase_impl(\n        int tree,\n\
    \        int position,\n        EraseRankResult& result\n    ) {\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int length = _nodes[tree].length;\n\
    \        if (position < left_size) {\n            _nodes[tree].left = erase_impl(\n\
    \                _nodes[tree].left,\n                position,\n             \
    \   result\n            );\n            update(tree);\n            return tree;\n\
    \        }\n        if (position >= left_size + length) {\n            result.ones_before\
    \ +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = erase_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                result\n    \
    \        );\n            update(tree);\n            return tree;\n        }\n\n\
    \        int local_position = position - left_size;\n        result.ones_before\
    \ += ones_of(_nodes[tree].left) +\n                              local_rank1(tree,\
    \ local_position);\n        result.value = local_erase(tree, local_position);\n\
    \        if (_nodes[tree].length == 0) {\n            int merged = merge(_nodes[tree].left,\
    \ _nodes[tree].right);\n            recycle_node(tree);\n            return merged;\n\
    \        }\n        return rebalance(tree);\n    }\n\n    void update_subtree(int\
    \ tree) {\n        if (tree == 0) return;\n        update_subtree(_nodes[tree].left);\n\
    \        update_subtree(_nodes[tree].right);\n        update(tree);\n    }\n\n\
    \    void build(const std::vector<std::uint8_t>& bits) {\n        _nodes.clear();\n\
    \        _nodes.emplace_back();\n        _free_nodes.clear();\n        _root =\
    \ 0;\n        _nodes.reserve(bits.size() / minimum_chunk_size + 2);\n\n      \
    \  std::vector<int> stack;\n        for (int first = 0; first < int(bits.size());\
    \ first += chunk_capacity) {\n            int last = std::min(first + chunk_capacity,\
    \ int(bits.size()));\n            int node = new_node(bits, first, last);\n  \
    \          int left = 0;\n            while (!stack.empty() &&\n             \
    \      _nodes[stack.back()].priority < _nodes[node].priority) {\n            \
    \    left = stack.back();\n                stack.pop_back();\n            }\n\
    \            _nodes[node].left = left;\n            if (!stack.empty()) _nodes[stack.back()].right\
    \ = node;\n            stack.push_back(node);\n        }\n        if (!stack.empty())\
    \ _root = stack.front();\n        update_subtree(_root);\n    }\n\n   public:\n\
    \    DynamicRankBitVector() : _nodes(1) {}\n\n    explicit DynamicRankBitVector(\n\
    \        const std::vector<std::uint8_t>& bits,\n        std::uint32_t seed =\
    \ 1\n    ) : _random_state(seed == 0 ? 1 : seed) {\n        build(bits);\n   \
    \ }\n\n    int size() const {\n        return size_of(_root);\n    }\n\n    bool\
    \ get(int position) const {\n        return access_with_rank(position).value;\n\
    \    }\n\n    AccessRankResult access_with_rank(int position) const {\n      \
    \  assert(0 <= position && position < size());\n        int ones_before = 0;\n\
    \        int tree = _root;\n        while (tree != 0) {\n            int left_size\
    \ = size_of(_nodes[tree].left);\n            if (position < left_size) {\n   \
    \             tree = _nodes[tree].left;\n            } else if (position < left_size\
    \ + _nodes[tree].length) {\n                int local_position = position - left_size;\n\
    \                ones_before += ones_of(_nodes[tree].left) +\n               \
    \                local_rank1(tree, local_position);\n                return AccessRankResult{\n\
    \                    local_get(tree, local_position),\n                    ones_before\n\
    \                };\n            } else {\n                ones_before +=\n  \
    \                  ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n   \
    \             position -= left_size + _nodes[tree].length;\n                tree\
    \ = _nodes[tree].right;\n            }\n        }\n        assert(false);\n  \
    \      return AccessRankResult{false, 0};\n    }\n\n    int rank1(int right) const\
    \ {\n        assert(0 <= right && right <= size());\n        return prefix_rank1_impl(_root,\
    \ right);\n    }\n\n    RankPair rank1_pair(int left, int right) const {\n   \
    \     assert(0 <= left && left <= right && right <= size());\n        return rank1_pair_impl(_root,\
    \ left, right);\n    }\n\n    void insert(int position, bool value) {\n      \
    \  insert_with_rank(position, value);\n    }\n\n    int insert_with_rank(int position,\
    \ bool value) {\n        assert(0 <= position && position <= size());\n      \
    \  int ones_before = 0;\n        _root = insert_impl(_root, position, value, ones_before);\n\
    \        return ones_before;\n    }\n\n    bool erase(int position) {\n      \
    \  return erase_with_rank(position).value;\n    }\n\n    EraseRankResult erase_with_rank(int\
    \ position) {\n        assert(0 <= position && position < size());\n        EraseRankResult\
    \ result{false, 0};\n        _root = erase_impl(_root, position, result);\n  \
    \      return result;\n    }\n};\n\n}  // namespace dynamic_wavelet_matrix_detail\n\
    \n// A dynamic wavelet matrix for integral sequences.\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nclass DynamicWaveletMatrix\
    \ {\n   public:\n    using value_type = T;\n    using unsigned_type = std::make_unsigned_t<T>;\n\
    \n   private:\n    static constexpr int bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (bit_width - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    int _size =\
    \ 0;\n    std::vector<dynamic_wavelet_matrix_detail::DynamicRankBitVector> _matrix;\n\
    \    std::array<int, bit_width> _zero_count{};\n\n    static unsigned_type encode(T\
    \ value) {\n        unsigned_type bits;\n        if constexpr (std::signed_integral<T>)\
    \ {\n            bits = std::bit_cast<unsigned_type>(value);\n        } else {\n\
    \            bits = value;\n        }\n        return bits ^ sign_mask;\n    }\n\
    \n    static T decode(unsigned_type key) {\n        unsigned_type bits = key ^\
    \ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n            return\
    \ std::bit_cast<T>(bits);\n        } else {\n            return bits;\n      \
    \  }\n    }\n\n    static bool bit(unsigned_type key, int level) {\n        return\
    \ (key >> (bit_width - 1 - level)) & unsigned_type(1);\n    }\n\n    void insert_encoded(int\
    \ position, unsigned_type key) {\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            if (bit(key, level)) {\n                int ones_before\
    \ =\n                    _matrix[level].insert_with_rank(position, true);\n  \
    \              int next_position = _zero_count[level] + ones_before;\n       \
    \         position = next_position;\n            } else {\n                int\
    \ ones_before =\n                    _matrix[level].insert_with_rank(position,\
    \ false);\n                int next_position = position - ones_before;\n     \
    \           _zero_count[level]++;\n                position = next_position;\n\
    \            }\n        }\n        _size++;\n    }\n\n    void erase_encoded(int\
    \ position) {\n        for (int level = 0; level < bit_width; level++) {\n   \
    \         auto erased = _matrix[level].erase_with_rank(position);\n          \
    \  int next_position;\n            if (erased.value) {\n                next_position\
    \ = _zero_count[level] + erased.ones_before;\n            } else {\n         \
    \       next_position = position - erased.ones_before;\n                _zero_count[level]--;\n\
    \            }\n            position = next_position;\n        }\n        _size--;\n\
    \    }\n\n    int count_less_encoded(int left, int right, unsigned_type upper)\
    \ const {\n        int result = 0;\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            auto ranks = _matrix[level].rank1_pair(left, right);\n\
    \            int left_ones = ranks.left_ones;\n            int right_ones = ranks.right_ones;\n\
    \            if (bit(upper, level)) {\n                result += (right - left)\
    \ - (right_ones - left_ones);\n                left = _zero_count[level] + left_ones;\n\
    \                right = _zero_count[level] + right_ones;\n            } else\
    \ {\n                left -= left_ones;\n                right -= right_ones;\n\
    \            }\n        }\n        return result;\n    }\n\n   public:\n    DynamicWaveletMatrix()\
    \ : _matrix(bit_width) {}\n\n    explicit DynamicWaveletMatrix(const std::vector<T>&\
    \ values)\n        : _size(int(values.size())) {\n        std::vector<unsigned_type>\
    \ current(_size);\n        std::vector<unsigned_type> next(_size);\n        for\
    \ (int i = 0; i < _size; i++) current[i] = encode(values[i]);\n\n        _matrix.reserve(bit_width);\n\
    \        for (int level = 0; level < bit_width; level++) {\n            std::vector<std::uint8_t>\
    \ bits(_size);\n            int zeros = 0;\n            for (int i = 0; i < _size;\
    \ i++) {\n                bits[i] = bit(current[i], level);\n                zeros\
    \ += !bits[i];\n            }\n            _zero_count[level] = zeros;\n     \
    \       int zero_position = 0;\n            int one_position = zeros;\n      \
    \      for (int i = 0; i < _size; i++) {\n                if (bits[i]) {\n   \
    \                 next[one_position++] = current[i];\n                } else {\n\
    \                    next[zero_position++] = current[i];\n                }\n\
    \            }\n            _matrix.emplace_back(\n                bits,\n   \
    \             std::uint32_t(0x9e3779b9U + level * 0x85ebca6bU)\n            );\n\
    \            current.swap(next);\n        }\n    }\n\n    int size() const {\n\
    \        return _size;\n    }\n\n    bool empty() const {\n        return _size\
    \ == 0;\n    }\n\n    void clear() {\n        *this = DynamicWaveletMatrix();\n\
    \    }\n\n    T access(int position) const {\n        assert(0 <= position &&\
    \ position < _size);\n        unsigned_type key = 0;\n        for (int level =\
    \ 0; level < bit_width; level++) {\n            auto accessed = _matrix[level].access_with_rank(position);\n\
    \            if (accessed.value) {\n                key |= unsigned_type(1) <<\
    \ (bit_width - 1 - level);\n                position = _zero_count[level] + accessed.ones_before;\n\
    \            } else {\n                position -= accessed.ones_before;\n   \
    \         }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ position) const {\n        return access(position);\n    }\n\n    void insert(int\
    \ position, T value) {\n        assert(0 <= position && position <= _size);\n\
    \        insert_encoded(position, encode(value));\n    }\n\n    void push_back(T\
    \ value) {\n        insert(_size, value);\n    }\n\n    T erase(int position)\
    \ {\n        assert(0 <= position && position < _size);\n        T value = access(position);\n\
    \        erase_encoded(position);\n        return value;\n    }\n\n    void set(int\
    \ position, T value) {\n        assert(0 <= position && position < _size);\n \
    \       if (access(position) == value) return;\n        erase_encoded(position);\n\
    \        insert_encoded(position, encode(value));\n    }\n\n    int rank(T value,\
    \ int right) const {\n        assert(0 <= right && right <= _size);\n        return\
    \ rank(value, 0, right);\n    }\n\n    int rank(T value, int left, int right)\
    \ const {\n        assert(0 <= left && left <= right && right <= _size);\n   \
    \     unsigned_type key = encode(value);\n        for (int level = 0; level <\
    \ bit_width; level++) {\n            auto ranks = _matrix[level].rank1_pair(left,\
    \ right);\n            int left_ones = ranks.left_ones;\n            int right_ones\
    \ = ranks.right_ones;\n            if (bit(key, level)) {\n                left\
    \ = _zero_count[level] + left_ones;\n                right = _zero_count[level]\
    \ + right_ones;\n            } else {\n                left -= left_ones;\n  \
    \              right -= right_ones;\n            }\n        }\n        return\
    \ right - left;\n    }\n\n    T kth_smallest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        unsigned_type key = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            auto ranks = _matrix[level].rank1_pair(left,\
    \ right);\n            int left_ones = ranks.left_ones;\n            int right_ones\
    \ = ranks.right_ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            if (k < zeros) {\n                left = left_zeros;\n\
    \                right = right_zeros;\n            } else {\n                k\
    \ -= zeros;\n                key |= unsigned_type(1) << (bit_width - 1 - level);\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            }\n        }\n        return\
    \ decode(key);\n    }\n\n    T kth_largest(int left, int right, int k) const {\n\
    \        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        return kth_smallest(left, right, right -\
    \ left - 1 - k);\n    }\n\n    int range_freq(int left, int right, T upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        return\
    \ count_less_encoded(left, right, encode(upper));\n    }\n\n    int range_freq(int\
    \ left, int right, T lower, T upper) const {\n        assert(0 <= left && left\
    \ <= right && right <= _size);\n        if (upper <= lower) return 0;\n      \
    \  return range_freq(left, right, upper) -\n               range_freq(left, right,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int left, int right, T upper)\
    \ const {\n        assert(0 <= left && left <= right && right <= _size);\n   \
    \     int count = range_freq(left, right, upper);\n        if (count == 0) return\
    \ std::nullopt;\n        return kth_smallest(left, right, count - 1);\n    }\n\
    \n    std::optional<T> next_value(int left, int right, T lower) const {\n    \
    \    assert(0 <= left && left <= right && right <= _size);\n        int count\
    \ = range_freq(left, right, lower);\n        if (count == right - left) return\
    \ std::nullopt;\n        return kth_smallest(left, right, count);\n    }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 17 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nnamespace dynamic_wavelet_matrix_sum_detail\
    \ {\n\n#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE\nstruct DynamicWaveletMatrixSumProfile\
    \ {\n    std::uint64_t bitvector_tree_traversals = 0;\n    std::uint64_t weight_tree_traversals\
    \ = 0;\n    std::uint64_t chunk_splits = 0;\n    std::uint64_t chunk_merges =\
    \ 0;\n    std::uint64_t local_element_moves = 0;\n    std::uint64_t full_chunk_rebuilds\
    \ = 0;\n};\n\ninline DynamicWaveletMatrixSumProfile profile;\n\ninline void reset_profile()\
    \ {\n    profile = DynamicWaveletMatrixSumProfile();\n}\n\ninline DynamicWaveletMatrixSumProfile\
    \ get_profile() {\n    return profile;\n}\n\n#define M1UNE_DWM_SUM_PROFILE_ADD(field,\
    \ amount) \\\n    (::m1une::ds::dynamic_wavelet_matrix_sum_detail::profile.field\
    \ += \\\n     (amount))\n#else\n#define M1UNE_DWM_SUM_PROFILE_ADD(field, amount)\
    \ ((void)0)\n#endif\n\n#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_CHUNK_CAPACITY\n\
    inline constexpr int configured_chunk_capacity =\n    M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_CHUNK_CAPACITY;\n\
    #else\ninline constexpr int configured_chunk_capacity = 64;\n#endif\n\n#ifdef\
    \ M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_GROUP_SIZE\ninline constexpr int configured_group_size\
    \ =\n    M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_GROUP_SIZE;\n#else\ninline constexpr\
    \ int configured_group_size = 16;\n#endif\n\n// A chunked implicit treap storing\
    \ routing bits and additive weights together.\ntemplate <\n    typename Sum,\n\
    \    int ChunkCapacity = configured_chunk_capacity,\n    int GroupSize = configured_group_size\n\
    >\nclass DynamicWeightedRankSequence {\n   public:\n    struct AccessRankResult\
    \ {\n        bool bit;\n        Sum weight;\n        int ones_before;\n    };\n\
    \n    struct EraseRankResult {\n        bool bit;\n        Sum weight;\n     \
    \   int ones_before;\n    };\n\n    struct PrefixStats {\n        int ones = 0;\n\
    \        Sum total_sum{};\n        Sum zero_sum{};\n    };\n\n    struct PrefixStatsPair\
    \ {\n        PrefixStats left;\n        PrefixStats right;\n    };\n\n   private:\n\
    \    static_assert(2 <= ChunkCapacity);\n    static_assert(\n        ChunkCapacity\
    \ <= std::numeric_limits<std::uint16_t>::max()\n    );\n    static_assert(0 <\
    \ GroupSize && GroupSize <= ChunkCapacity);\n    static_assert(ChunkCapacity %\
    \ GroupSize == 0);\n    static constexpr int word_bits = 64;\n    static constexpr\
    \ int word_count =\n        (ChunkCapacity + word_bits - 1) / word_bits;\n   \
    \ static constexpr int group_count = ChunkCapacity / GroupSize;\n    static constexpr\
    \ int minimum_chunk_size = ChunkCapacity / 2;\n\n    struct Node {\n        std::array<Sum,\
    \ ChunkCapacity> weights{};\n        std::array<Sum, group_count> group_total_sums{};\n\
    \        std::array<Sum, group_count> group_zero_sums{};\n        std::array<std::uint64_t,\
    \ word_count> bits{};\n        Sum chunk_total_sum{};\n        Sum chunk_zero_sum{};\n\
    \        Sum subtree_total_sum{};\n        Sum subtree_zero_sum{};\n        std::uint32_t\
    \ priority = 0;\n        int left = 0;\n        int right = 0;\n        int subtree_size\
    \ = 0;\n        int subtree_ones = 0;\n        std::uint16_t length = 0;\n   \
    \     std::uint16_t chunk_ones = 0;\n    };\n\n    std::vector<Node> _nodes;\n\
    \    std::vector<int> _free_nodes;\n    int _root = 0;\n    std::uint32_t _random_state\
    \ = 1;\n\n    int size_of(int node) const {\n        return _nodes[node].subtree_size;\n\
    \    }\n\n    int ones_of(int node) const {\n        return _nodes[node].subtree_ones;\n\
    \    }\n\n    const Sum& total_sum_of(int node) const {\n        return _nodes[node].subtree_total_sum;\n\
    \    }\n\n    const Sum& zero_sum_of(int node) const {\n        return _nodes[node].subtree_zero_sum;\n\
    \    }\n\n    std::uint32_t next_priority() {\n        _random_state ^= _random_state\
    \ << 13;\n        _random_state ^= _random_state >> 17;\n        _random_state\
    \ ^= _random_state << 5;\n        if (_random_state == 0) _random_state = 1;\n\
    \        return _random_state;\n    }\n\n    bool local_bit(int node, int position)\
    \ const {\n        return (_nodes[node].bits[position / word_bits] >>\n      \
    \          (position % word_bits)) &\n               1U;\n    }\n\n    void local_set_bit(int\
    \ node, int position, bool bit) {\n        std::uint64_t mask =\n            std::uint64_t(1)\
    \ << (position % word_bits);\n        std::uint64_t& word = _nodes[node].bits[position\
    \ / word_bits];\n        if (bit) {\n            word |= mask;\n        } else\
    \ {\n            word &= ~mask;\n        }\n    }\n\n    int local_rank1(int node,\
    \ int right) const {\n        int full_words = right / word_bits;\n        int\
    \ result = 0;\n        for (int word = 0; word < full_words; word++) {\n     \
    \       result += std::popcount(_nodes[node].bits[word]);\n        }\n       \
    \ int remainder = right % word_bits;\n        if (remainder != 0) {\n        \
    \    result += std::popcount(\n                _nodes[node].bits[full_words] &\n\
    \                ((std::uint64_t(1) << remainder) - 1)\n            );\n     \
    \   }\n        return result;\n    }\n\n    void update(int node) {\n        if\
    \ (node == 0) return;\n        Node& current = _nodes[node];\n        current.subtree_size\
    \ =\n            size_of(current.left) + int(current.length) +\n            size_of(current.right);\n\
    \        current.subtree_ones =\n            ones_of(current.left) + int(current.chunk_ones)\
    \ +\n            ones_of(current.right);\n        current.subtree_total_sum =\n\
    \            total_sum_of(current.left) + current.chunk_total_sum +\n        \
    \    total_sum_of(current.right);\n        current.subtree_zero_sum =\n      \
    \      zero_sum_of(current.left) + current.chunk_zero_sum +\n            zero_sum_of(current.right);\n\
    \    }\n\n    void rebuild_chunk(int node) {\n        M1UNE_DWM_SUM_PROFILE_ADD(full_chunk_rebuilds,\
    \ 1);\n        Node& current = _nodes[node];\n        current.group_total_sums.fill(Sum{});\n\
    \        current.group_zero_sums.fill(Sum{});\n        current.chunk_total_sum\
    \ = Sum{};\n        current.chunk_zero_sum = Sum{};\n        current.chunk_ones\
    \ = 0;\n        for (int position = 0; position < current.length; position++)\
    \ {\n            int group = position / GroupSize;\n            const Sum& weight\
    \ = current.weights[position];\n            current.group_total_sums[group] =\n\
    \                current.group_total_sums[group] + weight;\n            current.chunk_total_sum\
    \ = current.chunk_total_sum + weight;\n            if (local_bit(node, position))\
    \ {\n                current.chunk_ones++;\n            } else {\n           \
    \     current.group_zero_sums[group] =\n                    current.group_zero_sums[group]\
    \ + weight;\n                current.chunk_zero_sum = current.chunk_zero_sum +\
    \ weight;\n            }\n        }\n        update(node);\n    }\n\n    PrefixStats\
    \ local_prefix_stats(int node, int right) const {\n        PrefixStats result;\n\
    \        result.ones = local_rank1(node, right);\n        int full_groups = right\
    \ / GroupSize;\n        for (int group = 0; group < full_groups; group++) {\n\
    \            result.total_sum =\n                result.total_sum + _nodes[node].group_total_sums[group];\n\
    \            result.zero_sum =\n                result.zero_sum + _nodes[node].group_zero_sums[group];\n\
    \        }\n        for (int position = full_groups * GroupSize; position < right;\n\
    \             position++) {\n            const Sum& weight = _nodes[node].weights[position];\n\
    \            result.total_sum = result.total_sum + weight;\n            if (!local_bit(node,\
    \ position)) {\n                result.zero_sum = result.zero_sum + weight;\n\
    \            }\n        }\n        return result;\n    }\n\n    static void add_stats(PrefixStats&\
    \ destination, const PrefixStats& value) {\n        destination.ones += value.ones;\n\
    \        destination.total_sum = destination.total_sum + value.total_sum;\n  \
    \      destination.zero_sum = destination.zero_sum + value.zero_sum;\n    }\n\n\
    \    PrefixStats subtree_stats(int node) const {\n        return PrefixStats{\n\
    \            ones_of(node),\n            total_sum_of(node),\n            zero_sum_of(node)\n\
    \        };\n    }\n\n    void local_insert(int node, int position, bool bit,\
    \ const Sum& weight) {\n        Node& current = _nodes[node];\n        assert(0\
    \ <= position && position <= current.length);\n        assert(current.length <\
    \ ChunkCapacity);\n        M1UNE_DWM_SUM_PROFILE_ADD(\n            local_element_moves,\n\
    \            int(current.length) - position\n        );\n        for (int i =\
    \ current.length; position < i; i--) {\n            current.weights[i] = current.weights[i\
    \ - 1];\n            local_set_bit(node, i, local_bit(node, i - 1));\n       \
    \ }\n        current.weights[position] = weight;\n        local_set_bit(node,\
    \ position, bit);\n        current.length++;\n        rebuild_chunk(node);\n \
    \   }\n\n    EraseRankResult local_erase(int node, int position) {\n        Node&\
    \ current = _nodes[node];\n        assert(0 <= position && position < current.length);\n\
    \        M1UNE_DWM_SUM_PROFILE_ADD(\n            local_element_moves,\n      \
    \      int(current.length) - position - 1\n        );\n        EraseRankResult\
    \ result{\n            local_bit(node, position),\n            current.weights[position],\n\
    \            0\n        };\n        for (int i = position; i + 1 < current.length;\
    \ i++) {\n            current.weights[i] = current.weights[i + 1];\n         \
    \   local_set_bit(node, i, local_bit(node, i + 1));\n        }\n        current.length--;\n\
    \        current.weights[current.length] = Sum{};\n        local_set_bit(node,\
    \ current.length, false);\n        rebuild_chunk(node);\n        return result;\n\
    \    }\n\n    Sum local_set_weight(int node, int position, const Sum& weight)\
    \ {\n        Node& current = _nodes[node];\n        Sum old_weight = current.weights[position];\n\
    \        Sum delta = weight - old_weight;\n        current.weights[position] =\
    \ weight;\n        int group = position / GroupSize;\n        current.group_total_sums[group]\
    \ =\n            current.group_total_sums[group] + delta;\n        current.chunk_total_sum\
    \ = current.chunk_total_sum + delta;\n        if (!local_bit(node, position))\
    \ {\n            current.group_zero_sums[group] =\n                current.group_zero_sums[group]\
    \ + delta;\n            current.chunk_zero_sum = current.chunk_zero_sum + delta;\n\
    \        }\n        update(node);\n        return old_weight;\n    }\n\n    Sum\
    \ local_add_weight(int node, int position, const Sum& delta) {\n        return\
    \ local_set_weight(\n            node,\n            position,\n            _nodes[node].weights[position]\
    \ + delta\n        );\n    }\n\n    int new_node() {\n        int node;\n    \
    \    if (_free_nodes.empty()) {\n            node = int(_nodes.size());\n    \
    \        _nodes.emplace_back();\n        } else {\n            node = _free_nodes.back();\n\
    \            _free_nodes.pop_back();\n            _nodes[node] = Node();\n   \
    \     }\n        _nodes[node].priority = next_priority();\n        return node;\n\
    \    }\n\n    template <std::size_t Capacity>\n    void assign_from_values(\n\
    \        int node,\n        const std::array<std::uint8_t, Capacity>& bits,\n\
    \        const std::array<Sum, Capacity>& weights,\n        int first,\n     \
    \   int last\n    ) {\n        Node& current = _nodes[node];\n        current.bits.fill(0);\n\
    \        current.weights.fill(Sum{});\n        current.length = std::uint16_t(last\
    \ - first);\n        for (int position = first; position < last; position++) {\n\
    \            int destination = position - first;\n            current.weights[destination]\
    \ = weights[position];\n            if (bits[position]) local_set_bit(node, destination,\
    \ true);\n        }\n        rebuild_chunk(node);\n    }\n\n    void assign_from_values(\n\
    \        int node,\n        const std::vector<std::uint8_t>& bits,\n        const\
    \ std::vector<Sum>& weights,\n        int first,\n        int last\n    ) {\n\
    \        Node& current = _nodes[node];\n        current.bits.fill(0);\n      \
    \  current.weights.fill(Sum{});\n        current.length = std::uint16_t(last -\
    \ first);\n        for (int position = first; position < last; position++) {\n\
    \            int destination = position - first;\n            current.weights[destination]\
    \ = weights[position];\n            if (bits[position]) local_set_bit(node, destination,\
    \ true);\n        }\n        rebuild_chunk(node);\n    }\n\n    int new_node(\n\
    \        const std::vector<std::uint8_t>& bits,\n        const std::vector<Sum>&\
    \ weights,\n        int first,\n        int last\n    ) {\n        int node =\
    \ new_node();\n        assign_from_values(node, bits, weights, first, last);\n\
    \        return node;\n    }\n\n    void recycle_node(int node) {\n        assert(node\
    \ != 0);\n        _nodes[node] = Node();\n        _free_nodes.push_back(node);\n\
    \    }\n\n    int merge(int left, int right) {\n        if (left == 0 || right\
    \ == 0) return left != 0 ? left : right;\n        if (_nodes[left].priority >\
    \ _nodes[right].priority) {\n            _nodes[left].right = merge(_nodes[left].right,\
    \ right);\n            update(left);\n            return left;\n        }\n  \
    \      _nodes[right].left = merge(left, _nodes[right].left);\n        update(right);\n\
    \        return right;\n    }\n\n    int rotate_right(int tree) {\n        int\
    \ result = _nodes[tree].left;\n        _nodes[tree].left = _nodes[result].right;\n\
    \        _nodes[result].right = tree;\n        update(tree);\n        update(result);\n\
    \        return result;\n    }\n\n    int rotate_left(int tree) {\n        int\
    \ result = _nodes[tree].right;\n        _nodes[tree].right = _nodes[result].left;\n\
    \        _nodes[result].left = tree;\n        update(tree);\n        update(result);\n\
    \        return result;\n    }\n\n    int extract_leftmost(int tree, int& extracted)\
    \ {\n        if (_nodes[tree].left == 0) {\n            extracted = tree;\n  \
    \          int result = _nodes[tree].right;\n            _nodes[tree].right =\
    \ 0;\n            update(tree);\n            return result;\n        }\n     \
    \   _nodes[tree].left = extract_leftmost(_nodes[tree].left, extracted);\n    \
    \    update(tree);\n        return tree;\n    }\n\n    int extract_rightmost(int\
    \ tree, int& extracted) {\n        if (_nodes[tree].right == 0) {\n          \
    \  extracted = tree;\n            int result = _nodes[tree].left;\n          \
    \  _nodes[tree].left = 0;\n            update(tree);\n            return result;\n\
    \        }\n        _nodes[tree].right = extract_rightmost(_nodes[tree].right,\
    \ extracted);\n        update(tree);\n        return tree;\n    }\n\n    int rebalance(int\
    \ node) {\n        if (_nodes[node].length >= minimum_chunk_size) return node;\n\
    \n        if (_nodes[node].right != 0) {\n            int neighbor = 0;\n    \
    \        _nodes[node].right =\n                extract_leftmost(_nodes[node].right,\
    \ neighbor);\n            int node_length = _nodes[node].length;\n           \
    \ int neighbor_length = _nodes[neighbor].length;\n            int total = node_length\
    \ + neighbor_length;\n            std::array<std::uint8_t, ChunkCapacity * 2>\
    \ bits{};\n            std::array<Sum, ChunkCapacity * 2> weights{};\n       \
    \     for (int i = 0; i < node_length; i++) {\n                bits[i] = local_bit(node,\
    \ i);\n                weights[i] = _nodes[node].weights[i];\n            }\n\
    \            for (int i = 0; i < neighbor_length; i++) {\n                bits[node_length\
    \ + i] = local_bit(neighbor, i);\n                weights[node_length + i] = _nodes[neighbor].weights[i];\n\
    \            }\n            if (total <= ChunkCapacity) {\n                M1UNE_DWM_SUM_PROFILE_ADD(chunk_merges,\
    \ 1);\n                assign_from_values(node, bits, weights, 0, total);\n  \
    \              recycle_node(neighbor);\n            } else {\n               \
    \ int left_length = total / 2;\n                assign_from_values(node, bits,\
    \ weights, 0, left_length);\n                assign_from_values(\n           \
    \         neighbor,\n                    bits,\n                    weights,\n\
    \                    left_length,\n                    total\n               \
    \ );\n                _nodes[node].right = merge(neighbor, _nodes[node].right);\n\
    \            }\n            update(node);\n            return node;\n        }\n\
    \n        if (_nodes[node].left != 0) {\n            int neighbor = 0;\n     \
    \       _nodes[node].left =\n                extract_rightmost(_nodes[node].left,\
    \ neighbor);\n            int neighbor_length = _nodes[neighbor].length;\n   \
    \         int node_length = _nodes[node].length;\n            int total = neighbor_length\
    \ + node_length;\n            std::array<std::uint8_t, ChunkCapacity * 2> bits{};\n\
    \            std::array<Sum, ChunkCapacity * 2> weights{};\n            for (int\
    \ i = 0; i < neighbor_length; i++) {\n                bits[i] = local_bit(neighbor,\
    \ i);\n                weights[i] = _nodes[neighbor].weights[i];\n           \
    \ }\n            for (int i = 0; i < node_length; i++) {\n                bits[neighbor_length\
    \ + i] = local_bit(node, i);\n                weights[neighbor_length + i] = _nodes[node].weights[i];\n\
    \            }\n            if (total <= ChunkCapacity) {\n                M1UNE_DWM_SUM_PROFILE_ADD(chunk_merges,\
    \ 1);\n                assign_from_values(node, bits, weights, 0, total);\n  \
    \              recycle_node(neighbor);\n            } else {\n               \
    \ int left_length = total / 2;\n                assign_from_values(\n        \
    \            neighbor,\n                    bits,\n                    weights,\n\
    \                    0,\n                    left_length\n                );\n\
    \                assign_from_values(\n                    node,\n            \
    \        bits,\n                    weights,\n                    left_length,\n\
    \                    total\n                );\n                _nodes[node].left\
    \ = merge(_nodes[node].left, neighbor);\n            }\n            update(node);\n\
    \        }\n        return node;\n    }\n\n    int insert_impl(\n        int tree,\n\
    \        int position,\n        bool bit,\n        const Sum& weight,\n      \
    \  int& ones_before\n    ) {\n        if (tree == 0) {\n            int node =\
    \ new_node();\n            local_insert(node, 0, bit, weight);\n            return\
    \ node;\n        }\n\n        int left_size = size_of(_nodes[tree].left);\n  \
    \      int length = _nodes[tree].length;\n        if (position < left_size) {\n\
    \            _nodes[tree].left = insert_impl(\n                _nodes[tree].left,\n\
    \                position,\n                bit,\n                weight,\n  \
    \              ones_before\n            );\n            update(tree);\n      \
    \      if (_nodes[_nodes[tree].left].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_right(tree);\n            }\n            return\
    \ tree;\n        }\n        if (position > left_size + length) {\n           \
    \ ones_before +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = insert_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                bit,\n      \
    \          weight,\n                ones_before\n            );\n            update(tree);\n\
    \            if (_nodes[_nodes[tree].right].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_left(tree);\n            }\n            return\
    \ tree;\n        }\n\n        int local_position = position - left_size;\n   \
    \     ones_before += ones_of(_nodes[tree].left) +\n                       local_rank1(tree,\
    \ local_position);\n        if (length < ChunkCapacity) {\n            local_insert(tree,\
    \ local_position, bit, weight);\n            return tree;\n        }\n\n     \
    \   std::array<std::uint8_t, ChunkCapacity> bits{};\n        std::array<Sum, ChunkCapacity>\
    \ weights{};\n        M1UNE_DWM_SUM_PROFILE_ADD(chunk_splits, 1);\n        for\
    \ (int i = 0; i < ChunkCapacity; i++) {\n            bits[i] = local_bit(tree,\
    \ i);\n            weights[i] = _nodes[tree].weights[i];\n        }\n        int\
    \ right_chunk = new_node();\n        int middle = ChunkCapacity / 2;\n       \
    \ assign_from_values(tree, bits, weights, 0, middle);\n        assign_from_values(\n\
    \            right_chunk,\n            bits,\n            weights,\n         \
    \   middle,\n            ChunkCapacity\n        );\n        if (local_position\
    \ <= middle) {\n            local_insert(tree, local_position, bit, weight);\n\
    \        } else {\n            local_insert(\n                right_chunk,\n \
    \               local_position - middle,\n                bit,\n             \
    \   weight\n            );\n        }\n\n        int old_right = _nodes[tree].right;\n\
    \        _nodes[tree].right = 0;\n        update(tree);\n        return merge(merge(tree,\
    \ right_chunk), old_right);\n    }\n\n    int erase_impl(\n        int tree,\n\
    \        int position,\n        EraseRankResult& result\n    ) {\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int length = _nodes[tree].length;\n\
    \        if (position < left_size) {\n            _nodes[tree].left = erase_impl(\n\
    \                _nodes[tree].left,\n                position,\n             \
    \   result\n            );\n            update(tree);\n            return tree;\n\
    \        }\n        if (position >= left_size + length) {\n            result.ones_before\
    \ +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = erase_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                result\n    \
    \        );\n            update(tree);\n            return tree;\n        }\n\n\
    \        int local_position = position - left_size;\n        result.ones_before\
    \ += ones_of(_nodes[tree].left) +\n                              local_rank1(tree,\
    \ local_position);\n        EraseRankResult local = local_erase(tree, local_position);\n\
    \        result.bit = local.bit;\n        result.weight = local.weight;\n    \
    \    if (_nodes[tree].length == 0) {\n            int merged = merge(_nodes[tree].left,\
    \ _nodes[tree].right);\n            recycle_node(tree);\n            return merged;\n\
    \        }\n        return rebalance(tree);\n    }\n\n    template <bool Add>\n\
    \    void change_weight_impl(\n        int tree,\n        int position,\n    \
    \    const Sum& value,\n        AccessRankResult& result\n    ) {\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        if (position < left_size) {\n\
    \            change_weight_impl<Add>(\n                _nodes[tree].left,\n  \
    \              position,\n                value,\n                result\n   \
    \         );\n        } else if (position < left_size + _nodes[tree].length) {\n\
    \            int local_position = position - left_size;\n            result.ones_before\
    \ += ones_of(_nodes[tree].left) +\n                                  local_rank1(tree,\
    \ local_position);\n            result.bit = local_bit(tree, local_position);\n\
    \            if constexpr (Add) {\n                result.weight = local_add_weight(tree,\
    \ local_position, value);\n            } else {\n                result.weight\
    \ = local_set_weight(tree, local_position, value);\n            }\n          \
    \  return;\n        } else {\n            result.ones_before +=\n            \
    \    ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n            change_weight_impl<Add>(\n\
    \                _nodes[tree].right,\n                position - left_size - _nodes[tree].length,\n\
    \                value,\n                result\n            );\n        }\n \
    \       update(tree);\n    }\n\n    PrefixStats prefix_stats_impl(int tree, int\
    \ right) const {\n        PrefixStats result;\n        while (tree != 0 && right\
    \ != 0) {\n            int left_size = size_of(_nodes[tree].left);\n         \
    \   if (right <= left_size) {\n                tree = _nodes[tree].left;\n   \
    \             continue;\n            }\n            add_stats(result, subtree_stats(_nodes[tree].left));\n\
    \            right -= left_size;\n            int take = std::min(right, int(_nodes[tree].length));\n\
    \            add_stats(result, local_prefix_stats(tree, take));\n            right\
    \ -= take;\n            if (right == 0) break;\n            tree = _nodes[tree].right;\n\
    \        }\n        return result;\n    }\n\n    PrefixStatsPair prefix_stats_pair_impl(\n\
    \        int tree,\n        int left,\n        int right\n    ) const {\n    \
    \    if (left == right) {\n            PrefixStats value = prefix_stats_impl(tree,\
    \ left);\n            return PrefixStatsPair{value, value};\n        }\n     \
    \   if (tree == 0 || right == 0) return PrefixStatsPair{};\n\n        int left_size\
    \ = size_of(_nodes[tree].left);\n        int chunk_end = left_size + _nodes[tree].length;\n\
    \        if (right <= left_size) {\n            return prefix_stats_pair_impl(\n\
    \                _nodes[tree].left,\n                left,\n                right\n\
    \            );\n        }\n        if (chunk_end <= left) {\n            PrefixStats\
    \ base = subtree_stats(_nodes[tree].left);\n            add_stats(base, local_prefix_stats(tree,\
    \ _nodes[tree].length));\n            PrefixStatsPair result = prefix_stats_pair_impl(\n\
    \                _nodes[tree].right,\n                left - chunk_end,\n    \
    \            right - chunk_end\n            );\n            add_stats(result.left,\
    \ base);\n            add_stats(result.right, base);\n            return result;\n\
    \        }\n\n        PrefixStats left_stats;\n        if (left <= left_size)\
    \ {\n            left_stats = prefix_stats_impl(_nodes[tree].left, left);\n  \
    \      } else {\n            left_stats = subtree_stats(_nodes[tree].left);\n\
    \            add_stats(\n                left_stats,\n                local_prefix_stats(tree,\
    \ left - left_size)\n            );\n        }\n\n        PrefixStats right_stats\
    \ = subtree_stats(_nodes[tree].left);\n        if (right <= chunk_end) {\n   \
    \         add_stats(\n                right_stats,\n                local_prefix_stats(tree,\
    \ right - left_size)\n            );\n        } else {\n            add_stats(\n\
    \                right_stats,\n                local_prefix_stats(tree, _nodes[tree].length)\n\
    \            );\n            add_stats(\n                right_stats,\n      \
    \          prefix_stats_impl(_nodes[tree].right, right - chunk_end)\n        \
    \    );\n        }\n        return PrefixStatsPair{left_stats, right_stats};\n\
    \    }\n\n    template <class Predicate>\n    int consume_chunk_prefix(\n    \
    \    int node,\n        int left,\n        int right,\n        Sum& sum,\n   \
    \     Predicate& predicate\n    ) const {\n        int position = left;\n    \
    \    while (position < right) {\n            if (position % GroupSize == 0 &&\n\
    \                position + GroupSize <= right) {\n                int group =\
    \ position / GroupSize;\n                Sum candidate =\n                   \
    \ sum + _nodes[node].group_total_sums[group];\n                if (predicate(candidate))\
    \ {\n                    sum = candidate;\n                    position += GroupSize;\n\
    \                    continue;\n                }\n            }\n           \
    \ Sum candidate = sum + _nodes[node].weights[position];\n            if (!predicate(candidate))\
    \ break;\n            sum = candidate;\n            position++;\n        }\n \
    \       return position - left;\n    }\n\n    template <class Predicate>\n   \
    \ int consume_chunk_suffix(\n        int node,\n        int left,\n        int\
    \ right,\n        Sum& sum,\n        Predicate& predicate\n    ) const {\n   \
    \     int position = right;\n        while (left < position) {\n            if\
    \ (position % GroupSize == 0 &&\n                left <= position - GroupSize)\
    \ {\n                int group = position / GroupSize - 1;\n                Sum\
    \ candidate =\n                    sum + _nodes[node].group_total_sums[group];\n\
    \                if (predicate(candidate)) {\n                    sum = candidate;\n\
    \                    position -= GroupSize;\n                    continue;\n \
    \               }\n            }\n            Sum candidate = sum + _nodes[node].weights[position\
    \ - 1];\n            if (!predicate(candidate)) break;\n            sum = candidate;\n\
    \            position--;\n        }\n        return right - position;\n    }\n\
    \n    template <class Predicate>\n    int max_prefix_impl(\n        int tree,\n\
    \        int left,\n        int right,\n        Sum& sum,\n        Predicate&\
    \ predicate\n    ) const {\n        assert(tree != 0);\n        assert(0 <= left\
    \ && left < right && right <= size_of(tree));\n        if (left == 0 && right\
    \ == size_of(tree)) {\n            Sum candidate = sum + total_sum_of(tree);\n\
    \            if (predicate(candidate)) {\n                sum = candidate;\n \
    \               return size_of(tree);\n            }\n        }\n\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int chunk_end = left_size +\
    \ _nodes[tree].length;\n        int count = 0;\n        if (left < left_size)\
    \ {\n            int subtree_right = std::min(right, left_size);\n           \
    \ int consumed = max_prefix_impl(\n                _nodes[tree].left,\n      \
    \          left,\n                subtree_right,\n                sum,\n     \
    \           predicate\n            );\n            count += consumed;\n      \
    \      if (consumed < subtree_right - left) return count;\n        }\n\n     \
    \   int chunk_left = std::max(left, left_size);\n        int chunk_right = std::min(right,\
    \ chunk_end);\n        if (chunk_left < chunk_right) {\n            int consumed\
    \ = consume_chunk_prefix(\n                tree,\n                chunk_left -\
    \ left_size,\n                chunk_right - left_size,\n                sum,\n\
    \                predicate\n            );\n            count += consumed;\n \
    \           if (consumed < chunk_right - chunk_left) return count;\n        }\n\
    \n        if (chunk_end < right) {\n            int subtree_left = std::max(left,\
    \ chunk_end) - chunk_end;\n            int subtree_right = right - chunk_end;\n\
    \            count += max_prefix_impl(\n                _nodes[tree].right,\n\
    \                subtree_left,\n                subtree_right,\n             \
    \   sum,\n                predicate\n            );\n        }\n        return\
    \ count;\n    }\n\n    template <class Predicate>\n    int max_suffix_impl(\n\
    \        int tree,\n        int left,\n        int right,\n        Sum& sum,\n\
    \        Predicate& predicate\n    ) const {\n        assert(tree != 0);\n   \
    \     assert(0 <= left && left < right && right <= size_of(tree));\n        if\
    \ (left == 0 && right == size_of(tree)) {\n            Sum candidate = sum + total_sum_of(tree);\n\
    \            if (predicate(candidate)) {\n                sum = candidate;\n \
    \               return size_of(tree);\n            }\n        }\n\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int chunk_end = left_size +\
    \ _nodes[tree].length;\n        int count = 0;\n        if (chunk_end < right)\
    \ {\n            int subtree_left = std::max(left, chunk_end) - chunk_end;\n \
    \           int subtree_right = right - chunk_end;\n            int consumed =\
    \ max_suffix_impl(\n                _nodes[tree].right,\n                subtree_left,\n\
    \                subtree_right,\n                sum,\n                predicate\n\
    \            );\n            count += consumed;\n            if (consumed < subtree_right\
    \ - subtree_left) return count;\n        }\n\n        int chunk_left = std::max(left,\
    \ left_size);\n        int chunk_right = std::min(right, chunk_end);\n       \
    \ if (chunk_left < chunk_right) {\n            int consumed = consume_chunk_suffix(\n\
    \                tree,\n                chunk_left - left_size,\n            \
    \    chunk_right - left_size,\n                sum,\n                predicate\n\
    \            );\n            count += consumed;\n            if (consumed < chunk_right\
    \ - chunk_left) return count;\n        }\n\n        if (left < left_size) {\n\
    \            int subtree_right = std::min(right, left_size);\n            count\
    \ += max_suffix_impl(\n                _nodes[tree].left,\n                left,\n\
    \                subtree_right,\n                sum,\n                predicate\n\
    \            );\n        }\n        return count;\n    }\n\n    void update_subtree(int\
    \ tree) {\n        if (tree == 0) return;\n        update_subtree(_nodes[tree].left);\n\
    \        update_subtree(_nodes[tree].right);\n        update(tree);\n    }\n\n\
    \    void build(\n        const std::vector<std::uint8_t>& bits,\n        const\
    \ std::vector<Sum>& weights\n    ) {\n        assert(bits.size() == weights.size());\n\
    \        _nodes.clear();\n        _nodes.emplace_back();\n        _free_nodes.clear();\n\
    \        _root = 0;\n        _nodes.reserve(weights.size() / minimum_chunk_size\
    \ + 2);\n\n        std::vector<int> stack;\n        for (int first = 0; first\
    \ < int(weights.size());\n             first += ChunkCapacity) {\n           \
    \ int last =\n                std::min(first + ChunkCapacity, int(weights.size()));\n\
    \            int node = new_node(bits, weights, first, last);\n            int\
    \ left = 0;\n            while (!stack.empty() &&\n                   _nodes[stack.back()].priority\
    \ < _nodes[node].priority) {\n                left = stack.back();\n         \
    \       stack.pop_back();\n            }\n            _nodes[node].left = left;\n\
    \            if (!stack.empty()) _nodes[stack.back()].right = node;\n        \
    \    stack.push_back(node);\n        }\n        if (!stack.empty()) _root = stack.front();\n\
    \        update_subtree(_root);\n    }\n\n   public:\n    DynamicWeightedRankSequence()\
    \ : _nodes(1) {}\n\n    DynamicWeightedRankSequence(\n        const std::vector<std::uint8_t>&\
    \ bits,\n        const std::vector<Sum>& weights,\n        std::uint32_t seed\
    \ = 1\n    ) : _random_state(seed == 0 ? 1 : seed) {\n        build(bits, weights);\n\
    \    }\n\n    explicit DynamicWeightedRankSequence(\n        const std::vector<Sum>&\
    \ weights,\n        std::uint32_t seed = 1\n    ) : _random_state(seed == 0 ?\
    \ 1 : seed) {\n        build(std::vector<std::uint8_t>(weights.size()), weights);\n\
    \    }\n\n    int size() const {\n        return size_of(_root);\n    }\n\n  \
    \  AccessRankResult access_with_rank(int position) const {\n        assert(0 <=\
    \ position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        int tree = _root;\n        int ones_before = 0;\n        while\
    \ (tree != 0) {\n            int left_size = size_of(_nodes[tree].left);\n   \
    \         if (position < left_size) {\n                tree = _nodes[tree].left;\n\
    \            } else if (position < left_size + _nodes[tree].length) {\n      \
    \          int local_position = position - left_size;\n                ones_before\
    \ += ones_of(_nodes[tree].left) +\n                               local_rank1(tree,\
    \ local_position);\n                return AccessRankResult{\n               \
    \     local_bit(tree, local_position),\n                    _nodes[tree].weights[local_position],\n\
    \                    ones_before\n                };\n            } else {\n \
    \               ones_before +=\n                    ones_of(_nodes[tree].left)\
    \ + _nodes[tree].chunk_ones;\n                position -= left_size + _nodes[tree].length;\n\
    \                tree = _nodes[tree].right;\n            }\n        }\n      \
    \  assert(false);\n        return AccessRankResult{false, Sum{}, 0};\n    }\n\n\
    \    PrefixStats prefix_stats(int right) const {\n        assert(0 <= right &&\
    \ right <= size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        return prefix_stats_impl(_root, right);\n    }\n\n    PrefixStatsPair\
    \ prefix_stats_pair(int left, int right) const {\n        assert(0 <= left &&\
    \ left <= right && right <= size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        return prefix_stats_pair_impl(_root, left, right);\n    }\n\n \
    \   Sum range_sum(int left, int right) const {\n        PrefixStatsPair stats\
    \ = prefix_stats_pair(left, right);\n        return stats.right.total_sum - stats.left.total_sum;\n\
    \    }\n\n    int insert_with_rank(\n        int position,\n        bool bit,\n\
    \        const Sum& weight\n    ) {\n        assert(0 <= position && position\
    \ <= size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);\n\
    \        int ones_before = 0;\n        _root = insert_impl(\n            _root,\n\
    \            position,\n            bit,\n            weight,\n            ones_before\n\
    \        );\n        return ones_before;\n    }\n\n    EraseRankResult erase_with_rank(int\
    \ position) {\n        assert(0 <= position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        EraseRankResult result{false, Sum{}, 0};\n        _root = erase_impl(_root,\
    \ position, result);\n        return result;\n    }\n\n    AccessRankResult set_weight_with_rank(\n\
    \        int position,\n        const Sum& weight\n    ) {\n        assert(0 <=\
    \ position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        AccessRankResult result{false, Sum{}, 0};\n        change_weight_impl<false>(_root,\
    \ position, weight, result);\n        return result;\n    }\n\n    AccessRankResult\
    \ add_weight_with_rank(\n        int position,\n        const Sum& delta\n   \
    \ ) {\n        assert(0 <= position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        AccessRankResult result{false, Sum{}, 0};\n        change_weight_impl<true>(_root,\
    \ position, delta, result);\n        return result;\n    }\n\n    template <class\
    \ Predicate>\n    int max_prefix(\n        int left,\n        int right,\n   \
    \     Sum& sum,\n        Predicate& predicate\n    ) const {\n        assert(0\
    \ <= left && left <= right && right <= size());\n        if (left == right) return\
    \ 0;\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);\n        return\
    \ max_prefix_impl(_root, left, right, sum, predicate);\n    }\n\n    template\
    \ <class Predicate>\n    int max_suffix(\n        int left,\n        int right,\n\
    \        Sum& sum,\n        Predicate& predicate\n    ) const {\n        assert(0\
    \ <= left && left <= right && right <= size());\n        if (left == right) return\
    \ 0;\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);\n        return\
    \ max_suffix_impl(_root, left, right, sum, predicate);\n    }\n};\n\n}  // namespace\
    \ dynamic_wavelet_matrix_sum_detail\n\n#undef M1UNE_DWM_SUM_PROFILE_ADD\n\n//\
    \ A dynamic wavelet matrix with additive weights.\n// By default, each value is\
    \ also used as its weight.\ntemplate <\n    std::integral T,\n    typename Sum\
    \ = T,\n    int BitWidth = std::numeric_limits<std::make_unsigned_t<T>>::digits\n\
    >\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nclass DynamicWaveletMatrixSum\
    \ {\n   public:\n    using value_type = T;\n    using sum_type = Sum;\n    using\
    \ unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n    static constexpr\
    \ int full_bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static_assert(1 <= BitWidth && BitWidth <= full_bit_width);\n    static_assert(\n\
    \        BitWidth == full_bit_width || std::unsigned_integral<T>,\n        \"\
    reduced-width keys must use an unsigned type\"\n    );\n\n    static constexpr\
    \ unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (BitWidth - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    static constexpr\
    \ unsigned_type reduced_limit = [] {\n        if constexpr (BitWidth < full_bit_width)\
    \ {\n            return unsigned_type(1) << BitWidth;\n        } else {\n    \
    \        return unsigned_type(0);\n        }\n    }();\n\n    using Level = dynamic_wavelet_matrix_sum_detail::\n\
    \        DynamicWeightedRankSequence<Sum>;\n\n    struct ErasedElement {\n   \
    \     unsigned_type key;\n        Sum weight;\n    };\n\n    int _size = 0;\n\
    \    std::vector<Level> _levels;\n    Level _final_weights;\n    std::array<int,\
    \ BitWidth> _zero_count{};\n\n    static bool key_fits(T value) {\n        if\
    \ constexpr (BitWidth < full_bit_width) {\n            return static_cast<unsigned_type>(value)\
    \ < reduced_limit;\n        } else {\n            return true;\n        }\n  \
    \  }\n\n    static unsigned_type encode_unchecked(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static unsigned_type\
    \ encode_key(T value) {\n        assert(key_fits(value));\n        return encode_unchecked(value);\n\
    \    }\n\n    static T decode(unsigned_type key) {\n        unsigned_type bits\
    \ = key ^ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n     \
    \       return std::bit_cast<T>(bits);\n        } else {\n            return bits;\n\
    \        }\n    }\n\n    static bool bit(unsigned_type key, int level) {\n   \
    \     return (key >> (BitWidth - 1 - level)) & unsigned_type(1);\n    }\n\n  \
    \  static Sum range_total(const typename Level::PrefixStatsPair& stats) {\n  \
    \      return stats.right.total_sum - stats.left.total_sum;\n    }\n\n    static\
    \ Sum range_zero(const typename Level::PrefixStatsPair& stats) {\n        return\
    \ stats.right.zero_sum - stats.left.zero_sum;\n    }\n\n    void build(const std::vector<T>&\
    \ values, const std::vector<Sum>& weights) {\n        assert(values.size() ==\
    \ weights.size());\n        _size = int(values.size());\n\n        std::vector<unsigned_type>\
    \ current_keys(_size);\n        std::vector<unsigned_type> next_keys(_size);\n\
    \        std::vector<Sum> current_weights(weights);\n        std::vector<Sum>\
    \ next_weights(_size);\n        for (int i = 0; i < _size; i++) {\n          \
    \  current_keys[i] = encode_key(values[i]);\n        }\n\n        _levels.clear();\n\
    \        _levels.reserve(BitWidth);\n        for (int level = 0; level < BitWidth;\
    \ level++) {\n            std::vector<std::uint8_t> bits(_size);\n           \
    \ int zeros = 0;\n            for (int i = 0; i < _size; i++) {\n            \
    \    bits[i] = bit(current_keys[i], level);\n                zeros += !bits[i];\n\
    \            }\n            _zero_count[level] = zeros;\n            _levels.emplace_back(\n\
    \                bits,\n                current_weights,\n                std::uint32_t(0x9e3779b9U\
    \ + level * 0x85ebca6bU)\n            );\n\n            int zero_position = 0;\n\
    \            int one_position = zeros;\n            for (int i = 0; i < _size;\
    \ i++) {\n                int next_position = bits[i] ? one_position++ : zero_position++;\n\
    \                next_keys[next_position] = current_keys[i];\n               \
    \ next_weights[next_position] = current_weights[i];\n            }\n         \
    \   current_keys.swap(next_keys);\n            current_weights.swap(next_weights);\n\
    \        }\n        _final_weights = Level(current_weights, 0xb7e15162U);\n  \
    \  }\n\n    void insert_encoded(int position, unsigned_type key, const Sum& weight)\
    \ {\n        for (int level = 0; level < BitWidth; level++) {\n            bool\
    \ one = bit(key, level);\n            int ones_before =\n                _levels[level].insert_with_rank(position,\
    \ one, weight);\n            int next_position;\n            if (one) {\n    \
    \            next_position = _zero_count[level] + ones_before;\n            }\
    \ else {\n                next_position = position - ones_before;\n          \
    \      _zero_count[level]++;\n            }\n            position = next_position;\n\
    \        }\n        _final_weights.insert_with_rank(position, false, weight);\n\
    \        _size++;\n    }\n\n    ErasedElement erase_encoded(int position) {\n\
    \        unsigned_type key = 0;\n        Sum weight{};\n        for (int level\
    \ = 0; level < BitWidth; level++) {\n            auto erased = _levels[level].erase_with_rank(position);\n\
    \            if (level == 0) weight = erased.weight;\n            int next_position;\n\
    \            if (erased.bit) {\n                key |= unsigned_type(1) << (BitWidth\
    \ - 1 - level);\n                next_position = _zero_count[level] + erased.ones_before;\n\
    \            } else {\n                next_position = position - erased.ones_before;\n\
    \                _zero_count[level]--;\n            }\n            position =\
    \ next_position;\n        }\n        _final_weights.erase_with_rank(position);\n\
    \        _size--;\n        return ErasedElement{key, weight};\n    }\n\n    int\
    \ count_less_encoded(int left, int right, unsigned_type upper) const {\n     \
    \   int result = 0;\n        for (int level = 0; level < BitWidth; level++) {\n\
    \            auto stats = _levels[level].prefix_stats_pair(left, right);\n   \
    \         int left_ones = stats.left.ones;\n            int right_ones = stats.right.ones;\n\
    \            if (bit(upper, level)) {\n                result += (right - left)\
    \ - (right_ones - left_ones);\n                left = _zero_count[level] + left_ones;\n\
    \                right = _zero_count[level] + right_ones;\n            } else\
    \ {\n                left -= left_ones;\n                right -= right_ones;\n\
    \            }\n        }\n        return result;\n    }\n\n    int count_less(int\
    \ left, int right, T upper) const {\n        if constexpr (BitWidth < full_bit_width)\
    \ {\n            if (!key_fits(upper)) return right - left;\n        }\n     \
    \   return count_less_encoded(left, right, encode_unchecked(upper));\n    }\n\n\
    \    Sum sum_less_encoded(int left, int right, unsigned_type upper) const {\n\
    \        Sum result{};\n        for (int level = 0; level < BitWidth; level++)\
    \ {\n            auto stats = _levels[level].prefix_stats_pair(left, right);\n\
    \            int left_ones = stats.left.ones;\n            int right_ones = stats.right.ones;\n\
    \            if (bit(upper, level)) {\n                result = result + range_zero(stats);\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            } else {\n                left\
    \ -= left_ones;\n                right -= right_ones;\n            }\n       \
    \ }\n        return result;\n    }\n\n    Sum sum_less(int left, int right, T\
    \ upper) const {\n        if constexpr (BitWidth < full_bit_width) {\n       \
    \     if (!key_fits(upper)) return range_sum(left, right);\n        }\n      \
    \  return sum_less_encoded(left, right, encode_unchecked(upper));\n    }\n\n \
    \  public:\n    DynamicWaveletMatrixSum() : _levels(BitWidth) {}\n\n    explicit\
    \ DynamicWaveletMatrixSum(const std::vector<T>& values)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        std::vector<Sum> weights;\n        weights.reserve(values.size());\n\
    \        for (T value : values) weights.push_back(static_cast<Sum>(value));\n\
    \        build(values, weights);\n    }\n\n    DynamicWaveletMatrixSum(\n    \
    \    const std::vector<T>& values,\n        const std::vector<Sum>& weights\n\
    \    ) {\n        build(values, weights);\n    }\n\n    int size() const {\n \
    \       return _size;\n    }\n\n    bool empty() const {\n        return _size\
    \ == 0;\n    }\n\n    void clear() {\n        *this = DynamicWaveletMatrixSum();\n\
    \    }\n\n    T access(int position) const {\n        assert(0 <= position &&\
    \ position < _size);\n        unsigned_type key = 0;\n        for (int level =\
    \ 0; level < BitWidth; level++) {\n            auto accessed = _levels[level].access_with_rank(position);\n\
    \            if (accessed.bit) {\n                key |= unsigned_type(1) << (BitWidth\
    \ - 1 - level);\n                position = _zero_count[level] + accessed.ones_before;\n\
    \            } else {\n                position -= accessed.ones_before;\n   \
    \         }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ position) const {\n        return access(position);\n    }\n\n    Sum weight(int\
    \ position) const {\n        assert(0 <= position && position < _size);\n    \
    \    return _levels[0].access_with_rank(position).weight;\n    }\n\n    std::pair<T,\
    \ Sum> get(int position) const {\n        assert(0 <= position && position < _size);\n\
    \        unsigned_type key = 0;\n        Sum result_weight{};\n        for (int\
    \ level = 0; level < BitWidth; level++) {\n            auto accessed = _levels[level].access_with_rank(position);\n\
    \            if (level == 0) result_weight = accessed.weight;\n            if\
    \ (accessed.bit) {\n                key |= unsigned_type(1) << (BitWidth - 1 -\
    \ level);\n                position = _zero_count[level] + accessed.ones_before;\n\
    \            } else {\n                position -= accessed.ones_before;\n   \
    \         }\n        }\n        return std::pair<T, Sum>(decode(key), result_weight);\n\
    \    }\n\n    void insert(int position, T value)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        insert(position, value, static_cast<Sum>(value));\n   \
    \ }\n\n    void insert(int position, T value, const Sum& weight) {\n        assert(0\
    \ <= position && position <= _size);\n        insert_encoded(position, encode_key(value),\
    \ weight);\n    }\n\n    void push_back(T value)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        insert(_size, value);\n    }\n\n    void push_back(T value,\
    \ const Sum& weight) {\n        insert(_size, value, weight);\n    }\n\n    std::pair<T,\
    \ Sum> erase(int position) {\n        assert(0 <= position && position < _size);\n\
    \        ErasedElement erased = erase_encoded(position);\n        return std::pair<T,\
    \ Sum>(decode(erased.key), erased.weight);\n    }\n\n    void set(int position,\
    \ T value)\n        requires std::convertible_to<T, Sum>\n    {\n        set(position,\
    \ value, static_cast<Sum>(value));\n    }\n\n    void set(int position, T value,\
    \ const Sum& weight) {\n        assert(0 <= position && position < _size);\n \
    \       unsigned_type key = encode_key(value);\n        erase_encoded(position);\n\
    \        insert_encoded(position, key, weight);\n    }\n\n    void set_value(int\
    \ position, T value) {\n        assert(0 <= position && position < _size);\n \
    \       unsigned_type key = encode_key(value);\n        ErasedElement erased =\
    \ erase_encoded(position);\n        insert_encoded(position, key, erased.weight);\n\
    \    }\n\n    void set_weight(int position, const Sum& new_weight) {\n       \
    \ assert(0 <= position && position < _size);\n        for (int level = 0; level\
    \ < BitWidth; level++) {\n            auto accessed =\n                _levels[level].set_weight_with_rank(position,\
    \ new_weight);\n            if (accessed.bit) {\n                position = _zero_count[level]\
    \ + accessed.ones_before;\n            } else {\n                position -= accessed.ones_before;\n\
    \            }\n        }\n        _final_weights.set_weight_with_rank(position,\
    \ new_weight);\n    }\n\n    void add_weight(int position, const Sum& delta) {\n\
    \        assert(0 <= position && position < _size);\n        for (int level =\
    \ 0; level < BitWidth; level++) {\n            auto accessed =\n             \
    \   _levels[level].add_weight_with_rank(position, delta);\n            if (accessed.bit)\
    \ {\n                position = _zero_count[level] + accessed.ones_before;\n \
    \           } else {\n                position -= accessed.ones_before;\n    \
    \        }\n        }\n        _final_weights.add_weight_with_rank(position, delta);\n\
    \    }\n\n    int rank(T value, int right) const {\n        assert(0 <= right\
    \ && right <= _size);\n        return rank(value, 0, right);\n    }\n\n    int\
    \ rank(T value, int left, int right) const {\n        assert(0 <= left && left\
    \ <= right && right <= _size);\n        if constexpr (BitWidth < full_bit_width)\
    \ {\n            if (!key_fits(value)) return 0;\n        }\n        unsigned_type\
    \ key = encode_unchecked(value);\n        for (int level = 0; level < BitWidth;\
    \ level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            if (bit(key, level)) {\n                left\
    \ = _zero_count[level] + left_ones;\n                right = _zero_count[level]\
    \ + right_ones;\n            } else {\n                left -= left_ones;\n  \
    \              right -= right_ones;\n            }\n        }\n        return\
    \ right - left;\n    }\n\n    T kth_smallest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        unsigned_type key = 0;\n        for (int\
    \ level = 0; level < BitWidth; level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            if (k < zeros) {\n                left = left_zeros;\n\
    \                right = right_zeros;\n            } else {\n                k\
    \ -= zeros;\n                key |= unsigned_type(1) << (BitWidth - 1 - level);\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            }\n        }\n        return\
    \ decode(key);\n    }\n\n    T kth_largest(int left, int right, int k) const {\n\
    \        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        return kth_smallest(left, right, right -\
    \ left - 1 - k);\n    }\n\n    int range_freq(int left, int right, T upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        return\
    \ count_less(left, right, upper);\n    }\n\n    int range_freq(int left, int right,\
    \ T lower, T upper) const {\n        assert(0 <= left && left <= right && right\
    \ <= _size);\n        if (upper <= lower) return 0;\n        return count_less(left,\
    \ right, upper) -\n               count_less(left, right, lower);\n    }\n\n \
    \   std::optional<T> prev_value(int left, int right, T upper) const {\n      \
    \  assert(0 <= left && left <= right && right <= _size);\n        int count =\
    \ range_freq(left, right, upper);\n        if (count == 0) return std::nullopt;\n\
    \        return kth_smallest(left, right, count - 1);\n    }\n\n    std::optional<T>\
    \ next_value(int left, int right, T lower) const {\n        assert(0 <= left &&\
    \ left <= right && right <= _size);\n        int count = range_freq(left, right,\
    \ lower);\n        if (count == right - left) return std::nullopt;\n        return\
    \ kth_smallest(left, right, count);\n    }\n\n    Sum range_sum(int left, int\
    \ right) const {\n        assert(0 <= left && left <= right && right <= _size);\n\
    \        return _levels[0].range_sum(left, right);\n    }\n\n    Sum range_sum(int\
    \ left, int right, T upper) const {\n        assert(0 <= left && left <= right\
    \ && right <= _size);\n        return sum_less(left, right, upper);\n    }\n\n\
    \    Sum range_sum(int left, int right, T lower, T upper) const {\n        assert(0\
    \ <= left && left <= right && right <= _size);\n        if (upper <= lower) return\
    \ Sum{};\n        return sum_less(left, right, upper) -\n               sum_less(left,\
    \ right, lower);\n    }\n\n    Sum sum_k_smallest(int left, int right, int k)\
    \ const {\n        assert(0 <= left && left <= right && right <= _size);\n   \
    \     assert(0 <= k && k <= right - left);\n        Sum result{};\n        for\
    \ (int level = 0; level < BitWidth; level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            if (k < zeros) {\n                left = left_zeros;\n\
    \                right = right_zeros;\n            } else {\n                result\
    \ = result + range_zero(stats);\n                k -= zeros;\n               \
    \ left = _zero_count[level] + left_ones;\n                right = _zero_count[level]\
    \ + right_ones;\n            }\n        }\n        return result + _final_weights.range_sum(left,\
    \ left + k);\n    }\n\n    Sum sum_k_largest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k <= right - left);\n        return range_sum(left, right) -\n     \
    \          sum_k_smallest(left, right, right - left - k);\n    }\n\n    template\
    \ <class Predicate>\n    int max_count_smallest(\n        int left,\n        int\
    \ right,\n        Predicate predicate\n    ) const {\n        assert(0 <= left\
    \ && left <= right && right <= _size);\n        assert(predicate(Sum{}));\n  \
    \      Sum result{};\n        int count = 0;\n        for (int level = 0; level\
    \ < BitWidth; level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            Sum candidate = result + range_zero(stats);\n   \
    \         if (predicate(candidate)) {\n                result = candidate;\n \
    \               count += zeros;\n                left = _zero_count[level] + left_ones;\n\
    \                right = _zero_count[level] + right_ones;\n            } else\
    \ {\n                left = left_zeros;\n                right = right_zeros;\n\
    \            }\n        }\n        return count +\n               _final_weights.max_prefix(\n\
    \                   left,\n                   right,\n                   result,\n\
    \                   predicate\n               );\n    }\n\n    template <class\
    \ Predicate>\n    int max_count_largest(\n        int left,\n        int right,\n\
    \        Predicate predicate\n    ) const {\n        assert(0 <= left && left\
    \ <= right && right <= _size);\n        assert(predicate(Sum{}));\n        Sum\
    \ result{};\n        int count = 0;\n        for (int level = 0; level < BitWidth;\
    \ level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int ones = right_ones\
    \ - left_ones;\n            Sum zero_result = range_zero(stats);\n           \
    \ Sum one_result = range_total(stats) - zero_result;\n            Sum candidate\
    \ = result + one_result;\n            if (predicate(candidate)) {\n          \
    \      result = candidate;\n                count += ones;\n                left\
    \ = left_zeros;\n                right = right_zeros;\n            } else {\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            }\n        }\n        return\
    \ count +\n               _final_weights.max_suffix(\n                   left,\n\
    \                   right,\n                   result,\n                   predicate\n\
    \               );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\n\
    #include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp\"\
    \n\n#line 13 \"verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp\"\n\
    \nnamespace {\n\nusing Matrix = m1une::ds::DynamicWaveletMatrixSum<int, long long>;\n\
    \nstd::uint64_t random_state = 0x6a09e667f3bcc909ULL;\n\nstd::uint64_t random_value()\
    \ {\n    random_state ^= random_state << 7;\n    random_state ^= random_state\
    \ >> 9;\n    return random_state;\n}\n\nint random_int(int lower, int upper) {\n\
    \    return lower + int(random_value() % std::uint64_t(upper - lower + 1));\n\
    }\n\nvoid check_queries(\n    const Matrix& matrix,\n    const std::vector<int>&\
    \ values,\n    const std::vector<long long>& weights\n) {\n    assert(values.size()\
    \ == weights.size());\n    assert(matrix.size() == int(values.size()));\n    assert(matrix.empty()\
    \ == values.empty());\n    for (int i = 0; i < int(values.size()); i++) {\n  \
    \      assert(matrix.access(i) == values[i]);\n        assert(matrix[i] == values[i]);\n\
    \        assert(matrix.weight(i) == weights[i]);\n        std::pair<int, long\
    \ long> expected(values[i], weights[i]);\n        assert(matrix.get(i) == expected);\n\
    \    }\n\n    int left = int(random_value() % (values.size() + 1));\n    int right\
    \ = int(random_value() % (values.size() + 1));\n    if (right < left) std::swap(left,\
    \ right);\n    int lower = random_int(-25, 25);\n    int upper = random_int(-25,\
    \ 25);\n    if (upper < lower) std::swap(lower, upper);\n\n    long long total\
    \ = 0;\n    long long below = 0;\n    long long between = 0;\n    int frequency\
    \ = 0;\n    std::vector<std::pair<int, int>> order;\n    for (int i = left; i\
    \ < right; i++) {\n        total += weights[i];\n        if (values[i] < upper)\
    \ below += weights[i];\n        if (lower <= values[i] && values[i] < upper) {\n\
    \            between += weights[i];\n            frequency++;\n        }\n   \
    \     order.emplace_back(values[i], i);\n    }\n    std::stable_sort(\n      \
    \  order.begin(),\n        order.end(),\n        [](const auto& first, const auto&\
    \ second) {\n            return first.first < second.first;\n        }\n    );\n\
    \n    assert(matrix.range_sum(left, right) == total);\n    assert(matrix.range_sum(left,\
    \ right, upper) == below);\n    assert(matrix.range_sum(left, right, lower, upper)\
    \ == between);\n    assert(matrix.range_freq(left, right, lower, upper) == frequency);\n\
    \n    long long smallest_sum = 0;\n    long long largest_sum = 0;\n    for (int\
    \ k = 0; k <= int(order.size()); k++) {\n        assert(matrix.sum_k_smallest(left,\
    \ right, k) == smallest_sum);\n        assert(matrix.sum_k_largest(left, right,\
    \ k) == largest_sum);\n        if (k < int(order.size())) {\n            smallest_sum\
    \ += weights[order[k].second];\n            largest_sum += weights[order[order.size()\
    \ - 1 - k].second];\n        }\n    }\n\n    if (!order.empty()) {\n        int\
    \ k = int(random_value() % order.size());\n        assert(matrix.kth_smallest(left,\
    \ right, k) == order[k].first);\n        assert(\n            matrix.kth_largest(left,\
    \ right, k) ==\n            order[order.size() - 1 - k].first\n        );\n  \
    \  }\n\n    int value = random_int(-20, 20);\n    assert(\n        matrix.rank(value,\
    \ left, right) ==\n        int(std::count(values.begin() + left, values.begin()\
    \ + right, value))\n    );\n    assert(\n        matrix.rank(value, right) ==\n\
    \        int(std::count(values.begin(), values.begin() + right, value))\n    );\n\
    \n    std::optional<int> previous;\n    std::optional<int> next;\n    for (int\
    \ i = left; i < right; i++) {\n        if (values[i] < upper &&\n            (!previous.has_value()\
    \ || previous.value() < values[i])) {\n            previous = values[i];\n   \
    \     }\n        if (lower <= values[i] &&\n            (!next.has_value() ||\
    \ values[i] < next.value())) {\n            next = values[i];\n        }\n   \
    \ }\n    assert(matrix.prev_value(left, right, upper) == previous);\n    assert(matrix.next_value(left,\
    \ right, lower) == next);\n}\n\nvoid test_randomized() {\n    std::vector<int>\
    \ default_values;\n    default_values.push_back(std::numeric_limits<int>::min());\n\
    \    default_values.push_back(-2);\n    default_values.push_back(0);\n    default_values.push_back(std::numeric_limits<int>::max());\n\
    \    m1une::ds::DynamicWaveletMatrixSum<int, long long> default_matrix(\n    \
    \    default_values\n    );\n    assert(\n        default_matrix.range_sum(0,\
    \ 4) ==\n        static_cast<long long>(std::numeric_limits<int>::min()) - 2 +\n\
    \            std::numeric_limits<int>::max()\n    );\n    default_matrix.set(1,\
    \ 10);\n    assert(default_matrix.weight(1) == 10);\n    default_matrix.insert(2,\
    \ -7);\n    assert(default_matrix.weight(2) == -7);\n\n    std::vector<unsigned\
    \ long long> unsigned_values;\n    unsigned_values.push_back(0);\n    unsigned_values.push_back(std::numeric_limits<unsigned\
    \ long long>::max());\n    std::vector<long long> unsigned_weights;\n    unsigned_weights.push_back(3);\n\
    \    unsigned_weights.push_back(4);\n    m1une::ds::DynamicWaveletMatrixSum<unsigned\
    \ long long, long long>\n        unsigned_matrix(unsigned_values, unsigned_weights);\n\
    \    assert(unsigned_matrix.kth_largest(0, 2, 0) == unsigned_values[1]);\n   \
    \ assert(unsigned_matrix.range_sum(0, 2) == 7);\n    unsigned_matrix.clear();\n\
    \    assert(unsigned_matrix.empty());\n\n    for (int trial = 0; trial < 80; trial++)\
    \ {\n        int initial_size = random_int(0, 60);\n        std::vector<int> values(initial_size);\n\
    \        std::vector<long long> weights(initial_size);\n        for (int i = 0;\
    \ i < initial_size; i++) {\n            values[i] = random_int(-20, 20);\n   \
    \         weights[i] = random_int(-50, 50);\n        }\n        Matrix matrix(values,\
    \ weights);\n\n        for (int operation = 0; operation < 220; operation++) {\n\
    \            int type = int(random_value() % 8);\n            if (values.empty())\
    \ type = 0;\n            if (type == 0) {\n                int position = int(random_value()\
    \ % (values.size() + 1));\n                int value = random_int(-20, 20);\n\
    \                long long weight = random_int(-50, 50);\n                values.insert(values.begin()\
    \ + position, value);\n                weights.insert(weights.begin() + position,\
    \ weight);\n                matrix.insert(position, value, weight);\n        \
    \    } else if (type == 1) {\n                int position = int(random_value()\
    \ % values.size());\n                std::pair<int, long long> expected(\n   \
    \                 values[position],\n                    weights[position]\n \
    \               );\n                values.erase(values.begin() + position);\n\
    \                weights.erase(weights.begin() + position);\n                assert(matrix.erase(position)\
    \ == expected);\n            } else if (type == 2) {\n                int position\
    \ = int(random_value() % values.size());\n                int value = random_int(-20,\
    \ 20);\n                long long weight = random_int(-50, 50);\n            \
    \    values[position] = value;\n                weights[position] = weight;\n\
    \                matrix.set(position, value, weight);\n            } else if (type\
    \ == 3) {\n                int position = int(random_value() % values.size());\n\
    \                int value = random_int(-20, 20);\n                values[position]\
    \ = value;\n                matrix.set_value(position, value);\n            }\
    \ else if (type == 4) {\n                int position = int(random_value() % values.size());\n\
    \                long long weight = random_int(-50, 50);\n                weights[position]\
    \ = weight;\n                matrix.set_weight(position, weight);\n          \
    \  } else if (type == 5) {\n                int position = int(random_value()\
    \ % values.size());\n                long long delta = random_int(-20, 20);\n\
    \                weights[position] += delta;\n                matrix.add_weight(position,\
    \ delta);\n            } else if (type == 6) {\n                int value = random_int(-20,\
    \ 20);\n                values.push_back(value);\n                weights.push_back(value);\n\
    \                matrix.push_back(value);\n            } else {\n            \
    \    int position = int(random_value() % values.size());\n                int\
    \ value = random_int(-20, 20);\n                values[position] = value;\n  \
    \              weights[position] = value;\n                matrix.set(position,\
    \ value);\n            }\n            check_queries(matrix, values, weights);\n\
    \        }\n    }\n\n    std::vector<int> values(700);\n    std::vector<long long>\
    \ weights(700);\n    for (int i = 0; i < int(values.size()); i++) {\n        values[i]\
    \ = random_int(-100, 100);\n        weights[i] = random_int(-1000, 1000);\n  \
    \  }\n    Matrix matrix(values, weights);\n    for (int operation = 0; operation\
    \ < 2500; operation++) {\n        int from = int(random_value() % values.size());\n\
    \        int to = int(random_value() % values.size());\n        int value = values[from];\n\
    \        long long weight = weights[from];\n        values.erase(values.begin()\
    \ + from);\n        weights.erase(weights.begin() + from);\n        std::pair<int,\
    \ long long> expected(value, weight);\n        assert(matrix.erase(from) == expected);\n\
    \        values.insert(values.begin() + to, value);\n        weights.insert(weights.begin()\
    \ + to, weight);\n        matrix.insert(to, value, weight);\n        if (operation\
    \ % 25 == 0) check_queries(matrix, values, weights);\n    }\n}\n\nvoid test_boundary_search()\
    \ {\n    {\n        std::vector<int> equal_values(700, 7);\n        std::vector<long\
    \ long> equal_weights(700);\n        for (int i = 0; i < int(equal_weights.size());\
    \ i++) {\n            equal_weights[i] = i % 17 + 1;\n        }\n        Matrix\
    \ equal_matrix(equal_values, equal_weights);\n        for (int operation = 0;\
    \ operation < 300; operation++) {\n            int type = int(random_value() %\
    \ 3);\n            if (type == 0) {\n                int position =\n        \
    \            int(random_value() % (equal_values.size() + 1));\n              \
    \  long long weight = random_int(1, 20);\n                equal_values.insert(equal_values.begin()\
    \ + position, 7);\n                equal_weights.insert(\n                   \
    \ equal_weights.begin() + position,\n                    weight\n            \
    \    );\n                equal_matrix.insert(position, 7, weight);\n         \
    \   } else if (type == 1 && equal_values.size() > 300) {\n                int\
    \ position = int(random_value() % equal_values.size());\n                equal_values.erase(equal_values.begin()\
    \ + position);\n                equal_weights.erase(equal_weights.begin() + position);\n\
    \                equal_matrix.erase(position);\n            } else {\n       \
    \         int position = int(random_value() % equal_values.size());\n        \
    \        equal_weights[position] = random_int(1, 20);\n                equal_matrix.set_weight(position,\
    \ equal_weights[position]);\n            }\n\n            int left = int(random_value()\
    \ % (equal_values.size() + 1));\n            int right = int(random_value() %\
    \ (equal_values.size() + 1));\n            if (right < left) std::swap(left, right);\n\
    \            long long total = 0;\n            for (int i = left; i < right; i++)\
    \ total += equal_weights[i];\n            long long limit = static_cast<long long>(\n\
    \                random_value() % std::uint64_t(total + 21)\n            );\n\
    \            auto predicate = [limit](long long sum) {\n                return\
    \ sum <= limit;\n            };\n\n            long long sum = 0;\n          \
    \  int smallest = 0;\n            while (left + smallest < right &&\n        \
    \           sum + equal_weights[left + smallest] <= limit) {\n               \
    \ sum += equal_weights[left + smallest];\n                smallest++;\n      \
    \      }\n            assert(\n                equal_matrix.max_count_smallest(\n\
    \                    left,\n                    right,\n                    predicate\n\
    \                ) == smallest\n            );\n\n            sum = 0;\n     \
    \       int largest = 0;\n            while (left + largest < right &&\n     \
    \              sum + equal_weights[right - 1 - largest] <= limit) {\n        \
    \        sum += equal_weights[right - 1 - largest];\n                largest++;\n\
    \            }\n            assert(\n                equal_matrix.max_count_largest(left,\
    \ right, predicate) ==\n                largest\n            );\n        }\n \
    \   }\n\n    std::vector<int> values(700);\n    std::vector<long long> weights(700);\n\
    \    for (int i = 0; i < int(values.size()); i++) {\n        values[i] = random_int(-30,\
    \ 30);\n        weights[i] = random_int(1, 20);\n    }\n    Matrix matrix(values,\
    \ weights);\n\n    for (int operation = 0; operation < 700; operation++) {\n \
    \       int type = int(random_value() % 4);\n        if (type == 0) {\n      \
    \      int position = int(random_value() % (values.size() + 1));\n           \
    \ int value = random_int(-30, 30);\n            long long weight = random_int(1,\
    \ 20);\n            values.insert(values.begin() + position, value);\n       \
    \     weights.insert(weights.begin() + position, weight);\n            matrix.insert(position,\
    \ value, weight);\n        } else if (type == 1 && values.size() > 300) {\n  \
    \          int position = int(random_value() % values.size());\n            values.erase(values.begin()\
    \ + position);\n            weights.erase(weights.begin() + position);\n     \
    \       matrix.erase(position);\n        } else if (type == 2) {\n           \
    \ int position = int(random_value() % values.size());\n            values[position]\
    \ = random_int(-30, 30);\n            matrix.set_value(position, values[position]);\n\
    \        } else {\n            int position = int(random_value() % values.size());\n\
    \            weights[position] = random_int(1, 20);\n            matrix.set_weight(position,\
    \ weights[position]);\n        }\n\n        int left = int(random_value() % (values.size()\
    \ + 1));\n        int right = int(random_value() % (values.size() + 1));\n   \
    \     if (right < left) std::swap(left, right);\n        std::vector<std::pair<int,\
    \ int>> order;\n        long long total = 0;\n        for (int i = left; i < right;\
    \ i++) {\n            order.emplace_back(values[i], i);\n            total +=\
    \ weights[i];\n        }\n        std::stable_sort(\n            order.begin(),\n\
    \            order.end(),\n            [](const auto& first, const auto& second)\
    \ {\n                return first.first < second.first;\n            }\n     \
    \   );\n        long long limit = static_cast<long long>(\n            random_value()\
    \ % std::uint64_t(total + 21)\n        );\n        auto predicate = [limit](long\
    \ long sum) { return sum <= limit; };\n\n        long long sum = 0;\n        int\
    \ smallest = 0;\n        while (smallest < int(order.size()) &&\n            \
    \   sum + weights[order[smallest].second] <= limit) {\n            sum += weights[order[smallest].second];\n\
    \            smallest++;\n        }\n        assert(\n            matrix.max_count_smallest(left,\
    \ right, predicate) == smallest\n        );\n\n        sum = 0;\n        int largest\
    \ = 0;\n        while (largest < int(order.size()) &&\n               sum + weights[order[order.size()\
    \ - 1 - largest].second] <=\n                   limit) {\n            sum += weights[order[order.size()\
    \ - 1 - largest].second];\n            largest++;\n        }\n        assert(matrix.max_count_largest(left,\
    \ right, predicate) == largest);\n    }\n}\n\nstruct Point {\n    int x = 0;\n\
    \    int y = 0;\n    long long weight = 0;\n    int query_index = -1;\n};\n\n\
    struct Query {\n    int type = 0;\n    int first = 0;\n    int second = 0;\n \
    \   int third = 0;\n    int fourth = 0;\n    long long weight = 0;\n    int position\
    \ = -1;\n};\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \    test_boundary_search();\n\n    int point_count = 0;\n    int query_count\
    \ = 0;\n    fast_input >> point_count >> query_count;\n    std::vector<Point>\
    \ points(point_count);\n    for (Point& point : points) {\n        fast_input\
    \ >> point.x >> point.y >> point.weight;\n    }\n\n    std::vector<Query> queries(query_count);\n\
    \    for (int query_index = 0; query_index < query_count; query_index++) {\n \
    \       Query& query = queries[query_index];\n        fast_input >> query.type;\n\
    \        if (query.type == 0) {\n            fast_input >> query.first >> query.second\
    \ >> query.weight;\n            Point point;\n            point.x = query.first;\n\
    \            point.y = query.second;\n            point.query_index = query_index;\n\
    \            points.push_back(point);\n        } else {\n            fast_input\
    \ >> query.first >> query.second >> query.third >>\n                query.fourth;\n\
    \        }\n    }\n\n    std::stable_sort(\n        points.begin(),\n        points.end(),\n\
    \        [](const Point& first, const Point& second) {\n            return first.x\
    \ < second.x;\n        }\n    );\n    std::vector<int> xs(points.size());\n  \
    \  std::vector<int> ys(points.size());\n    std::vector<long long> weights(points.size());\n\
    \    for (int i = 0; i < int(points.size()); i++) {\n        xs[i] = points[i].x;\n\
    \        ys[i] = points[i].y;\n        weights[i] = points[i].weight;\n      \
    \  if (points[i].query_index != -1) {\n            queries[points[i].query_index].position\
    \ = i;\n        }\n    }\n\n    Matrix matrix(ys, weights);\n    for (const Query&\
    \ query : queries) {\n        if (query.type == 0) {\n            matrix.set_weight(query.position,\
    \ query.weight);\n        } else {\n            int left = int(std::lower_bound(\n\
    \                               xs.begin(),\n                               xs.end(),\n\
    \                               query.first\n                           ) -\n\
    \                           xs.begin());\n            int right = int(std::lower_bound(\n\
    \                                xs.begin(),\n                               \
    \ xs.end(),\n                                query.third\n                   \
    \         ) -\n                            xs.begin());\n            fast_output\
    \ << matrix.range_sum(\n                               left,\n               \
    \                right,\n                               query.second,\n      \
    \                         query.fourth\n                           )\n       \
    \                 << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <limits>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nusing Matrix = m1une::ds::DynamicWaveletMatrixSum<int,\
    \ long long>;\n\nstd::uint64_t random_state = 0x6a09e667f3bcc909ULL;\n\nstd::uint64_t\
    \ random_value() {\n    random_state ^= random_state << 7;\n    random_state ^=\
    \ random_state >> 9;\n    return random_state;\n}\n\nint random_int(int lower,\
    \ int upper) {\n    return lower + int(random_value() % std::uint64_t(upper -\
    \ lower + 1));\n}\n\nvoid check_queries(\n    const Matrix& matrix,\n    const\
    \ std::vector<int>& values,\n    const std::vector<long long>& weights\n) {\n\
    \    assert(values.size() == weights.size());\n    assert(matrix.size() == int(values.size()));\n\
    \    assert(matrix.empty() == values.empty());\n    for (int i = 0; i < int(values.size());\
    \ i++) {\n        assert(matrix.access(i) == values[i]);\n        assert(matrix[i]\
    \ == values[i]);\n        assert(matrix.weight(i) == weights[i]);\n        std::pair<int,\
    \ long long> expected(values[i], weights[i]);\n        assert(matrix.get(i) ==\
    \ expected);\n    }\n\n    int left = int(random_value() % (values.size() + 1));\n\
    \    int right = int(random_value() % (values.size() + 1));\n    if (right < left)\
    \ std::swap(left, right);\n    int lower = random_int(-25, 25);\n    int upper\
    \ = random_int(-25, 25);\n    if (upper < lower) std::swap(lower, upper);\n\n\
    \    long long total = 0;\n    long long below = 0;\n    long long between = 0;\n\
    \    int frequency = 0;\n    std::vector<std::pair<int, int>> order;\n    for\
    \ (int i = left; i < right; i++) {\n        total += weights[i];\n        if (values[i]\
    \ < upper) below += weights[i];\n        if (lower <= values[i] && values[i] <\
    \ upper) {\n            between += weights[i];\n            frequency++;\n   \
    \     }\n        order.emplace_back(values[i], i);\n    }\n    std::stable_sort(\n\
    \        order.begin(),\n        order.end(),\n        [](const auto& first, const\
    \ auto& second) {\n            return first.first < second.first;\n        }\n\
    \    );\n\n    assert(matrix.range_sum(left, right) == total);\n    assert(matrix.range_sum(left,\
    \ right, upper) == below);\n    assert(matrix.range_sum(left, right, lower, upper)\
    \ == between);\n    assert(matrix.range_freq(left, right, lower, upper) == frequency);\n\
    \n    long long smallest_sum = 0;\n    long long largest_sum = 0;\n    for (int\
    \ k = 0; k <= int(order.size()); k++) {\n        assert(matrix.sum_k_smallest(left,\
    \ right, k) == smallest_sum);\n        assert(matrix.sum_k_largest(left, right,\
    \ k) == largest_sum);\n        if (k < int(order.size())) {\n            smallest_sum\
    \ += weights[order[k].second];\n            largest_sum += weights[order[order.size()\
    \ - 1 - k].second];\n        }\n    }\n\n    if (!order.empty()) {\n        int\
    \ k = int(random_value() % order.size());\n        assert(matrix.kth_smallest(left,\
    \ right, k) == order[k].first);\n        assert(\n            matrix.kth_largest(left,\
    \ right, k) ==\n            order[order.size() - 1 - k].first\n        );\n  \
    \  }\n\n    int value = random_int(-20, 20);\n    assert(\n        matrix.rank(value,\
    \ left, right) ==\n        int(std::count(values.begin() + left, values.begin()\
    \ + right, value))\n    );\n    assert(\n        matrix.rank(value, right) ==\n\
    \        int(std::count(values.begin(), values.begin() + right, value))\n    );\n\
    \n    std::optional<int> previous;\n    std::optional<int> next;\n    for (int\
    \ i = left; i < right; i++) {\n        if (values[i] < upper &&\n            (!previous.has_value()\
    \ || previous.value() < values[i])) {\n            previous = values[i];\n   \
    \     }\n        if (lower <= values[i] &&\n            (!next.has_value() ||\
    \ values[i] < next.value())) {\n            next = values[i];\n        }\n   \
    \ }\n    assert(matrix.prev_value(left, right, upper) == previous);\n    assert(matrix.next_value(left,\
    \ right, lower) == next);\n}\n\nvoid test_randomized() {\n    std::vector<int>\
    \ default_values;\n    default_values.push_back(std::numeric_limits<int>::min());\n\
    \    default_values.push_back(-2);\n    default_values.push_back(0);\n    default_values.push_back(std::numeric_limits<int>::max());\n\
    \    m1une::ds::DynamicWaveletMatrixSum<int, long long> default_matrix(\n    \
    \    default_values\n    );\n    assert(\n        default_matrix.range_sum(0,\
    \ 4) ==\n        static_cast<long long>(std::numeric_limits<int>::min()) - 2 +\n\
    \            std::numeric_limits<int>::max()\n    );\n    default_matrix.set(1,\
    \ 10);\n    assert(default_matrix.weight(1) == 10);\n    default_matrix.insert(2,\
    \ -7);\n    assert(default_matrix.weight(2) == -7);\n\n    std::vector<unsigned\
    \ long long> unsigned_values;\n    unsigned_values.push_back(0);\n    unsigned_values.push_back(std::numeric_limits<unsigned\
    \ long long>::max());\n    std::vector<long long> unsigned_weights;\n    unsigned_weights.push_back(3);\n\
    \    unsigned_weights.push_back(4);\n    m1une::ds::DynamicWaveletMatrixSum<unsigned\
    \ long long, long long>\n        unsigned_matrix(unsigned_values, unsigned_weights);\n\
    \    assert(unsigned_matrix.kth_largest(0, 2, 0) == unsigned_values[1]);\n   \
    \ assert(unsigned_matrix.range_sum(0, 2) == 7);\n    unsigned_matrix.clear();\n\
    \    assert(unsigned_matrix.empty());\n\n    for (int trial = 0; trial < 80; trial++)\
    \ {\n        int initial_size = random_int(0, 60);\n        std::vector<int> values(initial_size);\n\
    \        std::vector<long long> weights(initial_size);\n        for (int i = 0;\
    \ i < initial_size; i++) {\n            values[i] = random_int(-20, 20);\n   \
    \         weights[i] = random_int(-50, 50);\n        }\n        Matrix matrix(values,\
    \ weights);\n\n        for (int operation = 0; operation < 220; operation++) {\n\
    \            int type = int(random_value() % 8);\n            if (values.empty())\
    \ type = 0;\n            if (type == 0) {\n                int position = int(random_value()\
    \ % (values.size() + 1));\n                int value = random_int(-20, 20);\n\
    \                long long weight = random_int(-50, 50);\n                values.insert(values.begin()\
    \ + position, value);\n                weights.insert(weights.begin() + position,\
    \ weight);\n                matrix.insert(position, value, weight);\n        \
    \    } else if (type == 1) {\n                int position = int(random_value()\
    \ % values.size());\n                std::pair<int, long long> expected(\n   \
    \                 values[position],\n                    weights[position]\n \
    \               );\n                values.erase(values.begin() + position);\n\
    \                weights.erase(weights.begin() + position);\n                assert(matrix.erase(position)\
    \ == expected);\n            } else if (type == 2) {\n                int position\
    \ = int(random_value() % values.size());\n                int value = random_int(-20,\
    \ 20);\n                long long weight = random_int(-50, 50);\n            \
    \    values[position] = value;\n                weights[position] = weight;\n\
    \                matrix.set(position, value, weight);\n            } else if (type\
    \ == 3) {\n                int position = int(random_value() % values.size());\n\
    \                int value = random_int(-20, 20);\n                values[position]\
    \ = value;\n                matrix.set_value(position, value);\n            }\
    \ else if (type == 4) {\n                int position = int(random_value() % values.size());\n\
    \                long long weight = random_int(-50, 50);\n                weights[position]\
    \ = weight;\n                matrix.set_weight(position, weight);\n          \
    \  } else if (type == 5) {\n                int position = int(random_value()\
    \ % values.size());\n                long long delta = random_int(-20, 20);\n\
    \                weights[position] += delta;\n                matrix.add_weight(position,\
    \ delta);\n            } else if (type == 6) {\n                int value = random_int(-20,\
    \ 20);\n                values.push_back(value);\n                weights.push_back(value);\n\
    \                matrix.push_back(value);\n            } else {\n            \
    \    int position = int(random_value() % values.size());\n                int\
    \ value = random_int(-20, 20);\n                values[position] = value;\n  \
    \              weights[position] = value;\n                matrix.set(position,\
    \ value);\n            }\n            check_queries(matrix, values, weights);\n\
    \        }\n    }\n\n    std::vector<int> values(700);\n    std::vector<long long>\
    \ weights(700);\n    for (int i = 0; i < int(values.size()); i++) {\n        values[i]\
    \ = random_int(-100, 100);\n        weights[i] = random_int(-1000, 1000);\n  \
    \  }\n    Matrix matrix(values, weights);\n    for (int operation = 0; operation\
    \ < 2500; operation++) {\n        int from = int(random_value() % values.size());\n\
    \        int to = int(random_value() % values.size());\n        int value = values[from];\n\
    \        long long weight = weights[from];\n        values.erase(values.begin()\
    \ + from);\n        weights.erase(weights.begin() + from);\n        std::pair<int,\
    \ long long> expected(value, weight);\n        assert(matrix.erase(from) == expected);\n\
    \        values.insert(values.begin() + to, value);\n        weights.insert(weights.begin()\
    \ + to, weight);\n        matrix.insert(to, value, weight);\n        if (operation\
    \ % 25 == 0) check_queries(matrix, values, weights);\n    }\n}\n\nvoid test_boundary_search()\
    \ {\n    {\n        std::vector<int> equal_values(700, 7);\n        std::vector<long\
    \ long> equal_weights(700);\n        for (int i = 0; i < int(equal_weights.size());\
    \ i++) {\n            equal_weights[i] = i % 17 + 1;\n        }\n        Matrix\
    \ equal_matrix(equal_values, equal_weights);\n        for (int operation = 0;\
    \ operation < 300; operation++) {\n            int type = int(random_value() %\
    \ 3);\n            if (type == 0) {\n                int position =\n        \
    \            int(random_value() % (equal_values.size() + 1));\n              \
    \  long long weight = random_int(1, 20);\n                equal_values.insert(equal_values.begin()\
    \ + position, 7);\n                equal_weights.insert(\n                   \
    \ equal_weights.begin() + position,\n                    weight\n            \
    \    );\n                equal_matrix.insert(position, 7, weight);\n         \
    \   } else if (type == 1 && equal_values.size() > 300) {\n                int\
    \ position = int(random_value() % equal_values.size());\n                equal_values.erase(equal_values.begin()\
    \ + position);\n                equal_weights.erase(equal_weights.begin() + position);\n\
    \                equal_matrix.erase(position);\n            } else {\n       \
    \         int position = int(random_value() % equal_values.size());\n        \
    \        equal_weights[position] = random_int(1, 20);\n                equal_matrix.set_weight(position,\
    \ equal_weights[position]);\n            }\n\n            int left = int(random_value()\
    \ % (equal_values.size() + 1));\n            int right = int(random_value() %\
    \ (equal_values.size() + 1));\n            if (right < left) std::swap(left, right);\n\
    \            long long total = 0;\n            for (int i = left; i < right; i++)\
    \ total += equal_weights[i];\n            long long limit = static_cast<long long>(\n\
    \                random_value() % std::uint64_t(total + 21)\n            );\n\
    \            auto predicate = [limit](long long sum) {\n                return\
    \ sum <= limit;\n            };\n\n            long long sum = 0;\n          \
    \  int smallest = 0;\n            while (left + smallest < right &&\n        \
    \           sum + equal_weights[left + smallest] <= limit) {\n               \
    \ sum += equal_weights[left + smallest];\n                smallest++;\n      \
    \      }\n            assert(\n                equal_matrix.max_count_smallest(\n\
    \                    left,\n                    right,\n                    predicate\n\
    \                ) == smallest\n            );\n\n            sum = 0;\n     \
    \       int largest = 0;\n            while (left + largest < right &&\n     \
    \              sum + equal_weights[right - 1 - largest] <= limit) {\n        \
    \        sum += equal_weights[right - 1 - largest];\n                largest++;\n\
    \            }\n            assert(\n                equal_matrix.max_count_largest(left,\
    \ right, predicate) ==\n                largest\n            );\n        }\n \
    \   }\n\n    std::vector<int> values(700);\n    std::vector<long long> weights(700);\n\
    \    for (int i = 0; i < int(values.size()); i++) {\n        values[i] = random_int(-30,\
    \ 30);\n        weights[i] = random_int(1, 20);\n    }\n    Matrix matrix(values,\
    \ weights);\n\n    for (int operation = 0; operation < 700; operation++) {\n \
    \       int type = int(random_value() % 4);\n        if (type == 0) {\n      \
    \      int position = int(random_value() % (values.size() + 1));\n           \
    \ int value = random_int(-30, 30);\n            long long weight = random_int(1,\
    \ 20);\n            values.insert(values.begin() + position, value);\n       \
    \     weights.insert(weights.begin() + position, weight);\n            matrix.insert(position,\
    \ value, weight);\n        } else if (type == 1 && values.size() > 300) {\n  \
    \          int position = int(random_value() % values.size());\n            values.erase(values.begin()\
    \ + position);\n            weights.erase(weights.begin() + position);\n     \
    \       matrix.erase(position);\n        } else if (type == 2) {\n           \
    \ int position = int(random_value() % values.size());\n            values[position]\
    \ = random_int(-30, 30);\n            matrix.set_value(position, values[position]);\n\
    \        } else {\n            int position = int(random_value() % values.size());\n\
    \            weights[position] = random_int(1, 20);\n            matrix.set_weight(position,\
    \ weights[position]);\n        }\n\n        int left = int(random_value() % (values.size()\
    \ + 1));\n        int right = int(random_value() % (values.size() + 1));\n   \
    \     if (right < left) std::swap(left, right);\n        std::vector<std::pair<int,\
    \ int>> order;\n        long long total = 0;\n        for (int i = left; i < right;\
    \ i++) {\n            order.emplace_back(values[i], i);\n            total +=\
    \ weights[i];\n        }\n        std::stable_sort(\n            order.begin(),\n\
    \            order.end(),\n            [](const auto& first, const auto& second)\
    \ {\n                return first.first < second.first;\n            }\n     \
    \   );\n        long long limit = static_cast<long long>(\n            random_value()\
    \ % std::uint64_t(total + 21)\n        );\n        auto predicate = [limit](long\
    \ long sum) { return sum <= limit; };\n\n        long long sum = 0;\n        int\
    \ smallest = 0;\n        while (smallest < int(order.size()) &&\n            \
    \   sum + weights[order[smallest].second] <= limit) {\n            sum += weights[order[smallest].second];\n\
    \            smallest++;\n        }\n        assert(\n            matrix.max_count_smallest(left,\
    \ right, predicate) == smallest\n        );\n\n        sum = 0;\n        int largest\
    \ = 0;\n        while (largest < int(order.size()) &&\n               sum + weights[order[order.size()\
    \ - 1 - largest].second] <=\n                   limit) {\n            sum += weights[order[order.size()\
    \ - 1 - largest].second];\n            largest++;\n        }\n        assert(matrix.max_count_largest(left,\
    \ right, predicate) == largest);\n    }\n}\n\nstruct Point {\n    int x = 0;\n\
    \    int y = 0;\n    long long weight = 0;\n    int query_index = -1;\n};\n\n\
    struct Query {\n    int type = 0;\n    int first = 0;\n    int second = 0;\n \
    \   int third = 0;\n    int fourth = 0;\n    long long weight = 0;\n    int position\
    \ = -1;\n};\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \    test_boundary_search();\n\n    int point_count = 0;\n    int query_count\
    \ = 0;\n    fast_input >> point_count >> query_count;\n    std::vector<Point>\
    \ points(point_count);\n    for (Point& point : points) {\n        fast_input\
    \ >> point.x >> point.y >> point.weight;\n    }\n\n    std::vector<Query> queries(query_count);\n\
    \    for (int query_index = 0; query_index < query_count; query_index++) {\n \
    \       Query& query = queries[query_index];\n        fast_input >> query.type;\n\
    \        if (query.type == 0) {\n            fast_input >> query.first >> query.second\
    \ >> query.weight;\n            Point point;\n            point.x = query.first;\n\
    \            point.y = query.second;\n            point.query_index = query_index;\n\
    \            points.push_back(point);\n        } else {\n            fast_input\
    \ >> query.first >> query.second >> query.third >>\n                query.fourth;\n\
    \        }\n    }\n\n    std::stable_sort(\n        points.begin(),\n        points.end(),\n\
    \        [](const Point& first, const Point& second) {\n            return first.x\
    \ < second.x;\n        }\n    );\n    std::vector<int> xs(points.size());\n  \
    \  std::vector<int> ys(points.size());\n    std::vector<long long> weights(points.size());\n\
    \    for (int i = 0; i < int(points.size()); i++) {\n        xs[i] = points[i].x;\n\
    \        ys[i] = points[i].y;\n        weights[i] = points[i].weight;\n      \
    \  if (points[i].query_index != -1) {\n            queries[points[i].query_index].position\
    \ = i;\n        }\n    }\n\n    Matrix matrix(ys, weights);\n    for (const Query&\
    \ query : queries) {\n        if (query.type == 0) {\n            matrix.set_weight(query.position,\
    \ query.weight);\n        } else {\n            int left = int(std::lower_bound(\n\
    \                               xs.begin(),\n                               xs.end(),\n\
    \                               query.first\n                           ) -\n\
    \                           xs.begin());\n            int right = int(std::lower_bound(\n\
    \                                xs.begin(),\n                               \
    \ xs.end(),\n                                query.third\n                   \
    \         ) -\n                            xs.begin());\n            fast_output\
    \ << matrix.range_sum(\n                               left,\n               \
    \                right,\n                               query.second,\n      \
    \                         query.fourth\n                           )\n       \
    \                 << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
  - ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-19 03:02:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
- /verify/verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp.html
title: verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
---
