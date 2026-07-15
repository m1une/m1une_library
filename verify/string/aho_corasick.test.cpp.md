---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick
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
    PROBLEM: https://judge.yosupo.jp/problem/aho_corasick
    links:
    - https://judge.yosupo.jp/problem/aho_corasick
  bundledCode: "#line 1 \"verify/string/aho_corasick.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aho_corasick\"\n\n#line 1 \"string/aho_corasick.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \n// Aho-Corasick automaton for a contiguous character alphabet.\ntemplate <int\
    \ AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct AhoCorasick {\n    static_assert(0\
    \ < AlphabetSize);\n\n    using node_id = int;\n    static constexpr node_id null_node\
    \ = -1;\n\n    struct Node {\n        // Completed automaton transitions. Valid\
    \ after build().\n        std::array<node_id, AlphabetSize> next;\n        node_id\
    \ failure;\n        node_id output_link;\n        node_id parent;\n        int\
    \ parent_symbol;\n        int depth;\n        std::vector<node_id> children;\n\
    \        std::vector<node_id> failure_children;\n        std::vector<int> pattern_ids;\n\
    \n        Node(\n            node_id parent_value = null_node,\n            int\
    \ parent_symbol_value = -1,\n            int depth_value = 0\n        ) : failure(0),\n\
    \            output_link(null_node),\n            parent(parent_value),\n    \
    \        parent_symbol(parent_symbol_value),\n            depth(depth_value) {\n\
    \            next.fill(null_node);\n        }\n    };\n\n   private:\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _pattern_length;\n    std::vector<node_id> _pattern_node;\n\
    \    std::vector<node_id> _bfs_order;\n    bool _built;\n\n    template <class\
    \ Symbol>\n    static int symbol_index(const Symbol& symbol) {\n        int index\
    \ = int(symbol) - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n\
    \        return index;\n    }\n\n    node_id new_node(node_id parent, int parent_symbol)\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        assert(_nodes[parent].depth < std::numeric_limits<int>::max());\n   \
    \     _nodes.emplace_back(parent, parent_symbol, _nodes[parent].depth + 1);\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n   public:\n    AhoCorasick()\
    \ : _nodes(1), _built(false) {}\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    bool built() const {\n        return _built;\n    }\n\n   \
    \ int pattern_count() const {\n        return int(_pattern_length.size());\n \
    \   }\n\n    int pattern_length(int pattern_id) const {\n        assert(0 <= pattern_id\
    \ && pattern_id < pattern_count());\n        return _pattern_length[pattern_id];\n\
    \    }\n\n    node_id pattern_node(int pattern_id) const {\n        assert(0 <=\
    \ pattern_id && pattern_id < pattern_count());\n        return _pattern_node[pattern_id];\n\
    \    }\n\n    std::size_t node_count() const {\n        return _nodes.size();\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n   \
    \ // Returns nodes in failure-link BFS order, beginning with the root.\n    const\
    \ std::vector<node_id>& bfs_order() const {\n        assert(_built);\n       \
    \ return _bfs_order;\n    }\n\n    void reserve(std::size_t node_capacity) {\n\
    \        assert(!_built);\n        _nodes.reserve(node_capacity);\n    }\n\n \
    \   void clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n\
    \        _pattern_length.clear();\n        _pattern_node.clear();\n        _bfs_order.clear();\n\
    \        _built = false;\n    }\n\n    // Inserts a pattern and returns its insertion-order\
    \ ID.\n    template <class Sequence>\n    int insert(const Sequence& pattern)\
    \ {\n        assert(!_built);\n        int pattern_id = pattern_count();\n   \
    \     int length = 0;\n        node_id state = root();\n        for (const auto&\
    \ symbol : pattern) {\n            assert(length < std::numeric_limits<int>::max());\n\
    \            int index = symbol_index(symbol);\n            if (_nodes[state].next[index]\
    \ == null_node) {\n                node_id child = new_node(state, index);\n \
    \               _nodes[state].next[index] = child;\n                _nodes[state].children.push_back(child);\n\
    \            }\n            state = _nodes[state].next[index];\n            length++;\n\
    \        }\n        _nodes[state].pattern_ids.push_back(pattern_id);\n       \
    \ _pattern_length.push_back(length);\n        _pattern_node.push_back(state);\n\
    \        return pattern_id;\n    }\n\n    // Builds failure links and completes\
    \ every automaton transition.\n    void build() {\n        assert(!_built);\n\
    \        std::queue<node_id> queue;\n        _bfs_order.clear();\n        _bfs_order.reserve(_nodes.size());\n\
    \        _bfs_order.push_back(root());\n\n        for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n            node_id child = _nodes[root()].next[symbol];\n\
    \            if (child == null_node) {\n                _nodes[root()].next[symbol]\
    \ = root();\n            } else {\n                _nodes[root()].next[symbol]\
    \ = child;\n                _nodes[child].failure = root();\n                _nodes[child].output_link\
    \ =\n                    _nodes[root()].pattern_ids.empty() ? null_node : root();\n\
    \                _nodes[root()].failure_children.push_back(child);\n         \
    \       queue.push(child);\n            }\n        }\n\n        while (!queue.empty())\
    \ {\n            node_id state = queue.front();\n            queue.pop();\n  \
    \          _bfs_order.push_back(state);\n\n            for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n                node_id child = _nodes[state].next[symbol];\n\
    \                if (child == null_node) {\n                    _nodes[state].next[symbol]\
    \ =\n                        _nodes[_nodes[state].failure].next[symbol];\n   \
    \                 continue;\n                }\n\n                _nodes[state].next[symbol]\
    \ = child;\n                node_id failure =\n                    _nodes[_nodes[state].failure].next[symbol];\n\
    \                _nodes[child].failure = failure;\n                _nodes[child].output_link\
    \ =\n                    _nodes[failure].pattern_ids.empty()\n               \
    \         ? _nodes[failure].output_link\n                        : failure;\n\
    \                _nodes[failure].failure_children.push_back(child);\n        \
    \        queue.push(child);\n            }\n        }\n        _built = true;\n\
    \    }\n\n    template <class Symbol>\n    node_id transition(node_id state, const\
    \ Symbol& symbol) const {\n        assert(_built);\n        assert(0 <= state\
    \ && std::size_t(state) < _nodes.size());\n        return _nodes[state].next[symbol_index(symbol)];\n\
    \    }\n\n    // Calls callback(pattern_id) for every pattern ending at `state`.\n\
    \    template <class Callback>\n    void for_each_output(node_id state, Callback\
    \ callback) const {\n        assert(_built);\n        assert(0 <= state && std::size_t(state)\
    \ < _nodes.size());\n        while (state != null_node) {\n            for (int\
    \ pattern_id : _nodes[state].pattern_ids) {\n                callback(pattern_id);\n\
    \            }\n            state = _nodes[state].output_link;\n        }\n  \
    \  }\n\n    // Calls callback(end, pattern_id) for every occurrence. `end` is\
    \ the\n    // exclusive end position. Empty patterns occur at every text boundary.\n\
    \    template <class Sequence, class Callback>\n    void match(const Sequence&\
    \ text, Callback callback) const {\n        assert(_built);\n        node_id state\
    \ = root();\n        for_each_output(state, [&callback](int pattern_id) {\n  \
    \          callback(0, pattern_id);\n        });\n\n        int end = 0;\n   \
    \     for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            end++;\n            for_each_output(state, [&callback,\
    \ end](int pattern_id) {\n                callback(end, pattern_id);\n       \
    \     });\n        }\n    }\n\n    // Counts occurrences of every inserted pattern\
    \ in linear time.\n    template <class Sequence>\n    std::vector<long long> count_occurrences(const\
    \ Sequence& text) const {\n        assert(_built);\n        std::vector<long long>\
    \ visits(_nodes.size(), 0);\n        node_id state = root();\n        visits[root()]++;\n\
    \        for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            visits[state]++;\n        }\n\n        for (std::size_t\
    \ index = _bfs_order.size(); index-- > 1;) {\n            node_id current = _bfs_order[index];\n\
    \            visits[_nodes[current].failure] += visits[current];\n        }\n\n\
    \        std::vector<long long> result(pattern_count(), 0);\n        for (node_id\
    \ current : _bfs_order) {\n            for (int pattern_id : _nodes[current].pattern_ids)\
    \ {\n                result[pattern_id] = visits[current];\n            }\n  \
    \      }\n        return result;\n    }\n};\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/string/aho_corasick.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/string/aho_corasick.test.cpp\"\n#include <cstdint>\n#line 1 \"\
    utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include <charconv>\n\
    #line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <type_traits>\n#include <utility>\n#include <unistd.h>\n\n\
    namespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/string/aho_corasick.test.cpp\"\
    \n#include <tuple>\n#line 12 \"verify/string/aho_corasick.test.cpp\"\n\nnamespace\
    \ {\n\nvoid check(\n    const std::vector<std::string>& patterns,\n    const std::string&\
    \ text\n) {\n    m1une::string::AhoCorasick<4, 'a'> automaton;\n    std::size_t\
    \ total_length = 1;\n    for (const std::string& pattern : patterns) {\n     \
    \   total_length += pattern.size();\n    }\n    automaton.reserve(total_length);\n\
    \    for (int id = 0; id < int(patterns.size()); ++id) {\n        assert(automaton.insert(patterns[id])\
    \ == id);\n        assert(automaton.pattern_length(id) == int(patterns[id].size()));\n\
    \    }\n    automaton.build();\n    assert(automaton.built());\n    assert(automaton.pattern_count()\
    \ == int(patterns.size()));\n    assert(automaton.nodes().size() == automaton.node_count());\n\
    \    assert(automaton.bfs_order().size() == automaton.node_count());\n    assert(automaton.bfs_order().front()\
    \ == automaton.root());\n\n    std::vector<int> failure_parent_count(automaton.node_count(),\
    \ 0);\n    for (const auto& node : automaton.nodes()) {\n        for (int child\
    \ : node.failure_children) {\n            failure_parent_count[child]++;\n   \
    \     }\n    }\n    for (int node = 1; node < int(automaton.node_count()); ++node)\
    \ {\n        assert(failure_parent_count[node] == 1);\n        assert(\n     \
    \       automaton.node(automaton.node(node).failure).depth\n            < automaton.node(node).depth\n\
    \        );\n        assert(\n            std::find(\n                automaton.node(automaton.node(node).parent).children.begin(),\n\
    \                automaton.node(automaton.node(node).parent).children.end(),\n\
    \                node\n            ) != automaton.node(automaton.node(node).parent).children.end()\n\
    \        );\n        assert(\n            automaton.node(automaton.node(node).parent)\n\
    \                .next[automaton.node(node).parent_symbol]\n            == node\n\
    \        );\n    }\n    for (int id = 0; id < int(patterns.size()); ++id) {\n\
    \        [[maybe_unused]] int terminal = automaton.pattern_node(id);\n       \
    \ assert(automaton.node(terminal).depth == int(patterns[id].size()));\n      \
    \  assert(\n            std::find(\n                automaton.node(terminal).pattern_ids.begin(),\n\
    \                automaton.node(terminal).pattern_ids.end(),\n               \
    \ id\n            ) != automaton.node(terminal).pattern_ids.end()\n        );\n\
    \    }\n\n    std::vector<std::tuple<int, int>> actual;\n    automaton.match(text,\
    \ [&actual](int end, int pattern_id) {\n        actual.emplace_back(end, pattern_id);\n\
    \    });\n    std::sort(actual.begin(), actual.end());\n\n    std::vector<std::tuple<int,\
    \ int>> expected;\n    std::vector<long long> expected_count(patterns.size(),\
    \ 0);\n    for (int end = 0; end <= int(text.size()); ++end) {\n        for (int\
    \ id = 0; id < int(patterns.size()); ++id) {\n            int length = int(patterns[id].size());\n\
    \            if (\n                length <= end &&\n                text.compare(end\
    \ - length, length, patterns[id]) == 0\n            ) {\n                expected.emplace_back(end,\
    \ id);\n                expected_count[id]++;\n            }\n        }\n    }\n\
    \    std::sort(expected.begin(), expected.end());\n    assert(actual == expected);\n\
    \    assert(automaton.count_occurrences(text) == expected_count);\n}\n\nvoid test_fixed()\
    \ {\n    check({}, \"abacaba\");\n    check({\"\"}, \"\");\n    check({\"\", \"\
    \", \"a\", \"a\", \"aa\", \"ba\"}, \"aaaaba\");\n\n    m1une::string::AhoCorasick<10,\
    \ '0'> digits;\n    [[maybe_unused]] int first = digits.insert(std::string(\"\
    12\"));\n    [[maybe_unused]] int second = digits.insert(std::string(\"2\"));\n\
    \    digits.build();\n    auto count = digits.count_occurrences(std::string(\"\
    1212\"));\n    assert(count[first] == 2);\n    assert(count[second] == 2);\n\n\
    \    digits.clear();\n    assert(!digits.built());\n    assert(digits.pattern_count()\
    \ == 0);\n    assert(digits.node_count() == 1);\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 313;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 4000; ++trial) {\n        int pattern_count\
    \ = int(random() % 15);\n        std::vector<std::string> patterns;\n        for\
    \ (int id = 0; id < pattern_count; ++id) {\n            int length = int(random()\
    \ % 8);\n            std::string pattern(length, 'a');\n            for (char&\
    \ symbol : pattern) {\n                symbol = char('a' + random() % 4);\n  \
    \          }\n            patterns.push_back(std::move(pattern));\n        }\n\
    \n        int text_length = int(random() % 35);\n        std::string text(text_length,\
    \ 'a');\n        for (char& symbol : text) {\n            symbol = char('a' +\
    \ random() % 4);\n        }\n        check(patterns, text);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \    int n;\n    fast_input >> n;\n    m1une::string::AhoCorasick<> automaton;\n\
    \    for (int i = 0; i < n; i++) {\n        std::string pattern;\n        fast_input\
    \ >> pattern;\n        automaton.insert(pattern);\n    }\n    automaton.build();\n\
    \n    int node_count = int(automaton.node_count());\n    fast_output << node_count\
    \ << '\\n';\n    for (int id = 1; id < node_count; id++) {\n        const auto&\
    \ node = automaton.node(id);\n        fast_output << node.parent << ' ' << node.failure\
    \ << '\\n';\n    }\n    for (int i = 0; i < n; i++) {\n        if (i) fast_output\
    \ << ' ';\n        fast_output << automaton.pattern_node(i);\n    }\n    fast_output\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aho_corasick\"\n\n#include\
    \ \"../../string/aho_corasick.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <string>\n\
    #include <tuple>\n#include <vector>\n\nnamespace {\n\nvoid check(\n    const std::vector<std::string>&\
    \ patterns,\n    const std::string& text\n) {\n    m1une::string::AhoCorasick<4,\
    \ 'a'> automaton;\n    std::size_t total_length = 1;\n    for (const std::string&\
    \ pattern : patterns) {\n        total_length += pattern.size();\n    }\n    automaton.reserve(total_length);\n\
    \    for (int id = 0; id < int(patterns.size()); ++id) {\n        assert(automaton.insert(patterns[id])\
    \ == id);\n        assert(automaton.pattern_length(id) == int(patterns[id].size()));\n\
    \    }\n    automaton.build();\n    assert(automaton.built());\n    assert(automaton.pattern_count()\
    \ == int(patterns.size()));\n    assert(automaton.nodes().size() == automaton.node_count());\n\
    \    assert(automaton.bfs_order().size() == automaton.node_count());\n    assert(automaton.bfs_order().front()\
    \ == automaton.root());\n\n    std::vector<int> failure_parent_count(automaton.node_count(),\
    \ 0);\n    for (const auto& node : automaton.nodes()) {\n        for (int child\
    \ : node.failure_children) {\n            failure_parent_count[child]++;\n   \
    \     }\n    }\n    for (int node = 1; node < int(automaton.node_count()); ++node)\
    \ {\n        assert(failure_parent_count[node] == 1);\n        assert(\n     \
    \       automaton.node(automaton.node(node).failure).depth\n            < automaton.node(node).depth\n\
    \        );\n        assert(\n            std::find(\n                automaton.node(automaton.node(node).parent).children.begin(),\n\
    \                automaton.node(automaton.node(node).parent).children.end(),\n\
    \                node\n            ) != automaton.node(automaton.node(node).parent).children.end()\n\
    \        );\n        assert(\n            automaton.node(automaton.node(node).parent)\n\
    \                .next[automaton.node(node).parent_symbol]\n            == node\n\
    \        );\n    }\n    for (int id = 0; id < int(patterns.size()); ++id) {\n\
    \        [[maybe_unused]] int terminal = automaton.pattern_node(id);\n       \
    \ assert(automaton.node(terminal).depth == int(patterns[id].size()));\n      \
    \  assert(\n            std::find(\n                automaton.node(terminal).pattern_ids.begin(),\n\
    \                automaton.node(terminal).pattern_ids.end(),\n               \
    \ id\n            ) != automaton.node(terminal).pattern_ids.end()\n        );\n\
    \    }\n\n    std::vector<std::tuple<int, int>> actual;\n    automaton.match(text,\
    \ [&actual](int end, int pattern_id) {\n        actual.emplace_back(end, pattern_id);\n\
    \    });\n    std::sort(actual.begin(), actual.end());\n\n    std::vector<std::tuple<int,\
    \ int>> expected;\n    std::vector<long long> expected_count(patterns.size(),\
    \ 0);\n    for (int end = 0; end <= int(text.size()); ++end) {\n        for (int\
    \ id = 0; id < int(patterns.size()); ++id) {\n            int length = int(patterns[id].size());\n\
    \            if (\n                length <= end &&\n                text.compare(end\
    \ - length, length, patterns[id]) == 0\n            ) {\n                expected.emplace_back(end,\
    \ id);\n                expected_count[id]++;\n            }\n        }\n    }\n\
    \    std::sort(expected.begin(), expected.end());\n    assert(actual == expected);\n\
    \    assert(automaton.count_occurrences(text) == expected_count);\n}\n\nvoid test_fixed()\
    \ {\n    check({}, \"abacaba\");\n    check({\"\"}, \"\");\n    check({\"\", \"\
    \", \"a\", \"a\", \"aa\", \"ba\"}, \"aaaaba\");\n\n    m1une::string::AhoCorasick<10,\
    \ '0'> digits;\n    [[maybe_unused]] int first = digits.insert(std::string(\"\
    12\"));\n    [[maybe_unused]] int second = digits.insert(std::string(\"2\"));\n\
    \    digits.build();\n    auto count = digits.count_occurrences(std::string(\"\
    1212\"));\n    assert(count[first] == 2);\n    assert(count[second] == 2);\n\n\
    \    digits.clear();\n    assert(!digits.built());\n    assert(digits.pattern_count()\
    \ == 0);\n    assert(digits.node_count() == 1);\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 313;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 4000; ++trial) {\n        int pattern_count\
    \ = int(random() % 15);\n        std::vector<std::string> patterns;\n        for\
    \ (int id = 0; id < pattern_count; ++id) {\n            int length = int(random()\
    \ % 8);\n            std::string pattern(length, 'a');\n            for (char&\
    \ symbol : pattern) {\n                symbol = char('a' + random() % 4);\n  \
    \          }\n            patterns.push_back(std::move(pattern));\n        }\n\
    \n        int text_length = int(random() % 35);\n        std::string text(text_length,\
    \ 'a');\n        for (char& symbol : text) {\n            symbol = char('a' +\
    \ random() % 4);\n        }\n        check(patterns, text);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \    int n;\n    fast_input >> n;\n    m1une::string::AhoCorasick<> automaton;\n\
    \    for (int i = 0; i < n; i++) {\n        std::string pattern;\n        fast_input\
    \ >> pattern;\n        automaton.insert(pattern);\n    }\n    automaton.build();\n\
    \n    int node_count = int(automaton.node_count());\n    fast_output << node_count\
    \ << '\\n';\n    for (int id = 1; id < node_count; id++) {\n        const auto&\
    \ node = automaton.node(id);\n        fast_output << node.parent << ' ' << node.failure\
    \ << '\\n';\n    }\n    for (int i = 0; i < n; i++) {\n        if (i) fast_output\
    \ << ' ';\n        fast_output << automaton.pattern_node(i);\n    }\n    fast_output\
    \ << '\\n';\n}\n"
  dependsOn:
  - string/aho_corasick.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/aho_corasick.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/aho_corasick.test.cpp
layout: document
redirect_from:
- /verify/verify/string/aho_corasick.test.cpp
- /verify/verify/string/aho_corasick.test.cpp.html
title: verify/string/aho_corasick.test.cpp
---
