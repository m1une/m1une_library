---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/merge_sort_tree.hpp
    title: Merge Sort Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound
    links:
    - https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound
  bundledCode: "#line 1 \"verify/ds/range_query/merge_sort_tree_sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound\"\
    \n\n#line 1 \"ds/range_query/merge_sort_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <iterator>\n\
    #include <limits>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\n\
    template <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 15 \"ds/range_query/merge_sort_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Static range counting, sums, and order\
    \ statistics for arbitrary ordered values.\ntemplate <class T, class Sum = T>\n\
    class MergeSortTree {\n   private:\n    struct Node {\n        std::vector<T>\
    \ values;\n        std::vector<Sum> prefix_sum;\n    };\n\n    static constexpr\
    \ bool supports_sum = requires(Sum left, Sum right, const T& value) {\n      \
    \  Sum{};\n        static_cast<Sum>(value);\n        { left + right } -> std::convertible_to<Sum>;\n\
    \        { left - right } -> std::convertible_to<Sum>;\n    };\n\n    int _n;\n\
    \    int _size;\n    std::vector<T> _values;\n    std::vector<T> _sorted_values;\n\
    \    std::vector<Node> _tree;\n    std::vector<Sum> _original_prefix_sum;\n\n\
    \    template <class Callback>\n    void visit(int left, int right, Callback&&\
    \ callback) const {\n        left += _size;\n        right += _size;\n       \
    \ while (left < right) {\n            if (left & 1) callback(_tree[left++]);\n\
    \            if (right & 1) callback(_tree[--right]);\n            left >>= 1;\n\
    \            right >>= 1;\n        }\n    }\n\n    static bool equivalent(const\
    \ T& left, const T& right) {\n        return !(left < right) && !(right < left);\n\
    \    }\n\n   public:\n    MergeSortTree()\n        : _n(0),\n          _size(1),\n\
    \          _tree(2) {\n        if constexpr (supports_sum) _original_prefix_sum.push_back(Sum{});\n\
    \    }\n\n    explicit MergeSortTree(const std::vector<T>& values)\n        :\
    \ _n(0),\n          _size(1) {\n        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        _n = int(values.size());\n        _size = m1une::math::bit_ceil(std::max(1,\
    \ _n));\n        _values = values;\n        _sorted_values = values;\n       \
    \ std::sort(_sorted_values.begin(), _sorted_values.end());\n        _sorted_values.erase(\n\
    \            std::unique(\n                _sorted_values.begin(),\n         \
    \       _sorted_values.end(),\n                [](const T& left, const T& right)\
    \ {\n                    return equivalent(left, right);\n                }\n\
    \            ),\n            _sorted_values.end()\n        );\n\n        _tree.resize(2\
    \ * _size);\n        for (int index = 0; index < _n; index++) {\n            _tree[_size\
    \ + index].values.push_back(values[index]);\n        }\n        for (int node\
    \ = _size - 1; node >= 1; node--) {\n            const auto& left = _tree[2 *\
    \ node].values;\n            const auto& right = _tree[2 * node + 1].values;\n\
    \            _tree[node].values.reserve(left.size() + right.size());\n       \
    \     std::merge(\n                left.begin(),\n                left.end(),\n\
    \                right.begin(),\n                right.end(),\n              \
    \  std::back_inserter(_tree[node].values)\n            );\n        }\n\n     \
    \   if constexpr (supports_sum) {\n            _original_prefix_sum.reserve(_n\
    \ + 1);\n            _original_prefix_sum.push_back(Sum{});\n            for (const\
    \ T& value : values) {\n                _original_prefix_sum.push_back(\n    \
    \                _original_prefix_sum.back() + static_cast<Sum>(value)\n     \
    \           );\n            }\n            for (Node& node : _tree) {\n      \
    \          if (node.values.empty()) continue;\n                node.prefix_sum.reserve(node.values.size()\
    \ + 1);\n                node.prefix_sum.push_back(Sum{});\n                for\
    \ (const T& value : node.values) {\n                    node.prefix_sum.push_back(\n\
    \                        node.prefix_sum.back() + static_cast<Sum>(value)\n  \
    \                  );\n                }\n            }\n        }\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    const T& get(int position) const {\n  \
    \      assert(0 <= position && position < _n);\n        return _values[position];\n\
    \    }\n\n    const T& operator[](int position) const {\n        return get(position);\n\
    \    }\n\n    int count_less(int left, int right, const T& upper) const {\n  \
    \      assert(0 <= left && left <= right && right <= _n);\n        int result\
    \ = 0;\n        visit(left, right, [&](const Node& node) {\n            const\
    \ auto& values = node.values;\n            result += int(std::lower_bound(values.begin(),\
    \ values.end(), upper) - values.begin());\n        });\n        return result;\n\
    \    }\n\n    int count_less_equal(int left, int right, const T& upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        int result\
    \ = 0;\n        visit(left, right, [&](const Node& node) {\n            const\
    \ auto& values = node.values;\n            result += int(std::upper_bound(values.begin(),\
    \ values.end(), upper) - values.begin());\n        });\n        return result;\n\
    \    }\n\n    int count(int left, int right, const T& value) const {\n       \
    \ assert(0 <= left && left <= right && right <= _n);\n        int result = 0;\n\
    \        visit(left, right, [&](const Node& node) {\n            const auto& values\
    \ = node.values;\n            auto range = std::equal_range(values.begin(), values.end(),\
    \ value);\n            result += int(range.second - range.first);\n        });\n\
    \        return result;\n    }\n\n    int count(int left, int right, const T&\
    \ lower, const T& upper) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        if (!(lower < upper)) return 0;\n        int result =\
    \ 0;\n        visit(left, right, [&](const Node& node) {\n            const auto&\
    \ values = node.values;\n            auto first = std::lower_bound(values.begin(),\
    \ values.end(), lower);\n            auto last = std::lower_bound(values.begin(),\
    \ values.end(), upper);\n            result += int(last - first);\n        });\n\
    \        return result;\n    }\n\n    Sum range_sum(int left, int right) const\
    \ requires(supports_sum) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        return _original_prefix_sum[right] - _original_prefix_sum[left];\n\
    \    }\n\n    Sum sum_less(int left, int right, const T& upper) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto iterator\
    \ = std::lower_bound(node.values.begin(), node.values.end(), upper);\n       \
    \     int position = int(iterator - node.values.begin());\n            result\
    \ = result + node.prefix_sum[position];\n        });\n        return result;\n\
    \    }\n\n    Sum sum_less_equal(int left, int right, const T& upper) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto iterator\
    \ = std::upper_bound(node.values.begin(), node.values.end(), upper);\n       \
    \     int position = int(iterator - node.values.begin());\n            result\
    \ = result + node.prefix_sum[position];\n        });\n        return result;\n\
    \    }\n\n    Sum sum(int left, int right, const T& value) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto range =\
    \ std::equal_range(node.values.begin(), node.values.end(), value);\n         \
    \   int first = int(range.first - node.values.begin());\n            int last\
    \ = int(range.second - node.values.begin());\n            result = result + node.prefix_sum[last]\
    \ - node.prefix_sum[first];\n        });\n        return result;\n    }\n\n  \
    \  Sum sum(int left, int right, const T& lower, const T& upper) const\n      \
    \  requires(supports_sum) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (!(lower < upper)) return Sum{};\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto first_iterator\
    \ = std::lower_bound(node.values.begin(), node.values.end(), lower);\n       \
    \     auto last_iterator = std::lower_bound(node.values.begin(), node.values.end(),\
    \ upper);\n            int first = int(first_iterator - node.values.begin());\n\
    \            int last = int(last_iterator - node.values.begin());\n          \
    \  result = result + node.prefix_sum[last] - node.prefix_sum[first];\n       \
    \ });\n        return result;\n    }\n\n    T kth_smallest(int left, int right,\
    \ int k) const {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        assert(0 <= k && k < right - left);\n        int low = 0;\n        int\
    \ high = int(_sorted_values.size()) - 1;\n        while (low < high) {\n     \
    \       int middle = (low + high) / 2;\n            if (count_less_equal(left,\
    \ right, _sorted_values[middle]) > k) {\n                high = middle;\n    \
    \        } else {\n                low = middle + 1;\n            }\n        }\n\
    \        return _sorted_values[low];\n    }\n\n    T kth_largest(int left, int\
    \ right, int k) const {\n        assert(0 <= left && left <= right && right <=\
    \ _n);\n        assert(0 <= k && k < right - left);\n        return kth_smallest(left,\
    \ right, right - left - 1 - k);\n    }\n\n    std::optional<T> prev_value(int\
    \ left, int right, const T& upper) const {\n        assert(0 <= left && left <=\
    \ right && right <= _n);\n        std::optional<T> result;\n        visit(left,\
    \ right, [&](const Node& node) {\n            const auto& values = node.values;\n\
    \            auto iterator = std::lower_bound(values.begin(), values.end(), upper);\n\
    \            if (iterator == values.begin()) return;\n            --iterator;\n\
    \            if (!result || *result < *iterator) result = *iterator;\n       \
    \ });\n        return result;\n    }\n\n    std::optional<T> next_value(int left,\
    \ int right, const T& lower) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        std::optional<T> result;\n        visit(left, right,\
    \ [&](const Node& node) {\n            const auto& values = node.values;\n   \
    \         auto iterator = std::lower_bound(values.begin(), values.end(), lower);\n\
    \            if (iterator == values.end()) return;\n            if (!result ||\
    \ *iterator < *result) result = *iterator;\n        });\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/merge_sort_tree_sum.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include\
    \ <cstdlib>\n#include <cstdint>\n#include <cstring>\n#line 13 \"utilities/fast_io.hpp\"\
    \n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 17 \"\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 7 \"verify/ds/range_query/merge_sort_tree_sum.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n, query_count;\n    fast_input >> n >> query_count;\n\
    \    std::vector<int> values(n);\n    for (int& value : values) fast_input >>\
    \ value;\n\n    m1une::ds::MergeSortTree<int, long long> tree(values);\n    while\
    \ (query_count--) {\n        int left, right, upper;\n        fast_input >> left\
    \ >> right >> upper;\n        fast_output << tree.count_less_equal(left, right,\
    \ upper) << ' '\n                  << tree.sum_less_equal(left, right, upper)\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound\"\
    \n\n#include \"../../../ds/range_query/merge_sort_tree.hpp\"\n\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    int n, query_count;\n  \
    \  fast_input >> n >> query_count;\n    std::vector<int> values(n);\n    for (int&\
    \ value : values) fast_input >> value;\n\n    m1une::ds::MergeSortTree<int, long\
    \ long> tree(values);\n    while (query_count--) {\n        int left, right, upper;\n\
    \        fast_input >> left >> right >> upper;\n        fast_output << tree.count_less_equal(left,\
    \ right, upper) << ' '\n                  << tree.sum_less_equal(left, right,\
    \ upper) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/merge_sort_tree.hpp
  - math/bit_ceil.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/merge_sort_tree_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/merge_sort_tree_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/merge_sort_tree_sum.test.cpp
- /verify/verify/ds/range_query/merge_sort_tree_sum.test.cpp.html
title: verify/ds/range_query/merge_sort_tree_sum.test.cpp
---
