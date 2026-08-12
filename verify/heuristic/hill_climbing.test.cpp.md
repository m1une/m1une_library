---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: heuristic/hill_climbing.hpp
    title: Hill Climbing
  - icon: ':heavy_check_mark:'
    path: heuristic/objective.hpp
    title: Heuristic Objective
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
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
  bundledCode: "#line 1 \"verify/heuristic/hill_climbing.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <limits>\n\n#line 1 \"heuristic/hill_climbing.hpp\"\n\n\n\n#include <concepts>\n\
    \n#line 1 \"heuristic/objective.hpp\"\n\n\n\nnamespace m1une {\nnamespace heuristic\
    \ {\n\nenum class Objective {\n    minimize,\n    maximize,\n};\n\ntemplate <class\
    \ Score>\nbool better_score(const Score& first, const Score& second,\n       \
    \           Objective objective) {\n    if (objective == Objective::maximize)\
    \ return second < first;\n    return first < second;\n}\n\n}  // namespace heuristic\n\
    }  // namespace m1une\n\n\n#line 7 \"heuristic/hill_climbing.hpp\"\n\nnamespace\
    \ m1une {\nnamespace heuristic {\n\nusing HillClimbingObjective = Objective;\n\
    \nclass HillClimbing {\n   private:\n    Objective _objective;\n    bool _accept_equal;\n\
    \n   public:\n    explicit HillClimbing(Objective objective = Objective::maximize,\n\
    \                          bool accept_equal = false)\n        : _objective(objective),\
    \ _accept_equal(accept_equal) {}\n\n    bool accept_delta(long double candidate_minus_current)\
    \ const {\n        if (_objective == Objective::maximize) {\n            return\
    \ _accept_equal ? 0.0L <= candidate_minus_current\n                          \
    \       : 0.0L < candidate_minus_current;\n        }\n        return _accept_equal\
    \ ? candidate_minus_current <= 0.0L\n                             : candidate_minus_current\
    \ < 0.0L;\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    bool accept(CurrentScore\
    \ current_score,\n                CandidateScore candidate_score) const {\n  \
    \      long double delta = static_cast<long double>(candidate_score) -\n     \
    \                       static_cast<long double>(current_score);\n        return\
    \ accept_delta(delta);\n    }\n};\n\n}  // namespace heuristic\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/random.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 6 \"utilities/random.hpp\"\n#include <chrono>\n#line 8 \"utilities/random.hpp\"\
    \n#include <cstdint>\n#include <functional>\n#include <numeric>\n#include <queue>\n\
    #include <random>\n#include <string>\n#include <string_view>\n#include <tuple>\n\
    #include <type_traits>\n#include <unordered_set>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace utilities {\n\nstruct RandomGraphOptions\
    \ {\n    bool directed = false;\n    bool allow_self_loops = false;\n    bool\
    \ allow_parallel_edges = false;\n};\n\nstruct Random {\n   private:\n    std::mt19937_64\
    \ _engine;\n\n    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
    \ long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    }\n\n    static std::uint64_t graph_edge_count(int vertex_count,\n      \
    \                                    const RandomGraphOptions& options) {\n  \
    \      std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if\
    \ (options.directed) {\n            return options.allow_self_loops ? n * n :\
    \ n * (n - 1);\n        }\n        return options.allow_self_loops ? n * (n +\
    \ 1) / 2 : n * (n - 1) / 2;\n    }\n\n    static std::pair<int, int> decode_graph_edge(\n\
    \        std::uint64_t index, int vertex_count,\n        const RandomGraphOptions&\
    \ options) {\n        std::uint64_t n = static_cast<unsigned int>(vertex_count);\n\
    \        if (options.directed) {\n            std::uint64_t width = options.allow_self_loops\
    \ ? n : n - 1;\n            int from = int(index / width);\n            int offset\
    \ = int(index % width);\n            int to = options.allow_self_loops || offset\
    \ < from ? offset : offset + 1;\n            return {from, to};\n        }\n\n\
    \        auto prefix = [&](std::uint64_t vertex) {\n            if (options.allow_self_loops)\
    \ {\n                return vertex * (2 * n - vertex + 1) / 2;\n            }\n\
    \            return vertex * (2 * n - vertex - 1) / 2;\n        };\n        std::uint64_t\
    \ low = 0;\n        std::uint64_t high = n;\n        while (low + 1 < high) {\n\
    \            std::uint64_t middle = (low + high) / 2;\n            if (prefix(middle)\
    \ <= index) {\n                low = middle;\n            } else {\n         \
    \       high = middle;\n            }\n        }\n        int from = int(low);\n\
    \        int to = from + int(index - prefix(low)) +\n                 (options.allow_self_loops\
    \ ? 0 : 1);\n        return {from, to};\n    }\n\n   public:\n    Random() : _engine(chrono_seed())\
    \ {}\n    explicit Random(unsigned long long seed) : _engine(seed) {}\n\n    void\
    \ seed(unsigned long long value) {\n        _engine.seed(value);\n    }\n\n  \
    \  std::mt19937_64& engine() {\n        return _engine;\n    }\n\n    unsigned\
    \ long long operator()() {\n        return _engine();\n    }\n\n    long long\
    \ uniform(long long l, long long r) {\n        return std::uniform_int_distribution<long\
    \ long>(l, r)(_engine);\n    }\n\n    unsigned long long uniform_unsigned(unsigned\
    \ long long l, unsigned long long r) {\n        return std::uniform_int_distribution<unsigned\
    \ long long>(l, r)(_engine);\n    }\n\n    double real(double l = 0.0, double\
    \ r = 1.0) {\n        return std::uniform_real_distribution<double>(l, r)(_engine);\n\
    \    }\n\n    template <std::integral T>\n    requires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\n    std::vector<T> sequence(int size, T lower, T upper) {\n        assert(0\
    \ <= size);\n        assert(lower <= upper);\n        if (size < 0 || upper <\
    \ lower) return {};\n        std::vector<T> result(size);\n        if constexpr\
    \ (std::signed_integral<T>) {\n            std::uniform_int_distribution<long\
    \ long> distribution(\n                static_cast<long long>(lower), static_cast<long\
    \ long>(upper));\n            for (T& value : result) value = static_cast<T>(distribution(_engine));\n\
    \        } else {\n            std::uniform_int_distribution<unsigned long long>\
    \ distribution(\n                static_cast<unsigned long long>(lower),\n   \
    \             static_cast<unsigned long long>(upper));\n            for (T& value\
    \ : result) value = static_cast<T>(distribution(_engine));\n        }\n      \
    \  return result;\n    }\n\n    std::string string(\n        int length,\n   \
    \     std::string_view alphabet = \"abcdefghijklmnopqrstuvwxyz\") {\n        assert(0\
    \ <= length);\n        assert(length == 0 || !alphabet.empty());\n        if (length\
    \ < 0 || (0 < length && alphabet.empty())) return {};\n        std::string result(length,\
    \ '\\0');\n        for (char& character : result) {\n            character = alphabet[uniform(0,\
    \ int(alphabet.size()) - 1)];\n        }\n        return result;\n    }\n\n  \
    \  std::vector<int> permutation(int size, int first = 0) {\n        assert(0 <=\
    \ size);\n        if (size < 0) return {};\n        std::vector<int> result(size);\n\
    \        std::iota(result.begin(), result.end(), first);\n        shuffle(result);\n\
    \        return result;\n    }\n\n    // Returns the edges of a uniformly random\
    \ labeled tree on [0, size).\n    std::vector<std::pair<int, int>> tree(int size)\
    \ {\n        assert(0 <= size);\n        if (size <= 1) return {};\n\n       \
    \ std::vector<int> prufer = sequence(size - 2, 0, size - 1);\n        std::vector<int>\
    \ degree(size, 1);\n        for (int vertex : prufer) degree[vertex]++;\n    \
    \    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;\n \
    \       for (int vertex = 0; vertex < size; vertex++) {\n            if (degree[vertex]\
    \ == 1) leaves.push(vertex);\n        }\n\n        std::vector<std::pair<int,\
    \ int>> edges;\n        edges.reserve(size - 1);\n        for (int vertex : prufer)\
    \ {\n            int leaf = leaves.top();\n            leaves.pop();\n       \
    \     edges.emplace_back(leaf, vertex);\n            if (--degree[vertex] == 1)\
    \ leaves.push(vertex);\n        }\n        int first = leaves.top();\n       \
    \ leaves.pop();\n        edges.emplace_back(first, leaves.top());\n\n        shuffle(edges);\n\
    \        for (auto& [from, to] : edges) {\n            if (uniform(0, 1)) std::swap(from,\
    \ to);\n        }\n        return edges;\n    }\n\n    // Returns m random edges\
    \ on [0, vertex_count). By default the result is\n    // a simple undirected graph\
    \ without self-loops.\n    std::vector<std::pair<int, int>> graph(\n        int\
    \ vertex_count, int edge_count,\n        RandomGraphOptions options = {}) {\n\
    \        assert(0 <= vertex_count);\n        assert(0 <= edge_count);\n      \
    \  if (vertex_count < 0 || edge_count < 0) return {};\n        if (edge_count\
    \ == 0) return {};\n        assert(0 < vertex_count);\n        if (vertex_count\
    \ == 0) return {};\n        if (!options.allow_self_loops) {\n            assert(2\
    \ <= vertex_count || edge_count == 0);\n            if (vertex_count < 2) return\
    \ {};\n        }\n\n        std::vector<std::pair<int, int>> edges;\n        edges.reserve(edge_count);\n\
    \        if (options.allow_parallel_edges) {\n            for (int edge = 0; edge\
    \ < edge_count; edge++) {\n                int from = int(uniform(0, vertex_count\
    \ - 1));\n                int to;\n                if (options.allow_self_loops)\
    \ {\n                    to = int(uniform(0, vertex_count - 1));\n           \
    \     } else {\n                    to = int(uniform(0, vertex_count - 2));\n\
    \                    if (from <= to) to++;\n                }\n              \
    \  if (!options.directed && to < from) std::swap(from, to);\n                edges.emplace_back(from,\
    \ to);\n            }\n            return edges;\n        }\n\n        std::uint64_t\
    \ maximum = graph_edge_count(vertex_count, options);\n        assert(static_cast<std::uint64_t>(edge_count)\
    \ <= maximum);\n        if (maximum < static_cast<std::uint64_t>(edge_count))\
    \ return {};\n\n        std::unordered_set<std::uint64_t> selected;\n        selected.reserve(static_cast<std::size_t>(edge_count)\
    \ * 2 + 1);\n        std::vector<std::uint64_t> indices;\n        indices.reserve(edge_count);\n\
    \        for (std::uint64_t current = maximum - edge_count;\n             current\
    \ < maximum; current++) {\n            std::uint64_t candidate = uniform_unsigned(0,\
    \ current);\n            if (selected.contains(candidate)) candidate = current;\n\
    \            selected.insert(candidate);\n            indices.push_back(candidate);\n\
    \        }\n        for (std::uint64_t index : indices) {\n            edges.push_back(decode_graph_edge(index,\
    \ vertex_count, options));\n        }\n        return edges;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> directed_graph(\n        int vertex_count, int edge_count,\n        bool\
    \ allow_self_loops = false) {\n        RandomGraphOptions options;\n        options.allow_self_loops\
    \ = allow_self_loops;\n        return directed_graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    std::vector<std::pair<int, int>> directed_graph(\n \
    \       int vertex_count, int edge_count, RandomGraphOptions options) {\n    \
    \    options.directed = true;\n        return graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    // Returns a directed acyclic graph. Vertices are randomly\
    \ permuted before\n    // every sampled edge is directed forward in that topological\
    \ order.\n    std::vector<std::pair<int, int>> dag(\n        int vertex_count,\
    \ int edge_count,\n        RandomGraphOptions options = {}) {\n        options.directed\
    \ = false;\n        options.allow_self_loops = false;\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<int> order = permutation(vertex_count);\n        for (auto& [from,\
    \ to] : edges) {\n            from = order[from];\n            to = order[to];\n\
    \        }\n        return edges;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_tree(\n        int size, Weight lower, Weight upper)\
    \ {\n        std::vector<std::pair<int, int>> edges = tree(size);\n        std::vector<Weight>\
    \ weights = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_graph(\n        int vertex_count, int edge_count, Weight\
    \ lower, Weight upper,\n        RandomGraphOptions options = {}) {\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);\n\
    \        std::vector<std::tuple<int, int, Weight>> result;\n        result.reserve(edges.size());\n\
    \        for (int index = 0; index < int(edges.size()); index++) {\n         \
    \   result.emplace_back(edges[index].first, edges[index].second,\n           \
    \                     weights[index]);\n        }\n        return result;\n  \
    \  }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   bool allow_self_loops = false) {\n        RandomGraphOptions options;\n  \
    \      options.allow_self_loops = allow_self_loops;\n        return weighted_directed_graph(vertex_count,\
    \ edge_count, lower, upper,\n                                       options);\n\
    \    }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   RandomGraphOptions options) {\n        options.directed = true;\n        return\
    \ weighted_graph(vertex_count, edge_count, lower, upper, options);\n    }\n\n\
    \    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_dag(\n      \
    \  int vertex_count, int edge_count, Weight lower, Weight upper,\n        RandomGraphOptions\
    \ options = {}) {\n        std::vector<std::pair<int, int>> edges =\n        \
    \    dag(vertex_count, edge_count, options);\n        std::vector<Weight> weights\
    \ = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <typename T>\n    void\
    \ shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(), v.end(), _engine);\n\
    \    }\n\n    template <typename Iterator>\n    void shuffle(Iterator first, Iterator\
    \ last) {\n        std::shuffle(first, last, _engine);\n    }\n\n    template\
    \ <typename T>\n    const T& choice(const std::vector<T>& v) {\n        return\
    \ v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/heuristic/hill_climbing.test.cpp\"\
    \n\nusing m1une::heuristic::HillClimbing;\nusing m1une::heuristic::Objective;\n\
    \nvoid test_basic() {\n    HillClimbing maximize;\n    assert(maximize.accept(10,\
    \ 11));\n    assert(!maximize.accept(10, 10));\n    assert(!maximize.accept(10,\
    \ 9));\n\n    HillClimbing maximize_equal(Objective::maximize, true);\n    assert(maximize_equal.accept_delta(1.0));\n\
    \    assert(maximize_equal.accept_delta(0.0));\n    assert(!maximize_equal.accept_delta(-1.0));\n\
    \n    HillClimbing minimize(Objective::minimize);\n    assert(minimize.accept(10,\
    \ 9));\n    assert(!minimize.accept(10, 10));\n    assert(!minimize.accept(10,\
    \ 11));\n\n    HillClimbing minimize_equal(Objective::minimize, true);\n    assert(minimize_equal.accept_delta(-1.0));\n\
    \    assert(minimize_equal.accept_delta(0.0));\n    assert(!minimize_equal.accept_delta(1.0));\n\
    }\n\nvoid test_extreme_scores() {\n    long long low = std::numeric_limits<long\
    \ long>::min();\n    long long high = std::numeric_limits<long long>::max();\n\
    \    assert(HillClimbing(Objective::maximize).accept(low, high));\n    assert(HillClimbing(Objective::minimize).accept(high,\
    \ low));\n}\n\nvoid test_randomized() {\n    m1une::utilities::Random random(0xc11ab1eULL);\n\
    \    for (bool accept_equal : {false, true}) {\n        for (int trial = 0; trial\
    \ < 20000; trial++) {\n            long long current = random.uniform(-1000, 1000);\n\
    \            long long candidate = random.uniform(-1000, 1000);\n            HillClimbing\
    \ maximize(Objective::maximize, accept_equal);\n            HillClimbing minimize(Objective::minimize,\
    \ accept_equal);\n            assert(maximize.accept(current, candidate) ==\n\
    \                   (accept_equal ? current <= candidate : current < candidate));\n\
    \            assert(minimize.accept(current, candidate) ==\n                 \
    \  (accept_equal ? candidate <= current : candidate < current));\n        }\n\
    \    }\n}\n\nint main() {\n    test_basic();\n    test_extreme_scores();\n   \
    \ test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <limits>\n\n#include \"../../heuristic/hill_climbing.hpp\"\
    \n#include \"../../utilities/random.hpp\"\n\nusing m1une::heuristic::HillClimbing;\n\
    using m1une::heuristic::Objective;\n\nvoid test_basic() {\n    HillClimbing maximize;\n\
    \    assert(maximize.accept(10, 11));\n    assert(!maximize.accept(10, 10));\n\
    \    assert(!maximize.accept(10, 9));\n\n    HillClimbing maximize_equal(Objective::maximize,\
    \ true);\n    assert(maximize_equal.accept_delta(1.0));\n    assert(maximize_equal.accept_delta(0.0));\n\
    \    assert(!maximize_equal.accept_delta(-1.0));\n\n    HillClimbing minimize(Objective::minimize);\n\
    \    assert(minimize.accept(10, 9));\n    assert(!minimize.accept(10, 10));\n\
    \    assert(!minimize.accept(10, 11));\n\n    HillClimbing minimize_equal(Objective::minimize,\
    \ true);\n    assert(minimize_equal.accept_delta(-1.0));\n    assert(minimize_equal.accept_delta(0.0));\n\
    \    assert(!minimize_equal.accept_delta(1.0));\n}\n\nvoid test_extreme_scores()\
    \ {\n    long long low = std::numeric_limits<long long>::min();\n    long long\
    \ high = std::numeric_limits<long long>::max();\n    assert(HillClimbing(Objective::maximize).accept(low,\
    \ high));\n    assert(HillClimbing(Objective::minimize).accept(high, low));\n\
    }\n\nvoid test_randomized() {\n    m1une::utilities::Random random(0xc11ab1eULL);\n\
    \    for (bool accept_equal : {false, true}) {\n        for (int trial = 0; trial\
    \ < 20000; trial++) {\n            long long current = random.uniform(-1000, 1000);\n\
    \            long long candidate = random.uniform(-1000, 1000);\n            HillClimbing\
    \ maximize(Objective::maximize, accept_equal);\n            HillClimbing minimize(Objective::minimize,\
    \ accept_equal);\n            assert(maximize.accept(current, candidate) ==\n\
    \                   (accept_equal ? current <= candidate : current < candidate));\n\
    \            assert(minimize.accept(current, candidate) ==\n                 \
    \  (accept_equal ? candidate <= current : candidate < current));\n        }\n\
    \    }\n}\n\nint main() {\n    test_basic();\n    test_extreme_scores();\n   \
    \ test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - heuristic/hill_climbing.hpp
  - heuristic/objective.hpp
  - utilities/random.hpp
  isVerificationFile: true
  path: verify/heuristic/hill_climbing.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/heuristic/hill_climbing.test.cpp
layout: document
redirect_from:
- /verify/verify/heuristic/hill_climbing.test.cpp
- /verify/verify/heuristic/hill_climbing.test.cpp.html
title: verify/heuristic/hill_climbing.test.cpp
---
