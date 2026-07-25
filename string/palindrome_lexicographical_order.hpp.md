---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/palindrome_lexicographical_order.test.cpp
    title: verify/string/palindrome_lexicographical_order.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/palindrome_lexicographical_order.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <string>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"string/eertree.hpp\"\n\n\n\n#include <array>\n#line 6\
    \ \"string/eertree.hpp\"\n#include <cstddef>\n#include <limits>\n#line 10 \"string/eertree.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\ntemplate <int AlphabetSize = 26,\
    \ int FirstCharacter = 'a'>\nstruct Eertree {\n    static_assert(0 < AlphabetSize);\n\
    \n    using node_id = int;\n    static constexpr node_id even_root = 0;\n    static\
    \ constexpr node_id odd_root = 1;\n    static constexpr node_id null_node = -1;\n\
    \n    struct Node {\n        std::array<node_id, AlphabetSize> next;\n       \
    \ node_id suffix_link;\n        node_id series_link;\n        int length;\n  \
    \      int diff;\n        int suffix_count;\n        int first_end;\n        long\
    \ long suffix_occurrences;\n\n        Node(int length_value = 0, node_id suffix_link_value\
    \ = even_root, node_id series_link_value = even_root)\n            : suffix_link(suffix_link_value),\n\
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
    \ string\n}  // namespace m1une\n\n\n#line 1 \"string/suffix_array.hpp\"\n\n\n\
    \n#line 6 \"string/suffix_array.hpp\"\n#include <numeric>\n#line 8 \"string/suffix_array.hpp\"\
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
    }  // namespace m1une\n\n\n#line 12 \"string/palindrome_lexicographical_order.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\n// Indexes the distinct nonempty\
    \ palindromic substrings of one sequence.\ntemplate <\n    class Sequence = std::string,\n\
    \    int AlphabetSize = 26,\n    int FirstCharacter = 'a'\n>\nstruct PalindromeLexicographicalOrder\
    \ {\n    static_assert(0 < AlphabetSize);\n\n    using eertree_type = Eertree<AlphabetSize,\
    \ FirstCharacter>;\n    using node_id = typename eertree_type::node_id;\n\n  \
    \ private:\n    Sequence _sequence;\n    eertree_type _eertree;\n    std::vector<node_id>\
    \ _nodes_in_order;\n    std::vector<int> _order_of_node;\n\n    template <class\
    \ Symbol>\n    static int symbol_index(const Symbol& symbol) {\n        int index\
    \ = int(symbol) - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n\
    \        return index;\n    }\n\n    void build_order() {\n        const int node_count\
    \ = _eertree.node_count();\n        std::vector<std::vector<node_id>> suffix_children(node_count);\n\
    \        for (node_id id = 0; id < node_count; id++) {\n            if (id ==\
    \ eertree_type::odd_root) continue;\n            suffix_children[_eertree.node(id).suffix_link].push_back(id);\n\
    \        }\n\n        std::vector<int> enter(node_count);\n        std::vector<int>\
    \ leave(node_count);\n        std::vector<std::pair<node_id, bool>> stack;\n \
    \       stack.reserve(2 * node_count);\n        stack.emplace_back(eertree_type::odd_root,\
    \ false);\n        int timer = 0;\n        while (!stack.empty()) {\n        \
    \    auto [id, exiting] = stack.back();\n            stack.pop_back();\n     \
    \       if (exiting) {\n                leave[id] = timer;\n                continue;\n\
    \            }\n\n            enter[id] = timer++;\n            stack.emplace_back(id,\
    \ true);\n            const auto& children = suffix_children[id];\n          \
    \  for (int i = int(children.size()) - 1; i >= 0; i--) {\n                stack.emplace_back(children[i],\
    \ false);\n            }\n        }\n\n        std::vector<int> suffixes = suffix_array(_sequence);\n\
    \        std::vector<int> suffix_rank(_sequence.size());\n        for (int rank\
    \ = 0; rank < int(suffixes.size()); rank++) {\n            suffix_rank[suffixes[rank]]\
    \ = rank;\n        }\n\n        _nodes_in_order.resize(_eertree.size());\n   \
    \     for (int i = 0; i < _eertree.size(); i++) {\n            _nodes_in_order[i]\
    \ = i + 2;\n        }\n\n        auto is_ancestor = [&](node_id ancestor, node_id\
    \ descendant) {\n            return\n                enter[ancestor] <= enter[descendant]\
    \ &&\n                leave[descendant] <= leave[ancestor];\n        };\n    \
    \    std::sort(\n            _nodes_in_order.begin(),\n            _nodes_in_order.end(),\n\
    \            [&](node_id first, node_id second) {\n                if (first ==\
    \ second) return false;\n\n                // A palindromic prefix is also a palindromic\
    \ suffix, so prefix\n                // cases are exactly the ancestor cases in\
    \ the suffix-link tree.\n                if (is_ancestor(first, second)) return\
    \ true;\n                if (is_ancestor(second, first)) return false;\n\n   \
    \             // Otherwise the first mismatch occurs inside both substrings,\n\
    \                // and the ranks of representative suffixes give their order.\n\
    \                int first_start = _eertree.first_occurrence(first).first;\n \
    \               int second_start = _eertree.first_occurrence(second).first;\n\
    \                return suffix_rank[first_start] < suffix_rank[second_start];\n\
    \            }\n        );\n\n        _order_of_node.assign(node_count, -1);\n\
    \        for (int order = 0; order < size(); order++) {\n            _order_of_node[_nodes_in_order[order]]\
    \ = order;\n        }\n    }\n\n   public:\n    PalindromeLexicographicalOrder()\
    \ : _order_of_node(2, -1) {}\n\n    explicit PalindromeLexicographicalOrder(const\
    \ Sequence& sequence)\n        : _sequence(sequence), _eertree(_sequence) {\n\
    \        build_order();\n    }\n\n    explicit PalindromeLexicographicalOrder(Sequence&&\
    \ sequence)\n        : _sequence(std::move(sequence)), _eertree(_sequence) {\n\
    \        build_order();\n    }\n\n    int size() const {\n        return int(_nodes_in_order.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes_in_order.empty();\n\
    \    }\n\n    int text_length() const {\n        return int(_sequence.size());\n\
    \    }\n\n    const Sequence& sequence() const {\n        return _sequence;\n\
    \    }\n\n    const eertree_type& eertree() const {\n        return _eertree;\n\
    \    }\n\n    const std::vector<node_id>& nodes_in_order() const {\n        return\
    \ _nodes_in_order;\n    }\n\n    int order_of_node(node_id id) const {\n     \
    \   assert(2 <= id && id < _eertree.node_count());\n        return _order_of_node[id];\n\
    \    }\n\n    node_id node_by_order(int order) const {\n        assert(0 <= order\
    \ && order < size());\n        return _nodes_in_order[order];\n    }\n\n    template\
    \ <class Palindrome>\n    node_id find(const Palindrome& palindrome) const {\n\
    \        const int length = int(palindrome.size());\n        if (length == 0)\
    \ return eertree_type::null_node;\n        for (int i = 0; i < length / 2; i++)\
    \ {\n            if (palindrome[i] != palindrome[length - 1 - i]) {\n        \
    \        return eertree_type::null_node;\n            }\n        }\n\n       \
    \ node_id id =\n            length & 1 ? eertree_type::odd_root : eertree_type::even_root;\n\
    \        for (int i = (length - 1) / 2; i >= 0; i--) {\n            int symbol\
    \ = symbol_index(palindrome[i]);\n            id = _eertree.node(id).next[symbol];\n\
    \            if (id == eertree_type::null_node) return id;\n        }\n      \
    \  return id;\n    }\n\n    template <class Palindrome>\n    bool contains(const\
    \ Palindrome& palindrome) const {\n        return find(palindrome) != eertree_type::null_node;\n\
    \    }\n\n    template <class Palindrome>\n    int order_of_palindrome(const Palindrome&\
    \ palindrome) const {\n        node_id id = find(palindrome);\n        return\
    \ id == eertree_type::null_node ? -1 : order_of_node(id);\n    }\n\n    std::pair<int,\
    \ int> representative_occurrence(int order) const {\n        return _eertree.first_occurrence(node_by_order(order));\n\
    \    }\n\n    Sequence palindrome(int order) const {\n        auto [left, right]\
    \ = representative_occurrence(order);\n        return Sequence(_sequence.begin()\
    \ + left, _sequence.begin() + right);\n    }\n\n    Sequence kth(int order) const\
    \ {\n        return palindrome(order);\n    }\n};\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_PALINDROME_LEXICOGRAPHICAL_ORDER_HPP\n#define M1UNE_STRING_PALINDROME_LEXICOGRAPHICAL_ORDER_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <string>\n#include <utility>\n\
    #include <vector>\n\n#include \"eertree.hpp\"\n#include \"suffix_array.hpp\"\n\
    \nnamespace m1une {\nnamespace string {\n\n// Indexes the distinct nonempty palindromic\
    \ substrings of one sequence.\ntemplate <\n    class Sequence = std::string,\n\
    \    int AlphabetSize = 26,\n    int FirstCharacter = 'a'\n>\nstruct PalindromeLexicographicalOrder\
    \ {\n    static_assert(0 < AlphabetSize);\n\n    using eertree_type = Eertree<AlphabetSize,\
    \ FirstCharacter>;\n    using node_id = typename eertree_type::node_id;\n\n  \
    \ private:\n    Sequence _sequence;\n    eertree_type _eertree;\n    std::vector<node_id>\
    \ _nodes_in_order;\n    std::vector<int> _order_of_node;\n\n    template <class\
    \ Symbol>\n    static int symbol_index(const Symbol& symbol) {\n        int index\
    \ = int(symbol) - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n\
    \        return index;\n    }\n\n    void build_order() {\n        const int node_count\
    \ = _eertree.node_count();\n        std::vector<std::vector<node_id>> suffix_children(node_count);\n\
    \        for (node_id id = 0; id < node_count; id++) {\n            if (id ==\
    \ eertree_type::odd_root) continue;\n            suffix_children[_eertree.node(id).suffix_link].push_back(id);\n\
    \        }\n\n        std::vector<int> enter(node_count);\n        std::vector<int>\
    \ leave(node_count);\n        std::vector<std::pair<node_id, bool>> stack;\n \
    \       stack.reserve(2 * node_count);\n        stack.emplace_back(eertree_type::odd_root,\
    \ false);\n        int timer = 0;\n        while (!stack.empty()) {\n        \
    \    auto [id, exiting] = stack.back();\n            stack.pop_back();\n     \
    \       if (exiting) {\n                leave[id] = timer;\n                continue;\n\
    \            }\n\n            enter[id] = timer++;\n            stack.emplace_back(id,\
    \ true);\n            const auto& children = suffix_children[id];\n          \
    \  for (int i = int(children.size()) - 1; i >= 0; i--) {\n                stack.emplace_back(children[i],\
    \ false);\n            }\n        }\n\n        std::vector<int> suffixes = suffix_array(_sequence);\n\
    \        std::vector<int> suffix_rank(_sequence.size());\n        for (int rank\
    \ = 0; rank < int(suffixes.size()); rank++) {\n            suffix_rank[suffixes[rank]]\
    \ = rank;\n        }\n\n        _nodes_in_order.resize(_eertree.size());\n   \
    \     for (int i = 0; i < _eertree.size(); i++) {\n            _nodes_in_order[i]\
    \ = i + 2;\n        }\n\n        auto is_ancestor = [&](node_id ancestor, node_id\
    \ descendant) {\n            return\n                enter[ancestor] <= enter[descendant]\
    \ &&\n                leave[descendant] <= leave[ancestor];\n        };\n    \
    \    std::sort(\n            _nodes_in_order.begin(),\n            _nodes_in_order.end(),\n\
    \            [&](node_id first, node_id second) {\n                if (first ==\
    \ second) return false;\n\n                // A palindromic prefix is also a palindromic\
    \ suffix, so prefix\n                // cases are exactly the ancestor cases in\
    \ the suffix-link tree.\n                if (is_ancestor(first, second)) return\
    \ true;\n                if (is_ancestor(second, first)) return false;\n\n   \
    \             // Otherwise the first mismatch occurs inside both substrings,\n\
    \                // and the ranks of representative suffixes give their order.\n\
    \                int first_start = _eertree.first_occurrence(first).first;\n \
    \               int second_start = _eertree.first_occurrence(second).first;\n\
    \                return suffix_rank[first_start] < suffix_rank[second_start];\n\
    \            }\n        );\n\n        _order_of_node.assign(node_count, -1);\n\
    \        for (int order = 0; order < size(); order++) {\n            _order_of_node[_nodes_in_order[order]]\
    \ = order;\n        }\n    }\n\n   public:\n    PalindromeLexicographicalOrder()\
    \ : _order_of_node(2, -1) {}\n\n    explicit PalindromeLexicographicalOrder(const\
    \ Sequence& sequence)\n        : _sequence(sequence), _eertree(_sequence) {\n\
    \        build_order();\n    }\n\n    explicit PalindromeLexicographicalOrder(Sequence&&\
    \ sequence)\n        : _sequence(std::move(sequence)), _eertree(_sequence) {\n\
    \        build_order();\n    }\n\n    int size() const {\n        return int(_nodes_in_order.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes_in_order.empty();\n\
    \    }\n\n    int text_length() const {\n        return int(_sequence.size());\n\
    \    }\n\n    const Sequence& sequence() const {\n        return _sequence;\n\
    \    }\n\n    const eertree_type& eertree() const {\n        return _eertree;\n\
    \    }\n\n    const std::vector<node_id>& nodes_in_order() const {\n        return\
    \ _nodes_in_order;\n    }\n\n    int order_of_node(node_id id) const {\n     \
    \   assert(2 <= id && id < _eertree.node_count());\n        return _order_of_node[id];\n\
    \    }\n\n    node_id node_by_order(int order) const {\n        assert(0 <= order\
    \ && order < size());\n        return _nodes_in_order[order];\n    }\n\n    template\
    \ <class Palindrome>\n    node_id find(const Palindrome& palindrome) const {\n\
    \        const int length = int(palindrome.size());\n        if (length == 0)\
    \ return eertree_type::null_node;\n        for (int i = 0; i < length / 2; i++)\
    \ {\n            if (palindrome[i] != palindrome[length - 1 - i]) {\n        \
    \        return eertree_type::null_node;\n            }\n        }\n\n       \
    \ node_id id =\n            length & 1 ? eertree_type::odd_root : eertree_type::even_root;\n\
    \        for (int i = (length - 1) / 2; i >= 0; i--) {\n            int symbol\
    \ = symbol_index(palindrome[i]);\n            id = _eertree.node(id).next[symbol];\n\
    \            if (id == eertree_type::null_node) return id;\n        }\n      \
    \  return id;\n    }\n\n    template <class Palindrome>\n    bool contains(const\
    \ Palindrome& palindrome) const {\n        return find(palindrome) != eertree_type::null_node;\n\
    \    }\n\n    template <class Palindrome>\n    int order_of_palindrome(const Palindrome&\
    \ palindrome) const {\n        node_id id = find(palindrome);\n        return\
    \ id == eertree_type::null_node ? -1 : order_of_node(id);\n    }\n\n    std::pair<int,\
    \ int> representative_occurrence(int order) const {\n        return _eertree.first_occurrence(node_by_order(order));\n\
    \    }\n\n    Sequence palindrome(int order) const {\n        auto [left, right]\
    \ = representative_occurrence(order);\n        return Sequence(_sequence.begin()\
    \ + left, _sequence.begin() + right);\n    }\n\n    Sequence kth(int order) const\
    \ {\n        return palindrome(order);\n    }\n};\n\n}  // namespace string\n\
    }  // namespace m1une\n\n#endif  // M1UNE_STRING_PALINDROME_LEXICOGRAPHICAL_ORDER_HPP\n"
  dependsOn:
  - string/eertree.hpp
  - string/suffix_array.hpp
  isVerificationFile: false
  path: string/palindrome_lexicographical_order.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-25 23:09:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/palindrome_lexicographical_order.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/palindrome_lexicographical_order.hpp
layout: document
title: Palindrome Lexicographical Order
---

## Overview

`PalindromeLexicographicalOrder` indexes every distinct nonempty palindromic
substring of one sequence. It assigns zero-based ranks after sorting the
palindromes lexicographically and supports both directions:

- find the rank of a palindrome or eertree node;
- recover the node, a representative occurrence, or a copy of the palindrome
  at a given rank.

The index combines an eertree with a suffix array. It does not count duplicate
occurrences separately.

```cpp
#include "string/palindrome_lexicographical_order.hpp"
```

## Template Parameters

```cpp
template <
    class Sequence = std::string,
    int AlphabetSize = 26,
    int FirstCharacter = 'a'
>
struct PalindromeLexicographicalOrder;
```

`Sequence` must provide `size()`, random-access iterators, and `operator[]`,
and it must be constructible from a pair of its iterators. Its value type must
be convertible to `int` and sortable. Symbols must belong to the contiguous range
`[FirstCharacter, FirstCharacter + AlphabetSize)`.

The default specialization accepts lowercase English strings. For a vector
whose values are in `[0, 4)`, use
`PalindromeLexicographicalOrder<std::vector<int>, 4, 0>`.

## Methods

Let `N` be the sequence length, `D` the number of distinct nonempty
palindromic substrings, and `L` the length of a queried or returned
palindrome.

| Method | Description | Complexity |
| --- | --- | --- |
| `PalindromeLexicographicalOrder()` | Constructs an empty index. | $O(1)$ |
| `PalindromeLexicographicalOrder(sequence)` | Copies or moves the sequence and builds its index. | $O(N \cdot AlphabetSize + N \log N)$ time and $O(N \cdot AlphabetSize)$ memory |
| `int size() const` | Returns `D`. | $O(1)$ |
| `bool empty() const` | Returns whether `D == 0`. | $O(1)$ |
| `int text_length() const` | Returns `N`. | $O(1)$ |
| `const Sequence& sequence() const` | Returns the indexed sequence. | $O(1)$ |
| `const eertree_type& eertree() const` | Returns the underlying eertree. | $O(1)$ |
| `const vector<node_id>& nodes_in_order() const` | Returns all real eertree nodes in increasing lexicographic order. | $O(1)$ |
| `int order_of_node(id) const` | Returns the zero-based rank of a real eertree node. | $O(1)$ |
| `node_id node_by_order(order) const` | Returns the eertree node having the given rank. | $O(1)$ |
| `node_id find(palindrome) const` | Returns its node, or `eertree_type::null_node` if it is not a nonempty palindromic substring. | $O(L)$ |
| `bool contains(palindrome) const` | Tests whether it is indexed. | $O(L)$ |
| `int order_of_palindrome(palindrome) const` | Returns its rank, or `-1` if it is not indexed. | $O(L)$ |
| `pair<int, int> representative_occurrence(order) const` | Returns a half-open occurrence interval of the ranked palindrome. | $O(1)$ |
| `Sequence palindrome(order) const` | Returns a copy of the ranked palindrome. | $O(L)$ |
| `Sequence kth(order) const` | Alias of `palindrome(order)`. | $O(L)$ |

`order_of_node`, `node_by_order`, `representative_occurrence`, `palindrome`,
and `kth` assert that their node or order is valid. The empty string is not
indexed. All query methods are non-mutating.

For a constant alphabet, construction takes $O(N \log N)$ time. It uses
$O(N)$ additional memory outside the fixed transition arrays stored by the
eertree.

## Example

```cpp
#include "string/palindrome_lexicographical_order.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::string::PalindromeLexicographicalOrder<> index(
        std::string("abacaba")
    );

    std::cout << index.order_of_palindrome(std::string("aca")) << '\n';
    for (int order = 0; order < index.size(); order++) {
        std::cout << order << ' ' << index.palindrome(order) << '\n';
    }
}
```
