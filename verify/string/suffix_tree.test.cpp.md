---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix_tree.hpp
    title: Suffix Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"verify/string/suffix_tree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/number_of_substrings\"\n\n#line 1 \"string/suffix_tree.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\n\
    struct SuffixTree {\n    static_assert(0 < AlphabetSize);\n\n    using node_id\
    \ = int;\n    static constexpr node_id root_node = 0;\n    static constexpr node_id\
    \ null_node = -1;\n    static constexpr int terminal_symbol = AlphabetSize;\n\n\
    \    struct Node {\n        std::array<node_id, AlphabetSize + 1> next;\n    \
    \    node_id suffix_link;\n        node_id parent;\n        int left;\n      \
    \  int right;\n        int suffix_start;\n        int representative_suffix;\n\
    \        int leaf_count;\n\n        Node(int left_value = 0, int right_value =\
    \ 0, node_id parent_value = null_node)\n            : suffix_link(null_node),\n\
    \              parent(parent_value),\n              left(left_value),\n      \
    \        right(right_value),\n              suffix_start(-1),\n              representative_suffix(-1),\n\
    \              leaf_count(0) {\n            next.fill(null_node);\n        }\n\
    \    };\n\n    struct Locus {\n        node_id node;\n        int offset;\n\n\
    \        explicit operator bool() const {\n            return node != null_node;\n\
    \        }\n\n        friend bool operator==(const Locus&, const Locus&) = default;\n\
    \    };\n\n   private:\n    struct ActivePoint {\n        node_id node;\n    \
    \    int offset;\n    };\n\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _text;\n    ActivePoint _active;\n    int _text_length;\n\n    template <class\
    \ Symbol>\n    static int symbol_index(const Symbol& symbol) {\n        int index\
    \ = int(symbol) - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n\
    \        return index;\n    }\n\n    int edge_length_unchecked(node_id id) const\
    \ {\n        return _nodes[id].right - _nodes[id].left;\n    }\n\n    node_id\
    \ new_node(int left, int right, node_id parent) {\n        assert(_nodes.size()\
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
    \      for (node_id child : _nodes[id].next) {\n                if (child == null_node)\
    \ continue;\n                depth[child] = depth[id] + edge_length_unchecked(child);\n\
    \                order.push_back(child);\n            }\n        }\n\n       \
    \ for (int i = int(order.size()) - 1; i >= 0; i--) {\n            node_id id =\
    \ order[i];\n            bool leaf = true;\n            for (node_id child : _nodes[id].next)\
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
    \ const {\n        assert(0 <= id && id < node_count());\n        for (int symbol\
    \ = 0; symbol <= terminal_symbol; symbol++) {\n            node_id child_id =\
    \ _nodes[id].next[symbol];\n            if (child_id != null_node) callback(symbol,\
    \ child_id);\n        }\n    }\n\n    void clear() {\n        _text.clear();\n\
    \        _text.push_back(terminal_symbol);\n        _text_length = 0;\n      \
    \  initialize();\n    }\n\n    template <class Sequence>\n    void build(const\
    \ Sequence& sequence) {\n        _text.clear();\n        for (const auto& symbol\
    \ : sequence) _text.push_back(symbol_index(symbol));\n        assert(_text.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _text_length = int(_text.size());\n\
    \        _text.push_back(terminal_symbol);\n        initialize();\n    }\n\n \
    \   template <class Sequence>\n    Locus find(const Sequence& sequence) const\
    \ {\n        ActivePoint point = {root_node, 0};\n        for (const auto& value\
    \ : sequence) {\n            int symbol = symbol_index(value);\n            if\
    \ (point.offset == edge_length_unchecked(point.node)) {\n                point\
    \ = {_nodes[point.node].next[symbol], 0};\n                if (point.node == null_node)\
    \ return {null_node, 0};\n            }\n            if (_text[_nodes[point.node].left\
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
    \ string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/suffix_tree.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
    #line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/string/suffix_tree.test.cpp\"\
    \n#include <map>\n#include <set>\n#line 14 \"verify/string/suffix_tree.test.cpp\"\
    \n\nnamespace {\n\nvoid test_features() {\n    using Tree = m1une::string::SuffixTree<>;\n\
    \    Tree empty;\n    assert(empty.empty());\n    assert(empty.text_length() ==\
    \ 0);\n    assert(empty.node_count() == 2);\n    assert(empty.count_occurrences(std::string())\
    \ == 1);\n    assert(empty.distinct_substring_count() == 0);\n\n    std::string\
    \ text = \"ababa\";\n    Tree tree(text);\n    assert(!tree.empty());\n    assert(tree.text_length()\
    \ == 5);\n    assert(tree.root() == Tree::root_node);\n    assert(tree.node_count()\
    \ <= 2 * int(text.size()) + 1);\n    assert(tree.contains(std::string(\"bab\"\
    )));\n    assert(!tree.contains(std::string(\"abb\")));\n    assert(tree.contains(std::string()));\n\
    \    assert(tree.count_occurrences(std::string(\"a\")) == 3);\n    assert(tree.count_occurrences(std::string(\"\
    aba\")) == 2);\n    assert(tree.count_occurrences(std::string(\"ababa\")) == 1);\n\
    \    assert(tree.count_occurrences(std::string()) == 6);\n    assert(tree.distinct_substring_count()\
    \ == 9);\n\n    auto occurrence = tree.representative_occurrence(std::string(\"\
    bab\"));\n    assert(text.substr(occurrence.first, occurrence.second - occurrence.first)\
    \ == \"bab\");\n    assert((tree.representative_occurrence(std::string(\"abb\"\
    )) == std::pair<int, int>(-1, -1)));\n\n    int root_children = 0;\n    bool has_terminal_leaf\
    \ = false;\n    tree.for_each_child(tree.root(), [&](int symbol, int child) {\n\
    \        root_children++;\n        assert(tree.node(child).parent == tree.root());\n\
    \        if (symbol == Tree::terminal_symbol) {\n            has_terminal_leaf\
    \ = true;\n            assert(tree.is_leaf(child));\n            assert(tree.node(child).suffix_start\
    \ == int(text.size()));\n        }\n    });\n    assert(root_children == 3);\n\
    \    assert(has_terminal_leaf);\n    assert(tree.child(tree.root(), 'a') != Tree::null_node);\n\
    \    assert(tree.child_by_index(tree.root(), Tree::terminal_symbol) != Tree::null_node);\n\
    \n    m1une::string::SuffixTree<10, '0'> digits(std::string(\"012012\"));\n  \
    \  assert(digits.contains(std::string(\"201\")));\n\n    tree.clear();\n    assert(tree.empty());\n\
    \    assert(tree.node_count() == 2);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 918273645;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 3000; trial++) {\n        int n = int(random() % 55);\n \
    \       std::string text(n, 'a');\n        for (char& character : text) character\
    \ = char('a' + random() % 4);\n        m1une::string::SuffixTree<4, 'a'> tree(text);\n\
    \n        assert(tree.node_count() <= std::max(2, 2 * n + 1));\n        assert(tree.node(tree.root()).parent\
    \ == tree.null_node);\n        assert(tree.node(tree.root()).suffix_link == tree.root());\n\
    \n        std::map<std::string, int> expected;\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                expected[text.substr(left, right - left)]++;\n          \
    \  }\n        }\n        assert(tree.distinct_substring_count() == int(expected.size()));\n\
    \        assert(tree.count_occurrences(std::string()) == n + 1);\n\n        for\
    \ (const auto& entry : expected) {\n            const std::string& substring =\
    \ entry.first;\n            int count = entry.second;\n            assert(tree.contains(substring));\n\
    \            assert(tree.count_occurrences(substring) == count);\n           \
    \ auto [left, right] = tree.representative_occurrence(substring);\n          \
    \  assert(0 <= left && left < right && right <= n);\n            assert(text.substr(left,\
    \ right - left) == substring);\n        }\n\n        std::set<int> suffix_starts;\n\
    \        int leaves = 0;\n        for (int id = 0; id < tree.node_count(); id++)\
    \ {\n            const auto& node = tree.node(id);\n            assert(0 <= node.left\
    \ && node.left <= node.right && node.right <= n + 1);\n            if (id != tree.root())\
    \ {\n                assert(0 <= node.parent && node.parent < tree.node_count());\n\
    \                assert(tree.edge_length(id) > 0);\n            }\n          \
    \  if (tree.is_leaf(id)) {\n                leaves++;\n                assert(0\
    \ <= node.suffix_start && node.suffix_start <= n);\n                suffix_starts.insert(node.suffix_start);\n\
    \                assert(node.leaf_count == 1);\n            } else {\n       \
    \         assert(node.suffix_start == -1);\n                assert(node.leaf_count\
    \ >= (id == tree.root() ? 1 : 2));\n            }\n        }\n        assert(leaves\
    \ == n + 1);\n        assert(int(suffix_starts.size()) == n + 1);\n        for\
    \ (int start = 0; start <= n; start++) assert(suffix_starts.count(start));\n\n\
    \        for (int length = 0; length <= n; length++) {\n            std::string\
    \ suffix = text.substr(n - length);\n            assert(tree.contains(suffix));\n\
    \            assert(tree.count_occurrences(suffix) >= 1);\n        }\n\n     \
    \   int query_length = int(random() % 25);\n        std::string query(query_length,\
    \ 'a');\n        for (char& character : query) character = char('a' + random()\
    \ % 4);\n        int naive_count = 0;\n        for (int position = 0; position\
    \ + query_length <= n; position++) {\n            if (text.compare(position, query_length,\
    \ query) == 0) naive_count++;\n        }\n        if (query.empty()) naive_count\
    \ = n + 1;\n        assert(tree.count_occurrences(query) == naive_count);\n  \
    \  }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n    test_randomized();\n\
    \n    std::string text;\n    fast_input >> text;\n    m1une::string::SuffixTree<>\
    \ tree(text);\n    fast_output << tree.distinct_substring_count() << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    \n#include \"../../string/suffix_tree.hpp\"\n\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <map>\n\
    #include <set>\n#include <string>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ {\n\nvoid test_features() {\n    using Tree = m1une::string::SuffixTree<>;\n\
    \    Tree empty;\n    assert(empty.empty());\n    assert(empty.text_length() ==\
    \ 0);\n    assert(empty.node_count() == 2);\n    assert(empty.count_occurrences(std::string())\
    \ == 1);\n    assert(empty.distinct_substring_count() == 0);\n\n    std::string\
    \ text = \"ababa\";\n    Tree tree(text);\n    assert(!tree.empty());\n    assert(tree.text_length()\
    \ == 5);\n    assert(tree.root() == Tree::root_node);\n    assert(tree.node_count()\
    \ <= 2 * int(text.size()) + 1);\n    assert(tree.contains(std::string(\"bab\"\
    )));\n    assert(!tree.contains(std::string(\"abb\")));\n    assert(tree.contains(std::string()));\n\
    \    assert(tree.count_occurrences(std::string(\"a\")) == 3);\n    assert(tree.count_occurrences(std::string(\"\
    aba\")) == 2);\n    assert(tree.count_occurrences(std::string(\"ababa\")) == 1);\n\
    \    assert(tree.count_occurrences(std::string()) == 6);\n    assert(tree.distinct_substring_count()\
    \ == 9);\n\n    auto occurrence = tree.representative_occurrence(std::string(\"\
    bab\"));\n    assert(text.substr(occurrence.first, occurrence.second - occurrence.first)\
    \ == \"bab\");\n    assert((tree.representative_occurrence(std::string(\"abb\"\
    )) == std::pair<int, int>(-1, -1)));\n\n    int root_children = 0;\n    bool has_terminal_leaf\
    \ = false;\n    tree.for_each_child(tree.root(), [&](int symbol, int child) {\n\
    \        root_children++;\n        assert(tree.node(child).parent == tree.root());\n\
    \        if (symbol == Tree::terminal_symbol) {\n            has_terminal_leaf\
    \ = true;\n            assert(tree.is_leaf(child));\n            assert(tree.node(child).suffix_start\
    \ == int(text.size()));\n        }\n    });\n    assert(root_children == 3);\n\
    \    assert(has_terminal_leaf);\n    assert(tree.child(tree.root(), 'a') != Tree::null_node);\n\
    \    assert(tree.child_by_index(tree.root(), Tree::terminal_symbol) != Tree::null_node);\n\
    \n    m1une::string::SuffixTree<10, '0'> digits(std::string(\"012012\"));\n  \
    \  assert(digits.contains(std::string(\"201\")));\n\n    tree.clear();\n    assert(tree.empty());\n\
    \    assert(tree.node_count() == 2);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 918273645;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 3000; trial++) {\n        int n = int(random() % 55);\n \
    \       std::string text(n, 'a');\n        for (char& character : text) character\
    \ = char('a' + random() % 4);\n        m1une::string::SuffixTree<4, 'a'> tree(text);\n\
    \n        assert(tree.node_count() <= std::max(2, 2 * n + 1));\n        assert(tree.node(tree.root()).parent\
    \ == tree.null_node);\n        assert(tree.node(tree.root()).suffix_link == tree.root());\n\
    \n        std::map<std::string, int> expected;\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                expected[text.substr(left, right - left)]++;\n          \
    \  }\n        }\n        assert(tree.distinct_substring_count() == int(expected.size()));\n\
    \        assert(tree.count_occurrences(std::string()) == n + 1);\n\n        for\
    \ (const auto& entry : expected) {\n            const std::string& substring =\
    \ entry.first;\n            int count = entry.second;\n            assert(tree.contains(substring));\n\
    \            assert(tree.count_occurrences(substring) == count);\n           \
    \ auto [left, right] = tree.representative_occurrence(substring);\n          \
    \  assert(0 <= left && left < right && right <= n);\n            assert(text.substr(left,\
    \ right - left) == substring);\n        }\n\n        std::set<int> suffix_starts;\n\
    \        int leaves = 0;\n        for (int id = 0; id < tree.node_count(); id++)\
    \ {\n            const auto& node = tree.node(id);\n            assert(0 <= node.left\
    \ && node.left <= node.right && node.right <= n + 1);\n            if (id != tree.root())\
    \ {\n                assert(0 <= node.parent && node.parent < tree.node_count());\n\
    \                assert(tree.edge_length(id) > 0);\n            }\n          \
    \  if (tree.is_leaf(id)) {\n                leaves++;\n                assert(0\
    \ <= node.suffix_start && node.suffix_start <= n);\n                suffix_starts.insert(node.suffix_start);\n\
    \                assert(node.leaf_count == 1);\n            } else {\n       \
    \         assert(node.suffix_start == -1);\n                assert(node.leaf_count\
    \ >= (id == tree.root() ? 1 : 2));\n            }\n        }\n        assert(leaves\
    \ == n + 1);\n        assert(int(suffix_starts.size()) == n + 1);\n        for\
    \ (int start = 0; start <= n; start++) assert(suffix_starts.count(start));\n\n\
    \        for (int length = 0; length <= n; length++) {\n            std::string\
    \ suffix = text.substr(n - length);\n            assert(tree.contains(suffix));\n\
    \            assert(tree.count_occurrences(suffix) >= 1);\n        }\n\n     \
    \   int query_length = int(random() % 25);\n        std::string query(query_length,\
    \ 'a');\n        for (char& character : query) character = char('a' + random()\
    \ % 4);\n        int naive_count = 0;\n        for (int position = 0; position\
    \ + query_length <= n; position++) {\n            if (text.compare(position, query_length,\
    \ query) == 0) naive_count++;\n        }\n        if (query.empty()) naive_count\
    \ = n + 1;\n        assert(tree.count_occurrences(query) == naive_count);\n  \
    \  }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n    test_randomized();\n\
    \n    std::string text;\n    fast_input >> text;\n    m1une::string::SuffixTree<>\
    \ tree(text);\n    fast_output << tree.distinct_substring_count() << '\\n';\n\
    }\n"
  dependsOn:
  - string/suffix_tree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/suffix_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-27 02:08:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/suffix_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/string/suffix_tree.test.cpp
- /verify/verify/string/suffix_tree.test.cpp.html
title: verify/string/suffix_tree.test.cpp
---
