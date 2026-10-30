---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\n\n\n\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <memory>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
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
    #line 17 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A persistent sparse dual segment tree over an integral\
    \ half-open interval.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct PersistentDynamicDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n        int references;\n        bool has_lazy;\n\n        Node() :\
    \ val(Monoid::id()), left(0), right(0), references(0), has_lazy(false) {}\n  \
    \  };\n\n    struct Config {\n        Index left;\n        Index right;\n    \
    \    T initial_value;\n\n        Config(Index left_bound, Index right_bound, T\
    \ value)\n            : left(left_bound), right(right_bound), initial_value(std::move(value))\
    \ {\n            assert(left <= right);\n        }\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicDualSegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node() const { return _pool->emplace(); }\n\n    int clone_or_new(int\
    \ t, bool copy_on_write = false) const {\n        if (!t) return new_node();\n\
    \        return copy_on_write ? _pool->clone_if_shared(t) : _pool->clone(t);\n\
    \    }\n\n    void all_apply_to_node(int t, Index left, Index right, const T&\
    \ x) const {\n        Node& node = (*_pool)[t];\n        if (std::midpoint(left,\
    \ right) == left) {\n            T value = node.has_lazy ? node.val : _config->initial_value;\n\
    \            node.val = Monoid::op(x, value);\n            node.has_lazy = true;\n\
    \        } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val)\
    \ : x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, const T& x, bool copy_on_write = false) const {\n\
    \        int result = clone_or_new(t, copy_on_write);\n        all_apply_to_node(result,\
    \ left, right, x);\n        return result;\n    }\n\n    void push(int t, Index\
    \ left, Index right, bool copy_on_write = false) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        T lazy = (*_pool)[t].val;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, lazy, copy_on_write);\n  \
    \      int right_child = all_apply_clone((*_pool)[t].right, middle, right, lazy,\
    \ copy_on_write);\n\n        Node& node = (*_pool)[t];\n        _pool->replace(node.left,\
    \ left_child);\n        _pool->replace(node.right, right_child);\n        node.val\
    \ = Monoid::id();\n        node.has_lazy = false;\n    }\n\n    int set_node(int\
    \ t, Index left, Index right, Index p, T x, bool copy_on_write = false) const\
    \ {\n        t = clone_or_new(t, copy_on_write);\n        Index middle = std::midpoint(left,\
    \ right);\n        if (middle == left) {\n            Node& node = (*_pool)[t];\n\
    \            node.val = std::move(x);\n            node.has_lazy = true;\n   \
    \         return t;\n        }\n\n        push(t, left, right, copy_on_write);\n\
    \        if (p < middle) {\n            int child = set_node((*_pool)[t].left,\
    \ left, middle, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ middle, right, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        return t;\n    }\n\n    int apply_node(int t, Index\
    \ left, Index right, Index query_left, Index query_right, const T& x,\n      \
    \             bool copy_on_write = false) const {\n        if (query_right <=\
    \ left || right <= query_left) return t;\n        if (query_left <= left && right\
    \ <= query_right) {\n            return all_apply_clone(t, left, right, x, copy_on_write);\n\
    \        }\n\n        t = clone_or_new(t, copy_on_write);\n        push(t, left,\
    \ right, copy_on_write);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node((*_pool)[t].left, left, middle, query_left,\
    \ query_right, x, copy_on_write);\n        int right_child = apply_node((*_pool)[t].right,\
    \ middle, right, query_left, query_right, x, copy_on_write);\n        _pool->replace((*_pool)[t].left,\
    \ left_child);\n        _pool->replace((*_pool)[t].right, right_child);\n    \
    \    return t;\n    }\n\n    T compose(const T& inherited, int t) const {\n  \
    \      if (!t || !(*_pool)[t].has_lazy) return inherited;\n        return Monoid::op(inherited,\
    \ (*_pool)[t].val);\n    }\n\n   public:\n    PersistentDynamicDualSegtree() :\
    \ PersistentDynamicDualSegtree(Index(0), Index(0), Monoid::id()) {}\n\n    explicit\
    \ PersistentDynamicDualSegtree(Index n) : PersistentDynamicDualSegtree(Index(0),\
    \ n, Monoid::id()) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0)\
    \ <= n);\n    }\n\n    PersistentDynamicDualSegtree(Index left, Index right) :\
    \ PersistentDynamicDualSegtree(left, right, Monoid::id()) {}\n\n    PersistentDynamicDualSegtree(Index\
    \ left, Index right, T initial_value)\n        : _config(std::make_shared<Config>(left,\
    \ right, std::move(initial_value))),\n          _pool(std::make_shared<Pool>()),\n\
    \          _root(0) {}\n\n    PersistentDynamicDualSegtree(const PersistentDynamicDualSegtree&\
    \ other)\n        : _config(other._config), _pool(other._pool), _root(other._root)\
    \ {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicDualSegtree(PersistentDynamicDualSegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicDualSegtree&\
    \ operator=(const PersistentDynamicDualSegtree& other) {\n        if (this ==\
    \ &other) return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicDualSegtree& operator=(PersistentDynamicDualSegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _config = std::move(other._config);\n      \
    \  _pool = std::move(other._pool);\n        _root = other._root;\n        other._root\
    \ = 0;\n        return *this;\n    }\n    ~PersistentDynamicDualSegtree() {\n\
    \        if (_pool) _pool->release(_root);\n    }\n\n    size_type size() const\
    \ { return detail::dynamic_distance(_config->left, _config->right); }\n\n    bool\
    \ empty() const { return _config->left == _config->right; }\n\n    Index left_bound()\
    \ const { return _config->left; }\n\n    Index right_bound() const { return _config->right;\
    \ }\n\n    const T& initial_value() const { return _config->initial_value; }\n\
    \n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity);\n\
    \    }\n\n    std::size_t node_count() const { return _pool->size(); }\n\n   \
    \ void release() {\n        if (_pool) _pool->release(_root);\n        _pool =\
    \ std::make_shared<Pool>();\n        _root = 0;\n    }\n\n    PersistentDynamicDualSegtree\
    \ set(Index p, T x) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        return PersistentDynamicDualSegtree(_config, _pool,\n               \
    \                             set_node(_root, left_bound(), right_bound(), p,\
    \ std::move(x)));\n    }\n\n    void set_inplace(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        int root = set_node(_root, left_bound(),\
    \ right_bound(), p, std::move(x), true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        int t = _root;\n        Index left = left_bound();\n\
    \        Index right = right_bound();\n        T inherited = Monoid::id();\n\n\
    \        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) {\n                T value = (*_pool)[t].has_lazy\
    \ ? (*_pool)[t].val : initial_value();\n                return Monoid::op(inherited,\
    \ value);\n            }\n            inherited = compose(inherited, t);\n   \
    \         if (p < middle) {\n                t = (*_pool)[t].left;\n         \
    \       right = middle;\n            } else {\n                t = (*_pool)[t].right;\n\
    \                left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ initial_value());\n    }\n\n    T operator[](Index p) const { return get(p);\
    \ }\n\n    PersistentDynamicDualSegtree apply(Index p, const T& x) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        return apply(p,\
    \ p + 1, x);\n    }\n\n    PersistentDynamicDualSegtree apply(Index left, Index\
    \ right, const T& x) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return *this;\n    \
    \    return PersistentDynamicDualSegtree(_config, _pool,\n                   \
    \                         apply_node(_root, left_bound(), right_bound(), left,\
    \ right, x));\n    }\n\n    void apply_inplace(Index p, const T& x) {\n      \
    \  assert(left_bound() <= p && p < right_bound());\n        apply_inplace(p, p\
    \ + 1, x);\n    }\n\n    void apply_inplace(Index left, Index right, const T&\
    \ x) {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return;\n        int root = apply_node(_root, left_bound(),\
    \ right_bound(), left, right, x, true);\n        _pool->replace(_root, root);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_DUAL_SEGTREE_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_DUAL_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <memory>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../monoid/concept.hpp\"\n#include \"dynamic_segtree_common.hpp\"\
    \n#include \"persistent_node_pool.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// A persistent sparse dual segment tree over an integral half-open interval.\n\
    template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>\n \
    \   requires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct PersistentDynamicDualSegtree\
    \ {\n    using T = typename Monoid::value_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        int left;\n        int right;\n        int references;\n\
    \        bool has_lazy;\n\n        Node() : val(Monoid::id()), left(0), right(0),\
    \ references(0), has_lazy(false) {}\n    };\n\n    struct Config {\n        Index\
    \ left;\n        Index right;\n        T initial_value;\n\n        Config(Index\
    \ left_bound, Index right_bound, T value)\n            : left(left_bound), right(right_bound),\
    \ initial_value(std::move(value)) {\n            assert(left <= right);\n    \
    \    }\n    };\n\n    std::shared_ptr<const Config> _config;\n    using Pool =\
    \ detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool> _pool;\n    int\
    \ _root;\n\n    PersistentDynamicDualSegtree(std::shared_ptr<const Config> config,\
    \ std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node() const { return _pool->emplace(); }\n\n    int clone_or_new(int\
    \ t, bool copy_on_write = false) const {\n        if (!t) return new_node();\n\
    \        return copy_on_write ? _pool->clone_if_shared(t) : _pool->clone(t);\n\
    \    }\n\n    void all_apply_to_node(int t, Index left, Index right, const T&\
    \ x) const {\n        Node& node = (*_pool)[t];\n        if (std::midpoint(left,\
    \ right) == left) {\n            T value = node.has_lazy ? node.val : _config->initial_value;\n\
    \            node.val = Monoid::op(x, value);\n            node.has_lazy = true;\n\
    \        } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val)\
    \ : x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, const T& x, bool copy_on_write = false) const {\n\
    \        int result = clone_or_new(t, copy_on_write);\n        all_apply_to_node(result,\
    \ left, right, x);\n        return result;\n    }\n\n    void push(int t, Index\
    \ left, Index right, bool copy_on_write = false) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        T lazy = (*_pool)[t].val;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, lazy, copy_on_write);\n  \
    \      int right_child = all_apply_clone((*_pool)[t].right, middle, right, lazy,\
    \ copy_on_write);\n\n        Node& node = (*_pool)[t];\n        _pool->replace(node.left,\
    \ left_child);\n        _pool->replace(node.right, right_child);\n        node.val\
    \ = Monoid::id();\n        node.has_lazy = false;\n    }\n\n    int set_node(int\
    \ t, Index left, Index right, Index p, T x, bool copy_on_write = false) const\
    \ {\n        t = clone_or_new(t, copy_on_write);\n        Index middle = std::midpoint(left,\
    \ right);\n        if (middle == left) {\n            Node& node = (*_pool)[t];\n\
    \            node.val = std::move(x);\n            node.has_lazy = true;\n   \
    \         return t;\n        }\n\n        push(t, left, right, copy_on_write);\n\
    \        if (p < middle) {\n            int child = set_node((*_pool)[t].left,\
    \ left, middle, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ middle, right, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        return t;\n    }\n\n    int apply_node(int t, Index\
    \ left, Index right, Index query_left, Index query_right, const T& x,\n      \
    \             bool copy_on_write = false) const {\n        if (query_right <=\
    \ left || right <= query_left) return t;\n        if (query_left <= left && right\
    \ <= query_right) {\n            return all_apply_clone(t, left, right, x, copy_on_write);\n\
    \        }\n\n        t = clone_or_new(t, copy_on_write);\n        push(t, left,\
    \ right, copy_on_write);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node((*_pool)[t].left, left, middle, query_left,\
    \ query_right, x, copy_on_write);\n        int right_child = apply_node((*_pool)[t].right,\
    \ middle, right, query_left, query_right, x, copy_on_write);\n        _pool->replace((*_pool)[t].left,\
    \ left_child);\n        _pool->replace((*_pool)[t].right, right_child);\n    \
    \    return t;\n    }\n\n    T compose(const T& inherited, int t) const {\n  \
    \      if (!t || !(*_pool)[t].has_lazy) return inherited;\n        return Monoid::op(inherited,\
    \ (*_pool)[t].val);\n    }\n\n   public:\n    PersistentDynamicDualSegtree() :\
    \ PersistentDynamicDualSegtree(Index(0), Index(0), Monoid::id()) {}\n\n    explicit\
    \ PersistentDynamicDualSegtree(Index n) : PersistentDynamicDualSegtree(Index(0),\
    \ n, Monoid::id()) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0)\
    \ <= n);\n    }\n\n    PersistentDynamicDualSegtree(Index left, Index right) :\
    \ PersistentDynamicDualSegtree(left, right, Monoid::id()) {}\n\n    PersistentDynamicDualSegtree(Index\
    \ left, Index right, T initial_value)\n        : _config(std::make_shared<Config>(left,\
    \ right, std::move(initial_value))),\n          _pool(std::make_shared<Pool>()),\n\
    \          _root(0) {}\n\n    PersistentDynamicDualSegtree(const PersistentDynamicDualSegtree&\
    \ other)\n        : _config(other._config), _pool(other._pool), _root(other._root)\
    \ {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicDualSegtree(PersistentDynamicDualSegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicDualSegtree&\
    \ operator=(const PersistentDynamicDualSegtree& other) {\n        if (this ==\
    \ &other) return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicDualSegtree& operator=(PersistentDynamicDualSegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _config = std::move(other._config);\n      \
    \  _pool = std::move(other._pool);\n        _root = other._root;\n        other._root\
    \ = 0;\n        return *this;\n    }\n    ~PersistentDynamicDualSegtree() {\n\
    \        if (_pool) _pool->release(_root);\n    }\n\n    size_type size() const\
    \ { return detail::dynamic_distance(_config->left, _config->right); }\n\n    bool\
    \ empty() const { return _config->left == _config->right; }\n\n    Index left_bound()\
    \ const { return _config->left; }\n\n    Index right_bound() const { return _config->right;\
    \ }\n\n    const T& initial_value() const { return _config->initial_value; }\n\
    \n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity);\n\
    \    }\n\n    std::size_t node_count() const { return _pool->size(); }\n\n   \
    \ void release() {\n        if (_pool) _pool->release(_root);\n        _pool =\
    \ std::make_shared<Pool>();\n        _root = 0;\n    }\n\n    PersistentDynamicDualSegtree\
    \ set(Index p, T x) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        return PersistentDynamicDualSegtree(_config, _pool,\n               \
    \                             set_node(_root, left_bound(), right_bound(), p,\
    \ std::move(x)));\n    }\n\n    void set_inplace(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        int root = set_node(_root, left_bound(),\
    \ right_bound(), p, std::move(x), true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        int t = _root;\n        Index left = left_bound();\n\
    \        Index right = right_bound();\n        T inherited = Monoid::id();\n\n\
    \        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) {\n                T value = (*_pool)[t].has_lazy\
    \ ? (*_pool)[t].val : initial_value();\n                return Monoid::op(inherited,\
    \ value);\n            }\n            inherited = compose(inherited, t);\n   \
    \         if (p < middle) {\n                t = (*_pool)[t].left;\n         \
    \       right = middle;\n            } else {\n                t = (*_pool)[t].right;\n\
    \                left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ initial_value());\n    }\n\n    T operator[](Index p) const { return get(p);\
    \ }\n\n    PersistentDynamicDualSegtree apply(Index p, const T& x) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        return apply(p,\
    \ p + 1, x);\n    }\n\n    PersistentDynamicDualSegtree apply(Index left, Index\
    \ right, const T& x) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return *this;\n    \
    \    return PersistentDynamicDualSegtree(_config, _pool,\n                   \
    \                         apply_node(_root, left_bound(), right_bound(), left,\
    \ right, x));\n    }\n\n    void apply_inplace(Index p, const T& x) {\n      \
    \  assert(left_bound() <= p && p < right_bound());\n        apply_inplace(p, p\
    \ + 1, x);\n    }\n\n    void apply_inplace(Index left, Index right, const T&\
    \ x) {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return;\n        int root = apply_node(_root, left_bound(),\
    \ right_bound(), left, right, x, true);\n        _pool->replace(_root, root);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_DYNAMIC_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/persistent_dynamic_dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_cow.test.cpp
  - verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
documentation_of: ds/segtree/persistent_dynamic_dual_segtree.hpp
layout: document
title: Persistent Dynamic Dual Segment Tree
---

## Overview

`m1une::ds::PersistentDynamicDualSegtree` is a persistent sparse dual segment
tree for range monoid updates and point queries. Each assignment or update
returns a new version while preserving every earlier version.

`apply(l, r, x)` changes each point value `v` in `[l, r)` to
`Monoid::op(x, v)`. This order is preserved for non-commutative monoids.
Untouched coordinates have one uniform `initial_value`.

Versions derived from the same root share a contiguous node pool. Queries do
not push tags, mutate versions, or allocate nodes. Unreferenced nodes are
recycled after version destruction, assignment, or `release()`.

The `_inplace` updates mutate only the current handle with copy-on-write,
cloning shared nodes before a write and reusing unique nodes. Ordinary `set` and
`apply` continue to return new persistent versions.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

## Construction

* `PersistentDynamicDualSegtree()`: creates an empty domain `[0, 0)`.
* `PersistentDynamicDualSegtree(Index n)`: creates `[0, n)` with identity
  values.
* `PersistentDynamicDualSegtree(Index left, Index right)`: creates
  `[left, right)` with identity values.
* `PersistentDynamicDualSegtree(Index left, Index right, T initial_value)`:
  creates a domain with the specified uniform initial point value.

Construction takes $O(1)$ time and storage.

## Methods

Let $U$ be the domain length and $K$ the number of live nodes in the shared
version family.

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial point value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves shared-pool space for `n` nodes. | $O(K)$ |
| `size_t node_count()` | Returns live nodes across shared versions. | $O(1)$ |
| `void release()` | Releases this root and resets the handle to the uniform initial version. | $O(F)$ |
| `PersistentDynamicDualSegtree set(Index p, T x)` | Returns a version assigning `x` at `p`. | $O(\log U)$ |
| `void set_inplace(Index p, T x)` | Assigns `x` in this version using copy-on-write. | $O(\log U)$ |
| `T get(Index p)` | Returns the current value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `PersistentDynamicDualSegtree apply(Index p, T x)` | Returns a version applying `x` at `p`. | $O(\log U)$ |
| `PersistentDynamicDualSegtree apply(Index l, Index r, T x)` | Returns a version applying `x` over `[l, r)`. | $O(\log U)$ |
| `void apply_inplace(Index p, const T& x)` | Applies `x` at `p` in this version using copy-on-write. | $O(\log U)$ |
| `void apply_inplace(Index l, Index r, const T& x)` | Applies `x` over `[l, r)` in this version using copy-on-write. | $O(\log U)$ |

Each new update allocates $O(\log U)$ nodes in the worst case. Copying a
version is $O(1)$. Here $F$ is the number of nodes freed by a release. Released
slots are reused by later updates.

## Example

```cpp
#include "ds/segtree/persistent_dynamic_dual_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicDualSegtree<Add>;

    Seg base(-1'000'000'000LL, 1'000'000'001LL, 0);
    Seg first = base.apply(-100, 200, 7);
    Seg second = first.apply(50, 60, 3);

    std::cout << base.get(55) << "\n";    // 0
    std::cout << first.get(55) << "\n";   // 7
    std::cout << second.get(55) << "\n";  // 10
}
```
