---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
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
    PROBLEM: https://judge.yosupo.jp/problem/eertree
    links:
    - https://judge.yosupo.jp/problem/eertree
  bundledCode: "#line 1 \"verify/string/eertree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/eertree\"\
    \n\n#line 1 \"string/eertree.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\ntemplate <int AlphabetSize = 26, int\
    \ FirstCharacter = 'a'>\nstruct Eertree {\n    static_assert(0 < AlphabetSize);\n\
    \n    using node_id = int;\n    static constexpr node_id even_root = 0;\n    static\
    \ constexpr node_id odd_root = 1;\n    static constexpr node_id null_node = -1;\n\
    \n    struct Node {\n        std::array<node_id, AlphabetSize> next;\n       \
    \ node_id suffix_link;\n        node_id series_link;\n        int length;\n  \
    \      int diff;\n        int suffix_count;\n        int first_end;\n        long\
    \ long suffix_occurrences;\n\n        Node(int length_value = 0, node_id suffix_link_value\
    \ = even_root, node_id series_link_value = even_root)\n            : suffix_link(suffix_link_value),\n\
    \              series_link(series_link_value),\n              length(length_value),\n\
    \              diff(0),\n              suffix_count(0),\n              first_end(0),\n\
    \              suffix_occurrences(0) {\n            next.fill(null_node);\n  \
    \      }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _text;\n    std::vector<node_id> _longest_suffix;\n    node_id _last;\n\n  \
    \  template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    node_id find_extendable(node_id\
    \ node, int position, int symbol) const {\n        while (true) {\n          \
    \  int length = _nodes[node].length;\n            int left = position - length\
    \ - 1;\n            if (0 <= left && _text[left] == symbol) return node;\n   \
    \         node = _nodes[node].suffix_link;\n        }\n    }\n\n    node_id new_node(int\
    \ length) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(length);\n        return int(_nodes.size()) - 1;\n\
    \    }\n\n   public:\n    Eertree() {\n        clear();\n    }\n\n    template\
    \ <class Sequence>\n    explicit Eertree(const Sequence& sequence) {\n       \
    \ clear();\n        build(sequence);\n    }\n\n    int size() const {\n      \
    \  return int(_nodes.size()) - 2;\n    }\n\n    bool empty() const {\n       \
    \ return size() == 0;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int text_length() const {\n        return int(_text.size());\n \
    \   }\n\n    node_id last() const {\n        return _last;\n    }\n\n    int longest_suffix_length()\
    \ const {\n        return _nodes[_last].length;\n    }\n\n    const Node& node(node_id\
    \ id) const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id];\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    node_id longest_suffix_node(int prefix_length) const {\n       \
    \ assert(1 <= prefix_length && prefix_length <= text_length());\n        return\
    \ _longest_suffix[prefix_length - 1];\n    }\n\n    const std::vector<node_id>&\
    \ longest_suffix_nodes() const {\n        return _longest_suffix;\n    }\n\n \
    \   template <class Callback>\n    void for_each_suffix(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        while (id >=\
    \ 2) {\n            callback(id);\n            id = _nodes[id].suffix_link;\n\
    \        }\n    }\n\n    template <class Callback>\n    void for_each_suffix(Callback\
    \ callback) const {\n        for_each_suffix(_last, callback);\n    }\n\n    void\
    \ reserve(std::size_t text_capacity) {\n        _text.reserve(text_capacity);\n\
    \        _longest_suffix.reserve(text_capacity);\n        _nodes.reserve(text_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _nodes.clear();\n        _nodes.emplace_back(0,\
    \ odd_root, even_root);\n        _nodes.emplace_back(-1, odd_root, odd_root);\n\
    \        _text.clear();\n        _longest_suffix.clear();\n        _last = even_root;\n\
    \    }\n\n    template <class Symbol>\n    node_id add(const Symbol& value) {\n\
    \        int symbol = symbol_index(value);\n        int position = int(_text.size());\n\
    \        _text.push_back(symbol);\n\n        node_id current = find_extendable(_last,\
    \ position, symbol);\n        node_id next = _nodes[current].next[symbol];\n \
    \       if (next == null_node) {\n            int length = _nodes[current].length\
    \ + 2;\n            next = new_node(length);\n            _nodes[current].next[symbol]\
    \ = next;\n\n            node_id suffix_link = even_root;\n            if (length\
    \ != 1) {\n                node_id candidate = find_extendable(_nodes[current].suffix_link,\
    \ position, symbol);\n                suffix_link = _nodes[candidate].next[symbol];\n\
    \                assert(suffix_link != null_node);\n            }\n\n        \
    \    Node& created = _nodes[next];\n            created.suffix_link = suffix_link;\n\
    \            created.diff = created.length - _nodes[suffix_link].length;\n   \
    \         created.series_link =\n                created.diff == _nodes[suffix_link].diff\
    \ ? _nodes[suffix_link].series_link : suffix_link;\n            created.suffix_count\
    \ = _nodes[suffix_link].suffix_count + 1;\n            created.first_end = position\
    \ + 1;\n        }\n\n        _last = next;\n        _nodes[_last].suffix_occurrences++;\n\
    \        _longest_suffix.push_back(_last);\n        return _last;\n    }\n\n \
    \   template <class Sequence>\n    void build(const Sequence& sequence) {\n  \
    \      for (const auto& symbol : sequence) add(symbol);\n    }\n\n    std::vector<long\
    \ long> occurrence_counts() const {\n        std::vector<long long> result(_nodes.size(),\
    \ 0);\n        for (node_id id = 0; id < node_count(); id++) {\n            result[id]\
    \ = _nodes[id].suffix_occurrences;\n        }\n        for (node_id id = node_count()\
    \ - 1; id >= 2; id--) {\n            result[_nodes[id].suffix_link] += result[id];\n\
    \        }\n        return result;\n    }\n\n    std::pair<int, int> first_occurrence(node_id\
    \ id) const {\n        assert(2 <= id && id < node_count());\n        int end\
    \ = _nodes[id].first_end;\n        return {end - _nodes[id].length, end};\n  \
    \  }\n};\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing\
    \ PalindromicTree = Eertree<AlphabetSize, FirstCharacter>;\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/eertree.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/string/eertree.test.cpp\"\n#include\
    \ <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <charconv>\n#line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n\
    #include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
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
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/string/eertree.test.cpp\"\
    \n#include <map>\n#include <set>\n#line 14 \"verify/string/eertree.test.cpp\"\n\
    \nnamespace {\n\nbool is_palindrome(const std::string& text, int left, int right)\
    \ {\n    while (left < right) {\n        right--;\n        if (text[left] != text[right])\
    \ return false;\n        left++;\n    }\n    return true;\n}\n\nvoid test_features()\
    \ {\n    using Eertree = m1une::string::Eertree<>;\n    Eertree tree;\n    tree.reserve(16);\n\
    \    assert(tree.empty());\n    assert(tree.node_count() == 2);\n    assert(tree.node(Eertree::even_root).length\
    \ == 0);\n    assert(tree.node(Eertree::odd_root).length == -1);\n\n    std::string\
    \ text = \"ababa\";\n    for (char character : text) tree.add(character);\n  \
    \  assert(tree.size() == 5);\n    assert(tree.text_length() == 5);\n    assert(tree.longest_suffix_length()\
    \ == 5);\n    assert(tree.node(tree.last()).suffix_count == 3);\n\n    std::vector<int>\
    \ expected_lengths = {1, 1, 3, 3, 5};\n    std::vector<int> actual_lengths;\n\
    \    for (int id = 2; id < tree.node_count(); id++) {\n        actual_lengths.push_back(tree.node(id).length);\n\
    \        auto [left, right] = tree.first_occurrence(id);\n        assert(right\
    \ - left == tree.node(id).length);\n        assert(is_palindrome(text, left, right));\n\
    \    }\n    assert(actual_lengths == expected_lengths);\n\n    std::vector<long\
    \ long> occurrence = tree.occurrence_counts();\n    std::map<std::string, long\
    \ long> expected;\n    expected[\"a\"] = 3;\n    expected[\"b\"] = 2;\n    expected[\"\
    aba\"] = 2;\n    expected[\"bab\"] = 1;\n    expected[\"ababa\"] = 1;\n    for\
    \ (int id = 2; id < tree.node_count(); id++) {\n        auto [left, right] = tree.first_occurrence(id);\n\
    \        assert(occurrence[id] == expected[text.substr(left, right - left)]);\n\
    \    }\n\n    assert(tree.node(tree.longest_suffix_node(1)).length == 1);\n  \
    \  assert(tree.node(tree.longest_suffix_node(2)).length == 1);\n    assert(tree.node(tree.longest_suffix_node(3)).length\
    \ == 3);\n    assert(tree.node(tree.longest_suffix_node(4)).length == 3);\n  \
    \  assert(tree.node(tree.longest_suffix_node(5)).length == 5);\n    std::vector<int>\
    \ suffix_lengths;\n    tree.for_each_suffix([&](int id) {\n        suffix_lengths.push_back(tree.node(id).length);\n\
    \    });\n    assert(suffix_lengths == std::vector<int>({5, 3, 1}));\n\n    m1une::string::PalindromicTree<10,\
    \ '0'> digits(std::string(\"01210\"));\n    assert(digits.longest_suffix_length()\
    \ == 5);\n\n    tree.clear();\n    assert(tree.empty());\n    assert(tree.text_length()\
    \ == 0);\n    assert(tree.last() == Eertree::even_root);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 91;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 60);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n\n        m1une::string::Eertree<4, 'a'>\
    \ tree(text);\n        std::map<std::string, long long> expected_count;\n    \
    \    std::vector<int> expected_longest(n, 0);\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                if (!is_palindrome(text, left, right)) continue;\n      \
    \          expected_count[text.substr(left, right - left)]++;\n              \
    \  expected_longest[right - 1] = std::max(expected_longest[right - 1], right -\
    \ left);\n            }\n        }\n\n        assert(tree.size() == int(expected_count.size()));\n\
    \        assert(tree.node_count() <= n + 2);\n        std::vector<long long> occurrence\
    \ = tree.occurrence_counts();\n        std::set<std::string> represented;\n  \
    \      for (int id = 2; id < tree.node_count(); id++) {\n            const auto&\
    \ node = tree.node(id);\n            auto [left, right] = tree.first_occurrence(id);\n\
    \            std::string palindrome = text.substr(left, right - left);\n     \
    \       assert(is_palindrome(text, left, right));\n            assert(node.length\
    \ == int(palindrome.size()));\n            assert(represented.insert(palindrome).second);\n\
    \            assert(occurrence[id] == expected_count[palindrome]);\n         \
    \   assert(tree.node(node.suffix_link).length < node.length);\n            assert(node.diff\
    \ == node.length - tree.node(node.suffix_link).length);\n            assert(node.suffix_count\
    \ == tree.node(node.suffix_link).suffix_count + 1);\n            assert(tree.node(node.series_link).length\
    \ < node.length);\n        }\n        assert(represented.size() == expected_count.size());\n\
    \        for (int prefix = 1; prefix <= n; prefix++) {\n            int id = tree.longest_suffix_node(prefix);\n\
    \            assert(tree.node(id).length == expected_longest[prefix - 1]);\n \
    \       }\n    }\n}\n\nint library_checker_id(int id) {\n    using Eertree = m1une::string::Eertree<>;\n\
    \    if (id == Eertree::odd_root) return 0;\n    if (id == Eertree::even_root)\
    \ return 1;\n    return id;\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n\
    \    test_randomized();\n    std::string text;\n    fast_input >> text;\n    m1une::string::Eertree<>\
    \ tree(text);\n\n    std::vector<int> parent(tree.node_count(), -1);\n    for\
    \ (int id = 0; id < tree.node_count(); id++) {\n        const auto& node = tree.node(id);\n\
    \        for (int symbol = 0; symbol < 26; symbol++) {\n            int to = node.next[symbol];\n\
    \            if (to != m1une::string::Eertree<>::null_node) parent[to] = id;\n\
    \        }\n    }\n\n    fast_output << tree.size() << '\\n';\n    for (int id\
    \ = 2; id < tree.node_count(); id++) {\n        fast_output << library_checker_id(parent[id])\
    \ - 1 << ' '\n                  << library_checker_id(tree.node(id).suffix_link)\
    \ - 1 << '\\n';\n    }\n    const auto& longest_suffix = tree.longest_suffix_nodes();\n\
    \    for (int i = 0; i < int(longest_suffix.size()); i++) {\n        if (i) fast_output\
    \ << ' ';\n        fast_output << longest_suffix[i] - 1;\n    }\n    fast_output\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eertree\"\n\n#include \"\
    ../../string/eertree.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <map>\n#include\
    \ <set>\n#include <string>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ {\n\nbool is_palindrome(const std::string& text, int left, int right) {\n  \
    \  while (left < right) {\n        right--;\n        if (text[left] != text[right])\
    \ return false;\n        left++;\n    }\n    return true;\n}\n\nvoid test_features()\
    \ {\n    using Eertree = m1une::string::Eertree<>;\n    Eertree tree;\n    tree.reserve(16);\n\
    \    assert(tree.empty());\n    assert(tree.node_count() == 2);\n    assert(tree.node(Eertree::even_root).length\
    \ == 0);\n    assert(tree.node(Eertree::odd_root).length == -1);\n\n    std::string\
    \ text = \"ababa\";\n    for (char character : text) tree.add(character);\n  \
    \  assert(tree.size() == 5);\n    assert(tree.text_length() == 5);\n    assert(tree.longest_suffix_length()\
    \ == 5);\n    assert(tree.node(tree.last()).suffix_count == 3);\n\n    std::vector<int>\
    \ expected_lengths = {1, 1, 3, 3, 5};\n    std::vector<int> actual_lengths;\n\
    \    for (int id = 2; id < tree.node_count(); id++) {\n        actual_lengths.push_back(tree.node(id).length);\n\
    \        auto [left, right] = tree.first_occurrence(id);\n        assert(right\
    \ - left == tree.node(id).length);\n        assert(is_palindrome(text, left, right));\n\
    \    }\n    assert(actual_lengths == expected_lengths);\n\n    std::vector<long\
    \ long> occurrence = tree.occurrence_counts();\n    std::map<std::string, long\
    \ long> expected;\n    expected[\"a\"] = 3;\n    expected[\"b\"] = 2;\n    expected[\"\
    aba\"] = 2;\n    expected[\"bab\"] = 1;\n    expected[\"ababa\"] = 1;\n    for\
    \ (int id = 2; id < tree.node_count(); id++) {\n        auto [left, right] = tree.first_occurrence(id);\n\
    \        assert(occurrence[id] == expected[text.substr(left, right - left)]);\n\
    \    }\n\n    assert(tree.node(tree.longest_suffix_node(1)).length == 1);\n  \
    \  assert(tree.node(tree.longest_suffix_node(2)).length == 1);\n    assert(tree.node(tree.longest_suffix_node(3)).length\
    \ == 3);\n    assert(tree.node(tree.longest_suffix_node(4)).length == 3);\n  \
    \  assert(tree.node(tree.longest_suffix_node(5)).length == 5);\n    std::vector<int>\
    \ suffix_lengths;\n    tree.for_each_suffix([&](int id) {\n        suffix_lengths.push_back(tree.node(id).length);\n\
    \    });\n    assert(suffix_lengths == std::vector<int>({5, 3, 1}));\n\n    m1une::string::PalindromicTree<10,\
    \ '0'> digits(std::string(\"01210\"));\n    assert(digits.longest_suffix_length()\
    \ == 5);\n\n    tree.clear();\n    assert(tree.empty());\n    assert(tree.text_length()\
    \ == 0);\n    assert(tree.last() == Eertree::even_root);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 91;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 60);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n\n        m1une::string::Eertree<4, 'a'>\
    \ tree(text);\n        std::map<std::string, long long> expected_count;\n    \
    \    std::vector<int> expected_longest(n, 0);\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                if (!is_palindrome(text, left, right)) continue;\n      \
    \          expected_count[text.substr(left, right - left)]++;\n              \
    \  expected_longest[right - 1] = std::max(expected_longest[right - 1], right -\
    \ left);\n            }\n        }\n\n        assert(tree.size() == int(expected_count.size()));\n\
    \        assert(tree.node_count() <= n + 2);\n        std::vector<long long> occurrence\
    \ = tree.occurrence_counts();\n        std::set<std::string> represented;\n  \
    \      for (int id = 2; id < tree.node_count(); id++) {\n            const auto&\
    \ node = tree.node(id);\n            auto [left, right] = tree.first_occurrence(id);\n\
    \            std::string palindrome = text.substr(left, right - left);\n     \
    \       assert(is_palindrome(text, left, right));\n            assert(node.length\
    \ == int(palindrome.size()));\n            assert(represented.insert(palindrome).second);\n\
    \            assert(occurrence[id] == expected_count[palindrome]);\n         \
    \   assert(tree.node(node.suffix_link).length < node.length);\n            assert(node.diff\
    \ == node.length - tree.node(node.suffix_link).length);\n            assert(node.suffix_count\
    \ == tree.node(node.suffix_link).suffix_count + 1);\n            assert(tree.node(node.series_link).length\
    \ < node.length);\n        }\n        assert(represented.size() == expected_count.size());\n\
    \        for (int prefix = 1; prefix <= n; prefix++) {\n            int id = tree.longest_suffix_node(prefix);\n\
    \            assert(tree.node(id).length == expected_longest[prefix - 1]);\n \
    \       }\n    }\n}\n\nint library_checker_id(int id) {\n    using Eertree = m1une::string::Eertree<>;\n\
    \    if (id == Eertree::odd_root) return 0;\n    if (id == Eertree::even_root)\
    \ return 1;\n    return id;\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n\
    \    test_randomized();\n    std::string text;\n    fast_input >> text;\n    m1une::string::Eertree<>\
    \ tree(text);\n\n    std::vector<int> parent(tree.node_count(), -1);\n    for\
    \ (int id = 0; id < tree.node_count(); id++) {\n        const auto& node = tree.node(id);\n\
    \        for (int symbol = 0; symbol < 26; symbol++) {\n            int to = node.next[symbol];\n\
    \            if (to != m1une::string::Eertree<>::null_node) parent[to] = id;\n\
    \        }\n    }\n\n    fast_output << tree.size() << '\\n';\n    for (int id\
    \ = 2; id < tree.node_count(); id++) {\n        fast_output << library_checker_id(parent[id])\
    \ - 1 << ' '\n                  << library_checker_id(tree.node(id).suffix_link)\
    \ - 1 << '\\n';\n    }\n    const auto& longest_suffix = tree.longest_suffix_nodes();\n\
    \    for (int i = 0; i < int(longest_suffix.size()); i++) {\n        if (i) fast_output\
    \ << ' ';\n        fast_output << longest_suffix[i] - 1;\n    }\n    fast_output\
    \ << '\\n';\n}\n"
  dependsOn:
  - string/eertree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/eertree.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/eertree.test.cpp
layout: document
redirect_from:
- /verify/verify/string/eertree.test.cpp
- /verify/verify/string/eertree.test.cpp.html
title: verify/string/eertree.test.cpp
---
