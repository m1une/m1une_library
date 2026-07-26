---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/suffix_tree.test.cpp
    title: verify/string/suffix_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/suffix_tree.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\ntemplate\
    \ <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct SuffixTree {\n   \
    \ static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n    static constexpr\
    \ node_id root_node = 0;\n    static constexpr node_id null_node = -1;\n    static\
    \ constexpr int terminal_symbol = AlphabetSize;\n\n    struct Node {\n       \
    \ std::array<node_id, AlphabetSize + 1> next;\n        node_id suffix_link;\n\
    \        node_id parent;\n        int left;\n        int right;\n        int suffix_start;\n\
    \        int representative_suffix;\n        int leaf_count;\n        int incoming_symbol;\n\
    \        node_id first_child;\n        node_id next_sibling;\n        int child_count;\n\
    \n        Node(int left_value = 0, int right_value = 0, node_id parent_value =\
    \ null_node)\n            : suffix_link(null_node),\n              parent(parent_value),\n\
    \              left(left_value),\n              right(right_value),\n        \
    \      suffix_start(-1),\n              representative_suffix(-1),\n         \
    \     leaf_count(0),\n              incoming_symbol(-1),\n              first_child(null_node),\n\
    \              next_sibling(null_node),\n              child_count(0) {\n    \
    \        next.fill(null_node);\n        }\n    };\n\n    struct Locus {\n    \
    \    node_id node;\n        int offset;\n\n        explicit operator bool() const\
    \ {\n            return node != null_node;\n        }\n\n        friend bool operator==(const\
    \ Locus&, const Locus&) = default;\n    };\n\n   private:\n    struct ActivePoint\
    \ {\n        node_id node;\n        int offset;\n    };\n\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _text;\n    ActivePoint _active;\n    int _text_length;\n\
    \n    template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    int edge_length_unchecked(node_id\
    \ id) const {\n        return _nodes[id].right - _nodes[id].left;\n    }\n\n \
    \   node_id new_node(int left, int right, node_id parent) {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back(left,\
    \ right, parent);\n        return int(_nodes.size()) - 1;\n    }\n\n    ActivePoint\
    \ go(ActivePoint point, int left, int right) const {\n        while (left < right)\
    \ {\n            if (point.offset == edge_length_unchecked(point.node)) {\n  \
    \              point = {_nodes[point.node].next[_text[left]], 0};\n          \
    \      if (point.node == null_node) return point;\n            } else {\n    \
    \            if (_text[_nodes[point.node].left + point.offset] != _text[left])\
    \ {\n                    return {null_node, 0};\n                }\n         \
    \       int remaining = edge_length_unchecked(point.node) - point.offset;\n  \
    \              if (right - left < remaining) {\n                    point.offset\
    \ += right - left;\n                    return point;\n                }\n   \
    \             left += remaining;\n                point.offset = edge_length_unchecked(point.node);\n\
    \            }\n        }\n        return point;\n    }\n\n    node_id split(ActivePoint\
    \ point) {\n        if (point.offset == edge_length_unchecked(point.node)) return\
    \ point.node;\n        if (point.offset == 0) return _nodes[point.node].parent;\n\
    \n        node_id child = point.node;\n        node_id parent = _nodes[child].parent;\n\
    \        int left = _nodes[child].left;\n        node_id middle = new_node(left,\
    \ left + point.offset, parent);\n        _nodes[parent].next[_text[left]] = middle;\n\
    \        _nodes[middle].next[_text[left + point.offset]] = child;\n        _nodes[child].parent\
    \ = middle;\n        _nodes[child].left += point.offset;\n        return middle;\n\
    \    }\n\n    node_id get_suffix_link(node_id id) {\n        if (_nodes[id].suffix_link\
    \ != null_node) return _nodes[id].suffix_link;\n        node_id parent = _nodes[id].parent;\n\
    \        if (parent == null_node) return root_node;\n\n        node_id parent_link\
    \ = get_suffix_link(parent);\n        ActivePoint point = {\n            parent_link,\n\
    \            edge_length_unchecked(parent_link)\n        };\n        int left\
    \ = _nodes[id].left + (parent == root_node);\n        point = go(point, left,\
    \ _nodes[id].right);\n        assert(point.node != null_node);\n        return\
    \ _nodes[id].suffix_link = split(point);\n    }\n\n    void extend(int position)\
    \ {\n        while (true) {\n            ActivePoint next = go(_active, position,\
    \ position + 1);\n            if (next.node != null_node) {\n                _active\
    \ = next;\n                return;\n            }\n\n            node_id middle\
    \ = split(_active);\n            node_id leaf = new_node(position, int(_text.size()),\
    \ middle);\n            _nodes[middle].next[_text[position]] = leaf;\n\n     \
    \       _active.node = get_suffix_link(middle);\n            _active.offset =\
    \ edge_length_unchecked(_active.node);\n            if (middle == root_node) return;\n\
    \        }\n    }\n\n    void finish_metadata() {\n        std::vector<node_id>\
    \ order;\n        order.reserve(_nodes.size());\n        order.push_back(root_node);\n\
    \        std::vector<int> depth(_nodes.size(), 0);\n\n        for (std::size_t\
    \ i = 0; i < order.size(); i++) {\n            node_id id = order[i];\n      \
    \      node_id previous_child = null_node;\n            for (int symbol = 0; symbol\
    \ <= terminal_symbol; symbol++) {\n                node_id child = _nodes[id].next[symbol];\n\
    \                if (child == null_node) continue;\n                _nodes[child].incoming_symbol\
    \ = symbol;\n                if (previous_child == null_node) {\n            \
    \        _nodes[id].first_child = child;\n                } else {\n         \
    \           _nodes[previous_child].next_sibling = child;\n                }\n\
    \                previous_child = child;\n                _nodes[id].child_count++;\n\
    \                depth[child] = depth[id] + edge_length_unchecked(child);\n  \
    \              order.push_back(child);\n            }\n        }\n\n        for\
    \ (int i = int(order.size()) - 1; i >= 0; i--) {\n            node_id id = order[i];\n\
    \            bool leaf = true;\n            for (node_id child : _nodes[id].next)\
    \ {\n                if (child == null_node) continue;\n                leaf =\
    \ false;\n                _nodes[id].leaf_count += _nodes[child].leaf_count;\n\
    \                if (_nodes[id].representative_suffix == -1) {\n             \
    \       _nodes[id].representative_suffix = _nodes[child].representative_suffix;\n\
    \                }\n            }\n            if (leaf) {\n                _nodes[id].suffix_start\
    \ = int(_text.size()) - depth[id];\n                _nodes[id].representative_suffix\
    \ = _nodes[id].suffix_start;\n                _nodes[id].leaf_count = 1;\n   \
    \         }\n        }\n    }\n\n    void initialize() {\n        _nodes.clear();\n\
    \        _nodes.reserve(2 * _text.size() + 1);\n        _nodes.emplace_back();\n\
    \        _nodes[root_node].suffix_link = root_node;\n        _active = {root_node,\
    \ 0};\n        for (int position = 0; position < int(_text.size()); position++)\
    \ extend(position);\n        finish_metadata();\n    }\n\n   public:\n    SuffixTree()\
    \ {\n        clear();\n    }\n\n    template <class Sequence>\n    explicit SuffixTree(const\
    \ Sequence& sequence) {\n        build(sequence);\n    }\n\n    int size() const\
    \ {\n        return node_count();\n    }\n\n    bool empty() const {\n       \
    \ return _text_length == 0;\n    }\n\n    int node_count() const {\n        return\
    \ int(_nodes.size());\n    }\n\n    int text_length() const {\n        return\
    \ _text_length;\n    }\n\n    node_id root() const {\n        return root_node;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ id < node_count());\n        return _nodes[id];\n    }\n\n    const std::vector<Node>&\
    \ nodes() const {\n        return _nodes;\n    }\n\n    int edge_length(node_id\
    \ id) const {\n        assert(0 <= id && id < node_count());\n        return edge_length_unchecked(id);\n\
    \    }\n\n    bool is_leaf(node_id id) const {\n        assert(0 <= id && id <\
    \ node_count());\n        return _nodes[id].suffix_start != -1;\n    }\n\n   \
    \ template <class Symbol>\n    node_id child(node_id id, const Symbol& symbol)\
    \ const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id].next[symbol_index(symbol)];\n\
    \    }\n\n    node_id child_by_index(node_id id, int symbol) const {\n       \
    \ assert(0 <= id && id < node_count());\n        assert(0 <= symbol && symbol\
    \ <= terminal_symbol);\n        return _nodes[id].next[symbol];\n    }\n\n   \
    \ template <class Callback>\n    void for_each_child(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        for (\n    \
    \        node_id child_id = _nodes[id].first_child;\n            child_id != null_node;\n\
    \            child_id = _nodes[child_id].next_sibling\n        ) {\n         \
    \   callback(_nodes[child_id].incoming_symbol, child_id);\n        }\n    }\n\n\
    \    void clear() {\n        _text.clear();\n        _text.push_back(terminal_symbol);\n\
    \        _text_length = 0;\n        initialize();\n    }\n\n    template <class\
    \ Sequence>\n    void build(const Sequence& sequence) {\n        _text.clear();\n\
    \        for (const auto& symbol : sequence) _text.push_back(symbol_index(symbol));\n\
    \        assert(_text.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _text_length = int(_text.size());\n        _text.push_back(terminal_symbol);\n\
    \        initialize();\n    }\n\n    template <class Sequence>\n    Locus find(const\
    \ Sequence& sequence) const {\n        ActivePoint point = {root_node, 0};\n \
    \       for (const auto& value : sequence) {\n            int symbol = symbol_index(value);\n\
    \            if (point.offset == edge_length_unchecked(point.node)) {\n      \
    \          point = {_nodes[point.node].next[symbol], 0};\n                if (point.node\
    \ == null_node) return {null_node, 0};\n            }\n            if (_text[_nodes[point.node].left\
    \ + point.offset] != symbol) {\n                return {null_node, 0};\n     \
    \       }\n            point.offset++;\n        }\n        return {point.node,\
    \ point.offset};\n    }\n\n    template <class Sequence>\n    bool contains(const\
    \ Sequence& sequence) const {\n        return bool(find(sequence));\n    }\n\n\
    \    template <class Sequence>\n    int count_occurrences(const Sequence& sequence)\
    \ const {\n        Locus locus = find(sequence);\n        return locus ? _nodes[locus.node].leaf_count\
    \ : 0;\n    }\n\n    template <class Sequence>\n    std::pair<int, int> representative_occurrence(const\
    \ Sequence& sequence) const {\n        Locus locus = {root_node, 0};\n       \
    \ int length = 0;\n        for (const auto& value : sequence) {\n            int\
    \ symbol = symbol_index(value);\n            if (locus.offset == edge_length_unchecked(locus.node))\
    \ {\n                locus = {_nodes[locus.node].next[symbol], 0};\n         \
    \       if (locus.node == null_node) return {-1, -1};\n            }\n       \
    \     if (_text[_nodes[locus.node].left + locus.offset] != symbol) return {-1,\
    \ -1};\n            locus.offset++;\n            length++;\n        }\n      \
    \  int left = _nodes[locus.node].representative_suffix;\n        return {left,\
    \ left + length};\n    }\n\n    long long distinct_substring_count() const {\n\
    \        long long result = 0;\n        for (node_id id = 1; id < node_count();\
    \ id++) {\n            result += std::max(0, std::min(_nodes[id].right, _text_length)\
    \ - _nodes[id].left);\n        }\n        return result;\n    }\n};\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_SUFFIX_TREE_HPP\n#define M1UNE_STRING_SUFFIX_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\n\
    struct SuffixTree {\n    static_assert(0 < AlphabetSize);\n\n    using node_id\
    \ = int;\n    static constexpr node_id root_node = 0;\n    static constexpr node_id\
    \ null_node = -1;\n    static constexpr int terminal_symbol = AlphabetSize;\n\n\
    \    struct Node {\n        std::array<node_id, AlphabetSize + 1> next;\n    \
    \    node_id suffix_link;\n        node_id parent;\n        int left;\n      \
    \  int right;\n        int suffix_start;\n        int representative_suffix;\n\
    \        int leaf_count;\n        int incoming_symbol;\n        node_id first_child;\n\
    \        node_id next_sibling;\n        int child_count;\n\n        Node(int left_value\
    \ = 0, int right_value = 0, node_id parent_value = null_node)\n            : suffix_link(null_node),\n\
    \              parent(parent_value),\n              left(left_value),\n      \
    \        right(right_value),\n              suffix_start(-1),\n              representative_suffix(-1),\n\
    \              leaf_count(0),\n              incoming_symbol(-1),\n          \
    \    first_child(null_node),\n              next_sibling(null_node),\n       \
    \       child_count(0) {\n            next.fill(null_node);\n        }\n    };\n\
    \n    struct Locus {\n        node_id node;\n        int offset;\n\n        explicit\
    \ operator bool() const {\n            return node != null_node;\n        }\n\n\
    \        friend bool operator==(const Locus&, const Locus&) = default;\n    };\n\
    \n   private:\n    struct ActivePoint {\n        node_id node;\n        int offset;\n\
    \    };\n\n    std::vector<Node> _nodes;\n    std::vector<int> _text;\n    ActivePoint\
    \ _active;\n    int _text_length;\n\n    template <class Symbol>\n    static int\
    \ symbol_index(const Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n\
    \        assert(0 <= index && index < AlphabetSize);\n        return index;\n\
    \    }\n\n    int edge_length_unchecked(node_id id) const {\n        return _nodes[id].right\
    \ - _nodes[id].left;\n    }\n\n    node_id new_node(int left, int right, node_id\
    \ parent) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(left, right, parent);\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    ActivePoint go(ActivePoint point, int left, int right) const\
    \ {\n        while (left < right) {\n            if (point.offset == edge_length_unchecked(point.node))\
    \ {\n                point = {_nodes[point.node].next[_text[left]], 0};\n    \
    \            if (point.node == null_node) return point;\n            } else {\n\
    \                if (_text[_nodes[point.node].left + point.offset] != _text[left])\
    \ {\n                    return {null_node, 0};\n                }\n         \
    \       int remaining = edge_length_unchecked(point.node) - point.offset;\n  \
    \              if (right - left < remaining) {\n                    point.offset\
    \ += right - left;\n                    return point;\n                }\n   \
    \             left += remaining;\n                point.offset = edge_length_unchecked(point.node);\n\
    \            }\n        }\n        return point;\n    }\n\n    node_id split(ActivePoint\
    \ point) {\n        if (point.offset == edge_length_unchecked(point.node)) return\
    \ point.node;\n        if (point.offset == 0) return _nodes[point.node].parent;\n\
    \n        node_id child = point.node;\n        node_id parent = _nodes[child].parent;\n\
    \        int left = _nodes[child].left;\n        node_id middle = new_node(left,\
    \ left + point.offset, parent);\n        _nodes[parent].next[_text[left]] = middle;\n\
    \        _nodes[middle].next[_text[left + point.offset]] = child;\n        _nodes[child].parent\
    \ = middle;\n        _nodes[child].left += point.offset;\n        return middle;\n\
    \    }\n\n    node_id get_suffix_link(node_id id) {\n        if (_nodes[id].suffix_link\
    \ != null_node) return _nodes[id].suffix_link;\n        node_id parent = _nodes[id].parent;\n\
    \        if (parent == null_node) return root_node;\n\n        node_id parent_link\
    \ = get_suffix_link(parent);\n        ActivePoint point = {\n            parent_link,\n\
    \            edge_length_unchecked(parent_link)\n        };\n        int left\
    \ = _nodes[id].left + (parent == root_node);\n        point = go(point, left,\
    \ _nodes[id].right);\n        assert(point.node != null_node);\n        return\
    \ _nodes[id].suffix_link = split(point);\n    }\n\n    void extend(int position)\
    \ {\n        while (true) {\n            ActivePoint next = go(_active, position,\
    \ position + 1);\n            if (next.node != null_node) {\n                _active\
    \ = next;\n                return;\n            }\n\n            node_id middle\
    \ = split(_active);\n            node_id leaf = new_node(position, int(_text.size()),\
    \ middle);\n            _nodes[middle].next[_text[position]] = leaf;\n\n     \
    \       _active.node = get_suffix_link(middle);\n            _active.offset =\
    \ edge_length_unchecked(_active.node);\n            if (middle == root_node) return;\n\
    \        }\n    }\n\n    void finish_metadata() {\n        std::vector<node_id>\
    \ order;\n        order.reserve(_nodes.size());\n        order.push_back(root_node);\n\
    \        std::vector<int> depth(_nodes.size(), 0);\n\n        for (std::size_t\
    \ i = 0; i < order.size(); i++) {\n            node_id id = order[i];\n      \
    \      node_id previous_child = null_node;\n            for (int symbol = 0; symbol\
    \ <= terminal_symbol; symbol++) {\n                node_id child = _nodes[id].next[symbol];\n\
    \                if (child == null_node) continue;\n                _nodes[child].incoming_symbol\
    \ = symbol;\n                if (previous_child == null_node) {\n            \
    \        _nodes[id].first_child = child;\n                } else {\n         \
    \           _nodes[previous_child].next_sibling = child;\n                }\n\
    \                previous_child = child;\n                _nodes[id].child_count++;\n\
    \                depth[child] = depth[id] + edge_length_unchecked(child);\n  \
    \              order.push_back(child);\n            }\n        }\n\n        for\
    \ (int i = int(order.size()) - 1; i >= 0; i--) {\n            node_id id = order[i];\n\
    \            bool leaf = true;\n            for (node_id child : _nodes[id].next)\
    \ {\n                if (child == null_node) continue;\n                leaf =\
    \ false;\n                _nodes[id].leaf_count += _nodes[child].leaf_count;\n\
    \                if (_nodes[id].representative_suffix == -1) {\n             \
    \       _nodes[id].representative_suffix = _nodes[child].representative_suffix;\n\
    \                }\n            }\n            if (leaf) {\n                _nodes[id].suffix_start\
    \ = int(_text.size()) - depth[id];\n                _nodes[id].representative_suffix\
    \ = _nodes[id].suffix_start;\n                _nodes[id].leaf_count = 1;\n   \
    \         }\n        }\n    }\n\n    void initialize() {\n        _nodes.clear();\n\
    \        _nodes.reserve(2 * _text.size() + 1);\n        _nodes.emplace_back();\n\
    \        _nodes[root_node].suffix_link = root_node;\n        _active = {root_node,\
    \ 0};\n        for (int position = 0; position < int(_text.size()); position++)\
    \ extend(position);\n        finish_metadata();\n    }\n\n   public:\n    SuffixTree()\
    \ {\n        clear();\n    }\n\n    template <class Sequence>\n    explicit SuffixTree(const\
    \ Sequence& sequence) {\n        build(sequence);\n    }\n\n    int size() const\
    \ {\n        return node_count();\n    }\n\n    bool empty() const {\n       \
    \ return _text_length == 0;\n    }\n\n    int node_count() const {\n        return\
    \ int(_nodes.size());\n    }\n\n    int text_length() const {\n        return\
    \ _text_length;\n    }\n\n    node_id root() const {\n        return root_node;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ id < node_count());\n        return _nodes[id];\n    }\n\n    const std::vector<Node>&\
    \ nodes() const {\n        return _nodes;\n    }\n\n    int edge_length(node_id\
    \ id) const {\n        assert(0 <= id && id < node_count());\n        return edge_length_unchecked(id);\n\
    \    }\n\n    bool is_leaf(node_id id) const {\n        assert(0 <= id && id <\
    \ node_count());\n        return _nodes[id].suffix_start != -1;\n    }\n\n   \
    \ template <class Symbol>\n    node_id child(node_id id, const Symbol& symbol)\
    \ const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id].next[symbol_index(symbol)];\n\
    \    }\n\n    node_id child_by_index(node_id id, int symbol) const {\n       \
    \ assert(0 <= id && id < node_count());\n        assert(0 <= symbol && symbol\
    \ <= terminal_symbol);\n        return _nodes[id].next[symbol];\n    }\n\n   \
    \ template <class Callback>\n    void for_each_child(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        for (\n    \
    \        node_id child_id = _nodes[id].first_child;\n            child_id != null_node;\n\
    \            child_id = _nodes[child_id].next_sibling\n        ) {\n         \
    \   callback(_nodes[child_id].incoming_symbol, child_id);\n        }\n    }\n\n\
    \    void clear() {\n        _text.clear();\n        _text.push_back(terminal_symbol);\n\
    \        _text_length = 0;\n        initialize();\n    }\n\n    template <class\
    \ Sequence>\n    void build(const Sequence& sequence) {\n        _text.clear();\n\
    \        for (const auto& symbol : sequence) _text.push_back(symbol_index(symbol));\n\
    \        assert(_text.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _text_length = int(_text.size());\n        _text.push_back(terminal_symbol);\n\
    \        initialize();\n    }\n\n    template <class Sequence>\n    Locus find(const\
    \ Sequence& sequence) const {\n        ActivePoint point = {root_node, 0};\n \
    \       for (const auto& value : sequence) {\n            int symbol = symbol_index(value);\n\
    \            if (point.offset == edge_length_unchecked(point.node)) {\n      \
    \          point = {_nodes[point.node].next[symbol], 0};\n                if (point.node\
    \ == null_node) return {null_node, 0};\n            }\n            if (_text[_nodes[point.node].left\
    \ + point.offset] != symbol) {\n                return {null_node, 0};\n     \
    \       }\n            point.offset++;\n        }\n        return {point.node,\
    \ point.offset};\n    }\n\n    template <class Sequence>\n    bool contains(const\
    \ Sequence& sequence) const {\n        return bool(find(sequence));\n    }\n\n\
    \    template <class Sequence>\n    int count_occurrences(const Sequence& sequence)\
    \ const {\n        Locus locus = find(sequence);\n        return locus ? _nodes[locus.node].leaf_count\
    \ : 0;\n    }\n\n    template <class Sequence>\n    std::pair<int, int> representative_occurrence(const\
    \ Sequence& sequence) const {\n        Locus locus = {root_node, 0};\n       \
    \ int length = 0;\n        for (const auto& value : sequence) {\n            int\
    \ symbol = symbol_index(value);\n            if (locus.offset == edge_length_unchecked(locus.node))\
    \ {\n                locus = {_nodes[locus.node].next[symbol], 0};\n         \
    \       if (locus.node == null_node) return {-1, -1};\n            }\n       \
    \     if (_text[_nodes[locus.node].left + locus.offset] != symbol) return {-1,\
    \ -1};\n            locus.offset++;\n            length++;\n        }\n      \
    \  int left = _nodes[locus.node].representative_suffix;\n        return {left,\
    \ left + length};\n    }\n\n    long long distinct_substring_count() const {\n\
    \        long long result = 0;\n        for (node_id id = 1; id < node_count();\
    \ id++) {\n            result += std::max(0, std::min(_nodes[id].right, _text_length)\
    \ - _nodes[id].left);\n        }\n        return result;\n    }\n};\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_SUFFIX_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_tree.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-27 02:17:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/suffix_tree.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/suffix_tree.hpp
