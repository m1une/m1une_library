---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
  - icon: ':heavy_check_mark:'
    path: ds/range_query/offline_rectangle_add_rectangle_sum.hpp
    title: Offline Rectangle Add Rectangle Sum
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
    PROBLEM: https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum
  bundledCode: "#line 1 \"verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum\"\
    \n\n#line 1 \"ds/range_query/offline_rectangle_add_rectangle_sum.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#line 6 \"ds/range_query/fenwick_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct FenwickTree\
    \ {\n   private:\n    int _n;\n    int _max_power;\n    std::vector<T> _data;\n\
    \n    static int max_power_leq(int n) {\n        int result = 1;\n        while\
    \ (result <= n / 2) result <<= 1;\n        return result;\n    }\n\n    T prefix_sum(int\
    \ r) const {\n        T result{};\n        const T* data = _data.data();\n   \
    \     while (r > 0) {\n            result += data[r];\n            r -= r & -r;\n\
    \        }\n        return result;\n    }\n\n   public:\n    FenwickTree() : _n(0),\
    \ _max_power(0) {}\n\n    explicit FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n\
    \ > 0 ? n : 1)), _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>&\
    \ a)\n        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0\
    \ ? _n : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i\
    \ <= _n; ++i) {\n            _data[i] += a[i - 1];\n            const int p =\
    \ i + (i & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Adds\
    \ `x` to the element at zero-based index `p`.\n    void add(int p, const T& x)\
    \ {\n        assert(0 <= p && p < _n);\n        ++p;\n        T* data = _data.data();\n\
    \        while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r).\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        return\
    \ prefix_sum(r);\n    }\n\n    // Returns the sum of elements in the range [l,\
    \ r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        return prefix_sum(r) - prefix_sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        const T* data = _data.data();\n\
    \        for (int k = _max_power; k > 0; k >>= 1) {\n            if (x + k <=\
    \ _n && data[x + k] < w) {\n                w -= data[x + k];\n              \
    \  x += k;\n            }\n        }\n        return x + 1;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 10 \"ds/range_query/offline_rectangle_add_rectangle_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Records rectangle additions and rectangle-sum\
    \ queries, then evaluates the\n// complete static batch with an offline sweep.\n\
    template <class T, class X = long long, class Y = X>\nclass OfflineRectangleAddRectangleSum\
    \ {\n   public:\n    using value_type = T;\n    using x_type = X;\n    using y_type\
    \ = Y;\n\n   private:\n    struct Update {\n        X x_lower;\n        X x_upper;\n\
    \        Y y_lower;\n        Y y_upper;\n        T value;\n    };\n\n    struct\
    \ Query {\n        X x_lower;\n        X x_upper;\n        Y y_lower;\n      \
    \  Y y_upper;\n    };\n\n    struct Coefficient {\n        T xy{};\n        T\
    \ x{};\n        T y{};\n        T constant{};\n\n        Coefficient& operator+=(const\
    \ Coefficient& other) {\n            xy += other.xy;\n            x += other.x;\n\
    \            y += other.y;\n            constant += other.constant;\n        \
    \    return *this;\n        }\n    };\n\n    struct PointEvent {\n        X x;\n\
    \        Y y;\n        Coefficient coefficient;\n    };\n\n    struct PrefixEvent\
    \ {\n        X x;\n        Y y;\n        int query_id;\n        bool subtract;\n\
    \    };\n\n    std::vector<Update> _updates;\n    std::vector<Query> _queries;\n\
    \n    template <class Coordinate>\n    static bool equivalent(const Coordinate&\
    \ first, const Coordinate& second) {\n        return !(first < second) && !(second\
    \ < first);\n    }\n\n    static Coefficient make_coefficient(\n        const\
    \ X& x,\n        const Y& y,\n        const T& signed_value\n    ) {\n       \
    \ const T converted_x(x);\n        const T converted_y(y);\n        return {\n\
    \            signed_value,\n            T{} - signed_value * converted_y,\n  \
    \          T{} - signed_value * converted_x,\n            signed_value * converted_x\
    \ * converted_y\n        };\n    }\n\n    static T evaluate(\n        const Coefficient&\
    \ coefficient,\n        const X& x,\n        const Y& y\n    ) {\n        const\
    \ T converted_x(x);\n        const T converted_y(y);\n        return coefficient.xy\
    \ * converted_x * converted_y +\n               coefficient.x * converted_x +\n\
    \               coefficient.y * converted_y +\n               coefficient.constant;\n\
    \    }\n\n   public:\n    int update_count() const {\n        return int(_updates.size());\n\
    \    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    bool empty() const {\n        return _updates.empty() && _queries.empty();\n\
    \    }\n\n    void reserve_updates(int capacity) {\n        assert(0 <= capacity);\n\
    \        _updates.reserve(capacity);\n    }\n\n    void reserve_queries(int capacity)\
    \ {\n        assert(0 <= capacity);\n        _queries.reserve(capacity);\n   \
    \ }\n\n    void clear() {\n        _updates.clear();\n        _queries.clear();\n\
    \    }\n\n    int add_rectangle(\n        const X& x_lower,\n        const X&\
    \ x_upper,\n        const Y& y_lower,\n        const Y& y_upper,\n        const\
    \ T& value\n    ) {\n        assert(!(x_upper < x_lower));\n        assert(!(y_upper\
    \ < y_lower));\n        const int id = update_count();\n        _updates.push_back(Update{x_lower,\
    \ x_upper, y_lower, y_upper, value});\n        return id;\n    }\n\n    int add_query(\n\
    \        const X& x_lower,\n        const X& x_upper,\n        const Y& y_lower,\n\
    \        const Y& y_upper\n    ) {\n        assert(!(x_upper < x_lower));\n  \
    \      assert(!(y_upper < y_lower));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{x_lower, x_upper, y_lower, y_upper});\n    \
    \    return id;\n    }\n\n    std::vector<T> calculate() const {\n        std::vector<T>\
    \ answers(_queries.size(), T{});\n        if (_queries.empty() || _updates.empty())\
    \ return answers;\n\n        std::vector<PointEvent> point_events;\n        point_events.reserve(4\
    \ * _updates.size());\n        std::vector<Y> y_coordinates;\n        y_coordinates.reserve(2\
    \ * _updates.size());\n        for (const Update& update : _updates) {\n     \
    \       if (equivalent(update.x_lower, update.x_upper) ||\n                equivalent(update.y_lower,\
    \ update.y_upper)) {\n                continue;\n            }\n            const\
    \ T negative_value = T{} - update.value;\n            point_events.push_back(PointEvent{\n\
    \                update.x_lower,\n                update.y_lower,\n          \
    \      make_coefficient(update.x_lower, update.y_lower, update.value)\n      \
    \      });\n            point_events.push_back(PointEvent{\n                update.x_lower,\n\
    \                update.y_upper,\n                make_coefficient(update.x_lower,\
    \ update.y_upper, negative_value)\n            });\n            point_events.push_back(PointEvent{\n\
    \                update.x_upper,\n                update.y_lower,\n          \
    \      make_coefficient(update.x_upper, update.y_lower, negative_value)\n    \
    \        });\n            point_events.push_back(PointEvent{\n               \
    \ update.x_upper,\n                update.y_upper,\n                make_coefficient(update.x_upper,\
    \ update.y_upper, update.value)\n            });\n            y_coordinates.push_back(update.y_lower);\n\
    \            y_coordinates.push_back(update.y_upper);\n        }\n        if (point_events.empty())\
    \ return answers;\n\n        std::sort(y_coordinates.begin(), y_coordinates.end());\n\
    \        y_coordinates.erase(\n            std::unique(\n                y_coordinates.begin(),\n\
    \                y_coordinates.end(),\n                [](const Y& first, const\
    \ Y& second) {\n                    return equivalent(first, second);\n      \
    \          }\n            ),\n            y_coordinates.end()\n        );\n  \
    \      std::sort(\n            point_events.begin(),\n            point_events.end(),\n\
    \            [](const PointEvent& first, const PointEvent& second) {\n       \
    \         return first.x < second.x;\n            }\n        );\n\n        std::vector<PrefixEvent>\
    \ prefix_events;\n        prefix_events.reserve(4 * _queries.size());\n      \
    \  for (int query_id = 0; query_id < query_count(); query_id++) {\n          \
    \  const Query& query = _queries[query_id];\n            prefix_events.push_back(PrefixEvent{\n\
    \                query.x_upper, query.y_upper, query_id, false\n            });\n\
    \            prefix_events.push_back(PrefixEvent{\n                query.x_lower,\
    \ query.y_upper, query_id, true\n            });\n            prefix_events.push_back(PrefixEvent{\n\
    \                query.x_upper, query.y_lower, query_id, true\n            });\n\
    \            prefix_events.push_back(PrefixEvent{\n                query.x_lower,\
    \ query.y_lower, query_id, false\n            });\n        }\n        std::sort(\n\
    \            prefix_events.begin(),\n            prefix_events.end(),\n      \
    \      [](const PrefixEvent& first, const PrefixEvent& second) {\n           \
    \     return first.x < second.x;\n            }\n        );\n\n        FenwickTree<Coefficient>\
    \ fenwick(int(y_coordinates.size()));\n        int point_index = 0;\n        for\
    \ (const PrefixEvent& event : prefix_events) {\n            while (\n        \
    \        point_index < int(point_events.size()) &&\n                point_events[point_index].x\
    \ < event.x\n            ) {\n                const PointEvent& point = point_events[point_index];\n\
    \                const int y_index = int(\n                    std::lower_bound(\n\
    \                        y_coordinates.begin(), y_coordinates.end(), point.y\n\
    \                    ) - y_coordinates.begin()\n                );\n         \
    \       fenwick.add(y_index, point.coefficient);\n                point_index++;\n\
    \            }\n            const int y_count = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(), y_coordinates.end(), event.y\n   \
    \             ) - y_coordinates.begin()\n            );\n            const T value\
    \ = evaluate(fenwick.sum(y_count), event.x, event.y);\n            if (event.subtract)\
    \ {\n                answers[event.query_id] -= value;\n            } else {\n\
    \                answers[event.query_id] += value;\n            }\n        }\n\
    \        return answers;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp\"\
    \n\n#line 7 \"verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp\"\
    \n#include <cstdint>\n#line 9 \"verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp\"\
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #include <type_traits>\n#line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0\
    \ < Modulus, \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\
    \n   public:\n    static constexpr uint32_t mod() {\n        return Modulus;\n\
    \    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt\
    \ x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept\
    \ : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
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
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
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
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#line 15 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
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
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp\"\
    \n\nnamespace {\n\nstruct Rectangle {\n    int x_lower;\n    int x_upper;\n  \
    \  int y_lower;\n    int y_upper;\n    long long value;\n};\n\nlong long overlap_length(int\
    \ first_lower, int first_upper, int second_lower, int second_upper) {\n    return\
    \ std::max(0, std::min(first_upper, second_upper) -\n                        \
    \   std::max(first_lower, second_lower));\n}\n\nlong long naive_sum(\n    const\
    \ std::vector<Rectangle>& updates,\n    int x_lower,\n    int x_upper,\n    int\
    \ y_lower,\n    int y_upper\n) {\n    long long result = 0;\n    for (const Rectangle&\
    \ update : updates) {\n        const long long width = overlap_length(\n     \
    \       update.x_lower, update.x_upper, x_lower, x_upper\n        );\n       \
    \ const long long height = overlap_length(\n            update.y_lower, update.y_upper,\
    \ y_lower, y_upper\n        );\n        result += width * height * update.value;\n\
    \    }\n    return result;\n}\n\nvoid test_randomized() {\n    using Solver =\
    \ m1une::ds::OfflineRectangleAddRectangleSum<long long, int>;\n\n    Solver empty;\n\
    \    assert(empty.empty());\n    assert(empty.update_count() == 0);\n    assert(empty.query_count()\
    \ == 0);\n    assert(empty.calculate().empty());\n\n    int empty_query = empty.add_query(-5,\
    \ 5, -5, 5);\n    assert(empty_query == 0);\n    assert(empty.calculate() == std::vector<long\
    \ long>(1, 0));\n    empty.clear();\n    assert(empty.empty());\n\n    Solver\
    \ unordered_batch;\n    int first_query = unordered_batch.add_query(1, 4, 1, 3);\n\
    \    unordered_batch.add_rectangle(0, 3, 0, 2, 5);\n    assert(unordered_batch.calculate()[first_query]\
    \ == 10);\n\n    std::uint64_t state = 987654321;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 400; trial++) {\n        const\
    \ int update_count = int(random() % 26);\n        const int query_count = int(random()\
    \ % 31);\n        Solver solver;\n        solver.reserve_updates(update_count);\n\
    \        solver.reserve_queries(query_count);\n        std::vector<Rectangle>\
    \ updates;\n        std::vector<long long> expected;\n\n        for (int update_id\
    \ = 0; update_id < update_count; update_id++) {\n            int x_lower = int(random()\
    \ % 21) - 10;\n            int x_upper = int(random() % 21) - 10;\n          \
    \  int y_lower = int(random() % 21) - 10;\n            int y_upper = int(random()\
    \ % 21) - 10;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n           \
    \ long long value = static_cast<long long>(random() % 21) - 10;\n            assert(\n\
    \                solver.add_rectangle(x_lower, x_upper, y_lower, y_upper, value)\
    \ ==\n                update_id\n            );\n            updates.push_back(Rectangle{x_lower,\
    \ x_upper, y_lower, y_upper, value});\n        }\n\n        for (int query_id\
    \ = 0; query_id < query_count; query_id++) {\n            int x_lower = int(random()\
    \ % 25) - 12;\n            int x_upper = int(random() % 25) - 12;\n          \
    \  int y_lower = int(random() % 25) - 12;\n            int y_upper = int(random()\
    \ % 25) - 12;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n           \
    \ assert(solver.add_query(x_lower, x_upper, y_lower, y_upper) == query_id);\n\
    \            expected.push_back(\n                naive_sum(updates, x_lower,\
    \ x_upper, y_lower, y_upper)\n            );\n        }\n\n        assert(solver.update_count()\
    \ == update_count);\n        assert(solver.query_count() == query_count);\n  \
    \      assert(solver.empty() == (update_count == 0 && query_count == 0));\n  \
    \      assert(solver.calculate() == expected);\n        assert(solver.calculate()\
    \ == expected);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \n    using Mint = m1une::math::modint998244353;\n    using Solver = m1une::ds::OfflineRectangleAddRectangleSum<Mint>;\n\
    \n    int n, q;\n    fast_input >> n >> q;\n    Solver solver;\n    solver.reserve_updates(n);\n\
    \    solver.reserve_queries(q);\n    for (int update = 0; update < n; update++)\
    \ {\n        long long left, lower, right, upper, value;\n        fast_input >>\
    \ left >> lower >> right >> upper >> value;\n        solver.add_rectangle(left,\
    \ right, lower, upper, Mint(value));\n    }\n    for (int query = 0; query < q;\
    \ query++) {\n        long long left, lower, right, upper;\n        fast_input\
    \ >> left >> lower >> right >> upper;\n        solver.add_query(left, right, lower,\
    \ upper);\n    }\n\n    for (const Mint& answer : solver.calculate()) {\n    \
    \    fast_output << answer << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum\"\
    \n\n#include \"../../../ds/range_query/offline_rectangle_add_rectangle_sum.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\
    \n#include \"../../../math/modint.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nstruct Rectangle {\n    int x_lower;\n    int x_upper;\n  \
    \  int y_lower;\n    int y_upper;\n    long long value;\n};\n\nlong long overlap_length(int\
    \ first_lower, int first_upper, int second_lower, int second_upper) {\n    return\
    \ std::max(0, std::min(first_upper, second_upper) -\n                        \
    \   std::max(first_lower, second_lower));\n}\n\nlong long naive_sum(\n    const\
    \ std::vector<Rectangle>& updates,\n    int x_lower,\n    int x_upper,\n    int\
    \ y_lower,\n    int y_upper\n) {\n    long long result = 0;\n    for (const Rectangle&\
    \ update : updates) {\n        const long long width = overlap_length(\n     \
    \       update.x_lower, update.x_upper, x_lower, x_upper\n        );\n       \
    \ const long long height = overlap_length(\n            update.y_lower, update.y_upper,\
    \ y_lower, y_upper\n        );\n        result += width * height * update.value;\n\
    \    }\n    return result;\n}\n\nvoid test_randomized() {\n    using Solver =\
    \ m1une::ds::OfflineRectangleAddRectangleSum<long long, int>;\n\n    Solver empty;\n\
    \    assert(empty.empty());\n    assert(empty.update_count() == 0);\n    assert(empty.query_count()\
    \ == 0);\n    assert(empty.calculate().empty());\n\n    int empty_query = empty.add_query(-5,\
    \ 5, -5, 5);\n    assert(empty_query == 0);\n    assert(empty.calculate() == std::vector<long\
    \ long>(1, 0));\n    empty.clear();\n    assert(empty.empty());\n\n    Solver\
    \ unordered_batch;\n    int first_query = unordered_batch.add_query(1, 4, 1, 3);\n\
    \    unordered_batch.add_rectangle(0, 3, 0, 2, 5);\n    assert(unordered_batch.calculate()[first_query]\
    \ == 10);\n\n    std::uint64_t state = 987654321;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 400; trial++) {\n        const\
    \ int update_count = int(random() % 26);\n        const int query_count = int(random()\
    \ % 31);\n        Solver solver;\n        solver.reserve_updates(update_count);\n\
    \        solver.reserve_queries(query_count);\n        std::vector<Rectangle>\
    \ updates;\n        std::vector<long long> expected;\n\n        for (int update_id\
    \ = 0; update_id < update_count; update_id++) {\n            int x_lower = int(random()\
    \ % 21) - 10;\n            int x_upper = int(random() % 21) - 10;\n          \
    \  int y_lower = int(random() % 21) - 10;\n            int y_upper = int(random()\
    \ % 21) - 10;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n           \
    \ long long value = static_cast<long long>(random() % 21) - 10;\n            assert(\n\
    \                solver.add_rectangle(x_lower, x_upper, y_lower, y_upper, value)\
    \ ==\n                update_id\n            );\n            updates.push_back(Rectangle{x_lower,\
    \ x_upper, y_lower, y_upper, value});\n        }\n\n        for (int query_id\
    \ = 0; query_id < query_count; query_id++) {\n            int x_lower = int(random()\
    \ % 25) - 12;\n            int x_upper = int(random() % 25) - 12;\n          \
    \  int y_lower = int(random() % 25) - 12;\n            int y_upper = int(random()\
    \ % 25) - 12;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n           \
    \ assert(solver.add_query(x_lower, x_upper, y_lower, y_upper) == query_id);\n\
    \            expected.push_back(\n                naive_sum(updates, x_lower,\
    \ x_upper, y_lower, y_upper)\n            );\n        }\n\n        assert(solver.update_count()\
    \ == update_count);\n        assert(solver.query_count() == query_count);\n  \
    \      assert(solver.empty() == (update_count == 0 && query_count == 0));\n  \
    \      assert(solver.calculate() == expected);\n        assert(solver.calculate()\
    \ == expected);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \n    using Mint = m1une::math::modint998244353;\n    using Solver = m1une::ds::OfflineRectangleAddRectangleSum<Mint>;\n\
    \n    int n, q;\n    fast_input >> n >> q;\n    Solver solver;\n    solver.reserve_updates(n);\n\
    \    solver.reserve_queries(q);\n    for (int update = 0; update < n; update++)\
    \ {\n        long long left, lower, right, upper, value;\n        fast_input >>\
    \ left >> lower >> right >> upper >> value;\n        solver.add_rectangle(left,\
    \ right, lower, upper, Mint(value));\n    }\n    for (int query = 0; query < q;\
    \ query++) {\n        long long left, lower, right, upper;\n        fast_input\
    \ >> left >> lower >> right >> upper;\n        solver.add_query(left, right, lower,\
    \ upper);\n    }\n\n    for (const Mint& answer : solver.calculate()) {\n    \
    \    fast_output << answer << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/offline_rectangle_add_rectangle_sum.hpp
  - ds/range_query/fenwick_tree.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 21:06:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
- /verify/verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp.html
title: verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
---
