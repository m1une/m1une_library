---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sqrt_tree.hpp
    title: Sqrt Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"verify/ds/range_query/sqrt_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n#line 1 \"ds/range_query/sqrt_tree.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n\
    #line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Concept to check if a type satisfies the requirements of a Monoid.\n// A Monoid\
    \ must have a `value_type`, an identity element `id()`, and an associative binary\
    \ operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for groups.\
    \ A type satisfying this concept must also obey the group\n// laws; concepts can\
    \ check the interface but not the algebraic properties.\ntemplate <typename M>\n\
    concept IsGroup = IsMonoid<M> && requires(typename M::value_type a) {\n    { M::inv(a)\
    \ } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ groups. Commutativity is a semantic requirement and\n// cannot be checked by\
    \ a C++ concept.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/range_query/sqrt_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Static Sqrt Tree with O(1) monoid-product\
    \ queries.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SqrtTree {\n   \
    \ using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n    std::size_t\
    \ _padded_size;\n    std::vector<T> _values;\n    std::vector<int> _layers;\n\
    \    std::vector<int> _layer_for_bit;\n    std::vector<std::vector<T>> _prefix;\n\
    \    std::vector<std::vector<T>> _suffix;\n    std::vector<std::vector<T>> _between;\n\
    \n    template <class U>\n    static T make_value(const U& value, int index) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else if constexpr (requires(U x, int i) { Monoid::make(x,\
    \ i); }) {\n            return Monoid::make(value, index);\n        } else {\n\
    \            return static_cast<T>(value);\n        }\n    }\n\n    void build_layers()\
    \ {\n        _layers.clear();\n        _layer_for_bit.clear();\n        if (_n\
    \ <= 1) return;\n\n        int exponent = std::bit_width(_padded_size) - 1;\n\
    \        _layers.push_back(exponent);\n        while (_layers.back() != 0) {\n\
    \            int current = _layers.back();\n            _layers.push_back(current\
    \ == 1 ? 0 : (current + 1) / 2);\n        }\n\n        _layer_for_bit.assign(exponent,\
    \ -1);\n        for (int layer = 0; layer + 1 < int(_layers.size()); ++layer)\
    \ {\n            for (\n                int bit = _layers[layer + 1];\n      \
    \          bit < _layers[layer];\n                ++bit\n            ) {\n   \
    \             _layer_for_bit[bit] = layer;\n            }\n        }\n    }\n\n\
    \    void build_level(int layer) {\n        int node_exponent = _layers[layer];\n\
    \        int block_exponent = _layers[layer + 1];\n        std::size_t node_size\
    \ = std::size_t(1) << node_exponent;\n        std::size_t block_size = std::size_t(1)\
    \ << block_exponent;\n        std::size_t block_count = node_size / block_size;\n\
    \        std::size_t node_count = _padded_size / node_size;\n\n        _prefix[layer].assign(_padded_size,\
    \ Monoid::id());\n        _suffix[layer].assign(_padded_size, Monoid::id());\n\
    \        _between[layer].assign(\n            node_count * block_count * block_count,\n\
    \            Monoid::id()\n        );\n\n        for (\n            std::size_t\
    \ block_start = 0;\n            block_start < _padded_size;\n            block_start\
    \ += block_size\n        ) {\n            std::size_t block_end = block_start\
    \ + block_size;\n            _prefix[layer][block_start] = _values[block_start];\n\
    \            for (\n                std::size_t index = block_start + 1;\n   \
    \             index < block_end;\n                ++index\n            ) {\n \
    \               _prefix[layer][index] = Monoid::op(\n                    _prefix[layer][index\
    \ - 1],\n                    _values[index]\n                );\n            }\n\
    \n            _suffix[layer][block_end - 1] = _values[block_end - 1];\n      \
    \      for (std::size_t index = block_end - 1; block_start < index;) {\n     \
    \           --index;\n                _suffix[layer][index] = Monoid::op(\n  \
    \                  _values[index],\n                    _suffix[layer][index +\
    \ 1]\n                );\n            }\n        }\n\n        for (std::size_t\
    \ node = 0; node < node_count; ++node) {\n            std::size_t node_start =\
    \ node * node_size;\n            std::size_t table_start =\n                node\
    \ * block_count * block_count;\n            for (std::size_t first = 0; first\
    \ < block_count; ++first) {\n                T product = Monoid::id();\n     \
    \           for (std::size_t last = first; last < block_count; ++last) {\n   \
    \                 std::size_t block_end =\n                        node_start\
    \ + (last + 1) * block_size;\n                    product = Monoid::op(\n    \
    \                    product,\n                        _prefix[layer][block_end\
    \ - 1]\n                    );\n                    _between[layer][\n       \
    \                 table_start + first * block_count + last\n                 \
    \   ] = product;\n                }\n            }\n        }\n    }\n\n    void\
    \ build() {\n        if (_n == 0) {\n            _padded_size = 0;\n         \
    \   _layers.clear();\n            _layer_for_bit.clear();\n            _prefix.clear();\n\
    \            _suffix.clear();\n            _between.clear();\n            return;\n\
    \        }\n\n        _padded_size = std::bit_ceil(std::size_t(_n));\n       \
    \ _values.resize(_padded_size, Monoid::id());\n        build_layers();\n     \
    \   int level_count = _layers.empty() ? 0 : int(_layers.size()) - 1;\n       \
    \ _prefix.resize(level_count);\n        _suffix.resize(level_count);\n       \
    \ _between.resize(level_count);\n        for (int layer = 0; layer < level_count;\
    \ ++layer) {\n            build_level(layer);\n        }\n    }\n\n   public:\n\
    \    SqrtTree() : _n(0), _padded_size(0) {}\n\n    explicit SqrtTree(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(values) {\n        build();\n    }\n\n    explicit SqrtTree(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(std::move(values)) {\n        build();\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i); }\
    \ ||\n        std::convertible_to<U, T>\n    )\n    explicit SqrtTree(const std::vector<U>&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(values.size(), Monoid::id()) {\n        for (int index = 0; index\
    \ < _n; ++index) {\n            _values[index] = make_value(values[index], index);\n\
    \        }\n        build();\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   // Returns the ordered monoid product over [left, right).\n    T prod(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (left == right) return Monoid::id();\n        --right;\n\
    \        if (left == right) return _values[left];\n\n        std::size_t first\
    \ = std::size_t(left);\n        std::size_t last = std::size_t(right);\n     \
    \   int differing_bit = std::bit_width(first ^ last) - 1;\n        int layer =\
    \ _layer_for_bit[differing_bit];\n        int node_exponent = _layers[layer];\n\
    \        int block_exponent = _layers[layer + 1];\n        std::size_t node_size\
    \ = std::size_t(1) << node_exponent;\n        std::size_t block_size = std::size_t(1)\
    \ << block_exponent;\n        std::size_t block_count = node_size / block_size;\n\
    \        std::size_t node = first / node_size;\n        std::size_t first_block\
    \ = (first % node_size) / block_size;\n        std::size_t last_block = (last\
    \ % node_size) / block_size;\n\n        T result = _suffix[layer][first];\n  \
    \      if (first_block + 1 < last_block) {\n            std::size_t table_start\
    \ =\n                node * block_count * block_count;\n            result = Monoid::op(\n\
    \                result,\n                _between[layer][\n                 \
    \   table_start\n                    + (first_block + 1) * block_count\n     \
    \               + (last_block - 1)\n                ]\n            );\n      \
    \  }\n        return Monoid::op(result, _prefix[layer][last]);\n    }\n\n    T\
    \ all_prod() const {\n        return prod(0, _n);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/sqrt_tree.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/sqrt_tree.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\n#include\
    \ <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\
    \n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct\
    \ is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/ds/range_query/sqrt_tree.test.cpp\"\
    \n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n   \
    \ using value_type = T;\n\n    // Returns the identity element for addition, which\
    \ is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    //\
    \ Returns the sum of a and b.\n    static constexpr T op(const T& a, const T&\
    \ b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T& x)\
    \ {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 12 \"verify/ds/range_query/sqrt_tree.test.cpp\"\n\nnamespace\
    \ {\n\nstruct Concat {\n    using value_type = std::string;\n\n    static value_type\
    \ id() {\n        return \"\";\n    }\n\n    static value_type op(const value_type&\
    \ first, const value_type& second) {\n        return first + second;\n    }\n\
    };\n\nvoid test_fixed() {\n    m1une::ds::SqrtTree<m1une::monoid::Add<long long>>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.prod(0, 0) == 0);\n   \
    \ assert(empty.all_prod() == 0);\n\n    std::vector<long long> values = {1, 2,\
    \ 3, 4, 5};\n    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> sum(values);\n\
    \    assert(sum.size() == 5);\n    assert(sum.prod(0, 5) == 15);\n    assert(sum.prod(1,\
    \ 4) == 9);\n    assert(sum.prod(3, 3) == 0);\n\n    std::vector<std::string>\
    \ letters = {\"a\", \"b\", \"c\", \"d\", \"e\", \"f\"};\n    m1une::ds::SqrtTree<Concat>\
    \ text(letters);\n    assert(text.prod(0, 6) == \"abcdef\");\n    assert(text.prod(1,\
    \ 5) == \"bcde\");\n    assert(text.prod(2, 3) == \"c\");\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 601;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2000; ++trial) {\n        int size = int(random()\
    \ % 250);\n        std::vector<long long> values(size);\n        for (long long&\
    \ value : values) {\n            value = static_cast<long long>(random() % 101)\
    \ - 50;\n        }\n        m1une::ds::SqrtTree<m1une::monoid::Add<long long>>\
    \ tree(values);\n\n        for (int query = 0; query < 300; ++query) {\n     \
    \       int left = int(random() % (size + 1));\n            int right = int(random()\
    \ % (size + 1));\n            if (right < left) std::swap(left, right);\n\n  \
    \          [[maybe_unused]] long long expected = 0;\n            for (int index\
    \ = left; index < right; ++index) {\n                expected += values[index];\n\
    \            }\n            assert(tree.prod(left, right) == expected);\n    \
    \    }\n    }\n\n    for (int size = 0; size <= 80; ++size) {\n        std::vector<std::string>\
    \ values(size);\n        for (int index = 0; index < size; ++index) {\n      \
    \      values[index] = char('a' + index % 5);\n        }\n        m1une::ds::SqrtTree<Concat>\
    \ tree(values);\n        for (int left = 0; left <= size; ++left) {\n        \
    \    std::string expected;\n            for (int right = left; right <= size;\
    \ ++right) {\n                assert(tree.prod(left, right) == expected);\n  \
    \              if (right < size) expected += values[right];\n            }\n \
    \       }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n\n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long\
    \ long> values(n);\n    for (long long& value : values) fast_input >> value;\n\
    \n    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> tree(values);\n    while\
    \ (q--) {\n        int left, right;\n        fast_input >> left >> right;\n  \
    \      fast_output << tree.prod(left, right) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include \"../../../ds/range_query/sqrt_tree.hpp\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\n#include <string>\n\
    #include <vector>\n\n#include \"../../../monoid/add.hpp\"\n\nnamespace {\n\nstruct\
    \ Concat {\n    using value_type = std::string;\n\n    static value_type id()\
    \ {\n        return \"\";\n    }\n\n    static value_type op(const value_type&\
    \ first, const value_type& second) {\n        return first + second;\n    }\n\
    };\n\nvoid test_fixed() {\n    m1une::ds::SqrtTree<m1une::monoid::Add<long long>>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.prod(0, 0) == 0);\n   \
    \ assert(empty.all_prod() == 0);\n\n    std::vector<long long> values = {1, 2,\
    \ 3, 4, 5};\n    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> sum(values);\n\
    \    assert(sum.size() == 5);\n    assert(sum.prod(0, 5) == 15);\n    assert(sum.prod(1,\
    \ 4) == 9);\n    assert(sum.prod(3, 3) == 0);\n\n    std::vector<std::string>\
    \ letters = {\"a\", \"b\", \"c\", \"d\", \"e\", \"f\"};\n    m1une::ds::SqrtTree<Concat>\
    \ text(letters);\n    assert(text.prod(0, 6) == \"abcdef\");\n    assert(text.prod(1,\
    \ 5) == \"bcde\");\n    assert(text.prod(2, 3) == \"c\");\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 601;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2000; ++trial) {\n        int size = int(random()\
    \ % 250);\n        std::vector<long long> values(size);\n        for (long long&\
    \ value : values) {\n            value = static_cast<long long>(random() % 101)\
    \ - 50;\n        }\n        m1une::ds::SqrtTree<m1une::monoid::Add<long long>>\
    \ tree(values);\n\n        for (int query = 0; query < 300; ++query) {\n     \
    \       int left = int(random() % (size + 1));\n            int right = int(random()\
    \ % (size + 1));\n            if (right < left) std::swap(left, right);\n\n  \
    \          [[maybe_unused]] long long expected = 0;\n            for (int index\
    \ = left; index < right; ++index) {\n                expected += values[index];\n\
    \            }\n            assert(tree.prod(left, right) == expected);\n    \
    \    }\n    }\n\n    for (int size = 0; size <= 80; ++size) {\n        std::vector<std::string>\
    \ values(size);\n        for (int index = 0; index < size; ++index) {\n      \
    \      values[index] = char('a' + index % 5);\n        }\n        m1une::ds::SqrtTree<Concat>\
    \ tree(values);\n        for (int left = 0; left <= size; ++left) {\n        \
    \    std::string expected;\n            for (int right = left; right <= size;\
    \ ++right) {\n                assert(tree.prod(left, right) == expected);\n  \
    \              if (right < size) expected += values[right];\n            }\n \
    \       }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n\n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long\
    \ long> values(n);\n    for (long long& value : values) fast_input >> value;\n\
    \n    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> tree(values);\n    while\
    \ (q--) {\n        int left, right;\n        fast_input >> left >> right;\n  \
    \      fast_output << tree.prod(left, right) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/sqrt_tree.hpp
  - monoid/concept.hpp
  - utilities/fast_io.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sqrt_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 20:44:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sqrt_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sqrt_tree.test.cpp
- /verify/verify/ds/range_query/sqrt_tree.test.cpp.html
title: verify/ds/range_query/sqrt_tree.test.cpp
---
