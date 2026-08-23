---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: game/all.hpp
    title: Game Library
  - icon: ':heavy_check_mark:'
    path: game/grundy.hpp
    title: Grundy Numbers
  - icon: ':heavy_check_mark:'
    path: game/nim.hpp
    title: Nim
  - icon: ':heavy_check_mark:'
    path: game/nim_product.hpp
    title: Nim Product
  - icon: ':heavy_check_mark:'
    path: game/retrograde_analysis.hpp
    title: Game Retrograde Analysis
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/game/game_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"game/all.hpp\"\n\n\n\
    \n#line 1 \"game/grundy.hpp\"\n\n\n\n#include <cassert>\n#include <queue>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace game {\n\n// graph[v] contains the\
    \ states reachable from v in one move.\n// The graph must be a DAG.\ntemplate\
    \ <typename Graph>\nstd::vector<int> grundy_numbers(const Graph& graph) {\n  \
    \  const int size = int(graph.size());\n    std::vector<int> indegree(size);\n\
    \    for (int vertex = 0; vertex < size; ++vertex) {\n        for (int next :\
    \ graph[vertex]) {\n            assert(0 <= next && next < size);\n          \
    \  indegree[next]++;\n        }\n    }\n\n    std::queue<int> queue;\n    for\
    \ (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex] ==\
    \ 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ graph[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n    }\n    assert(int(order.size()) == size);\n\n    std::vector<int>\
    \ grundy(size);\n    std::vector<int> seen(size + 1, -1);\n    for (int position\
    \ = size - 1; position >= 0; --position) {\n        const int vertex = order[position];\n\
    \        for (int next : graph[vertex]) {\n            const int value = grundy[next];\n\
    \            if (value <= size) seen[value] = vertex;\n        }\n        while\
    \ (grundy[vertex] <= size && seen[grundy[vertex]] == vertex) {\n            grundy[vertex]++;\n\
    \        }\n    }\n    return grundy;\n}\n\n}  // namespace game\n}  // namespace\
    \ m1une\n\n\n#line 1 \"game/nim.hpp\"\n\n\n\n#include <iterator>\n\nnamespace\
    \ m1une {\nnamespace game {\n\ntemplate <typename Iterator>\nauto nim_sum(Iterator\
    \ first, Iterator last) {\n    using T = typename std::iterator_traits<Iterator>::value_type;\n\
    \    T result{};\n    while (first != last) {\n        result ^= *first;\n   \
    \     ++first;\n    }\n    return result;\n}\n\ntemplate <typename Range>\nauto\
    \ nim_sum(const Range& heaps) {\n    using std::begin;\n    using std::end;\n\
    \    return nim_sum(begin(heaps), end(heaps));\n}\n\ntemplate <typename Range>\n\
    bool nim_first_player_wins(const Range& heaps) {\n    return nim_sum(heaps) !=\
    \ 0;\n}\n\ntemplate <typename Range>\nbool misere_nim_first_player_wins(const\
    \ Range& heaps) {\n    using std::begin;\n    using std::end;\n\n    auto first\
    \ = begin(heaps);\n    const auto last = end(heaps);\n    bool odd_nonzero_heaps\
    \ = false;\n    bool has_large_heap = false;\n    using T = typename std::iterator_traits<decltype(first)>::value_type;\n\
    \    T sum{};\n    for (; first != last; ++first) {\n        sum ^= *first;\n\
    \        if (*first != 0) {\n            odd_nonzero_heaps = !odd_nonzero_heaps;\n\
    \        }\n        if (*first > 1) has_large_heap = true;\n    }\n    return\
    \ has_large_heap ? sum != 0 : !odd_nonzero_heaps;\n}\n\n}  // namespace game\n\
    }  // namespace m1une\n\n\n#line 1 \"game/nim_product.hpp\"\n\n\n\n#include <array>\n\
    #line 6 \"game/nim_product.hpp\"\n#include <cstdint>\n#include <limits>\n\nnamespace\
    \ m1une {\nnamespace game {\nnamespace internal {\n\ninline uint64_t nim_product_small(uint64_t\
    \ x, uint64_t y) {\n    if (x < 2 || y < 2) return x * y;\n\n    int shift = 1;\n\
    \    const uint64_t largest = x | y;\n    while ((uint64_t(1) << (shift * 2))\
    \ <= largest) shift *= 2;\n    const uint64_t mask = (uint64_t(1) << shift) -\
    \ 1;\n    const uint64_t x_high = x >> shift;\n    const uint64_t x_low = x &\
    \ mask;\n    const uint64_t y_high = y >> shift;\n    const uint64_t y_low = y\
    \ & mask;\n\n    const uint64_t high_product = nim_product_small(x_high, y_high);\n\
    \    const uint64_t low_product = nim_product_small(x_low, y_low);\n    const\
    \ uint64_t mixed_product =\n        nim_product_small(x_high ^ x_low, y_high ^\
    \ y_low);\n    return ((mixed_product ^ low_product) << shift) ^ low_product\n\
    \           ^ nim_product_small(high_product, uint64_t(1) << (shift - 1));\n}\n\
    \ninline const std::array<uint8_t, 1 << 16>& nim_product_8_table() {\n    static\
    \ const auto table = [] {\n        std::array<uint8_t, 1 << 16> result{};\n  \
    \      for (int x = 0; x < 256; ++x) {\n            for (int y = 0; y < 256; ++y)\
    \ {\n                result[(x << 8) | y] = uint8_t(nim_product_small(x, y));\n\
    \            }\n        }\n        return result;\n    }();\n    return table;\n\
    }\n\ninline uint64_t nim_product_8(uint64_t x, uint64_t y) {\n    return nim_product_8_table()[(x\
    \ << 8) | y];\n}\n\ntemplate <int Bits>\ninline uint64_t nim_product_fixed(uint64_t\
    \ x, uint64_t y) {\n    if constexpr (Bits == 8) {\n        return nim_product_8(x,\
    \ y);\n    } else {\n        constexpr int shift = Bits / 2;\n        constexpr\
    \ uint64_t mask = (uint64_t(1) << shift) - 1;\n        const uint64_t x_high =\
    \ x >> shift;\n        const uint64_t x_low = x & mask;\n        const uint64_t\
    \ y_high = y >> shift;\n        const uint64_t y_low = y & mask;\n\n        const\
    \ uint64_t high_product =\n            nim_product_fixed<shift>(x_high, y_high);\n\
    \        const uint64_t low_product = nim_product_fixed<shift>(x_low, y_low);\n\
    \        const uint64_t mixed_product = nim_product_fixed<shift>(\n          \
    \  x_high ^ x_low,\n            y_high ^ y_low\n        );\n        return ((mixed_product\
    \ ^ low_product) << shift) ^ low_product\n               ^ nim_product_fixed<shift>(\n\
    \                   high_product,\n                   uint64_t(1) << (shift -\
    \ 1)\n               );\n    }\n}\n\n}  // namespace internal\n\ninline uint64_t\
    \ nim_product(uint64_t x, uint64_t y) {\n    return internal::nim_product_fixed<64>(x,\
    \ y);\n}\n\ninline uint64_t nim_power(uint64_t base, uint64_t exponent) {\n  \
    \  uint64_t result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ result = nim_product(result, base);\n        base = nim_product(base, base);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t nim_inverse(uint64_t\
    \ value) {\n    assert(value != 0);\n    return nim_power(value, std::numeric_limits<uint64_t>::max()\
    \ - 1);\n}\n\ninline uint64_t nim_quotient(uint64_t numerator, uint64_t denominator)\
    \ {\n    assert(denominator != 0);\n    return nim_product(numerator, nim_inverse(denominator));\n\
    }\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line 1 \"game/retrograde_analysis.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"game/retrograde_analysis.hpp\"\n#include\
    \ <utility>\n#line 9 \"game/retrograde_analysis.hpp\"\n\nnamespace m1une {\nnamespace\
    \ game {\n\nenum class GameOutcome { Win, Lose, Draw };\n\nstruct RetrogradeResult\
    \ {\n    std::vector<GameOutcome> outcome;\n    std::vector<int> distance;\n};\n\
    \n// graph[v] contains the states reachable from v in one move.\ninline RetrogradeResult\
    \ retrograde_analysis(\n    const std::vector<std::vector<int>>& graph\n) {\n\
    \    const int size = int(graph.size());\n    std::vector<std::vector<int>> reverse_graph(size);\n\
    \    std::vector<int> remaining(size);\n    for (int vertex = 0; vertex < size;\
    \ ++vertex) {\n        remaining[vertex] = int(graph[vertex].size());\n      \
    \  for (int next : graph[vertex]) {\n            assert(0 <= next && next < size);\n\
    \            reverse_graph[next].push_back(vertex);\n        }\n    }\n\n    std::vector<GameOutcome>\
    \ outcome(size, GameOutcome::Draw);\n    std::vector<int> distance(size, -1);\n\
    \    std::vector<int> longest_win_successor(size);\n    std::vector<bool> decided(size);\n\
    \    std::queue<int> queue;\n    for (int vertex = 0; vertex < size; ++vertex)\
    \ {\n        if (remaining[vertex] == 0) {\n            outcome[vertex] = GameOutcome::Lose;\n\
    \            distance[vertex] = 0;\n            decided[vertex] = true;\n    \
    \        queue.push(vertex);\n        }\n    }\n\n    while (!queue.empty()) {\n\
    \        const int vertex = queue.front();\n        queue.pop();\n        for\
    \ (int previous : reverse_graph[vertex]) {\n            if (decided[previous])\
    \ continue;\n            if (outcome[vertex] == GameOutcome::Lose) {\n       \
    \         outcome[previous] = GameOutcome::Win;\n                distance[previous]\
    \ = distance[vertex] + 1;\n                decided[previous] = true;\n       \
    \         queue.push(previous);\n            } else {\n                longest_win_successor[previous]\
    \ = std::max(\n                    longest_win_successor[previous],\n        \
    \            distance[vertex]\n                );\n                if (--remaining[previous]\
    \ == 0) {\n                    outcome[previous] = GameOutcome::Lose;\n      \
    \              distance[previous] = longest_win_successor[previous] + 1;\n   \
    \                 decided[previous] = true;\n                    queue.push(previous);\n\
    \                }\n            }\n        }\n    }\n    return {std::move(outcome),\
    \ std::move(distance)};\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n\
    #line 8 \"game/all.hpp\"\n\n\n#line 4 \"verify/game/game_algorithms.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#line\
    \ 14 \"utilities/fast_io.hpp\"\n#include <string>\n#include <sys/stat.h>\n#include\
    \ <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/game/game_algorithms.test.cpp\"\
    \n#include <random>\n#line 11 \"verify/game/game_algorithms.test.cpp\"\n\nnamespace\
    \ {\n\nusing m1une::game::GameOutcome;\n\nvoid test_nim() {\n    std::vector<int>\
    \ empty;\n    assert(m1une::game::nim_sum(empty) == 0);\n    assert(!m1une::game::nim_first_player_wins(empty));\n\
    \    assert(m1une::game::misere_nim_first_player_wins(empty));\n\n    std::vector<int>\
    \ ordinary = {1, 4, 5};\n    assert(m1une::game::nim_sum(ordinary) == 0);\n  \
    \  assert(!m1une::game::nim_first_player_wins(ordinary));\n\n    std::vector<int>\
    \ one_one = {1, 1};\n    std::vector<int> one_one_one = {1, 1, 1};\n    assert(m1une::game::misere_nim_first_player_wins(one_one));\n\
    \    assert(!m1une::game::misere_nim_first_player_wins(one_one_one));\n\n    std::vector<int>\
    \ general = {1, 2, 3};\n    assert(!m1une::game::misere_nim_first_player_wins(general));\n\
    }\n\nstd::vector<int> naive_grundy(const std::vector<std::vector<int>>& graph)\
    \ {\n    const int size = int(graph.size());\n    std::vector<int> result(size);\n\
    \    for (int vertex = size - 1; vertex >= 0; --vertex) {\n        std::vector<bool>\
    \ appears(size + 1);\n        for (int next : graph[vertex]) appears[result[next]]\
    \ = true;\n        while (appears[result[vertex]]) result[vertex]++;\n    }\n\
    \    return result;\n}\n\nvoid test_grundy_random() {\n    std::mt19937 random(123456789);\n\
    \    for (int size = 0; size <= 40; ++size) {\n        for (int trial = 0; trial\
    \ < 100; ++trial) {\n            std::vector<std::vector<int>> graph(size);\n\
    \            for (int from = 0; from < size; ++from) {\n                for (int\
    \ to = from + 1; to < size; ++to) {\n                    if (random() % 5 == 0)\
    \ graph[from].push_back(to);\n                }\n            }\n            assert(m1une::game::grundy_numbers(graph)\
    \ == naive_grundy(graph));\n        }\n    }\n}\n\nstd::vector<GameOutcome> naive_outcomes(\n\
    \    const std::vector<std::vector<int>>& graph\n) {\n    const int size = int(graph.size());\n\
    \    std::vector<GameOutcome> result(size, GameOutcome::Draw);\n    std::vector<bool>\
    \ decided(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n      \
    \  if (graph[vertex].empty()) {\n            result[vertex] = GameOutcome::Lose;\n\
    \            decided[vertex] = true;\n        }\n    }\n\n    bool changed = true;\n\
    \    while (changed) {\n        changed = false;\n        for (int vertex = 0;\
    \ vertex < size; ++vertex) {\n            if (decided[vertex]) continue;\n   \
    \         bool has_losing_move = false;\n            bool all_moves_win = true;\n\
    \            for (int next : graph[vertex]) {\n                has_losing_move\
    \ |= decided[next] && result[next] == GameOutcome::Lose;\n                all_moves_win\
    \ &= decided[next] && result[next] == GameOutcome::Win;\n            }\n     \
    \       if (has_losing_move || all_moves_win) {\n                result[vertex]\
    \ = has_losing_move ? GameOutcome::Win : GameOutcome::Lose;\n                decided[vertex]\
    \ = true;\n                changed = true;\n            }\n        }\n    }\n\
    \    return result;\n}\n\nvoid test_retrograde_random() {\n    std::mt19937 random(987654321);\n\
    \    for (int size = 0; size <= 30; ++size) {\n        for (int trial = 0; trial\
    \ < 100; ++trial) {\n            std::vector<std::vector<int>> graph(size);\n\
    \            for (int from = 0; from < size; ++from) {\n                for (int\
    \ to = 0; to < size; ++to) {\n                    if (random() % 8 == 0) graph[from].push_back(to);\n\
    \                }\n            }\n            auto actual = m1une::game::retrograde_analysis(graph);\n\
    \            assert(actual.outcome == naive_outcomes(graph));\n            for\
    \ (int vertex = 0; vertex < size; ++vertex) {\n                assert((actual.distance[vertex]\
    \ == -1)\n                       == (actual.outcome[vertex] == GameOutcome::Draw));\n\
    \            }\n        }\n    }\n\n    std::vector<std::vector<int>> chain(5);\n\
    \    chain[0].push_back(1);\n    chain[1].push_back(2);\n    chain[2].push_back(3);\n\
    \    chain[3].push_back(4);\n    auto result = m1une::game::retrograde_analysis(chain);\n\
    \    for (int vertex = 0; vertex < 5; ++vertex) {\n        assert(result.distance[vertex]\
    \ == 4 - vertex);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_nim();\n\
    \    test_grundy_random();\n    test_retrograde_random();\n\n    long long first,\
    \ second;\n    fast_input >> first >> second;\n    fast_output << first + second\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../game/all.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n\
    #include \"../../utilities/fast_io.hpp\"\n#include <random>\n#include <vector>\n\
    \nnamespace {\n\nusing m1une::game::GameOutcome;\n\nvoid test_nim() {\n    std::vector<int>\
    \ empty;\n    assert(m1une::game::nim_sum(empty) == 0);\n    assert(!m1une::game::nim_first_player_wins(empty));\n\
    \    assert(m1une::game::misere_nim_first_player_wins(empty));\n\n    std::vector<int>\
    \ ordinary = {1, 4, 5};\n    assert(m1une::game::nim_sum(ordinary) == 0);\n  \
    \  assert(!m1une::game::nim_first_player_wins(ordinary));\n\n    std::vector<int>\
    \ one_one = {1, 1};\n    std::vector<int> one_one_one = {1, 1, 1};\n    assert(m1une::game::misere_nim_first_player_wins(one_one));\n\
    \    assert(!m1une::game::misere_nim_first_player_wins(one_one_one));\n\n    std::vector<int>\
    \ general = {1, 2, 3};\n    assert(!m1une::game::misere_nim_first_player_wins(general));\n\
    }\n\nstd::vector<int> naive_grundy(const std::vector<std::vector<int>>& graph)\
    \ {\n    const int size = int(graph.size());\n    std::vector<int> result(size);\n\
    \    for (int vertex = size - 1; vertex >= 0; --vertex) {\n        std::vector<bool>\
    \ appears(size + 1);\n        for (int next : graph[vertex]) appears[result[next]]\
    \ = true;\n        while (appears[result[vertex]]) result[vertex]++;\n    }\n\
    \    return result;\n}\n\nvoid test_grundy_random() {\n    std::mt19937 random(123456789);\n\
    \    for (int size = 0; size <= 40; ++size) {\n        for (int trial = 0; trial\
    \ < 100; ++trial) {\n            std::vector<std::vector<int>> graph(size);\n\
    \            for (int from = 0; from < size; ++from) {\n                for (int\
    \ to = from + 1; to < size; ++to) {\n                    if (random() % 5 == 0)\
    \ graph[from].push_back(to);\n                }\n            }\n            assert(m1une::game::grundy_numbers(graph)\
    \ == naive_grundy(graph));\n        }\n    }\n}\n\nstd::vector<GameOutcome> naive_outcomes(\n\
    \    const std::vector<std::vector<int>>& graph\n) {\n    const int size = int(graph.size());\n\
    \    std::vector<GameOutcome> result(size, GameOutcome::Draw);\n    std::vector<bool>\
    \ decided(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n      \
    \  if (graph[vertex].empty()) {\n            result[vertex] = GameOutcome::Lose;\n\
    \            decided[vertex] = true;\n        }\n    }\n\n    bool changed = true;\n\
    \    while (changed) {\n        changed = false;\n        for (int vertex = 0;\
    \ vertex < size; ++vertex) {\n            if (decided[vertex]) continue;\n   \
    \         bool has_losing_move = false;\n            bool all_moves_win = true;\n\
    \            for (int next : graph[vertex]) {\n                has_losing_move\
    \ |= decided[next] && result[next] == GameOutcome::Lose;\n                all_moves_win\
    \ &= decided[next] && result[next] == GameOutcome::Win;\n            }\n     \
    \       if (has_losing_move || all_moves_win) {\n                result[vertex]\
    \ = has_losing_move ? GameOutcome::Win : GameOutcome::Lose;\n                decided[vertex]\
    \ = true;\n                changed = true;\n            }\n        }\n    }\n\
    \    return result;\n}\n\nvoid test_retrograde_random() {\n    std::mt19937 random(987654321);\n\
    \    for (int size = 0; size <= 30; ++size) {\n        for (int trial = 0; trial\
    \ < 100; ++trial) {\n            std::vector<std::vector<int>> graph(size);\n\
    \            for (int from = 0; from < size; ++from) {\n                for (int\
    \ to = 0; to < size; ++to) {\n                    if (random() % 8 == 0) graph[from].push_back(to);\n\
    \                }\n            }\n            auto actual = m1une::game::retrograde_analysis(graph);\n\
    \            assert(actual.outcome == naive_outcomes(graph));\n            for\
    \ (int vertex = 0; vertex < size; ++vertex) {\n                assert((actual.distance[vertex]\
    \ == -1)\n                       == (actual.outcome[vertex] == GameOutcome::Draw));\n\
    \            }\n        }\n    }\n\n    std::vector<std::vector<int>> chain(5);\n\
    \    chain[0].push_back(1);\n    chain[1].push_back(2);\n    chain[2].push_back(3);\n\
    \    chain[3].push_back(4);\n    auto result = m1une::game::retrograde_analysis(chain);\n\
    \    for (int vertex = 0; vertex < 5; ++vertex) {\n        assert(result.distance[vertex]\
    \ == 4 - vertex);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_nim();\n\
    \    test_grundy_random();\n    test_retrograde_random();\n\n    long long first,\
    \ second;\n    fast_input >> first >> second;\n    fast_output << first + second\
    \ << '\\n';\n}\n"
  dependsOn:
  - game/all.hpp
  - game/grundy.hpp
  - game/nim.hpp
  - game/nim_product.hpp
  - game/retrograde_analysis.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/game/game_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-08-24 02:00:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/game/game_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/game/game_algorithms.test.cpp
- /verify/verify/game/game_algorithms.test.cpp.html
title: verify/game/game_algorithms.test.cpp
---
