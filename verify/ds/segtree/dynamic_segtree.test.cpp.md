---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree.hpp
    title: Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#line 1 \"ds/segtree/dynamic_segtree.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n\
    #include <limits>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\n\
    #line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing dynamic_size_type\
    \ = std::make_unsigned_t<Index>;\n\ntemplate <std::integral Index>\nconstexpr\
    \ dynamic_size_type<Index> dynamic_distance(Index left, Index right) {\n    return\
    \ static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
    }\n\ntemplate <class Monoid, class Size>\ntypename Monoid::value_type monoid_repeat(typename\
    \ Monoid::value_type value, Size count) {\n    typename Monoid::value_type result\
    \ = Monoid::id();\n    while (count != 0) {\n        if (count & 1) result = Monoid::op(result,\
    \ value);\n        count >>= 1;\n        if (count != 0) value = Monoid::op(value,\
    \ value);\n    }\n    return result;\n}\n\ntemplate <class ActedMonoid>\ntypename\
    \ ActedMonoid::value_type dynamic_mapping(\n    const typename ActedMonoid::operator_type&\
    \ f,\n    const typename ActedMonoid::value_type& value\n) {\n    using F = typename\
    \ ActedMonoid::operator_type;\n    using T = typename ActedMonoid::value_type;\n\
    \    if constexpr (requires(F g, T x, long long ord) { ActedMonoid::mapping(g,\
    \ x, ord); }) {\n        return ActedMonoid::mapping(f, value, 0);\n    } else\
    \ {\n        return ActedMonoid::mapping(f, value);\n    }\n}\n\ntemplate <class\
    \ ActedMonoid, class Size>\ntypename ActedMonoid::operator_type dynamic_shift(\n\
    \    const typename ActedMonoid::operator_type& f,\n    Size offset\n) {\n   \
    \ using F = typename ActedMonoid::operator_type;\n    if constexpr (requires(F\
    \ g, long long ord) { ActedMonoid::op_shift(g, ord); }) {\n        assert(offset\
    \ <= static_cast<Size>(std::numeric_limits<long long>::max()));\n        return\
    \ ActedMonoid::op_shift(f, static_cast<long long>(offset));\n    } else {\n  \
    \      return f;\n    }\n}\n\ntemplate <class Monoid, std::integral Index>\nclass\
    \ UniformMonoidDomain {\n   public:\n    using T = typename Monoid::value_type;\n\
    \    using size_type = dynamic_size_type<Index>;\n\n   private:\n    struct Level\
    \ {\n        size_type small_length;\n        T small_value;\n        T large_value;\n\
    \    };\n\n    Index _left;\n    Index _right;\n    T _initial_value;\n    std::vector<Level>\
    \ _levels;\n\n   public:\n    UniformMonoidDomain(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        size_type n = size();\n        constexpr\
    \ int digits = std::numeric_limits<size_type>::digits;\n        _levels.reserve(digits\
    \ + 1);\n        for (int depth = 0; depth <= digits; depth++) {\n           \
    \ size_type small = depth == digits ? 0 : n >> depth;\n            size_type large\
    \ = small;\n            if (depth != 0) {\n                bool has_remainder;\n\
    \                if (depth == digits) {\n                    has_remainder = n\
    \ != 0;\n                } else {\n                    size_type mask = (size_type(1)\
    \ << depth) - 1;\n                    has_remainder = (n & mask) != 0;\n     \
    \           }\n                if (has_remainder) large++;\n            }\n  \
    \          _levels.push_back(Level{\n                small,\n                monoid_repeat<Monoid>(_initial_value,\
    \ small),\n                monoid_repeat<Monoid>(_initial_value, large),\n   \
    \         });\n        }\n    }\n\n    Index left_bound() const {\n        return\
    \ _left;\n    }\n\n    Index right_bound() const {\n        return _right;\n \
    \   }\n\n    size_type size() const {\n        return dynamic_distance(_left,\
    \ _right);\n    }\n\n    bool empty() const {\n        return _left == _right;\n\
    \    }\n\n    const T& initial_value() const {\n        return _initial_value;\n\
    \    }\n\n    const T& default_product(int depth, Index left, Index right) const\
    \ {\n        assert(0 <= depth && depth < int(_levels.size()));\n        const\
    \ Level& level = _levels[depth];\n        size_type length = dynamic_distance(left,\
    \ right);\n        if (length == level.small_length) return level.small_value;\n\
    \        assert(length == level.small_length + 1);\n        return level.large_value;\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 16 \"ds/segtree/dynamic_segtree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// A sparse segment tree over an integral half-open\
    \ interval.\n// Nodes are allocated from a contiguous pool only when a position\
    \ is touched.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral Index =\
    \ long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct DynamicSegtree\
    \ {\n    using T = typename Monoid::value_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        int left;\n        int right;\n\n        Node()\
    \ : val(Monoid::id()), left(0), right(0) {}\n    };\n\n    static constexpr int\
    \ path_capacity = std::numeric_limits<size_type>::digits + 1;\n\n    detail::UniformMonoidDomain<Monoid,\
    \ Index> _domain;\n    int _root;\n    std::vector<Node> _nodes;\n\n    int new_node()\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    const T& value(int t, Index left, Index right, int depth) const {\n    \
    \    if (t) return _nodes[t].val;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void update(int t, Index left, Index right, int\
    \ depth) {\n        Index middle = std::midpoint(left, right);\n        _nodes[t].val\
    \ = Monoid::op(\n            value(_nodes[t].left, left, middle, depth + 1),\n\
    \            value(_nodes[t].right, middle, right, depth + 1)\n        );\n  \
    \  }\n\n    T prod_node(int t, Index l, Index r, int depth, Index ql, Index qr)\
    \ const {\n        if (qr <= l || r <= ql) return Monoid::id();\n        if (ql\
    \ <= l && r <= qr) return value(t, l, r, depth);\n        Index m = std::midpoint(l,\
    \ r);\n        return Monoid::op(\n            prod_node(t ? _nodes[t].left :\
    \ 0, l, m, depth + 1, ql, qr),\n            prod_node(t ? _nodes[t].right : 0,\
    \ m, r, depth + 1, ql, qr)\n        );\n    }\n\n    template <class F>\n    Index\
    \ max_right_node(\n        int t,\n        Index l,\n        Index r,\n      \
    \  int depth,\n        Index ql,\n        T& sm,\n        F& f\n    ) const {\n\
    \        if (r <= ql) return r;\n        if (ql <= l) {\n            T next =\
    \ Monoid::op(sm, value(t, l, r, depth));\n            if (f(next)) {\n       \
    \         sm = std::move(next);\n                return r;\n            }\n  \
    \          Index m = std::midpoint(l, r);\n            if (m == l) return l;\n\
    \        }\n        Index m = std::midpoint(l, r);\n        Index res = max_right_node(\n\
    \            t ? _nodes[t].left : 0,\n            l,\n            m,\n       \
    \     depth + 1,\n            ql,\n            sm,\n            f\n        );\n\
    \        if (res < m) return res;\n        return max_right_node(\n          \
    \  t ? _nodes[t].right : 0,\n            m,\n            r,\n            depth\
    \ + 1,\n            ql,\n            sm,\n            f\n        );\n    }\n\n\
    \    template <class F>\n    Index min_left_node(\n        int t,\n        Index\
    \ l,\n        Index r,\n        int depth,\n        Index qr,\n        T& sm,\n\
    \        F& f\n    ) const {\n        if (qr <= l) return l;\n        if (r <=\
    \ qr) {\n            T next = Monoid::op(value(t, l, r, depth), sm);\n       \
    \     if (f(next)) {\n                sm = std::move(next);\n                return\
    \ l;\n            }\n            Index m = std::midpoint(l, r);\n            if\
    \ (m == l) return r;\n        }\n        Index m = std::midpoint(l, r);\n    \
    \    Index res = min_left_node(\n            t ? _nodes[t].right : 0,\n      \
    \      m,\n            r,\n            depth + 1,\n            qr,\n         \
    \   sm,\n            f\n        );\n        if (m < res) return res;\n       \
    \ return min_left_node(\n            t ? _nodes[t].left : 0,\n            l,\n\
    \            m,\n            depth + 1,\n            qr,\n            sm,\n  \
    \          f\n        );\n    }\n\n   public:\n    // Constructs an empty tree\
    \ over [0, 0).\n    DynamicSegtree() : DynamicSegtree(Index(0), Index(0)) {}\n\
    \n    // Constructs a tree over [0, n).\n    explicit DynamicSegtree(Index n)\
    \ : DynamicSegtree(Index(0), n) {\n        if constexpr (std::signed_integral<Index>)\
    \ assert(Index(0) <= n);\n    }\n\n    // Constructs a tree over [left, right).\n\
    \    DynamicSegtree(Index left, Index right)\n        : DynamicSegtree(left, right,\
    \ Monoid::id()) {}\n\n    // Constructs a tree over [left, right) with every coordinate\
    \ initialized to\n    // `initial_value`.\n    DynamicSegtree(Index left, Index\
    \ right, T initial_value)\n        : _domain(left, right, std::move(initial_value)),\
    \ _root(0), _nodes(1) {}\n\n    // Returns the number of coordinates in the domain.\n\
    \    size_type size() const {\n        return _domain.size();\n    }\n\n    //\
    \ Returns whether the coordinate domain is empty.\n    bool empty() const {\n\
    \        return _domain.empty();\n    }\n\n    // Returns the left endpoint of\
    \ the coordinate domain.\n    Index left_bound() const {\n        return _domain.left_bound();\n\
    \    }\n\n    // Returns the right endpoint of the coordinate domain.\n    Index\
    \ right_bound() const {\n        return _domain.right_bound();\n    }\n\n    //\
    \ Returns the value assigned to untouched coordinates.\n    const T& initial_value()\
    \ const {\n        return _domain.initial_value();\n    }\n\n    // Reserves space\
    \ for `node_capacity` allocated nodes.\n    void reserve(std::size_t node_capacity)\
    \ {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _nodes.reserve(node_capacity + 1);\n    }\n\n    // Returns the number\
    \ of allocated nodes, excluding the sentinel.\n    std::size_t node_count() const\
    \ {\n        return _nodes.size() - 1;\n    }\n\n    // Restores every coordinate\
    \ to the initial value while preserving capacity.\n    void clear() {\n      \
    \  _root = 0;\n        _nodes.resize(1);\n    }\n\n    // Sets the value at coordinate\
    \ `p` to `x`.\n    void set(Index p, T x) {\n        assert(left_bound() <= p\
    \ && p < right_bound());\n        if (!_root) _root = new_node();\n\n        std::array<int,\
    \ path_capacity> path;\n        std::array<Index, path_capacity> path_left;\n\
    \        std::array<Index, path_capacity> path_right;\n        int depth = 0;\n\
    \        int t = _root;\n        Index l = left_bound();\n        Index r = right_bound();\n\
    \n        while (true) {\n            assert(depth < path_capacity);\n       \
    \     path[depth] = t;\n            path_left[depth] = l;\n            path_right[depth]\
    \ = r;\n            depth++;\n            Index m = std::midpoint(l, r);\n   \
    \         if (m == l) break;\n\n            if (p < m) {\n                int\
    \ child = _nodes[t].left;\n                if (!child) {\n                   \
    \ child = new_node();\n                    _nodes[t].left = child;\n         \
    \       }\n                t = child;\n                r = m;\n            } else\
    \ {\n                int child = _nodes[t].right;\n                if (!child)\
    \ {\n                    child = new_node();\n                    _nodes[t].right\
    \ = child;\n                }\n                t = child;\n                l =\
    \ m;\n            }\n        }\n\n        _nodes[t].val = std::move(x);\n    \
    \    for (int i = depth - 2; i >= 0; i--) {\n            update(path[i], path_left[i],\
    \ path_right[i], i);\n        }\n    }\n\n    // Returns the value at coordinate\
    \ `p`.\n    T get(Index p) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        int t = _root;\n        Index l = left_bound();\n        Index r = right_bound();\n\
    \        int depth = 0;\n\n        while (t) {\n            Index m = std::midpoint(l,\
    \ r);\n            if (m == l) return value(t, l, r, depth);\n            if (p\
    \ < m) {\n                t = _nodes[t].left;\n                r = m;\n      \
    \      } else {\n                t = _nodes[t].right;\n                l = m;\n\
    \            }\n            depth++;\n        }\n        return initial_value();\n\
    \    }\n\n    // Returns the value at coordinate `p`.\n    T operator[](Index\
    \ p) const {\n        return get(p);\n    }\n\n    // Returns the monoid product\
    \ over [l, r).\n    T prod(Index l, Index r) const {\n        assert(left_bound()\
    \ <= l && l <= r && r <= right_bound());\n        if (l == r) return Monoid::id();\n\
    \        return prod_node(_root, left_bound(), right_bound(), 0, l, r);\n    }\n\
    \n    // Returns the monoid product over the entire coordinate domain.\n    T\
    \ all_prod() const {\n        return value(_root, left_bound(), right_bound(),\
    \ 0);\n    }\n\n    // Finds the largest r such that f(prod(l, r)) is true.\n\
    \    template <class F>\n    Index max_right(Index l, F f) const {\n        assert(left_bound()\
    \ <= l && l <= right_bound());\n        assert(f(Monoid::id()));\n        if (l\
    \ == right_bound()) return right_bound();\n        T sm = Monoid::id();\n    \
    \    return max_right_node(\n            _root,\n            left_bound(),\n \
    \           right_bound(),\n            0,\n            l,\n            sm,\n\
    \            f\n        );\n    }\n\n    // Finds the smallest l such that f(prod(l,\
    \ r)) is true.\n    template <class F>\n    Index min_left(Index r, F f) const\
    \ {\n        assert(left_bound() <= r && r <= right_bound());\n        assert(f(Monoid::id()));\n\
    \        if (r == left_bound()) return left_bound();\n        T sm = Monoid::id();\n\
    \        return min_left_node(\n            _root,\n            left_bound(),\n\
    \            right_bound(),\n            0,\n            r,\n            sm,\n\
    \            f\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n#include <cstdint>\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n#include <cstdio>\n\
    #include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\
    \n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n   \
    \ using value_type = T;\n\n    // Returns the identity element for addition, which\
    \ is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    //\
    \ Returns the sum of a and b.\n    static constexpr T op(const T& a, const T&\
    \ b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T& x)\
    \ {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 14 \"verify/ds/segtree/dynamic_segtree.test.cpp\"\n\nnamespace\
    \ {\n\nstruct Concat {\n    using value_type = std::string;\n\n    static value_type\
    \ id() {\n        return \"\";\n    }\n\n    static value_type op(const value_type&\
    \ a, const value_type& b) {\n        return a + b;\n    }\n};\n\nvoid test_library_features()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    using Seg = m1une::ds::DynamicSegtree<Sum>;\n\
    \n    Seg empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n\
    \    assert(empty.all_prod() == 0);\n\n    Seg seg(-1'000'000'000'000'000'000LL,\
    \ 1'000'000'000'000'000'000LL);\n    assert(!seg.empty());\n    assert(seg.left_bound()\
    \ == -1'000'000'000'000'000'000LL);\n    assert(seg.right_bound() == 1'000'000'000'000'000'000LL);\n\
    \    assert(seg.size() == 2'000'000'000'000'000'000ULL);\n\n    seg.reserve(256);\n\
    \    seg.set(-3, 2);\n    seg.set(2, 4);\n    seg.set(7, 1);\n\n    assert(seg.get(-3)\
    \ == 2);\n    assert(seg[-2] == 0);\n    assert(seg.prod(-4, 3) == 6);\n    assert(seg.prod(3,\
    \ 7) == 0);\n    assert(seg.all_prod() == 7);\n    assert(seg.max_right(-8, [](long\
    \ long x) { return x <= 5; }) == 2);\n    assert(seg.min_left(8, [](long long\
    \ x) { return x <= 4; }) == 3);\n\n    [[maybe_unused]] std::size_t nodes = seg.node_count();\n\
    \    seg.set(-3, 5);\n    assert(seg.node_count() == nodes);\n    assert(seg.all_prod()\
    \ == 10);\n\n    seg.clear();\n    assert(seg.node_count() == 0);\n    assert(seg.all_prod()\
    \ == 0);\n    assert(seg.get(-3) == 0);\n\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> uniform(-5, 6, 3);\n    assert(uniform.initial_value() == 3);\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \    assert(uniform.prod(-2, 4) == 18);\n    assert(uniform.max_right(-5, [](long\
    \ long x) { return x <= 14; }) == -1);\n    assert(uniform.min_left(6, [](long\
    \ long x) { return x <= 14; }) == 2);\n    uniform.set(0, 10);\n    assert(uniform.all_prod()\
    \ == 40);\n    assert(uniform.prod(-2, 4) == 25);\n    uniform.clear();\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \n    m1une::ds::DynamicSegtree<Concat, int> text(-4, 5);\n    text.set(2, \"\
    b\");\n    text.set(-1, \"a\");\n    assert(text.prod(-4, 5) == \"ab\");\n\n \
    \   m1une::ds::DynamicSegtree<Concat, int> uniform_text(-2, 3, \"x\");\n    assert(uniform_text.all_prod()\
    \ == \"xxxxx\");\n    uniform_text.set(1, \"a\");\n    uniform_text.set(-1, \"\
    b\");\n    assert(uniform_text.all_prod() == \"xbxax\");\n\n    Seg extreme(std::numeric_limits<long\
    \ long>::min(), std::numeric_limits<long long>::max());\n    extreme.set(std::numeric_limits<long\
    \ long>::min(), 3);\n    extreme.set(std::numeric_limits<long long>::max() - 1,\
    \ 4);\n    assert(extreme.size() == std::numeric_limits<unsigned long long>::max());\n\
    \    assert(extreme.get(std::numeric_limits<long long>::min()) == 3);\n    assert(extreme.get(std::numeric_limits<long\
    \ long>::max() - 1) == 4);\n    assert(extreme.all_prod() == 7);\n\n    constexpr\
    \ int left = -37;\n    constexpr int right = 42;\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> small(left, right);\n    std::vector<long long> a(right - left);\n    auto\
    \ value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p - left)];\n\
    \    };\n    std::uint64_t state = 1;\n    auto random = [&state]() {\n      \
    \  state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 2000; step++) {\n        int p = left\
    \ + int(random() % a.size());\n        long long x = static_cast<long long>(random()\
    \ % 10);\n        small.set(p, x);\n        value_at(p) = x;\n\n        int l\
    \ = left + int(random() % (a.size() + 1));\n        int r = left + int(random()\
    \ % (a.size() + 1));\n        if (r < l) std::swap(l, r);\n        [[maybe_unused]]\
    \ long long expected = 0;\n        for (int i = l; i < r; i++) expected += value_at(i);\n\
    \        assert(small.prod(l, r) == expected);\n\n        long long limit = static_cast<long\
    \ long>(random() % 100);\n        int max_right = l;\n        long long sum =\
    \ 0;\n        while (max_right < right && sum + value_at(max_right) <= limit)\
    \ {\n            sum += value_at(max_right);\n            max_right++;\n     \
    \   }\n        assert(small.max_right(l, [limit](long long value) { return value\
    \ <= limit; }) == max_right);\n\n        int min_left = r;\n        sum = 0;\n\
    \        while (left < min_left && value_at(min_left - 1) + sum <= limit) {\n\
    \            min_left--;\n            sum += value_at(min_left);\n        }\n\
    \        assert(small.min_left(r, [limit](long long value) { return value <= limit;\
    \ }) == min_left);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_library_features();\n\
    \n    int n, q;\n    fast_input >> n >> q;\n\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    m1une::ds::DynamicSegtree<Sum, int> seg(n);\n    seg.reserve(std::size_t(2)\
    \ * std::size_t(n));\n\n    for (int i = 0; i < n; i++) {\n        long long x;\n\
    \        fast_input >> x;\n        seg.set(i, x);\n    }\n\n    for (int query\
    \ = 0; query < q; query++) {\n        int type;\n        fast_input >> type;\n\
    \        if (type == 0) {\n            int p;\n            long long x;\n    \
    \        fast_input >> p >> x;\n            seg.set(p, seg.get(p) + x);\n    \
    \    } else {\n            int l, r;\n            fast_input >> l >> r;\n    \
    \        fast_output << seg.prod(l, r) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"../../../ds/segtree/dynamic_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <limits>\n#include <string>\n#include <vector>\n\n#include \"../../../monoid/add.hpp\"\
    \n\nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n  \
    \  static value_type id() {\n        return \"\";\n    }\n\n    static value_type\
    \ op(const value_type& a, const value_type& b) {\n        return a + b;\n    }\n\
    };\n\nvoid test_library_features() {\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    using Seg = m1une::ds::DynamicSegtree<Sum>;\n\n    Seg empty;\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.all_prod()\
    \ == 0);\n\n    Seg seg(-1'000'000'000'000'000'000LL, 1'000'000'000'000'000'000LL);\n\
    \    assert(!seg.empty());\n    assert(seg.left_bound() == -1'000'000'000'000'000'000LL);\n\
    \    assert(seg.right_bound() == 1'000'000'000'000'000'000LL);\n    assert(seg.size()\
    \ == 2'000'000'000'000'000'000ULL);\n\n    seg.reserve(256);\n    seg.set(-3,\
    \ 2);\n    seg.set(2, 4);\n    seg.set(7, 1);\n\n    assert(seg.get(-3) == 2);\n\
    \    assert(seg[-2] == 0);\n    assert(seg.prod(-4, 3) == 6);\n    assert(seg.prod(3,\
    \ 7) == 0);\n    assert(seg.all_prod() == 7);\n    assert(seg.max_right(-8, [](long\
    \ long x) { return x <= 5; }) == 2);\n    assert(seg.min_left(8, [](long long\
    \ x) { return x <= 4; }) == 3);\n\n    [[maybe_unused]] std::size_t nodes = seg.node_count();\n\
    \    seg.set(-3, 5);\n    assert(seg.node_count() == nodes);\n    assert(seg.all_prod()\
    \ == 10);\n\n    seg.clear();\n    assert(seg.node_count() == 0);\n    assert(seg.all_prod()\
    \ == 0);\n    assert(seg.get(-3) == 0);\n\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> uniform(-5, 6, 3);\n    assert(uniform.initial_value() == 3);\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \    assert(uniform.prod(-2, 4) == 18);\n    assert(uniform.max_right(-5, [](long\
    \ long x) { return x <= 14; }) == -1);\n    assert(uniform.min_left(6, [](long\
    \ long x) { return x <= 14; }) == 2);\n    uniform.set(0, 10);\n    assert(uniform.all_prod()\
    \ == 40);\n    assert(uniform.prod(-2, 4) == 25);\n    uniform.clear();\n    assert(uniform.node_count()\
    \ == 0);\n    assert(uniform.get(0) == 3);\n    assert(uniform.all_prod() == 33);\n\
    \n    m1une::ds::DynamicSegtree<Concat, int> text(-4, 5);\n    text.set(2, \"\
    b\");\n    text.set(-1, \"a\");\n    assert(text.prod(-4, 5) == \"ab\");\n\n \
    \   m1une::ds::DynamicSegtree<Concat, int> uniform_text(-2, 3, \"x\");\n    assert(uniform_text.all_prod()\
    \ == \"xxxxx\");\n    uniform_text.set(1, \"a\");\n    uniform_text.set(-1, \"\
    b\");\n    assert(uniform_text.all_prod() == \"xbxax\");\n\n    Seg extreme(std::numeric_limits<long\
    \ long>::min(), std::numeric_limits<long long>::max());\n    extreme.set(std::numeric_limits<long\
    \ long>::min(), 3);\n    extreme.set(std::numeric_limits<long long>::max() - 1,\
    \ 4);\n    assert(extreme.size() == std::numeric_limits<unsigned long long>::max());\n\
    \    assert(extreme.get(std::numeric_limits<long long>::min()) == 3);\n    assert(extreme.get(std::numeric_limits<long\
    \ long>::max() - 1) == 4);\n    assert(extreme.all_prod() == 7);\n\n    constexpr\
    \ int left = -37;\n    constexpr int right = 42;\n    m1une::ds::DynamicSegtree<Sum,\
    \ int> small(left, right);\n    std::vector<long long> a(right - left);\n    auto\
    \ value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p - left)];\n\
    \    };\n    std::uint64_t state = 1;\n    auto random = [&state]() {\n      \
    \  state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int step = 0; step < 2000; step++) {\n        int p = left\
    \ + int(random() % a.size());\n        long long x = static_cast<long long>(random()\
    \ % 10);\n        small.set(p, x);\n        value_at(p) = x;\n\n        int l\
    \ = left + int(random() % (a.size() + 1));\n        int r = left + int(random()\
    \ % (a.size() + 1));\n        if (r < l) std::swap(l, r);\n        [[maybe_unused]]\
    \ long long expected = 0;\n        for (int i = l; i < r; i++) expected += value_at(i);\n\
    \        assert(small.prod(l, r) == expected);\n\n        long long limit = static_cast<long\
    \ long>(random() % 100);\n        int max_right = l;\n        long long sum =\
    \ 0;\n        while (max_right < right && sum + value_at(max_right) <= limit)\
    \ {\n            sum += value_at(max_right);\n            max_right++;\n     \
    \   }\n        assert(small.max_right(l, [limit](long long value) { return value\
    \ <= limit; }) == max_right);\n\n        int min_left = r;\n        sum = 0;\n\
    \        while (left < min_left && value_at(min_left - 1) + sum <= limit) {\n\
    \            min_left--;\n            sum += value_at(min_left);\n        }\n\
    \        assert(small.min_left(r, [limit](long long value) { return value <= limit;\
    \ }) == min_left);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_library_features();\n\
    \n    int n, q;\n    fast_input >> n >> q;\n\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    m1une::ds::DynamicSegtree<Sum, int> seg(n);\n    seg.reserve(std::size_t(2)\
    \ * std::size_t(n));\n\n    for (int i = 0; i < n; i++) {\n        long long x;\n\
    \        fast_input >> x;\n        seg.set(i, x);\n    }\n\n    for (int query\
    \ = 0; query < q; query++) {\n        int type;\n        fast_input >> type;\n\
    \        if (type == 0) {\n            int p;\n            long long x;\n    \
    \        fast_input >> p >> x;\n            seg.set(p, seg.get(p) + x);\n    \
    \    } else {\n            int l, r;\n            fast_input >> l >> r;\n    \
    \        fast_output << seg.prod(l, r) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/dynamic_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  - utilities/fast_io.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/segtree/dynamic_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/dynamic_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/dynamic_segtree.test.cpp
- /verify/verify/ds/segtree/dynamic_segtree.test.cpp.html
title: verify/ds/segtree/dynamic_segtree.test.cpp
---
