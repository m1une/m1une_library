---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/range_lis_query.hpp
    title: Static Range LIS Query
  - icon: ':heavy_check_mark:'
    path: ds/range_query/static_range_count_distinct.hpp
    title: Static Range Count Distinct
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_lis_query.test.cpp
    title: verify/ds/range_query/range_lis_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_range_count_distinct.test.cpp
    title: verify/ds/range_query/static_range_count_distinct.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/wavelet_matrix/wavelet_matrix.test.cpp
    title: verify/ds/wavelet_matrix/wavelet_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/wavelet_matrix/wavelet_matrix.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n\
    #include <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#if defined(__AVX2__) || defined(__BMI2__)\n#include <immintrin.h>\n\
    #endif\n\nnamespace m1une {\nnamespace ds {\n\n// A static wavelet matrix for\
    \ integral values.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
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
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_HPP\n#define M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <concepts>\n\
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
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/wavelet_matrix/wavelet_matrix.hpp
  requiredBy:
  - ds/range_query/range_lis_query.hpp
  - ds/range_query/static_range_count_distinct.hpp
  timestamp: '2026-07-16 18:47:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/static_range_count_distinct.test.cpp
  - verify/ds/range_query/range_lis_query.test.cpp
  - verify/ds/wavelet_matrix/wavelet_matrix.test.cpp
documentation_of: ds/wavelet_matrix/wavelet_matrix.hpp
layout: document
title: Wavelet Matrix
---

## Overview

`m1une::ds::WaveletMatrix` is a static data structure for integral sequences.
It supports access, occurrence counting, range order statistics, range
frequency queries, and predecessor/successor searches.

Each level uses a packed bitvector with constant-time prefix rank. Signed values
are ordered by flipping their sign bit internally, so negative values and the
full range of the selected integer type work without coordinate compression.
Leading bits shared by every value are omitted.

Construction packs each level one machine word at a time and performs stable
partitioning by iterating the packed zero and one masks. This avoids an
unpredictable branch for every input value. AVX2 is used for bit extraction and
BMI2 for rank masking when those instruction sets are enabled at compile time;
otherwise the same compact bit and prefix arrays use portable scalar
operations.

## Template Parameter

* `T`: A non-`bool` integral type.

Let $B$ be the bit width of `T`, such as 32 for `int` or 64 for `long long`.
Let $L$ be the bit width of the exclusive-or of the minimum and maximum
internally encoded values. Thus $0 \le L \le B$; equal values have $L = 0$.

## Construction

* `WaveletMatrix()`: creates an empty matrix.
* `WaveletMatrix(const std::vector<T>& values)`: builds from `values`.

Construction takes $O(NL + N)$ time and $O(NL)$ bits for level bitvectors,
plus rank metadata and $O(N)$ temporary storage.

## Methods

All index ranges are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the sequence length. | $O(1)$ |
| `bool empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int p)` | Returns the value at index `p`. | $O(L)$ |
| `T operator[](int p)` | Equivalent to `access(p)`. | $O(L)$ |
| `int rank(T x, int r)` | Counts occurrences of `x` in `[0, r)`. | $O(L)$ |
| `int rank(T x, int l, int r)` | Counts occurrences of `x` in `[l, r)`. | $O(L)$ |
| `T kth_smallest(int l, int r, int k)` | Returns the zero-based `k`-th smallest value in `[l, r)`. | $O(L)$ |
| `T kth_largest(int l, int r, int k)` | Returns the zero-based `k`-th largest value in `[l, r)`. | $O(L)$ |
| `int range_freq(int l, int r, T upper)` | Counts values less than `upper` in `[l, r)`. | $O(L)$ |
| `int range_freq(int l, int r, T lower, T upper)` | Counts values in `[lower, upper)` within `[l, r)`. | $O(L)$ |
| `optional<T> prev_value(int l, int r, T upper)` | Returns the greatest value less than `upper`, or `nullopt`. | $O(L)$ |
| `optional<T> next_value(int l, int r, T lower)` | Returns the smallest value at least `lower`, or `nullopt`. | $O(L)$ |

`kth_smallest` and `kth_largest` require `0 <= k < r - l`.

For range sums or weights attached to values, use `WaveletMatrixSum`.

## Example

```cpp
#include "ds/wavelet_matrix/wavelet_matrix.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, -2, 8, 5, 1};
    m1une::ds::WaveletMatrix<long long> matrix(values);

    std::cout << matrix.kth_smallest(0, 5, 1) << "\n";  // 1
    std::cout << matrix.rank(5, 0, 4) << "\n";          // 2
    std::cout << matrix.range_freq(1, 5, 0, 6) << "\n"; // 3

    auto predecessor = matrix.prev_value(0, 5, 5);
    if (predecessor) std::cout << *predecessor << "\n"; // 1
}
```
