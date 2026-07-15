---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix_2d.hpp
    title: Wavelet Matrix 2D
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
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    ds/range_query/wavelet_matrix_2d.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// A static wavelet matrix for a sequence\
    \ of pairs.\n//\n// Besides the index range, queries can restrict the first component\
    \ and count\n// or select by the second component. This corresponds to orthogonal\
    \ queries in\n// the three dimensions (index, first, second).\ntemplate <class\
    \ X, class Y = X>\nclass WaveletMatrix2D {\n   public:\n    using first_type =\
    \ X;\n    using second_type = Y;\n    using value_type = std::pair<X, Y>;\n\n\
    \   private:\n    struct BitVector {\n        std::vector<std::uint64_t> bits;\n\
    \        std::vector<int> prefix;\n\n        BitVector() = default;\n\n      \
    \  explicit BitVector(int n)\n            : bits((std::size_t(n) + 63) >> 6, 0),\n\
    \              prefix(bits.size() + 1, 0) {}\n\n        void set(int p) {\n  \
    \          bits[std::size_t(p) >> 6] |= std::uint64_t(1) << (p & 63);\n      \
    \  }\n\n        void build() {\n            for (std::size_t i = 0; i < bits.size();\
    \ i++) {\n                prefix[i + 1] = prefix[i] + std::popcount(bits[i]);\n\
    \            }\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    class RankWaveletMatrix {\n       private:\n        int\
    \ _n = 0;\n        int _alphabet_size = 0;\n        int _log = 0;\n        std::vector<BitVector>\
    \ _matrix;\n        std::vector<int> _zero_count;\n\n        bool bit(int value,\
    \ int level) const {\n            return (value >> (_log - 1 - level)) & 1;\n\
    \        }\n\n        int count_less(int l, int r, int upper) const {\n      \
    \      if (upper <= 0) return 0;\n            if (upper >= _alphabet_size) return\
    \ r - l;\n\n            int result = 0;\n            for (int level = 0; level\
    \ < _log; level++) {\n                int l0 = _matrix[level].rank0(l);\n    \
    \            int r0 = _matrix[level].rank0(r);\n                if (bit(upper,\
    \ level)) {\n                    result += r0 - l0;\n                    l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                    r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \                } else {\n                    l = l0;\n                    r\
    \ = r0;\n                }\n            }\n            return result;\n      \
    \  }\n\n       public:\n        RankWaveletMatrix() = default;\n\n        RankWaveletMatrix(\n\
    \            const std::vector<int>& values,\n            int alphabet_size\n\
    \        ) {\n            build(values, alphabet_size);\n        }\n\n       \
    \ void build(const std::vector<int>& values, int alphabet_size) {\n          \
    \  assert(alphabet_size >= 0);\n            _n = int(values.size());\n       \
    \     _alphabet_size = alphabet_size;\n            _log = alphabet_size == 0\n\
    \                       ? 0\n                       : std::max(\n            \
    \                 1,\n                             int(std::bit_width(unsigned(alphabet_size\
    \ - 1)))\n                         );\n\n            _matrix.clear();\n      \
    \      _matrix.reserve(_log);\n            _zero_count.assign(_log, 0);\n    \
    \        std::vector<int> current(values);\n            std::vector<int> next(_n);\n\
    \            for (int value : values) {\n                assert(0 <= value &&\
    \ value < alphabet_size);\n                (void)value;\n            }\n\n   \
    \         for (int level = 0; level < _log; level++) {\n                _matrix.emplace_back(_n);\n\
    \                for (int i = 0; i < _n; i++) {\n                    if (bit(current[i],\
    \ level)) _matrix.back().set(i);\n                }\n                _matrix.back().build();\n\
    \n                int zeros = _matrix.back().rank0(_n);\n                _zero_count[level]\
    \ = zeros;\n                int zero_position = 0;\n                int one_position\
    \ = zeros;\n                for (int value : current) {\n                    if\
    \ (bit(value, level)) {\n                        next[one_position++] = value;\n\
    \                    } else {\n                        next[zero_position++] =\
    \ value;\n                    }\n                }\n                current.swap(next);\n\
    \            }\n        }\n\n        int range_freq(int l, int r, int lower, int\
    \ upper) const {\n            assert(0 <= l && l <= r && r <= _n);\n         \
    \   if (upper <= lower) return 0;\n            return count_less(l, r, upper)\
    \ - count_less(l, r, lower);\n        }\n    };\n\n    int _n = 0;\n    int _log\
    \ = 0;\n    std::vector<value_type> _values;\n    std::vector<X> _first_coordinates;\n\
    \    std::vector<Y> _second_coordinates;\n    RankWaveletMatrix _first_matrix;\n\
    \    std::vector<BitVector> _matrix;\n    std::vector<int> _zero_count;\n    std::vector<RankWaveletMatrix>\
    \ _zero_first_matrix;\n\n    template <class T>\n    static bool equal(const T&\
    \ first, const T& second) {\n        return !(first < second) && !(second < first);\n\
    \    }\n\n    template <class T>\n    static void sort_unique(std::vector<T>&\
    \ values) {\n        std::sort(values.begin(), values.end());\n        values.erase(\n\
    \            std::unique(\n                values.begin(),\n                values.end(),\n\
    \                [](const T& first, const T& second) {\n                    return\
    \ equal(first, second);\n                }\n            ),\n            values.end()\n\
    \        );\n    }\n\n    bool bit(int value, int level) const {\n        return\
    \ (value >> (_log - 1 - level)) & 1;\n    }\n\n    int first_lower_bound(const\
    \ X& value) const {\n        return int(\n            std::lower_bound(\n    \
    \            _first_coordinates.begin(),\n                _first_coordinates.end(),\n\
    \                value\n            ) - _first_coordinates.begin()\n        );\n\
    \    }\n\n    int second_lower_bound(const Y& value) const {\n        return int(\n\
    \            std::lower_bound(\n                _second_coordinates.begin(),\n\
    \                _second_coordinates.end(),\n                value\n         \
    \   ) - _second_coordinates.begin()\n        );\n    }\n\n    int count_first_rank(\n\
    \        int l,\n        int r,\n        int first_lower,\n        int first_upper\n\
    \    ) const {\n        return _first_matrix.range_freq(l, r, first_lower, first_upper);\n\
    \    }\n\n    int count_second_less(\n        int l,\n        int r,\n       \
    \ int first_lower,\n        int first_upper,\n        int second_upper\n    )\
    \ const {\n        if (second_upper <= 0) return 0;\n        if (second_upper\
    \ >= int(_second_coordinates.size())) {\n            return count_first_rank(l,\
    \ r, first_lower, first_upper);\n        }\n\n        int result = 0;\n      \
    \  for (int level = 0; level < _log; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(second_upper,\
    \ level)) {\n                result += _zero_first_matrix[level].range_freq(\n\
    \                    l0,\n                    r0,\n                    first_lower,\n\
    \                    first_upper\n                );\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n   public:\n    WaveletMatrix2D()\
    \ = default;\n\n    explicit WaveletMatrix2D(const std::vector<value_type>& values)\
    \ {\n        build(values);\n    }\n\n    explicit WaveletMatrix2D(std::vector<value_type>&&\
    \ values) {\n        build(std::move(values));\n    }\n\n    WaveletMatrix2D(\n\
    \        const std::vector<X>& first,\n        const std::vector<Y>& second\n\
    \    ) {\n        build(first, second);\n    }\n\n    void build(std::vector<value_type>\
    \ values) {\n        _values = std::move(values);\n        _n = int(_values.size());\n\
    \n        _first_coordinates.clear();\n        _second_coordinates.clear();\n\
    \        _first_coordinates.reserve(_n);\n        _second_coordinates.reserve(_n);\n\
    \        for (const auto& value : _values) {\n            _first_coordinates.push_back(value.first);\n\
    \            _second_coordinates.push_back(value.second);\n        }\n       \
    \ sort_unique(_first_coordinates);\n        sort_unique(_second_coordinates);\n\
    \n        if (_n == 0) {\n            _log = 0;\n            _first_matrix = RankWaveletMatrix();\n\
    \            _matrix.clear();\n            _zero_count.clear();\n            _zero_first_matrix.clear();\n\
    \            return;\n        }\n\n        std::vector<int> current_first(_n);\n\
    \        std::vector<int> current_second(_n);\n        std::vector<int> next_first(_n);\n\
    \        std::vector<int> next_second(_n);\n        for (int i = 0; i < _n; i++)\
    \ {\n            current_first[i] = first_lower_bound(_values[i].first);\n   \
    \         current_second[i] = second_lower_bound(_values[i].second);\n       \
    \ }\n\n        int first_size = int(_first_coordinates.size());\n        int second_size\
    \ = int(_second_coordinates.size());\n        _first_matrix.build(current_first,\
    \ first_size);\n        _log = std::max(\n            1,\n            int(std::bit_width(unsigned(second_size\
    \ - 1)))\n        );\n        _matrix.clear();\n        _matrix.reserve(_log);\n\
    \        _zero_count.assign(_log, 0);\n        _zero_first_matrix.clear();\n \
    \       _zero_first_matrix.reserve(_log);\n\n        for (int level = 0; level\
    \ < _log; level++) {\n            _matrix.emplace_back(_n);\n            for (int\
    \ i = 0; i < _n; i++) {\n                if (bit(current_second[i], level)) _matrix.back().set(i);\n\
    \            }\n            _matrix.back().build();\n\n            int zeros =\
    \ _matrix.back().rank0(_n);\n            _zero_count[level] = zeros;\n       \
    \     int zero_position = 0;\n            int one_position = zeros;\n        \
    \    for (int i = 0; i < _n; i++) {\n                int position;\n         \
    \       if (bit(current_second[i], level)) {\n                    position = one_position++;\n\
    \                } else {\n                    position = zero_position++;\n \
    \               }\n                next_first[position] = current_first[i];\n\
    \                next_second[position] = current_second[i];\n            }\n\n\
    \            std::vector<int> zero_first(\n                next_first.begin(),\n\
    \                next_first.begin() + zeros\n            );\n            _zero_first_matrix.emplace_back(zero_first,\
    \ first_size);\n            current_first.swap(next_first);\n            current_second.swap(next_second);\n\
    \        }\n    }\n\n    void build(\n        const std::vector<X>& first,\n \
    \       const std::vector<Y>& second\n    ) {\n        assert(first.size() ==\
    \ second.size());\n        std::vector<value_type> values;\n        values.reserve(first.size());\n\
    \        for (int i = 0; i < int(first.size()); i++) {\n            values.emplace_back(first[i],\
    \ second[i]);\n        }\n        build(std::move(values));\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    const value_type& access(int p) const {\n \
    \       assert(0 <= p && p < _n);\n        return _values[p];\n    }\n\n    const\
    \ value_type& operator[](int p) const {\n        return access(p);\n    }\n\n\
    \    int count(\n        int l,\n        int r,\n        const X& first_lower,\n\
    \        const X& first_upper,\n        const Y& second_lower,\n        const\
    \ Y& second_upper\n    ) const {\n        assert(0 <= l && l <= r && r <= _n);\n\
    \        assert(!(first_upper < first_lower));\n        assert(!(second_upper\
    \ < second_lower));\n        int first_l = first_lower_bound(first_lower);\n \
    \       int first_r = first_lower_bound(first_upper);\n        int second_l =\
    \ second_lower_bound(second_lower);\n        int second_r = second_lower_bound(second_upper);\n\
    \        return count_second_less(l, r, first_l, first_r, second_r) -\n      \
    \         count_second_less(l, r, first_l, first_r, second_l);\n    }\n\n    Y\
    \ quantile(\n        int l,\n        int r,\n        const X& first_lower,\n \
    \       const X& first_upper,\n        int k\n    ) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        assert(!(first_upper < first_lower));\n\
    \        int first_l = first_lower_bound(first_lower);\n        int first_r =\
    \ first_lower_bound(first_upper);\n        int candidates = count_first_rank(l,\
    \ r, first_l, first_r);\n        assert(0 <= k && k < candidates);\n        (void)candidates;\n\
    \n        int second_rank = 0;\n        for (int level = 0; level < _log; level++)\
    \ {\n            int l0 = _matrix[level].rank0(l);\n            int r0 = _matrix[level].rank0(r);\n\
    \            int zeros = _zero_first_matrix[level].range_freq(\n             \
    \   l0,\n                r0,\n                first_l,\n                first_r\n\
    \            );\n            if (k < zeros) {\n                l = l0;\n     \
    \           r = r0;\n            } else {\n                k -= zeros;\n     \
    \           second_rank |= 1 << (_log - 1 - level);\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            }\n        }\n        return _second_coordinates[second_rank];\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    namespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
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
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 11 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\n\n\
    namespace {\n\nusing Matrix = m1une::ds::WaveletMatrix2D<int, int>;\n\n#ifndef\
    \ NDEBUG\nvoid randomized_test() {\n    Matrix empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n    assert(empty.count(0, 0, -10, 10, -10, 10)\
    \ == 0);\n\n    std::uint64_t state = 20260713;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 80; trial++) {\n        int\
    \ n = int(random() % 40);\n        std::vector<Matrix::value_type> values;\n \
    \       std::vector<int> first;\n        std::vector<int> second;\n        values.reserve(n);\n\
    \        first.reserve(n);\n        second.reserve(n);\n        for (int i = 0;\
    \ i < n; i++) {\n            int x = int(random() % 21) - 10;\n            int\
    \ y = int(random() % 21) - 10;\n            values.emplace_back(x, y);\n     \
    \       first.push_back(x);\n            second.push_back(y);\n        }\n\n \
    \       Matrix matrix(values);\n        Matrix parallel(first, second);\n    \
    \    assert(matrix.size() == n);\n        assert(matrix.empty() == (n == 0));\n\
    \        for (int i = 0; i < n; i++) {\n            assert(matrix[i] == values[i]);\n\
    \            assert(parallel.access(i) == values[i]);\n        }\n\n        for\
    \ (int query = 0; query < 150; query++) {\n            int l = int(random() %\
    \ std::uint64_t(n + 1));\n            int r = int(random() % std::uint64_t(n +\
    \ 1));\n            if (r < l) std::swap(l, r);\n            int first_lower =\
    \ int(random() % 31) - 15;\n            int first_upper = int(random() % 31) -\
    \ 15;\n            int second_lower = int(random() % 31) - 15;\n            int\
    \ second_upper = int(random() % 31) - 15;\n            if (first_upper < first_lower)\
    \ {\n                std::swap(first_lower, first_upper);\n            }\n   \
    \         if (second_upper < second_lower) {\n                std::swap(second_lower,\
    \ second_upper);\n            }\n\n            int expected_count = 0;\n     \
    \       std::vector<int> selected;\n            for (int i = l; i < r; i++) {\n\
    \                if (first_lower <= values[i].first &&\n                    values[i].first\
    \ < first_upper) {\n                    selected.push_back(values[i].second);\n\
    \                    if (second_lower <= values[i].second &&\n               \
    \         values[i].second < second_upper) {\n                        expected_count++;\n\
    \                    }\n                }\n            }\n            std::sort(selected.begin(),\
    \ selected.end());\n\n            assert(\n                matrix.count(\n   \
    \                 l,\n                    r,\n                    first_lower,\n\
    \                    first_upper,\n                    second_lower,\n       \
    \             second_upper\n                ) == expected_count\n            );\n\
    \            assert(\n                parallel.count(\n                    l,\n\
    \                    r,\n                    first_lower,\n                  \
    \  first_upper,\n                    second_lower,\n                    second_upper\n\
    \                ) == expected_count\n            );\n            for (int k =\
    \ 0; k < int(selected.size()); k++) {\n                assert(\n             \
    \       matrix.quantile(\n                        l,\n                       \
    \ r,\n                        first_lower,\n                        first_upper,\n\
    \                        k\n                    ) == selected[k]\n           \
    \     );\n            }\n        }\n    }\n\n    std::vector<Matrix::value_type>\
    \ equal_values(20, Matrix::value_type(4, 7));\n    Matrix equal_matrix(equal_values);\n\
    \    assert(equal_matrix.count(3, 18, 4, 5, 7, 8) == 15);\n    assert(equal_matrix.quantile(3,\
    \ 18, 4, 5, 14) == 7);\n}\n#endif\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n#ifndef NDEBUG\n\
    \    randomized_test();\n#endif\n    int n, query_count;\n    fast_input >> n\
    \ >> query_count;\n    std::vector<std::pair<int, long long>> values(n);\n   \
    \ for (auto& value : values) {\n        value.first = 0;\n        fast_input >>\
    \ value.second;\n    }\n\n    m1une::ds::WaveletMatrix2D<int, long long> matrix(values);\n\
    \    while (query_count--) {\n        int l, r, k;\n        fast_input >> l >>\
    \ r >> k;\n        fast_output << matrix.quantile(l, r, 0, 1, k) << '\\n';\n \
    \   }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../../ds/range_query/wavelet_matrix_2d.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <utility>\n#include <vector>\n\nnamespace {\n\nusing Matrix = m1une::ds::WaveletMatrix2D<int,\
    \ int>;\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    Matrix empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n    assert(empty.count(0, 0, -10, 10, -10, 10)\
    \ == 0);\n\n    std::uint64_t state = 20260713;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 80; trial++) {\n        int\
    \ n = int(random() % 40);\n        std::vector<Matrix::value_type> values;\n \
    \       std::vector<int> first;\n        std::vector<int> second;\n        values.reserve(n);\n\
    \        first.reserve(n);\n        second.reserve(n);\n        for (int i = 0;\
    \ i < n; i++) {\n            int x = int(random() % 21) - 10;\n            int\
    \ y = int(random() % 21) - 10;\n            values.emplace_back(x, y);\n     \
    \       first.push_back(x);\n            second.push_back(y);\n        }\n\n \
    \       Matrix matrix(values);\n        Matrix parallel(first, second);\n    \
    \    assert(matrix.size() == n);\n        assert(matrix.empty() == (n == 0));\n\
    \        for (int i = 0; i < n; i++) {\n            assert(matrix[i] == values[i]);\n\
    \            assert(parallel.access(i) == values[i]);\n        }\n\n        for\
    \ (int query = 0; query < 150; query++) {\n            int l = int(random() %\
    \ std::uint64_t(n + 1));\n            int r = int(random() % std::uint64_t(n +\
    \ 1));\n            if (r < l) std::swap(l, r);\n            int first_lower =\
    \ int(random() % 31) - 15;\n            int first_upper = int(random() % 31) -\
    \ 15;\n            int second_lower = int(random() % 31) - 15;\n            int\
    \ second_upper = int(random() % 31) - 15;\n            if (first_upper < first_lower)\
    \ {\n                std::swap(first_lower, first_upper);\n            }\n   \
    \         if (second_upper < second_lower) {\n                std::swap(second_lower,\
    \ second_upper);\n            }\n\n            int expected_count = 0;\n     \
    \       std::vector<int> selected;\n            for (int i = l; i < r; i++) {\n\
    \                if (first_lower <= values[i].first &&\n                    values[i].first\
    \ < first_upper) {\n                    selected.push_back(values[i].second);\n\
    \                    if (second_lower <= values[i].second &&\n               \
    \         values[i].second < second_upper) {\n                        expected_count++;\n\
    \                    }\n                }\n            }\n            std::sort(selected.begin(),\
    \ selected.end());\n\n            assert(\n                matrix.count(\n   \
    \                 l,\n                    r,\n                    first_lower,\n\
    \                    first_upper,\n                    second_lower,\n       \
    \             second_upper\n                ) == expected_count\n            );\n\
    \            assert(\n                parallel.count(\n                    l,\n\
    \                    r,\n                    first_lower,\n                  \
    \  first_upper,\n                    second_lower,\n                    second_upper\n\
    \                ) == expected_count\n            );\n            for (int k =\
    \ 0; k < int(selected.size()); k++) {\n                assert(\n             \
    \       matrix.quantile(\n                        l,\n                       \
    \ r,\n                        first_lower,\n                        first_upper,\n\
    \                        k\n                    ) == selected[k]\n           \
    \     );\n            }\n        }\n    }\n\n    std::vector<Matrix::value_type>\
    \ equal_values(20, Matrix::value_type(4, 7));\n    Matrix equal_matrix(equal_values);\n\
    \    assert(equal_matrix.count(3, 18, 4, 5, 7, 8) == 15);\n    assert(equal_matrix.quantile(3,\
    \ 18, 4, 5, 14) == 7);\n}\n#endif\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n#ifndef NDEBUG\n\
    \    randomized_test();\n#endif\n    int n, query_count;\n    fast_input >> n\
    \ >> query_count;\n    std::vector<std::pair<int, long long>> values(n);\n   \
    \ for (auto& value : values) {\n        value.first = 0;\n        fast_input >>\
    \ value.second;\n    }\n\n    m1une::ds::WaveletMatrix2D<int, long long> matrix(values);\n\
    \    while (query_count--) {\n        int l, r, k;\n        fast_input >> l >>\
    \ r >> k;\n        fast_output << matrix.quantile(l, r, 0, 1, k) << '\\n';\n \
    \   }\n}\n"
  dependsOn:
  - ds/range_query/wavelet_matrix_2d.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/wavelet_matrix_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/wavelet_matrix_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/wavelet_matrix_2d.test.cpp
- /verify/verify/ds/range_query/wavelet_matrix_2d.test.cpp.html
title: verify/ds/range_query/wavelet_matrix_2d.test.cpp
---
