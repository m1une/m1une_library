---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: ds/dsu/range_parallel_dsu.hpp
    title: Range-Parallel DSU
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_parallel_unionfind
    links:
    - https://judge.yosupo.jp/problem/range_parallel_unionfind
  bundledCode: "#line 1 \"verify/ds/dsu/range_parallel_dsu.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_parallel_unionfind\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\n#line 1 \"ds/dsu/dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <numeric>\n#include <utility>\n#line 8\
    \ \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n  \
    \ private:\n    int _n;\n    // parent_or_size[i] is the parent of i if it's >=\
    \ 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is the size\
    \ of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns {new leader,\
    \ absorbed leader}. The absorbed leader is -1 when\n    // both vertices already\
    \ belong to the same component.\n    std::pair<int, int> merge_leaders(int a,\
    \ int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y) return\
    \ {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"ds/dsu/range_parallel_dsu.hpp\"\n\n\n\n#include\
    \ <bit>\n#line 6 \"ds/dsu/range_parallel_dsu.hpp\"\n#include <cstddef>\n#line\
    \ 9 \"ds/dsu/range_parallel_dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Merges corresponding vertices of two equal-length ranges.\nclass RangeParallelDsu\
    \ {\n   private:\n    struct LevelDsu {\n        std::vector<int> parent_or_size;\n\
    \        int component_count;\n\n        explicit LevelDsu(int size = 0)\n   \
    \         : parent_or_size(std::size_t(size), -1), component_count(size) {}\n\n\
    \        int leader(int vertex) {\n            if (parent_or_size[vertex] < 0)\
    \ return vertex;\n            return parent_or_size[vertex] = leader(parent_or_size[vertex]);\n\
    \        }\n\n        int leader(int vertex) const {\n            while (parent_or_size[vertex]\
    \ >= 0) {\n                vertex = parent_or_size[vertex];\n            }\n \
    \           return vertex;\n        }\n\n        std::pair<int, int> merge(int\
    \ first, int second) {\n            first = leader(first);\n            second\
    \ = leader(second);\n            if (first == second) return {first, -1};\n  \
    \          if (-parent_or_size[first] < -parent_or_size[second]) {\n         \
    \       std::swap(first, second);\n            }\n            parent_or_size[first]\
    \ += parent_or_size[second];\n            parent_or_size[second] = first;\n  \
    \          component_count--;\n            return {first, second};\n        }\n\
    \    };\n\n    int _size;\n    std::vector<LevelDsu> _levels;\n\n    static int\
    \ check_size(int size) {\n        assert(size >= 0);\n        return size;\n \
    \   }\n\n    void check_vertex(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < _size);\n    }\n\n    void check_range(int first, int length) const\
    \ {\n        assert(0 <= first && 0 <= length);\n        assert(length <= _size);\n\
    \        assert(first <= _size - length);\n    }\n\n    template <class Callback>\n\
    \    int merge_block(int level, int first, int second, Callback& callback) {\n\
    \        std::pair<int, int> merged = _levels[level].merge(first, second);\n \
    \       if (merged.second == -1) return 0;\n        if (level == 0) {\n      \
    \      callback(merged.first, merged.second);\n            return 1;\n       \
    \ }\n\n        const int half = 1 << (level - 1);\n        int result = merge_block(level\
    \ - 1, first, second, callback);\n        result += merge_block(level - 1, first\
    \ + half, second + half, callback);\n        return result;\n    }\n\n   public:\n\
    \    RangeParallelDsu() : RangeParallelDsu(0) {}\n\n    explicit RangeParallelDsu(int\
    \ size) : _size(check_size(size)) {\n        _levels.emplace_back(_size);\n  \
    \      for (int block_size = 2; block_size < _size; block_size *= 2) {\n     \
    \       _levels.emplace_back(_size - block_size + 1);\n            if (block_size\
    \ > _size / 2) break;\n        }\n    }\n\n    int size() const {\n        return\
    \ _size;\n    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\
    \n    int component_count() const {\n        return _levels[0].component_count;\n\
    \    }\n\n    int leader(int vertex) {\n        check_vertex(vertex);\n      \
    \  return _levels[0].leader(vertex);\n    }\n\n    int leader(int vertex) const\
    \ {\n        check_vertex(vertex);\n        return _levels[0].leader(vertex);\n\
    \    }\n\n    bool same(int first, int second) {\n        return leader(first)\
    \ == leader(second);\n    }\n\n    bool same(int first, int second) const {\n\
    \        return leader(first) == leader(second);\n    }\n\n    int group_size(int\
    \ vertex) {\n        return -_levels[0].parent_or_size[leader(vertex)];\n    }\n\
    \n    int group_size(int vertex) const {\n        return -_levels[0].parent_or_size[leader(vertex)];\n\
    \    }\n\n    template <class Callback>\n    int merge(int first, int second,\
    \ int length, Callback&& callback) {\n        check_range(first, length);\n  \
    \      check_range(second, length);\n        if (length == 0) return 0;\n    \
    \    if (length == 1) {\n            return merge_block(0, first, second, callback);\n\
    \        }\n\n        const int level = int(std::bit_width(unsigned(length - 1)))\
    \ - 1;\n        const int block_size = 1 << level;\n        int result = merge_block(level,\
    \ first, second, callback);\n        result += merge_block(level, first + length\
    \ - block_size,\n                              second + length - block_size, callback);\n\
    \        return result;\n    }\n\n    int merge(int first, int second, int length)\
    \ {\n        auto ignore = [](int, int) {};\n        return merge(first, second,\
    \ length, ignore);\n    }\n\n    template <class Callback>\n    int merge_ranges(int\
    \ first_left, int first_right, int second_left,\n                     int second_right,\
    \ Callback&& callback) {\n        assert(first_right - first_left == second_right\
    \ - second_left);\n        return merge(first_left, second_left, first_right -\
    \ first_left,\n                     std::forward<Callback>(callback));\n    }\n\
    \n    int merge_ranges(int first_left, int first_right, int second_left,\n   \
    \                  int second_right) {\n        auto ignore = [](int, int) {};\n\
    \        return merge_ranges(first_left, first_right, second_left, second_right,\n\
    \                            ignore);\n    }\n\n    template <class Callback>\n\
    \    int merge(int first, int second, Callback&& callback) {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return merge_block(0, first, second, callback);\n\
    \    }\n\n    int merge(int first, int second) {\n        auto ignore = [](int,\
    \ int) {};\n        return merge(first, second, ignore);\n    }\n};\n\nusing RangeParallelUnionFind\
    \ = RangeParallelDsu;\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/modint.hpp\"\n\n\n\n#line 7 \"math/modint.hpp\"\n#include <type_traits>\n\
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
    \n\n#line 11 \"verify/ds/dsu/range_parallel_dsu.test.cpp\"\n\nnamespace {\n\n\
    void test_randomized() {\n    uint64_t state = 0xa0761d6478bd642fULL;\n    auto\
    \ random = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 200; trial++)\
    \ {\n        const int size = int(random() % 60) + 1;\n        m1une::ds::RangeParallelDsu\
    \ range_dsu(size);\n        m1une::ds::Dsu naive(size);\n        assert(range_dsu.size()\
    \ == size);\n        assert(!range_dsu.empty());\n\n        for (int query = 0;\
    \ query < 500; query++) {\n            const int length = int(random() % (size\
    \ + 1));\n            const int first = int(random() % (size - length + 1));\n\
    \            const int second = int(random() % (size - length + 1));\n\n     \
    \       int expected_merges = 0;\n            for (int offset = 0; offset < length;\
    \ offset++) {\n                if (!naive.same(first + offset, second + offset))\
    \ {\n                    naive.merge(first + offset, second + offset);\n     \
    \               expected_merges++;\n                }\n            }\n\n     \
    \       int callback_count = 0;\n            const int merges = range_dsu.merge(\n\
    \                first, second, length,\n                [&](int leader, int absorbed)\
    \ {\n                    assert(range_dsu.leader(leader) == leader);\n       \
    \             assert(range_dsu.leader(absorbed) == leader);\n                \
    \    callback_count++;\n                });\n            assert(merges == expected_merges);\n\
    \            assert(callback_count == expected_merges);\n\n            for (int\
    \ first_vertex = 0; first_vertex < size; first_vertex++) {\n                assert(range_dsu.group_size(first_vertex)\
    \ ==\n                       naive.size(first_vertex));\n                for (int\
    \ second_vertex = 0; second_vertex < size;\n                     second_vertex++)\
    \ {\n                    assert(range_dsu.same(first_vertex, second_vertex) ==\n\
    \                           naive.same(first_vertex, second_vertex));\n      \
    \          }\n            }\n        }\n        assert(range_dsu.component_count()\
    \ == int(naive.groups().size()));\n    }\n}\n\nvoid test_overloads() {\n    m1une::ds::RangeParallelUnionFind\
    \ dsu(8);\n    assert(dsu.merge_ranges(0, 4, 4, 8) == 4);\n    assert(dsu.same(0,\
    \ 4));\n    assert(dsu.same(3, 7));\n    assert(dsu.merge(0, 1) == 1);\n    assert(dsu.group_size(0)\
    \ == 4);\n    assert(dsu.merge(0, 4, 4) == 0);\n\n    m1une::ds::RangeParallelDsu\
    \ empty;\n    assert(empty.empty());\n    assert(empty.component_count() == 0);\n\
    \    assert(empty.merge(0, 0, 0) == 0);\n}\n\n}  // namespace\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    test_randomized();\n\
    \    test_overloads();\n\n    using Mint = m1une::math::modint998244353;\n   \
    \ int size, query_count;\n    std::cin >> size >> query_count;\n    std::vector<Mint>\
    \ component_sum(size);\n    for (Mint& value : component_sum) std::cin >> value;\n\
    \n    m1une::ds::RangeParallelDsu dsu(size);\n    Mint answer = 0;\n    auto on_merge\
    \ = [&](int leader, int absorbed) {\n        answer += component_sum[leader] *\
    \ component_sum[absorbed];\n        component_sum[leader] += component_sum[absorbed];\n\
    \    };\n\n    while (query_count--) {\n        int length, first, second;\n \
    \       std::cin >> length >> first >> second;\n        dsu.merge(first, second,\
    \ length, on_merge);\n        std::cout << answer << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_parallel_unionfind\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \n#include \"../../../ds/dsu/dsu.hpp\"\n#include \"../../../ds/dsu/range_parallel_dsu.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    uint64_t state = 0xa0761d6478bd642fULL;\n    auto random = [&]() {\n\
    \        state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 200; trial++) {\n        const int\
    \ size = int(random() % 60) + 1;\n        m1une::ds::RangeParallelDsu range_dsu(size);\n\
    \        m1une::ds::Dsu naive(size);\n        assert(range_dsu.size() == size);\n\
    \        assert(!range_dsu.empty());\n\n        for (int query = 0; query < 500;\
    \ query++) {\n            const int length = int(random() % (size + 1));\n   \
    \         const int first = int(random() % (size - length + 1));\n           \
    \ const int second = int(random() % (size - length + 1));\n\n            int expected_merges\
    \ = 0;\n            for (int offset = 0; offset < length; offset++) {\n      \
    \          if (!naive.same(first + offset, second + offset)) {\n             \
    \       naive.merge(first + offset, second + offset);\n                    expected_merges++;\n\
    \                }\n            }\n\n            int callback_count = 0;\n   \
    \         const int merges = range_dsu.merge(\n                first, second,\
    \ length,\n                [&](int leader, int absorbed) {\n                 \
    \   assert(range_dsu.leader(leader) == leader);\n                    assert(range_dsu.leader(absorbed)\
    \ == leader);\n                    callback_count++;\n                });\n  \
    \          assert(merges == expected_merges);\n            assert(callback_count\
    \ == expected_merges);\n\n            for (int first_vertex = 0; first_vertex\
    \ < size; first_vertex++) {\n                assert(range_dsu.group_size(first_vertex)\
    \ ==\n                       naive.size(first_vertex));\n                for (int\
    \ second_vertex = 0; second_vertex < size;\n                     second_vertex++)\
    \ {\n                    assert(range_dsu.same(first_vertex, second_vertex) ==\n\
    \                           naive.same(first_vertex, second_vertex));\n      \
    \          }\n            }\n        }\n        assert(range_dsu.component_count()\
    \ == int(naive.groups().size()));\n    }\n}\n\nvoid test_overloads() {\n    m1une::ds::RangeParallelUnionFind\
    \ dsu(8);\n    assert(dsu.merge_ranges(0, 4, 4, 8) == 4);\n    assert(dsu.same(0,\
    \ 4));\n    assert(dsu.same(3, 7));\n    assert(dsu.merge(0, 1) == 1);\n    assert(dsu.group_size(0)\
    \ == 4);\n    assert(dsu.merge(0, 4, 4) == 0);\n\n    m1une::ds::RangeParallelDsu\
    \ empty;\n    assert(empty.empty());\n    assert(empty.component_count() == 0);\n\
    \    assert(empty.merge(0, 0, 0) == 0);\n}\n\n}  // namespace\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    test_randomized();\n\
    \    test_overloads();\n\n    using Mint = m1une::math::modint998244353;\n   \
    \ int size, query_count;\n    std::cin >> size >> query_count;\n    std::vector<Mint>\
    \ component_sum(size);\n    for (Mint& value : component_sum) std::cin >> value;\n\
    \n    m1une::ds::RangeParallelDsu dsu(size);\n    Mint answer = 0;\n    auto on_merge\
    \ = [&](int leader, int absorbed) {\n        answer += component_sum[leader] *\
    \ component_sum[absorbed];\n        component_sum[leader] += component_sum[absorbed];\n\
    \    };\n\n    while (query_count--) {\n        int length, first, second;\n \
    \       std::cin >> length >> first >> second;\n        dsu.merge(first, second,\
    \ length, on_merge);\n        std::cout << answer << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/dsu/dsu.hpp
  - ds/dsu/range_parallel_dsu.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/dsu/range_parallel_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/range_parallel_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/range_parallel_dsu.test.cpp
- /verify/verify/ds/dsu/range_parallel_dsu.test.cpp.html
title: verify/ds/dsu/range_parallel_dsu.test.cpp
---