layout: document
title: Suffix Tree
---

## Overview

`SuffixTree` stores all suffixes of a static text in a compact trie. It supports
substring lookup, occurrence counting, representative occurrences, and direct
tree traversal.

Construction uses Ukkonen's algorithm. A unique terminal symbol is appended
internally, so every suffix, including the empty suffix, ends at its own leaf.
The terminal symbol has index `AlphabetSize` and cannot occur in input.

For a fixed alphabet, construction takes `O(N)` time, creates at most
`max(2, 2N + 1)` nodes, and uses `O(N * AlphabetSize)` memory for fixed
transition arrays.

## How to Use the Tree

Node zero is the root. Every non-root node has one incoming edge, and
`node(v).parent` is the node at the other end of that edge. The edge label is
the slice

```cpp
text.substr(tree.node(v).left, tree.edge_length(v))
```

except that a leaf edge may include the internal terminal symbol at position
`text.size()`. In that case `node(v).right == text.size() + 1`; exclude the last
position when reading the label from the original string.

There are two ways to access children:

```cpp
// Follow a known character in O(1).
int child = tree.child(node, 'a');

// Visit only existing children in O(number of children).
tree.for_each_child(node, [&](int symbol, int child) {
    // symbol is 0 for 'a', 1 for 'b', ..., or terminal_symbol.
});
```

