---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/chmin_chmax.hpp
    title: Chmin Chmax
  - icon: ':heavy_check_mark:'
    path: utilities/compressor.hpp
    title: Compressor
  - icon: ':heavy_check_mark:'
    path: utilities/y_combinator.hpp
    title: Y Combinator
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
  bundledCode: "#line 1 \"verify/utilities/extra_utilities.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <stdexcept>\n#include <vector>\n\nusing namespace std;\n\n#line 1 \"\
    utilities/chmin_chmax.hpp\"\n\n\n\nnamespace m1une {\nnamespace utilities {\n\n\
    template <typename T, typename U>\nbool chmin(T& a, const U& b) {\n    if (b <\
    \ a) {\n        a = b;\n        return true;\n    }\n    return false;\n}\n\n\
    template <typename T, typename U>\nbool chmax(T& a, const U& b) {\n    if (a <\
    \ b) {\n        a = b;\n        return true;\n    }\n    return false;\n}\n\n\
    }  // namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/compressor.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <initializer_list>\n#line 7 \"utilities/compressor.hpp\"\
    \n#include <utility>\n#line 9 \"utilities/compressor.hpp\"\n\nnamespace m1une\
    \ {\nnamespace utilities {\n\ntemplate <typename T>\nstruct Compressor {\n   private:\n\
    \    std::vector<T> _values;\n\n   public:\n    Compressor() = default;\n\n  \
    \  explicit Compressor(std::vector<T> values) : _values(std::move(values)) {\n\
    \        build();\n    }\n\n    Compressor(std::initializer_list<T> values) :\
    \ _values(values) {\n        build();\n    }\n\n    template <typename Iterator>\n\
    \    Compressor(Iterator first, Iterator last) : _values(first, last) {\n    \
    \    build();\n    }\n\n    void add(const T& value) {\n        _values.push_back(value);\n\
    \    }\n\n    void build() {\n        std::sort(_values.begin(), _values.end());\n\
    \        _values.erase(std::unique(_values.begin(), _values.end()), _values.end());\n\
    \    }\n\n    int get(const T& value) const {\n        auto it = std::lower_bound(_values.begin(),\
    \ _values.end(), value);\n        if (it == _values.end() || *it != value) {\n\
    \            throw std::out_of_range(\"value is not contained in Compressor\"\
    );\n        }\n        return static_cast<int>(it - _values.begin());\n    }\n\
    \n    int lower_bound(const T& value) const {\n        return static_cast<int>(std::lower_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    int upper_bound(const\
    \ T& value) const {\n        return static_cast<int>(std::upper_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    bool contains(const\
    \ T& value) const {\n        auto it = std::lower_bound(_values.begin(), _values.end(),\
    \ value);\n        return it != _values.end() && *it == value;\n    }\n\n    const\
    \ T& operator[](int index) const {\n        return _values.at(index);\n    }\n\
    \n    const std::vector<T>& values() const {\n        return _values;\n    }\n\
    \n    int size() const {\n        return static_cast<int>(_values.size());\n \
    \   }\n\n    bool empty() const {\n        return _values.empty();\n    }\n};\n\
    \n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/y_combinator.hpp\"\
    \n\n\n\n#include <type_traits>\n#line 6 \"utilities/y_combinator.hpp\"\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\ntemplate <typename F>\nstruct YCombinator\
    \ {\n   private:\n    F _f;\n\n   public:\n    explicit YCombinator(F&& f) : _f(std::forward<F>(f))\
    \ {}\n\n    template <typename... Args>\n    decltype(auto) operator()(Args&&...\
    \ args) {\n        return _f(*this, std::forward<Args>(args)...);\n    }\n\n \
    \   template <typename... Args>\n    decltype(auto) operator()(Args&&... args)\
    \ const {\n        return _f(*this, std::forward<Args>(args)...);\n    }\n};\n\
    \ntemplate <typename F>\nauto y_combinator(F&& f) {\n    return YCombinator<std::decay_t<F>>(std::forward<F>(f));\n\
    }\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 13 \"verify/utilities/extra_utilities.test.cpp\"\
    \n\nvoid test_chmin_chmax() {\n    int x = 10;\n    assert(m1une::utilities::chmin(x,\
    \ 3));\n    assert(x == 3);\n    assert(!m1une::utilities::chmin(x, 7));\n   \
    \ assert(m1une::utilities::chmax(x, 7));\n    assert(x == 7);\n    assert(!m1une::utilities::chmax(x,\
    \ 4));\n}\n\nvoid test_compressor() {\n    vector<long long> xs = {100, -5, 100,\
    \ 7};\n    m1une::utilities::Compressor<long long> comp(xs);\n\n    assert(comp.size()\
    \ == 3);\n    assert(comp[0] == -5);\n    assert(comp[1] == 7);\n    assert(comp[2]\
    \ == 100);\n    assert(comp.get(100) == 2);\n    assert(comp.lower_bound(8) ==\
    \ 2);\n    assert(comp.upper_bound(7) == 2);\n    assert(comp.contains(-5));\n\
    \    assert(!comp.contains(6));\n\n    m1une::utilities::Compressor<int> incremental;\n\
    \    incremental.add(4);\n    incremental.add(1);\n    incremental.add(4);\n \
    \   incremental.build();\n    assert(incremental.size() == 2);\n    assert(incremental.get(1)\
    \ == 0);\n    assert(incremental.get(4) == 1);\n\n    bool rejected = false;\n\
    \    try {\n        (void)comp.get(6);\n    } catch (const out_of_range&) {\n\
    \        rejected = true;\n    }\n    assert(rejected);\n}\n\nvoid test_y_combinator()\
    \ {\n    auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long\
    \ long {\n        if (n == 0) return 1;\n        return n * self(n - 1);\n   \
    \ });\n    assert(fact(10) == 3628800);\n}\n\nint main() {\n    test_chmin_chmax();\n\
    \    test_compressor();\n    test_y_combinator();\n\n    long long a, b;\n   \
    \ cin >> a >> b;\n    cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <stdexcept>\n#include <vector>\n\nusing namespace\
    \ std;\n\n#include \"../../utilities/chmin_chmax.hpp\"\n#include \"../../utilities/compressor.hpp\"\
    \n#include \"../../utilities/y_combinator.hpp\"\n\nvoid test_chmin_chmax() {\n\
    \    int x = 10;\n    assert(m1une::utilities::chmin(x, 3));\n    assert(x ==\
    \ 3);\n    assert(!m1une::utilities::chmin(x, 7));\n    assert(m1une::utilities::chmax(x,\
    \ 7));\n    assert(x == 7);\n    assert(!m1une::utilities::chmax(x, 4));\n}\n\n\
    void test_compressor() {\n    vector<long long> xs = {100, -5, 100, 7};\n    m1une::utilities::Compressor<long\
    \ long> comp(xs);\n\n    assert(comp.size() == 3);\n    assert(comp[0] == -5);\n\
    \    assert(comp[1] == 7);\n    assert(comp[2] == 100);\n    assert(comp.get(100)\
    \ == 2);\n    assert(comp.lower_bound(8) == 2);\n    assert(comp.upper_bound(7)\
    \ == 2);\n    assert(comp.contains(-5));\n    assert(!comp.contains(6));\n\n \
    \   m1une::utilities::Compressor<int> incremental;\n    incremental.add(4);\n\
    \    incremental.add(1);\n    incremental.add(4);\n    incremental.build();\n\
    \    assert(incremental.size() == 2);\n    assert(incremental.get(1) == 0);\n\
    \    assert(incremental.get(4) == 1);\n\n    bool rejected = false;\n    try {\n\
    \        (void)comp.get(6);\n    } catch (const out_of_range&) {\n        rejected\
    \ = true;\n    }\n    assert(rejected);\n}\n\nvoid test_y_combinator() {\n   \
    \ auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long long\
    \ {\n        if (n == 0) return 1;\n        return n * self(n - 1);\n    });\n\
    \    assert(fact(10) == 3628800);\n}\n\nint main() {\n    test_chmin_chmax();\n\
    \    test_compressor();\n    test_y_combinator();\n\n    long long a, b;\n   \
    \ cin >> a >> b;\n    cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/chmin_chmax.hpp
  - utilities/compressor.hpp
  - utilities/y_combinator.hpp
  isVerificationFile: true
  path: verify/utilities/extra_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/extra_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/extra_utilities.test.cpp
- /verify/verify/utilities/extra_utilities.test.cpp.html
title: verify/utilities/extra_utilities.test.cpp
---
