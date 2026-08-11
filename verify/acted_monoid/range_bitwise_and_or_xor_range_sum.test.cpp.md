---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
    title: Range Bitwise AND/OR/XOR Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
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
    \n\n#line 1 \"acted_monoid/range_bitwise_and_or_xor_range_sum.hpp\"\n\n\n\n#include\
    \ <array>\n#line 6 \"acted_monoid/range_bitwise_and_or_xor_range_sum.hpp\"\n#include\
    \ <type_traits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T, int BITS>\nstruct RangeBitwiseAndOrXorRangeSumNode {\n    T sum;\n    std::array<long\
    \ long, BITS> bit_count;\n    long long size;\n};\n\n// Acted monoid for range\
    \ bitwise AND, OR, and XOR updates and range sum queries.\ntemplate <typename\
    \ T, int BITS = 30>\nstruct RangeBitwiseAndOrXorRangeSum {\n    static_assert(std::is_integral_v<T>\
    \ && !std::is_same_v<std::remove_cv_t<T>, bool>);\n    static_assert(0 < BITS\
    \ && BITS <= std::numeric_limits<T>::digits);\n\n    using value_type = RangeBitwiseAndOrXorRangeSumNode<T,\
    \ BITS>;\n\n    // Represents f(x) = (x & and_mask) ^ xor_mask on the lowest BITS\
    \ bits.\n    struct operator_type {\n        T and_mask;\n        T xor_mask;\n\
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
    \          long long count = ((f.and_mask >> i) & T(1)) ? x.bit_count[i] : 0;\n\
    \            if ((f.xor_mask >> i) & T(1)) count = x.size - count;\n         \
    \   res.bit_count[i] = count;\n            res.sum += static_cast<T>(count) *\
    \ (T(1) << i);\n        }\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& value) {\n        value_type res;\n        res.sum\
    \ = value;\n        res.size = 1;\n        for (int i = 0; i < BITS; ++i) {\n\
    \            res.bit_count[i] = (value >> i) & T(1);\n        }\n        return\
    \ res;\n    }\n\n    static constexpr operator_type make_and(const T& mask) {\n\
    \        return {mask & bit_mask(), T(0)};\n    }\n\n    static constexpr operator_type\
    \ make_or(const T& mask) {\n        T normalized = mask & bit_mask();\n      \
    \  return {bit_mask() ^ normalized, normalized};\n    }\n\n    static constexpr\
    \ operator_type make_xor(const T& mask) {\n        return {bit_mask(), mask &\
    \ bit_mask()};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/segtree/lazy_segtree.hpp\"\n\n\n\n#include <bit>\n#line 7 \"\
    ds/segtree/lazy_segtree.hpp\"\n#include <utility>\n#line 9 \"ds/segtree/lazy_segtree.hpp\"\
    \n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/lazy_segtree.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\n// A highly generic Lazy Segment Tree utilizing\
    \ C++20 Concepts for type safety.\n// It operates on any Acted Monoid structure\
    \ satisfying the `m1une::acted_monoid::IsActedMonoid` concept.\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    int _n,\
    \ _size, _log;\n    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    // Recalculates\
    \ the value of the node k from its children.\n    void update(int k) {\n     \
    \   _d[k] = ActedMonoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n    static T\
    \ mapping_at(const F& f, const T& value, long long ord) {\n        if constexpr\
    \ (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n   \
    \         return ActedMonoid::mapping(f, value, ord);\n        } else {\n    \
    \        return ActedMonoid::mapping(f, value);\n        }\n    }\n\n    static\
    \ F shift_operator(const F& f, long long ord) {\n        if constexpr (requires(F\
    \ g, long long i) { ActedMonoid::op_shift(g, i); }) {\n            return ActedMonoid::op_shift(f,\
    \ ord);\n        } else {\n            return f;\n        }\n    }\n\n    int\
    \ node_length(int k) const {\n        int level = std::bit_width((unsigned int)k)\
    \ - 1;\n        return _size >> level;\n    }\n\n    int node_left(int k) const\
    \ {\n        int level = std::bit_width((unsigned int)k) - 1;\n        int len\
    \ = _size >> level;\n        return (k - (1 << level)) * len;\n    }\n\n    //\
    \ Applies the operator f to the node k and updates its lazy tag if it's an internal\
    \ node.\n    void all_apply(int k, F f) {\n        _d[k] = mapping_at(f, _d[k],\
    \ 0);\n        if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f,\
    \ _lz[k]);\n        }\n    }\n\n    // Propagates the lazy tag of the node k down\
    \ to its children.\n    void push(int k) {\n        all_apply(2 * k, _lz[k]);\n\
    \        all_apply(2 * k + 1, shift_operator(_lz[k], node_length(k) / 2));\n \
    \       _lz[k] = ActedMonoid::op_id();\n    }\n\n   public:\n    // Constructs\
    \ an empty lazy segment tree.\n    LazySegtree() : LazySegtree(0) {}\n\n    //\
    \ Constructs a lazy segment tree of size `n`, initialized with the identity element.\n\
    \    explicit LazySegtree(int n) : LazySegtree(std::vector<T>(n, ActedMonoid::id()))\
    \ {}\n\n    // Constructs a lazy segment tree from an existing vector.\n    explicit\
    \ LazySegtree(const std::vector<T>& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2 * _size,\
    \ ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n    \
    \    for (int i = 0; i < _n; i++) _d[_size + i] = v[i];\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n    explicit LazySegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);\n     \
    \   for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Constructs\
    \ a lazy segment tree from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. ActedMonoid::make(val)\
    \ if it exists.\n    // 2. ActedMonoid::make(val, index) if the monoid requires\
    \ global indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { ActedMonoid::make(x); } ||\n        requires(U x, int i) { ActedMonoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit LazySegtree(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size,\
    \ ActedMonoid::op_id());\n        for (int i = 0; i < _n; i++) {\n           \
    \ if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n                _d[_size\
    \ + i] = ActedMonoid::make(v[i]);\n            } else if constexpr (requires(U\
    \ x, int idx) { ActedMonoid::make(x, idx); }) {\n                _d[_size + i]\
    \ = ActedMonoid::make(v[i], i);\n            } else {\n                _d[_size\
    \ + i] = static_cast<T>(v[i]);\n            }\n        }\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Returns the number of elements.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Assigns x to the p-th element.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--)\
    \ push(p >> i);\n        _d[p] = x;\n        for (int i = 1; i <= _log; i++) update(p\
    \ >> i);\n    }\n\n    // Returns the value of the p-th element.\n    T get(int\
    \ p) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for (int\
    \ i = _log; i >= 1; i--) push(p >> i);\n        return _d[p];\n    }\n\n    //\
    \ Returns the value of the p-th element.\n    T operator[](int p) {\n        return\
    \ get(p);\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return ActedMonoid::id();\n\n       \
    \ l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1; i--)\
    \ {\n            if (((l >> i) << i) != l) push(l >> i);\n            if (((r\
    \ >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        T sml = ActedMonoid::id(),\
    \ smr = ActedMonoid::id();\n        while (l < r) {\n            if (l & 1) sml\
    \ = ActedMonoid::op(sml, _d[l++]);\n            if (r & 1) smr = ActedMonoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n\n        return\
    \ ActedMonoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire\
    \ array.\n    T all_prod() const {\n        return _d[1];\n    }\n\n    // Returns\
    \ all elements as a vector.\n    std::vector<T> to_vector() {\n        for (int\
    \ k = 1; k < _size; k++) push(k);\n        std::vector<T> res;\n        res.reserve(_n);\n\
    \        for (int i = 0; i < _n; i++) res.push_back(_d[_size + i]);\n        return\
    \ res;\n    }\n\n    // Returns the elements in the range [l, r) as a vector.\n\
    \    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        std::vector<T> res;\n        res.reserve(r - l);\n   \
    \     for (int i = l; i < r; i++) res.push_back(get(i));\n        return res;\n\
    \    }\n\n    // Applies the operator f to the p-th element.\n    void apply(int\
    \ p, F f) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p] = mapping_at(f, _d[p],\
    \ 0);\n        for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    //\
    \ Applies the operator f to all elements in the range [l, r).\n    void apply(int\
    \ l, int r, F f) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l\
    \ == r) return;\n\n        int base_l = l;\n        l += _size;\n        r +=\
    \ _size;\n\n        for (int i = _log; i >= 1; i--) {\n            if (((l >>\
    \ i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\n        }\n\n        {\n            int l2 = l, r2 = r;\n     \
    \       while (l < r) {\n                if (l & 1) {\n                    all_apply(l,\
    \ shift_operator(f, node_left(l) - base_l));\n                    l++;\n     \
    \           }\n                if (r & 1) {\n                    --r;\n      \
    \              all_apply(r, shift_operator(f, node_left(r) - base_l));\n     \
    \           }\n                l >>= 1;\n                r >>= 1;\n          \
    \  }\n            l = l2;\n            r = r2;\n        }\n\n        for (int\
    \ i = 1; i <= _log; i++) {\n            if (((l >> i) << i) != l) update(l >>\
    \ i);\n            if (((r >> i) << i) != r) update((r - 1) >> i);\n        }\n\
    \    }\n\n    // Finds the largest r such that g(prod(l, r)) is true.\n    template\
    \ <class F_pred>\n    int max_right(int l, F_pred g) {\n        assert(0 <= l\
    \ && l <= _n);\n        assert(g(ActedMonoid::id()));\n        if (l == _n) return\
    \ _n;\n        l += _size;\n        for (int i = _log; i >= 1; i--) push(l >>\
    \ i);\n        T sm = ActedMonoid::id();\n        do {\n            while (l %\
    \ 2 == 0) l >>= 1;\n            if (!g(ActedMonoid::op(sm, _d[l]))) {\n      \
    \          while (l < _size) {\n                    push(l);\n               \
    \     l = (2 * l);\n                    if (g(ActedMonoid::op(sm, _d[l]))) {\n\
    \                        sm = ActedMonoid::op(sm, _d[l]);\n                  \
    \      l++;\n                    }\n                }\n                return\
    \ l - _size;\n            }\n            sm = ActedMonoid::op(sm, _d[l]);\n  \
    \          l++;\n        } while ((l & -l) != l);\n        return _n;\n    }\n\
    \n    // Finds the smallest l such that g(prod(l, r)) is true.\n    template <class\
    \ F_pred>\n    int min_left(int r, F_pred g) {\n        assert(0 <= r && r <=\
    \ _n);\n        assert(g(ActedMonoid::id()));\n        if (r == 0) return 0;\n\
    \        r += _size;\n        for (int i = _log; i >= 1; i--) push((r - 1) >>\
    \ i);\n        T sm = ActedMonoid::id();\n        do {\n            r--;\n   \
    \         while (r > 1 && (r % 2)) r >>= 1;\n            if (!g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                while (r < _size) {\n                    push(r);\n\
    \                    r = (2 * r + 1);\n                    if (g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                        sm = ActedMonoid::op(_d[r], sm);\n        \
    \                r--;\n                    }\n                }\n            \
    \    return r + 1 - _size;\n            }\n            sm = ActedMonoid::op(_d[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 13 \"verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp\"\
    \n\nnamespace {\n\nusing AM = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long\
    \ long, 10>;\nusing SignedFullWidth = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long\
    \ long, 63>;\nusing UnsignedFullWidth =\n    m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<unsigned\
    \ long long, 64>;\n\nlong long apply_scalar(const AM::operator_type& f, long long\
    \ x) {\n    return (x & f.and_mask) ^ f.xor_mask;\n}\n\nvoid test_composition()\
    \ {\n    std::vector<AM::operator_type> operators;\n    for (long long mask =\
    \ 0; mask < 32; ++mask) {\n        operators.push_back(AM::make_and(mask));\n\
    \        operators.push_back(AM::make_or(mask));\n        operators.push_back(AM::make_xor(mask));\n\
    \    }\n\n    for (const auto& f : operators) {\n        for (const auto& g :\
    \ operators) {\n            auto composition = AM::op_comp(f, g);\n          \
    \  for (long long x = 0; x < 32; ++x) {\n                assert(apply_scalar(composition,\
    \ x) == apply_scalar(f, apply_scalar(g, x)));\n            }\n        }\n    }\n\
    }\n\nvoid test_randomized() {\n    constexpr int n = 73;\n    constexpr long long\
    \ mask = (1LL << 10) - 1;\n    std::uint64_t state = 123456789;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    std::vector<long long> values(n);\n    for\
    \ (long long& value : values) value = static_cast<long long>(random() & mask);\n\
    \    m1une::ds::LazySegtree<AM> seg(values);\n\n    for (int step = 0; step <\
    \ 5000; ++step) {\n        int l = static_cast<int>(random() % (n + 1));\n   \
    \     int r = static_cast<int>(random() % (n + 1));\n        if (r < l) std::swap(l,\
    \ r);\n\n        if (random() % 4 != 0) {\n            long long operand = static_cast<long\
    \ long>(random() & mask);\n            int type = static_cast<int>(random() %\
    \ 3);\n            AM::operator_type f = AM::op_id();\n            if (type ==\
    \ 0) {\n                f = AM::make_and(operand);\n                for (int i\
    \ = l; i < r; ++i) values[i] &= operand;\n            } else if (type == 1) {\n\
    \                f = AM::make_or(operand);\n                for (int i = l; i\
    \ < r; ++i) values[i] |= operand;\n            } else {\n                f = AM::make_xor(operand);\n\
    \                for (int i = l; i < r; ++i) values[i] ^= operand;\n         \
    \   }\n            seg.apply(l, r, f);\n        } else {\n            long long\
    \ expected = 0;\n            for (int i = l; i < r; ++i) expected += values[i];\n\
    \            assert(seg.prod(l, r).sum == expected);\n        }\n\n        int\
    \ index = static_cast<int>(random() % n);\n        assert(seg.get(index).sum ==\
    \ values[index]);\n    }\n}\n\nstatic_assert(m1une::acted_monoid::IsActedMonoid<AM>);\n\
    static_assert(AM::commutative);\nstatic_assert(!AM::operator_commutative);\nstatic_assert(SignedFullWidth::bit_mask()\
    \ == std::numeric_limits<long long>::max());\nstatic_assert(UnsignedFullWidth::bit_mask()\
    \ == std::numeric_limits<unsigned long long>::max());\n\n}  // namespace\n\nint\
    \ main() {\n    test_composition();\n    test_randomized();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <vector>\n\n#include \"../../acted_monoid/concept.hpp\"\n#include \"\
    ../../acted_monoid/range_bitwise_and_or_xor_range_sum.hpp\"\n#include \"../../ds/segtree/lazy_segtree.hpp\"\
    \n\nnamespace {\n\nusing AM = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long\
    \ long, 10>;\nusing SignedFullWidth = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long\
    \ long, 63>;\nusing UnsignedFullWidth =\n    m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<unsigned\
    \ long long, 64>;\n\nlong long apply_scalar(const AM::operator_type& f, long long\
    \ x) {\n    return (x & f.and_mask) ^ f.xor_mask;\n}\n\nvoid test_composition()\
    \ {\n    std::vector<AM::operator_type> operators;\n    for (long long mask =\
    \ 0; mask < 32; ++mask) {\n        operators.push_back(AM::make_and(mask));\n\
    \        operators.push_back(AM::make_or(mask));\n        operators.push_back(AM::make_xor(mask));\n\
    \    }\n\n    for (const auto& f : operators) {\n        for (const auto& g :\
    \ operators) {\n            auto composition = AM::op_comp(f, g);\n          \
    \  for (long long x = 0; x < 32; ++x) {\n                assert(apply_scalar(composition,\
    \ x) == apply_scalar(f, apply_scalar(g, x)));\n            }\n        }\n    }\n\
    }\n\nvoid test_randomized() {\n    constexpr int n = 73;\n    constexpr long long\
    \ mask = (1LL << 10) - 1;\n    std::uint64_t state = 123456789;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    std::vector<long long> values(n);\n    for\
    \ (long long& value : values) value = static_cast<long long>(random() & mask);\n\
    \    m1une::ds::LazySegtree<AM> seg(values);\n\n    for (int step = 0; step <\
    \ 5000; ++step) {\n        int l = static_cast<int>(random() % (n + 1));\n   \
    \     int r = static_cast<int>(random() % (n + 1));\n        if (r < l) std::swap(l,\
    \ r);\n\n        if (random() % 4 != 0) {\n            long long operand = static_cast<long\
    \ long>(random() & mask);\n            int type = static_cast<int>(random() %\
    \ 3);\n            AM::operator_type f = AM::op_id();\n            if (type ==\
    \ 0) {\n                f = AM::make_and(operand);\n                for (int i\
    \ = l; i < r; ++i) values[i] &= operand;\n            } else if (type == 1) {\n\
    \                f = AM::make_or(operand);\n                for (int i = l; i\
    \ < r; ++i) values[i] |= operand;\n            } else {\n                f = AM::make_xor(operand);\n\
    \                for (int i = l; i < r; ++i) values[i] ^= operand;\n         \
    \   }\n            seg.apply(l, r, f);\n        } else {\n            long long\
    \ expected = 0;\n            for (int i = l; i < r; ++i) expected += values[i];\n\
    \            assert(seg.prod(l, r).sum == expected);\n        }\n\n        int\
    \ index = static_cast<int>(random() % n);\n        assert(seg.get(index).sum ==\
    \ values[index]);\n    }\n}\n\nstatic_assert(m1une::acted_monoid::IsActedMonoid<AM>);\n\
    static_assert(AM::commutative);\nstatic_assert(!AM::operator_commutative);\nstatic_assert(SignedFullWidth::bit_mask()\
    \ == std::numeric_limits<long long>::max());\nstatic_assert(UnsignedFullWidth::bit_mask()\
    \ == std::numeric_limits<unsigned long long>::max());\n\n}  // namespace\n\nint\
    \ main() {\n    test_composition();\n    test_randomized();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
  - ds/segtree/lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  isVerificationFile: true
  path: verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 00:05:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
- /verify/verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp.html
title: verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
---
