---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/map_trie.hpp
    title: Map Trie
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
  bundledCode: "#line 1 \"verify/string/map_trie.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n\n#line 1 \"string/map_trie.hpp\"\n\n\n\n#include <cassert>\n#include <cstddef>\n\
    #include <functional>\n#include <limits>\n#include <map>\n#include <vector>\n\n\
    namespace m1une {\nnamespace string {\n\n// A multiset trie whose outgoing edges\
    \ are stored in ordered maps.\ntemplate <class Symbol, class Compare = std::less<Symbol>>\n\
    struct MapTrie {\n    using node_id = int;\n    static constexpr node_id null_node\
    \ = -1;\n\n    struct Node {\n        std::map<Symbol, node_id, Compare> child;\n\
    \        int subtree_count = 0;\n        int terminal_count = 0;\n    };\n\n \
    \  private:\n    std::vector<Node> _nodes;\n    int _distinct_size;\n\n    node_id\
    \ new_node() {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    template <class Sequence>\n    node_id find_node(const Sequence& sequence)\
    \ const {\n        node_id node = 0;\n        for (const auto& symbol : sequence)\
    \ {\n            auto iterator = _nodes[node].child.find(symbol);\n          \
    \  if (iterator == _nodes[node].child.end()) return null_node;\n            node\
    \ = iterator->second;\n            if (_nodes[node].subtree_count == 0) return\
    \ null_node;\n        }\n        return node;\n    }\n\n   public:\n    MapTrie()\
    \ : _nodes(1), _distinct_size(0) {}\n\n    int size() const {\n        return\
    \ _nodes[0].subtree_count;\n    }\n\n    int distinct_size() const {\n       \
    \ return _distinct_size;\n    }\n\n    bool empty() const {\n        return size()\
    \ == 0;\n    }\n\n    node_id root() const {\n        return 0;\n    }\n\n   \
    \ const Node& node(node_id id) const {\n        assert(0 <= id && std::size_t(id)\
    \ < _nodes.size());\n        return _nodes[id];\n    }\n\n    template <class\
    \ Sequence>\n    node_id find(const Sequence& sequence) const {\n        return\
    \ find_node(sequence);\n    }\n\n    std::size_t node_count() const {\n      \
    \  return _nodes.size();\n    }\n\n    void reserve(std::size_t node_capacity)\
    \ {\n        _nodes.reserve(node_capacity);\n    }\n\n    void clear() {\n   \
    \     _nodes.clear();\n        _nodes.emplace_back();\n        _distinct_size\
    \ = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const Sequence&\
    \ sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n     \
    \   node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n \
    \       for (const auto& symbol : sequence) {\n            auto iterator = _nodes[node].child.find(symbol);\n\
    \            node_id child;\n            if (iterator == _nodes[node].child.end())\
    \ {\n                child = new_node();\n                _nodes[node].child.emplace(symbol,\
    \ child);\n            } else {\n                child = iterator->second;\n \
    \           }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored sequences beginning with\
    \ prefix.\n    template <class Sequence>\n    int prefix_count(const Sequence&\
    \ prefix) const {\n        node_id node = find_node(prefix);\n        return node\
    \ == null_node ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class\
    \ Sequence>\n    bool starts_with(const Sequence& prefix) const {\n        return\
    \ prefix_count(prefix) != 0;\n    }\n\n    template <class Sequence>\n    bool\
    \ erase_one(const Sequence& sequence) {\n        node_id terminal = find_node(sequence);\n\
    \        if (terminal == null_node || _nodes[terminal].terminal_count == 0) {\n\
    \            return false;\n        }\n\n        node_id node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child.find(symbol)->second;\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        node_id\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child.find(symbol)->second;\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        node_id node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        auto iterator = _nodes[node].child.find(symbol);\n            if (iterator\
    \ == _nodes[node].child.end()) return;\n            node = iterator->second;\n\
    \            if (_nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored sequence that is a prefix.\n    // Returns\
    \ -1 when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/map_trie.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/string/map_trie.test.cpp\"\n#include\
    \ <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <array>\n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
    #include <type_traits>\n#include <utility>\n#include <unistd.h>\n\nnamespace m1une\
    \ {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 13 \"verify/string/map_trie.test.cpp\"\
    \n\nnamespace {\n\nusing Sequence = std::vector<int>;\n\nvoid test_features()\
    \ {\n    using Trie = m1une::string::MapTrie<int>;\n    Trie trie;\n    assert(trie.empty());\n\
    \    assert(trie.node_count() == 1);\n    trie.reserve(128);\n\n    Sequence empty;\n\
    \    Sequence first;\n    first.push_back(1000000000);\n    first.push_back(-7);\n\
    \    Sequence longer = first;\n    longer.push_back(42);\n    Sequence other;\n\
    \    other.push_back(-1000000000);\n\n    const auto empty_node = trie.insert(empty);\n\
    \    const auto first_node = trie.insert(first, 2);\n    trie.insert(longer);\n\
    \    trie.insert(other);\n\n    assert(empty_node == trie.root());\n    assert(first_node\
    \ == trie.find(first));\n    Sequence absent;\n    absent.push_back(5);\n    assert(trie.find(absent)\
    \ == Trie::null_node);\n    assert(trie.node(trie.root()).subtree_count == 5);\n\
    \    assert(trie.node(first_node).terminal_count == 2);\n    assert(trie.node(first_node).subtree_count\
    \ == 3);\n    auto root_edge = trie.node(trie.root()).child.find(1000000000);\n\
    \    assert(root_edge != trie.node(trie.root()).child.end());\n    assert(trie.node(root_edge->second).subtree_count\
    \ == 3);\n    assert(trie.size() == 5);\n    assert(trie.distinct_size() == 4);\n\
    \    assert(trie.count(first) == 2);\n    assert(trie.prefix_count(first) == 3);\n\
    \    assert(trie.prefix_count(empty) == 5);\n    assert(trie.starts_with(longer));\n\
    \    assert(!trie.starts_with(absent));\n    assert(trie.longest_prefix(longer)\
    \ == 3);\n    assert(trie.longest_prefix(absent) == 0);\n\n    std::vector<std::pair<int,\
    \ int>> prefixes;\n    trie.for_each_prefix(longer, [&prefixes](int length, int\
    \ count) {\n        prefixes.emplace_back(length, count);\n    });\n    std::vector<std::pair<int,\
    \ int>> expected;\n    expected.emplace_back(0, 1);\n    expected.emplace_back(2,\
    \ 2);\n    expected.emplace_back(3, 1);\n    assert(prefixes == expected);\n\n\
    \    assert(trie.erase_one(first));\n    assert(trie.count(first) == 1);\n   \
    \ assert(trie.erase_all(first) == 1);\n    assert(!trie.contains(first));\n  \
    \  assert(!trie.erase(first));\n    assert(trie.distinct_size() == 3);\n\n   \
    \ m1une::string::MapTrie<std::string> token_trie;\n    std::vector<std::string>\
    \ tokens;\n    tokens.push_back(\"large alphabet\");\n    tokens.push_back(\"\
    token\");\n    token_trie.insert(tokens);\n    assert(token_trie.contains(tokens));\n\
    \n    m1une::string::MapTrie<int, std::greater<int>> descending_trie;\n    descending_trie.insert(longer);\n\
    \    assert(descending_trie.contains(longer));\n\n    Trie reusable_trie;\n  \
    \  reusable_trie.insert(longer);\n    std::size_t allocated = reusable_trie.node_count();\n\
    \    assert(reusable_trie.erase_all(longer) == 1);\n    assert(reusable_trie.find(longer)\
    \ == Trie::null_node);\n    reusable_trie.insert(longer);\n    assert(reusable_trie.contains(longer));\n\
    \    assert(reusable_trie.node_count() == allocated);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 73;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    m1une::string::MapTrie<int> trie;\n    std::map<Sequence, int> expected;\n\
    \n    for (int step = 0; step < 10000; step++) {\n        int length = int(random()\
    \ % 9);\n        Sequence sequence(length);\n        for (int& symbol : sequence)\
    \ {\n            symbol = int(random() % 2000000001ULL) - 1000000000;\n      \
    \  }\n        if (random() % 2 == 0 && !sequence.empty()) {\n            sequence.back()\
    \ = int(random() % 5) - 2;\n        }\n        int type = int(random() % 6);\n\
    \n        if (type == 0) {\n            int multiplicity = int(random() % 3) +\
    \ 1;\n            trie.insert(sequence, multiplicity);\n            expected[sequence]\
    \ += multiplicity;\n        } else if (type == 1) {\n            [[maybe_unused]]\
    \ bool erased = trie.erase_one(sequence);\n            bool expected_erased =\
    \ expected[sequence] != 0;\n            assert(erased == expected_erased);\n \
    \           if (expected_erased) expected[sequence]--;\n        } else if (type\
    \ == 2) {\n            [[maybe_unused]] int erased = trie.erase_all(sequence);\n\
    \            assert(erased == expected[sequence]);\n            expected[sequence]\
    \ = 0;\n        } else {\n            assert(trie.count(sequence) == expected[sequence]);\n\
    \            [[maybe_unused]] int prefix_count = 0;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.first.size()\
    \ >= sequence.size() &&\n                    std::equal(sequence.begin(), sequence.end(),\
    \ entry.first.begin())\n                ) {\n                    prefix_count\
    \ += entry.second;\n                }\n            }\n            assert(trie.prefix_count(sequence)\
    \ == prefix_count);\n\n            int longest = -1;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.second\
    \ != 0 &&\n                    entry.first.size() <= sequence.size() &&\n    \
    \                std::equal(entry.first.begin(), entry.first.end(), sequence.begin())\n\
    \                ) {\n                    longest = std::max(longest, int(entry.first.size()));\n\
    \                }\n            }\n            assert(trie.longest_prefix(sequence)\
    \ == longest);\n        }\n\n        [[maybe_unused]] int size = 0;\n        [[maybe_unused]]\
    \ int distinct = 0;\n        for (const auto& entry : expected) {\n          \
    \  size += entry.second;\n            if (entry.second != 0) distinct++;\n   \
    \     }\n        assert(trie.size() == size);\n        assert(trie.distinct_size()\
    \ == distinct);\n    }\n\n    trie.clear();\n    assert(trie.empty());\n    assert(trie.distinct_size()\
    \ == 0);\n    assert(trie.node_count() == 1);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_features();\n    test_randomized();\n\n    int q;\n\
    \    fast_input >> q;\n    m1une::string::MapTrie<char> trie;\n    while (q--)\
    \ {\n        std::string command;\n        std::string word;\n        fast_input\
    \ >> command >> word;\n        if (command == \"insert\") {\n            trie.insert(word);\n\
    \        } else {\n            fast_output << (trie.contains(word) ? \"yes\" :\
    \ \"no\") << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n\n#include \"../../string/map_trie.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <map>\n\
    #include <string>\n#include <utility>\n#include <vector>\n\nnamespace {\n\nusing\
    \ Sequence = std::vector<int>;\n\nvoid test_features() {\n    using Trie = m1une::string::MapTrie<int>;\n\
    \    Trie trie;\n    assert(trie.empty());\n    assert(trie.node_count() == 1);\n\
    \    trie.reserve(128);\n\n    Sequence empty;\n    Sequence first;\n    first.push_back(1000000000);\n\
    \    first.push_back(-7);\n    Sequence longer = first;\n    longer.push_back(42);\n\
    \    Sequence other;\n    other.push_back(-1000000000);\n\n    const auto empty_node\
    \ = trie.insert(empty);\n    const auto first_node = trie.insert(first, 2);\n\
    \    trie.insert(longer);\n    trie.insert(other);\n\n    assert(empty_node ==\
    \ trie.root());\n    assert(first_node == trie.find(first));\n    Sequence absent;\n\
    \    absent.push_back(5);\n    assert(trie.find(absent) == Trie::null_node);\n\
    \    assert(trie.node(trie.root()).subtree_count == 5);\n    assert(trie.node(first_node).terminal_count\
    \ == 2);\n    assert(trie.node(first_node).subtree_count == 3);\n    auto root_edge\
    \ = trie.node(trie.root()).child.find(1000000000);\n    assert(root_edge != trie.node(trie.root()).child.end());\n\
    \    assert(trie.node(root_edge->second).subtree_count == 3);\n    assert(trie.size()\
    \ == 5);\n    assert(trie.distinct_size() == 4);\n    assert(trie.count(first)\
    \ == 2);\n    assert(trie.prefix_count(first) == 3);\n    assert(trie.prefix_count(empty)\
    \ == 5);\n    assert(trie.starts_with(longer));\n    assert(!trie.starts_with(absent));\n\
    \    assert(trie.longest_prefix(longer) == 3);\n    assert(trie.longest_prefix(absent)\
    \ == 0);\n\n    std::vector<std::pair<int, int>> prefixes;\n    trie.for_each_prefix(longer,\
    \ [&prefixes](int length, int count) {\n        prefixes.emplace_back(length,\
    \ count);\n    });\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(2, 2);\n    expected.emplace_back(3, 1);\n  \
    \  assert(prefixes == expected);\n\n    assert(trie.erase_one(first));\n    assert(trie.count(first)\
    \ == 1);\n    assert(trie.erase_all(first) == 1);\n    assert(!trie.contains(first));\n\
    \    assert(!trie.erase(first));\n    assert(trie.distinct_size() == 3);\n\n \
    \   m1une::string::MapTrie<std::string> token_trie;\n    std::vector<std::string>\
    \ tokens;\n    tokens.push_back(\"large alphabet\");\n    tokens.push_back(\"\
    token\");\n    token_trie.insert(tokens);\n    assert(token_trie.contains(tokens));\n\
    \n    m1une::string::MapTrie<int, std::greater<int>> descending_trie;\n    descending_trie.insert(longer);\n\
    \    assert(descending_trie.contains(longer));\n\n    Trie reusable_trie;\n  \
    \  reusable_trie.insert(longer);\n    std::size_t allocated = reusable_trie.node_count();\n\
    \    assert(reusable_trie.erase_all(longer) == 1);\n    assert(reusable_trie.find(longer)\
    \ == Trie::null_node);\n    reusable_trie.insert(longer);\n    assert(reusable_trie.contains(longer));\n\
    \    assert(reusable_trie.node_count() == allocated);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 73;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    m1une::string::MapTrie<int> trie;\n    std::map<Sequence, int> expected;\n\
    \n    for (int step = 0; step < 10000; step++) {\n        int length = int(random()\
    \ % 9);\n        Sequence sequence(length);\n        for (int& symbol : sequence)\
    \ {\n            symbol = int(random() % 2000000001ULL) - 1000000000;\n      \
    \  }\n        if (random() % 2 == 0 && !sequence.empty()) {\n            sequence.back()\
    \ = int(random() % 5) - 2;\n        }\n        int type = int(random() % 6);\n\
    \n        if (type == 0) {\n            int multiplicity = int(random() % 3) +\
    \ 1;\n            trie.insert(sequence, multiplicity);\n            expected[sequence]\
    \ += multiplicity;\n        } else if (type == 1) {\n            [[maybe_unused]]\
    \ bool erased = trie.erase_one(sequence);\n            bool expected_erased =\
    \ expected[sequence] != 0;\n            assert(erased == expected_erased);\n \
    \           if (expected_erased) expected[sequence]--;\n        } else if (type\
    \ == 2) {\n            [[maybe_unused]] int erased = trie.erase_all(sequence);\n\
    \            assert(erased == expected[sequence]);\n            expected[sequence]\
    \ = 0;\n        } else {\n            assert(trie.count(sequence) == expected[sequence]);\n\
    \            [[maybe_unused]] int prefix_count = 0;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.first.size()\
    \ >= sequence.size() &&\n                    std::equal(sequence.begin(), sequence.end(),\
    \ entry.first.begin())\n                ) {\n                    prefix_count\
    \ += entry.second;\n                }\n            }\n            assert(trie.prefix_count(sequence)\
    \ == prefix_count);\n\n            int longest = -1;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.second\
    \ != 0 &&\n                    entry.first.size() <= sequence.size() &&\n    \
    \                std::equal(entry.first.begin(), entry.first.end(), sequence.begin())\n\
    \                ) {\n                    longest = std::max(longest, int(entry.first.size()));\n\
    \                }\n            }\n            assert(trie.longest_prefix(sequence)\
    \ == longest);\n        }\n\n        [[maybe_unused]] int size = 0;\n        [[maybe_unused]]\
    \ int distinct = 0;\n        for (const auto& entry : expected) {\n          \
    \  size += entry.second;\n            if (entry.second != 0) distinct++;\n   \
    \     }\n        assert(trie.size() == size);\n        assert(trie.distinct_size()\
    \ == distinct);\n    }\n\n    trie.clear();\n    assert(trie.empty());\n    assert(trie.distinct_size()\
    \ == 0);\n    assert(trie.node_count() == 1);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_features();\n    test_randomized();\n\n    int q;\n\
    \    fast_input >> q;\n    m1une::string::MapTrie<char> trie;\n    while (q--)\
    \ {\n        std::string command;\n        std::string word;\n        fast_input\
    \ >> command >> word;\n        if (command == \"insert\") {\n            trie.insert(word);\n\
    \        } else {\n            fast_output << (trie.contains(word) ? \"yes\" :\
    \ \"no\") << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - string/map_trie.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/map_trie.test.cpp
  requiredBy: []
  timestamp: '2026-08-11 13:50:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/map_trie.test.cpp
layout: document
redirect_from:
- /verify/verify/string/map_trie.test.cpp
- /verify/verify/string/map_trie.test.cpp.html
title: verify/string/map_trie.test.cpp
---
