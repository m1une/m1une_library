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
    path: math/bit_ceil.hpp
    title: Bit Ceil
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
  bundledCode: "#line 1 \"ds/segtree/rollback_lazy_segtree.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"ds/detail/rollback_journal.hpp\"\n\
    \n\n\n#include <algorithm>\n#line 6 \"ds/detail/rollback_journal.hpp\"\n#include\
    \ <cstddef>\n#include <cstdint>\n#include <limits>\n#line 11 \"ds/detail/rollback_journal.hpp\"\
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
    \ ds\n}  // namespace m1une\n\n\n#line 13 \"ds/segtree/rollback_lazy_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct RollbackLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        T value = ActedMonoid::id();\n        F lazy = ActedMonoid::op_id();\n\
    \        bool has_lazy = false;\n    };\n\n    int _n = 0;\n    int _size = 1;\n\
    \    int _log = 0;\n    detail::RollbackJournal<Node> _journal;\n\n    static\
    \ T mapping_at(const F& f, const T& value, long long ordinal) {\n        if constexpr\
    \ (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n   \
    \         return ActedMonoid::mapping(f, value, ordinal);\n        } else {\n\
    \            return ActedMonoid::mapping(f, value);\n        }\n    }\n\n    static\
    \ F shift_operator(const F& f, long long ordinal) {\n        if constexpr (requires(F\
    \ g, long long i) { ActedMonoid::op_shift(g, i); }) {\n            return ActedMonoid::op_shift(f,\
    \ ordinal);\n        } else {\n            return f;\n        }\n    }\n\n   \
    \ template <class U>\n    static T make_value(const U& value, int index) {\n \
    \       if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n           \
    \ return ActedMonoid::make(value);\n        } else if constexpr (requires(U x,\
    \ int i) { ActedMonoid::make(x, i); }) {\n            return ActedMonoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    int node_length(int node) const {\n        int level = std::bit_width(static_cast<unsigned\
    \ int>(node)) - 1;\n        return _size >> level;\n    }\n\n    int node_left(int\
    \ node) const {\n        int level = std::bit_width(static_cast<unsigned int>(node))\
    \ - 1;\n        int length = _size >> level;\n        return (node - (1 << level))\
    \ * length;\n    }\n\n    void update(int node) {\n        _journal.touch(node);\n\
    \        _journal[node].value = ActedMonoid::op(\n            _journal[node <<\
    \ 1].value,\n            _journal[node << 1 | 1].value\n        );\n    }\n\n\
    \    void all_apply(int node, const F& f) {\n        _journal.touch(node);\n \
    \       _journal[node].value = mapping_at(f, _journal[node].value, 0);\n     \
    \   if (node < _size) {\n            _journal[node].lazy = ActedMonoid::op_comp(f,\
    \ _journal[node].lazy);\n            _journal[node].has_lazy = true;\n       \
    \ }\n    }\n\n    void push(int node) {\n        if (!_journal[node].has_lazy)\
    \ return;\n        F lazy = _journal[node].lazy;\n        all_apply(node << 1,\
    \ lazy);\n        all_apply(node << 1 | 1, shift_operator(lazy, node_length(node)\
    \ / 2));\n        _journal.touch(node);\n        _journal[node].lazy = ActedMonoid::op_id();\n\
    \        _journal[node].has_lazy = false;\n    }\n\n    template <class U>\n \
    \   void build(const std::vector<U>& values) {\n        _n = int(values.size());\n\
    \        _size = int(m1une::math::bit_ceil(static_cast<unsigned int>(_n)));\n\
    \        _log = 0;\n        while ((1U << _log) < static_cast<unsigned int>(_size))\
    \ ++_log;\n        _journal.nodes.assign(2 * _size, Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n        for (int index = 0; index < _n; ++index) {\n            _journal[_size\
    \ + index].value = make_value(values[index], index);\n        }\n        for (int\
    \ node = _size - 1; node > 0; --node) {\n            _journal[node].value = ActedMonoid::op(\n\
    \                _journal[node << 1].value,\n                _journal[node <<\
    \ 1 | 1].value\n            );\n        }\n    }\n\n   public:\n    RollbackLazySegtree()\
    \ { build(std::vector<T>()); }\n    explicit RollbackLazySegtree(int n) {\n  \
    \      assert(0 <= n);\n        build(std::vector<T>(n, ActedMonoid::id()));\n\
    \    }\n    explicit RollbackLazySegtree(const std::vector<T>& values) { build(values);\
    \ }\n    explicit RollbackLazySegtree(std::vector<T>&& values) { build(values);\
    \ }\n\n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackLazySegtree(const std::vector<U>& values) { build(values); }\n\n   \
    \ int size() const { return _n; }\n    bool empty() const { return _n == 0; }\n\
    \    std::size_t node_count() const { return _journal.nodes.size(); }\n\n    void\
    \ set(int pos, T value) {\n        assert(0 <= pos && pos < _n);\n        int\
    \ node = pos + _size;\n        for (int level = _log; level >= 1; --level) push(node\
    \ >> level);\n        _journal.touch(node);\n        _journal[node].value = std::move(value);\n\
    \        for (int level = 1; level <= _log; ++level) update(node >> level);\n\
    \    }\n\n    void set_inplace(int pos, T value) { set(pos, std::move(value));\
    \ }\n\n    T get(int pos) {\n        assert(0 <= pos && pos < _n);\n        int\
    \ node = pos + _size;\n        for (int level = _log; level >= 1; --level) push(node\
    \ >> level);\n        return _journal[node].value;\n    }\n\n    T operator[](int\
    \ pos) { return get(pos); }\n\n    T prod(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        if (left == right) return\
    \ ActedMonoid::id();\n        left += _size;\n        right += _size;\n      \
    \  for (int level = _log; level >= 1; --level) {\n            if (((left >> level)\
    \ << level) != left) push(left >> level);\n            if (((right >> level) <<\
    \ level) != right) push((right - 1) >> level);\n        }\n        T left_product\
    \ = ActedMonoid::id();\n        T right_product = ActedMonoid::id();\n       \
    \ while (left < right) {\n            if (left & 1) left_product = ActedMonoid::op(left_product,\
    \ _journal[left++].value);\n            if (right & 1) right_product = ActedMonoid::op(_journal[--right].value,\
    \ right_product);\n            left >>= 1;\n            right >>= 1;\n       \
    \ }\n        return ActedMonoid::op(left_product, right_product);\n    }\n\n \
    \   T all_prod() const { return _journal[1].value; }\n\n    std::vector<T> to_vector()\
    \ {\n        for (int node = 1; node < _size; ++node) push(node);\n        std::vector<T>\
    \ result;\n        result.reserve(_n);\n        for (int index = 0; index < _n;\
    \ ++index) result.push_back(_journal[_size + index].value);\n        return result;\n\
    \    }\n\n    std::vector<T> to_vector(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        std::vector<T> result;\n\
    \        result.reserve(right - left);\n        for (int index = left; index <\
    \ right; ++index) result.push_back(get(index));\n        return result;\n    }\n\
    \n    void apply(int pos, const F& f) {\n        assert(0 <= pos && pos < _n);\n\
    \        int node = pos + _size;\n        for (int level = _log; level >= 1; --level)\
    \ push(node >> level);\n        _journal.touch(node);\n        _journal[node].value\
    \ = mapping_at(f, _journal[node].value, 0);\n        for (int level = 1; level\
    \ <= _log; ++level) update(node >> level);\n    }\n\n    void apply(int left,\
    \ int right, const F& f) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (left == right) return;\n        int base_left = left;\n\
    \        left += _size;\n        right += _size;\n        for (int level = _log;\
    \ level >= 1; --level) {\n            if (((left >> level) << level) != left)\
    \ push(left >> level);\n            if (((right >> level) << level) != right)\
    \ push((right - 1) >> level);\n        }\n        int saved_left = left;\n   \
    \     int saved_right = right;\n        while (left < right) {\n            if\
    \ (left & 1) {\n                all_apply(left, shift_operator(f, node_left(left)\
    \ - base_left));\n                ++left;\n            }\n            if (right\
    \ & 1) {\n                --right;\n                all_apply(right, shift_operator(f,\
    \ node_left(right) - base_left));\n            }\n            left >>= 1;\n  \
    \          right >>= 1;\n        }\n        left = saved_left;\n        right\
    \ = saved_right;\n        for (int level = 1; level <= _log; ++level) {\n    \
    \        if (((left >> level) << level) != left) update(left >> level);\n    \
    \        if (((right >> level) << level) != right) update((right - 1) >> level);\n\
    \        }\n    }\n\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        int node = left + _size;\n      \
    \  for (int level = _log; level >= 1; --level) push(node >> level);\n        T\
    \ product = ActedMonoid::id();\n        do {\n            while ((node & 1) ==\
    \ 0) node >>= 1;\n            T next = ActedMonoid::op(product, _journal[node].value);\n\
    \            if (!predicate(next)) {\n                while (node < _size) {\n\
    \                    push(node);\n                    node <<= 1;\n          \
    \          next = ActedMonoid::op(product, _journal[node].value);\n          \
    \          if (predicate(next)) {\n                        product = std::move(next);\n\
    \                        ++node;\n                    }\n                }\n \
    \               return node - _size;\n            }\n            product = std::move(next);\n\
    \            ++node;\n        } while ((node & -node) != node);\n        return\
    \ _n;\n    }\n\n    template <class Predicate>\n    int min_left(int right, Predicate\
    \ predicate) {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        int node = right + _size;\n      \
    \  for (int level = _log; level >= 1; --level) push((node - 1) >> level);\n  \
    \      T product = ActedMonoid::id();\n        do {\n            --node;\n   \
    \         while (node > 1 && (node & 1)) node >>= 1;\n            T next = ActedMonoid::op(_journal[node].value,\
    \ product);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    push(node);\n                    node = node\
    \ << 1 | 1;\n                    next = ActedMonoid::op(_journal[node].value,\
    \ product);\n                    if (predicate(next)) {\n                    \
    \    product = std::move(next);\n                        --node;\n           \
    \         }\n                }\n                return node + 1 - _size;\n   \
    \         }\n            product = std::move(next);\n        } while ((node &\
    \ -node) != node);\n        return 0;\n    }\n\n    int snapshot() { return _journal.snapshot();\
    \ }\n    int snapshot_count() const { return _journal.snapshot_count(); }\n  \
    \  void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n\
    \    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _n = 0; _size = 1; _log\
    \ = 0; _journal.clear(); }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../acted_monoid/concept.hpp\"\n#include \"\
    ../../math/bit_ceil.hpp\"\n#include \"../detail/rollback_journal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\n\
    struct RollbackLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        T value = ActedMonoid::id();\n        F lazy = ActedMonoid::op_id();\n\
    \        bool has_lazy = false;\n    };\n\n    int _n = 0;\n    int _size = 1;\n\
    \    int _log = 0;\n    detail::RollbackJournal<Node> _journal;\n\n    static\
    \ T mapping_at(const F& f, const T& value, long long ordinal) {\n        if constexpr\
    \ (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n   \
    \         return ActedMonoid::mapping(f, value, ordinal);\n        } else {\n\
    \            return ActedMonoid::mapping(f, value);\n        }\n    }\n\n    static\
    \ F shift_operator(const F& f, long long ordinal) {\n        if constexpr (requires(F\
    \ g, long long i) { ActedMonoid::op_shift(g, i); }) {\n            return ActedMonoid::op_shift(f,\
    \ ordinal);\n        } else {\n            return f;\n        }\n    }\n\n   \
    \ template <class U>\n    static T make_value(const U& value, int index) {\n \
    \       if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n           \
    \ return ActedMonoid::make(value);\n        } else if constexpr (requires(U x,\
    \ int i) { ActedMonoid::make(x, i); }) {\n            return ActedMonoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    int node_length(int node) const {\n        int level = std::bit_width(static_cast<unsigned\
    \ int>(node)) - 1;\n        return _size >> level;\n    }\n\n    int node_left(int\
    \ node) const {\n        int level = std::bit_width(static_cast<unsigned int>(node))\
    \ - 1;\n        int length = _size >> level;\n        return (node - (1 << level))\
    \ * length;\n    }\n\n    void update(int node) {\n        _journal.touch(node);\n\
    \        _journal[node].value = ActedMonoid::op(\n            _journal[node <<\
    \ 1].value,\n            _journal[node << 1 | 1].value\n        );\n    }\n\n\
    \    void all_apply(int node, const F& f) {\n        _journal.touch(node);\n \
    \       _journal[node].value = mapping_at(f, _journal[node].value, 0);\n     \
    \   if (node < _size) {\n            _journal[node].lazy = ActedMonoid::op_comp(f,\
    \ _journal[node].lazy);\n            _journal[node].has_lazy = true;\n       \
    \ }\n    }\n\n    void push(int node) {\n        if (!_journal[node].has_lazy)\
    \ return;\n        F lazy = _journal[node].lazy;\n        all_apply(node << 1,\
    \ lazy);\n        all_apply(node << 1 | 1, shift_operator(lazy, node_length(node)\
    \ / 2));\n        _journal.touch(node);\n        _journal[node].lazy = ActedMonoid::op_id();\n\
    \        _journal[node].has_lazy = false;\n    }\n\n    template <class U>\n \
    \   void build(const std::vector<U>& values) {\n        _n = int(values.size());\n\
    \        _size = int(m1une::math::bit_ceil(static_cast<unsigned int>(_n)));\n\
    \        _log = 0;\n        while ((1U << _log) < static_cast<unsigned int>(_size))\
    \ ++_log;\n        _journal.nodes.assign(2 * _size, Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n        for (int index = 0; index < _n; ++index) {\n            _journal[_size\
    \ + index].value = make_value(values[index], index);\n        }\n        for (int\
    \ node = _size - 1; node > 0; --node) {\n            _journal[node].value = ActedMonoid::op(\n\
    \                _journal[node << 1].value,\n                _journal[node <<\
    \ 1 | 1].value\n            );\n        }\n    }\n\n   public:\n    RollbackLazySegtree()\
    \ { build(std::vector<T>()); }\n    explicit RollbackLazySegtree(int n) {\n  \
    \      assert(0 <= n);\n        build(std::vector<T>(n, ActedMonoid::id()));\n\
    \    }\n    explicit RollbackLazySegtree(const std::vector<T>& values) { build(values);\
    \ }\n    explicit RollbackLazySegtree(std::vector<T>&& values) { build(values);\
    \ }\n\n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackLazySegtree(const std::vector<U>& values) { build(values); }\n\n   \
    \ int size() const { return _n; }\n    bool empty() const { return _n == 0; }\n\
    \    std::size_t node_count() const { return _journal.nodes.size(); }\n\n    void\
    \ set(int pos, T value) {\n        assert(0 <= pos && pos < _n);\n        int\
    \ node = pos + _size;\n        for (int level = _log; level >= 1; --level) push(node\
    \ >> level);\n        _journal.touch(node);\n        _journal[node].value = std::move(value);\n\
    \        for (int level = 1; level <= _log; ++level) update(node >> level);\n\
    \    }\n\n    void set_inplace(int pos, T value) { set(pos, std::move(value));\
    \ }\n\n    T get(int pos) {\n        assert(0 <= pos && pos < _n);\n        int\
    \ node = pos + _size;\n        for (int level = _log; level >= 1; --level) push(node\
    \ >> level);\n        return _journal[node].value;\n    }\n\n    T operator[](int\
    \ pos) { return get(pos); }\n\n    T prod(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        if (left == right) return\
    \ ActedMonoid::id();\n        left += _size;\n        right += _size;\n      \
    \  for (int level = _log; level >= 1; --level) {\n            if (((left >> level)\
    \ << level) != left) push(left >> level);\n            if (((right >> level) <<\
    \ level) != right) push((right - 1) >> level);\n        }\n        T left_product\
    \ = ActedMonoid::id();\n        T right_product = ActedMonoid::id();\n       \
    \ while (left < right) {\n            if (left & 1) left_product = ActedMonoid::op(left_product,\
    \ _journal[left++].value);\n            if (right & 1) right_product = ActedMonoid::op(_journal[--right].value,\
    \ right_product);\n            left >>= 1;\n            right >>= 1;\n       \
    \ }\n        return ActedMonoid::op(left_product, right_product);\n    }\n\n \
    \   T all_prod() const { return _journal[1].value; }\n\n    std::vector<T> to_vector()\
    \ {\n        for (int node = 1; node < _size; ++node) push(node);\n        std::vector<T>\
    \ result;\n        result.reserve(_n);\n        for (int index = 0; index < _n;\
    \ ++index) result.push_back(_journal[_size + index].value);\n        return result;\n\
    \    }\n\n    std::vector<T> to_vector(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        std::vector<T> result;\n\
    \        result.reserve(right - left);\n        for (int index = left; index <\
    \ right; ++index) result.push_back(get(index));\n        return result;\n    }\n\
    \n    void apply(int pos, const F& f) {\n        assert(0 <= pos && pos < _n);\n\
    \        int node = pos + _size;\n        for (int level = _log; level >= 1; --level)\
    \ push(node >> level);\n        _journal.touch(node);\n        _journal[node].value\
    \ = mapping_at(f, _journal[node].value, 0);\n        for (int level = 1; level\
    \ <= _log; ++level) update(node >> level);\n    }\n\n    void apply(int left,\
    \ int right, const F& f) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (left == right) return;\n        int base_left = left;\n\
    \        left += _size;\n        right += _size;\n        for (int level = _log;\
    \ level >= 1; --level) {\n            if (((left >> level) << level) != left)\
    \ push(left >> level);\n            if (((right >> level) << level) != right)\
    \ push((right - 1) >> level);\n        }\n        int saved_left = left;\n   \
    \     int saved_right = right;\n        while (left < right) {\n            if\
    \ (left & 1) {\n                all_apply(left, shift_operator(f, node_left(left)\
    \ - base_left));\n                ++left;\n            }\n            if (right\
    \ & 1) {\n                --right;\n                all_apply(right, shift_operator(f,\
    \ node_left(right) - base_left));\n            }\n            left >>= 1;\n  \
    \          right >>= 1;\n        }\n        left = saved_left;\n        right\
    \ = saved_right;\n        for (int level = 1; level <= _log; ++level) {\n    \
    \        if (((left >> level) << level) != left) update(left >> level);\n    \
    \        if (((right >> level) << level) != right) update((right - 1) >> level);\n\
    \        }\n    }\n\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        int node = left + _size;\n      \
    \  for (int level = _log; level >= 1; --level) push(node >> level);\n        T\
    \ product = ActedMonoid::id();\n        do {\n            while ((node & 1) ==\
    \ 0) node >>= 1;\n            T next = ActedMonoid::op(product, _journal[node].value);\n\
    \            if (!predicate(next)) {\n                while (node < _size) {\n\
    \                    push(node);\n                    node <<= 1;\n          \
    \          next = ActedMonoid::op(product, _journal[node].value);\n          \
    \          if (predicate(next)) {\n                        product = std::move(next);\n\
    \                        ++node;\n                    }\n                }\n \
    \               return node - _size;\n            }\n            product = std::move(next);\n\
    \            ++node;\n        } while ((node & -node) != node);\n        return\
    \ _n;\n    }\n\n    template <class Predicate>\n    int min_left(int right, Predicate\
    \ predicate) {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        int node = right + _size;\n      \
    \  for (int level = _log; level >= 1; --level) push((node - 1) >> level);\n  \
    \      T product = ActedMonoid::id();\n        do {\n            --node;\n   \
    \         while (node > 1 && (node & 1)) node >>= 1;\n            T next = ActedMonoid::op(_journal[node].value,\
    \ product);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    push(node);\n                    node = node\
    \ << 1 | 1;\n                    next = ActedMonoid::op(_journal[node].value,\
    \ product);\n                    if (predicate(next)) {\n                    \
    \    product = std::move(next);\n                        --node;\n           \
    \         }\n                }\n                return node + 1 - _size;\n   \
    \         }\n            product = std::move(next);\n        } while ((node &\
    \ -node) != node);\n        return 0;\n    }\n\n    int snapshot() { return _journal.snapshot();\
    \ }\n    int snapshot_count() const { return _journal.snapshot_count(); }\n  \
    \  void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n\
    \    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _n = 0; _size = 1; _log\
    \ = 0; _journal.clear(); }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    #endif  // M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - ds/detail/rollback_journal.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_lazy_segtree.hpp
layout: document
title: Rollback Lazy Segment Tree
---

## Overview

`RollbackLazySegtree<ActedMonoid>` provides point assignment, range actions,
range products, and registered-snapshot rollback. `ActedMonoid` must satisfy
`m1une::acted_monoid::IsActedMonoid`.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to a point or `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a tree node is saved only before its first mutation.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/rollback_lazy_segtree.hpp"

#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackLazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
int state = seg.snapshot();
seg.apply(0, 2, 5);
seg.rollback(state);
assert(seg.all_prod().sum == 6);
```
