---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sqrt_blocks.hpp
    title: Custom Square-Root Blocks
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/range_query/sqrt_blocks.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Square-root decomposition\
    \ framework with user-defined per-block state.\ntemplate <class T, class Block>\n\
    struct SqrtBlocks {\n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n\
    \    std::vector<T> _values;\n    std::vector<Block> _blocks;\n\n    void initialize_blocks(int\
    \ requested_block_size) {\n        if (requested_block_size > 0) {\n         \
    \   _block_size = requested_block_size;\n        } else {\n            _block_size\
    \ = std::max(\n                1,\n                int(std::ceil(std::sqrt(static_cast<long\
    \ double>(_n))))\n            );\n        }\n        _block_count = _n == 0 ?\
    \ 0 : 1 + (_n - 1) / _block_size;\n        _blocks.resize(_block_count);\n   \
    \     for (int block_index = 0; block_index < _block_count; ++block_index) {\n\
    \            rebuild(block_index);\n        }\n    }\n\n   public:\n    SqrtBlocks()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtBlocks(std::vector<T>\
    \ values, int block_size = -1)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks(block_size);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        int left = block_index\
    \ * _block_size;\n        return {left, std::min(_n, left + _block_size)};\n \
    \   }\n\n    const std::vector<T>& values() const {\n        return _values;\n\
    \    }\n\n    const Block& block(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        return _blocks[block_index];\n\
    \    }\n\n    Block& block(int block_index) {\n        assert(0 <= block_index\
    \ && block_index < _block_count);\n        return _blocks[block_index];\n    }\n\
    \n    // Rebuilds the cached state from raw values. This does not push first.\n\
    \    void rebuild(int block_index) {\n        auto [left, right] = block_range(block_index);\n\
    \        _blocks[block_index].build(_values, left, right);\n    }\n\n    // Materializes\
    \ this block's optional lazy state into raw values.\n    void push(int block_index)\
    \ {\n        assert(0 <= block_index && block_index < _block_count);\n       \
    \ if constexpr (requires(\n            Block& current,\n            std::vector<T>&\
    \ values,\n            int left,\n            int right\n        ) {\n       \
    \     current.push(values, left, right);\n        }) {\n            auto [left,\
    \ right] = block_range(block_index);\n            _blocks[block_index].push(_values,\
    \ left, right);\n        }\n    }\n\n    T get(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        const Block& current = _blocks[block_of(index)];\n\
    \        if constexpr (requires(\n            const Block& candidate,\n      \
    \      const T& raw,\n            int position\n        ) {\n            candidate.value(raw,\
    \ position);\n        }) {\n            return current.value(_values[index], index);\n\
    \        } else if constexpr (requires(const Block& candidate, const T& raw) {\n\
    \            candidate.value(raw);\n        }) {\n            return current.value(_values[index]);\n\
    \        } else {\n            return _values[index];\n        }\n    }\n\n  \
    \  T operator[](int index) const {\n        return get(index);\n    }\n\n    void\
    \ set(int index, T value) {\n        assert(0 <= index && index < _n);\n     \
    \   int block_index = block_of(index);\n        push(block_index);\n        _values[index]\
    \ = std::move(value);\n        rebuild(block_index);\n    }\n\n    template <class\
    \ F>\n    void apply_point(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        int block_index = block_of(index);\n        push(block_index);\n\
    \        f(_values[index]);\n        rebuild(block_index);\n    }\n\n    template\
    \ <class Full, class Partial>\n    void update_range(int left, int right, Full\
    \ full, Partial partial) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        while (left < right) {\n            int block_index = left\
    \ / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                push(block_index);\n\
    \                partial(\n                    left,\n                    segment_right,\n\
    \                    block_index,\n                    _values,\n            \
    \        _blocks[block_index]\n                );\n                rebuild(block_index);\n\
    \            }\n            left = segment_right;\n        }\n    }\n\n    template\
    \ <class Full, class Partial>\n    void query_range(int left, int right, Full\
    \ full, Partial partial) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        while (left < right) {\n            int block_index =\
    \ left / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                partial(left,\
    \ segment_right, block_index, _blocks[block_index]);\n            }\n        \
    \    left = segment_right;\n        }\n    }\n};\n\n}  // namespace ds\n}  //\
    \ namespace m1une\n\n\n#line 4 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n\
    \n#line 7 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 17 \"\
    utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\
    \n\nnamespace {\n\nstruct SortedBlock {\n    std::vector<long long> sorted;\n\n\
    \    void build(const std::vector<long long>& values, int left, int right) {\n\
    \        sorted.assign(values.begin() + left, values.begin() + right);\n     \
    \   std::sort(sorted.begin(), sorted.end());\n    }\n};\n\nstruct RangeCountLess\
    \ {\n    m1une::ds::SqrtBlocks<long long, SortedBlock> data;\n\n    explicit RangeCountLess(std::vector<long\
    \ long> values, int block_size = -1)\n        : data(std::move(values), block_size)\
    \ {}\n\n    void set(int index, long long value) {\n        data.set(index, value);\n\
    \    }\n\n    void increment(int index) {\n        data.apply_point(index, [](long\
    \ long& value) { ++value; });\n    }\n\n    int count_less(int left, int right,\
    \ long long x) const {\n        int result = 0;\n        data.query_range(\n \
    \           left,\n            right,\n            [&](int, const SortedBlock&\
    \ block) {\n                result += int(std::lower_bound(\n                \
    \    block.sorted.begin(),\n                    block.sorted.end(),\n        \
    \            x\n                ) - block.sorted.begin());\n            },\n \
    \           [&](int segment_left, int segment_right, int, const SortedBlock&)\
    \ {\n                for (int index = segment_left; index < segment_right; ++index)\
    \ {\n                    result += data.get(index) < x;\n                }\n \
    \           }\n        );\n        return result;\n    }\n};\n\nstruct AddBlock\
    \ {\n    std::vector<long long> sorted;\n    long long lazy = 0;\n\n    void build(const\
    \ std::vector<long long>& values, int left, int right) {\n        sorted.assign(values.begin()\
    \ + left, values.begin() + right);\n        std::sort(sorted.begin(), sorted.end());\n\
    \        lazy = 0;\n    }\n\n    void push(std::vector<long long>& values, int\
    \ left, int right) {\n        for (int index = left; index < right; ++index) {\n\
    \            values[index] += lazy;\n        }\n        lazy = 0;\n    }\n\n \
    \   long long value(const long long& raw, int) const {\n        return raw + lazy;\n\
    \    }\n};\n\nstruct RangeAddCountLess {\n    m1une::ds::SqrtBlocks<long long,\
    \ AddBlock> data;\n\n    explicit RangeAddCountLess(\n        std::vector<long\
    \ long> values,\n        int block_size = -1\n    ) : data(std::move(values),\
    \ block_size) {}\n\n    void add(int left, int right, long long value) {\n   \
    \     data.update_range(\n            left,\n            right,\n            [&](int,\
    \ AddBlock& block) {\n                block.lazy += value;\n            },\n \
    \           [&](int segment_left,\n                int segment_right,\n      \
    \          int,\n                std::vector<long long>& values,\n           \
    \     AddBlock&) {\n                for (int index = segment_left; index < segment_right;\
    \ ++index) {\n                    values[index] += value;\n                }\n\
    \            }\n        );\n    }\n\n    int count_less(int left, int right, long\
    \ long x) const {\n        int result = 0;\n        data.query_range(\n      \
    \      left,\n            right,\n            [&](int, const AddBlock& block)\
    \ {\n                result += int(std::lower_bound(\n                    block.sorted.begin(),\n\
    \                    block.sorted.end(),\n                    x - block.lazy\n\
    \                ) - block.sorted.begin());\n            },\n            [&](int\
    \ segment_left, int segment_right, int, const AddBlock&) {\n                for\
    \ (int index = segment_left; index < segment_right; ++index) {\n             \
    \       result += data.get(index) < x;\n                }\n            }\n   \
    \     );\n        return result;\n    }\n\n    long long get(int index) const\
    \ {\n        return data.get(index);\n    }\n};\n\nint naive_count_less(\n   \
    \ const std::vector<long long>& values,\n    int left,\n    int right,\n    long\
    \ long x\n) {\n    int result = 0;\n    for (int index = left; index < right;\
    \ ++index) {\n        result += values[index] < x;\n    }\n    return result;\n\
    }\n\nvoid test_fixed() {\n    RangeCountLess empty(std::vector<long long>{});\n\
    \    assert(empty.data.empty());\n    assert(empty.data.size() == 0);\n    assert(empty.data.block_size()\
    \ == 1);\n    assert(empty.data.block_count() == 0);\n    assert(empty.count_less(0,\
    \ 0, 10) == 0);\n\n    RangeAddCountLess custom_empty(std::vector<long long>{},\
    \ 7);\n    assert(custom_empty.data.block_size() == 7);\n    assert(custom_empty.data.block_count()\
    \ == 0);\n    custom_empty.add(0, 0, 3);\n    assert(custom_empty.count_less(0,\
    \ 0, 0) == 0);\n\n    RangeCountLess one(std::vector<long long>{4});\n    assert(one.count_less(0,\
    \ 1, 5) == 1);\n    one.set(0, 9);\n    assert(one.count_less(0, 1, 5) == 0);\n\
    \    one.increment(0);\n    assert(one.data[0] == 10);\n\n    std::vector<long\
    \ long> initial = {3, -1, 4, 1, 5};\n    RangeAddCountLess range_add(initial,\
    \ 3);\n    assert(range_add.data.block_size() == 3);\n    assert(range_add.data.block_count()\
    \ == 2);\n    assert(range_add.data.block_of(4) == 1);\n    std::pair<int, int>\
    \ expected_range(0, 3);\n    assert(range_add.data.block_range(0) == expected_range);\n\
    \    range_add.add(0, 3, 7);\n    initial[0] += 7;\n    initial[1] += 7;\n   \
    \ initial[2] += 7;\n    assert(range_add.get(1) == initial[1]);\n    range_add.add(1,\
    \ 5, -2);\n    for (int index = 1; index < 5; ++index) initial[index] -= 2;\n\
    \    for (int index = 0; index < 5; ++index) {\n        assert(range_add.get(index)\
    \ == initial[index]);\n    }\n    for (long long x = -5; x <= 15; ++x) {\n   \
    \     assert(\n            range_add.count_less(1, 5, x) ==\n            naive_count_less(initial,\
    \ 1, 5, x)\n        );\n    }\n}\n\nvoid test_range_count_less_randomized() {\n\
    \    std::uint64_t state = 0xA0761D6478BD642FULL;\n    auto random = [&]() {\n\
    \        state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int n = int(random()\
    \ % 26);\n        std::vector<long long> naive(n);\n        for (long long& value\
    \ : naive) {\n            value = static_cast<long long>(random() % 21) - 10;\n\
    \        }\n        int block_size = trial % 2 == 0 ? -1 : int(random() % 8) +\
    \ 1;\n        RangeCountLess blocks(naive, block_size);\n\n        for (int operation\
    \ = 0; operation < 250; ++operation) {\n            if (n != 0 && random() % 3\
    \ == 0) {\n                int index = int(random() % n);\n                long\
    \ long value = static_cast<long long>(random() % 31) - 15;\n                naive[index]\
    \ = value;\n                blocks.set(index, value);\n            } else {\n\
    \                int left = int(random() % (n + 1));\n                int right\
    \ = int(random() % (n + 1));\n                if (right < left) std::swap(left,\
    \ right);\n                long long x = static_cast<long long>(random() % 35)\
    \ - 17;\n                assert(\n                    blocks.count_less(left,\
    \ right, x) ==\n                    naive_count_less(naive, left, right, x)\n\
    \                );\n            }\n        }\n    }\n}\n\nvoid test_range_add_count_less_randomized()\
    \ {\n    std::uint64_t state = 0xE7037ED1A0B428DBULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int\
    \ n = int(random() % 26);\n        std::vector<long long> naive(n);\n        for\
    \ (long long& value : naive) {\n            value = static_cast<long long>(random()\
    \ % 21) - 10;\n        }\n        int block_size = trial % 2 == 0 ? -1 : int(random()\
    \ % 8) + 1;\n        RangeAddCountLess blocks(naive, block_size);\n\n        for\
    \ (int operation = 0; operation < 250; ++operation) {\n            int type =\
    \ int(random() % 3);\n            if (type == 0) {\n                int left =\
    \ int(random() % (n + 1));\n                int right = int(random() % (n + 1));\n\
    \                if (right < left) std::swap(left, right);\n                long\
    \ long value = static_cast<long long>(random() % 15) - 7;\n                blocks.add(left,\
    \ right, value);\n                for (int index = left; index < right; ++index)\
    \ {\n                    naive[index] += value;\n                }\n         \
    \   } else if (type == 1 || n == 0) {\n                int left = int(random()\
    \ % (n + 1));\n                int right = int(random() % (n + 1));\n        \
    \        if (right < left) std::swap(left, right);\n                long long\
    \ x = static_cast<long long>(random() % 61) - 30;\n                assert(\n \
    \                   blocks.count_less(left, right, x) ==\n                   \
    \ naive_count_less(naive, left, right, x)\n                );\n            } else\
    \ {\n                int index = int(random() % n);\n                assert(blocks.get(index)\
    \ == naive[index]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_range_count_less_randomized();\n\
    \    test_range_add_count_less_randomized();\n\n    long long a, b;\n    fast_input\
    \ >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/range_query/sqrt_blocks.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nstruct SortedBlock {\n    std::vector<long\
    \ long> sorted;\n\n    void build(const std::vector<long long>& values, int left,\
    \ int right) {\n        sorted.assign(values.begin() + left, values.begin() +\
    \ right);\n        std::sort(sorted.begin(), sorted.end());\n    }\n};\n\nstruct\
    \ RangeCountLess {\n    m1une::ds::SqrtBlocks<long long, SortedBlock> data;\n\n\
    \    explicit RangeCountLess(std::vector<long long> values, int block_size = -1)\n\
    \        : data(std::move(values), block_size) {}\n\n    void set(int index, long\
    \ long value) {\n        data.set(index, value);\n    }\n\n    void increment(int\
    \ index) {\n        data.apply_point(index, [](long long& value) { ++value; });\n\
    \    }\n\n    int count_less(int left, int right, long long x) const {\n     \
    \   int result = 0;\n        data.query_range(\n            left,\n          \
    \  right,\n            [&](int, const SortedBlock& block) {\n                result\
    \ += int(std::lower_bound(\n                    block.sorted.begin(),\n      \
    \              block.sorted.end(),\n                    x\n                ) -\
    \ block.sorted.begin());\n            },\n            [&](int segment_left, int\
    \ segment_right, int, const SortedBlock&) {\n                for (int index =\
    \ segment_left; index < segment_right; ++index) {\n                    result\
    \ += data.get(index) < x;\n                }\n            }\n        );\n    \
    \    return result;\n    }\n};\n\nstruct AddBlock {\n    std::vector<long long>\
    \ sorted;\n    long long lazy = 0;\n\n    void build(const std::vector<long long>&\
    \ values, int left, int right) {\n        sorted.assign(values.begin() + left,\
    \ values.begin() + right);\n        std::sort(sorted.begin(), sorted.end());\n\
    \        lazy = 0;\n    }\n\n    void push(std::vector<long long>& values, int\
    \ left, int right) {\n        for (int index = left; index < right; ++index) {\n\
    \            values[index] += lazy;\n        }\n        lazy = 0;\n    }\n\n \
    \   long long value(const long long& raw, int) const {\n        return raw + lazy;\n\
    \    }\n};\n\nstruct RangeAddCountLess {\n    m1une::ds::SqrtBlocks<long long,\
    \ AddBlock> data;\n\n    explicit RangeAddCountLess(\n        std::vector<long\
    \ long> values,\n        int block_size = -1\n    ) : data(std::move(values),\
    \ block_size) {}\n\n    void add(int left, int right, long long value) {\n   \
    \     data.update_range(\n            left,\n            right,\n            [&](int,\
    \ AddBlock& block) {\n                block.lazy += value;\n            },\n \
    \           [&](int segment_left,\n                int segment_right,\n      \
    \          int,\n                std::vector<long long>& values,\n           \
    \     AddBlock&) {\n                for (int index = segment_left; index < segment_right;\
    \ ++index) {\n                    values[index] += value;\n                }\n\
    \            }\n        );\n    }\n\n    int count_less(int left, int right, long\
    \ long x) const {\n        int result = 0;\n        data.query_range(\n      \
    \      left,\n            right,\n            [&](int, const AddBlock& block)\
    \ {\n                result += int(std::lower_bound(\n                    block.sorted.begin(),\n\
    \                    block.sorted.end(),\n                    x - block.lazy\n\
    \                ) - block.sorted.begin());\n            },\n            [&](int\
    \ segment_left, int segment_right, int, const AddBlock&) {\n                for\
    \ (int index = segment_left; index < segment_right; ++index) {\n             \
    \       result += data.get(index) < x;\n                }\n            }\n   \
    \     );\n        return result;\n    }\n\n    long long get(int index) const\
    \ {\n        return data.get(index);\n    }\n};\n\nint naive_count_less(\n   \
    \ const std::vector<long long>& values,\n    int left,\n    int right,\n    long\
    \ long x\n) {\n    int result = 0;\n    for (int index = left; index < right;\
    \ ++index) {\n        result += values[index] < x;\n    }\n    return result;\n\
    }\n\nvoid test_fixed() {\n    RangeCountLess empty(std::vector<long long>{});\n\
    \    assert(empty.data.empty());\n    assert(empty.data.size() == 0);\n    assert(empty.data.block_size()\
    \ == 1);\n    assert(empty.data.block_count() == 0);\n    assert(empty.count_less(0,\
    \ 0, 10) == 0);\n\n    RangeAddCountLess custom_empty(std::vector<long long>{},\
    \ 7);\n    assert(custom_empty.data.block_size() == 7);\n    assert(custom_empty.data.block_count()\
    \ == 0);\n    custom_empty.add(0, 0, 3);\n    assert(custom_empty.count_less(0,\
    \ 0, 0) == 0);\n\n    RangeCountLess one(std::vector<long long>{4});\n    assert(one.count_less(0,\
    \ 1, 5) == 1);\n    one.set(0, 9);\n    assert(one.count_less(0, 1, 5) == 0);\n\
    \    one.increment(0);\n    assert(one.data[0] == 10);\n\n    std::vector<long\
    \ long> initial = {3, -1, 4, 1, 5};\n    RangeAddCountLess range_add(initial,\
    \ 3);\n    assert(range_add.data.block_size() == 3);\n    assert(range_add.data.block_count()\
    \ == 2);\n    assert(range_add.data.block_of(4) == 1);\n    std::pair<int, int>\
    \ expected_range(0, 3);\n    assert(range_add.data.block_range(0) == expected_range);\n\
    \    range_add.add(0, 3, 7);\n    initial[0] += 7;\n    initial[1] += 7;\n   \
    \ initial[2] += 7;\n    assert(range_add.get(1) == initial[1]);\n    range_add.add(1,\
    \ 5, -2);\n    for (int index = 1; index < 5; ++index) initial[index] -= 2;\n\
    \    for (int index = 0; index < 5; ++index) {\n        assert(range_add.get(index)\
    \ == initial[index]);\n    }\n    for (long long x = -5; x <= 15; ++x) {\n   \
    \     assert(\n            range_add.count_less(1, 5, x) ==\n            naive_count_less(initial,\
    \ 1, 5, x)\n        );\n    }\n}\n\nvoid test_range_count_less_randomized() {\n\
    \    std::uint64_t state = 0xA0761D6478BD642FULL;\n    auto random = [&]() {\n\
    \        state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int n = int(random()\
    \ % 26);\n        std::vector<long long> naive(n);\n        for (long long& value\
    \ : naive) {\n            value = static_cast<long long>(random() % 21) - 10;\n\
    \        }\n        int block_size = trial % 2 == 0 ? -1 : int(random() % 8) +\
    \ 1;\n        RangeCountLess blocks(naive, block_size);\n\n        for (int operation\
    \ = 0; operation < 250; ++operation) {\n            if (n != 0 && random() % 3\
    \ == 0) {\n                int index = int(random() % n);\n                long\
    \ long value = static_cast<long long>(random() % 31) - 15;\n                naive[index]\
    \ = value;\n                blocks.set(index, value);\n            } else {\n\
    \                int left = int(random() % (n + 1));\n                int right\
    \ = int(random() % (n + 1));\n                if (right < left) std::swap(left,\
    \ right);\n                long long x = static_cast<long long>(random() % 35)\
    \ - 17;\n                assert(\n                    blocks.count_less(left,\
    \ right, x) ==\n                    naive_count_less(naive, left, right, x)\n\
    \                );\n            }\n        }\n    }\n}\n\nvoid test_range_add_count_less_randomized()\
    \ {\n    std::uint64_t state = 0xE7037ED1A0B428DBULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int\
    \ n = int(random() % 26);\n        std::vector<long long> naive(n);\n        for\
    \ (long long& value : naive) {\n            value = static_cast<long long>(random()\
    \ % 21) - 10;\n        }\n        int block_size = trial % 2 == 0 ? -1 : int(random()\
    \ % 8) + 1;\n        RangeAddCountLess blocks(naive, block_size);\n\n        for\
    \ (int operation = 0; operation < 250; ++operation) {\n            int type =\
    \ int(random() % 3);\n            if (type == 0) {\n                int left =\
    \ int(random() % (n + 1));\n                int right = int(random() % (n + 1));\n\
    \                if (right < left) std::swap(left, right);\n                long\
    \ long value = static_cast<long long>(random() % 15) - 7;\n                blocks.add(left,\
    \ right, value);\n                for (int index = left; index < right; ++index)\
    \ {\n                    naive[index] += value;\n                }\n         \
    \   } else if (type == 1 || n == 0) {\n                int left = int(random()\
    \ % (n + 1));\n                int right = int(random() % (n + 1));\n        \
    \        if (right < left) std::swap(left, right);\n                long long\
    \ x = static_cast<long long>(random() % 61) - 30;\n                assert(\n \
    \                   blocks.count_less(left, right, x) ==\n                   \
    \ naive_count_less(naive, left, right, x)\n                );\n            } else\
    \ {\n                int index = int(random() % n);\n                assert(blocks.get(index)\
    \ == naive[index]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_range_count_less_randomized();\n\
    \    test_range_add_count_less_randomized();\n\n    long long a, b;\n    fast_input\
    \ >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/range_query/sqrt_blocks.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sqrt_blocks.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sqrt_blocks.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sqrt_blocks.test.cpp
- /verify/verify/ds/range_query/sqrt_blocks.test.cpp.html
title: verify/ds/range_query/sqrt_blocks.test.cpp
---
