---
data:
  _extendedDependsOn:
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
    PROBLEM: https://judge.yosupo.jp/problem/predecessor_problem
    links:
    - https://judge.yosupo.jp/problem/predecessor_problem
  bundledCode: "#line 1 \"verify/ds/bst/predecessor_set.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\n#line 1 \"ds/bst/predecessor_set.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <cstdint>\n#include <limits>\n\
    #include <string_view>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\
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
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <cstddef>\n#include <cstdio>\n#line 8 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    verify/ds/bst/predecessor_set.test.cpp\"\n\n#line 8 \"verify/ds/bst/predecessor_set.test.cpp\"\
    \n#include <set>\n#line 10 \"verify/ds/bst/predecessor_set.test.cpp\"\n\nnamespace\
    \ {\n\nint expected_successor(const std::set<int>& expected, int key) {\n    auto\
    \ iterator = expected.lower_bound(key);\n    return iterator == expected.end()\
    \ ? -1 : *iterator;\n}\n\nint expected_strict_successor(const std::set<int>& expected,\
    \ int key) {\n    auto iterator = expected.upper_bound(key);\n    return iterator\
    \ == expected.end() ? -1 : *iterator;\n}\n\nint expected_predecessor(const std::set<int>&\
    \ expected, int key) {\n    auto iterator = expected.upper_bound(key);\n    if\
    \ (iterator == expected.begin()) return -1;\n    return *--iterator;\n}\n\nint\
    \ expected_strict_predecessor(const std::set<int>& expected, int key) {\n    auto\
    \ iterator = expected.lower_bound(key);\n    if (iterator == expected.begin())\
    \ return -1;\n    return *--iterator;\n}\n\nvoid test_randomized() {\n    m1une::ds::PredecessorSet\
    \ empty;\n    assert(empty.universe_size() == 0);\n    assert(empty.size() ==\
    \ 0);\n    assert(empty.empty());\n    assert(empty.min() == -1);\n    assert(empty.max()\
    \ == -1);\n\n    constexpr int universe_size = 5000;\n    std::uint64_t state\
    \ = 1602176623ULL;\n    auto random = [&]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    std::string\
    \ membership(universe_size, '0');\n    std::set<int> expected;\n    for (int key\
    \ = 0; key < universe_size; key++) {\n        if (random() % 11 == 0) {\n    \
    \        membership[key] = '1';\n            expected.insert(key);\n        }\n\
    \    }\n    m1une::ds::PredecessorSet set(membership);\n    assert(set.universe_size()\
    \ == universe_size);\n    assert(set.size() == int(expected.size()));\n\n    for\
    \ (int query = 0; query < 50000; query++) {\n        int key = int(random() %\
    \ universe_size);\n        int type = int(random() % 7);\n        if (type ==\
    \ 0) {\n            assert(set.insert(key) == expected.insert(key).second);\n\
    \        } else if (type == 1) {\n            assert(set.erase(key) == (expected.erase(key)\
    \ != 0));\n        } else if (type == 2) {\n            assert(set.contains(key)\
    \ == expected.contains(key));\n        } else if (type == 3) {\n            int\
    \ answer = expected_successor(expected, key);\n            assert(set.successor(key)\
    \ == answer);\n            assert(set.min_ge(key) == answer);\n        } else\
    \ if (type == 4) {\n            int answer = expected_predecessor(expected, key);\n\
    \            assert(set.predecessor(key) == answer);\n            assert(set.max_le(key)\
    \ == answer);\n        } else if (type == 5) {\n            assert(set.min_gt(key)\
    \ == expected_strict_successor(expected, key));\n        } else {\n          \
    \  assert(set.max_lt(key) == expected_strict_predecessor(expected, key));\n  \
    \      }\n\n        if (query % 1000 == 0) {\n            assert(set.size() ==\
    \ int(expected.size()));\n            assert(set.empty() == expected.empty());\n\
    \            assert(set.min() == expected_successor(expected, 0));\n         \
    \   assert(set.max() == expected_predecessor(expected, universe_size - 1));\n\
    \            for (int boundary : {0, 63, 64, 4095, 4096, universe_size - 1}) {\n\
    \                assert(set.contains(boundary) == expected.contains(boundary));\n\
    \                assert(set.successor(boundary) == expected_successor(expected,\
    \ boundary));\n                assert(set.predecessor(boundary) == expected_predecessor(expected,\
    \ boundary));\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_randomized();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    int n = 0, query_count = 0;\n    std::string membership;\n  \
    \  input.read(n, query_count, membership);\n    m1une::ds::PredecessorSet set(membership);\n\
    \    assert(set.universe_size() == n);\n\n    while (query_count--) {\n      \
    \  int type = 0, key = 0;\n        input.read(type, key);\n        if (type ==\
    \ 0) {\n            set.insert(key);\n        } else if (type == 1) {\n      \
    \      set.erase(key);\n        } else if (type == 2) {\n            output.println(set.contains(key));\n\
    \        } else if (type == 3) {\n            output.println(set.successor(key));\n\
    \        } else {\n            output.println(set.predecessor(key));\n       \
    \ }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\
    \n#include \"../../../ds/bst/predecessor_set.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <set>\n#include <string>\n\
    \nnamespace {\n\nint expected_successor(const std::set<int>& expected, int key)\
    \ {\n    auto iterator = expected.lower_bound(key);\n    return iterator == expected.end()\
    \ ? -1 : *iterator;\n}\n\nint expected_strict_successor(const std::set<int>& expected,\
    \ int key) {\n    auto iterator = expected.upper_bound(key);\n    return iterator\
    \ == expected.end() ? -1 : *iterator;\n}\n\nint expected_predecessor(const std::set<int>&\
    \ expected, int key) {\n    auto iterator = expected.upper_bound(key);\n    if\
    \ (iterator == expected.begin()) return -1;\n    return *--iterator;\n}\n\nint\
    \ expected_strict_predecessor(const std::set<int>& expected, int key) {\n    auto\
    \ iterator = expected.lower_bound(key);\n    if (iterator == expected.begin())\
    \ return -1;\n    return *--iterator;\n}\n\nvoid test_randomized() {\n    m1une::ds::PredecessorSet\
    \ empty;\n    assert(empty.universe_size() == 0);\n    assert(empty.size() ==\
    \ 0);\n    assert(empty.empty());\n    assert(empty.min() == -1);\n    assert(empty.max()\
    \ == -1);\n\n    constexpr int universe_size = 5000;\n    std::uint64_t state\
    \ = 1602176623ULL;\n    auto random = [&]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    std::string\
    \ membership(universe_size, '0');\n    std::set<int> expected;\n    for (int key\
    \ = 0; key < universe_size; key++) {\n        if (random() % 11 == 0) {\n    \
    \        membership[key] = '1';\n            expected.insert(key);\n        }\n\
    \    }\n    m1une::ds::PredecessorSet set(membership);\n    assert(set.universe_size()\
    \ == universe_size);\n    assert(set.size() == int(expected.size()));\n\n    for\
    \ (int query = 0; query < 50000; query++) {\n        int key = int(random() %\
    \ universe_size);\n        int type = int(random() % 7);\n        if (type ==\
    \ 0) {\n            assert(set.insert(key) == expected.insert(key).second);\n\
    \        } else if (type == 1) {\n            assert(set.erase(key) == (expected.erase(key)\
    \ != 0));\n        } else if (type == 2) {\n            assert(set.contains(key)\
    \ == expected.contains(key));\n        } else if (type == 3) {\n            int\
    \ answer = expected_successor(expected, key);\n            assert(set.successor(key)\
    \ == answer);\n            assert(set.min_ge(key) == answer);\n        } else\
    \ if (type == 4) {\n            int answer = expected_predecessor(expected, key);\n\
    \            assert(set.predecessor(key) == answer);\n            assert(set.max_le(key)\
    \ == answer);\n        } else if (type == 5) {\n            assert(set.min_gt(key)\
    \ == expected_strict_successor(expected, key));\n        } else {\n          \
    \  assert(set.max_lt(key) == expected_strict_predecessor(expected, key));\n  \
    \      }\n\n        if (query % 1000 == 0) {\n            assert(set.size() ==\
    \ int(expected.size()));\n            assert(set.empty() == expected.empty());\n\
    \            assert(set.min() == expected_successor(expected, 0));\n         \
    \   assert(set.max() == expected_predecessor(expected, universe_size - 1));\n\
    \            for (int boundary : {0, 63, 64, 4095, 4096, universe_size - 1}) {\n\
    \                assert(set.contains(boundary) == expected.contains(boundary));\n\
    \                assert(set.successor(boundary) == expected_successor(expected,\
    \ boundary));\n                assert(set.predecessor(boundary) == expected_predecessor(expected,\
    \ boundary));\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_randomized();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    int n = 0, query_count = 0;\n    std::string membership;\n  \
    \  input.read(n, query_count, membership);\n    m1une::ds::PredecessorSet set(membership);\n\
    \    assert(set.universe_size() == n);\n\n    while (query_count--) {\n      \
    \  int type = 0, key = 0;\n        input.read(type, key);\n        if (type ==\
    \ 0) {\n            set.insert(key);\n        } else if (type == 1) {\n      \
    \      set.erase(key);\n        } else if (type == 2) {\n            output.println(set.contains(key));\n\
    \        } else if (type == 3) {\n            output.println(set.successor(key));\n\
    \        } else {\n            output.println(set.predecessor(key));\n       \
    \ }\n    }\n}\n"
  dependsOn:
  - ds/bst/predecessor_set.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/bst/predecessor_set.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 01:33:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/predecessor_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/predecessor_set.test.cpp
- /verify/verify/ds/bst/predecessor_set.test.cpp.html
title: verify/ds/bst/predecessor_set.test.cpp
---
