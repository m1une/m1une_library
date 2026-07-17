---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/cartesian_tree.hpp
    title: Cartesian Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"verify/graph/tree/cartesian_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#line 1 \"utilities/fast_io.hpp\"\n\
    \n\n\n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
    #include <utility>\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
    \ {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 7 \"verify/graph/tree/cartesian_tree.test.cpp\"\
    \n#include <random>\n#include <vector>\n\n#line 1 \"graph/tree/cartesian_tree.hpp\"\
    \n\n\n\n#line 7 \"graph/tree/cartesian_tree.hpp\"\n#include <limits>\n#line 10\
    \ \"graph/tree/cartesian_tree.hpp\"\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 12 \"graph/tree/cartesian_tree.hpp\"\n\nnamespace m1une {\n\
    namespace tree {\n\nstruct CartesianTree {\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> left;\n    std::vector<int> right;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n    }\n\n   public:\n    CartesianTree() : root(-1), _n(0) {}\n\n\
    \    template <class T, class Compare = std::less<T>>\n    explicit CartesianTree(const\
    \ std::vector<T>& a, Compare comp = Compare()) : root(-1), _n(0) {\n        build(a,\
    \ comp);\n    }\n\n    template <class T, class Compare = std::less<T>>\n    void\
    \ build(const std::vector<T>& a, Compare comp = Compare()) {\n        assert(a.size()\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n        _n =\
    \ int(a.size());\n        root = -1;\n        parent.assign(_n, -1);\n       \
    \ left.assign(_n, -1);\n        right.assign(_n, -1);\n\n        std::vector<int>\
    \ stack;\n        stack.reserve(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            int last = -1;\n            while (!stack.empty() && comp(a[i], a[stack.back()]))\
    \ {\n                last = stack.back();\n                stack.pop_back();\n\
    \            }\n            if (last != -1) {\n                left[i] = last;\n\
    \                parent[last] = i;\n            }\n            if (!stack.empty())\
    \ {\n                right[stack.back()] = i;\n                parent[i] = stack.back();\n\
    \            }\n            stack.push_back(i);\n        }\n\n        if (!stack.empty())\
    \ root = stack.front();\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ parent_or_self(int v) const {\n        check_vertex(v);\n        return parent[v]\
    \ == -1 ? v : parent[v];\n    }\n\n    std::vector<int> parent_with_root_self()\
    \ const {\n        std::vector<int> result = parent;\n        if (root != -1)\
    \ result[root] = root;\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges() const {\n        std::vector<std::pair<int, int>> result;\n  \
    \      if (_n == 0) return result;\n        result.reserve(_n - 1);\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (parent[v] != -1) result.emplace_back(parent[v],\
    \ v);\n        }\n        return result;\n    }\n\n    m1une::graph::Graph<int>\
    \ to_graph() const {\n        m1une::graph::Graph<int> g(_n);\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (parent[v] != -1) g.add_edge(parent[v],\
    \ v);\n        }\n        return g;\n    }\n};\n\ntemplate <class T, class Compare\
    \ = std::less<T>>\nCartesianTree cartesian_tree(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n    CartesianTree result;\n    result.build(a, comp);\n\
    \    return result;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line\
    \ 11 \"verify/graph/tree/cartesian_tree.test.cpp\"\n\nstruct ExpectedCartesianTree\
    \ {\n    int root;\n    std::vector<int> parent;\n    std::vector<int> left;\n\
    \    std::vector<int> right;\n};\n\ntemplate <class T, class Compare>\nint build_naive_cartesian_tree(\n\
    \    const std::vector<T>& a,\n    int l,\n    int r,\n    int p,\n    Compare\
    \ comp,\n    ExpectedCartesianTree& result\n) {\n    if (l == r) return -1;\n\
    \    int best = l;\n    for (int i = l + 1; i < r; i++) {\n        if (comp(a[i],\
    \ a[best])) best = i;\n    }\n    result.parent[best] = p;\n    result.left[best]\
    \ = build_naive_cartesian_tree(a, l, best, best, comp, result);\n    result.right[best]\
    \ = build_naive_cartesian_tree(a, best + 1, r, best, comp, result);\n    return\
    \ best;\n}\n\ntemplate <class T, class Compare>\nExpectedCartesianTree naive_cartesian_tree(const\
    \ std::vector<T>& a, Compare comp) {\n    ExpectedCartesianTree result;\n    int\
    \ n = int(a.size());\n    result.root = -1;\n    result.parent.assign(n, -1);\n\
    \    result.left.assign(n, -1);\n    result.right.assign(n, -1);\n    result.root\
    \ = build_naive_cartesian_tree(a, 0, n, -1, comp, result);\n    return result;\n\
    }\n\nvoid collect_inorder(const m1une::tree::CartesianTree& tree, int v, std::vector<int>&\
    \ order) {\n    if (v == -1) return;\n    collect_inorder(tree, tree.left[v],\
    \ order);\n    order.push_back(v);\n    collect_inorder(tree, tree.right[v], order);\n\
    }\n\ntemplate <class T, class Compare>\nvoid assert_cartesian_tree(const std::vector<T>&\
    \ a, Compare comp) {\n    const int n = int(a.size());\n    m1une::tree::CartesianTree\
    \ tree(a, comp);\n    ExpectedCartesianTree expected = naive_cartesian_tree(a,\
    \ comp);\n\n    assert(tree.size() == n);\n    assert(tree.empty() == (n == 0));\n\
    \    assert(tree.root == expected.root);\n    assert(tree.parent == expected.parent);\n\
    \    assert(tree.left == expected.left);\n    assert(tree.right == expected.right);\n\
    \n    std::vector<int> inorder;\n    inorder.reserve(n);\n    collect_inorder(tree,\
    \ tree.root, inorder);\n    assert(int(inorder.size()) == n);\n    for (int i\
    \ = 0; i < n; i++) assert(inorder[i] == i);\n\n    std::vector<int> parent_self\
    \ = tree.parent_with_root_self();\n    assert(int(parent_self.size()) == n);\n\
    \    for (int v = 0; v < n; v++) {\n        if (tree.parent[v] == -1) {\n    \
    \        assert(v == tree.root);\n            assert(parent_self[v] == v);\n \
    \           assert(tree.parent_or_self(v) == v);\n        } else {\n         \
    \   assert(parent_self[v] == tree.parent[v]);\n            assert(tree.parent_or_self(v)\
    \ == tree.parent[v]);\n            assert(!comp(a[v], a[tree.parent[v]]));\n \
    \       }\n        if (tree.left[v] != -1) {\n            assert(tree.left[v]\
    \ < v);\n            assert(tree.parent[tree.left[v]] == v);\n        }\n    \
    \    if (tree.right[v] != -1) {\n            assert(v < tree.right[v]);\n    \
    \        assert(tree.parent[tree.right[v]] == v);\n        }\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges = tree.edges();\n    assert(int(edges.size()) == std::max(0, n -\
    \ 1));\n    auto graph = tree.to_graph();\n    assert(graph.size() == n);\n  \
    \  assert(graph.edge_count() == std::max(0, n - 1));\n}\n\nvoid run_local_tests()\
    \ {\n    assert_cartesian_tree(std::vector<int>(), std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3,\
    \ 1, 4, 0, 2}, std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3,\
    \ 1, 4, 0, 2}, std::greater<int>());\n    assert_cartesian_tree(std::vector<int>{2,\
    \ 2, 2, 1, 1, 3}, std::less<int>());\n\n    std::mt19937 rng(123456789);\n   \
    \ for (int n = 0; n <= 60; n++) {\n        for (int test = 0; test < 100; test++)\
    \ {\n            std::vector<int> values(n);\n            for (int& x : values)\
    \ x = int(rng() % 11) - 5;\n            assert_cartesian_tree(values, std::less<int>());\n\
    \            assert_cartesian_tree(values, std::greater<int>());\n        }\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    run_local_tests();\n\n    int n;\n    fast_input >> n;\n\
    \    std::vector<long long> a(n);\n    for (int i = 0; i < n; i++) fast_input\
    \ >> a[i];\n\n    m1une::tree::CartesianTree tree(a);\n    std::vector<int> parent\
    \ = tree.parent_with_root_self();\n    for (int i = 0; i < n; i++) {\n       \
    \ if (i) fast_output << ' ';\n        fast_output << parent[i];\n    }\n    fast_output\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <random>\n#include <vector>\n\n#include \"../../../graph/tree/cartesian_tree.hpp\"\
    \n\nstruct ExpectedCartesianTree {\n    int root;\n    std::vector<int> parent;\n\
    \    std::vector<int> left;\n    std::vector<int> right;\n};\n\ntemplate <class\
    \ T, class Compare>\nint build_naive_cartesian_tree(\n    const std::vector<T>&\
    \ a,\n    int l,\n    int r,\n    int p,\n    Compare comp,\n    ExpectedCartesianTree&\
    \ result\n) {\n    if (l == r) return -1;\n    int best = l;\n    for (int i =\
    \ l + 1; i < r; i++) {\n        if (comp(a[i], a[best])) best = i;\n    }\n  \
    \  result.parent[best] = p;\n    result.left[best] = build_naive_cartesian_tree(a,\
    \ l, best, best, comp, result);\n    result.right[best] = build_naive_cartesian_tree(a,\
    \ best + 1, r, best, comp, result);\n    return best;\n}\n\ntemplate <class T,\
    \ class Compare>\nExpectedCartesianTree naive_cartesian_tree(const std::vector<T>&\
    \ a, Compare comp) {\n    ExpectedCartesianTree result;\n    int n = int(a.size());\n\
    \    result.root = -1;\n    result.parent.assign(n, -1);\n    result.left.assign(n,\
    \ -1);\n    result.right.assign(n, -1);\n    result.root = build_naive_cartesian_tree(a,\
    \ 0, n, -1, comp, result);\n    return result;\n}\n\nvoid collect_inorder(const\
    \ m1une::tree::CartesianTree& tree, int v, std::vector<int>& order) {\n    if\
    \ (v == -1) return;\n    collect_inorder(tree, tree.left[v], order);\n    order.push_back(v);\n\
    \    collect_inorder(tree, tree.right[v], order);\n}\n\ntemplate <class T, class\
    \ Compare>\nvoid assert_cartesian_tree(const std::vector<T>& a, Compare comp)\
    \ {\n    const int n = int(a.size());\n    m1une::tree::CartesianTree tree(a,\
    \ comp);\n    ExpectedCartesianTree expected = naive_cartesian_tree(a, comp);\n\
    \n    assert(tree.size() == n);\n    assert(tree.empty() == (n == 0));\n    assert(tree.root\
    \ == expected.root);\n    assert(tree.parent == expected.parent);\n    assert(tree.left\
    \ == expected.left);\n    assert(tree.right == expected.right);\n\n    std::vector<int>\
    \ inorder;\n    inorder.reserve(n);\n    collect_inorder(tree, tree.root, inorder);\n\
    \    assert(int(inorder.size()) == n);\n    for (int i = 0; i < n; i++) assert(inorder[i]\
    \ == i);\n\n    std::vector<int> parent_self = tree.parent_with_root_self();\n\
    \    assert(int(parent_self.size()) == n);\n    for (int v = 0; v < n; v++) {\n\
    \        if (tree.parent[v] == -1) {\n            assert(v == tree.root);\n  \
    \          assert(parent_self[v] == v);\n            assert(tree.parent_or_self(v)\
    \ == v);\n        } else {\n            assert(parent_self[v] == tree.parent[v]);\n\
    \            assert(tree.parent_or_self(v) == tree.parent[v]);\n            assert(!comp(a[v],\
    \ a[tree.parent[v]]));\n        }\n        if (tree.left[v] != -1) {\n       \
    \     assert(tree.left[v] < v);\n            assert(tree.parent[tree.left[v]]\
    \ == v);\n        }\n        if (tree.right[v] != -1) {\n            assert(v\
    \ < tree.right[v]);\n            assert(tree.parent[tree.right[v]] == v);\n  \
    \      }\n    }\n\n    std::vector<std::pair<int, int>> edges = tree.edges();\n\
    \    assert(int(edges.size()) == std::max(0, n - 1));\n    auto graph = tree.to_graph();\n\
    \    assert(graph.size() == n);\n    assert(graph.edge_count() == std::max(0,\
    \ n - 1));\n}\n\nvoid run_local_tests() {\n    assert_cartesian_tree(std::vector<int>(),\
    \ std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3, 1, 4, 0, 2},\
    \ std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3, 1, 4, 0, 2},\
    \ std::greater<int>());\n    assert_cartesian_tree(std::vector<int>{2, 2, 2, 1,\
    \ 1, 3}, std::less<int>());\n\n    std::mt19937 rng(123456789);\n    for (int\
    \ n = 0; n <= 60; n++) {\n        for (int test = 0; test < 100; test++) {\n \
    \           std::vector<int> values(n);\n            for (int& x : values) x =\
    \ int(rng() % 11) - 5;\n            assert_cartesian_tree(values, std::less<int>());\n\
    \            assert_cartesian_tree(values, std::greater<int>());\n        }\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    run_local_tests();\n\n    int n;\n    fast_input >> n;\n\
    \    std::vector<long long> a(n);\n    for (int i = 0; i < n; i++) fast_input\
    \ >> a[i];\n\n    m1une::tree::CartesianTree tree(a);\n    std::vector<int> parent\
    \ = tree.parent_with_root_self();\n    for (int i = 0; i < n; i++) {\n       \
    \ if (i) fast_output << ' ';\n        fast_output << parent[i];\n    }\n    fast_output\
    \ << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - graph/tree/cartesian_tree.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/cartesian_tree.test.cpp
- /verify/verify/graph/tree/cartesian_tree.test.cpp.html
title: verify/graph/tree/cartesian_tree.test.cpp
---
