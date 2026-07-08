---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_extension.hpp
    title: Longest Common Extension
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/longest_common_substring
    links:
    - https://judge.yosupo.jp/problem/longest_common_substring
  bundledCode: "#line 1 \"verify/string/longest_common_extension.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\n\n#line\
    \ 1 \"string/longest_common_extension.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <string>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"string/suffix_array.hpp\"\n\n\n\n#line 6 \"string/suffix_array.hpp\"\n#include\
    \ <numeric>\n#line 8 \"string/suffix_array.hpp\"\n#include <type_traits>\n#line\
    \ 10 \"string/suffix_array.hpp\"\n\nnamespace m1une {\nnamespace string {\nnamespace\
    \ detail {\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array_impl(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    if (n == 0) return\
    \ {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
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
    \ // namespace m1une\n\n\n#line 4 \"verify/string/longest_common_extension.test.cpp\"\
    \n\n#line 7 \"verify/string/longest_common_extension.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 11 \"verify/string/longest_common_extension.test.cpp\"\
    \n\nnamespace {\n\nint naive_longest_common_extension(const std::string& text,\
    \ int i, int j) {\n    int n = int(text.size());\n    int result = 0;\n    while\
    \ (i + result < n && j + result < n && text[i + result] == text[j + result]) {\n\
    \        result++;\n    }\n    return result;\n}\n\nint sign(int value) {\n  \
    \  if (value < 0) return -1;\n    if (value > 0) return 1;\n    return 0;\n}\n\
    \nvoid test_fixed() {\n    std::string empty;\n    m1une::string::LongestCommonExtension<>\
    \ empty_extension(empty);\n    assert(empty_extension.empty());\n    assert(empty_extension.longest_common_extension(0,\
    \ 0) == 0);\n    assert(empty_extension.compare_suffix(0, 0) == 0);\n    assert(empty_extension.compare(0,\
    \ 0, 0, 0) == 0);\n    assert(empty_extension.suffix_array().empty());\n    assert(empty_extension.rank().empty());\n\
    \    assert(empty_extension.lcp_array().empty());\n\n    std::string text = \"\
    banana\";\n    m1une::string::LongestCommonExtension<> extension(text);\n    assert(extension.size()\
    \ == 6);\n    assert(extension.sequence() == text);\n    assert(extension.longest_common_extension(1,\
    \ 3) == 3);\n    assert(extension.longest_common_extension(2, 4) == 2);\n    assert(extension.longest_common_extension(0,\
    \ 2) == 0);\n    assert(extension.longest_common_extension(6, 1) == 0);\n    assert(extension.longest_common_extension(2,\
    \ 2) == 4);\n    assert(extension.longest_common_extension(1, 3, 2) == 2);\n \
    \   assert(extension.lcp(1, 3) == 3);\n    assert(extension(1, 3) == 3);\n   \
    \ assert(extension.compare_suffix(1, 3) == 1);\n    assert(extension.compare_suffix(3,\
    \ 1) == -1);\n    assert(extension.compare(1, 4, 3, 6) == 0);\n    assert(extension.compare(1,\
    \ 5, 3, 6) == 1);\n    assert(extension.compare(0, 0, 1, 2) == -1);\n\n    std::vector<int>\
    \ values;\n    values.push_back(2);\n    values.push_back(1);\n    values.push_back(2);\n\
    \    values.push_back(1);\n    values.push_back(2);\n    m1une::string::LongestCommonExtension<std::vector<int>>\
    \ vector_extension(values);\n    assert(vector_extension.longest_common_extension(0,\
    \ 2) == 3);\n    assert(vector_extension.longest_common_extension(1, 3) == 2);\n\
    \    assert(vector_extension.compare(0, 3, 2, 5) == 0);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20240709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1500; trial++) {\n        int n = int(random()\
    \ % 50);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 5);\n        m1une::string::LongestCommonExtension<>\
    \ extension(text);\n\n        const std::vector<int>& suffixes = extension.suffix_array();\n\
    \        const std::vector<int>& rank = extension.rank();\n        for (int i\
    \ = 0; i < n; i++) {\n            assert(0 <= suffixes[i] && suffixes[i] < n);\n\
    \            assert(rank[suffixes[i]] == i);\n        }\n\n        for (int i\
    \ = 0; i <= n; i++) {\n            for (int j = 0; j <= n; j++) {\n          \
    \      int expected = naive_longest_common_extension(text, i, j);\n          \
    \      assert(extension.longest_common_extension(i, j) == expected);\n       \
    \         int limit = int(random() % (n + 1));\n                assert(extension.longest_common_extension(i,\
    \ j, limit) == std::min(expected, limit));\n\n                std::string suffix_i\
    \ = text.substr(i);\n                std::string suffix_j = text.substr(j);\n\
    \                assert(extension.compare_suffix(i, j) == sign(suffix_i.compare(suffix_j)));\n\
    \            }\n        }\n\n        for (int query = 0; query < 200; query++)\
    \ {\n            int l1 = int(random() % (n + 1));\n            int r1 = l1 +\
    \ int(random() % (n - l1 + 1));\n            int l2 = int(random() % (n + 1));\n\
    \            int r2 = l2 + int(random() % (n - l2 + 1));\n            std::string\
    \ first = text.substr(l1, r1 - l1);\n            std::string second = text.substr(l2,\
    \ r2 - l2);\n            assert(extension.compare(l1, r1, l2, r2) == sign(first.compare(second)));\n\
    \        }\n    }\n}\n\nstd::vector<int> combine_strings(const std::string& first,\
    \ const std::string& second) {\n    std::vector<int> combined;\n    combined.reserve(first.size()\
    \ + second.size() + 1);\n    for (unsigned char character : first) combined.push_back(int(character)\
    \ + 2);\n    combined.push_back(1);\n    for (unsigned char character : second)\
    \ combined.push_back(int(character) + 2);\n    return combined;\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::string first, second;\n    std::cin >>\
    \ first >> second;\n\n    int n = int(first.size());\n    int m = int(second.size());\n\
    \    std::vector<int> combined = combine_strings(first, second);\n    m1une::string::LongestCommonExtension<std::vector<int>>\
    \ extension(combined);\n\n    int best_first = 0;\n    int best_second = 0;\n\
    \    int best_length = 0;\n    const std::vector<int>& suffixes = extension.suffix_array();\n\
    \    for (int i = 0; i + 1 < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n\
    \        int b = suffixes[i + 1];\n        bool a_first = a < n;\n        bool\
    \ b_first = b < n;\n        bool a_second = n < a;\n        bool b_second = n\
    \ < b;\n        if (a_first == b_first || a_second == b_second) continue;\n  \
    \      if ((!a_first && !a_second) || (!b_first && !b_second)) continue;\n\n \
    \       int first_pos = a_first ? a : b;\n        int second_pos = a_first ? b\
    \ - n - 1 : a - n - 1;\n        int length = extension.longest_common_extension(a,\
    \ b);\n        length = std::min(length, n - first_pos);\n        length = std::min(length,\
    \ m - second_pos);\n        if (length > best_length) {\n            best_length\
    \ = length;\n            best_first = first_pos;\n            best_second = second_pos;\n\
    \        }\n    }\n\n    std::cout << best_first << ' ' << best_first + best_length\
    \ << ' '\n              << best_second << ' ' << best_second + best_length <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\
    \n\n#include \"../../string/longest_common_extension.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <string>\n\
    #include <vector>\n\nnamespace {\n\nint naive_longest_common_extension(const std::string&\
    \ text, int i, int j) {\n    int n = int(text.size());\n    int result = 0;\n\
    \    while (i + result < n && j + result < n && text[i + result] == text[j + result])\
    \ {\n        result++;\n    }\n    return result;\n}\n\nint sign(int value) {\n\
    \    if (value < 0) return -1;\n    if (value > 0) return 1;\n    return 0;\n\
    }\n\nvoid test_fixed() {\n    std::string empty;\n    m1une::string::LongestCommonExtension<>\
    \ empty_extension(empty);\n    assert(empty_extension.empty());\n    assert(empty_extension.longest_common_extension(0,\
    \ 0) == 0);\n    assert(empty_extension.compare_suffix(0, 0) == 0);\n    assert(empty_extension.compare(0,\
    \ 0, 0, 0) == 0);\n    assert(empty_extension.suffix_array().empty());\n    assert(empty_extension.rank().empty());\n\
    \    assert(empty_extension.lcp_array().empty());\n\n    std::string text = \"\
    banana\";\n    m1une::string::LongestCommonExtension<> extension(text);\n    assert(extension.size()\
    \ == 6);\n    assert(extension.sequence() == text);\n    assert(extension.longest_common_extension(1,\
    \ 3) == 3);\n    assert(extension.longest_common_extension(2, 4) == 2);\n    assert(extension.longest_common_extension(0,\
    \ 2) == 0);\n    assert(extension.longest_common_extension(6, 1) == 0);\n    assert(extension.longest_common_extension(2,\
    \ 2) == 4);\n    assert(extension.longest_common_extension(1, 3, 2) == 2);\n \
    \   assert(extension.lcp(1, 3) == 3);\n    assert(extension(1, 3) == 3);\n   \
    \ assert(extension.compare_suffix(1, 3) == 1);\n    assert(extension.compare_suffix(3,\
    \ 1) == -1);\n    assert(extension.compare(1, 4, 3, 6) == 0);\n    assert(extension.compare(1,\
    \ 5, 3, 6) == 1);\n    assert(extension.compare(0, 0, 1, 2) == -1);\n\n    std::vector<int>\
    \ values;\n    values.push_back(2);\n    values.push_back(1);\n    values.push_back(2);\n\
    \    values.push_back(1);\n    values.push_back(2);\n    m1une::string::LongestCommonExtension<std::vector<int>>\
    \ vector_extension(values);\n    assert(vector_extension.longest_common_extension(0,\
    \ 2) == 3);\n    assert(vector_extension.longest_common_extension(1, 3) == 2);\n\
    \    assert(vector_extension.compare(0, 3, 2, 5) == 0);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20240709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1500; trial++) {\n        int n = int(random()\
    \ % 50);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 5);\n        m1une::string::LongestCommonExtension<>\
    \ extension(text);\n\n        const std::vector<int>& suffixes = extension.suffix_array();\n\
    \        const std::vector<int>& rank = extension.rank();\n        for (int i\
    \ = 0; i < n; i++) {\n            assert(0 <= suffixes[i] && suffixes[i] < n);\n\
    \            assert(rank[suffixes[i]] == i);\n        }\n\n        for (int i\
    \ = 0; i <= n; i++) {\n            for (int j = 0; j <= n; j++) {\n          \
    \      int expected = naive_longest_common_extension(text, i, j);\n          \
    \      assert(extension.longest_common_extension(i, j) == expected);\n       \
    \         int limit = int(random() % (n + 1));\n                assert(extension.longest_common_extension(i,\
    \ j, limit) == std::min(expected, limit));\n\n                std::string suffix_i\
    \ = text.substr(i);\n                std::string suffix_j = text.substr(j);\n\
    \                assert(extension.compare_suffix(i, j) == sign(suffix_i.compare(suffix_j)));\n\
    \            }\n        }\n\n        for (int query = 0; query < 200; query++)\
    \ {\n            int l1 = int(random() % (n + 1));\n            int r1 = l1 +\
    \ int(random() % (n - l1 + 1));\n            int l2 = int(random() % (n + 1));\n\
    \            int r2 = l2 + int(random() % (n - l2 + 1));\n            std::string\
    \ first = text.substr(l1, r1 - l1);\n            std::string second = text.substr(l2,\
    \ r2 - l2);\n            assert(extension.compare(l1, r1, l2, r2) == sign(first.compare(second)));\n\
    \        }\n    }\n}\n\nstd::vector<int> combine_strings(const std::string& first,\
    \ const std::string& second) {\n    std::vector<int> combined;\n    combined.reserve(first.size()\
    \ + second.size() + 1);\n    for (unsigned char character : first) combined.push_back(int(character)\
    \ + 2);\n    combined.push_back(1);\n    for (unsigned char character : second)\
    \ combined.push_back(int(character) + 2);\n    return combined;\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::string first, second;\n    std::cin >>\
    \ first >> second;\n\n    int n = int(first.size());\n    int m = int(second.size());\n\
    \    std::vector<int> combined = combine_strings(first, second);\n    m1une::string::LongestCommonExtension<std::vector<int>>\
    \ extension(combined);\n\n    int best_first = 0;\n    int best_second = 0;\n\
    \    int best_length = 0;\n    const std::vector<int>& suffixes = extension.suffix_array();\n\
    \    for (int i = 0; i + 1 < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n\
    \        int b = suffixes[i + 1];\n        bool a_first = a < n;\n        bool\
    \ b_first = b < n;\n        bool a_second = n < a;\n        bool b_second = n\
    \ < b;\n        if (a_first == b_first || a_second == b_second) continue;\n  \
    \      if ((!a_first && !a_second) || (!b_first && !b_second)) continue;\n\n \
    \       int first_pos = a_first ? a : b;\n        int second_pos = a_first ? b\
    \ - n - 1 : a - n - 1;\n        int length = extension.longest_common_extension(a,\
    \ b);\n        length = std::min(length, n - first_pos);\n        length = std::min(length,\
    \ m - second_pos);\n        if (length > best_length) {\n            best_length\
    \ = length;\n            best_first = first_pos;\n            best_second = second_pos;\n\
    \        }\n    }\n\n    std::cout << best_first << ' ' << best_first + best_length\
    \ << ' '\n              << best_second << ' ' << best_second + best_length <<\
    \ '\\n';\n}\n"
  dependsOn:
  - string/longest_common_extension.hpp
  - string/suffix_array.hpp
  isVerificationFile: true
  path: verify/string/longest_common_extension.test.cpp
  requiredBy: []
  timestamp: '2026-07-09 02:40:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/longest_common_extension.test.cpp
layout: document
redirect_from:
- /verify/verify/string/longest_common_extension.test.cpp
- /verify/verify/string/longest_common_extension.test.cpp.html
title: verify/string/longest_common_extension.test.cpp
---
