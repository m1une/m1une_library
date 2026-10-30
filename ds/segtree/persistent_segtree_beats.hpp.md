---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_segtree_beats.test.cpp
    title: verify/ds/segtree/persistent_segtree_beats.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/persistent_segtree_beats.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstddef>\n#include <memory>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"beats_acted_monoid/concept.hpp\"\n\
    \n\n\n#line 5 \"beats_acted_monoid/concept.hpp\"\n\n#line 1 \"acted_monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\n// Concept defining the requirements for an Acted Monoid.\ntemplate <typename\
    \ AM>\nconcept IsActedMonoid = requires(typename AM::value_type a, typename AM::value_type\
    \ b, typename AM::operator_type f,\n                                 typename\
    \ AM::operator_type g) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \  // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n//\
    \ Concept for acted monoids whose value monoid is a commutative group.\n// The\
    \ value operation must obey commutativity and inverse laws.\ntemplate <typename\
    \ AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM> && requires(typename\
    \ AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename AM::value_type>;\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 7 \"beats_acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace beats_acted_monoid {\n\n// An acted monoid whose\
    \ action may require descent before it can be applied.\ntemplate <typename AM>\n\
    concept IsBeatsActedMonoid = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename\
    \ AM::value_type x, typename AM::operator_type f) {\n        { AM::can_apply(f,\
    \ x) } -> std::same_as<bool>;\n    };\n\n}  // namespace beats_acted_monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"ds/segtree/persistent_node_pool.hpp\"\n\n\
    \n\n#line 6 \"ds/segtree/persistent_node_pool.hpp\"\n#include <limits>\n#line\
    \ 9 \"ds/segtree/persistent_node_pool.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\nnamespace detail {\n\n// Node must have integer `left`, `right`, and `references`\
    \ members.\ntemplate <class Node>\nstruct PersistentNodePool {\n    std::vector<Node>\
    \ nodes;\n    int first_free = 0;\n    std::size_t live_nodes = 0;\n\n   private:\n\
    \    void release_zero(int node) {\n        int left = nodes[node].left;\n   \
    \     int right = nodes[node].right;\n        nodes[node] = Node();\n        nodes[node].left\
    \ = first_free;\n        first_free = node;\n        --live_nodes;\n        if\
    \ (left && --nodes[left].references == 0) release_zero(left);\n        if (right\
    \ && --nodes[right].references == 0) release_zero(right);\n    }\n\n   public:\n\
    \    PersistentNodePool() { nodes.emplace_back(); }\n\n    void reserve(std::size_t\
    \ capacity) { nodes.reserve(capacity + 1); }\n\n    Node& operator[](int node)\
    \ { return nodes[node]; }\n\n    const Node& operator[](int node) const { return\
    \ nodes[node]; }\n\n    void retain(int node) {\n        if (node) ++nodes[node].references;\n\
    \    }\n\n    void release(int node) {\n        if (!node) return;\n        assert(nodes[node].references\
    \ > 0);\n        if (--nodes[node].references == 0) release_zero(node);\n    }\n\
    \n    template <class... Args>\n    int emplace(Args&&... args) {\n        int\
    \ result;\n        if (!first_free) {\n            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
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
    #line 13 \"ds/segtree/persistent_segtree_beats.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// A persistent Segment Tree Beats for fallible monoid actions.\ntemplate\
    \ <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>\nstruct PersistentSegtreeBeats\
    \ {\n    using value_type = typename ActedMonoid::value_type;\n    using operator_type\
    \ = typename ActedMonoid::operator_type;\n    using T = value_type;\n    using\
    \ F = operator_type;\n\n   private:\n    struct Node {\n        T val;\n     \
    \   F lazy;\n        int left;\n        int right;\n        int references;\n\
    \        bool has_lazy;\n\n        Node()\n            : val(ActedMonoid::id()),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(0),\n         \
    \     right(0),\n              references(0),\n              has_lazy(false) {}\n\
    \n        explicit Node(T value)\n            : val(std::move(value)),\n     \
    \         lazy(ActedMonoid::op_id()),\n              left(0),\n              right(0),\n\
    \              references(0),\n              has_lazy(false) {}\n\n        Node(T\
    \ value, int left_child, int right_child)\n            : val(std::move(value)),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(left_child),\n\
    \              right(right_child),\n              references(0),\n           \
    \   has_lazy(false) {}\n    };\n\n    using Pool = detail::PersistentNodePool<Node>;\n\
    \n    int _n;\n    int _root;\n    std::shared_ptr<Pool> _pool;\n\n    explicit\
    \ PersistentSegtreeBeats(\n        int n,\n        int root,\n        std::shared_ptr<Pool>\
    \ pool\n    ) : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const {\n        return _pool->emplace(node);\n\
    \    }\n\n    int new_node(Node&& node) const {\n        return _pool->emplace(std::move(node));\n\
    \    }\n\n    int clone_node(int node) const {\n        return _pool->clone(node);\n\
    \    }\n\n    template <typename U>\n    static T make_value(const U& value, int\
    \ index) {\n        if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n\
    \            return ActedMonoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) {\n            ActedMonoid::make(x, i);\n        }) {\n          \
    \  return ActedMonoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const F&\
    \ f, const T& value, long long ordinal) {\n        if constexpr (requires(F g,\
    \ T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n        })\
    \ {\n            return ActedMonoid::mapping(f, value, ordinal);\n        } else\
    \ {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\n\
    \    static bool can_apply_at(\n        const F& f,\n        const T& value,\n\
    \        long long ordinal\n    ) {\n        if constexpr (requires(F g, T x,\
    \ long long i) {\n            ActedMonoid::can_apply(g, x, i);\n        }) {\n\
    \            return ActedMonoid::can_apply(f, value, ordinal);\n        } else\
    \ {\n            return ActedMonoid::can_apply(f, value);\n        }\n    }\n\n\
    \    static F shift_operator(const F& f, long long ordinal) {\n        if constexpr\
    \ (requires(F g, long long i) {\n            ActedMonoid::op_shift(g, i);\n  \
    \      }) {\n            return ActedMonoid::op_shift(f, ordinal);\n        }\
    \ else {\n            return f;\n        }\n    }\n\n    int build(int left, int\
    \ right, const std::vector<T>& values) const {\n        if (left == right) return\
    \ 0;\n        if (right - left == 1) return new_node(Node(values[left]));\n  \
    \      int middle = left + (right - left) / 2;\n        int left_child = build(left,\
    \ middle, values);\n        int right_child = build(middle, right, values);\n\
    \        return new_node(Node(\n            ActedMonoid::op(\n               \
    \ (*_pool)[left_child].val,\n                (*_pool)[right_child].val\n     \
    \       ),\n            left_child,\n            right_child\n        ));\n  \
    \  }\n\n    int build(int left, int right, std::vector<T>& values) const {\n \
    \       if (left == right) return 0;\n        if (right - left == 1) {\n     \
    \       return new_node(Node(std::move(values[left])));\n        }\n        int\
    \ middle = left + (right - left) / 2;\n        int left_child = build(left, middle,\
    \ values);\n        int right_child = build(middle, right, values);\n        return\
    \ new_node(Node(\n            ActedMonoid::op(\n                (*_pool)[left_child].val,\n\
    \                (*_pool)[right_child].val\n            ),\n            left_child,\n\
    \            right_child\n        ));\n    }\n\n    template <typename U>\n  \
    \  int build_from_values(\n        int left,\n        int right,\n        const\
    \ std::vector<U>& values\n    ) const {\n        if (left == right) return 0;\n\
    \        if (right - left == 1) {\n            return new_node(Node(make_value(values[left],\
    \ left)));\n        }\n        int middle = left + (right - left) / 2;\n     \
    \   int left_child = build_from_values(left, middle, values);\n        int right_child\
    \ = build_from_values(middle, right, values);\n        return new_node(Node(\n\
    \            ActedMonoid::op(\n                (*_pool)[left_child].val,\n   \
    \             (*_pool)[right_child].val\n            ),\n            left_child,\n\
    \            right_child\n        ));\n    }\n\n    void update(int node) const\
    \ {\n        Node& current = (*_pool)[node];\n        current.val = ActedMonoid::op(\n\
    \            (*_pool)[current.left].val,\n            (*_pool)[current.right].val\n\
    \        );\n    }\n\n    int all_apply_clone(\n        int node,\n        int\
    \ left,\n        int right,\n        const F& f,\n        bool copy_on_write =\
    \ false\n    ) const {\n        int result = copy_on_write ? _pool->clone_if_shared(node)\
    \ : clone_node(node);\n        Node& current = (*_pool)[result];\n        if (can_apply_at(f,\
    \ current.val, 0)) {\n            current.val = mapping_at(f, current.val, 0);\n\
    \            if (right - left > 1) {\n                current.lazy = ActedMonoid::op_comp(f,\
    \ current.lazy);\n                current.has_lazy = true;\n            }\n  \
    \          return result;\n        }\n\n        assert(right - left > 1);\n  \
    \      push(result, left, right, copy_on_write);\n        int middle = left +\
    \ (right - left) / 2;\n        int left_child = all_apply_clone(\n           \
    \ (*_pool)[result].left,\n            left,\n            middle,\n           \
    \ f,\n            copy_on_write\n        );\n        int right_child = all_apply_clone(\n\
    \            (*_pool)[result].right,\n            middle,\n            right,\n\
    \            shift_operator(f, middle - left),\n            copy_on_write\n  \
    \      );\n        _pool->replace((*_pool)[result].left, left_child);\n      \
    \  _pool->replace((*_pool)[result].right, right_child);\n        update(result);\n\
    \        return result;\n    }\n\n    void push(\n        int node,\n        int\
    \ left,\n        int right,\n        bool copy_on_write = false\n    ) const {\n\
    \        if (!(*_pool)[node].has_lazy) return;\n        assert(right - left >\
    \ 1);\n\n        F lazy = (*_pool)[node].lazy;\n        int middle = left + (right\
    \ - left) / 2;\n        int left_child = all_apply_clone(\n            (*_pool)[node].left,\n\
    \            left,\n            middle,\n            lazy,\n            copy_on_write\n\
    \        );\n        int right_child = all_apply_clone(\n            (*_pool)[node].right,\n\
    \            middle,\n            right,\n            shift_operator(lazy, middle\
    \ - left),\n            copy_on_write\n        );\n        _pool->replace((*_pool)[node].left,\
    \ left_child);\n        _pool->replace((*_pool)[node].right, right_child);\n \
    \       Node& current = (*_pool)[node];\n        current.lazy = ActedMonoid::op_id();\n\
    \        current.has_lazy = false;\n    }\n\n    int set_node(\n        int node,\n\
    \        int left,\n        int right,\n        int index,\n        T value,\n\
    \        bool copy_on_write = false\n    ) const {\n        int result = copy_on_write\
    \ ? _pool->clone_if_shared(node) : clone_node(node);\n        if (right - left\
    \ == 1) {\n            Node& current = (*_pool)[result];\n            current.val\
    \ = std::move(value);\n            current.lazy = ActedMonoid::op_id();\n    \
    \        current.has_lazy = false;\n            return result;\n        }\n\n\
    \        push(result, left, right, copy_on_write);\n        int middle = left\
    \ + (right - left) / 2;\n        if (index < middle) {\n            int child\
    \ = set_node(\n                (*_pool)[result].left,\n                left,\n\
    \                middle,\n                index,\n                std::move(value),\n\
    \                copy_on_write\n            );\n            _pool->replace((*_pool)[result].left,\
    \ child);\n        } else {\n            int child = set_node(\n             \
    \   (*_pool)[result].right,\n                middle,\n                right,\n\
    \                index,\n                std::move(value),\n                copy_on_write\n\
    \            );\n            _pool->replace((*_pool)[result].right, child);\n\
    \        }\n        update(result);\n        return result;\n    }\n\n    int\
    \ apply_node(\n        int node,\n        int left,\n        int right,\n    \
    \    int query_left,\n        int query_right,\n        const F& f,\n        bool\
    \ copy_on_write = false\n    ) const {\n        if (query_right <= left || right\
    \ <= query_left) return node;\n        if (query_left <= left && right <= query_right)\
    \ {\n            return all_apply_clone(\n                node,\n            \
    \    left,\n                right,\n                shift_operator(f, left - query_left),\n\
    \                copy_on_write\n            );\n        }\n\n        int result\
    \ = copy_on_write ? _pool->clone_if_shared(node) : clone_node(node);\n       \
    \ push(result, left, right, copy_on_write);\n        int middle = left + (right\
    \ - left) / 2;\n        int left_child = apply_node(\n            (*_pool)[result].left,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right,\n            f,\n            copy_on_write\n        );\n      \
    \  int right_child = apply_node(\n            (*_pool)[result].right,\n      \
    \      middle,\n            right,\n            query_left,\n            query_right,\n\
    \            f,\n            copy_on_write\n        );\n        _pool->replace((*_pool)[result].left,\
    \ left_child);\n        _pool->replace((*_pool)[result].right, right_child);\n\
    \        update(result);\n        return result;\n    }\n\n    int copy_range_node(\n\
    \        int target,\n        int source,\n        int left,\n        int right,\n\
    \        int query_left,\n        int query_right\n    ) const {\n        if (query_right\
    \ <= left || right <= query_left) return target;\n        if (query_left <= left\
    \ && right <= query_right) return source;\n\n        int result = clone_node(target);\n\
    \        int materialized_source = clone_node(source);\n        _pool->retain(materialized_source);\n\
    \        push(result, left, right);\n        push(materialized_source, left, right);\n\
    \n        int middle = left + (right - left) / 2;\n        int left_child = copy_range_node(\n\
    \            (*_pool)[result].left,\n            (*_pool)[materialized_source].left,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right\n        );\n        int right_child = copy_range_node(\n      \
    \      (*_pool)[result].right,\n            (*_pool)[materialized_source].right,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  query_right\n        );\n        _pool->replace((*_pool)[result].left, left_child);\n\
    \        _pool->replace((*_pool)[result].right, right_child);\n        update(result);\n\
    \        _pool->release(materialized_source);\n        return result;\n    }\n\
    \n    F compose_for_child(\n        const F& inherited,\n        const Node& node,\n\
    \        long long ordinal\n    ) const {\n        F shifted = shift_operator(inherited,\
    \ ordinal);\n        if (!node.has_lazy) return shifted;\n        return ActedMonoid::op_comp(\n\
    \            shifted,\n            shift_operator(node.lazy, ordinal)\n      \
    \  );\n    }\n\n    T evaluate_node(\n        int node,\n        int left,\n \
    \       int right,\n        const F& inherited\n    ) const {\n        const Node&\
    \ current = (*_pool)[node];\n        if (can_apply_at(inherited, current.val,\
    \ 0)) {\n            return mapping_at(inherited, current.val, 0);\n        }\n\
    \n        assert(right - left > 1);\n        int middle = left + (right - left)\
    \ / 2;\n        return ActedMonoid::op(\n            evaluate_node(\n        \
    \        current.left,\n                left,\n                middle,\n     \
    \           compose_for_child(inherited, current, 0)\n            ),\n       \
    \     evaluate_node(\n                current.right,\n                middle,\n\
    \                right,\n                compose_for_child(inherited, current,\
    \ middle - left)\n            )\n        );\n    }\n\n    T prod_node(\n     \
    \   int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        const F& inherited\n    ) const {\n       \
    \ if (query_right <= left || right <= query_left) {\n            return ActedMonoid::id();\n\
    \        }\n        if (query_left <= left && right <= query_right) {\n      \
    \      return evaluate_node(node, left, right, inherited);\n        }\n\n    \
    \    const Node& current = (*_pool)[node];\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_node(\n    \
    \            current.left,\n                left,\n                middle,\n \
    \               query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ current, 0)\n            ),\n            prod_node(\n                current.right,\n\
    \                middle,\n                right,\n                query_left,\n\
    \                query_right,\n                compose_for_child(inherited, current,\
    \ middle - left)\n            )\n        );\n    }\n\n    void collect_node(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        const F& inherited,\n        std::vector<T>&\
    \ result\n    ) const {\n        if (query_right <= left || right <= query_left)\
    \ return;\n        const Node& current = (*_pool)[node];\n        if (right -\
    \ left == 1) {\n            result.push_back(mapping_at(inherited, current.val,\
    \ 0));\n            return;\n        }\n\n        int middle = left + (right -\
    \ left) / 2;\n        collect_node(\n            current.left,\n            left,\n\
    \            middle,\n            query_left,\n            query_right,\n    \
    \        compose_for_child(inherited, current, 0),\n            result\n     \
    \   );\n        collect_node(\n            current.right,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       compose_for_child(inherited, current, middle - left),\n            result\n\
    \        );\n    }\n\n    template <class Predicate>\n    int max_right_node(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        T& product,\n        const F& inherited,\n        Predicate& predicate\n\
    \    ) const {\n        if (right <= query_left) return right;\n        if (query_left\
    \ <= left) {\n            T next = ActedMonoid::op(\n                product,\n\
    \                evaluate_node(node, left, right, inherited)\n            );\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return right;\n            }\n            if (right - left ==\
    \ 1) return left;\n        }\n\n        const Node& current = (*_pool)[node];\n\
    \        int middle = left + (right - left) / 2;\n        int result = max_right_node(\n\
    \            current.left,\n            left,\n            middle,\n         \
    \   query_left,\n            product,\n            compose_for_child(inherited,\
    \ current, 0),\n            predicate\n        );\n        if (result < middle)\
    \ return result;\n        return max_right_node(\n            current.right,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  product,\n            compose_for_child(inherited, current, middle - left),\n\
    \            predicate\n        );\n    }\n\n    template <class Predicate>\n\
    \    int min_left_node(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        T& product,\n        const F& inherited,\n\
    \        Predicate& predicate\n    ) const {\n        if (query_right <= left)\
    \ return left;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(\n\
    \                evaluate_node(node, left, right, inherited),\n              \
    \  product\n            );\n            if (predicate(next)) {\n             \
    \   product = std::move(next);\n                return left;\n            }\n\
    \            if (right - left == 1) return right;\n        }\n\n        const\
    \ Node& current = (*_pool)[node];\n        int middle = left + (right - left)\
    \ / 2;\n        int result = min_left_node(\n            current.right,\n    \
    \        middle,\n            right,\n            query_right,\n            product,\n\
    \            compose_for_child(inherited, current, middle - left),\n         \
    \   predicate\n        );\n        if (middle < result) return result;\n     \
    \   return min_left_node(\n            current.left,\n            left,\n    \
    \        middle,\n            query_right,\n            product,\n           \
    \ compose_for_child(inherited, current, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    PersistentSegtreeBeats() : PersistentSegtreeBeats(0)\
    \ {}\n\n    explicit PersistentSegtreeBeats(int n)\n        : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        if (_n >\
    \ 0) {\n            std::vector<T> values(_n, ActedMonoid::id());\n          \
    \  _root = build(0, _n, values);\n        }\n        _pool->retain(_root);\n \
    \   }\n\n    explicit PersistentSegtreeBeats(const std::vector<T>& values)\n \
    \       : _n(int(values.size())),\n          _root(0),\n          _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(values.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, values);\n        _pool->retain(_root);\n    }\n\n    explicit PersistentSegtreeBeats(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _root(0),\n          _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(values.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, values);\n        _pool->retain(_root);\n    }\n\n    template <typename\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x);\
    \ } ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n       \
    \ std::convertible_to<U, T>\n    )\n    explicit PersistentSegtreeBeats(const\
    \ std::vector<U>& values)\n        : _n(int(values.size())),\n          _root(0),\n\
    \          _pool(std::make_shared<Pool>()) {\n        _pool->reserve(values.size()\
    \ * 2);\n        if (_n > 0) _root = build_from_values(0, _n, values);\n     \
    \   _pool->retain(_root);\n    }\n\n    PersistentSegtreeBeats(const PersistentSegtreeBeats&\
    \ other)\n        : _n(other._n), _root(other._root), _pool(other._pool) {\n \
    \       if (_pool) _pool->retain(_root);\n    }\n\n    PersistentSegtreeBeats(PersistentSegtreeBeats&&\
    \ other) noexcept\n        : _n(other._n),\n          _root(other._root),\n  \
    \        _pool(std::move(other._pool)) {\n        other._n = 0;\n        other._root\
    \ = 0;\n    }\n\n    PersistentSegtreeBeats& operator=(\n        const PersistentSegtreeBeats&\
    \ other\n    ) {\n        if (this == &other) return *this;\n        if (other._pool)\
    \ other._pool->retain(other._root);\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentSegtreeBeats& operator=(\n    \
    \    PersistentSegtreeBeats&& other\n    ) noexcept {\n        if (this == &other)\
    \ return *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentSegtreeBeats() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    void release() {\n        if\
    \ (_pool) _pool->release(_root);\n        _pool = std::make_shared<Pool>();\n\
    \        _root = 0;\n        _n = 0;\n    }\n\n    std::size_t node_count() const\
    \ {\n        return _pool ? _pool->size() : 0;\n    }\n\n    PersistentSegtreeBeats\
    \ set(int index, T value) const {\n        assert(0 <= index && index < _n);\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            set_node(_root,\
    \ 0, _n, index, std::move(value)),\n            _pool\n        );\n    }\n\n \
    \   void set_inplace(int index, T value) {\n        assert(0 <= index && index\
    \ < _n);\n        int root = set_node(\n            _root,\n            0,\n \
    \           _n,\n            index,\n            std::move(value),\n         \
    \   true\n        );\n        _pool->replace(_root, root);\n    }\n\n    T get(int\
    \ index) const {\n        assert(0 <= index && index < _n);\n        return prod(index,\
    \ index + 1);\n    }\n\n    T operator[](int index) const {\n        return get(index);\n\
    \    }\n\n    T prod(int left, int right) const {\n        assert(0 <= left &&\
    \ left <= right && right <= _n);\n        if (left == right) return ActedMonoid::id();\n\
    \        return prod_node(\n            _root,\n            0,\n            _n,\n\
    \            left,\n            right,\n            ActedMonoid::op_id()\n   \
    \     );\n    }\n\n    T all_prod() const {\n        return _root ? (*_pool)[_root].val\
    \ : ActedMonoid::id();\n    }\n\n    PersistentSegtreeBeats apply(int index, const\
    \ F& f) const {\n        assert(0 <= index && index < _n);\n        return apply(index,\
    \ index + 1, f);\n    }\n\n    PersistentSegtreeBeats apply(\n        int left,\n\
    \        int right,\n        const F& f\n    ) const {\n        assert(0 <= left\
    \ && left <= right && right <= _n);\n        if (left == right) return *this;\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            apply_node(_root,\
    \ 0, _n, left, right, f),\n            _pool\n        );\n    }\n\n    void apply_inplace(int\
    \ index, const F& f) {\n        assert(0 <= index && index < _n);\n        apply_inplace(index,\
    \ index + 1, f);\n    }\n\n    void apply_inplace(int left, int right, const F&\
    \ f) {\n        assert(0 <= left && left <= right && right <= _n);\n        if\
    \ (left == right) return;\n        int root = apply_node(\n            _root,\n\
    \            0,\n            _n,\n            left,\n            right,\n    \
    \        f,\n            true\n        );\n        _pool->replace(_root, root);\n\
    \    }\n\n    PersistentSegtreeBeats copy_range_from(\n        const PersistentSegtreeBeats&\
    \ source,\n        int left,\n        int right\n    ) const {\n        assert(_n\
    \ == source._n);\n        assert(_pool == source._pool);\n        assert(0 <=\
    \ left && left <= right && right <= _n);\n        if (left == right) return *this;\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            copy_range_node(\n\
    \                _root,\n                source._root,\n                0,\n \
    \               _n,\n                left,\n                right\n          \
    \  ),\n            _pool\n        );\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        std::vector<T> result;\n        result.reserve(right - left);\n\
    \        if (left != right) {\n            collect_node(\n                _root,\n\
    \                0,\n                _n,\n                left,\n            \
    \    right,\n                ActedMonoid::op_id(),\n                result\n \
    \           );\n        }\n        return result;\n    }\n\n    template <class\
    \ Predicate>\n    int max_right(int left, Predicate predicate) const {\n     \
    \   assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        return max_right_node(\n            _root,\n            0,\n        \
    \    _n,\n            left,\n            product,\n            ActedMonoid::op_id(),\n\
    \            predicate\n        );\n    }\n\n    template <class Predicate>\n\
    \    int min_left(int right, Predicate predicate) const {\n        assert(0 <=\
    \ right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n    \
    \    if (right == 0) return 0;\n        T product = ActedMonoid::id();\n     \
    \   return min_left_node(\n            _root,\n            0,\n            _n,\n\
    \            right,\n            product,\n            ActedMonoid::op_id(),\n\
    \            predicate\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_DS_PERSISTENT_SEGTREE_BEATS_HPP\n#define M1UNE_DS_PERSISTENT_SEGTREE_BEATS_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <memory>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../beats_acted_monoid/concept.hpp\"\
    \n#include \"persistent_node_pool.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// A persistent Segment Tree Beats for fallible monoid actions.\ntemplate <m1une::beats_acted_monoid::IsBeatsActedMonoid\
    \ ActedMonoid>\nstruct PersistentSegtreeBeats {\n    using value_type = typename\
    \ ActedMonoid::value_type;\n    using operator_type = typename ActedMonoid::operator_type;\n\
    \    using T = value_type;\n    using F = operator_type;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        int references;\n        bool has_lazy;\n\n        Node()\n         \
    \   : val(ActedMonoid::id()),\n              lazy(ActedMonoid::op_id()),\n   \
    \           left(0),\n              right(0),\n              references(0),\n\
    \              has_lazy(false) {}\n\n        explicit Node(T value)\n        \
    \    : val(std::move(value)),\n              lazy(ActedMonoid::op_id()),\n   \
    \           left(0),\n              right(0),\n              references(0),\n\
    \              has_lazy(false) {}\n\n        Node(T value, int left_child, int\
    \ right_child)\n            : val(std::move(value)),\n              lazy(ActedMonoid::op_id()),\n\
    \              left(left_child),\n              right(right_child),\n        \
    \      references(0),\n              has_lazy(false) {}\n    };\n\n    using Pool\
    \ = detail::PersistentNodePool<Node>;\n\n    int _n;\n    int _root;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    explicit PersistentSegtreeBeats(\n        int n,\n        int\
    \ root,\n        std::shared_ptr<Pool> pool\n    ) : _n(n), _root(root), _pool(std::move(pool))\
    \ {\n        _pool->retain(_root);\n    }\n\n    int new_node(const Node& node)\
    \ const {\n        return _pool->emplace(node);\n    }\n\n    int new_node(Node&&\
    \ node) const {\n        return _pool->emplace(std::move(node));\n    }\n\n  \
    \  int clone_node(int node) const {\n        return _pool->clone(node);\n    }\n\
    \n    template <typename U>\n    static T make_value(const U& value, int index)\
    \ {\n        if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n      \
    \      return ActedMonoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) {\n            ActedMonoid::make(x, i);\n        }) {\n          \
    \  return ActedMonoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const F&\
    \ f, const T& value, long long ordinal) {\n        if constexpr (requires(F g,\
    \ T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n        })\
    \ {\n            return ActedMonoid::mapping(f, value, ordinal);\n        } else\
    \ {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\n\
    \    static bool can_apply_at(\n        const F& f,\n        const T& value,\n\
    \        long long ordinal\n    ) {\n        if constexpr (requires(F g, T x,\
    \ long long i) {\n            ActedMonoid::can_apply(g, x, i);\n        }) {\n\
    \            return ActedMonoid::can_apply(f, value, ordinal);\n        } else\
    \ {\n            return ActedMonoid::can_apply(f, value);\n        }\n    }\n\n\
    \    static F shift_operator(const F& f, long long ordinal) {\n        if constexpr\
    \ (requires(F g, long long i) {\n            ActedMonoid::op_shift(g, i);\n  \
    \      }) {\n            return ActedMonoid::op_shift(f, ordinal);\n        }\
    \ else {\n            return f;\n        }\n    }\n\n    int build(int left, int\
    \ right, const std::vector<T>& values) const {\n        if (left == right) return\
    \ 0;\n        if (right - left == 1) return new_node(Node(values[left]));\n  \
    \      int middle = left + (right - left) / 2;\n        int left_child = build(left,\
    \ middle, values);\n        int right_child = build(middle, right, values);\n\
    \        return new_node(Node(\n            ActedMonoid::op(\n               \
    \ (*_pool)[left_child].val,\n                (*_pool)[right_child].val\n     \
    \       ),\n            left_child,\n            right_child\n        ));\n  \
    \  }\n\n    int build(int left, int right, std::vector<T>& values) const {\n \
    \       if (left == right) return 0;\n        if (right - left == 1) {\n     \
    \       return new_node(Node(std::move(values[left])));\n        }\n        int\
    \ middle = left + (right - left) / 2;\n        int left_child = build(left, middle,\
    \ values);\n        int right_child = build(middle, right, values);\n        return\
    \ new_node(Node(\n            ActedMonoid::op(\n                (*_pool)[left_child].val,\n\
    \                (*_pool)[right_child].val\n            ),\n            left_child,\n\
    \            right_child\n        ));\n    }\n\n    template <typename U>\n  \
    \  int build_from_values(\n        int left,\n        int right,\n        const\
    \ std::vector<U>& values\n    ) const {\n        if (left == right) return 0;\n\
    \        if (right - left == 1) {\n            return new_node(Node(make_value(values[left],\
    \ left)));\n        }\n        int middle = left + (right - left) / 2;\n     \
    \   int left_child = build_from_values(left, middle, values);\n        int right_child\
    \ = build_from_values(middle, right, values);\n        return new_node(Node(\n\
    \            ActedMonoid::op(\n                (*_pool)[left_child].val,\n   \
    \             (*_pool)[right_child].val\n            ),\n            left_child,\n\
    \            right_child\n        ));\n    }\n\n    void update(int node) const\
    \ {\n        Node& current = (*_pool)[node];\n        current.val = ActedMonoid::op(\n\
    \            (*_pool)[current.left].val,\n            (*_pool)[current.right].val\n\
    \        );\n    }\n\n    int all_apply_clone(\n        int node,\n        int\
    \ left,\n        int right,\n        const F& f,\n        bool copy_on_write =\
    \ false\n    ) const {\n        int result = copy_on_write ? _pool->clone_if_shared(node)\
    \ : clone_node(node);\n        Node& current = (*_pool)[result];\n        if (can_apply_at(f,\
    \ current.val, 0)) {\n            current.val = mapping_at(f, current.val, 0);\n\
    \            if (right - left > 1) {\n                current.lazy = ActedMonoid::op_comp(f,\
    \ current.lazy);\n                current.has_lazy = true;\n            }\n  \
    \          return result;\n        }\n\n        assert(right - left > 1);\n  \
    \      push(result, left, right, copy_on_write);\n        int middle = left +\
    \ (right - left) / 2;\n        int left_child = all_apply_clone(\n           \
    \ (*_pool)[result].left,\n            left,\n            middle,\n           \
    \ f,\n            copy_on_write\n        );\n        int right_child = all_apply_clone(\n\
    \            (*_pool)[result].right,\n            middle,\n            right,\n\
    \            shift_operator(f, middle - left),\n            copy_on_write\n  \
    \      );\n        _pool->replace((*_pool)[result].left, left_child);\n      \
    \  _pool->replace((*_pool)[result].right, right_child);\n        update(result);\n\
    \        return result;\n    }\n\n    void push(\n        int node,\n        int\
    \ left,\n        int right,\n        bool copy_on_write = false\n    ) const {\n\
    \        if (!(*_pool)[node].has_lazy) return;\n        assert(right - left >\
    \ 1);\n\n        F lazy = (*_pool)[node].lazy;\n        int middle = left + (right\
    \ - left) / 2;\n        int left_child = all_apply_clone(\n            (*_pool)[node].left,\n\
    \            left,\n            middle,\n            lazy,\n            copy_on_write\n\
    \        );\n        int right_child = all_apply_clone(\n            (*_pool)[node].right,\n\
    \            middle,\n            right,\n            shift_operator(lazy, middle\
    \ - left),\n            copy_on_write\n        );\n        _pool->replace((*_pool)[node].left,\
    \ left_child);\n        _pool->replace((*_pool)[node].right, right_child);\n \
    \       Node& current = (*_pool)[node];\n        current.lazy = ActedMonoid::op_id();\n\
    \        current.has_lazy = false;\n    }\n\n    int set_node(\n        int node,\n\
    \        int left,\n        int right,\n        int index,\n        T value,\n\
    \        bool copy_on_write = false\n    ) const {\n        int result = copy_on_write\
    \ ? _pool->clone_if_shared(node) : clone_node(node);\n        if (right - left\
    \ == 1) {\n            Node& current = (*_pool)[result];\n            current.val\
    \ = std::move(value);\n            current.lazy = ActedMonoid::op_id();\n    \
    \        current.has_lazy = false;\n            return result;\n        }\n\n\
    \        push(result, left, right, copy_on_write);\n        int middle = left\
    \ + (right - left) / 2;\n        if (index < middle) {\n            int child\
    \ = set_node(\n                (*_pool)[result].left,\n                left,\n\
    \                middle,\n                index,\n                std::move(value),\n\
    \                copy_on_write\n            );\n            _pool->replace((*_pool)[result].left,\
    \ child);\n        } else {\n            int child = set_node(\n             \
    \   (*_pool)[result].right,\n                middle,\n                right,\n\
    \                index,\n                std::move(value),\n                copy_on_write\n\
    \            );\n            _pool->replace((*_pool)[result].right, child);\n\
    \        }\n        update(result);\n        return result;\n    }\n\n    int\
    \ apply_node(\n        int node,\n        int left,\n        int right,\n    \
    \    int query_left,\n        int query_right,\n        const F& f,\n        bool\
    \ copy_on_write = false\n    ) const {\n        if (query_right <= left || right\
    \ <= query_left) return node;\n        if (query_left <= left && right <= query_right)\
    \ {\n            return all_apply_clone(\n                node,\n            \
    \    left,\n                right,\n                shift_operator(f, left - query_left),\n\
    \                copy_on_write\n            );\n        }\n\n        int result\
    \ = copy_on_write ? _pool->clone_if_shared(node) : clone_node(node);\n       \
    \ push(result, left, right, copy_on_write);\n        int middle = left + (right\
    \ - left) / 2;\n        int left_child = apply_node(\n            (*_pool)[result].left,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right,\n            f,\n            copy_on_write\n        );\n      \
    \  int right_child = apply_node(\n            (*_pool)[result].right,\n      \
    \      middle,\n            right,\n            query_left,\n            query_right,\n\
    \            f,\n            copy_on_write\n        );\n        _pool->replace((*_pool)[result].left,\
    \ left_child);\n        _pool->replace((*_pool)[result].right, right_child);\n\
    \        update(result);\n        return result;\n    }\n\n    int copy_range_node(\n\
    \        int target,\n        int source,\n        int left,\n        int right,\n\
    \        int query_left,\n        int query_right\n    ) const {\n        if (query_right\
    \ <= left || right <= query_left) return target;\n        if (query_left <= left\
    \ && right <= query_right) return source;\n\n        int result = clone_node(target);\n\
    \        int materialized_source = clone_node(source);\n        _pool->retain(materialized_source);\n\
    \        push(result, left, right);\n        push(materialized_source, left, right);\n\
    \n        int middle = left + (right - left) / 2;\n        int left_child = copy_range_node(\n\
    \            (*_pool)[result].left,\n            (*_pool)[materialized_source].left,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right\n        );\n        int right_child = copy_range_node(\n      \
    \      (*_pool)[result].right,\n            (*_pool)[materialized_source].right,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  query_right\n        );\n        _pool->replace((*_pool)[result].left, left_child);\n\
    \        _pool->replace((*_pool)[result].right, right_child);\n        update(result);\n\
    \        _pool->release(materialized_source);\n        return result;\n    }\n\
    \n    F compose_for_child(\n        const F& inherited,\n        const Node& node,\n\
    \        long long ordinal\n    ) const {\n        F shifted = shift_operator(inherited,\
    \ ordinal);\n        if (!node.has_lazy) return shifted;\n        return ActedMonoid::op_comp(\n\
    \            shifted,\n            shift_operator(node.lazy, ordinal)\n      \
    \  );\n    }\n\n    T evaluate_node(\n        int node,\n        int left,\n \
    \       int right,\n        const F& inherited\n    ) const {\n        const Node&\
    \ current = (*_pool)[node];\n        if (can_apply_at(inherited, current.val,\
    \ 0)) {\n            return mapping_at(inherited, current.val, 0);\n        }\n\
    \n        assert(right - left > 1);\n        int middle = left + (right - left)\
    \ / 2;\n        return ActedMonoid::op(\n            evaluate_node(\n        \
    \        current.left,\n                left,\n                middle,\n     \
    \           compose_for_child(inherited, current, 0)\n            ),\n       \
    \     evaluate_node(\n                current.right,\n                middle,\n\
    \                right,\n                compose_for_child(inherited, current,\
    \ middle - left)\n            )\n        );\n    }\n\n    T prod_node(\n     \
    \   int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        const F& inherited\n    ) const {\n       \
    \ if (query_right <= left || right <= query_left) {\n            return ActedMonoid::id();\n\
    \        }\n        if (query_left <= left && right <= query_right) {\n      \
    \      return evaluate_node(node, left, right, inherited);\n        }\n\n    \
    \    const Node& current = (*_pool)[node];\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_node(\n    \
    \            current.left,\n                left,\n                middle,\n \
    \               query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ current, 0)\n            ),\n            prod_node(\n                current.right,\n\
    \                middle,\n                right,\n                query_left,\n\
    \                query_right,\n                compose_for_child(inherited, current,\
    \ middle - left)\n            )\n        );\n    }\n\n    void collect_node(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        const F& inherited,\n        std::vector<T>&\
    \ result\n    ) const {\n        if (query_right <= left || right <= query_left)\
    \ return;\n        const Node& current = (*_pool)[node];\n        if (right -\
    \ left == 1) {\n            result.push_back(mapping_at(inherited, current.val,\
    \ 0));\n            return;\n        }\n\n        int middle = left + (right -\
    \ left) / 2;\n        collect_node(\n            current.left,\n            left,\n\
    \            middle,\n            query_left,\n            query_right,\n    \
    \        compose_for_child(inherited, current, 0),\n            result\n     \
    \   );\n        collect_node(\n            current.right,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       compose_for_child(inherited, current, middle - left),\n            result\n\
    \        );\n    }\n\n    template <class Predicate>\n    int max_right_node(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        T& product,\n        const F& inherited,\n        Predicate& predicate\n\
    \    ) const {\n        if (right <= query_left) return right;\n        if (query_left\
    \ <= left) {\n            T next = ActedMonoid::op(\n                product,\n\
    \                evaluate_node(node, left, right, inherited)\n            );\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return right;\n            }\n            if (right - left ==\
    \ 1) return left;\n        }\n\n        const Node& current = (*_pool)[node];\n\
    \        int middle = left + (right - left) / 2;\n        int result = max_right_node(\n\
    \            current.left,\n            left,\n            middle,\n         \
    \   query_left,\n            product,\n            compose_for_child(inherited,\
    \ current, 0),\n            predicate\n        );\n        if (result < middle)\
    \ return result;\n        return max_right_node(\n            current.right,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  product,\n            compose_for_child(inherited, current, middle - left),\n\
    \            predicate\n        );\n    }\n\n    template <class Predicate>\n\
    \    int min_left_node(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        T& product,\n        const F& inherited,\n\
    \        Predicate& predicate\n    ) const {\n        if (query_right <= left)\
    \ return left;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(\n\
    \                evaluate_node(node, left, right, inherited),\n              \
    \  product\n            );\n            if (predicate(next)) {\n             \
    \   product = std::move(next);\n                return left;\n            }\n\
    \            if (right - left == 1) return right;\n        }\n\n        const\
    \ Node& current = (*_pool)[node];\n        int middle = left + (right - left)\
    \ / 2;\n        int result = min_left_node(\n            current.right,\n    \
    \        middle,\n            right,\n            query_right,\n            product,\n\
    \            compose_for_child(inherited, current, middle - left),\n         \
    \   predicate\n        );\n        if (middle < result) return result;\n     \
    \   return min_left_node(\n            current.left,\n            left,\n    \
    \        middle,\n            query_right,\n            product,\n           \
    \ compose_for_child(inherited, current, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    PersistentSegtreeBeats() : PersistentSegtreeBeats(0)\
    \ {}\n\n    explicit PersistentSegtreeBeats(int n)\n        : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        if (_n >\
    \ 0) {\n            std::vector<T> values(_n, ActedMonoid::id());\n          \
    \  _root = build(0, _n, values);\n        }\n        _pool->retain(_root);\n \
    \   }\n\n    explicit PersistentSegtreeBeats(const std::vector<T>& values)\n \
    \       : _n(int(values.size())),\n          _root(0),\n          _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(values.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, values);\n        _pool->retain(_root);\n    }\n\n    explicit PersistentSegtreeBeats(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _root(0),\n          _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(values.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, values);\n        _pool->retain(_root);\n    }\n\n    template <typename\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x);\
    \ } ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n       \
    \ std::convertible_to<U, T>\n    )\n    explicit PersistentSegtreeBeats(const\
    \ std::vector<U>& values)\n        : _n(int(values.size())),\n          _root(0),\n\
    \          _pool(std::make_shared<Pool>()) {\n        _pool->reserve(values.size()\
    \ * 2);\n        if (_n > 0) _root = build_from_values(0, _n, values);\n     \
    \   _pool->retain(_root);\n    }\n\n    PersistentSegtreeBeats(const PersistentSegtreeBeats&\
    \ other)\n        : _n(other._n), _root(other._root), _pool(other._pool) {\n \
    \       if (_pool) _pool->retain(_root);\n    }\n\n    PersistentSegtreeBeats(PersistentSegtreeBeats&&\
    \ other) noexcept\n        : _n(other._n),\n          _root(other._root),\n  \
    \        _pool(std::move(other._pool)) {\n        other._n = 0;\n        other._root\
    \ = 0;\n    }\n\n    PersistentSegtreeBeats& operator=(\n        const PersistentSegtreeBeats&\
    \ other\n    ) {\n        if (this == &other) return *this;\n        if (other._pool)\
    \ other._pool->retain(other._root);\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentSegtreeBeats& operator=(\n    \
    \    PersistentSegtreeBeats&& other\n    ) noexcept {\n        if (this == &other)\
    \ return *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentSegtreeBeats() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    void release() {\n        if\
    \ (_pool) _pool->release(_root);\n        _pool = std::make_shared<Pool>();\n\
    \        _root = 0;\n        _n = 0;\n    }\n\n    std::size_t node_count() const\
    \ {\n        return _pool ? _pool->size() : 0;\n    }\n\n    PersistentSegtreeBeats\
    \ set(int index, T value) const {\n        assert(0 <= index && index < _n);\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            set_node(_root,\
    \ 0, _n, index, std::move(value)),\n            _pool\n        );\n    }\n\n \
    \   void set_inplace(int index, T value) {\n        assert(0 <= index && index\
    \ < _n);\n        int root = set_node(\n            _root,\n            0,\n \
    \           _n,\n            index,\n            std::move(value),\n         \
    \   true\n        );\n        _pool->replace(_root, root);\n    }\n\n    T get(int\
    \ index) const {\n        assert(0 <= index && index < _n);\n        return prod(index,\
    \ index + 1);\n    }\n\n    T operator[](int index) const {\n        return get(index);\n\
    \    }\n\n    T prod(int left, int right) const {\n        assert(0 <= left &&\
    \ left <= right && right <= _n);\n        if (left == right) return ActedMonoid::id();\n\
    \        return prod_node(\n            _root,\n            0,\n            _n,\n\
    \            left,\n            right,\n            ActedMonoid::op_id()\n   \
    \     );\n    }\n\n    T all_prod() const {\n        return _root ? (*_pool)[_root].val\
    \ : ActedMonoid::id();\n    }\n\n    PersistentSegtreeBeats apply(int index, const\
    \ F& f) const {\n        assert(0 <= index && index < _n);\n        return apply(index,\
    \ index + 1, f);\n    }\n\n    PersistentSegtreeBeats apply(\n        int left,\n\
    \        int right,\n        const F& f\n    ) const {\n        assert(0 <= left\
    \ && left <= right && right <= _n);\n        if (left == right) return *this;\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            apply_node(_root,\
    \ 0, _n, left, right, f),\n            _pool\n        );\n    }\n\n    void apply_inplace(int\
    \ index, const F& f) {\n        assert(0 <= index && index < _n);\n        apply_inplace(index,\
    \ index + 1, f);\n    }\n\n    void apply_inplace(int left, int right, const F&\
    \ f) {\n        assert(0 <= left && left <= right && right <= _n);\n        if\
    \ (left == right) return;\n        int root = apply_node(\n            _root,\n\
    \            0,\n            _n,\n            left,\n            right,\n    \
    \        f,\n            true\n        );\n        _pool->replace(_root, root);\n\
    \    }\n\n    PersistentSegtreeBeats copy_range_from(\n        const PersistentSegtreeBeats&\
    \ source,\n        int left,\n        int right\n    ) const {\n        assert(_n\
    \ == source._n);\n        assert(_pool == source._pool);\n        assert(0 <=\
    \ left && left <= right && right <= _n);\n        if (left == right) return *this;\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            copy_range_node(\n\
    \                _root,\n                source._root,\n                0,\n \
    \               _n,\n                left,\n                right\n          \
    \  ),\n            _pool\n        );\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        std::vector<T> result;\n        result.reserve(right - left);\n\
    \        if (left != right) {\n            collect_node(\n                _root,\n\
    \                0,\n                _n,\n                left,\n            \
    \    right,\n                ActedMonoid::op_id(),\n                result\n \
    \           );\n        }\n        return result;\n    }\n\n    template <class\
    \ Predicate>\n    int max_right(int left, Predicate predicate) const {\n     \
    \   assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        return max_right_node(\n            _root,\n            0,\n        \
    \    _n,\n            left,\n            product,\n            ActedMonoid::op_id(),\n\
    \            predicate\n        );\n    }\n\n    template <class Predicate>\n\
    \    int min_left(int right, Predicate predicate) const {\n        assert(0 <=\
    \ right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n    \
    \    if (right == 0) return 0;\n        T product = ActedMonoid::id();\n     \
    \   return min_left_node(\n            _root,\n            0,\n            _n,\n\
    \            right,\n            product,\n            ActedMonoid::op_id(),\n\
    \            predicate\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_DS_PERSISTENT_SEGTREE_BEATS_HPP\n"
  dependsOn:
  - beats_acted_monoid/concept.hpp
  - acted_monoid/concept.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/persistent_segtree_beats.hpp
  requiredBy: []
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_cow.test.cpp
  - verify/ds/segtree/persistent_segtree_beats.test.cpp
documentation_of: ds/segtree/persistent_segtree_beats.hpp
layout: document
redirect_from:
- /library/ds/segtree/persistent_segtree_beats.hpp
- /library/ds/segtree/persistent_segtree_beats.hpp.html
title: ds/segtree/persistent_segtree_beats.hpp
---