`for_each_child` does not scan the alphabet. Each node stores a linked list of
its actual children in ascending symbol order. The same list can be traversed
manually when a callback is inconvenient:

```cpp
for (
    int child = tree.node(node).first_child;
    child != tree.null_node;
    child = tree.node(child).next_sibling
) {
    int symbol = tree.node(child).incoming_symbol;
    // Use child and symbol.
}
```

Concatenating incoming edge labels from the root to a node gives the string
represented by that node. A leaf represents the suffix beginning at
`node(leaf).suffix_start`. `node(v).leaf_count` is the number of occurrences of
the path string of `v`.

Most substring-query code does not need to traverse the topology manually:

```cpp
auto locus = tree.find(pattern);
if (locus) {
    int occurrences = tree.node(locus.node).leaf_count;
}
```

The pattern can end in the middle of an edge. `locus.node` is the child at the
end of that edge, and `locus.offset` is the number of edge symbols consumed.
The descendant leaves—and therefore the occurrence count—are the same for
every point inside that edge.

## Template Parameters

- `AlphabetSize`: number of input symbols, default `26`.
- `FirstCharacter`: character code mapped to transition zero, default `'a'`.

Every input symbol `c` must satisfy
`FirstCharacter <= c < FirstCharacter + AlphabetSize`. For decimal strings,
use `SuffixTree<10, '0'>`.

