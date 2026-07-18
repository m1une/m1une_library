---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/static_range_mode_query.hpp
    title: Static Range Mode Query
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_mode_query
    links:
    - https://judge.yosupo.jp/problem/static_range_mode_query
  bundledCode: "#line 1 \"verify/ds/range_query/static_range_mode_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\n\
    \n#line 1 \"ds/range_query/static_range_mode_query.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <utility>\n#include <vector>\n\n\
    namespace m1une {\nnamespace ds {\n\n// Static range modes with O(N sqrt N) preprocessing\
    \ and O(sqrt N) queries.\ntemplate <class T>\nstruct StaticRangeModeQuery {\n\
    \    using result_type = std::pair<T, int>;\n\n   private:\n    int _n;\n    int\
    \ _block_size;\n    int _block_count;\n    std::vector<T> _values;\n    std::vector<int>\
    \ _rank;\n    std::vector<std::vector<int>> _boundary_frequency;\n    std::vector<std::vector<int>>\
    \ _mode;\n    std::vector<std::vector<int>> _mode_frequency;\n    std::vector<int>\
    \ _extra_frequency;\n    std::vector<unsigned int> _seen_at;\n    unsigned int\
    \ _query_time;\n\n    int block_start(int block) const {\n        return std::min(_n,\
    \ block * _block_size);\n    }\n\n    void build_boundary_frequency() {\n    \
    \    int value_count = int(_values.size());\n        _boundary_frequency.assign(\n\
    \            _block_count + 1,\n            std::vector<int>(value_count, 0)\n\
    \        );\n        for (int block = 0; block < _block_count; block++) {\n  \
    \          _boundary_frequency[block + 1] = _boundary_frequency[block];\n    \
    \        for (\n                int i = block_start(block);\n                i\
    \ < block_start(block + 1);\n                i++\n            ) {\n          \
    \      _boundary_frequency[block + 1][_rank[i]]++;\n            }\n        }\n\
    \    }\n\n    void build_block_modes() {\n        int value_count = int(_values.size());\n\
    \        _mode.assign(\n            _block_count,\n            std::vector<int>(_block_count\
    \ + 1, -1)\n        );\n        _mode_frequency.assign(\n            _block_count,\n\
    \            std::vector<int>(_block_count + 1, 0)\n        );\n\n        std::vector<int>\
    \ frequency(value_count, 0);\n        for (int first = 0; first < _block_count;\
    \ first++) {\n            std::fill(frequency.begin(), frequency.end(), 0);\n\
    \            int best = -1;\n            int best_frequency = 0;\n           \
    \ for (int last = first; last < _block_count; last++) {\n                for (\n\
    \                    int i = block_start(last);\n                    i < block_start(last\
    \ + 1);\n                    i++\n                ) {\n                    int\
    \ value = _rank[i];\n                    frequency[value]++;\n               \
    \     if (frequency[value] > best_frequency) {\n                        best =\
    \ value;\n                        best_frequency = frequency[value];\n       \
    \             }\n                }\n                _mode[first][last + 1] = best;\n\
    \                _mode_frequency[first][last + 1] = best_frequency;\n        \
    \    }\n        }\n    }\n\n   public:\n    StaticRangeModeQuery()\n        :\
    \ _n(0),\n          _block_size(1),\n          _block_count(0),\n          _query_time(0)\
    \ {}\n\n    explicit StaticRangeModeQuery(const std::vector<T>& values)\n    \
    \    : _n(int(values.size())),\n          _block_size(1),\n          _block_count(0),\n\
    \          _values(values),\n          _query_time(0) {\n        if (_n == 0)\
    \ return;\n\n        _block_size = std::max(\n            1,\n            int(std::sqrt(static_cast<long\
    \ double>(_n)))\n        );\n        while (1LL * _block_size * _block_size <\
    \ _n) _block_size++;\n        _block_count = (_n + _block_size - 1) / _block_size;\n\
    \n        std::sort(_values.begin(), _values.end());\n        _values.erase(\n\
    \            std::unique(_values.begin(), _values.end()),\n            _values.end()\n\
    \        );\n        _rank.resize(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            _rank[i] = int(\n                std::lower_bound(_values.begin(),\
    \ _values.end(), values[i])\n                - _values.begin()\n            );\n\
    \        }\n\n        build_boundary_frequency();\n        build_block_modes();\n\
    \        _extra_frequency.assign(_values.size(), 0);\n        _seen_at.assign(_values.size(),\
    \ 0);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int block_size() const\
    \ {\n        return _block_size;\n    }\n\n    // Returns {a mode, its frequency}\
    \ for the nonempty range [left, right).\n    // The method reuses internal scratch\
    \ arrays and is therefore non-const.\n    result_type query(int left, int right)\
    \ {\n        assert(0 <= left && left < right && right <= _n);\n\n        int\
    \ first_full = (left + _block_size - 1) / _block_size;\n        int last_full\
    \ = right / _block_size;\n        int left_end = std::min(right, block_start(first_full));\n\
    \        int right_start = std::max(left_end, block_start(last_full));\n\n   \
    \     int answer = -1;\n        int answer_frequency = 0;\n        if (first_full\
    \ < last_full) {\n            answer = _mode[first_full][last_full];\n       \
    \     answer_frequency = _mode_frequency[first_full][last_full];\n        }\n\n\
    \        _query_time++;\n        if (_query_time == 0) {\n            std::fill(_seen_at.begin(),\
    \ _seen_at.end(), 0);\n            _query_time = 1;\n        }\n        std::vector<int>\
    \ touched;\n        touched.reserve(left_end - left + right - right_start);\n\
    \        auto add = [&](int index) {\n            int value = _rank[index];\n\
    \            if (_seen_at[value] != _query_time) {\n                _seen_at[value]\
    \ = _query_time;\n                _extra_frequency[value] = 0;\n             \
    \   touched.push_back(value);\n            }\n            _extra_frequency[value]++;\n\
    \        };\n        for (int i = left; i < left_end; i++) add(i);\n        for\
    \ (int i = right_start; i < right; i++) add(i);\n\n        for (int value : touched)\
    \ {\n            int frequency = _extra_frequency[value];\n            if (first_full\
    \ < last_full) {\n                frequency +=\n                    _boundary_frequency[last_full][value]\n\
    \                    - _boundary_frequency[first_full][value];\n            }\n\
    \            if (frequency > answer_frequency) {\n                answer = value;\n\
    \                answer_frequency = frequency;\n            }\n        }\n   \
    \     assert(answer != -1);\n        return {_values[answer], answer_frequency};\n\
    \    }\n\n    result_type mode(int left, int right) {\n        return query(left,\
    \ right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1\
    \ \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include\
    \ <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/range_query/static_range_mode_query.test.cpp\"\
    \n\n#line 9 \"verify/ds/range_query/static_range_mode_query.test.cpp\"\n#include\
    \ <map>\n#line 12 \"verify/ds/range_query/static_range_mode_query.test.cpp\"\n\
    \nnamespace {\n\nstd::pair<int, int> brute(\n    const std::vector<int>& values,\n\
    \    int left,\n    int right\n) {\n    std::map<int, int> frequency;\n    std::pair<int,\
    \ int> result{values[left], 0};\n    for (int i = left; i < right; i++) {\n  \
    \      int count = ++frequency[values[i]];\n        if (count > result.second)\
    \ result = {values[i], count};\n    }\n    return result;\n}\n\nvoid test_randomized()\
    \ {\n    m1une::ds::StaticRangeModeQuery<int> empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n\n    std::uint64_t state = 2718281828ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 500;\
    \ trial++) {\n        int n = int(random() % 50) + 1;\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 13) - 6;\n\
    \        m1une::ds::StaticRangeModeQuery<int> structure(values);\n        assert(structure.size()\
    \ == n);\n        assert(!structure.empty());\n\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                auto [value, frequency] = structure.query(left, right);\n\
    \                auto expected = brute(values, left, right);\n               \
    \ assert(frequency == expected.second);\n                assert(\n           \
    \         std::count(\n                        values.begin() + left,\n      \
    \                  values.begin() + right,\n                        value\n  \
    \                  ) == frequency\n                );\n            }\n       \
    \ }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\n \
    \   m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0, query_count = 0;\n    input.read(n, query_count);\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) input.read(value);\n\n    m1une::ds::StaticRangeModeQuery<int>\
    \ structure(values);\n    while (query_count--) {\n        int left = 0, right\
    \ = 0;\n        input.read(left, right);\n        auto [mode, frequency] = structure.query(left,\
    \ right);\n        output.println(mode, frequency);\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\
    \n\n#include \"../../../ds/range_query/static_range_mode_query.hpp\"\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <map>\n#include <utility>\n#include <vector>\n\n\
    namespace {\n\nstd::pair<int, int> brute(\n    const std::vector<int>& values,\n\
    \    int left,\n    int right\n) {\n    std::map<int, int> frequency;\n    std::pair<int,\
    \ int> result{values[left], 0};\n    for (int i = left; i < right; i++) {\n  \
    \      int count = ++frequency[values[i]];\n        if (count > result.second)\
    \ result = {values[i], count};\n    }\n    return result;\n}\n\nvoid test_randomized()\
    \ {\n    m1une::ds::StaticRangeModeQuery<int> empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n\n    std::uint64_t state = 2718281828ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 500;\
    \ trial++) {\n        int n = int(random() % 50) + 1;\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 13) - 6;\n\
    \        m1une::ds::StaticRangeModeQuery<int> structure(values);\n        assert(structure.size()\
    \ == n);\n        assert(!structure.empty());\n\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                auto [value, frequency] = structure.query(left, right);\n\
    \                auto expected = brute(values, left, right);\n               \
    \ assert(frequency == expected.second);\n                assert(\n           \
    \         std::count(\n                        values.begin() + left,\n      \
    \                  values.begin() + right,\n                        value\n  \
    \                  ) == frequency\n                );\n            }\n       \
    \ }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\n \
    \   m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0, query_count = 0;\n    input.read(n, query_count);\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) input.read(value);\n\n    m1une::ds::StaticRangeModeQuery<int>\
    \ structure(values);\n    while (query_count--) {\n        int left = 0, right\
    \ = 0;\n        input.read(left, right);\n        auto [mode, frequency] = structure.query(left,\
    \ right);\n        output.println(mode, frequency);\n    }\n}\n"
  dependsOn:
  - ds/range_query/static_range_mode_query.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/static_range_mode_query.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/static_range_mode_query.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/static_range_mode_query.test.cpp
- /verify/verify/ds/range_query/static_range_mode_query.test.cpp.html
title: verify/ds/range_query/static_range_mode_query.test.cpp
---
