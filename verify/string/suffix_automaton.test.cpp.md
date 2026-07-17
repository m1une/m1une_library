---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.hpp
    title: Suffix Automaton
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
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"verify/string/suffix_automaton.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\n#line 1 \"string/suffix_automaton.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\n\
    struct SuffixAutomaton {\n    static_assert(0 < AlphabetSize);\n\n    using state_id\
    \ = int;\n    static constexpr state_id root_state = 0;\n    static constexpr\
    \ state_id null_state = -1;\n\n    struct State {\n        std::array<state_id,\
    \ AlphabetSize> next;\n        state_id suffix_link;\n        int length;\n  \
    \      int first_end;\n        int direct_occurrences;\n        bool clone;\n\n\
    \        State(int length_value = 0)\n            : suffix_link(null_state),\n\
    \              length(length_value),\n              first_end(0),\n          \
    \    direct_occurrences(0),\n              clone(false) {\n            next.fill(null_state);\n\
    \        }\n    };\n\n   private:\n    std::vector<State> _states;\n    state_id\
    \ _last;\n    int _text_length;\n\n    template <class Symbol>\n    static int\
    \ symbol_index(const Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n\
    \        assert(0 <= index && index < AlphabetSize);\n        return index;\n\
    \    }\n\n    state_id new_state(int length) {\n        assert(_states.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _states.emplace_back(length);\n\
    \        return int(_states.size()) - 1;\n    }\n\n   public:\n    SuffixAutomaton()\
    \ {\n        clear();\n    }\n\n    template <class Sequence>\n    explicit SuffixAutomaton(const\
    \ Sequence& sequence) {\n        clear();\n        build(sequence);\n    }\n\n\
    \    int state_count() const {\n        return int(_states.size());\n    }\n\n\
    \    int size() const {\n        return state_count();\n    }\n\n    bool empty()\
    \ const {\n        return _text_length == 0;\n    }\n\n    int text_length() const\
    \ {\n        return _text_length;\n    }\n\n    state_id root() const {\n    \
    \    return root_state;\n    }\n\n    state_id last() const {\n        return\
    \ _last;\n    }\n\n    const State& state(state_id id) const {\n        assert(0\
    \ <= id && id < state_count());\n        return _states[id];\n    }\n\n    const\
    \ std::vector<State>& states() const {\n        return _states;\n    }\n\n   \
    \ int minimum_length(state_id id) const {\n        assert(0 <= id && id < state_count());\n\
    \        return id == root_state ? 0 : _states[_states[id].suffix_link].length\
    \ + 1;\n    }\n\n    template <class Symbol>\n    state_id transition(state_id\
    \ id, const Symbol& symbol) const {\n        assert(0 <= id && id < state_count());\n\
    \        return _states[id].next[symbol_index(symbol)];\n    }\n\n    void reserve(std::size_t\
    \ text_capacity) {\n        _states.reserve(2 * text_capacity);\n    }\n\n   \
    \ void clear() {\n        _states.clear();\n        _states.emplace_back();\n\
    \        _last = root_state;\n        _text_length = 0;\n    }\n\n    template\
    \ <class Symbol>\n    state_id add(const Symbol& value) {\n        int symbol\
    \ = symbol_index(value);\n        assert(_text_length < std::numeric_limits<int>::max());\n\
    \        _text_length++;\n\n        state_id current = new_state(_states[_last].length\
    \ + 1);\n        _states[current].first_end = _text_length;\n        _states[current].direct_occurrences\
    \ = 1;\n\n        state_id p = _last;\n        while (p != null_state && _states[p].next[symbol]\
    \ == null_state) {\n            _states[p].next[symbol] = current;\n         \
    \   p = _states[p].suffix_link;\n        }\n\n        if (p == null_state) {\n\
    \            _states[current].suffix_link = root_state;\n        } else {\n  \
    \          state_id q = _states[p].next[symbol];\n            if (_states[p].length\
    \ + 1 == _states[q].length) {\n                _states[current].suffix_link =\
    \ q;\n            } else {\n                state_id clone = new_state(_states[p].length\
    \ + 1);\n                _states[clone] = _states[q];\n                _states[clone].length\
    \ = _states[p].length + 1;\n                _states[clone].direct_occurrences\
    \ = 0;\n                _states[clone].clone = true;\n\n                while\
    \ (p != null_state && _states[p].next[symbol] == q) {\n                    _states[p].next[symbol]\
    \ = clone;\n                    p = _states[p].suffix_link;\n                }\n\
    \                _states[q].suffix_link = clone;\n                _states[current].suffix_link\
    \ = clone;\n            }\n        }\n\n        _last = current;\n        return\
    \ current;\n    }\n\n    template <class Sequence>\n    void build(const Sequence&\
    \ sequence) {\n        for (const auto& symbol : sequence) add(symbol);\n    }\n\
    \n    template <class Sequence>\n    state_id find(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        for (const auto& symbol :\
    \ sequence) {\n            current = transition(current, symbol);\n          \
    \  if (current == null_state) return null_state;\n        }\n        return current;\n\
    \    }\n\n    template <class Sequence>\n    bool contains(const Sequence& sequence)\
    \ const {\n        return find(sequence) != null_state;\n    }\n\n    std::vector<state_id>\
    \ length_order() const {\n        std::vector<int> count(_text_length + 1, 0);\n\
    \        for (const State& current : _states) count[current.length]++;\n     \
    \   for (int length = 1; length <= _text_length; length++) count[length] += count[length\
    \ - 1];\n\n        std::vector<state_id> order(state_count());\n        for (state_id\
    \ id = state_count() - 1; id >= 0; id--) {\n            order[--count[_states[id].length]]\
    \ = id;\n        }\n        return order;\n    }\n\n    std::vector<long long>\
    \ occurrence_counts() const {\n        std::vector<long long> result(state_count(),\
    \ 0);\n        for (state_id id = 0; id < state_count(); id++) {\n           \
    \ result[id] = _states[id].direct_occurrences;\n        }\n        std::vector<state_id>\
    \ order = length_order();\n        for (int i = int(order.size()) - 1; i > 0;\
    \ i--) {\n            state_id id = order[i];\n            result[_states[id].suffix_link]\
    \ += result[id];\n        }\n        return result;\n    }\n\n    std::vector<bool>\
    \ terminal_states() const {\n        std::vector<bool> result(state_count(), false);\n\
    \        for (state_id id = _last; id != null_state; id = _states[id].suffix_link)\
    \ {\n            result[id] = true;\n        }\n        return result;\n    }\n\
    \n    long long distinct_substring_count() const {\n        long long result =\
    \ 0;\n        for (state_id id = 1; id < state_count(); id++) {\n            result\
    \ += _states[id].length - _states[_states[id].suffix_link].length;\n        }\n\
    \        return result;\n    }\n\n    std::pair<int, int> longest_representative(state_id\
    \ id) const {\n        assert(0 <= id && id < state_count());\n        int end\
    \ = _states[id].first_end;\n        return {end - _states[id].length, end};\n\
    \    }\n\n    template <class Sequence>\n    std::pair<int, int> representative_occurrence(const\
    \ Sequence& sequence) const {\n        state_id id = root_state;\n        int\
    \ length = 0;\n        for (const auto& symbol : sequence) {\n            id =\
    \ transition(id, symbol);\n            if (id == null_state) return {-1, -1};\n\
    \            length++;\n        }\n        int end = _states[id].first_end;\n\
    \        return {end - length, end};\n    }\n\n    template <class Sequence>\n\
    \    std::pair<int, int> longest_common_substring(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        int current_length = 0;\n\
    \        int best_length = 0;\n        int best_end = 0;\n        int end = 0;\n\
    \n        for (const auto& value : sequence) {\n            int symbol = symbol_index(value);\n\
    \            while (current != root_state && _states[current].next[symbol] ==\
    \ null_state) {\n                current = _states[current].suffix_link;\n   \
    \             current_length = std::min(current_length, _states[current].length);\n\
    \            }\n            state_id next = _states[current].next[symbol];\n \
    \           if (next == null_state) {\n                current = root_state;\n\
    \                current_length = 0;\n            } else {\n                current\
    \ = next;\n                current_length++;\n            }\n            end++;\n\
    \            if (best_length < current_length) {\n                best_length\
    \ = current_length;\n                best_end = end;\n            }\n        }\n\
    \        return {best_end - best_length, best_end};\n    }\n};\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/suffix_automaton.test.cpp\"\
    \n\n#line 7 \"verify/string/suffix_automaton.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n#include <cstdio>\n\
    #include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
    #line 17 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/string/suffix_automaton.test.cpp\"\
    \n#include <map>\n#include <set>\n#line 14 \"verify/string/suffix_automaton.test.cpp\"\
    \n\nnamespace {\n\nvoid test_features() {\n    using Automaton = m1une::string::SuffixAutomaton<>;\n\
    \    Automaton automaton;\n    automaton.reserve(16);\n    assert(automaton.empty());\n\
    \    assert(automaton.state_count() == 1);\n    assert(automaton.root() == Automaton::root_state);\n\
    \    assert(automaton.last() == automaton.root());\n\n    std::string text = \"\
    ababa\";\n    for (char character : text) automaton.add(character);\n    assert(!automaton.empty());\n\
    \    assert(automaton.text_length() == 5);\n    assert(automaton.state(automaton.last()).length\
    \ == 5);\n    assert(automaton.contains(std::string(\"bab\")));\n    assert(!automaton.contains(std::string(\"\
    abb\")));\n    assert(automaton.contains(std::string()));\n    assert(automaton.transition(automaton.root(),\
    \ 'a') == automaton.find(std::string(\"a\")));\n    assert(automaton.distinct_substring_count()\
    \ == 9);\n\n    std::vector<long long> count = automaton.occurrence_counts();\n\
    \    assert(count[automaton.root()] == 5);\n    assert(count[automaton.find(std::string(\"\
    a\"))] == 3);\n    assert(count[automaton.find(std::string(\"b\"))] == 2);\n \
    \   assert(count[automaton.find(std::string(\"aba\"))] == 2);\n    assert(count[automaton.find(std::string(\"\
    ababa\"))] == 1);\n\n    auto occurrence = automaton.representative_occurrence(std::string(\"\
    bab\"));\n    assert(text.substr(occurrence.first, occurrence.second - occurrence.first)\
    \ == \"bab\");\n    assert((automaton.representative_occurrence(std::string(\"\
    x\")) == std::pair<int, int>({-1, -1})));\n\n    std::vector<bool> terminal =\
    \ automaton.terminal_states();\n    assert(terminal[automaton.root()]);\n    for\
    \ (int length = 1; length <= int(text.size()); length++) {\n        int id = automaton.find(text.substr(text.size()\
    \ - length));\n        assert(terminal[id]);\n    }\n\n    std::string other =\
    \ \"zzbababx\";\n    auto common = automaton.longest_common_substring(other);\n\
    \    assert(other.substr(common.first, common.second - common.first) == \"baba\"\
    );\n\n    std::vector<int> order = automaton.length_order();\n    for (int i =\
    \ 1; i < int(order.size()); i++) {\n        assert(automaton.state(order[i - 1]).length\
    \ <= automaton.state(order[i]).length);\n    }\n\n    m1une::string::SuffixAutomaton<10,\
    \ '0'> digits(std::string(\"012012\"));\n    assert(digits.contains(std::string(\"\
    201\")));\n\n    automaton.clear();\n    assert(automaton.empty());\n    assert(automaton.state_count()\
    \ == 1);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 117;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 2000;\
    \ trial++) {\n        int n = int(random() % 55);\n        std::string text(n,\
    \ 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n        m1une::string::SuffixAutomaton<4, 'a'> automaton(text);\n\n \
    \       assert(automaton.state_count() <= std::max(1, 2 * n));\n        std::map<std::string,\
    \ int> expected_count;\n        for (int left = 0; left < n; left++) {\n     \
    \       for (int right = left + 1; right <= n; right++) {\n                expected_count[text.substr(left,\
    \ right - left)]++;\n            }\n        }\n        assert(automaton.distinct_substring_count()\
    \ == int(expected_count.size()));\n\n        std::vector<long long> occurrence\
    \ = automaton.occurrence_counts();\n        for (const auto& [substring, expected]\
    \ : expected_count) {\n            int id = automaton.find(substring);\n     \
    \       assert(id != automaton.null_state);\n            assert(occurrence[id]\
    \ == expected);\n            auto [left, right] = automaton.representative_occurrence(substring);\n\
    \            assert(text.substr(left, right - left) == substring);\n        }\n\
    \n        for (int id = 1; id < automaton.state_count(); id++) {\n           \
    \ const auto& current = automaton.state(id);\n            assert(0 <= current.suffix_link\
    \ && current.suffix_link < automaton.state_count());\n            assert(automaton.state(current.suffix_link).length\
    \ < current.length);\n            assert(automaton.minimum_length(id) == automaton.state(current.suffix_link).length\
    \ + 1);\n            auto [left, right] = automaton.longest_representative(id);\n\
    \            assert(0 <= left && left < right && right <= n);\n            std::string\
    \ represented = text.substr(left, right - left);\n            assert(int(represented.size())\
    \ == current.length);\n            assert(automaton.find(represented) == id);\n\
    \        }\n\n        std::vector<bool> expected_terminal(automaton.state_count(),\
    \ false);\n        expected_terminal[automaton.root()] = true;\n        for (int\
    \ left = 0; left < n; left++) {\n            expected_terminal[automaton.find(text.substr(left))]\
    \ = true;\n        }\n        assert(automaton.terminal_states() == expected_terminal);\n\
    \n        int m = int(random() % 55);\n        std::string query(m, 'a');\n  \
    \      for (char& character : query) character = char('a' + random() % 4);\n \
    \       int expected_lcs = 0;\n        for (int left = 0; left < m; left++) {\n\
    \            for (int right = left + 1; right <= m; right++) {\n             \
    \   if (automaton.contains(query.substr(left, right - left))) {\n            \
    \        expected_lcs = std::max(expected_lcs, right - left);\n              \
    \  }\n            }\n        }\n        auto [left, right] = automaton.longest_common_substring(query);\n\
    \        assert(right - left == expected_lcs);\n        assert(automaton.contains(query.substr(left,\
    \ right - left)));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n\
    \    test_randomized();\n    std::string text;\n    fast_input >> text;\n    m1une::string::SuffixAutomaton<>\
    \ automaton(text);\n    fast_output << automaton.distinct_substring_count() <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    \n#include \"../../string/suffix_automaton.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include\
    \ <map>\n#include <set>\n#include <string>\n#include <utility>\n#include <vector>\n\
    \nnamespace {\n\nvoid test_features() {\n    using Automaton = m1une::string::SuffixAutomaton<>;\n\
    \    Automaton automaton;\n    automaton.reserve(16);\n    assert(automaton.empty());\n\
    \    assert(automaton.state_count() == 1);\n    assert(automaton.root() == Automaton::root_state);\n\
    \    assert(automaton.last() == automaton.root());\n\n    std::string text = \"\
    ababa\";\n    for (char character : text) automaton.add(character);\n    assert(!automaton.empty());\n\
    \    assert(automaton.text_length() == 5);\n    assert(automaton.state(automaton.last()).length\
    \ == 5);\n    assert(automaton.contains(std::string(\"bab\")));\n    assert(!automaton.contains(std::string(\"\
    abb\")));\n    assert(automaton.contains(std::string()));\n    assert(automaton.transition(automaton.root(),\
    \ 'a') == automaton.find(std::string(\"a\")));\n    assert(automaton.distinct_substring_count()\
    \ == 9);\n\n    std::vector<long long> count = automaton.occurrence_counts();\n\
    \    assert(count[automaton.root()] == 5);\n    assert(count[automaton.find(std::string(\"\
    a\"))] == 3);\n    assert(count[automaton.find(std::string(\"b\"))] == 2);\n \
    \   assert(count[automaton.find(std::string(\"aba\"))] == 2);\n    assert(count[automaton.find(std::string(\"\
    ababa\"))] == 1);\n\n    auto occurrence = automaton.representative_occurrence(std::string(\"\
    bab\"));\n    assert(text.substr(occurrence.first, occurrence.second - occurrence.first)\
    \ == \"bab\");\n    assert((automaton.representative_occurrence(std::string(\"\
    x\")) == std::pair<int, int>({-1, -1})));\n\n    std::vector<bool> terminal =\
    \ automaton.terminal_states();\n    assert(terminal[automaton.root()]);\n    for\
    \ (int length = 1; length <= int(text.size()); length++) {\n        int id = automaton.find(text.substr(text.size()\
    \ - length));\n        assert(terminal[id]);\n    }\n\n    std::string other =\
    \ \"zzbababx\";\n    auto common = automaton.longest_common_substring(other);\n\
    \    assert(other.substr(common.first, common.second - common.first) == \"baba\"\
    );\n\n    std::vector<int> order = automaton.length_order();\n    for (int i =\
    \ 1; i < int(order.size()); i++) {\n        assert(automaton.state(order[i - 1]).length\
    \ <= automaton.state(order[i]).length);\n    }\n\n    m1une::string::SuffixAutomaton<10,\
    \ '0'> digits(std::string(\"012012\"));\n    assert(digits.contains(std::string(\"\
    201\")));\n\n    automaton.clear();\n    assert(automaton.empty());\n    assert(automaton.state_count()\
    \ == 1);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 117;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 2000;\
    \ trial++) {\n        int n = int(random() % 55);\n        std::string text(n,\
    \ 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n        m1une::string::SuffixAutomaton<4, 'a'> automaton(text);\n\n \
    \       assert(automaton.state_count() <= std::max(1, 2 * n));\n        std::map<std::string,\
    \ int> expected_count;\n        for (int left = 0; left < n; left++) {\n     \
    \       for (int right = left + 1; right <= n; right++) {\n                expected_count[text.substr(left,\
    \ right - left)]++;\n            }\n        }\n        assert(automaton.distinct_substring_count()\
    \ == int(expected_count.size()));\n\n        std::vector<long long> occurrence\
    \ = automaton.occurrence_counts();\n        for (const auto& [substring, expected]\
    \ : expected_count) {\n            int id = automaton.find(substring);\n     \
    \       assert(id != automaton.null_state);\n            assert(occurrence[id]\
    \ == expected);\n            auto [left, right] = automaton.representative_occurrence(substring);\n\
    \            assert(text.substr(left, right - left) == substring);\n        }\n\
    \n        for (int id = 1; id < automaton.state_count(); id++) {\n           \
    \ const auto& current = automaton.state(id);\n            assert(0 <= current.suffix_link\
    \ && current.suffix_link < automaton.state_count());\n            assert(automaton.state(current.suffix_link).length\
    \ < current.length);\n            assert(automaton.minimum_length(id) == automaton.state(current.suffix_link).length\
    \ + 1);\n            auto [left, right] = automaton.longest_representative(id);\n\
    \            assert(0 <= left && left < right && right <= n);\n            std::string\
    \ represented = text.substr(left, right - left);\n            assert(int(represented.size())\
    \ == current.length);\n            assert(automaton.find(represented) == id);\n\
    \        }\n\n        std::vector<bool> expected_terminal(automaton.state_count(),\
    \ false);\n        expected_terminal[automaton.root()] = true;\n        for (int\
    \ left = 0; left < n; left++) {\n            expected_terminal[automaton.find(text.substr(left))]\
    \ = true;\n        }\n        assert(automaton.terminal_states() == expected_terminal);\n\
    \n        int m = int(random() % 55);\n        std::string query(m, 'a');\n  \
    \      for (char& character : query) character = char('a' + random() % 4);\n \
    \       int expected_lcs = 0;\n        for (int left = 0; left < m; left++) {\n\
    \            for (int right = left + 1; right <= m; right++) {\n             \
    \   if (automaton.contains(query.substr(left, right - left))) {\n            \
    \        expected_lcs = std::max(expected_lcs, right - left);\n              \
    \  }\n            }\n        }\n        auto [left, right] = automaton.longest_common_substring(query);\n\
    \        assert(right - left == expected_lcs);\n        assert(automaton.contains(query.substr(left,\
    \ right - left)));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n\
    \    test_randomized();\n    std::string text;\n    fast_input >> text;\n    m1une::string::SuffixAutomaton<>\
    \ automaton(text);\n    fast_output << automaton.distinct_substring_count() <<\
    \ '\\n';\n}\n"
  dependsOn:
  - string/suffix_automaton.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/suffix_automaton.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/suffix_automaton.test.cpp
layout: document
redirect_from:
- /verify/verify/string/suffix_automaton.test.cpp
- /verify/verify/string/suffix_automaton.test.cpp.html
title: verify/string/suffix_automaton.test.cpp
---
