---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/convex_hull_trick.hpp
    title: Convex Hull Trick
  - icon: ':heavy_check_mark:'
    path: convex/li_chao_tree.hpp
    title: Li Chao Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 1 \"verify/convex/li_chao_tree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/line_add_get_min\"\n\n#line 1 \"convex/li_chao_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <limits>\n#include <numeric>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"convex/convex_hull_trick.hpp\"\
    \n\n\n\n#line 10 \"convex/convex_hull_trick.hpp\"\n\nnamespace m1une {\nnamespace\
    \ convex {\n\nenum class LineOptimization {\n    Minimize,\n    Maximize,\n};\n\
    \ntemplate <std::signed_integral T>\nusing line_wide_type = __int128_t;\n\ntemplate\
    \ <std::signed_integral T>\nstruct LinearFunction {\n    using value_type = line_wide_type<T>;\n\
    \n    value_type slope;\n    value_type intercept;\n\n    constexpr LinearFunction()\
    \ : slope(0), intercept(0) {}\n\n    constexpr LinearFunction(T slope_value, T\
    \ intercept_value) : slope(slope_value), intercept(intercept_value) {}\n\n   \
    \ constexpr value_type operator()(T x) const {\n        return slope * value_type(x)\
    \ + intercept;\n    }\n};\n\n// Convex hull trick for lines inserted in nondecreasing\
    \ slope order.\ntemplate <std::signed_integral T, LineOptimization Objective =\
    \ LineOptimization::Minimize>\nstruct ConvexHullTrick {\n    using Line = LinearFunction<T>;\n\
    \    using value_type = typename Line::value_type;\n\n   private:\n    std::vector<Line>\
    \ _lines;\n\n    static bool better(value_type first, value_type second) {\n \
    \       if constexpr (Objective == LineOptimization::Minimize) {\n           \
    \ return first < second;\n        } else {\n            return second < first;\n\
    \        }\n    }\n\n    static bool redundant(const Line& first, const Line&\
    \ middle, const Line& last) {\n        value_type left = (first.intercept - middle.intercept)\
    \ * (last.slope - middle.slope);\n        value_type right = (middle.intercept\
    \ - last.intercept) * (middle.slope - first.slope);\n        if constexpr (Objective\
    \ == LineOptimization::Minimize) {\n            return left <= right;\n      \
    \  } else {\n            return right <= left;\n        }\n    }\n\n   public:\n\
    \    ConvexHullTrick() = default;\n\n    int size() const {\n        return int(_lines.size());\n\
    \    }\n\n    bool empty() const {\n        return _lines.empty();\n    }\n\n\
    \    const std::vector<Line>& lines() const {\n        return _lines;\n    }\n\
    \n    void reserve(std::size_t line_capacity) {\n        _lines.reserve(line_capacity);\n\
    \    }\n\n    void clear() {\n        _lines.clear();\n    }\n\n    // Slopes\
    \ must be inserted in nondecreasing order.\n    void add_line(T slope, T intercept)\
    \ {\n        Line line(slope, intercept);\n        if (!_lines.empty()) {\n  \
    \          assert(_lines.back().slope <= line.slope);\n        }\n\n        if\
    \ (!_lines.empty() && _lines.back().slope == line.slope) {\n            if (!better(line.intercept,\
    \ _lines.back().intercept)) return;\n            _lines.pop_back();\n        }\n\
    \n        while (_lines.size() >= 2 && redundant(_lines[_lines.size() - 2], _lines.back(),\
    \ line)) {\n            _lines.pop_back();\n        }\n        _lines.push_back(line);\n\
    \    }\n\n    std::optional<value_type> try_query(T x) const {\n        if (_lines.empty())\
    \ return std::nullopt;\n        int low = 0;\n        int high = int(_lines.size())\
    \ - 1;\n        while (low < high) {\n            int middle = low + (high - low)\
    \ / 2;\n            value_type first = _lines[middle](x);\n            value_type\
    \ second = _lines[middle + 1](x);\n            if (better(first, second) || first\
    \ == second) {\n                high = middle;\n            } else {\n       \
    \         low = middle + 1;\n            }\n        }\n        return _lines[low](x);\n\
    \    }\n\n    value_type query(T x) const {\n        assert(!empty());\n     \
    \   return *try_query(x);\n    }\n};\n\ntemplate <std::signed_integral T>\nusing\
    \ MinConvexHullTrick = ConvexHullTrick<T, LineOptimization::Minimize>;\n\ntemplate\
    \ <std::signed_integral T>\nusing MaxConvexHullTrick = ConvexHullTrick<T, LineOptimization::Maximize>;\n\
    \n}  // namespace convex\n}  // namespace m1une\n\n\n#line 15 \"convex/li_chao_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\n// Dynamic Li Chao tree over an integral\
    \ half-open coordinate domain.\ntemplate <std::signed_integral T, LineOptimization\
    \ Objective = LineOptimization::Minimize>\nstruct LiChaoTree {\n    using Line\
    \ = LinearFunction<T>;\n    using value_type = typename Line::value_type;\n\n\
    \   private:\n    struct Node {\n        Line line;\n        bool has_line;\n\
    \        int left;\n        int right;\n\n        Node() : has_line(false), left(-1),\
    \ right(-1) {}\n\n        explicit Node(Line value) : line(std::move(value)),\
    \ has_line(true), left(-1), right(-1) {}\n    };\n\n    T _left;\n    T _right;\n\
    \    int _root;\n    std::vector<Node> _nodes;\n\n    static bool better(value_type\
    \ first, value_type second) {\n        if constexpr (Objective == LineOptimization::Minimize)\
    \ {\n            return first < second;\n        } else {\n            return\
    \ second < first;\n        }\n    }\n\n    int new_node() {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back();\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int new_node(Line line)\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(std::move(line));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_line_node(int node, T left, T right, Line line) {\n\
    \        if (node == -1) return new_node(std::move(line));\n        if (!_nodes[node].has_line)\
    \ {\n            _nodes[node].line = std::move(line);\n            _nodes[node].has_line\
    \ = true;\n            return node;\n        }\n\n        T middle = std::midpoint(left,\
    \ right);\n        bool left_better = better(line(left), _nodes[node].line(left));\n\
    \        bool middle_better = better(line(middle), _nodes[node].line(middle));\n\
    \        if (middle_better) std::swap(line, _nodes[node].line);\n        if (middle\
    \ == left) return node;\n\n        if (left_better != middle_better) {\n     \
    \       int child = add_line_node(_nodes[node].left, left, middle, std::move(line));\n\
    \            _nodes[node].left = child;\n        } else {\n            int child\
    \ = add_line_node(_nodes[node].right, middle, right, std::move(line));\n     \
    \       _nodes[node].right = child;\n        }\n        return node;\n    }\n\n\
    \    int add_segment_node(int node, T left, T right, T query_left, T query_right,\
    \ const Line& line) {\n        if (query_right <= left || right <= query_left)\
    \ return node;\n        if (query_left <= left && right <= query_right) {\n  \
    \          return add_line_node(node, left, right, line);\n        }\n       \
    \ if (node == -1) node = new_node();\n\n        T middle = std::midpoint(left,\
    \ right);\n        if (middle == left) return add_line_node(node, left, right,\
    \ line);\n        int left_child = add_segment_node(_nodes[node].left, left, middle,\
    \ query_left, query_right, line);\n        int right_child = add_segment_node(_nodes[node].right,\
    \ middle, right, query_left, query_right, line);\n        _nodes[node].left =\
    \ left_child;\n        _nodes[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    LiChaoTree() : _left(0), _right(0), _root(-1) {}\n\n\
    \    LiChaoTree(T left, T right) : _left(left), _right(right), _root(-1) {\n \
    \       assert(left <= right);\n    }\n\n    T left_bound() const {\n        return\
    \ _left;\n    }\n\n    T right_bound() const {\n        return _right;\n    }\n\
    \n    bool empty() const {\n        return _root == -1;\n    }\n\n    std::size_t\
    \ node_count() const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _root = -1;\n        _nodes.clear();\n    }\n\n    void add_line(T\
    \ slope, T intercept) {\n        assert(_left < _right);\n        _root = add_line_node(_root,\
    \ _left, _right, Line(slope, intercept));\n    }\n\n    void add_segment(T segment_left,\
    \ T segment_right, T slope, T intercept) {\n        assert(_left <= segment_left\
    \ && segment_left <= segment_right && segment_right <= _right);\n        if (segment_left\
    \ == segment_right) return;\n        _root = add_segment_node(_root, _left, _right,\
    \ segment_left, segment_right, Line(slope, intercept));\n    }\n\n    // Returns\
    \ nullopt when no inserted line covers x.\n    std::optional<value_type> query(T\
    \ x) const {\n        assert(_left <= x && x < _right);\n        std::optional<value_type>\
    \ result;\n        int node = _root;\n        T left = _left;\n        T right\
    \ = _right;\n        while (node != -1) {\n            if (_nodes[node].has_line)\
    \ {\n                value_type candidate = _nodes[node].line(x);\n          \
    \      if (!result || better(candidate, *result)) {\n                    result\
    \ = candidate;\n                }\n            }\n\n            T middle = std::midpoint(left,\
    \ right);\n            if (middle == left) break;\n            if (x < middle)\
    \ {\n                node = _nodes[node].left;\n                right = middle;\n\
    \            } else {\n                node = _nodes[node].right;\n          \
    \      left = middle;\n            }\n        }\n        return result;\n    }\n\
    \n    value_type get(T x) const {\n        std::optional<value_type> result =\
    \ query(x);\n        assert(result.has_value());\n        return result.value_or(value_type());\n\
    \    }\n};\n\ntemplate <std::signed_integral T>\nusing MinLiChaoTree = LiChaoTree<T,\
    \ LineOptimization::Minimize>;\n\ntemplate <std::signed_integral T>\nusing MaxLiChaoTree\
    \ = LiChaoTree<T, LineOptimization::Maximize>;\n\n}  // namespace convex\n}  //\
    \ namespace m1une\n\n\n#line 4 \"verify/convex/li_chao_tree.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 7 \"verify/convex/li_chao_tree.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#line 15 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
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
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/convex/li_chao_tree.test.cpp\"\
    \n\nnamespace {\n\nstruct SegmentLine {\n    int left;\n    int right;\n    long\
    \ long slope;\n    long long intercept;\n};\n\ntemplate <m1une::convex::LineOptimization\
    \ Objective>\nvoid check(const std::vector<SegmentLine>& lines) {\n    m1une::convex::LiChaoTree<long\
    \ long, Objective> tree(-64, 65);\n    for (const SegmentLine& line : lines) {\n\
    \        if (line.left == -64 && line.right == 65) {\n            tree.add_line(line.slope,\
    \ line.intercept);\n        } else {\n            tree.add_segment(\n        \
    \        line.left,\n                line.right,\n                line.slope,\n\
    \                line.intercept\n            );\n        }\n    }\n\n    for (long\
    \ long x = -64; x < 65; ++x) {\n        std::optional<__int128_t> expected;\n\
    \        for (const SegmentLine& line : lines) {\n            if (x < line.left\
    \ || line.right <= x) continue;\n            __int128_t value =\n            \
    \    __int128_t(line.slope) * x + line.intercept;\n            if (\n        \
    \        !expected\n                || (\n                    Objective\n    \
    \                    == m1une::convex::LineOptimization::Minimize\n          \
    \          ? value < *expected\n                    : *expected < value\n    \
    \            )\n            ) {\n                expected = value;\n         \
    \   }\n        }\n        assert(tree.query(x) == expected);\n        if (expected)\
    \ assert(tree.get(x) == *expected);\n    }\n}\n\nvoid test_randomized() {\n  \
    \  std::uint64_t state = 1013;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 3000; ++trial) {\n        int count = int(random()\
    \ % 50);\n        std::vector<SegmentLine> lines;\n        for (int index = 0;\
    \ index < count; ++index) {\n            int left = int(random() % 129) - 64;\n\
    \            int right = int(random() % 129) - 64;\n            if (right < left)\
    \ std::swap(left, right);\n            if (random() % 3 == 0) {\n            \
    \    left = -64;\n                right = 65;\n            }\n            lines.push_back(SegmentLine{\n\
    \                left,\n                right,\n                static_cast<long\
    \ long>(random() % 101) - 50,\n                static_cast<long long>(random()\
    \ % 201) - 100,\n            });\n        }\n        check<m1une::convex::LineOptimization::Minimize>(lines);\n\
    \        check<m1une::convex::LineOptimization::Maximize>(lines);\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\n \
    \   int line_count, query_count;\n    fast_input >> line_count >> query_count;\n\
    \    constexpr long long left = -1'000'000'000LL;\n    constexpr long long right\
    \ = 1'000'000'001LL;\n    m1une::convex::MinLiChaoTree<long long> tree(left, right);\n\
    \    for (int index = 0; index < line_count; ++index) {\n        long long slope,\
    \ intercept;\n        fast_input >> slope >> intercept;\n        tree.add_line(slope,\
    \ intercept);\n    }\n\n    while (query_count--) {\n        int type;\n     \
    \   fast_input >> type;\n        if (type == 0) {\n            long long slope,\
    \ intercept;\n            fast_input >> slope >> intercept;\n            tree.add_line(slope,\
    \ intercept);\n        } else {\n            long long x;\n            fast_input\
    \ >> x;\n            fast_output << static_cast<long long>(tree.get(x)) << '\\\
    n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n\
    #include \"../../convex/li_chao_tree.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <limits>\n\
    #include <optional>\n#include <vector>\n\nnamespace {\n\nstruct SegmentLine {\n\
    \    int left;\n    int right;\n    long long slope;\n    long long intercept;\n\
    };\n\ntemplate <m1une::convex::LineOptimization Objective>\nvoid check(const std::vector<SegmentLine>&\
    \ lines) {\n    m1une::convex::LiChaoTree<long long, Objective> tree(-64, 65);\n\
    \    for (const SegmentLine& line : lines) {\n        if (line.left == -64 &&\
    \ line.right == 65) {\n            tree.add_line(line.slope, line.intercept);\n\
    \        } else {\n            tree.add_segment(\n                line.left,\n\
    \                line.right,\n                line.slope,\n                line.intercept\n\
    \            );\n        }\n    }\n\n    for (long long x = -64; x < 65; ++x)\
    \ {\n        std::optional<__int128_t> expected;\n        for (const SegmentLine&\
    \ line : lines) {\n            if (x < line.left || line.right <= x) continue;\n\
    \            __int128_t value =\n                __int128_t(line.slope) * x +\
    \ line.intercept;\n            if (\n                !expected\n             \
    \   || (\n                    Objective\n                        == m1une::convex::LineOptimization::Minimize\n\
    \                    ? value < *expected\n                    : *expected < value\n\
    \                )\n            ) {\n                expected = value;\n     \
    \       }\n        }\n        assert(tree.query(x) == expected);\n        if (expected)\
    \ assert(tree.get(x) == *expected);\n    }\n}\n\nvoid test_randomized() {\n  \
    \  std::uint64_t state = 1013;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 3000; ++trial) {\n        int count = int(random()\
    \ % 50);\n        std::vector<SegmentLine> lines;\n        for (int index = 0;\
    \ index < count; ++index) {\n            int left = int(random() % 129) - 64;\n\
    \            int right = int(random() % 129) - 64;\n            if (right < left)\
    \ std::swap(left, right);\n            if (random() % 3 == 0) {\n            \
    \    left = -64;\n                right = 65;\n            }\n            lines.push_back(SegmentLine{\n\
    \                left,\n                right,\n                static_cast<long\
    \ long>(random() % 101) - 50,\n                static_cast<long long>(random()\
    \ % 201) - 100,\n            });\n        }\n        check<m1une::convex::LineOptimization::Minimize>(lines);\n\
    \        check<m1une::convex::LineOptimization::Maximize>(lines);\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\n \
    \   int line_count, query_count;\n    fast_input >> line_count >> query_count;\n\
    \    constexpr long long left = -1'000'000'000LL;\n    constexpr long long right\
    \ = 1'000'000'001LL;\n    m1une::convex::MinLiChaoTree<long long> tree(left, right);\n\
    \    for (int index = 0; index < line_count; ++index) {\n        long long slope,\
    \ intercept;\n        fast_input >> slope >> intercept;\n        tree.add_line(slope,\
    \ intercept);\n    }\n\n    while (query_count--) {\n        int type;\n     \
    \   fast_input >> type;\n        if (type == 0) {\n            long long slope,\
    \ intercept;\n            fast_input >> slope >> intercept;\n            tree.add_line(slope,\
    \ intercept);\n        } else {\n            long long x;\n            fast_input\
    \ >> x;\n            fast_output << static_cast<long long>(tree.get(x)) << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - convex/li_chao_tree.hpp
  - convex/convex_hull_trick.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/convex/li_chao_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/convex/li_chao_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/convex/li_chao_tree.test.cpp
- /verify/verify/convex/li_chao_tree.test.cpp.html
title: verify/convex/li_chao_tree.test.cpp
---
