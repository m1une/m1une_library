---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/sequence/mex.hpp
    title: Mex
  - icon: ':heavy_check_mark:'
    path: ds/bst/mex_multiset.hpp
    title: Mex Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/predecessor_set.hpp
    title: Predecessor Set
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
    PROBLEM: https://yukicoder.me/problems/no/3075
    links:
    - https://yukicoder.me/problems/no/3075
  bundledCode: "#line 1 \"verify/ds/bst/mex_multiset.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/3075\"\n\n#line 1 \"algo/sequence/mex.hpp\"\n\
    \n\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Returns the smallest\
    \ nonnegative integer absent from values.\ntemplate <class T>\nint mex(const std::vector<T>&\
    \ values) {\n    static_assert(\n        std::is_integral_v<T> && sizeof(T) <=\
    \ sizeof(std::uintmax_t),\n        \"mex requires standard integral values\"\n\
    \    );\n    assert(values.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n\
    \    const int n = int(values.size());\n    std::vector<unsigned char> present(n,\
    \ 0);\n    for (T value : values) {\n        if constexpr (std::is_signed_v<T>)\
    \ {\n            if (value < 0) continue;\n        }\n        if (static_cast<std::uintmax_t>(value)\
    \ < static_cast<std::uintmax_t>(n)) {\n            present[int(value)] = 1;\n\
    \        }\n    }\n    int answer = 0;\n    while (answer < n && present[answer])\
    \ ++answer;\n    return answer;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/bst/mex_multiset.hpp\"\n\n\n\n#line 7 \"ds/bst/mex_multiset.hpp\"\
    \n#include <string>\n#line 10 \"ds/bst/mex_multiset.hpp\"\n\n#line 1 \"ds/bst/predecessor_set.hpp\"\
    \n\n\n\n#include <bit>\n#line 8 \"ds/bst/predecessor_set.hpp\"\n#include <string_view>\n\
    #line 10 \"ds/bst/predecessor_set.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// Fixed-universe integer set with predecessor and successor queries.\nstruct\
    \ PredecessorSet {\n   private:\n    static constexpr int word_bits = 64;\n\n\
    \    int _universe_size;\n    int _size;\n    std::vector<std::vector<std::uint64_t>>\
    \ _levels;\n\n    static int checked_size(std::string_view membership) {\n   \
    \     assert(\n            membership.size()\n            <= static_cast<std::size_t>(std::numeric_limits<int>::max())\n\
    \        );\n        return int(membership.size());\n    }\n\n    int next_index(int\
    \ index) const {\n        if (index >= _universe_size) return _universe_size;\n\
    \        for (int level = 0; level < int(_levels.size()); level++) {\n       \
    \     if (index / word_bits >= int(_levels[level].size())) break;\n          \
    \  std::uint64_t word =\n                _levels[level][index / word_bits] >>\
    \ (index % word_bits);\n            if (word == 0) {\n                index =\
    \ index / word_bits + 1;\n                continue;\n            }\n         \
    \   index += int(std::countr_zero(word));\n            for (int lower = level\
    \ - 1; lower >= 0; lower--) {\n                index *= word_bits;\n         \
    \       std::uint64_t lower_word =\n                    _levels[lower][index /\
    \ word_bits];\n                index += int(std::countr_zero(lower_word));\n \
    \           }\n            return index;\n        }\n        return _universe_size;\n\
    \    }\n\n    int previous_index(int index) const {\n        if (_universe_size\
    \ == 0 || index < 0) return -1;\n        if (index >= _universe_size) index =\
    \ _universe_size - 1;\n        for (int level = 0; level < int(_levels.size());\
    \ level++) {\n            int offset = index % word_bits;\n            std::uint64_t\
    \ word = _levels[level][index / word_bits];\n            if (offset != word_bits\
    \ - 1) {\n                word &= (std::uint64_t(1) << (offset + 1)) - 1;\n  \
    \          }\n            if (word == 0) {\n                index = index / word_bits\
    \ - 1;\n                if (index < 0) break;\n                continue;\n   \
    \         }\n            index += word_bits - 1 - int(std::countl_zero(word))\
    \ - offset;\n            for (int lower = level - 1; lower >= 0; lower--) {\n\
    \                index *= word_bits;\n                std::uint64_t lower_word\
    \ =\n                    _levels[lower][index / word_bits];\n                index\
    \ += word_bits - 1 - int(std::countl_zero(lower_word));\n            }\n     \
    \       return index;\n        }\n        return -1;\n    }\n\n    static int\
    \ not_found_if_end(int index, int universe_size) {\n        return index == universe_size\
    \ ? -1 : index;\n    }\n\n   public:\n    PredecessorSet() : PredecessorSet(0)\
    \ {}\n\n    explicit PredecessorSet(int universe_size)\n        : _universe_size(universe_size),\
    \ _size(0) {\n        assert(universe_size >= 0);\n        int length = universe_size\
    \ == 0 ? 1 : universe_size;\n        do {\n            int words = int((std::int64_t(length)\
    \ + word_bits - 1) / word_bits);\n            _levels.emplace_back(words, 0);\n\
    \            length = words;\n        } while (length > 1);\n    }\n\n    explicit\
    \ PredecessorSet(std::string_view membership)\n        : PredecessorSet(checked_size(membership))\
    \ {\n        for (int index = 0; index < _universe_size; index++) {\n        \
    \    assert(membership[index] == '0' || membership[index] == '1');\n         \
    \   if (membership[index] == '1') {\n                _levels[0][index / word_bits]\n\
    \                    |= std::uint64_t(1) << (index % word_bits);\n           \
    \     _size++;\n            }\n        }\n        for (int level = 1; level <\
    \ int(_levels.size()); level++) {\n            for (int index = 0; index < int(_levels[level\
    \ - 1].size()); index++) {\n                if (_levels[level - 1][index] != 0)\
    \ {\n                    _levels[level][index / word_bits]\n                 \
    \       |= std::uint64_t(1) << (index % word_bits);\n                }\n     \
    \       }\n        }\n    }\n\n    int universe_size() const {\n        return\
    \ _universe_size;\n    }\n\n    int size() const {\n        return _size;\n  \
    \  }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\n    bool\
    \ contains(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return ((_levels[0][key / word_bits] >> (key % word_bits)) & 1U) != 0;\n\
    \    }\n\n    bool insert(int key) {\n        assert(0 <= key && key < _universe_size);\n\
    \        if (contains(key)) return false;\n        int index = key;\n        for\
    \ (auto& level : _levels) {\n            std::uint64_t& word = level[index / word_bits];\n\
    \            bool was_empty = word == 0;\n            word |= std::uint64_t(1)\
    \ << (index % word_bits);\n            if (!was_empty) break;\n            index\
    \ /= word_bits;\n        }\n        _size++;\n        return true;\n    }\n\n\
    \    bool erase(int key) {\n        assert(0 <= key && key < _universe_size);\n\
    \        if (!contains(key)) return false;\n        int index = key;\n       \
    \ for (auto& level : _levels) {\n            std::uint64_t& word = level[index\
    \ / word_bits];\n            word &= ~(std::uint64_t(1) << (index % word_bits));\n\
    \            if (word != 0) break;\n            index /= word_bits;\n        }\n\
    \        _size--;\n        return true;\n    }\n\n    // Returns the smallest\
    \ key greater than or equal to key, or -1.\n    int successor(int key) const {\n\
    \        assert(0 <= key && key < _universe_size);\n        return not_found_if_end(next_index(key),\
    \ _universe_size);\n    }\n\n    // Returns the largest key less than or equal\
    \ to key, or -1.\n    int predecessor(int key) const {\n        assert(0 <= key\
    \ && key < _universe_size);\n        return previous_index(key);\n    }\n\n  \
    \  int min_ge(int key) const {\n        return successor(key);\n    }\n\n    int\
    \ min_gt(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return not_found_if_end(next_index(key + 1), _universe_size);\n    }\n\
    \n    int max_le(int key) const {\n        return predecessor(key);\n    }\n\n\
    \    int max_lt(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return previous_index(key - 1);\n    }\n\n    int min() const {\n   \
    \     return not_found_if_end(next_index(0), _universe_size);\n    }\n\n    int\
    \ max() const {\n        return previous_index(_universe_size - 1);\n    }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"ds/bst/mex_multiset.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Tracks multiplicities in [0, U) and\
    \ returns min(actual mex, U).\nstruct MexMultiset {\n   private:\n    std::vector<int>\
    \ _count;\n    PredecessorSet _missing;\n    int _mex;\n\n    static int checked_universe_size(int\
    \ universe_size) {\n        assert(universe_size >= 0);\n        return universe_size;\n\
    \    }\n\n    static int checked_size(std::size_t size) {\n        assert(size\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n        return\
    \ int(size);\n    }\n\n   public:\n    MexMultiset() : MexMultiset(0) {}\n\n \
    \   explicit MexMultiset(int universe_size)\n        : _count(checked_universe_size(universe_size),\
    \ 0),\n          _missing(std::string(universe_size, '1')), _mex(0) {}\n\n   \
    \ template <class T>\n    explicit MexMultiset(const std::vector<T>& values)\n\
    \        : _count(checked_size(values.size()), 0), _missing(0), _mex(0) {\n  \
    \      static_assert(\n            std::is_integral_v<T> && sizeof(T) <= sizeof(std::uintmax_t),\n\
    \            \"MexMultiset requires standard integral values\"\n        );\n \
    \       const int n = universe_size();\n        for (T value : values) {\n   \
    \         if constexpr (std::is_signed_v<T>) {\n                if (value < 0)\
    \ continue;\n            }\n            if (static_cast<std::uintmax_t>(value)\
    \ < static_cast<std::uintmax_t>(n)) {\n                ++_count[int(value)];\n\
    \            }\n        }\n        std::string membership(n, '1');\n        for\
    \ (int value = 0; value < n; ++value) {\n            if (_count[value] != 0) membership[value]\
    \ = '0';\n        }\n        _missing = PredecessorSet(membership);\n        const\
    \ int first = _missing.min();\n        _mex = first == -1 ? n : first;\n    }\n\
    \n    int universe_size() const {\n        return int(_count.size());\n    }\n\
    \n    int count(long long value) const {\n        if (value < 0 || value >= universe_size())\
    \ return 0;\n        return _count[int(value)];\n    }\n\n    void insert(long\
    \ long value) {\n        if (value < 0 || value >= universe_size()) return;\n\
    \        const int key = int(value);\n        assert(_count[key] < std::numeric_limits<int>::max());\n\
    \        if (_count[key]++ != 0) return;\n        _missing.erase(key);\n     \
    \   if (key == _mex) {\n            const int first = _missing.min();\n      \
    \      _mex = first == -1 ? universe_size() : first;\n        }\n    }\n\n   \
    \ // Removes one occurrence; returns false for absent or untracked values.\n \
    \   bool erase(long long value) {\n        if (value < 0 || value >= universe_size())\
    \ return false;\n        const int key = int(value);\n        if (_count[key]\
    \ == 0) return false;\n        if (--_count[key] == 0) {\n            _missing.insert(key);\n\
    \            if (key < _mex) _mex = key;\n        }\n        return true;\n  \
    \  }\n\n    int mex() const {\n        return _mex;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cerrno>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#line 15 \"utilities/fast_io.hpp\"\n\
    #include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\n#include <utility>\n\
    #include <unistd.h>\n#line 20 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\n\
    namespace utilities {\n\nstruct FastOutput;\n\nnamespace internal {\n\n// Shared\
    \ with the convenience helpers in template.hpp.\ninline FastOutput* standard_output_instance\
    \ = nullptr;\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class\
    \ = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\nstruct\
    \ is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n  \
    \  decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
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
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \    char _range_separator;\n    std::string* _capture = nullptr;\n\n    template\
    \ <class T>\n    std::string format_cell(const T& value) {\n        std::string\
    \ result;\n        struct CaptureGuard {\n            std::string*& target;\n\
    \            std::string* previous;\n            ~CaptureGuard() { target = previous;\
    \ }\n        } guard{_capture, _capture};\n        _capture = &result;\n     \
    \   write(value);\n        return result;\n    }\n\n    template <class Matrix>\n\
    \    void write_aligned_matrix(const Matrix& matrix) {\n        std::vector<std::vector<std::string>>\
    \ rows;\n        std::vector<std::size_t> widths;\n        for (const auto& row\
    \ : matrix) {\n            auto& cells = rows.emplace_back();\n            std::size_t\
    \ column = 0;\n            for (const auto& value : row) {\n                cells.push_back(format_cell(value));\n\
    \                if (column == widths.size()) widths.push_back(0);\n         \
    \       widths[column] = std::max(widths[column], cells.back().size());\n    \
    \            ++column;\n            }\n        }\n        bool first = true;\n\
    \        for (const auto& row : rows) {\n            if (!first) write_char('\\\
    n');\n            first = false;\n            for (std::size_t column = 0; column\
    \ < row.size(); ++column) {\n                if (column != 0) write_char(_range_separator);\n\
    \                for (std::size_t padding = row[column].size();\n            \
    \         padding < widths[column]; ++padding) {\n                    write_char('\
    \ ');\n                }\n                write(row[column]);\n            }\n\
    \        }\n    }\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream),\n          _position(0),\n          _precision(6),\n\
    \          _float_format(std::chars_format::general),\n          _range_separator('\
    \ ') {\n        if (_stream == stdout\n            && internal::standard_output_instance\
    \ == nullptr) {\n            internal::standard_output_instance = this;\n    \
    \    }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \        if (internal::standard_output_instance == this) {\n            internal::standard_output_instance\
    \ = nullptr;\n        }\n    }\n\n    void flush() {\n        if (_position !=\
    \ 0) {\n            std::fwrite(_buffer, 1, _position, _stream);\n           \
    \ _position = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void\
    \ write_char(char c) {\n        if (_capture != nullptr) {\n            _capture->push_back(c);\n\
    \            return;\n        }\n        if (_position == buffer_size) flush();\n\
    \        _buffer[_position++] = c;\n    }\n\n    void write(const char* s) {\n\
    \        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        if (_capture != nullptr) {\n            _capture->append(s);\n\
    \            return;\n        }\n        std::size_t position = 0;\n        while\
    \ (position < s.size()) {\n            if (_position == buffer_size) flush();\n\
    \            const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
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
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_capture\
    \ == nullptr && _position > buffer_size - 64) flush();\n        char captured[64];\n\
    \        char* const begin = _capture != nullptr ? captured : _buffer + _position;\n\
    \        char* destination = begin;\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) *destination++ = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(destination, digits, 4);\n            destination +=\
    \ 4;\n        }\n        if (_capture != nullptr) {\n            _capture->append(begin,\
    \ destination - begin);\n        } else {\n            _position += int(destination\
    \ - begin);\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
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
    \    _range_separator = separator;\n    }\n\n    template <class Matrix>\n   \
    \ void write_aligned(const Matrix& matrix) {\n        using Row = internal::range_stored_value_t<const\
    \ Matrix>;\n        using Cell = internal::range_stored_value_t<const Row>;\n\
    \        static_assert(internal::is_range_v<Row> && !internal::is_string_like_v<Row>,\n\
    \                      \"write_aligned requires a two-dimensional range\");\n\
    \        static_assert(!internal::is_range_v<Cell> || internal::is_string_like_v<Cell>,\n\
    \                      \"write_aligned requires scalar cells\");\n        write_aligned_matrix(matrix);\n\
    \    }\n\n    template <class Matrix>\n    void println_aligned(const Matrix&\
    \ matrix) {\n        write_aligned(matrix);\n        write_char('\\n');\n    }\n\
    \n    template <class... Args>\n    void println(const Args&... args) {\n    \
    \    print(args...);\n        write_char('\\n');\n    }\n\n    template <class\
    \ T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n  \
    \      return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 6 \"verify/ds/bst/mex_multiset.test.cpp\"\n\n#line 11 \"verify/ds/bst/mex_multiset.test.cpp\"\
    \n#include <numeric>\n#include <random>\n#include <set>\n#line 15 \"verify/ds/bst/mex_multiset.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class T>\nint naive_mex(const std::vector<T>& values)\
    \ {\n    std::set<T> present(values.begin(), values.end());\n    int answer =\
    \ 0;\n    while (present.contains(T(answer))) ++answer;\n    return answer;\n\
    }\n\nvoid test_static() {\n    using m1une::algo::mex;\n    assert(mex(std::vector<int>())\
    \ == 0);\n    assert(mex(std::vector<int>{0, 1, 1, 3}) == 2);\n    assert(mex(std::vector<int>{1,\
    \ 2, 3}) == 0);\n    assert(mex(std::vector<long long>{\n        std::numeric_limits<long\
    \ long>::min(), 0, 1,\n        std::numeric_limits<long long>::max()\n    }) ==\
    \ 2);\n    assert(mex(std::vector<std::uint64_t>{\n        0, 1, std::numeric_limits<std::uint64_t>::max()\n\
    \    }) == 2);\n    assert(mex(std::vector<bool>{false, true}) == 2);\n\n    //\
    \ Exhaust all short vectors over an alphabet containing a negative value.\n  \
    \  int cases = 1;\n    for (int n = 0; n <= 6; ++n, cases *= 6) {\n        for\
    \ (int code = 0; code < cases; ++code) {\n            int remaining = code;\n\
    \            std::vector<int> values(n);\n            for (int& value : values)\
    \ {\n                value = remaining % 6 - 1;\n                remaining /=\
    \ 6;\n            }\n            const auto original = values;\n            assert(mex(values)\
    \ == naive_mex(values));\n            assert(values == original);\n        }\n\
    \    }\n\n    std::mt19937_64 random(1602176623);\n    for (int iteration = 0;\
    \ iteration < 5000; ++iteration) {\n        const int n = int(random() % 200);\n\
    \        std::vector<long long> values(n);\n        for (long long& value : values)\
    \ {\n            value = static_cast<long long>(random() % (2 * n + 3)) - n /\
    \ 2;\n        }\n        assert(mex(values) == naive_mex(values));\n        std::vector<std::uint64_t>\
    \ unsigned_values(n);\n        for (auto& value : unsigned_values) {\n       \
    \     value = random() % 3 == 0 ? random() : random() % (n + 1);\n        }\n\
    \        assert(mex(unsigned_values) == naive_mex(unsigned_values));\n    }\n\
    }\n\nvoid test_boundaries() {\n    using m1une::ds::MexMultiset;\n    MexMultiset\
    \ empty;\n    assert(empty.universe_size() == 0);\n    empty.insert(0);\n    empty.insert(-1);\n\
    \    assert(!empty.erase(0));\n    assert(empty.count(0) == 0);\n    assert(empty.mex()\
    \ == 0);\n\n    for (int n : {0, 1, 2, 63, 64, 65, 127, 128, 129, 4095, 4096,\
    \ 4097, 262145}) {\n        MexMultiset values(n);\n        const MexMultiset&\
    \ query = values;\n        for (int value = 0; value < n; ++value) {\n       \
    \     assert(query.mex() == value);\n            values.insert(value);\n     \
    \       values.insert(value);\n            assert(query.count(value) == 2);\n\
    \            assert(query.mex() == value + 1);\n            assert(values.erase(value));\n\
    \            assert(query.mex() == value + 1);\n        }\n        assert(query.mex()\
    \ == n);\n        values.insert(std::numeric_limits<long long>::min());\n    \
    \    values.insert(std::numeric_limits<long long>::max());\n        values.insert(n);\n\
    \        assert(!values.erase(-1));\n        assert(!values.erase(n));\n     \
    \   assert(query.count(-1) == 0);\n        assert(query.count(n) == 0);\n    \
    \    assert(query.mex() == n);\n\n        const MexMultiset original = values;\n\
    \        for (int hole : {0, 63, 64, 127, 128, 4095, 4096, 262143, 262144}) {\n\
    \            if (hole >= n) continue;\n            assert(values.erase(hole));\n\
    \            assert(!values.erase(hole));\n            assert(query.mex() == hole);\n\
    \            assert(original.mex() == n);\n            values.insert(hole);\n\
    \            assert(query.mex() == n);\n        }\n        for (int value = n\
    \ - 1; value >= 0; --value) {\n            assert(values.erase(value));\n    \
    \        assert(query.mex() == value);\n        }\n\n        std::vector<int>\
    \ permutation(n);\n        std::iota(permutation.begin(), permutation.end(), 0);\n\
    \        const MexMultiset built(permutation);\n        assert(built.universe_size()\
    \ == n);\n        assert(built.mex() == n);\n    }\n\n    const MexMultiset wide(std::vector<std::uint64_t>{\n\
    \        0, 1, std::numeric_limits<std::uint64_t>::max()\n    });\n    assert(wide.mex()\
    \ == 2);\n    assert(wide.count(0) == 1);\n    assert(wide.count(1) == 1);\n \
    \   assert(wide.count(2) == 0);\n    assert(MexMultiset(std::vector<bool>{false,\
    \ true}).mex() == 2);\n}\n\nvoid test_randomized_updates() {\n    std::mt19937\
    \ random(314159265);\n    for (int iteration = 0; iteration < 100; ++iteration)\
    \ {\n        const int n = int(random() % 257);\n        std::vector<long long>\
    \ initial(n);\n        std::vector<int> counts(n, 0);\n        for (long long&\
    \ value : initial) {\n            value = int(random() % (n + 7)) - 3;\n     \
    \       if (0 <= value && value < n) ++counts[int(value)];\n        }\n      \
    \  m1une::ds::MexMultiset values(initial);\n        assert(values.mex() == naive_mex(initial));\n\
    \        for (int step = 0; step < 2000; ++step) {\n            const int key\
    \ = int(random() % (n + 7)) - 3;\n            if (random() % 2 == 0) {\n     \
    \           values.insert(key);\n                if (0 <= key && key < n) ++counts[key];\n\
    \            } else {\n                const bool exists = 0 <= key && key < n\
    \ && counts[key] != 0;\n                assert(values.erase(key) == exists);\n\
    \                if (exists) --counts[key];\n            }\n            int expected\
    \ = 0;\n            while (expected < n && counts[expected] != 0) ++expected;\n\
    \            assert(values.mex() == expected);\n            assert(values.count(key)\
    \ == (0 <= key && key < n ? counts[key] : 0));\n        }\n    }\n}\n\nlong long\
    \ recurrence_term(std::vector<long long> window, long long index) {\n    const\
    \ int n = int(window.size());\n    if (index <= n) return window[int(index - 1)];\n\
    \    m1une::ds::MexMultiset values(window);\n    assert(values.mex() == m1une::algo::mex(window));\n\
    \    std::vector<int> period(n + 1);\n    for (int step = 0; step <= n; ++step)\
    \ {\n        const int next = values.mex();\n        period[step] = next;\n  \
    \      values.erase(window[step % n]);\n        values.insert(next);\n       \
    \ window[step % n] = next;\n    }\n    // Consecutive generated terms cannot repeat\
    \ within N positions.\n    // These N+1 terms are therefore a permutation of [0,\
    \ N], which repeats.\n    return period[static_cast<std::size_t>((index - n -\
    \ 1) % (n + 1))];\n}\n\nvoid test_recurrence() {\n    std::mt19937 random(271828182);\n\
    \    for (int iteration = 0; iteration < 300; ++iteration) {\n        const int\
    \ n = 1 + int(random() % 30);\n        std::vector<long long> initial(n);\n  \
    \      for (auto& value : initial) value = random() % (2 * n + 5);\n        std::vector<long\
    \ long> sequence = initial;\n        for (int index = n; index < 5 * n + 10; ++index)\
    \ {\n            std::vector<long long> window(sequence.end() - n, sequence.end());\n\
    \            sequence.push_back(naive_mex(window));\n        }\n        for (int\
    \ index = 1; index <= int(sequence.size()); ++index) {\n            assert(recurrence_term(initial,\
    \ index) == sequence[index - 1]);\n        }\n        const long long distant\
    \ = 1000000000000000000LL;\n        const int equivalent = n + 1 + int((distant\
    \ - n - 1) % (n + 1));\n        assert(recurrence_term(initial, distant) == sequence[equivalent\
    \ - 1]);\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_static();\n  \
    \  test_boundaries();\n    test_randomized_updates();\n    test_recurrence();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    int n = 0;\n    long long index = 0;\n    input.read(n, index);\n    std::vector<long\
    \ long> initial(n);\n    for (auto& value : initial) input.read(value);\n    output.println(recurrence_term(initial,\
    \ index));\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/3075\"\n\n#include \"\
    ../../../algo/sequence/mex.hpp\"\n#include \"../../../ds/bst/mex_multiset.hpp\"\
    \n#include \"../../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <limits>\n#include <numeric>\n#include\
    \ <random>\n#include <set>\n#include <vector>\n\nnamespace {\n\ntemplate <class\
    \ T>\nint naive_mex(const std::vector<T>& values) {\n    std::set<T> present(values.begin(),\
    \ values.end());\n    int answer = 0;\n    while (present.contains(T(answer)))\
    \ ++answer;\n    return answer;\n}\n\nvoid test_static() {\n    using m1une::algo::mex;\n\
    \    assert(mex(std::vector<int>()) == 0);\n    assert(mex(std::vector<int>{0,\
    \ 1, 1, 3}) == 2);\n    assert(mex(std::vector<int>{1, 2, 3}) == 0);\n    assert(mex(std::vector<long\
    \ long>{\n        std::numeric_limits<long long>::min(), 0, 1,\n        std::numeric_limits<long\
    \ long>::max()\n    }) == 2);\n    assert(mex(std::vector<std::uint64_t>{\n  \
    \      0, 1, std::numeric_limits<std::uint64_t>::max()\n    }) == 2);\n    assert(mex(std::vector<bool>{false,\
    \ true}) == 2);\n\n    // Exhaust all short vectors over an alphabet containing\
    \ a negative value.\n    int cases = 1;\n    for (int n = 0; n <= 6; ++n, cases\
    \ *= 6) {\n        for (int code = 0; code < cases; ++code) {\n            int\
    \ remaining = code;\n            std::vector<int> values(n);\n            for\
    \ (int& value : values) {\n                value = remaining % 6 - 1;\n      \
    \          remaining /= 6;\n            }\n            const auto original = values;\n\
    \            assert(mex(values) == naive_mex(values));\n            assert(values\
    \ == original);\n        }\n    }\n\n    std::mt19937_64 random(1602176623);\n\
    \    for (int iteration = 0; iteration < 5000; ++iteration) {\n        const int\
    \ n = int(random() % 200);\n        std::vector<long long> values(n);\n      \
    \  for (long long& value : values) {\n            value = static_cast<long long>(random()\
    \ % (2 * n + 3)) - n / 2;\n        }\n        assert(mex(values) == naive_mex(values));\n\
    \        std::vector<std::uint64_t> unsigned_values(n);\n        for (auto& value\
    \ : unsigned_values) {\n            value = random() % 3 == 0 ? random() : random()\
    \ % (n + 1);\n        }\n        assert(mex(unsigned_values) == naive_mex(unsigned_values));\n\
    \    }\n}\n\nvoid test_boundaries() {\n    using m1une::ds::MexMultiset;\n   \
    \ MexMultiset empty;\n    assert(empty.universe_size() == 0);\n    empty.insert(0);\n\
    \    empty.insert(-1);\n    assert(!empty.erase(0));\n    assert(empty.count(0)\
    \ == 0);\n    assert(empty.mex() == 0);\n\n    for (int n : {0, 1, 2, 63, 64,\
    \ 65, 127, 128, 129, 4095, 4096, 4097, 262145}) {\n        MexMultiset values(n);\n\
    \        const MexMultiset& query = values;\n        for (int value = 0; value\
    \ < n; ++value) {\n            assert(query.mex() == value);\n            values.insert(value);\n\
    \            values.insert(value);\n            assert(query.count(value) == 2);\n\
    \            assert(query.mex() == value + 1);\n            assert(values.erase(value));\n\
    \            assert(query.mex() == value + 1);\n        }\n        assert(query.mex()\
    \ == n);\n        values.insert(std::numeric_limits<long long>::min());\n    \
    \    values.insert(std::numeric_limits<long long>::max());\n        values.insert(n);\n\
    \        assert(!values.erase(-1));\n        assert(!values.erase(n));\n     \
    \   assert(query.count(-1) == 0);\n        assert(query.count(n) == 0);\n    \
    \    assert(query.mex() == n);\n\n        const MexMultiset original = values;\n\
    \        for (int hole : {0, 63, 64, 127, 128, 4095, 4096, 262143, 262144}) {\n\
    \            if (hole >= n) continue;\n            assert(values.erase(hole));\n\
    \            assert(!values.erase(hole));\n            assert(query.mex() == hole);\n\
    \            assert(original.mex() == n);\n            values.insert(hole);\n\
    \            assert(query.mex() == n);\n        }\n        for (int value = n\
    \ - 1; value >= 0; --value) {\n            assert(values.erase(value));\n    \
    \        assert(query.mex() == value);\n        }\n\n        std::vector<int>\
    \ permutation(n);\n        std::iota(permutation.begin(), permutation.end(), 0);\n\
    \        const MexMultiset built(permutation);\n        assert(built.universe_size()\
    \ == n);\n        assert(built.mex() == n);\n    }\n\n    const MexMultiset wide(std::vector<std::uint64_t>{\n\
    \        0, 1, std::numeric_limits<std::uint64_t>::max()\n    });\n    assert(wide.mex()\
    \ == 2);\n    assert(wide.count(0) == 1);\n    assert(wide.count(1) == 1);\n \
    \   assert(wide.count(2) == 0);\n    assert(MexMultiset(std::vector<bool>{false,\
    \ true}).mex() == 2);\n}\n\nvoid test_randomized_updates() {\n    std::mt19937\
    \ random(314159265);\n    for (int iteration = 0; iteration < 100; ++iteration)\
    \ {\n        const int n = int(random() % 257);\n        std::vector<long long>\
    \ initial(n);\n        std::vector<int> counts(n, 0);\n        for (long long&\
    \ value : initial) {\n            value = int(random() % (n + 7)) - 3;\n     \
    \       if (0 <= value && value < n) ++counts[int(value)];\n        }\n      \
    \  m1une::ds::MexMultiset values(initial);\n        assert(values.mex() == naive_mex(initial));\n\
    \        for (int step = 0; step < 2000; ++step) {\n            const int key\
    \ = int(random() % (n + 7)) - 3;\n            if (random() % 2 == 0) {\n     \
    \           values.insert(key);\n                if (0 <= key && key < n) ++counts[key];\n\
    \            } else {\n                const bool exists = 0 <= key && key < n\
    \ && counts[key] != 0;\n                assert(values.erase(key) == exists);\n\
    \                if (exists) --counts[key];\n            }\n            int expected\
    \ = 0;\n            while (expected < n && counts[expected] != 0) ++expected;\n\
    \            assert(values.mex() == expected);\n            assert(values.count(key)\
    \ == (0 <= key && key < n ? counts[key] : 0));\n        }\n    }\n}\n\nlong long\
    \ recurrence_term(std::vector<long long> window, long long index) {\n    const\
    \ int n = int(window.size());\n    if (index <= n) return window[int(index - 1)];\n\
    \    m1une::ds::MexMultiset values(window);\n    assert(values.mex() == m1une::algo::mex(window));\n\
    \    std::vector<int> period(n + 1);\n    for (int step = 0; step <= n; ++step)\
    \ {\n        const int next = values.mex();\n        period[step] = next;\n  \
    \      values.erase(window[step % n]);\n        values.insert(next);\n       \
    \ window[step % n] = next;\n    }\n    // Consecutive generated terms cannot repeat\
    \ within N positions.\n    // These N+1 terms are therefore a permutation of [0,\
    \ N], which repeats.\n    return period[static_cast<std::size_t>((index - n -\
    \ 1) % (n + 1))];\n}\n\nvoid test_recurrence() {\n    std::mt19937 random(271828182);\n\
    \    for (int iteration = 0; iteration < 300; ++iteration) {\n        const int\
    \ n = 1 + int(random() % 30);\n        std::vector<long long> initial(n);\n  \
    \      for (auto& value : initial) value = random() % (2 * n + 5);\n        std::vector<long\
    \ long> sequence = initial;\n        for (int index = n; index < 5 * n + 10; ++index)\
    \ {\n            std::vector<long long> window(sequence.end() - n, sequence.end());\n\
    \            sequence.push_back(naive_mex(window));\n        }\n        for (int\
    \ index = 1; index <= int(sequence.size()); ++index) {\n            assert(recurrence_term(initial,\
    \ index) == sequence[index - 1]);\n        }\n        const long long distant\
    \ = 1000000000000000000LL;\n        const int equivalent = n + 1 + int((distant\
    \ - n - 1) % (n + 1));\n        assert(recurrence_term(initial, distant) == sequence[equivalent\
    \ - 1]);\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_static();\n  \
    \  test_boundaries();\n    test_randomized_updates();\n    test_recurrence();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    int n = 0;\n    long long index = 0;\n    input.read(n, index);\n    std::vector<long\
    \ long> initial(n);\n    for (auto& value : initial) input.read(value);\n    output.println(recurrence_term(initial,\
    \ index));\n}\n"
  dependsOn:
  - algo/sequence/mex.hpp
  - ds/bst/mex_multiset.hpp
  - ds/bst/predecessor_set.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/bst/mex_multiset.test.cpp
  requiredBy: []
  timestamp: '2026-10-06 02:15:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/mex_multiset.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/mex_multiset.test.cpp
- /verify/verify/ds/bst/mex_multiset.test.cpp.html
title: verify/ds/bst/mex_multiset.test.cpp
---
