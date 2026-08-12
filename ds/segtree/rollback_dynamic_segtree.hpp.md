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
  bundledCode: "#line 1 \"ds/segtree/rollback_dynamic_segtree.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include\
    \ <numeric>\n#include <type_traits>\n#include <utility>\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
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
    \n\n#line 15 \"ds/segtree/rollback_dynamic_segtree.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral Index\
    \ = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct\
    \ RollbackDynamicSegtree {\n    using T = typename Monoid::value_type;\n    using\
    \ index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T value = Monoid::id();\n        int\
    \ left = 0;\n        int right = 0;\n    };\n\n    static constexpr int path_capacity\
    \ = std::numeric_limits<size_type>::digits + 1;\n    detail::UniformMonoidDomain<Monoid,\
    \ Index> _domain;\n    detail::RollbackJournal<Node> _journal;\n\n    int root()\
    \ const { return _journal[0].left; }\n\n    int new_node() { return _journal.emplace();\
    \ }\n\n    const T& value(int node, Index left, Index right, int depth) const\
    \ {\n        if (node) return _journal[node].value;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void update(int node, Index left, Index right, int\
    \ depth) {\n        Index middle = std::midpoint(left, right);\n        _journal.touch(node);\n\
    \        _journal[node].value = Monoid::op(\n            value(_journal[node].left,\
    \ left, middle, depth + 1),\n            value(_journal[node].right, middle, right,\
    \ depth + 1)\n        );\n    }\n\n    T prod_node(int node, Index left, Index\
    \ right, int depth, Index query_left, Index query_right) const {\n        if (query_right\
    \ <= left || right <= query_left) return Monoid::id();\n        if (query_left\
    \ <= left && right <= query_right) return value(node, left, right, depth);\n \
    \       Index middle = std::midpoint(left, right);\n        return Monoid::op(\n\
    \            prod_node(node ? _journal[node].left : 0, left, middle, depth + 1,\
    \ query_left, query_right),\n            prod_node(node ? _journal[node].right\
    \ : 0, middle, right, depth + 1, query_left, query_right)\n        );\n    }\n\
    \n    template <class Predicate>\n    Index max_right_node(int node, Index left,\
    \ Index right, int depth, Index query_left, T& product,\n                    \
    \     Predicate& predicate) const {\n        if (right <= query_left) return right;\n\
    \        if (query_left <= left) {\n            T next = Monoid::op(product, value(node,\
    \ left, right, depth));\n            if (predicate(next)) {\n                product\
    \ = std::move(next);\n                return right;\n            }\n         \
    \   Index middle = std::midpoint(left, right);\n            if (middle == left)\
    \ return left;\n        }\n        Index middle = std::midpoint(left, right);\n\
    \        Index result = max_right_node(node ? _journal[node].left : 0, left, middle,\
    \ depth + 1,\n                                      query_left, product, predicate);\n\
    \        if (result < middle) return result;\n        return max_right_node(node\
    \ ? _journal[node].right : 0, middle, right, depth + 1,\n                    \
    \          query_left, product, predicate);\n    }\n\n    template <class Predicate>\n\
    \    Index min_left_node(int node, Index left, Index right, int depth, Index query_right,\
    \ T& product,\n                        Predicate& predicate) const {\n       \
    \ if (query_right <= left) return left;\n        if (right <= query_right) {\n\
    \            T next = Monoid::op(value(node, left, right, depth), product);\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return left;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return right;\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        Index result = min_left_node(node\
    \ ? _journal[node].right : 0, middle, right, depth + 1,\n                    \
    \                 query_right, product, predicate);\n        if (middle < result)\
    \ return result;\n        return min_left_node(node ? _journal[node].left : 0,\
    \ left, middle, depth + 1,\n                             query_right, product,\
    \ predicate);\n    }\n\n   public:\n    RollbackDynamicSegtree() : RollbackDynamicSegtree(Index(0),\
    \ Index(0)) {}\n    explicit RollbackDynamicSegtree(Index n) : RollbackDynamicSegtree(Index(0),\
    \ n) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0) <=\
    \ n);\n    }\n    RollbackDynamicSegtree(Index left, Index right)\n        : RollbackDynamicSegtree(left,\
    \ right, Monoid::id()) {}\n    RollbackDynamicSegtree(Index left, Index right,\
    \ T initial_value)\n        : _domain(left, right, std::move(initial_value)) {\n\
    \        _journal.emplace();\n    }\n\n    size_type size() const { return _domain.size();\
    \ }\n    bool empty() const { return _domain.empty(); }\n    Index left_bound()\
    \ const { return _domain.left_bound(); }\n    Index right_bound() const { return\
    \ _domain.right_bound(); }\n    const T& initial_value() const { return _domain.initial_value();\
    \ }\n\n    void reserve(std::size_t node_capacity) {\n        _journal.nodes.reserve(node_capacity\
    \ + 1);\n        _journal.saved_epoch.reserve(node_capacity + 1);\n    }\n\n \
    \   std::size_t node_count() const { return _journal.nodes.size() - 1; }\n\n \
    \   void set(Index pos, T x) {\n        assert(left_bound() <= pos && pos < right_bound());\n\
    \        if (!root()) {\n            int node = new_node();\n            _journal.touch(0);\n\
    \            _journal[0].left = node;\n        }\n\n        std::array<int, path_capacity>\
    \ path;\n        std::array<Index, path_capacity> path_left;\n        std::array<Index,\
    \ path_capacity> path_right;\n        int depth = 0;\n        int node = root();\n\
    \        Index left = left_bound();\n        Index right = right_bound();\n\n\
    \        while (true) {\n            path[depth] = node;\n            path_left[depth]\
    \ = left;\n            path_right[depth] = right;\n            ++depth;\n    \
    \        Index middle = std::midpoint(left, right);\n            if (middle ==\
    \ left) break;\n            if (pos < middle) {\n                if (!_journal[node].left)\
    \ {\n                    int child = new_node();\n                    _journal.touch(node);\n\
    \                    _journal[node].left = child;\n                }\n       \
    \         node = _journal[node].left;\n                right = middle;\n     \
    \       } else {\n                if (!_journal[node].right) {\n             \
    \       int child = new_node();\n                    _journal.touch(node);\n \
    \                   _journal[node].right = child;\n                }\n       \
    \         node = _journal[node].right;\n                left = middle;\n     \
    \       }\n        }\n        _journal.touch(node);\n        _journal[node].value\
    \ = std::move(x);\n        for (int index = depth - 2; index >= 0; --index) {\n\
    \            update(path[index], path_left[index], path_right[index], index);\n\
    \        }\n    }\n\n    void set_inplace(Index pos, T x) { set(pos, std::move(x));\
    \ }\n\n    T get(Index pos) const {\n        assert(left_bound() <= pos && pos\
    \ < right_bound());\n        int node = root();\n        Index left = left_bound();\n\
    \        Index right = right_bound();\n        int depth = 0;\n        while (node)\
    \ {\n            Index middle = std::midpoint(left, right);\n            if (middle\
    \ == left) return value(node, left, right, depth);\n            if (pos < middle)\
    \ {\n                node = _journal[node].left;\n                right = middle;\n\
    \            } else {\n                node = _journal[node].right;\n        \
    \        left = middle;\n            }\n            ++depth;\n        }\n    \
    \    return initial_value();\n    }\n\n    T operator[](Index pos) const { return\
    \ get(pos); }\n    T prod(Index left, Index right) const {\n        assert(left_bound()\
    \ <= left && left <= right && right <= right_bound());\n        if (left == right)\
    \ return Monoid::id();\n        return prod_node(root(), left_bound(), right_bound(),\
    \ 0, left, right);\n    }\n    T all_prod() const { return value(root(), left_bound(),\
    \ right_bound(), 0); }\n\n    template <class Predicate>\n    Index max_right(Index\
    \ left, Predicate predicate) const {\n        assert(left_bound() <= left && left\
    \ <= right_bound());\n        assert(predicate(Monoid::id()));\n        if (left\
    \ == right_bound()) return right_bound();\n        T product = Monoid::id();\n\
    \        return max_right_node(root(), left_bound(), right_bound(), 0, left, product,\
    \ predicate);\n    }\n\n    template <class Predicate>\n    Index min_left(Index\
    \ right, Predicate predicate) const {\n        assert(left_bound() <= right &&\
    \ right <= right_bound());\n        assert(predicate(Monoid::id()));\n       \
    \ if (right == left_bound()) return left_bound();\n        T product = Monoid::id();\n\
    \        return min_left_node(root(), left_bound(), right_bound(), 0, right, product,\
    \ predicate);\n    }\n\n    int snapshot() { return _journal.snapshot(); }\n \
    \   int snapshot_count() const { return _journal.snapshot_count(); }\n    void\
    \ reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n    void\
    \ rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _journal.clear(); _journal.emplace();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP\
    \ 1\n\n#include <array>\n#include <cassert>\n#include <concepts>\n#include <limits>\n\
    #include <numeric>\n#include <type_traits>\n#include <utility>\n\n#include \"\
    ../../monoid/concept.hpp\"\n#include \"../detail/rollback_journal.hpp\"\n#include\
    \ \"dynamic_segtree_common.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\ntemplate\
    \ <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>,\
    \ bool>)\nstruct RollbackDynamicSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T value = Monoid::id();\n        int\
    \ left = 0;\n        int right = 0;\n    };\n\n    static constexpr int path_capacity\
    \ = std::numeric_limits<size_type>::digits + 1;\n    detail::UniformMonoidDomain<Monoid,\
    \ Index> _domain;\n    detail::RollbackJournal<Node> _journal;\n\n    int root()\
    \ const { return _journal[0].left; }\n\n    int new_node() { return _journal.emplace();\
    \ }\n\n    const T& value(int node, Index left, Index right, int depth) const\
    \ {\n        if (node) return _journal[node].value;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void update(int node, Index left, Index right, int\
    \ depth) {\n        Index middle = std::midpoint(left, right);\n        _journal.touch(node);\n\
    \        _journal[node].value = Monoid::op(\n            value(_journal[node].left,\
    \ left, middle, depth + 1),\n            value(_journal[node].right, middle, right,\
    \ depth + 1)\n        );\n    }\n\n    T prod_node(int node, Index left, Index\
    \ right, int depth, Index query_left, Index query_right) const {\n        if (query_right\
    \ <= left || right <= query_left) return Monoid::id();\n        if (query_left\
    \ <= left && right <= query_right) return value(node, left, right, depth);\n \
    \       Index middle = std::midpoint(left, right);\n        return Monoid::op(\n\
    \            prod_node(node ? _journal[node].left : 0, left, middle, depth + 1,\
    \ query_left, query_right),\n            prod_node(node ? _journal[node].right\
    \ : 0, middle, right, depth + 1, query_left, query_right)\n        );\n    }\n\
    \n    template <class Predicate>\n    Index max_right_node(int node, Index left,\
    \ Index right, int depth, Index query_left, T& product,\n                    \
    \     Predicate& predicate) const {\n        if (right <= query_left) return right;\n\
    \        if (query_left <= left) {\n            T next = Monoid::op(product, value(node,\
    \ left, right, depth));\n            if (predicate(next)) {\n                product\
    \ = std::move(next);\n                return right;\n            }\n         \
    \   Index middle = std::midpoint(left, right);\n            if (middle == left)\
    \ return left;\n        }\n        Index middle = std::midpoint(left, right);\n\
    \        Index result = max_right_node(node ? _journal[node].left : 0, left, middle,\
    \ depth + 1,\n                                      query_left, product, predicate);\n\
    \        if (result < middle) return result;\n        return max_right_node(node\
    \ ? _journal[node].right : 0, middle, right, depth + 1,\n                    \
    \          query_left, product, predicate);\n    }\n\n    template <class Predicate>\n\
    \    Index min_left_node(int node, Index left, Index right, int depth, Index query_right,\
    \ T& product,\n                        Predicate& predicate) const {\n       \
    \ if (query_right <= left) return left;\n        if (right <= query_right) {\n\
    \            T next = Monoid::op(value(node, left, right, depth), product);\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return left;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return right;\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        Index result = min_left_node(node\
    \ ? _journal[node].right : 0, middle, right, depth + 1,\n                    \
    \                 query_right, product, predicate);\n        if (middle < result)\
    \ return result;\n        return min_left_node(node ? _journal[node].left : 0,\
    \ left, middle, depth + 1,\n                             query_right, product,\
    \ predicate);\n    }\n\n   public:\n    RollbackDynamicSegtree() : RollbackDynamicSegtree(Index(0),\
    \ Index(0)) {}\n    explicit RollbackDynamicSegtree(Index n) : RollbackDynamicSegtree(Index(0),\
    \ n) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0) <=\
    \ n);\n    }\n    RollbackDynamicSegtree(Index left, Index right)\n        : RollbackDynamicSegtree(left,\
    \ right, Monoid::id()) {}\n    RollbackDynamicSegtree(Index left, Index right,\
    \ T initial_value)\n        : _domain(left, right, std::move(initial_value)) {\n\
    \        _journal.emplace();\n    }\n\n    size_type size() const { return _domain.size();\
    \ }\n    bool empty() const { return _domain.empty(); }\n    Index left_bound()\
    \ const { return _domain.left_bound(); }\n    Index right_bound() const { return\
    \ _domain.right_bound(); }\n    const T& initial_value() const { return _domain.initial_value();\
    \ }\n\n    void reserve(std::size_t node_capacity) {\n        _journal.nodes.reserve(node_capacity\
    \ + 1);\n        _journal.saved_epoch.reserve(node_capacity + 1);\n    }\n\n \
    \   std::size_t node_count() const { return _journal.nodes.size() - 1; }\n\n \
    \   void set(Index pos, T x) {\n        assert(left_bound() <= pos && pos < right_bound());\n\
    \        if (!root()) {\n            int node = new_node();\n            _journal.touch(0);\n\
    \            _journal[0].left = node;\n        }\n\n        std::array<int, path_capacity>\
    \ path;\n        std::array<Index, path_capacity> path_left;\n        std::array<Index,\
    \ path_capacity> path_right;\n        int depth = 0;\n        int node = root();\n\
    \        Index left = left_bound();\n        Index right = right_bound();\n\n\
    \        while (true) {\n            path[depth] = node;\n            path_left[depth]\
    \ = left;\n            path_right[depth] = right;\n            ++depth;\n    \
    \        Index middle = std::midpoint(left, right);\n            if (middle ==\
    \ left) break;\n            if (pos < middle) {\n                if (!_journal[node].left)\
    \ {\n                    int child = new_node();\n                    _journal.touch(node);\n\
    \                    _journal[node].left = child;\n                }\n       \
    \         node = _journal[node].left;\n                right = middle;\n     \
    \       } else {\n                if (!_journal[node].right) {\n             \
    \       int child = new_node();\n                    _journal.touch(node);\n \
    \                   _journal[node].right = child;\n                }\n       \
    \         node = _journal[node].right;\n                left = middle;\n     \
    \       }\n        }\n        _journal.touch(node);\n        _journal[node].value\
    \ = std::move(x);\n        for (int index = depth - 2; index >= 0; --index) {\n\
    \            update(path[index], path_left[index], path_right[index], index);\n\
    \        }\n    }\n\n    void set_inplace(Index pos, T x) { set(pos, std::move(x));\
    \ }\n\n    T get(Index pos) const {\n        assert(left_bound() <= pos && pos\
    \ < right_bound());\n        int node = root();\n        Index left = left_bound();\n\
    \        Index right = right_bound();\n        int depth = 0;\n        while (node)\
    \ {\n            Index middle = std::midpoint(left, right);\n            if (middle\
    \ == left) return value(node, left, right, depth);\n            if (pos < middle)\
    \ {\n                node = _journal[node].left;\n                right = middle;\n\
    \            } else {\n                node = _journal[node].right;\n        \
    \        left = middle;\n            }\n            ++depth;\n        }\n    \
    \    return initial_value();\n    }\n\n    T operator[](Index pos) const { return\
    \ get(pos); }\n    T prod(Index left, Index right) const {\n        assert(left_bound()\
    \ <= left && left <= right && right <= right_bound());\n        if (left == right)\
    \ return Monoid::id();\n        return prod_node(root(), left_bound(), right_bound(),\
    \ 0, left, right);\n    }\n    T all_prod() const { return value(root(), left_bound(),\
    \ right_bound(), 0); }\n\n    template <class Predicate>\n    Index max_right(Index\
    \ left, Predicate predicate) const {\n        assert(left_bound() <= left && left\
    \ <= right_bound());\n        assert(predicate(Monoid::id()));\n        if (left\
    \ == right_bound()) return right_bound();\n        T product = Monoid::id();\n\
    \        return max_right_node(root(), left_bound(), right_bound(), 0, left, product,\
    \ predicate);\n    }\n\n    template <class Predicate>\n    Index min_left(Index\
    \ right, Predicate predicate) const {\n        assert(left_bound() <= right &&\
    \ right <= right_bound());\n        assert(predicate(Monoid::id()));\n       \
    \ if (right == left_bound()) return left_bound();\n        T product = Monoid::id();\n\
    \        return min_left_node(root(), left_bound(), right_bound(), 0, right, product,\
    \ predicate);\n    }\n\n    int snapshot() { return _journal.snapshot(); }\n \
    \   int snapshot_count() const { return _journal.snapshot_count(); }\n    void\
    \ reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n    void\
    \ rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _journal.clear(); _journal.emplace();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_dynamic_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
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

Constructors and read-only methods follow `DynamicSegtree<Monoid, Index>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |

$U$ is the domain width and $F = O(\log U)$ per assignment.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a materialized node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

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
