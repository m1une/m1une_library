---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sliding_window_aggregation_deque.hpp
    title: Sliding Window Aggregation Deque
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/deque_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/deque_operate_all_composite
  bundledCode: "#line 1 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#line 1 \"ds/range_query/sliding_window_aggregation_deque.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for groups.\
    \ A type satisfying this concept must also obey the group\n// laws; concepts can\
    \ check the interface but not the algebraic properties.\ntemplate <typename M>\n\
    concept IsGroup = IsMonoid<M> && requires(typename M::value_type a) {\n    { M::inv(a)\
    \ } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ groups. Commutativity is a semantic requirement and\n// cannot be checked by\
    \ a C++ concept.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 10 \"ds/range_query/sliding_window_aggregation_deque.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A deque supporting the ordered product\
    \ of all elements in amortized O(1).\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct SlidingWindowAggregationDeque {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Entry {\n        T value;\n        T product;\n    };\n\
    \n    // The back of _front is the front of the deque. _back is in deque order.\n\
    \    std::vector<Entry> _front;\n    std::vector<Entry> _back;\n\n    void rebalance(bool\
    \ need_front) {\n        assert(empty() == false);\n\n        std::vector<T> values;\n\
    \        values.reserve(size());\n        for (auto iter = _front.rbegin(); iter\
    \ != _front.rend(); ++iter) {\n            values.push_back(std::move(iter->value));\n\
    \        }\n        for (Entry& entry : _back) values.push_back(std::move(entry.value));\n\
    \n        _front.clear();\n        _back.clear();\n\n        const std::size_t\
    \ front_size = need_front ? (values.size() + 1) / 2 : values.size() / 2;\n   \
    \     for (std::size_t index = front_size; index > 0; --index) {\n           \
    \ push_front(std::move(values[index - 1]));\n        }\n        for (std::size_t\
    \ index = front_size; index < values.size(); ++index) {\n            push_back(std::move(values[index]));\n\
    \        }\n    }\n\n    void ensure_front() {\n        if (_front.empty()) rebalance(true);\n\
    \    }\n\n    void ensure_back() {\n        if (_back.empty()) rebalance(false);\n\
    \    }\n\n   public:\n    SlidingWindowAggregationDeque() = default;\n\n    explicit\
    \ SlidingWindowAggregationDeque(const std::vector<T>& values) {\n        reserve(values.size());\n\
    \        for (const T& value : values) push_back(value);\n    }\n\n    explicit\
    \ SlidingWindowAggregationDeque(std::vector<T>&& values) {\n        reserve(values.size());\n\
    \        for (T& value : values) push_back(std::move(value));\n    }\n\n    std::size_t\
    \ size() const {\n        return _front.size() + _back.size();\n    }\n\n    bool\
    \ empty() const {\n        return _front.empty() && _back.empty();\n    }\n\n\
    \    void reserve(std::size_t capacity) {\n        _front.reserve(capacity);\n\
    \        _back.reserve(capacity);\n    }\n\n    void clear() {\n        _front.clear();\n\
    \        _back.clear();\n    }\n\n    void push_front(T value) {\n        T product\
    \ = _front.empty() ? value : Monoid::op(value, _front.back().product);\n     \
    \   _front.push_back(Entry{\n            std::move(value),\n            std::move(product),\n\
    \        });\n    }\n\n    void push_back(T value) {\n        T product = _back.empty()\
    \ ? value : Monoid::op(_back.back().product, value);\n        _back.push_back(Entry{\n\
    \            std::move(value),\n            std::move(product),\n        });\n\
    \    }\n\n    void pop_front() {\n        assert(!empty());\n        ensure_front();\n\
    \        _front.pop_back();\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        ensure_back();\n        _back.pop_back();\n    }\n\n    const T& front()\
    \ {\n        assert(!empty());\n        ensure_front();\n        return _front.back().value;\n\
    \    }\n\n    const T& back() {\n        assert(!empty());\n        ensure_back();\n\
    \        return _back.back().value;\n    }\n\n    // Returns the product in deque\
    \ order, or the identity when empty.\n    T prod() const {\n        if (_front.empty())\
    \ {\n            return _back.empty() ? Monoid::id() : _back.back().product;\n\
    \        }\n        if (_back.empty()) return _front.back().product;\n       \
    \ return Monoid::op(_front.back().product, _back.back().product);\n    }\n\n \
    \   T all_prod() const {\n        return prod();\n    }\n};\n\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nusing SwagDeque = SlidingWindowAggregationDeque<Monoid>;\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n#include <cstdint>\n#include <deque>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\
    \n#include <array>\n#include <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
    #include <type_traits>\n#line 17 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/ds/range_query/sliding_window_aggregation_deque.test.cpp\"\
    \n\nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n  \
    \  static value_type id() {\n        return \"\";\n    }\n\n    static value_type\
    \ op(const value_type& left, const value_type& right) {\n        return left +\
    \ right;\n    }\n};\n\nconstexpr long long mod = 998244353;\n\nstruct Affine {\n\
    \    struct value_type {\n        long long a;\n        long long b;\n    };\n\
    \n    static value_type id() {\n        return value_type{1, 0};\n    }\n\n  \
    \  static value_type op(const value_type& first, const value_type& second) {\n\
    \        return value_type{\n            second.a * first.a % mod,\n         \
    \   (second.a * first.b + second.b) % mod,\n        };\n    }\n};\n\nvoid test_fixed()\
    \ {\n    m1une::ds::SwagDeque<Concat> deque;\n    assert(deque.empty());\n   \
    \ assert(deque.prod().empty());\n\n    deque.reserve(10);\n    deque.push_back(\"\
    b\");\n    deque.push_front(\"a\");\n    deque.push_back(\"c\");\n    deque.push_front(\"\
    z\");\n    assert(deque.size() == 4);\n    assert(deque.front() == \"z\");\n \
    \   assert(deque.back() == \"c\");\n    assert(deque.prod() == \"zabc\");\n\n\
    \    deque.pop_front();\n    deque.pop_back();\n    assert(deque.front() == \"\
    a\");\n    assert(deque.back() == \"b\");\n    assert(deque.all_prod() == \"ab\"\
    );\n\n    deque.clear();\n    assert(deque.empty());\n\n    std::vector<std::string>\
    \ values = {\"x\", \"y\", \"z\"};\n    m1une::ds::SlidingWindowAggregationDeque<Concat>\
    \ built(values);\n    assert(built.prod() == \"xyz\");\n    built.pop_back();\n\
    \    built.pop_back();\n    assert(built.front() == \"x\");\n    assert(built.back()\
    \ == \"x\");\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 904;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    m1une::ds::SwagDeque<Concat>\
    \ deque;\n    std::deque<std::string> expected;\n    for (int operation = 0; operation\
    \ < 50000; ++operation) {\n        int type = expected.empty() ? int(random()\
    \ % 2) : int(random() % 4);\n        if (type == 0) {\n            std::string\
    \ value(1, char('a' + random() % 5));\n            deque.push_front(value);\n\
    \            expected.push_front(value);\n        } else if (type == 1) {\n  \
    \          std::string value(1, char('a' + random() % 5));\n            deque.push_back(value);\n\
    \            expected.push_back(value);\n        } else if (type == 2) {\n   \
    \         deque.pop_front();\n            expected.pop_front();\n        } else\
    \ {\n            deque.pop_back();\n            expected.pop_back();\n       \
    \ }\n\n        assert(deque.size() == expected.size());\n        assert(deque.empty()\
    \ == expected.empty());\n        std::string product;\n        for (const std::string&\
    \ value : expected) product += value;\n        assert(deque.prod() == product);\n\
    \        if (!expected.empty()) {\n            assert(deque.front() == expected.front());\n\
    \            assert(deque.back() == expected.back());\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \n    int query_count;\n    fast_input >> query_count;\n    m1une::ds::SwagDeque<Affine>\
    \ deque;\n    while (query_count--) {\n        int type;\n        fast_input >>\
    \ type;\n        if (type == 0 || type == 1) {\n            Affine::value_type\
    \ function;\n            fast_input >> function.a >> function.b;\n           \
    \ if (type == 0) {\n                deque.push_front(function);\n            }\
    \ else {\n                deque.push_back(function);\n            }\n        }\
    \ else if (type == 2) {\n            deque.pop_front();\n        } else if (type\
    \ == 3) {\n            deque.pop_back();\n        } else {\n            long long\
    \ x;\n            fast_input >> x;\n            auto function = deque.prod();\n\
    \            fast_output << (function.a * x + function.b) % mod << '\\n';\n  \
    \      }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#include \"../../../ds/range_query/sliding_window_aggregation_deque.hpp\"\n\
    \n#include <cassert>\n#include <cstdint>\n#include <deque>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <string>\n#include <vector>\n\nnamespace {\n\nstruct Concat {\n   \
    \ using value_type = std::string;\n\n    static value_type id() {\n        return\
    \ \"\";\n    }\n\n    static value_type op(const value_type& left, const value_type&\
    \ right) {\n        return left + right;\n    }\n};\n\nconstexpr long long mod\
    \ = 998244353;\n\nstruct Affine {\n    struct value_type {\n        long long\
    \ a;\n        long long b;\n    };\n\n    static value_type id() {\n        return\
    \ value_type{1, 0};\n    }\n\n    static value_type op(const value_type& first,\
    \ const value_type& second) {\n        return value_type{\n            second.a\
    \ * first.a % mod,\n            (second.a * first.b + second.b) % mod,\n     \
    \   };\n    }\n};\n\nvoid test_fixed() {\n    m1une::ds::SwagDeque<Concat> deque;\n\
    \    assert(deque.empty());\n    assert(deque.prod().empty());\n\n    deque.reserve(10);\n\
    \    deque.push_back(\"b\");\n    deque.push_front(\"a\");\n    deque.push_back(\"\
    c\");\n    deque.push_front(\"z\");\n    assert(deque.size() == 4);\n    assert(deque.front()\
    \ == \"z\");\n    assert(deque.back() == \"c\");\n    assert(deque.prod() == \"\
    zabc\");\n\n    deque.pop_front();\n    deque.pop_back();\n    assert(deque.front()\
    \ == \"a\");\n    assert(deque.back() == \"b\");\n    assert(deque.all_prod()\
    \ == \"ab\");\n\n    deque.clear();\n    assert(deque.empty());\n\n    std::vector<std::string>\
    \ values = {\"x\", \"y\", \"z\"};\n    m1une::ds::SlidingWindowAggregationDeque<Concat>\
    \ built(values);\n    assert(built.prod() == \"xyz\");\n    built.pop_back();\n\
    \    built.pop_back();\n    assert(built.front() == \"x\");\n    assert(built.back()\
    \ == \"x\");\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 904;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    m1une::ds::SwagDeque<Concat>\
    \ deque;\n    std::deque<std::string> expected;\n    for (int operation = 0; operation\
    \ < 50000; ++operation) {\n        int type = expected.empty() ? int(random()\
    \ % 2) : int(random() % 4);\n        if (type == 0) {\n            std::string\
    \ value(1, char('a' + random() % 5));\n            deque.push_front(value);\n\
    \            expected.push_front(value);\n        } else if (type == 1) {\n  \
    \          std::string value(1, char('a' + random() % 5));\n            deque.push_back(value);\n\
    \            expected.push_back(value);\n        } else if (type == 2) {\n   \
    \         deque.pop_front();\n            expected.pop_front();\n        } else\
    \ {\n            deque.pop_back();\n            expected.pop_back();\n       \
    \ }\n\n        assert(deque.size() == expected.size());\n        assert(deque.empty()\
    \ == expected.empty());\n        std::string product;\n        for (const std::string&\
    \ value : expected) product += value;\n        assert(deque.prod() == product);\n\
    \        if (!expected.empty()) {\n            assert(deque.front() == expected.front());\n\
    \            assert(deque.back() == expected.back());\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \n    int query_count;\n    fast_input >> query_count;\n    m1une::ds::SwagDeque<Affine>\
    \ deque;\n    while (query_count--) {\n        int type;\n        fast_input >>\
    \ type;\n        if (type == 0 || type == 1) {\n            Affine::value_type\
    \ function;\n            fast_input >> function.a >> function.b;\n           \
    \ if (type == 0) {\n                deque.push_front(function);\n            }\
    \ else {\n                deque.push_back(function);\n            }\n        }\
    \ else if (type == 2) {\n            deque.pop_front();\n        } else if (type\
    \ == 3) {\n            deque.pop_back();\n        } else {\n            long long\
    \ x;\n            fast_input >> x;\n            auto function = deque.prod();\n\
    \            fast_output << (function.a * x + function.b) % mod << '\\n';\n  \
    \      }\n    }\n}\n"
  dependsOn:
  - ds/range_query/sliding_window_aggregation_deque.hpp
  - monoid/concept.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
- /verify/verify/ds/range_query/sliding_window_aggregation_deque.test.cpp.html
title: verify/ds/range_query/sliding_window_aggregation_deque.test.cpp
---
