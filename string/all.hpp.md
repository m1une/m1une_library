---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  - icon: ':heavy_check_mark:'
    path: string/kmp.hpp
    title: Knuth-Morris-Pratt
  - icon: ':heavy_check_mark:'
    path: string/levenshtein_distance.hpp
    title: Levenshtein Distance
  - icon: ':heavy_check_mark:'
    path: string/longest_common_extension.hpp
    title: Longest Common Extension
  - icon: ':heavy_check_mark:'
    path: string/longest_common_subsequence.hpp
    title: Longest Common Subsequence
  - icon: ':heavy_check_mark:'
    path: string/longest_common_substring.hpp
    title: Longest Common Substring
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: Lyndon Factorization
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: Manacher Algorithm
  - icon: ':heavy_check_mark:'
    path: string/minimum_rotation.hpp
    title: Minimum Rotation
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Static Rolling Hash
  - icon: ':heavy_check_mark:'
    path: string/runs.hpp
    title: Runs
  - icon: ':heavy_check_mark:'
    path: string/string_hash.hpp
    title: String Hash
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.hpp
    title: Suffix Automaton
  - icon: ':heavy_check_mark:'
    path: string/trie.hpp
    title: Trie
  - icon: ':heavy_check_mark:'
    path: string/wildcard_pattern_matching.hpp
    title: Wildcard Pattern Matching
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: Z Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/all.hpp\"\n\n\n\n#line 1 \"string/aho_corasick.hpp\"\
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
    \ m1une\n\n\n#line 1 \"string/eertree.hpp\"\n\n\n\n#line 8 \"string/eertree.hpp\"\
    \n#include <utility>\n#line 10 \"string/eertree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct\
    \ Eertree {\n    static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n\
    \    static constexpr node_id even_root = 0;\n    static constexpr node_id odd_root\
    \ = 1;\n    static constexpr node_id null_node = -1;\n\n    struct Node {\n  \
    \      std::array<node_id, AlphabetSize> next;\n        node_id suffix_link;\n\
    \        node_id series_link;\n        int length;\n        int diff;\n      \
    \  int suffix_count;\n        int first_end;\n        long long suffix_occurrences;\n\
    \n        Node(int length_value = 0, node_id suffix_link_value = even_root, node_id\
    \ series_link_value = even_root)\n            : suffix_link(suffix_link_value),\n\
    \              series_link(series_link_value),\n              length(length_value),\n\
    \              diff(0),\n              suffix_count(0),\n              first_end(0),\n\
    \              suffix_occurrences(0) {\n            next.fill(null_node);\n  \
    \      }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _text;\n    std::vector<node_id> _longest_suffix;\n    node_id _last;\n\n  \
    \  template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    node_id find_extendable(node_id\
    \ node, int position, int symbol) const {\n        while (true) {\n          \
    \  int length = _nodes[node].length;\n            int left = position - length\
    \ - 1;\n            if (0 <= left && _text[left] == symbol) return node;\n   \
    \         node = _nodes[node].suffix_link;\n        }\n    }\n\n    node_id new_node(int\
    \ length) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(length);\n        return int(_nodes.size()) - 1;\n\
    \    }\n\n   public:\n    Eertree() {\n        clear();\n    }\n\n    template\
    \ <class Sequence>\n    explicit Eertree(const Sequence& sequence) {\n       \
    \ clear();\n        build(sequence);\n    }\n\n    int size() const {\n      \
    \  return int(_nodes.size()) - 2;\n    }\n\n    bool empty() const {\n       \
    \ return size() == 0;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int text_length() const {\n        return int(_text.size());\n \
    \   }\n\n    node_id last() const {\n        return _last;\n    }\n\n    int longest_suffix_length()\
    \ const {\n        return _nodes[_last].length;\n    }\n\n    const Node& node(node_id\
    \ id) const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id];\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    node_id longest_suffix_node(int prefix_length) const {\n       \
    \ assert(1 <= prefix_length && prefix_length <= text_length());\n        return\
    \ _longest_suffix[prefix_length - 1];\n    }\n\n    const std::vector<node_id>&\
    \ longest_suffix_nodes() const {\n        return _longest_suffix;\n    }\n\n \
    \   template <class Callback>\n    void for_each_suffix(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        while (id >=\
    \ 2) {\n            callback(id);\n            id = _nodes[id].suffix_link;\n\
    \        }\n    }\n\n    template <class Callback>\n    void for_each_suffix(Callback\
    \ callback) const {\n        for_each_suffix(_last, callback);\n    }\n\n    void\
    \ reserve(std::size_t text_capacity) {\n        _text.reserve(text_capacity);\n\
    \        _longest_suffix.reserve(text_capacity);\n        _nodes.reserve(text_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _nodes.clear();\n        _nodes.emplace_back(0,\
    \ odd_root, even_root);\n        _nodes.emplace_back(-1, odd_root, odd_root);\n\
    \        _text.clear();\n        _longest_suffix.clear();\n        _last = even_root;\n\
    \    }\n\n    template <class Symbol>\n    node_id add(const Symbol& value) {\n\
    \        int symbol = symbol_index(value);\n        int position = int(_text.size());\n\
    \        _text.push_back(symbol);\n\n        node_id current = find_extendable(_last,\
    \ position, symbol);\n        node_id next = _nodes[current].next[symbol];\n \
    \       if (next == null_node) {\n            int length = _nodes[current].length\
    \ + 2;\n            next = new_node(length);\n            _nodes[current].next[symbol]\
    \ = next;\n\n            node_id suffix_link = even_root;\n            if (length\
    \ != 1) {\n                node_id candidate = find_extendable(_nodes[current].suffix_link,\
    \ position, symbol);\n                suffix_link = _nodes[candidate].next[symbol];\n\
    \                assert(suffix_link != null_node);\n            }\n\n        \
    \    Node& created = _nodes[next];\n            created.suffix_link = suffix_link;\n\
    \            created.diff = created.length - _nodes[suffix_link].length;\n   \
    \         created.series_link =\n                created.diff == _nodes[suffix_link].diff\
    \ ? _nodes[suffix_link].series_link : suffix_link;\n            created.suffix_count\
    \ = _nodes[suffix_link].suffix_count + 1;\n            created.first_end = position\
    \ + 1;\n        }\n\n        _last = next;\n        _nodes[_last].suffix_occurrences++;\n\
    \        _longest_suffix.push_back(_last);\n        return _last;\n    }\n\n \
    \   template <class Sequence>\n    void build(const Sequence& sequence) {\n  \
    \      for (const auto& symbol : sequence) add(symbol);\n    }\n\n    std::vector<long\
    \ long> occurrence_counts() const {\n        std::vector<long long> result(_nodes.size(),\
    \ 0);\n        for (node_id id = 0; id < node_count(); id++) {\n            result[id]\
    \ = _nodes[id].suffix_occurrences;\n        }\n        for (node_id id = node_count()\
    \ - 1; id >= 2; id--) {\n            result[_nodes[id].suffix_link] += result[id];\n\
    \        }\n        return result;\n    }\n\n    std::pair<int, int> first_occurrence(node_id\
    \ id) const {\n        assert(2 <= id && id < node_count());\n        int end\
    \ = _nodes[id].first_end;\n        return {end - _nodes[id].length, end};\n  \
    \  }\n};\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing\
    \ PalindromicTree = Eertree<AlphabetSize, FirstCharacter>;\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n#line 1 \"string/kmp.hpp\"\n\n\n\n#line 5\
    \ \"string/kmp.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n// Returns the\
    \ KMP prefix function.\ntemplate <class Sequence>\nstd::vector<int> prefix_function(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    std::vector<int>\
    \ prefix(n);\n    for (int i = 1; i < n; i++) {\n        int j = prefix[i - 1];\n\
    \        while (j > 0 && sequence[i] != sequence[j]) {\n            j = prefix[j\
    \ - 1];\n        }\n        if (sequence[i] == sequence[j]) j++;\n        prefix[i]\
    \ = j;\n    }\n    return prefix;\n}\n\n// Returns every starting position where\
    \ pattern occurs in text.\n// An empty pattern occurs at every position from 0\
    \ through text.size().\ntemplate <class Text, class Pattern>\nstd::vector<int>\
    \ kmp_search(const Text& text, const Pattern& pattern) {\n    int n = int(text.size());\n\
    \    int m = int(pattern.size());\n    if (m == 0) {\n        std::vector<int>\
    \ occurrences(n + 1);\n        for (int i = 0; i <= n; i++) occurrences[i] = i;\n\
    \        return occurrences;\n    }\n\n    std::vector<int> prefix = prefix_function(pattern);\n\
    \    std::vector<int> occurrences;\n    int matched = 0;\n    for (int i = 0;\
    \ i < n; i++) {\n        while (matched > 0 && text[i] != pattern[matched]) {\n\
    \            matched = prefix[matched - 1];\n        }\n        if (text[i] ==\
    \ pattern[matched]) matched++;\n        if (matched == m) {\n            occurrences.push_back(i\
    \ - m + 1);\n            matched = prefix[matched - 1];\n        }\n    }\n  \
    \  return occurrences;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\
    \n#line 1 \"string/levenshtein_distance.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 7 \"string/levenshtein_distance.hpp\"\n\nnamespace m1une {\nnamespace string\
    \ {\n\nnamespace levenshtein_distance_detail {\n\ntemplate <class RowSequence,\
    \ class ColumnSequence>\nint solve(const RowSequence& rows, const ColumnSequence&\
    \ columns) {\n    int row_count = int(rows.size());\n    int column_count = int(columns.size());\n\
    \    std::vector<int> distance(column_count + 1);\n    for (int column = 0; column\
    \ <= column_count; column++) distance[column] = column;\n\n    for (int row =\
    \ 1; row <= row_count; row++) {\n        int diagonal = distance[0];\n       \
    \ distance[0] = row;\n        for (int column = 1; column <= column_count; column++)\
    \ {\n            int above = distance[column];\n            int substitution =\
    \ diagonal + (rows[row - 1] == columns[column - 1] ? 0 : 1);\n            distance[column]\
    \ =\n                std::min({above + 1, distance[column - 1] + 1, substitution});\n\
    \            diagonal = above;\n        }\n    }\n    return distance[column_count];\n\
    }\n\ntemplate <class RowSequence, class ColumnSequence>\nint solve_bounded(const\
    \ RowSequence& rows, const ColumnSequence& columns,\n                  int max_distance)\
    \ {\n    int row_count = int(rows.size());\n    int column_count = int(columns.size());\n\
    \    assert(column_count <= row_count);\n    if (row_count - column_count > max_distance)\
    \ return max_distance + 1;\n    if (max_distance >= row_count) return solve(rows,\
    \ columns);\n\n    int infinity = max_distance + 1;\n    int previous_left = 0;\n\
    \    int previous_right = std::min(column_count, max_distance);\n    std::vector<int>\
    \ previous(previous_right + 1);\n    for (int column = 0; column <= previous_right;\
    \ column++) previous[column] = column;\n    std::vector<int> current;\n\n    for\
    \ (int row = 1; row <= row_count; row++) {\n        int current_left = std::max(0,\
    \ row - max_distance);\n        int current_right = int(std::min<long long>(column_count,\n\
    \                                                    static_cast<long long>(row)\
    \ + max_distance));\n        current.assign(current_right - current_left + 1,\
    \ infinity);\n\n        for (int column = current_left; column <= current_right;\
    \ column++) {\n            int best = infinity;\n            if (previous_left\
    \ <= column && column <= previous_right) {\n                best = std::min(best,\
    \ previous[column - previous_left] + 1);\n            }\n            if (current_left\
    \ < column) {\n                best = std::min(best, current[column - current_left\
    \ - 1] + 1);\n            }\n            if (0 < column && previous_left <= column\
    \ - 1 && column - 1 <= previous_right) {\n                int substitution = previous[column\
    \ - 1 - previous_left] +\n                                   (rows[row - 1] ==\
    \ columns[column - 1] ? 0 : 1);\n                best = std::min(best, substitution);\n\
    \            }\n            current[column - current_left] = std::min(best, infinity);\n\
    \        }\n\n        previous.swap(current);\n        previous_left = current_left;\n\
    \        previous_right = current_right;\n    }\n    return previous[column_count\
    \ - previous_left];\n}\n\n}  // namespace levenshtein_distance_detail\n\n// Returns\
    \ the minimum number of insertions, deletions, and substitutions\n// needed to\
    \ transform first into second.\ntemplate <class Sequence1, class Sequence2>\n\
    int levenshtein_distance(const Sequence1& first, const Sequence2& second) {\n\
    \    if (first.size() < second.size()) {\n        return levenshtein_distance_detail::solve(second,\
    \ first);\n    }\n    return levenshtein_distance_detail::solve(first, second);\n\
    }\n\n// Returns the exact distance when it is at most max_distance, and\n// max_distance\
    \ + 1 otherwise.\ntemplate <class Sequence1, class Sequence2>\nint levenshtein_distance(const\
    \ Sequence1& first, const Sequence2& second,\n                         int max_distance)\
    \ {\n    assert(0 <= max_distance);\n    if (first.size() < second.size()) {\n\
    \        return levenshtein_distance_detail::solve_bounded(second, first, max_distance);\n\
    \    }\n    return levenshtein_distance_detail::solve_bounded(first, second, max_distance);\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/longest_common_extension.hpp\"\
    \n\n\n\n#line 6 \"string/longest_common_extension.hpp\"\n#include <string>\n#line\
    \ 9 \"string/longest_common_extension.hpp\"\n\n#line 1 \"string/suffix_array.hpp\"\
    \n\n\n\n#line 6 \"string/suffix_array.hpp\"\n#include <numeric>\n#line 8 \"string/suffix_array.hpp\"\
    \n#include <type_traits>\n#line 10 \"string/suffix_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace string {\nnamespace detail {\n\ntemplate <class Sequence>\nstd::vector<int>\
    \ suffix_array_impl(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    if (n == 0) return {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
    \    std::vector<Value> sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(),\
    \ sorted.end());\n    sorted.erase(std::unique(sorted.begin(), sorted.end()),\
    \ sorted.end());\n\n    int length = n + 1;\n    std::vector<int> order(length);\n\
    \    std::vector<int> rank(length);\n    std::vector<int> key(length);\n    key[n]\
    \ = 0;\n    for (int i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
    \ sorted.end(), sequence[i]) - sorted.begin()) + 1;\n    }\n\n    int alphabet\
    \ = int(sorted.size()) + 1;\n    std::vector<int> count(std::max(length, alphabet),\
    \ 0);\n    for (int value : key) count[value]++;\n    for (int i = 1; i < alphabet;\
    \ i++) count[i] += count[i - 1];\n    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]]\
    \ = i;\n\n    int classes = 1;\n    rank[order[0]] = 0;\n    for (int i = 1; i\
    \ < length; i++) {\n        if (key[order[i - 1]] != key[order[i]]) classes++;\n\
    \        rank[order[i]] = classes - 1;\n    }\n\n    std::vector<int> shifted(length);\n\
    \    std::vector<int> next_rank(length);\n    for (long long half = 1; half <\
    \ length; half <<= 1) {\n        for (int i = 0; i < length; i++) {\n        \
    \    long long position = order[i] - half;\n            if (position < 0) position\
    \ += length;\n            shifted[i] = int(position);\n        }\n\n        count.assign(classes,\
    \ 0);\n        for (int position : shifted) count[rank[position]]++;\n       \
    \ for (int i = 1; i < classes; i++) count[i] += count[i - 1];\n        for (int\
    \ i = length - 1; i >= 0; i--) {\n            int position = shifted[i];\n   \
    \         order[--count[rank[position]]] = position;\n        }\n\n        int\
    \ next_classes = 1;\n        next_rank[order[0]] = 0;\n        for (int i = 1;\
    \ i < length; i++) {\n            int current = order[i];\n            int previous\
    \ = order[i - 1];\n            int current_second = int((current + half) % length);\n\
    \            int previous_second = int((previous + half) % length);\n        \
    \    if (\n                rank[current] != rank[previous] ||\n              \
    \  rank[current_second] != rank[previous_second]\n            ) {\n          \
    \      next_classes++;\n            }\n            next_rank[current] = next_classes\
    \ - 1;\n        }\n        rank.swap(next_rank);\n        classes = next_classes;\n\
    \        if (classes == length) break;\n    }\n\n    std::vector<int> suffixes(n);\n\
    \    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];\n    return suffixes;\n\
    }\n\n}  // namespace detail\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array(const\
    \ Sequence& sequence) {\n    return detail::suffix_array_impl(sequence);\n}\n\n\
    inline std::vector<int> suffix_array(const std::string& text) {\n    std::vector<unsigned\
    \ char> values;\n    values.reserve(text.size());\n    for (unsigned char character\
    \ : text) values.push_back(character);\n    return detail::suffix_array_impl(values);\n\
    }\n\ntemplate <class Sequence>\nstd::vector<int> lcp_array(const Sequence& sequence,\
    \ const std::vector<int>& suffixes) {\n    int n = int(sequence.size());\n   \
    \ assert(int(suffixes.size()) == n);\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ rank(n);\n    for (int i = 0; i < n; i++) {\n        assert(0 <= suffixes[i]\
    \ && suffixes[i] < n);\n        rank[suffixes[i]] = i;\n    }\n\n    std::vector<int>\
    \ lcp(n - 1);\n    int common = 0;\n    for (int i = 0; i < n; i++) {\n      \
    \  int position = rank[i];\n        if (position == n - 1) {\n            common\
    \ = 0;\n            continue;\n        }\n        int j = suffixes[position +\
    \ 1];\n        while (\n            i + common < n &&\n            j + common\
    \ < n &&\n            sequence[i + common] == sequence[j + common]\n        )\
    \ {\n            common++;\n        }\n        lcp[position] = common;\n     \
    \   if (common > 0) common--;\n    }\n    return lcp;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 11 \"string/longest_common_extension.hpp\"\n\n\
    namespace m1une {\nnamespace string {\n\ntemplate <class Sequence = std::string>\n\
    struct LongestCommonExtension {\n   private:\n    Sequence _sequence;\n    std::vector<int>\
    \ _suffix_array;\n    std::vector<int> _rank;\n    std::vector<int> _lcp;\n  \
    \  std::vector<int> _log;\n    std::vector<std::vector<int>> _table;\n\n    int\
    \ range_min(int left, int right) const {\n        assert(0 <= left && left < right\
    \ && right <= int(_lcp.size()));\n        int k = _log[right - left];\n      \
    \  return std::min(_table[k][left], _table[k][right - (1 << k)]);\n    }\n\n \
    \   void build() {\n        int n = int(_sequence.size());\n        _suffix_array\
    \ = m1une::string::suffix_array(_sequence);\n        _rank.assign(n, 0);\n   \
    \     for (int i = 0; i < n; i++) {\n            _rank[_suffix_array[i]] = i;\n\
    \        }\n\n        _lcp = m1une::string::lcp_array(_sequence, _suffix_array);\n\
    \        int m = int(_lcp.size());\n        _log.assign(m + 1, 0);\n        for\
    \ (int i = 2; i <= m; i++) {\n            _log[i] = _log[i >> 1] + 1;\n      \
    \  }\n\n        _table.clear();\n        if (m == 0) return;\n        _table.assign(_log[m]\
    \ + 1, std::vector<int>());\n        _table[0] = _lcp;\n        for (int k = 1;\
    \ k < int(_table.size()); k++) {\n            int width = 1 << k;\n          \
    \  int half = width >> 1;\n            _table[k].resize(m - width + 1);\n    \
    \        for (int i = 0; i + width <= m; i++) {\n                _table[k][i]\
    \ = std::min(_table[k - 1][i], _table[k - 1][i + half]);\n            }\n    \
    \    }\n    }\n\n   public:\n    LongestCommonExtension() = default;\n\n    explicit\
    \ LongestCommonExtension(const Sequence& sequence) : _sequence(sequence) {\n \
    \       build();\n    }\n\n    explicit LongestCommonExtension(Sequence&& sequence)\
    \ : _sequence(std::move(sequence)) {\n        build();\n    }\n\n    int size()\
    \ const {\n        return int(_sequence.size());\n    }\n\n    bool empty() const\
    \ {\n        return _sequence.empty();\n    }\n\n    const Sequence& sequence()\
    \ const {\n        return _sequence;\n    }\n\n    const std::vector<int>& suffix_array()\
    \ const {\n        return _suffix_array;\n    }\n\n    const std::vector<int>&\
    \ rank() const {\n        return _rank;\n    }\n\n    const std::vector<int>&\
    \ lcp_array() const {\n        return _lcp;\n    }\n\n    int longest_common_extension(int\
    \ i, int j) const {\n        int n = size();\n        assert(0 <= i && i <= n);\n\
    \        assert(0 <= j && j <= n);\n        if (i == j) return n - i;\n      \
    \  if (i == n || j == n) return 0;\n\n        int left = _rank[i];\n        int\
    \ right = _rank[j];\n        if (left > right) std::swap(left, right);\n     \
    \   return range_min(left, right);\n    }\n\n    int longest_common_extension(int\
    \ i, int j, int limit) const {\n        assert(0 <= limit);\n        return std::min(longest_common_extension(i,\
    \ j), limit);\n    }\n\n    int lcp(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int operator()(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int compare_suffix(int i, int j) const {\n        int n =\
    \ size();\n        assert(0 <= i && i <= n);\n        assert(0 <= j && j <= n);\n\
    \        if (i == j) return 0;\n        int common = longest_common_extension(i,\
    \ j);\n        if (i + common == n && j + common == n) return 0;\n        if (i\
    \ + common == n) return -1;\n        if (j + common == n) return 1;\n        return\
    \ _sequence[i + common] < _sequence[j + common] ? -1 : 1;\n    }\n\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int n = size();\n        assert(0\
    \ <= l1 && l1 <= r1 && r1 <= n);\n        assert(0 <= l2 && l2 <= r2 && r2 <=\
    \ n);\n        int len1 = r1 - l1;\n        int len2 = r2 - l2;\n        int common\
    \ = longest_common_extension(l1, l2, std::min(len1, len2));\n        if (common\
    \ == len1 && common == len2) return 0;\n        if (common == len1) return -1;\n\
    \        if (common == len2) return 1;\n        return _sequence[l1 + common]\
    \ < _sequence[l2 + common] ? -1 : 1;\n    }\n};\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n\n#line 1 \"string/longest_common_subsequence.hpp\"\n\n\
    \n\n#line 9 \"string/longest_common_subsequence.hpp\"\n\nnamespace m1une {\nnamespace\
    \ string {\n\nstruct LongestCommonSubsequence {\n    std::vector<std::pair<int,\
    \ int>> matches;\n\n    int length() const {\n        return int(matches.size());\n\
    \    }\n\n    bool empty() const {\n        return matches.empty();\n    }\n\n\
    \    std::vector<int> first_indices() const {\n        std::vector<int> result;\n\
    \        result.reserve(matches.size());\n        for (auto [i, j] : matches)\
    \ {\n            (void)j;\n            result.push_back(i);\n        }\n     \
    \   return result;\n    }\n\n    std::vector<int> second_indices() const {\n \
    \       std::vector<int> result;\n        result.reserve(matches.size());\n  \
    \      for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(j);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_first(const Sequence& first) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(first[i]);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_second(const Sequence& second) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(second[j]);\n\
    \        }\n        return result;\n    }\n};\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nint longest_common_subsequence_length(const FirstSequence&\
    \ first, const SecondSequence& second) {\n    int n = int(first.size());\n   \
    \ int m = int(second.size());\n    if (m <= n) {\n        std::vector<int> dp(m\
    \ + 1, 0);\n        for (int i = 0; i < n; i++) {\n            int diagonal =\
    \ 0;\n            for (int j = 0; j < m; j++) {\n                int up = dp[j\
    \ + 1];\n                if (first[i] == second[j]) {\n                    dp[j\
    \ + 1] = diagonal + 1;\n                } else {\n                    dp[j + 1]\
    \ = std::max(dp[j + 1], dp[j]);\n                }\n                diagonal =\
    \ up;\n            }\n        }\n        return dp[m];\n    } else {\n       \
    \ std::vector<int> dp(n + 1, 0);\n        for (int j = 0; j < m; j++) {\n    \
    \        int diagonal = 0;\n            for (int i = 0; i < n; i++) {\n      \
    \          int up = dp[i + 1];\n                if (first[i] == second[j]) {\n\
    \                    dp[i + 1] = diagonal + 1;\n                } else {\n   \
    \                 dp[i + 1] = std::max(dp[i + 1], dp[i]);\n                }\n\
    \                diagonal = up;\n            }\n        }\n        return dp[n];\n\
    \    }\n}\n\ntemplate <class FirstSequence, class SecondSequence>\nLongestCommonSubsequence\
    \ longest_common_subsequence(\n    const FirstSequence& first,\n    const SecondSequence&\
    \ second\n) {\n    int n = int(first.size());\n    int m = int(second.size());\n\
    \    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));\n  \
    \  for (int i = 0; i < n; i++) {\n        for (int j = 0; j < m; j++) {\n    \
    \        if (first[i] == second[j]) {\n                dp[i + 1][j + 1] = dp[i][j]\
    \ + 1;\n            } else {\n                dp[i + 1][j + 1] = std::max(dp[i][j\
    \ + 1], dp[i + 1][j]);\n            }\n        }\n    }\n\n    LongestCommonSubsequence\
    \ result;\n    result.matches.reserve(dp[n][m]);\n    int i = n;\n    int j =\
    \ m;\n    while (i > 0 && j > 0) {\n        if (first[i - 1] == second[j - 1])\
    \ {\n            result.matches.emplace_back(i - 1, j - 1);\n            i--;\n\
    \            j--;\n        } else if (dp[i - 1][j] >= dp[i][j - 1]) {\n      \
    \      i--;\n        } else {\n            j--;\n        }\n    }\n    std::reverse(result.matches.begin(),\
    \ result.matches.end());\n    return result;\n}\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n\n#line 1 \"string/longest_common_substring.hpp\"\n\n\n\
    \n#line 9 \"string/longest_common_substring.hpp\"\n\n#line 11 \"string/longest_common_substring.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\nstruct LongestCommonSubstring {\n\
    \    int first_left = 0;\n    int first_right = 0;\n    int second_left = 0;\n\
    \    int second_right = 0;\n\n    int length() const {\n        assert(first_right\
    \ - first_left == second_right - second_left);\n        return first_right - first_left;\n\
    \    }\n\n    bool empty() const {\n        return length() == 0;\n    }\n\n \
    \   std::pair<int, int> first_interval() const {\n        return {first_left,\
    \ first_right};\n    }\n\n    std::pair<int, int> second_interval() const {\n\
    \        return {second_left, second_right};\n    }\n};\n\nnamespace detail {\n\
    \ntemplate <class Sequence>\nstd::vector<int> compressed_join_with_separator(const\
    \ Sequence& first, const Sequence& second) {\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(first[0])>>;\n\
    \n    std::vector<Value> values;\n    values.reserve(first.size() + second.size());\n\
    \    for (const auto& value : first) values.push_back(value);\n    for (const\
    \ auto& value : second) values.push_back(value);\n    std::sort(values.begin(),\
    \ values.end());\n    values.erase(std::unique(values.begin(), values.end()),\
    \ values.end());\n\n    std::vector<int> joined;\n    joined.reserve(first.size()\
    \ + second.size() + 1);\n    for (const auto& value : first) {\n        joined.push_back(int(std::lower_bound(values.begin(),\
    \ values.end(), value) - values.begin()) + 2);\n    }\n    joined.push_back(1);\n\
    \    for (const auto& value : second) {\n        joined.push_back(int(std::lower_bound(values.begin(),\
    \ values.end(), value) - values.begin()) + 2);\n    }\n    return joined;\n}\n\
    \n}  // namespace detail\n\ntemplate <class Sequence>\nLongestCommonSubstring\
    \ longest_common_substring(const Sequence& first, const Sequence& second) {\n\
    \    int n = int(first.size());\n    int m = int(second.size());\n    std::vector<int>\
    \ joined = detail::compressed_join_with_separator(first, second);\n    std::vector<int>\
    \ suffixes = suffix_array(joined);\n    std::vector<int> lcp = lcp_array(joined,\
    \ suffixes);\n\n    LongestCommonSubstring result;\n    for (int i = 0; i + 1\
    \ < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n        int b\
    \ = suffixes[i + 1];\n        if (a == n || b == n) continue;\n\n        bool\
    \ a_first = a < n;\n        bool b_first = b < n;\n        if (a_first == b_first)\
    \ continue;\n\n        int first_left = a_first ? a : b;\n        int second_left\
    \ = a_first ? b - n - 1 : a - n - 1;\n        int length = lcp[i];\n        length\
    \ = std::min(length, n - first_left);\n        length = std::min(length, m - second_left);\n\
    \        if (length > result.length()) {\n            result.first_left = first_left;\n\
    \            result.first_right = first_left + length;\n            result.second_left\
    \ = second_left;\n            result.second_right = second_left + length;\n  \
    \      }\n    }\n    return result;\n}\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n\n#line 1 \"string/lyndon_factorization.hpp\"\n\n\n\n#line 6 \"string/lyndon_factorization.hpp\"\
    \n\n#line 1 \"string/minimum_rotation.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ string {\n\n// Returns the smallest starting index of a lexicographically minimum\
    \ cyclic shift.\ntemplate <class Sequence>\nint minimum_cyclic_shift(const Sequence&\
    \ sequence) {\n    const int size = int(sequence.size());\n    if (size == 0)\
    \ return 0;\n\n    auto less = [&](int left, int right) {\n        return sequence[left\
    \ < size ? left : left - size] <\n               sequence[right < size ? right\
    \ : right - size];\n    };\n\n    int answer = 0;\n    int start = 0;\n    while\
    \ (start < size) {\n        answer = start;\n        int scan = start + 1;\n \
    \       int matched = start;\n        while (scan < 2 * size && !less(scan, matched))\
    \ {\n            if (less(matched, scan)) {\n                matched = start;\n\
    \            } else {\n                matched++;\n            }\n           \
    \ scan++;\n        }\n\n        const int period = scan - matched;\n        while\
    \ (start <= matched) start += period;\n    }\n    return answer;\n}\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n#line 8 \"string/lyndon_factorization.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\n// Returns boundaries 0 = a[0] <\
    \ a[1] < ... < a[k] = sequence.size()\n// of the Lyndon factorization.\ntemplate\
    \ <class Sequence>\nstd::vector<int> lyndon_factor_boundaries(const Sequence&\
    \ sequence) {\n    int n = int(sequence.size());\n    std::vector<int> boundaries;\n\
    \    boundaries.push_back(0);\n\n    int i = 0;\n    while (i < n) {\n       \
    \ int j = i + 1;\n        int k = i;\n        while (j < n && !(sequence[j] <\
    \ sequence[k])) {\n            if (sequence[k] < sequence[j]) {\n            \
    \    k = i;\n            } else {\n                k++;\n            }\n     \
    \       j++;\n        }\n\n        int length = j - k;\n        while (i <= k)\
    \ {\n            i += length;\n            boundaries.push_back(i);\n        }\n\
    \    }\n    return boundaries;\n}\n\n// Returns half-open intervals [left, right)\
    \ of the Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const Sequence& sequence) {\n    std::vector<int>\
    \ boundaries = lyndon_factor_boundaries(sequence);\n    std::vector<std::pair<int,\
    \ int>> factors;\n    factors.reserve(boundaries.size() - 1);\n    for (int i\
    \ = 0; i + 1 < int(boundaries.size()); i++) {\n        factors.emplace_back(boundaries[i],\
    \ boundaries[i + 1]);\n    }\n    return factors;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 1 \"string/manacher.hpp\"\n\n\n\n#line 7 \"string/manacher.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\nstruct ManacherResult {\n    // odd[i]\
    \ is the radius including center i.\n    // The palindrome is [i - odd[i] + 1,\
    \ i + odd[i]).\n    std::vector<int> odd;\n\n    // even[i] is the radius centered\
    \ between i - 1 and i.\n    // The palindrome is [i - even[i], i + even[i]).\n\
    \    std::vector<int> even;\n\n    int size() const {\n        return int(odd.size());\n\
    \    }\n\n    bool empty() const {\n        return odd.empty();\n    }\n\n   \
    \ bool is_palindrome(int left, int right) const {\n        int n = size();\n \
    \       assert(0 <= left && left <= right && right <= n);\n        int length\
    \ = right - left;\n        if (length == 0) return true;\n        if (length &\
    \ 1) {\n            int center = (left + right) / 2;\n            return length\
    \ / 2 + 1 <= odd[center];\n        }\n        int center = (left + right) / 2;\n\
    \        return length / 2 <= even[center];\n    }\n\n    int longest_length()\
    \ const {\n        int result = 0;\n        for (int radius : odd) result = std::max(result,\
    \ 2 * radius - 1);\n        for (int radius : even) result = std::max(result,\
    \ 2 * radius);\n        return result;\n    }\n};\n\ntemplate <class Sequence>\n\
    ManacherResult manacher(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    ManacherResult result;\n    result.odd.assign(n, 0);\n    result.even.assign(n,\
    \ 0);\n\n    int left = 0;\n    int right = -1;\n    for (int i = 0; i < n; i++)\
    \ {\n        int radius = i > right ? 1 : std::min(result.odd[left + right - i],\
    \ right - i + 1);\n        while (\n            0 <= i - radius &&\n         \
    \   i + radius < n &&\n            sequence[i - radius] == sequence[i + radius]\n\
    \        ) {\n            radius++;\n        }\n        result.odd[i] = radius;\n\
    \        if (right < i + radius - 1) {\n            left = i - radius + 1;\n \
    \           right = i + radius - 1;\n        }\n    }\n\n    left = 0;\n    right\
    \ = -1;\n    for (int i = 0; i < n; i++) {\n        int radius = i > right ? 0\
    \ : std::min(result.even[left + right - i + 1], right - i + 1);\n        while\
    \ (\n            0 <= i - radius - 1 &&\n            i + radius < n &&\n     \
    \       sequence[i - radius - 1] == sequence[i + radius]\n        ) {\n      \
    \      radius++;\n        }\n        result.even[i] = radius;\n        if (right\
    \ < i + radius - 1) {\n            left = i - radius;\n            right = i +\
    \ radius - 1;\n        }\n    }\n    return result;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 1 \"string/rolling_hash.hpp\"\n\n\n\n#line 8\
    \ \"string/rolling_hash.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n// Standard\
    \ Rolling Hash for static strings.\n// Precomputes hashes to answer substring\
    \ queries in O(1).\n// Provides advanced operations like LCP, lexicographical\
    \ comparison, and string repetition in O(log N).\ntemplate <long long Base = 10007,\
    \ long long Mod = (1LL << 61) - 1>\nstruct RollingHash {\n    std::string s;\n\
    \    std::vector<long long> hash;\n    std::vector<long long> power;\n\n    RollingHash()\
    \ = default;\n\n    // Constructs the rolling hash table for the given string.\n\
    \    explicit RollingHash(const std::string& str) : s(str) {\n        int n =\
    \ s.size();\n        hash.assign(n + 1, 0);\n        power.assign(n + 1, 1);\n\
    \        for (int i = 0; i < n; ++i) {\n            // Use __int128_t to prevent\
    \ overflow during multiplication\n            hash[i + 1] = (static_cast<__int128_t>(hash[i])\
    \ * Base + s[i]) % Mod;\n            power[i + 1] = (static_cast<__int128_t>(power[i])\
    \ * Base) % Mod;\n        }\n    }\n\n    // Returns the hash of the substring\
    \ S[l..r) in O(1).\n    long long get(int l, int r) const {\n        long long\
    \ res = hash[r] - (static_cast<__int128_t>(hash[l]) * power[r - l]) % Mod;\n \
    \       if (res < 0) res += Mod;\n        return res;\n    }\n\n    // Returns\
    \ the hash of the concatenated substrings S[l1..r1) and S[l2..r2).\n    long long\
    \ concat(int l1, int r1, int l2, int r2) const {\n        long long h1 = get(l1,\
    \ r1);\n        long long h2 = get(l2, r2);\n        return combine(h1, h2, power[r2\
    \ - l2]);\n    }\n\n    // Calculates the Longest Common Prefix (LCP) length of\
    \ S[l1..r1) and S[l2..r2) in O(log N).\n    int lcp(int l1, int r1, int l2, int\
    \ r2) const {\n        int len = std::min(r1 - l1, r2 - l2);\n        int low\
    \ = 0, high = len + 1;\n        while (high - low > 1) {\n            int mid\
    \ = low + (high - low) / 2;\n            if (get(l1, l1 + mid) == get(l2, l2 +\
    \ mid)) {\n                low = mid;\n            } else {\n                high\
    \ = mid;\n            }\n        }\n        return low;\n    }\n\n    // Lexicographically\
    \ compares S[l1..r1) and S[l2..r2) in O(log N).\n    // Returns -1 if S[l1..r1)\
    \ < S[l2..r2), 0 if equal, and 1 if S[l1..r1) > S[l2..r2).\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int l = lcp(l1, r1, l2, r2);\n\
    \        bool end1 = (l1 + l == r1);\n        bool end2 = (l2 + l == r2);\n  \
    \      if (end1 && end2) return 0;\n        if (end1) return -1;\n        if (end2)\
    \ return 1;\n        return s[l1 + l] < s[l2 + l] ? -1 : 1;\n    }\n\n    // Returns\
    \ the hash of the substring S[l..r) repeated 'k' times.\n    long long repeat(int\
    \ l, int r, long long k) const {\n        long long h = get(l, r);\n        long\
    \ long p = power[r - l];\n        return repeat_hash(h, p, k);\n    }\n\n    //\
    \ --- Static Helpers for dynamic processing and Monoid integration ---\n\n   \
    \ // Computes the hash of a single string in O(N) time and O(1) space.\n    static\
    \ long long compute_hash(const std::string& str) {\n        long long h = 0;\n\
    \        for (char c : str) {\n            h = (static_cast<__int128_t>(h) * Base\
    \ + c) % Mod;\n        }\n        return h;\n    }\n\n    // Combines two hashes.\
    \ Equivalent to concatenating string 'b' to the right of string 'a'.\n    static\
    \ constexpr long long combine(long long h1, long long h2, long long base_power2)\
    \ {\n        return (static_cast<__int128_t>(h1) * base_power2 + h2) % Mod;\n\
    \    }\n\n    // Returns the hash of a string (with hash 'h' and base_power 'p')\
    \ repeated 'k' times.\n    static constexpr long long repeat_hash(long long h,\
    \ long long p, long long k) {\n        long long res_h = 0;\n        long long\
    \ res_p = 1;\n        long long cur_h = h;\n        long long cur_p = p;\n   \
    \     while (k > 0) {\n            if (k & 1) {\n                res_h = combine(res_h,\
    \ cur_h, cur_p);\n                res_p = (static_cast<__int128_t>(res_p) * cur_p)\
    \ % Mod;\n            }\n            cur_h = combine(cur_h, cur_h, cur_p);\n \
    \           cur_p = (static_cast<__int128_t>(cur_p) * cur_p) % Mod;\n        \
    \    k >>= 1;\n        }\n        return res_h;\n    }\n\n    // Creates the state\
    \ pair {hash_value, base_power} for a single character.\n    static constexpr\
    \ std::pair<long long, long long> make_single(long long c) {\n        return {c\
    \ % Mod, Base % Mod};\n    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\
    \n\n#line 1 \"string/runs.hpp\"\n\n\n\n#line 5 \"string/runs.hpp\"\n#include <set>\n\
    #line 8 \"string/runs.hpp\"\n\nnamespace m1une {\nnamespace string {\n\nstruct\
    \ Run {\n    int period;\n    int left;\n    int right;\n\n    bool operator==(const\
    \ Run&) const = default;\n};\n\nnamespace internal {\n\ntemplate <class Sequence>\n\
    class RunEnumerator {\n   private:\n    const Sequence& _sequence;\n    int _size;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _candidates;\n\n    template\
    \ <class Access>\n    static std::vector<int> z_algorithm(int length, Access access)\
    \ {\n        std::vector<int> z(length + 1, 0);\n        if (length == 0) return\
    \ z;\n        z[0] = length;\n        int left = 0;\n        int right = 0;\n\
    \        for (int i = 1; i < length; i++) {\n            if (i < right) z[i] =\
    \ std::min(right - i, z[i - left]);\n            while (\n                i +\
    \ z[i] < length &&\n                access(z[i]) == access(i + z[i])\n       \
    \     ) {\n                z[i]++;\n            }\n            if (right < i +\
    \ z[i]) {\n                left = i;\n                right = i + z[i];\n    \
    \        }\n        }\n        return z;\n    }\n\n    decltype(auto) element(int\
    \ index, bool reversed) const {\n        int original_index = reversed ? _size\
    \ - 1 - index : index;\n        return _sequence[original_index];\n    }\n\n \
    \   void add_candidate(int period, int left, int right, bool reversed) {\n   \
    \     if (reversed) {\n            left = _size - left;\n            right = _size\
    \ - right;\n            std::swap(left, right);\n        }\n        _candidates[period].emplace_back(left,\
    \ right);\n    }\n\n    void collect(int range_left, int range_right, int phase,\
    \ bool reversed) {\n        if (range_right - range_left <= 1) return;\n     \
    \   int middle = (range_left + range_right + phase) / 2;\n        collect(range_left,\
    \ middle, phase, reversed);\n        collect(middle, range_right, phase, reversed);\n\
    \n        int left_length = middle - range_left;\n        int right_length = range_right\
    \ - middle;\n        std::vector<int> left_z = z_algorithm(left_length, [&](int\
    \ index) -> decltype(auto) {\n            return element(middle - 1 - index, reversed);\n\
    \        });\n\n        int combined_length = right_length + range_right - range_left;\n\
    \        std::vector<int> right_z = z_algorithm(combined_length, [&](int index)\
    \ -> decltype(auto) {\n            if (index < right_length) return element(middle\
    \ + index, reversed);\n            return element(range_left + index - right_length,\
    \ reversed);\n        });\n\n        for (int start = middle - 1; start >= range_left;\
    \ start--) {\n            int period = middle - start;\n            int extend_left\
    \ = std::min(start - range_left, left_z[period]);\n            int extend_right\
    \ = std::min(\n                range_right - middle,\n                right_z[range_right\
    \ - range_left - period]\n            );\n            int left = start - extend_left;\n\
    \            int right = middle + extend_right;\n            if (right - left\
    \ >= 2 * period) {\n                add_candidate(period, left, right, reversed);\n\
    \            }\n        }\n    }\n\n   public:\n    explicit RunEnumerator(const\
    \ Sequence& sequence)\n        : _sequence(sequence),\n          _size(int(sequence.size())),\n\
    \          _candidates(_size / 2 + 1) {}\n\n    std::vector<Run> enumerate() {\n\
    \        collect(0, _size, 0, true);\n        collect(0, _size, 1, false);\n\n\
    \        std::set<std::pair<int, int>> used_intervals;\n        std::vector<Run>\
    \ result;\n        for (int period = 1; period <= _size / 2; period++) {\n   \
    \         std::vector<std::pair<int, int>>& candidates = _candidates[period];\n\
    \            std::sort(\n                candidates.begin(),\n               \
    \ candidates.end(),\n                [](const auto& first, const auto& second)\
    \ {\n                    if (first.first != second.first) {\n                \
    \        return first.first < second.first;\n                    }\n         \
    \           return first.second > second.second;\n                }\n        \
    \    );\n\n            int farthest_right = -1;\n            for (const auto&\
    \ interval : candidates) {\n                if (interval.second <= farthest_right)\
    \ continue;\n                farthest_right = interval.second;\n             \
    \   if (!used_intervals.insert(interval).second) continue;\n                result.push_back(Run{period,\
    \ interval.first, interval.second});\n            }\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace internal\n\n// Returns all runs as (minimum\
    \ period, maximal half-open interval),\n// sorted lexicographically by (period,\
    \ left, right).\ntemplate <class Sequence>\nstd::vector<Run> enumerate_runs(const\
    \ Sequence& sequence) {\n    return internal::RunEnumerator<Sequence>(sequence).enumerate();\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/string_hash.hpp\"\
    \n\n\n\n#line 5 \"string/string_hash.hpp\"\n#include <cstdint>\n#line 7 \"string/string_hash.hpp\"\
    \n#include <string_view>\n\nnamespace m1une {\nnamespace string {\n\nstruct StringHash\
    \ {\n    std::uint32_t first;\n    std::uint32_t second;\n    std::uint32_t first_power;\n\
    \    std::uint32_t second_power;\n    std::size_t length;\n\n    friend constexpr\
    \ bool operator==(const StringHash& left, const StringHash& right) {\n       \
    \ return left.length == right.length && left.first == right.first && left.second\
    \ == right.second;\n    }\n};\n\nnamespace string_hash_detail {\n\ninline constexpr\
    \ std::uint64_t first_mod = 1'000'000'007;\ninline constexpr std::uint64_t second_mod\
    \ = 1'000'000'009;\ninline constexpr std::uint64_t base = 911'382'323;\n\n}  //\
    \ namespace string_hash_detail\n\n// Computes a double polynomial hash. Bytes\
    \ are interpreted as unsigned.\nconstexpr StringHash hash_string(std::string_view\
    \ value) {\n    using namespace string_hash_detail;\n    std::uint64_t first =\
    \ 0;\n    std::uint64_t second = 0;\n    std::uint64_t first_power = 1;\n    std::uint64_t\
    \ second_power = 1;\n    for (char character : value) {\n        std::uint64_t\
    \ symbol = static_cast<unsigned char>(character) + std::uint64_t(1);\n       \
    \ first = (first * base + symbol) % first_mod;\n        second = (second * base\
    \ + symbol) % second_mod;\n        first_power = first_power * base % first_mod;\n\
    \        second_power = second_power * base % second_mod;\n    }\n    return StringHash{\n\
    \        static_cast<std::uint32_t>(first),\n        static_cast<std::uint32_t>(second),\n\
    \        static_cast<std::uint32_t>(first_power),\n        static_cast<std::uint32_t>(second_power),\n\
    \        value.size(),\n    };\n}\n\nconstexpr StringHash hash_string(const std::string&\
    \ value) {\n    return hash_string(std::string_view(value));\n}\n\nconstexpr StringHash\
    \ hash_string(const char* value) {\n    return hash_string(std::string_view(value));\n\
    }\n\n// Returns the hash of the concatenation represented by `left` and `right`.\n\
    constexpr StringHash concat_string_hash(const StringHash& left, const StringHash&\
    \ right) {\n    using namespace string_hash_detail;\n    return StringHash{\n\
    \        static_cast<std::uint32_t>((std::uint64_t(left.first) * right.first_power\
    \ + right.first) % first_mod),\n        static_cast<std::uint32_t>((std::uint64_t(left.second)\
    \ * right.second_power + right.second) % second_mod),\n        static_cast<std::uint32_t>(std::uint64_t(left.first_power)\
    \ * right.first_power % first_mod),\n        static_cast<std::uint32_t>(std::uint64_t(left.second_power)\
    \ * right.second_power % second_mod),\n        left.length + right.length,\n \
    \   };\n}\n\n// Hash adapter for std::unordered_map and std::unordered_set.\n\
    struct StringHasher {\n    using is_transparent = void;\n\n    constexpr std::size_t\
    \ operator()(std::string_view value) const {\n        return operator()(hash_string(value));\n\
    \    }\n\n    constexpr std::size_t operator()(const std::string& value) const\
    \ {\n        return operator()(std::string_view(value));\n    }\n\n    constexpr\
    \ std::size_t operator()(const char* value) const {\n        return operator()(std::string_view(value));\n\
    \    }\n\n    constexpr std::size_t operator()(const StringHash& value) const\
    \ {\n        std::uint64_t combined = (std::uint64_t(value.first) << 32) | value.second;\n\
    \        combined ^= std::uint64_t(value.length) + 0x9e3779b97f4a7c15ULL;\n  \
    \      combined ^= combined >> 30;\n        combined *= 0xbf58476d1ce4e5b9ULL;\n\
    \        combined ^= combined >> 27;\n        combined *= 0x94d049bb133111ebULL;\n\
    \        combined ^= combined >> 31;\n        return static_cast<std::size_t>(combined);\n\
    \    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/suffix_automaton.hpp\"\
    \n\n\n\n#line 11 \"string/suffix_automaton.hpp\"\n\nnamespace m1une {\nnamespace\
    \ string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct\
    \ SuffixAutomaton {\n    static_assert(0 < AlphabetSize);\n\n    using state_id\
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
    \ string\n}  // namespace m1une\n\n\n#line 1 \"string/trie.hpp\"\n\n\n\n#line\
    \ 9 \"string/trie.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n// A multiset\
    \ trie for a contiguous character alphabet.\ntemplate <int AlphabetSize = 26,\
    \ int FirstCharacter = 'a'>\nstruct Trie {\n    static_assert(0 < AlphabetSize);\n\
    \n    using node_id = int;\n    static constexpr node_id null_node = -1;\n\n \
    \   struct Node {\n        std::array<node_id, AlphabetSize> child;\n        int\
    \ subtree_count;\n        int terminal_count;\n\n        Node() : subtree_count(0),\
    \ terminal_count(0) {\n            child.fill(null_node);\n        }\n    };\n\
    \n   private:\n    std::vector<Node> _nodes;\n    int _distinct_size;\n\n    template\
    \ <class Symbol>\n    static int symbol_index(const Symbol& symbol) {\n      \
    \  int index = int(symbol) - FirstCharacter;\n        assert(0 <= index && index\
    \ < AlphabetSize);\n        return index;\n    }\n\n    node_id new_node() {\n\
    \        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    template <class Sequence>\n    node_id find_node(const Sequence& sequence)\
    \ const {\n        node_id node = 0;\n        for (const auto& symbol : sequence)\
    \ {\n            node = _nodes[node].child[symbol_index(symbol)];\n          \
    \  if (node == null_node || _nodes[node].subtree_count == 0) {\n             \
    \   return null_node;\n            }\n        }\n        return node;\n    }\n\
    \n   public:\n    Trie() : _nodes(1), _distinct_size(0) {}\n\n    int size() const\
    \ {\n        return _nodes[0].subtree_count;\n    }\n\n    int distinct_size()\
    \ const {\n        return _distinct_size;\n    }\n\n    bool empty() const {\n\
    \        return size() == 0;\n    }\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id\
    \ && std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n\
    \    template <class Sequence>\n    node_id find(const Sequence& sequence) const\
    \ {\n        return find_node(sequence);\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n       \
    \ _distinct_size = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const\
    \ Sequence& sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n\
    \        node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n\
    \        for (const auto& symbol : sequence) {\n            int index = symbol_index(symbol);\n\
    \            node_id child = _nodes[node].child[index];\n            if (child\
    \ == null_node) {\n                child = new_node();\n                _nodes[node].child[index]\
    \ = child;\n            }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored strings beginning with prefix.\n\
    \    template <class Sequence>\n    int prefix_count(const Sequence& prefix) const\
    \ {\n        node_id node = find_node(prefix);\n        return node == null_node\
    \ ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class Sequence>\n\
    \    bool starts_with(const Sequence& prefix) const {\n        return prefix_count(prefix)\
    \ != 0;\n    }\n\n    template <class Sequence>\n    bool erase_one(const Sequence&\
    \ sequence) {\n        node_id terminal = find_node(sequence);\n        if (terminal\
    \ == null_node || _nodes[terminal].terminal_count == 0) {\n            return\
    \ false;\n        }\n\n        int node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        int\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        int node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        node = _nodes[node].child[symbol_index(symbol)];\n            if (node\
    \ == null_node || _nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored string that is a prefix.\n    // Returns -1\
    \ when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/wildcard_pattern_matching.hpp\"\
    \n\n\n\n#line 7 \"string/wildcard_pattern_matching.hpp\"\n\n#line 1 \"math/fps/convolution.hpp\"\
    \n\n\n\n#line 8 \"math/fps/convolution.hpp\"\n#include <cstring>\n#include <new>\n\
    #line 13 \"math/fps/convolution.hpp\"\n\n#if defined(__GNUC__) && !defined(__clang__)\
    \ && (defined(__x86_64__) || defined(__i386__))\n#include <immintrin.h>\n#define\
    \ M1UNE_FPS_HAS_X86_SIMD 1\n#pragma GCC push_options\n#pragma GCC target(\"avx2,bmi\"\
    )\n#endif\n\n#line 1 \"math/fps/internal/ntt998_faster.hpp\"\n\n\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \n#line 9 \"math/fps/internal/ntt998_faster.hpp\"\n\n#include <immintrin.h>\n\n\
    namespace m1une {\nnamespace fps {\nnamespace internal {\nnamespace fast998_v2\
    \ {\n\n// Fixed-modulus AVX2 transform with an in-register degree-8 residue product.\n\
    \nusing u32=unsigned;\nusing u64=unsigned long long;\nusing idt=std::size_t;\n\
    using I256=__m256i;\ninline void store256(void*p,I256 x){\n    _mm256_store_si256((I256*)p,x);\n\
    }\ninline I256 load256(const void*p){\n    return _mm256_load_si256((const I256*)p);\n\
    }\nconstexpr u32 shrk(u32 x,u32 M){\n    return std::min(x,x-M);\n}\nconstexpr\
    \ u32 dilt(u32 x,u32 M){\n    return std::min(x,x+M);\n}\nconstexpr u32 reduce(u64\
    \ x,u32 niv,u32 M){\n    return (x+u64(u32(x)*niv)*M)>>32;\n}\nconstexpr u32 mul(u32\
    \ x,u32 y,u32 niv,u32 M){\n    return reduce(u64(x)*y,niv,M);\n}\nconstexpr u32\
    \ mul_s(u32 x,u32 y,u32 niv,u32 M){\n    return shrk(reduce(u64(x)*y,niv,M),M);\n\
    }\nconstexpr u32 qpw(u32 a,u32 b,u32 niv,u32 M,u32 r){\n    for(;b;b>>=1,a=mul(a,a,niv,M)){\n\
    \        if(b&1){\n            r=mul(r,a,niv,M);\n        }\n    }\n    return\
    \ r;\n}\nconstexpr u32 qpw_s(u32 a,u32 b,u32 niv,u32 M,u32 r){\n    return shrk(qpw(a,b,niv,M,r),M);\n\
    }\ninline I256 shrk32(I256 x,I256 M){\n    return _mm256_min_epu32(x,_mm256_sub_epi32(x,M));\n\
    }\ninline I256 dilt32(I256 x,I256 M){\n    return _mm256_min_epu32(x,_mm256_add_epi32(x,M));\n\
    }\ninline I256 Ladd32(I256 x,I256 y,I256){\n    return _mm256_add_epi32(x,y);\n\
    }\ninline I256 Lsub32(I256 x,I256 y,I256 M){\n    return _mm256_add_epi32(_mm256_sub_epi32(x,y),M);\n\
    }\ninline I256 add32(I256 x,I256 y,I256 M){\n    return shrk32(_mm256_add_epi32(x,y),M);\n\
    }\ninline I256 sub32(I256 x,I256 y,I256 M){\n    return dilt32(_mm256_sub_epi32(x,y),M);\n\
    }\ntemplate<int msk>inline I256 neg32_m(I256 x,I256 M){\n    return _mm256_blend_epi32(x,_mm256_sub_epi32(M,x),msk);\n\
    }\ninline I256 reduce(I256 a,I256 b,I256 niv,I256 M){\n    I256 c=_mm256_mul_epu32(a,niv),d=_mm256_mul_epu32(b,niv);\n\
    \    c=_mm256_mul_epu32(c,M),d=_mm256_mul_epu32(d,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(a,c),32),_mm256_add_epi64(b,d),0xaa);\n\
    }\ninline I256 mul(I256 a,I256 b,I256 niv,I256 M){\n    return reduce(_mm256_mul_epu32(a,b),_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(b,32)),niv,M);\n\
    }\ninline I256 mul_s(I256 a,I256 b,I256 niv,I256 M){\n    return shrk32(mul(a,b,niv,M),M);\n\
    }\ninline I256 mul_bsm(I256 a,I256 b,I256 niv,I256 M){\n    return reduce(_mm256_mul_epu32(a,b),_mm256_mul_epu32(_mm256_srli_epi64(a,32),b),niv,M);\n\
    }\ninline I256 mul_bsmfxd(I256 a,I256 b,I256 bniv,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bniv),dd=_mm256_mul_epu32(_mm256_srli_epi64(a,32),bniv);\n\
    \    I256 c=_mm256_mul_epu32(a,b),d=_mm256_mul_epu32(_mm256_srli_epi64(a,32),b);\n\
    \    cc=_mm256_mul_epu32(cc,M),dd=_mm256_mul_epu32(dd,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),_mm256_add_epi64(d,dd),0xaa);\n\
    }\ninline I256 mul_bfxd(I256 a,I256 b,I256 bniv,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bniv),dd=_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(bniv,32));\n\
    \    I256 c=_mm256_mul_epu32(a,b),d=_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(b,32));\n\
    \    cc=_mm256_mul_epu32(cc,M),dd=_mm256_mul_epu32(dd,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),_mm256_add_epi64(d,dd),0xaa);\n\
    }\ninline I256 mul_upd_rt(I256 a,I256 bu,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bu),c=_mm256_mul_epu32(a,_mm256_srli_epi64(bu,32));\n\
    \    cc=_mm256_mul_epu32(cc,M);\n    return shrk32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),M);\n\
    }\nconstexpr auto _mxlg=26,_lg_itth=6;\nconstexpr auto _itth=idt(1)<<_lg_itth;\n\
    static_assert(_lg_itth%2==0);\nstruct FNTT32_info{\n    u32 mod,mod2,niv,one,r2,r3,img,imgniv,RT1[_mxlg];\n\
    \    alignas(32) std::array<u32,8> rt3[_mxlg-2],rt3i[_mxlg-2],bwbr,bwb,bwbi,rt4[_mxlg-3],rt4niv[_mxlg-3],rt4i[_mxlg-3],rt4iniv[_mxlg-3],pr2,pr4,pr2niv,pr4niv,pr2i,pr2iniv,pr4i,pr4iniv;\n\
    \    constexpr FNTT32_info(const u32 m):mod(m),mod2(m*2),niv([&]{u32 n=2+m;for(int\
    \ i=0;i<4;++i){n*=2+m*n;}return n;}()),one((-m)%m),r2((-u64(m))%m),r3(mul_s(r2,r2,niv,m)),img{},imgniv{},RT1{},rt3{},rt3i{},bwbr{},bwb{},bwbi{},rt4{},rt4niv{},rt4i{},rt4iniv{},pr2{},pr4{},pr2niv{},pr4niv{},pr2i{},pr2iniv{},pr4i{},pr4iniv{}{\n\
    \        const int k=__builtin_ctz(m-1);\n\t\tu32 _g=mul(3,r2,niv,mod);\n    \
    \    for(;;++_g){\n            if(qpw_s(_g,mod>>1,niv,mod,one)!=one){\n      \
    \          break;\n            }\n        }\n\t\t_g=qpw(_g,mod>>k,niv,mod,one);\n\
    \        u32 rt1[_mxlg-1],rt1i[_mxlg-1];\n        rt1[k-2]=_g,rt1i[k-2]=qpw(_g,mod-2,niv,mod,one);\n\
    \        for(int i=k-2;i>0;--i){\n            rt1[i-1]=mul(rt1[i],rt1[i],niv,mod);\n\
    \            rt1i[i-1]=mul(rt1i[i],rt1i[i],niv,mod);\n        }\n        RT1[k-1]=qpw_s(_g,3,niv,mod,one);\n\
    \        for(int i=k-1;i>0;--i){\n\t\t\tRT1[i-1]=mul_s(RT1[i],RT1[i],niv,mod);\n\
    \        }\n        img=rt1[0],imgniv=img*niv;\n        bwbr={one,0,one,0,one};\n\
    \        bwb={rt1[1],0,rt1[0],0,mod-mul_s(rt1[0],rt1[1],niv,mod)};\n        bwbi={rt1i[1],0,rt1i[0],0,mul_s(rt1i[0],rt1i[1],niv,mod)};\n\
    \        u32 pr=one,pri=one;\n        for(int i=0;i<k-2;++i){\n            const\
    \ u32 r=mul_s(pr,rt1[i+1],niv,mod),ri=mul_s(pri,rt1i[i+1],niv,mod);\n        \
    \    const u32 r2=mul_s(r,r,niv,mod),r2i=mul_s(ri,ri,niv,mod);\n            const\
    \ u32 r3=mul_s(r,r2,niv,mod),r3i=mul_s(ri,r2i,niv,mod);\n            rt3[i]={r*niv,r,r2*niv,r2,r3*niv,r3};\n\
    \            rt3i[i]={ri*niv,ri,r2i*niv,r2i,r3i*niv,r3i};\n            pr=mul(pr,rt1i[i+1],niv,mod),pri=mul(pri,rt1[i+1],niv,mod);\n\
    \        }\n        pr=one,pri=one;\n        for(int i=0;i<k-3;++i){\n       \
    \     const u32 r=mul_s(pr,rt1[i+2],niv,mod),ri=mul_s(pri,rt1i[i+2],niv,mod);\n\
    \            rt4[i][0]=rt4i[i][0]=one;\n            for(int j=1;j<8;++j){\n  \
    \              rt4[i][j]=mul_s(rt4[i][j-1],r,niv,mod);\n                rt4i[i][j]=mul_s(rt4i[i][j-1],ri,niv,mod);\n\
    \            }\n            for(int j=0;j<8;++j){\n                rt4niv[i][j]=rt4[i][j]*niv;\n\
    \                rt4iniv[i][j]=rt4i[i][j]*niv;\n            }\n            pr=mul(pr,rt1i[i+2],niv,mod),pri=mul(pri,rt1[i+2],niv,mod);\n\
    \        }\n        pr2={one,one,one,img,one,one,one,img};\n        pr4={one,one,one,one,one,rt1[1],img,mul_s(img,rt1[1],niv,mod)};\n\
    \        const u32 nr2=mod-r2,imgr2=mul_s(img,r2,niv,mod);\n        pr2i={nr2,nr2,nr2,imgr2,nr2,nr2,nr2,imgr2};\n\
    \        pr4i={one,one,one,one,one,rt1i[1],rt1i[0],mul_s(rt1i[0],rt1i[1],niv,mod)};\n\
    \        for(int j=0;j<8;++j){\n            pr2niv[j]=pr2[j]*niv,pr4niv[j]=pr4[j]*niv;\n\
    \            pr2iniv[j]=pr2i[j]*niv,pr4iniv[j]=pr4i[j]*niv;\n        }\n    }\n\
    };\ninline void vector_dif(I256*const f,const idt n,const FNTT32_info*info){\n\
    \    alignas(32) std::array<u32,8> st_1[_mxlg>>1];\n    const I256 Mod=_mm256_set1_epi32(info->mod),Mod2=_mm256_set1_epi32(info->mod2),Niv=_mm256_set1_epi32(info->niv);\n\
    \    const I256 Img=_mm256_set1_epi32(info->img),ImgNiv=_mm256_set1_epi32(info->imgniv),id=_mm256_setr_epi32(0,2,0,4,0,2,0,4);\n\
    \    const int lgn=__builtin_ctzll(n);\n    std::fill(st_1,st_1+(lgn>>1),info->bwb);\n\
    \    const idt nn=n>>(lgn&1),m=std::min(n,_itth),mm=std::min(nn,_itth);\n    //\
    \ I256 rr=_mm256_set1_epi32(info->one);\n    if(nn!=n){\n        for(idt i=0;i<nn;++i){\n\
    \            auto const p0=f+i,p1=f+nn+i;\n            const auto f0=load256(p0),f1=load256(p1);\n\
    \            const auto g0=add32(f0,f1,Mod2),g1=Lsub32(f0,f1,Mod2);\n        \
    \    store256(p0,g0),store256(p1,g1);\n        }\n    }\n    for(idt L=nn>>2;L>0;L>>=2){\n\
    \        for(idt i=0;i<L;++i){\n            auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \            const auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n\
    \            const auto g3=mul_bsmfxd(Lsub32(f1,f3,Mod2),Img,ImgNiv,Mod),g1=add32(f1,f3,Mod2);\n\
    \            const auto g0=add32(f0,f2,Mod2),g2=sub32(f0,f2,Mod2);\n         \
    \   const auto h0=add32(g0,g1,Mod2),h1=Lsub32(g0,g1,Mod2);\n            const\
    \ auto h2=Ladd32(g2,g3,Mod2),h3=Lsub32(g2,g3,Mod2);\n            store256(p0,h0),store256(p1,h1),store256(p2,h2),store256(p3,h3);\n\
    \        }\n    }\n    for(idt j=0;j<n;j+=m){\n        int t=((j==0)?std::min(_lg_itth,lgn):__builtin_ctzll(j))&-2,p=(t-2)>>1;\n\
    \        for(idt L=(idt(1)<<t)>>2;L>=_itth;L>>=2,t-=2,--p){\n            auto\
    \ rt=load256(st_1+p);\n            const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n\
    \            const auto r1Niv=_mm256_permutevar8x32_epi32(_mm256_mul_epu32(rt,Niv),id);\n\
    \            rt=mul_upd_rt(rt,load256(info->rt3+__builtin_ctzll(~j>>t)),Mod);\n\
    \            const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB),nr3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n\
    \            const auto r2Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_BBBB),nr3Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_DDDD);\n\
    \            store256(st_1+p,rt);\n            for(idt i=0;i<L;++i){\n       \
    \         auto const p0=f+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n                const\
    \ auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n        \
    \        const auto g1=mul_bsmfxd(f1,r1,r1Niv,Mod),ng3=mul_bsmfxd(f3,nr3,nr3Niv,Mod);\n\
    \                const auto g2=mul_bsmfxd(f2,r2,r2Niv,Mod),g0=shrk32(f0,Mod2);\n\
    \                const auto h3=mul_bsmfxd(Ladd32(g1,ng3,Mod2),Img,ImgNiv,Mod),h1=sub32(g1,ng3,Mod2);\n\
    \                const auto h0=add32(g0,g2,Mod2),h2=sub32(g0,g2,Mod2);\n     \
    \           const auto u0=Ladd32(h0,h1,Mod2),u1=Lsub32(h0,h1,Mod2);\n        \
    \        const auto u2=Ladd32(h2,h3,Mod2),u3=Lsub32(h2,h3,Mod2);\n           \
    \     store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n     \
    \       }\n        }\n        I256*const g=f+j;\n        for(idt l=mm,L=mm>>2;L;l=L,L>>=2,t-=2,--p){\n\
    \            auto rt=load256(st_1+p);\n            for(idt i=(j==0?l:0),k=(j+i)>>t;i<m;i+=l,++k){\n\
    \                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n         \
    \       const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB);\n              \
    \  const auto nr3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n                for(idt\
    \ j=0;j<L;++j){\n                    auto const p0=g+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                    const auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n\
    \                    const auto g1=mul_bsm(f1,r1,Niv,Mod),ng3=mul_bsm(f3,nr3,Niv,Mod);\n\
    \                    const auto g2=mul_bsm(f2,r2,Niv,Mod),g0=shrk32(f0,Mod2);\n\
    \                    const auto h3=mul_bsmfxd(Ladd32(g1,ng3,Mod2),Img,ImgNiv,Mod),h1=sub32(g1,ng3,Mod2);\n\
    \                    const auto h0=add32(g0,g2,Mod2),h2=sub32(g0,g2,Mod2);\n \
    \                   const auto u0=Ladd32(h0,h1,Mod2),u1=Lsub32(h0,h1,Mod2);\n\
    \                    const auto u2=Ladd32(h2,h3,Mod2),u3=Lsub32(h2,h3,Mod2);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n                rt=mul_upd_rt(rt,load256(info->rt3+__builtin_ctzll(~k)),Mod);\n\
    \            }\n            store256(st_1+p,rt);\n        }\n        // const\
    \ auto pr2=load256(&info->pr2),pr4=load256(&info->pr4);\n        // const auto\
    \ pr2Niv=load256(&info->pr2niv),pr4Niv=load256(&info->pr4niv);\n        // for(idt\
    \ i=j;i<j+m;++i){\n        //     auto fi=load256(f+i);\n        //     fi=mul(fi,rr,Niv,Mod);\n\
    \        //     rr=shrk32(mul_bfxd(rr,load256(info->rt4+__builtin_ctzll(~i)),load256(info->rt4niv+__builtin_ctzll(~i)),Mod),Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xf0>(fi,Mod2),_mm256_permute2x128_si256(fi,fi,1),Mod2),pr4,pr4Niv,Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xcc>(fi,Mod2),_mm256_shuffle_epi32(fi,0x4e),Mod2),pr2,pr2Niv,Mod);\n\
    \        //     fi=sub32(_mm256_shuffle_epi32(fi,0xb1),neg32_m<0x55>(fi,Mod2),Mod2);\n\
    \        //     store256(f+i,fi);\n        // }\n    }\n}\ntemplate<bool shrk=false>inline\
    \ void vector_dit(I256*const f,idt n,const FNTT32_info*const info){\n    alignas(32)\
    \ std::array<u32,8> st_1[_mxlg>>1];\n    const I256 Mod=_mm256_set1_epi32(info->mod),Mod2=_mm256_set1_epi32(info->mod2),Niv=_mm256_set1_epi32(info->niv);\n\
    \    const I256 Img=_mm256_set1_epi32(info->img),ImgNiv=_mm256_set1_epi32(info->imgniv),id=_mm256_setr_epi32(0,2,0,4,0,2,0,4);\n\
    \    const int lgn=__builtin_ctzll(n);\n    std::fill(st_1,st_1+(_lg_itth>>1),info->bwbr);\n\
    \    std::fill(st_1+(_lg_itth>>1),st_1+(_mxlg>>1),info->bwbi);\n    const idt\
    \ nn=n>>(lgn&1),mm=std::min(nn,_itth);\n    // I256 rr=_mm256_set1_epi32((info->mod-1)>>(lgn+3));\n\
    \    for(idt j=0;j<n;j+=mm){\n        // const auto pr2=load256(&info->pr2i),pr4=load256(&info->pr4i);\n\
    \        // const auto pr2Niv=load256(&info->pr2iniv),pr4Niv=load256(&info->pr4iniv);\n\
    \        // for(idt i=j;i<j+mm;++i){\n        //     auto fi=load256(f+i);\n \
    \       //     const auto rt=rr;\n        //     rr=shrk32(mul_bfxd(rr,load256(info->rt4i+__builtin_ctzll(~i)),load256(info->rt4iniv+__builtin_ctzll(~i)),Mod),Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xaa>(fi,Mod2),_mm256_shuffle_epi32(fi,0xb1),Mod2),pr2,pr2Niv,Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xcc>(fi,Mod2),_mm256_shuffle_epi32(fi,0x4e),Mod2),pr4,pr4Niv,Mod);\n\
    \        //     fi=mul(Ladd32(neg32_m<0xf0>(fi,Mod2),_mm256_permute2x128_si256(fi,fi,1),Mod2),rt,Niv,Mod);\n\
    \        //     store256(f+i,fi);\n        // }\n        I256*const g=f+j;\n \
    \       int t=2,p=0;\n        for(idt l=4,L=1;l<=mm;L=l,l<<=2,t+=2,++p){\n   \
    \         auto rt=load256(st_1+p);\n            for(idt i=0,k=j>>t;i<mm;i+=l,++k){\n\
    \                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n         \
    \       const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB);\n              \
    \  const auto r3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n                for(idt\
    \ j=0;j<L;++j){\n                    auto const p0=g+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                    const auto f0=load256(p0),f1=load256(p1),f2=load256(p2),f3=load256(p3);\n\
    \                    const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n \
    \                   const auto g2=add32(f2,f3,Mod2),g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod);\n\
    \                    const auto h0=Ladd32(g0,g2,Mod2),h1=Ladd32(g1,g3,Mod2);\n\
    \                    const auto h2=Lsub32(g0,g2,Mod2),h3=Lsub32(g1,g3,Mod2);\n\
    \                    const auto u0=shrk32(h0,Mod2),u1=mul_bsm(h1,r1,Niv,Mod);\n\
    \                    const auto u2=mul_bsm(h2,r2,Niv,Mod),u3=mul_bsm(h3,r3,Niv,Mod);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n                rt=mul_upd_rt(rt,load256(info->rt3i+__builtin_ctzll(~k)),Mod);\n\
    \            }\n            store256(st_1+p,rt);\n        }\n        int tt=std::min(__builtin_ctzll(~(j>>_lg_itth))+_lg_itth,lgn);\n\
    \        for(idt L=_itth,l=L<<2;t<=tt;L=l,l<<=2,t+=2,++p){\n            if((j+_itth)==l){\n\
    \                if(shrk && l==n){\n                    for(idt i=0;i<L;++i){\n\
    \                        auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n        \
    \                const auto f2=load256(p2),f3=load256(p3),f0=load256(p0),f1=load256(p1);\n\
    \                        const auto g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod),g2=add32(f2,f3,Mod2);\n\
    \                        const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \                        const auto h0=add32(g0,g2,Mod2),h1=add32(g1,g3,Mod2);\n\
    \                        const auto h2=sub32(g0,g2,Mod2),h3=sub32(g1,g3,Mod2);\n\
    \                        const auto u0=shrk32(h0,Mod),u1=shrk32(h1,Mod);\n   \
    \                     const auto u2=shrk32(h2,Mod),u3=shrk32(h3,Mod);\n      \
    \                  store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                    }\n                }\n                else{\n           \
    \         for(idt i=0;i<L;++i){\n                        auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                        const auto f2=load256(p2),f3=load256(p3),f0=load256(p0),f1=load256(p1);\n\
    \                        const auto g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod),g2=add32(f2,f3,Mod2);\n\
    \                        const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \                        const auto h0=add32(g0,g2,Mod2),h1=add32(g1,g3,Mod2);\n\
    \                        const auto h2=sub32(g0,g2,Mod2),h3=sub32(g1,g3,Mod2);\n\
    \                        store256(p0,h0),store256(p1,h1),store256(p2,h2),store256(p3,h3);\n\
    \                    }\n                }\n            }\n            else{\n\
    \                auto rt=load256(st_1+p);\n                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n\
    \                const auto r1Niv=_mm256_permutevar8x32_epi32(_mm256_mul_epu32(rt,Niv),id);\n\
    \                rt=mul_upd_rt(rt,load256(info->rt3i+__builtin_ctzll(~j>>t)),Mod);\n\
    \                const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB),r3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n\
    \                const auto r2Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_BBBB),r3Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_DDDD);\n\
    \                store256(st_1+p,rt);\n                for(idt i=0;i<L;++i){\n\
    \                    auto const p0=f+j+_itth-l+i,p1=p0+L,p2=p1+L,p3=p2+L;\n  \
    \                  const auto f0=load256(p0),f1=load256(p1),f2=load256(p2),f3=load256(p3);\n\
    \                    const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n \
    \                   const auto g2=add32(f2,f3,Mod2),g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod);\n\
    \                    const auto h0=Ladd32(g0,g2,Mod2),h1=Ladd32(g1,g3,Mod2);\n\
    \                    const auto h2=Lsub32(g0,g2,Mod2),h3=Lsub32(g1,g3,Mod2);\n\
    \                    const auto u0=shrk32(h0,Mod2),u1=mul_bsmfxd(h1,r1,r1Niv,Mod);\n\
    \                    const auto u2=mul_bsmfxd(h2,r2,r2Niv,Mod),u3=mul_bsmfxd(h3,r3,r3Niv,Mod);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n            }\n        }\n    }\n    if(shrk && nn==n && n<=_itth){\n\
    \        for(idt i=0;i<n;++i){\n            const auto f0=load256(f+i);\n    \
    \        store256(f+i,shrk32(f0,Mod));\n        }\n    }\n    if(nn!=n){\n   \
    \     for(idt i=0;i<nn;++i){\n            auto const p0=f+i,p1=f+nn+i;\n     \
    \       const auto f0=load256(p0),f1=load256(p1);\n            const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \            if constexpr(shrk){\n                const auto h0=shrk32(g0,Mod),h1=shrk32(g1,Mod);\n\
    \                store256(p0,h0),store256(p1,h1);\n            }\n           \
    \ else{\n                store256(p0,g0),store256(p1,g1);\n            }\n   \
    \     }\n    }\n}\n// Returns fx * f[0,8) * g[0,8) (mod x^8 - ww).\n[[gnu::always_inline]]\
    \ inline I256 convolve8(const I256*f,const I256*g,I256 ww,I256 fx,I256 Niv,I256\
    \ Mod,I256 Mod2){\n    const auto raa=load256(f),rbb=load256(g);\n    const auto\
    \ taa=shrk32(raa,Mod2),bb=shrk32(mul_bsm(rbb,fx,Niv,Mod),Mod);\n    const auto\
    \ aw=shrk32(mul_bsm(taa,ww,Niv,Mod),Mod);\n    const auto aa=shrk32(taa,Mod);\n\
    \    const auto awa=_mm256_permute2x128_si256(aa,aw,3);\n    \n    const auto\
    \ b0=_mm256_permute4x64_epi64(bb,0x00),b1=_mm256_shuffle_epi32(b0,_MM_PERM_CDAB);\n\
    \    const auto a0=aa,a1=_mm256_srli_epi64(a0,32);\n    const auto aw7=_mm256_alignr_epi8(aa,awa,12);\n\
    \    auto res00=_mm256_mul_epu32(a0,b0);\n    auto res01=_mm256_mul_epu32(a1,b0);\n\
    \    auto res10=_mm256_mul_epu32(aw7,b1);\n    auto res11=_mm256_mul_epu32(a0,b1);\n\
    \n    const auto b2=_mm256_permute4x64_epi64(bb,0x55),b3=_mm256_shuffle_epi32(b2,_MM_PERM_CDAB);\n\
    \    const auto aw6=_mm256_alignr_epi8(aa,awa,8);\n    const auto aw5=_mm256_alignr_epi8(aa,awa,4);\n\
    \    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(aw6,b2));\n    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw7,b2));\n\
    \    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw5,b3));\n    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(aw6,b3));\n\
    \n    const auto b4=_mm256_permute4x64_epi64(bb,0xaa),b5=_mm256_shuffle_epi32(b4,_MM_PERM_CDAB);\n\
    \    const auto aw3=_mm256_alignr_epi8(awa,aw,12);\n    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(awa,b4));\n\
    \    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw5,b4));\n    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw3,b5));\n\
    \    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(awa,b5));\n\n    const auto\
    \ b6=_mm256_permute4x64_epi64(bb,0xff),b7=_mm256_shuffle_epi32(b6,_MM_PERM_CDAB);\n\
    \    const auto aw2=_mm256_alignr_epi8(awa,aw,8);\n    const auto aw1=_mm256_alignr_epi8(awa,aw,4);\n\
    \    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(aw2,b6));\n    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw3,b6));\n\
    \    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw1,b7));\n    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(aw2,b7));\n\
    \n    res00=_mm256_add_epi64(res00,res10);\n    res01=_mm256_add_epi64(res01,res11);\n\
    \n    return shrk32(reduce(res00,res01,Niv,Mod),Mod2);\n}\ninline void vector_convolution_direct(I256*f,const\
    \ I256*g,idt lm,const FNTT32_info*const info){\n    u32 RR=info->one;\n    const\
    \ auto mod=info->mod,niv=info->niv;\n    const auto Fx=_mm256_set1_epi32(mul_s((mod-((mod-1)>>(__builtin_ctzll(lm)))),info->r3,niv,mod));\n\
    \    const auto Niv=_mm256_set1_epi32(niv),Mod=_mm256_set1_epi32(mod),Mod2=_mm256_set1_epi32(info->mod2);\n\
    \    for(idt i=0;i<lm;++i){\n        store256(f+i,convolve8(f+i,g+i,_mm256_set1_epi32(RR),Fx,Niv,Mod,Mod2));\n\
    \        RR=mul(RR,info->RT1[__builtin_ctzll(~i)],niv,mod);\n    }\n}\ninline\
    \ void vector_convolution_accumulate(I256*const result,const I256*const f,\n \
    \                                         const I256*const g,idt lm,\n       \
    \                                   const FNTT32_info*const info){\n    u32 RR=info->one;\n\
    \    const auto mod=info->mod,niv=info->niv;\n    const auto Fx=_mm256_set1_epi32(mul_s((mod-((mod-1)>>(__builtin_ctzll(lm)))),info->r3,niv,mod));\n\
    \    const auto Niv=_mm256_set1_epi32(niv),Mod=_mm256_set1_epi32(mod),Mod2=_mm256_set1_epi32(info->mod2);\n\
    \    for(idt i=0;i<lm;++i){\n        const auto product=convolve8(f+i,g+i,_mm256_set1_epi32(RR),Fx,Niv,Mod,Mod2);\n\
    \        store256(result+i,add32(load256(result+i),product,Mod2));\n        RR=mul(RR,info->RT1[__builtin_ctzll(~i)],niv,mod);\n\
    \    }\n}\n\n}  // namespace fast998_v2\n}  // namespace internal\n}  // namespace\
    \ fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_HAS_X86_SIMD\n\n\n#line 22\
    \ \"math/fps/convolution.hpp\"\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n#pragma GCC pop_options\n\
    #endif\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include\
    \ <iostream>\n#line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus,\
    \ \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 27 \"math/fps/convolution.hpp\"\n\nnamespace m1une {\nnamespace fps\
    \ {\n\nnamespace internal {\n\ntemplate <class Mint, class = void>\nstruct has_static_modulus\
    \ : std::false_type {};\n\ntemplate <class Mint>\nstruct has_static_modulus<\n\
    \    Mint, std::void_t<decltype(std::integral_constant<uint32_t, Mint::mod()>{})>>\n\
    \    : std::true_type {};\n\nconstexpr uint32_t primitive_root_constexpr(uint32_t\
    \ mod) {\n    if (mod == 2) return 1;\n    if (mod == 167772161) return 3;\n \
    \   if (mod == 469762049) return 3;\n    if (mod == 754974721) return 11;\n  \
    \  if (mod == 998244353) return 3;\n    if (mod == 1224736769) return 3;\n\n \
    \   uint32_t divisors[32] = {};\n    int count = 0;\n    uint32_t x = mod - 1;\n\
    \    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {\n        if (x % p != 0)\
    \ continue;\n        divisors[count++] = p;\n        while (x % p == 0) x /= p;\n\
    \    }\n    if (x > 1) divisors[count++] = x;\n\n    for (uint32_t g = 2;; g++)\
    \ {\n        bool ok = true;\n        for (int i = 0; i < count; i++) {\n    \
    \        uint64_t value = 1;\n            uint64_t base = g;\n            uint32_t\
    \ exponent = (mod - 1) / divisors[i];\n            while (exponent > 0) {\n  \
    \              if (exponent & 1) value = value * base % mod;\n               \
    \ base = base * base % mod;\n                exponent >>= 1;\n            }\n\
    \            if (value == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\nconstexpr int\
    \ two_adic_order(uint32_t x) {\n    int result = 0;\n    while ((x & 1) == 0)\
    \ {\n        x >>= 1;\n        result++;\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstruct NttRoots {\n    static constexpr int max_base = two_adic_order(Mint::mod()\
    \ - 1);\n    std::array<Mint, max_base + 1> root;\n    std::array<Mint, max_base\
    \ + 1> inverse_root;\n    std::array<Mint, max_base> rate;\n    std::array<Mint,\
    \ max_base> inverse_rate;\n    std::array<Mint, max_base> rate_radix4;\n    std::array<Mint,\
    \ max_base> inverse_rate_radix4;\n\n    NttRoots() {\n        constexpr uint32_t\
    \ primitive_root = primitive_root_constexpr(Mint::mod());\n        for (int level\
    \ = 1; level <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n        Mint product = 1;\n        Mint inverse_product = 1;\n       \
    \ for (int i = 0; i + 1 < max_base; i++) {\n            rate[i] = root[i + 2]\
    \ * product;\n            inverse_rate[i] = inverse_root[i + 2] * inverse_product;\n\
    \            product *= inverse_root[i + 2];\n            inverse_product *= root[i\
    \ + 2];\n        }\n        product = 1;\n        inverse_product = 1;\n     \
    \   for (int i = 0; i + 2 < max_base; i++) {\n            rate_radix4[i] = root[i\
    \ + 3] * product;\n            inverse_rate_radix4[i] = inverse_root[i + 3] *\
    \ inverse_product;\n            product *= inverse_root[i + 3];\n            inverse_product\
    \ *= root[i + 3];\n        }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>&\
    \ ntt_roots() {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\
    \ntemplate <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse, bool normalize\
    \ = true) {\n    const int n = int(a.size());\n    assert(n > 0 && (n & (n - 1))\
    \ == 0);\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n    const auto&\
    \ roots = ntt_roots<Mint>();\n    const int height = two_adic_order(uint32_t(n));\n\
    \    if (!inverse) {\n        int phase = 0;\n        while (phase < height) {\n\
    \            if (height - phase == 1) {\n                const int width = 1 <<\
    \ (height - phase - 1);\n                Mint twiddle = 1;\n                for\
    \ (int block = 0; block < (1 << phase); block++) {\n                    const\
    \ int offset = block << (height - phase);\n                    for (int i = 0;\
    \ i < width; i++) {\n                        const Mint left = a[offset + i];\n\
    \                        const Mint right = a[offset + i + width] * twiddle;\n\
    \                        a[offset + i] = left + right;\n                     \
    \   a[offset + i + width] = left - right;\n                    }\n           \
    \         if (block + 1 != (1 << phase))\n                        twiddle *= roots.rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase++;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase - 2);\n     \
    \       Mint twiddle = 1;\n            const Mint imaginary = roots.root[2];\n\
    \            for (int block = 0; block < (1 << phase); block++) {\n          \
    \      const Mint twiddle2 = twiddle * twiddle;\n                const Mint twiddle3\
    \ = twiddle2 * twiddle;\n                const int offset = block << (height -\
    \ phase);\n                for (int i = 0; i < width; i++) {\n               \
    \     const uint64_t mod2 = uint64_t(Mint::mod()) * Mint::mod();\n           \
    \         const uint64_t a0 = a[offset + i].val();\n                    const\
    \ uint64_t a1 = uint64_t(a[offset + i + width].val()) * twiddle.val();\n     \
    \               const uint64_t a2 =\n                        uint64_t(a[offset\
    \ + i + 2 * width].val()) * twiddle2.val();\n                    const uint64_t\
    \ a3 =\n                        uint64_t(a[offset + i + 3 * width].val()) * twiddle3.val();\n\
    \                    const uint64_t a1na3i =\n                        uint64_t(Mint(a1\
    \ + mod2 - a3).val()) * imaginary.val();\n                    const uint64_t negative_a2\
    \ = mod2 - a2;\n                    a[offset + i] = Mint(a0 + a2 + a1 + a3);\n\
    \                    a[offset + i + width] = Mint(a0 + a2 + 2 * mod2 - a1 - a3);\n\
    \                    a[offset + i + 2 * width] = Mint(a0 + negative_a2 + a1na3i);\n\
    \                    a[offset + i + 3 * width] = Mint(a0 + negative_a2 + mod2\
    \ - a1na3i);\n                }\n                if (block + 1 != (1 << phase))\n\
    \                    twiddle *= roots.rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase += 2;\n        }\n    } else {\n        int\
    \ phase = height;\n        while (phase > 0) {\n            if (phase == 1) {\n\
    \                const int width = 1 << (height - phase);\n                Mint\
    \ twiddle = 1;\n                for (int block = 0; block < (1 << (phase - 1));\
    \ block++) {\n                    const int offset = block << (height - phase\
    \ + 1);\n                    for (int i = 0; i < width; i++) {\n             \
    \           const Mint left = a[offset + i];\n                        const Mint\
    \ right = a[offset + i + width];\n                        a[offset + i] = left\
    \ + right;\n                        a[offset + i + width] = (left - right) * twiddle;\n\
    \                    }\n                    if (block + 1 != (1 << (phase - 1)))\n\
    \                        twiddle *= roots.inverse_rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase--;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase);\n         \
    \   Mint twiddle = 1;\n            const Mint inverse_imaginary = roots.inverse_root[2];\n\
    \            for (int block = 0; block < (1 << (phase - 2)); block++) {\n    \
    \            const Mint twiddle2 = twiddle * twiddle;\n                const Mint\
    \ twiddle3 = twiddle2 * twiddle;\n                const int offset = block <<\
    \ (height - phase + 2);\n                for (int i = 0; i < width; i++) {\n \
    \                   const uint64_t a0 = a[offset + i].val();\n               \
    \     const uint64_t a1 = a[offset + i + width].val();\n                    const\
    \ uint64_t a2 = a[offset + i + 2 * width].val();\n                    const uint64_t\
    \ a3 = a[offset + i + 3 * width].val();\n                    const uint64_t a2na3i\
    \ =\n                        uint64_t(Mint((Mint::mod() + a2 - a3) * inverse_imaginary.val()).val());\n\
    \                    a[offset + i] = Mint(a0 + a1 + a2 + a3);\n              \
    \      a[offset + i + width] =\n                        Mint((a0 + Mint::mod()\
    \ - a1 + a2na3i) * twiddle.val());\n                    a[offset + i + 2 * width]\
    \ = Mint(\n                        (a0 + a1 + 2ULL * Mint::mod() - a2 - a3) *\
    \ twiddle2.val());\n                    a[offset + i + 3 * width] = Mint(\n  \
    \                      (a0 + Mint::mod() - a1 + Mint::mod() - a2na3i) * twiddle3.val());\n\
    \                }\n                if (block + 1 != (1 << (phase - 2)))\n   \
    \                 twiddle *= roots.inverse_rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase -= 2;\n        }\n        if (normalize) {\n\
    \            const Mint inverse_n = Mint(n).inv();\n            for (Mint& value\
    \ : a) value *= inverse_n;\n        }\n    }\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \n#pragma GCC push_options\n#pragma GCC target(\"avx2,bmi\")\n\ntemplate <class\
    \ Mint>\n__attribute__((target(\"avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_simd(const\
    \ std::vector<Mint>& a,\n                                             const std::vector<Mint>&\
    \ b) {\n    const int result_size = int(a.size() + b.size() - 1);\n    int n =\
    \ 1;\n    while (n < result_size) n <<= 1;\n    auto* transformed_a = static_cast<uint32_t*>(\n\
    \        ::operator new[](sizeof(uint32_t) * n, std::align_val_t(32)));\n    auto*\
    \ transformed_b = static_cast<uint32_t*>(\n        ::operator new[](sizeof(uint32_t)\
    \ * n, std::align_val_t(32)));\n    if constexpr (std::is_same_v<Mint, math::ModInt<998244353>>)\
    \ {\n        static_assert(sizeof(Mint) == sizeof(uint32_t) && std::is_trivially_copyable_v<Mint>);\n\
    \        std::memcpy(transformed_a, a.data(), sizeof(uint32_t) * a.size());\n\
    \        std::memcpy(transformed_b, b.data(), sizeof(uint32_t) * b.size());\n\
    \    } else {\n        for (int i = 0; i < int(a.size()); i++) transformed_a[i]\
    \ = a[i].val();\n        for (int i = 0; i < int(b.size()); i++) transformed_b[i]\
    \ = b[i].val();\n    }\n    std::memset(transformed_a + a.size(), 0, sizeof(uint32_t)\
    \ * (n - a.size()));\n    std::memset(transformed_b + b.size(), 0, sizeof(uint32_t)\
    \ * (n - b.size()));\n\n    static constexpr fast998_v2::FNTT32_info transform(998244353);\n\
    \    const std::size_t vector_size = std::size_t(n) >> 3;\n    fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed_a),\
    \ vector_size, &transform);\n    fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed_b),\
    \ vector_size, &transform);\n    fast998_v2::vector_convolution_direct(\n    \
    \    reinterpret_cast<__m256i*>(transformed_a),\n        reinterpret_cast<const\
    \ __m256i*>(transformed_b), vector_size, &transform);\n    fast998_v2::vector_dit<true>(reinterpret_cast<__m256i*>(transformed_a),\
    \ vector_size,\n                                 &transform);\n\n    std::vector<Mint>\
    \ result(result_size);\n    if constexpr (std::is_same_v<Mint, math::ModInt<998244353>>)\
    \ {\n        std::memcpy(result.data(), transformed_a, sizeof(uint32_t) * result_size);\n\
    \    } else {\n        for (int j = 0; j < result_size; j++) result[j] = Mint::raw(transformed_a[j]);\n\
    \    }\n    ::operator delete[](transformed_a, std::align_val_t(32));\n    ::operator\
    \ delete[](transformed_b, std::align_val_t(32));\n    return result;\n}\n\n#pragma\
    \ GCC pop_options\n\n#endif\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    std::vector<Mint> convolution_naive(const std::vector<Mint>& a, const std::vector<Mint>&\
    \ b) {\n    if (a.empty() || b.empty()) return {};\n    std::vector<Mint> result(a.size()\
    \ + b.size() - 1);\n    if (a.size() < b.size()) {\n        for (int i = 0; i\
    \ < int(a.size()); i++) {\n            for (int j = 0; j < int(b.size()); j++)\
    \ result[i + j] += a[i] * b[j];\n        }\n    } else {\n        for (int j =\
    \ 0; j < int(b.size()); j++) {\n            for (int i = 0; i < int(a.size());\
    \ i++) result[i + j] += a[i] * b[j];\n        }\n    }\n    return result;\n}\n\
    \ntemplate <class Mint>\nstd::vector<Mint> convolution_ntt(const std::vector<Mint>&\
    \ a, const std::vector<Mint>& b) {\n    const int result_size = int(a.size() +\
    \ b.size() - 1);\n    int n = 1;\n    while (n < result_size) n <<= 1;\n    assert((Mint::mod()\
    \ - 1) % uint32_t(n) == 0);\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n    if constexpr\
    \ (Mint::mod() == 998244353) {\n        if (n >= 64 && __builtin_cpu_supports(\"\
    avx2\"))\n            return internal::convolution_998244353_simd(a, b);\n   \
    \ }\n#endif\n\n    // Allocate the padded buffers directly.  Constructing from\
    \ the inputs and\n    // then resizing used to allocate and copy both large operands\
    \ twice.\n    std::vector<Mint> fa(n);\n    std::vector<Mint> fb(n);\n    std::copy(a.begin(),\
    \ a.end(), fa.begin());\n    std::copy(b.begin(), b.end(), fb.begin());\n    internal::ntt(fa,\
    \ false);\n    internal::ntt(fb, false);\n    const Mint inverse_n = Mint(n).inv();\n\
    \    for (int i = 0; i < n; i++) fa[i] *= fb[i] * inverse_n;\n    internal::ntt(fa,\
    \ true, false);\n    fa.resize(result_size);\n    return fa;\n}\n\nnamespace internal\
    \ {\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_998244353_blocked_scalar(const\
    \ std::vector<Mint>& a,\n                                                    \
    \   const std::vector<Mint>& b,\n                                            \
    \           int transform_size) {\n    assert(Mint::mod() == 998244353);\n   \
    \ assert(transform_size >= 2 && (transform_size & (transform_size - 1)) == 0);\n\
    \    assert((Mint::mod() - 1) % uint32_t(transform_size) == 0);\n\n    const int\
    \ block_size = transform_size / 2;\n    const int a_blocks = int((a.size() + block_size\
    \ - 1) / block_size);\n    const int b_blocks = int((b.size() + block_size - 1)\
    \ / block_size);\n\n    auto transform_blocks = [&](const std::vector<Mint>& values,\
    \ int block_count) {\n        std::vector<std::vector<Mint>> blocks;\n       \
    \ blocks.reserve(block_count);\n        for (int block = 0; block < block_count;\
    \ block++) {\n            const int begin = block * block_size;\n            const\
    \ int count = std::min(block_size, int(values.size()) - begin);\n            std::vector<Mint>\
    \ transformed(transform_size);\n            std::copy_n(values.begin() + begin,\
    \ count, transformed.begin());\n            ntt(transformed, false);\n       \
    \     blocks.emplace_back(std::move(transformed));\n        }\n        return\
    \ blocks;\n    };\n\n    std::vector<std::vector<Mint>> transformed_a = transform_blocks(a,\
    \ a_blocks);\n    std::vector<std::vector<Mint>> transformed_b = transform_blocks(b,\
    \ b_blocks);\n    const int result_size = int(a.size() + b.size() - 1);\n    std::vector<Mint>\
    \ result(result_size);\n    std::vector<Mint> transformed_result(transform_size);\n\
    \    for (int diagonal = 0; diagonal < a_blocks + b_blocks - 1; diagonal++) {\n\
    \        std::fill(transformed_result.begin(), transformed_result.end(), Mint(0));\n\
    \        const int first_a = std::max(0, diagonal - (b_blocks - 1));\n       \
    \ const int last_a = std::min(a_blocks - 1, diagonal);\n        for (int a_block\
    \ = first_a; a_block <= last_a; a_block++) {\n            const int b_block =\
    \ diagonal - a_block;\n            for (int i = 0; i < transform_size; i++)\n\
    \                transformed_result[i] +=\n                    transformed_a[a_block][i]\
    \ * transformed_b[b_block][i];\n        }\n        ntt(transformed_result, true);\n\
    \n        const int output_offset = diagonal * block_size;\n        const int\
    \ output_count = std::min(transform_size, result_size - output_offset);\n    \
    \    for (int i = 0; i < output_count; i++)\n            result[output_offset\
    \ + i] += transformed_result[i];\n    }\n    return result;\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \nclass AlignedUint32Buffer {\n   private:\n    uint32_t* data_;\n\n   public:\n\
    \    explicit AlignedUint32Buffer(std::size_t size)\n        : data_(static_cast<uint32_t*>(\n\
    \              ::operator new[](sizeof(uint32_t) * size, std::align_val_t(32))))\
    \ {}\n\n    AlignedUint32Buffer(const AlignedUint32Buffer&) = delete;\n    AlignedUint32Buffer&\
    \ operator=(const AlignedUint32Buffer&) = delete;\n\n    AlignedUint32Buffer(AlignedUint32Buffer&&\
    \ other) noexcept : data_(other.data_) {\n        other.data_ = nullptr;\n   \
    \ }\n\n    AlignedUint32Buffer& operator=(AlignedUint32Buffer&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        ::operator delete[](data_,\
    \ std::align_val_t(32));\n        data_ = other.data_;\n        other.data_ =\
    \ nullptr;\n        return *this;\n    }\n\n    ~AlignedUint32Buffer() {\n   \
    \     ::operator delete[](data_, std::align_val_t(32));\n    }\n\n    uint32_t*\
    \ data() {\n        return data_;\n    }\n\n    const uint32_t* data() const {\n\
    \        return data_;\n    }\n};\n\ntemplate <class Mint>\n__attribute__((target(\"\
    avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_blocked_simd(const\
    \ std::vector<Mint>& a,\n                                                    \
    \ const std::vector<Mint>& b,\n                                              \
    \       int transform_size) {\n    assert(Mint::mod() == 998244353);\n    assert(transform_size\
    \ >= 64 && (transform_size & (transform_size - 1)) == 0);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(transform_size) == 0);\n\n    const int block_size = transform_size\
    \ / 2;\n    const int a_blocks = int((a.size() + block_size - 1) / block_size);\n\
    \    const int b_blocks = int((b.size() + block_size - 1) / block_size);\n   \
    \ static constexpr fast998_v2::FNTT32_info transform(998244353);\n    const std::size_t\
    \ vector_size = std::size_t(transform_size) / 8;\n\n    auto transform_blocks\
    \ = [&](const std::vector<Mint>& values, int block_count) {\n        std::vector<AlignedUint32Buffer>\
    \ blocks;\n        blocks.reserve(block_count);\n        for (int block = 0; block\
    \ < block_count; block++) {\n            const int begin = block * block_size;\n\
    \            const int count = std::min(block_size, int(values.size()) - begin);\n\
    \            AlignedUint32Buffer transformed(transform_size);\n            if\
    \ constexpr (std::is_same_v<Mint, math::ModInt<998244353>>) {\n              \
    \  static_assert(sizeof(Mint) == sizeof(uint32_t) &&\n                       \
    \       std::is_trivially_copyable_v<Mint>);\n                std::memcpy(transformed.data(),\
    \ values.data() + begin,\n                            sizeof(uint32_t) * count);\n\
    \            } else {\n                for (int i = 0; i < count; i++)\n     \
    \               transformed.data()[i] = values[begin + i].val();\n           \
    \ }\n            std::memset(transformed.data() + count, 0,\n                \
    \        sizeof(uint32_t) * (transform_size - count));\n            fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed.data()),\n\
    \                                   vector_size, &transform);\n            blocks.emplace_back(std::move(transformed));\n\
    \        }\n        return blocks;\n    };\n\n    std::vector<AlignedUint32Buffer>\
    \ transformed_a = transform_blocks(a, a_blocks);\n    std::vector<AlignedUint32Buffer>\
    \ transformed_b = transform_blocks(b, b_blocks);\n    const int result_size =\
    \ int(a.size() + b.size() - 1);\n    std::vector<Mint> result(result_size);\n\
    \    AlignedUint32Buffer transformed_result(transform_size);\n    for (int diagonal\
    \ = 0; diagonal < a_blocks + b_blocks - 1; diagonal++) {\n        std::memset(transformed_result.data(),\
    \ 0, sizeof(uint32_t) * transform_size);\n        const int first_a = std::max(0,\
    \ diagonal - (b_blocks - 1));\n        const int last_a = std::min(a_blocks -\
    \ 1, diagonal);\n        for (int a_block = first_a; a_block <= last_a; a_block++)\
    \ {\n            const int b_block = diagonal - a_block;\n            fast998_v2::vector_convolution_accumulate(\n\
    \                reinterpret_cast<__m256i*>(transformed_result.data()),\n    \
    \            reinterpret_cast<const __m256i*>(transformed_a[a_block].data()),\n\
    \                reinterpret_cast<const __m256i*>(transformed_b[b_block].data()),\n\
    \                vector_size, &transform);\n        }\n        fast998_v2::vector_dit<true>(\n\
    \            reinterpret_cast<__m256i*>(transformed_result.data()), vector_size,\n\
    \            &transform);\n\n        const int output_offset = diagonal * block_size;\n\
    \        const int output_count = std::min(transform_size, result_size - output_offset);\n\
    \        for (int i = 0; i < output_count; i++) {\n            uint32_t value\
    \ = result[output_offset + i].val() + transformed_result.data()[i];\n        \
    \    if (value >= Mint::mod()) value -= Mint::mod();\n            result[output_offset\
    \ + i] = Mint::raw(value);\n        }\n    }\n    return result;\n}\n\n#endif\n\
    \ntemplate <class Mint>\nstd::vector<Mint> convolution_998244353_blocked(const\
    \ std::vector<Mint>& a,\n                                                const\
    \ std::vector<Mint>& b,\n                                                int transform_size\
    \ = 1 << 23) {\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n    if (transform_size >= 64 &&\
    \ __builtin_cpu_supports(\"avx2\"))\n        return convolution_998244353_blocked_simd(a,\
    \ b, transform_size);\n#endif\n    return convolution_998244353_blocked_scalar(a,\
    \ b, transform_size);\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    std::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>&\
    \ b) {\n    if (a.empty() || b.empty()) return {};\n    if (std::min(a.size(),\
    \ b.size()) <= 32) return convolution_naive(a, b);\n\n    const int result_size\
    \ = int(a.size() + b.size() - 1);\n    int n = 1;\n    while (n < result_size)\
    \ n <<= 1;\n    if constexpr (internal::has_static_modulus<Mint>::value) {\n \
    \       if constexpr (Mint::mod() == 998244353) {\n            if (n > (1 << 23))\n\
    \                return internal::convolution_998244353_blocked(a, b);\n     \
    \   }\n        if ((Mint::mod() - 1) % uint32_t(n) == 0) return convolution_ntt(a,\
    \ b);\n    }\n\n    using Mint1 = math::ModInt<167772161>;\n    using Mint2 =\
    \ math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n    assert(n\
    \ <= (1 << 24));\n\n    [[maybe_unused]] const unsigned __int128 coefficient_bound\
    \ =\n        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod()\
    \ - 1) *\n        (Mint::mod() - 1);\n    [[maybe_unused]] const unsigned __int128\
    \ crt_modulus =\n        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod()\
    \ * Mint3::mod();\n    assert(coefficient_bound < crt_modulus);\n\n    auto converted_convolution\
    \ = [&]<class OtherMint>() {\n        std::vector<OtherMint> converted_a(a.size());\n\
    \        std::vector<OtherMint> converted_b(b.size());\n        for (int i = 0;\
    \ i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());\n        for\
    \ (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());\n\
    \        return convolution_ntt(converted_a, converted_b);\n    };\n    std::vector<Mint1>\
    \ c1 = converted_convolution.template operator()<Mint1>();\n    std::vector<Mint2>\
    \ c2 = converted_convolution.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ c3 = converted_convolution.template operator()<Mint3>();\n    static const uint64_t\
    \ inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();\n    static const uint64_t\
    \ mod1_mod3 = Mint1::mod() % Mint3::mod();\n    static const uint64_t mod1_mod2_mod3\
    \ =\n        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();\n    static\
    \ const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();\n\
    \n    const uint64_t target_mod = Mint::mod();\n    const uint64_t mod1_target\
    \ = Mint1::mod() % target_mod;\n    const uint64_t mod1_mod2_target = mod1_target\
    \ * (Mint2::mod() % target_mod) % target_mod;\n    std::vector<Mint> result(result_size);\n\
    \    for (int i = 0; i < result_size; i++) {\n        const uint64_t r1 = c1[i].val();\n\
    \        const uint64_t r2 = c2[i].val();\n        const uint64_t r3 = c3[i].val();\n\
    \        const uint64_t first =\n            (r2 + Mint2::mod() - r1 % Mint2::mod())\
    \ % Mint2::mod() * inverse_mod1_mod2 %\n            Mint2::mod();\n        const\
    \ uint64_t combined_mod3 =\n            (r1 % Mint3::mod() + mod1_mod3 * (first\
    \ % Mint3::mod())) % Mint3::mod();\n        const uint64_t second =\n        \
    \    (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3\
    \ %\n            Mint3::mod();\n\n        uint64_t value = r1 % target_mod;\n\
    \        value = (value + mod1_target * (first % target_mod)) % target_mod;\n\
    \        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;\n\
    \        result[i] = Mint::raw(uint32_t(value));\n    }\n    return result;\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 9 \"string/wildcard_pattern_matching.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\nnamespace internal {\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> wildcard_mismatch_scores(\n    const std::string&\
    \ text,\n    const std::string& pattern,\n    char wildcard\n) {\n    int n =\
    \ int(text.size());\n    int m = int(pattern.size());\n    std::array<std::vector<Mint>,\
    \ 3> text_powers;\n    std::array<std::vector<Mint>, 3> pattern_powers;\n    for\
    \ (auto& powers : text_powers) powers.resize(n);\n    for (auto& powers : pattern_powers)\
    \ powers.resize(m);\n\n    auto encode = [wildcard](char character) {\n      \
    \  if (character == wildcard) return 0;\n        return int(static_cast<unsigned\
    \ char>(character)) + 1;\n    };\n    for (int i = 0; i < n; i++) {\n        Mint\
    \ value = encode(text[i]);\n        text_powers[0][i] = value;\n        text_powers[1][i]\
    \ = value * value;\n        text_powers[2][i] = value * value * value;\n    }\n\
    \    for (int i = 0; i < m; i++) {\n        Mint value = encode(pattern[m - 1\
    \ - i]);\n        pattern_powers[0][i] = value;\n        pattern_powers[1][i]\
    \ = value * value;\n        pattern_powers[2][i] = value * value * value;\n  \
    \  }\n\n    std::vector<Mint> scores(n - m + 1);\n    for (int power = 0; power\
    \ < 3; power++) {\n        std::vector<Mint> product = fps::convolution(\n   \
    \         text_powers[power],\n            pattern_powers[2 - power]\n       \
    \ );\n        Mint multiplier = power == 1 ? Mint(-2) : Mint(1);\n        for\
    \ (int start = 0; start <= n - m; start++) {\n            scores[start] += multiplier\
    \ * product[start + m - 1];\n        }\n    }\n    return scores;\n}\n\n}  //\
    \ namespace internal\n\n// result[i] is true exactly when pattern matches text[i,\
    \ i + pattern.size()).\n// The wildcard character matches every character on either\
    \ side.\ninline std::vector<bool> wildcard_pattern_matching(\n    const std::string&\
    \ text,\n    const std::string& pattern,\n    char wildcard = '*'\n) {\n    int\
    \ n = int(text.size());\n    int m = int(pattern.size());\n    if (m == 0) return\
    \ std::vector<bool>(n + 1, true);\n    if (n < m) return {};\n\n    using Mint1\
    \ = math::ModInt<469762049>;\n    using Mint2 = math::ModInt<754974721>;\n   \
    \ std::vector<Mint1> first_scores =\n        internal::wildcard_mismatch_scores<Mint1>(text,\
    \ pattern, wildcard);\n    std::vector<Mint2> second_scores =\n        internal::wildcard_mismatch_scores<Mint2>(text,\
    \ pattern, wildcard);\n\n    std::vector<bool> result(n - m + 1, false);\n   \
    \ for (int start = 0; start <= n - m; start++) {\n        result[start] = first_scores[start].val()\
    \ == 0 &&\n                        second_scores[start].val() == 0;\n    }\n \
    \   return result;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line\
    \ 1 \"string/z_algorithm.hpp\"\n\n\n\n#line 6 \"string/z_algorithm.hpp\"\n\nnamespace\
    \ m1une {\nnamespace string {\n\n// Returns z[i] = LCP(sequence, sequence[i..]).\n\
    template <class Sequence>\nstd::vector<int> z_algorithm(const Sequence& sequence)\
    \ {\n    int n = int(sequence.size());\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ z(n);\n    z[0] = n;\n    int left = 0;\n    int right = 0;\n    for (int i\
    \ = 1; i < n; i++) {\n        if (i < right) z[i] = std::min(right - i, z[i -\
    \ left]);\n        while (i + z[i] < n && sequence[z[i]] == sequence[i + z[i]])\
    \ {\n            z[i]++;\n        }\n        if (right < i + z[i]) {\n       \
    \     left = i;\n            right = i + z[i];\n        }\n    }\n    return z;\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 22 \"string/all.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_STRING_ALL_HPP

    #define M1UNE_STRING_ALL_HPP 1


    #include "aho_corasick.hpp"

    #include "eertree.hpp"

    #include "kmp.hpp"

    #include "levenshtein_distance.hpp"

    #include "longest_common_extension.hpp"

    #include "longest_common_subsequence.hpp"

    #include "longest_common_substring.hpp"

    #include "lyndon_factorization.hpp"

    #include "manacher.hpp"

    #include "minimum_rotation.hpp"

    #include "rolling_hash.hpp"

    #include "runs.hpp"

    #include "string_hash.hpp"

    #include "suffix_automaton.hpp"

    #include "suffix_array.hpp"

    #include "trie.hpp"

    #include "wildcard_pattern_matching.hpp"

    #include "z_algorithm.hpp"


    #endif  // M1UNE_STRING_ALL_HPP

    '
  dependsOn:
  - string/aho_corasick.hpp
  - string/eertree.hpp
  - string/kmp.hpp
  - string/levenshtein_distance.hpp
  - string/longest_common_extension.hpp
  - string/suffix_array.hpp
  - string/longest_common_subsequence.hpp
  - string/longest_common_substring.hpp
  - string/lyndon_factorization.hpp
  - string/minimum_rotation.hpp
  - string/manacher.hpp
  - string/rolling_hash.hpp
  - string/runs.hpp
  - string/string_hash.hpp
  - string/suffix_automaton.hpp
  - string/trie.hpp
  - string/wildcard_pattern_matching.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - string/z_algorithm.hpp
  isVerificationFile: false
  path: string/all.hpp
  requiredBy: []
  timestamp: '2026-07-13 23:28:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