## Node and Locus Fields

An edge into node `v` is labeled by the internal augmented-text interval
`[node(v).left, node(v).right)`. The augmented text has length `N + 1`; position
`N` is the unique terminal symbol.

| Field | Meaning |
| --- | --- |
| `next[c]` | Child whose edge starts with symbol index `c`, or `null_node`. Index `AlphabetSize` is the terminal symbol. |
| `suffix_link` | Ukkonen suffix link for an internal node. It may be `null_node` for a leaf. |
| `parent` | Parent node, or `null_node` at the root. |
| `left`, `right` | Half-open augmented-text interval labeling the incoming edge. |
| `suffix_start` | Starting position of the represented suffix for a leaf, or `-1` for an internal node. |
| `representative_suffix` | Start of one descendant suffix. |
| `leaf_count` | Number of descendant leaves. |
| `incoming_symbol` | First symbol index of the incoming edge, or `-1` at the root. |
| `first_child` | First actual child in symbol order, or `null_node`. |
| `next_sibling` | Next child of the same parent, or `null_node`. |
| `child_count` | Number of actual children. |

`Locus` contains `node` and `offset`. A successful search may end inside the
incoming edge of `node`; `offset` is the number of consumed symbols on that
edge. It is an explicit node exactly when `offset == edge_length(node)`.
A `Locus` converts to `false` when no match exists.

