---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/deque_eertree.hpp
    title: Deque Eertree
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
    PROBLEM: https://judge.yosupo.jp/problem/palindromes_in_deque
    links:
    - https://judge.yosupo.jp/problem/palindromes_in_deque
  bundledCode: "#line 1 \"verify/string/deque_eertree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/palindromes_in_deque\"\n\n#line 1 \"string/deque_eertree.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstddef>\n#include <deque>\n\
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
    \ FirstCharacter>;\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/string/deque_eertree.test.cpp\"\n\n#include <algorithm>\n#line 7\
    \ \"verify/string/deque_eertree.test.cpp\"\n#include <cstdint>\n#line 9 \"verify/string/deque_eertree.test.cpp\"\
    \n#include <set>\n#include <string>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n\
    #line 5 \"utilities/fast_io.hpp\"\n#include <cerrno>\n#include <charconv>\n#line\
    \ 8 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line 11\
    \ \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#line 14\
    \ \"utilities/fast_io.hpp\"\n#include <sys/stat.h>\n#include <type_traits>\n#include\
    \ <utility>\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\n\
    namespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/string/deque_eertree.test.cpp\"\
    \n\nnamespace {\n\nstruct NaiveResult {\n    int distinct;\n    int longest_prefix;\n\
    \    int longest_suffix;\n};\n\nbool is_palindrome(const std::string& text, int\
    \ left, int right) {\n    while (left < right) {\n        right--;\n        if\
    \ (text[left] != text[right]) return false;\n        left++;\n    }\n    return\
    \ true;\n}\n\nNaiveResult solve_naively(const std::deque<char>& sequence) {\n\
    \    std::string text(sequence.begin(), sequence.end());\n    std::set<std::string>\
    \ distinct;\n    int longest_prefix = 0;\n    int longest_suffix = 0;\n    for\
    \ (int left = 0; left < int(text.size()); left++) {\n        for (int right =\
    \ left + 1; right <= int(text.size()); right++) {\n            if (!is_palindrome(text,\
    \ left, right)) continue;\n            distinct.insert(text.substr(left, right\
    \ - left));\n            if (left == 0) longest_prefix = std::max(longest_prefix,\
    \ right);\n            if (right == int(text.size())) longest_suffix = std::max(longest_suffix,\
    \ right - left);\n        }\n    }\n    return {int(distinct.size()), longest_prefix,\
    \ longest_suffix};\n}\n\nvoid check(\n    const m1une::string::DequeEertree<4,\
    \ 'a'>& tree,\n    const std::deque<char>& sequence\n) {\n    NaiveResult expected\
    \ = solve_naively(sequence);\n    assert(tree.size() == expected.distinct);\n\
    \    assert(tree.text_length() == int(sequence.size()));\n    assert(tree.empty()\
    \ == sequence.empty());\n    assert(tree.distinct_palindrome_count() == expected.distinct);\n\
    \    assert(tree.longest_prefix_length() == expected.longest_prefix);\n    assert(tree.longest_suffix_length()\
    \ == expected.longest_suffix);\n}\n\nvoid test_features() {\n    m1une::string::DequeEertree<4,\
    \ 'a'> tree;\n    tree.reserve(32);\n    std::deque<char> sequence;\n    check(tree,\
    \ sequence);\n\n    tree.push_back('a');\n    sequence.push_back('a');\n    tree.push_back('b');\n\
    \    sequence.push_back('b');\n    tree.push_front('b');\n    sequence.push_front('b');\n\
    \    check(tree, sequence);\n\n    tree.pop_back();\n    sequence.pop_back();\n\
    \    check(tree, sequence);\n    tree.clear();\n    sequence.clear();\n    check(tree,\
    \ sequence);\n\n    m1une::string::DoubleEndedEertree<4, 'a'> built(std::string(\"\
    abacaba\"));\n    assert(built.text_length() == 7);\n    assert(built.size() ==\
    \ 7);\n    assert(built.distinct_palindrome_count() == 7);\n    assert(built.longest_prefix_length()\
    \ == 7);\n    assert(built.longest_suffix_length() == 7);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 817;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1500; trial++) {\n        m1une::string::DequeEertree<4,\
    \ 'a'> tree;\n        tree.reserve(120);\n        std::deque<char> sequence;\n\
    \        for (int operation = 0; operation < 120; operation++) {\n           \
    \ int type = sequence.empty() ? int(random() % 2) : int(random() % 4);\n     \
    \       char symbol = char('a' + random() % 4);\n            if (type == 0) {\n\
    \                tree.push_front(symbol);\n                sequence.push_front(symbol);\n\
    \            } else if (type == 1) {\n                tree.push_back(symbol);\n\
    \                sequence.push_back(symbol);\n            } else if (type == 2)\
    \ {\n                tree.pop_front();\n                sequence.pop_front();\n\
    \            } else {\n                tree.pop_back();\n                sequence.pop_back();\n\
    \            }\n            check(tree, sequence);\n        }\n    }\n}\n\n} \
    \ // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n    test_randomized();\n\
    \n    int query_count;\n    fast_input >> query_count;\n    m1une::string::DequeEertree<>\
    \ tree;\n    tree.reserve(query_count);\n    for (int query = 0; query < query_count;\
    \ query++) {\n        int type;\n        fast_input >> type;\n        if (type\
    \ == 0) {\n            char symbol;\n            fast_input >> symbol;\n     \
    \       tree.push_front(symbol);\n        } else if (type == 1) {\n          \
    \  char symbol;\n            fast_input >> symbol;\n            tree.push_back(symbol);\n\
    \        } else if (type == 2) {\n            tree.pop_front();\n        } else\
    \ {\n            assert(type == 3);\n            tree.pop_back();\n        }\n\
    \        fast_output << tree.distinct_palindrome_count() << ' '\n            \
    \        << tree.longest_prefix_length() << ' '\n                    << tree.longest_suffix_length()\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/palindromes_in_deque\"\n\
    \n#include \"../../string/deque_eertree.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <deque>\n#include <set>\n#include <string>\n\
    #include \"../../utilities/fast_io.hpp\"\n\nnamespace {\n\nstruct NaiveResult\
    \ {\n    int distinct;\n    int longest_prefix;\n    int longest_suffix;\n};\n\
    \nbool is_palindrome(const std::string& text, int left, int right) {\n    while\
    \ (left < right) {\n        right--;\n        if (text[left] != text[right]) return\
    \ false;\n        left++;\n    }\n    return true;\n}\n\nNaiveResult solve_naively(const\
    \ std::deque<char>& sequence) {\n    std::string text(sequence.begin(), sequence.end());\n\
    \    std::set<std::string> distinct;\n    int longest_prefix = 0;\n    int longest_suffix\
    \ = 0;\n    for (int left = 0; left < int(text.size()); left++) {\n        for\
    \ (int right = left + 1; right <= int(text.size()); right++) {\n            if\
    \ (!is_palindrome(text, left, right)) continue;\n            distinct.insert(text.substr(left,\
    \ right - left));\n            if (left == 0) longest_prefix = std::max(longest_prefix,\
    \ right);\n            if (right == int(text.size())) longest_suffix = std::max(longest_suffix,\
    \ right - left);\n        }\n    }\n    return {int(distinct.size()), longest_prefix,\
    \ longest_suffix};\n}\n\nvoid check(\n    const m1une::string::DequeEertree<4,\
    \ 'a'>& tree,\n    const std::deque<char>& sequence\n) {\n    NaiveResult expected\
    \ = solve_naively(sequence);\n    assert(tree.size() == expected.distinct);\n\
    \    assert(tree.text_length() == int(sequence.size()));\n    assert(tree.empty()\
    \ == sequence.empty());\n    assert(tree.distinct_palindrome_count() == expected.distinct);\n\
    \    assert(tree.longest_prefix_length() == expected.longest_prefix);\n    assert(tree.longest_suffix_length()\
    \ == expected.longest_suffix);\n}\n\nvoid test_features() {\n    m1une::string::DequeEertree<4,\
    \ 'a'> tree;\n    tree.reserve(32);\n    std::deque<char> sequence;\n    check(tree,\
    \ sequence);\n\n    tree.push_back('a');\n    sequence.push_back('a');\n    tree.push_back('b');\n\
    \    sequence.push_back('b');\n    tree.push_front('b');\n    sequence.push_front('b');\n\
    \    check(tree, sequence);\n\n    tree.pop_back();\n    sequence.pop_back();\n\
    \    check(tree, sequence);\n    tree.clear();\n    sequence.clear();\n    check(tree,\
    \ sequence);\n\n    m1une::string::DoubleEndedEertree<4, 'a'> built(std::string(\"\
    abacaba\"));\n    assert(built.text_length() == 7);\n    assert(built.size() ==\
    \ 7);\n    assert(built.distinct_palindrome_count() == 7);\n    assert(built.longest_prefix_length()\
    \ == 7);\n    assert(built.longest_suffix_length() == 7);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 817;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1500; trial++) {\n        m1une::string::DequeEertree<4,\
    \ 'a'> tree;\n        tree.reserve(120);\n        std::deque<char> sequence;\n\
    \        for (int operation = 0; operation < 120; operation++) {\n           \
    \ int type = sequence.empty() ? int(random() % 2) : int(random() % 4);\n     \
    \       char symbol = char('a' + random() % 4);\n            if (type == 0) {\n\
    \                tree.push_front(symbol);\n                sequence.push_front(symbol);\n\
    \            } else if (type == 1) {\n                tree.push_back(symbol);\n\
    \                sequence.push_back(symbol);\n            } else if (type == 2)\
    \ {\n                tree.pop_front();\n                sequence.pop_front();\n\
    \            } else {\n                tree.pop_back();\n                sequence.pop_back();\n\
    \            }\n            check(tree, sequence);\n        }\n    }\n}\n\n} \
    \ // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n    test_randomized();\n\
    \n    int query_count;\n    fast_input >> query_count;\n    m1une::string::DequeEertree<>\
    \ tree;\n    tree.reserve(query_count);\n    for (int query = 0; query < query_count;\
    \ query++) {\n        int type;\n        fast_input >> type;\n        if (type\
    \ == 0) {\n            char symbol;\n            fast_input >> symbol;\n     \
    \       tree.push_front(symbol);\n        } else if (type == 1) {\n          \
    \  char symbol;\n            fast_input >> symbol;\n            tree.push_back(symbol);\n\
    \        } else if (type == 2) {\n            tree.pop_front();\n        } else\
    \ {\n            assert(type == 3);\n            tree.pop_back();\n        }\n\
    \        fast_output << tree.distinct_palindrome_count() << ' '\n            \
    \        << tree.longest_prefix_length() << ' '\n                    << tree.longest_suffix_length()\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - string/deque_eertree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/deque_eertree.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/deque_eertree.test.cpp
layout: document
redirect_from:
- /verify/verify/string/deque_eertree.test.cpp
- /verify/verify/string/deque_eertree.test.cpp.html
title: verify/string/deque_eertree.test.cpp
---
