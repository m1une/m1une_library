---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"verify/algo/offline/mo.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#line 1 \"algo/offline/mo.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace m1une {\n\
    namespace algo {\n\n// Offline Mo's algorithm for half-open array ranges.\nstruct\
    \ Mo {\n    struct Query {\n        int left;\n        int right;\n        int\
    \ id;\n    };\n\n   private:\n    int _n;\n    std::vector<Query> _queries;\n\n\
    \   public:\n    Mo() : _n(0) {}\n\n    explicit Mo(int n) : _n(n) {\n       \
    \ assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\
    \n    int query_count() const {\n        return int(_queries.size());\n    }\n\
    \n    bool empty() const {\n        return _queries.empty();\n    }\n\n    const\
    \ std::vector<Query>& queries() const {\n        return _queries;\n    }\n\n \
    \   void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n    }\n\n    // Adds [left, right) and returns its insertion-order\
    \ ID.\n    int add_query(int left, int right) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        int id = query_count();\n        _queries.push_back(Query{left,\
    \ right, id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order.\
    \ A non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 4 \"verify/algo/offline/mo.test.cpp\"\
    \n\n#line 7 \"verify/algo/offline/mo.test.cpp\"\n#include <cstdint>\n#line 1 \"\
    utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/algo/offline/mo.test.cpp\"\
    \n\n#line 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#line 6 \"ds/range_query/fenwick_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct FenwickTree\
    \ {\n   private:\n    int _n;\n    int _max_power;\n    std::vector<T> _data;\n\
    \n    static int max_power_leq(int n) {\n        int result = 1;\n        while\
    \ (result <= n / 2) result <<= 1;\n        return result;\n    }\n\n    T prefix_sum(int\
    \ r) const {\n        T result{};\n        const T* data = _data.data();\n   \
    \     while (r > 0) {\n            result += data[r];\n            r -= r & -r;\n\
    \        }\n        return result;\n    }\n\n   public:\n    FenwickTree() : _n(0),\
    \ _max_power(0) {}\n\n    explicit FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n\
    \ > 0 ? n : 1)), _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>&\
    \ a)\n        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0\
    \ ? _n : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i\
    \ <= _n; ++i) {\n            _data[i] += a[i - 1];\n            const int p =\
    \ i + (i & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Adds\
    \ `x` to the element at zero-based index `p`.\n    void add(int p, const T& x)\
    \ {\n        assert(0 <= p && p < _n);\n        ++p;\n        T* data = _data.data();\n\
    \        while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r).\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        return\
    \ prefix_sum(r);\n    }\n\n    // Returns the sum of elements in the range [l,\
    \ r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        return prefix_sum(r) - prefix_sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        const T* data = _data.data();\n\
    \        for (int k = _max_power; k > 0; k >>= 1) {\n            if (x + k <=\
    \ _n && data[x + k] < w) {\n                w -= data[x + k];\n              \
    \  x += k;\n            }\n        }\n        return x + 1;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 12 \"verify/algo/offline/mo.test.cpp\"\
    \n\nnamespace {\n\nvoid test_randomized() {\n    std::uint64_t state = 503;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 2500; ++trial) {\n        int n = int(random() % 60);\n        int query_count\
    \ = int(random() % 80);\n        std::vector<int> values(n);\n        for (int&\
    \ value : values) value = int(random() % 12);\n\n        m1une::algo::Mo mo(n);\n\
    \        mo.reserve(query_count);\n        std::vector<std::pair<int, int>> ranges;\n\
    \        for (int query = 0; query < query_count; ++query) {\n            int\
    \ left = int(random() % (n + 1));\n            int right = int(random() % (n +\
    \ 1));\n            if (right < left) std::swap(left, right);\n            assert(mo.add_query(left,\
    \ right) == query);\n            ranges.emplace_back(left, right);\n        }\n\
    \n        std::vector<int> frequency(12);\n        std::vector<int> actual(query_count);\n\
    \        int distinct = 0;\n        mo.run(\n            [&](int index) {\n  \
    \              if (frequency[values[index]]++ == 0) distinct++;\n            },\n\
    \            [&](int index) {\n                if (--frequency[values[index]]\
    \ == 0) distinct--;\n            },\n            [&](int query_id) {\n       \
    \         actual[query_id] = distinct;\n            }\n        );\n\n        for\
    \ (int query = 0; query < query_count; ++query) {\n            std::vector<char>\
    \ seen(12);\n            [[maybe_unused]] int expected = 0;\n            for (\n\
    \                int index = ranges[query].first;\n                index < ranges[query].second;\n\
    \                ++index\n            ) {\n                if (!seen[values[index]])\
    \ {\n                    seen[values[index]] = true;\n                    expected++;\n\
    \                }\n            }\n            assert(actual[query] == expected);\n\
    \        }\n    }\n}\n\nstd::vector<long long> inversion_queries(\n    const std::vector<int>&\
    \ values,\n    const std::vector<std::pair<int, int>>& ranges\n) {\n    std::vector<int>\
    \ sorted = values;\n    std::sort(sorted.begin(), sorted.end());\n    sorted.erase(std::unique(sorted.begin(),\
    \ sorted.end()), sorted.end());\n\n    std::vector<int> compressed(values.size());\n\
    \    for (int index = 0; index < int(values.size()); ++index) {\n        compressed[index]\
    \ = int(\n            std::lower_bound(sorted.begin(), sorted.end(), values[index])\n\
    \            - sorted.begin()\n        );\n    }\n\n    m1une::algo::Mo mo(int(values.size()));\n\
    \    for (const auto& range : ranges) {\n        mo.add_query(range.first, range.second);\n\
    \    }\n\n    m1une::ds::FenwickTree<int> frequency(int(sorted.size()));\n   \
    \ std::vector<long long> result(ranges.size());\n    long long inversions = 0;\n\
    \    int current_size = 0;\n\n    mo.run(\n        [&](int index) {\n        \
    \    int value = compressed[index];\n            inversions += frequency.sum(value);\n\
    \            frequency.add(value, 1);\n            current_size++;\n        },\n\
    \        [&](int index) {\n            int value = compressed[index];\n      \
    \      inversions += current_size - frequency.sum(value + 1);\n            frequency.add(value,\
    \ 1);\n            current_size++;\n        },\n        [&](int index) {\n   \
    \         int value = compressed[index];\n            frequency.add(value, -1);\n\
    \            current_size--;\n            inversions -= frequency.sum(value);\n\
    \        },\n        [&](int index) {\n            int value = compressed[index];\n\
    \            frequency.add(value, -1);\n            current_size--;\n        \
    \    inversions -= current_size - frequency.sum(value + 1);\n        },\n    \
    \    [&](int query_id) {\n            result[query_id] = inversions;\n       \
    \ }\n    );\n    return result;\n}\n\nvoid test_directional_callbacks() {\n  \
    \  std::uint64_t state = 509;\n    auto random = [&state]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n\
    \    for (int trial = 0; trial < 1500; ++trial) {\n        int n = 1 + int(random()\
    \ % 45);\n        int query_count = 1 + int(random() % 60);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 20);\n\
    \        std::vector<std::pair<int, int>> ranges;\n        for (int query = 0;\
    \ query < query_count; ++query) {\n            int left = int(random() % (n +\
    \ 1));\n            int right = int(random() % (n + 1));\n            if (right\
    \ < left) std::swap(left, right);\n            ranges.emplace_back(left, right);\n\
    \        }\n\n        auto actual = inversion_queries(values, ranges);\n     \
    \   for (int query = 0; query < query_count; ++query) {\n            [[maybe_unused]]\
    \ long long expected = 0;\n            for (int i = ranges[query].first; i < ranges[query].second;\
    \ ++i) {\n                for (int j = i + 1; j < ranges[query].second; ++j) {\n\
    \                    expected += values[i] > values[j];\n                }\n \
    \           }\n            assert(actual[query] == expected);\n        }\n   \
    \ }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n   \
    \ test_directional_callbacks();\n\n    int n, q;\n    fast_input >> n >> q;\n\
    \    std::vector<int> values(n);\n    for (int& value : values) fast_input >>\
    \ value;\n    std::vector<std::pair<int, int>> ranges(q);\n    for (auto& range\
    \ : ranges) {\n        fast_input >> range.first >> range.second;\n    }\n   \
    \ for (long long answer : inversion_queries(values, ranges)) {\n        fast_output\
    \ << answer << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"../../../algo/offline/mo.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\n\
    #include <vector>\n\n#include \"../../../ds/range_query/fenwick_tree.hpp\"\n\n\
    namespace {\n\nvoid test_randomized() {\n    std::uint64_t state = 503;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 2500;\
    \ ++trial) {\n        int n = int(random() % 60);\n        int query_count = int(random()\
    \ % 80);\n        std::vector<int> values(n);\n        for (int& value : values)\
    \ value = int(random() % 12);\n\n        m1une::algo::Mo mo(n);\n        mo.reserve(query_count);\n\
    \        std::vector<std::pair<int, int>> ranges;\n        for (int query = 0;\
    \ query < query_count; ++query) {\n            int left = int(random() % (n +\
    \ 1));\n            int right = int(random() % (n + 1));\n            if (right\
    \ < left) std::swap(left, right);\n            assert(mo.add_query(left, right)\
    \ == query);\n            ranges.emplace_back(left, right);\n        }\n\n   \
    \     std::vector<int> frequency(12);\n        std::vector<int> actual(query_count);\n\
    \        int distinct = 0;\n        mo.run(\n            [&](int index) {\n  \
    \              if (frequency[values[index]]++ == 0) distinct++;\n            },\n\
    \            [&](int index) {\n                if (--frequency[values[index]]\
    \ == 0) distinct--;\n            },\n            [&](int query_id) {\n       \
    \         actual[query_id] = distinct;\n            }\n        );\n\n        for\
    \ (int query = 0; query < query_count; ++query) {\n            std::vector<char>\
    \ seen(12);\n            [[maybe_unused]] int expected = 0;\n            for (\n\
    \                int index = ranges[query].first;\n                index < ranges[query].second;\n\
    \                ++index\n            ) {\n                if (!seen[values[index]])\
    \ {\n                    seen[values[index]] = true;\n                    expected++;\n\
    \                }\n            }\n            assert(actual[query] == expected);\n\
    \        }\n    }\n}\n\nstd::vector<long long> inversion_queries(\n    const std::vector<int>&\
    \ values,\n    const std::vector<std::pair<int, int>>& ranges\n) {\n    std::vector<int>\
    \ sorted = values;\n    std::sort(sorted.begin(), sorted.end());\n    sorted.erase(std::unique(sorted.begin(),\
    \ sorted.end()), sorted.end());\n\n    std::vector<int> compressed(values.size());\n\
    \    for (int index = 0; index < int(values.size()); ++index) {\n        compressed[index]\
    \ = int(\n            std::lower_bound(sorted.begin(), sorted.end(), values[index])\n\
    \            - sorted.begin()\n        );\n    }\n\n    m1une::algo::Mo mo(int(values.size()));\n\
    \    for (const auto& range : ranges) {\n        mo.add_query(range.first, range.second);\n\
    \    }\n\n    m1une::ds::FenwickTree<int> frequency(int(sorted.size()));\n   \
    \ std::vector<long long> result(ranges.size());\n    long long inversions = 0;\n\
    \    int current_size = 0;\n\n    mo.run(\n        [&](int index) {\n        \
    \    int value = compressed[index];\n            inversions += frequency.sum(value);\n\
    \            frequency.add(value, 1);\n            current_size++;\n        },\n\
    \        [&](int index) {\n            int value = compressed[index];\n      \
    \      inversions += current_size - frequency.sum(value + 1);\n            frequency.add(value,\
    \ 1);\n            current_size++;\n        },\n        [&](int index) {\n   \
    \         int value = compressed[index];\n            frequency.add(value, -1);\n\
    \            current_size--;\n            inversions -= frequency.sum(value);\n\
    \        },\n        [&](int index) {\n            int value = compressed[index];\n\
    \            frequency.add(value, -1);\n            current_size--;\n        \
    \    inversions -= current_size - frequency.sum(value + 1);\n        },\n    \
    \    [&](int query_id) {\n            result[query_id] = inversions;\n       \
    \ }\n    );\n    return result;\n}\n\nvoid test_directional_callbacks() {\n  \
    \  std::uint64_t state = 509;\n    auto random = [&state]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n\
    \    for (int trial = 0; trial < 1500; ++trial) {\n        int n = 1 + int(random()\
    \ % 45);\n        int query_count = 1 + int(random() % 60);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 20);\n\
    \        std::vector<std::pair<int, int>> ranges;\n        for (int query = 0;\
    \ query < query_count; ++query) {\n            int left = int(random() % (n +\
    \ 1));\n            int right = int(random() % (n + 1));\n            if (right\
    \ < left) std::swap(left, right);\n            ranges.emplace_back(left, right);\n\
    \        }\n\n        auto actual = inversion_queries(values, ranges);\n     \
    \   for (int query = 0; query < query_count; ++query) {\n            [[maybe_unused]]\
    \ long long expected = 0;\n            for (int i = ranges[query].first; i < ranges[query].second;\
    \ ++i) {\n                for (int j = i + 1; j < ranges[query].second; ++j) {\n\
    \                    expected += values[i] > values[j];\n                }\n \
    \           }\n            assert(actual[query] == expected);\n        }\n   \
    \ }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n   \
    \ test_directional_callbacks();\n\n    int n, q;\n    fast_input >> n >> q;\n\
    \    std::vector<int> values(n);\n    for (int& value : values) fast_input >>\
    \ value;\n    std::vector<std::pair<int, int>> ranges(q);\n    for (auto& range\
    \ : ranges) {\n        fast_input >> range.first >> range.second;\n    }\n   \
    \ for (long long answer : inversion_queries(values, ranges)) {\n        fast_output\
    \ << answer << '\\n';\n    }\n}\n"
  dependsOn:
  - algo/offline/mo.hpp
  - utilities/fast_io.hpp
  - ds/range_query/fenwick_tree.hpp
  isVerificationFile: true
  path: verify/algo/offline/mo.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/offline/mo.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/offline/mo.test.cpp
- /verify/verify/algo/offline/mo.test.cpp.html
title: verify/algo/offline/mo.test.cpp
---
