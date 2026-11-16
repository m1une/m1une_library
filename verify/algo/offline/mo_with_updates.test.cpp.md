---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo_with_updates.hpp
    title: Mo's Algorithm with Updates
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_frequency
    links:
    - https://judge.yosupo.jp/problem/point_set_range_frequency
  bundledCode: "#line 1 \"verify/algo/offline/mo_with_updates.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_frequency\"\n\n#line\
    \ 1 \"algo/offline/mo_with_updates.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <cstddef>\n#include <limits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Offline Mo ordering in\
    \ (left, right, update time). Array values and the\n// before/after values of\
    \ each point update are owned by the caller.\nstruct MoWithUpdates {\n    struct\
    \ Query {\n        int left;\n        int right;\n        int time;\n        int\
    \ id;\n    };\n\n   private:\n    int _n;\n    int _update_count = 0;\n    std::vector<Query>\
    \ _queries;\n\n   public:\n    MoWithUpdates() : _n(0) {}\n\n    explicit MoWithUpdates(int\
    \ n) : _n(n) { assert(0 <= n); }\n\n    int size() const { return _n; }\n\n  \
    \  int query_count() const { return int(_queries.size()); }\n\n    int update_count()\
    \ const { return _update_count; }\n\n    bool empty() const { return _queries.empty();\
    \ }\n\n    const std::vector<Query>& queries() const { return _queries; }\n\n\
    \    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n        _update_count = 0;\n    }\n\n    // Registers\
    \ one update and returns its zero-based ID. Time t means that\n    // updates\
    \ [0, t) have been applied, including any no-op assignments.\n    int add_update()\
    \ {\n        assert(_update_count < std::numeric_limits<int>::max());\n      \
    \  return _update_count++;\n    }\n\n    int add_query(int left, int right) {\
    \ return add_query(left, right, _update_count); }\n\n    // Historical times are\
    \ allowed, but the updates must already be registered.\n    int add_query(int\
    \ left, int right, int time) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        assert(0 <= time && time <= _update_count);\n        assert(_queries.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{left, right, time, id});\n        return id;\n\
    \    }\n\n    std::vector<int> order(int block_size = 0) const {\n        const\
    \ int q = query_count();\n        if (q == 0) return {};\n        auto times =\
    \ std::minmax_element(_queries.begin(), _queries.end(),\n            [](const\
    \ Query& a, const Query& b) { return a.time < b.time; });\n        const int time_span\
    \ = times.second->time - times.first->time;\n        if (block_size <= 0) {\n\
    \            const double n = _n;\n            const double static_size = n /\
    \ std::sqrt(double(q));\n            const double dynamic_size = std::cbrt(n *\
    \ n * double(time_span) / double(q));\n            const double estimate = std::max(static_size,\
    \ dynamic_size);\n            block_size = int(std::clamp(estimate, 1.0, double(std::max(1,\
    \ _n))));\n        }\n\n        struct Entry {\n            int left_block;\n\
    \            int right_block;\n            int time;\n            int id;\n  \
    \      };\n        std::vector<Entry> entries;\n        entries.reserve(q);\n\
    \        for (const Query& query : _queries) {\n            entries.push_back(Entry{\n\
    \                query.left / block_size, query.right / block_size, query.time,\
    \ query.id});\n        }\n        std::sort(entries.begin(), entries.end(), [&](const\
    \ Entry& a, const Entry& b) {\n            if (a.left_block != b.left_block) return\
    \ a.left_block < b.left_block;\n            const bool reverse_right = (a.left_block\
    \ & 1) != 0;\n            if (time_span != 0) {\n                if (a.right_block\
    \ != b.right_block) {\n                    return reverse_right ? a.right_block\
    \ > b.right_block : a.right_block < b.right_block;\n                }\n      \
    \          if (a.time != b.time) {\n                    return ((a.left_block\
    \ ^ a.right_block) & 1) ? a.time > b.time : a.time < b.time;\n               \
    \ }\n            }\n            const int a_right = _queries[a.id].right;\n  \
    \          const int b_right = _queries[b.id].right;\n            if (a_right\
    \ != b_right) return reverse_right ? a_right > b_right : a_right < b_right;\n\
    \            return a.id < b.id;\n        });\n        std::vector<int> result;\n\
    \        result.reserve(q);\n        for (const Entry& entry : entries) result.push_back(entry.id);\n\
    \        return result;\n    }\n\n    // apply(id, left, right) moves time id\
    \ -> id + 1; undo(id, left, right)\n    // reverses that update. Both must update\
    \ the array even outside the active\n    // range, and must repair the maintained\
    \ answer when necessary inside it.\n    template <class AddLeft, class AddRight,\
    \ class RemoveLeft, class RemoveRight,\n              class Apply, class Undo,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right,\n             Apply apply, Undo undo,\
    \ Answer answer, int block_size = 0) const {\n        int left = 0;\n        int\
    \ right = 0;\n        int time = 0;\n        for (int query_index : order(block_size))\
    \ {\n            const Query& query = _queries[query_index];\n            while\
    \ (time < query.time) {\n                apply(time, left, right);\n         \
    \       ++time;\n            }\n            while (query.time < time) {\n    \
    \            --time;\n                undo(time, left, right);\n            }\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    template <class Add, class Remove, class Apply, class\
    \ Undo, class Answer>\n    void run(Add add, Remove remove, Apply apply, Undo\
    \ undo, Answer answer,\n             int block_size = 0) const {\n        run(add,\
    \ add, remove, remove, apply, undo, answer, block_size);\n    }\n};\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 4 \"verify/algo/offline/mo_with_updates.test.cpp\"\
    \n\n#line 7 \"verify/algo/offline/mo_with_updates.test.cpp\"\n#include <cstdint>\n\
    #include <numeric>\n#include <string>\n#line 11 \"verify/algo/offline/mo_with_updates.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <array>\n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#line 15 \"utilities/fast_io.hpp\"\n\
    #include <sys/stat.h>\n#include <type_traits>\n#include <utility>\n#include <unistd.h>\n\
    #line 20 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    \nstruct FastOutput;\n\nnamespace internal {\n\n// Shared with the convenience\
    \ helpers in template.hpp.\ninline FastOutput* standard_output_instance = nullptr;\n\
    \n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct\
    \ is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
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
    \    char _range_separator;\n    std::string* _capture = nullptr;\n\n    template\
    \ <class T>\n    std::string format_cell(const T& value) {\n        std::string\
    \ result;\n        struct CaptureGuard {\n            std::string*& target;\n\
    \            std::string* previous;\n            ~CaptureGuard() { target = previous;\
    \ }\n        } guard{_capture, _capture};\n        _capture = &result;\n     \
    \   write(value);\n        return result;\n    }\n\n    template <class Matrix>\n\
    \    void write_aligned_matrix(const Matrix& matrix) {\n        std::vector<std::vector<std::string>>\
    \ rows;\n        std::vector<std::size_t> widths;\n        for (const auto& row\
    \ : matrix) {\n            auto& cells = rows.emplace_back();\n            std::size_t\
    \ column = 0;\n            for (const auto& value : row) {\n                cells.push_back(format_cell(value));\n\
    \                if (column == widths.size()) widths.push_back(0);\n         \
    \       widths[column] = std::max(widths[column], cells.back().size());\n    \
    \            ++column;\n            }\n        }\n        bool first = true;\n\
    \        for (const auto& row : rows) {\n            if (!first) write_char('\\\
    n');\n            first = false;\n            for (std::size_t column = 0; column\
    \ < row.size(); ++column) {\n                if (column != 0) write_char(_range_separator);\n\
    \                for (std::size_t padding = row[column].size();\n            \
    \         padding < widths[column]; ++padding) {\n                    write_char('\
    \ ');\n                }\n                write(row[column]);\n            }\n\
    \        }\n    }\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream),\n          _position(0),\n          _precision(6),\n\
    \          _float_format(std::chars_format::general),\n          _range_separator('\
    \ ') {\n        if (_stream == stdout\n            && internal::standard_output_instance\
    \ == nullptr) {\n            internal::standard_output_instance = this;\n    \
    \    }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \        if (internal::standard_output_instance == this) {\n            internal::standard_output_instance\
    \ = nullptr;\n        }\n    }\n\n    void flush() {\n        if (_position !=\
    \ 0) {\n            std::fwrite(_buffer, 1, _position, _stream);\n           \
    \ _position = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void\
    \ write_char(char c) {\n        if (_capture != nullptr) {\n            _capture->push_back(c);\n\
    \            return;\n        }\n        if (_position == buffer_size) flush();\n\
    \        _buffer[_position++] = c;\n    }\n\n    void write(const char* s) {\n\
    \        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        if (_capture != nullptr) {\n            _capture->append(s);\n\
    \            return;\n        }\n        std::size_t position = 0;\n        while\
    \ (position < s.size()) {\n            if (_position == buffer_size) flush();\n\
    \            const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
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
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_capture\
    \ == nullptr && _position > buffer_size - 64) flush();\n        char captured[64];\n\
    \        char* const begin = _capture != nullptr ? captured : _buffer + _position;\n\
    \        char* destination = begin;\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) *destination++ = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(destination, digits, 4);\n            destination +=\
    \ 4;\n        }\n        if (_capture != nullptr) {\n            _capture->append(begin,\
    \ destination - begin);\n        } else {\n            _position += int(destination\
    \ - begin);\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
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
    \    _range_separator = separator;\n    }\n\n    template <class Matrix>\n   \
    \ void write_aligned(const Matrix& matrix) {\n        using Row = internal::range_stored_value_t<const\
    \ Matrix>;\n        using Cell = internal::range_stored_value_t<const Row>;\n\
    \        static_assert(internal::is_range_v<Row> && !internal::is_string_like_v<Row>,\n\
    \                      \"write_aligned requires a two-dimensional range\");\n\
    \        static_assert(!internal::is_range_v<Cell> || internal::is_string_like_v<Cell>,\n\
    \                      \"write_aligned requires scalar cells\");\n        write_aligned_matrix(matrix);\n\
    \    }\n\n    template <class Matrix>\n    void println_aligned(const Matrix&\
    \ matrix) {\n        write_aligned(matrix);\n        write_char('\\n');\n    }\n\
    \n    template <class... Args>\n    void println(const Args&... args) {\n    \
    \    print(args...);\n        write_char('\\n');\n    }\n\n    template <class\
    \ T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n  \
    \      return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 13 \"verify/algo/offline/mo_with_updates.test.cpp\"\n\nnamespace\
    \ {\n\nusing Mo = m1une::algo::MoWithUpdates;\n\nstruct Change {\n    int position;\n\
    \    int before;\n    int after;\n};\n\nstruct Counts {\n    int inside_apply\
    \ = 0;\n    int outside_apply = 0;\n    int inside_undo = 0;\n    int outside_undo\
    \ = 0;\n};\n\nstd::vector<int> frequencies(const Mo& mo, const std::vector<int>&\
    \ initial,\n                             const std::vector<Change>& changes, const\
    \ std::vector<int>& targets,\n                             int alphabet, int block_size\
    \ = 0, Counts* counts = nullptr) {\n    std::vector<int> values = initial;\n \
    \   std::vector<int> frequency(alphabet, 0), result(mo.query_count(), -1);\n \
    \   int time = 0;\n    int length = 0;\n    auto add = [&](int index) {\n    \
    \    ++frequency[values[index]];\n        ++length;\n    };\n    auto remove =\
    \ [&](int index) {\n        assert(frequency[values[index]] > 0);\n        --frequency[values[index]];\n\
    \        --length;\n    };\n    auto replace = [&](int id, int left, int right,\
    \ bool forward) {\n        const Change& change = changes[id];\n        const\
    \ int old_value = forward ? change.before : change.after;\n        const int new_value\
    \ = forward ? change.after : change.before;\n        assert(values[change.position]\
    \ == old_value);\n        (void)old_value;\n        const bool inside = left <=\
    \ change.position && change.position < right;\n        if (inside) remove(change.position);\n\
    \        values[change.position] = new_value;\n        if (inside) add(change.position);\n\
    \        if (counts != nullptr) {\n            if (forward && inside) ++counts->inside_apply;\n\
    \            if (forward && !inside) ++counts->outside_apply;\n            if\
    \ (!forward && inside) ++counts->inside_undo;\n            if (!forward && !inside)\
    \ ++counts->outside_undo;\n        }\n    };\n    mo.run(add, remove,\n      \
    \  [&](int id, int left, int right) {\n            assert(id == time);\n     \
    \       replace(id, left, right, true);\n            ++time;\n        },\n   \
    \     [&](int id, int left, int right) {\n            assert(id == time - 1);\n\
    \            replace(id, left, right, false);\n            --time;\n        },\n\
    \        [&](int id) {\n            const auto& query = mo.queries()[id];\n  \
    \          assert(time == query.time && length == query.right - query.left);\n\
    \            assert(result[id] == -1);\n            (void)query;\n           \
    \ result[id] = frequency[targets[id]];\n        }, block_size);\n    return result;\n\
    }\n\nvoid check_directional(const Mo& mo, const std::vector<int>& initial,\n \
    \                      const std::vector<Change>& changes,\n                 \
    \      const std::vector<std::vector<int>>& states, int block_size) {\n    std::vector<int>\
    \ values = initial;\n    std::string word;\n    int left = 0, right = 0, time\
    \ = 0, answered = 0;\n    auto replace = [&](int id, int l, int r, bool forward)\
    \ {\n        assert(l == left && r == right && int(word.size()) == r - l);\n \
    \       const Change& change = changes[id];\n        assert(values[change.position]\
    \ == (forward ? change.before : change.after));\n        values[change.position]\
    \ = forward ? change.after : change.before;\n        if (l <= change.position\
    \ && change.position < r) {\n            word[change.position - l] = char('a'\
    \ + values[change.position]);\n        }\n    };\n    mo.run(\n        [&](int\
    \ index) {\n            assert(index == left - 1);\n            --left;\n    \
    \        word.insert(word.begin(), char('a' + values[index]));\n        },\n \
    \       [&](int index) {\n            assert(index == right);\n            ++right;\n\
    \            word.push_back(char('a' + values[index]));\n        },\n        [&](int\
    \ index) {\n            assert(index == left && !word.empty());\n            assert(word.front()\
    \ == char('a' + values[index]));\n            ++left;\n            word.erase(word.begin());\n\
    \        },\n        [&](int index) {\n            assert(index == right - 1 &&\
    \ !word.empty());\n            assert(word.back() == char('a' + values[index]));\n\
    \            --right;\n            word.pop_back();\n        },\n        [&](int\
    \ id, int l, int r) {\n            assert(id == time);\n            replace(id,\
    \ l, r, true);\n            ++time;\n        },\n        [&](int id, int l, int\
    \ r) {\n            assert(id == time - 1);\n            replace(id, l, r, false);\n\
    \            --time;\n        },\n        [&](int id) {\n            const auto&\
    \ query = mo.queries()[id];\n            assert(left == query.left && right ==\
    \ query.right && time == query.time);\n            assert(values == states[time]);\n\
    \            std::string expected;\n            for (int i = left; i < right;\
    \ ++i) expected += char('a' + states[time][i]);\n            assert(word == expected);\n\
    \            ++answered;\n            (void)query;\n        }, block_size);\n\
    \    assert(answered == mo.query_count());\n}\n\nvoid test_boundaries() {\n  \
    \  Mo empty;\n    assert(empty.size() == 0 && empty.empty());\n    assert(empty.query_count()\
    \ == 0 && empty.update_count() == 0);\n    assert(empty.order().empty());\n  \
    \  int calls = 0;\n    empty.run([&](int) { ++calls; }, [&](int) { ++calls; },\n\
    \        [&](int, int, int) { ++calls; }, [&](int, int, int) { ++calls; },\n \
    \       [&](int) { ++calls; });\n    assert(calls == 0);\n    int id = empty.add_query(0,\
    \ 0);\n    assert(id == 0);\n    empty.run([&](int) { assert(false); }, [&](int)\
    \ { assert(false); },\n        [&](int, int, int) { assert(false); }, [&](int,\
    \ int, int) { assert(false); },\n        [&](int id) { assert(id == 0); ++calls;\
    \ });\n    assert(calls == 1);\n    empty.clear();\n    assert(empty.empty() &&\
    \ empty.update_count() == 0);\n\n    Mo updates_only(6);\n    updates_only.reserve(10);\n\
    \    id = updates_only.add_update();\n    assert(id == 0);\n    id = updates_only.add_update();\n\
    \    assert(id == 1);\n    assert(updates_only.empty());\n    updates_only.run([](int)\
    \ { assert(false); }, [](int) { assert(false); },\n        [](int, int, int) {\
    \ assert(false); }, [](int, int, int) { assert(false); },\n        [](int) { assert(false);\
    \ });\n    id = updates_only.add_query(0, 1, 2);\n    assert(id == 0);\n    id\
    \ = updates_only.add_query(1, 2, 0);\n    assert(id == 1);\n    id = updates_only.add_query(2,\
    \ 3);\n    assert(id == 2);\n    id = updates_only.add_query(4, 5, 0);\n    assert(id\
    \ == 3);\n    const std::vector<int> initial = {0, 1, 2, 3, 4, 5};\n    std::vector<Change>\
    \ changes;\n    changes.push_back(Change{0, 0, 5});\n    changes.push_back(Change{1,\
    \ 1, 5});\n    Counts counts;\n    const auto result = frequencies(updates_only,\
    \ initial, changes, std::vector<int>(4, 5), 6, 1, &counts);\n    const std::vector<int>\
    \ expected = {1, 0, 0, 0};\n    assert(result == expected);\n    assert(counts.inside_apply\
    \ > 0 && counts.outside_apply > 0);\n    assert(counts.inside_undo > 0 && counts.outside_undo\
    \ > 0);\n    updates_only.clear();\n    assert(updates_only.size() == 6 && updates_only.update_count()\
    \ == 0);\n    id = updates_only.add_update();\n    assert(id == 0);\n    id =\
    \ updates_only.add_query(0, 6);\n    assert(id == 0);\n    assert(updates_only.queries()[0].time\
    \ == 1);\n    (void)id;\n}\n\nvoid test_randomized() {\n    std::uint64_t seed\
    \ = 20261117;\n    auto random = [&]() {\n        seed ^= seed << 7;\n       \
    \ seed ^= seed >> 9;\n        return seed;\n    };\n    for (int trial = 0; trial\
    \ < 250; ++trial) {\n        const int n = int(random() % 26);\n        std::vector<int>\
    \ initial(n);\n        for (int& value : initial) value = int(random() % 6);\n\
    \        std::vector<int> current = initial;\n        std::vector<std::vector<int>>\
    \ states;\n        states.push_back(initial);\n        std::vector<Change> changes;\n\
    \        std::vector<int> targets, expected;\n        Mo mo(n);\n        mo.reserve(100);\n\
    \        auto query = [&](int time, bool explicit_time) {\n            int left\
    \ = int(random() % (n + 1));\n            int right = int(random() % (n + 1));\n\
    \            if (left > right) std::swap(left, right);\n            const int\
    \ value = int(random() % 7);\n            const int id = explicit_time ? mo.add_query(left,\
    \ right, time) : mo.add_query(left, right);\n            assert(id == int(targets.size()));\n\
    \            (void)id;\n            targets.push_back(value);\n            expected.push_back(int(std::count(states[time].begin()\
    \ + left, states[time].begin() + right, value)));\n        };\n        const int\
    \ events = int(random() % 100);\n        for (int event = 0; event < events; ++event)\
    \ {\n            if (n > 0 && random() % 2 == 0) {\n                const int\
    \ position = int(random() % n);\n                const int value = int(random()\
    \ % 6);\n                const int id = mo.add_update();\n                assert(id\
    \ == int(changes.size()));\n                (void)id;\n                changes.push_back(Change{position,\
    \ current[position], value});\n                current[position] = value;\n  \
    \              states.push_back(current);\n            } else {\n            \
    \    query(mo.update_count(), false);\n            }\n        }\n        for (int\
    \ i = 0; i < 8; ++i) query(int(random() % states.size()), true);\n\n        for\
    \ (int block_size : std::vector<int>{0, 1, 3, n + 1, -1}) {\n            const\
    \ auto order = mo.order(block_size);\n            assert(order == mo.order(block_size));\n\
    \            auto sorted = order;\n            std::sort(sorted.begin(), sorted.end());\n\
    \            std::vector<int> ids(mo.query_count());\n            std::iota(ids.begin(),\
    \ ids.end(), 0);\n            assert(sorted == ids);\n            const auto actual\
    \ = frequencies(mo, initial, changes, targets, 7, block_size);\n            assert(actual\
    \ == expected);\n        }\n        check_directional(mo, initial, changes, states,\
    \ 2);\n        // A second run starts from a fresh array and aggregate; the schedule\
    \ is unchanged.\n        const auto repeated = frequencies(mo, initial, changes,\
    \ targets, 7);\n        assert(repeated == expected);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_boundaries();\n    test_randomized();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    if (!input.read(n,\
    \ q)) return 0;\n    std::vector<int> initial(n);\n    for (int& value : initial)\
    \ input >> value;\n    std::vector<int> current = initial;\n    std::vector<int>\
    \ alphabet = initial;\n    std::vector<Change> changes;\n    std::vector<int>\
    \ targets;\n    Mo mo(n);\n    mo.reserve(q);\n    for (int event = 0; event <\
    \ q; ++event) {\n        int type;\n        input >> type;\n        if (type ==\
    \ 0) {\n            int position, value;\n            input >> position >> value;\n\
    \            mo.add_update();\n            changes.push_back(Change{position,\
    \ current[position], value});\n            current[position] = value;\n      \
    \      alphabet.push_back(value);\n        } else {\n            int left, right,\
    \ value;\n            input >> left >> right >> value;\n            mo.add_query(left,\
    \ right);\n            targets.push_back(value);\n            alphabet.push_back(value);\n\
    \        }\n    }\n    std::sort(alphabet.begin(), alphabet.end());\n    alphabet.erase(std::unique(alphabet.begin(),\
    \ alphabet.end()), alphabet.end());\n    auto compress = [&](int value) {\n  \
    \      return int(std::lower_bound(alphabet.begin(), alphabet.end(), value) -\
    \ alphabet.begin());\n    };\n    for (int& value : initial) value = compress(value);\n\
    \    for (auto& change : changes) {\n        change.before = compress(change.before);\n\
    \        change.after = compress(change.after);\n    }\n    for (int& value :\
    \ targets) value = compress(value);\n    for (int result : frequencies(mo, initial,\
    \ changes, targets, int(alphabet.size()))) {\n        output << result << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_frequency\"\
    \n\n#include \"../../../algo/offline/mo_with_updates.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <numeric>\n#include <string>\n\
    #include <vector>\n\n#include \"../../../utilities/fast_io.hpp\"\n\nnamespace\
    \ {\n\nusing Mo = m1une::algo::MoWithUpdates;\n\nstruct Change {\n    int position;\n\
    \    int before;\n    int after;\n};\n\nstruct Counts {\n    int inside_apply\
    \ = 0;\n    int outside_apply = 0;\n    int inside_undo = 0;\n    int outside_undo\
    \ = 0;\n};\n\nstd::vector<int> frequencies(const Mo& mo, const std::vector<int>&\
    \ initial,\n                             const std::vector<Change>& changes, const\
    \ std::vector<int>& targets,\n                             int alphabet, int block_size\
    \ = 0, Counts* counts = nullptr) {\n    std::vector<int> values = initial;\n \
    \   std::vector<int> frequency(alphabet, 0), result(mo.query_count(), -1);\n \
    \   int time = 0;\n    int length = 0;\n    auto add = [&](int index) {\n    \
    \    ++frequency[values[index]];\n        ++length;\n    };\n    auto remove =\
    \ [&](int index) {\n        assert(frequency[values[index]] > 0);\n        --frequency[values[index]];\n\
    \        --length;\n    };\n    auto replace = [&](int id, int left, int right,\
    \ bool forward) {\n        const Change& change = changes[id];\n        const\
    \ int old_value = forward ? change.before : change.after;\n        const int new_value\
    \ = forward ? change.after : change.before;\n        assert(values[change.position]\
    \ == old_value);\n        (void)old_value;\n        const bool inside = left <=\
    \ change.position && change.position < right;\n        if (inside) remove(change.position);\n\
    \        values[change.position] = new_value;\n        if (inside) add(change.position);\n\
    \        if (counts != nullptr) {\n            if (forward && inside) ++counts->inside_apply;\n\
    \            if (forward && !inside) ++counts->outside_apply;\n            if\
    \ (!forward && inside) ++counts->inside_undo;\n            if (!forward && !inside)\
    \ ++counts->outside_undo;\n        }\n    };\n    mo.run(add, remove,\n      \
    \  [&](int id, int left, int right) {\n            assert(id == time);\n     \
    \       replace(id, left, right, true);\n            ++time;\n        },\n   \
    \     [&](int id, int left, int right) {\n            assert(id == time - 1);\n\
    \            replace(id, left, right, false);\n            --time;\n        },\n\
    \        [&](int id) {\n            const auto& query = mo.queries()[id];\n  \
    \          assert(time == query.time && length == query.right - query.left);\n\
    \            assert(result[id] == -1);\n            (void)query;\n           \
    \ result[id] = frequency[targets[id]];\n        }, block_size);\n    return result;\n\
    }\n\nvoid check_directional(const Mo& mo, const std::vector<int>& initial,\n \
    \                      const std::vector<Change>& changes,\n                 \
    \      const std::vector<std::vector<int>>& states, int block_size) {\n    std::vector<int>\
    \ values = initial;\n    std::string word;\n    int left = 0, right = 0, time\
    \ = 0, answered = 0;\n    auto replace = [&](int id, int l, int r, bool forward)\
    \ {\n        assert(l == left && r == right && int(word.size()) == r - l);\n \
    \       const Change& change = changes[id];\n        assert(values[change.position]\
    \ == (forward ? change.before : change.after));\n        values[change.position]\
    \ = forward ? change.after : change.before;\n        if (l <= change.position\
    \ && change.position < r) {\n            word[change.position - l] = char('a'\
    \ + values[change.position]);\n        }\n    };\n    mo.run(\n        [&](int\
    \ index) {\n            assert(index == left - 1);\n            --left;\n    \
    \        word.insert(word.begin(), char('a' + values[index]));\n        },\n \
    \       [&](int index) {\n            assert(index == right);\n            ++right;\n\
    \            word.push_back(char('a' + values[index]));\n        },\n        [&](int\
    \ index) {\n            assert(index == left && !word.empty());\n            assert(word.front()\
    \ == char('a' + values[index]));\n            ++left;\n            word.erase(word.begin());\n\
    \        },\n        [&](int index) {\n            assert(index == right - 1 &&\
    \ !word.empty());\n            assert(word.back() == char('a' + values[index]));\n\
    \            --right;\n            word.pop_back();\n        },\n        [&](int\
    \ id, int l, int r) {\n            assert(id == time);\n            replace(id,\
    \ l, r, true);\n            ++time;\n        },\n        [&](int id, int l, int\
    \ r) {\n            assert(id == time - 1);\n            replace(id, l, r, false);\n\
    \            --time;\n        },\n        [&](int id) {\n            const auto&\
    \ query = mo.queries()[id];\n            assert(left == query.left && right ==\
    \ query.right && time == query.time);\n            assert(values == states[time]);\n\
    \            std::string expected;\n            for (int i = left; i < right;\
    \ ++i) expected += char('a' + states[time][i]);\n            assert(word == expected);\n\
    \            ++answered;\n            (void)query;\n        }, block_size);\n\
    \    assert(answered == mo.query_count());\n}\n\nvoid test_boundaries() {\n  \
    \  Mo empty;\n    assert(empty.size() == 0 && empty.empty());\n    assert(empty.query_count()\
    \ == 0 && empty.update_count() == 0);\n    assert(empty.order().empty());\n  \
    \  int calls = 0;\n    empty.run([&](int) { ++calls; }, [&](int) { ++calls; },\n\
    \        [&](int, int, int) { ++calls; }, [&](int, int, int) { ++calls; },\n \
    \       [&](int) { ++calls; });\n    assert(calls == 0);\n    int id = empty.add_query(0,\
    \ 0);\n    assert(id == 0);\n    empty.run([&](int) { assert(false); }, [&](int)\
    \ { assert(false); },\n        [&](int, int, int) { assert(false); }, [&](int,\
    \ int, int) { assert(false); },\n        [&](int id) { assert(id == 0); ++calls;\
    \ });\n    assert(calls == 1);\n    empty.clear();\n    assert(empty.empty() &&\
    \ empty.update_count() == 0);\n\n    Mo updates_only(6);\n    updates_only.reserve(10);\n\
    \    id = updates_only.add_update();\n    assert(id == 0);\n    id = updates_only.add_update();\n\
    \    assert(id == 1);\n    assert(updates_only.empty());\n    updates_only.run([](int)\
    \ { assert(false); }, [](int) { assert(false); },\n        [](int, int, int) {\
    \ assert(false); }, [](int, int, int) { assert(false); },\n        [](int) { assert(false);\
    \ });\n    id = updates_only.add_query(0, 1, 2);\n    assert(id == 0);\n    id\
    \ = updates_only.add_query(1, 2, 0);\n    assert(id == 1);\n    id = updates_only.add_query(2,\
    \ 3);\n    assert(id == 2);\n    id = updates_only.add_query(4, 5, 0);\n    assert(id\
    \ == 3);\n    const std::vector<int> initial = {0, 1, 2, 3, 4, 5};\n    std::vector<Change>\
    \ changes;\n    changes.push_back(Change{0, 0, 5});\n    changes.push_back(Change{1,\
    \ 1, 5});\n    Counts counts;\n    const auto result = frequencies(updates_only,\
    \ initial, changes, std::vector<int>(4, 5), 6, 1, &counts);\n    const std::vector<int>\
    \ expected = {1, 0, 0, 0};\n    assert(result == expected);\n    assert(counts.inside_apply\
    \ > 0 && counts.outside_apply > 0);\n    assert(counts.inside_undo > 0 && counts.outside_undo\
    \ > 0);\n    updates_only.clear();\n    assert(updates_only.size() == 6 && updates_only.update_count()\
    \ == 0);\n    id = updates_only.add_update();\n    assert(id == 0);\n    id =\
    \ updates_only.add_query(0, 6);\n    assert(id == 0);\n    assert(updates_only.queries()[0].time\
    \ == 1);\n    (void)id;\n}\n\nvoid test_randomized() {\n    std::uint64_t seed\
    \ = 20261117;\n    auto random = [&]() {\n        seed ^= seed << 7;\n       \
    \ seed ^= seed >> 9;\n        return seed;\n    };\n    for (int trial = 0; trial\
    \ < 250; ++trial) {\n        const int n = int(random() % 26);\n        std::vector<int>\
    \ initial(n);\n        for (int& value : initial) value = int(random() % 6);\n\
    \        std::vector<int> current = initial;\n        std::vector<std::vector<int>>\
    \ states;\n        states.push_back(initial);\n        std::vector<Change> changes;\n\
    \        std::vector<int> targets, expected;\n        Mo mo(n);\n        mo.reserve(100);\n\
    \        auto query = [&](int time, bool explicit_time) {\n            int left\
    \ = int(random() % (n + 1));\n            int right = int(random() % (n + 1));\n\
    \            if (left > right) std::swap(left, right);\n            const int\
    \ value = int(random() % 7);\n            const int id = explicit_time ? mo.add_query(left,\
    \ right, time) : mo.add_query(left, right);\n            assert(id == int(targets.size()));\n\
    \            (void)id;\n            targets.push_back(value);\n            expected.push_back(int(std::count(states[time].begin()\
    \ + left, states[time].begin() + right, value)));\n        };\n        const int\
    \ events = int(random() % 100);\n        for (int event = 0; event < events; ++event)\
    \ {\n            if (n > 0 && random() % 2 == 0) {\n                const int\
    \ position = int(random() % n);\n                const int value = int(random()\
    \ % 6);\n                const int id = mo.add_update();\n                assert(id\
    \ == int(changes.size()));\n                (void)id;\n                changes.push_back(Change{position,\
    \ current[position], value});\n                current[position] = value;\n  \
    \              states.push_back(current);\n            } else {\n            \
    \    query(mo.update_count(), false);\n            }\n        }\n        for (int\
    \ i = 0; i < 8; ++i) query(int(random() % states.size()), true);\n\n        for\
    \ (int block_size : std::vector<int>{0, 1, 3, n + 1, -1}) {\n            const\
    \ auto order = mo.order(block_size);\n            assert(order == mo.order(block_size));\n\
    \            auto sorted = order;\n            std::sort(sorted.begin(), sorted.end());\n\
    \            std::vector<int> ids(mo.query_count());\n            std::iota(ids.begin(),\
    \ ids.end(), 0);\n            assert(sorted == ids);\n            const auto actual\
    \ = frequencies(mo, initial, changes, targets, 7, block_size);\n            assert(actual\
    \ == expected);\n        }\n        check_directional(mo, initial, changes, states,\
    \ 2);\n        // A second run starts from a fresh array and aggregate; the schedule\
    \ is unchanged.\n        const auto repeated = frequencies(mo, initial, changes,\
    \ targets, 7);\n        assert(repeated == expected);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_boundaries();\n    test_randomized();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    if (!input.read(n,\
    \ q)) return 0;\n    std::vector<int> initial(n);\n    for (int& value : initial)\
    \ input >> value;\n    std::vector<int> current = initial;\n    std::vector<int>\
    \ alphabet = initial;\n    std::vector<Change> changes;\n    std::vector<int>\
    \ targets;\n    Mo mo(n);\n    mo.reserve(q);\n    for (int event = 0; event <\
    \ q; ++event) {\n        int type;\n        input >> type;\n        if (type ==\
    \ 0) {\n            int position, value;\n            input >> position >> value;\n\
    \            mo.add_update();\n            changes.push_back(Change{position,\
    \ current[position], value});\n            current[position] = value;\n      \
    \      alphabet.push_back(value);\n        } else {\n            int left, right,\
    \ value;\n            input >> left >> right >> value;\n            mo.add_query(left,\
    \ right);\n            targets.push_back(value);\n            alphabet.push_back(value);\n\
    \        }\n    }\n    std::sort(alphabet.begin(), alphabet.end());\n    alphabet.erase(std::unique(alphabet.begin(),\
    \ alphabet.end()), alphabet.end());\n    auto compress = [&](int value) {\n  \
    \      return int(std::lower_bound(alphabet.begin(), alphabet.end(), value) -\
    \ alphabet.begin());\n    };\n    for (int& value : initial) value = compress(value);\n\
    \    for (auto& change : changes) {\n        change.before = compress(change.before);\n\
    \        change.after = compress(change.after);\n    }\n    for (int& value :\
    \ targets) value = compress(value);\n    for (int result : frequencies(mo, initial,\
    \ changes, targets, int(alphabet.size()))) {\n        output << result << '\\\
    n';\n    }\n}\n"
  dependsOn:
  - algo/offline/mo_with_updates.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/algo/offline/mo_with_updates.test.cpp
  requiredBy: []
  timestamp: '2026-11-17 04:04:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/offline/mo_with_updates.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/offline/mo_with_updates.test.cpp
- /verify/verify/algo/offline/mo_with_updates.test.cpp.html
title: verify/algo/offline/mo_with_updates.test.cpp
---
