---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/functional_graph.hpp
    title: Functional Graph
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
  bundledCode: "#line 1 \"verify/graph/functional_graph.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"graph/functional_graph.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct FunctionalGraph {\n    int component_count;\n    std::vector<int>\
    \ successor;\n    std::vector<std::vector<int>> predecessors;\n    std::vector<std::vector<int>>\
    \ cycles;\n    std::vector<int> component;\n    std::vector<int> component_size;\n\
    \    std::vector<int> cycle_entry;\n    std::vector<int> cycle_position;\n   \
    \ std::vector<int> distance_to_cycle;\n\n   private:\n    std::vector<std::vector<int>>\
    \ _up;\n\n    void check_vertex(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < size());\n    }\n\n    int advance_before_cycle(int vertex, int\
    \ steps) const {\n        assert(0 <= steps && steps <= distance_to_cycle[vertex]);\n\
    \        int bit = 0;\n        while (steps > 0) {\n            if (steps & 1)\
    \ vertex = _up[bit][vertex];\n            steps >>= 1;\n            bit++;\n \
    \       }\n        return vertex;\n    }\n\n   public:\n    FunctionalGraph()\
    \ : component_count(0) {}\n\n    explicit FunctionalGraph(const std::vector<int>&\
    \ successor_) {\n        build(successor_);\n    }\n\n    void build(const std::vector<int>&\
    \ successor_) {\n        successor = successor_;\n        const int n = size();\n\
    \        for (int to : successor) assert(0 <= to && to < n);\n\n        component_count\
    \ = 0;\n        predecessors.assign(n, {});\n        cycles.clear();\n       \
    \ component.assign(n, -1);\n        cycle_entry.assign(n, -1);\n        cycle_position.assign(n,\
    \ -1);\n        distance_to_cycle.assign(n, -1);\n\n        std::vector<int> indegree(n,\
    \ 0);\n        for (int vertex = 0; vertex < n; vertex++) {\n            predecessors[successor[vertex]].push_back(vertex);\n\
    \            indegree[successor[vertex]]++;\n        }\n\n        std::queue<int>\
    \ queue;\n        std::vector<char> removed(n, false);\n        for (int vertex\
    \ = 0; vertex < n; vertex++) {\n            if (indegree[vertex] == 0) queue.push(vertex);\n\
    \        }\n        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            removed[vertex] = true;\n            const\
    \ int to = successor[vertex];\n            indegree[to]--;\n            if (indegree[to]\
    \ == 0) queue.push(to);\n        }\n\n        for (int start = 0; start < n; start++)\
    \ {\n            if (removed[start] || component[start] != -1) continue;\n   \
    \         const int component_id = int(cycles.size());\n            std::vector<int>\
    \ cycle;\n            int vertex = start;\n            do {\n                const\
    \ int position = int(cycle.size());\n                cycle.push_back(vertex);\n\
    \                component[vertex] = component_id;\n                cycle_entry[vertex]\
    \ = vertex;\n                cycle_position[vertex] = position;\n            \
    \    distance_to_cycle[vertex] = 0;\n                vertex = successor[vertex];\n\
    \            } while (vertex != start);\n            cycles.push_back(std::move(cycle));\n\
    \        }\n        component_count = int(cycles.size());\n\n        for (const\
    \ std::vector<int>& cycle : cycles) {\n            for (int vertex : cycle) queue.push(vertex);\n\
    \        }\n        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int from : predecessors[vertex]) {\n\
    \                if (component[from] != -1) continue;\n                component[from]\
    \ = component[vertex];\n                cycle_entry[from] = cycle_entry[vertex];\n\
    \                cycle_position[from] = cycle_position[vertex];\n            \
    \    distance_to_cycle[from] = distance_to_cycle[vertex] + 1;\n              \
    \  queue.push(from);\n            }\n        }\n\n        component_size.assign(component_count,\
    \ 0);\n        for (int component_id : component) component_size[component_id]++;\n\
    \n        int log = 1;\n        while ((std::uint64_t(1) << log) <= std::uint64_t(n))\
    \ log++;\n        _up.assign(log, successor);\n        for (int bit = 1; bit <\
    \ log; bit++) {\n            for (int vertex = 0; vertex < n; vertex++) {\n  \
    \              _up[bit][vertex] = _up[bit - 1][_up[bit - 1][vertex]];\n      \
    \      }\n        }\n    }\n\n    int size() const {\n        return int(successor.size());\n\
    \    }\n\n    bool empty() const {\n        return successor.empty();\n    }\n\
    \n    bool same_component(int first, int second) const {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return component[first] == component[second];\n\
    \    }\n\n    bool on_cycle(int vertex) const {\n        check_vertex(vertex);\n\
    \        return distance_to_cycle[vertex] == 0;\n    }\n\n    int cycle_size(int\
    \ vertex) const {\n        check_vertex(vertex);\n        return int(cycles[component[vertex]].size());\n\
    \    }\n\n    int orbit_size(int vertex) const {\n        check_vertex(vertex);\n\
    \        return distance_to_cycle[vertex] + cycle_size(vertex);\n    }\n\n   \
    \ int jump(int vertex, std::uint64_t steps) const {\n        check_vertex(vertex);\n\
    \        const int tail_length = distance_to_cycle[vertex];\n        if (steps\
    \ < std::uint64_t(tail_length)) {\n            return advance_before_cycle(vertex,\
    \ int(steps));\n        }\n\n        steps -= std::uint64_t(tail_length);\n  \
    \      const int entry = cycle_entry[vertex];\n        const int length = cycle_size(entry);\n\
    \        const int offset = int(steps % std::uint64_t(length));\n        const\
    \ int position = (cycle_position[entry] + offset) % length;\n        return cycles[component[vertex]][position];\n\
    \    }\n\n    long long distance(int from, int to) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        if (!same_component(from, to)) return -1;\n\
    \n        if (!on_cycle(to)) {\n            if (distance_to_cycle[from] < distance_to_cycle[to])\
    \ return -1;\n            const int difference = distance_to_cycle[from] - distance_to_cycle[to];\n\
    \            return advance_before_cycle(from, difference) == to ? difference\
    \ : -1;\n        }\n\n        const int entry = cycle_entry[from];\n        const\
    \ int length = cycle_size(from);\n        int cycle_distance = cycle_position[to]\
    \ - cycle_position[entry];\n        if (cycle_distance < 0) cycle_distance +=\
    \ length;\n        return static_cast<long long>(distance_to_cycle[from]) + cycle_distance;\n\
    \    }\n\n    bool reachable(int from, int to) const {\n        return distance(from,\
    \ to) != -1;\n    }\n\n    std::vector<int> path(int from, int to) const {\n \
    \       const long long path_length = distance(from, to);\n        if (path_length\
    \ == -1) return {};\n\n        std::vector<int> result;\n        result.reserve(path_length\
    \ + 1);\n        for (long long step = 0; step <= path_length; step++) {\n   \
    \         result.push_back(from);\n            from = successor[from];\n     \
    \   }\n        return result;\n    }\n\n    std::vector<int> orbit(int vertex)\
    \ const {\n        check_vertex(vertex);\n        const int length = orbit_size(vertex);\n\
    \        std::vector<int> result;\n        result.reserve(length);\n        for\
    \ (int step = 0; step < length; step++) {\n            result.push_back(vertex);\n\
    \            vertex = successor[vertex];\n        }\n        return result;\n\
    \    }\n\n    std::uint64_t visit_count(\n        int from,\n        int to,\n\
    \        std::uint64_t step_count\n    ) const {\n        const long long first_visit\
    \ = distance(from, to);\n        if (first_visit == -1 ||\n            std::uint64_t(first_visit)\
    \ >= step_count) {\n            return 0;\n        }\n        if (!on_cycle(to))\
    \ return 1;\n\n        const std::uint64_t remaining =\n            step_count\
    \ - 1 - std::uint64_t(first_visit);\n        return 1 + remaining / std::uint64_t(cycle_size(to));\n\
    \    }\n\n    long long first_meeting_time(int first, int second) const {\n  \
    \      check_vertex(first);\n        check_vertex(second);\n        if (!same_component(first,\
    \ second)) return -1;\n        if (first == second) return 0;\n\n        const\
    \ int first_depth = distance_to_cycle[first];\n        const int second_depth\
    \ = distance_to_cycle[second];\n        if (first_depth == second_depth &&\n \
    \           cycle_entry[first] == cycle_entry[second]) {\n            int elapsed\
    \ = 0;\n            for (int bit = int(_up.size()) - 1; bit >= 0; bit--) {\n \
    \               const int steps = 1 << bit;\n                if (first_depth -\
    \ elapsed < steps) continue;\n                const int next_first = _up[bit][first];\n\
    \                const int next_second = _up[bit][second];\n                if\
    \ (next_first == next_second) continue;\n                first = next_first;\n\
    \                second = next_second;\n                elapsed += steps;\n  \
    \          }\n            return elapsed + 1;\n        }\n\n        const int\
    \ length = cycle_size(first);\n        int first_phase =\n            cycle_position[first]\
    \ - first_depth % length;\n        int second_phase =\n            cycle_position[second]\
    \ - second_depth % length;\n        if (first_phase < 0) first_phase += length;\n\
    \        if (second_phase < 0) second_phase += length;\n        if (first_phase\
    \ != second_phase) return -1;\n        return std::max(first_depth, second_depth);\n\
    \    }\n\n    int first_meeting_vertex(int first, int second) const {\n      \
    \  const long long time = first_meeting_time(first, second);\n        if (time\
    \ == -1) return -1;\n        return jump(first, std::uint64_t(time));\n    }\n\
    };\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 18 \"\
    utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/graph/functional_graph.test.cpp\"\
    \n\n#line 9 \"verify/graph/functional_graph.test.cpp\"\n\nnamespace {\n\nint naive_jump(\n\
    \    const std::vector<int>& successor,\n    int vertex,\n    std::uint64_t steps\n\
    ) {\n    const int n = int(successor.size());\n    std::vector<long long> first_visit(n,\
    \ -1);\n    std::vector<int> path;\n    while (first_visit[vertex] == -1) {\n\
    \        first_visit[vertex] = int(path.size());\n        path.push_back(vertex);\n\
    \        vertex = successor[vertex];\n    }\n\n    if (steps < path.size()) return\
    \ path[steps];\n    const std::uint64_t cycle_start = std::uint64_t(first_visit[vertex]);\n\
    \    const std::uint64_t cycle_length = path.size() - cycle_start;\n    const\
    \ std::uint64_t position =\n        cycle_start + (steps - cycle_start) % cycle_length;\n\
    \    return path[position];\n}\n\nlong long naive_distance(\n    const std::vector<int>&\
    \ successor,\n    int from,\n    int to\n) {\n    const int n = int(successor.size());\n\
    \    std::vector<char> visited(n, false);\n    for (int distance = 0; !visited[from];\
    \ distance++) {\n        if (from == to) return distance;\n        visited[from]\
    \ = true;\n        from = successor[from];\n    }\n    return -1;\n}\n\nstd::vector<int>\
    \ naive_orbit(\n    const std::vector<int>& successor,\n    int vertex\n) {\n\
    \    std::vector<char> visited(successor.size(), false);\n    std::vector<int>\
    \ result;\n    while (!visited[vertex]) {\n        visited[vertex] = true;\n \
    \       result.push_back(vertex);\n        vertex = successor[vertex];\n    }\n\
    \    return result;\n}\n\nstd::uint64_t naive_visit_count(\n    const std::vector<int>&\
    \ successor,\n    int from,\n    int to,\n    std::uint64_t step_count\n) {\n\
    \    std::uint64_t result = 0;\n    for (std::uint64_t step = 0; step < step_count;\
    \ step++) {\n        if (from == to) result++;\n        from = successor[from];\n\
    \    }\n    return result;\n}\n\nlong long naive_first_meeting_time(\n    const\
    \ std::vector<int>& successor,\n    int first,\n    int second\n) {\n    const\
    \ int n = int(successor.size());\n    std::vector<char> visited(n * n, false);\n\
    \    for (int time = 0; !visited[first * n + second]; time++) {\n        if (first\
    \ == second) return time;\n        visited[first * n + second] = true;\n     \
    \   first = successor[first];\n        second = successor[second];\n    }\n  \
    \  return -1;\n}\n\nvoid test_focused_cases() {\n    const std::vector<int> successor\
    \ = {1, 2, 0, 2, 3, 6, 5, 6, 3};\n    m1une::graph::FunctionalGraph graph(successor);\n\
    \n    assert(graph.size() == 9);\n    assert(!graph.empty());\n    assert(graph.component_count\
    \ == 2);\n    assert(graph.same_component(0, 4));\n    assert(!graph.same_component(0,\
    \ 5));\n    assert(graph.on_cycle(0));\n    assert(graph.on_cycle(5));\n    assert(!graph.on_cycle(4));\n\
    \    assert(graph.cycle_entry[4] == 2);\n    assert(graph.distance_to_cycle[4]\
    \ == 2);\n    assert(graph.cycle_size(4) == 3);\n    assert(graph.cycle_size(7)\
    \ == 2);\n    assert(graph.component_size[graph.component[4]] == 6);\n    assert(graph.component_size[graph.component[7]]\
    \ == 3);\n    assert((graph.predecessors[3] == std::vector<int>{4, 8}));\n   \
    \ assert(graph.orbit_size(4) == 5);\n    assert((graph.orbit(4) == std::vector<int>{4,\
    \ 3, 2, 0, 1}));\n\n    assert(graph.jump(4, 0) == 4);\n    assert(graph.jump(4,\
    \ 1) == 3);\n    assert(graph.jump(4, 2) == 2);\n    assert(graph.jump(4, 4) ==\
    \ 1);\n    assert(graph.jump(7, 3) == 6);\n    assert(graph.jump(4, UINT64_C(1000000000000000000))\
    \ ==\n           naive_jump(successor, 4, UINT64_C(1000000000000000000)));\n\n\
    \    assert(graph.distance(4, 4) == 0);\n    assert(graph.distance(4, 3) == 1);\n\
    \    assert(graph.distance(4, 2) == 2);\n    assert(graph.distance(4, 1) == 4);\n\
    \    assert(graph.distance(1, 4) == -1);\n    assert(graph.distance(3, 4) == -1);\n\
    \    assert(graph.distance(4, 5) == -1);\n    assert(graph.distance(7, 5) == 2);\n\
    \    assert(graph.reachable(4, 1));\n    assert(!graph.reachable(1, 4));\n   \
    \ assert((graph.path(4, 1) == std::vector<int>{4, 3, 2, 0, 1}));\n    assert(graph.path(1,\
    \ 4).empty());\n\n    assert(graph.visit_count(4, 2, 0) == 0);\n    assert(graph.visit_count(4,\
    \ 2, 3) == 1);\n    assert(graph.visit_count(4, 2, 5) == 1);\n    assert(graph.visit_count(4,\
    \ 2, 6) == 2);\n    assert(graph.visit_count(4, 3, UINT64_MAX) == 1);\n    assert(graph.visit_count(4,\
    \ 5, UINT64_MAX) == 0);\n\n    assert(graph.first_meeting_time(4, 8) == 1);\n\
    \    assert(graph.first_meeting_vertex(4, 8) == 3);\n    assert(graph.first_meeting_time(4,\
    \ 0) == 2);\n    assert(graph.first_meeting_vertex(4, 0) == 2);\n    assert(graph.first_meeting_time(4,\
    \ 1) == -1);\n    assert(graph.first_meeting_vertex(4, 1) == -1);\n    assert(graph.first_meeting_time(7,\
    \ 5) == 1);\n    assert(graph.first_meeting_vertex(7, 5) == 6);\n    assert(graph.first_meeting_time(4,\
    \ 5) == -1);\n    assert(graph.first_meeting_time(2, 2) == 0);\n\n    graph.build(std::vector<int>{0});\n\
    \    assert(graph.size() == 1);\n    assert(graph.component_count == 1);\n   \
    \ assert(graph.on_cycle(0));\n    assert(graph.jump(0, UINT64_MAX) == 0);\n  \
    \  assert(graph.distance(0, 0) == 0);\n    assert(graph.orbit_size(0) == 1);\n\
    \    assert(graph.visit_count(0, 0, UINT64_MAX) == UINT64_MAX);\n    assert(graph.first_meeting_time(0,\
    \ 0) == 0);\n\n    graph.build(std::vector<int>());\n    assert(graph.empty());\n\
    \    assert(graph.component_count == 0);\n    assert(graph.cycles.empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = UINT64_C(0x5f3759df12345678);\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 500; trial++) {\n        const int n = 1 + int(random() % 60);\n        std::vector<int>\
    \ successor(n);\n        for (int& to : successor) to = int(random() % n);\n \
    \       m1une::graph::FunctionalGraph graph(successor);\n\n        assert(graph.size()\
    \ == n);\n        assert(1 <= graph.component_count && graph.component_count <=\
    \ n);\n        std::vector<int> expected_component_size(graph.component_count,\
    \ 0);\n        for (int component : graph.component) expected_component_size[component]++;\n\
    \        assert(graph.component_size == expected_component_size);\n        int\
    \ cycle_vertex_count = 0;\n        for (int component = 0; component < graph.component_count;\
    \ component++) {\n            const std::vector<int>& cycle = graph.cycles[component];\n\
    \            assert(!cycle.empty());\n            cycle_vertex_count += int(cycle.size());\n\
    \            for (int position = 0; position < int(cycle.size()); position++)\
    \ {\n                const int vertex = cycle[position];\n                const\
    \ int next = cycle[(position + 1) % cycle.size()];\n                assert(successor[vertex]\
    \ == next);\n                assert(graph.component[vertex] == component);\n \
    \               assert(graph.cycle_entry[vertex] == vertex);\n               \
    \ assert(graph.cycle_position[vertex] == position);\n                assert(graph.distance_to_cycle[vertex]\
    \ == 0);\n            }\n        }\n\n        int counted_cycle_vertices = 0;\n\
    \        for (int vertex = 0; vertex < n; vertex++) {\n            assert(0 <=\
    \ graph.component[vertex]);\n            assert(graph.component[vertex] < graph.component_count);\n\
    \            assert(0 <= graph.cycle_position[vertex]);\n            assert(graph.cycle_position[vertex]\
    \ < graph.cycle_size(vertex));\n            assert(graph.cycles[graph.component[vertex]][graph.cycle_position[vertex]]\
    \ ==\n                   graph.cycle_entry[vertex]);\n            assert(graph.jump(vertex,\
    \ graph.distance_to_cycle[vertex]) ==\n                   graph.cycle_entry[vertex]);\n\
    \            assert(graph.orbit(vertex) == naive_orbit(successor, vertex));\n\
    \            assert(graph.orbit_size(vertex) == int(graph.orbit(vertex).size()));\n\
    \            if (graph.on_cycle(vertex)) counted_cycle_vertices++;\n\n       \
    \     int predecessor_count = 0;\n            for (int from = 0; from < n; from++)\
    \ {\n                if (successor[from] == vertex) predecessor_count++;\n   \
    \         }\n            assert(int(graph.predecessors[vertex].size()) == predecessor_count);\n\
    \            for (int from : graph.predecessors[vertex]) {\n                assert(successor[from]\
    \ == vertex);\n            }\n\n            for (int query = 0; query < 12; query++)\
    \ {\n                const std::uint64_t steps =\n                    query ==\
    \ 0 ? random() : random() % std::uint64_t(4 * n + 1);\n                assert(graph.jump(vertex,\
    \ steps) == naive_jump(successor, vertex, steps));\n            }\n          \
    \  for (int query = 0; query < 8; query++) {\n                const int to = int(random()\
    \ % n);\n                const std::uint64_t step_count = random() % std::uint64_t(4\
    \ * n + 1);\n                assert(graph.visit_count(vertex, to, step_count)\
    \ ==\n                       naive_visit_count(successor, vertex, to, step_count));\n\
    \            }\n        }\n        assert(counted_cycle_vertices == cycle_vertex_count);\n\
    \n        for (int from = 0; from < n; from++) {\n            for (int to = 0;\
    \ to < n; to++) {\n                const long long expected_distance = naive_distance(successor,\
    \ from, to);\n                assert(graph.distance(from, to) == expected_distance);\n\
    \                assert(graph.reachable(from, to) == (expected_distance != -1));\n\
    \                const std::vector<int> path = graph.path(from, to);\n       \
    \         if (expected_distance == -1) {\n                    assert(path.empty());\n\
    \                } else {\n                    assert(int(path.size()) == expected_distance\
    \ + 1);\n                    int vertex = from;\n                    for (int\
    \ value : path) {\n                        assert(value == vertex);\n        \
    \                vertex = successor[vertex];\n                    }\n        \
    \            assert(path.back() == to);\n                }\n            }\n  \
    \      }\n\n        for (int query = 0; query < 40; query++) {\n            const\
    \ int first = int(random() % n);\n            const int second = int(random()\
    \ % n);\n            const long long expected =\n                naive_first_meeting_time(successor,\
    \ first, second);\n            assert(graph.first_meeting_time(first, second)\
    \ == expected);\n            assert(graph.first_meeting_time(second, first) ==\
    \ expected);\n            const int meeting_vertex = graph.first_meeting_vertex(first,\
    \ second);\n            assert(meeting_vertex ==\n                   (expected\
    \ == -1 ? -1 : naive_jump(successor, first, expected)));\n        }\n    }\n}\n\
    \n}  // namespace\n\nint main() {\n    test_focused_cases();\n    test_randomized();\n\
    \n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    long long first, second;\n    fast_input >> first >> second;\n\
    \    fast_output << first + second << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../graph/functional_graph.hpp\"\n#include \"../../utilities/fast_io.hpp\"\n\
    \n#include <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace {\n\n\
    int naive_jump(\n    const std::vector<int>& successor,\n    int vertex,\n   \
    \ std::uint64_t steps\n) {\n    const int n = int(successor.size());\n    std::vector<long\
    \ long> first_visit(n, -1);\n    std::vector<int> path;\n    while (first_visit[vertex]\
    \ == -1) {\n        first_visit[vertex] = int(path.size());\n        path.push_back(vertex);\n\
    \        vertex = successor[vertex];\n    }\n\n    if (steps < path.size()) return\
    \ path[steps];\n    const std::uint64_t cycle_start = std::uint64_t(first_visit[vertex]);\n\
    \    const std::uint64_t cycle_length = path.size() - cycle_start;\n    const\
    \ std::uint64_t position =\n        cycle_start + (steps - cycle_start) % cycle_length;\n\
    \    return path[position];\n}\n\nlong long naive_distance(\n    const std::vector<int>&\
    \ successor,\n    int from,\n    int to\n) {\n    const int n = int(successor.size());\n\
    \    std::vector<char> visited(n, false);\n    for (int distance = 0; !visited[from];\
    \ distance++) {\n        if (from == to) return distance;\n        visited[from]\
    \ = true;\n        from = successor[from];\n    }\n    return -1;\n}\n\nstd::vector<int>\
    \ naive_orbit(\n    const std::vector<int>& successor,\n    int vertex\n) {\n\
    \    std::vector<char> visited(successor.size(), false);\n    std::vector<int>\
    \ result;\n    while (!visited[vertex]) {\n        visited[vertex] = true;\n \
    \       result.push_back(vertex);\n        vertex = successor[vertex];\n    }\n\
    \    return result;\n}\n\nstd::uint64_t naive_visit_count(\n    const std::vector<int>&\
    \ successor,\n    int from,\n    int to,\n    std::uint64_t step_count\n) {\n\
    \    std::uint64_t result = 0;\n    for (std::uint64_t step = 0; step < step_count;\
    \ step++) {\n        if (from == to) result++;\n        from = successor[from];\n\
    \    }\n    return result;\n}\n\nlong long naive_first_meeting_time(\n    const\
    \ std::vector<int>& successor,\n    int first,\n    int second\n) {\n    const\
    \ int n = int(successor.size());\n    std::vector<char> visited(n * n, false);\n\
    \    for (int time = 0; !visited[first * n + second]; time++) {\n        if (first\
    \ == second) return time;\n        visited[first * n + second] = true;\n     \
    \   first = successor[first];\n        second = successor[second];\n    }\n  \
    \  return -1;\n}\n\nvoid test_focused_cases() {\n    const std::vector<int> successor\
    \ = {1, 2, 0, 2, 3, 6, 5, 6, 3};\n    m1une::graph::FunctionalGraph graph(successor);\n\
    \n    assert(graph.size() == 9);\n    assert(!graph.empty());\n    assert(graph.component_count\
    \ == 2);\n    assert(graph.same_component(0, 4));\n    assert(!graph.same_component(0,\
    \ 5));\n    assert(graph.on_cycle(0));\n    assert(graph.on_cycle(5));\n    assert(!graph.on_cycle(4));\n\
    \    assert(graph.cycle_entry[4] == 2);\n    assert(graph.distance_to_cycle[4]\
    \ == 2);\n    assert(graph.cycle_size(4) == 3);\n    assert(graph.cycle_size(7)\
    \ == 2);\n    assert(graph.component_size[graph.component[4]] == 6);\n    assert(graph.component_size[graph.component[7]]\
    \ == 3);\n    assert((graph.predecessors[3] == std::vector<int>{4, 8}));\n   \
    \ assert(graph.orbit_size(4) == 5);\n    assert((graph.orbit(4) == std::vector<int>{4,\
    \ 3, 2, 0, 1}));\n\n    assert(graph.jump(4, 0) == 4);\n    assert(graph.jump(4,\
    \ 1) == 3);\n    assert(graph.jump(4, 2) == 2);\n    assert(graph.jump(4, 4) ==\
    \ 1);\n    assert(graph.jump(7, 3) == 6);\n    assert(graph.jump(4, UINT64_C(1000000000000000000))\
    \ ==\n           naive_jump(successor, 4, UINT64_C(1000000000000000000)));\n\n\
    \    assert(graph.distance(4, 4) == 0);\n    assert(graph.distance(4, 3) == 1);\n\
    \    assert(graph.distance(4, 2) == 2);\n    assert(graph.distance(4, 1) == 4);\n\
    \    assert(graph.distance(1, 4) == -1);\n    assert(graph.distance(3, 4) == -1);\n\
    \    assert(graph.distance(4, 5) == -1);\n    assert(graph.distance(7, 5) == 2);\n\
    \    assert(graph.reachable(4, 1));\n    assert(!graph.reachable(1, 4));\n   \
    \ assert((graph.path(4, 1) == std::vector<int>{4, 3, 2, 0, 1}));\n    assert(graph.path(1,\
    \ 4).empty());\n\n    assert(graph.visit_count(4, 2, 0) == 0);\n    assert(graph.visit_count(4,\
    \ 2, 3) == 1);\n    assert(graph.visit_count(4, 2, 5) == 1);\n    assert(graph.visit_count(4,\
    \ 2, 6) == 2);\n    assert(graph.visit_count(4, 3, UINT64_MAX) == 1);\n    assert(graph.visit_count(4,\
    \ 5, UINT64_MAX) == 0);\n\n    assert(graph.first_meeting_time(4, 8) == 1);\n\
    \    assert(graph.first_meeting_vertex(4, 8) == 3);\n    assert(graph.first_meeting_time(4,\
    \ 0) == 2);\n    assert(graph.first_meeting_vertex(4, 0) == 2);\n    assert(graph.first_meeting_time(4,\
    \ 1) == -1);\n    assert(graph.first_meeting_vertex(4, 1) == -1);\n    assert(graph.first_meeting_time(7,\
    \ 5) == 1);\n    assert(graph.first_meeting_vertex(7, 5) == 6);\n    assert(graph.first_meeting_time(4,\
    \ 5) == -1);\n    assert(graph.first_meeting_time(2, 2) == 0);\n\n    graph.build(std::vector<int>{0});\n\
    \    assert(graph.size() == 1);\n    assert(graph.component_count == 1);\n   \
    \ assert(graph.on_cycle(0));\n    assert(graph.jump(0, UINT64_MAX) == 0);\n  \
    \  assert(graph.distance(0, 0) == 0);\n    assert(graph.orbit_size(0) == 1);\n\
    \    assert(graph.visit_count(0, 0, UINT64_MAX) == UINT64_MAX);\n    assert(graph.first_meeting_time(0,\
    \ 0) == 0);\n\n    graph.build(std::vector<int>());\n    assert(graph.empty());\n\
    \    assert(graph.component_count == 0);\n    assert(graph.cycles.empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = UINT64_C(0x5f3759df12345678);\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 500; trial++) {\n        const int n = 1 + int(random() % 60);\n        std::vector<int>\
    \ successor(n);\n        for (int& to : successor) to = int(random() % n);\n \
    \       m1une::graph::FunctionalGraph graph(successor);\n\n        assert(graph.size()\
    \ == n);\n        assert(1 <= graph.component_count && graph.component_count <=\
    \ n);\n        std::vector<int> expected_component_size(graph.component_count,\
    \ 0);\n        for (int component : graph.component) expected_component_size[component]++;\n\
    \        assert(graph.component_size == expected_component_size);\n        int\
    \ cycle_vertex_count = 0;\n        for (int component = 0; component < graph.component_count;\
    \ component++) {\n            const std::vector<int>& cycle = graph.cycles[component];\n\
    \            assert(!cycle.empty());\n            cycle_vertex_count += int(cycle.size());\n\
    \            for (int position = 0; position < int(cycle.size()); position++)\
    \ {\n                const int vertex = cycle[position];\n                const\
    \ int next = cycle[(position + 1) % cycle.size()];\n                assert(successor[vertex]\
    \ == next);\n                assert(graph.component[vertex] == component);\n \
    \               assert(graph.cycle_entry[vertex] == vertex);\n               \
    \ assert(graph.cycle_position[vertex] == position);\n                assert(graph.distance_to_cycle[vertex]\
    \ == 0);\n            }\n        }\n\n        int counted_cycle_vertices = 0;\n\
    \        for (int vertex = 0; vertex < n; vertex++) {\n            assert(0 <=\
    \ graph.component[vertex]);\n            assert(graph.component[vertex] < graph.component_count);\n\
    \            assert(0 <= graph.cycle_position[vertex]);\n            assert(graph.cycle_position[vertex]\
    \ < graph.cycle_size(vertex));\n            assert(graph.cycles[graph.component[vertex]][graph.cycle_position[vertex]]\
    \ ==\n                   graph.cycle_entry[vertex]);\n            assert(graph.jump(vertex,\
    \ graph.distance_to_cycle[vertex]) ==\n                   graph.cycle_entry[vertex]);\n\
    \            assert(graph.orbit(vertex) == naive_orbit(successor, vertex));\n\
    \            assert(graph.orbit_size(vertex) == int(graph.orbit(vertex).size()));\n\
    \            if (graph.on_cycle(vertex)) counted_cycle_vertices++;\n\n       \
    \     int predecessor_count = 0;\n            for (int from = 0; from < n; from++)\
    \ {\n                if (successor[from] == vertex) predecessor_count++;\n   \
    \         }\n            assert(int(graph.predecessors[vertex].size()) == predecessor_count);\n\
    \            for (int from : graph.predecessors[vertex]) {\n                assert(successor[from]\
    \ == vertex);\n            }\n\n            for (int query = 0; query < 12; query++)\
    \ {\n                const std::uint64_t steps =\n                    query ==\
    \ 0 ? random() : random() % std::uint64_t(4 * n + 1);\n                assert(graph.jump(vertex,\
    \ steps) == naive_jump(successor, vertex, steps));\n            }\n          \
    \  for (int query = 0; query < 8; query++) {\n                const int to = int(random()\
    \ % n);\n                const std::uint64_t step_count = random() % std::uint64_t(4\
    \ * n + 1);\n                assert(graph.visit_count(vertex, to, step_count)\
    \ ==\n                       naive_visit_count(successor, vertex, to, step_count));\n\
    \            }\n        }\n        assert(counted_cycle_vertices == cycle_vertex_count);\n\
    \n        for (int from = 0; from < n; from++) {\n            for (int to = 0;\
    \ to < n; to++) {\n                const long long expected_distance = naive_distance(successor,\
    \ from, to);\n                assert(graph.distance(from, to) == expected_distance);\n\
    \                assert(graph.reachable(from, to) == (expected_distance != -1));\n\
    \                const std::vector<int> path = graph.path(from, to);\n       \
    \         if (expected_distance == -1) {\n                    assert(path.empty());\n\
    \                } else {\n                    assert(int(path.size()) == expected_distance\
    \ + 1);\n                    int vertex = from;\n                    for (int\
    \ value : path) {\n                        assert(value == vertex);\n        \
    \                vertex = successor[vertex];\n                    }\n        \
    \            assert(path.back() == to);\n                }\n            }\n  \
    \      }\n\n        for (int query = 0; query < 40; query++) {\n            const\
    \ int first = int(random() % n);\n            const int second = int(random()\
    \ % n);\n            const long long expected =\n                naive_first_meeting_time(successor,\
    \ first, second);\n            assert(graph.first_meeting_time(first, second)\
    \ == expected);\n            assert(graph.first_meeting_time(second, first) ==\
    \ expected);\n            const int meeting_vertex = graph.first_meeting_vertex(first,\
    \ second);\n            assert(meeting_vertex ==\n                   (expected\
    \ == -1 ? -1 : naive_jump(successor, first, expected)));\n        }\n    }\n}\n\
    \n}  // namespace\n\nint main() {\n    test_focused_cases();\n    test_randomized();\n\
    \n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    long long first, second;\n    fast_input >> first >> second;\n\
    \    fast_output << first + second << '\\n';\n}\n"
  dependsOn:
  - graph/functional_graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/functional_graph.test.cpp
  requiredBy: []
  timestamp: '2026-08-24 02:34:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/functional_graph.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/functional_graph.test.cpp
- /verify/verify/graph/functional_graph.test.cpp.html
title: verify/graph/functional_graph.test.cpp
---
