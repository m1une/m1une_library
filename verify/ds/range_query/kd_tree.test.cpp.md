---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/kd_tree.hpp
    title: K-d Tree
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C
  bundledCode: "#line 1 \"verify/ds/range_query/kd_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C\"\n\n#line 1 \"ds/range_query/kd_tree.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <optional>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Static orthogonal range and nearest-neighbor queries in K dimensions.\ntemplate\
    \ <class T, std::size_t K>\nclass KdTree {\n    static_assert(K > 0);\n    static_assert(std::is_arithmetic_v<T>);\n\
    \    static_assert(!std::is_same_v<std::remove_cv_t<T>, bool>);\n\n   public:\n\
    \    using coordinate_type = T;\n    using point_type = std::array<T, K>;\n  \
    \  using distance_type =\n        std::conditional_t<std::is_integral_v<T>, __int128_t,\
    \ long double>;\n    static constexpr std::size_t dimension = K;\n\n    struct\
    \ Neighbor {\n        int index;\n        distance_type distance_squared;\n\n\
    \        friend bool operator==(const Neighbor&, const Neighbor&) = default;\n\
    \    };\n\n   private:\n    struct Node {\n        point_type minimum;\n     \
    \   point_type maximum;\n        int point_index = -1;\n        int left = -1;\n\
    \        int right = -1;\n        int subtree_size = 1;\n    };\n\n    std::vector<point_type>\
    \ _points;\n    std::vector<Node> _nodes;\n    int _root = -1;\n    int _node_count\
    \ = 0;\n\n    static distance_type squared_distance(\n        const point_type&\
    \ first,\n        const point_type& second\n    ) {\n        distance_type result\
    \ = 0;\n        for (std::size_t axis = 0; axis < K; axis++) {\n            distance_type\
    \ difference =\n                distance_type(first[axis]) - distance_type(second[axis]);\n\
    \            result += difference * difference;\n        }\n        return result;\n\
    \    }\n\n    distance_type box_distance(int node, const point_type& point) const\
    \ {\n        distance_type result = 0;\n        for (std::size_t axis = 0; axis\
    \ < K; axis++) {\n            distance_type difference = 0;\n            if (point[axis]\
    \ < _nodes[node].minimum[axis]) {\n                difference = distance_type(_nodes[node].minimum[axis])\n\
    \                    - distance_type(point[axis]);\n            } else if (_nodes[node].maximum[axis]\
    \ < point[axis]) {\n                difference = distance_type(point[axis])\n\
    \                    - distance_type(_nodes[node].maximum[axis]);\n          \
    \  }\n            result += difference * difference;\n        }\n        return\
    \ result;\n    }\n\n    int build_node(\n        std::vector<int>& order,\n  \
    \      int left,\n        int right\n    ) {\n        if (left == right) return\
    \ -1;\n\n        point_type minimum = _points[order[left]];\n        point_type\
    \ maximum = minimum;\n        for (int position = left + 1; position < right;\
    \ position++) {\n            const point_type& point = _points[order[position]];\n\
    \            for (std::size_t axis = 0; axis < K; axis++) {\n                if\
    \ (point[axis] < minimum[axis]) minimum[axis] = point[axis];\n               \
    \ if (maximum[axis] < point[axis]) maximum[axis] = point[axis];\n            }\n\
    \        }\n\n        std::size_t split_axis = 0;\n        distance_type maximum_extent\
    \ =\n            distance_type(maximum[0]) - distance_type(minimum[0]);\n    \
    \    for (std::size_t axis = 1; axis < K; axis++) {\n            distance_type\
    \ extent =\n                distance_type(maximum[axis]) - distance_type(minimum[axis]);\n\
    \            if (maximum_extent < extent) {\n                maximum_extent =\
    \ extent;\n                split_axis = axis;\n            }\n        }\n\n  \
    \      int middle = (left + right) / 2;\n        std::nth_element(\n         \
    \   order.begin() + left,\n            order.begin() + middle,\n            order.begin()\
    \ + right,\n            [&](int first, int second) {\n                if (_points[first][split_axis]\n\
    \                    < _points[second][split_axis]) return true;\n           \
    \     if (_points[second][split_axis]\n                    < _points[first][split_axis])\
    \ return false;\n                return first < second;\n            }\n     \
    \   );\n\n        int node = _node_count++;\n        _nodes[node].point_index\
    \ = order[middle];\n        _nodes[node].minimum = minimum;\n        _nodes[node].maximum\
    \ = maximum;\n        _nodes[node].left = build_node(order, left, middle);\n \
    \       _nodes[node].right = build_node(order, middle + 1, right);\n        _nodes[node].subtree_size\
    \ = 1;\n        if (_nodes[node].left != -1) {\n            _nodes[node].subtree_size\
    \ +=\n                _nodes[_nodes[node].left].subtree_size;\n        }\n   \
    \     if (_nodes[node].right != -1) {\n            _nodes[node].subtree_size +=\n\
    \                _nodes[_nodes[node].right].subtree_size;\n        }\n       \
    \ return node;\n    }\n\n    static bool contains(\n        const point_type&\
    \ point,\n        const point_type& lower,\n        const point_type& upper\n\
    \    ) {\n        for (std::size_t axis = 0; axis < K; axis++) {\n           \
    \ if (point[axis] < lower[axis] || !(point[axis] < upper[axis])) {\n         \
    \       return false;\n            }\n        }\n        return true;\n    }\n\
    \n    bool disjoint(\n        int node,\n        const point_type& lower,\n  \
    \      const point_type& upper\n    ) const {\n        for (std::size_t axis =\
    \ 0; axis < K; axis++) {\n            if (_nodes[node].maximum[axis] < lower[axis]\n\
    \                || !(_nodes[node].minimum[axis] < upper[axis])) {\n         \
    \       return true;\n            }\n        }\n        return false;\n    }\n\
    \n    bool covered(\n        int node,\n        const point_type& lower,\n   \
    \     const point_type& upper\n    ) const {\n        for (std::size_t axis =\
    \ 0; axis < K; axis++) {\n            if (_nodes[node].minimum[axis] < lower[axis]\n\
    \                || !(_nodes[node].maximum[axis] < upper[axis])) {\n         \
    \       return false;\n            }\n        }\n        return true;\n    }\n\
    \n    void collect_subtree(int node, std::vector<int>& result) const {\n     \
    \   if (node == -1) return;\n        result.push_back(_nodes[node].point_index);\n\
    \        collect_subtree(_nodes[node].left, result);\n        collect_subtree(_nodes[node].right,\
    \ result);\n    }\n\n    void range_search_node(\n        int node,\n        const\
    \ point_type& lower,\n        const point_type& upper,\n        std::vector<int>&\
    \ result\n    ) const {\n        if (node == -1 || disjoint(node, lower, upper))\
    \ return;\n        if (covered(node, lower, upper)) {\n            collect_subtree(node,\
    \ result);\n            return;\n        }\n        int point_index = _nodes[node].point_index;\n\
    \        if (contains(_points[point_index], lower, upper)) {\n            result.push_back(point_index);\n\
    \        }\n        range_search_node(_nodes[node].left, lower, upper, result);\n\
    \        range_search_node(_nodes[node].right, lower, upper, result);\n    }\n\
    \n    int count_node(\n        int node,\n        const point_type& lower,\n \
    \       const point_type& upper\n    ) const {\n        if (node == -1 || disjoint(node,\
    \ lower, upper)) return 0;\n        if (covered(node, lower, upper)) return _nodes[node].subtree_size;\n\
    \        int result = int(contains(\n            _points[_nodes[node].point_index],\n\
    \            lower,\n            upper\n        ));\n        result += count_node(_nodes[node].left,\
    \ lower, upper);\n        result += count_node(_nodes[node].right, lower, upper);\n\
    \        return result;\n    }\n\n    static bool better(const Neighbor& first,\
    \ const Neighbor& second) {\n        if (first.distance_squared != second.distance_squared)\
    \ {\n            return first.distance_squared < second.distance_squared;\n  \
    \      }\n        return first.index < second.index;\n    }\n\n    void nearest_node(\n\
    \        int node,\n        const point_type& query,\n        std::optional<Neighbor>&\
    \ best\n    ) const {\n        if (node == -1) return;\n        distance_type\
    \ bound = box_distance(node, query);\n        if (best && best->distance_squared\
    \ < bound) return;\n\n        int point_index = _nodes[node].point_index;\n  \
    \      Neighbor candidate{\n            point_index,\n            squared_distance(_points[point_index],\
    \ query)\n        };\n        if (!best || better(candidate, *best)) best = candidate;\n\
    \n        int first = _nodes[node].left;\n        int second = _nodes[node].right;\n\
    \        if (first != -1 && second != -1\n            && box_distance(second,\
    \ query) < box_distance(first, query)) {\n            std::swap(first, second);\n\
    \        }\n        nearest_node(first, query, best);\n        nearest_node(second,\
    \ query, best);\n    }\n\n    using HeapEntry = std::pair<distance_type, int>;\n\
    \n    void k_nearest_node(\n        int node,\n        const point_type& query,\n\
    \        int k,\n        std::priority_queue<HeapEntry>& heap\n    ) const {\n\
    \        if (node == -1) return;\n        distance_type bound = box_distance(node,\
    \ query);\n        if (int(heap.size()) == k && heap.top().first < bound) return;\n\
    \n        int point_index = _nodes[node].point_index;\n        HeapEntry candidate\
    \ = {\n            squared_distance(_points[point_index], query),\n          \
    \  point_index\n        };\n        if (int(heap.size()) < k) {\n            heap.push(candidate);\n\
    \        } else if (candidate < heap.top()) {\n            heap.pop();\n     \
    \       heap.push(candidate);\n        }\n\n        int first = _nodes[node].left;\n\
    \        int second = _nodes[node].right;\n        if (first != -1 && second !=\
    \ -1\n            && box_distance(second, query) < box_distance(first, query))\
    \ {\n            std::swap(first, second);\n        }\n        k_nearest_node(first,\
    \ query, k, heap);\n        k_nearest_node(second, query, k, heap);\n    }\n\n\
    \    static void assert_valid_box(\n        const point_type& lower,\n       \
    \ const point_type& upper\n    ) {\n        for (std::size_t axis = 0; axis <\
    \ K; axis++) {\n            assert(!(upper[axis] < lower[axis]));\n        }\n\
    \    }\n\n   public:\n    KdTree() = default;\n\n    explicit KdTree(const std::vector<point_type>&\
    \ points) {\n        build(points);\n    }\n\n    void build(const std::vector<point_type>&\
    \ points) {\n        assert(points.size()\n            <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        _points = points;\n        _nodes.clear();\n        _nodes.resize(points.size());\n\
    \        _root = -1;\n        _node_count = 0;\n        std::vector<int> order(points.size());\n\
    \        for (int index = 0; index < int(points.size()); index++) {\n        \
    \    order[index] = index;\n        }\n        _root = build_node(order, 0, int(order.size()));\n\
    \    }\n\n    int size() const {\n        return int(_points.size());\n    }\n\
    \n    bool empty() const {\n        return _points.empty();\n    }\n\n    const\
    \ point_type& get(int index) const {\n        assert(0 <= index && index < size());\n\
    \        return _points[index];\n    }\n\n    const point_type& operator[](int\
    \ index) const {\n        return get(index);\n    }\n\n    std::vector<int> range_search(\n\
    \        const point_type& lower,\n        const point_type& upper\n    ) const\
    \ {\n        assert_valid_box(lower, upper);\n        std::vector<int> result;\n\
    \        range_search_node(_root, lower, upper, result);\n        return result;\n\
    \    }\n\n    int count(\n        const point_type& lower,\n        const point_type&\
    \ upper\n    ) const {\n        assert_valid_box(lower, upper);\n        return\
    \ count_node(_root, lower, upper);\n    }\n\n    std::optional<Neighbor> nearest(const\
    \ point_type& query) const {\n        std::optional<Neighbor> result;\n      \
    \  nearest_node(_root, query, result);\n        return result;\n    }\n\n    std::vector<Neighbor>\
    \ k_nearest(\n        const point_type& query,\n        int k\n    ) const {\n\
    \        assert(0 <= k && k <= size());\n        if (k == 0) return {};\n    \
    \    std::priority_queue<HeapEntry> heap;\n        k_nearest_node(_root, query,\
    \ k, heap);\n        std::vector<Neighbor> result;\n        result.reserve(k);\n\
    \        while (!heap.empty()) {\n            result.push_back(Neighbor{heap.top().second,\
    \ heap.top().first});\n            heap.pop();\n        }\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n} \
    \ // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/kd_tree.test.cpp\"\n\
    \n#line 8 \"verify/ds/range_query/kd_tree.test.cpp\"\n#include <cstdint>\n#line\
    \ 10 \"verify/ds/range_query/kd_tree.test.cpp\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#line 6 \"utilities/fast_io.hpp\"\n#include <cerrno>\n#include <charconv>\n\
    #line 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include\
    \ <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/ds/range_query/kd_tree.test.cpp\"\
    \n\nnamespace {\n\nusing RandomTree = m1une::ds::KdTree<long long, 3>;\nusing\
    \ RandomPoint = RandomTree::point_type;\n\nlong long distance_squared(\n    const\
    \ RandomPoint& first,\n    const RandomPoint& second\n) {\n    long long result\
    \ = 0;\n    for (int axis = 0; axis < 3; axis++) {\n        long long difference\
    \ = first[axis] - second[axis];\n        result += difference * difference;\n\
    \    }\n    return result;\n}\n\nvoid fixed_test() {\n    using Tree = m1une::ds::KdTree<int,\
    \ 2>;\n    using Point = Tree::point_type;\n\n    Tree empty;\n    Point origin\
    \ = {0, 0};\n    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.range_search(origin,\
    \ origin).empty());\n    assert(empty.count(origin, origin) == 0);\n    assert(!empty.nearest(origin));\n\
    \    assert(empty.k_nearest(origin, 0).empty());\n\n    std::vector<Point> points\
    \ = {\n        Point{0, 0},\n        Point{2, 0},\n        Point{0, 2},\n    \
    \    Point{0, 0},\n        Point{-2, 0}\n    };\n    Tree tree(points);\n    assert(tree.size()\
    \ == 5);\n    assert(tree[3] == points[3]);\n\n    Point lower = {-1, -1};\n \
    \   Point upper = {1, 1};\n    std::vector<int> indices = tree.range_search(lower,\
    \ upper);\n    std::sort(indices.begin(), indices.end());\n    assert(indices\
    \ == std::vector<int>({0, 3}));\n    assert(tree.count(lower, upper) == 2);\n\n\
    \    Point query = {1, 0};\n    auto nearest = tree.nearest(query);\n    assert(nearest.has_value());\n\
    \    assert(nearest->index == 0);\n    assert(nearest->distance_squared == 1);\n\
    \n    std::vector<Tree::Neighbor> neighbors = tree.k_nearest(query, 3);\n    assert(neighbors.size()\
    \ == 3);\n    Tree::Neighbor first_expected{0, 1};\n    Tree::Neighbor second_expected{1,\
    \ 1};\n    Tree::Neighbor third_expected{3, 1};\n    assert(neighbors[0] == first_expected);\n\
    \    assert(neighbors[1] == second_expected);\n    assert(neighbors[2] == third_expected);\n\
    \n    tree.build({Point{10, 20}});\n    assert(tree.size() == 1);\n    assert(tree.nearest(origin)->index\
    \ == 0);\n    assert(tree.nearest(origin)->distance_squared == 500);\n\n    using\
    \ FloatTree = m1une::ds::KdTree<double, 2>;\n    using FloatPoint = FloatTree::point_type;\n\
    \    FloatPoint floating_first = {-0.5, 1.25};\n    FloatPoint floating_second\
    \ = {2.0, 3.0};\n    std::vector<FloatPoint> floating_points = {\n        floating_first,\n\
    \        floating_second\n    };\n    FloatTree floating_tree(floating_points);\n\
    \    FloatPoint floating_query = {0.0, 1.0};\n    auto floating_nearest = floating_tree.nearest(floating_query);\n\
    \    assert(floating_nearest->index == 0);\n    assert(floating_nearest->distance_squared\
    \ == 0.3125L);\n}\n\nvoid randomized_test() {\n    std::uint64_t state = 123456789123456789ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 300; trial++) {\n        int n = int(random() % 50);\n        std::vector<RandomPoint>\
    \ points(n);\n        for (RandomPoint& point : points) {\n            for (long\
    \ long& coordinate : point) {\n                coordinate = static_cast<long long>(random()\
    \ % 31) - 15;\n            }\n        }\n\n        RandomTree tree(points);\n\
    \        assert(tree.size() == n);\n        assert(tree.empty() == points.empty());\n\
    \        for (int index = 0; index < n; index++) {\n            assert(tree[index]\
    \ == points[index]);\n        }\n\n        for (int query_index = 0; query_index\
    \ < 100; query_index++) {\n            RandomPoint lower;\n            RandomPoint\
    \ upper;\n            RandomPoint query;\n            for (int axis = 0; axis\
    \ < 3; axis++) {\n                lower[axis] = static_cast<long long>(random()\
    \ % 41) - 20;\n                upper[axis] = static_cast<long long>(random() %\
    \ 41) - 20;\n                if (upper[axis] < lower[axis]) {\n              \
    \      std::swap(lower[axis], upper[axis]);\n                }\n             \
    \   query[axis] = static_cast<long long>(random() % 41) - 20;\n            }\n\
    \n            std::vector<int> expected_range;\n            std::vector<RandomTree::Neighbor>\
    \ expected_neighbors;\n            for (int index = 0; index < n; index++) {\n\
    \                bool inside = true;\n                for (int axis = 0; axis\
    \ < 3; axis++) {\n                    inside &= lower[axis] <= points[index][axis]\n\
    \                        && points[index][axis] < upper[axis];\n             \
    \   }\n                if (inside) expected_range.push_back(index);\n        \
    \        expected_neighbors.push_back(RandomTree::Neighbor{\n                \
    \    index,\n                    distance_squared(points[index], query)\n    \
    \            });\n            }\n\n            std::vector<int> actual_range =\
    \ tree.range_search(lower, upper);\n            std::sort(actual_range.begin(),\
    \ actual_range.end());\n            assert(actual_range == expected_range);\n\
    \            assert(tree.count(lower, upper) == int(expected_range.size()));\n\
    \n            std::sort(\n                expected_neighbors.begin(),\n      \
    \          expected_neighbors.end(),\n                [](const auto& first, const\
    \ auto& second) {\n                    if (first.distance_squared != second.distance_squared)\
    \ {\n                        return first.distance_squared < second.distance_squared;\n\
    \                    }\n                    return first.index < second.index;\n\
    \                }\n            );\n            auto nearest = tree.nearest(query);\n\
    \            if (n == 0) {\n                assert(!nearest);\n            } else\
    \ {\n                assert(nearest.has_value());\n                assert(*nearest\
    \ == expected_neighbors[0]);\n            }\n\n            int k = int(random()\
    \ % (n + 1));\n            std::vector<RandomTree::Neighbor> actual_neighbors\
    \ =\n                tree.k_nearest(query, k);\n            expected_neighbors.resize(k);\n\
    \            assert(actual_neighbors == expected_neighbors);\n        }\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    fixed_test();\n    randomized_test();\n\
    \n    using Tree = m1une::ds::KdTree<long long, 2>;\n    using Point = Tree::point_type;\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n;\n    fast_input >> n;\n    std::vector<Point> points(n);\n\
    \    for (Point& point : points) fast_input >> point[0] >> point[1];\n    Tree\
    \ tree(points);\n\n    int query_count;\n    fast_input >> query_count;\n    while\
    \ (query_count--) {\n        long long left, right, lower, upper;\n        fast_input\
    \ >> left >> right >> lower >> upper;\n        Point box_lower = {left, lower};\n\
    \        Point box_upper = {right + 1, upper + 1};\n        std::vector<int> result\
    \ = tree.range_search(box_lower, box_upper);\n        std::sort(result.begin(),\
    \ result.end());\n        for (int index : result) fast_output << index << '\\\
    n';\n        fast_output << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C\"\n\n\
    #include \"../../../ds/range_query/kd_tree.hpp\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n\nnamespace {\n\nusing RandomTree = m1une::ds::KdTree<long\
    \ long, 3>;\nusing RandomPoint = RandomTree::point_type;\n\nlong long distance_squared(\n\
    \    const RandomPoint& first,\n    const RandomPoint& second\n) {\n    long long\
    \ result = 0;\n    for (int axis = 0; axis < 3; axis++) {\n        long long difference\
    \ = first[axis] - second[axis];\n        result += difference * difference;\n\
    \    }\n    return result;\n}\n\nvoid fixed_test() {\n    using Tree = m1une::ds::KdTree<int,\
    \ 2>;\n    using Point = Tree::point_type;\n\n    Tree empty;\n    Point origin\
    \ = {0, 0};\n    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.range_search(origin,\
    \ origin).empty());\n    assert(empty.count(origin, origin) == 0);\n    assert(!empty.nearest(origin));\n\
    \    assert(empty.k_nearest(origin, 0).empty());\n\n    std::vector<Point> points\
    \ = {\n        Point{0, 0},\n        Point{2, 0},\n        Point{0, 2},\n    \
    \    Point{0, 0},\n        Point{-2, 0}\n    };\n    Tree tree(points);\n    assert(tree.size()\
    \ == 5);\n    assert(tree[3] == points[3]);\n\n    Point lower = {-1, -1};\n \
    \   Point upper = {1, 1};\n    std::vector<int> indices = tree.range_search(lower,\
    \ upper);\n    std::sort(indices.begin(), indices.end());\n    assert(indices\
    \ == std::vector<int>({0, 3}));\n    assert(tree.count(lower, upper) == 2);\n\n\
    \    Point query = {1, 0};\n    auto nearest = tree.nearest(query);\n    assert(nearest.has_value());\n\
    \    assert(nearest->index == 0);\n    assert(nearest->distance_squared == 1);\n\
    \n    std::vector<Tree::Neighbor> neighbors = tree.k_nearest(query, 3);\n    assert(neighbors.size()\
    \ == 3);\n    Tree::Neighbor first_expected{0, 1};\n    Tree::Neighbor second_expected{1,\
    \ 1};\n    Tree::Neighbor third_expected{3, 1};\n    assert(neighbors[0] == first_expected);\n\
    \    assert(neighbors[1] == second_expected);\n    assert(neighbors[2] == third_expected);\n\
    \n    tree.build({Point{10, 20}});\n    assert(tree.size() == 1);\n    assert(tree.nearest(origin)->index\
    \ == 0);\n    assert(tree.nearest(origin)->distance_squared == 500);\n\n    using\
    \ FloatTree = m1une::ds::KdTree<double, 2>;\n    using FloatPoint = FloatTree::point_type;\n\
    \    FloatPoint floating_first = {-0.5, 1.25};\n    FloatPoint floating_second\
    \ = {2.0, 3.0};\n    std::vector<FloatPoint> floating_points = {\n        floating_first,\n\
    \        floating_second\n    };\n    FloatTree floating_tree(floating_points);\n\
    \    FloatPoint floating_query = {0.0, 1.0};\n    auto floating_nearest = floating_tree.nearest(floating_query);\n\
    \    assert(floating_nearest->index == 0);\n    assert(floating_nearest->distance_squared\
    \ == 0.3125L);\n}\n\nvoid randomized_test() {\n    std::uint64_t state = 123456789123456789ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 300; trial++) {\n        int n = int(random() % 50);\n        std::vector<RandomPoint>\
    \ points(n);\n        for (RandomPoint& point : points) {\n            for (long\
    \ long& coordinate : point) {\n                coordinate = static_cast<long long>(random()\
    \ % 31) - 15;\n            }\n        }\n\n        RandomTree tree(points);\n\
    \        assert(tree.size() == n);\n        assert(tree.empty() == points.empty());\n\
    \        for (int index = 0; index < n; index++) {\n            assert(tree[index]\
    \ == points[index]);\n        }\n\n        for (int query_index = 0; query_index\
    \ < 100; query_index++) {\n            RandomPoint lower;\n            RandomPoint\
    \ upper;\n            RandomPoint query;\n            for (int axis = 0; axis\
    \ < 3; axis++) {\n                lower[axis] = static_cast<long long>(random()\
    \ % 41) - 20;\n                upper[axis] = static_cast<long long>(random() %\
    \ 41) - 20;\n                if (upper[axis] < lower[axis]) {\n              \
    \      std::swap(lower[axis], upper[axis]);\n                }\n             \
    \   query[axis] = static_cast<long long>(random() % 41) - 20;\n            }\n\
    \n            std::vector<int> expected_range;\n            std::vector<RandomTree::Neighbor>\
    \ expected_neighbors;\n            for (int index = 0; index < n; index++) {\n\
    \                bool inside = true;\n                for (int axis = 0; axis\
    \ < 3; axis++) {\n                    inside &= lower[axis] <= points[index][axis]\n\
    \                        && points[index][axis] < upper[axis];\n             \
    \   }\n                if (inside) expected_range.push_back(index);\n        \
    \        expected_neighbors.push_back(RandomTree::Neighbor{\n                \
    \    index,\n                    distance_squared(points[index], query)\n    \
    \            });\n            }\n\n            std::vector<int> actual_range =\
    \ tree.range_search(lower, upper);\n            std::sort(actual_range.begin(),\
    \ actual_range.end());\n            assert(actual_range == expected_range);\n\
    \            assert(tree.count(lower, upper) == int(expected_range.size()));\n\
    \n            std::sort(\n                expected_neighbors.begin(),\n      \
    \          expected_neighbors.end(),\n                [](const auto& first, const\
    \ auto& second) {\n                    if (first.distance_squared != second.distance_squared)\
    \ {\n                        return first.distance_squared < second.distance_squared;\n\
    \                    }\n                    return first.index < second.index;\n\
    \                }\n            );\n            auto nearest = tree.nearest(query);\n\
    \            if (n == 0) {\n                assert(!nearest);\n            } else\
    \ {\n                assert(nearest.has_value());\n                assert(*nearest\
    \ == expected_neighbors[0]);\n            }\n\n            int k = int(random()\
    \ % (n + 1));\n            std::vector<RandomTree::Neighbor> actual_neighbors\
    \ =\n                tree.k_nearest(query, k);\n            expected_neighbors.resize(k);\n\
    \            assert(actual_neighbors == expected_neighbors);\n        }\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    fixed_test();\n    randomized_test();\n\
    \n    using Tree = m1une::ds::KdTree<long long, 2>;\n    using Point = Tree::point_type;\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n;\n    fast_input >> n;\n    std::vector<Point> points(n);\n\
    \    for (Point& point : points) fast_input >> point[0] >> point[1];\n    Tree\
    \ tree(points);\n\n    int query_count;\n    fast_input >> query_count;\n    while\
    \ (query_count--) {\n        long long left, right, lower, upper;\n        fast_input\
    \ >> left >> right >> lower >> upper;\n        Point box_lower = {left, lower};\n\
    \        Point box_upper = {right + 1, upper + 1};\n        std::vector<int> result\
    \ = tree.range_search(box_lower, box_upper);\n        std::sort(result.begin(),\
    \ result.end());\n        for (int index : result) fast_output << index << '\\\
    n';\n        fast_output << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/kd_tree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/kd_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 14:00:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/kd_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/kd_tree.test.cpp
- /verify/verify/ds/range_query/kd_tree.test.cpp.html
title: verify/ds/range_query/kd_tree.test.cpp
---
