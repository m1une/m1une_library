---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: algo/dp/all.hpp
    title: DP Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/dp/knapsack.hpp
    title: Knapsack Helpers
  - icon: ':warning:'
    path: algo/enumeration/all.hpp
    title: Enumeration Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/combination.hpp
    title: Combination Masks
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/gray_code.hpp
    title: Gray Code
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/submask.hpp
    title: Submask Enumeration
  - icon: ':warning:'
    path: algo/offline/all.hpp
    title: Offline Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/offline/cdq_divide_and_conquer.hpp
    title: CDQ Divide And Conquer
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: algo/offline/parallel_binary_search.hpp
    title: Parallel Binary Search
  - icon: ':warning:'
    path: algo/search/all.hpp
    title: Search Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/search/bisect.hpp
    title: Bisect
  - icon: ':heavy_check_mark:'
    path: algo/search/golden_section_search.hpp
    title: Golden Section Search
  - icon: ':heavy_check_mark:'
    path: algo/search/ternary_search.hpp
    title: Ternary Search
  - icon: ':warning:'
    path: algo/sequence/all.hpp
    title: Sequence Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/sequence/inversion_count.hpp
    title: Inversion Count
  - icon: ':heavy_check_mark:'
    path: algo/sequence/lis.hpp
    title: Longest Increasing Subsequence (LIS)
  - icon: ':heavy_check_mark:'
    path: algo/sequence/run_length_encoding.hpp
    title: Run Length Encoding
  - icon: ':heavy_check_mark:'
    path: algo/sequence/subset_sum.hpp
    title: Meet-in-the-Middle Subset Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/all.hpp\"\n\n\n\n#line 1 \"algo/dp/all.hpp\"\n\n\n\n\
    #line 1 \"algo/dp/knapsack.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstddef>\n#include <deque>\n#include <limits>\n#include <vector>\n\n\
    namespace m1une {\nnamespace algo {\n\ninline std::vector<char> subset_sum_reachable(const\
    \ std::vector<int>& weights, int limit) {\n    assert(0 <= limit);\n    using\
    \ Word = unsigned long long;\n    constexpr int word_bits = std::numeric_limits<Word>::digits;\n\
    \n    const std::size_t bit_count = std::size_t(limit) + 1;\n    std::vector<Word>\
    \ bits((bit_count + word_bits - 1) / word_bits, Word(0));\n    bits[0] = Word(1);\n\
    \n    auto trim = [&]() {\n        const int extra = int(bit_count % word_bits);\n\
    \        if (extra != 0) {\n            bits.back() &= (Word(1) << extra) - Word(1);\n\
    \        }\n    };\n\n    for (int weight : weights) {\n        assert(0 <= weight);\n\
    \        if (weight == 0 || limit < weight) continue;\n\n        const std::size_t\
    \ word_shift = std::size_t(weight / word_bits);\n        const int bit_shift =\
    \ weight % word_bits;\n        for (std::size_t i = bits.size() - word_shift;\
    \ i-- > 0;) {\n            const Word source = bits[i];\n            if (source\
    \ == Word(0)) continue;\n            const std::size_t target = i + word_shift;\n\
    \            bits[target] |= source << bit_shift;\n            if (bit_shift !=\
    \ 0 && target + 1 < bits.size()) {\n                bits[target + 1] |= source\
    \ >> (word_bits - bit_shift);\n            }\n        }\n        trim();\n   \
    \ }\n\n    std::vector<char> reachable(std::size_t(limit) + 1, 0);\n    for (int\
    \ sum = 0; sum <= limit; ++sum) {\n        reachable[sum] = char((bits[std::size_t(sum\
    \ / word_bits)] >> (sum % word_bits)) & Word(1));\n    }\n    return reachable;\n\
    }\n\ntemplate <typename Value = long long>\nstd::vector<Value> zero_one_knapsack_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<Value>& values,\n\
    \    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest() /\
    \ Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(0 <=\
    \ capacity);\n\n    std::vector<Value> dp(std::size_t(capacity) + 1, neg_inf);\n\
    \    dp[0] = Value{};\n    for (std::size_t item = 0; item < weights.size(); ++item)\
    \ {\n        const int weight = weights[item];\n        assert(0 <= weight);\n\
    \        for (int current = capacity; weight <= current; --current) {\n      \
    \      if (dp[current - weight] == neg_inf) continue;\n            dp[current]\
    \ = std::max(dp[current], dp[current - weight] + values[item]);\n        }\n \
    \   }\n\n    for (int current = 1; current <= capacity; ++current) {\n       \
    \ dp[current] = std::max(dp[current], dp[current - 1]);\n    }\n    return dp;\n\
    }\n\ntemplate <typename Value = long long>\nstd::vector<Value> bounded_knapsack_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<Value>& values,\n\
    \    const std::vector<int>& counts,\n    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest()\
    \ / Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(weights.size()\
    \ == counts.size());\n    assert(0 <= capacity);\n\n    std::vector<Value> dp(std::size_t(capacity)\
    \ + 1, neg_inf);\n    dp[0] = Value{};\n\n    for (std::size_t item = 0; item\
    \ < weights.size(); ++item) {\n        const int weight = weights[item];\n   \
    \     const Value value = values[item];\n        const int count = counts[item];\n\
    \        assert(0 <= weight);\n        assert(0 <= count);\n        if (count\
    \ == 0) continue;\n\n        if (weight == 0) {\n            if (Value{} < value)\
    \ {\n                const Value gain = value * Value(count);\n              \
    \  for (Value& current : dp) {\n                    if (current != neg_inf) current\
    \ += gain;\n                }\n            }\n            continue;\n        }\n\
    \n        std::vector<Value> next = dp;\n        for (int residue = 0; residue\
    \ < weight && residue <= capacity; ++residue) {\n            std::deque<int> indices;\n\
    \            std::deque<Value> bases;\n            int k = 0;\n            for\
    \ (int current = residue; current <= capacity; current += weight, ++k) {\n   \
    \             if (dp[current] != neg_inf) {\n                    const Value base\
    \ = dp[current] - Value(k) * value;\n                    while (!bases.empty()\
    \ && bases.back() <= base) {\n                        bases.pop_back();\n    \
    \                    indices.pop_back();\n                    }\n            \
    \        bases.push_back(base);\n                    indices.push_back(k);\n \
    \               }\n\n                while (!indices.empty() && indices.front()\
    \ < k - count) {\n                    indices.pop_front();\n                 \
    \   bases.pop_front();\n                }\n                if (!bases.empty())\
    \ {\n                    next[current] = std::max(next[current], bases.front()\
    \ + Value(k) * value);\n                }\n            }\n        }\n        dp.swap(next);\n\
    \    }\n\n    for (int current = 1; current <= capacity; ++current) {\n      \
    \  dp[current] = std::max(dp[current], dp[current - 1]);\n    }\n    return dp;\n\
    }\n\ntemplate <typename Weight = long long>\nstd::vector<Weight> zero_one_knapsack_min_weight_for_value(\n\
    \    const std::vector<Weight>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit,\n    Weight inf = std::numeric_limits<Weight>::max() / Weight(4)\n\
    ) {\n    assert(weights.size() == values.size());\n    assert(0 <= value_limit);\n\
    \n    std::vector<Weight> dp(std::size_t(value_limit) + 1, inf);\n    dp[0] =\
    \ Weight{};\n    for (std::size_t item = 0; item < weights.size(); ++item) {\n\
    \        assert(Weight{} <= weights[item]);\n        assert(0 <= values[item]);\n\
    \        for (int value = value_limit; values[item] <= value; --value) {\n   \
    \         if (dp[value - values[item]] == inf) continue;\n            dp[value]\
    \ = std::min(dp[value], dp[value - values[item]] + weights[item]);\n        }\n\
    \    }\n    return dp;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n\
    #line 5 \"algo/dp/all.hpp\"\n\n\n#line 1 \"algo/enumeration/all.hpp\"\n\n\n\n\
    #line 1 \"algo/enumeration/combination.hpp\"\n\n\n\n#line 5 \"algo/enumeration/combination.hpp\"\
    \n#include <concepts>\n#include <cstdint>\n#line 8 \"algo/enumeration/combination.hpp\"\
    \n#include <type_traits>\n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal\
    \ {\n\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nUInt combination_low_bits(int bit_count) {\n    constexpr int digits\
    \ = std::numeric_limits<UInt>::digits;\n    assert(0 <= bit_count && bit_count\
    \ <= digits);\n    if (bit_count == digits) return ~UInt(0);\n    return (UInt(1)\
    \ << bit_count) - UInt(1);\n}\n\n}  // namespace internal\n\ntemplate <std::unsigned_integral\
    \ UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    UInt first_combination_mask(int bit_count, int choose) {\n    constexpr int digits\
    \ = std::numeric_limits<UInt>::digits;\n    assert(0 <= choose && choose <= bit_count\
    \ && bit_count <= digits);\n    if (choose == 0) return UInt(0);\n    if (choose\
    \ == bit_count) return internal::combination_low_bits<UInt>(bit_count);\n    return\
    \ (UInt(1) << choose) - UInt(1);\n}\n\ntemplate <std::unsigned_integral UInt>\n\
    requires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nbool next_combination_mask(UInt&\
    \ mask, int bit_count) {\n    const UInt universe = internal::combination_low_bits<UInt>(bit_count);\n\
    \    assert((mask & ~universe) == 0);\n    if (mask == 0) return false;\n\n  \
    \  const UInt lowest = mask & (~mask + UInt(1));\n    const UInt ripple = mask\
    \ + lowest;\n    if (ripple == 0 || (ripple & ~universe) != 0) return false;\n\
    \n    const UInt next = (((ripple ^ mask) >> 2) / lowest) | ripple;\n    if ((next\
    \ & ~universe) != 0) return false;\n    mask = next;\n    return true;\n}\n\n\
    template <std::unsigned_integral UInt = std::uint64_t, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_combination_mask(int bit_count, int choose, F f) {\n \
    \   constexpr int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <=\
    \ choose && choose <= bit_count && bit_count <= digits);\n    UInt mask = first_combination_mask<UInt>(bit_count,\
    \ choose);\n    while (true) {\n        f(mask);\n        if (!next_combination_mask(mask,\
    \ bit_count)) break;\n    }\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 1 \"algo/enumeration/gray_code.hpp\"\n\n\n\n#line 11 \"algo/enumeration/gray_code.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\n// Converts a binary value to its binary-reflected\
    \ Gray code.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nconstexpr UInt gray_encode(UInt value) noexcept {\n    return value\
    \ ^ (value >> 1);\n}\n\n// Converts a binary-reflected Gray code to the corresponding\
    \ binary value.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nconstexpr UInt gray_decode(UInt code) noexcept {\n    for (int shift\
    \ = 1; shift < std::numeric_limits<UInt>::digits;\n         shift <<= 1) {\n \
    \       code ^= code >> shift;\n    }\n    return code;\n}\n\n// Returns all bit_count-bit\
    \ binary-reflected Gray codes in traversal order.\ntemplate <std::unsigned_integral\
    \ UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    std::vector<UInt> gray_code_sequence(int bit_count) {\n    constexpr int uint_digits\
    \ = std::numeric_limits<UInt>::digits;\n    constexpr int size_digits = std::numeric_limits<std::size_t>::digits;\n\
    \    assert(0 <= bit_count);\n    assert(bit_count <= uint_digits);\n    assert(bit_count\
    \ < size_digits);\n    if (bit_count < 0 || uint_digits < bit_count || size_digits\
    \ <= bit_count) {\n        return {};\n    }\n\n    const std::size_t size = std::size_t(1)\
    \ << bit_count;\n    std::vector<UInt> result(size);\n    for (std::size_t index\
    \ = 0; index < size; ++index) {\n        result[index] = gray_encode(static_cast<UInt>(index));\n\
    \    }\n    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 1 \"algo/enumeration/submask.hpp\"\n\n\n\n#line 8 \"algo/enumeration/submask.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nUInt submask_low_bits(int\
    \ bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_submask(UInt mask, F f) {\n    UInt submask = mask;\n\
    \    while (true) {\n        f(submask);\n        if (submask == 0) break;\n \
    \       submask = (submask - 1) & mask;\n    }\n}\n\ntemplate <std::unsigned_integral\
    \ UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nvoid\
    \ for_each_nonzero_submask(UInt mask, F f) {\n    for (UInt submask = mask; submask\
    \ != 0; submask = (submask - 1) & mask) {\n        f(submask);\n    }\n}\n\ntemplate\
    \ <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_supermask(UInt mask, int bit_count, F f) {\n    const\
    \ UInt universe = internal::submask_low_bits<UInt>(bit_count);\n    assert((mask\
    \ & ~universe) == 0);\n    const UInt free_bits = universe ^ mask;\n    for_each_submask(free_bits,\
    \ [&](UInt added_bits) {\n        f(mask | added_bits);\n    });\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 7 \"algo/enumeration/all.hpp\"\n\n\n\
    #line 1 \"algo/offline/all.hpp\"\n\n\n\n#line 1 \"algo/offline/cdq_divide_and_conquer.hpp\"\
    \n\n\n\n#line 5 \"algo/offline/cdq_divide_and_conquer.hpp\"\n\nnamespace m1une\
    \ {\nnamespace algo {\n\ntemplate <class SolveCross>\nvoid cdq_divide_and_conquer(int\
    \ left, int right, SolveCross solve_cross) {\n    assert(left <= right);\n\n \
    \   auto dfs = [&](auto& self, int l, int r) -> void {\n        if (r - l <= 1)\
    \ return;\n        const int middle = l + (r - l) / 2;\n        self(self, l,\
    \ middle);\n        self(self, middle, r);\n        solve_cross(l, middle, r);\n\
    \    };\n    dfs(dfs, left, right);\n}\n\ntemplate <class SolveCross>\nvoid cdq_divide_and_conquer(int\
    \ n, SolveCross solve_cross) {\n    assert(0 <= n);\n    cdq_divide_and_conquer(0,\
    \ n, solve_cross);\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 1 \"algo/offline/mo.hpp\"\n\n\n\n#line 6 \"algo/offline/mo.hpp\"\n#include <cmath>\n\
    #include <numeric>\n#line 9 \"algo/offline/mo.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\n// Offline Mo's algorithm for half-open array ranges.\nstruct Mo {\n\
    \    struct Query {\n        int left;\n        int right;\n        int id;\n\
    \    };\n\n   private:\n    int _n;\n    std::vector<Query> _queries;\n\n   public:\n\
    \    Mo() : _n(0) {}\n\n    explicit Mo(int n) : _n(n) {\n        assert(0 <=\
    \ n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    int query_count()\
    \ const {\n        return int(_queries.size());\n    }\n\n    bool empty() const\
    \ {\n        return _queries.empty();\n    }\n\n    const std::vector<Query>&\
    \ queries() const {\n        return _queries;\n    }\n\n    void reserve(int query_capacity)\
    \ {\n        assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \    }\n\n    void clear() {\n        _queries.clear();\n    }\n\n    // Adds\
    \ [left, right) and returns its insertion-order ID.\n    int add_query(int left,\
    \ int right) {\n        assert(0 <= left && left <= right && right <= _n);\n \
    \       int id = query_count();\n        _queries.push_back(Query{left, right,\
    \ id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order. A\
    \ non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/offline/parallel_binary_search.hpp\"\
    \n\n\n\n#line 6 \"algo/offline/parallel_binary_search.hpp\"\n\nnamespace m1une\
    \ {\nnamespace algo {\n\ntemplate <class Apply, class Check, class Reset>\nstd::vector<int>\
    \ parallel_binary_search(\n    int query_count,\n    int event_count,\n    Apply\
    \ apply,\n    Check check,\n    Reset reset\n) {\n    assert(0 <= query_count);\n\
    \    assert(0 <= event_count);\n\n    std::vector<int> low(query_count, -1);\n\
    \    std::vector<int> high(query_count, event_count + 1);\n    std::vector<std::vector<int>>\
    \ bucket(event_count + 1);\n\n    while (true) {\n        bool active = false;\n\
    \        for (auto& queries : bucket) queries.clear();\n\n        for (int query\
    \ = 0; query < query_count; ++query) {\n            if (high[query] - low[query]\
    \ <= 1) continue;\n            const int middle = low[query] + (high[query] -\
    \ low[query]) / 2;\n            bucket[middle].push_back(query);\n           \
    \ active = true;\n        }\n        if (!active) break;\n\n        reset();\n\
    \        int applied = 0;\n        for (int middle = 0; middle <= event_count;\
    \ ++middle) {\n            while (applied < middle) {\n                apply(applied);\n\
    \                ++applied;\n            }\n            for (int query : bucket[middle])\
    \ {\n                if (check(query)) {\n                    high[query] = middle;\n\
    \                } else {\n                    low[query] = middle;\n        \
    \        }\n            }\n        }\n    }\n\n    return high;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 7 \"algo/offline/all.hpp\"\n\n\n#line\
    \ 1 \"algo/search/all.hpp\"\n\n\n\n#line 1 \"algo/search/bisect.hpp\"\n\n\n\n\
    #line 5 \"algo/search/bisect.hpp\"\n\nnamespace m1une {\nnamespace algo {\n\n\
    template <typename F>\nlong long first_true(long long ng, long long ok, F pred)\
    \ {\n    auto distance = [](long long a, long long b) {\n        return a > b\
    \ ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b) - a;\n    };\n\
    \    while (distance(ng, ok) > 1) {\n        long long mid = std::midpoint(ng,\
    \ ok);\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n  \
    \          ng = mid;\n        }\n    }\n    return ok;\n}\n\ntemplate <typename\
    \ F>\nlong long last_true(long long ok, long long ng, F pred) {\n    auto distance\
    \ = [](long long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a)\
    \ - b : static_cast<__int128_t>(b) - a;\n    };\n    while (distance(ok, ng) >\
    \ 1) {\n        long long mid = std::midpoint(ok, ng);\n        if (pred(mid))\
    \ {\n            ok = mid;\n        } else {\n            ng = mid;\n        }\n\
    \    }\n    return ok;\n}\n\ntemplate <typename F>\ndouble real_first_true(double\
    \ ng, double ok, F pred, int iterations = 80) {\n    for (int i = 0; i < iterations;\
    \ ++i) {\n        double mid = (ng + ok) / 2.0;\n        if (pred(mid)) {\n  \
    \          ok = mid;\n        } else {\n            ng = mid;\n        }\n   \
    \ }\n    return ok;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 1 \"algo/search/golden_section_search.hpp\"\n\n\n\n#line 8 \"algo/search/golden_section_search.hpp\"\
    \n#include <utility>\n#line 10 \"algo/search/golden_section_search.hpp\"\n\nnamespace\
    \ m1une {\nnamespace algo {\n\nnamespace detail {\n\ntemplate <std::integral Int,\
    \ class F, class Compare>\nInt integer_golden_section_search(Int left, Int right,\
    \ F f, Compare comp) {\n    assert(left < right);\n\n    using UInt = std::make_unsigned_t<Int>;\n\
    \    using Uint128 = unsigned __int128;\n    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right)\
    \ - static_cast<UInt>(left));\n\n    auto add_offset = [left](Uint128 offset)\
    \ -> Int {\n        if constexpr (std::signed_integral<Int>) {\n            if\
    \ (left < 0) {\n                const Uint128 negative_count = static_cast<Uint128>(-(left\
    \ + 1)) + 1;\n                if (offset < negative_count) {\n               \
    \     return static_cast<Int>(left + static_cast<Int>(offset));\n            \
    \    }\n                return static_cast<Int>(offset - negative_count);\n  \
    \          }\n        }\n        return static_cast<Int>(left + static_cast<Int>(offset));\n\
    \    };\n\n    using Value = std::decay_t<decltype(f(left))>;\n    struct Evaluated\
    \ {\n        Uint128 pos;\n        const Value* value;\n    };\n\n    Uint128\
    \ fib0 = 1;\n    Uint128 fib1 = 1;\n    Uint128 fib2 = 2;\n    int k = 2;\n  \
    \  while (fib2 < n) {\n        fib0 = fib1;\n        fib1 = fib2;\n        fib2\
    \ = fib0 + fib1;\n        ++k;\n    }\n\n    std::vector<std::pair<Uint128, Value>>\
    \ cache;\n    cache.reserve(static_cast<unsigned>(k) + 4);\n\n    auto find_cached\
    \ = [&](Uint128 pos) -> const Value* {\n        for (const auto& [cached_pos,\
    \ value] : cache) {\n            if (cached_pos == pos) return &value;\n     \
    \   }\n        return nullptr;\n    };\n\n    auto advance_fibonacci = [&]() {\n\
    \        const Uint128 old0 = fib0;\n        const Uint128 old1 = fib1;\n    \
    \    fib0 = old1 - old0;\n        fib1 = old0;\n        fib2 = old1;\n       \
    \ --k;\n    };\n\n    auto eval = [&](Uint128 pos) -> Evaluated {\n        if\
    \ (pos >= n) return Evaluated{pos, nullptr};\n        if (const Value* value =\
    \ find_cached(pos)) return Evaluated{pos, value};\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return Evaluated{pos, &cache.back().second};\n\
    \    };\n\n    auto get_value = [&](Uint128 pos) -> const Value& {\n        if\
    \ (const Value* value = find_cached(pos)) return *value;\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return cache.back().second;\n    };\n\n    auto\
    \ scan = [&](Uint128 scan_left, Uint128 scan_right) -> Int {\n        Int best\
    \ = add_offset(scan_left);\n        const Value* best_value = &get_value(scan_left);\n\
    \        for (Uint128 pos = scan_left + 1; pos <= scan_right; ++pos) {\n     \
    \       Int x = add_offset(pos);\n            const Value& value = get_value(pos);\n\
    \            if (comp(value, *best_value)) {\n                best = x;\n    \
    \            best_value = &value;\n            }\n        }\n        return best;\n\
    \    };\n\n    if (n <= 3) return scan(0, n - 1);\n\n    auto better = [&](const\
    \ Evaluated& a, const Evaluated& b) -> bool {\n        if ((a.value != nullptr)\
    \ != (b.value != nullptr)) return a.value != nullptr;\n        if (a.value ==\
    \ nullptr) return false;\n        return comp(*a.value, *b.value);\n    };\n\n\
    \    Uint128 left_pos = 0;\n    Uint128 right_pos = fib2 - 1;\n    Uint128 x1\
    \ = left_pos + fib0 - 1;\n    Uint128 x2 = left_pos + fib1 - 1;\n    Evaluated\
    \ y1 = eval(x1);\n    Evaluated y2 = eval(x2);\n\n    while (k > 2) {\n      \
    \  if (better(y2, y1)) {\n            left_pos = x1 + 1;\n            x1 = x2;\n\
    \            y1 = y2;\n            advance_fibonacci();\n            if (k ==\
    \ 2) break;\n            x2 = left_pos + fib1 - 1;\n            y2 = eval(x2);\n\
    \        } else {\n            right_pos = x2;\n            x2 = x1;\n       \
    \     y2 = y1;\n            advance_fibonacci();\n            if (k == 2) break;\n\
    \            x1 = left_pos + fib0 - 1;\n            y1 = eval(x1);\n        }\n\
    \    }\n\n    const Uint128 last_valid = n - 1;\n    if (right_pos > last_valid)\
    \ right_pos = last_valid;\n    assert(left_pos <= right_pos);\n    return scan(left_pos,\
    \ right_pos);\n}\n\n}  // namespace detail\n\ntemplate <std::integral Int, class\
    \ F>\nInt golden_section_search_argmin(Int left, Int right, F f) {\n    return\
    \ detail::integer_golden_section_search(left, right, f, [](const auto& a, const\
    \ auto& b) { return a < b; });\n}\n\ntemplate <std::integral Int, class F>\nInt\
    \ golden_section_search_argmax(Int left, Int right, F f) {\n    return detail::integer_golden_section_search(left,\
    \ right, f, [](const auto& a, const auto& b) { return b < a; });\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmin(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y2 < y1) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y2 < y1) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmax(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y1 < y2) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y1 < y2) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/search/ternary_search.hpp\"\
    \n\n\n\n#line 6 \"algo/search/ternary_search.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\ntemplate <std::integral Int, class F>\nInt ternary_search_argmin(Int\
    \ left, Int right, F f) {\n    assert(left < right);\n    while (right - left\
    \ > 3) {\n        const Int third = (right - left) / 3;\n        const Int middle_left\
    \ = left + third;\n        const Int middle_right = right - third;\n        if\
    \ (f(middle_right) < f(middle_left)) {\n            left = middle_left + 1;\n\
    \        } else {\n            right = middle_right;\n        }\n    }\n\n   \
    \ Int best = left;\n    auto best_value = f(best);\n    for (Int x = left + 1;\
    \ x < right; ++x) {\n        auto value = f(x);\n        if (value < best_value)\
    \ {\n            best = x;\n            best_value = value;\n        }\n    }\n\
    \    return best;\n}\n\ntemplate <std::integral Int, class F>\nInt ternary_search_argmax(Int\
    \ left, Int right, F f) {\n    assert(left < right);\n    while (right - left\
    \ > 3) {\n        const Int third = (right - left) / 3;\n        const Int middle_left\
    \ = left + third;\n        const Int middle_right = right - third;\n        if\
    \ (f(middle_left) < f(middle_right)) {\n            left = middle_left + 1;\n\
    \        } else {\n            right = middle_right;\n        }\n    }\n\n   \
    \ Int best = left;\n    auto best_value = f(best);\n    for (Int x = left + 1;\
    \ x < right; ++x) {\n        auto value = f(x);\n        if (best_value < value)\
    \ {\n            best = x;\n            best_value = value;\n        }\n    }\n\
    \    return best;\n}\n\ntemplate <class F>\ndouble real_ternary_search_argmin(double\
    \ left, double right, F f, int iterations = 100) {\n    assert(left <= right);\n\
    \    assert(0 <= iterations);\n    for (int i = 0; i < iterations; ++i) {\n  \
    \      const double middle_left = (left * 2.0 + right) / 3.0;\n        const double\
    \ middle_right = (left + right * 2.0) / 3.0;\n        if (f(middle_right) < f(middle_left))\
    \ {\n            left = middle_left;\n        } else {\n            right = middle_right;\n\
    \        }\n    }\n    return (left + right) / 2.0;\n}\n\ntemplate <class F>\n\
    double real_ternary_search_argmax(double left, double right, F f, int iterations\
    \ = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n    for\
    \ (int i = 0; i < iterations; ++i) {\n        const double middle_left = (left\
    \ * 2.0 + right) / 3.0;\n        const double middle_right = (left + right * 2.0)\
    \ / 3.0;\n        if (f(middle_left) < f(middle_right)) {\n            left =\
    \ middle_left;\n        } else {\n            right = middle_right;\n        }\n\
    \    }\n    return (left + right) / 2.0;\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n\n#line 7 \"algo/search/all.hpp\"\n\n\n#line 1 \"algo/sequence/all.hpp\"\
    \n\n\n\n#line 1 \"algo/sequence/inversion_count.hpp\"\n\n\n\n#line 5 \"algo/sequence/inversion_count.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\n// Returns the number of pairs (i,\
    \ j) with i < j and a[i] > a[j].\n// The vector is taken by value because merge\
    \ sort rearranges it.\ntemplate <typename T>\nlong long inversion_count(std::vector<T>\
    \ a) {\n    const int n = int(a.size());\n    std::vector<T> temp = a;\n\n   \
    \ auto merge_sort = [&](auto& self, int l, int r) -> long long {\n        if (r\
    \ - l <= 1) return 0;\n\n        const int m = l + (r - l) / 2;\n        long\
    \ long inv = self(self, l, m) + self(self, m, r);\n\n        int i = l;\n    \
    \    int j = m;\n        int k = l;\n        while (i < m && j < r) {\n      \
    \      if (!(a[j] < a[i])) {\n                temp[k++] = a[i++];\n          \
    \  } else {\n                temp[k++] = a[j++];\n                inv += m - i;\n\
    \            }\n        }\n\n        while (i < m) temp[k++] = a[i++];\n     \
    \   while (j < r) temp[k++] = a[j++];\n\n        for (int p = l; p < r; ++p) {\n\
    \            a[p] = temp[p];\n        }\n\n        return inv;\n    };\n\n   \
    \ return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/sequence/lis.hpp\"\n\n\n\n#line 5 \"algo/sequence/lis.hpp\"\
    \n#include <iterator>\n#line 7 \"algo/sequence/lis.hpp\"\n\nnamespace m1une {\n\
    namespace algo {\n\n// Returns the zero-based indices of a longest increasing\
    \ subsequence.\n// If `strict` is false, equal adjacent values are also allowed.\n\
    template <typename T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict\
    \ = true) {\n    const int n = int(a.size());\n    std::vector<T> tails;\n   \
    \ std::vector<int> tail_positions;\n    std::vector<int> predecessor(n, -1);\n\
    \    tails.reserve(n);\n    tail_positions.reserve(n);\n\n    for (int i = 0;\
    \ i < n; ++i) {\n        auto it = strict ? std::lower_bound(tails.begin(), tails.end(),\
    \ a[i])\n                         : std::upper_bound(tails.begin(), tails.end(),\
    \ a[i]);\n        const int length = int(std::distance(tails.begin(), it));\n\n\
    \        if (it == tails.end()) {\n            tails.push_back(a[i]);\n      \
    \      tail_positions.push_back(i);\n        } else {\n            *it = a[i];\n\
    \            tail_positions[length] = i;\n        }\n\n        if (length > 0)\
    \ {\n            predecessor[i] = tail_positions[length - 1];\n        }\n   \
    \ }\n\n    if (tail_positions.empty()) return {};\n\n    std::vector<int> result;\n\
    \    result.reserve(tail_positions.size());\n    int current = tail_positions.back();\n\
    \    while (current != -1) {\n        result.push_back(current);\n        current\
    \ = predecessor[current];\n    }\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 1 \"algo/sequence/run_length_encoding.hpp\"\n\n\n\n#line 7 \"algo/sequence/run_length_encoding.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\ntemplate <typename Container>\nauto\
    \ run_length_encoding(const Container& values) {\n    using T = typename Container::value_type;\n\
    \    std::vector<std::pair<T, long long>> result;\n\n    auto it = std::begin(values);\n\
    \    auto last = std::end(values);\n    if (it == last) {\n        return result;\n\
    \    }\n\n    T current = *it;\n    long long count = 0;\n    for (; it != last;\
    \ ++it) {\n        if (*it == current) {\n            ++count;\n        } else\
    \ {\n            result.emplace_back(current, count);\n            current = *it;\n\
    \            count = 1;\n        }\n    }\n    result.emplace_back(current, count);\n\
    \    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 1 \"algo/sequence/subset_sum.hpp\"\n\n\n\n#line 8 \"algo/sequence/subset_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <typename\
    \ T>\nstd::vector<T> enumerate_sorted_subset_sums(\n    const std::vector<T>&\
    \ values,\n    int left,\n    int right\n) {\n    std::vector<T> sums(1, T{});\n\
    \    std::vector<T> merged;\n\n    for (int i = left; i < right; ++i) {\n    \
    \    const std::size_t size = sums.size();\n        merged.clear();\n        merged.reserve(size\
    \ * 2);\n\n        std::size_t without = 0;\n        std::size_t with = 0;\n \
    \       while (without < size && with < size) {\n            const T with_current\
    \ = sums[with] + values[i];\n            if (with_current < sums[without]) {\n\
    \                merged.push_back(with_current);\n                ++with;\n  \
    \          } else {\n                merged.push_back(sums[without]);\n      \
    \          ++without;\n            }\n        }\n        while (without < size)\
    \ {\n            merged.push_back(sums[without]);\n            ++without;\n  \
    \      }\n        while (with < size) {\n            merged.push_back(sums[with]\
    \ + values[i]);\n            ++with;\n        }\n        sums.swap(merged);\n\
    \    }\n\n    return sums;\n}\n\n}  // namespace internal\n\n// Returns the sorted\
    \ subset sums of values[0, n / 2) and values[n / 2, n).\ntemplate <typename T>\n\
    std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(\n    const\
    \ std::vector<T>& values\n) {\n    const int n = int(values.size());\n    const\
    \ int middle = n / 2;\n    return {\n        internal::enumerate_sorted_subset_sums(values,\
    \ 0, middle),\n        internal::enumerate_sorted_subset_sums(values, middle,\
    \ n)\n    };\n}\n\n// Returns the maximum subset sum not exceeding limit.\ntemplate\
    \ <typename T>\nT maximum_subset_sum(const std::vector<T>& values, const T& limit)\
    \ {\n    assert(!(limit < T{}));\n    auto [left_sums, right_sums] = enumerate_half_subset_sums(values);\n\
    \n    T answer{};\n    std::size_t right_count = right_sums.size();\n    for (const\
    \ T& left : left_sums) {\n        while (\n            right_count > 0 &&\n  \
    \          limit < left + right_sums[right_count - 1]\n        ) {\n         \
    \   --right_count;\n        }\n        if (right_count == 0) break;\n\n      \
    \  const T candidate = left + right_sums[right_count - 1];\n        if (answer\
    \ < candidate) answer = candidate;\n    }\n    return answer;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 8 \"algo/sequence/all.hpp\"\n\n\n#line\
    \ 9 \"algo/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_ALL_HPP

    #define M1UNE_ALGO_ALL_HPP 1


    #include "dp/all.hpp"

    #include "enumeration/all.hpp"

    #include "offline/all.hpp"

    #include "search/all.hpp"

    #include "sequence/all.hpp"


    #endif  // M1UNE_ALGO_ALL_HPP

    '
  dependsOn:
  - algo/dp/all.hpp
  - algo/dp/knapsack.hpp
  - algo/enumeration/all.hpp
  - algo/enumeration/combination.hpp
  - algo/enumeration/gray_code.hpp
  - algo/enumeration/submask.hpp
  - algo/offline/all.hpp
  - algo/offline/cdq_divide_and_conquer.hpp
  - algo/offline/mo.hpp
  - algo/offline/parallel_binary_search.hpp
  - algo/search/all.hpp
  - algo/search/bisect.hpp
  - algo/search/golden_section_search.hpp
  - algo/search/ternary_search.hpp
  - algo/sequence/all.hpp
  - algo/sequence/inversion_count.hpp
  - algo/sequence/lis.hpp
  - algo/sequence/run_length_encoding.hpp
  - algo/sequence/subset_sum.hpp
  isVerificationFile: false
  path: algo/all.hpp
  requiredBy: []
  timestamp: '2026-07-09 00:39:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/all.hpp
layout: document
title: Algorithms All
---

## Overview

`algo/all.hpp` includes one-shot, domain-neutral algorithms. The public
namespace is `m1une::algo`; subdirectories are only browsing categories.

Convex optimization helpers live under `convex/`.

If a header builds an object and then answers repeated queries, it belongs in
`ds/` instead, even when it is static. For example, cumulative sums live in
`ds/range_query/`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/sequence/all.hpp` | Sequence and array algorithms such as LIS, inversion count, run-length encoding, and subset sum. |
| `algo/search/all.hpp` | Search-over-answer and unimodal optimization helpers. |
| `algo/offline/all.hpp` | Offline query processing such as Mo's algorithm. |
| `algo/enumeration/all.hpp` | Combinatorial traversal helpers such as Gray-code enumeration. |
| `algo/dp/all.hpp` | Domain-neutral DP helpers such as knapsack routines. |
