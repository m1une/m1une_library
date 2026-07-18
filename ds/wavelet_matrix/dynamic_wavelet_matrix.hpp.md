---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
    title: Dynamic Wavelet Matrix with Sums
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/wavelet_matrix/dynamic_wavelet_matrix.test.cpp
    title: verify/ds/wavelet_matrix/dynamic_wavelet_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
    title: verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/wavelet_matrix/dynamic_wavelet_matrix.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <bit>\n#include <cassert>\n#include\
    \ <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\nnamespace dynamic_wavelet_matrix_detail {\n\n// A dynamic bit\
    \ vector stored as an implicit treap of small packed chunks.\nclass DynamicRankBitVector\
    \ {\n   private:\n    static constexpr int word_bits = 64;\n    static constexpr\
    \ int chunk_words = 4;\n    static constexpr int chunk_capacity = word_bits *\
    \ chunk_words;\n    static constexpr int minimum_chunk_size = chunk_capacity /\
    \ 2;\n\n    struct Node {\n        std::array<std::uint64_t, chunk_words> bits{};\n\
    \        std::uint32_t priority = 0;\n        int left = 0;\n        int right\
    \ = 0;\n        int subtree_size = 0;\n        int subtree_ones = 0;\n       \
    \ std::uint16_t length = 0;\n        std::uint16_t chunk_ones = 0;\n    };\n\n\
    \    std::vector<Node> _nodes;\n    std::vector<int> _free_nodes;\n    int _root\
    \ = 0;\n    std::uint32_t _random_state = 1;\n\n    int size_of(int node) const\
    \ {\n        return _nodes[node].subtree_size;\n    }\n\n    int ones_of(int node)\
    \ const {\n        return _nodes[node].subtree_ones;\n    }\n\n    std::uint32_t\
    \ next_priority() {\n        _random_state ^= _random_state << 13;\n        _random_state\
    \ ^= _random_state >> 17;\n        _random_state ^= _random_state << 5;\n    \
    \    if (_random_state == 0) _random_state = 1;\n        return _random_state;\n\
    \    }\n\n    void update(int node) {\n        if (node == 0) return;\n      \
    \  _nodes[node].subtree_size =\n            size_of(_nodes[node].left) + int(_nodes[node].length)\
    \ +\n            size_of(_nodes[node].right);\n        _nodes[node].subtree_ones\
    \ =\n            ones_of(_nodes[node].left) + int(_nodes[node].chunk_ones) +\n\
    \            ones_of(_nodes[node].right);\n    }\n\n    bool local_get(int node,\
    \ int position) const {\n        return (_nodes[node].bits[position / word_bits]\
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
    \            }\n        }\n        update(node);\n    }\n\n    int insert_impl(int\
    \ tree, int position, bool value) {\n        if (tree == 0) {\n            int\
    \ node = new_node();\n            local_insert(node, 0, value);\n            return\
    \ node;\n        }\n\n        int left_size = size_of(_nodes[tree].left);\n  \
    \      int length = _nodes[tree].length;\n        if (position < left_size) {\n\
    \            _nodes[tree].left =\n                insert_impl(_nodes[tree].left,\
    \ position, value);\n            update(tree);\n            if (_nodes[_nodes[tree].left].priority\
    \ >\n                _nodes[tree].priority) {\n                tree = rotate_right(tree);\n\
    \            }\n            return tree;\n        }\n        if (position > left_size\
    \ + length) {\n            _nodes[tree].right = insert_impl(\n               \
    \ _nodes[tree].right,\n                position - left_size - length,\n      \
    \          value\n            );\n            update(tree);\n            if (_nodes[_nodes[tree].right].priority\
    \ >\n                _nodes[tree].priority) {\n                tree = rotate_left(tree);\n\
    \            }\n            return tree;\n        }\n\n        int local_position\
    \ = position - left_size;\n        if (length < chunk_capacity) {\n          \
    \  local_insert(tree, local_position, value);\n            return tree;\n    \
    \    }\n\n        std::vector<std::uint8_t> values(chunk_capacity);\n        for\
    \ (int i = 0; i < chunk_capacity; i++) {\n            values[i] = local_get(tree,\
    \ i);\n        }\n        int right_chunk = new_node();\n        int middle =\
    \ chunk_capacity / 2;\n        assign_from_values(tree, values, 0, middle);\n\
    \        assign_from_values(right_chunk, values, middle, chunk_capacity);\n  \
    \      if (local_position <= middle) {\n            local_insert(tree, local_position,\
    \ value);\n        } else {\n            local_insert(right_chunk, local_position\
    \ - middle, value);\n        }\n\n        int old_right = _nodes[tree].right;\n\
    \        _nodes[tree].right = 0;\n        update(tree);\n        return merge(merge(tree,\
    \ right_chunk), old_right);\n    }\n\n    int erase_impl(int tree, int position)\
    \ {\n        int left_size = size_of(_nodes[tree].left);\n        int length =\
    \ _nodes[tree].length;\n        if (position < left_size) {\n            _nodes[tree].left\
    \ = erase_impl(_nodes[tree].left, position);\n            update(tree);\n    \
    \        return tree;\n        }\n        if (position >= left_size + length)\
    \ {\n            _nodes[tree].right = erase_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length\n            );\n            update(tree);\n\
    \            return tree;\n        }\n\n        local_erase(tree, position - left_size);\n\
    \        if (_nodes[tree].length == 0) {\n            int result = merge(_nodes[tree].left,\
    \ _nodes[tree].right);\n            recycle_node(tree);\n            return result;\n\
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
    \ get(int position) const {\n        assert(0 <= position && position < size());\n\
    \        int tree = _root;\n        while (tree != 0) {\n            int left_size\
    \ = size_of(_nodes[tree].left);\n            if (position < left_size) {\n   \
    \             tree = _nodes[tree].left;\n            } else if (position < left_size\
    \ + _nodes[tree].length) {\n                return local_get(tree, position -\
    \ left_size);\n            } else {\n                position -= left_size + _nodes[tree].length;\n\
    \                tree = _nodes[tree].right;\n            }\n        }\n      \
    \  assert(false);\n        return false;\n    }\n\n    int rank1(int right) const\
    \ {\n        assert(0 <= right && right <= size());\n        int result = 0;\n\
    \        int tree = _root;\n        while (tree != 0 && right != 0) {\n      \
    \      int left_size = size_of(_nodes[tree].left);\n            if (right <= left_size)\
    \ {\n                tree = _nodes[tree].left;\n                continue;\n  \
    \          }\n            result += ones_of(_nodes[tree].left);\n            right\
    \ -= left_size;\n            int take = std::min(right, int(_nodes[tree].length));\n\
    \            result += local_rank1(tree, take);\n            right -= take;\n\
    \            if (right == 0) break;\n            tree = _nodes[tree].right;\n\
    \        }\n        return result;\n    }\n\n    void insert(int position, bool\
    \ value) {\n        assert(0 <= position && position <= size());\n        _root\
    \ = insert_impl(_root, position, value);\n    }\n\n    bool erase(int position)\
    \ {\n        assert(0 <= position && position < size());\n        bool value =\
    \ get(position);\n        _root = erase_impl(_root, position);\n        return\
    \ value;\n    }\n};\n\n}  // namespace dynamic_wavelet_matrix_detail\n\n// A dynamic\
    \ wavelet matrix for integral sequences.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nclass DynamicWaveletMatrix {\n   public:\n    using value_type = T;\n\
    \    using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n    static\
    \ constexpr int bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
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
    \ level++) {\n            int ones_before = _matrix[level].rank1(position);\n\
    \            if (bit(key, level)) {\n                int next_position = _zero_count[level]\
    \ + ones_before;\n                _matrix[level].insert(position, true);\n   \
    \             position = next_position;\n            } else {\n              \
    \  int next_position = position - ones_before;\n                _matrix[level].insert(position,\
    \ false);\n                _zero_count[level]++;\n                position = next_position;\n\
    \            }\n        }\n        _size++;\n    }\n\n    void erase_encoded(int\
    \ position) {\n        for (int level = 0; level < bit_width; level++) {\n   \
    \         int ones_before = _matrix[level].rank1(position);\n            bool\
    \ one = _matrix[level].get(position);\n            int next_position;\n      \
    \      if (one) {\n                next_position = _zero_count[level] + ones_before;\n\
    \            } else {\n                next_position = position - ones_before;\n\
    \                _zero_count[level]--;\n            }\n            _matrix[level].erase(position);\n\
    \            position = next_position;\n        }\n        _size--;\n    }\n\n\
    \    int count_less_encoded(int left, int right, unsigned_type upper) const {\n\
    \        int result = 0;\n        for (int level = 0; level < bit_width; level++)\
    \ {\n            int left_ones = _matrix[level].rank1(left);\n            int\
    \ right_ones = _matrix[level].rank1(right);\n            if (bit(upper, level))\
    \ {\n                result += (right - left) - (right_ones - left_ones);\n  \
    \              left = _zero_count[level] + left_ones;\n                right =\
    \ _zero_count[level] + right_ones;\n            } else {\n                left\
    \ -= left_ones;\n                right -= right_ones;\n            }\n       \
    \ }\n        return result;\n    }\n\n   public:\n    DynamicWaveletMatrix() :\
    \ _matrix(bit_width) {}\n\n    explicit DynamicWaveletMatrix(const std::vector<T>&\
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
    \ 0; level < bit_width; level++) {\n            int ones_before = _matrix[level].rank1(position);\n\
    \            if (_matrix[level].get(position)) {\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                position = _zero_count[level] +\
    \ ones_before;\n            } else {\n                position -= ones_before;\n\
    \            }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
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
    \ bit_width; level++) {\n            int left_ones = _matrix[level].rank1(left);\n\
    \            int right_ones = _matrix[level].rank1(right);\n            if (bit(key,\
    \ level)) {\n                left = _zero_count[level] + left_ones;\n        \
    \        right = _zero_count[level] + right_ones;\n            } else {\n    \
    \            left -= left_ones;\n                right -= right_ones;\n      \
    \      }\n        }\n        return right - left;\n    }\n\n    T kth_smallest(int\
    \ left, int right, int k) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _size);\n        assert(0 <= k && k < right - left);\n        unsigned_type\
    \ key = 0;\n        for (int level = 0; level < bit_width; level++) {\n      \
    \      int left_ones = _matrix[level].rank1(left);\n            int right_ones\
    \ = _matrix[level].rank1(right);\n            int left_zeros = left - left_ones;\n\
    \            int right_zeros = right - right_ones;\n            int zeros = right_zeros\
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
    \n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_HPP\n#define M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <bit>\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\nnamespace dynamic_wavelet_matrix_detail {\n\n// A dynamic\
    \ bit vector stored as an implicit treap of small packed chunks.\nclass DynamicRankBitVector\
    \ {\n   private:\n    static constexpr int word_bits = 64;\n    static constexpr\
    \ int chunk_words = 4;\n    static constexpr int chunk_capacity = word_bits *\
    \ chunk_words;\n    static constexpr int minimum_chunk_size = chunk_capacity /\
    \ 2;\n\n    struct Node {\n        std::array<std::uint64_t, chunk_words> bits{};\n\
    \        std::uint32_t priority = 0;\n        int left = 0;\n        int right\
    \ = 0;\n        int subtree_size = 0;\n        int subtree_ones = 0;\n       \
    \ std::uint16_t length = 0;\n        std::uint16_t chunk_ones = 0;\n    };\n\n\
    \    std::vector<Node> _nodes;\n    std::vector<int> _free_nodes;\n    int _root\
    \ = 0;\n    std::uint32_t _random_state = 1;\n\n    int size_of(int node) const\
    \ {\n        return _nodes[node].subtree_size;\n    }\n\n    int ones_of(int node)\
    \ const {\n        return _nodes[node].subtree_ones;\n    }\n\n    std::uint32_t\
    \ next_priority() {\n        _random_state ^= _random_state << 13;\n        _random_state\
    \ ^= _random_state >> 17;\n        _random_state ^= _random_state << 5;\n    \
    \    if (_random_state == 0) _random_state = 1;\n        return _random_state;\n\
    \    }\n\n    void update(int node) {\n        if (node == 0) return;\n      \
    \  _nodes[node].subtree_size =\n            size_of(_nodes[node].left) + int(_nodes[node].length)\
    \ +\n            size_of(_nodes[node].right);\n        _nodes[node].subtree_ones\
    \ =\n            ones_of(_nodes[node].left) + int(_nodes[node].chunk_ones) +\n\
    \            ones_of(_nodes[node].right);\n    }\n\n    bool local_get(int node,\
    \ int position) const {\n        return (_nodes[node].bits[position / word_bits]\
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
    \            }\n        }\n        update(node);\n    }\n\n    int insert_impl(int\
    \ tree, int position, bool value) {\n        if (tree == 0) {\n            int\
    \ node = new_node();\n            local_insert(node, 0, value);\n            return\
    \ node;\n        }\n\n        int left_size = size_of(_nodes[tree].left);\n  \
    \      int length = _nodes[tree].length;\n        if (position < left_size) {\n\
    \            _nodes[tree].left =\n                insert_impl(_nodes[tree].left,\
    \ position, value);\n            update(tree);\n            if (_nodes[_nodes[tree].left].priority\
    \ >\n                _nodes[tree].priority) {\n                tree = rotate_right(tree);\n\
    \            }\n            return tree;\n        }\n        if (position > left_size\
    \ + length) {\n            _nodes[tree].right = insert_impl(\n               \
    \ _nodes[tree].right,\n                position - left_size - length,\n      \
    \          value\n            );\n            update(tree);\n            if (_nodes[_nodes[tree].right].priority\
    \ >\n                _nodes[tree].priority) {\n                tree = rotate_left(tree);\n\
    \            }\n            return tree;\n        }\n\n        int local_position\
    \ = position - left_size;\n        if (length < chunk_capacity) {\n          \
    \  local_insert(tree, local_position, value);\n            return tree;\n    \
    \    }\n\n        std::vector<std::uint8_t> values(chunk_capacity);\n        for\
    \ (int i = 0; i < chunk_capacity; i++) {\n            values[i] = local_get(tree,\
    \ i);\n        }\n        int right_chunk = new_node();\n        int middle =\
    \ chunk_capacity / 2;\n        assign_from_values(tree, values, 0, middle);\n\
    \        assign_from_values(right_chunk, values, middle, chunk_capacity);\n  \
    \      if (local_position <= middle) {\n            local_insert(tree, local_position,\
    \ value);\n        } else {\n            local_insert(right_chunk, local_position\
    \ - middle, value);\n        }\n\n        int old_right = _nodes[tree].right;\n\
    \        _nodes[tree].right = 0;\n        update(tree);\n        return merge(merge(tree,\
    \ right_chunk), old_right);\n    }\n\n    int erase_impl(int tree, int position)\
    \ {\n        int left_size = size_of(_nodes[tree].left);\n        int length =\
    \ _nodes[tree].length;\n        if (position < left_size) {\n            _nodes[tree].left\
    \ = erase_impl(_nodes[tree].left, position);\n            update(tree);\n    \
    \        return tree;\n        }\n        if (position >= left_size + length)\
    \ {\n            _nodes[tree].right = erase_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length\n            );\n            update(tree);\n\
    \            return tree;\n        }\n\n        local_erase(tree, position - left_size);\n\
    \        if (_nodes[tree].length == 0) {\n            int result = merge(_nodes[tree].left,\
    \ _nodes[tree].right);\n            recycle_node(tree);\n            return result;\n\
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
    \ get(int position) const {\n        assert(0 <= position && position < size());\n\
    \        int tree = _root;\n        while (tree != 0) {\n            int left_size\
    \ = size_of(_nodes[tree].left);\n            if (position < left_size) {\n   \
    \             tree = _nodes[tree].left;\n            } else if (position < left_size\
    \ + _nodes[tree].length) {\n                return local_get(tree, position -\
    \ left_size);\n            } else {\n                position -= left_size + _nodes[tree].length;\n\
    \                tree = _nodes[tree].right;\n            }\n        }\n      \
    \  assert(false);\n        return false;\n    }\n\n    int rank1(int right) const\
    \ {\n        assert(0 <= right && right <= size());\n        int result = 0;\n\
    \        int tree = _root;\n        while (tree != 0 && right != 0) {\n      \
    \      int left_size = size_of(_nodes[tree].left);\n            if (right <= left_size)\
    \ {\n                tree = _nodes[tree].left;\n                continue;\n  \
    \          }\n            result += ones_of(_nodes[tree].left);\n            right\
    \ -= left_size;\n            int take = std::min(right, int(_nodes[tree].length));\n\
    \            result += local_rank1(tree, take);\n            right -= take;\n\
    \            if (right == 0) break;\n            tree = _nodes[tree].right;\n\
    \        }\n        return result;\n    }\n\n    void insert(int position, bool\
    \ value) {\n        assert(0 <= position && position <= size());\n        _root\
    \ = insert_impl(_root, position, value);\n    }\n\n    bool erase(int position)\
    \ {\n        assert(0 <= position && position < size());\n        bool value =\
    \ get(position);\n        _root = erase_impl(_root, position);\n        return\
    \ value;\n    }\n};\n\n}  // namespace dynamic_wavelet_matrix_detail\n\n// A dynamic\
    \ wavelet matrix for integral sequences.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nclass DynamicWaveletMatrix {\n   public:\n    using value_type = T;\n\
    \    using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n    static\
    \ constexpr int bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
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
    \ level++) {\n            int ones_before = _matrix[level].rank1(position);\n\
    \            if (bit(key, level)) {\n                int next_position = _zero_count[level]\
    \ + ones_before;\n                _matrix[level].insert(position, true);\n   \
    \             position = next_position;\n            } else {\n              \
    \  int next_position = position - ones_before;\n                _matrix[level].insert(position,\
    \ false);\n                _zero_count[level]++;\n                position = next_position;\n\
    \            }\n        }\n        _size++;\n    }\n\n    void erase_encoded(int\
    \ position) {\n        for (int level = 0; level < bit_width; level++) {\n   \
    \         int ones_before = _matrix[level].rank1(position);\n            bool\
    \ one = _matrix[level].get(position);\n            int next_position;\n      \
    \      if (one) {\n                next_position = _zero_count[level] + ones_before;\n\
    \            } else {\n                next_position = position - ones_before;\n\
    \                _zero_count[level]--;\n            }\n            _matrix[level].erase(position);\n\
    \            position = next_position;\n        }\n        _size--;\n    }\n\n\
    \    int count_less_encoded(int left, int right, unsigned_type upper) const {\n\
    \        int result = 0;\n        for (int level = 0; level < bit_width; level++)\
    \ {\n            int left_ones = _matrix[level].rank1(left);\n            int\
    \ right_ones = _matrix[level].rank1(right);\n            if (bit(upper, level))\
    \ {\n                result += (right - left) - (right_ones - left_ones);\n  \
    \              left = _zero_count[level] + left_ones;\n                right =\
    \ _zero_count[level] + right_ones;\n            } else {\n                left\
    \ -= left_ones;\n                right -= right_ones;\n            }\n       \
    \ }\n        return result;\n    }\n\n   public:\n    DynamicWaveletMatrix() :\
    \ _matrix(bit_width) {}\n\n    explicit DynamicWaveletMatrix(const std::vector<T>&\
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
    \ 0; level < bit_width; level++) {\n            int ones_before = _matrix[level].rank1(position);\n\
    \            if (_matrix[level].get(position)) {\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                position = _zero_count[level] +\
    \ ones_before;\n            } else {\n                position -= ones_before;\n\
    \            }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
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
    \ bit_width; level++) {\n            int left_ones = _matrix[level].rank1(left);\n\
    \            int right_ones = _matrix[level].rank1(right);\n            if (bit(key,\
    \ level)) {\n                left = _zero_count[level] + left_ones;\n        \
    \        right = _zero_count[level] + right_ones;\n            } else {\n    \
    \            left -= left_ones;\n                right -= right_ones;\n      \
    \      }\n        }\n        return right - left;\n    }\n\n    T kth_smallest(int\
    \ left, int right, int k) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _size);\n        assert(0 <= k && k < right - left);\n        unsigned_type\
    \ key = 0;\n        for (int level = 0; level < bit_width; level++) {\n      \
    \      int left_ones = _matrix[level].rank1(left);\n            int right_ones\
    \ = _matrix[level].rank1(right);\n            int left_zeros = left - left_ones;\n\
    \            int right_zeros = right - right_ones;\n            int zeros = right_zeros\
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
    \n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
  requiredBy:
  - ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
  timestamp: '2026-07-16 19:05:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/wavelet_matrix/dynamic_wavelet_matrix.test.cpp
  - verify/ds/wavelet_matrix/dynamic_wavelet_matrix_sum.test.cpp
documentation_of: ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
layout: document
title: Dynamic Wavelet Matrix
---

## Overview

`m1une::ds::DynamicWaveletMatrix<T>` maintains an integral sequence while
supporting insertion, erasure, point assignment, frequency queries, and range
order statistics. It is the updateable counterpart of `WaveletMatrix` and uses
zero-based indices and half-open ranges.

Each wavelet level stores its routing bits in a dynamic rank bit vector. The bit
vector is an implicit randomized treap of packed 256-bit chunks, keeping memory
usage substantially below a one-node-per-bit representation.

## Requirements

`T` must be an integral type other than `bool`. Signed values are ordered by
their usual numeric order, and the full range of `T` is supported. Treap bounds
are expected and insertion and erasure bounds are amortized because packed
chunks occasionally split or merge.

Let `B = numeric_limits<make_unsigned_t<T>>::digits` and let `N` be the current
sequence length.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `DynamicWaveletMatrix()` | Constructs an empty sequence. | $O(B)$ |
| `explicit DynamicWaveletMatrix(const std::vector<T>& values)` | Builds from `values`. | $O(BN)$ |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Tests whether the sequence is empty. | $O(1)$ |
| `void clear()` | Removes every value. | $O(B)$ |
| `T access(int position) const` | Returns the value at `position`. | Expected $O(B\log N)$ |
| `T operator[](int position) const` | Equivalent to `access(position)`. | Expected $O(B\log N)$ |
| `void insert(int position, T value)` | Inserts before `position`; `position == size()` is allowed. | Expected amortized $O(B\log N)$ |
| `void push_back(T value)` | Appends `value`. | Expected amortized $O(B\log N)$ |
| `T erase(int position)` | Erases and returns the value at `position`. | Expected amortized $O(B\log N)$ |
| `void set(int position, T value)` | Assigns `value` at `position`. | Expected amortized $O(B\log N)$ |
| `int rank(T value, int right) const` | Counts `value` in `[0, right)`. | Expected $O(B\log N)$ |
| `int rank(T value, int left, int right) const` | Counts `value` in `[left, right)`. | Expected $O(B\log N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest value in `[left, right)`. | Expected $O(B\log N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest value in `[left, right)`. | Expected $O(B\log N)$ |
| `int range_freq(int left, int right, T upper) const` | Counts values less than `upper` in `[left, right)`. | Expected $O(B\log N)$ |
| `int range_freq(int left, int right, T lower, T upper) const` | Counts values in `[lower, upper)` within `[left, right)`. | Expected $O(B\log N)$ |
| `std::optional<T> prev_value(int left, int right, T upper) const` | Returns the largest value below `upper`, or `nullopt`. | Expected $O(B\log N)$ |
| `std::optional<T> next_value(int left, int right, T lower) const` | Returns the smallest value at least `lower`, or `nullopt`. | Expected $O(B\log N)$ |

The structure uses $O(BN)$ memory. Query indices and update positions are
asserted. `kth_smallest` and `kth_largest` require
`0 <= k < right - left`.

## Example

```cpp
#include "ds/wavelet_matrix/dynamic_wavelet_matrix.hpp"

#include <cassert>
#include <vector>

int main() {
    std::vector<int> values = {5, 1, 4, 1, 3};
    m1une::ds::DynamicWaveletMatrix<int> matrix(values);

    assert(matrix.kth_smallest(0, 5, 2) == 3);
    matrix.set(0, 0);
    matrix.insert(2, 7);
    assert(matrix.rank(1, 0, matrix.size()) == 2);
    assert(matrix.erase(2) == 7);
}
```
