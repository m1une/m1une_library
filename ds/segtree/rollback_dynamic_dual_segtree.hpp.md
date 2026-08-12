---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
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
  bundledCode: "#line 1 \"ds/segtree/rollback_dynamic_dual_segtree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <limits>\n#include <numeric>\n#include\
    \ <type_traits>\n#include <utility>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n\
    #line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Concept to check if a type satisfies the requirements of a Monoid.\n// A Monoid\
    \ must have a `value_type`, an identity element `id()`, and an associative binary\
    \ operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for groups.\
    \ A type satisfying this concept must also obey the group\n// laws; concepts can\
    \ check the interface but not the algebraic properties.\ntemplate <typename M>\n\
    concept IsGroup = IsMonoid<M> && requires(typename M::value_type a) {\n    { M::inv(a)\
    \ } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ groups. Commutativity is a semantic requirement and\n// cannot be checked by\
    \ a C++ concept.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"ds/detail/rollback_journal.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 6 \"ds/detail/rollback_journal.hpp\"\n#include\
    \ <cstddef>\n#include <cstdint>\n#line 10 \"ds/detail/rollback_journal.hpp\"\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n\
    template <class Node>\nstruct RollbackJournal {\n    struct Change {\n       \
    \ int index;\n        Node value;\n    };\n\n    struct Checkpoint {\n       \
    \ std::size_t change_size;\n        std::size_t node_size;\n        std::uint64_t\
    \ epoch;\n    };\n\n    std::vector<Node> nodes;\n    std::vector<Change> changes;\n\
    \    std::vector<Checkpoint> checkpoints;\n    std::vector<std::uint64_t> saved_epoch;\n\
    \    std::uint64_t next_epoch = 1;\n\n    std::uint64_t new_epoch() {\n      \
    \  if (next_epoch == 0) {\n            std::fill(saved_epoch.begin(), saved_epoch.end(),\
    \ 0);\n            next_epoch = 1;\n        }\n        return next_epoch++;\n\
    \    }\n\n    int size() const { return int(nodes.size()); }\n\n    Node& operator[](int\
    \ index) { return nodes[index]; }\n    const Node& operator[](int index) const\
    \ { return nodes[index]; }\n\n    template <class... Args>\n    int emplace(Args&&...\
    \ args) {\n        assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        int index = int(nodes.size());\n        nodes.emplace_back(std::forward<Args>(args)...);\n\
    \        saved_epoch.push_back(0);\n        return index;\n    }\n\n    int snapshot()\
    \ {\n        assert(checkpoints.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        checkpoints.push_back(Checkpoint{changes.size(), nodes.size(), new_epoch()});\n\
    \        return int(checkpoints.size());\n    }\n\n    void touch(int index) {\n\
    \        assert(0 <= index && index < size());\n        if (checkpoints.empty())\
    \ return;\n        const Checkpoint& checkpoint = checkpoints.back();\n      \
    \  if (std::size_t(index) >= checkpoint.node_size) return;\n        if (saved_epoch[index]\
    \ == checkpoint.epoch) return;\n        saved_epoch[index] = checkpoint.epoch;\n\
    \        changes.push_back(Change{index, nodes[index]});\n    }\n\n    int snapshot_count()\
    \ const { return int(checkpoints.size()); }\n\n    void reserve_snapshots(int\
    \ count) {\n        assert(0 <= count);\n        checkpoints.reserve(count);\n\
    \    }\n\n    void reserve_changes(std::size_t count) { changes.reserve(count);\
    \ }\n\n    void rollback(int state) {\n        assert(1 <= state && state <= snapshot_count());\n\
    \        Checkpoint checkpoint = checkpoints[state - 1];\n        while (changes.size()\
    \ > checkpoint.change_size) {\n            Change change = std::move(changes.back());\n\
    \            changes.pop_back();\n            nodes[change.index] = std::move(change.value);\n\
    \        }\n        nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n\
    \        saved_epoch.resize(checkpoint.node_size);\n        checkpoints.resize(state);\n\
    \        checkpoints.back().change_size = changes.size();\n        checkpoints.back().node_size\
    \ = nodes.size();\n        checkpoints.back().epoch = new_epoch();\n    }\n\n\
    \    void clear_history() {\n        changes.clear();\n        checkpoints.clear();\n\
    \        std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n    }\n\n    void\
    \ clear() {\n        nodes.clear();\n        changes.clear();\n        checkpoints.clear();\n\
    \        saved_epoch.clear();\n        next_epoch = 1;\n    }\n};\n\n}  // namespace\
    \ detail\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\
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
    \n\n#line 14 \"ds/segtree/rollback_dynamic_dual_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct RollbackDynamicDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T value = Monoid::id();\n        int\
    \ left = 0;\n        int right = 0;\n        bool has_value = false;\n    };\n\
    \n    Index _left;\n    Index _right;\n    T _initial_value;\n    detail::RollbackJournal<Node>\
    \ _journal;\n\n    int root() const { return _journal[0].left; }\n    int new_node()\
    \ { return _journal.emplace(); }\n\n    int ensure(int node) { return node ? node\
    \ : new_node(); }\n\n    void all_apply(int node, Index left, Index right, const\
    \ T& value) {\n        _journal.touch(node);\n        Node& current = _journal[node];\n\
    \        if (std::midpoint(left, right) == left) {\n            T old = current.has_value\
    \ ? current.value : _initial_value;\n            current.value = Monoid::op(value,\
    \ old);\n        } else {\n            current.value = current.has_value ? Monoid::op(value,\
    \ current.value) : value;\n        }\n        current.has_value = true;\n    }\n\
    \n    void push(int node, Index left, Index right) {\n        if (!_journal[node].has_value)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n        T lazy = _journal[node].value;\n        int left_child\
    \ = ensure(_journal[node].left);\n        int right_child = ensure(_journal[node].right);\n\
    \        all_apply(left_child, left, middle, lazy);\n        all_apply(right_child,\
    \ middle, right, lazy);\n        _journal.touch(node);\n        _journal[node].left\
    \ = left_child;\n        _journal[node].right = right_child;\n        _journal[node].value\
    \ = Monoid::id();\n        _journal[node].has_value = false;\n    }\n\n    int\
    \ set_node(int node, Index left, Index right, Index pos, T value) {\n        node\
    \ = ensure(node);\n        Index middle = std::midpoint(left, right);\n      \
    \  if (middle == left) {\n            _journal.touch(node);\n            _journal[node].value\
    \ = std::move(value);\n            _journal[node].has_value = true;\n        \
    \    return node;\n        }\n        push(node, left, right);\n        if (pos\
    \ < middle) {\n            int child = set_node(_journal[node].left, left, middle,\
    \ pos, std::move(value));\n            _journal.touch(node);\n            _journal[node].left\
    \ = child;\n        } else {\n            int child = set_node(_journal[node].right,\
    \ middle, right, pos, std::move(value));\n            _journal.touch(node);\n\
    \            _journal[node].right = child;\n        }\n        return node;\n\
    \    }\n\n    int apply_node(int node, Index left, Index right, Index query_left,\
    \ Index query_right, const T& value) {\n        if (query_right <= left || right\
    \ <= query_left) return node;\n        node = ensure(node);\n        if (query_left\
    \ <= left && right <= query_right) {\n            all_apply(node, left, right,\
    \ value);\n            return node;\n        }\n        push(node, left, right);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node(_journal[node].left, left, middle, query_left, query_right, value);\n\
    \        int right_child = apply_node(_journal[node].right, middle, right, query_left,\
    \ query_right, value);\n        _journal.touch(node);\n        _journal[node].left\
    \ = left_child;\n        _journal[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    RollbackDynamicDualSegtree()\n        : RollbackDynamicDualSegtree(Index(0),\
    \ Index(0), Monoid::id()) {}\n    explicit RollbackDynamicDualSegtree(Index n)\n\
    \        : RollbackDynamicDualSegtree(Index(0), n, Monoid::id()) {\n        if\
    \ constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n    RollbackDynamicDualSegtree(Index\
    \ left, Index right)\n        : RollbackDynamicDualSegtree(left, right, Monoid::id())\
    \ {}\n    RollbackDynamicDualSegtree(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        _journal.emplace();\n    }\n\n  \
    \  size_type size() const { return detail::dynamic_distance(_left, _right); }\n\
    \    bool empty() const { return _left == _right; }\n    Index left_bound() const\
    \ { return _left; }\n    Index right_bound() const { return _right; }\n    const\
    \ T& initial_value() const { return _initial_value; }\n    std::size_t node_count()\
    \ const { return _journal.nodes.size() - 1; }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _journal.nodes.reserve(node_capacity + 1);\n     \
    \   _journal.saved_epoch.reserve(node_capacity + 1);\n    }\n\n    void set(Index\
    \ pos, T value) {\n        assert(_left <= pos && pos < _right);\n        int\
    \ next_root = set_node(root(), _left, _right, pos, std::move(value));\n      \
    \  if (next_root != root()) {\n            _journal.touch(0);\n            _journal[0].left\
    \ = next_root;\n        }\n    }\n    void set_inplace(Index pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    T get(Index pos) const {\n        assert(_left <=\
    \ pos && pos < _right);\n        int node = root();\n        Index left = _left;\n\
    \        Index right = _right;\n        T inherited = Monoid::id();\n        while\
    \ (node) {\n            Index middle = std::midpoint(left, right);\n         \
    \   if (middle == left) {\n                T value = _journal[node].has_value\
    \ ? _journal[node].value : _initial_value;\n                return Monoid::op(inherited,\
    \ value);\n            }\n            if (_journal[node].has_value) inherited\
    \ = Monoid::op(inherited, _journal[node].value);\n            if (pos < middle)\
    \ {\n                node = _journal[node].left;\n                right = middle;\n\
    \            } else {\n                node = _journal[node].right;\n        \
    \        left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ _initial_value);\n    }\n    T operator[](Index pos) const { return get(pos);\
    \ }\n\n    void apply(Index pos, const T& value) { apply(pos, pos + 1, value);\
    \ }\n    void apply(Index left, Index right, const T& value) {\n        assert(_left\
    \ <= left && left <= right && right <= _right);\n        if (left == right) return;\n\
    \        int next_root = apply_node(root(), _left, _right, left, right, value);\n\
    \        if (next_root != root()) {\n            _journal.touch(0);\n        \
    \    _journal[0].left = next_root;\n        }\n    }\n    void apply_inplace(Index\
    \ pos, const T& value) { apply(pos, value); }\n    void apply_inplace(Index left,\
    \ Index right, const T& value) { apply(left, right, value); }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _journal.clear(); _journal.emplace();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include <numeric>\n\
    #include <type_traits>\n#include <utility>\n\n#include \"../../monoid/concept.hpp\"\
    \n#include \"../detail/rollback_journal.hpp\"\n#include \"dynamic_segtree_common.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid,\
    \ std::integral Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct RollbackDynamicDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T value = Monoid::id();\n        int\
    \ left = 0;\n        int right = 0;\n        bool has_value = false;\n    };\n\
    \n    Index _left;\n    Index _right;\n    T _initial_value;\n    detail::RollbackJournal<Node>\
    \ _journal;\n\n    int root() const { return _journal[0].left; }\n    int new_node()\
    \ { return _journal.emplace(); }\n\n    int ensure(int node) { return node ? node\
    \ : new_node(); }\n\n    void all_apply(int node, Index left, Index right, const\
    \ T& value) {\n        _journal.touch(node);\n        Node& current = _journal[node];\n\
    \        if (std::midpoint(left, right) == left) {\n            T old = current.has_value\
    \ ? current.value : _initial_value;\n            current.value = Monoid::op(value,\
    \ old);\n        } else {\n            current.value = current.has_value ? Monoid::op(value,\
    \ current.value) : value;\n        }\n        current.has_value = true;\n    }\n\
    \n    void push(int node, Index left, Index right) {\n        if (!_journal[node].has_value)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n        T lazy = _journal[node].value;\n        int left_child\
    \ = ensure(_journal[node].left);\n        int right_child = ensure(_journal[node].right);\n\
    \        all_apply(left_child, left, middle, lazy);\n        all_apply(right_child,\
    \ middle, right, lazy);\n        _journal.touch(node);\n        _journal[node].left\
    \ = left_child;\n        _journal[node].right = right_child;\n        _journal[node].value\
    \ = Monoid::id();\n        _journal[node].has_value = false;\n    }\n\n    int\
    \ set_node(int node, Index left, Index right, Index pos, T value) {\n        node\
    \ = ensure(node);\n        Index middle = std::midpoint(left, right);\n      \
    \  if (middle == left) {\n            _journal.touch(node);\n            _journal[node].value\
    \ = std::move(value);\n            _journal[node].has_value = true;\n        \
    \    return node;\n        }\n        push(node, left, right);\n        if (pos\
    \ < middle) {\n            int child = set_node(_journal[node].left, left, middle,\
    \ pos, std::move(value));\n            _journal.touch(node);\n            _journal[node].left\
    \ = child;\n        } else {\n            int child = set_node(_journal[node].right,\
    \ middle, right, pos, std::move(value));\n            _journal.touch(node);\n\
    \            _journal[node].right = child;\n        }\n        return node;\n\
    \    }\n\n    int apply_node(int node, Index left, Index right, Index query_left,\
    \ Index query_right, const T& value) {\n        if (query_right <= left || right\
    \ <= query_left) return node;\n        node = ensure(node);\n        if (query_left\
    \ <= left && right <= query_right) {\n            all_apply(node, left, right,\
    \ value);\n            return node;\n        }\n        push(node, left, right);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node(_journal[node].left, left, middle, query_left, query_right, value);\n\
    \        int right_child = apply_node(_journal[node].right, middle, right, query_left,\
    \ query_right, value);\n        _journal.touch(node);\n        _journal[node].left\
    \ = left_child;\n        _journal[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    RollbackDynamicDualSegtree()\n        : RollbackDynamicDualSegtree(Index(0),\
    \ Index(0), Monoid::id()) {}\n    explicit RollbackDynamicDualSegtree(Index n)\n\
    \        : RollbackDynamicDualSegtree(Index(0), n, Monoid::id()) {\n        if\
    \ constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n    RollbackDynamicDualSegtree(Index\
    \ left, Index right)\n        : RollbackDynamicDualSegtree(left, right, Monoid::id())\
    \ {}\n    RollbackDynamicDualSegtree(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        _journal.emplace();\n    }\n\n  \
    \  size_type size() const { return detail::dynamic_distance(_left, _right); }\n\
    \    bool empty() const { return _left == _right; }\n    Index left_bound() const\
    \ { return _left; }\n    Index right_bound() const { return _right; }\n    const\
    \ T& initial_value() const { return _initial_value; }\n    std::size_t node_count()\
    \ const { return _journal.nodes.size() - 1; }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _journal.nodes.reserve(node_capacity + 1);\n     \
    \   _journal.saved_epoch.reserve(node_capacity + 1);\n    }\n\n    void set(Index\
    \ pos, T value) {\n        assert(_left <= pos && pos < _right);\n        int\
    \ next_root = set_node(root(), _left, _right, pos, std::move(value));\n      \
    \  if (next_root != root()) {\n            _journal.touch(0);\n            _journal[0].left\
    \ = next_root;\n        }\n    }\n    void set_inplace(Index pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    T get(Index pos) const {\n        assert(_left <=\
    \ pos && pos < _right);\n        int node = root();\n        Index left = _left;\n\
    \        Index right = _right;\n        T inherited = Monoid::id();\n        while\
    \ (node) {\n            Index middle = std::midpoint(left, right);\n         \
    \   if (middle == left) {\n                T value = _journal[node].has_value\
    \ ? _journal[node].value : _initial_value;\n                return Monoid::op(inherited,\
    \ value);\n            }\n            if (_journal[node].has_value) inherited\
    \ = Monoid::op(inherited, _journal[node].value);\n            if (pos < middle)\
    \ {\n                node = _journal[node].left;\n                right = middle;\n\
    \            } else {\n                node = _journal[node].right;\n        \
    \        left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ _initial_value);\n    }\n    T operator[](Index pos) const { return get(pos);\
    \ }\n\n    void apply(Index pos, const T& value) { apply(pos, pos + 1, value);\
    \ }\n    void apply(Index left, Index right, const T& value) {\n        assert(_left\
    \ <= left && left <= right && right <= _right);\n        if (left == right) return;\n\
    \        int next_root = apply_node(root(), _left, _right, left, right, value);\n\
    \        if (next_root != root()) {\n            _journal.touch(0);\n        \
    \    _journal[0].left = next_root;\n        }\n    }\n    void apply_inplace(Index\
    \ pos, const T& value) { apply(pos, value); }\n    void apply_inplace(Index left,\
    \ Index right, const T& value) { apply(left, right, value); }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _journal.clear(); _journal.emplace();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_dynamic_dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_dynamic_dual_segtree.hpp
layout: document
title: Rollback Dynamic Dual Segment Tree
---

## Overview

`RollbackDynamicDualSegtree<Monoid, Index>` is a sparse dual segment tree with
range action composition, point assignment, point queries, and rollback over an
integral half-open domain.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `void apply(Index pos, const T& value)`, `void apply(Index left, Index right, const T& value)` | Composes an action on a point or range. | $O(\log U)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log U)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a materialized node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

## Example

```cpp
#include "ds/segtree/rollback_dynamic_dual_segtree.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDynamicDualSegtree<Add> seg(-100, 100, 0);
int state = seg.snapshot();
seg.apply(-5, 6, 3);
seg.rollback(state);
assert(seg.get(0) == 0);
```
