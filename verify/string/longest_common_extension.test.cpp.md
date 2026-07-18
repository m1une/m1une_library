---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_extension.hpp
    title: Longest Common Extension
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
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
    PROBLEM: https://judge.yosupo.jp/problem/longest_common_substring
    links:
    - https://judge.yosupo.jp/problem/longest_common_substring
  bundledCode: "#line 1 \"verify/string/longest_common_extension.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\n\n#line\
    \ 1 \"string/longest_common_extension.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <string>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"string/suffix_array.hpp\"\n\n\n\n#line 6 \"string/suffix_array.hpp\"\n#include\
    \ <numeric>\n#line 8 \"string/suffix_array.hpp\"\n#include <type_traits>\n#line\
    \ 10 \"string/suffix_array.hpp\"\n\nnamespace m1une {\nnamespace string {\nnamespace\
    \ detail {\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array_impl(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    if (n == 0) return\
    \ {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
    \    std::vector<Value> sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(),\
    \ sorted.end());\n    sorted.erase(std::unique(sorted.begin(), sorted.end()),\
    \ sorted.end());\n\n    int length = n + 1;\n    std::vector<int> order(length);\n\
    \    std::vector<int> rank(length);\n    std::vector<int> key(length);\n    key[n]\
    \ = 0;\n    for (int i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
    \ sorted.end(), sequence[i]) - sorted.begin()) + 1;\n    }\n\n    int alphabet\
    \ = int(sorted.size()) + 1;\n    std::vector<int> count(std::max(length, alphabet),\
    \ 0);\n    for (int value : key) count[value]++;\n    for (int i = 1; i < alphabet;\
    \ i++) count[i] += count[i - 1];\n    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]]\
    \ = i;\n\n    int classes = 1;\n    rank[order[0]] = 0;\n    for (int i = 1; i\
    \ < length; i++) {\n        if (key[order[i - 1]] != key[order[i]]) classes++;\n\
    \        rank[order[i]] = classes - 1;\n    }\n\n    std::vector<int> shifted(length);\n\
    \    std::vector<int> next_rank(length);\n    for (long long half = 1; half <\
    \ length; half <<= 1) {\n        for (int i = 0; i < length; i++) {\n        \
    \    long long position = order[i] - half;\n            if (position < 0) position\
    \ += length;\n            shifted[i] = int(position);\n        }\n\n        count.assign(classes,\
    \ 0);\n        for (int position : shifted) count[rank[position]]++;\n       \
    \ for (int i = 1; i < classes; i++) count[i] += count[i - 1];\n        for (int\
    \ i = length - 1; i >= 0; i--) {\n            int position = shifted[i];\n   \
    \         order[--count[rank[position]]] = position;\n        }\n\n        int\
    \ next_classes = 1;\n        next_rank[order[0]] = 0;\n        for (int i = 1;\
    \ i < length; i++) {\n            int current = order[i];\n            int previous\
    \ = order[i - 1];\n            int current_second = int((current + half) % length);\n\
    \            int previous_second = int((previous + half) % length);\n        \
    \    if (\n                rank[current] != rank[previous] ||\n              \
    \  rank[current_second] != rank[previous_second]\n            ) {\n          \
    \      next_classes++;\n            }\n            next_rank[current] = next_classes\
    \ - 1;\n        }\n        rank.swap(next_rank);\n        classes = next_classes;\n\
    \        if (classes == length) break;\n    }\n\n    std::vector<int> suffixes(n);\n\
    \    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];\n    return suffixes;\n\
    }\n\n}  // namespace detail\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array(const\
    \ Sequence& sequence) {\n    return detail::suffix_array_impl(sequence);\n}\n\n\
    inline std::vector<int> suffix_array(const std::string& text) {\n    std::vector<unsigned\
    \ char> values;\n    values.reserve(text.size());\n    for (unsigned char character\
    \ : text) values.push_back(character);\n    return detail::suffix_array_impl(values);\n\
    }\n\ntemplate <class Sequence>\nstd::vector<int> lcp_array(const Sequence& sequence,\
    \ const std::vector<int>& suffixes) {\n    int n = int(sequence.size());\n   \
    \ assert(int(suffixes.size()) == n);\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ rank(n);\n    for (int i = 0; i < n; i++) {\n        assert(0 <= suffixes[i]\
    \ && suffixes[i] < n);\n        rank[suffixes[i]] = i;\n    }\n\n    std::vector<int>\
    \ lcp(n - 1);\n    int common = 0;\n    for (int i = 0; i < n; i++) {\n      \
    \  int position = rank[i];\n        if (position == n - 1) {\n            common\
    \ = 0;\n            continue;\n        }\n        int j = suffixes[position +\
    \ 1];\n        while (\n            i + common < n &&\n            j + common\
    \ < n &&\n            sequence[i + common] == sequence[j + common]\n        )\
    \ {\n            common++;\n        }\n        lcp[position] = common;\n     \
    \   if (common > 0) common--;\n    }\n    return lcp;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 11 \"string/longest_common_extension.hpp\"\n\n\
    namespace m1une {\nnamespace string {\n\ntemplate <class Sequence = std::string>\n\
    struct LongestCommonExtension {\n   private:\n    Sequence _sequence;\n    std::vector<int>\
    \ _suffix_array;\n    std::vector<int> _rank;\n    std::vector<int> _lcp;\n  \
    \  std::vector<int> _log;\n    std::vector<std::vector<int>> _table;\n\n    int\
    \ range_min(int left, int right) const {\n        assert(0 <= left && left < right\
    \ && right <= int(_lcp.size()));\n        int k = _log[right - left];\n      \
    \  return std::min(_table[k][left], _table[k][right - (1 << k)]);\n    }\n\n \
    \   void build() {\n        int n = int(_sequence.size());\n        _suffix_array\
    \ = m1une::string::suffix_array(_sequence);\n        _rank.assign(n, 0);\n   \
    \     for (int i = 0; i < n; i++) {\n            _rank[_suffix_array[i]] = i;\n\
    \        }\n\n        _lcp = m1une::string::lcp_array(_sequence, _suffix_array);\n\
    \        int m = int(_lcp.size());\n        _log.assign(m + 1, 0);\n        for\
    \ (int i = 2; i <= m; i++) {\n            _log[i] = _log[i >> 1] + 1;\n      \
    \  }\n\n        _table.clear();\n        if (m == 0) return;\n        _table.assign(_log[m]\
    \ + 1, std::vector<int>());\n        _table[0] = _lcp;\n        for (int k = 1;\
    \ k < int(_table.size()); k++) {\n            int width = 1 << k;\n          \
    \  int half = width >> 1;\n            _table[k].resize(m - width + 1);\n    \
    \        for (int i = 0; i + width <= m; i++) {\n                _table[k][i]\
    \ = std::min(_table[k - 1][i], _table[k - 1][i + half]);\n            }\n    \
    \    }\n    }\n\n   public:\n    LongestCommonExtension() = default;\n\n    explicit\
    \ LongestCommonExtension(const Sequence& sequence) : _sequence(sequence) {\n \
    \       build();\n    }\n\n    explicit LongestCommonExtension(Sequence&& sequence)\
    \ : _sequence(std::move(sequence)) {\n        build();\n    }\n\n    int size()\
    \ const {\n        return int(_sequence.size());\n    }\n\n    bool empty() const\
    \ {\n        return _sequence.empty();\n    }\n\n    const Sequence& sequence()\
    \ const {\n        return _sequence;\n    }\n\n    const std::vector<int>& suffix_array()\
    \ const {\n        return _suffix_array;\n    }\n\n    const std::vector<int>&\
    \ rank() const {\n        return _rank;\n    }\n\n    const std::vector<int>&\
    \ lcp_array() const {\n        return _lcp;\n    }\n\n    int longest_common_extension(int\
    \ i, int j) const {\n        int n = size();\n        assert(0 <= i && i <= n);\n\
    \        assert(0 <= j && j <= n);\n        if (i == j) return n - i;\n      \
    \  if (i == n || j == n) return 0;\n\n        int left = _rank[i];\n        int\
    \ right = _rank[j];\n        if (left > right) std::swap(left, right);\n     \
    \   return range_min(left, right);\n    }\n\n    int longest_common_extension(int\
    \ i, int j, int limit) const {\n        assert(0 <= limit);\n        return std::min(longest_common_extension(i,\
    \ j), limit);\n    }\n\n    int lcp(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int operator()(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int compare_suffix(int i, int j) const {\n        int n =\
    \ size();\n        assert(0 <= i && i <= n);\n        assert(0 <= j && j <= n);\n\
    \        if (i == j) return 0;\n        int common = longest_common_extension(i,\
    \ j);\n        if (i + common == n && j + common == n) return 0;\n        if (i\
    \ + common == n) return -1;\n        if (j + common == n) return 1;\n        return\
    \ _sequence[i + common] < _sequence[j + common] ? -1 : 1;\n    }\n\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int n = size();\n        assert(0\
    \ <= l1 && l1 <= r1 && r1 <= n);\n        assert(0 <= l2 && l2 <= r2 && r2 <=\
    \ n);\n        int len1 = r1 - l1;\n        int len2 = r2 - l2;\n        int common\
    \ = longest_common_extension(l1, l2, std::min(len1, len2));\n        if (common\
    \ == len1 && common == len2) return 0;\n        if (common == len1) return -1;\n\
    \        if (common == len2) return 1;\n        return _sequence[l1 + common]\
    \ < _sequence[l2 + common] ? -1 : 1;\n    }\n};\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n\n#line 4 \"verify/string/longest_common_extension.test.cpp\"\
    \n\n#line 7 \"verify/string/longest_common_extension.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include\
    \ <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n\
    #include <iterator>\n#line 15 \"utilities/fast_io.hpp\"\n#include <sys/stat.h>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/string/longest_common_extension.test.cpp\"\
    \n\nnamespace {\n\nint naive_longest_common_extension(const std::string& text,\
    \ int i, int j) {\n    int n = int(text.size());\n    int result = 0;\n    while\
    \ (i + result < n && j + result < n && text[i + result] == text[j + result]) {\n\
    \        result++;\n    }\n    return result;\n}\n\nint sign(int value) {\n  \
    \  if (value < 0) return -1;\n    if (value > 0) return 1;\n    return 0;\n}\n\
    \nvoid test_fixed() {\n    std::string empty;\n    m1une::string::LongestCommonExtension<>\
    \ empty_extension(empty);\n    assert(empty_extension.empty());\n    assert(empty_extension.longest_common_extension(0,\
    \ 0) == 0);\n    assert(empty_extension.compare_suffix(0, 0) == 0);\n    assert(empty_extension.compare(0,\
    \ 0, 0, 0) == 0);\n    assert(empty_extension.suffix_array().empty());\n    assert(empty_extension.rank().empty());\n\
    \    assert(empty_extension.lcp_array().empty());\n\n    std::string text = \"\
    banana\";\n    m1une::string::LongestCommonExtension<> extension(text);\n    assert(extension.size()\
    \ == 6);\n    assert(extension.sequence() == text);\n    assert(extension.longest_common_extension(1,\
    \ 3) == 3);\n    assert(extension.longest_common_extension(2, 4) == 2);\n    assert(extension.longest_common_extension(0,\
    \ 2) == 0);\n    assert(extension.longest_common_extension(6, 1) == 0);\n    assert(extension.longest_common_extension(2,\
    \ 2) == 4);\n    assert(extension.longest_common_extension(1, 3, 2) == 2);\n \
    \   assert(extension.lcp(1, 3) == 3);\n    assert(extension(1, 3) == 3);\n   \
    \ assert(extension.compare_suffix(1, 3) == 1);\n    assert(extension.compare_suffix(3,\
    \ 1) == -1);\n    assert(extension.compare(1, 4, 3, 6) == 0);\n    assert(extension.compare(1,\
    \ 5, 3, 6) == 1);\n    assert(extension.compare(0, 0, 1, 2) == -1);\n\n    std::vector<int>\
    \ values;\n    values.push_back(2);\n    values.push_back(1);\n    values.push_back(2);\n\
    \    values.push_back(1);\n    values.push_back(2);\n    m1une::string::LongestCommonExtension<std::vector<int>>\
    \ vector_extension(values);\n    assert(vector_extension.longest_common_extension(0,\
    \ 2) == 3);\n    assert(vector_extension.longest_common_extension(1, 3) == 2);\n\
    \    assert(vector_extension.compare(0, 3, 2, 5) == 0);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20240709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1500; trial++) {\n        int n = int(random()\
    \ % 50);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 5);\n        m1une::string::LongestCommonExtension<>\
    \ extension(text);\n\n        const std::vector<int>& suffixes = extension.suffix_array();\n\
    \        const std::vector<int>& rank = extension.rank();\n        for (int i\
    \ = 0; i < n; i++) {\n            assert(0 <= suffixes[i] && suffixes[i] < n);\n\
    \            assert(rank[suffixes[i]] == i);\n        }\n\n        for (int i\
    \ = 0; i <= n; i++) {\n            for (int j = 0; j <= n; j++) {\n          \
    \      int expected = naive_longest_common_extension(text, i, j);\n          \
    \      assert(extension.longest_common_extension(i, j) == expected);\n       \
    \         int limit = int(random() % (n + 1));\n                assert(extension.longest_common_extension(i,\
    \ j, limit) == std::min(expected, limit));\n\n                std::string suffix_i\
    \ = text.substr(i);\n                std::string suffix_j = text.substr(j);\n\
    \                assert(extension.compare_suffix(i, j) == sign(suffix_i.compare(suffix_j)));\n\
    \            }\n        }\n\n        for (int query = 0; query < 200; query++)\
    \ {\n            int l1 = int(random() % (n + 1));\n            int r1 = l1 +\
    \ int(random() % (n - l1 + 1));\n            int l2 = int(random() % (n + 1));\n\
    \            int r2 = l2 + int(random() % (n - l2 + 1));\n            std::string\
    \ first = text.substr(l1, r1 - l1);\n            std::string second = text.substr(l2,\
    \ r2 - l2);\n            assert(extension.compare(l1, r1, l2, r2) == sign(first.compare(second)));\n\
    \        }\n    }\n}\n\nstd::vector<int> combine_strings(const std::string& first,\
    \ const std::string& second) {\n    std::vector<int> combined;\n    combined.reserve(first.size()\
    \ + second.size() + 1);\n    for (unsigned char character : first) combined.push_back(int(character)\
    \ + 2);\n    combined.push_back(1);\n    for (unsigned char character : second)\
    \ combined.push_back(int(character) + 2);\n    return combined;\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n    std::string first,\
    \ second;\n    fast_input >> first >> second;\n\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    std::vector<int> combined = combine_strings(first,\
    \ second);\n    m1une::string::LongestCommonExtension<std::vector<int>> extension(combined);\n\
    \n    int best_first = 0;\n    int best_second = 0;\n    int best_length = 0;\n\
    \    const std::vector<int>& suffixes = extension.suffix_array();\n    for (int\
    \ i = 0; i + 1 < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n\
    \        int b = suffixes[i + 1];\n        bool a_first = a < n;\n        bool\
    \ b_first = b < n;\n        bool a_second = n < a;\n        bool b_second = n\
    \ < b;\n        if (a_first == b_first || a_second == b_second) continue;\n  \
    \      if ((!a_first && !a_second) || (!b_first && !b_second)) continue;\n\n \
    \       int first_pos = a_first ? a : b;\n        int second_pos = a_first ? b\
    \ - n - 1 : a - n - 1;\n        int length = extension.longest_common_extension(a,\
    \ b);\n        length = std::min(length, n - first_pos);\n        length = std::min(length,\
    \ m - second_pos);\n        if (length > best_length) {\n            best_length\
    \ = length;\n            best_first = first_pos;\n            best_second = second_pos;\n\
    \        }\n    }\n\n    fast_output << best_first << ' ' << best_first + best_length\
    \ << ' '\n              << best_second << ' ' << best_second + best_length <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\
    \n\n#include \"../../string/longest_common_extension.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <string>\n#include <vector>\n\nnamespace {\n\nint naive_longest_common_extension(const\
    \ std::string& text, int i, int j) {\n    int n = int(text.size());\n    int result\
    \ = 0;\n    while (i + result < n && j + result < n && text[i + result] == text[j\
    \ + result]) {\n        result++;\n    }\n    return result;\n}\n\nint sign(int\
    \ value) {\n    if (value < 0) return -1;\n    if (value > 0) return 1;\n    return\
    \ 0;\n}\n\nvoid test_fixed() {\n    std::string empty;\n    m1une::string::LongestCommonExtension<>\
    \ empty_extension(empty);\n    assert(empty_extension.empty());\n    assert(empty_extension.longest_common_extension(0,\
    \ 0) == 0);\n    assert(empty_extension.compare_suffix(0, 0) == 0);\n    assert(empty_extension.compare(0,\
    \ 0, 0, 0) == 0);\n    assert(empty_extension.suffix_array().empty());\n    assert(empty_extension.rank().empty());\n\
    \    assert(empty_extension.lcp_array().empty());\n\n    std::string text = \"\
    banana\";\n    m1une::string::LongestCommonExtension<> extension(text);\n    assert(extension.size()\
    \ == 6);\n    assert(extension.sequence() == text);\n    assert(extension.longest_common_extension(1,\
    \ 3) == 3);\n    assert(extension.longest_common_extension(2, 4) == 2);\n    assert(extension.longest_common_extension(0,\
    \ 2) == 0);\n    assert(extension.longest_common_extension(6, 1) == 0);\n    assert(extension.longest_common_extension(2,\
    \ 2) == 4);\n    assert(extension.longest_common_extension(1, 3, 2) == 2);\n \
    \   assert(extension.lcp(1, 3) == 3);\n    assert(extension(1, 3) == 3);\n   \
    \ assert(extension.compare_suffix(1, 3) == 1);\n    assert(extension.compare_suffix(3,\
    \ 1) == -1);\n    assert(extension.compare(1, 4, 3, 6) == 0);\n    assert(extension.compare(1,\
    \ 5, 3, 6) == 1);\n    assert(extension.compare(0, 0, 1, 2) == -1);\n\n    std::vector<int>\
    \ values;\n    values.push_back(2);\n    values.push_back(1);\n    values.push_back(2);\n\
    \    values.push_back(1);\n    values.push_back(2);\n    m1une::string::LongestCommonExtension<std::vector<int>>\
    \ vector_extension(values);\n    assert(vector_extension.longest_common_extension(0,\
    \ 2) == 3);\n    assert(vector_extension.longest_common_extension(1, 3) == 2);\n\
    \    assert(vector_extension.compare(0, 3, 2, 5) == 0);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20240709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1500; trial++) {\n        int n = int(random()\
    \ % 50);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 5);\n        m1une::string::LongestCommonExtension<>\
    \ extension(text);\n\n        const std::vector<int>& suffixes = extension.suffix_array();\n\
    \        const std::vector<int>& rank = extension.rank();\n        for (int i\
    \ = 0; i < n; i++) {\n            assert(0 <= suffixes[i] && suffixes[i] < n);\n\
    \            assert(rank[suffixes[i]] == i);\n        }\n\n        for (int i\
    \ = 0; i <= n; i++) {\n            for (int j = 0; j <= n; j++) {\n          \
    \      int expected = naive_longest_common_extension(text, i, j);\n          \
    \      assert(extension.longest_common_extension(i, j) == expected);\n       \
    \         int limit = int(random() % (n + 1));\n                assert(extension.longest_common_extension(i,\
    \ j, limit) == std::min(expected, limit));\n\n                std::string suffix_i\
    \ = text.substr(i);\n                std::string suffix_j = text.substr(j);\n\
    \                assert(extension.compare_suffix(i, j) == sign(suffix_i.compare(suffix_j)));\n\
    \            }\n        }\n\n        for (int query = 0; query < 200; query++)\
    \ {\n            int l1 = int(random() % (n + 1));\n            int r1 = l1 +\
    \ int(random() % (n - l1 + 1));\n            int l2 = int(random() % (n + 1));\n\
    \            int r2 = l2 + int(random() % (n - l2 + 1));\n            std::string\
    \ first = text.substr(l1, r1 - l1);\n            std::string second = text.substr(l2,\
    \ r2 - l2);\n            assert(extension.compare(l1, r1, l2, r2) == sign(first.compare(second)));\n\
    \        }\n    }\n}\n\nstd::vector<int> combine_strings(const std::string& first,\
    \ const std::string& second) {\n    std::vector<int> combined;\n    combined.reserve(first.size()\
    \ + second.size() + 1);\n    for (unsigned char character : first) combined.push_back(int(character)\
    \ + 2);\n    combined.push_back(1);\n    for (unsigned char character : second)\
    \ combined.push_back(int(character) + 2);\n    return combined;\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n    std::string first,\
    \ second;\n    fast_input >> first >> second;\n\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    std::vector<int> combined = combine_strings(first,\
    \ second);\n    m1une::string::LongestCommonExtension<std::vector<int>> extension(combined);\n\
    \n    int best_first = 0;\n    int best_second = 0;\n    int best_length = 0;\n\
    \    const std::vector<int>& suffixes = extension.suffix_array();\n    for (int\
    \ i = 0; i + 1 < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n\
    \        int b = suffixes[i + 1];\n        bool a_first = a < n;\n        bool\
    \ b_first = b < n;\n        bool a_second = n < a;\n        bool b_second = n\
    \ < b;\n        if (a_first == b_first || a_second == b_second) continue;\n  \
    \      if ((!a_first && !a_second) || (!b_first && !b_second)) continue;\n\n \
    \       int first_pos = a_first ? a : b;\n        int second_pos = a_first ? b\
    \ - n - 1 : a - n - 1;\n        int length = extension.longest_common_extension(a,\
    \ b);\n        length = std::min(length, n - first_pos);\n        length = std::min(length,\
    \ m - second_pos);\n        if (length > best_length) {\n            best_length\
    \ = length;\n            best_first = first_pos;\n            best_second = second_pos;\n\
    \        }\n    }\n\n    fast_output << best_first << ' ' << best_first + best_length\
    \ << ' '\n              << best_second << ' ' << best_second + best_length <<\
    \ '\\n';\n}\n"
  dependsOn:
  - string/longest_common_extension.hpp
  - string/suffix_array.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/longest_common_extension.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/longest_common_extension.test.cpp
layout: document
redirect_from:
- /verify/verify/string/longest_common_extension.test.cpp
- /verify/verify/string/longest_common_extension.test.cpp.html
title: verify/string/longest_common_extension.test.cpp
---
