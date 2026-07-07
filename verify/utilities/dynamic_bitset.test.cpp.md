---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: utilities/dynamic_bitset.hpp
    title: Dynamic Bitset
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/utilities/dynamic_bitset.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <random>\n#include <vector>\n\n#line\
    \ 1 \"utilities/dynamic_bitset.hpp\"\n\n\n\n#line 6 \"utilities/dynamic_bitset.hpp\"\
    \n#include <cstddef>\n#include <cstdint>\n#line 9 \"utilities/dynamic_bitset.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\nstruct DynamicBitset {\n   private:\n\
    \    static constexpr int BITS_PER_BLOCK = 64;\n    static constexpr uint64_t\
    \ FULL_BLOCK = ~uint64_t{0};\n\n    int _n;\n    std::vector<uint64_t> blocks;\n\
    \n    static int block_count(int n) {\n        assert(n >= 0);\n        return\
    \ (n + BITS_PER_BLOCK - 1) >> 6;\n    }\n\n    uint64_t tail_mask() const {\n\
    \        const int rem = _n & (BITS_PER_BLOCK - 1);\n        return rem == 0 ?\
    \ FULL_BLOCK : ((uint64_t{1} << rem) - 1);\n    }\n\n    // Keep unused bits in\
    \ the last block equal to zero.\n    void clean() {\n        if (!blocks.empty())\
    \ blocks.back() &= tail_mask();\n    }\n\n   public:\n    DynamicBitset() : _n(0),\
    \ blocks() {}\n\n    explicit DynamicBitset(int n, bool val = false) : _n(n),\
    \ blocks(block_count(n), val ? FULL_BLOCK : 0) {\n        if (val) clean();\n\
    \    }\n\n    // Returns the logical number of bits.\n    int size() const {\n\
    \        return _n;\n    }\n\n    // Returns whether the bit at index i is set.\n\
    \    bool test(int i) const {\n        assert(0 <= i && i < _n);\n        return\
    \ (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) & 1;\n    }\n\n    // Sets the\
    \ bit at index i to true.\n    void set(int i) {\n        assert(0 <= i && i <\
    \ _n);\n        blocks[i >> 6] |= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));\n\
    \    }\n\n    // Sets all bits to true.\n    void set() {\n        std::fill(blocks.begin(),\
    \ blocks.end(), FULL_BLOCK);\n        clean();\n    }\n\n    // Sets the bit at\
    \ index i to false.\n    void reset(int i) {\n        assert(0 <= i && i < _n);\n\
    \        blocks[i >> 6] &= ~(uint64_t{1} << (i & (BITS_PER_BLOCK - 1)));\n   \
    \ }\n\n    // Sets all bits to false.\n    void reset() {\n        std::fill(blocks.begin(),\
    \ blocks.end(), uint64_t{0});\n    }\n\n    // Flips the bit at index i.\n   \
    \ void flip(int i) {\n        assert(0 <= i && i < _n);\n        blocks[i >> 6]\
    \ ^= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));\n    }\n\n    // Flips all bits.\n\
    \    void flip() {\n        for (uint64_t& block : blocks) block = ~block;\n \
    \       clean();\n    }\n\n    // Returns the number of set bits.\n    int popcount()\
    \ const {\n        int res = 0;\n        for (uint64_t block : blocks) res +=\
    \ __builtin_popcountll(block);\n        return res;\n    }\n\n    // Returns the\
    \ index of the least significant set bit, or -1 if no bit is set.\n    int lowbit()\
    \ const {\n        const int m = static_cast<int>(blocks.size());\n        for\
    \ (int i = 0; i < m; ++i) {\n            if (blocks[i] != 0) return (i << 6) +\
    \ __builtin_ctzll(blocks[i]);\n        }\n        return -1;\n    }\n\n    //\
    \ Returns the index of the most significant set bit, or -1 if no bit is set.\n\
    \    int topbit() const {\n        for (int i = static_cast<int>(blocks.size())\
    \ - 1; i >= 0; --i) {\n            if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK\
    \ - 1 - __builtin_clzll(blocks[i]));\n        }\n        return -1;\n    }\n\n\
    \    // Returns whether at least one bit is set.\n    bool any() const {\n   \
    \     for (uint64_t block : blocks) {\n            if (block != 0) return true;\n\
    \        }\n        return false;\n    }\n\n    // Returns whether every logical\
    \ bit is set.\n    bool all() const {\n        if (_n == 0) return true;\n\n \
    \       const int m = static_cast<int>(blocks.size());\n        for (int i = 0;\
    \ i + 1 < m; ++i) {\n            if (blocks[i] != FULL_BLOCK) return false;\n\
    \        }\n        return blocks.back() == tail_mask();\n    }\n\n    // Returns\
    \ whether no bit is set.\n    bool none() const {\n        return !any();\n  \
    \  }\n\n    DynamicBitset& operator&=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] &= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset& operator|=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] |= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset& operator^=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset operator~() const {\n        DynamicBitset res = *this;\n\
    \        res.flip();\n        return res;\n    }\n\n    friend DynamicBitset operator&(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        lhs &= rhs;\n        return lhs;\n\
    \    }\n\n    friend DynamicBitset operator|(DynamicBitset lhs, const DynamicBitset&\
    \ rhs) {\n        lhs |= rhs;\n        return lhs;\n    }\n\n    friend DynamicBitset\
    \ operator^(DynamicBitset lhs, const DynamicBitset& rhs) {\n        lhs ^= rhs;\n\
    \        return lhs;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 10 \"verify/utilities/dynamic_bitset.test.cpp\"\n\nusing m1une::utilities::DynamicBitset;\n\
    \nvoid verify_state(const DynamicBitset& bits, const std::vector<int>& model)\
    \ {\n    const int n = static_cast<int>(model.size());\n    assert(bits.size()\
    \ == n);\n\n    int count = 0;\n    int low = -1;\n    int top = -1;\n    for\
    \ (int i = 0; i < n; ++i) {\n        assert(bits.test(i) == static_cast<bool>(model[i]));\n\
    \        if (model[i]) {\n            ++count;\n            if (low == -1) low\
    \ = i;\n            top = i;\n        }\n    }\n\n    assert(bits.popcount() ==\
    \ count);\n    assert(bits.lowbit() == low);\n    assert(bits.topbit() == top);\n\
    \    assert(bits.any() == (count > 0));\n    assert(bits.none() == (count == 0));\n\
    \    assert(bits.all() == (count == n));\n}\n\nDynamicBitset make_bitset(const\
    \ std::vector<int>& model) {\n    DynamicBitset bits(static_cast<int>(model.size()));\n\
    \    for (int i = 0; i < static_cast<int>(model.size()); ++i) {\n        if (model[i])\
    \ bits.set(i);\n    }\n    return bits;\n}\n\nstd::vector<int> bitwise_and_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] & rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_or_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] | rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_xor_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] ^ rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_not_model(const\
    \ std::vector<int>& model) {\n    std::vector<int> res(model.size());\n    for\
    \ (int i = 0; i < static_cast<int>(model.size()); ++i) res[i] = model[i] ^ 1;\n\
    \    return res;\n}\n\nvoid test_constructors() {\n    const std::vector<int>\
    \ sizes = {0, 1, 2, 3, 31, 32, 33, 63, 64, 65, 66,\n                         \
    \           127, 128, 129, 130, 191, 192, 193, 257};\n\n    DynamicBitset empty;\n\
    \    verify_state(empty, std::vector<int>());\n\n    for (int n : sizes) {\n \
    \       DynamicBitset zero(n);\n        verify_state(zero, std::vector<int>(n,\
    \ 0));\n\n        DynamicBitset one(n, true);\n        verify_state(one, std::vector<int>(n,\
    \ 1));\n    }\n}\n\nvoid test_point_and_global_operations() {\n    const std::vector<int>\
    \ sizes = {0, 1, 5, 63, 64, 65, 129, 257};\n\n    for (int n : sizes) {\n    \
    \    DynamicBitset bits(n);\n        std::vector<int> model(n, 0);\n        verify_state(bits,\
    \ model);\n\n        bits.set();\n        std::fill(model.begin(), model.end(),\
    \ 1);\n        verify_state(bits, model);\n\n        bits.reset();\n        std::fill(model.begin(),\
    \ model.end(), 0);\n        verify_state(bits, model);\n\n        bits.flip();\n\
    \        for (int& x : model) x ^= 1;\n        verify_state(bits, model);\n\n\
    \        bits.flip();\n        for (int& x : model) x ^= 1;\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 3 == 0)\
    \ {\n                bits.set(i);\n                model[i] = 1;\n           \
    \ }\n        }\n        verify_state(bits, model);\n\n        for (int i = 0;\
    \ i < n; ++i) {\n            if (i % 5 == 0) {\n                bits.reset(i);\n\
    \                model[i] = 0;\n            }\n        }\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 7 == 0)\
    \ {\n                bits.flip(i);\n                model[i] ^= 1;\n         \
    \   }\n        }\n        verify_state(bits, model);\n    }\n}\n\nvoid test_bitwise_operations()\
    \ {\n    const std::vector<int> sizes = {0, 1, 2, 63, 64, 65, 100, 127, 128, 129,\
    \ 255};\n\n    for (int n : sizes) {\n        std::vector<int> lhs(n), rhs(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            lhs[i] = ((i * 37 + n) % 5)\
    \ < 2;\n            rhs[i] = ((i * 19 + n * 3) % 7) < 3;\n        }\n\n      \
    \  const DynamicBitset a = make_bitset(lhs);\n        const DynamicBitset b =\
    \ make_bitset(rhs);\n\n        verify_state(a & b, bitwise_and_model(lhs, rhs));\n\
    \        verify_state(a | b, bitwise_or_model(lhs, rhs));\n        verify_state(a\
    \ ^ b, bitwise_xor_model(lhs, rhs));\n        verify_state(~a, bitwise_not_model(lhs));\n\
    \n        DynamicBitset c = a;\n        c &= b;\n        verify_state(c, bitwise_and_model(lhs,\
    \ rhs));\n\n        c = a;\n        c |= b;\n        verify_state(c, bitwise_or_model(lhs,\
    \ rhs));\n\n        c = a;\n        c ^= b;\n        verify_state(c, bitwise_xor_model(lhs,\
    \ rhs));\n    }\n}\n\nvoid test_randomized() {\n    std::mt19937_64 rng(123456789);\n\
    \n    for (int trial = 0; trial < 200; ++trial) {\n        int n;\n        if\
    \ (trial < 130) {\n            n = trial;\n        } else {\n            n = static_cast<int>(rng()\
    \ % 600);\n        }\n\n        DynamicBitset bits(n, (rng() & 1) != 0);\n   \
    \     std::vector<int> model(n, bits.all() ? 1 : 0);\n        verify_state(bits,\
    \ model);\n\n        for (int step = 0; step < 400; ++step) {\n            const\
    \ int op = static_cast<int>(rng() % 10);\n            if (op == 0) {\n       \
    \         bits.set();\n                std::fill(model.begin(), model.end(), 1);\n\
    \            } else if (op == 1) {\n                bits.reset();\n          \
    \      std::fill(model.begin(), model.end(), 0);\n            } else if (op ==\
    \ 2) {\n                bits.flip();\n                for (int& x : model) x ^=\
    \ 1;\n            } else if (op <= 5) {\n                if (n == 0) continue;\n\
    \                const int i = static_cast<int>(rng() % n);\n                if\
    \ (op == 3) {\n                    bits.set(i);\n                    model[i]\
    \ = 1;\n                } else if (op == 4) {\n                    bits.reset(i);\n\
    \                    model[i] = 0;\n                } else {\n               \
    \     bits.flip(i);\n                    model[i] ^= 1;\n                }\n \
    \           } else {\n                std::vector<int> other_model(n);\n     \
    \           for (int i = 0; i < n; ++i) other_model[i] = (rng() % 3) == 0;\n \
    \               DynamicBitset other = make_bitset(other_model);\n\n          \
    \      if (op == 6) {\n                    bits &= other;\n                  \
    \  model = bitwise_and_model(model, other_model);\n                } else if (op\
    \ == 7) {\n                    bits |= other;\n                    model = bitwise_or_model(model,\
    \ other_model);\n                } else if (op == 8) {\n                    bits\
    \ ^= other;\n                    model = bitwise_xor_model(model, other_model);\n\
    \                } else {\n                    verify_state(bits & other, bitwise_and_model(model,\
    \ other_model));\n                    verify_state(bits | other, bitwise_or_model(model,\
    \ other_model));\n                    verify_state(bits ^ other, bitwise_xor_model(model,\
    \ other_model));\n                    verify_state(~bits, bitwise_not_model(model));\n\
    \                }\n            }\n            verify_state(bits, model);\n  \
    \      }\n    }\n}\n\nint main() {\n    test_constructors();\n    test_point_and_global_operations();\n\
    \    test_bitwise_operations();\n    test_randomized();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <vector>\n\
    \n#include \"../../utilities/dynamic_bitset.hpp\"\n\nusing m1une::utilities::DynamicBitset;\n\
    \nvoid verify_state(const DynamicBitset& bits, const std::vector<int>& model)\
    \ {\n    const int n = static_cast<int>(model.size());\n    assert(bits.size()\
    \ == n);\n\n    int count = 0;\n    int low = -1;\n    int top = -1;\n    for\
    \ (int i = 0; i < n; ++i) {\n        assert(bits.test(i) == static_cast<bool>(model[i]));\n\
    \        if (model[i]) {\n            ++count;\n            if (low == -1) low\
    \ = i;\n            top = i;\n        }\n    }\n\n    assert(bits.popcount() ==\
    \ count);\n    assert(bits.lowbit() == low);\n    assert(bits.topbit() == top);\n\
    \    assert(bits.any() == (count > 0));\n    assert(bits.none() == (count == 0));\n\
    \    assert(bits.all() == (count == n));\n}\n\nDynamicBitset make_bitset(const\
    \ std::vector<int>& model) {\n    DynamicBitset bits(static_cast<int>(model.size()));\n\
    \    for (int i = 0; i < static_cast<int>(model.size()); ++i) {\n        if (model[i])\
    \ bits.set(i);\n    }\n    return bits;\n}\n\nstd::vector<int> bitwise_and_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] & rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_or_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] | rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_xor_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] ^ rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_not_model(const\
    \ std::vector<int>& model) {\n    std::vector<int> res(model.size());\n    for\
    \ (int i = 0; i < static_cast<int>(model.size()); ++i) res[i] = model[i] ^ 1;\n\
    \    return res;\n}\n\nvoid test_constructors() {\n    const std::vector<int>\
    \ sizes = {0, 1, 2, 3, 31, 32, 33, 63, 64, 65, 66,\n                         \
    \           127, 128, 129, 130, 191, 192, 193, 257};\n\n    DynamicBitset empty;\n\
    \    verify_state(empty, std::vector<int>());\n\n    for (int n : sizes) {\n \
    \       DynamicBitset zero(n);\n        verify_state(zero, std::vector<int>(n,\
    \ 0));\n\n        DynamicBitset one(n, true);\n        verify_state(one, std::vector<int>(n,\
    \ 1));\n    }\n}\n\nvoid test_point_and_global_operations() {\n    const std::vector<int>\
    \ sizes = {0, 1, 5, 63, 64, 65, 129, 257};\n\n    for (int n : sizes) {\n    \
    \    DynamicBitset bits(n);\n        std::vector<int> model(n, 0);\n        verify_state(bits,\
    \ model);\n\n        bits.set();\n        std::fill(model.begin(), model.end(),\
    \ 1);\n        verify_state(bits, model);\n\n        bits.reset();\n        std::fill(model.begin(),\
    \ model.end(), 0);\n        verify_state(bits, model);\n\n        bits.flip();\n\
    \        for (int& x : model) x ^= 1;\n        verify_state(bits, model);\n\n\
    \        bits.flip();\n        for (int& x : model) x ^= 1;\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 3 == 0)\
    \ {\n                bits.set(i);\n                model[i] = 1;\n           \
    \ }\n        }\n        verify_state(bits, model);\n\n        for (int i = 0;\
    \ i < n; ++i) {\n            if (i % 5 == 0) {\n                bits.reset(i);\n\
    \                model[i] = 0;\n            }\n        }\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 7 == 0)\
    \ {\n                bits.flip(i);\n                model[i] ^= 1;\n         \
    \   }\n        }\n        verify_state(bits, model);\n    }\n}\n\nvoid test_bitwise_operations()\
    \ {\n    const std::vector<int> sizes = {0, 1, 2, 63, 64, 65, 100, 127, 128, 129,\
    \ 255};\n\n    for (int n : sizes) {\n        std::vector<int> lhs(n), rhs(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            lhs[i] = ((i * 37 + n) % 5)\
    \ < 2;\n            rhs[i] = ((i * 19 + n * 3) % 7) < 3;\n        }\n\n      \
    \  const DynamicBitset a = make_bitset(lhs);\n        const DynamicBitset b =\
    \ make_bitset(rhs);\n\n        verify_state(a & b, bitwise_and_model(lhs, rhs));\n\
    \        verify_state(a | b, bitwise_or_model(lhs, rhs));\n        verify_state(a\
    \ ^ b, bitwise_xor_model(lhs, rhs));\n        verify_state(~a, bitwise_not_model(lhs));\n\
    \n        DynamicBitset c = a;\n        c &= b;\n        verify_state(c, bitwise_and_model(lhs,\
    \ rhs));\n\n        c = a;\n        c |= b;\n        verify_state(c, bitwise_or_model(lhs,\
    \ rhs));\n\n        c = a;\n        c ^= b;\n        verify_state(c, bitwise_xor_model(lhs,\
    \ rhs));\n    }\n}\n\nvoid test_randomized() {\n    std::mt19937_64 rng(123456789);\n\
    \n    for (int trial = 0; trial < 200; ++trial) {\n        int n;\n        if\
    \ (trial < 130) {\n            n = trial;\n        } else {\n            n = static_cast<int>(rng()\
    \ % 600);\n        }\n\n        DynamicBitset bits(n, (rng() & 1) != 0);\n   \
    \     std::vector<int> model(n, bits.all() ? 1 : 0);\n        verify_state(bits,\
    \ model);\n\n        for (int step = 0; step < 400; ++step) {\n            const\
    \ int op = static_cast<int>(rng() % 10);\n            if (op == 0) {\n       \
    \         bits.set();\n                std::fill(model.begin(), model.end(), 1);\n\
    \            } else if (op == 1) {\n                bits.reset();\n          \
    \      std::fill(model.begin(), model.end(), 0);\n            } else if (op ==\
    \ 2) {\n                bits.flip();\n                for (int& x : model) x ^=\
    \ 1;\n            } else if (op <= 5) {\n                if (n == 0) continue;\n\
    \                const int i = static_cast<int>(rng() % n);\n                if\
    \ (op == 3) {\n                    bits.set(i);\n                    model[i]\
    \ = 1;\n                } else if (op == 4) {\n                    bits.reset(i);\n\
    \                    model[i] = 0;\n                } else {\n               \
    \     bits.flip(i);\n                    model[i] ^= 1;\n                }\n \
    \           } else {\n                std::vector<int> other_model(n);\n     \
    \           for (int i = 0; i < n; ++i) other_model[i] = (rng() % 3) == 0;\n \
    \               DynamicBitset other = make_bitset(other_model);\n\n          \
    \      if (op == 6) {\n                    bits &= other;\n                  \
    \  model = bitwise_and_model(model, other_model);\n                } else if (op\
    \ == 7) {\n                    bits |= other;\n                    model = bitwise_or_model(model,\
    \ other_model);\n                } else if (op == 8) {\n                    bits\
    \ ^= other;\n                    model = bitwise_xor_model(model, other_model);\n\
    \                } else {\n                    verify_state(bits & other, bitwise_and_model(model,\
    \ other_model));\n                    verify_state(bits | other, bitwise_or_model(model,\
    \ other_model));\n                    verify_state(bits ^ other, bitwise_xor_model(model,\
    \ other_model));\n                    verify_state(~bits, bitwise_not_model(model));\n\
    \                }\n            }\n            verify_state(bits, model);\n  \
    \      }\n    }\n}\n\nint main() {\n    test_constructors();\n    test_point_and_global_operations();\n\
    \    test_bitwise_operations();\n    test_randomized();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/dynamic_bitset.hpp
  isVerificationFile: true
  path: verify/utilities/dynamic_bitset.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 14:34:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/utilities/dynamic_bitset.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/dynamic_bitset.test.cpp
- /verify/verify/utilities/dynamic_bitset.test.cpp.html
title: verify/utilities/dynamic_bitset.test.cpp
---
