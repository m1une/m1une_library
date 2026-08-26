---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  - icon: ':heavy_check_mark:'
    path: string/palindrome_lexicographical_order.hpp
    title: Palindrome Lexicographical Order
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
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
    PROBLEM: https://judge.yosupo.jp/problem/eertree
    links:
    - https://judge.yosupo.jp/problem/eertree
  bundledCode: "#line 1 \"verify/string/palindrome_lexicographical_order.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/eertree\"\n\n#line 1 \"string/palindrome_lexicographical_order.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <string>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"string/eertree.hpp\"\n\n\n\n#include\
    \ <array>\n#line 6 \"string/eertree.hpp\"\n#include <cstddef>\n#include <limits>\n\
    #line 10 \"string/eertree.hpp\"\n\nnamespace m1une {\nnamespace string {\n\ntemplate\
    \ <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct Eertree {\n    static_assert(0\
    \ < AlphabetSize);\n\n    using node_id = int;\n    static constexpr node_id even_root\
    \ = 0;\n    static constexpr node_id odd_root = 1;\n    static constexpr node_id\
    \ null_node = -1;\n\n    struct Node {\n        std::array<node_id, AlphabetSize>\
    \ next;\n        node_id suffix_link;\n        node_id series_link;\n        int\
    \ length;\n        int diff;\n        int suffix_count;\n        int first_end;\n\
    \        long long suffix_occurrences;\n\n        Node(int length_value = 0, node_id\
    \ suffix_link_value = even_root, node_id series_link_value = even_root)\n    \
    \        : suffix_link(suffix_link_value),\n              series_link(series_link_value),\n\
    \              length(length_value),\n              diff(0),\n              suffix_count(0),\n\
    \              first_end(0),\n              suffix_occurrences(0) {\n        \
    \    next.fill(null_node);\n        }\n    };\n\n   private:\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _text;\n    std::vector<node_id> _longest_suffix;\n\
    \    node_id _last;\n\n    template <class Symbol>\n    static int symbol_index(const\
    \ Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n     \
    \   assert(0 <= index && index < AlphabetSize);\n        return index;\n    }\n\
    \n    node_id find_extendable(node_id node, int position, int symbol) const {\n\
    \        while (true) {\n            int length = _nodes[node].length;\n     \
    \       int left = position - length - 1;\n            if (0 <= left && _text[left]\
    \ == symbol) return node;\n            node = _nodes[node].suffix_link;\n    \
    \    }\n    }\n\n    node_id new_node(int length) {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back(length);\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n   public:\n    Eertree() {\n\
    \        clear();\n    }\n\n    template <class Sequence>\n    explicit Eertree(const\
    \ Sequence& sequence) {\n        clear();\n        build(sequence);\n    }\n\n\
    \    int size() const {\n        return int(_nodes.size()) - 2;\n    }\n\n   \
    \ bool empty() const {\n        return size() == 0;\n    }\n\n    int node_count()\
    \ const {\n        return int(_nodes.size());\n    }\n\n    int text_length()\
    \ const {\n        return int(_text.size());\n    }\n\n    node_id last() const\
    \ {\n        return _last;\n    }\n\n    int longest_suffix_length() const {\n\
    \        return _nodes[_last].length;\n    }\n\n    const Node& node(node_id id)\
    \ const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id];\n\
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
    }  // namespace m1une\n\n\n#line 4 \"verify/string/palindrome_lexicographical_order.test.cpp\"\
    \n\n#line 7 \"verify/string/palindrome_lexicographical_order.test.cpp\"\n#include\
    \ <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#line 15 \"utilities/fast_io.hpp\"\n#include\
    \ <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\nstruct FastOutput;\n\nnamespace internal {\n\
    \n// Shared with the convenience helpers in template.hpp.\ninline FastOutput*\
    \ standard_output_instance = nullptr;\n\n// Detect std::begin(x), std::end(x).\n\
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
    \          _range_separator(' ') {\n        if (_stream == stdout\n          \
    \  && internal::standard_output_instance == nullptr) {\n            internal::standard_output_instance\
    \ = this;\n        }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n \
    \   FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n        if (internal::standard_output_instance == this) {\n\
    \            internal::standard_output_instance = nullptr;\n        }\n    }\n\
    \n    void flush() {\n        if (_position != 0) {\n            std::fwrite(_buffer,\
    \ 1, _position, _stream);\n            _position = 0;\n        }\n        std::fflush(_stream);\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        std::size_t position = 0;\n        while (position\
    \ < s.size()) {\n            if (_position == buffer_size) flush();\n        \
    \    const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/string/palindrome_lexicographical_order.test.cpp\"\
    \n#include <set>\n#line 14 \"verify/string/palindrome_lexicographical_order.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class Sequence>\nbool is_palindrome(const Sequence&\
    \ sequence, int left, int right) {\n    while (left < right) {\n        right--;\n\
    \        if (sequence[left] != sequence[right]) return false;\n        left++;\n\
    \    }\n    return true;\n}\n\ntemplate <class Sequence>\nstd::vector<Sequence>\
    \ naive_palindromes(const Sequence& sequence) {\n    std::set<Sequence> distinct;\n\
    \    int n = int(sequence.size());\n    for (int left = 0; left < n; left++) {\n\
    \        for (int right = left + 1; right <= n; right++) {\n            if (!is_palindrome(sequence,\
    \ left, right)) continue;\n            distinct.emplace(sequence.begin() + left,\
    \ sequence.begin() + right);\n        }\n    }\n    return std::vector<Sequence>(distinct.begin(),\
    \ distinct.end());\n}\n\ntemplate <class Index>\nvoid check_index(const Index&\
    \ index) {\n    using Tree = typename Index::eertree_type;\n    using Sequence\
    \ = std::remove_cvref_t<decltype(index.sequence())>;\n\n    std::vector<Sequence>\
    \ expected = naive_palindromes(index.sequence());\n    assert(index.size() ==\
    \ int(expected.size()));\n    assert(index.empty() == expected.empty());\n   \
    \ assert(index.text_length() == int(index.sequence().size()));\n    assert(index.eertree().size()\
    \ == index.size());\n    assert(int(index.nodes_in_order().size()) == index.size());\n\
    \n    for (int order = 0; order < index.size(); order++) {\n        const Sequence&\
    \ palindrome = expected[order];\n        int id = index.node_by_order(order);\n\
    \        assert(index.nodes_in_order()[order] == id);\n        assert(index.order_of_node(id)\
    \ == order);\n        assert(index.find(palindrome) == id);\n        assert(index.contains(palindrome));\n\
    \        assert(index.order_of_palindrome(palindrome) == order);\n        assert(index.palindrome(order)\
    \ == palindrome);\n        assert(index.kth(order) == palindrome);\n\n       \
    \ auto [left, right] = index.representative_occurrence(order);\n        assert(0\
    \ <= left && left < right);\n        assert(right <= index.text_length());\n \
    \       assert(\n            Sequence(\n                index.sequence().begin()\
    \ + left,\n                index.sequence().begin() + right\n            ) ==\
    \ palindrome\n        );\n    }\n\n    Sequence empty;\n    assert(index.find(empty)\
    \ == Tree::null_node);\n    assert(!index.contains(empty));\n    assert(index.order_of_palindrome(empty)\
    \ == -1);\n}\n\nvoid fixed_tests() {\n    using Index = m1une::string::PalindromeLexicographicalOrder<>;\n\
    \    Index empty;\n    check_index(empty);\n\n    Index index(std::string(\"abacaba\"\
    ));\n    check_index(index);\n    std::vector<std::string> expected = {\n    \
    \    \"a\", \"aba\", \"abacaba\", \"aca\", \"b\", \"bacab\", \"c\"\n    };\n \
    \   assert(naive_palindromes(index.sequence()) == expected);\n    assert(index.order_of_palindrome(std::string(\"\
    aca\")) == 3);\n    assert(index.order_of_palindrome(std::string(\"aa\")) == -1);\n\
    \    assert(index.order_of_palindrome(std::string(\"abc\")) == -1);\n    assert(!index.contains(std::string(\"\
    aa\")));\n    assert(!index.contains(std::string(\"abc\")));\n\n    Index moved(std::string(\"\
    aaaaa\"));\n    check_index(moved);\n    for (int length = 1; length <= 5; length++)\
    \ {\n        assert(moved.palindrome(length - 1) == std::string(length, 'a'));\n\
    \    }\n\n    using IntegerIndex =\n        m1une::string::PalindromeLexicographicalOrder<std::vector<int>,\
    \ 4, 0>;\n    std::vector<int> values;\n    values.push_back(2);\n    values.push_back(1);\n\
    \    values.push_back(2);\n    values.push_back(0);\n    values.push_back(2);\n\
    \    values.push_back(1);\n    values.push_back(2);\n    IntegerIndex integer_index(values);\n\
    \    check_index(integer_index);\n}\n\nvoid exhaustive_tests() {\n    for (int\
    \ length = 0; length <= 8; length++) {\n        std::uint64_t count = 1;\n   \
    \     for (int i = 0; i < length; i++) count *= 3;\n        for (std::uint64_t\
    \ code = 0; code < count; code++) {\n            std::uint64_t value = code;\n\
    \            std::string text(length, 'a');\n            for (char& character\
    \ : text) {\n                character = char('a' + value % 3);\n            \
    \    value /= 3;\n            }\n            check_index(\n                m1une::string::PalindromeLexicographicalOrder<\n\
    \                    std::string, 3, 'a'\n                >(std::move(text))\n\
    \            );\n        }\n    }\n}\n\nvoid randomized_tests() {\n    std::uint64_t\
    \ state = 0xf4c3182d9ab760e5ULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1000; trial++) {\n        int length = int(random()\
    \ % 45);\n        std::string text(length, 'a');\n        for (char& character\
    \ : text) {\n            character = char('a' + random() % 4);\n        }\n  \
    \      check_index(\n            m1une::string::PalindromeLexicographicalOrder<\n\
    \                std::string, 4, 'a'\n            >(std::move(text))\n       \
    \ );\n    }\n}\n\nint library_checker_id(int id) {\n    using Tree = m1une::string::Eertree<>;\n\
    \    if (id == Tree::odd_root) return 0;\n    if (id == Tree::even_root) return\
    \ 1;\n    return id;\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    fixed_tests();\n\
    \    exhaustive_tests();\n    randomized_tests();\n\n    std::string text;\n \
    \   fast_input >> text;\n    m1une::string::PalindromeLexicographicalOrder<> index(std::move(text));\n\
    \    const auto& tree = index.eertree();\n\n    std::vector<int> parent(tree.node_count(),\
    \ -1);\n    for (int id = 0; id < tree.node_count(); id++) {\n        const auto&\
    \ node = tree.node(id);\n        for (int symbol = 0; symbol < 26; symbol++) {\n\
    \            int to = node.next[symbol];\n            if (to != m1une::string::Eertree<>::null_node)\
    \ parent[to] = id;\n        }\n    }\n\n    fast_output << tree.size() << '\\\
    n';\n    for (int id = 2; id < tree.node_count(); id++) {\n        fast_output\
    \ << library_checker_id(parent[id]) - 1 << ' '\n                    << library_checker_id(tree.node(id).suffix_link)\
    \ - 1\n                    << '\\n';\n    }\n    const auto& longest_suffix =\
    \ tree.longest_suffix_nodes();\n    for (int i = 0; i < int(longest_suffix.size());\
    \ i++) {\n        if (i) fast_output << ' ';\n        fast_output << longest_suffix[i]\
    \ - 1;\n    }\n    fast_output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eertree\"\n\n#include \"\
    ../../string/palindrome_lexicographical_order.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <set>\n#include <string>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\ntemplate <class Sequence>\nbool is_palindrome(const\
    \ Sequence& sequence, int left, int right) {\n    while (left < right) {\n   \
    \     right--;\n        if (sequence[left] != sequence[right]) return false;\n\
    \        left++;\n    }\n    return true;\n}\n\ntemplate <class Sequence>\nstd::vector<Sequence>\
    \ naive_palindromes(const Sequence& sequence) {\n    std::set<Sequence> distinct;\n\
    \    int n = int(sequence.size());\n    for (int left = 0; left < n; left++) {\n\
    \        for (int right = left + 1; right <= n; right++) {\n            if (!is_palindrome(sequence,\
    \ left, right)) continue;\n            distinct.emplace(sequence.begin() + left,\
    \ sequence.begin() + right);\n        }\n    }\n    return std::vector<Sequence>(distinct.begin(),\
    \ distinct.end());\n}\n\ntemplate <class Index>\nvoid check_index(const Index&\
    \ index) {\n    using Tree = typename Index::eertree_type;\n    using Sequence\
    \ = std::remove_cvref_t<decltype(index.sequence())>;\n\n    std::vector<Sequence>\
    \ expected = naive_palindromes(index.sequence());\n    assert(index.size() ==\
    \ int(expected.size()));\n    assert(index.empty() == expected.empty());\n   \
    \ assert(index.text_length() == int(index.sequence().size()));\n    assert(index.eertree().size()\
    \ == index.size());\n    assert(int(index.nodes_in_order().size()) == index.size());\n\
    \n    for (int order = 0; order < index.size(); order++) {\n        const Sequence&\
    \ palindrome = expected[order];\n        int id = index.node_by_order(order);\n\
    \        assert(index.nodes_in_order()[order] == id);\n        assert(index.order_of_node(id)\
    \ == order);\n        assert(index.find(palindrome) == id);\n        assert(index.contains(palindrome));\n\
    \        assert(index.order_of_palindrome(palindrome) == order);\n        assert(index.palindrome(order)\
    \ == palindrome);\n        assert(index.kth(order) == palindrome);\n\n       \
    \ auto [left, right] = index.representative_occurrence(order);\n        assert(0\
    \ <= left && left < right);\n        assert(right <= index.text_length());\n \
    \       assert(\n            Sequence(\n                index.sequence().begin()\
    \ + left,\n                index.sequence().begin() + right\n            ) ==\
    \ palindrome\n        );\n    }\n\n    Sequence empty;\n    assert(index.find(empty)\
    \ == Tree::null_node);\n    assert(!index.contains(empty));\n    assert(index.order_of_palindrome(empty)\
    \ == -1);\n}\n\nvoid fixed_tests() {\n    using Index = m1une::string::PalindromeLexicographicalOrder<>;\n\
    \    Index empty;\n    check_index(empty);\n\n    Index index(std::string(\"abacaba\"\
    ));\n    check_index(index);\n    std::vector<std::string> expected = {\n    \
    \    \"a\", \"aba\", \"abacaba\", \"aca\", \"b\", \"bacab\", \"c\"\n    };\n \
    \   assert(naive_palindromes(index.sequence()) == expected);\n    assert(index.order_of_palindrome(std::string(\"\
    aca\")) == 3);\n    assert(index.order_of_palindrome(std::string(\"aa\")) == -1);\n\
    \    assert(index.order_of_palindrome(std::string(\"abc\")) == -1);\n    assert(!index.contains(std::string(\"\
    aa\")));\n    assert(!index.contains(std::string(\"abc\")));\n\n    Index moved(std::string(\"\
    aaaaa\"));\n    check_index(moved);\n    for (int length = 1; length <= 5; length++)\
    \ {\n        assert(moved.palindrome(length - 1) == std::string(length, 'a'));\n\
    \    }\n\n    using IntegerIndex =\n        m1une::string::PalindromeLexicographicalOrder<std::vector<int>,\
    \ 4, 0>;\n    std::vector<int> values;\n    values.push_back(2);\n    values.push_back(1);\n\
    \    values.push_back(2);\n    values.push_back(0);\n    values.push_back(2);\n\
    \    values.push_back(1);\n    values.push_back(2);\n    IntegerIndex integer_index(values);\n\
    \    check_index(integer_index);\n}\n\nvoid exhaustive_tests() {\n    for (int\
    \ length = 0; length <= 8; length++) {\n        std::uint64_t count = 1;\n   \
    \     for (int i = 0; i < length; i++) count *= 3;\n        for (std::uint64_t\
    \ code = 0; code < count; code++) {\n            std::uint64_t value = code;\n\
    \            std::string text(length, 'a');\n            for (char& character\
    \ : text) {\n                character = char('a' + value % 3);\n            \
    \    value /= 3;\n            }\n            check_index(\n                m1une::string::PalindromeLexicographicalOrder<\n\
    \                    std::string, 3, 'a'\n                >(std::move(text))\n\
    \            );\n        }\n    }\n}\n\nvoid randomized_tests() {\n    std::uint64_t\
    \ state = 0xf4c3182d9ab760e5ULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1000; trial++) {\n        int length = int(random()\
    \ % 45);\n        std::string text(length, 'a');\n        for (char& character\
    \ : text) {\n            character = char('a' + random() % 4);\n        }\n  \
    \      check_index(\n            m1une::string::PalindromeLexicographicalOrder<\n\
    \                std::string, 4, 'a'\n            >(std::move(text))\n       \
    \ );\n    }\n}\n\nint library_checker_id(int id) {\n    using Tree = m1une::string::Eertree<>;\n\
    \    if (id == Tree::odd_root) return 0;\n    if (id == Tree::even_root) return\
    \ 1;\n    return id;\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    fixed_tests();\n\
    \    exhaustive_tests();\n    randomized_tests();\n\n    std::string text;\n \
    \   fast_input >> text;\n    m1une::string::PalindromeLexicographicalOrder<> index(std::move(text));\n\
    \    const auto& tree = index.eertree();\n\n    std::vector<int> parent(tree.node_count(),\
    \ -1);\n    for (int id = 0; id < tree.node_count(); id++) {\n        const auto&\
    \ node = tree.node(id);\n        for (int symbol = 0; symbol < 26; symbol++) {\n\
    \            int to = node.next[symbol];\n            if (to != m1une::string::Eertree<>::null_node)\
    \ parent[to] = id;\n        }\n    }\n\n    fast_output << tree.size() << '\\\
    n';\n    for (int id = 2; id < tree.node_count(); id++) {\n        fast_output\
    \ << library_checker_id(parent[id]) - 1 << ' '\n                    << library_checker_id(tree.node(id).suffix_link)\
    \ - 1\n                    << '\\n';\n    }\n    const auto& longest_suffix =\
    \ tree.longest_suffix_nodes();\n    for (int i = 0; i < int(longest_suffix.size());\
    \ i++) {\n        if (i) fast_output << ' ';\n        fast_output << longest_suffix[i]\
    \ - 1;\n    }\n    fast_output << '\\n';\n}\n"
  dependsOn:
  - string/palindrome_lexicographical_order.hpp
  - string/eertree.hpp
  - string/suffix_array.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/palindrome_lexicographical_order.test.cpp
  requiredBy: []
  timestamp: '2026-08-26 23:16:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/palindrome_lexicographical_order.test.cpp
layout: document
redirect_from:
- /verify/verify/string/palindrome_lexicographical_order.test.cpp
- /verify/verify/string/palindrome_lexicographical_order.test.cpp.html
title: verify/string/palindrome_lexicographical_order.test.cpp
---
