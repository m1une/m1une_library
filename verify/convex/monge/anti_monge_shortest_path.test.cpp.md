---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/anti_monge_shortest_path.hpp
    title: Anti-Monge DAG Shortest Paths
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
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
  bundledCode: "#line 1 \"verify/convex/monge/anti_monge_shortest_path.test.cpp\"\n\
    // No matching forward anti-Monge shortest-path judge target was found.\n// The\
    \ aplusb fallback runs the focused checks below before handling input.\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <climits>\n#include <random>\n#include\
    \ <vector>\n\n#line 1 \"convex/monge/anti_monge_shortest_path.hpp\"\n\n\n\n#line\
    \ 7 \"convex/monge/anti_monge_shortest_path.hpp\"\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#line 5 \"convex/monge/smawk.hpp\"\n#include <functional>\n#include <numeric>\n\
    #line 8 \"convex/monge/smawk.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\n\
    namespace smawk_detail {\n\ntemplate <class Select>\nvoid solve(const std::vector<int>&\
    \ rows, const std::vector<int>& columns,\n           const Select& select, std::vector<int>&\
    \ answer) {\n    if (rows.empty()) return;\n\n    std::vector<int> reduced;\n\
    \    reduced.reserve(columns.size());\n    for (int column : columns) {\n    \
    \    while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
    \ - 1];\n            if (!select(row, reduced.back(), column)) break;\n      \
    \      reduced.pop_back();\n        }\n        if (reduced.size() < rows.size())\
    \ reduced.push_back(column);\n    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size()\
    \ / 2);\n    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, select, answer);\n\n    int left = 0;\n    int right\
    \ = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n        if (i + 1\
    \ < int(rows.size())) {\n            while (reduced[right] != answer[rows[i +\
    \ 1]]) right++;\n        } else {\n            right = int(reduced.size()) - 1;\n\
    \        }\n\n        int best = left;\n        for (int j = left + 1; j <= right;\
    \ j++) {\n            if (select(rows[i], reduced[best], reduced[j])) {\n    \
    \            best = j;\n            }\n        }\n        answer[rows[i]] = reduced[best];\n\
    \        left = right;\n    }\n}\n\ntemplate <class Select>\nstd::vector<int>\
    \ row_optima(int row_count, int column_count, const Select& select) {\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n\n    std::vector<int> rows(row_count), columns(column_count);\n  \
    \  std::iota(rows.begin(), rows.end(), 0);\n    std::iota(columns.begin(), columns.end(),\
    \ 0);\n    solve(rows, columns, select, answer);\n    return answer;\n}\n\n} \
    \ // namespace smawk_detail\n\n// Search a fixed H x W rectangle, returning column\
    \ indices (leftmost on ties).\n// Requires total monotonicity under Compare; Monge\
    \ suffices for minima.\n// For anti-Monge minima, reverse columns in value and\
    \ map indices back.\n// O(H + W) evaluations; callbacks may be queried out of\
    \ row order.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ smawk_row_optima(int row_count, int column_count, Value value,\n           \
    \                       Compare compare = Compare()) {\n    assert(row_count >=\
    \ 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
    \        row_count, column_count,\n        [&](int row, int current, int candidate)\
    \ {\n            return compare(value(row, candidate), value(row, current));\n\
    \        });\n}\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmin(int\
    \ row_count, int column_count, Value value) {\n    return smawk_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ smawk_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ smawk_row_optima(row_count, column_count, value, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/anti_monge_shortest_path.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct AntiMongeShortestPathResult\
    \ {\n    std::vector<T> distance;\n    std::vector<int> parent;\n};\n\n// dist[j]\
    \ = min(dist[i] + cost(i, j)), where j - i >= minimum_step.\n// cost must be finite\
    \ and anti-Monge on valid rectangles; see the docs.\n// O(N log N + N * minimum_step)\
    \ time for O(1) cost evaluations.\n// In particular, minimum_step = 1 or 2 gives\
    \ O(N log N) time.\ntemplate <class T, class Cost>\nAntiMongeShortestPathResult<T>\
    \ anti_monge_shortest_path(\n    int vertex_count, Cost cost, T infinity, int\
    \ minimum_step = 1) {\n    assert(vertex_count >= 0);\n    assert(minimum_step\
    \ >= 1);\n    assert(T() < infinity);\n\n    AntiMongeShortestPathResult<T> result;\n\
    \    result.distance.assign(vertex_count, infinity);\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count == 0) return result;\n    result.distance[0] = T();\n\
    \    if (minimum_step >= vertex_count) return result;\n\n    auto relax = [&](int\
    \ from, int to) {\n        if (result.distance[from] == infinity) return;\n  \
    \      T candidate = result.distance[from] + cost(from, to);\n        if (candidate\
    \ < result.distance[to] ||\n            (candidate == result.distance[to] && from\
    \ > result.parent[to])) {\n            result.distance[to] = candidate;\n    \
    \        result.parent[to] = from;\n        }\n    };\n\n    // All pairs in this\
    \ rectangle are valid. Remove unreachable columns,\n    // then reverse the remaining\
    \ columns to turn anti-Monge into Monge.\n    auto rectangle = [&](int first,\
    \ int last, int top, int bottom) {\n        if (first == last || top == bottom)\
    \ return;\n        std::vector<int> sources;\n        for (int from = last; from\
    \ > first;) {\n            --from;\n            if (result.distance[from] != infinity)\
    \ sources.push_back(from);\n        }\n        if (sources.empty()) return;\n\
    \        if (sources.size() == 1) {\n            for (int to = top; to < bottom;\
    \ to++) relax(sources[0], to);\n            return;\n        }\n        auto argmin\
    \ = smawk_row_argmin(\n            bottom - top, int(sources.size()), [&](int\
    \ row, int column) -> T {\n                int from = sources[column];\n     \
    \           return result.distance[from] + cost(from, top + row);\n          \
    \  });\n        for (int row = 0; row < bottom - top; row++) {\n            relax(sources[argmin[row]],\
    \ top + row);\n        }\n    };\n\n    auto solve = [&](auto& self, int left,\
    \ int right) -> void {\n        // Such a block contains no valid internal edge.\n\
    \        if (right - left <= minimum_step) return;\n        int middle = left\
    \ + (right - left) / 2;\n        self(self, left, middle);\n\n        // Two valid\
    \ rectangles and a small corner partition the cross edges.\n        int source_end\
    \ = std::max(left, middle - (minimum_step - 1));\n        int target_begin = middle\
    \ + std::min(right - middle, minimum_step - 1);\n        rectangle(left, middle,\
    \ target_begin, right);\n        rectangle(left, source_end, middle, target_begin);\n\
    \        for (int from = source_end; from < middle; from++) {\n            //\
    \ Subtraction avoids overflow when minimum_step is large.\n            if (minimum_step\
    \ >= target_begin - from) continue;\n            for (int to = std::max(middle,\
    \ from + minimum_step);\n                 to < target_begin; to++) {\n       \
    \         relax(from, to);\n            }\n        }\n\n        // Incoming transitions\
    \ must be applied BEFORE solving the right half.\n        self(self, middle, right);\n\
    \    };\n    solve(solve, 0, vertex_count);\n    return result;\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n\
    #line 5 \"utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n#include\
    \ <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include\
    \ <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n#include\
    \ <sys/stat.h>\n#include <type_traits>\n#include <utility>\n#include <unistd.h>\n\
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
    \ m1une\n\n\n#line 14 \"verify/convex/monge/anti_monge_shortest_path.test.cpp\"\
    \n\nconstexpr long long infinity = 1LL << 60;\n\ntemplate <class Cost>\nvoid check(int\
    \ n, int step, Cost cost) {\n    std::vector<long long> distance(n, infinity);\n\
    \    std::vector<int> parent(n, -1);\n    if (n > 0) distance[0] = 0;\n    for\
    \ (int to = 1; to < n; ++to) {\n        for (int from = 0; from <= to - step;\
    \ ++from) {\n            if (distance[from] == infinity) continue;\n         \
    \   long long candidate = distance[from] + cost(from, to);\n            if (candidate\
    \ <= distance[to]) {\n                distance[to] = candidate;\n            \
    \    parent[to] = from;\n            }\n        }\n    }\n    auto result = m1une::convex::anti_monge_shortest_path(\n\
    \        n,\n        [&](int from, int to) {\n            assert(0 <= from &&\
    \ from < to && to < n);\n            assert(to - from >= step);\n            assert(distance[from]\
    \ != infinity);\n            return cost(from, to);\n        },\n        infinity,\
    \ step);\n    assert(result.distance == distance);\n    assert(result.parent ==\
    \ parent);\n}\n\nvoid test_random_anti_monge() {\n    std::mt19937 random(0xC0FFEE);\n\
    \    for (int n = 0; n <= 65; ++n) {\n        for (int trial = 0; trial < 8; ++trial)\
    \ {\n            std::vector<std::vector<long long>> matrix(\n               \
    \ n, std::vector<long long>(n));\n            for (int i = 0; i < n; ++i) {\n\
    \                matrix[i][0] = int(random() % 101) - 50;\n                matrix[0][i]\
    \ = int(random() % 101) - 50;\n            }\n            // Nonnegative mixed\
    \ second differences generate anti-Monge.\n            for (int i = 1; i < n;\
    \ ++i) {\n                for (int j = 1; j < n; ++j) {\n                    matrix[i][j]\
    \ = matrix[i - 1][j] + matrix[i][j - 1] -\n                                  \
    \ matrix[i - 1][j - 1] + random() % 5;\n                }\n            }\n   \
    \         auto cost = [&](int from, int to) { return matrix[from][to]; };\n  \
    \          for (int step = 1; step <= n + 1; ++step) check(n, step, cost);\n \
    \       }\n    }\n}\n\nvoid test_concave_gap_costs() {\n    std::mt19937 random(0x5EED);\n\
    \    for (int n = 0; n <= 80; ++n) {\n        for (int trial = 0; trial < 8; ++trial)\
    \ {\n            std::vector<long long> position(n), source_fee(n), target_fee(n);\n\
    \            for (int i = 0; i < n; ++i) {\n                if (i > 0) position[i]\
    \ = position[i - 1] + random() % 4;\n                source_fee[i] = int(random()\
    \ % 101) - 50;\n                target_fee[i] = int(random() % 101) - 50;\n  \
    \          }\n            auto quadratic = [&](int from, int to) {\n         \
    \       long long gap = position[to] - position[from];\n                return\
    \ source_fee[from] + target_fee[to] - gap * gap;\n            };\n           \
    \ auto piecewise_linear = [&](int from, int to) {\n                long long gap\
    \ = position[to] - position[from];\n                return source_fee[from] +\
    \ target_fee[to] +\n                       std::min(2 * gap, gap + 5);\n     \
    \       };\n            for (int step : std::vector<int>{1, 2, 3, n / 2 + 1, n\
    \ + 1}) {\n                check(n, step, quadratic);\n                check(n,\
    \ step, piecewise_linear);\n            }\n        }\n    }\n}\n\nvoid test_exhaustive_concave_sequences()\
    \ {\n    // Enumerate concave gap costs by their nonincreasing first differences.\n\
    \    // Arbitrary row/column fees retain anti-Monge and vary optimal parents.\n\
    \    for (int n = 1, count = 1; n <= 8; ++n, count *= 3) {\n        for (int mask\
    \ = 0; mask < count; ++mask) {\n            std::vector<long long> gap_cost(n);\n\
    \            int code = mask;\n            long long difference = 3;\n       \
    \     for (int gap = 1; gap < n; ++gap) {\n                difference -= code\
    \ % 3;\n                code /= 3;\n                gap_cost[gap] = gap_cost[gap\
    \ - 1] + difference;\n            }\n            auto cost = [&](int from, int\
    \ to) {\n                return gap_cost[to - from] + (from * 7) % 5 - 2 +\n \
    \                      (to * 11) % 7 - 3;\n            };\n            for (int\
    \ step = 1; step <= n + 1; ++step) check(n, step, cost);\n        }\n    }\n}\n\
    \nvoid test_large_and_boundaries() {\n    auto zero = [](int, int) { return 0LL;\
    \ };\n    check(0, INT_MAX, zero);\n    check(12, INT_MAX, zero);\n    check(12,\
    \ 1, zero);\n    // Negative constant costs force many edges and exercise DP ordering.\n\
    \    check(100, 1, [](int, int) { return -7LL; });\n    check(100, 2, [](int,\
    \ int) { return -1'000'000'000'000LL; });\n    check(100, 5, [](int, int) { return\
    \ 1'000'000'000'000LL; });\n    auto integers = m1une::convex::anti_monge_shortest_path(\n\
    \        12, [](int, int) { return -1; }, 1'000'000, 2);\n    assert(integers.distance.back()\
    \ == -5);\n    auto defaults = m1une::convex::anti_monge_shortest_path(12, zero,\
    \ infinity);\n    assert(defaults.distance == std::vector<long long>(12, 0));\n\
    \    for (int i = 1; i < 12; ++i) assert(defaults.parent[i] == i - 1);\n\n   \
    \ const int n = (1 << 17) + 3;\n    for (int step : std::vector<int>{1, 2, 3,\
    \ 17}) {\n        long long evaluations = 0;\n        auto result = m1une::convex::anti_monge_shortest_path(\n\
    \            n,\n            [&](int, int) {\n                ++evaluations;\n\
    \                return 0LL;\n            },\n            infinity, step);\n \
    \       for (int j = 1; j < n; ++j) {\n            if (j < step) {\n         \
    \       assert(result.distance[j] == infinity);\n                assert(result.parent[j]\
    \ == -1);\n            } else {\n                assert(result.distance[j] ==\
    \ 0);\n                int expected = j >= 2 * step ? j - step : 0;\n        \
    \        assert(result.parent[j] == expected);\n            }\n        }\n   \
    \     // Reject quadratic rectangle scans for fixed small minimum steps.\n   \
    \     assert(evaluations < 24LL * n * std::bit_width(unsigned(n)));\n    }\n}\n\
    \nint main() {\n    test_random_anti_monge();\n    test_concave_gap_costs();\n\
    \    test_exhaustive_concave_sequences();\n    test_large_and_boundaries();\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    long long a, b;\n    input >> a >> b;\n    output << a + b << '\\n';\n}\n"
  code: "// No matching forward anti-Monge shortest-path judge target was found.\n\
    // The aplusb fallback runs the focused checks below before handling input.\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <climits>\n#include <random>\n#include\
    \ <vector>\n\n#include \"../../../convex/monge/anti_monge_shortest_path.hpp\"\n\
    #include \"../../../utilities/fast_io.hpp\"\n\nconstexpr long long infinity =\
    \ 1LL << 60;\n\ntemplate <class Cost>\nvoid check(int n, int step, Cost cost)\
    \ {\n    std::vector<long long> distance(n, infinity);\n    std::vector<int> parent(n,\
    \ -1);\n    if (n > 0) distance[0] = 0;\n    for (int to = 1; to < n; ++to) {\n\
    \        for (int from = 0; from <= to - step; ++from) {\n            if (distance[from]\
    \ == infinity) continue;\n            long long candidate = distance[from] + cost(from,\
    \ to);\n            if (candidate <= distance[to]) {\n                distance[to]\
    \ = candidate;\n                parent[to] = from;\n            }\n        }\n\
    \    }\n    auto result = m1une::convex::anti_monge_shortest_path(\n        n,\n\
    \        [&](int from, int to) {\n            assert(0 <= from && from < to &&\
    \ to < n);\n            assert(to - from >= step);\n            assert(distance[from]\
    \ != infinity);\n            return cost(from, to);\n        },\n        infinity,\
    \ step);\n    assert(result.distance == distance);\n    assert(result.parent ==\
    \ parent);\n}\n\nvoid test_random_anti_monge() {\n    std::mt19937 random(0xC0FFEE);\n\
    \    for (int n = 0; n <= 65; ++n) {\n        for (int trial = 0; trial < 8; ++trial)\
    \ {\n            std::vector<std::vector<long long>> matrix(\n               \
    \ n, std::vector<long long>(n));\n            for (int i = 0; i < n; ++i) {\n\
    \                matrix[i][0] = int(random() % 101) - 50;\n                matrix[0][i]\
    \ = int(random() % 101) - 50;\n            }\n            // Nonnegative mixed\
    \ second differences generate anti-Monge.\n            for (int i = 1; i < n;\
    \ ++i) {\n                for (int j = 1; j < n; ++j) {\n                    matrix[i][j]\
    \ = matrix[i - 1][j] + matrix[i][j - 1] -\n                                  \
    \ matrix[i - 1][j - 1] + random() % 5;\n                }\n            }\n   \
    \         auto cost = [&](int from, int to) { return matrix[from][to]; };\n  \
    \          for (int step = 1; step <= n + 1; ++step) check(n, step, cost);\n \
    \       }\n    }\n}\n\nvoid test_concave_gap_costs() {\n    std::mt19937 random(0x5EED);\n\
    \    for (int n = 0; n <= 80; ++n) {\n        for (int trial = 0; trial < 8; ++trial)\
    \ {\n            std::vector<long long> position(n), source_fee(n), target_fee(n);\n\
    \            for (int i = 0; i < n; ++i) {\n                if (i > 0) position[i]\
    \ = position[i - 1] + random() % 4;\n                source_fee[i] = int(random()\
    \ % 101) - 50;\n                target_fee[i] = int(random() % 101) - 50;\n  \
    \          }\n            auto quadratic = [&](int from, int to) {\n         \
    \       long long gap = position[to] - position[from];\n                return\
    \ source_fee[from] + target_fee[to] - gap * gap;\n            };\n           \
    \ auto piecewise_linear = [&](int from, int to) {\n                long long gap\
    \ = position[to] - position[from];\n                return source_fee[from] +\
    \ target_fee[to] +\n                       std::min(2 * gap, gap + 5);\n     \
    \       };\n            for (int step : std::vector<int>{1, 2, 3, n / 2 + 1, n\
    \ + 1}) {\n                check(n, step, quadratic);\n                check(n,\
    \ step, piecewise_linear);\n            }\n        }\n    }\n}\n\nvoid test_exhaustive_concave_sequences()\
    \ {\n    // Enumerate concave gap costs by their nonincreasing first differences.\n\
    \    // Arbitrary row/column fees retain anti-Monge and vary optimal parents.\n\
    \    for (int n = 1, count = 1; n <= 8; ++n, count *= 3) {\n        for (int mask\
    \ = 0; mask < count; ++mask) {\n            std::vector<long long> gap_cost(n);\n\
    \            int code = mask;\n            long long difference = 3;\n       \
    \     for (int gap = 1; gap < n; ++gap) {\n                difference -= code\
    \ % 3;\n                code /= 3;\n                gap_cost[gap] = gap_cost[gap\
    \ - 1] + difference;\n            }\n            auto cost = [&](int from, int\
    \ to) {\n                return gap_cost[to - from] + (from * 7) % 5 - 2 +\n \
    \                      (to * 11) % 7 - 3;\n            };\n            for (int\
    \ step = 1; step <= n + 1; ++step) check(n, step, cost);\n        }\n    }\n}\n\
    \nvoid test_large_and_boundaries() {\n    auto zero = [](int, int) { return 0LL;\
    \ };\n    check(0, INT_MAX, zero);\n    check(12, INT_MAX, zero);\n    check(12,\
    \ 1, zero);\n    // Negative constant costs force many edges and exercise DP ordering.\n\
    \    check(100, 1, [](int, int) { return -7LL; });\n    check(100, 2, [](int,\
    \ int) { return -1'000'000'000'000LL; });\n    check(100, 5, [](int, int) { return\
    \ 1'000'000'000'000LL; });\n    auto integers = m1une::convex::anti_monge_shortest_path(\n\
    \        12, [](int, int) { return -1; }, 1'000'000, 2);\n    assert(integers.distance.back()\
    \ == -5);\n    auto defaults = m1une::convex::anti_monge_shortest_path(12, zero,\
    \ infinity);\n    assert(defaults.distance == std::vector<long long>(12, 0));\n\
    \    for (int i = 1; i < 12; ++i) assert(defaults.parent[i] == i - 1);\n\n   \
    \ const int n = (1 << 17) + 3;\n    for (int step : std::vector<int>{1, 2, 3,\
    \ 17}) {\n        long long evaluations = 0;\n        auto result = m1une::convex::anti_monge_shortest_path(\n\
    \            n,\n            [&](int, int) {\n                ++evaluations;\n\
    \                return 0LL;\n            },\n            infinity, step);\n \
    \       for (int j = 1; j < n; ++j) {\n            if (j < step) {\n         \
    \       assert(result.distance[j] == infinity);\n                assert(result.parent[j]\
    \ == -1);\n            } else {\n                assert(result.distance[j] ==\
    \ 0);\n                int expected = j >= 2 * step ? j - step : 0;\n        \
    \        assert(result.parent[j] == expected);\n            }\n        }\n   \
    \     // Reject quadratic rectangle scans for fixed small minimum steps.\n   \
    \     assert(evaluations < 24LL * n * std::bit_width(unsigned(n)));\n    }\n}\n\
    \nint main() {\n    test_random_anti_monge();\n    test_concave_gap_costs();\n\
    \    test_exhaustive_concave_sequences();\n    test_large_and_boundaries();\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    long long a, b;\n    input >> a >> b;\n    output << a + b << '\\n';\n}\n"
  dependsOn:
  - convex/monge/anti_monge_shortest_path.hpp
  - convex/monge/smawk.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/convex/monge/anti_monge_shortest_path.test.cpp
  requiredBy: []
  timestamp: '2026-10-24 20:27:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/convex/monge/anti_monge_shortest_path.test.cpp
layout: document
redirect_from:
- /verify/verify/convex/monge/anti_monge_shortest_path.test.cpp
- /verify/verify/convex/monge/anti_monge_shortest_path.test.cpp.html
title: verify/convex/monge/anti_monge_shortest_path.test.cpp
---
