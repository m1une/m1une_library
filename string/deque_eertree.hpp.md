---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/deque_eertree.test.cpp
    title: verify/string/deque_eertree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/deque_eertree.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <deque>\n#include <limits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace string {\n\ntemplate <int AlphabetSize\
    \ = 26, int FirstCharacter = 'a'>\nstruct DequeEertree {\n    static_assert(0\
    \ < AlphabetSize);\n\n    using node_id = int;\n    static constexpr node_id odd_root\
    \ = 0;\n    static constexpr node_id even_root = 1;\n    static constexpr node_id\
    \ null_node = -1;\n\n   private:\n    struct Node {\n        std::array<node_id,\
    \ AlphabetSize> next;\n        node_id parent;\n        node_id suffix_link;\n\
    \        node_id quick_link;\n        int length;\n        int surface_count;\n\
    \        int suffix_link_children;\n        bool active;\n\n        Node(\n  \
    \          int length_value = 0,\n            node_id parent_value = null_node,\n\
    \            node_id suffix_link_value = null_node,\n            node_id quick_link_value\
    \ = null_node\n        )\n            : parent(parent_value),\n              suffix_link(suffix_link_value),\n\
    \              quick_link(quick_link_value),\n              length(length_value),\n\
    \              surface_count(0),\n              suffix_link_children(0),\n   \
    \           active(true) {\n            next.fill(null_node);\n        }\n   \
    \ };\n\n    struct Position {\n        int symbol;\n        node_id prefix_surface;\n\
    \        node_id suffix_surface;\n    };\n\n    std::vector<Node> _nodes;\n  \
    \  std::deque<Position> _text;\n    int _distinct_palindromes;\n\n    template\
    \ <class Symbol>\n    static int symbol_index(const Symbol& value) {\n       \
    \ int symbol = int(value) - FirstCharacter;\n        assert(0 <= symbol && symbol\
    \ < AlphabetSize);\n        return symbol;\n    }\n\n    node_id new_node(node_id\
    \ parent, node_id suffix_link, int length, int symbol) {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        node_id id = int(_nodes.size());\n\
    \        _nodes.emplace_back(length, parent, suffix_link, odd_root);\n       \
    \ _nodes[parent].next[symbol] = id;\n        _nodes[suffix_link].suffix_link_children++;\n\
    \        _distinct_palindromes++;\n        return id;\n    }\n\n    void remove_node(node_id\
    \ id, int symbol) {\n        Node& removed = _nodes[id];\n        assert(removed.active);\n\
    \        assert(removed.surface_count == 0);\n        assert(removed.suffix_link_children\
    \ == 0);\n        assert(_nodes[removed.parent].next[symbol] == id);\n       \
    \ _nodes[removed.parent].next[symbol] = null_node;\n        _nodes[removed.suffix_link].suffix_link_children--;\n\
    \        removed.active = false;\n        _distinct_palindromes--;\n    }\n\n\
    \    node_id back_appendable(int symbol, node_id node) const {\n        int n\
    \ = int(_text.size());\n        while (true) {\n            int length = _nodes[node].length;\n\
    \            if (length == -1 || (length < n && _text[n - length - 1].symbol ==\
    \ symbol)) {\n                return node;\n            }\n            node_id\
    \ suffix = _nodes[node].suffix_link;\n            int suffix_length = _nodes[suffix].length;\n\
    \            if (suffix_length == -1 || _text[n - suffix_length - 1].symbol ==\
    \ symbol) {\n                return suffix;\n            }\n            node =\
    \ _nodes[node].quick_link;\n        }\n    }\n\n    node_id front_appendable(int\
    \ symbol, node_id node) const {\n        int n = int(_text.size());\n        while\
    \ (true) {\n            int length = _nodes[node].length;\n            if (length\
    \ == -1 || (length < n && _text[length].symbol == symbol)) {\n               \
    \ return node;\n            }\n            node_id suffix = _nodes[node].suffix_link;\n\
    \            int suffix_length = _nodes[suffix].length;\n            if (suffix_length\
    \ == -1 || _text[suffix_length].symbol == symbol) {\n                return suffix;\n\
    \            }\n            node = _nodes[node].quick_link;\n        }\n    }\n\
    \n    node_id prefix_node() const {\n        return _text.empty() ? even_root\
    \ : _text.front().prefix_surface;\n    }\n\n    node_id suffix_node() const {\n\
    \        return _text.empty() ? even_root : _text.back().suffix_surface;\n   \
    \ }\n\n    void initialize_roots() {\n        _nodes.clear();\n        _nodes.emplace_back(-1,\
    \ odd_root, odd_root, odd_root);\n        _nodes.emplace_back(0, odd_root, odd_root,\
    \ odd_root);\n        _distinct_palindromes = 0;\n    }\n\n   public:\n    DequeEertree()\
    \ {\n        initialize_roots();\n    }\n\n    template <class Sequence>\n   \
    \ explicit DequeEertree(const Sequence& sequence) {\n        initialize_roots();\n\
    \        build(sequence);\n    }\n\n    int size() const {\n        return _distinct_palindromes;\n\
    \    }\n\n    int text_length() const {\n        return int(_text.size());\n \
    \   }\n\n    bool empty() const {\n        return _text.empty();\n    }\n\n  \
    \  int distinct_palindrome_count() const {\n        return _distinct_palindromes;\n\
    \    }\n\n    int longest_prefix_length() const {\n        return _nodes[prefix_node()].length;\n\
    \    }\n\n    int longest_suffix_length() const {\n        return _nodes[suffix_node()].length;\n\
    \    }\n\n    void reserve(std::size_t operation_capacity) {\n        _nodes.reserve(operation_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _text.clear();\n        initialize_roots();\n\
    \    }\n\n    template <class Symbol>\n    void push_back(const Symbol& value)\
    \ {\n        int symbol = symbol_index(value);\n        node_id parent = _text.empty()\
    \ ? odd_root : back_appendable(symbol, suffix_node());\n        node_id palindrome\
    \ = _nodes[parent].next[symbol];\n        node_id suffix = even_root;\n\n    \
    \    if (palindrome == null_node) {\n            if (parent != odd_root) {\n \
    \               node_id suffix_parent = back_appendable(symbol, _nodes[parent].suffix_link);\n\
    \                suffix = _nodes[suffix_parent].next[symbol];\n              \
    \  assert(suffix != null_node);\n            }\n        } else {\n           \
    \ suffix = _nodes[palindrome].suffix_link;\n        }\n\n        _text.push_back(Position{symbol,\
    \ even_root, even_root});\n        int n = int(_text.size());\n        if (palindrome\
    \ == null_node) {\n            palindrome = new_node(parent, suffix, _nodes[parent].length\
    \ + 2, symbol);\n\n            Node& created = _nodes[palindrome];\n         \
    \   if (\n                _nodes[suffix].suffix_link != odd_root &&\n        \
    \        _text[n - _nodes[suffix].length - 1].symbol ==\n                    _text[n\
    \ - _nodes[_nodes[suffix].suffix_link].length - 1].symbol\n            ) {\n \
    \               created.quick_link = _nodes[suffix].quick_link;\n            }\
    \ else {\n                created.quick_link = _nodes[suffix].suffix_link;\n \
    \           }\n        }\n\n        int left = n - _nodes[palindrome].length;\n\
    \        _text.back().suffix_surface = palindrome;\n        _text[left].prefix_surface\
    \ = palindrome;\n        if (\n            _nodes[suffix].length >= 1 &&\n   \
    \         _text[left + _nodes[suffix].length - 1].suffix_surface == suffix\n \
    \       ) {\n            _text[left + _nodes[suffix].length - 1].suffix_surface\
    \ = even_root;\n        }\n        _nodes[palindrome].surface_count++;\n    }\n\
    \n    template <class Symbol>\n    void push_front(const Symbol& value) {\n  \
    \      int symbol = symbol_index(value);\n        node_id parent = _text.empty()\
    \ ? odd_root : front_appendable(symbol, prefix_node());\n        node_id palindrome\
    \ = _nodes[parent].next[symbol];\n        node_id suffix = even_root;\n\n    \
    \    if (palindrome == null_node) {\n            if (parent != odd_root) {\n \
    \               node_id suffix_parent = front_appendable(symbol, _nodes[parent].suffix_link);\n\
    \                suffix = _nodes[suffix_parent].next[symbol];\n              \
    \  assert(suffix != null_node);\n            }\n        } else {\n           \
    \ suffix = _nodes[palindrome].suffix_link;\n        }\n\n        _text.push_front(Position{symbol,\
    \ even_root, even_root});\n        if (palindrome == null_node) {\n          \
    \  palindrome = new_node(parent, suffix, _nodes[parent].length + 2, symbol);\n\
    \n            Node& created = _nodes[palindrome];\n            if (\n        \
    \        _nodes[suffix].suffix_link != odd_root &&\n                _text[_nodes[suffix].length].symbol\
    \ ==\n                    _text[_nodes[_nodes[suffix].suffix_link].length].symbol\n\
    \            ) {\n                created.quick_link = _nodes[suffix].quick_link;\n\
    \            } else {\n                created.quick_link = _nodes[suffix].suffix_link;\n\
    \            }\n        }\n\n        _text.front().prefix_surface = palindrome;\n\
    \        _text[_nodes[palindrome].length - 1].suffix_surface = palindrome;\n \
    \       if (\n            _nodes[suffix].length >= 1 &&\n            _text[_nodes[palindrome].length\
    \ - _nodes[suffix].length].prefix_surface == suffix\n        ) {\n           \
    \ _text[_nodes[palindrome].length - _nodes[suffix].length].prefix_surface = even_root;\n\
    \        }\n        _nodes[palindrome].surface_count++;\n    }\n\n    void pop_back()\
    \ {\n        assert(!_text.empty());\n        node_id palindrome = suffix_node();\n\
    \        node_id suffix = _nodes[palindrome].suffix_link;\n        int left =\
    \ text_length() - _nodes[palindrome].length;\n        int suffix_end = left +\
    \ _nodes[suffix].length - 1;\n\n        if (\n            _nodes[palindrome].length\
    \ >= 2 &&\n            _nodes[_text[suffix_end].suffix_surface].length < _nodes[suffix].length\n\
    \        ) {\n            _text[suffix_end].suffix_surface = suffix;\n       \
    \     _text[left].prefix_surface = suffix;\n        } else {\n            _text[left].prefix_surface\
    \ = even_root;\n        }\n\n        _nodes[palindrome].surface_count--;\n   \
    \     int symbol = _text.back().symbol;\n        if (\n            _nodes[palindrome].surface_count\
    \ == 0 &&\n            _nodes[palindrome].suffix_link_children == 0\n        )\
    \ {\n            remove_node(palindrome, symbol);\n        }\n        _text.pop_back();\n\
    \    }\n\n    void pop_front() {\n        assert(!_text.empty());\n        node_id\
    \ palindrome = prefix_node();\n        node_id suffix = _nodes[palindrome].suffix_link;\n\
    \        int suffix_start = _nodes[palindrome].length - _nodes[suffix].length;\n\
    \n        if (\n            _nodes[palindrome].length >= 2 &&\n            _nodes[_text[suffix_start].prefix_surface].length\
    \ < _nodes[suffix].length\n        ) {\n            _text[suffix_start].prefix_surface\
    \ = suffix;\n            _text[_nodes[palindrome].length - 1].suffix_surface =\
    \ suffix;\n        } else {\n            _text[_nodes[palindrome].length - 1].suffix_surface\
    \ = even_root;\n        }\n\n        _nodes[palindrome].surface_count--;\n   \
    \     int symbol = _text.front().symbol;\n        if (\n            _nodes[palindrome].surface_count\
    \ == 0 &&\n            _nodes[palindrome].suffix_link_children == 0\n        )\
    \ {\n            remove_node(palindrome, symbol);\n        }\n        _text.pop_front();\n\
    \    }\n\n    template <class Sequence>\n    void build(const Sequence& sequence)\
    \ {\n        for (const auto& symbol : sequence) push_back(symbol);\n    }\n};\n\
    \ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing DoubleEndedEertree\
    \ = DequeEertree<AlphabetSize, FirstCharacter>;\n\ntemplate <int AlphabetSize\
    \ = 26, int FirstCharacter = 'a'>\nusing DequePalindromicTree = DequeEertree<AlphabetSize,\
    \ FirstCharacter>;\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_DEQUE_EERTREE_HPP\n#define M1UNE_STRING_DEQUE_EERTREE_HPP\
    \ 1\n\n#include <array>\n#include <cassert>\n#include <cstddef>\n#include <deque>\n\
    #include <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct DequeEertree\
    \ {\n    static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n    static\
    \ constexpr node_id odd_root = 0;\n    static constexpr node_id even_root = 1;\n\
    \    static constexpr node_id null_node = -1;\n\n   private:\n    struct Node\
    \ {\n        std::array<node_id, AlphabetSize> next;\n        node_id parent;\n\
    \        node_id suffix_link;\n        node_id quick_link;\n        int length;\n\
    \        int surface_count;\n        int suffix_link_children;\n        bool active;\n\
    \n        Node(\n            int length_value = 0,\n            node_id parent_value\
    \ = null_node,\n            node_id suffix_link_value = null_node,\n         \
    \   node_id quick_link_value = null_node\n        )\n            : parent(parent_value),\n\
    \              suffix_link(suffix_link_value),\n              quick_link(quick_link_value),\n\
    \              length(length_value),\n              surface_count(0),\n      \
    \        suffix_link_children(0),\n              active(true) {\n            next.fill(null_node);\n\
    \        }\n    };\n\n    struct Position {\n        int symbol;\n        node_id\
    \ prefix_surface;\n        node_id suffix_surface;\n    };\n\n    std::vector<Node>\
    \ _nodes;\n    std::deque<Position> _text;\n    int _distinct_palindromes;\n\n\
    \    template <class Symbol>\n    static int symbol_index(const Symbol& value)\
    \ {\n        int symbol = int(value) - FirstCharacter;\n        assert(0 <= symbol\
    \ && symbol < AlphabetSize);\n        return symbol;\n    }\n\n    node_id new_node(node_id\
    \ parent, node_id suffix_link, int length, int symbol) {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        node_id id = int(_nodes.size());\n\
    \        _nodes.emplace_back(length, parent, suffix_link, odd_root);\n       \
    \ _nodes[parent].next[symbol] = id;\n        _nodes[suffix_link].suffix_link_children++;\n\
    \        _distinct_palindromes++;\n        return id;\n    }\n\n    void remove_node(node_id\
    \ id, int symbol) {\n        Node& removed = _nodes[id];\n        assert(removed.active);\n\
    \        assert(removed.surface_count == 0);\n        assert(removed.suffix_link_children\
    \ == 0);\n        assert(_nodes[removed.parent].next[symbol] == id);\n       \
    \ _nodes[removed.parent].next[symbol] = null_node;\n        _nodes[removed.suffix_link].suffix_link_children--;\n\
    \        removed.active = false;\n        _distinct_palindromes--;\n    }\n\n\
    \    node_id back_appendable(int symbol, node_id node) const {\n        int n\
    \ = int(_text.size());\n        while (true) {\n            int length = _nodes[node].length;\n\
    \            if (length == -1 || (length < n && _text[n - length - 1].symbol ==\
    \ symbol)) {\n                return node;\n            }\n            node_id\
    \ suffix = _nodes[node].suffix_link;\n            int suffix_length = _nodes[suffix].length;\n\
    \            if (suffix_length == -1 || _text[n - suffix_length - 1].symbol ==\
    \ symbol) {\n                return suffix;\n            }\n            node =\
    \ _nodes[node].quick_link;\n        }\n    }\n\n    node_id front_appendable(int\
    \ symbol, node_id node) const {\n        int n = int(_text.size());\n        while\
    \ (true) {\n            int length = _nodes[node].length;\n            if (length\
    \ == -1 || (length < n && _text[length].symbol == symbol)) {\n               \
    \ return node;\n            }\n            node_id suffix = _nodes[node].suffix_link;\n\
    \            int suffix_length = _nodes[suffix].length;\n            if (suffix_length\
    \ == -1 || _text[suffix_length].symbol == symbol) {\n                return suffix;\n\
    \            }\n            node = _nodes[node].quick_link;\n        }\n    }\n\
    \n    node_id prefix_node() const {\n        return _text.empty() ? even_root\
    \ : _text.front().prefix_surface;\n    }\n\n    node_id suffix_node() const {\n\
    \        return _text.empty() ? even_root : _text.back().suffix_surface;\n   \
    \ }\n\n    void initialize_roots() {\n        _nodes.clear();\n        _nodes.emplace_back(-1,\
    \ odd_root, odd_root, odd_root);\n        _nodes.emplace_back(0, odd_root, odd_root,\
    \ odd_root);\n        _distinct_palindromes = 0;\n    }\n\n   public:\n    DequeEertree()\
    \ {\n        initialize_roots();\n    }\n\n    template <class Sequence>\n   \
    \ explicit DequeEertree(const Sequence& sequence) {\n        initialize_roots();\n\
    \        build(sequence);\n    }\n\n    int size() const {\n        return _distinct_palindromes;\n\
    \    }\n\n    int text_length() const {\n        return int(_text.size());\n \
    \   }\n\n    bool empty() const {\n        return _text.empty();\n    }\n\n  \
    \  int distinct_palindrome_count() const {\n        return _distinct_palindromes;\n\
    \    }\n\n    int longest_prefix_length() const {\n        return _nodes[prefix_node()].length;\n\
    \    }\n\n    int longest_suffix_length() const {\n        return _nodes[suffix_node()].length;\n\
    \    }\n\n    void reserve(std::size_t operation_capacity) {\n        _nodes.reserve(operation_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _text.clear();\n        initialize_roots();\n\
    \    }\n\n    template <class Symbol>\n    void push_back(const Symbol& value)\
    \ {\n        int symbol = symbol_index(value);\n        node_id parent = _text.empty()\
    \ ? odd_root : back_appendable(symbol, suffix_node());\n        node_id palindrome\
    \ = _nodes[parent].next[symbol];\n        node_id suffix = even_root;\n\n    \
    \    if (palindrome == null_node) {\n            if (parent != odd_root) {\n \
    \               node_id suffix_parent = back_appendable(symbol, _nodes[parent].suffix_link);\n\
    \                suffix = _nodes[suffix_parent].next[symbol];\n              \
    \  assert(suffix != null_node);\n            }\n        } else {\n           \
    \ suffix = _nodes[palindrome].suffix_link;\n        }\n\n        _text.push_back(Position{symbol,\
    \ even_root, even_root});\n        int n = int(_text.size());\n        if (palindrome\
    \ == null_node) {\n            palindrome = new_node(parent, suffix, _nodes[parent].length\
    \ + 2, symbol);\n\n            Node& created = _nodes[palindrome];\n         \
    \   if (\n                _nodes[suffix].suffix_link != odd_root &&\n        \
    \        _text[n - _nodes[suffix].length - 1].symbol ==\n                    _text[n\
    \ - _nodes[_nodes[suffix].suffix_link].length - 1].symbol\n            ) {\n \
    \               created.quick_link = _nodes[suffix].quick_link;\n            }\
    \ else {\n                created.quick_link = _nodes[suffix].suffix_link;\n \
    \           }\n        }\n\n        int left = n - _nodes[palindrome].length;\n\
    \        _text.back().suffix_surface = palindrome;\n        _text[left].prefix_surface\
    \ = palindrome;\n        if (\n            _nodes[suffix].length >= 1 &&\n   \
    \         _text[left + _nodes[suffix].length - 1].suffix_surface == suffix\n \
    \       ) {\n            _text[left + _nodes[suffix].length - 1].suffix_surface\
    \ = even_root;\n        }\n        _nodes[palindrome].surface_count++;\n    }\n\
    \n    template <class Symbol>\n    void push_front(const Symbol& value) {\n  \
    \      int symbol = symbol_index(value);\n        node_id parent = _text.empty()\
    \ ? odd_root : front_appendable(symbol, prefix_node());\n        node_id palindrome\
    \ = _nodes[parent].next[symbol];\n        node_id suffix = even_root;\n\n    \
    \    if (palindrome == null_node) {\n            if (parent != odd_root) {\n \
    \               node_id suffix_parent = front_appendable(symbol, _nodes[parent].suffix_link);\n\
    \                suffix = _nodes[suffix_parent].next[symbol];\n              \
    \  assert(suffix != null_node);\n            }\n        } else {\n           \
    \ suffix = _nodes[palindrome].suffix_link;\n        }\n\n        _text.push_front(Position{symbol,\
    \ even_root, even_root});\n        if (palindrome == null_node) {\n          \
    \  palindrome = new_node(parent, suffix, _nodes[parent].length + 2, symbol);\n\
    \n            Node& created = _nodes[palindrome];\n            if (\n        \
    \        _nodes[suffix].suffix_link != odd_root &&\n                _text[_nodes[suffix].length].symbol\
    \ ==\n                    _text[_nodes[_nodes[suffix].suffix_link].length].symbol\n\
    \            ) {\n                created.quick_link = _nodes[suffix].quick_link;\n\
    \            } else {\n                created.quick_link = _nodes[suffix].suffix_link;\n\
    \            }\n        }\n\n        _text.front().prefix_surface = palindrome;\n\
    \        _text[_nodes[palindrome].length - 1].suffix_surface = palindrome;\n \
    \       if (\n            _nodes[suffix].length >= 1 &&\n            _text[_nodes[palindrome].length\
    \ - _nodes[suffix].length].prefix_surface == suffix\n        ) {\n           \
    \ _text[_nodes[palindrome].length - _nodes[suffix].length].prefix_surface = even_root;\n\
    \        }\n        _nodes[palindrome].surface_count++;\n    }\n\n    void pop_back()\
    \ {\n        assert(!_text.empty());\n        node_id palindrome = suffix_node();\n\
    \        node_id suffix = _nodes[palindrome].suffix_link;\n        int left =\
    \ text_length() - _nodes[palindrome].length;\n        int suffix_end = left +\
    \ _nodes[suffix].length - 1;\n\n        if (\n            _nodes[palindrome].length\
    \ >= 2 &&\n            _nodes[_text[suffix_end].suffix_surface].length < _nodes[suffix].length\n\
    \        ) {\n            _text[suffix_end].suffix_surface = suffix;\n       \
    \     _text[left].prefix_surface = suffix;\n        } else {\n            _text[left].prefix_surface\
    \ = even_root;\n        }\n\n        _nodes[palindrome].surface_count--;\n   \
    \     int symbol = _text.back().symbol;\n        if (\n            _nodes[palindrome].surface_count\
    \ == 0 &&\n            _nodes[palindrome].suffix_link_children == 0\n        )\
    \ {\n            remove_node(palindrome, symbol);\n        }\n        _text.pop_back();\n\
    \    }\n\n    void pop_front() {\n        assert(!_text.empty());\n        node_id\
    \ palindrome = prefix_node();\n        node_id suffix = _nodes[palindrome].suffix_link;\n\
    \        int suffix_start = _nodes[palindrome].length - _nodes[suffix].length;\n\
    \n        if (\n            _nodes[palindrome].length >= 2 &&\n            _nodes[_text[suffix_start].prefix_surface].length\
    \ < _nodes[suffix].length\n        ) {\n            _text[suffix_start].prefix_surface\
    \ = suffix;\n            _text[_nodes[palindrome].length - 1].suffix_surface =\
    \ suffix;\n        } else {\n            _text[_nodes[palindrome].length - 1].suffix_surface\
    \ = even_root;\n        }\n\n        _nodes[palindrome].surface_count--;\n   \
    \     int symbol = _text.front().symbol;\n        if (\n            _nodes[palindrome].surface_count\
    \ == 0 &&\n            _nodes[palindrome].suffix_link_children == 0\n        )\
    \ {\n            remove_node(palindrome, symbol);\n        }\n        _text.pop_front();\n\
    \    }\n\n    template <class Sequence>\n    void build(const Sequence& sequence)\
    \ {\n        for (const auto& symbol : sequence) push_back(symbol);\n    }\n};\n\
    \ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing DoubleEndedEertree\
    \ = DequeEertree<AlphabetSize, FirstCharacter>;\n\ntemplate <int AlphabetSize\
    \ = 26, int FirstCharacter = 'a'>\nusing DequePalindromicTree = DequeEertree<AlphabetSize,\
    \ FirstCharacter>;\n\n}  // namespace string\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_STRING_DEQUE_EERTREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/deque_eertree.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-16 20:00:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/deque_eertree.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/deque_eertree.hpp
layout: document
title: Deque Eertree
---

## Overview

`DequeEertree` maintains the palindromic substrings of a sequence while symbols
are inserted or removed at either end. It can report the number of distinct
nonempty palindromes and the longest palindromic prefix and suffix after every
operation.

The implementation records palindrome surfaces and uses quick suffix links.
Its transition arrays require a contiguous, fixed alphabet. The default
alphabet is the lowercase English letters.

`DoubleEndedEertree` and `DequePalindromicTree` are aliases for
`DequeEertree`.

## Template Parameters

- `AlphabetSize`: number of symbols, default `26`.
- `FirstCharacter`: character code mapped to transition zero, default `'a'`.

For example, `DequeEertree<10, '0'>` accepts decimal digits.

## Methods

Let `N` be the current sequence length and let `Q` be the total number of push
operations since the last `clear()`.

| Method | Description | Complexity |
| --- | --- | --- |
| `DequeEertree()` | Creates an empty structure. | `O(1)` |
| `DequeEertree(sequence)` | Builds a structure by pushing the sequence at the back. | `O(N * AlphabetSize)` total |
| `int size() const` | Returns the number of distinct nonempty palindromic substrings. | `O(1)` |
| `int text_length() const` | Returns `N`. | `O(1)` |
| `bool empty() const` | Returns whether the sequence is empty. | `O(1)` |
| `int distinct_palindrome_count() const` | Returns the number of distinct nonempty palindromic substrings. | `O(1)` |
| `int longest_prefix_length() const` | Returns the longest palindromic prefix length, or zero if empty. | `O(1)` |
| `int longest_suffix_length() const` | Returns the longest palindromic suffix length, or zero if empty. | `O(1)` |
| `void reserve(operation_capacity)` | Reserves node storage for future pushes. | `O(Q * AlphabetSize)` if reallocated |
| `void clear()` | Removes the sequence and all historical nodes. | `O(N + Q)` |
| `void push_front(symbol)` | Inserts a symbol at the front. | Amortized `O(AlphabetSize)` |
| `void push_back(symbol)` | Inserts a symbol at the back. | Amortized `O(AlphabetSize)` |
| `void pop_front()` | Removes the front symbol; the sequence must be nonempty. | Amortized `O(1)` |
| `void pop_back()` | Removes the back symbol; the sequence must be nonempty. | Amortized `O(1)` |
| `void build(sequence)` | Pushes every symbol at the back. | `O(N * AlphabetSize)` total |

For a constant alphabet, all deque operations take amortized `O(1)` time. The
structure uses `O(N + Q * AlphabetSize)` memory: deleted historical nodes are
kept so internal node references remain stable. Calling `clear()` discards
those historical nodes, while allocated vector capacity may be retained.

`pop_front()` and `pop_back()` assert when called on an empty sequence. Symbols
outside the configured alphabet also cause an assertion failure.

## Example

```cpp
#include "string/deque_eertree.hpp"
#include <iostream>

int main() {
    m1une::string::DequeEertree<> tree;
    tree.push_back('a');
    tree.push_back('b');
    tree.push_front('b');  // "bab"

    std::cout << tree.distinct_palindrome_count() << '\n';  // 3
    std::cout << tree.longest_prefix_length() << '\n';      // 3
    std::cout << tree.longest_suffix_length() << '\n';      // 3

    tree.pop_front();  // "ab"
    std::cout << tree.distinct_palindrome_count() << '\n';  // 2
}
```
