---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
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
  bundledCode: "#line 1 \"ds/segtree/rollback_dynamic_lazy_segtree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n#include\
    \ <numeric>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    #line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \n\n#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 7 \"ds/detail/rollback_journal.hpp\"\n#include <cstdint>\n#line 11 \"ds/detail/rollback_journal.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\n\
    struct RollbackJournal {\n    struct Change {\n        int index;\n        Node\
    \ value;\n    };\n\n    struct Checkpoint {\n        std::size_t change_size;\n\
    \        std::size_t node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node>\
    \ nodes;\n    std::vector<Change> changes;\n    std::vector<Checkpoint> checkpoints;\n\
    \    std::vector<std::uint64_t> saved_epoch;\n    std::uint64_t next_epoch = 1;\n\
    \n    std::uint64_t new_epoch() {\n        if (next_epoch == 0) {\n          \
    \  std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n            next_epoch\
    \ = 1;\n        }\n        return next_epoch++;\n    }\n\n    int size() const\
    \ { return int(nodes.size()); }\n\n    Node& operator[](int index) { return nodes[index];\
    \ }\n    const Node& operator[](int index) const { return nodes[index]; }\n\n\
    \    template <class... Args>\n    int emplace(Args&&... args) {\n        assert(nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        int index = int(nodes.size());\n\
    \        nodes.emplace_back(std::forward<Args>(args)...);\n        saved_epoch.push_back(0);\n\
    \        return index;\n    }\n\n    int snapshot() {\n        assert(checkpoints.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        checkpoints.push_back(Checkpoint{changes.size(),\
    \ nodes.size(), new_epoch()});\n        return int(checkpoints.size());\n    }\n\
    \n    void touch(int index) {\n        assert(0 <= index && index < size());\n\
    \        if (checkpoints.empty()) return;\n        const Checkpoint& checkpoint\
    \ = checkpoints.back();\n        if (std::size_t(index) >= checkpoint.node_size)\
    \ return;\n        if (saved_epoch[index] == checkpoint.epoch) return;\n     \
    \   saved_epoch[index] = checkpoint.epoch;\n        changes.push_back(Change{index,\
    \ nodes[index]});\n    }\n\n    int snapshot_count() const { return int(checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        checkpoints.reserve(count);\n    }\n\n    void reserve_changes(std::size_t\
    \ count) { changes.reserve(count); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        Checkpoint checkpoint\
    \ = checkpoints[state - 1];\n        while (changes.size() > checkpoint.change_size)\
    \ {\n            Change change = std::move(changes.back());\n            changes.pop_back();\n\
    \            nodes[change.index] = std::move(change.value);\n        }\n     \
    \   nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n        saved_epoch.resize(checkpoint.node_size);\n\
    \        checkpoints.resize(state);\n        checkpoints.back().change_size =\
    \ changes.size();\n        checkpoints.back().node_size = nodes.size();\n    \
    \    checkpoints.back().epoch = new_epoch();\n    }\n\n    void clear_history()\
    \ {\n        changes.clear();\n        checkpoints.clear();\n        std::fill(saved_epoch.begin(),\
    \ saved_epoch.end(), 0);\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        changes.clear();\n        checkpoints.clear();\n        saved_epoch.clear();\n\
    \        next_epoch = 1;\n    }\n};\n\n}  // namespace detail\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing\
    \ dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
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
    \n\n#line 16 \"ds/segtree/rollback_dynamic_lazy_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A sparse lazy segment tree over an integral half-open\
    \ interval.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid, std::integral\
    \ Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct RollbackDynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        bool has_lazy;\n\n        explicit Node(T value)\n            : val(std::move(value)),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(0),\n         \
    \     right(0),\n              has_lazy(false) {}\n    };\n\n    detail::UniformMonoidDomain<ActedMonoid,\
    \ Index> _domain;\n    detail::RollbackJournal<Node> _journal;\n\n    int root()\
    \ const { return _journal[0].left; }\n\n    int new_node(Index left, Index right,\
    \ int depth) {\n        assert(_journal.nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        return _journal.emplace(_domain.default_product(depth, left, right));\n\
    \    }\n\n    const T& value(int t, Index left, Index right, int depth) const\
    \ {\n        if (t) return _journal[t].val;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void all_apply(int& t, Index left, Index right,\
    \ int depth, const F& f) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        _journal.touch(t);\n        Node& node = _journal[t];\n        node.val\
    \ = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n        if (std::midpoint(left,\
    \ right) != left) {\n            node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \            node.has_lazy = true;\n        }\n    }\n\n    void push(int t, Index\
    \ left, Index right, int depth) {\n        if (!_journal[t].has_lazy) return;\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ return;\n\n        F lazy = _journal[t].lazy;\n        int left_child = _journal[t].left;\n\
    \        int right_child = _journal[t].right;\n        all_apply(left_child, left,\
    \ middle, depth + 1, lazy);\n        all_apply(\n            right_child,\n  \
    \          middle,\n            right,\n            depth + 1,\n            detail::dynamic_shift<ActedMonoid>(lazy,\
    \ detail::dynamic_distance(left, middle))\n        );\n\n        _journal.touch(t);\n\
    \        Node& node = _journal[t];\n        node.left = left_child;\n        node.right\
    \ = right_child;\n        node.lazy = ActedMonoid::op_id();\n        node.has_lazy\
    \ = false;\n    }\n\n    void update(int t, Index left, Index right, int depth)\
    \ {\n        _journal.touch(t);\n        Index middle = std::midpoint(left, right);\n\
    \        _journal[t].val = ActedMonoid::op(\n            value(_journal[t].left,\
    \ left, middle, depth + 1),\n            value(_journal[t].right, middle, right,\
    \ depth + 1)\n        );\n    }\n\n    int set_node(int t, Index left, Index right,\
    \ int depth, Index p, T x) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ {\n            _journal.touch(t);\n            Node& node = _journal[t];\n \
    \           node.val = std::move(x);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n\n    \
    \    push(t, left, right, depth);\n        if (p < middle) {\n            int\
    \ child = set_node(_journal[t].left, left, middle, depth + 1, p, std::move(x));\n\
    \            _journal.touch(t);\n            _journal[t].left = child;\n     \
    \   } else {\n            int child = set_node(_journal[t].right, middle, right,\
    \ depth + 1, p, std::move(x));\n            _journal.touch(t);\n            _journal[t].right\
    \ = child;\n        }\n        update(t, left, right, depth);\n        return\
    \ t;\n    }\n\n    int apply_node(\n        int t,\n        Index left,\n    \
    \    Index right,\n        int depth,\n        Index query_left,\n        Index\
    \ query_right,\n        const F& f\n    ) {\n        if (query_right <= left ||\
    \ right <= query_left) return t;\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                t,\n                left,\n     \
    \           right,\n                depth,\n                detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left))\n            );\n            return\
    \ t;\n        }\n\n        if (!t) t = new_node(left, right, depth);\n       \
    \ push(t, left, right, depth);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node(_journal[t].left, left, middle, depth + 1,\
    \ query_left, query_right, f);\n        int right_child = apply_node(_journal[t].right,\
    \ middle, right, depth + 1, query_left, query_right, f);\n        _journal.touch(t);\n\
    \        _journal[t].left = left_child;\n        _journal[t].right = right_child;\n\
    \        update(t, left, right, depth);\n        return t;\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !_journal[t].has_lazy) return shifted;\n       \
    \ return ActedMonoid::op_comp(\n            shifted,\n            detail::dynamic_shift<ActedMonoid>(_journal[t].lazy,\
    \ offset)\n        );\n    }\n\n    T prod_node(\n        int t,\n        Index\
    \ left,\n        Index right,\n        int depth,\n        Index query_left,\n\
    \        Index query_right,\n        const F& inherited\n    ) const {\n     \
    \   if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(\n                inherited,\n        \
    \        value(t, left, right, depth)\n            );\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        return ActedMonoid::op(\n    \
    \        prod_node(\n                t ? _journal[t].left : 0,\n             \
    \   left,\n                middle,\n                depth + 1,\n             \
    \   query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ t, 0)\n            ),\n            prod_node(\n                t ? _journal[t].right\
    \ : 0,\n                middle,\n                right,\n                depth\
    \ + 1,\n                query_left,\n                query_right,\n          \
    \      compose_for_child(inherited, t, detail::dynamic_distance(left, middle))\n\
    \            )\n        );\n    }\n\n    template <class G>\n    Index max_right_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        int depth,\n\
    \        Index query_left,\n        T& product,\n        const F& inherited,\n\
    \        G& predicate\n    ) const {\n        if (right <= query_left) return\
    \ right;\n        if (query_left <= left) {\n            T next = ActedMonoid::op(\n\
    \                product,\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                )\n            );\n            if (predicate(next)) {\n     \
    \           product = std::move(next);\n                return right;\n      \
    \      }\n            Index middle = std::midpoint(left, right);\n           \
    \ if (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(\n            t ? _journal[t].left\
    \ : 0,\n            left,\n            middle,\n            depth + 1,\n     \
    \       query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, 0),\n            predicate\n        );\n        if (result < middle) return\
    \ result;\n        return max_right_node(\n            t ? _journal[t].right :\
    \ 0,\n            middle,\n            right,\n            depth + 1,\n      \
    \      query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n    }\n\n    template <class G>\n    Index min_left_node(\n        int t,\n\
    \        Index left,\n        Index right,\n        int depth,\n        Index\
    \ query_right,\n        T& product,\n        const F& inherited,\n        G& predicate\n\
    \    ) const {\n        if (query_right <= left) return left;\n        if (right\
    \ <= query_right) {\n            T next = ActedMonoid::op(\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                ),\n                product\n            );\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return left;\n\
    \            }\n            Index middle = std::midpoint(left, right);\n     \
    \       if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = min_left_node(\n            t ? _journal[t].right\
    \ : 0,\n            middle,\n            right,\n            depth + 1,\n    \
    \        query_right,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n        if (middle < result) return result;\n        return min_left_node(\n\
    \            t ? _journal[t].left : 0,\n            left,\n            middle,\n\
    \            depth + 1,\n            query_right,\n            product,\n    \
    \        compose_for_child(inherited, t, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    RollbackDynamicLazySegtree()\n        : RollbackDynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit RollbackDynamicLazySegtree(Index\
    \ n)\n        : RollbackDynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n\
    \        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n \
    \   }\n\n    RollbackDynamicLazySegtree(Index left, Index right)\n        : RollbackDynamicLazySegtree(left,\
    \ right, ActedMonoid::id()) {}\n\n    RollbackDynamicLazySegtree(Index left, Index\
    \ right, T initial_value)\n        : _domain(left, right, std::move(initial_value))\
    \ {\n        _journal.emplace(ActedMonoid::id());\n    }\n\n    size_type size()\
    \ const {\n        return _domain.size();\n    }\n\n    bool empty() const {\n\
    \        return _domain.empty();\n    }\n\n    Index left_bound() const {\n  \
    \      return _domain.left_bound();\n    }\n\n    Index right_bound() const {\n\
    \        return _domain.right_bound();\n    }\n\n    const T& initial_value()\
    \ const {\n        return _domain.initial_value();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _journal.nodes.reserve(node_capacity + 1);\n        _journal.saved_epoch.reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _journal.nodes.size()\
    \ - 1;\n    }\n\n    void clear() {\n        if (_journal.snapshot_count() ==\
    \ 0) {\n            _journal.clear();\n            _journal.emplace(ActedMonoid::id());\n\
    \            return;\n        }\n        _journal.touch(0);\n        _journal[0].left\
    \ = 0;\n    }\n\n    void set(Index p, T x) {\n        assert(left_bound() <=\
    \ p && p < right_bound());\n        int next_root = set_node(root(), left_bound(),\
    \ right_bound(), 0, p, std::move(x));\n        if (next_root != root()) {\n  \
    \          _journal.touch(0);\n            _journal[0].left = next_root;\n   \
    \     }\n    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p\
    \ && p < right_bound());\n        return prod(p, p + 1);\n    }\n\n    T operator[](Index\
    \ p) const {\n        return get(p);\n    }\n\n    T prod(Index left, Index right)\
    \ const {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return ActedMonoid::id();\n        return prod_node(\n\
    \            root(),\n            left_bound(),\n            right_bound(),\n\
    \            0,\n            left,\n            right,\n            ActedMonoid::op_id()\n\
    \        );\n    }\n\n    T all_prod() const {\n        return value(root(), left_bound(),\
    \ right_bound(), 0);\n    }\n\n    void apply(Index p, const F& f) {\n       \
    \ assert(left_bound() <= p && p < right_bound());\n        apply(p, p + 1, f);\n\
    \    }\n\n    void apply(Index left, Index right, const F& f) {\n        assert(left_bound()\
    \ <= left && left <= right && right <= right_bound());\n        if (left == right)\
    \ return;\n        int next_root = apply_node(\n            root(), left_bound(),\
    \ right_bound(), 0, left, right, f\n        );\n        if (next_root != root())\
    \ {\n            _journal.touch(0);\n            _journal[0].left = next_root;\n\
    \        }\n    }\n\n    template <class G>\n    Index max_right(Index left, G\
    \ predicate) const {\n        assert(left_bound() <= left && left <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(\n            root(),\n            left_bound(),\n          \
    \  right_bound(),\n            0,\n            left,\n            product,\n \
    \           ActedMonoid::op_id(),\n            predicate\n        );\n    }\n\n\
    \    template <class G>\n    Index min_left(Index right, G predicate) const {\n\
    \        assert(left_bound() <= right && right <= right_bound());\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == left_bound()) return left_bound();\n        T product =\
    \ ActedMonoid::id();\n        return min_left_node(\n            root(),\n   \
    \         left_bound(),\n            right_bound(),\n            0,\n        \
    \    right,\n            product,\n            ActedMonoid::op_id(),\n       \
    \     predicate\n        );\n    }\n\n    void set_inplace(Index p, T x) { set(p,\
    \ std::move(x)); }\n    void apply_inplace(Index p, const F& f) { apply(p, f);\
    \ }\n    void apply_inplace(Index left, Index right, const F& f) { apply(left,\
    \ right, f); }\n\n    int snapshot() { return _journal.snapshot(); }\n    int\
    \ snapshot_count() const { return _journal.snapshot_count(); }\n    void reserve_snapshots(int\
    \ count) { _journal.reserve_snapshots(count); }\n    void rollback(int state)\
    \ { _journal.rollback(state); }\n    void clear_history() { _journal.clear_history();\
    \ }\n    void release() { _journal.clear(); _journal.emplace(ActedMonoid::id());\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_LAZY_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_LAZY_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n\
    #include <numeric>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../acted_monoid/concept.hpp\"\n#include \"../detail/rollback_journal.hpp\"\
    \n#include \"dynamic_segtree_common.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// A sparse lazy segment tree over an integral half-open interval.\ntemplate\
    \ <m1une::acted_monoid::IsActedMonoid ActedMonoid, std::integral Index = long\
    \ long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct RollbackDynamicLazySegtree\
    \ {\n    using T = typename ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        F lazy;\n        int\
    \ left;\n        int right;\n        bool has_lazy;\n\n        explicit Node(T\
    \ value)\n            : val(std::move(value)),\n              lazy(ActedMonoid::op_id()),\n\
    \              left(0),\n              right(0),\n              has_lazy(false)\
    \ {}\n    };\n\n    detail::UniformMonoidDomain<ActedMonoid, Index> _domain;\n\
    \    detail::RollbackJournal<Node> _journal;\n\n    int root() const { return\
    \ _journal[0].left; }\n\n    int new_node(Index left, Index right, int depth)\
    \ {\n        assert(_journal.nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        return _journal.emplace(_domain.default_product(depth, left, right));\n\
    \    }\n\n    const T& value(int t, Index left, Index right, int depth) const\
    \ {\n        if (t) return _journal[t].val;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void all_apply(int& t, Index left, Index right,\
    \ int depth, const F& f) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        _journal.touch(t);\n        Node& node = _journal[t];\n        node.val\
    \ = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n        if (std::midpoint(left,\
    \ right) != left) {\n            node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \            node.has_lazy = true;\n        }\n    }\n\n    void push(int t, Index\
    \ left, Index right, int depth) {\n        if (!_journal[t].has_lazy) return;\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ return;\n\n        F lazy = _journal[t].lazy;\n        int left_child = _journal[t].left;\n\
    \        int right_child = _journal[t].right;\n        all_apply(left_child, left,\
    \ middle, depth + 1, lazy);\n        all_apply(\n            right_child,\n  \
    \          middle,\n            right,\n            depth + 1,\n            detail::dynamic_shift<ActedMonoid>(lazy,\
    \ detail::dynamic_distance(left, middle))\n        );\n\n        _journal.touch(t);\n\
    \        Node& node = _journal[t];\n        node.left = left_child;\n        node.right\
    \ = right_child;\n        node.lazy = ActedMonoid::op_id();\n        node.has_lazy\
    \ = false;\n    }\n\n    void update(int t, Index left, Index right, int depth)\
    \ {\n        _journal.touch(t);\n        Index middle = std::midpoint(left, right);\n\
    \        _journal[t].val = ActedMonoid::op(\n            value(_journal[t].left,\
    \ left, middle, depth + 1),\n            value(_journal[t].right, middle, right,\
    \ depth + 1)\n        );\n    }\n\n    int set_node(int t, Index left, Index right,\
    \ int depth, Index p, T x) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ {\n            _journal.touch(t);\n            Node& node = _journal[t];\n \
    \           node.val = std::move(x);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n\n    \
    \    push(t, left, right, depth);\n        if (p < middle) {\n            int\
    \ child = set_node(_journal[t].left, left, middle, depth + 1, p, std::move(x));\n\
    \            _journal.touch(t);\n            _journal[t].left = child;\n     \
    \   } else {\n            int child = set_node(_journal[t].right, middle, right,\
    \ depth + 1, p, std::move(x));\n            _journal.touch(t);\n            _journal[t].right\
    \ = child;\n        }\n        update(t, left, right, depth);\n        return\
    \ t;\n    }\n\n    int apply_node(\n        int t,\n        Index left,\n    \
    \    Index right,\n        int depth,\n        Index query_left,\n        Index\
    \ query_right,\n        const F& f\n    ) {\n        if (query_right <= left ||\
    \ right <= query_left) return t;\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                t,\n                left,\n     \
    \           right,\n                depth,\n                detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left))\n            );\n            return\
    \ t;\n        }\n\n        if (!t) t = new_node(left, right, depth);\n       \
    \ push(t, left, right, depth);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node(_journal[t].left, left, middle, depth + 1,\
    \ query_left, query_right, f);\n        int right_child = apply_node(_journal[t].right,\
    \ middle, right, depth + 1, query_left, query_right, f);\n        _journal.touch(t);\n\
    \        _journal[t].left = left_child;\n        _journal[t].right = right_child;\n\
    \        update(t, left, right, depth);\n        return t;\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !_journal[t].has_lazy) return shifted;\n       \
    \ return ActedMonoid::op_comp(\n            shifted,\n            detail::dynamic_shift<ActedMonoid>(_journal[t].lazy,\
    \ offset)\n        );\n    }\n\n    T prod_node(\n        int t,\n        Index\
    \ left,\n        Index right,\n        int depth,\n        Index query_left,\n\
    \        Index query_right,\n        const F& inherited\n    ) const {\n     \
    \   if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(\n                inherited,\n        \
    \        value(t, left, right, depth)\n            );\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        return ActedMonoid::op(\n    \
    \        prod_node(\n                t ? _journal[t].left : 0,\n             \
    \   left,\n                middle,\n                depth + 1,\n             \
    \   query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ t, 0)\n            ),\n            prod_node(\n                t ? _journal[t].right\
    \ : 0,\n                middle,\n                right,\n                depth\
    \ + 1,\n                query_left,\n                query_right,\n          \
    \      compose_for_child(inherited, t, detail::dynamic_distance(left, middle))\n\
    \            )\n        );\n    }\n\n    template <class G>\n    Index max_right_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        int depth,\n\
    \        Index query_left,\n        T& product,\n        const F& inherited,\n\
    \        G& predicate\n    ) const {\n        if (right <= query_left) return\
    \ right;\n        if (query_left <= left) {\n            T next = ActedMonoid::op(\n\
    \                product,\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                )\n            );\n            if (predicate(next)) {\n     \
    \           product = std::move(next);\n                return right;\n      \
    \      }\n            Index middle = std::midpoint(left, right);\n           \
    \ if (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(\n            t ? _journal[t].left\
    \ : 0,\n            left,\n            middle,\n            depth + 1,\n     \
    \       query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, 0),\n            predicate\n        );\n        if (result < middle) return\
    \ result;\n        return max_right_node(\n            t ? _journal[t].right :\
    \ 0,\n            middle,\n            right,\n            depth + 1,\n      \
    \      query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n    }\n\n    template <class G>\n    Index min_left_node(\n        int t,\n\
    \        Index left,\n        Index right,\n        int depth,\n        Index\
    \ query_right,\n        T& product,\n        const F& inherited,\n        G& predicate\n\
    \    ) const {\n        if (query_right <= left) return left;\n        if (right\
    \ <= query_right) {\n            T next = ActedMonoid::op(\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                ),\n                product\n            );\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return left;\n\
    \            }\n            Index middle = std::midpoint(left, right);\n     \
    \       if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = min_left_node(\n            t ? _journal[t].right\
    \ : 0,\n            middle,\n            right,\n            depth + 1,\n    \
    \        query_right,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n        if (middle < result) return result;\n        return min_left_node(\n\
    \            t ? _journal[t].left : 0,\n            left,\n            middle,\n\
    \            depth + 1,\n            query_right,\n            product,\n    \
    \        compose_for_child(inherited, t, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    RollbackDynamicLazySegtree()\n        : RollbackDynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit RollbackDynamicLazySegtree(Index\
    \ n)\n        : RollbackDynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n\
    \        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n \
    \   }\n\n    RollbackDynamicLazySegtree(Index left, Index right)\n        : RollbackDynamicLazySegtree(left,\
    \ right, ActedMonoid::id()) {}\n\n    RollbackDynamicLazySegtree(Index left, Index\
    \ right, T initial_value)\n        : _domain(left, right, std::move(initial_value))\
    \ {\n        _journal.emplace(ActedMonoid::id());\n    }\n\n    size_type size()\
    \ const {\n        return _domain.size();\n    }\n\n    bool empty() const {\n\
    \        return _domain.empty();\n    }\n\n    Index left_bound() const {\n  \
    \      return _domain.left_bound();\n    }\n\n    Index right_bound() const {\n\
    \        return _domain.right_bound();\n    }\n\n    const T& initial_value()\
    \ const {\n        return _domain.initial_value();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _journal.nodes.reserve(node_capacity + 1);\n        _journal.saved_epoch.reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _journal.nodes.size()\
    \ - 1;\n    }\n\n    void clear() {\n        if (_journal.snapshot_count() ==\
    \ 0) {\n            _journal.clear();\n            _journal.emplace(ActedMonoid::id());\n\
    \            return;\n        }\n        _journal.touch(0);\n        _journal[0].left\
    \ = 0;\n    }\n\n    void set(Index p, T x) {\n        assert(left_bound() <=\
    \ p && p < right_bound());\n        int next_root = set_node(root(), left_bound(),\
    \ right_bound(), 0, p, std::move(x));\n        if (next_root != root()) {\n  \
    \          _journal.touch(0);\n            _journal[0].left = next_root;\n   \
    \     }\n    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p\
    \ && p < right_bound());\n        return prod(p, p + 1);\n    }\n\n    T operator[](Index\
    \ p) const {\n        return get(p);\n    }\n\n    T prod(Index left, Index right)\
    \ const {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return ActedMonoid::id();\n        return prod_node(\n\
    \            root(),\n            left_bound(),\n            right_bound(),\n\
    \            0,\n            left,\n            right,\n            ActedMonoid::op_id()\n\
    \        );\n    }\n\n    T all_prod() const {\n        return value(root(), left_bound(),\
    \ right_bound(), 0);\n    }\n\n    void apply(Index p, const F& f) {\n       \
    \ assert(left_bound() <= p && p < right_bound());\n        apply(p, p + 1, f);\n\
    \    }\n\n    void apply(Index left, Index right, const F& f) {\n        assert(left_bound()\
    \ <= left && left <= right && right <= right_bound());\n        if (left == right)\
    \ return;\n        int next_root = apply_node(\n            root(), left_bound(),\
    \ right_bound(), 0, left, right, f\n        );\n        if (next_root != root())\
    \ {\n            _journal.touch(0);\n            _journal[0].left = next_root;\n\
    \        }\n    }\n\n    template <class G>\n    Index max_right(Index left, G\
    \ predicate) const {\n        assert(left_bound() <= left && left <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(\n            root(),\n            left_bound(),\n          \
    \  right_bound(),\n            0,\n            left,\n            product,\n \
    \           ActedMonoid::op_id(),\n            predicate\n        );\n    }\n\n\
    \    template <class G>\n    Index min_left(Index right, G predicate) const {\n\
    \        assert(left_bound() <= right && right <= right_bound());\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == left_bound()) return left_bound();\n        T product =\
    \ ActedMonoid::id();\n        return min_left_node(\n            root(),\n   \
    \         left_bound(),\n            right_bound(),\n            0,\n        \
    \    right,\n            product,\n            ActedMonoid::op_id(),\n       \
    \     predicate\n        );\n    }\n\n    void set_inplace(Index p, T x) { set(p,\
    \ std::move(x)); }\n    void apply_inplace(Index p, const F& f) { apply(p, f);\
    \ }\n    void apply_inplace(Index left, Index right, const F& f) { apply(left,\
    \ right, f); }\n\n    int snapshot() { return _journal.snapshot(); }\n    int\
    \ snapshot_count() const { return _journal.snapshot_count(); }\n    void reserve_snapshots(int\
    \ count) { _journal.reserve_snapshots(count); }\n    void rollback(int state)\
    \ { _journal.rollback(state); }\n    void clear_history() { _journal.clear_history();\
    \ }\n    void release() { _journal.clear(); _journal.emplace(ActedMonoid::id());\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_dynamic_lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_dynamic_lazy_segtree.hpp
layout: document
title: Rollback Dynamic Lazy Segment Tree
---

## Overview

`RollbackDynamicLazySegtree<ActedMonoid, Index>` is a sparse lazy segment tree
with point assignment, range actions, range products, and rollback over an
integral half-open domain.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Resets the logical tree to its initial value. | $O(P)$ without snapshots; $O(1)$ with an active snapshot |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `void apply(Index pos, const F& f)`, `void apply(Index left, Index right, const F& f)` | Applies an action to a point or range. | $O(\log U)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log U)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |

$U$ is the domain width, $P$ is the number of materialized nodes, and $F$ is
the number of saved or newly allocated nodes discarded by the operation.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a materialized node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/rollback_dynamic_lazy_segtree.hpp"

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackDynamicLazySegtree<AM> seg(0, 100, AM::id());
int state = seg.snapshot();
seg.set(3, AM::make(2));
seg.apply(3, 4, 5);
seg.rollback(state);
assert(seg.get(3).sum == 0);
```
