---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_affine_range_sum.hpp
    title: Range Affine Range Sum
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_ap_add_range_sum.hpp
    title: Range AP Add Range Sum
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
    title: Range Bitwise AND/OR/XOR Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_lazy_segtree.hpp
    title: Rollback Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/rollback_lazy_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <random>\n#include\
    \ <vector>\n\n#line 1 \"acted_monoid/range_affine_range_sum.hpp\"\n\n\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeAffineRangeSumNode {\n    T sum;\n    int size;\n};\n\n// Designed\
    \ to accept Modint or similar types as T\ntemplate <typename T>\nstruct RangeAffineRangeSum\
    \ {\n    using value_type = RangeAffineRangeSumNode<T>;\n    using operator_type\
    \ = std::pair<T, T>;  // {a, b} for ax + b\n    static constexpr bool commutative\
    \ = true;\n    static constexpr bool operator_commutative = false;\n\n    // Value\
    \ Monoid\n    static constexpr value_type id() {\n        return {T(0), 0};\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n    static constexpr\
    \ int size(const value_type& value) {\n        return value.size;\n    }\n\n \
    \   // Operator Monoid (Affine Composition)\n    // f(x) = a1*x + b1, g(x) = a2*x\
    \ + b2\n    // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x + (a1*b2 + b1)\n    static\
    \ constexpr operator_type op_id() {\n        return {T(1), T(0)};\n    }\n   \
    \ static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return {f.first * g.first, f.first * g.second + f.second};\n \
    \   }\n\n    // Mapping\n    // \\sum (a*x_i + b) = a * \\sum x_i + b * size\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        return {f.first * x.sum + f.second * T(x.size), x.size};\n   \
    \ }\n\n    // Helper for initializing a leaf node\n    static constexpr value_type\
    \ make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"acted_monoid/range_ap_add_range_sum.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/range_ap_add_range_sum.hpp\"\n\nnamespace m1une\
    \ {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeApAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n    T ord_sum;\n};\n\ntemplate <typename\
    \ T>\nstruct RangeApAddRangeSum {\n    using value_type = RangeApAddRangeSumNode<T>;\n\
    \    using operator_type = std::pair<T, T>;  // {a, b} for adding a * i + b\n\
    \    static constexpr bool commutative = false;\n    static constexpr bool operator_commutative\
    \ = true;\n\n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n\
    \        return {T(0), 0, T(0)};\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {a.sum + b.sum, a.size\
    \ + b.size, a.ord_sum + b.ord_sum + T(a.size) * T(b.size)};\n    }\n\n    // Operator\
    \ Monoid (Add)\n    static constexpr operator_type op_id() {\n        return {T(0),\
    \ T(0)};\n    }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return {f.first + g.first, f.second +\
    \ g.second};\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return mapping(f, x, 0);\n    }\n\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x, long\
    \ long ord) {\n        return {x.sum + f.first * (x.ord_sum + T(ord) * T(x.size))\
    \ + f.second * T(x.size), x.size, x.ord_sum};\n    }\n\n    static constexpr operator_type\
    \ op_shift(const operator_type& f, long long ord) {\n        return {f.first,\
    \ f.second + f.first * T(ord)};\n    }\n\n    static constexpr operator_type op_reverse(const\
    \ operator_type& f, long long size) {\n        return {-f.first, f.second + f.first\
    \ * T(size - 1)};\n    }\n\n    static constexpr value_type make(const T& val)\
    \ {\n        return {val, 1, T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"acted_monoid/range_bitwise_and_or_xor_range_sum.hpp\"\
    \n\n\n\n#include <array>\n#include <limits>\n#include <type_traits>\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, int BITS, typename\
    \ Count = long long>\nstruct RangeBitwiseAndOrXorRangeSumNode {\n    T sum;\n\
    \    std::array<Count, BITS> bit_count;\n    Count size;\n};\n\n// Acted monoid\
    \ for range bitwise AND, OR, and XOR updates and range sum queries.\ntemplate\
    \ <typename T, int BITS = 30, typename Count = long long>\nstruct RangeBitwiseAndOrXorRangeSum\
    \ {\n    static_assert(std::is_integral_v<T> && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>);\n    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);\n\
    \n    static_assert(std::is_integral_v<Count> && !std::is_same_v<std::remove_cv_t<Count>,\
    \ bool>);\n\n    using value_type = RangeBitwiseAndOrXorRangeSumNode<T, BITS,\
    \ Count>;\n\n    // Represents f(x) = (x & and_mask) ^ xor_mask on the lowest\
    \ BITS bits.\n    struct operator_type {\n        T and_mask;\n        T xor_mask;\n\
    \    };\n\n    static constexpr bool commutative = true;\n    static constexpr\
    \ bool operator_commutative = false;\n\n    static constexpr T bit_mask() {\n\
    \        if constexpr (std::is_unsigned_v<T> && BITS == std::numeric_limits<T>::digits)\
    \ {\n            return ~T(0);\n        } else {\n            return (T(1) <<\
    \ (BITS - 1)) | ((T(1) << (BITS - 1)) - 1);\n        }\n    }\n\n    static constexpr\
    \ value_type id() {\n        value_type res;\n        res.sum = T(0);\n      \
    \  res.bit_count.fill(0);\n        res.size = 0;\n        return res;\n    }\n\
    \n    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        value_type res;\n        res.sum = a.sum + b.sum;\n        res.size\
    \ = a.size + b.size;\n        for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i]\
    \ = a.bit_count[i] + b.bit_count[i];\n        }\n        return res;\n    }\n\n\
    \    static constexpr operator_type op_id() {\n        return {bit_mask(), T(0)};\n\
    \    }\n\n    // Returns f(g(x)).\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.and_mask & g.and_mask,\
    \ (g.xor_mask & f.and_mask) ^ f.xor_mask};\n    }\n\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        value_type res\
    \ = x;\n        res.sum = T(0);\n        for (int i = 0; i < BITS; ++i) {\n  \
    \          // Use full-width masks so both selections can be vectorized.\n   \
    \         Count keep = -static_cast<Count>((f.and_mask >> i) & T(1));\n      \
    \      Count flip = -static_cast<Count>((f.xor_mask >> i) & T(1));\n         \
    \   Count count = x.bit_count[i] & keep;\n            count = (count & ~flip)\
    \ | ((x.size - count) & flip);\n            res.bit_count[i] = count;\n      \
    \      res.sum += static_cast<T>(count) * (T(1) << i);\n        }\n        return\
    \ res;\n    }\n\n    static constexpr value_type make(const T& value) {\n    \
    \    value_type res;\n        res.sum = value;\n        res.size = 1;\n      \
    \  for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i] = (value >>\
    \ i) & T(1);\n        }\n        return res;\n    }\n\n    static constexpr operator_type\
    \ make_and(const T& mask) {\n        return {mask & bit_mask(), T(0)};\n    }\n\
    \n    static constexpr operator_type make_or(const T& mask) {\n        T normalized\
    \ = mask & bit_mask();\n        return {bit_mask() ^ normalized, normalized};\n\
    \    }\n\n    static constexpr operator_type make_xor(const T& mask) {\n     \
    \   return {bit_mask(), mask & bit_mask()};\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"ds/segtree/rollback_lazy_segtree.hpp\"\n\n\
    \n\n#include <bit>\n#line 6 \"ds/segtree/rollback_lazy_segtree.hpp\"\n#include\
    \ <concepts>\n#line 9 \"ds/segtree/rollback_lazy_segtree.hpp\"\n\n#line 1 \"acted_monoid/concept.hpp\"\
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
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"math/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n#line 6 \"ds/detail/rollback_journal.hpp\"\
    \n#include <cstddef>\n#line 11 \"ds/detail/rollback_journal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\nstruct\
    \ RollbackJournal {\n    struct Change {\n        int index;\n        Node value;\n\
    \    };\n\n    struct Checkpoint {\n        std::size_t change_size;\n       \
    \ std::size_t node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node>\
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
    \   if (node < _size) {\n            _journal[node].lazy = _journal[node].has_lazy\n\
    \                ? ActedMonoid::op_comp(f, _journal[node].lazy) : f;\n       \
    \     _journal[node].has_lazy = true;\n        }\n    }\n\n    void push(int node)\
    \ {\n        if (!_journal[node].has_lazy) return;\n        F lazy = _journal[node].lazy;\n\
    \        all_apply(node << 1, lazy);\n        all_apply(node << 1 | 1, shift_operator(lazy,\
    \ node_length(node) / 2));\n        _journal.touch(node);\n        _journal[node].has_lazy\
    \ = false;\n    }\n\n    // Ancestor tags are newer than the tags stored below\
    \ them. Carry their\n    // composition down instead of pushing (and journaling)\
    \ nodes for a query.\n    T prod_node(int node, int start, int length, int left,\
    \ int right,\n                const F& inherited, bool has_inherited) const {\n\
    \        const Node& current = _journal[node];\n        if (left <= start && start\
    \ + length <= right) {\n            return has_inherited ? mapping_at(inherited,\
    \ current.value, 0) : current.value;\n        }\n        F lazy = inherited;\n\
    \        bool has_lazy = has_inherited || current.has_lazy;\n        if (current.has_lazy)\
    \ {\n            lazy = has_inherited ? ActedMonoid::op_comp(inherited, current.lazy)\
    \ : current.lazy;\n        }\n        int half = length / 2;\n        int middle\
    \ = start + half;\n        if (right <= middle) {\n            return prod_node(node\
    \ << 1, start, half, left, right, lazy, has_lazy);\n        }\n        F right_lazy\
    \ = shift_operator(lazy, half);\n        if (middle <= left) {\n            return\
    \ prod_node(node << 1 | 1, middle, half, left, right, right_lazy, has_lazy);\n\
    \        }\n        return ActedMonoid::op(\n            prod_node(node << 1,\
    \ start, half, left, right, lazy, has_lazy),\n            prod_node(node << 1\
    \ | 1, middle, half, left, right, right_lazy, has_lazy)\n        );\n    }\n\n\
    \    template <class U>\n    void build(const std::vector<U>& values) {\n    \
    \    _n = int(values.size());\n        _size = int(m1une::math::bit_ceil(static_cast<unsigned\
    \ int>(_n)));\n        _log = 0;\n        while ((1U << _log) < static_cast<unsigned\
    \ int>(_size)) ++_log;\n        _journal.nodes.assign(2 * _size, Node());\n  \
    \      _journal.saved_epoch.assign(_journal.nodes.size(), 0);\n        for (int\
    \ index = 0; index < _n; ++index) {\n            _journal[_size + index].value\
    \ = make_value(values[index], index);\n        }\n        for (int node = _size\
    \ - 1; node > 0; --node) {\n            _journal[node].value = ActedMonoid::op(\n\
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
    \ }\n\n    T get(int pos) const {\n        assert(0 <= pos && pos < _n);\n   \
    \     return prod(pos, pos + 1);\n    }\n\n    T operator[](int pos) const { return\
    \ get(pos); }\n\n    T prod(int left, int right) const {\n        assert(0 <=\
    \ left && left <= right && right <= _n);\n        if (left == right) return ActedMonoid::id();\n\
    \        return prod_node(1, 0, _size, left, right, ActedMonoid::op_id(), false);\n\
    \    }\n\n    T all_prod() const { return _journal[1].value; }\n\n    std::vector<T>\
    \ to_vector() {\n        for (int node = 1; node < _size; ++node) push(node);\n\
    \        std::vector<T> result;\n        result.reserve(_n);\n        for (int\
    \ index = 0; index < _n; ++index) result.push_back(_journal[_size + index].value);\n\
    \        return result;\n    }\n\n    std::vector<T> to_vector(int left, int right)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        std::vector<T>\
    \ result;\n        result.reserve(right - left);\n        for (int index = left;\
    \ index < right; ++index) result.push_back(get(index));\n        return result;\n\
    \    }\n\n    void apply(int pos, const F& f) {\n        assert(0 <= pos && pos\
    \ < _n);\n        int node = pos + _size;\n        for (int level = _log; level\
    \ >= 1; --level) push(node >> level);\n        _journal.touch(node);\n       \
    \ _journal[node].value = mapping_at(f, _journal[node].value, 0);\n        for\
    \ (int level = 1; level <= _log; ++level) update(node >> level);\n    }\n\n  \
    \  void apply(int left, int right, const F& f) {\n        assert(0 <= left &&\
    \ left <= right && right <= _n);\n        if (left == right) return;\n       \
    \ int base_left = left;\n        left += _size;\n        right += _size;\n   \
    \     for (int level = _log; level >= 1; --level) {\n            if (((left >>\
    \ level) << level) != left) push(left >> level);\n            if (((right >> level)\
    \ << level) != right) push((right - 1) >> level);\n        }\n        int saved_left\
    \ = left;\n        int saved_right = right;\n        while (left < right) {\n\
    \            if (left & 1) {\n                all_apply(left, shift_operator(f,\
    \ node_left(left) - base_left));\n                ++left;\n            }\n   \
    \         if (right & 1) {\n                --right;\n                all_apply(right,\
    \ shift_operator(f, node_left(right) - base_left));\n            }\n         \
    \   left >>= 1;\n            right >>= 1;\n        }\n        left = saved_left;\n\
    \        right = saved_right;\n        for (int level = 1; level <= _log; ++level)\
    \ {\n            int left_node = left >> level;\n            int right_node =\
    \ (right - 1) >> level;\n            bool update_left = (left_node << level) !=\
    \ left;\n            if (update_left) update(left_node);\n            if (((right\
    \ >> level) << level) != right &&\n                (!update_left || right_node\
    \ != left_node)) update(right_node);\n        }\n    }\n\n    void apply_inplace(int\
    \ pos, const F& f) { apply(pos, f); }\n    void apply_inplace(int left, int right,\
    \ const F& f) { apply(left, right, f); }\n\n    template <class Predicate>\n \
    \   int max_right(int left, Predicate predicate) {\n        assert(0 <= left &&\
    \ left <= _n);\n        assert(predicate(ActedMonoid::id()));\n        if (left\
    \ == _n) return _n;\n        int node = left + _size;\n        for (int level\
    \ = _log; level >= 1; --level) push(node >> level);\n        T product = ActedMonoid::id();\n\
    \        do {\n            while ((node & 1) == 0) node >>= 1;\n            T\
    \ next = ActedMonoid::op(product, _journal[node].value);\n            if (!predicate(next))\
    \ {\n                while (node < _size) {\n                    push(node);\n\
    \                    node <<= 1;\n                    next = ActedMonoid::op(product,\
    \ _journal[node].value);\n                    if (predicate(next)) {\n       \
    \                 product = std::move(next);\n                        ++node;\n\
    \                    }\n                }\n                return node - _size;\n\
    \            }\n            product = std::move(next);\n            ++node;\n\
    \        } while ((node & -node) != node);\n        return _n;\n    }\n\n    template\
    \ <class Predicate>\n    int min_left(int right, Predicate predicate) {\n    \
    \    assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
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
    \n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line\
    \ 6 \"utilities/fast_io.hpp\"\n#include <cerrno>\n#include <charconv>\n#line 9\
    \ \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line 12 \"\
    utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include <string>\n\
    #include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    #line 20 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    \nstruct FastOutput;\n\nnamespace internal {\n\n// Shared with the convenience\
    \ helpers in template.hpp.\ninline FastOutput* standard_output_instance = nullptr;\n\
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
    \    char _range_separator;\n    std::string* _capture = nullptr;\n\n    template\
    \ <class T>\n    std::string format_cell(const T& value) {\n        std::string\
    \ result;\n        struct CaptureGuard {\n            std::string*& target;\n\
    \            std::string* previous;\n            ~CaptureGuard() { target = previous;\
    \ }\n        } guard{_capture, _capture};\n        _capture = &result;\n     \
    \   write(value);\n        return result;\n    }\n\n    template <class Matrix>\n\
    \    void write_aligned_matrix(const Matrix& matrix) {\n        std::vector<std::vector<std::string>>\
    \ rows;\n        std::vector<std::size_t> widths;\n        for (const auto& row\
    \ : matrix) {\n            auto& cells = rows.emplace_back();\n            std::size_t\
    \ column = 0;\n            for (const auto& value : row) {\n                cells.push_back(format_cell(value));\n\
    \                if (column == widths.size()) widths.push_back(0);\n         \
    \       widths[column] = std::max(widths[column], cells.back().size());\n    \
    \            ++column;\n            }\n        }\n        bool first = true;\n\
    \        for (const auto& row : rows) {\n            if (!first) write_char('\\\
    n');\n            first = false;\n            for (std::size_t column = 0; column\
    \ < row.size(); ++column) {\n                if (column != 0) write_char(_range_separator);\n\
    \                for (std::size_t padding = row[column].size();\n            \
    \         padding < widths[column]; ++padding) {\n                    write_char('\
    \ ');\n                }\n                write(row[column]);\n            }\n\
    \        }\n    }\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream),\n          _position(0),\n          _precision(6),\n\
    \          _float_format(std::chars_format::general),\n          _range_separator('\
    \ ') {\n        if (_stream == stdout\n            && internal::standard_output_instance\
    \ == nullptr) {\n            internal::standard_output_instance = this;\n    \
    \    }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \        if (internal::standard_output_instance == this) {\n            internal::standard_output_instance\
    \ = nullptr;\n        }\n    }\n\n    void flush() {\n        if (_position !=\
    \ 0) {\n            std::fwrite(_buffer, 1, _position, _stream);\n           \
    \ _position = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void\
    \ write_char(char c) {\n        if (_capture != nullptr) {\n            _capture->push_back(c);\n\
    \            return;\n        }\n        if (_position == buffer_size) flush();\n\
    \        _buffer[_position++] = c;\n    }\n\n    void write(const char* s) {\n\
    \        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        if (_capture != nullptr) {\n            _capture->append(s);\n\
    \            return;\n        }\n        std::size_t position = 0;\n        while\
    \ (position < s.size()) {\n            if (_position == buffer_size) flush();\n\
    \            const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
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
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_capture\
    \ == nullptr && _position > buffer_size - 64) flush();\n        char captured[64];\n\
    \        char* const begin = _capture != nullptr ? captured : _buffer + _position;\n\
    \        char* destination = begin;\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) *destination++ = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(destination, digits, 4);\n            destination +=\
    \ 4;\n        }\n        if (_capture != nullptr) {\n            _capture->append(begin,\
    \ destination - begin);\n        } else {\n            _position += int(destination\
    \ - begin);\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
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
    \    _range_separator = separator;\n    }\n\n    template <class Matrix>\n   \
    \ void write_aligned(const Matrix& matrix) {\n        using Row = internal::range_stored_value_t<const\
    \ Matrix>;\n        using Cell = internal::range_stored_value_t<const Row>;\n\
    \        static_assert(internal::is_range_v<Row> && !internal::is_string_like_v<Row>,\n\
    \                      \"write_aligned requires a two-dimensional range\");\n\
    \        static_assert(!internal::is_range_v<Cell> || internal::is_string_like_v<Cell>,\n\
    \                      \"write_aligned requires scalar cells\");\n        write_aligned_matrix(matrix);\n\
    \    }\n\n    template <class Matrix>\n    void println_aligned(const Matrix&\
    \ matrix) {\n        write_aligned(matrix);\n        write_char('\\n');\n    }\n\
    \n    template <class... Args>\n    void println(const Args&... args) {\n    \
    \    print(args...);\n        write_char('\\n');\n    }\n\n    template <class\
    \ T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n  \
    \      return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 15 \"verify/ds/segtree/rollback_lazy_segtree.test.cpp\"\n\n\
    namespace {\n\nusing mint = m1une::math::modint998244353;\nusing Affine = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\
    \ntemplate <class AM, class Scalar, class MakeAction, class ApplyScalar>\nvoid\
    \ randomized_test(MakeAction make_action, ApplyScalar apply_scalar) {\n    std::mt19937\
    \ random(173);\n    for (int n : {0, 1, 2, 7, 32, 73}) {\n        std::vector<Scalar>\
    \ expected(n);\n        for (auto& value : expected) value = Scalar(random() %\
    \ 1024);\n        m1une::ds::RollbackLazySegtree<AM> seg(expected);\n        std::vector<std::vector<Scalar>>\
    \ states;\n        for (int step = 0; step < 2500; ++step) {\n            int\
    \ type = int(random() % 9);\n            int left = int(random() % (n + 1));\n\
    \            int right = int(random() % (n + 1));\n            if (right < left)\
    \ std::swap(left, right);\n            if (type == 0) {\n                int token\
    \ = seg.snapshot();\n                states.push_back(expected);\n           \
    \     assert(token == int(states.size()));\n            } else if (type == 1 &&\
    \ !states.empty()) {\n                int index = int(random() % states.size());\n\
    \                seg.rollback(index + 1);\n                expected = states[index];\n\
    \                states.resize(index + 1);\n            } else if (type == 2)\
    \ {\n                seg.clear_history();\n                states.clear();\n \
    \           } else if (type == 3 && n > 0) {\n                int pos = int(random()\
    \ % n);\n                expected[pos] = Scalar(random() % 1024);\n          \
    \      seg.set(pos, AM::make(expected[pos]));\n            } else if (type ==\
    \ 4 && n > 0) {\n                int pos = int(random() % n);\n              \
    \  auto action = make_action(random);\n                seg.apply(pos, action);\n\
    \                expected[pos] = apply_scalar(action, expected[pos], 0);\n   \
    \         } else if (type >= 5) {\n                auto action = make_action(random);\n\
    \                seg.apply(left, right, action);\n                for (int i =\
    \ left; i < right; ++i) {\n                    expected[i] = apply_scalar(action,\
    \ expected[i], i - left);\n                }\n            }\n\n            //\
    \ Read through a const reference, including under unpushed tags and\n        \
    \    // nested snapshots. Queries must not mutate the tree or its history.\n \
    \           const auto& query = seg;\n            Scalar sum = 0;\n          \
    \  for (int i = left; i < right; ++i) sum += expected[i];\n            assert(query.prod(left,\
    \ right).sum == sum);\n            assert(seg.snapshot_count() == int(states.size()));\n\
    \            if (n > 0) {\n                int pos = int(random() % n);\n    \
    \            assert(query.get(pos).sum == expected[pos]);\n                assert(query[pos].sum\
    \ == expected[pos]);\n            }\n            if (step % 97 == 0) {\n     \
    \           auto values = seg.to_vector();\n                for (int i = 0; i\
    \ < n; ++i) assert(values[i].sum == expected[i]);\n            }\n        }\n\
    \    }\n}\n\nvoid test_queries() {\n    randomized_test<Affine, mint>(\n     \
    \   [](auto& random) {\n            return Affine::operator_type{mint(random()\
    \ % 5), mint(random() % 1024)};\n        },\n        [](const auto& f, mint x,\
    \ int) { return f.first * x + f.second; }\n    );\n    using AP = m1une::acted_monoid::RangeApAddRangeSum<long\
    \ long>;\n    randomized_test<AP, long long>(\n        [](auto& random) {\n  \
    \          return AP::operator_type{int(random() % 11) - 5, int(random() % 21)\
    \ - 10};\n        },\n        [](const auto& f, long long x, int ordinal) {\n\
    \            return x + f.first * ordinal + f.second;\n        }\n    );\n   \
    \ using Bits = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<std::uint32_t>;\n\
    \    randomized_test<Bits, std::uint32_t>(\n        [](auto& random) {\n     \
    \       int type = int(random() % 3);\n            std::uint32_t mask = random()\
    \ & Bits::bit_mask();\n            if (type == 0) return Bits::make_and(mask);\n\
    \            if (type == 1) return Bits::make_or(mask);\n            return Bits::make_xor(mask);\n\
    \        },\n        [](const auto& f, std::uint32_t x, int) { return (x & f.and_mask)\
    \ ^ f.xor_mask; }\n    );\n    using CompactBits =\n        m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<std::uint32_t,\
    \ 30, int>;\n    randomized_test<CompactBits, std::uint32_t>(\n        [](auto&\
    \ random) {\n            return CompactBits::operator_type{\n                static_cast<std::uint32_t>(random())\
    \ & CompactBits::bit_mask(),\n                static_cast<std::uint32_t>(random())\
    \ & CompactBits::bit_mask()\n            };\n        },\n        [](const auto&\
    \ f, std::uint32_t x, int) { return (x & f.and_mask) ^ f.xor_mask; }\n    );\n\
    }\n\n}  // namespace\n\nint main() {\n    test_queries();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    input >>\
    \ n >> q;\n    std::vector<mint> values(n);\n    for (mint& value : values) input\
    \ >> value;\n    m1une::ds::RollbackLazySegtree<Affine> seg(values);\n    int\
    \ state = seg.snapshot();\n    while (q--) {\n        int type, left, right;\n\
    \        input >> type >> left >> right;\n        if (type == 0) {\n         \
    \   mint a, b;\n            input >> a >> b;\n            seg.apply(left, right,\
    \ {a, b});\n        } else {\n            output << seg.prod(left, right).sum\
    \ << '\\n';\n        }\n    }\n    seg.rollback(state);\n    for (int i = 0; i\
    \ < n; ++i) assert(seg.get(i).sum == values[i]);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <random>\n\
    #include <vector>\n\n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\
    \n#include \"../../../acted_monoid/range_ap_add_range_sum.hpp\"\n#include \"../../../acted_monoid/range_bitwise_and_or_xor_range_sum.hpp\"\
    \n#include \"../../../ds/segtree/rollback_lazy_segtree.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n#include \"../../../utilities/fast_io.hpp\"\n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\n\
    using Affine = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\ntemplate <class\
    \ AM, class Scalar, class MakeAction, class ApplyScalar>\nvoid randomized_test(MakeAction\
    \ make_action, ApplyScalar apply_scalar) {\n    std::mt19937 random(173);\n  \
    \  for (int n : {0, 1, 2, 7, 32, 73}) {\n        std::vector<Scalar> expected(n);\n\
    \        for (auto& value : expected) value = Scalar(random() % 1024);\n     \
    \   m1une::ds::RollbackLazySegtree<AM> seg(expected);\n        std::vector<std::vector<Scalar>>\
    \ states;\n        for (int step = 0; step < 2500; ++step) {\n            int\
    \ type = int(random() % 9);\n            int left = int(random() % (n + 1));\n\
    \            int right = int(random() % (n + 1));\n            if (right < left)\
    \ std::swap(left, right);\n            if (type == 0) {\n                int token\
    \ = seg.snapshot();\n                states.push_back(expected);\n           \
    \     assert(token == int(states.size()));\n            } else if (type == 1 &&\
    \ !states.empty()) {\n                int index = int(random() % states.size());\n\
    \                seg.rollback(index + 1);\n                expected = states[index];\n\
    \                states.resize(index + 1);\n            } else if (type == 2)\
    \ {\n                seg.clear_history();\n                states.clear();\n \
    \           } else if (type == 3 && n > 0) {\n                int pos = int(random()\
    \ % n);\n                expected[pos] = Scalar(random() % 1024);\n          \
    \      seg.set(pos, AM::make(expected[pos]));\n            } else if (type ==\
    \ 4 && n > 0) {\n                int pos = int(random() % n);\n              \
    \  auto action = make_action(random);\n                seg.apply(pos, action);\n\
    \                expected[pos] = apply_scalar(action, expected[pos], 0);\n   \
    \         } else if (type >= 5) {\n                auto action = make_action(random);\n\
    \                seg.apply(left, right, action);\n                for (int i =\
    \ left; i < right; ++i) {\n                    expected[i] = apply_scalar(action,\
    \ expected[i], i - left);\n                }\n            }\n\n            //\
    \ Read through a const reference, including under unpushed tags and\n        \
    \    // nested snapshots. Queries must not mutate the tree or its history.\n \
    \           const auto& query = seg;\n            Scalar sum = 0;\n          \
    \  for (int i = left; i < right; ++i) sum += expected[i];\n            assert(query.prod(left,\
    \ right).sum == sum);\n            assert(seg.snapshot_count() == int(states.size()));\n\
    \            if (n > 0) {\n                int pos = int(random() % n);\n    \
    \            assert(query.get(pos).sum == expected[pos]);\n                assert(query[pos].sum\
    \ == expected[pos]);\n            }\n            if (step % 97 == 0) {\n     \
    \           auto values = seg.to_vector();\n                for (int i = 0; i\
    \ < n; ++i) assert(values[i].sum == expected[i]);\n            }\n        }\n\
    \    }\n}\n\nvoid test_queries() {\n    randomized_test<Affine, mint>(\n     \
    \   [](auto& random) {\n            return Affine::operator_type{mint(random()\
    \ % 5), mint(random() % 1024)};\n        },\n        [](const auto& f, mint x,\
    \ int) { return f.first * x + f.second; }\n    );\n    using AP = m1une::acted_monoid::RangeApAddRangeSum<long\
    \ long>;\n    randomized_test<AP, long long>(\n        [](auto& random) {\n  \
    \          return AP::operator_type{int(random() % 11) - 5, int(random() % 21)\
    \ - 10};\n        },\n        [](const auto& f, long long x, int ordinal) {\n\
    \            return x + f.first * ordinal + f.second;\n        }\n    );\n   \
    \ using Bits = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<std::uint32_t>;\n\
    \    randomized_test<Bits, std::uint32_t>(\n        [](auto& random) {\n     \
    \       int type = int(random() % 3);\n            std::uint32_t mask = random()\
    \ & Bits::bit_mask();\n            if (type == 0) return Bits::make_and(mask);\n\
    \            if (type == 1) return Bits::make_or(mask);\n            return Bits::make_xor(mask);\n\
    \        },\n        [](const auto& f, std::uint32_t x, int) { return (x & f.and_mask)\
    \ ^ f.xor_mask; }\n    );\n    using CompactBits =\n        m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<std::uint32_t,\
    \ 30, int>;\n    randomized_test<CompactBits, std::uint32_t>(\n        [](auto&\
    \ random) {\n            return CompactBits::operator_type{\n                static_cast<std::uint32_t>(random())\
    \ & CompactBits::bit_mask(),\n                static_cast<std::uint32_t>(random())\
    \ & CompactBits::bit_mask()\n            };\n        },\n        [](const auto&\
    \ f, std::uint32_t x, int) { return (x & f.and_mask) ^ f.xor_mask; }\n    );\n\
    }\n\n}  // namespace\n\nint main() {\n    test_queries();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    input >>\
    \ n >> q;\n    std::vector<mint> values(n);\n    for (mint& value : values) input\
    \ >> value;\n    m1une::ds::RollbackLazySegtree<Affine> seg(values);\n    int\
    \ state = seg.snapshot();\n    while (q--) {\n        int type, left, right;\n\
    \        input >> type >> left >> right;\n        if (type == 0) {\n         \
    \   mint a, b;\n            input >> a >> b;\n            seg.apply(left, right,\
    \ {a, b});\n        } else {\n            output << seg.prod(left, right).sum\
    \ << '\\n';\n        }\n    }\n    seg.rollback(state);\n    for (int i = 0; i\
    \ < n; ++i) assert(seg.get(i).sum == values[i]);\n}\n"
  dependsOn:
  - acted_monoid/range_affine_range_sum.hpp
  - acted_monoid/range_ap_add_range_sum.hpp
  - acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
  - ds/segtree/rollback_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - ds/detail/rollback_journal.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/segtree/rollback_lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-10-24 12:29:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/rollback_lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/rollback_lazy_segtree.test.cpp
- /verify/verify/ds/segtree/rollback_lazy_segtree.test.cpp.html
title: verify/ds/segtree/rollback_lazy_segtree.test.cpp
---
