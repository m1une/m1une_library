---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: heuristic/all.hpp
    title: Heuristic Search
  - icon: ':heavy_check_mark:'
    path: heuristic/beam_search.hpp
    title: Beam Search
  - icon: ':heavy_check_mark:'
    path: heuristic/hill_climbing.hpp
    title: Hill Climbing
  - icon: ':heavy_check_mark:'
    path: heuristic/objective.hpp
    title: Heuristic Objective
  - icon: ':heavy_check_mark:'
    path: heuristic/simulated_annealing.hpp
    title: Simulated Annealing
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
  bundledCode: "#line 1 \"verify/heuristic/simulated_annealing.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <iostream>\n#include <limits>\n\
    \n#line 1 \"heuristic/all.hpp\"\n\n\n\n#line 1 \"heuristic/beam_search.hpp\"\n\
    \n\n\n#line 6 \"heuristic/beam_search.hpp\"\n#include <concepts>\n#include <cstddef>\n\
    #include <functional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"heuristic/objective.hpp\"\n\n\n\nnamespace m1une {\nnamespace heuristic\
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
    \ heuristic\n}  // namespace m1une\n\n\n#line 1 \"heuristic/hill_climbing.hpp\"\
    \n\n\n\n#line 5 \"heuristic/hill_climbing.hpp\"\n\n#line 7 \"heuristic/hill_climbing.hpp\"\
    \n\nnamespace m1une {\nnamespace heuristic {\n\nusing HillClimbingObjective =\
    \ Objective;\n\nclass HillClimbing {\n   private:\n    Objective _objective;\n\
    \    bool _accept_equal;\n\n   public:\n    explicit HillClimbing(Objective objective\
    \ = Objective::maximize,\n                          bool accept_equal = false)\n\
    \        : _objective(objective), _accept_equal(accept_equal) {}\n\n    bool accept_delta(long\
    \ double candidate_minus_current) const {\n        if (_objective == Objective::maximize)\
    \ {\n            return _accept_equal ? 0.0L <= candidate_minus_current\n    \
    \                             : 0.0L < candidate_minus_current;\n        }\n \
    \       return _accept_equal ? candidate_minus_current <= 0.0L\n             \
    \                : candidate_minus_current < 0.0L;\n    }\n\n    template <std::convertible_to<long\
    \ double> CurrentScore,\n              std::convertible_to<long double> CandidateScore>\n\
    \    bool accept(CurrentScore current_score,\n                CandidateScore candidate_score)\
    \ const {\n        long double delta = static_cast<long double>(candidate_score)\
    \ -\n                            static_cast<long double>(current_score);\n  \
    \      return accept_delta(delta);\n    }\n};\n\n}  // namespace heuristic\n}\
    \  // namespace m1une\n\n\n#line 1 \"heuristic/simulated_annealing.hpp\"\n\n\n\
    \n#line 8 \"heuristic/simulated_annealing.hpp\"\n\n#line 10 \"heuristic/simulated_annealing.hpp\"\
    \n\nnamespace m1une {\nnamespace heuristic {\n\nusing AnnealingObjective = Objective;\n\
    \nenum class AnnealingCooling {\n    linear,\n    exponential,\n};\n\nclass SimulatedAnnealing\
    \ {\n   private:\n    double _start_temperature;\n    double _end_temperature;\n\
    \    AnnealingObjective _objective;\n    AnnealingCooling _cooling;\n\n    long\
    \ double directed_delta(long double candidate_minus_current) const {\n       \
    \ if (_objective == AnnealingObjective::maximize) {\n            return candidate_minus_current;\n\
    \        }\n        return -candidate_minus_current;\n    }\n\n   public:\n  \
    \  SimulatedAnnealing(\n        double start_temperature, double end_temperature,\n\
    \        AnnealingObjective objective = AnnealingObjective::maximize,\n      \
    \  AnnealingCooling cooling = AnnealingCooling::exponential)\n        : _start_temperature(start_temperature),\n\
    \          _end_temperature(end_temperature),\n          _objective(objective),\n\
    \          _cooling(cooling) {\n        assert(std::isfinite(start_temperature));\n\
    \        assert(std::isfinite(end_temperature));\n        assert(0.0 <= end_temperature);\n\
    \        assert(end_temperature <= start_temperature);\n        assert(cooling\
    \ != AnnealingCooling::exponential ||\n               0.0 < end_temperature);\n\
    \    }\n\n    double temperature(double progress) const {\n        assert(std::isfinite(progress));\n\
    \        assert(0.0 <= progress && progress <= 1.0);\n        progress = std::clamp(progress,\
    \ 0.0, 1.0);\n        if (_cooling == AnnealingCooling::linear) {\n          \
    \  return _start_temperature +\n                   (_end_temperature - _start_temperature)\
    \ * progress;\n        }\n        return _start_temperature *\n              \
    \ std::pow(_end_temperature / _start_temperature, progress);\n    }\n\n    double\
    \ acceptance_probability_delta(\n        long double candidate_minus_current,\
    \ double progress) const {\n        long double improvement = directed_delta(candidate_minus_current);\n\
    \        if (0.0L <= improvement) return 1.0;\n        double current_temperature\
    \ = temperature(progress);\n        if (current_temperature == 0.0) return 0.0;\n\
    \        return std::exp(static_cast<double>(\n            improvement / static_cast<long\
    \ double>(current_temperature)));\n    }\n\n    bool accept_delta(long double\
    \ candidate_minus_current, double progress,\n                      double random01)\
    \ const {\n        assert(std::isfinite(random01));\n        assert(0.0 <= random01\
    \ && random01 < 1.0);\n        return random01 <\n               acceptance_probability_delta(candidate_minus_current,\
    \ progress);\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    double acceptance_probability(CurrentScore\
    \ current_score,\n                                  CandidateScore candidate_score,\n\
    \                                  double progress) const {\n        long double\
    \ delta = static_cast<long double>(candidate_score) -\n                      \
    \      static_cast<long double>(current_score);\n        return acceptance_probability_delta(delta,\
    \ progress);\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    bool accept(CurrentScore\
    \ current_score, CandidateScore candidate_score,\n                double progress,\
    \ double random01) const {\n        long double delta = static_cast<long double>(candidate_score)\
    \ -\n                            static_cast<long double>(current_score);\n  \
    \      return accept_delta(delta, progress, random01);\n    }\n};\n\n}  // namespace\
    \ heuristic\n}  // namespace m1une\n\n\n#line 8 \"heuristic/all.hpp\"\n\n\n#line\
    \ 1 \"utilities/random.hpp\"\n\n\n\n#line 6 \"utilities/random.hpp\"\n#include\
    \ <chrono>\n#line 8 \"utilities/random.hpp\"\n#include <cstdint>\n#line 10 \"\
    utilities/random.hpp\"\n#include <numeric>\n#include <queue>\n#include <random>\n\
    #include <string>\n#include <string_view>\n#include <tuple>\n#line 17 \"utilities/random.hpp\"\
    \n#include <unordered_set>\n#line 20 \"utilities/random.hpp\"\n\nnamespace m1une\
    \ {\nnamespace utilities {\n\nstruct RandomGraphOptions {\n    bool directed =\
    \ false;\n    bool allow_self_loops = false;\n    bool allow_parallel_edges =\
    \ false;\n};\n\nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\n\
    \    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/heuristic/simulated_annealing.test.cpp\"\
    \n\nusing m1une::heuristic::AnnealingCooling;\nusing m1une::heuristic::AnnealingObjective;\n\
    using m1une::heuristic::SimulatedAnnealing;\n\nbool close(double first, double\
    \ second) {\n    return std::abs(first - second) <=\n           1e-12 * std::max(1.0,\
    \ std::abs(second));\n}\n\nvoid test_temperature() {\n    SimulatedAnnealing exponential(100.0,\
    \ 1.0);\n    assert(close(exponential.temperature(0.0), 100.0));\n    assert(close(exponential.temperature(0.5),\
    \ 10.0));\n    assert(close(exponential.temperature(1.0), 1.0));\n\n    SimulatedAnnealing\
    \ linear(100.0, 0.0,\n                              AnnealingObjective::maximize,\n\
    \                              AnnealingCooling::linear);\n    assert(close(linear.temperature(0.0),\
    \ 100.0));\n    assert(close(linear.temperature(0.25), 75.0));\n    assert(close(linear.temperature(1.0),\
    \ 0.0));\n}\n\nvoid test_maximization() {\n    SimulatedAnnealing annealing(10.0,\
    \ 10.0);\n    assert(annealing.acceptance_probability(3, 4, 0.5) == 1.0);\n  \
    \  assert(annealing.acceptance_probability(3, 3, 0.5) == 1.0);\n    assert(close(annealing.acceptance_probability(3,\
    \ -7, 0.5),\n                 std::exp(-1.0)));\n    assert(annealing.accept(3,\
    \ 4, 0.5, 0.999999));\n    assert(annealing.accept(3, -7, 0.5, 0.3));\n    assert(!annealing.accept(3,\
    \ -7, 0.5, 0.4));\n}\n\nvoid test_minimization() {\n    SimulatedAnnealing annealing(2.0,\
    \ 2.0,\n                                 AnnealingObjective::minimize);\n    assert(annealing.acceptance_probability(5,\
    \ 4, 0.0) == 1.0);\n    assert(close(annealing.acceptance_probability(5, 7, 0.0),\n\
    \                 std::exp(-1.0)));\n    assert(annealing.accept_delta(-1.0, 0.0,\
    \ 0.999999));\n    assert(!annealing.accept_delta(2.0, 0.0, 0.4));\n}\n\nvoid\
    \ test_zero_temperature_and_large_scores() {\n    SimulatedAnnealing greedy(1.0,\
    \ 0.0,\n                              AnnealingObjective::maximize,\n        \
    \                      AnnealingCooling::linear);\n    assert(greedy.acceptance_probability_delta(-1.0,\
    \ 1.0) == 0.0);\n    assert(!greedy.accept_delta(-1.0, 1.0, 0.0));\n    assert(greedy.accept_delta(0.0,\
    \ 1.0, 0.999999));\n\n    long long low = std::numeric_limits<long long>::min();\n\
    \    long long high = std::numeric_limits<long long>::max();\n    assert(greedy.acceptance_probability(low,\
    \ high, 1.0) == 1.0);\n    assert(greedy.acceptance_probability(high, low, 1.0)\
    \ == 0.0);\n}\n\nvoid test_randomized_against_formula() {\n    m1une::utilities::Random\
    \ random(0x51a7edULL);\n    for (AnnealingObjective objective : {AnnealingObjective::minimize,\n\
    \                                         AnnealingObjective::maximize}) {\n \
    \       SimulatedAnnealing annealing(30.0, 0.03, objective);\n        for (int\
    \ trial = 0; trial < 10000; trial++) {\n            long long current = random.uniform(-1000000000,\
    \ 1000000000);\n            long long candidate = random.uniform(-1000000000,\
    \ 1000000000);\n            double progress = random.real();\n            double\
    \ random01 = random.real();\n\n            long double delta = static_cast<long\
    \ double>(candidate) -\n                                static_cast<long double>(current);\n\
    \            long double improvement =\n                objective == AnnealingObjective::maximize\
    \ ? delta : -delta;\n            double expected = 1.0;\n            if (improvement\
    \ < 0.0L) {\n                expected = std::exp(static_cast<double>(\n      \
    \              improvement / annealing.temperature(progress)));\n            }\n\
    \            assert(close(annealing.acceptance_probability(\n                \
    \             current, candidate, progress),\n                         expected));\n\
    \            assert(annealing.accept(current, candidate, progress, random01) ==\n\
    \                   (random01 < expected));\n        }\n    }\n}\n\nint main()\
    \ {\n    test_temperature();\n    test_maximization();\n    test_minimization();\n\
    \    test_zero_temperature_and_large_scores();\n    test_randomized_against_formula();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <iostream>\n#include <limits>\n\
    \n#include \"../../heuristic/all.hpp\"\n#include \"../../utilities/random.hpp\"\
    \n\nusing m1une::heuristic::AnnealingCooling;\nusing m1une::heuristic::AnnealingObjective;\n\
    using m1une::heuristic::SimulatedAnnealing;\n\nbool close(double first, double\
    \ second) {\n    return std::abs(first - second) <=\n           1e-12 * std::max(1.0,\
    \ std::abs(second));\n}\n\nvoid test_temperature() {\n    SimulatedAnnealing exponential(100.0,\
    \ 1.0);\n    assert(close(exponential.temperature(0.0), 100.0));\n    assert(close(exponential.temperature(0.5),\
    \ 10.0));\n    assert(close(exponential.temperature(1.0), 1.0));\n\n    SimulatedAnnealing\
    \ linear(100.0, 0.0,\n                              AnnealingObjective::maximize,\n\
    \                              AnnealingCooling::linear);\n    assert(close(linear.temperature(0.0),\
    \ 100.0));\n    assert(close(linear.temperature(0.25), 75.0));\n    assert(close(linear.temperature(1.0),\
    \ 0.0));\n}\n\nvoid test_maximization() {\n    SimulatedAnnealing annealing(10.0,\
    \ 10.0);\n    assert(annealing.acceptance_probability(3, 4, 0.5) == 1.0);\n  \
    \  assert(annealing.acceptance_probability(3, 3, 0.5) == 1.0);\n    assert(close(annealing.acceptance_probability(3,\
    \ -7, 0.5),\n                 std::exp(-1.0)));\n    assert(annealing.accept(3,\
    \ 4, 0.5, 0.999999));\n    assert(annealing.accept(3, -7, 0.5, 0.3));\n    assert(!annealing.accept(3,\
    \ -7, 0.5, 0.4));\n}\n\nvoid test_minimization() {\n    SimulatedAnnealing annealing(2.0,\
    \ 2.0,\n                                 AnnealingObjective::minimize);\n    assert(annealing.acceptance_probability(5,\
    \ 4, 0.0) == 1.0);\n    assert(close(annealing.acceptance_probability(5, 7, 0.0),\n\
    \                 std::exp(-1.0)));\n    assert(annealing.accept_delta(-1.0, 0.0,\
    \ 0.999999));\n    assert(!annealing.accept_delta(2.0, 0.0, 0.4));\n}\n\nvoid\
    \ test_zero_temperature_and_large_scores() {\n    SimulatedAnnealing greedy(1.0,\
    \ 0.0,\n                              AnnealingObjective::maximize,\n        \
    \                      AnnealingCooling::linear);\n    assert(greedy.acceptance_probability_delta(-1.0,\
    \ 1.0) == 0.0);\n    assert(!greedy.accept_delta(-1.0, 1.0, 0.0));\n    assert(greedy.accept_delta(0.0,\
    \ 1.0, 0.999999));\n\n    long long low = std::numeric_limits<long long>::min();\n\
    \    long long high = std::numeric_limits<long long>::max();\n    assert(greedy.acceptance_probability(low,\
    \ high, 1.0) == 1.0);\n    assert(greedy.acceptance_probability(high, low, 1.0)\
    \ == 0.0);\n}\n\nvoid test_randomized_against_formula() {\n    m1une::utilities::Random\
    \ random(0x51a7edULL);\n    for (AnnealingObjective objective : {AnnealingObjective::minimize,\n\
    \                                         AnnealingObjective::maximize}) {\n \
    \       SimulatedAnnealing annealing(30.0, 0.03, objective);\n        for (int\
    \ trial = 0; trial < 10000; trial++) {\n            long long current = random.uniform(-1000000000,\
    \ 1000000000);\n            long long candidate = random.uniform(-1000000000,\
    \ 1000000000);\n            double progress = random.real();\n            double\
    \ random01 = random.real();\n\n            long double delta = static_cast<long\
    \ double>(candidate) -\n                                static_cast<long double>(current);\n\
    \            long double improvement =\n                objective == AnnealingObjective::maximize\
    \ ? delta : -delta;\n            double expected = 1.0;\n            if (improvement\
    \ < 0.0L) {\n                expected = std::exp(static_cast<double>(\n      \
    \              improvement / annealing.temperature(progress)));\n            }\n\
    \            assert(close(annealing.acceptance_probability(\n                \
    \             current, candidate, progress),\n                         expected));\n\
    \            assert(annealing.accept(current, candidate, progress, random01) ==\n\
    \                   (random01 < expected));\n        }\n    }\n}\n\nint main()\
    \ {\n    test_temperature();\n    test_maximization();\n    test_minimization();\n\
    \    test_zero_temperature_and_large_scores();\n    test_randomized_against_formula();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - heuristic/all.hpp
  - heuristic/beam_search.hpp
  - heuristic/objective.hpp
  - heuristic/hill_climbing.hpp
  - heuristic/simulated_annealing.hpp
  - utilities/random.hpp
  isVerificationFile: true
  path: verify/heuristic/simulated_annealing.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/heuristic/simulated_annealing.test.cpp
layout: document
redirect_from:
- /verify/verify/heuristic/simulated_annealing.test.cpp
- /verify/verify/heuristic/simulated_annealing.test.cpp.html
title: verify/heuristic/simulated_annealing.test.cpp
---
