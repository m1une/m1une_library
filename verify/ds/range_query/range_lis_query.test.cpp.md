---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/range_lis_query.hpp
    title: Static Range LIS Query
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix.hpp
    title: Wavelet Matrix
  - icon: ':question:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_lis_query
    links:
    - https://judge.yosupo.jp/problem/static_range_lis_query
  bundledCode: "#line 1 \"verify/ds/range_query/range_lis_query.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_lis_query\"\n\n#line\
    \ 1 \"ds/range_query/range_lis_query.hpp\"\n\n\n\n#line 1 \"ds/range_query/wavelet_matrix.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n\
    #include <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// A static wavelet\
    \ matrix for integral values.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct WaveletMatrix {\n    using value_type = T;\n    using unsigned_type\
    \ = std::make_unsigned_t<T>;\n\n   private:\n    static constexpr int bit_width\
    \ = std::numeric_limits<unsigned_type>::digits;\n    static constexpr unsigned_type\
    \ sign_mask = [] {\n        if constexpr (std::signed_integral<T>) {\n       \
    \     return unsigned_type(1) << (bit_width - 1);\n        } else {\n        \
    \    return unsigned_type(0);\n        }\n    }();\n\n    struct BitVector {\n\
    \        std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\n\
    \        BitVector() = default;\n\n        explicit BitVector(int n)\n       \
    \     : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
    \ + 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >>\
    \ 6] |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n \
    \           for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     bool get(int p) const {\n            return (bits[std::size_t(p) >> 6] >>\
    \ (p & 63)) & 1;\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    int _n;\n    std::vector<BitVector> _matrix;\n    std::vector<int>\
    \ _zero_count;\n\n    static unsigned_type encode(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static T decode(unsigned_type\
    \ key) {\n        unsigned_type bits = key ^ sign_mask;\n        if constexpr\
    \ (std::signed_integral<T>) {\n            return std::bit_cast<T>(bits);\n  \
    \      } else {\n            return bits;\n        }\n    }\n\n    static bool\
    \ bit(unsigned_type value, int level) {\n        return (value >> (bit_width -\
    \ 1 - level)) & unsigned_type(1);\n    }\n\n    int count_less_encoded(int l,\
    \ int r, unsigned_type upper) const {\n        int result = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(upper, level))\
    \ {\n                result += r0 - l0;\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n   public:\n    WaveletMatrix()\
    \ : _n(0), _matrix(bit_width), _zero_count(bit_width, 0) {}\n\n    explicit WaveletMatrix(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())),\n          _matrix(),\n\
    \          _zero_count(bit_width, 0) {\n        std::vector<unsigned_type> current(_n);\n\
    \        std::vector<unsigned_type> next(_n);\n        for (int i = 0; i < _n;\
    \ i++) current[i] = encode(values[i]);\n\n        _matrix.reserve(bit_width);\n\
    \        for (int level = 0; level < bit_width; level++) {\n            _matrix.emplace_back(_n);\n\
    \            for (int i = 0; i < _n; i++) {\n                if (bit(current[i],\
    \ level)) _matrix.back().set(i);\n            }\n            _matrix.back().build();\n\
    \n            int zeros = _matrix.back().rank0(_n);\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (unsigned_type value : current) {\n                if (bit(value,\
    \ level)) {\n                    next[one_pos++] = value;\n                } else\
    \ {\n                    next[zero_pos++] = value;\n                }\n      \
    \      }\n            current.swap(next);\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    T access(int p) const {\n        assert(0 <= p && p <\
    \ _n);\n        unsigned_type key = 0;\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            bool one = _matrix[level].get(p);\n            if (one)\
    \ {\n                key |= unsigned_type(1) << (bit_width - 1 - level);\n   \
    \             p = _zero_count[level] + _matrix[level].rank1(p);\n            }\
    \ else {\n                p = _matrix[level].rank0(p);\n            }\n      \
    \  }\n        return decode(key);\n    }\n\n    T operator[](int p) const {\n\
    \        return access(p);\n    }\n\n    int rank(T value, int r) const {\n  \
    \      assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n    }\n\n\
    \    int rank(T value, int l, int r) const {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        unsigned_type key = encode(value);\n        for (int level\
    \ = 0; level < bit_width; level++) {\n            if (bit(key, level)) {\n   \
    \             l = _zero_count[level] + _matrix[level].rank1(l);\n            \
    \    r = _zero_count[level] + _matrix[level].rank1(r);\n            } else {\n\
    \                l = _matrix[level].rank0(l);\n                r = _matrix[level].rank0(r);\n\
    \            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            int zeros = r0 - l0;\n\
    \            if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                l = _zero_count[level] + _matrix[level].rank1(l);\n\
    \                r = _zero_count[level] + _matrix[level].rank1(r);\n         \
    \   }\n        }\n        return decode(key);\n    }\n\n    T kth_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        return kth_smallest(l, r, r - l -\
    \ 1 - k);\n    }\n\n    int range_freq(int l, int r, T upper) const {\n      \
    \  assert(0 <= l && l <= r && r <= _n);\n        return count_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    int range_freq(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return 0;\n        return range_freq(l, r, upper) - range_freq(l, r,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, upper);\n        if (count == 0) return std::nullopt;\n        return kth_smallest(l,\
    \ r, count - 1);\n    }\n\n    std::optional<T> next_value(int l, int r, T lower)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, lower);\n        if (count == r - l) return std::nullopt;\n        return\
    \ kth_smallest(l, r, count);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 5 \"ds/range_query/range_lis_query.hpp\"\n\n#include <algorithm>\n\
    #line 8 \"ds/range_query/range_lis_query.hpp\"\n#include <numeric>\n#line 11 \"\
    ds/range_query/range_lis_query.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    namespace range_lis_query_internal {\n\nconstexpr int none = -1;\nusing Permutation\
    \ = std::vector<int>;\nusing Iterator = Permutation::iterator;\n\ninline Permutation\
    \ inverse(const Permutation& permutation) {\n    int n = int(permutation.size());\n\
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
    \ right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1\
    \ \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cstddef>\n#include\
    \ <cstdio>\n#line 8 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#line 13 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ = has_static_mod_raw<T>::value;\n\n}  // namespace internal\n\nstruct FastInput\
    \ {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n    std::FILE*\
    \ _stream;\n    char _buffer[buffer_size];\n    int _position;\n    int _length;\n\
    \n    bool prepare_number() {\n        if (_length - _position >= 32) return true;\n\
    \        const int remaining = _length - _position;\n        if (remaining > 0)\
    \ std::memmove(_buffer, _buffer + _position, remaining);\n        const int added\
    \ = int(std::fread(_buffer + remaining, 1, buffer_size - remaining, _stream));\n\
    \        _position = 0;\n        _length = remaining + added;\n        if (_length\
    \ < buffer_size) _buffer[_length] = '\\0';\n        return _length != 0;\n   \
    \ }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n       \
    \ : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const FastInput&)\
    \ = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\n    int read_char_raw()\
    \ {\n        if (_position == _length) {\n            _length = int(std::fread(_buffer,\
    \ 1, buffer_size, _stream));\n            _position = 0;\n            if (_length\
    \ == 0) return EOF;\n        }\n        return _buffer[_position++];\n    }\n\n\
    \    bool skip_spaces() {\n        int c = read_char_raw();\n        while (c\
    \ != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \        --_position;\n        return true;\n    }\n\n    bool read(char& value)\
    \ {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (std::is_signed_v<T>) {\n            T result = 0;\n  \
    \          while ('0' <= c && c <= '9') {\n                const int first = c\
    \ - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
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
    \ <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n  \
    \          && !std::is_integral_v<T>\n            && !internal::is_range_v<T>,\n\
    \        bool\n    >\n    read(T& value) {\n        long long x;\n        if (!read(x))\
    \ return false;\n        if constexpr (internal::has_static_mod_raw_v<T>) {\n\
    \            if (x >= 0 && uint64_t(x) < uint64_t(T::mod())) {\n             \
    \   value = T::raw(uint32_t(x));\n            } else {\n                value\
    \ = T(x);\n            }\n        } else {\n            value = T(x);\n      \
    \  }\n        return true;\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>,\n\
    \        bool\n    >\n    read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        read(value);\n   \
    \     return *this;\n    }\n};\n\nstruct FastOutput {\n    static constexpr int\
    \ buffer_size = 1 << 20;\n\n   private:\n    inline static const auto digit_quads\
    \ = [] {\n        std::array<char, 40000> result{};\n        for (int i = 0; i\
    \ < 10000; i++) {\n            int value = i;\n            for (int j = 3; j >=\
    \ 0; j--) {\n                result[4 * i + j] = char('0' + value % 10);\n   \
    \             value /= 10;\n            }\n        }\n        return result;\n\
    \    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int\
    \ _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream), _position(0) {}\n\n    FastOutput(const FastOutput&)\
    \ = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput()\
    \ {\n        flush();\n    }\n\n    void flush() {\n        if (_position == 0)\
    \ return;\n        std::fwrite(_buffer, 1, _position, _stream);\n        _position\
    \ = 0;\n    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        unsigned\
    \ chunks[16];\n        int count = 0;\n        while (magnitude >= 10000) {\n\
    \            const Unsigned quotient = magnitude / 10000;\n            chunks[count++]\
    \ = unsigned(magnitude - quotient * 10000);\n            magnitude = quotient;\n\
    \        }\n        if (_position > buffer_size - 64) flush();\n        const\
    \ unsigned leading = unsigned(magnitude);\n        const char* first = digit_quads.data()\
    \ + 4 * leading;\n        int skip = leading < 10 ? 3 : leading < 100 ? 2 : leading\
    \ < 1000 ? 1 : 0;\n        for (; skip < 4; skip++) _buffer[_position++] = first[skip];\n\
    \        while (count--) {\n            const char* digits = digit_quads.data()\
    \ + 4 * chunks[count];\n            std::memcpy(_buffer + _position, digits, 4);\n\
    \            _position += 4;\n        }\n    }\n\n    template <class T>\n   \
    \ std::enable_if_t<\n        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n\n    template <class T>\n    FastOutput&\
    \ operator<<(const T& value) {\n        write(value);\n        return *this;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 5 \"\
    verify/ds/range_query/range_lis_query.test.cpp\"\n\n#line 10 \"verify/ds/range_query/range_lis_query.test.cpp\"\
    \n\nnamespace {\n\nint brute(const std::vector<int>& values, int left, int right)\
    \ {\n    std::vector<int> tails;\n    for (int i = left; i < right; i++) {\n \
    \       auto position = std::lower_bound(\n            tails.begin(),\n      \
    \      tails.end(),\n            values[i]\n        );\n        if (position ==\
    \ tails.end()) {\n            tails.push_back(values[i]);\n        } else {\n\
    \            *position = values[i];\n        }\n    }\n    return int(tails.size());\n\
    }\n\nvoid test_randomized() {\n    m1une::ds::RangeLisQuery<int> empty(std::vector<int>{});\n\
    \    assert(empty.empty());\n    assert(empty.query(0, 0) == 0);\n\n    std::uint64_t\
    \ state = 3141592653ULL;\n    auto random = [&]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 500; trial++) {\n        int n = int(random() % 36);\n  \
    \      std::vector<int> values(n);\n        for (int& value : values) value =\
    \ int(random() % 11) - 5;\n        m1une::ds::RangeLisQuery<int> structure(values);\n\
    \        assert(structure.size() == n);\n        assert(structure.empty() == (n\
    \ == 0));\n\n        for (int left = 0; left <= n; left++) {\n            for\
    \ (int right = left; right <= n; right++) {\n                int expected = brute(values,\
    \ left, right);\n                assert(structure.query(left, right) == expected);\n\
    \                assert(structure.lis_length(left, right) == expected);\n    \
    \        }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0, query_count = 0;\n    input.read(n, query_count);\n    std::vector<int>\
    \ permutation(n);\n    for (int& value : permutation) input.read(value);\n\n \
    \   m1une::ds::RangeLisQuery<int> structure(permutation);\n    while (query_count--)\
    \ {\n        int left = 0, right = 0;\n        input.read(left, right);\n    \
    \    output.println(structure.query(left, right));\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_lis_query\"\
    \n\n#include \"../../../ds/range_query/range_lis_query.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\
    \nnamespace {\n\nint brute(const std::vector<int>& values, int left, int right)\
    \ {\n    std::vector<int> tails;\n    for (int i = left; i < right; i++) {\n \
    \       auto position = std::lower_bound(\n            tails.begin(),\n      \
    \      tails.end(),\n            values[i]\n        );\n        if (position ==\
    \ tails.end()) {\n            tails.push_back(values[i]);\n        } else {\n\
    \            *position = values[i];\n        }\n    }\n    return int(tails.size());\n\
    }\n\nvoid test_randomized() {\n    m1une::ds::RangeLisQuery<int> empty(std::vector<int>{});\n\
    \    assert(empty.empty());\n    assert(empty.query(0, 0) == 0);\n\n    std::uint64_t\
    \ state = 3141592653ULL;\n    auto random = [&]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 500; trial++) {\n        int n = int(random() % 36);\n  \
    \      std::vector<int> values(n);\n        for (int& value : values) value =\
    \ int(random() % 11) - 5;\n        m1une::ds::RangeLisQuery<int> structure(values);\n\
    \        assert(structure.size() == n);\n        assert(structure.empty() == (n\
    \ == 0));\n\n        for (int left = 0; left <= n; left++) {\n            for\
    \ (int right = left; right <= n; right++) {\n                int expected = brute(values,\
    \ left, right);\n                assert(structure.query(left, right) == expected);\n\
    \                assert(structure.lis_length(left, right) == expected);\n    \
    \        }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0, query_count = 0;\n    input.read(n, query_count);\n    std::vector<int>\
    \ permutation(n);\n    for (int& value : permutation) input.read(value);\n\n \
    \   m1une::ds::RangeLisQuery<int> structure(permutation);\n    while (query_count--)\
    \ {\n        int left = 0, right = 0;\n        input.read(left, right);\n    \
    \    output.println(structure.query(left, right));\n    }\n}\n"
  dependsOn:
  - ds/range_query/range_lis_query.hpp
  - ds/range_query/wavelet_matrix.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/range_lis_query.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/range_lis_query.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/range_lis_query.test.cpp
- /verify/verify/ds/range_query/range_lis_query.test.cpp.html
title: verify/ds/range_query/range_lis_query.test.cpp
---
