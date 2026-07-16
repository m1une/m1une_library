---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_potentialized_dsu.hpp
    title: Persistent Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/xor.hpp
    title: Bitwise XOR Monoid
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
  bundledCode: "#line 1 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#line 1 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 12 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n\
    \    requires std::equality_comparable<typename Group::value_type>\nstruct PersistentPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n    struct Value {\n       \
    \ int parent_or_size;\n        T diff_to_parent;\n\n        Value() : parent_or_size(0),\
    \ diff_to_parent(Group::id()) {}\n        Value(int parent_or_size_, const T&\
    \ diff_to_parent_)\n            : parent_or_size(parent_or_size_), diff_to_parent(diff_to_parent_)\
    \ {}\n        Value(int parent_or_size_, T&& diff_to_parent_)\n            : parent_or_size(parent_or_size_),\
    \ diff_to_parent(std::move(diff_to_parent_)) {}\n    };\n\n   private:\n    struct\
    \ Node {\n        Value val;\n        int l, r;\n\n        Node() : val(), l(0),\
    \ r(0) {}\n        explicit Node(const Value& value) : val(value), l(0), r(0)\
    \ {}\n        explicit Node(Value&& value) : val(std::move(value)), l(0), r(0)\
    \ {}\n        Node(const Value& value, int left, int right) : val(value), l(left),\
    \ r(right) {}\n        Node(Value&& value, int left, int right) : val(std::move(value)),\
    \ l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n\n    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int build(int l, int r)\
    \ const {\n        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(Value(-1,\
    \ Group::id())));\n        int m = (l + r) >> 1;\n        int left = build(l,\
    \ m);\n        int right = build(m, r);\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    int set_node(int t, int l, int r, int p, Value\
    \ value) const {\n        if (r - l == 1) return new_node(Node(std::move(value)));\n\
    \        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int\
    \ right = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left,\
    \ l, m, p, std::move(value));\n        } else {\n            right = set_node(right,\
    \ m, r, p, std::move(value));\n        }\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    Value get_value(int t, int l, int r, int p) const\
    \ {\n        while (r - l > 1) {\n            int m = (l + r) >> 1;\n        \
    \    if (p < m) {\n                t = (*_pool)[t].l;\n                r = m;\n\
    \            } else {\n                t = (*_pool)[t].r;\n                l =\
    \ m;\n            }\n        }\n        return (*_pool)[t].val;\n    }\n\n   \
    \ std::pair<int, T> leader_and_potential(int a) const {\n        T res = Group::id();\n\
    \        while (true) {\n            Value cur = get(a);\n            if (cur.parent_or_size\
    \ < 0) return {a, res};\n            res = Group::op(cur.diff_to_parent, res);\n\
    \            a = cur.parent_or_size;\n        }\n    }\n\n   public:\n    PersistentPotentializedDsu()\
    \ : PersistentPotentializedDsu(0) {}\n\n    explicit PersistentPotentializedDsu(int\
    \ n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {\n     \
    \   assert(0 <= n);\n        _pool->reserve(n * 4 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n);\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       return leader_and_potential(a).first;\n    }\n\n    bool same(int a, int\
    \ b) const {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b <\
    \ _n);\n        return leader(a) == leader(b);\n    }\n\n    int group_size(int\
    \ a) const {\n        assert(0 <= a && a < _n);\n        return -get(leader(a)).parent_or_size;\n\
    \    }\n\n    int size(int a) const {\n        return group_size(a);\n    }\n\n\
    \    T potential(int a) const {\n        assert(0 <= a && a < _n);\n        return\
    \ leader_and_potential(a).second;\n    }\n\n    T diff(int a, int b) const {\n\
    \        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    Value get(int p) const {\n        assert(0 <= p\
    \ && p < _n);\n        return get_value(_root, 0, _n, p);\n    }\n\n    int parent_or_size(int\
    \ p) const {\n        return get(p).parent_or_size;\n    }\n\n    std::pair<PersistentPotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        assert(0 <= a && a <\
    \ _n);\n        assert(0 <= b && b < _n);\n        auto [x, pa] = leader_and_potential(a);\n\
    \        auto [y, pb] = leader_and_potential(b);\n        if (x == y) return {*this,\
    \ Group::op(Group::inv(pa), pb) == w};\n\n        int sx = -get(x).parent_or_size;\n\
    \        int sy = -get(y).parent_or_size;\n        T y_from_x = Group::op(Group::op(pa,\
    \ w), Group::inv(pb));\n        if (sx < sy) {\n            std::swap(x, y);\n\
    \            std::swap(sx, sy);\n            y_from_x = Group::inv(y_from_x);\n\
    \        }\n        int root = set_node(_root, 0, _n, x, Value(-(sx + sy), Group::id()));\n\
    \        root = set_node(root, 0, _n, y, Value(x, std::move(y_from_x)));\n   \
    \     return {PersistentPotentializedDsu(_n, root, _pool), true};\n    }\n\n \
    \   std::vector<std::vector<int>> groups() const {\n        std::vector<int> leader_buf(_n),\
    \ group_size(_n);\n        for (int i = 0; i < _n; i++) {\n            leader_buf[i]\
    \ = leader(i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate <typename\
    \ T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for addition, which is 0.\n    static constexpr T id() {\n        return T(0);\n\
    \    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a + b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/xor.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace monoid {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate <typename\
    \ T>\nstruct Xor {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for bitwise XOR, which is 0.\n    static constexpr T id() {\n        return\
    \ T(0);\n    }\n\n    // Returns the bitwise XOR of a and b.\n    static constexpr\
    \ T op(const T& a, const T& b) {\n        return a ^ b;\n    }\n\n    static constexpr\
    \ T inv(const T& x) {\n        return x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 6 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\
    \n\n#line 8 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\n#include\
    \ <array>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #include <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n\
    #include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\
    \n#include <random>\n#line 14 \"verify/ds/dsu/persistent_potentialized_dsu.test.cpp\"\
    \n\nstruct Permutation3Group {\n    using value_type = std::array<int, 3>;\n\n\
    \    static value_type id() {\n        return {0, 1, 2};\n    }\n\n    static\
    \ value_type op(const value_type& first, const value_type& second) {\n       \
    \ value_type result;\n        for (int i = 0; i < 3; i++) result[i] = second[first[i]];\n\
    \        return result;\n    }\n\n    static value_type inv(const value_type&\
    \ value) {\n        value_type result;\n        for (int i = 0; i < 3; i++) result[value[i]]\
    \ = i;\n        return result;\n    }\n};\n\nstatic_assert(m1une::monoid::IsGroup<Permutation3Group>);\n\
    \ntemplate <class Group>\nstruct NaivePotentializedDsu {\n    using T = typename\
    \ Group::value_type;\n\n    std::vector<int> parent_or_size;\n    std::vector<T>\
    \ diff_to_parent;\n\n    explicit NaivePotentializedDsu(int n = 0) : parent_or_size(n,\
    \ -1), diff_to_parent(n, Group::id()) {}\n\n    std::pair<int, T> leader_and_potential(int\
    \ a) const {\n        T res = Group::id();\n        while (parent_or_size[a] >=\
    \ 0) {\n            res = Group::op(diff_to_parent[a], res);\n            a =\
    \ parent_or_size[a];\n        }\n        return {a, res};\n    }\n\n    int leader(int\
    \ a) const {\n        return leader_and_potential(a).first;\n    }\n\n    bool\
    \ same(int a, int b) const {\n        return leader(a) == leader(b);\n    }\n\n\
    \    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    T potential(int a) const {\n        return leader_and_potential(a).second;\n\
    \    }\n\n    T diff(int a, int b) const {\n        assert(same(a, b));\n    \
    \    return Group::op(Group::inv(potential(a)), potential(b));\n    }\n\n    std::pair<NaivePotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        NaivePotentializedDsu\
    \ res = *this;\n        auto [x, pa] = res.leader_and_potential(a);\n        auto\
    \ [y, pb] = res.leader_and_potential(b);\n        if (x == y) return {res, Group::op(Group::inv(pa),\
    \ pb) == w};\n\n        int sx = -res.parent_or_size[x];\n        int sy = -res.parent_or_size[y];\n\
    \        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if\
    \ (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n\
    \            y_from_x = Group::inv(y_from_x);\n        }\n        res.parent_or_size[x]\
    \ += res.parent_or_size[y];\n        res.parent_or_size[y] = x;\n        res.diff_to_parent[y]\
    \ = y_from_x;\n        return {res, true};\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nvoid self_test()\
    \ {\n    using Add = m1une::monoid::Add<long long>;\n    using AddDsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \n    AddDsu base(5);\n    auto [a, ok1] = base.merge(0, 1, 3);\n    auto [b,\
    \ ok2] = a.merge(1, 2, 4);\n    auto [c, ok3] = b.merge(3, 4, -2);\n    auto [d,\
    \ ok4] = b.merge(2, 3, 5);\n    auto [bad, ok_bad] = b.merge(0, 2, 8);\n\n   \
    \ assert(ok1);\n    assert(ok2);\n    assert(ok3);\n    assert(ok4);\n    assert(!ok_bad);\n\
    \    assert(base.size() == 5);\n    assert(!base.empty());\n    assert(!base.same(0,\
    \ 2));\n    assert(a.same(0, 1));\n    assert(!a.same(0, 2));\n    assert(b.diff(0,\
    \ 2) == 7);\n    assert(b.diff(2, 0) == -7);\n    assert(c.diff(3, 4) == -2);\n\
    \    assert(!c.same(0, 4));\n    assert(d.diff(0, 3) == 12);\n    assert(bad.diff(0,\
    \ 2) == 7);\n    assert(d.group_size(0) == 4);\n    assert(d.size(0) == 4);\n\
    \    assert(base.group_size(0) == 1);\n    assert(base.parent_or_size(0) == -1);\n\
    \n    std::vector<std::vector<int>> base_groups;\n    base_groups.emplace_back(std::vector<int>{0});\n\
    \    base_groups.emplace_back(std::vector<int>{1});\n    base_groups.emplace_back(std::vector<int>{2});\n\
    \    base_groups.emplace_back(std::vector<int>{3});\n    base_groups.emplace_back(std::vector<int>{4});\n\
    \    assert(base.groups() == base_groups);\n\n    using Xor = m1une::monoid::Xor<int>;\n\
    \    m1une::ds::PersistentPotentializedDsu<Xor> xor_base(4);\n    auto [xor_a,\
    \ xor_ok1] = xor_base.merge(0, 1, 5);\n    auto [xor_b, xor_ok2] = xor_a.merge(1,\
    \ 2, 6);\n    auto [xor_bad, xor_ok_bad] = xor_b.merge(0, 2, 2);\n    assert(xor_ok1);\n\
    \    assert(xor_ok2);\n    assert(!xor_ok_bad);\n    assert(xor_b.diff(0, 2) ==\
    \ (5 ^ 6));\n    assert(xor_bad.diff(0, 2) == (5 ^ 6));\n\n    using Permutation\
    \ = Permutation3Group::value_type;\n    using PermutationDsu =\n        m1une::ds::PersistentPotentializedDsu<Permutation3Group>;\n\
    \    Permutation rotate = {1, 2, 0};\n    Permutation swap_last = {0, 2, 1};\n\
    \    Permutation swap_first = {1, 0, 2};\n    assert(Permutation3Group::op(rotate,\
    \ swap_last) !=\n           Permutation3Group::op(swap_last, rotate));\n\n   \
    \ PermutationDsu permutation_base(4);\n    auto [permutation_a, permutation_ok1]\
    \ =\n        permutation_base.merge(0, 1, rotate);\n    auto [permutation_b, permutation_ok2]\
    \ =\n        permutation_a.merge(1, 2, swap_last);\n    auto [permutation_c, permutation_ok3]\
    \ =\n        permutation_b.merge(3, 2, swap_first);\n    Permutation composed\
    \ = Permutation3Group::op(rotate, swap_last);\n    auto [permutation_bad, permutation_bad_ok]\
    \ =\n        permutation_c.merge(0, 2, Permutation3Group::op(swap_last, rotate));\n\
    \    assert(permutation_ok1);\n    assert(permutation_ok2);\n    assert(permutation_ok3);\n\
    \    assert(!permutation_bad_ok);\n    assert(!permutation_base.same(0, 1));\n\
    \    assert(permutation_b.diff(0, 2) == composed);\n    assert(permutation_b.diff(2,\
    \ 0) == Permutation3Group::inv(composed));\n    assert(permutation_c.diff(3, 2)\
    \ == swap_first);\n    assert(permutation_c.diff(3, 0) == Permutation3Group::op(\n\
    \        swap_first, Permutation3Group::inv(composed)\n    ));\n    assert(permutation_bad.diff(0,\
    \ 2) == composed);\n\n    AddDsu empty;\n    assert(empty.size() == 0);\n    assert(empty.empty());\n\
    \n    std::mt19937 rng(0);\n    constexpr int N = 25;\n    std::vector<std::pair<AddDsu,\
    \ NaivePotentializedDsu<Add>>> versions;\n    versions.emplace_back(AddDsu(N),\
    \ NaivePotentializedDsu<Add>(N));\n\n    for (int step = 0; step < 400; step++)\
    \ {\n        int id = int(rng() % versions.size());\n        AddDsu cur = versions[id].first;\n\
    \        NaivePotentializedDsu<Add> expected = versions[id].second;\n\n      \
    \  for (int i = 0; i < N; i++) {\n            assert(cur.group_size(i) == expected.group_size(i));\n\
    \            assert(cur.parent_or_size(i) == expected.parent_or_size[i]);\n  \
    \          for (int j = 0; j < N; j++) {\n                assert(cur.same(i, j)\
    \ == expected.same(i, j));\n                if (cur.same(i, j)) assert(cur.diff(i,\
    \ j) == expected.diff(i, j));\n            }\n        }\n        assert(cur.groups()\
    \ == expected.groups());\n\n        int u = int(rng() % N);\n        int v = int(rng()\
    \ % N);\n        long long w = int(rng() % 21) - 10;\n        if (expected.same(u,\
    \ v) && (rng() & 1)) w = expected.diff(u, v);\n\n        auto [next, ok] = cur.merge(u,\
    \ v, w);\n        auto [next_expected, expected_ok] = expected.merge(u, v, w);\n\
    \        assert(ok == expected_ok);\n\n        for (int i = 0; i < N; i++) {\n\
    \            assert(cur.group_size(i) == expected.group_size(i));\n          \
    \  assert(next.group_size(i) == next_expected.group_size(i));\n            assert(next.parent_or_size(i)\
    \ == next_expected.parent_or_size[i]);\n        }\n\n        versions.emplace_back(next,\
    \ next_expected);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    self_test();\n\n    using\
    \ Add = m1une::monoid::Add<long long>;\n    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \    int n, q;\n    fast_input >> n >> q;\n    Dsu dsu(n);\n\n    while (q--)\
    \ {\n        int type, x, y;\n        fast_input >> type >> x >> y;\n        if\
    \ (type == 0) {\n            long long z;\n            fast_input >> z;\n    \
    \        auto [next, ok] = dsu.merge(x, y, z);\n            (void)ok;\n      \
    \      dsu = next;\n        } else {\n            if (dsu.same(x, y)) {\n    \
    \            fast_output << dsu.diff(x, y) << '\\n';\n            } else {\n \
    \               fast_output << \"?\\n\";\n            }\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include \"../../../ds/dsu/persistent_potentialized_dsu.hpp\"\n#include \"\
    ../../../monoid/add.hpp\"\n#include \"../../../monoid/xor.hpp\"\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <random>\n#include <utility>\n#include <vector>\n\nstruct Permutation3Group\
    \ {\n    using value_type = std::array<int, 3>;\n\n    static value_type id()\
    \ {\n        return {0, 1, 2};\n    }\n\n    static value_type op(const value_type&\
    \ first, const value_type& second) {\n        value_type result;\n        for\
    \ (int i = 0; i < 3; i++) result[i] = second[first[i]];\n        return result;\n\
    \    }\n\n    static value_type inv(const value_type& value) {\n        value_type\
    \ result;\n        for (int i = 0; i < 3; i++) result[value[i]] = i;\n       \
    \ return result;\n    }\n};\n\nstatic_assert(m1une::monoid::IsGroup<Permutation3Group>);\n\
    \ntemplate <class Group>\nstruct NaivePotentializedDsu {\n    using T = typename\
    \ Group::value_type;\n\n    std::vector<int> parent_or_size;\n    std::vector<T>\
    \ diff_to_parent;\n\n    explicit NaivePotentializedDsu(int n = 0) : parent_or_size(n,\
    \ -1), diff_to_parent(n, Group::id()) {}\n\n    std::pair<int, T> leader_and_potential(int\
    \ a) const {\n        T res = Group::id();\n        while (parent_or_size[a] >=\
    \ 0) {\n            res = Group::op(diff_to_parent[a], res);\n            a =\
    \ parent_or_size[a];\n        }\n        return {a, res};\n    }\n\n    int leader(int\
    \ a) const {\n        return leader_and_potential(a).first;\n    }\n\n    bool\
    \ same(int a, int b) const {\n        return leader(a) == leader(b);\n    }\n\n\
    \    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    T potential(int a) const {\n        return leader_and_potential(a).second;\n\
    \    }\n\n    T diff(int a, int b) const {\n        assert(same(a, b));\n    \
    \    return Group::op(Group::inv(potential(a)), potential(b));\n    }\n\n    std::pair<NaivePotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        NaivePotentializedDsu\
    \ res = *this;\n        auto [x, pa] = res.leader_and_potential(a);\n        auto\
    \ [y, pb] = res.leader_and_potential(b);\n        if (x == y) return {res, Group::op(Group::inv(pa),\
    \ pb) == w};\n\n        int sx = -res.parent_or_size[x];\n        int sy = -res.parent_or_size[y];\n\
    \        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if\
    \ (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n\
    \            y_from_x = Group::inv(y_from_x);\n        }\n        res.parent_or_size[x]\
    \ += res.parent_or_size[y];\n        res.parent_or_size[y] = x;\n        res.diff_to_parent[y]\
    \ = y_from_x;\n        return {res, true};\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        int n = int(parent_or_size.size());\n        std::vector<int>\
    \ leader_buf(n), group_size(n);\n        for (int i = 0; i < n; i++) {\n     \
    \       leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(n);\n        for (int\
    \ i = 0; i < n; i++) result[i].reserve(group_size[i]);\n        for (int i = 0;\
    \ i < n; i++) result[leader_buf[i]].push_back(i);\n        result.erase(std::remove_if(result.begin(),\
    \ result.end(), [](const std::vector<int>& v) { return v.empty(); }),\n      \
    \               result.end());\n        return result;\n    }\n};\n\nvoid self_test()\
    \ {\n    using Add = m1une::monoid::Add<long long>;\n    using AddDsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \n    AddDsu base(5);\n    auto [a, ok1] = base.merge(0, 1, 3);\n    auto [b,\
    \ ok2] = a.merge(1, 2, 4);\n    auto [c, ok3] = b.merge(3, 4, -2);\n    auto [d,\
    \ ok4] = b.merge(2, 3, 5);\n    auto [bad, ok_bad] = b.merge(0, 2, 8);\n\n   \
    \ assert(ok1);\n    assert(ok2);\n    assert(ok3);\n    assert(ok4);\n    assert(!ok_bad);\n\
    \    assert(base.size() == 5);\n    assert(!base.empty());\n    assert(!base.same(0,\
    \ 2));\n    assert(a.same(0, 1));\n    assert(!a.same(0, 2));\n    assert(b.diff(0,\
    \ 2) == 7);\n    assert(b.diff(2, 0) == -7);\n    assert(c.diff(3, 4) == -2);\n\
    \    assert(!c.same(0, 4));\n    assert(d.diff(0, 3) == 12);\n    assert(bad.diff(0,\
    \ 2) == 7);\n    assert(d.group_size(0) == 4);\n    assert(d.size(0) == 4);\n\
    \    assert(base.group_size(0) == 1);\n    assert(base.parent_or_size(0) == -1);\n\
    \n    std::vector<std::vector<int>> base_groups;\n    base_groups.emplace_back(std::vector<int>{0});\n\
    \    base_groups.emplace_back(std::vector<int>{1});\n    base_groups.emplace_back(std::vector<int>{2});\n\
    \    base_groups.emplace_back(std::vector<int>{3});\n    base_groups.emplace_back(std::vector<int>{4});\n\
    \    assert(base.groups() == base_groups);\n\n    using Xor = m1une::monoid::Xor<int>;\n\
    \    m1une::ds::PersistentPotentializedDsu<Xor> xor_base(4);\n    auto [xor_a,\
    \ xor_ok1] = xor_base.merge(0, 1, 5);\n    auto [xor_b, xor_ok2] = xor_a.merge(1,\
    \ 2, 6);\n    auto [xor_bad, xor_ok_bad] = xor_b.merge(0, 2, 2);\n    assert(xor_ok1);\n\
    \    assert(xor_ok2);\n    assert(!xor_ok_bad);\n    assert(xor_b.diff(0, 2) ==\
    \ (5 ^ 6));\n    assert(xor_bad.diff(0, 2) == (5 ^ 6));\n\n    using Permutation\
    \ = Permutation3Group::value_type;\n    using PermutationDsu =\n        m1une::ds::PersistentPotentializedDsu<Permutation3Group>;\n\
    \    Permutation rotate = {1, 2, 0};\n    Permutation swap_last = {0, 2, 1};\n\
    \    Permutation swap_first = {1, 0, 2};\n    assert(Permutation3Group::op(rotate,\
    \ swap_last) !=\n           Permutation3Group::op(swap_last, rotate));\n\n   \
    \ PermutationDsu permutation_base(4);\n    auto [permutation_a, permutation_ok1]\
    \ =\n        permutation_base.merge(0, 1, rotate);\n    auto [permutation_b, permutation_ok2]\
    \ =\n        permutation_a.merge(1, 2, swap_last);\n    auto [permutation_c, permutation_ok3]\
    \ =\n        permutation_b.merge(3, 2, swap_first);\n    Permutation composed\
    \ = Permutation3Group::op(rotate, swap_last);\n    auto [permutation_bad, permutation_bad_ok]\
    \ =\n        permutation_c.merge(0, 2, Permutation3Group::op(swap_last, rotate));\n\
    \    assert(permutation_ok1);\n    assert(permutation_ok2);\n    assert(permutation_ok3);\n\
    \    assert(!permutation_bad_ok);\n    assert(!permutation_base.same(0, 1));\n\
    \    assert(permutation_b.diff(0, 2) == composed);\n    assert(permutation_b.diff(2,\
    \ 0) == Permutation3Group::inv(composed));\n    assert(permutation_c.diff(3, 2)\
    \ == swap_first);\n    assert(permutation_c.diff(3, 0) == Permutation3Group::op(\n\
    \        swap_first, Permutation3Group::inv(composed)\n    ));\n    assert(permutation_bad.diff(0,\
    \ 2) == composed);\n\n    AddDsu empty;\n    assert(empty.size() == 0);\n    assert(empty.empty());\n\
    \n    std::mt19937 rng(0);\n    constexpr int N = 25;\n    std::vector<std::pair<AddDsu,\
    \ NaivePotentializedDsu<Add>>> versions;\n    versions.emplace_back(AddDsu(N),\
    \ NaivePotentializedDsu<Add>(N));\n\n    for (int step = 0; step < 400; step++)\
    \ {\n        int id = int(rng() % versions.size());\n        AddDsu cur = versions[id].first;\n\
    \        NaivePotentializedDsu<Add> expected = versions[id].second;\n\n      \
    \  for (int i = 0; i < N; i++) {\n            assert(cur.group_size(i) == expected.group_size(i));\n\
    \            assert(cur.parent_or_size(i) == expected.parent_or_size[i]);\n  \
    \          for (int j = 0; j < N; j++) {\n                assert(cur.same(i, j)\
    \ == expected.same(i, j));\n                if (cur.same(i, j)) assert(cur.diff(i,\
    \ j) == expected.diff(i, j));\n            }\n        }\n        assert(cur.groups()\
    \ == expected.groups());\n\n        int u = int(rng() % N);\n        int v = int(rng()\
    \ % N);\n        long long w = int(rng() % 21) - 10;\n        if (expected.same(u,\
    \ v) && (rng() & 1)) w = expected.diff(u, v);\n\n        auto [next, ok] = cur.merge(u,\
    \ v, w);\n        auto [next_expected, expected_ok] = expected.merge(u, v, w);\n\
    \        assert(ok == expected_ok);\n\n        for (int i = 0; i < N; i++) {\n\
    \            assert(cur.group_size(i) == expected.group_size(i));\n          \
    \  assert(next.group_size(i) == next_expected.group_size(i));\n            assert(next.parent_or_size(i)\
    \ == next_expected.parent_or_size[i]);\n        }\n\n        versions.emplace_back(next,\
    \ next_expected);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    self_test();\n\n    using\
    \ Add = m1une::monoid::Add<long long>;\n    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;\n\
    \    int n, q;\n    fast_input >> n >> q;\n    Dsu dsu(n);\n\n    while (q--)\
    \ {\n        int type, x, y;\n        fast_input >> type >> x >> y;\n        if\
    \ (type == 0) {\n            long long z;\n            fast_input >> z;\n    \
    \        auto [next, ok] = dsu.merge(x, y, z);\n            (void)ok;\n      \
    \      dsu = next;\n        } else {\n            if (dsu.same(x, y)) {\n    \
    \            fast_output << dsu.diff(x, y) << '\\n';\n            } else {\n \
    \               fast_output << \"?\\n\";\n            }\n        }\n    }\n}\n"
  dependsOn:
  - ds/dsu/persistent_potentialized_dsu.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - monoid/xor.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 20:44:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/persistent_potentialized_dsu.test.cpp
- /verify/verify/ds/dsu/persistent_potentialized_dsu.test.cpp.html
title: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
---