## Methods

Let `V` be the number of nodes, `L` a query length, and `A = AlphabetSize`.

| Method | Description | Complexity |
| --- | --- | --- |
| `SuffixTree()` | Builds the tree of the empty text and its terminal suffix. | `O(A)` |
| `template<class Sequence> explicit SuffixTree(const Sequence& sequence)` | Builds the suffix tree of `sequence`. | `O(N * A)` |
| `int size() const`, `int node_count() const` | Returns `V`, including the root and terminal leaf. | `O(1)` |
| `bool empty() const` | Returns whether the original text is empty. | `O(1)` |
| `int text_length() const` | Returns `N`, excluding the terminal symbol. | `O(1)` |
| `node_id root() const` | Returns node zero. | `O(1)` |
| `const Node& node(node_id id) const` | Returns node metadata. | `O(1)` |
| `const std::vector<Node>& nodes() const` | Returns all nodes. | `O(1)` |
| `int edge_length(node_id id) const` | Returns the length of the incoming edge. | `O(1)` |
| `bool is_leaf(node_id id) const` | Tests whether a node represents one complete suffix. | `O(1)` |
| `template<class Symbol> node_id child(node_id id, const Symbol& symbol) const` | Returns an input-symbol child, or `null_node`. | `O(1)` |
| `node_id child_by_index(node_id id, int symbol) const` | Returns a child by symbol index, including `terminal_symbol`. | `O(1)` |
| `template<class Callback> void for_each_child(node_id id, Callback callback) const` | Calls `callback(symbol, child)` for each actual child in symbol-index order. | `O(node(id).child_count)` |
| `void clear()` | Replaces the tree with the empty-text tree. | `O(V + A)` |
| `template<class Sequence> void build(const Sequence& sequence)` | Replaces the tree with the suffix tree of `sequence`. | `O(V + N * A)` |
| `template<class Sequence> Locus find(const Sequence& sequence) const` | Returns the locus of a substring, or a false locus. | `O(L)` |
| `template<class Sequence> bool contains(const Sequence& sequence) const` | Tests whether a sequence is a substring. | `O(L)` |
| `template<class Sequence> int count_occurrences(const Sequence& sequence) const` | Counts possibly overlapping occurrences. | `O(L)` |
| `template<class Sequence> std::pair<int, int> representative_occurrence(const Sequence& sequence) const` | Returns one half-open occurrence, or `(-1, -1)`. | `O(L)` |
| `long long distinct_substring_count() const` | Counts distinct nonempty substrings. | `O(V)` |

