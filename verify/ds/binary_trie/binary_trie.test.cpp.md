---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/binary_trie/binary_trie.hpp
    title: Binary Trie
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
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "#line 1 \"verify/ds/binary_trie/binary_trie.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#line 1 \"ds/binary_trie/binary_trie.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <initializer_list>\n\
    #include <limits>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename UInt = std::uint32_t, int BitWidth =\
    \ std::numeric_limits<UInt>::digits>\nstruct BinaryTrie {\n    static_assert(std::is_integral_v<UInt>);\n\
    \    static_assert(std::is_unsigned_v<UInt>);\n    static_assert(!std::is_same_v<UInt,\
    \ bool>);\n    static_assert(0 < BitWidth);\n    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);\n\
    \n    using node_id = int;\n    static constexpr node_id null_node = -1;\n\n \
    \   struct Node {\n        node_id child[2];\n        int count;\n\n        Node()\
    \ : child{null_node, null_node}, count(0) {}\n    };\n\n   private:\n    std::vector<Node>\
    \ nodes;\n    UInt lazy_xor;\n\n    static constexpr int bit(UInt value, int position)\
    \ {\n        return int((value >> position) & UInt(1));\n    }\n\n    static constexpr\
    \ UInt value_mask() {\n        if constexpr (BitWidth == std::numeric_limits<UInt>::digits)\
    \ {\n            return std::numeric_limits<UInt>::max();\n        } else {\n\
    \            return (UInt(1) << BitWidth) - UInt(1);\n        }\n    }\n\n   \
    \ static constexpr bool valid_value(UInt value) {\n        return (value & ~value_mask())\
    \ == UInt(0);\n    }\n\n    node_id new_node() {\n        nodes.emplace_back();\n\
    \        return int(nodes.size()) - 1;\n    }\n\n    int subtree_size(node_id\
    \ node) const {\n        return node == null_node ? 0 : nodes[node].count;\n \
    \   }\n\n    node_id find_node(UInt value) const {\n        node_id node = 0;\n\
    \        value ^= lazy_xor;\n        for (int position = BitWidth - 1; position\
    \ >= 0; --position) {\n            node = nodes[node].child[bit(value, position)];\n\
    \            if (node == null_node || nodes[node].count == 0) {\n            \
    \    return null_node;\n            }\n        }\n        return node;\n    }\n\
    \n   public:\n    BinaryTrie() : nodes(1), lazy_xor(0) {}\n\n    BinaryTrie(std::initializer_list<UInt>\
    \ init) : BinaryTrie() {\n        for (UInt value : init) insert(value);\n   \
    \ }\n\n    template <typename Iterator>\n    BinaryTrie(Iterator first, Iterator\
    \ last) : BinaryTrie() {\n        while (first != last) {\n            insert(*first);\n\
    \            ++first;\n        }\n    }\n\n    int size() const {\n        return\
    \ nodes[0].count;\n    }\n\n    bool empty() const {\n        return size() ==\
    \ 0;\n    }\n\n    node_id root() const {\n        return 0;\n    }\n\n    const\
    \ Node& node(node_id id) const {\n        assert(0 <= id && std::size_t(id) <\
    \ nodes.size());\n        return nodes[id];\n    }\n\n    node_id find(UInt value)\
    \ const {\n        assert(valid_value(value));\n        return find_node(value);\n\
    \    }\n\n    std::size_t node_count() const {\n        return nodes.size();\n\
    \    }\n\n    void reserve(std::size_t node_capacity) {\n        nodes.reserve(node_capacity);\n\
    \    }\n\n    UInt xor_mask() const {\n        return lazy_xor;\n    }\n\n   \
    \ void clear() {\n        nodes.clear();\n        nodes.emplace_back();\n    \
    \    lazy_xor = 0;\n    }\n\n    node_id insert(UInt value, int multiplicity =\
    \ 1) {\n        assert(valid_value(value));\n        assert(multiplicity > 0);\n\
    \        value ^= lazy_xor;\n        node_id node = 0;\n        nodes[node].count\
    \ += multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            const int direction = bit(value, position);\n            if (nodes[node].child[direction]\
    \ == null_node) {\n                const node_id child = new_node();\n       \
    \         nodes[node].child[direction] = child;\n            }\n            node\
    \ = nodes[node].child[direction];\n            nodes[node].count += multiplicity;\n\
    \        }\n        return node;\n    }\n\n    int count(UInt value) const {\n\
    \        assert(valid_value(value));\n        const node_id node = find_node(value);\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    bool\
    \ contains(UInt value) const {\n        return count(value) > 0;\n    }\n\n  \
    \  bool erase_one(UInt value) {\n        assert(valid_value(value));\n       \
    \ if (!contains(value)) return false;\n        value ^= lazy_xor;\n        int\
    \ node = 0;\n        --nodes[node].count;\n        for (int position = BitWidth\
    \ - 1; position >= 0; --position) {\n            node = nodes[node].child[bit(value,\
    \ position)];\n            --nodes[node].count;\n        }\n        return true;\n\
    \    }\n\n    bool erase(UInt value) {\n        return erase_one(value);\n   \
    \ }\n\n    int erase_all(UInt value) {\n        assert(valid_value(value));\n\
    \        const int multiplicity = count(value);\n        if (multiplicity == 0)\
    \ return 0;\n        value ^= lazy_xor;\n        int node = 0;\n        nodes[node].count\
    \ -= multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            node = nodes[node].child[bit(value, position)];\n           \
    \ nodes[node].count -= multiplicity;\n        }\n        return multiplicity;\n\
    \    }\n\n    void xor_all(UInt value) {\n        assert(valid_value(value));\n\
    \        lazy_xor ^= value;\n    }\n\n    UInt kth_xor(int k, UInt value) const\
    \ {\n        assert(0 <= k && k < size());\n        assert(valid_value(value));\n\
    \        const UInt effective_xor = lazy_xor ^ value;\n        UInt result = 0;\n\
    \        int node = 0;\n        for (int position = BitWidth - 1; position >=\
    \ 0; --position) {\n            const int preferred = bit(effective_xor, position);\n\
    \            const int preferred_size = subtree_size(nodes[node].child[preferred]);\n\
    \            if (k < preferred_size) {\n                node = nodes[node].child[preferred];\n\
    \            } else {\n                k -= preferred_size;\n                node\
    \ = nodes[node].child[preferred ^ 1];\n                result |= UInt(1) << position;\n\
    \            }\n        }\n        return result;\n    }\n\n    UInt kth(int k)\
    \ const {\n        return kth_xor(k, 0);\n    }\n\n    UInt min() const {\n  \
    \      return kth(0);\n    }\n\n    UInt max() const {\n        return kth(size()\
    \ - 1);\n    }\n\n    UInt min_xor(UInt value) const {\n        return kth_xor(0,\
    \ value);\n    }\n\n    UInt max_xor(UInt value) const {\n        return kth_xor(size()\
    \ - 1, value);\n    }\n\n    int count_less_xor(UInt value, UInt upper) const\
    \ {\n        assert(valid_value(value));\n        if (!valid_value(upper)) return\
    \ size();\n        const UInt effective_xor = lazy_xor ^ value;\n        int result\
    \ = 0;\n        int node = 0;\n        for (int position = BitWidth - 1; position\
    \ >= 0 && node != -1; --position) {\n            const int zero = bit(effective_xor,\
    \ position);\n            if (bit(upper, position) == 1) {\n                result\
    \ += subtree_size(nodes[node].child[zero]);\n                node = nodes[node].child[zero\
    \ ^ 1];\n            } else {\n                node = nodes[node].child[zero];\n\
    \            }\n        }\n        return result;\n    }\n\n    int count_xor_less(UInt\
    \ value, UInt upper) const {\n        return count_less_xor(value, upper);\n \
    \   }\n\n    int count_xor_less_equal(UInt value, UInt upper) const {\n      \
    \  assert(valid_value(value));\n        assert(valid_value(upper));\n        if\
    \ (upper == value_mask()) return size();\n        return count_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    int count_xor_greater(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return size() - count_xor_less_equal(value, lower);\n    }\n\n    int\
    \ count_xor_greater_equal(UInt value, UInt lower) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        return size() - count_xor_less(value,\
    \ lower);\n    }\n\n    int count_xor_range(UInt value, UInt lower, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        assert(lower <= upper);\n        return count_xor_less(value, upper)\
    \ -\n               count_xor_less(value, lower);\n    }\n\n    int order_of_key(UInt\
    \ value) const {\n        return count_less_xor(0, value);\n    }\n\n    int count_less(UInt\
    \ value) const {\n        return order_of_key(value);\n    }\n\n    int count_less_equal(UInt\
    \ value) const {\n        assert(valid_value(value));\n        if (value == value_mask())\
    \ return size();\n        return count_less(value + UInt(1));\n    }\n\n    int\
    \ count_greater(UInt value) const {\n        return size() - count_less_equal(value);\n\
    \    }\n\n    int count_greater_equal(UInt value) const {\n        return size()\
    \ - count_less(value);\n    }\n\n    std::vector<UInt> to_vector() const {\n \
    \       std::vector<UInt> result;\n        result.reserve(size());\n        for\
    \ (int k = 0; k < size(); ++k) {\n            result.push_back(kth(k));\n    \
    \    }\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/ds/binary_trie/binary_trie.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include\
    \ <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 16 \"utilities/fast_io.hpp\"\
    \n#include <utility>\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
    \ {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
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
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
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
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/ds/binary_trie/binary_trie.test.cpp\"\
    \n#include <set>\n#line 13 \"verify/ds/binary_trie/binary_trie.test.cpp\"\n\n\
    void unit_test() {\n    using Trie = m1une::ds::BinaryTrie<std::uint32_t, 10>;\n\
    \n    Trie basic;\n    basic.reserve(64);\n    const auto five_node = basic.insert(5,\
    \ 3);\n    basic.insert(9);\n    assert(basic.root() == 0);\n    assert(basic.find(5)\
    \ == five_node);\n    assert(basic.find(7) == Trie::null_node);\n    assert(basic.node(basic.root()).count\
    \ == 4);\n    assert(basic.node(five_node).count == 3);\n    assert(basic.node_count()\
    \ == 1 + 10 + 4);\n    assert(basic.count(5) == 3);\n    assert(basic.kth_xor(0,\
    \ 7) == (5U ^ 7U));\n    assert(basic.erase_one(5));\n    assert(basic.erase_all(5)\
    \ == 2);\n    basic.xor_all(6);\n    assert(basic.xor_mask() == 6);\n    assert(basic.find(9U\
    \ ^ 6U) != Trie::null_node);\n    assert(basic.contains(9U ^ 6U));\n    basic.clear();\n\
    \    assert(basic.node_count() == 1);\n    assert(basic.xor_mask() == 0);\n  \
    \  basic.insert(1023);\n    assert(basic.count_less_equal(1023) == 1);\n    assert(basic.count_less_xor(0,\
    \ 1024) == 1);\n\n    Trie trie;\n    std::multiset<std::uint32_t> expected;\n\
    \    std::uint64_t seed = 123456789;\n\n    for (int query = 0; query < 10000;\
    \ ++query) {\n        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        const std::uint32_t value = std::uint32_t(seed >> 32) & 1023U;\n    \
    \    const int type = int(seed % 7);\n\n        if (type <= 1) {\n           \
    \ trie.insert(value);\n            expected.insert(value);\n        } else if\
    \ (type == 2) {\n            const bool erased = trie.erase_one(value);\n    \
    \        auto it = expected.find(value);\n            assert(erased == (it !=\
    \ expected.end()));\n            if (it != expected.end()) expected.erase(it);\n\
    \        } else if (type == 3) {\n            const int erased = trie.erase_all(value);\n\
    \            assert(erased == int(expected.count(value)));\n            expected.erase(value);\n\
    \        } else if (type == 4) {\n            trie.xor_all(value);\n         \
    \   std::multiset<std::uint32_t> transformed;\n            for (std::uint32_t\
    \ element : expected) {\n                transformed.insert(element ^ value);\n\
    \            }\n            expected = std::move(transformed);\n        } else\
    \ if (type == 5) {\n            assert(trie.count(value) == int(expected.count(value)));\n\
    \            assert(trie.count_less(value) ==\n                   int(std::distance(expected.begin(),\
    \ expected.lower_bound(value))));\n            assert(trie.count_less_equal(value)\
    \ ==\n                   int(std::distance(expected.begin(), expected.upper_bound(value))));\n\
    \        } else if (!expected.empty()) {\n            std::vector<std::uint32_t>\
    \ xor_values;\n            xor_values.reserve(expected.size());\n            for\
    \ (std::uint32_t element : expected) {\n                xor_values.push_back(element\
    \ ^ value);\n            }\n            std::sort(xor_values.begin(), xor_values.end());\n\
    \            assert(trie.min_xor(value) == xor_values.front());\n            assert(trie.max_xor(value)\
    \ == xor_values.back());\n            assert(trie.count_less_xor(value, 512) ==\n\
    \                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less(value,\
    \ 512) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less_equal(value,\
    \ 512) ==\n                   int(std::upper_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_greater(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::upper_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_greater_equal(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::lower_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_range(value, 200,\
    \ 800) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 800) -\n                       std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 200)));\n        }\n\n        assert(trie.size() == int(expected.size()));\n\
    \        assert(trie.empty() == expected.empty());\n        if (!expected.empty())\
    \ {\n            assert(trie.min() == *expected.begin());\n            assert(trie.max()\
    \ == *expected.rbegin());\n            const int k = int(seed % expected.size());\n\
    \            auto it = expected.begin();\n            std::advance(it, k);\n \
    \           assert(trie.kth(k) == *it);\n        }\n    }\n\n    assert(trie.to_vector()\
    \ ==\n           std::vector<std::uint32_t>(expected.begin(), expected.end()));\n\
    \    trie.clear();\n    assert(trie.empty());\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    unit_test();\n\
    \n    int query_count;\n    fast_input >> query_count;\n\n    m1une::ds::BinaryTrie<std::uint32_t,\
    \ 30> trie;\n    while (query_count--) {\n        int type;\n        std::uint32_t\
    \ value;\n        fast_input >> type >> value;\n\n        if (type == 0) {\n \
    \           if (!trie.contains(value)) trie.insert(value);\n        } else if\
    \ (type == 1) {\n            trie.erase(value);\n        } else {\n          \
    \  fast_output << trie.min_xor(value) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#include\
    \ \"../../../ds/binary_trie/binary_trie.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\n\
    #include <iterator>\n#include <set>\n#include <utility>\n#include <vector>\n\n\
    void unit_test() {\n    using Trie = m1une::ds::BinaryTrie<std::uint32_t, 10>;\n\
    \n    Trie basic;\n    basic.reserve(64);\n    const auto five_node = basic.insert(5,\
    \ 3);\n    basic.insert(9);\n    assert(basic.root() == 0);\n    assert(basic.find(5)\
    \ == five_node);\n    assert(basic.find(7) == Trie::null_node);\n    assert(basic.node(basic.root()).count\
    \ == 4);\n    assert(basic.node(five_node).count == 3);\n    assert(basic.node_count()\
    \ == 1 + 10 + 4);\n    assert(basic.count(5) == 3);\n    assert(basic.kth_xor(0,\
    \ 7) == (5U ^ 7U));\n    assert(basic.erase_one(5));\n    assert(basic.erase_all(5)\
    \ == 2);\n    basic.xor_all(6);\n    assert(basic.xor_mask() == 6);\n    assert(basic.find(9U\
    \ ^ 6U) != Trie::null_node);\n    assert(basic.contains(9U ^ 6U));\n    basic.clear();\n\
    \    assert(basic.node_count() == 1);\n    assert(basic.xor_mask() == 0);\n  \
    \  basic.insert(1023);\n    assert(basic.count_less_equal(1023) == 1);\n    assert(basic.count_less_xor(0,\
    \ 1024) == 1);\n\n    Trie trie;\n    std::multiset<std::uint32_t> expected;\n\
    \    std::uint64_t seed = 123456789;\n\n    for (int query = 0; query < 10000;\
    \ ++query) {\n        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        const std::uint32_t value = std::uint32_t(seed >> 32) & 1023U;\n    \
    \    const int type = int(seed % 7);\n\n        if (type <= 1) {\n           \
    \ trie.insert(value);\n            expected.insert(value);\n        } else if\
    \ (type == 2) {\n            const bool erased = trie.erase_one(value);\n    \
    \        auto it = expected.find(value);\n            assert(erased == (it !=\
    \ expected.end()));\n            if (it != expected.end()) expected.erase(it);\n\
    \        } else if (type == 3) {\n            const int erased = trie.erase_all(value);\n\
    \            assert(erased == int(expected.count(value)));\n            expected.erase(value);\n\
    \        } else if (type == 4) {\n            trie.xor_all(value);\n         \
    \   std::multiset<std::uint32_t> transformed;\n            for (std::uint32_t\
    \ element : expected) {\n                transformed.insert(element ^ value);\n\
    \            }\n            expected = std::move(transformed);\n        } else\
    \ if (type == 5) {\n            assert(trie.count(value) == int(expected.count(value)));\n\
    \            assert(trie.count_less(value) ==\n                   int(std::distance(expected.begin(),\
    \ expected.lower_bound(value))));\n            assert(trie.count_less_equal(value)\
    \ ==\n                   int(std::distance(expected.begin(), expected.upper_bound(value))));\n\
    \        } else if (!expected.empty()) {\n            std::vector<std::uint32_t>\
    \ xor_values;\n            xor_values.reserve(expected.size());\n            for\
    \ (std::uint32_t element : expected) {\n                xor_values.push_back(element\
    \ ^ value);\n            }\n            std::sort(xor_values.begin(), xor_values.end());\n\
    \            assert(trie.min_xor(value) == xor_values.front());\n            assert(trie.max_xor(value)\
    \ == xor_values.back());\n            assert(trie.count_less_xor(value, 512) ==\n\
    \                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less(value,\
    \ 512) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less_equal(value,\
    \ 512) ==\n                   int(std::upper_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_greater(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::upper_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_greater_equal(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::lower_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_range(value, 200,\
    \ 800) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 800) -\n                       std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 200)));\n        }\n\n        assert(trie.size() == int(expected.size()));\n\
    \        assert(trie.empty() == expected.empty());\n        if (!expected.empty())\
    \ {\n            assert(trie.min() == *expected.begin());\n            assert(trie.max()\
    \ == *expected.rbegin());\n            const int k = int(seed % expected.size());\n\
    \            auto it = expected.begin();\n            std::advance(it, k);\n \
    \           assert(trie.kth(k) == *it);\n        }\n    }\n\n    assert(trie.to_vector()\
    \ ==\n           std::vector<std::uint32_t>(expected.begin(), expected.end()));\n\
    \    trie.clear();\n    assert(trie.empty());\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    unit_test();\n\
    \n    int query_count;\n    fast_input >> query_count;\n\n    m1une::ds::BinaryTrie<std::uint32_t,\
    \ 30> trie;\n    while (query_count--) {\n        int type;\n        std::uint32_t\
    \ value;\n        fast_input >> type >> value;\n\n        if (type == 0) {\n \
    \           if (!trie.contains(value)) trie.insert(value);\n        } else if\
    \ (type == 1) {\n            trie.erase(value);\n        } else {\n          \
    \  fast_output << trie.min_xor(value) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/binary_trie/binary_trie.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/binary_trie/binary_trie.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/binary_trie/binary_trie.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/binary_trie/binary_trie.test.cpp
- /verify/verify/ds/binary_trie/binary_trie.test.cpp.html
title: verify/ds/binary_trie/binary_trie.test.cpp
---
