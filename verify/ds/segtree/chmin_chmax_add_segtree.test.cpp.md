---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/chmin_chmax_add_segtree.hpp
    title: Chmin Chmax Add Segment Tree Beats!
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
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/chmin_chmax_add_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\n\
    \n#line 1 \"ds/segtree/chmin_chmax_add_segtree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <limits>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Segment Tree Beats supporting range\
    \ chmin/chmax/add and sum/min/max queries.\ntemplate <std::signed_integral T =\
    \ long long>\nstruct ChminChmaxAddSegtree {\n   private:\n    static constexpr\
    \ T positive_infinity = std::numeric_limits<T>::max();\n    static constexpr T\
    \ negative_infinity = std::numeric_limits<T>::lowest();\n\n    struct Node {\n\
    \        T sum = 0;\n        T maximum = negative_infinity;\n        T second_maximum\
    \ = negative_infinity;\n        T minimum = positive_infinity;\n        T second_minimum\
    \ = positive_infinity;\n        T lazy_add = 0;\n        int maximum_count = 0;\n\
    \        int minimum_count = 0;\n        int length = 0;\n    };\n\n    int _n;\n\
    \    std::vector<Node> _nodes;\n\n    static Node make_leaf(T value) {\n     \
    \   Node node;\n        node.sum = value;\n        node.maximum = value;\n   \
    \     node.minimum = value;\n        node.maximum_count = 1;\n        node.minimum_count\
    \ = 1;\n        node.length = 1;\n        return node;\n    }\n\n    static Node\
    \ merge_nodes(const Node& left, const Node& right) {\n        Node result;\n \
    \       result.sum = left.sum + right.sum;\n        result.length = left.length\
    \ + right.length;\n\n        result.maximum = std::max(left.maximum, right.maximum);\n\
    \        result.maximum_count = 0;\n        result.second_maximum = negative_infinity;\n\
    \        if (left.maximum == result.maximum) {\n            result.maximum_count\
    \ += left.maximum_count;\n            result.second_maximum =\n              \
    \  std::max(result.second_maximum, left.second_maximum);\n        } else {\n \
    \           result.second_maximum =\n                std::max(result.second_maximum,\
    \ left.maximum);\n        }\n        if (right.maximum == result.maximum) {\n\
    \            result.maximum_count += right.maximum_count;\n            result.second_maximum\
    \ =\n                std::max(result.second_maximum, right.second_maximum);\n\
    \        } else {\n            result.second_maximum =\n                std::max(result.second_maximum,\
    \ right.maximum);\n        }\n\n        result.minimum = std::min(left.minimum,\
    \ right.minimum);\n        result.minimum_count = 0;\n        result.second_minimum\
    \ = positive_infinity;\n        if (left.minimum == result.minimum) {\n      \
    \      result.minimum_count += left.minimum_count;\n            result.second_minimum\
    \ =\n                std::min(result.second_minimum, left.second_minimum);\n \
    \       } else {\n            result.second_minimum =\n                std::min(result.second_minimum,\
    \ left.minimum);\n        }\n        if (right.minimum == result.minimum) {\n\
    \            result.minimum_count += right.minimum_count;\n            result.second_minimum\
    \ =\n                std::min(result.second_minimum, right.second_minimum);\n\
    \        } else {\n            result.second_minimum =\n                std::min(result.second_minimum,\
    \ right.minimum);\n        }\n        return result;\n    }\n\n    void build(int\
    \ node, int left, int right, const std::vector<T>& values) {\n        if (right\
    \ - left == 1) {\n            _nodes[node] = make_leaf(values[left]);\n      \
    \      return;\n        }\n        int middle = left + (right - left) / 2;\n \
    \       build(node * 2, left, middle, values);\n        build(node * 2 + 1, middle,\
    \ right, values);\n        pull(node);\n    }\n\n    void pull(int node) {\n \
    \       _nodes[node] = merge_nodes(\n            _nodes[node * 2],\n         \
    \   _nodes[node * 2 + 1]\n        );\n    }\n\n    void apply_add(int node, T\
    \ value) {\n        Node& current = _nodes[node];\n        current.sum += value\
    \ * T(current.length);\n        current.maximum += value;\n        current.minimum\
    \ += value;\n        if (current.second_maximum != negative_infinity) {\n    \
    \        current.second_maximum += value;\n        }\n        if (current.second_minimum\
    \ != positive_infinity) {\n            current.second_minimum += value;\n    \
    \    }\n        current.lazy_add += value;\n    }\n\n    void apply_chmin(int\
    \ node, T value) {\n        Node& current = _nodes[node];\n        if (current.maximum\
    \ <= value) return;\n        current.sum +=\n            (value - current.maximum)\
    \ * T(current.maximum_count);\n        if (current.minimum == current.maximum)\
    \ {\n            current.minimum = value;\n        } else if (current.second_minimum\
    \ == current.maximum) {\n            current.second_minimum = value;\n       \
    \ }\n        current.maximum = value;\n    }\n\n    void apply_chmax(int node,\
    \ T value) {\n        Node& current = _nodes[node];\n        if (value <= current.minimum)\
    \ return;\n        current.sum +=\n            (value - current.minimum) * T(current.minimum_count);\n\
    \        if (current.maximum == current.minimum) {\n            current.maximum\
    \ = value;\n        } else if (current.second_maximum == current.minimum) {\n\
    \            current.second_maximum = value;\n        }\n        current.minimum\
    \ = value;\n    }\n\n    void push(int node) {\n        Node& current = _nodes[node];\n\
    \        if (current.length == 1) {\n            current.lazy_add = 0;\n     \
    \       return;\n        }\n        if (current.lazy_add != 0) {\n           \
    \ apply_add(node * 2, current.lazy_add);\n            apply_add(node * 2 + 1,\
    \ current.lazy_add);\n            current.lazy_add = 0;\n        }\n        apply_chmin(node\
    \ * 2, current.maximum);\n        apply_chmin(node * 2 + 1, current.maximum);\n\
    \        apply_chmax(node * 2, current.minimum);\n        apply_chmax(node * 2\
    \ + 1, current.minimum);\n    }\n\n    void range_chmin(\n        int node,\n\
    \        int left,\n        int right,\n        int query_left,\n        int query_right,\n\
    \        T value\n    ) {\n        Node& current = _nodes[node];\n        if (\n\
    \            query_right <= left ||\n            right <= query_left ||\n    \
    \        current.maximum <= value\n        ) {\n            return;\n        }\n\
    \        if (\n            query_left <= left &&\n            right <= query_right\
    \ &&\n            current.second_maximum < value\n        ) {\n            apply_chmin(node,\
    \ value);\n            return;\n        }\n        push(node);\n        int middle\
    \ = left + (right - left) / 2;\n        range_chmin(\n            node * 2,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right,\n            value\n        );\n        range_chmin(\n        \
    \    node * 2 + 1,\n            middle,\n            right,\n            query_left,\n\
    \            query_right,\n            value\n        );\n        pull(node);\n\
    \    }\n\n    void range_chmax(\n        int node,\n        int left,\n      \
    \  int right,\n        int query_left,\n        int query_right,\n        T value\n\
    \    ) {\n        Node& current = _nodes[node];\n        if (\n            query_right\
    \ <= left ||\n            right <= query_left ||\n            value <= current.minimum\n\
    \        ) {\n            return;\n        }\n        if (\n            query_left\
    \ <= left &&\n            right <= query_right &&\n            value < current.second_minimum\n\
    \        ) {\n            apply_chmax(node, value);\n            return;\n   \
    \     }\n        push(node);\n        int middle = left + (right - left) / 2;\n\
    \        range_chmax(\n            node * 2,\n            left,\n            middle,\n\
    \            query_left,\n            query_right,\n            value\n      \
    \  );\n        range_chmax(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       value\n        );\n        pull(node);\n    }\n\n    void range_add(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        T value\n    ) {\n        if (query_right <=\
    \ left || right <= query_left) return;\n        if (query_left <= left && right\
    \ <= query_right) {\n            apply_add(node, value);\n            return;\n\
    \        }\n        push(node);\n        int middle = left + (right - left) /\
    \ 2;\n        range_add(\n            node * 2,\n            left,\n         \
    \   middle,\n            query_left,\n            query_right,\n            value\n\
    \        );\n        range_add(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       value\n        );\n        pull(node);\n    }\n\n    Node range_query(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right\n    ) {\n        if (query_left <= left && right <=\
    \ query_right) {\n            return _nodes[node];\n        }\n        push(node);\n\
    \        int middle = left + (right - left) / 2;\n        if (query_right <= middle)\
    \ {\n            return range_query(\n                node * 2,\n            \
    \    left,\n                middle,\n                query_left,\n           \
    \     query_right\n            );\n        }\n        if (middle <= query_left)\
    \ {\n            return range_query(\n                node * 2 + 1,\n        \
    \        middle,\n                right,\n                query_left,\n      \
    \          query_right\n            );\n        }\n        return merge_nodes(\n\
    \            range_query(\n                node * 2,\n                left,\n\
    \                middle,\n                query_left,\n                query_right\n\
    \            ),\n            range_query(\n                node * 2 + 1,\n   \
    \             middle,\n                right,\n                query_left,\n \
    \               query_right\n            )\n        );\n    }\n\n   public:\n\
    \    ChminChmaxAddSegtree() : _n(0) {}\n\n    explicit ChminChmaxAddSegtree(int\
    \ n)\n        : _n(n) {\n        assert(0 <= n);\n        if (_n != 0) {\n   \
    \         _nodes.resize(std::size_t(_n) * 4);\n            std::vector<T> values(_n,\
    \ T(0));\n            build(1, 0, _n, values);\n        }\n    }\n\n    explicit\
    \ ChminChmaxAddSegtree(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _nodes(values.empty() ? 0 : values.size() * 4) {\n        if (_n !=\
    \ 0) build(1, 0, _n, values);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   void chmin(int left, int right, T value) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        if (left != right) {\n            range_chmin(1,\
    \ 0, _n, left, right, value);\n        }\n    }\n\n    void chmax(int left, int\
    \ right, T value) {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        if (left != right) {\n            range_chmax(1, 0, _n, left, right,\
    \ value);\n        }\n    }\n\n    void add(int left, int right, T value) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ != right) {\n            range_add(1, 0, _n, left, right, value);\n        }\n\
    \    }\n\n    void range_chmin(int left, int right, T value) {\n        chmin(left,\
    \ right, value);\n    }\n\n    void range_chmax(int left, int right, T value)\
    \ {\n        chmax(left, right, value);\n    }\n\n    void range_add(int left,\
    \ int right, T value) {\n        add(left, right, value);\n    }\n\n    T sum(int\
    \ left, int right) {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        return left == right\n            ? T(0)\n            : range_query(1,\
    \ 0, _n, left, right).sum;\n    }\n\n    T min(int left, int right) {\n      \
    \  assert(0 <= left && left < right && right <= _n);\n        return range_query(1,\
    \ 0, _n, left, right).minimum;\n    }\n\n    T max(int left, int right) {\n  \
    \      assert(0 <= left && left < right && right <= _n);\n        return range_query(1,\
    \ 0, _n, left, right).maximum;\n    }\n\n    T range_sum(int left, int right)\
    \ {\n        return sum(left, right);\n    }\n\n    T range_min(int left, int\
    \ right) {\n        return min(left, right);\n    }\n\n    T range_max(int left,\
    \ int right) {\n        return max(left, right);\n    }\n\n    T all_sum() const\
    \ {\n        return _n == 0 ? T(0) : _nodes[1].sum;\n    }\n\n    T all_min()\
    \ const {\n        assert(_n != 0);\n        return _nodes[1].minimum;\n    }\n\
    \n    T all_max() const {\n        assert(_n != 0);\n        return _nodes[1].maximum;\n\
    \    }\n\n    T get(int index) {\n        assert(0 <= index && index < _n);\n\
    \        return sum(index, index + 1);\n    }\n\n    T operator[](int index) {\n\
    \        return get(index);\n    }\n\n    void set(int index, T value) {\n   \
    \     assert(0 <= index && index < _n);\n        T current = get(index);\n   \
    \     add(index, index + 1, value - current);\n    }\n\n    std::vector<T> to_vector()\
    \ {\n        std::vector<T> result(_n);\n        for (int index = 0; index < _n;\
    \ ++index) {\n            result[index] = get(index);\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4\
    \ \"verify/ds/segtree/chmin_chmax_add_segtree.test.cpp\"\n\n#line 7 \"verify/ds/segtree/chmin_chmax_add_segtree.test.cpp\"\
    \n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/ds/segtree/chmin_chmax_add_segtree.test.cpp\"\
    \n#include <numeric>\n#line 11 \"verify/ds/segtree/chmin_chmax_add_segtree.test.cpp\"\
    \n\nnamespace {\n\nvoid test_randomized() {\n    std::uint64_t state = 1201;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1500; ++trial) {\n        int size = int(random() % 100);\n        std::vector<long\
    \ long> values(size);\n        for (long long& value : values) {\n           \
    \ value = static_cast<long long>(random() % 201) - 100;\n        }\n        m1une::ds::ChminChmaxAddSegtree<long\
    \ long> seg(values);\n\n        for (int operation = 0; operation < 1000; ++operation)\
    \ {\n            int left = int(random() % (size + 1));\n            int right\
    \ = int(random() % (size + 1));\n            if (right < left) std::swap(left,\
    \ right);\n            int type = int(random() % 8);\n            long long value\
    \ =\n                static_cast<long long>(random() % 101) - 50;\n\n        \
    \    if (type == 0) {\n                seg.chmin(left, right, value);\n      \
    \          for (int index = left; index < right; ++index) {\n                \
    \    values[index] = std::min(values[index], value);\n                }\n    \
    \        } else if (type == 1) {\n                seg.chmax(left, right, value);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::max(values[index], value);\n                }\n\
    \            } else if (type == 2) {\n                seg.add(left, right, value);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] += value;\n                }\n            } else if (type\
    \ == 3 && left < right) {\n                [[maybe_unused]] long long expected\
    \ =\n                    *std::min_element(\n                        values.begin()\
    \ + left,\n                        values.begin() + right\n                  \
    \  );\n                assert(seg.min(left, right) == expected);\n           \
    \ } else if (type == 4 && left < right) {\n                [[maybe_unused]] long\
    \ long expected =\n                    *std::max_element(\n                  \
    \      values.begin() + left,\n                        values.begin() + right\n\
    \                    );\n                assert(seg.max(left, right) == expected);\n\
    \            } else if (type == 5 && size != 0) {\n                int index =\
    \ int(random() % size);\n                seg.set(index, value);\n            \
    \    values[index] = value;\n            } else {\n                [[maybe_unused]]\
    \ long long expected = std::accumulate(\n                    values.begin() +\
    \ left,\n                    values.begin() + right,\n                    0LL\n\
    \                );\n                assert(seg.sum(left, right) == expected);\n\
    \            }\n\n            assert(seg.to_vector() == values);\n           \
    \ assert(\n                seg.all_sum()\n                == std::accumulate(values.begin(),\
    \ values.end(), 0LL)\n            );\n            if (!values.empty()) {\n   \
    \             assert(\n                    seg.all_min()\n                   \
    \ == *std::min_element(values.begin(), values.end())\n                );\n   \
    \             assert(\n                    seg.all_max()\n                   \
    \ == *std::max_element(values.begin(), values.end())\n                );\n   \
    \         }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) fast_input >> value;\n    m1une::ds::ChminChmaxAddSegtree<long\
    \ long> seg(values);\n\n    while (q--) {\n        int type, left, right;\n  \
    \      fast_input >> type >> left >> right;\n        if (type == 0) {\n      \
    \      long long value;\n            fast_input >> value;\n            seg.chmin(left,\
    \ right, value);\n        } else if (type == 1) {\n            long long value;\n\
    \            fast_input >> value;\n            seg.chmax(left, right, value);\n\
    \        } else if (type == 2) {\n            long long value;\n            fast_input\
    \ >> value;\n            seg.add(left, right, value);\n        } else {\n    \
    \        fast_output << seg.sum(left, right) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include \"../../../ds/segtree/chmin_chmax_add_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <numeric>\n#include <vector>\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1201;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1500; ++trial) {\n        int size\
    \ = int(random() % 100);\n        std::vector<long long> values(size);\n     \
    \   for (long long& value : values) {\n            value = static_cast<long long>(random()\
    \ % 201) - 100;\n        }\n        m1une::ds::ChminChmaxAddSegtree<long long>\
    \ seg(values);\n\n        for (int operation = 0; operation < 1000; ++operation)\
    \ {\n            int left = int(random() % (size + 1));\n            int right\
    \ = int(random() % (size + 1));\n            if (right < left) std::swap(left,\
    \ right);\n            int type = int(random() % 8);\n            long long value\
    \ =\n                static_cast<long long>(random() % 101) - 50;\n\n        \
    \    if (type == 0) {\n                seg.chmin(left, right, value);\n      \
    \          for (int index = left; index < right; ++index) {\n                \
    \    values[index] = std::min(values[index], value);\n                }\n    \
    \        } else if (type == 1) {\n                seg.chmax(left, right, value);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::max(values[index], value);\n                }\n\
    \            } else if (type == 2) {\n                seg.add(left, right, value);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] += value;\n                }\n            } else if (type\
    \ == 3 && left < right) {\n                [[maybe_unused]] long long expected\
    \ =\n                    *std::min_element(\n                        values.begin()\
    \ + left,\n                        values.begin() + right\n                  \
    \  );\n                assert(seg.min(left, right) == expected);\n           \
    \ } else if (type == 4 && left < right) {\n                [[maybe_unused]] long\
    \ long expected =\n                    *std::max_element(\n                  \
    \      values.begin() + left,\n                        values.begin() + right\n\
    \                    );\n                assert(seg.max(left, right) == expected);\n\
    \            } else if (type == 5 && size != 0) {\n                int index =\
    \ int(random() % size);\n                seg.set(index, value);\n            \
    \    values[index] = value;\n            } else {\n                [[maybe_unused]]\
    \ long long expected = std::accumulate(\n                    values.begin() +\
    \ left,\n                    values.begin() + right,\n                    0LL\n\
    \                );\n                assert(seg.sum(left, right) == expected);\n\
    \            }\n\n            assert(seg.to_vector() == values);\n           \
    \ assert(\n                seg.all_sum()\n                == std::accumulate(values.begin(),\
    \ values.end(), 0LL)\n            );\n            if (!values.empty()) {\n   \
    \             assert(\n                    seg.all_min()\n                   \
    \ == *std::min_element(values.begin(), values.end())\n                );\n   \
    \             assert(\n                    seg.all_max()\n                   \
    \ == *std::max_element(values.begin(), values.end())\n                );\n   \
    \         }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) fast_input >> value;\n    m1une::ds::ChminChmaxAddSegtree<long\
    \ long> seg(values);\n\n    while (q--) {\n        int type, left, right;\n  \
    \      fast_input >> type >> left >> right;\n        if (type == 0) {\n      \
    \      long long value;\n            fast_input >> value;\n            seg.chmin(left,\
    \ right, value);\n        } else if (type == 1) {\n            long long value;\n\
    \            fast_input >> value;\n            seg.chmax(left, right, value);\n\
    \        } else if (type == 2) {\n            long long value;\n            fast_input\
    \ >> value;\n            seg.add(left, right, value);\n        } else {\n    \
    \        fast_output << seg.sum(left, right) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/chmin_chmax_add_segtree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/segtree/chmin_chmax_add_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/chmin_chmax_add_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/chmin_chmax_add_segtree.test.cpp
- /verify/verify/ds/segtree/chmin_chmax_add_segtree.test.cpp.html
title: verify/ds/segtree/chmin_chmax_add_segtree.test.cpp
---