For the empty query, `count_occurrences` returns `N + 1` and
`representative_occurrence` returns an empty interval.

Node handles remain valid until `build` or `clear`. Both operations rebuild the
whole tree and invalidate all earlier handles and references.

## Example

```cpp
#include "string/suffix_tree.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string text = "ababa";
    m1une::string::SuffixTree<> tree(text);

    std::cout << tree.contains(std::string("bab")) << '\n';       // 1
    std::cout << tree.count_occurrences(std::string("aba")) << '\n';  // 2
    std::cout << tree.distinct_substring_count() << '\n';         // 9

    auto occurrence = tree.representative_occurrence(std::string("bab"));
    std::cout << occurrence.first << ' ' << occurrence.second << '\n';

    // Print every edge as: parent, child, label.
    std::vector<int> stack(1, tree.root());
    while (!stack.empty()) {
        int parent = stack.back();
        stack.pop_back();
        tree.for_each_child(parent, [&](int symbol, int child) {
            const auto& current = tree.node(child);
            int right = std::min(current.right, tree.text_length());
            std::string label = text.substr(current.left, right - current.left);
            std::cout << parent << " -> " << child << ": " << label;
            if (symbol == tree.terminal_symbol || current.right > tree.text_length()) {
                std::cout << '$';
            }
            std::cout << '\n';
            stack.push_back(child);
        });
    }
}
```