documentation_of: string/all.hpp
layout: document
title: String Algorithms Bundle
---

## Overview

`string/all.hpp` includes the reusable string algorithms in this repository.
Use individual headers when compile time matters, or this bundle during a
contest when convenience matters more.

## Included Headers

| Header | Contents |
| --- | --- |
| `string/aho_corasick.hpp` | Multi-pattern matching with failure links and occurrence counting. |
| `string/eertree.hpp` | Online palindromic tree with suffix and series links. |
| `string/levenshtein_distance.hpp` | Unit-cost edit distance in linear auxiliary memory. |
| `string/kmp.hpp` | Prefix function and linear-time KMP occurrence search. |
| `string/longest_common_extension.hpp` | Static longest-common-extension queries and substring comparisons. |
| `string/longest_common_subsequence.hpp` | Finds one longest subsequence common to two sequences. |
| `string/longest_common_substring.hpp` | Finds one longest substring common to two sequences. |
| `string/lyndon_factorization.hpp` | Duval's linear-time Lyndon factorization. |
| `string/z_algorithm.hpp` | Linear-time Z array. |
| `string/manacher.hpp` | Odd/even palindrome radii and substring checks. |
| `string/minimum_rotation.hpp` | Earliest lexicographically minimum cyclic shift in linear time. |
| `string/suffix_automaton.hpp` | Online suffix automaton for substring queries and occurrence classes. |
| `string/suffix_array.hpp` | Suffix array and LCP array. |
| `string/trie.hpp` | Contiguous-alphabet multiset trie with prefix queries. |
| `string/wildcard_pattern_matching.hpp` | Exact wildcard matching at every text alignment. |
| `string/rolling_hash.hpp` | Static substring hashing, LCP, and comparison. |
| `string/runs.hpp` | Enumerates maximal periodic substrings and their minimum periods. |
| `string/string_hash.hpp` | Double whole-string hashing and constant-time hash concatenation. |
