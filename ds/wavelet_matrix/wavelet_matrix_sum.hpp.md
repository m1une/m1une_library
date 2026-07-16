---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/static_rectangle_sum.hpp
    title: Static Rectangle Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_rectangle_sum.test.cpp
    title: verify/ds/range_query/static_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/wavelet_matrix/wavelet_matrix_sum.test.cpp
    title: verify/ds/wavelet_matrix/wavelet_matrix_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/wavelet_matrix/wavelet_matrix_sum.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstdint>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#if defined(__AVX2__) || defined(__BMI2__)\n\
    #include <immintrin.h>\n#endif\n\nnamespace m1une {\nnamespace ds {\n\n// A static\
    \ wavelet matrix with additive weights.\n// By default, each value is also used\
    \ as its weight.\ntemplate <std::integral T, typename Sum = T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrixSum {\n    using value_type = T;\n    using sum_type\
    \ = Sum;\n    using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n\
    \    static constexpr int value_bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
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
    \ _matrix;\n    std::vector<int> _zero_count;\n    std::vector<std::vector<Sum>>\
    \ _zero_prefix;\n    std::vector<Sum> _original_prefix;\n    std::vector<Sum>\
    \ _final_prefix;\n\n    static unsigned_type encode(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static T decode(unsigned_type\
    \ key) {\n        unsigned_type bits = key ^ sign_mask;\n        if constexpr\
    \ (std::signed_integral<T>) {\n            return std::bit_cast<T>(bits);\n  \
    \      } else {\n            return bits;\n        }\n    }\n\n    bool bit(unsigned_type\
    \ value, int level) const {\n        return (value >> (_log - 1 - level)) & unsigned_type(1);\n\
    \    }\n\n    static std::uint64_t extract_bits(\n        const unsigned_type*\
    \ values,\n        int count,\n        int shift\n    ) {\n        std::uint64_t\
    \ result = 0;\n        int i = 0;\n#if defined(__AVX2__)\n        if constexpr\
    \ (sizeof(unsigned_type) == 8) {\n            __m128i left = _mm_cvtsi32_si128(63\
    \ - shift);\n            for (; i + 4 <= count; i += 4) {\n                __m256i\
    \ data = _mm256_loadu_si256(\n                    reinterpret_cast<const __m256i*>(values\
    \ + i)\n                );\n                data = _mm256_sll_epi64(data, left);\n\
    \                int mask = _mm256_movemask_pd(_mm256_castsi256_pd(data));\n \
    \               result |= std::uint64_t(mask) << i;\n            }\n        }\
    \ else if constexpr (sizeof(unsigned_type) == 4) {\n            __m128i left =\
    \ _mm_cvtsi32_si128(31 - shift);\n            for (; i + 8 <= count; i += 8) {\n\
    \                __m256i data = _mm256_loadu_si256(\n                    reinterpret_cast<const\
    \ __m256i*>(values + i)\n                );\n                data = _mm256_sll_epi32(data,\
    \ left);\n                int mask = _mm256_movemask_ps(_mm256_castsi256_ps(data));\n\
    \                result |= std::uint64_t(mask) << i;\n            }\n        }\n\
    #endif\n        for (; i < count; i++) {\n            result |= std::uint64_t((values[i]\
    \ >> shift) & unsigned_type(1))\n                      << i;\n        }\n    \
    \    return result;\n    }\n\n    Sum zero_sum(int level, int l, int r) const\
    \ {\n        return _zero_prefix[level][r] - _zero_prefix[level][l];\n    }\n\n\
    \    Sum sum_less_encoded(int l, int r, unsigned_type upper) const {\n       \
    \ if (_n == 0 || upper <= _min_key) return Sum{};\n        if (upper > _max_key)\
    \ {\n            return _original_prefix[r] - _original_prefix[l];\n        }\n\
    \n        Sum result{};\n        for (int level = 0; level < _log; level++) {\n\
    \            int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(upper, level)) {\n                result = result + zero_sum(level,\
    \ l, r);\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return result;\n    }\n\n    int count_less_encoded(int\
    \ l, int r, unsigned_type upper) const {\n        if (_n == 0 || upper <= _min_key)\
    \ return 0;\n        if (upper > _max_key) return r - l;\n\n        int result\
    \ = 0;\n        for (int level = 0; level < _log; level++) {\n            int\
    \ l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(upper, level)) {\n                result += (r - l) - (r1\
    \ - l1);\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return result;\n    }\n\n    void build(const\
    \ std::vector<T>& values, const std::vector<Sum>& weights) {\n        assert(values.size()\
    \ == weights.size());\n\n        std::vector<unsigned_type> current_keys(_n);\n\
    \        std::vector<unsigned_type> next_keys(_n);\n        std::vector<Sum> current_weights(weights);\n\
    \        std::vector<Sum> next_weights(_n);\n        for (int i = 0; i < _n; i++)\
    \ current_keys[i] = encode(values[i]);\n\n        _original_prefix.assign(std::size_t(_n)\
    \ + 1, Sum{});\n        for (int i = 0; i < _n; i++) {\n            _original_prefix[i\
    \ + 1] = _original_prefix[i] + weights[i];\n        }\n        if (_n == 0) {\n\
    \            _final_prefix.assign(1, Sum{});\n            return;\n        }\n\
    \n        _min_key = current_keys[0];\n        _max_key = current_keys[0];\n \
    \       for (unsigned_type key : current_keys) {\n            if (key < _min_key)\
    \ _min_key = key;\n            if (_max_key < key) _max_key = key;\n        }\n\
    \        _log = int(std::bit_width(unsigned_type(_min_key ^ _max_key)));\n   \
    \     if (_log != value_bit_width) {\n            _key_prefix = unsigned_type((_min_key\
    \ >> _log) << _log);\n        }\n        _zero_count.assign(_log, 0);\n\n    \
    \    _matrix.reserve(_log);\n        _zero_prefix.reserve(_log);\n        for\
    \ (int level = 0; level < _log; level++) {\n            _matrix.emplace_back(_n);\n\
    \            _zero_prefix.emplace_back(std::size_t(_n) + 1, Sum{});\n        \
    \    BitVector& bit_vector = _matrix.back();\n            int shift = _log - 1\
    \ - level;\n            int zeros = 0;\n            for (int base = 0; base <\
    \ _n; base += 64) {\n                int count = std::min(64, _n - base);\n  \
    \              std::uint64_t word = extract_bits(\n                    current_keys.data()\
    \ + base,\n                    count,\n                    shift\n           \
    \     );\n                bit_vector.bits[std::size_t(base) >> 6] = word;\n  \
    \              zeros += count - std::popcount(word);\n            }\n        \
    \    bit_vector.build();\n\n            std::vector<Sum>& prefix = _zero_prefix.back();\n\
    \            for (int base = 0; base < _n; base += 64) {\n                int\
    \ count = std::min(64, _n - base);\n                std::uint64_t ones = bit_vector.bits[std::size_t(base)\
    \ >> 6];\n                for (int offset = 0; offset < count; offset++) {\n \
    \                   int i = base + offset;\n                    prefix[i + 1]\
    \ = prefix[i];\n                    if (((ones >> offset) & 1) == 0) {\n     \
    \                   prefix[i + 1] = prefix[i + 1] + current_weights[i];\n    \
    \                }\n                }\n            }\n\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (int base = 0; base < _n; base += 64) {\n                int\
    \ count = std::min(64, _n - base);\n                std::uint64_t ones = bit_vector.bits[std::size_t(base)\
    \ >> 6];\n                std::uint64_t valid = count == 64\n                \
    \                          ? ~std::uint64_t(0)\n                             \
    \             : (std::uint64_t(1) << count) - 1;\n                std::uint64_t\
    \ zeroes = (~ones) & valid;\n                while (zeroes != 0) {\n         \
    \           int offset = std::countr_zero(zeroes);\n                    next_keys[zero_pos]\
    \ = current_keys[base + offset];\n                    next_weights[zero_pos] =\
    \ current_weights[base + offset];\n                    zero_pos++;\n         \
    \           zeroes &= zeroes - 1;\n                }\n                while (ones\
    \ != 0) {\n                    int offset = std::countr_zero(ones);\n        \
    \            next_keys[one_pos] = current_keys[base + offset];\n             \
    \       next_weights[one_pos] = current_weights[base + offset];\n            \
    \        one_pos++;\n                    ones &= ones - 1;\n                }\n\
    \            }\n            current_keys.swap(next_keys);\n            current_weights.swap(next_weights);\n\
    \        }\n\n        _final_prefix.assign(std::size_t(_n) + 1, Sum{});\n    \
    \    for (int i = 0; i < _n; i++) {\n            _final_prefix[i + 1] = _final_prefix[i]\
    \ + current_weights[i];\n        }\n    }\n\n   public:\n    WaveletMatrixSum()\n\
    \        : _n(0),\n          _log(0),\n          _key_prefix(0),\n          _min_key(0),\n\
    \          _max_key(0),\n          _original_prefix(1, Sum{}),\n          _final_prefix(1,\
    \ Sum{}) {}\n\n    explicit WaveletMatrixSum(const std::vector<T>& values)\n \
    \       requires std::convertible_to<T, Sum>\n        : _n(int(values.size())),\n\
    \          _log(0),\n          _key_prefix(0),\n          _min_key(0),\n     \
    \     _max_key(0) {\n        std::vector<Sum> weights;\n        weights.reserve(values.size());\n\
    \        for (T value : values) weights.push_back(static_cast<Sum>(value));\n\
    \        build(values, weights);\n    }\n\n    WaveletMatrixSum(\n        const\
    \ std::vector<T>& values,\n        const std::vector<Sum>& weights\n    ) : _n(int(values.size())),\n\
    \        _log(0),\n        _key_prefix(0),\n        _min_key(0),\n        _max_key(0)\
    \ {\n        build(values, weights);\n    }\n\n    int size() const {\n      \
    \  return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n  \
    \  }\n\n    T access(int p) const {\n        assert(0 <= p && p < _n);\n     \
    \   unsigned_type key = _key_prefix;\n        for (int level = 0; level < _log;\
    \ level++) {\n            int ones_before = _matrix[level].rank1(p);\n       \
    \     bool one = _matrix[level].get(p);\n            if (one) {\n            \
    \    key |= unsigned_type(1) << (_log - 1 - level);\n                p = _zero_count[level]\
    \ + ones_before;\n            } else {\n                p -= ones_before;\n  \
    \          }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ p) const {\n        return access(p);\n    }\n\n    int rank(T value, int r)\
    \ const {\n        assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n\
    \    }\n\n    int rank(T value, int l, int r) const {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        unsigned_type key = encode(value);\n        if\
    \ (_n == 0 || key < _min_key || _max_key < key) return 0;\n        for (int level\
    \ = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            if (bit(key, level))\
    \ {\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = _key_prefix;\n\
    \        for (int level = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
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
    \ }\n\n    Sum range_sum(int l, int r) const {\n        assert(0 <= l && l <=\
    \ r && r <= _n);\n        return _original_prefix[r] - _original_prefix[l];\n\
    \    }\n\n    Sum range_sum(int l, int r, T upper) const {\n        assert(0 <=\
    \ l && l <= r && r <= _n);\n        return sum_less_encoded(l, r, encode(upper));\n\
    \    }\n\n    Sum range_sum(int l, int r, T lower, T upper) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        if (upper <= lower) return Sum{};\n   \
    \     return range_sum(l, r, upper) - range_sum(l, r, lower);\n    }\n\n    Sum\
    \ sum_k_smallest(int l, int r, int k) const {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        assert(0 <= k && k <= r - l);\n        Sum result{};\n\
    \        for (int level = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            int l0 = l - l1;\n\
    \            int r0 = r - r1;\n            int zeros = r0 - l0;\n            if\
    \ (k < zeros) {\n                l = l0;\n                r = r0;\n          \
    \  } else {\n                result = result + zero_sum(level, l, r);\n      \
    \          k -= zeros;\n                l = _zero_count[level] + l1;\n       \
    \         r = _zero_count[level] + r1;\n            }\n        }\n        return\
    \ result + (_final_prefix[l + k] - _final_prefix[l]);\n    }\n\n    Sum sum_k_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k <= r - l);\n        return range_sum(l, r) - sum_k_smallest(l,\
    \ r, r - l - k);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_SUM_HPP\n#define M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_SUM_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <concepts>\n\
    #include <cstdint>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#if defined(__AVX2__) || defined(__BMI2__)\n\
    #include <immintrin.h>\n#endif\n\nnamespace m1une {\nnamespace ds {\n\n// A static\
    \ wavelet matrix with additive weights.\n// By default, each value is also used\
    \ as its weight.\ntemplate <std::integral T, typename Sum = T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrixSum {\n    using value_type = T;\n    using sum_type\
    \ = Sum;\n    using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n\
    \    static constexpr int value_bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
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
    \ _matrix;\n    std::vector<int> _zero_count;\n    std::vector<std::vector<Sum>>\
    \ _zero_prefix;\n    std::vector<Sum> _original_prefix;\n    std::vector<Sum>\
    \ _final_prefix;\n\n    static unsigned_type encode(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static T decode(unsigned_type\
    \ key) {\n        unsigned_type bits = key ^ sign_mask;\n        if constexpr\
    \ (std::signed_integral<T>) {\n            return std::bit_cast<T>(bits);\n  \
    \      } else {\n            return bits;\n        }\n    }\n\n    bool bit(unsigned_type\
    \ value, int level) const {\n        return (value >> (_log - 1 - level)) & unsigned_type(1);\n\
    \    }\n\n    static std::uint64_t extract_bits(\n        const unsigned_type*\
    \ values,\n        int count,\n        int shift\n    ) {\n        std::uint64_t\
    \ result = 0;\n        int i = 0;\n#if defined(__AVX2__)\n        if constexpr\
    \ (sizeof(unsigned_type) == 8) {\n            __m128i left = _mm_cvtsi32_si128(63\
    \ - shift);\n            for (; i + 4 <= count; i += 4) {\n                __m256i\
    \ data = _mm256_loadu_si256(\n                    reinterpret_cast<const __m256i*>(values\
    \ + i)\n                );\n                data = _mm256_sll_epi64(data, left);\n\
    \                int mask = _mm256_movemask_pd(_mm256_castsi256_pd(data));\n \
    \               result |= std::uint64_t(mask) << i;\n            }\n        }\
    \ else if constexpr (sizeof(unsigned_type) == 4) {\n            __m128i left =\
    \ _mm_cvtsi32_si128(31 - shift);\n            for (; i + 8 <= count; i += 8) {\n\
    \                __m256i data = _mm256_loadu_si256(\n                    reinterpret_cast<const\
    \ __m256i*>(values + i)\n                );\n                data = _mm256_sll_epi32(data,\
    \ left);\n                int mask = _mm256_movemask_ps(_mm256_castsi256_ps(data));\n\
    \                result |= std::uint64_t(mask) << i;\n            }\n        }\n\
    #endif\n        for (; i < count; i++) {\n            result |= std::uint64_t((values[i]\
    \ >> shift) & unsigned_type(1))\n                      << i;\n        }\n    \
    \    return result;\n    }\n\n    Sum zero_sum(int level, int l, int r) const\
    \ {\n        return _zero_prefix[level][r] - _zero_prefix[level][l];\n    }\n\n\
    \    Sum sum_less_encoded(int l, int r, unsigned_type upper) const {\n       \
    \ if (_n == 0 || upper <= _min_key) return Sum{};\n        if (upper > _max_key)\
    \ {\n            return _original_prefix[r] - _original_prefix[l];\n        }\n\
    \n        Sum result{};\n        for (int level = 0; level < _log; level++) {\n\
    \            int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(upper, level)) {\n                result = result + zero_sum(level,\
    \ l, r);\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return result;\n    }\n\n    int count_less_encoded(int\
    \ l, int r, unsigned_type upper) const {\n        if (_n == 0 || upper <= _min_key)\
    \ return 0;\n        if (upper > _max_key) return r - l;\n\n        int result\
    \ = 0;\n        for (int level = 0; level < _log; level++) {\n            int\
    \ l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(upper, level)) {\n                result += (r - l) - (r1\
    \ - l1);\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return result;\n    }\n\n    void build(const\
    \ std::vector<T>& values, const std::vector<Sum>& weights) {\n        assert(values.size()\
    \ == weights.size());\n\n        std::vector<unsigned_type> current_keys(_n);\n\
    \        std::vector<unsigned_type> next_keys(_n);\n        std::vector<Sum> current_weights(weights);\n\
    \        std::vector<Sum> next_weights(_n);\n        for (int i = 0; i < _n; i++)\
    \ current_keys[i] = encode(values[i]);\n\n        _original_prefix.assign(std::size_t(_n)\
    \ + 1, Sum{});\n        for (int i = 0; i < _n; i++) {\n            _original_prefix[i\
    \ + 1] = _original_prefix[i] + weights[i];\n        }\n        if (_n == 0) {\n\
    \            _final_prefix.assign(1, Sum{});\n            return;\n        }\n\
    \n        _min_key = current_keys[0];\n        _max_key = current_keys[0];\n \
    \       for (unsigned_type key : current_keys) {\n            if (key < _min_key)\
    \ _min_key = key;\n            if (_max_key < key) _max_key = key;\n        }\n\
    \        _log = int(std::bit_width(unsigned_type(_min_key ^ _max_key)));\n   \
    \     if (_log != value_bit_width) {\n            _key_prefix = unsigned_type((_min_key\
    \ >> _log) << _log);\n        }\n        _zero_count.assign(_log, 0);\n\n    \
    \    _matrix.reserve(_log);\n        _zero_prefix.reserve(_log);\n        for\
    \ (int level = 0; level < _log; level++) {\n            _matrix.emplace_back(_n);\n\
    \            _zero_prefix.emplace_back(std::size_t(_n) + 1, Sum{});\n        \
    \    BitVector& bit_vector = _matrix.back();\n            int shift = _log - 1\
    \ - level;\n            int zeros = 0;\n            for (int base = 0; base <\
    \ _n; base += 64) {\n                int count = std::min(64, _n - base);\n  \
    \              std::uint64_t word = extract_bits(\n                    current_keys.data()\
    \ + base,\n                    count,\n                    shift\n           \
    \     );\n                bit_vector.bits[std::size_t(base) >> 6] = word;\n  \
    \              zeros += count - std::popcount(word);\n            }\n        \
    \    bit_vector.build();\n\n            std::vector<Sum>& prefix = _zero_prefix.back();\n\
    \            for (int base = 0; base < _n; base += 64) {\n                int\
    \ count = std::min(64, _n - base);\n                std::uint64_t ones = bit_vector.bits[std::size_t(base)\
    \ >> 6];\n                for (int offset = 0; offset < count; offset++) {\n \
    \                   int i = base + offset;\n                    prefix[i + 1]\
    \ = prefix[i];\n                    if (((ones >> offset) & 1) == 0) {\n     \
    \                   prefix[i + 1] = prefix[i + 1] + current_weights[i];\n    \
    \                }\n                }\n            }\n\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (int base = 0; base < _n; base += 64) {\n                int\
    \ count = std::min(64, _n - base);\n                std::uint64_t ones = bit_vector.bits[std::size_t(base)\
    \ >> 6];\n                std::uint64_t valid = count == 64\n                \
    \                          ? ~std::uint64_t(0)\n                             \
    \             : (std::uint64_t(1) << count) - 1;\n                std::uint64_t\
    \ zeroes = (~ones) & valid;\n                while (zeroes != 0) {\n         \
    \           int offset = std::countr_zero(zeroes);\n                    next_keys[zero_pos]\
    \ = current_keys[base + offset];\n                    next_weights[zero_pos] =\
    \ current_weights[base + offset];\n                    zero_pos++;\n         \
    \           zeroes &= zeroes - 1;\n                }\n                while (ones\
    \ != 0) {\n                    int offset = std::countr_zero(ones);\n        \
    \            next_keys[one_pos] = current_keys[base + offset];\n             \
    \       next_weights[one_pos] = current_weights[base + offset];\n            \
    \        one_pos++;\n                    ones &= ones - 1;\n                }\n\
    \            }\n            current_keys.swap(next_keys);\n            current_weights.swap(next_weights);\n\
    \        }\n\n        _final_prefix.assign(std::size_t(_n) + 1, Sum{});\n    \
    \    for (int i = 0; i < _n; i++) {\n            _final_prefix[i + 1] = _final_prefix[i]\
    \ + current_weights[i];\n        }\n    }\n\n   public:\n    WaveletMatrixSum()\n\
    \        : _n(0),\n          _log(0),\n          _key_prefix(0),\n          _min_key(0),\n\
    \          _max_key(0),\n          _original_prefix(1, Sum{}),\n          _final_prefix(1,\
    \ Sum{}) {}\n\n    explicit WaveletMatrixSum(const std::vector<T>& values)\n \
    \       requires std::convertible_to<T, Sum>\n        : _n(int(values.size())),\n\
    \          _log(0),\n          _key_prefix(0),\n          _min_key(0),\n     \
    \     _max_key(0) {\n        std::vector<Sum> weights;\n        weights.reserve(values.size());\n\
    \        for (T value : values) weights.push_back(static_cast<Sum>(value));\n\
    \        build(values, weights);\n    }\n\n    WaveletMatrixSum(\n        const\
    \ std::vector<T>& values,\n        const std::vector<Sum>& weights\n    ) : _n(int(values.size())),\n\
    \        _log(0),\n        _key_prefix(0),\n        _min_key(0),\n        _max_key(0)\
    \ {\n        build(values, weights);\n    }\n\n    int size() const {\n      \
    \  return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n  \
    \  }\n\n    T access(int p) const {\n        assert(0 <= p && p < _n);\n     \
    \   unsigned_type key = _key_prefix;\n        for (int level = 0; level < _log;\
    \ level++) {\n            int ones_before = _matrix[level].rank1(p);\n       \
    \     bool one = _matrix[level].get(p);\n            if (one) {\n            \
    \    key |= unsigned_type(1) << (_log - 1 - level);\n                p = _zero_count[level]\
    \ + ones_before;\n            } else {\n                p -= ones_before;\n  \
    \          }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ p) const {\n        return access(p);\n    }\n\n    int rank(T value, int r)\
    \ const {\n        assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n\
    \    }\n\n    int rank(T value, int l, int r) const {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        unsigned_type key = encode(value);\n        if\
    \ (_n == 0 || key < _min_key || _max_key < key) return 0;\n        for (int level\
    \ = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            if (bit(key, level))\
    \ {\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = _key_prefix;\n\
    \        for (int level = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
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
    \ }\n\n    Sum range_sum(int l, int r) const {\n        assert(0 <= l && l <=\
    \ r && r <= _n);\n        return _original_prefix[r] - _original_prefix[l];\n\
    \    }\n\n    Sum range_sum(int l, int r, T upper) const {\n        assert(0 <=\
    \ l && l <= r && r <= _n);\n        return sum_less_encoded(l, r, encode(upper));\n\
    \    }\n\n    Sum range_sum(int l, int r, T lower, T upper) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        if (upper <= lower) return Sum{};\n   \
    \     return range_sum(l, r, upper) - range_sum(l, r, lower);\n    }\n\n    Sum\
    \ sum_k_smallest(int l, int r, int k) const {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        assert(0 <= k && k <= r - l);\n        Sum result{};\n\
    \        for (int level = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            int l0 = l - l1;\n\
    \            int r0 = r - r1;\n            int zeros = r0 - l0;\n            if\
    \ (k < zeros) {\n                l = l0;\n                r = r0;\n          \
    \  } else {\n                result = result + zero_sum(level, l, r);\n      \
    \          k -= zeros;\n                l = _zero_count[level] + l1;\n       \
    \         r = _zero_count[level] + r1;\n            }\n        }\n        return\
    \ result + (_final_prefix[l + k] - _final_prefix[l]);\n    }\n\n    Sum sum_k_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k <= r - l);\n        return range_sum(l, r) - sum_k_smallest(l,\
    \ r, r - l - k);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/wavelet_matrix/wavelet_matrix_sum.hpp
  requiredBy:
  - ds/range_query/static_rectangle_sum.hpp
  timestamp: '2026-07-16 18:47:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/static_rectangle_sum.test.cpp
  - verify/ds/wavelet_matrix/wavelet_matrix_sum.test.cpp
documentation_of: ds/wavelet_matrix/wavelet_matrix_sum.hpp
layout: document
title: Wavelet Matrix with Sums
---

## Overview

`m1une::ds::WaveletMatrixSum` is a static wavelet matrix that stores an
additive weight for every value. It supports range order statistics together
with:

* total weight in an index range,
* total weight for values below a bound or inside a value interval, and
* total weight of the smallest or largest `k` values.

By default, each value is also its weight, producing ordinary sums of selected
values. A separate weight vector can instead represent costs, counts, or other
additive data.

Signed values are ordered across their full type range by an internal sign-bit
transform. No coordinate compression is required.

Levels are packed and stable-partitioned one machine word at a time, avoiding
an unpredictable branch for every value. AVX2 bit extraction and BMI2 rank
masking are selected when the corresponding instruction sets are enabled at
compile time, with compact scalar fallbacks otherwise.

## Template Parameters

* `T`: A non-`bool` integral value type used for ordering.
* `Sum`: The weight and sum type. It defaults to `T`.

`Sum{}` must be the additive identity, and `Sum` must support addition and
subtraction. Choose a sufficiently wide type because arithmetic overflow is not
checked.

Let $B$ be the bit width of `T`. Let $L$ be the bit width of the exclusive-or
of the minimum and maximum internally encoded values. Leading bits shared by
all values are omitted, so $0 \le L \le B$ and equal values have $L = 0$.

## Construction

* `WaveletMatrixSum()`: creates an empty matrix.
* `WaveletMatrixSum(const vector<T>& values)`: uses each value as its own
  weight. This requires `T` to be convertible to `Sum`.
* `WaveletMatrixSum(const vector<T>& values, const vector<Sum>& weights)`:
  associates `weights[i]` with `values[i]`.

The value and weight vectors must have equal lengths. Construction takes
$O(NL + N)$ time and $O(NL + N)$ storage.

## Methods

All index and value intervals are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the sequence length. | $O(1)$ |
| `bool empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int p)` | Returns the value at index `p`. | $O(L)$ |
| `T operator[](int p)` | Equivalent to `access(p)`. | $O(L)$ |
| `int rank(T x, int r)` | Counts occurrences of `x` in `[0, r)`. | $O(L)$ |
| `int rank(T x, int l, int r)` | Counts occurrences of `x` in `[l, r)`. | $O(L)$ |
| `T kth_smallest(int l, int r, int k)` | Returns the zero-based `k`-th smallest value. | $O(L)$ |
| `T kth_largest(int l, int r, int k)` | Returns the zero-based `k`-th largest value. | $O(L)$ |
| `int range_freq(int l, int r, T upper)` | Counts values less than `upper`. | $O(L)$ |
| `int range_freq(int l, int r, T lower, T upper)` | Counts values in `[lower, upper)`. | $O(L)$ |
| `optional<T> prev_value(int l, int r, T upper)` | Returns the greatest value less than `upper`, or `nullopt`. | $O(L)$ |
| `optional<T> next_value(int l, int r, T lower)` | Returns the smallest value at least `lower`, or `nullopt`. | $O(L)$ |
| `Sum range_sum(int l, int r)` | Returns the total weight in `[l, r)`. | $O(1)$ |
| `Sum range_sum(int l, int r, T upper)` | Sums weights whose values are less than `upper`. | $O(L)$ |
| `Sum range_sum(int l, int r, T lower, T upper)` | Sums weights whose values are in `[lower, upper)`. | $O(L)$ |
| `Sum sum_k_smallest(int l, int r, int k)` | Sums the weights of the smallest `k` values. | $O(L)$ |
| `Sum sum_k_largest(int l, int r, int k)` | Sums the weights of the largest `k` values. | $O(L)$ |

The `k` used by sum methods may range from `0` through `r - l`, inclusive. If
equal values have different weights, `sum_k_smallest` selects ties in original
index order, while `sum_k_largest` selects them in reverse original index order.

## Example

```cpp
#include "ds/wavelet_matrix/wavelet_matrix_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, -2, 8, 5, 1};
    m1une::ds::WaveletMatrixSum<long long> matrix(values);

    std::cout << matrix.range_sum(0, 5, 0, 6) << "\n"; // 11
    std::cout << matrix.sum_k_smallest(0, 5, 3) << "\n"; // 4

    std::vector<int> keys = {4, 1, 4, 2};
    std::vector<long long> weights = {10, 20, 30, 40};
    m1une::ds::WaveletMatrixSum<int, long long> weighted(keys, weights);

    std::cout << weighted.range_sum(0, 4, 2, 5) << "\n"; // 80
}
```
