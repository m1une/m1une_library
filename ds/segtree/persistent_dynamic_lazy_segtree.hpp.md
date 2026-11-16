---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/persistent_dynamic_lazy_segtree.hpp\"\n\n\n\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <memory>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral\
    \ Index>\nusing dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
    \ Index>\nconstexpr dynamic_size_type<Index> dynamic_distance(Index left, Index\
    \ right) {\n    return static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
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
    \n\n#line 1 \"ds/segtree/persistent_node_pool.hpp\"\n\n\n\n#line 9 \"ds/segtree/persistent_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have\
    \ integer `left`, `right`, and `references` members.\ntemplate <class Node>\n\
    struct PersistentNodePool {\n    std::vector<Node> nodes;\n    int first_free\
    \ = 0;\n    std::size_t live_nodes = 0;\n\n   private:\n    void release_zero(int\
    \ node) {\n        int left = nodes[node].left;\n        int right = nodes[node].right;\n\
    \        nodes[node] = Node();\n        nodes[node].left = first_free;\n     \
    \   first_free = node;\n        --live_nodes;\n        if (left && --nodes[left].references\
    \ == 0) release_zero(left);\n        if (right && --nodes[right].references ==\
    \ 0) release_zero(right);\n    }\n\n   public:\n    PersistentNodePool() { nodes.emplace_back();\
    \ }\n\n    void reserve(std::size_t capacity) { nodes.reserve(capacity + 1); }\n\
    \n    Node& operator[](int node) { return nodes[node]; }\n\n    const Node& operator[](int\
    \ node) const { return nodes[node]; }\n\n    void retain(int node) {\n       \
    \ if (node) ++nodes[node].references;\n    }\n\n    void release(int node) {\n\
    \        if (!node) return;\n        assert(nodes[node].references > 0);\n   \
    \     if (--nodes[node].references == 0) release_zero(node);\n    }\n\n    template\
    \ <class... Args>\n    int emplace(Args&&... args) {\n        int result;\n  \
    \      if (!first_free) {\n            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \            nodes.emplace_back(std::forward<Args>(args)...);\n            result\
    \ = int(nodes.size()) - 1;\n        } else {\n            result = first_free;\n\
    \            first_free = nodes[result].left;\n            nodes[result] = Node(std::forward<Args>(args)...);\n\
    \        }\n        Node& node = nodes[result];\n        node.references = 0;\n\
    \        retain(node.left);\n        retain(node.right);\n        ++live_nodes;\n\
    \        return result;\n    }\n\n    int clone(int node) {\n        assert(node);\n\
    \        Node copy = nodes[node];\n        return emplace(std::move(copy));\n\
    \    }\n\n    bool unique(int node) const {\n        return !node || nodes[node].references\
    \ == 1;\n    }\n\n    // Returns node itself when it has one owner, otherwise\
    \ an unowned clone.\n    // The caller must attach a returned clone with replace()\
    \ before it can be\n    // released or exposed as a root.\n    int clone_if_shared(int\
    \ node) {\n        if (unique(node)) return node;\n        return clone(node);\n\
    \    }\n\n    void replace(int& edge, int node) {\n        if (edge == node) return;\n\
    \        retain(node);\n        int old = edge;\n        edge = node;\n      \
    \  release(old);\n    }\n\n    std::size_t size() const { return live_nodes; }\n\
    };\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\n\n\
    #line 17 \"ds/segtree/persistent_dynamic_lazy_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A persistent sparse lazy segment tree over an integral\
    \ half-open interval.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid,\
    \ std::integral Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct PersistentDynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        int references;\n        bool has_lazy;\n\n        Node()\n         \
    \   : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), left(0), right(0), references(0),\
    \ has_lazy(false) {}\n        explicit Node(T value)\n            : val(std::move(value)),\
    \ lazy(ActedMonoid::op_id()), left(0), right(0), references(0), has_lazy(false)\
    \ {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<ActedMonoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value) :\
    \ domain(left, right, std::move(initial_value)) {}\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicLazySegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node(Index left, Index right, int depth) const {\n        return\
    \ _pool->emplace(_config->domain.default_product(depth, left, right));\n    }\n\
    \n    int clone_or_new(int t, Index left, Index right, int depth, bool copy_on_write\
    \ = false) const {\n        if (!t) return new_node(left, right, depth);\n   \
    \     return copy_on_write ? _pool->clone_if_shared(t) : _pool->clone(t);\n  \
    \  }\n\n    const T& value(int t, Index left, Index right, int depth) const {\n\
    \        if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    void all_apply_to_node(int t, Index left, Index\
    \ right, const F& f) const {\n        Node& node = (*_pool)[t];\n        node.val\
    \ = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n        if (std::midpoint(left,\
    \ right) != left) {\n            node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, int depth, const F& f,\n                       \
    \ bool copy_on_write = false) const {\n        int result = clone_or_new(t, left,\
    \ right, depth, copy_on_write);\n        all_apply_to_node(result, left, right,\
    \ f);\n        return result;\n    }\n\n    void push(int t, Index left, Index\
    \ right, int depth, bool copy_on_write = false) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        F lazy = (*_pool)[t].lazy;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, depth + 1, lazy, copy_on_write);\n\
    \        int right_child =\n            all_apply_clone((*_pool)[t].right, middle,\
    \ right, depth + 1,\n                            detail::dynamic_shift<ActedMonoid>(lazy,\
    \ detail::dynamic_distance(left, middle)),\n                            copy_on_write);\n\
    \n        Node& node = (*_pool)[t];\n        _pool->replace(node.left, left_child);\n\
    \        _pool->replace(node.right, right_child);\n        node.lazy = ActedMonoid::op_id();\n\
    \        node.has_lazy = false;\n    }\n\n    void update(int t, Index left, Index\
    \ right, int depth) const {\n        Index middle = std::midpoint(left, right);\n\
    \        Node& node = (*_pool)[t];\n        node.val =\n            ActedMonoid::op(value(node.left,\
    \ left, middle, depth + 1), value(node.right, middle, right, depth + 1));\n  \
    \  }\n\n    int set_node(int t, Index left, Index right, int depth, Index p, T\
    \ x,\n                 bool copy_on_write = false) const {\n        t = clone_or_new(t,\
    \ left, right, depth, copy_on_write);\n        Index middle = std::midpoint(left,\
    \ right);\n        if (middle == left) {\n            Node& node = (*_pool)[t];\n\
    \            node.val = std::move(x);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n\n    \
    \    push(t, left, right, depth, copy_on_write);\n        if (p < middle) {\n\
    \            int child = set_node((*_pool)[t].left, left, middle, depth + 1, p,\
    \ std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ middle, right, depth + 1, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        update(t, left, right, depth);\n        return t;\n\
    \    }\n\n    int apply_node(int t, Index left, Index right, int depth, Index\
    \ query_left, Index query_right, const F& f,\n                   bool copy_on_write\
    \ = false) const {\n        if (query_right <= left || right <= query_left) return\
    \ t;\n        if (query_left <= left && right <= query_right) {\n            return\
    \ all_apply_clone(t, left, right, depth,\n                                   detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left)),\n                             \
    \      copy_on_write);\n        }\n\n        t = clone_or_new(t, left, right,\
    \ depth, copy_on_write);\n        push(t, left, right, depth, copy_on_write);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node((*_pool)[t].left, left, middle, depth + 1, query_left, query_right,\
    \ f,\n                                    copy_on_write);\n        int right_child\
    \ = apply_node((*_pool)[t].right, middle, right, depth + 1, query_left, query_right,\
    \ f,\n                                     copy_on_write);\n        _pool->replace((*_pool)[t].left,\
    \ left_child);\n        _pool->replace((*_pool)[t].right, right_child);\n    \
    \    update(t, left, right, depth);\n        return t;\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !(*_pool)[t].has_lazy) return shifted;\n       \
    \ return ActedMonoid::op_comp(shifted, detail::dynamic_shift<ActedMonoid>((*_pool)[t].lazy,\
    \ offset));\n    }\n\n    T prod_node(int t, Index left, Index right, int depth,\
    \ Index query_left, Index query_right,\n                const F& inherited) const\
    \ {\n        if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(inherited, value(t, left, right, depth));\n\
    \        }\n        Index middle = std::midpoint(left, right);\n        return\
    \ ActedMonoid::op(prod_node(t ? (*_pool)[t].left : 0, left, middle, depth + 1,\
    \ query_left, query_right,\n                                         compose_for_child(inherited,\
    \ t, 0)),\n                               prod_node(t ? (*_pool)[t].right : 0,\
    \ middle, right, depth + 1, query_left, query_right,\n                       \
    \                  compose_for_child(inherited, t, detail::dynamic_distance(left,\
    \ middle))));\n    }\n\n    template <class G>\n    Index max_right_node(int t,\
    \ Index left, Index right, int depth, Index query_left, T& product, const F& inherited,\n\
    \                         G& predicate) const {\n        if (right <= query_left)\
    \ return right;\n        if (query_left <= left) {\n            T next =\n   \
    \             ActedMonoid::op(product, detail::dynamic_mapping<ActedMonoid>(inherited,\
    \ value(t, left, right, depth)));\n            if (predicate(next)) {\n      \
    \          product = std::move(next);\n                return right;\n       \
    \     }\n            Index middle = std::midpoint(left, right);\n            if\
    \ (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(t ? (*_pool)[t].left : 0, left,\
    \ middle, depth + 1, query_left, product,\n                                  \
    \    compose_for_child(inherited, t, 0), predicate);\n        if (result < middle)\
    \ return result;\n        return max_right_node(t ? (*_pool)[t].right : 0, middle,\
    \ right, depth + 1, query_left, product,\n                              compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)), predicate);\n    }\n\n    template\
    \ <class G>\n    Index min_left_node(int t, Index left, Index right, int depth,\
    \ Index query_right, T& product, const F& inherited,\n                       \
    \ G& predicate) const {\n        if (query_right <= left) return left;\n     \
    \   if (right <= query_right) {\n            T next =\n                ActedMonoid::op(detail::dynamic_mapping<ActedMonoid>(inherited,\
    \ value(t, left, right, depth)), product);\n            if (predicate(next)) {\n\
    \                product = std::move(next);\n                return left;\n  \
    \          }\n            Index middle = std::midpoint(left, right);\n       \
    \     if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result =\n            min_left_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_right, product,\n                     \
    \     compose_for_child(inherited, t, detail::dynamic_distance(left, middle)),\
    \ predicate);\n        if (middle < result) return result;\n        return min_left_node(t\
    \ ? (*_pool)[t].left : 0, left, middle, depth + 1, query_right, product,\n   \
    \                          compose_for_child(inherited, t, 0), predicate);\n \
    \   }\n\n   public:\n    PersistentDynamicLazySegtree() : PersistentDynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit PersistentDynamicLazySegtree(Index\
    \ n) : PersistentDynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n      \
    \  if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n\n\
    \    PersistentDynamicLazySegtree(Index left, Index right)\n        : PersistentDynamicLazySegtree(left,\
    \ right, ActedMonoid::id()) {}\n\n    PersistentDynamicLazySegtree(Index left,\
    \ Index right, T initial_value)\n        : _config(std::make_shared<Config>(left,\
    \ right, std::move(initial_value))),\n          _pool(std::make_shared<Pool>()),\n\
    \          _root(0) {}\n\n    PersistentDynamicLazySegtree(const PersistentDynamicLazySegtree&\
    \ other)\n        : _config(other._config), _pool(other._pool), _root(other._root)\
    \ {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicLazySegtree(PersistentDynamicLazySegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicLazySegtree&\
    \ operator=(const PersistentDynamicLazySegtree& other) {\n        if (this ==\
    \ &other) return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicLazySegtree& operator=(PersistentDynamicLazySegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _config = std::move(other._config);\n      \
    \  _pool = std::move(other._pool);\n        _root = other._root;\n        other._root\
    \ = 0;\n        return *this;\n    }\n    ~PersistentDynamicLazySegtree() {\n\
    \        if (_pool) _pool->release(_root);\n    }\n\n    size_type size() const\
    \ { return _config->domain.size(); }\n\n    bool empty() const { return _config->domain.empty();\
    \ }\n\n    Index left_bound() const { return _config->domain.left_bound(); }\n\
    \n    Index right_bound() const { return _config->domain.right_bound(); }\n\n\
    \    const T& initial_value() const { return _config->domain.initial_value();\
    \ }\n\n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity);\n\
    \    }\n\n    std::size_t node_count() const { return _pool->size(); }\n\n   \
    \ void release() {\n        if (_pool) _pool->release(_root);\n        _pool =\
    \ std::make_shared<Pool>();\n        _root = 0;\n    }\n\n    PersistentDynamicLazySegtree\
    \ set(Index p, T x) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        return PersistentDynamicLazySegtree(_config, _pool,\n               \
    \                             set_node(_root, left_bound(), right_bound(), 0,\
    \ p, std::move(x)));\n    }\n\n    void set_inplace(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        int root = set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x), true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        return prod(p, p + 1);\n    }\n\n    T operator[](Index\
    \ p) const { return get(p); }\n\n    T prod(Index left, Index right) const {\n\
    \        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return ActedMonoid::id();\n        return prod_node(_root,\
    \ left_bound(), right_bound(), 0, left, right, ActedMonoid::op_id());\n    }\n\
    \n    T all_prod() const { return value(_root, left_bound(), right_bound(), 0);\
    \ }\n\n    PersistentDynamicLazySegtree apply(Index p, const F& f) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        return apply(p,\
    \ p + 1, f);\n    }\n\n    PersistentDynamicLazySegtree apply(Index left, Index\
    \ right, const F& f) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return *this;\n    \
    \    return PersistentDynamicLazySegtree(_config, _pool,\n                   \
    \                         apply_node(_root, left_bound(), right_bound(), 0, left,\
    \ right, f));\n    }\n\n    void apply_inplace(Index p, const F& f) {\n      \
    \  assert(left_bound() <= p && p < right_bound());\n        apply_inplace(p, p\
    \ + 1, f);\n    }\n\n    void apply_inplace(Index left, Index right, const F&\
    \ f) {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return;\n        int root = apply_node(_root, left_bound(),\
    \ right_bound(), 0, left, right, f, true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    template <class G>\n    Index max_right(Index left, G predicate)\
    \ const {\n        assert(left_bound() <= left && left <= right_bound());\n  \
    \      assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(_root, left_bound(), right_bound(), 0, left, product, ActedMonoid::op_id(),\
    \ predicate);\n    }\n\n    template <class G>\n    Index min_left(Index right,\
    \ G predicate) const {\n        assert(left_bound() <= right && right <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (right == left_bound())\
    \ return left_bound();\n        T product = ActedMonoid::id();\n        return\
    \ min_left_node(_root, left_bound(), right_bound(), 0, right, product, ActedMonoid::op_id(),\
    \ predicate);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_LAZY_SEGTREE_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_LAZY_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <memory>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../acted_monoid/concept.hpp\"\n#include \"\
    dynamic_segtree_common.hpp\"\n#include \"persistent_node_pool.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// A persistent sparse lazy segment tree over an\
    \ integral half-open interval.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid,\
    \ std::integral Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct PersistentDynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        int references;\n        bool has_lazy;\n\n        Node()\n         \
    \   : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), left(0), right(0), references(0),\
    \ has_lazy(false) {}\n        explicit Node(T value)\n            : val(std::move(value)),\
    \ lazy(ActedMonoid::op_id()), left(0), right(0), references(0), has_lazy(false)\
    \ {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<ActedMonoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value) :\
    \ domain(left, right, std::move(initial_value)) {}\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicLazySegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node(Index left, Index right, int depth) const {\n        return\
    \ _pool->emplace(_config->domain.default_product(depth, left, right));\n    }\n\
    \n    int clone_or_new(int t, Index left, Index right, int depth, bool copy_on_write\
    \ = false) const {\n        if (!t) return new_node(left, right, depth);\n   \
    \     return copy_on_write ? _pool->clone_if_shared(t) : _pool->clone(t);\n  \
    \  }\n\n    const T& value(int t, Index left, Index right, int depth) const {\n\
    \        if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    void all_apply_to_node(int t, Index left, Index\
    \ right, const F& f) const {\n        Node& node = (*_pool)[t];\n        node.val\
    \ = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n        if (std::midpoint(left,\
    \ right) != left) {\n            node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, int depth, const F& f,\n                       \
    \ bool copy_on_write = false) const {\n        int result = clone_or_new(t, left,\
    \ right, depth, copy_on_write);\n        all_apply_to_node(result, left, right,\
    \ f);\n        return result;\n    }\n\n    void push(int t, Index left, Index\
    \ right, int depth, bool copy_on_write = false) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        F lazy = (*_pool)[t].lazy;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, depth + 1, lazy, copy_on_write);\n\
    \        int right_child =\n            all_apply_clone((*_pool)[t].right, middle,\
    \ right, depth + 1,\n                            detail::dynamic_shift<ActedMonoid>(lazy,\
    \ detail::dynamic_distance(left, middle)),\n                            copy_on_write);\n\
    \n        Node& node = (*_pool)[t];\n        _pool->replace(node.left, left_child);\n\
    \        _pool->replace(node.right, right_child);\n        node.lazy = ActedMonoid::op_id();\n\
    \        node.has_lazy = false;\n    }\n\n    void update(int t, Index left, Index\
    \ right, int depth) const {\n        Index middle = std::midpoint(left, right);\n\
    \        Node& node = (*_pool)[t];\n        node.val =\n            ActedMonoid::op(value(node.left,\
    \ left, middle, depth + 1), value(node.right, middle, right, depth + 1));\n  \
    \  }\n\n    int set_node(int t, Index left, Index right, int depth, Index p, T\
    \ x,\n                 bool copy_on_write = false) const {\n        t = clone_or_new(t,\
    \ left, right, depth, copy_on_write);\n        Index middle = std::midpoint(left,\
    \ right);\n        if (middle == left) {\n            Node& node = (*_pool)[t];\n\
    \            node.val = std::move(x);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n\n    \
    \    push(t, left, right, depth, copy_on_write);\n        if (p < middle) {\n\
    \            int child = set_node((*_pool)[t].left, left, middle, depth + 1, p,\
    \ std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ middle, right, depth + 1, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        update(t, left, right, depth);\n        return t;\n\
    \    }\n\n    int apply_node(int t, Index left, Index right, int depth, Index\
    \ query_left, Index query_right, const F& f,\n                   bool copy_on_write\
    \ = false) const {\n        if (query_right <= left || right <= query_left) return\
    \ t;\n        if (query_left <= left && right <= query_right) {\n            return\
    \ all_apply_clone(t, left, right, depth,\n                                   detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left)),\n                             \
    \      copy_on_write);\n        }\n\n        t = clone_or_new(t, left, right,\
    \ depth, copy_on_write);\n        push(t, left, right, depth, copy_on_write);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node((*_pool)[t].left, left, middle, depth + 1, query_left, query_right,\
    \ f,\n                                    copy_on_write);\n        int right_child\
    \ = apply_node((*_pool)[t].right, middle, right, depth + 1, query_left, query_right,\
    \ f,\n                                     copy_on_write);\n        _pool->replace((*_pool)[t].left,\
    \ left_child);\n        _pool->replace((*_pool)[t].right, right_child);\n    \
    \    update(t, left, right, depth);\n        return t;\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !(*_pool)[t].has_lazy) return shifted;\n       \
    \ return ActedMonoid::op_comp(shifted, detail::dynamic_shift<ActedMonoid>((*_pool)[t].lazy,\
    \ offset));\n    }\n\n    T prod_node(int t, Index left, Index right, int depth,\
    \ Index query_left, Index query_right,\n                const F& inherited) const\
    \ {\n        if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(inherited, value(t, left, right, depth));\n\
    \        }\n        Index middle = std::midpoint(left, right);\n        return\
    \ ActedMonoid::op(prod_node(t ? (*_pool)[t].left : 0, left, middle, depth + 1,\
    \ query_left, query_right,\n                                         compose_for_child(inherited,\
    \ t, 0)),\n                               prod_node(t ? (*_pool)[t].right : 0,\
    \ middle, right, depth + 1, query_left, query_right,\n                       \
    \                  compose_for_child(inherited, t, detail::dynamic_distance(left,\
    \ middle))));\n    }\n\n    template <class G>\n    Index max_right_node(int t,\
    \ Index left, Index right, int depth, Index query_left, T& product, const F& inherited,\n\
    \                         G& predicate) const {\n        if (right <= query_left)\
    \ return right;\n        if (query_left <= left) {\n            T next =\n   \
    \             ActedMonoid::op(product, detail::dynamic_mapping<ActedMonoid>(inherited,\
    \ value(t, left, right, depth)));\n            if (predicate(next)) {\n      \
    \          product = std::move(next);\n                return right;\n       \
    \     }\n            Index middle = std::midpoint(left, right);\n            if\
    \ (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(t ? (*_pool)[t].left : 0, left,\
    \ middle, depth + 1, query_left, product,\n                                  \
    \    compose_for_child(inherited, t, 0), predicate);\n        if (result < middle)\
    \ return result;\n        return max_right_node(t ? (*_pool)[t].right : 0, middle,\
    \ right, depth + 1, query_left, product,\n                              compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)), predicate);\n    }\n\n    template\
    \ <class G>\n    Index min_left_node(int t, Index left, Index right, int depth,\
    \ Index query_right, T& product, const F& inherited,\n                       \
    \ G& predicate) const {\n        if (query_right <= left) return left;\n     \
    \   if (right <= query_right) {\n            T next =\n                ActedMonoid::op(detail::dynamic_mapping<ActedMonoid>(inherited,\
    \ value(t, left, right, depth)), product);\n            if (predicate(next)) {\n\
    \                product = std::move(next);\n                return left;\n  \
    \          }\n            Index middle = std::midpoint(left, right);\n       \
    \     if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result =\n            min_left_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_right, product,\n                     \
    \     compose_for_child(inherited, t, detail::dynamic_distance(left, middle)),\
    \ predicate);\n        if (middle < result) return result;\n        return min_left_node(t\
    \ ? (*_pool)[t].left : 0, left, middle, depth + 1, query_right, product,\n   \
    \                          compose_for_child(inherited, t, 0), predicate);\n \
    \   }\n\n   public:\n    PersistentDynamicLazySegtree() : PersistentDynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit PersistentDynamicLazySegtree(Index\
    \ n) : PersistentDynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n      \
    \  if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n\n\
    \    PersistentDynamicLazySegtree(Index left, Index right)\n        : PersistentDynamicLazySegtree(left,\
    \ right, ActedMonoid::id()) {}\n\n    PersistentDynamicLazySegtree(Index left,\
    \ Index right, T initial_value)\n        : _config(std::make_shared<Config>(left,\
    \ right, std::move(initial_value))),\n          _pool(std::make_shared<Pool>()),\n\
    \          _root(0) {}\n\n    PersistentDynamicLazySegtree(const PersistentDynamicLazySegtree&\
    \ other)\n        : _config(other._config), _pool(other._pool), _root(other._root)\
    \ {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicLazySegtree(PersistentDynamicLazySegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicLazySegtree&\
    \ operator=(const PersistentDynamicLazySegtree& other) {\n        if (this ==\
    \ &other) return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicLazySegtree& operator=(PersistentDynamicLazySegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _config = std::move(other._config);\n      \
    \  _pool = std::move(other._pool);\n        _root = other._root;\n        other._root\
    \ = 0;\n        return *this;\n    }\n    ~PersistentDynamicLazySegtree() {\n\
    \        if (_pool) _pool->release(_root);\n    }\n\n    size_type size() const\
    \ { return _config->domain.size(); }\n\n    bool empty() const { return _config->domain.empty();\
    \ }\n\n    Index left_bound() const { return _config->domain.left_bound(); }\n\
    \n    Index right_bound() const { return _config->domain.right_bound(); }\n\n\
    \    const T& initial_value() const { return _config->domain.initial_value();\
    \ }\n\n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity);\n\
    \    }\n\n    std::size_t node_count() const { return _pool->size(); }\n\n   \
    \ void release() {\n        if (_pool) _pool->release(_root);\n        _pool =\
    \ std::make_shared<Pool>();\n        _root = 0;\n    }\n\n    PersistentDynamicLazySegtree\
    \ set(Index p, T x) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        return PersistentDynamicLazySegtree(_config, _pool,\n               \
    \                             set_node(_root, left_bound(), right_bound(), 0,\
    \ p, std::move(x)));\n    }\n\n    void set_inplace(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        int root = set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x), true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        return prod(p, p + 1);\n    }\n\n    T operator[](Index\
    \ p) const { return get(p); }\n\n    T prod(Index left, Index right) const {\n\
    \        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return ActedMonoid::id();\n        return prod_node(_root,\
    \ left_bound(), right_bound(), 0, left, right, ActedMonoid::op_id());\n    }\n\
    \n    T all_prod() const { return value(_root, left_bound(), right_bound(), 0);\
    \ }\n\n    PersistentDynamicLazySegtree apply(Index p, const F& f) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        return apply(p,\
    \ p + 1, f);\n    }\n\n    PersistentDynamicLazySegtree apply(Index left, Index\
    \ right, const F& f) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return *this;\n    \
    \    return PersistentDynamicLazySegtree(_config, _pool,\n                   \
    \                         apply_node(_root, left_bound(), right_bound(), 0, left,\
    \ right, f));\n    }\n\n    void apply_inplace(Index p, const F& f) {\n      \
    \  assert(left_bound() <= p && p < right_bound());\n        apply_inplace(p, p\
    \ + 1, f);\n    }\n\n    void apply_inplace(Index left, Index right, const F&\
    \ f) {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return;\n        int root = apply_node(_root, left_bound(),\
    \ right_bound(), 0, left, right, f, true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    template <class G>\n    Index max_right(Index left, G predicate)\
    \ const {\n        assert(left_bound() <= left && left <= right_bound());\n  \
    \      assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(_root, left_bound(), right_bound(), 0, left, product, ActedMonoid::op_id(),\
    \ predicate);\n    }\n\n    template <class G>\n    Index min_left(Index right,\
    \ G predicate) const {\n        assert(left_bound() <= right && right <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (right == left_bound())\
    \ return left_bound();\n        T product = ActedMonoid::id();\n        return\
    \ min_left_node(_root, left_bound(), right_bound(), 0, right, product, ActedMonoid::op_id(),\
    \ predicate);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_PERSISTENT_DYNAMIC_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/persistent_dynamic_lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  - verify/ds/persistent_cow.test.cpp
documentation_of: ds/segtree/persistent_dynamic_lazy_segtree.hpp
layout: document
title: Persistent Dynamic Lazy Segment Tree
---

## Overview

`m1une::ds::PersistentDynamicLazySegtree` combines persistence, sparse
allocation, and lazy propagation over a fixed integer coordinate domain.
Assignments and range updates return new versions; previous versions remain
queryable.

Every coordinate begins with one uniform `initial_value`. Untouched segment
products are derived from that leaf without building the segment. For
size-aware acted monoids, pass a real leaf value such as
`RangeAddRangeSum<long long>::make(0)`, not the empty-product identity.

All versions derived from one tree share a contiguous node pool and immutable
domain metadata. Read-only queries allocate no nodes. Reference counting
recycles nodes after their last parent or version handle is released.

`set_inplace` and `apply_inplace` mutate only the current handle using
copy-on-write. Shared nodes, including children receiving a pushed lazy tag, are
cloned before modification; unique nodes are reused. The ordinary updates still
return new persistent versions.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

Position-dependent acted monoids may provide `op_shift(f, offset)`. Existing
shifted acted monoids accept `long long`, so applied interval lengths must fit
in that type.

## Construction

* `PersistentDynamicLazySegtree()`: creates an empty domain `[0, 0)`.
* `PersistentDynamicLazySegtree(Index n)`: creates `[0, n)` with initial leaf
  `ActedMonoid::id()`.
* `PersistentDynamicLazySegtree(Index left, Index right)`: creates
  `[left, right)` with initial leaf `ActedMonoid::id()`.
* `PersistentDynamicLazySegtree(Index left, Index right, T initial_value)`:
  creates a domain with the specified uniform initial leaf.

Construction uses $O(\log U)$ metadata and $O(\log^2 U)$ monoid operations to
cache untouched products, where $U$ is the domain length. No tree node is
allocated initially.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial leaf. | $O(1)$ |
| `void reserve(size_t n)` | Reserves shared-pool space for `n` nodes. | $O(K)$ |
| `size_t node_count()` | Returns live nodes in the shared version family. | $O(1)$ |
| `void release()` | Releases this root and resets the handle to the uniform initial version. | $O(F)$ |
| `PersistentDynamicLazySegtree set(Index p, T x)` | Returns a version assigning `x` at `p`. | $O(\log U)$ |
| `void set_inplace(Index p, T x)` | Assigns `x` in this version using copy-on-write. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `PersistentDynamicLazySegtree apply(Index p, F f)` | Returns a version applying `f` at `p`. | $O(\log U)$ |
| `PersistentDynamicLazySegtree apply(Index l, Index r, F f)` | Returns a version applying `f` over `[l, r)`. | $O(\log U)$ |
| `void apply_inplace(Index p, const F& f)` | Applies `f` at `p` in this version using copy-on-write. | $O(\log U)$ |
| `void apply_inplace(Index l, Index r, const F& f)` | Applies `f` over `[l, r)` in this version using copy-on-write. | $O(\log U)$ |
| `Index max_right(Index l, G g)` | Finds the largest valid right boundary. | $O(\log U)$ |
| `Index min_left(Index r, G g)` | Finds the smallest valid left boundary. | $O(\log U)$ |

Here $K$ is the number of live nodes and $F$ is the number freed by a release.
Each update allocates $O(\log U)$ nodes in the worst case. Copying a version is
$O(1)$. Destruction and assignment release roots automatically, and freed slots
are reused.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/persistent_dynamic_lazy_segtree.hpp"

#include <iostream>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentDynamicLazySegtree<AM>;

    Seg base(-1'000'000'000LL, 1'000'000'001LL, AM::make(0));
    Seg first = base.apply(-10, 20, 5);
    Seg second = first.set(0, AM::make(100));

    std::cout << base.all_prod().sum << "\n";    // 0
    std::cout << first.all_prod().sum << "\n";   // 150
    std::cout << second.all_prod().sum << "\n";  // 245
    first.release();                             // drop an unneeded root early
}
```
