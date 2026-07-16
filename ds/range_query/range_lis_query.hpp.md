---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/wavelet_matrix.hpp
    title: Wavelet Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_lis_query.test.cpp
    title: verify/ds/range_query/range_lis_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/range_lis_query.hpp\"\n\n\n\n#line 1 \"ds/wavelet_matrix/wavelet_matrix.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <concepts>\n\
    #include <cstdint>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#if defined(__AVX2__) || defined(__BMI2__)\n\
    #include <immintrin.h>\n#endif\n\nnamespace m1une {\nnamespace ds {\n\n// A static\
    \ wavelet matrix for integral values.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrix {\n    using value_type = T;\n    using unsigned_type\
    \ = std::make_unsigned_t<T>;\n\n   private:\n    static constexpr int value_bit_width\
    \ =\n        std::numeric_limits<unsigned_type>::digits;\n    static constexpr\
    \ unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (value_bit_width - 1);\n        }\
    \ else {\n            return unsigned_type(0);\n        }\n    }();\n\n    struct\
    \ BitVector {\n        std::vector<std::uint64_t> bits;\n        std::vector<int>\
    \ prefix;\n\n        BitVector() = default;\n\n        explicit BitVector(int\
    \ n)\n            : bits(((std::size_t(n) + 63) >> 6) + 1, 0),\n             \
    \ prefix(bits.size(), 0) {}\n\n        void build() {\n            for (std::size_t\
    \ i = 0; i + 1 < bits.size(); i++) {\n                prefix[i + 1] = prefix[i]\
    \ + std::popcount(bits[i]);\n            }\n        }\n\n        bool get(int\
    \ p) const {\n            return (bits[std::size_t(p) >> 6] >> (p & 63)) & 1;\n\
    \        }\n\n        int rank1(int r) const {\n            std::size_t word =\
    \ std::size_t(r) >> 6;\n            int offset = r & 63;\n            int result\
    \ = prefix[word];\n#if defined(__BMI2__)\n            result += std::popcount(\n\
    \                _bzhi_u64(bits[word], static_cast<unsigned int>(offset))\n  \
    \          );\n#else\n            if (offset != 0) {\n                result +=\
    \ std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n#endif\n            return result;\n\
    \        }\n    };\n\n    int _n;\n    int _log;\n    unsigned_type _key_prefix;\n\
    \    unsigned_type _min_key;\n    unsigned_type _max_key;\n    std::vector<BitVector>\
    \ _matrix;\n    std::vector<int> _zero_count;\n\n    static unsigned_type encode(T\
    \ value) {\n        unsigned_type bits;\n        if constexpr (std::signed_integral<T>)\
    \ {\n            bits = std::bit_cast<unsigned_type>(value);\n        } else {\n\
    \            bits = value;\n        }\n        return bits ^ sign_mask;\n    }\n\
    \n    static T decode(unsigned_type key) {\n        unsigned_type bits = key ^\
    \ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n            return\
    \ std::bit_cast<T>(bits);\n        } else {\n            return bits;\n      \
    \  }\n    }\n\n    bool bit(unsigned_type value, int level) const {\n        return\
    \ (value >> (_log - 1 - level)) & unsigned_type(1);\n    }\n\n    static std::uint64_t\
    \ extract_bits(\n        const unsigned_type* values,\n        int count,\n  \
    \      int shift\n    ) {\n        std::uint64_t result = 0;\n        int i =\
    \ 0;\n#if defined(__AVX2__)\n        if constexpr (sizeof(unsigned_type) == 8)\
    \ {\n            __m128i left = _mm_cvtsi32_si128(63 - shift);\n            for\
    \ (; i + 4 <= count; i += 4) {\n                __m256i data = _mm256_loadu_si256(\n\
    \                    reinterpret_cast<const __m256i*>(values + i)\n          \
    \      );\n                data = _mm256_sll_epi64(data, left);\n            \
    \    int mask = _mm256_movemask_pd(_mm256_castsi256_pd(data));\n             \
    \   result |= std::uint64_t(mask) << i;\n            }\n        } else if constexpr\
    \ (sizeof(unsigned_type) == 4) {\n            __m128i left = _mm_cvtsi32_si128(31\
    \ - shift);\n            for (; i + 8 <= count; i += 8) {\n                __m256i\
    \ data = _mm256_loadu_si256(\n                    reinterpret_cast<const __m256i*>(values\
    \ + i)\n                );\n                data = _mm256_sll_epi32(data, left);\n\
    \                int mask = _mm256_movemask_ps(_mm256_castsi256_ps(data));\n \
    \               result |= std::uint64_t(mask) << i;\n            }\n        }\n\
    #endif\n        for (; i < count; i++) {\n            result |= std::uint64_t((values[i]\
    \ >> shift) & unsigned_type(1))\n                      << i;\n        }\n    \
    \    return result;\n    }\n\n    int count_less_encoded(int l, int r, unsigned_type\
    \ upper) const {\n        if (_n == 0 || upper <= _min_key) return 0;\n      \
    \  if (upper > _max_key) return r - l;\n\n        int result = 0;\n        for\
    \ (int level = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            if (bit(upper, level))\
    \ {\n                result += (r - l) - (r1 - l1);\n                l = _zero_count[level]\
    \ + l1;\n                r = _zero_count[level] + r1;\n            } else {\n\
    \                l -= l1;\n                r -= r1;\n            }\n        }\n\
    \        return result;\n    }\n\n   public:\n    WaveletMatrix()\n        : _n(0),\n\
    \          _log(0),\n          _key_prefix(0),\n          _min_key(0),\n     \
    \     _max_key(0) {}\n\n    explicit WaveletMatrix(const std::vector<T>& values)\n\
    \        : _n(int(values.size())),\n          _log(0),\n          _key_prefix(0),\n\
    \          _min_key(0),\n          _max_key(0) {\n        std::vector<unsigned_type>\
    \ current(_n);\n        std::vector<unsigned_type> next(_n);\n        for (int\
    \ i = 0; i < _n; i++) current[i] = encode(values[i]);\n        if (_n == 0) return;\n\
    \n        _min_key = current[0];\n        _max_key = current[0];\n        for\
    \ (unsigned_type key : current) {\n            if (key < _min_key) _min_key =\
    \ key;\n            if (_max_key < key) _max_key = key;\n        }\n        _log\
    \ = int(std::bit_width(unsigned_type(_min_key ^ _max_key)));\n        if (_log\
    \ != value_bit_width) {\n            _key_prefix = unsigned_type((_min_key >>\
    \ _log) << _log);\n        }\n        _zero_count.assign(_log, 0);\n\n       \
    \ _matrix.reserve(_log);\n        for (int level = 0; level < _log; level++) {\n\
    \            _matrix.emplace_back(_n);\n            BitVector& bit_vector = _matrix.back();\n\
    \            int shift = _log - 1 - level;\n            int zeros = 0;\n     \
    \       for (int base = 0; base < _n; base += 64) {\n                int count\
    \ = std::min(64, _n - base);\n                std::uint64_t word = extract_bits(\n\
    \                    current.data() + base,\n                    count,\n    \
    \                shift\n                );\n                bit_vector.bits[std::size_t(base)\
    \ >> 6] = word;\n                zeros += count - std::popcount(word);\n     \
    \       }\n            bit_vector.build();\n\n            _zero_count[level] =\
    \ zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n  \
    \          for (int base = 0; base < _n; base += 64) {\n                int count\
    \ = std::min(64, _n - base);\n                std::uint64_t ones = bit_vector.bits[std::size_t(base)\
    \ >> 6];\n                std::uint64_t valid = count == 64\n                \
    \                          ? ~std::uint64_t(0)\n                             \
    \             : (std::uint64_t(1) << count) - 1;\n                std::uint64_t\
    \ zeroes = (~ones) & valid;\n                while (zeroes != 0) {\n         \
    \           int offset = std::countr_zero(zeroes);\n                    next[zero_pos++]\
    \ = current[base + offset];\n                    zeroes &= zeroes - 1;\n     \
    \           }\n                while (ones != 0) {\n                    int offset\
    \ = std::countr_zero(ones);\n                    next[one_pos++] = current[base\
    \ + offset];\n                    ones &= ones - 1;\n                }\n     \
    \       }\n            current.swap(next);\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    T access(int p) const {\n        assert(0 <= p && p <\
    \ _n);\n        unsigned_type key = _key_prefix;\n        for (int level = 0;\
    \ level < _log; level++) {\n            int ones_before = _matrix[level].rank1(p);\n\
    \            bool one = _matrix[level].get(p);\n            if (one) {\n     \
    \           key |= unsigned_type(1) << (_log - 1 - level);\n                p\
    \ = _zero_count[level] + ones_before;\n            } else {\n                p\
    \ -= ones_before;\n            }\n        }\n        return decode(key);\n   \
    \ }\n\n    T operator[](int p) const {\n        return access(p);\n    }\n\n \
    \   int rank(T value, int r) const {\n        assert(0 <= r && r <= _n);\n   \
    \     return rank(value, 0, r);\n    }\n\n    int rank(T value, int l, int r)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        unsigned_type\
    \ key = encode(value);\n        if (_n == 0 || key < _min_key || _max_key < key)\
    \ return 0;\n        for (int level = 0; level < _log; level++) {\n          \
    \  int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(key, level)) {\n                l = _zero_count[level] +\
    \ l1;\n                r = _zero_count[level] + r1;\n            } else {\n  \
    \              l -= l1;\n                r -= r1;\n            }\n        }\n\
    \        return r - l;\n    }\n\n    T kth_smallest(int l, int r, int k) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        assert(0 <= k && k\
    \ < r - l);\n        unsigned_type key = _key_prefix;\n        for (int level\
    \ = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            int l0 = l - l1;\n\
    \            int r0 = r - r1;\n            int zeros = r0 - l0;\n            if\
    \ (k < zeros) {\n                l = l0;\n                r = r0;\n          \
    \  } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (_log - 1 - level);\n                l = _zero_count[level] + l1;\n     \
    \           r = _zero_count[level] + r1;\n            }\n        }\n        return\
    \ decode(key);\n    }\n\n    T kth_largest(int l, int r, int k) const {\n    \
    \    assert(0 <= l && l <= r && r <= _n);\n        assert(0 <= k && k < r - l);\n\
    \        return kth_smallest(l, r, r - l - 1 - k);\n    }\n\n    int range_freq(int\
    \ l, int r, T upper) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       return count_less_encoded(l, r, encode(upper));\n    }\n\n    int range_freq(int\
    \ l, int r, T lower, T upper) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        if (upper <= lower) return 0;\n        return range_freq(l, r,\
    \ upper) - range_freq(l, r, lower);\n    }\n\n    std::optional<T> prev_value(int\
    \ l, int r, T upper) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       int count = range_freq(l, r, upper);\n        if (count == 0) return std::nullopt;\n\
    \        return kth_smallest(l, r, count - 1);\n    }\n\n    std::optional<T>\
    \ next_value(int l, int r, T lower) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        int count = range_freq(l, r, lower);\n        if (count ==\
    \ r - l) return std::nullopt;\n        return kth_smallest(l, r, count);\n   \
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 5 \"ds/range_query/range_lis_query.hpp\"\
    \n\n#line 8 \"ds/range_query/range_lis_query.hpp\"\n#include <numeric>\n#line\
    \ 11 \"ds/range_query/range_lis_query.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\nnamespace range_lis_query_internal {\n\nconstexpr int none = -1;\nusing\
    \ Permutation = std::vector<int>;\nusing Iterator = Permutation::iterator;\n\n\
    inline Permutation inverse(const Permutation& permutation) {\n    int n = int(permutation.size());\n\
    \    Permutation result(n, none);\n    for (int i = 0; i < n; i++) {\n       \
    \ if (permutation[i] != none) result[permutation[i]] = i;\n    }\n    return result;\n\
    }\n\n// Distance multiplication of two unit-Monge matrices, represented by their\n\
    // permutations. `workspace` must have the size used by subunit_monge_product.\n\
    inline void unit_monge_product(\n    int n,\n    Iterator workspace,\n    Iterator\
    \ first,\n    Iterator second\n) {\n    if (n == 1) {\n        workspace[0] =\
    \ 0;\n        return;\n    }\n\n    Iterator result_row = workspace;\n    workspace\
    \ += n;\n    Iterator result_column = workspace;\n    workspace += n;\n\n    auto\
    \ map_half = [=](int length, const auto& belongs, const auto& map) {\n       \
    \ Iterator first_half = workspace;\n        Iterator first_position = workspace\
    \ + length;\n        Iterator second_half = workspace + 2 * length;\n        Iterator\
    \ second_position = workspace + 3 * length;\n\n        auto split = [=](Iterator\
    \ source, Iterator half, Iterator position) {\n            for (int i = 0; i <\
    \ n; i++) {\n                if (belongs(source[i])) {\n                    *half++\
    \ = map(source[i]);\n                    *position++ = i;\n                }\n\
    \            }\n        };\n        split(first, first_half, first_position);\n\
    \        split(second, second_half, second_position);\n\n        Iterator product\
    \ = workspace + 4 * length;\n        unit_monge_product(\n            length,\n\
    \            product,\n            first_half,\n            second_half\n    \
    \    );\n        for (int i = 0; i < length; i++) {\n            int row = first_position[i];\n\
    \            int column = second_position[product[i]];\n            result_row[row]\
    \ = column;\n            result_column[column] = row;\n        }\n    };\n\n \
    \   int middle = n / 2;\n    map_half(\n        middle,\n        [middle](int\
    \ value) { return value < middle; },\n        [](int value) { return value; }\n\
    \    );\n    map_half(\n        n - middle,\n        [middle](int value) { return\
    \ value >= middle; },\n        [middle](int value) { return value - middle; }\n\
    \    );\n\n    struct DiagonalIterator {\n        int delta = 0;\n        int\
    \ column = 0;\n    };\n\n    int row = n;\n    auto move_right = [&](DiagonalIterator&\
    \ iterator) {\n        if (second[iterator.column] < middle) {\n            if\
    \ (result_column[iterator.column] >= row) iterator.delta++;\n        } else {\n\
    \            if (result_column[iterator.column] < row) iterator.delta++;\n   \
    \     }\n        iterator.column++;\n    };\n    auto move_up = [&](DiagonalIterator&\
    \ iterator) {\n        if (first[row] < middle) {\n            if (result_row[row]\
    \ >= iterator.column) iterator.delta--;\n        } else {\n            if (result_row[row]\
    \ < iterator.column) iterator.delta--;\n        }\n    };\n\n    DiagonalIterator\
    \ negative;\n    DiagonalIterator positive;\n    while (row != 0) {\n        while\
    \ (positive.column != n) {\n            DiagonalIterator next = positive;\n  \
    \          move_right(next);\n            if (next.delta != 0) break;\n      \
    \      positive = next;\n        }\n        row--;\n        move_up(negative);\n\
    \        move_up(positive);\n        while (negative.delta != 0) move_right(negative);\n\
    \        if (negative.column > positive.column) {\n            result_row[row]\
    \ = positive.column;\n        }\n    }\n}\n\ninline int workspace_size(int n)\
    \ {\n    int result = 1;\n    while (n > 1) {\n        result += 2 * n;\n    \
    \    n = (n + 1) / 2;\n        result += 4 * n;\n    }\n    return result;\n}\n\
    \ninline Permutation subunit_monge_product(\n    Permutation first,\n    Permutation\
    \ second\n) {\n    int n = int(first.size());\n    Permutation first_inverse =\
    \ inverse(first);\n    Permutation second_inverse = inverse(second);\n    std::swap(second,\
    \ second_inverse);\n\n    Permutation first_map;\n    Permutation second_map;\n\
    \    for (int i = n - 1; i >= 0; i--) {\n        if (first[i] != none) {\n   \
    \         first_map.push_back(i);\n            first[n - int(first_map.size())]\
    \ = first[i];\n        }\n    }\n    std::reverse(first_map.begin(), first_map.end());\n\
    \n    int missing = 0;\n    for (int i = 0; i < n; i++) {\n        if (first_inverse[i]\
    \ == none) first[missing++] = i;\n    }\n    for (int i = 0; i < n; i++) {\n \
    \       if (second[i] != none) {\n            second[int(second_map.size())] =\
    \ second[i];\n            second_map.push_back(i);\n        }\n    }\n    missing\
    \ = int(second_map.size());\n    for (int i = 0; i < n; i++) {\n        if (second_inverse[i]\
    \ == none) second[missing++] = i;\n    }\n\n    Permutation workspace(workspace_size(n));\n\
    \    unit_monge_product(\n        n,\n        workspace.begin(),\n        first.begin(),\n\
    \        second.begin()\n    );\n\n    Permutation result(n, none);\n    int first_count\
    \ = int(first_map.size());\n    int second_count = int(second_map.size());\n \
    \   for (int i = 0; i < first_count; i++) {\n        int mapped = workspace[n\
    \ - first_count + i];\n        if (mapped < second_count) {\n            result[first_map[i]]\
    \ = second_map[mapped];\n        }\n    }\n    return result;\n}\n\ninline Permutation\
    \ seaweed_doubling(const Permutation& permutation) {\n    int n = int(permutation.size());\n\
    \    if (n == 1) return Permutation(1, none);\n\n    int middle = n / 2;\n   \
    \ Permutation lower;\n    Permutation upper;\n    Permutation lower_map;\n   \
    \ Permutation upper_map;\n    for (int i = 0; i < n; i++) {\n        int value\
    \ = permutation[i];\n        if (value < middle) {\n            lower.push_back(value);\n\
    \            lower_map.push_back(i);\n        } else {\n            upper.push_back(value\
    \ - middle);\n            upper_map.push_back(i);\n        }\n    }\n\n    lower\
    \ = seaweed_doubling(lower);\n    upper = seaweed_doubling(upper);\n    Permutation\
    \ lower_padded(n);\n    Permutation upper_padded(n);\n    std::iota(lower_padded.begin(),\
    \ lower_padded.end(), 0);\n    std::iota(upper_padded.begin(), upper_padded.end(),\
    \ 0);\n\n    for (int i = 0; i < middle; i++) {\n        lower_padded[lower_map[i]]\
    \ =\n            lower[i] == none ? none : lower_map[lower[i]];\n    }\n    for\
    \ (int i = 0; middle + i < n; i++) {\n        upper_padded[upper_map[i]] =\n \
    \           upper[i] == none ? none : upper_map[upper[i]];\n    }\n    return\
    \ subunit_monge_product(\n        std::move(lower_padded),\n        std::move(upper_padded)\n\
    \    );\n}\n\ntemplate <class T>\nPermutation make_permutation(const std::vector<T>&\
    \ values) {\n    int n = int(values.size());\n    Permutation order(n);\n    std::iota(order.begin(),\
    \ order.end(), 0);\n    std::sort(order.begin(), order.end(), [&](int first, int\
    \ second) {\n        if (values[first] < values[second]) return true;\n      \
    \  if (values[second] < values[first]) return false;\n        return first > second;\n\
    \    });\n\n    Permutation permutation(n);\n    for (int rank = 0; rank < n;\
    \ rank++) {\n        permutation[order[rank]] = rank;\n    }\n    return permutation;\n\
    }\n\n}  // namespace range_lis_query_internal\n\n// Static strict-LIS lengths\
    \ for arbitrary subarrays.\ntemplate <class T>\nstruct RangeLisQuery {\n   private:\n\
    \    int _n;\n    WaveletMatrix<int> _seaweed;\n\n   public:\n    RangeLisQuery()\
    \ : _n(0), _seaweed() {}\n\n    explicit RangeLisQuery(const std::vector<T>& values)\n\
    \        : _n(int(values.size())), _seaweed() {\n        if (_n == 0) return;\n\
    \        std::vector<int> row = range_lis_query_internal::seaweed_doubling(\n\
    \            range_lis_query_internal::make_permutation(values)\n        );\n\
    \        for (int& value : row) {\n            if (value == range_lis_query_internal::none)\
    \ value = _n;\n        }\n        _seaweed = WaveletMatrix<int>(row);\n    }\n\
    \n    int size() const {\n        return _n;\n    }\n\n    bool empty() const\
    \ {\n        return _n == 0;\n    }\n\n    // Returns the strict LIS length of\
    \ values[left, right).\n    int query(int left, int right) const {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        if (left == right) return\
    \ 0;\n        return right - left - _seaweed.range_freq(left, _n, right);\n  \
    \  }\n\n    int lis_length(int left, int right) const {\n        return query(left,\
    \ right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_RANGE_LIS_QUERY_HPP\n#define M1UNE_DS_RANGE_QUERY_RANGE_LIS_QUERY_HPP\
    \ 1\n\n#include \"../wavelet_matrix/wavelet_matrix.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\nnamespace range_lis_query_internal {\n\n\
    constexpr int none = -1;\nusing Permutation = std::vector<int>;\nusing Iterator\
    \ = Permutation::iterator;\n\ninline Permutation inverse(const Permutation& permutation)\
    \ {\n    int n = int(permutation.size());\n    Permutation result(n, none);\n\
    \    for (int i = 0; i < n; i++) {\n        if (permutation[i] != none) result[permutation[i]]\
    \ = i;\n    }\n    return result;\n}\n\n// Distance multiplication of two unit-Monge\
    \ matrices, represented by their\n// permutations. `workspace` must have the size\
    \ used by subunit_monge_product.\ninline void unit_monge_product(\n    int n,\n\
    \    Iterator workspace,\n    Iterator first,\n    Iterator second\n) {\n    if\
    \ (n == 1) {\n        workspace[0] = 0;\n        return;\n    }\n\n    Iterator\
    \ result_row = workspace;\n    workspace += n;\n    Iterator result_column = workspace;\n\
    \    workspace += n;\n\n    auto map_half = [=](int length, const auto& belongs,\
    \ const auto& map) {\n        Iterator first_half = workspace;\n        Iterator\
    \ first_position = workspace + length;\n        Iterator second_half = workspace\
    \ + 2 * length;\n        Iterator second_position = workspace + 3 * length;\n\n\
    \        auto split = [=](Iterator source, Iterator half, Iterator position) {\n\
    \            for (int i = 0; i < n; i++) {\n                if (belongs(source[i]))\
    \ {\n                    *half++ = map(source[i]);\n                    *position++\
    \ = i;\n                }\n            }\n        };\n        split(first, first_half,\
    \ first_position);\n        split(second, second_half, second_position);\n\n \
    \       Iterator product = workspace + 4 * length;\n        unit_monge_product(\n\
    \            length,\n            product,\n            first_half,\n        \
    \    second_half\n        );\n        for (int i = 0; i < length; i++) {\n   \
    \         int row = first_position[i];\n            int column = second_position[product[i]];\n\
    \            result_row[row] = column;\n            result_column[column] = row;\n\
    \        }\n    };\n\n    int middle = n / 2;\n    map_half(\n        middle,\n\
    \        [middle](int value) { return value < middle; },\n        [](int value)\
    \ { return value; }\n    );\n    map_half(\n        n - middle,\n        [middle](int\
    \ value) { return value >= middle; },\n        [middle](int value) { return value\
    \ - middle; }\n    );\n\n    struct DiagonalIterator {\n        int delta = 0;\n\
    \        int column = 0;\n    };\n\n    int row = n;\n    auto move_right = [&](DiagonalIterator&\
    \ iterator) {\n        if (second[iterator.column] < middle) {\n            if\
    \ (result_column[iterator.column] >= row) iterator.delta++;\n        } else {\n\
    \            if (result_column[iterator.column] < row) iterator.delta++;\n   \
    \     }\n        iterator.column++;\n    };\n    auto move_up = [&](DiagonalIterator&\
    \ iterator) {\n        if (first[row] < middle) {\n            if (result_row[row]\
    \ >= iterator.column) iterator.delta--;\n        } else {\n            if (result_row[row]\
    \ < iterator.column) iterator.delta--;\n        }\n    };\n\n    DiagonalIterator\
    \ negative;\n    DiagonalIterator positive;\n    while (row != 0) {\n        while\
    \ (positive.column != n) {\n            DiagonalIterator next = positive;\n  \
    \          move_right(next);\n            if (next.delta != 0) break;\n      \
    \      positive = next;\n        }\n        row--;\n        move_up(negative);\n\
    \        move_up(positive);\n        while (negative.delta != 0) move_right(negative);\n\
    \        if (negative.column > positive.column) {\n            result_row[row]\
    \ = positive.column;\n        }\n    }\n}\n\ninline int workspace_size(int n)\
    \ {\n    int result = 1;\n    while (n > 1) {\n        result += 2 * n;\n    \
    \    n = (n + 1) / 2;\n        result += 4 * n;\n    }\n    return result;\n}\n\
    \ninline Permutation subunit_monge_product(\n    Permutation first,\n    Permutation\
    \ second\n) {\n    int n = int(first.size());\n    Permutation first_inverse =\
    \ inverse(first);\n    Permutation second_inverse = inverse(second);\n    std::swap(second,\
    \ second_inverse);\n\n    Permutation first_map;\n    Permutation second_map;\n\
    \    for (int i = n - 1; i >= 0; i--) {\n        if (first[i] != none) {\n   \
    \         first_map.push_back(i);\n            first[n - int(first_map.size())]\
    \ = first[i];\n        }\n    }\n    std::reverse(first_map.begin(), first_map.end());\n\
    \n    int missing = 0;\n    for (int i = 0; i < n; i++) {\n        if (first_inverse[i]\
    \ == none) first[missing++] = i;\n    }\n    for (int i = 0; i < n; i++) {\n \
    \       if (second[i] != none) {\n            second[int(second_map.size())] =\
    \ second[i];\n            second_map.push_back(i);\n        }\n    }\n    missing\
    \ = int(second_map.size());\n    for (int i = 0; i < n; i++) {\n        if (second_inverse[i]\
    \ == none) second[missing++] = i;\n    }\n\n    Permutation workspace(workspace_size(n));\n\
    \    unit_monge_product(\n        n,\n        workspace.begin(),\n        first.begin(),\n\
    \        second.begin()\n    );\n\n    Permutation result(n, none);\n    int first_count\
    \ = int(first_map.size());\n    int second_count = int(second_map.size());\n \
    \   for (int i = 0; i < first_count; i++) {\n        int mapped = workspace[n\
    \ - first_count + i];\n        if (mapped < second_count) {\n            result[first_map[i]]\
    \ = second_map[mapped];\n        }\n    }\n    return result;\n}\n\ninline Permutation\
    \ seaweed_doubling(const Permutation& permutation) {\n    int n = int(permutation.size());\n\
    \    if (n == 1) return Permutation(1, none);\n\n    int middle = n / 2;\n   \
    \ Permutation lower;\n    Permutation upper;\n    Permutation lower_map;\n   \
    \ Permutation upper_map;\n    for (int i = 0; i < n; i++) {\n        int value\
    \ = permutation[i];\n        if (value < middle) {\n            lower.push_back(value);\n\
    \            lower_map.push_back(i);\n        } else {\n            upper.push_back(value\
    \ - middle);\n            upper_map.push_back(i);\n        }\n    }\n\n    lower\
    \ = seaweed_doubling(lower);\n    upper = seaweed_doubling(upper);\n    Permutation\
    \ lower_padded(n);\n    Permutation upper_padded(n);\n    std::iota(lower_padded.begin(),\
    \ lower_padded.end(), 0);\n    std::iota(upper_padded.begin(), upper_padded.end(),\
    \ 0);\n\n    for (int i = 0; i < middle; i++) {\n        lower_padded[lower_map[i]]\
    \ =\n            lower[i] == none ? none : lower_map[lower[i]];\n    }\n    for\
    \ (int i = 0; middle + i < n; i++) {\n        upper_padded[upper_map[i]] =\n \
    \           upper[i] == none ? none : upper_map[upper[i]];\n    }\n    return\
    \ subunit_monge_product(\n        std::move(lower_padded),\n        std::move(upper_padded)\n\
    \    );\n}\n\ntemplate <class T>\nPermutation make_permutation(const std::vector<T>&\
    \ values) {\n    int n = int(values.size());\n    Permutation order(n);\n    std::iota(order.begin(),\
    \ order.end(), 0);\n    std::sort(order.begin(), order.end(), [&](int first, int\
    \ second) {\n        if (values[first] < values[second]) return true;\n      \
    \  if (values[second] < values[first]) return false;\n        return first > second;\n\
    \    });\n\n    Permutation permutation(n);\n    for (int rank = 0; rank < n;\
    \ rank++) {\n        permutation[order[rank]] = rank;\n    }\n    return permutation;\n\
    }\n\n}  // namespace range_lis_query_internal\n\n// Static strict-LIS lengths\
    \ for arbitrary subarrays.\ntemplate <class T>\nstruct RangeLisQuery {\n   private:\n\
    \    int _n;\n    WaveletMatrix<int> _seaweed;\n\n   public:\n    RangeLisQuery()\
    \ : _n(0), _seaweed() {}\n\n    explicit RangeLisQuery(const std::vector<T>& values)\n\
    \        : _n(int(values.size())), _seaweed() {\n        if (_n == 0) return;\n\
    \        std::vector<int> row = range_lis_query_internal::seaweed_doubling(\n\
    \            range_lis_query_internal::make_permutation(values)\n        );\n\
    \        for (int& value : row) {\n            if (value == range_lis_query_internal::none)\
    \ value = _n;\n        }\n        _seaweed = WaveletMatrix<int>(row);\n    }\n\
    \n    int size() const {\n        return _n;\n    }\n\n    bool empty() const\
    \ {\n        return _n == 0;\n    }\n\n    // Returns the strict LIS length of\
    \ values[left, right).\n    int query(int left, int right) const {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        if (left == right) return\
    \ 0;\n        return right - left - _seaweed.range_freq(left, _n, right);\n  \
    \  }\n\n    int lis_length(int left, int right) const {\n        return query(left,\
    \ right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_DS_RANGE_QUERY_RANGE_LIS_QUERY_HPP\n"
  dependsOn:
  - ds/wavelet_matrix/wavelet_matrix.hpp
  isVerificationFile: false
  path: ds/range_query/range_lis_query.hpp
  requiredBy: []
  timestamp: '2026-07-16 18:47:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/range_lis_query.test.cpp
