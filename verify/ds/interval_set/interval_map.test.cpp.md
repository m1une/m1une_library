---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/interval_set/interval_map.hpp
    title: Interval Map
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/power.hpp
    title: Monoid Power
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
    PROBLEM: https://judge.yosupo.jp/problem/range_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/range_set_range_composite
  bundledCode: "#line 1 \"verify/ds/interval_set/interval_map.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_set_range_composite\"\n\n#line\
    \ 1 \"ds/interval_set/interval_map.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <iterator>\n#include <limits>\n#include\
    \ <memory>\n#include <set>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// A sparse piecewise-constant map. Adjacent intervals\
    \ with equal values merge.\ntemplate <class Key, class T>\nclass IntervalMap {\n\
    \   public:\n    using key_type = Key;\n    using value_type = T;\n\n    struct\
    \ interval_type {\n        Key l;\n        Key r;\n        T value;\n    };\n\n\
    \   private:\n    struct Compare {\n        using is_transparent = void;\n\n \
    \       bool operator()(const interval_type& a, const interval_type& b) const\
    \ {\n            return a.l < b.l;\n        }\n        bool operator()(const interval_type&\
    \ a, const Key& b) const { return a.l < b; }\n        bool operator()(const Key&\
    \ a, const interval_type& b) const { return a < b.l; }\n    };\n\n    using Set\
    \ = std::set<interval_type, Compare>;\n    using iterator = typename Set::iterator;\n\
    \    Set _intervals;\n\n    static bool equal_key(const Key& a, const Key& b)\
    \ {\n        return !(a < b) && !(b < a);\n    }\n\n    // Creates a boundary\
    \ at x if x is strictly inside a stored interval.\n    // The extracted left node\
    \ is reused; only the right node is allocated.\n    iterator split(Key x) {\n\
    \        auto right = _intervals.lower_bound(x);\n        if (right != _intervals.end()\
    \ && equal_key(right->l, x)) return right;\n        if (right == _intervals.begin())\
    \ return right;\n        auto left = std::prev(right);\n        if (!(x < left->r))\
    \ return right;\n\n        right = _intervals.emplace_hint(right, interval_type{x,\
    \ left->r, left->value});\n        auto node = _intervals.extract(left);\n   \
    \     node.value().r = std::move(x);\n        _intervals.insert(right, std::move(node));\n\
    \        return right;\n    }\n\n    template <class Callback>\n    iterator erase_range(Key\
    \ l, Key r, Callback& on_erase) {\n        auto last = split(r);\n        auto\
    \ first = split(l);\n        for (auto it = first; it != last; ++it) on_erase(it->l,\
    \ it->r, it->value);\n        return _intervals.erase(first, last);\n    }\n\n\
    \   public:\n    using const_iterator = typename Set::const_iterator;\n\n    IntervalMap()\
    \ = default;\n\n    IntervalMap(Key l, Key r, T value) { assign(l, r, std::move(value));\
    \ }\n\n    // Input intervals must be nonempty, sorted, and nonoverlapping.\n\
    \    explicit IntervalMap(const std::vector<interval_type>& intervals) {\n   \
    \     for (const auto& interval : intervals) {\n            assert(interval.l\
    \ < interval.r);\n            if (!_intervals.empty()) {\n                auto\
    \ previous = std::prev(_intervals.end());\n                assert(!(interval.l\
    \ < previous->r));\n                if (equal_key(previous->r, interval.l) &&\
    \ previous->value == interval.value) {\n                    auto node = _intervals.extract(previous);\n\
    \                    node.value().r = interval.r;\n                    _intervals.insert(_intervals.end(),\
    \ std::move(node));\n                    continue;\n                }\n      \
    \      }\n            _intervals.insert(_intervals.end(), interval);\n       \
    \ }\n    }\n\n    // Dense array convenience constructor: values[i] is assigned\
    \ to [i, i + 1).\n    explicit IntervalMap(const std::vector<T>& values) requires\
    \ std::same_as<Key, int> {\n        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        const int n = int(values.size());\n        for (int l = 0; l < n;) {\n\
    \            int r = l + 1;\n            while (r < n && values[l] == values[r])\
    \ ++r;\n            _intervals.emplace_hint(_intervals.end(), interval_type{l,\
    \ r, values[l]});\n            l = r;\n        }\n    }\n\n    int size() const\
    \ { return int(_intervals.size()); }\n\n    bool empty() const { return _intervals.empty();\
    \ }\n\n    void clear() { _intervals.clear(); }\n\n    // Returns the interval\
    \ containing x, rather than requiring x to be a boundary.\n    const_iterator\
    \ find(Key x) const {\n        auto it = _intervals.upper_bound(x);\n        if\
    \ (it == _intervals.begin()) return _intervals.end();\n        --it;\n       \
    \ return x < it->r ? it : _intervals.end();\n    }\n\n    bool contains(Key x)\
    \ const { return find(x) != end(); }\n\n    const T& get(Key x) const {\n    \
    \    auto it = find(x);\n        assert(it != end());\n        return it->value;\n\
    \    }\n\n    const T* get_if(Key x) const {\n        auto it = find(x);\n   \
    \     return it == end() ? nullptr : std::addressof(it->value);\n    }\n\n   \
    \ void assign(Key l, Key r, T value) {\n        assign(l, r, std::move(value),\
    \ [](Key, Key, const T&) {});\n    }\n\n    // Calls on_erase(a, b, old_value)\
    \ for covered parts of [l, r), even when\n    // old_value == value. Gaps do not\
    \ generate callbacks. The value is owned\n    // before any erasure, so assign(l,\
    \ r, get(x)) is safe.\n    template <class Callback>\n    void assign(Key l, Key\
    \ r, T value, Callback&& on_erase) {\n        assert(!(r < l));\n        if (!(l\
    \ < r)) return;\n        auto right = erase_range(l, r, on_erase);\n\n       \
    \ if (right != _intervals.begin()) {\n            auto left = std::prev(right);\n\
    \            if (equal_key(left->r, l) && left->value == value) {\n          \
    \      l = left->l;\n                _intervals.erase(left);\n            }\n\
    \        }\n        if (right != _intervals.end() && equal_key(r, right->l) &&\
    \ right->value == value) {\n            r = right->r;\n            right = _intervals.erase(right);\n\
    \        }\n        _intervals.emplace_hint(right, interval_type{std::move(l),\
    \ std::move(r), std::move(value)});\n    }\n\n    void erase(Key l, Key r) { erase(l,\
    \ r, [](Key, Key, const T&) {}); }\n\n    template <class Callback>\n    void\
    \ erase(Key l, Key r, Callback&& on_erase) {\n        assert(!(r < l));\n    \
    \    if (l < r) erase_range(l, r, on_erase);\n    }\n\n    // Visits the covered\
    \ parts of [l, r), clipped to the query and in order.\n    // No callback may\
    \ modify this map while traversal or an update is active.\n    template <class\
    \ Callback>\n    void for_each(Key l, Key r, Callback&& callback) const {\n  \
    \      assert(!(r < l));\n        if (!(l < r)) return;\n        auto it = _intervals.lower_bound(l);\n\
    \        if (it != _intervals.begin()) {\n            auto previous = std::prev(it);\n\
    \            if (l < previous->r) it = previous;\n        }\n        for (; it\
    \ != _intervals.end() && it->l < r; ++it) {\n            callback(std::max(l,\
    \ it->l), std::min(r, it->r), it->value);\n        }\n    }\n\n    std::vector<interval_type>\
    \ to_vector() const {\n        return std::vector<interval_type>(begin(), end());\n\
    \    }\n\n    const_iterator begin() const { return _intervals.begin(); }\n\n\
    \    const_iterator end() const { return _intervals.end(); }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/interval_set/interval_map.test.cpp\"\
    \n\n#line 7 \"verify/ds/interval_set/interval_map.test.cpp\"\n#include <cstdint>\n\
    #line 9 \"verify/ds/interval_set/interval_map.test.cpp\"\n#include <optional>\n\
    #line 12 \"verify/ds/interval_set/interval_map.test.cpp\"\n\n#line 1 \"ds/segtree/segtree.hpp\"\
    \n\n\n\n#line 8 \"ds/segtree/segtree.hpp\"\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr T\
    \ bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
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
    \ namespace m1une\n\n\n#line 11 \"ds/segtree/segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A generic Segment Tree utilizing C++20 Concepts for\
    \ type safety.\n// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct Segtree {\n    using T = typename\
    \ Monoid::value_type;\n\n   private:\n    int _n, _size, _log;\n    std::vector<T>\
    \ _d;\n\n    void update(int k) {\n        _d[k] = Monoid::op(_d[2 * k], _d[2\
    \ * k + 1]);\n    }\n\n   public:\n    // Constructs an empty segment tree.\n\
    \    Segtree() : Segtree(0) {}\n\n    // Constructs a segment tree of size `n`,\
    \ initialized with the identity element.\n    explicit Segtree(int n) : Segtree(std::vector<T>(n,\
    \ Monoid::id())) {}\n\n    // Constructs a segment tree from an existing vector.\n\
    \    explicit Segtree(const std::vector<T>& v) : _n(int(v.size())) {\n       \
    \ _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n    \
    \    while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size + i]\
    \ = v[i];\n        for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n  \
    \  explicit Segtree(std::vector<T>&& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2 * _size,\
    \ Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);\n\
    \        for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Constructs\
    \ a segment tree from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. Monoid::make(val)\
    \ if it exists.\n    // 2. Monoid::make(val, index) if the monoid requires global\
    \ indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit Segtree(const std::vector<U>&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n;\
    \ i++) {\n            if constexpr (requires(U x) { Monoid::make(x); }) {\n  \
    \              _d[_size + i] = Monoid::make(v[i]);\n            } else if constexpr\
    \ (requires(U x, int idx) { Monoid::make(x, idx); }) {\n                _d[_size\
    \ + i] = Monoid::make(v[i], i);\n            } else {\n                _d[_size\
    \ + i] = static_cast<T>(v[i]);\n            }\n        }\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Returns the number of elements.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Sets the value of the element at index `p` to `x`.\n    void set(int p,\
    \ T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        _d[p]\
    \ = x;\n        for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n   \
    \ // Returns the value of the element at index `p`.\n    T get(int p) const {\n\
    \        assert(0 <= p && p < _n);\n        return _d[p + _size];\n    }\n\n \
    \   // Returns the value of the element at index `p`.\n    T operator[](int p)\
    \ const {\n        return get(p);\n    }\n\n    // Returns the product (result\
    \ of the monoid operation) in the range [l, r).\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        T sml = Monoid::id(),\
    \ smr = Monoid::id();\n        l += _size;\n        r += _size;\n        while\
    \ (l < r) {\n            if (l & 1) sml = Monoid::op(sml, _d[l++]);\n        \
    \    if (r & 1) smr = Monoid::op(_d[--r], smr);\n            l >>= 1;\n      \
    \      r >>= 1;\n        }\n        return Monoid::op(sml, smr);\n    }\n\n  \
    \  // Returns the product of the entire array.\n    T all_prod() const {\n   \
    \     return _d[1];\n    }\n\n    // Returns all elements as a vector.\n    std::vector<T>\
    \ to_vector() const {\n        return to_vector(0, _n);\n    }\n\n    // Returns\
    \ the elements in the range [l, r) as a vector.\n    std::vector<T> to_vector(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        for (int i = l; i < r; i++) res.push_back(_d[_size\
    \ + i]);\n        return res;\n    }\n\n    // Finds the largest `r` such that\
    \ `f(prod(l, r))` is true.\n    // Uses a custom functor or lambda `f`.\n    template\
    \ <class F>\n    int max_right(int l, F f) const {\n        assert(0 <= l && l\
    \ <= _n);\n        assert(f(Monoid::id()));\n        if (l == _n) return _n;\n\
    \        l += _size;\n        T sm = Monoid::id();\n        do {\n           \
    \ while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm, _d[l]))) {\n\
    \                while (l < _size) {\n                    l = (2 * l);\n     \
    \               if (f(Monoid::op(sm, _d[l]))) {\n                        sm =\
    \ Monoid::op(sm, _d[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - _size;\n            }\n       \
    \     sm = Monoid::op(sm, _d[l]);\n            l++;\n        } while ((l & -l)\
    \ != l);\n        return _n;\n    }\n\n    // Finds the smallest `l` such that\
    \ `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int r, F\
    \ f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"\
    math/modint.hpp\"\n#include <iostream>\n#include <type_traits>\n#line 9 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n\
    \   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr ModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n  \
    \          if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
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
    \ math\n}  // namespace m1une\n\n\n#line 1 \"monoid/power.hpp\"\n\n\n\n#line 5\
    \ \"monoid/power.hpp\"\n\nnamespace m1une {\nnamespace monoid {\n\n// Computes\
    \ a^n (a * a * ... * a, n times) for an element 'a' in Monoid 'M'.\n// Uses binary\
    \ exponentiation to achieve O(log n) time complexity.\n// The template parameter\
    \ 'M' is constrained by the 'IsMonoid' concept.\ntemplate <IsMonoid M>\nconstexpr\
    \ typename M::value_type power(typename M::value_type a, long long n) {\n    typename\
    \ M::value_type res = M::id();\n    while (n > 0) {\n        if (n & 1) {\n  \
    \          res = M::op(res, a);\n        }\n        a = M::op(a, a);\n       \
    \ n >>= 1;\n    }\n    return res;\n}\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#line 14 \"utilities/fast_io.hpp\"\n#include <string>\n#include <sys/stat.h>\n\
    #line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n#line 20 \"utilities/fast_io.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\nstruct FastOutput;\n\nnamespace\
    \ internal {\n\n// Shared with the convenience helpers in template.hpp.\ninline\
    \ FastOutput* standard_output_instance = nullptr;\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ m1une\n\n\n#line 17 \"verify/ds/interval_set/interval_map.test.cpp\"\n\nnamespace\
    \ {\n\nusing Map = m1une::ds::IntervalMap<int, int>;\nusing Interval = Map::interval_type;\n\
    \nvoid assert_intervals(const std::vector<Interval>& actual, const std::vector<Interval>&\
    \ expected) {\n    assert(actual.size() == expected.size());\n    for (int i =\
    \ 0; i < int(actual.size()); ++i) {\n        assert(actual[i].l == expected[i].l);\n\
    \        assert(actual[i].r == expected[i].r);\n        assert(actual[i].value\
    \ == expected[i].value);\n    }\n}\n\nstd::vector<Interval> naive_intervals(const\
    \ std::vector<std::optional<int>>& values) {\n    std::vector<Interval> result;\n\
    \    for (int l = 0; l < int(values.size());) {\n        if (!values[l].has_value())\
    \ {\n            ++l;\n            continue;\n        }\n        int r = l + 1;\n\
    \        while (r < int(values.size()) && values[l] == values[r]) ++r;\n     \
    \   result.push_back(Interval{l - 16, r - 16, *values[l]});\n        l = r;\n\
    \    }\n    return result;\n}\n\nstd::vector<Interval> clipped(const std::vector<Interval>&\
    \ intervals, int l, int r) {\n    std::vector<Interval> result;\n    for (const\
    \ auto& interval : intervals) {\n        int a = std::max(l, interval.l);\n  \
    \      int b = std::min(r, interval.r);\n        if (a < b) result.push_back(Interval{a,\
    \ b, interval.value});\n    }\n    return result;\n}\n\nvoid check_map(const Map&\
    \ map, const std::vector<std::optional<int>>& values) {\n    auto expected = naive_intervals(values);\n\
    \    assert_intervals(map.to_vector(), expected);\n    assert(map.size() == int(expected.size()));\n\
    \    assert(map.empty() == expected.empty());\n    assert_intervals(std::vector<Interval>(map.begin(),\
    \ map.end()), expected);\n    for (int i = 0; i < int(values.size()); ++i) {\n\
    \        int x = i - 16;\n        assert(map.contains(x) == values[i].has_value());\n\
    \        const int* value = map.get_if(x);\n        auto it = map.find(x);\n \
    \       assert((value != nullptr) == values[i].has_value());\n        assert((it\
    \ != map.end()) == values[i].has_value());\n        if (value != nullptr) {\n\
    \            assert(*value == *values[i]);\n            assert(map.get(x) == *values[i]);\n\
    \            assert(it->l <= x && x < it->r && it->value == *values[i]);\n   \
    \     }\n    }\n    assert(!map.contains(-17));\n    assert(!map.contains(16));\n\
    \    assert_intervals(map.to_vector(), expected);  // Const queries preserve the\
    \ partition.\n}\n\nvoid test_boundaries() {\n    Map map;\n    int callbacks =\
    \ 0;\n    auto count = [&](int, int, const int&) { ++callbacks; };\n    map.assign(3,\
    \ 3, 7, count);\n    map.erase(3, 3, count);\n    map.for_each(3, 3, count);\n\
    \    assert(map.empty() && callbacks == 0);\n\n    map.assign(0, 2, 7);\n    map.assign(4,\
    \ 6, 7);\n    assert(map.size() == 2 && map.get_if(2) == nullptr);\n    map.assign(2,\
    \ 4, 7, count);  // Filling a gap merges both neighbors without callbacks.\n \
    \   assert(map.size() == 1 && map.begin()->l == 0 && map.begin()->r == 6);\n \
    \   assert(callbacks == 0);\n    map.assign(1, 5, map.get(2), count);  // Aliased\
    \ input survives erasure.\n    assert(callbacks == 1 && map.size() == 1);\n  \
    \  map.erase(2, 4);\n    assert(map.size() == 2 && map.find(2) == map.end());\n\
    \    map.assign(1, 5, 9);\n    assert(map.size() == 3 && map.get(0) == 7 && map.get(5)\
    \ == 7);\n\n    std::vector<Interval> input;\n    input.push_back(Interval{-10,\
    \ -4, 3});\n    input.push_back(Interval{-4, 0, 3});\n    input.push_back(Interval{2,\
    \ 5, 3});\n    Map sorted(input);\n    assert(sorted.size() == 2 && sorted.begin()->r\
    \ == 0);\n    Map copied = sorted;\n    copied.assign(-10, 5, 1);\n    assert(sorted.size()\
    \ == 2 && copied.size() == 1);\n    Map moved = std::move(copied);\n    assert(moved.size()\
    \ == 1 && moved.get(0) == 1);\n    moved.clear();\n    assert(moved.empty());\n\
    \    Map no_runs(std::vector<Interval>{});\n    Map no_values(std::vector<int>{});\n\
    \    assert(no_runs.empty() && no_values.empty());\n    Map empty_range(0, 0,\
    \ 4);\n    assert(empty_range.empty());\n\n    using WideMap = m1une::ds::IntervalMap<long\
    \ long, int>;\n    const long long lo = std::numeric_limits<long long>::lowest();\n\
    \    const long long hi = std::numeric_limits<long long>::max();\n    WideMap\
    \ wide(lo, hi, 1);\n    wide.assign(lo, 0, 2);\n    wide.assign(0, hi, 2);\n \
    \   assert(wide.size() == 1 && wide.get(lo) == 2 && wide.get(hi - 1) == 2);\n\
    \    assert(!wide.contains(hi));\n    wide.erase(lo, hi);\n    assert(wide.empty());\n\
    }\n\nstruct Coordinate {\n    long long x;\n    explicit Coordinate(long long\
    \ value) : x(value) {}\n    friend bool operator<(const Coordinate& a, const Coordinate&\
    \ b) { return a.x < b.x; }\n};\n\nstruct Label {\n    int id;\n    explicit Label(int\
    \ value) : id(value) {}\n    bool operator==(const Label&) const = default;\n\
    \    const Label* operator&() const { return nullptr; }\n};\n\nvoid test_generic_types()\
    \ {\n    using GenericMap = m1une::ds::IntervalMap<Coordinate, Label>;\n    GenericMap\
    \ map(Coordinate(-10), Coordinate(10), Label(3));\n    map.assign(Coordinate(-2),\
    \ Coordinate(2), Label(8));\n    assert(map.get(Coordinate(0)).id == 8);\n   \
    \ assert(map.get_if(Coordinate(0)) != nullptr);\n    map.assign(Coordinate(-2),\
    \ Coordinate(2), map.get(Coordinate(-5)));\n    assert(map.size() == 1);\n   \
    \ map.erase(Coordinate(-1), Coordinate(1));\n    assert(map.size() == 2 && !map.contains(Coordinate(0)));\n\
    \n    struct Counter {\n        int calls = 0;\n        Counter() = default;\n\
    \        Counter(const Counter&) = delete;\n        void operator()(Coordinate\
    \ l, Coordinate r, const Label& value) {\n            assert(l.x < r.x && value.id\
    \ == 3);\n            ++calls;\n        }\n    };\n    Counter counter;\n    map.for_each(Coordinate(-100),\
    \ Coordinate(100), counter);\n    assert(counter.calls == 2);\n    map.erase(Coordinate(-100),\
    \ Coordinate(100), counter);\n    assert(counter.calls == 4 && map.empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 20261117;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n    for (int trial = 0; trial < 60; ++trial) {\n \
    \       std::vector<std::optional<int>> values(32);\n        Map map;\n      \
    \  for (int step = 0; step < 350; ++step) {\n            int l = int(random()\
    \ % 33);\n            int r = int(random() % 33);\n            if (r < l) std::swap(l,\
    \ r);\n            int value = int(random() % 5) - 2;\n            int type =\
    \ int(random() % 5);\n            auto before = naive_intervals(values);\n   \
    \         std::vector<Interval> visited;\n            auto callback = [&](int\
    \ a, int b, const int& old_value) {\n                visited.push_back(Interval{a,\
    \ b, old_value});\n            };\n            if (type == 0) {\n            \
    \    map.assign(l - 16, r - 16, value, callback);\n                for (int i\
    \ = l; i < r; ++i) values[i] = value;\n            } else if (type == 1) {\n \
    \               map.erase(l - 16, r - 16, callback);\n                for (int\
    \ i = l; i < r; ++i) values[i].reset();\n            } else if (type == 2) {\n\
    \                const Map& view = map;\n                view.for_each(l - 16,\
    \ r - 16, callback);\n            } else if (type == 3) {\n                map.assign(l\
    \ - 16, r - 16, value);\n                for (int i = l; i < r; ++i) values[i]\
    \ = value;\n            } else {\n                map.erase(l - 16, r - 16);\n\
    \                for (int i = l; i < r; ++i) values[i].reset();\n            }\n\
    \            if (type <= 2) assert_intervals(visited, clipped(before, l - 16,\
    \ r - 16));\n            check_map(map, values);\n        }\n\n        std::vector<int>\
    \ dense(32);\n        for (int& value : dense) value = int(random() % 4);\n  \
    \      Map from_values(dense);\n        for (int i = 0; i < 32; ++i) assert(from_values.get(i)\
    \ == dense[i]);\n        int runs = 0;\n        for (int i = 0; i < 32; ++i) runs\
    \ += i == 0 || dense[i] != dense[i - 1];\n        assert(from_values.size() ==\
    \ runs);\n    }\n}\n\nusing Mint = m1une::math::modint998244353;\nusing Function\
    \ = std::pair<Mint, Mint>;\n\nstruct Composition {\n    using value_type = Function;\n\
    \    static Function id() { return {Mint(1), Mint(0)}; }\n    static Function\
    \ op(const Function& a, const Function& b) {\n        return {b.first * a.first,\
    \ b.first * a.second + b.second};\n    }\n};\n\n// One segment-tree marker per\
    \ constant run. The interval map determines which\n// markers to remove and which\
    \ boundary fragments to rebuild after assignment.\nclass RunProducts {\n    int\
    \ _n;\n    m1une::ds::IntervalMap<int, Function> _runs;\n    m1une::ds::Segtree<Composition>\
    \ _products;\n\n    void rebuild(int position) {\n        auto run = _runs.find(position);\n\
    \        _products.set(run->l, m1une::monoid::power<Composition>(run->value, run->r\
    \ - run->l));\n    }\n\n   public:\n    explicit RunProducts(const std::vector<Function>&\
    \ functions)\n        : _n(int(functions.size())), _runs(functions), _products(_n)\
    \ {\n        for (const auto& run : _runs) rebuild(run.l);\n    }\n\n    void\
    \ assign(int l, int r, Function value) {\n        if (l == r) return;\n      \
    \  _products.set(_runs.find(l)->l, Composition::id());\n        if (r < _n) _products.set(_runs.find(r)->l,\
    \ Composition::id());\n        _runs.assign(l, r, value, [&](int a, int, const\
    \ Function&) {\n            _products.set(a, Composition::id());\n        });\n\
    \        if (l > 0) rebuild(l - 1);\n        rebuild(l);\n        if (r < _n)\
    \ rebuild(r);\n    }\n\n    Function prod(int l, int r) const {\n        if (l\
    \ == r) return Composition::id();\n        auto first = _runs.find(l);\n     \
    \   auto last = _runs.find(r - 1);\n        if (first == last) return m1une::monoid::power<Composition>(first->value,\
    \ r - l);\n        Function result = m1une::monoid::power<Composition>(first->value,\
    \ first->r - l);\n        result = Composition::op(result, _products.prod(first->r,\
    \ last->l));\n        return Composition::op(result, m1une::monoid::power<Composition>(last->value,\
    \ r - last->l));\n    }\n};\n\nvoid test_run_products() {\n    std::uint64_t state\
    \ = 123456789;\n    auto random = [&]() {\n        state ^= state << 7;\n    \
    \    state ^= state >> 9;\n        return state;\n    };\n    for (int trial =\
    \ 0; trial < 30; ++trial) {\n        const int n = 1 + int(random() % 20);\n \
    \       std::vector<Function> values(n);\n        for (auto& value : values) value\
    \ = Function{Mint(random() % 4), Mint(random() % 4)};\n        RunProducts runs(values);\n\
    \        for (int step = 0; step < 150; ++step) {\n            int l = int(random()\
    \ % (n + 1));\n            int r = int(random() % (n + 1));\n            if (r\
    \ < l) std::swap(l, r);\n            if (random() & 1) {\n                Function\
    \ value = {Mint(random() % 4), Mint(random() % 4)};\n                runs.assign(l,\
    \ r, value);\n                std::fill(values.begin() + l, values.begin() + r,\
    \ value);\n            }\n            Function expected = Composition::id();\n\
    \            for (int i = l; i < r; ++i) expected = Composition::op(expected,\
    \ values[i]);\n            assert(runs.prod(l, r) == expected);\n        }\n \
    \   }\n}\n\n}  // namespace\n\nint main() {\n    test_boundaries();\n    test_generic_types();\n\
    \    test_randomized();\n    test_run_products();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    input >>\
    \ n >> q;\n    std::vector<Function> functions(n);\n    for (auto& function :\
    \ functions) {\n        int a, b;\n        input >> a >> b;\n        function\
    \ = Function{Mint(a), Mint(b)};\n    }\n    RunProducts runs(functions);\n   \
    \ while (q--) {\n        int type, l, r, x;\n        input >> type >> l >> r >>\
    \ x;\n        if (type == 0) {\n            int b;\n            input >> b;\n\
    \            runs.assign(l, r, Function{Mint(x), Mint(b)});\n        } else {\n\
    \            Function result = runs.prod(l, r);\n            output << (result.first\
    \ * Mint(x) + result.second) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_set_range_composite\"\
    \n\n#include \"../../../ds/interval_set/interval_map.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../../ds/segtree/segtree.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n#include \"../../../monoid/power.hpp\"\
    \n#include \"../../../utilities/fast_io.hpp\"\n\nnamespace {\n\nusing Map = m1une::ds::IntervalMap<int,\
    \ int>;\nusing Interval = Map::interval_type;\n\nvoid assert_intervals(const std::vector<Interval>&\
    \ actual, const std::vector<Interval>& expected) {\n    assert(actual.size() ==\
    \ expected.size());\n    for (int i = 0; i < int(actual.size()); ++i) {\n    \
    \    assert(actual[i].l == expected[i].l);\n        assert(actual[i].r == expected[i].r);\n\
    \        assert(actual[i].value == expected[i].value);\n    }\n}\n\nstd::vector<Interval>\
    \ naive_intervals(const std::vector<std::optional<int>>& values) {\n    std::vector<Interval>\
    \ result;\n    for (int l = 0; l < int(values.size());) {\n        if (!values[l].has_value())\
    \ {\n            ++l;\n            continue;\n        }\n        int r = l + 1;\n\
    \        while (r < int(values.size()) && values[l] == values[r]) ++r;\n     \
    \   result.push_back(Interval{l - 16, r - 16, *values[l]});\n        l = r;\n\
    \    }\n    return result;\n}\n\nstd::vector<Interval> clipped(const std::vector<Interval>&\
    \ intervals, int l, int r) {\n    std::vector<Interval> result;\n    for (const\
    \ auto& interval : intervals) {\n        int a = std::max(l, interval.l);\n  \
    \      int b = std::min(r, interval.r);\n        if (a < b) result.push_back(Interval{a,\
    \ b, interval.value});\n    }\n    return result;\n}\n\nvoid check_map(const Map&\
    \ map, const std::vector<std::optional<int>>& values) {\n    auto expected = naive_intervals(values);\n\
    \    assert_intervals(map.to_vector(), expected);\n    assert(map.size() == int(expected.size()));\n\
    \    assert(map.empty() == expected.empty());\n    assert_intervals(std::vector<Interval>(map.begin(),\
    \ map.end()), expected);\n    for (int i = 0; i < int(values.size()); ++i) {\n\
    \        int x = i - 16;\n        assert(map.contains(x) == values[i].has_value());\n\
    \        const int* value = map.get_if(x);\n        auto it = map.find(x);\n \
    \       assert((value != nullptr) == values[i].has_value());\n        assert((it\
    \ != map.end()) == values[i].has_value());\n        if (value != nullptr) {\n\
    \            assert(*value == *values[i]);\n            assert(map.get(x) == *values[i]);\n\
    \            assert(it->l <= x && x < it->r && it->value == *values[i]);\n   \
    \     }\n    }\n    assert(!map.contains(-17));\n    assert(!map.contains(16));\n\
    \    assert_intervals(map.to_vector(), expected);  // Const queries preserve the\
    \ partition.\n}\n\nvoid test_boundaries() {\n    Map map;\n    int callbacks =\
    \ 0;\n    auto count = [&](int, int, const int&) { ++callbacks; };\n    map.assign(3,\
    \ 3, 7, count);\n    map.erase(3, 3, count);\n    map.for_each(3, 3, count);\n\
    \    assert(map.empty() && callbacks == 0);\n\n    map.assign(0, 2, 7);\n    map.assign(4,\
    \ 6, 7);\n    assert(map.size() == 2 && map.get_if(2) == nullptr);\n    map.assign(2,\
    \ 4, 7, count);  // Filling a gap merges both neighbors without callbacks.\n \
    \   assert(map.size() == 1 && map.begin()->l == 0 && map.begin()->r == 6);\n \
    \   assert(callbacks == 0);\n    map.assign(1, 5, map.get(2), count);  // Aliased\
    \ input survives erasure.\n    assert(callbacks == 1 && map.size() == 1);\n  \
    \  map.erase(2, 4);\n    assert(map.size() == 2 && map.find(2) == map.end());\n\
    \    map.assign(1, 5, 9);\n    assert(map.size() == 3 && map.get(0) == 7 && map.get(5)\
    \ == 7);\n\n    std::vector<Interval> input;\n    input.push_back(Interval{-10,\
    \ -4, 3});\n    input.push_back(Interval{-4, 0, 3});\n    input.push_back(Interval{2,\
    \ 5, 3});\n    Map sorted(input);\n    assert(sorted.size() == 2 && sorted.begin()->r\
    \ == 0);\n    Map copied = sorted;\n    copied.assign(-10, 5, 1);\n    assert(sorted.size()\
    \ == 2 && copied.size() == 1);\n    Map moved = std::move(copied);\n    assert(moved.size()\
    \ == 1 && moved.get(0) == 1);\n    moved.clear();\n    assert(moved.empty());\n\
    \    Map no_runs(std::vector<Interval>{});\n    Map no_values(std::vector<int>{});\n\
    \    assert(no_runs.empty() && no_values.empty());\n    Map empty_range(0, 0,\
    \ 4);\n    assert(empty_range.empty());\n\n    using WideMap = m1une::ds::IntervalMap<long\
    \ long, int>;\n    const long long lo = std::numeric_limits<long long>::lowest();\n\
    \    const long long hi = std::numeric_limits<long long>::max();\n    WideMap\
    \ wide(lo, hi, 1);\n    wide.assign(lo, 0, 2);\n    wide.assign(0, hi, 2);\n \
    \   assert(wide.size() == 1 && wide.get(lo) == 2 && wide.get(hi - 1) == 2);\n\
    \    assert(!wide.contains(hi));\n    wide.erase(lo, hi);\n    assert(wide.empty());\n\
    }\n\nstruct Coordinate {\n    long long x;\n    explicit Coordinate(long long\
    \ value) : x(value) {}\n    friend bool operator<(const Coordinate& a, const Coordinate&\
    \ b) { return a.x < b.x; }\n};\n\nstruct Label {\n    int id;\n    explicit Label(int\
    \ value) : id(value) {}\n    bool operator==(const Label&) const = default;\n\
    \    const Label* operator&() const { return nullptr; }\n};\n\nvoid test_generic_types()\
    \ {\n    using GenericMap = m1une::ds::IntervalMap<Coordinate, Label>;\n    GenericMap\
    \ map(Coordinate(-10), Coordinate(10), Label(3));\n    map.assign(Coordinate(-2),\
    \ Coordinate(2), Label(8));\n    assert(map.get(Coordinate(0)).id == 8);\n   \
    \ assert(map.get_if(Coordinate(0)) != nullptr);\n    map.assign(Coordinate(-2),\
    \ Coordinate(2), map.get(Coordinate(-5)));\n    assert(map.size() == 1);\n   \
    \ map.erase(Coordinate(-1), Coordinate(1));\n    assert(map.size() == 2 && !map.contains(Coordinate(0)));\n\
    \n    struct Counter {\n        int calls = 0;\n        Counter() = default;\n\
    \        Counter(const Counter&) = delete;\n        void operator()(Coordinate\
    \ l, Coordinate r, const Label& value) {\n            assert(l.x < r.x && value.id\
    \ == 3);\n            ++calls;\n        }\n    };\n    Counter counter;\n    map.for_each(Coordinate(-100),\
    \ Coordinate(100), counter);\n    assert(counter.calls == 2);\n    map.erase(Coordinate(-100),\
    \ Coordinate(100), counter);\n    assert(counter.calls == 4 && map.empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 20261117;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n    for (int trial = 0; trial < 60; ++trial) {\n \
    \       std::vector<std::optional<int>> values(32);\n        Map map;\n      \
    \  for (int step = 0; step < 350; ++step) {\n            int l = int(random()\
    \ % 33);\n            int r = int(random() % 33);\n            if (r < l) std::swap(l,\
    \ r);\n            int value = int(random() % 5) - 2;\n            int type =\
    \ int(random() % 5);\n            auto before = naive_intervals(values);\n   \
    \         std::vector<Interval> visited;\n            auto callback = [&](int\
    \ a, int b, const int& old_value) {\n                visited.push_back(Interval{a,\
    \ b, old_value});\n            };\n            if (type == 0) {\n            \
    \    map.assign(l - 16, r - 16, value, callback);\n                for (int i\
    \ = l; i < r; ++i) values[i] = value;\n            } else if (type == 1) {\n \
    \               map.erase(l - 16, r - 16, callback);\n                for (int\
    \ i = l; i < r; ++i) values[i].reset();\n            } else if (type == 2) {\n\
    \                const Map& view = map;\n                view.for_each(l - 16,\
    \ r - 16, callback);\n            } else if (type == 3) {\n                map.assign(l\
    \ - 16, r - 16, value);\n                for (int i = l; i < r; ++i) values[i]\
    \ = value;\n            } else {\n                map.erase(l - 16, r - 16);\n\
    \                for (int i = l; i < r; ++i) values[i].reset();\n            }\n\
    \            if (type <= 2) assert_intervals(visited, clipped(before, l - 16,\
    \ r - 16));\n            check_map(map, values);\n        }\n\n        std::vector<int>\
    \ dense(32);\n        for (int& value : dense) value = int(random() % 4);\n  \
    \      Map from_values(dense);\n        for (int i = 0; i < 32; ++i) assert(from_values.get(i)\
    \ == dense[i]);\n        int runs = 0;\n        for (int i = 0; i < 32; ++i) runs\
    \ += i == 0 || dense[i] != dense[i - 1];\n        assert(from_values.size() ==\
    \ runs);\n    }\n}\n\nusing Mint = m1une::math::modint998244353;\nusing Function\
    \ = std::pair<Mint, Mint>;\n\nstruct Composition {\n    using value_type = Function;\n\
    \    static Function id() { return {Mint(1), Mint(0)}; }\n    static Function\
    \ op(const Function& a, const Function& b) {\n        return {b.first * a.first,\
    \ b.first * a.second + b.second};\n    }\n};\n\n// One segment-tree marker per\
    \ constant run. The interval map determines which\n// markers to remove and which\
    \ boundary fragments to rebuild after assignment.\nclass RunProducts {\n    int\
    \ _n;\n    m1une::ds::IntervalMap<int, Function> _runs;\n    m1une::ds::Segtree<Composition>\
    \ _products;\n\n    void rebuild(int position) {\n        auto run = _runs.find(position);\n\
    \        _products.set(run->l, m1une::monoid::power<Composition>(run->value, run->r\
    \ - run->l));\n    }\n\n   public:\n    explicit RunProducts(const std::vector<Function>&\
    \ functions)\n        : _n(int(functions.size())), _runs(functions), _products(_n)\
    \ {\n        for (const auto& run : _runs) rebuild(run.l);\n    }\n\n    void\
    \ assign(int l, int r, Function value) {\n        if (l == r) return;\n      \
    \  _products.set(_runs.find(l)->l, Composition::id());\n        if (r < _n) _products.set(_runs.find(r)->l,\
    \ Composition::id());\n        _runs.assign(l, r, value, [&](int a, int, const\
    \ Function&) {\n            _products.set(a, Composition::id());\n        });\n\
    \        if (l > 0) rebuild(l - 1);\n        rebuild(l);\n        if (r < _n)\
    \ rebuild(r);\n    }\n\n    Function prod(int l, int r) const {\n        if (l\
    \ == r) return Composition::id();\n        auto first = _runs.find(l);\n     \
    \   auto last = _runs.find(r - 1);\n        if (first == last) return m1une::monoid::power<Composition>(first->value,\
    \ r - l);\n        Function result = m1une::monoid::power<Composition>(first->value,\
    \ first->r - l);\n        result = Composition::op(result, _products.prod(first->r,\
    \ last->l));\n        return Composition::op(result, m1une::monoid::power<Composition>(last->value,\
    \ r - last->l));\n    }\n};\n\nvoid test_run_products() {\n    std::uint64_t state\
    \ = 123456789;\n    auto random = [&]() {\n        state ^= state << 7;\n    \
    \    state ^= state >> 9;\n        return state;\n    };\n    for (int trial =\
    \ 0; trial < 30; ++trial) {\n        const int n = 1 + int(random() % 20);\n \
    \       std::vector<Function> values(n);\n        for (auto& value : values) value\
    \ = Function{Mint(random() % 4), Mint(random() % 4)};\n        RunProducts runs(values);\n\
    \        for (int step = 0; step < 150; ++step) {\n            int l = int(random()\
    \ % (n + 1));\n            int r = int(random() % (n + 1));\n            if (r\
    \ < l) std::swap(l, r);\n            if (random() & 1) {\n                Function\
    \ value = {Mint(random() % 4), Mint(random() % 4)};\n                runs.assign(l,\
    \ r, value);\n                std::fill(values.begin() + l, values.begin() + r,\
    \ value);\n            }\n            Function expected = Composition::id();\n\
    \            for (int i = l; i < r; ++i) expected = Composition::op(expected,\
    \ values[i]);\n            assert(runs.prod(l, r) == expected);\n        }\n \
    \   }\n}\n\n}  // namespace\n\nint main() {\n    test_boundaries();\n    test_generic_types();\n\
    \    test_randomized();\n    test_run_products();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    input >>\
    \ n >> q;\n    std::vector<Function> functions(n);\n    for (auto& function :\
    \ functions) {\n        int a, b;\n        input >> a >> b;\n        function\
    \ = Function{Mint(a), Mint(b)};\n    }\n    RunProducts runs(functions);\n   \
    \ while (q--) {\n        int type, l, r, x;\n        input >> type >> l >> r >>\
    \ x;\n        if (type == 0) {\n            int b;\n            input >> b;\n\
    \            runs.assign(l, r, Function{Mint(x), Mint(b)});\n        } else {\n\
    \            Function result = runs.prod(l, r);\n            output << (result.first\
    \ * Mint(x) + result.second) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/interval_set/interval_map.hpp
  - ds/segtree/segtree.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - math/modint.hpp
  - monoid/power.hpp
  - monoid/concept.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/interval_set/interval_map.test.cpp
  requiredBy: []
  timestamp: '2026-11-17 03:01:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/interval_set/interval_map.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/interval_set/interval_map.test.cpp
- /verify/verify/ds/interval_set/interval_map.test.cpp.html
title: verify/ds/interval_set/interval_map.test.cpp
---
