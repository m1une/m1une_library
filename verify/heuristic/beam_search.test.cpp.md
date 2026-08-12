---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: heuristic/beam_search.hpp
    title: Beam Search
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
  bundledCode: "#line 1 \"verify/heuristic/beam_search.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <memory>\n#include <string>\n#include <utility>\n#include <vector>\n\n\
    #line 1 \"heuristic/beam_search.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"\
    heuristic/beam_search.hpp\"\n#include <concepts>\n#include <cstddef>\n#include\
    \ <functional>\n#include <type_traits>\n#line 12 \"heuristic/beam_search.hpp\"\
    \n\n#line 1 \"heuristic/objective.hpp\"\n\n\n\nnamespace m1une {\nnamespace heuristic\
    \ {\n\nenum class Objective {\n    minimize,\n    maximize,\n};\n\ntemplate <class\
    \ Score>\nbool better_score(const Score& first, const Score& second,\n       \
    \           Objective objective) {\n    if (objective == Objective::maximize)\
    \ return second < first;\n    return first < second;\n}\n\n}  // namespace heuristic\n\
    }  // namespace m1une\n\n\n#line 14 \"heuristic/beam_search.hpp\"\n\nnamespace\
    \ m1une {\nnamespace heuristic {\n\ntemplate <class State, class Score>\nstruct\
    \ BeamSearchResult {\n    State state;\n    Score score;\n    int depth;\n   \
    \ std::size_t expanded_states;\n    std::size_t generated_states;\n};\n\nnamespace\
    \ beam_search_detail {\n\ntemplate <class State, class Score>\nstruct Node {\n\
    \    State state;\n    Score score;\n    std::size_t order;\n};\n\ntemplate <class\
    \ State, class Score>\nstruct BetterNode {\n    Objective objective;\n\n    bool\
    \ operator()(const Node<State, Score>& first,\n                    const Node<State,\
    \ Score>& second) const {\n        if (better_score(first.score, second.score,\
    \ objective)) return true;\n        if (better_score(second.score, first.score,\
    \ objective)) return false;\n        return first.order < second.order;\n    }\n\
    };\n\n}  // namespace beam_search_detail\n\n// expand(state, next_depth) may return\
    \ a range of children. For allocation-free\n// generation, expand(state, next_depth,\
    \ emit) may instead call emit(child).\n// evaluate(state) returns its score. The\
    \ best beam_width states are retained at\n// every depth, and the best state in\
    \ the last non-empty layer is returned.\ntemplate <class State, class Expand,\
    \ class Evaluate>\nauto beam_search(State initial_state, int depth_limit, int\
    \ beam_width,\n                 Expand expand, Evaluate evaluate,\n          \
    \       Objective objective = Objective::maximize) {\n    assert(0 <= depth_limit);\n\
    \    assert(0 < beam_width);\n\n    using Score = std::remove_cvref_t<\n     \
    \   std::invoke_result_t<Evaluate&, const State&>>;\n    using Node = beam_search_detail::Node<State,\
    \ Score>;\n    using Better = beam_search_detail::BetterNode<State, Score>;\n\n\
    \    Score initial_score = std::invoke(evaluate, initial_state);\n    std::vector<Node>\
    \ beam;\n    beam.push_back(Node{std::move(initial_state),\n                 \
    \       std::move(initial_score), 0});\n\n    std::size_t expanded_states = 0;\n\
    \    std::size_t generated_states = 0;\n    int reached_depth = 0;\n    if (depth_limit\
    \ < 0 || beam_width <= 0) depth_limit = 0;\n\n    Better better{objective};\n\
    \    for (int next_depth = 1; next_depth <= depth_limit; next_depth++) {\n   \
    \     std::vector<Node> candidates;\n        candidates.reserve(static_cast<std::size_t>(beam_width));\n\
    \        std::size_t order = 0;\n\n        for (const Node& node : beam) {\n \
    \           expanded_states++;\n            auto emit = [&](auto&& candidate_state)\
    \ {\n                using Candidate = decltype(candidate_state);\n          \
    \      static_assert(std::is_constructible_v<State, Candidate>);\n           \
    \     State state(std::forward<Candidate>(candidate_state));\n               \
    \ Score candidate_score = std::invoke(evaluate, state);\n                Node\
    \ candidate{std::move(state), std::move(candidate_score),\n                  \
    \             order++};\n                generated_states++;\n               \
    \ if (int(candidates.size()) < beam_width) {\n                    candidates.push_back(std::move(candidate));\n\
    \                    std::push_heap(candidates.begin(), candidates.end(), better);\n\
    \                } else if (better(candidate, candidates.front())) {\n       \
    \             std::pop_heap(candidates.begin(), candidates.end(), better);\n \
    \                   candidates.back() = std::move(candidate);\n              \
    \      std::push_heap(candidates.begin(), candidates.end(), better);\n       \
    \         }\n            };\n            if constexpr (std::invocable<Expand&,\
    \ const State&, int>) {\n                auto next_states =\n                \
    \    std::invoke(expand, node.state, next_depth);\n                for (auto&\
    \ candidate_state : next_states) {\n                    emit(std::move(candidate_state));\n\
    \                }\n            } else if constexpr (std::invocable<Expand&, const\
    \ State&>) {\n                auto next_states = std::invoke(expand, node.state);\n\
    \                for (auto& candidate_state : next_states) {\n               \
    \     emit(std::move(candidate_state));\n                }\n            } else\
    \ {\n                std::invoke(expand, node.state, next_depth, emit);\n    \
    \        }\n        }\n\n        if (candidates.empty()) break;\n        beam\
    \ = std::move(candidates);\n        reached_depth = next_depth;\n    }\n\n   \
    \ int best = 0;\n    for (int index = 1; index < int(beam.size()); index++) {\n\
    \        if (better(beam[index], beam[best])) best = index;\n    }\n    return\
    \ BeamSearchResult<State, Score>{\n        std::move(beam[best].state), std::move(beam[best].score),\n\
    \        reached_depth, expanded_states, generated_states};\n}\n\n}  // namespace\
    \ heuristic\n}  // namespace m1une\n\n\n#line 1 \"utilities/random.hpp\"\n\n\n\
    \n#line 6 \"utilities/random.hpp\"\n#include <chrono>\n#line 8 \"utilities/random.hpp\"\
    \n#include <cstdint>\n#line 10 \"utilities/random.hpp\"\n#include <numeric>\n\
    #include <queue>\n#include <random>\n#line 14 \"utilities/random.hpp\"\n#include\
    \ <string_view>\n#include <tuple>\n#line 17 \"utilities/random.hpp\"\n#include\
    \ <unordered_set>\n#line 20 \"utilities/random.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\nstruct RandomGraphOptions {\n    bool directed = false;\n   \
    \ bool allow_self_loops = false;\n    bool allow_parallel_edges = false;\n};\n\
    \nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\n    static unsigned\
    \ long long chrono_seed() {\n        return static_cast<unsigned long long>(\n\
    \            std::chrono::steady_clock::now().time_since_epoch().count());\n \
    \   }\n\n    static std::uint64_t graph_edge_count(int vertex_count,\n       \
    \                                   const RandomGraphOptions& options) {\n   \
    \     std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if (options.directed)\
    \ {\n            return options.allow_self_loops ? n * n : n * (n - 1);\n    \
    \    }\n        return options.allow_self_loops ? n * (n + 1) / 2 : n * (n - 1)\
    \ / 2;\n    }\n\n    static std::pair<int, int> decode_graph_edge(\n        std::uint64_t\
    \ index, int vertex_count,\n        const RandomGraphOptions& options) {\n   \
    \     std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if (options.directed)\
    \ {\n            std::uint64_t width = options.allow_self_loops ? n : n - 1;\n\
    \            int from = int(index / width);\n            int offset = int(index\
    \ % width);\n            int to = options.allow_self_loops || offset < from ?\
    \ offset : offset + 1;\n            return {from, to};\n        }\n\n        auto\
    \ prefix = [&](std::uint64_t vertex) {\n            if (options.allow_self_loops)\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/heuristic/beam_search.test.cpp\"\
    \n\nusing m1une::heuristic::Objective;\nusing m1une::heuristic::beam_search;\n\
    \nauto digit_expander(int radix) {\n    return [radix](const std::string& state,\
    \ int, auto emit) {\n        for (int digit = 0; digit < radix; digit++) {\n \
    \           std::string candidate = state;\n            candidate.push_back(static_cast<char>('0'\
    \ + digit));\n            emit(std::move(candidate));\n        }\n    };\n}\n\n\
    auto digit_range_expander(int radix) {\n    return [radix](const std::string&\
    \ state, int) {\n        std::vector<std::string> result;\n        result.reserve(radix);\n\
    \        for (int digit = 0; digit < radix; digit++) {\n            result.push_back(state\
    \ + static_cast<char>('0' + digit));\n        }\n        return result;\n    };\n\
    }\n\nint digit_value(const std::string& state) {\n    int result = 0;\n    for\
    \ (char digit : state) result = result * 10 + digit - '0';\n    return result;\n\
    }\n\nvoid test_objectives_and_statistics() {\n    auto maximize = beam_search(std::string(),\
    \ 3, 2, digit_range_expander(3),\n                                digit_value,\
    \ Objective::maximize);\n    assert(maximize.state == \"222\");\n    assert(maximize.score\
    \ == 222);\n    assert(maximize.depth == 3);\n    assert(maximize.expanded_states\
    \ == 5);\n    assert(maximize.generated_states == 15);\n\n    auto minimize =\
    \ beam_search(std::string(), 3, 2, digit_range_expander(3),\n                \
    \                digit_value, Objective::minimize);\n    assert(minimize.state\
    \ == \"000\");\n    assert(minimize.score == 0);\n}\n\nvoid test_early_stop_and_zero_depth()\
    \ {\n    auto expand_once = [](const int& state, int depth, auto emit) {\n   \
    \     if (depth == 1) {\n            emit(state + 3);\n            emit(state\
    \ + 5);\n        }\n    };\n    auto identity = [](const int& state) { return\
    \ state; };\n\n    auto stopped = beam_search(0, 10, 4, expand_once, identity);\n\
    \    assert(stopped.state == 5);\n    assert(stopped.depth == 1);\n    assert(stopped.expanded_states\
    \ == 3);\n    assert(stopped.generated_states == 2);\n\n    auto zero = beam_search(7,\
    \ 0, 1, expand_once, identity);\n    assert(zero.state == 7);\n    assert(zero.score\
    \ == 7);\n    assert(zero.depth == 0);\n    assert(zero.expanded_states == 0);\n\
    \n    auto expand_without_depth = [](const int& state) {\n        return std::vector<int>{state\
    \ + 1, state + 2};\n    };\n    auto no_depth = beam_search(0, 3, 1, expand_without_depth,\
    \ identity);\n    assert(no_depth.state == 6);\n    assert(no_depth.depth == 3);\n\
    }\n\nstruct MoveOnlyState {\n    std::unique_ptr<int> value;\n\n    explicit MoveOnlyState(int\
    \ value_) : value(std::make_unique<int>(value_)) {}\n    MoveOnlyState(MoveOnlyState&&)\
    \ = default;\n    MoveOnlyState& operator=(MoveOnlyState&&) = default;\n    MoveOnlyState(const\
    \ MoveOnlyState&) = delete;\n    MoveOnlyState& operator=(const MoveOnlyState&)\
    \ = delete;\n};\n\nvoid test_move_only_state() {\n    auto expand = [](const MoveOnlyState&\
    \ state, int, auto emit) {\n        emit(MoveOnlyState(*state.value + 1));\n \
    \       emit(MoveOnlyState(*state.value + 2));\n    };\n    auto evaluate = [](const\
    \ MoveOnlyState& state) { return *state.value; };\n    auto result = beam_search(MoveOnlyState(0),\
    \ 4, 2, expand, evaluate);\n    assert(*result.state.value == 8);\n    assert(result.score\
    \ == 8);\n}\n\nvoid test_randomized_against_exhaustive_search() {\n    m1une::utilities::Random\
    \ random(0xbea45eaULL);\n    for (int trial = 0; trial < 200; trial++) {\n   \
    \     int depth_limit = int(random.uniform(1, 5));\n        int radix = int(random.uniform(2,\
    \ 4));\n        bool maximize = random.uniform(0, 1) != 0;\n        Objective\
    \ objective = maximize ? Objective::maximize\n                               \
    \        : Objective::minimize;\n        int state_count = 1;\n        for (int\
    \ depth = 0; depth < depth_limit; depth++) {\n            state_count *= radix;\n\
    \        }\n\n        auto result = beam_search(std::string(), depth_limit, state_count,\n\
    \                                  digit_expander(radix), digit_value, objective);\n\
    \        int expected = 0;\n        if (maximize) {\n            for (int depth\
    \ = 0; depth < depth_limit; depth++) {\n                expected = expected *\
    \ 10 + radix - 1;\n            }\n        }\n        assert(result.score == expected);\n\
    \    }\n}\n\nint main() {\n    test_objectives_and_statistics();\n    test_early_stop_and_zero_depth();\n\
    \    test_move_only_state();\n    test_randomized_against_exhaustive_search();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <memory>\n#include <string>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../heuristic/beam_search.hpp\"\n#include \"\
    ../../utilities/random.hpp\"\n\nusing m1une::heuristic::Objective;\nusing m1une::heuristic::beam_search;\n\
    \nauto digit_expander(int radix) {\n    return [radix](const std::string& state,\
    \ int, auto emit) {\n        for (int digit = 0; digit < radix; digit++) {\n \
    \           std::string candidate = state;\n            candidate.push_back(static_cast<char>('0'\
    \ + digit));\n            emit(std::move(candidate));\n        }\n    };\n}\n\n\
    auto digit_range_expander(int radix) {\n    return [radix](const std::string&\
    \ state, int) {\n        std::vector<std::string> result;\n        result.reserve(radix);\n\
    \        for (int digit = 0; digit < radix; digit++) {\n            result.push_back(state\
    \ + static_cast<char>('0' + digit));\n        }\n        return result;\n    };\n\
    }\n\nint digit_value(const std::string& state) {\n    int result = 0;\n    for\
    \ (char digit : state) result = result * 10 + digit - '0';\n    return result;\n\
    }\n\nvoid test_objectives_and_statistics() {\n    auto maximize = beam_search(std::string(),\
    \ 3, 2, digit_range_expander(3),\n                                digit_value,\
    \ Objective::maximize);\n    assert(maximize.state == \"222\");\n    assert(maximize.score\
    \ == 222);\n    assert(maximize.depth == 3);\n    assert(maximize.expanded_states\
    \ == 5);\n    assert(maximize.generated_states == 15);\n\n    auto minimize =\
    \ beam_search(std::string(), 3, 2, digit_range_expander(3),\n                \
    \                digit_value, Objective::minimize);\n    assert(minimize.state\
    \ == \"000\");\n    assert(minimize.score == 0);\n}\n\nvoid test_early_stop_and_zero_depth()\
    \ {\n    auto expand_once = [](const int& state, int depth, auto emit) {\n   \
    \     if (depth == 1) {\n            emit(state + 3);\n            emit(state\
    \ + 5);\n        }\n    };\n    auto identity = [](const int& state) { return\
    \ state; };\n\n    auto stopped = beam_search(0, 10, 4, expand_once, identity);\n\
    \    assert(stopped.state == 5);\n    assert(stopped.depth == 1);\n    assert(stopped.expanded_states\
    \ == 3);\n    assert(stopped.generated_states == 2);\n\n    auto zero = beam_search(7,\
    \ 0, 1, expand_once, identity);\n    assert(zero.state == 7);\n    assert(zero.score\
    \ == 7);\n    assert(zero.depth == 0);\n    assert(zero.expanded_states == 0);\n\
    \n    auto expand_without_depth = [](const int& state) {\n        return std::vector<int>{state\
    \ + 1, state + 2};\n    };\n    auto no_depth = beam_search(0, 3, 1, expand_without_depth,\
    \ identity);\n    assert(no_depth.state == 6);\n    assert(no_depth.depth == 3);\n\
    }\n\nstruct MoveOnlyState {\n    std::unique_ptr<int> value;\n\n    explicit MoveOnlyState(int\
    \ value_) : value(std::make_unique<int>(value_)) {}\n    MoveOnlyState(MoveOnlyState&&)\
    \ = default;\n    MoveOnlyState& operator=(MoveOnlyState&&) = default;\n    MoveOnlyState(const\
    \ MoveOnlyState&) = delete;\n    MoveOnlyState& operator=(const MoveOnlyState&)\
    \ = delete;\n};\n\nvoid test_move_only_state() {\n    auto expand = [](const MoveOnlyState&\
    \ state, int, auto emit) {\n        emit(MoveOnlyState(*state.value + 1));\n \
    \       emit(MoveOnlyState(*state.value + 2));\n    };\n    auto evaluate = [](const\
    \ MoveOnlyState& state) { return *state.value; };\n    auto result = beam_search(MoveOnlyState(0),\
    \ 4, 2, expand, evaluate);\n    assert(*result.state.value == 8);\n    assert(result.score\
    \ == 8);\n}\n\nvoid test_randomized_against_exhaustive_search() {\n    m1une::utilities::Random\
    \ random(0xbea45eaULL);\n    for (int trial = 0; trial < 200; trial++) {\n   \
    \     int depth_limit = int(random.uniform(1, 5));\n        int radix = int(random.uniform(2,\
    \ 4));\n        bool maximize = random.uniform(0, 1) != 0;\n        Objective\
    \ objective = maximize ? Objective::maximize\n                               \
    \        : Objective::minimize;\n        int state_count = 1;\n        for (int\
    \ depth = 0; depth < depth_limit; depth++) {\n            state_count *= radix;\n\
    \        }\n\n        auto result = beam_search(std::string(), depth_limit, state_count,\n\
    \                                  digit_expander(radix), digit_value, objective);\n\
    \        int expected = 0;\n        if (maximize) {\n            for (int depth\
    \ = 0; depth < depth_limit; depth++) {\n                expected = expected *\
    \ 10 + radix - 1;\n            }\n        }\n        assert(result.score == expected);\n\
    \    }\n}\n\nint main() {\n    test_objectives_and_statistics();\n    test_early_stop_and_zero_depth();\n\
    \    test_move_only_state();\n    test_randomized_against_exhaustive_search();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - heuristic/beam_search.hpp
  - heuristic/objective.hpp
  - utilities/random.hpp
  isVerificationFile: true
  path: verify/heuristic/beam_search.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/heuristic/beam_search.test.cpp
layout: document
redirect_from:
- /verify/verify/heuristic/beam_search.test.cpp
- /verify/verify/heuristic/beam_search.test.cpp.html
title: verify/heuristic/beam_search.test.cpp
---