documentation_of: ds/range_query/range_lis_query.hpp
layout: document
title: Static Range LIS Query
---

## Overview

`RangeLisQuery<T>` preprocesses a static array and returns the length of its
strict longest increasing subsequence in any subarray `[left, right)`.
Equal values cannot both appear in the increasing subsequence.

The implementation converts the array to an equivalent permutation and builds
its semi-local LIS (seaweed) matrix. A wavelet matrix then counts the seaweeds
crossing each query rectangle.

## Requirements

`T` must support `<` as a strict weak ordering. The array is static after
construction. Duplicate values are supported.

## Complexity

| Operation | Time | Memory |
| --- | --- | --- |
| Construction | $O(N\log^2 N)$ | $O(N\log N)$ |
| Query | $O(\log N)$ | $O(1)$ |

## Methods

| Method | Complexity | Description |
| --- | --- | --- |
| `RangeLisQuery()` | $O(1)$ | Constructs an empty structure. |
| `explicit RangeLisQuery(const std::vector<T>& values)` | $O(N\log^2 N)$ | Builds the structure for `values`. |
| `int query(int left, int right) const` | $O(\log N)$ | Returns the strict LIS length in `[left, right)`. |
| `int lis_length(int left, int right) const` | $O(\log N)$ | Alias of `query`. |
| `int size() const` | $O(1)$ | Returns the array size. |
| `bool empty() const` | $O(1)$ | Returns whether the array is empty. |

## Example

```cpp
#include "ds/range_query/range_lis_query.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {3, 1, 2, 2, 4};
    m1une::ds::RangeLisQuery<int> lis(values);

    std::cout << lis.query(0, 5) << "\n"; // 3: 1, 2, 4
    std::cout << lis.query(1, 4) << "\n"; // 2: 1, 2
}
```
