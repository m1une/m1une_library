---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_segtree.hpp
    title: Persistent Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/rollback_dynamic_segtree.hpp\"\n\n\n\n#include\
    \ <concepts>\n#include <type_traits>\n#include <utility>\n\n#line 1 \"ds/detail/rollback_persistent_base.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#line 8 \"\
    ds/detail/rollback_persistent_base.hpp\"\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Persistent>\nstruct\
    \ RollbackPersistentBase : Persistent {\n   private:\n    std::vector<Persistent>\
    \ _history;\n\n   protected:\n    using Persistent::Persistent;\n\n    const Persistent&\
    \ persistent() const {\n        return *this;\n    }\n\n    void commit(Persistent\
    \ next) {\n        assert(_history.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _history.emplace_back(persistent());\n        Persistent::operator=(std::move(next));\n\
    \    }\n\n   public:\n    RollbackPersistentBase() = default;\n\n    explicit\
    \ RollbackPersistentBase(Persistent initial)\n        : Persistent(std::move(initial))\
    \ {}\n\n    int history_size() const {\n        return int(_history.size());\n\
    \    }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n\
    \        _history.reserve(count);\n    }\n\n    bool undo() {\n        if (_history.empty())\
    \ return false;\n        Persistent::operator=(std::move(_history.back()));\n\
    \        _history.pop_back();\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    void clear_history() {\n        _history.clear();\n\
    \    }\n\n    void release() {\n        _history.clear();\n        Persistent::release();\n\
    \    }\n\n    const Persistent& current_version() const {\n        return persistent();\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/segtree/persistent_dynamic_segtree.hpp\"\n\n\n\n#line 8 \"ds/segtree/persistent_dynamic_segtree.hpp\"\
    \n#include <memory>\n#include <numeric>\n#line 13 \"ds/segtree/persistent_dynamic_segtree.hpp\"\
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
    \ namespace m1une\n\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\
    \n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une {\nnamespace\
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
    #line 17 \"ds/segtree/persistent_dynamic_segtree.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\n// A persistent sparse segment tree over an integral half-open\
    \ interval.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral Index = long\
    \ long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct PersistentDynamicSegtree\
    \ {\n    using T = typename Monoid::value_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        int left;\n        int right;\n        int references;\n\
    \n        Node() : val(Monoid::id()), left(0), right(0), references(0) {}\n  \
    \      explicit Node(T value) : val(std::move(value)), left(0), right(0), references(0)\
    \ {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<Monoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value) :\
    \ domain(left, right, std::move(initial_value)) {}\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicSegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node(T value) const { return _pool->emplace(std::move(value)); }\n\
    \n    const T& value(int t, Index left, Index right, int depth) const {\n    \
    \    if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    int set_node(int t, Index left, Index right, int\
    \ depth, Index p, T x, bool copy_on_write = false) const {\n        Index middle\
    \ = std::midpoint(left, right);\n        if (copy_on_write) {\n            int\
    \ result = t ? _pool->clone_if_shared(t) : new_node(value(0, left, right, depth));\n\
    \            if (middle == left) {\n                (*_pool)[result].val = std::move(x);\n\
    \                return result;\n            }\n            int child;\n     \
    \       if (p < middle) {\n                child = set_node((*_pool)[result].left,\
    \ left, middle, depth + 1, p, std::move(x), true);\n                _pool->replace((*_pool)[result].left,\
    \ child);\n            } else {\n                child = set_node((*_pool)[result].right,\
    \ middle, right, depth + 1, p, std::move(x), true);\n                _pool->replace((*_pool)[result].right,\
    \ child);\n            }\n            Node& node = (*_pool)[result];\n       \
    \     node.val = Monoid::op(value(node.left, left, middle, depth + 1),\n     \
    \                             value(node.right, middle, right, depth + 1));\n\
    \            return result;\n        }\n        if (middle == left) return new_node(std::move(x));\n\
    \n        int left_child = t ? (*_pool)[t].left : 0;\n        int right_child\
    \ = t ? (*_pool)[t].right : 0;\n        if (p < middle) {\n            left_child\
    \ = set_node(left_child, left, middle, depth + 1, p, std::move(x));\n        }\
    \ else {\n            right_child = set_node(right_child, middle, right, depth\
    \ + 1, p, std::move(x));\n        }\n\n        int result = new_node(\n      \
    \      Monoid::op(value(left_child, left, middle, depth + 1), value(right_child,\
    \ middle, right, depth + 1)));\n        _pool->replace((*_pool)[result].left,\
    \ left_child);\n        _pool->replace((*_pool)[result].right, right_child);\n\
    \        return result;\n    }\n\n    T prod_node(int t, Index left, Index right,\
    \ int depth, Index query_left, Index query_right) const {\n        if (query_right\
    \ <= left || right <= query_left) return Monoid::id();\n        if (query_left\
    \ <= left && right <= query_right) {\n            return value(t, left, right,\
    \ depth);\n        }\n        Index middle = std::midpoint(left, right);\n   \
    \     return Monoid::op(prod_node(t ? (*_pool)[t].left : 0, left, middle, depth\
    \ + 1, query_left, query_right),\n                          prod_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_left, query_right));\n    }\n\n    template\
    \ <class F>\n    Index max_right_node(int t, Index left, Index right, int depth,\
    \ Index query_left, T& product, F& predicate) const {\n        if (right <= query_left)\
    \ return right;\n        if (query_left <= left) {\n            T next = Monoid::op(product,\
    \ value(t, left, right, depth));\n            if (predicate(next)) {\n       \
    \         product = std::move(next);\n                return right;\n        \
    \    }\n            Index middle = std::midpoint(left, right);\n            if\
    \ (middle == left) return left;\n        }\n\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result =\n            max_right_node(t ? (*_pool)[t].left\
    \ : 0, left, middle, depth + 1, query_left, product, predicate);\n        if (result\
    \ < middle) return result;\n        return max_right_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_left, product, predicate);\n    }\n\n \
    \   template <class F>\n    Index min_left_node(int t, Index left, Index right,\
    \ int depth, Index query_right, T& product, F& predicate) const {\n        if\
    \ (query_right <= left) return left;\n        if (right <= query_right) {\n  \
    \          T next = Monoid::op(value(t, left, right, depth), product);\n     \
    \       if (predicate(next)) {\n                product = std::move(next);\n \
    \               return left;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return right;\n        }\n\n      \
    \  Index middle = std::midpoint(left, right);\n        Index result =\n      \
    \      min_left_node(t ? (*_pool)[t].right : 0, middle, right, depth + 1, query_right,\
    \ product, predicate);\n        if (middle < result) return result;\n        return\
    \ min_left_node(t ? (*_pool)[t].left : 0, left, middle, depth + 1, query_right,\
    \ product, predicate);\n    }\n\n   public:\n    PersistentDynamicSegtree() :\
    \ PersistentDynamicSegtree(Index(0), Index(0), Monoid::id()) {}\n\n    explicit\
    \ PersistentDynamicSegtree(Index n) : PersistentDynamicSegtree(Index(0), n, Monoid::id())\
    \ {\n        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n\
    \    }\n\n    PersistentDynamicSegtree(Index left, Index right) : PersistentDynamicSegtree(left,\
    \ right, Monoid::id()) {}\n\n    PersistentDynamicSegtree(Index left, Index right,\
    \ T initial_value)\n        : _config(std::make_shared<Config>(left, right, std::move(initial_value))),\n\
    \          _pool(std::make_shared<Pool>()),\n          _root(0) {}\n\n    PersistentDynamicSegtree(const\
    \ PersistentDynamicSegtree& other)\n        : _config(other._config), _pool(other._pool),\
    \ _root(other._root) {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicSegtree(PersistentDynamicSegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicSegtree&\
    \ operator=(const PersistentDynamicSegtree& other) {\n        if (this == &other)\
    \ return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicSegtree& operator=(PersistentDynamicSegtree&& other)\
    \ noexcept {\n        if (this == &other) return *this;\n        if (_pool) _pool->release(_root);\n\
    \        _config = std::move(other._config);\n        _pool = std::move(other._pool);\n\
    \        _root = other._root;\n        other._root = 0;\n        return *this;\n\
    \    }\n    ~PersistentDynamicSegtree() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    size_type size() const { return _config->domain.size(); }\n\n  \
    \  bool empty() const { return _config->domain.empty(); }\n\n    Index left_bound()\
    \ const { return _config->domain.left_bound(); }\n\n    Index right_bound() const\
    \ { return _config->domain.right_bound(); }\n\n    const T& initial_value() const\
    \ { return _config->domain.initial_value(); }\n\n    void reserve(std::size_t\
    \ node_capacity) const {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _pool->reserve(node_capacity);\n    }\n\n    std::size_t node_count()\
    \ const { return _pool->size(); }\n\n    void release() {\n        if (_pool)\
    \ _pool->release(_root);\n        _pool = std::make_shared<Pool>();\n        _root\
    \ = 0;\n    }\n\n    PersistentDynamicSegtree set(Index p, T x) const {\n    \
    \    assert(left_bound() <= p && p < right_bound());\n        return PersistentDynamicSegtree(_config,\
    \ _pool,\n                                        set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x)));\n    }\n\n    void set_inplace(Index p,\
    \ T x) {\n        assert(left_bound() <= p && p < right_bound());\n        int\
    \ root = set_node(_root, left_bound(), right_bound(), 0, p, std::move(x), true);\n\
    \        _pool->replace(_root, root);\n    }\n\n    T get(Index p) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        int t = _root;\n\
    \        Index left = left_bound();\n        Index right = right_bound();\n\n\
    \        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) return (*_pool)[t].val;\n            if (p <\
    \ middle) {\n                t = (*_pool)[t].left;\n                right = middle;\n\
    \            } else {\n                t = (*_pool)[t].right;\n              \
    \  left = middle;\n            }\n        }\n        return initial_value();\n\
    \    }\n\n    T operator[](Index p) const { return get(p); }\n\n    T prod(Index\
    \ left, Index right) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return Monoid::id();\n\
    \        return prod_node(_root, left_bound(), right_bound(), 0, left, right);\n\
    \    }\n\n    T all_prod() const { return value(_root, left_bound(), right_bound(),\
    \ 0); }\n\n    template <class F>\n    Index max_right(Index left, F predicate)\
    \ const {\n        assert(left_bound() <= left && left <= right_bound());\n  \
    \      assert(predicate(Monoid::id()));\n        if (left == right_bound()) return\
    \ right_bound();\n        T product = Monoid::id();\n        return max_right_node(_root,\
    \ left_bound(), right_bound(), 0, left, product, predicate);\n    }\n\n    template\
    \ <class F>\n    Index min_left(Index right, F predicate) const {\n        assert(left_bound()\
    \ <= right && right <= right_bound());\n        assert(predicate(Monoid::id()));\n\
    \        if (right == left_bound()) return left_bound();\n        T product =\
    \ Monoid::id();\n        return min_left_node(_root, left_bound(), right_bound(),\
    \ 0, right, product, predicate);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 10 \"ds/segtree/rollback_dynamic_segtree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct RollbackDynamicSegtree\n    : detail::RollbackPersistentBase<PersistentDynamicSegtree<Monoid,\
    \ Index>> {\n    using T = typename Monoid::value_type;\n\n   private:\n    using\
    \ Persistent = PersistentDynamicSegtree<Monoid, Index>;\n    using Base = detail::RollbackPersistentBase<Persistent>;\n\
    \n   public:\n    using Base::Base;\n\n    void set(Index pos, T value) {\n  \
    \      Base::commit(Base::persistent().set(pos, std::move(value)));\n    }\n \
    \   void set_inplace(Index pos, T value) { set(pos, std::move(value)); }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP\
    \ 1\n\n#include <concepts>\n#include <type_traits>\n#include <utility>\n\n#include\
    \ \"../detail/rollback_persistent_base.hpp\"\n#include \"persistent_dynamic_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid,\
    \ std::integral Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct RollbackDynamicSegtree\n    : detail::RollbackPersistentBase<PersistentDynamicSegtree<Monoid,\
    \ Index>> {\n    using T = typename Monoid::value_type;\n\n   private:\n    using\
    \ Persistent = PersistentDynamicSegtree<Monoid, Index>;\n    using Base = detail::RollbackPersistentBase<Persistent>;\n\
    \n   public:\n    using Base::Base;\n\n    void set(Index pos, T value) {\n  \
    \      Base::commit(Base::persistent().set(pos, std::move(value)));\n    }\n \
    \   void set_inplace(Index pos, T value) { set(pos, std::move(value)); }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/segtree/persistent_dynamic_segtree.hpp
  - monoid/concept.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_dynamic_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_dynamic_segtree.hpp
layout: document
title: Rollback Dynamic Segment Tree
---

## Overview

`RollbackDynamicSegtree<Monoid, Index>` is a sparse segment tree over an
integral half-open domain with point assignment and rollback. Unvisited ranges
retain the configured initial value.

## Methods

Constructors and read-only domain, product, boundary-search, and node-count
methods match `PersistentDynamicSegtree<Monoid, Index>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one assignment. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |
| `const PersistentDynamicSegtree<Monoid, Index>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$U$ is the domain width and $F = O(\log U)$ per assignment.

## Example

```cpp
#include "ds/segtree/rollback_dynamic_segtree.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDynamicSegtree<Add> seg(-100, 100);
int state = seg.snapshot();
seg.set(-4, 7);
seg.rollback(state);
assert(seg.all_prod() == 0);
```
