---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
  - icon: ':heavy_check_mark:'
    path: utilities/random_testing.hpp
    title: Random Testing
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
  bundledCode: "#line 1 \"verify/utilities/random_testing.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"utilities/random_testing.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <cstdlib>\n#include <exception>\n#include <functional>\n#include <iostream>\n\
    #include <iterator>\n#include <sstream>\n#include <string>\n#include <tuple>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"utilities/random.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 6 \"utilities/random.hpp\"\n#include <chrono>\n\
    #line 10 \"utilities/random.hpp\"\n#include <numeric>\n#include <queue>\n#include\
    \ <random>\n#line 14 \"utilities/random.hpp\"\n#include <string_view>\n#line 17\
    \ \"utilities/random.hpp\"\n#include <unordered_set>\n#line 20 \"utilities/random.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\nstruct RandomGraphOptions {\n\
    \    bool directed = false;\n    bool allow_self_loops = false;\n    bool allow_parallel_edges\
    \ = false;\n};\n\nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\
    \n    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 20 \"utilities/random_testing.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\ninline constexpr std::uint64_t\
    \ default_random_test_seed =\n    0x243f6a8885a308d3ULL;\n\nstruct RandomTestConfig\
    \ {\n    int trials = 1000;\n    std::uint64_t seed = default_random_test_seed;\n\
    };\n\nenum class RandomTestFailure {\n    none,\n    property,\n    mismatch,\n\
    \    rejected_output,\n    query_limit,\n    invalid_query,\n};\n\ninline const\
    \ char* random_test_failure_name(RandomTestFailure failure) {\n    switch (failure)\
    \ {\n        case RandomTestFailure::none:\n            return \"none\";\n   \
    \     case RandomTestFailure::property:\n            return \"property\";\n  \
    \      case RandomTestFailure::mismatch:\n            return \"mismatch\";\n \
    \       case RandomTestFailure::rejected_output:\n            return \"rejected\
    \ output\";\n        case RandomTestFailure::query_limit:\n            return\
    \ \"query limit exceeded\";\n        case RandomTestFailure::invalid_query:\n\
    \            return \"invalid query\";\n    }\n    return \"unknown\";\n}\n\n\
    struct RandomTestResult {\n    std::uint64_t seed = 0;\n    int requested_trials\
    \ = 0;\n    int completed_trials = 0;\n    int failed_trial = -1;\n    RandomTestFailure\
    \ failure = RandomTestFailure::none;\n    int query_count = -1;\n\n    bool passed()\
    \ const {\n        return failed_trial == -1;\n    }\n\n    explicit operator\
    \ bool() const {\n        return passed();\n    }\n};\n\nstruct IgnoreRandomTestFailure\
    \ {\n    template <class... Args>\n    void operator()(Args&&...) const {}\n};\n\
    \nstruct InteractionExchange {\n    std::string query;\n    std::string response;\n\
    \    bool responded = false;\n};\n\nstruct InteractionTranscript {\n    std::vector<InteractionExchange>\
    \ exchanges;\n    std::string answer;\n    bool answered = false;\n    std::string\
    \ failure_message;\n};\n\nnamespace random_testing_detail {\n\ntemplate <class\
    \ T>\nvoid print_value(std::ostream& output, const T& value) {\n    if constexpr\
    \ (requires { output << value; }) {\n        output << value;\n    } else if constexpr\
    \ (requires {\n                             typename std::tuple_size<\n      \
    \                           std::remove_cvref_t<T>>::type;\n                 \
    \        }) {\n        output << '(';\n        int index = 0;\n        std::apply(\n\
    \            [&](const auto&... elements) {\n                ((output << (index++\
    \ == 0 ? \"\" : \", \"),\n                  print_value(output, elements)),\n\
    \                 ...);\n            },\n            value);\n        output <<\
    \ ')';\n    } else if constexpr (requires { std::begin(value); std::end(value);\
    \ }) {\n        output << '[';\n        bool first = true;\n        for (const\
    \ auto& element : value) {\n            if (!first) output << \", \";\n      \
    \      first = false;\n            print_value(output, element);\n        }\n\
    \        output << ']';\n    } else {\n        output << \"<unprintable>\";\n\
    \    }\n}\n\ntemplate <class Function>\ndecltype(auto) invoke_with_trial(Function&\
    \ function, Random& random, int trial) {\n    if constexpr (std::invocable<Function&,\
    \ Random&, int>) {\n        return std::invoke(function, random, trial);\n   \
    \ } else {\n        static_assert(std::invocable<Function&, Random&>);\n     \
    \   return std::invoke(function, random);\n    }\n}\n\ninline RandomTestResult\
    \ success_result(const RandomTestConfig& config) {\n    RandomTestResult result;\n\
    \    result.seed = config.seed;\n    result.requested_trials = config.trials;\n\
    \    result.completed_trials = config.trials;\n    return result;\n}\n\ninline\
    \ RandomTestResult failure_result(const RandomTestConfig& config,\n          \
    \                             int failed_trial,\n                            \
    \           RandomTestFailure failure,\n                                     \
    \  int query_count = -1) {\n    RandomTestResult result;\n    result.seed = config.seed;\n\
    \    result.requested_trials = config.trials;\n    result.completed_trials = failed_trial;\n\
    \    result.failed_trial = failed_trial;\n    result.failure = failure;\n    result.query_count\
    \ = query_count;\n    return result;\n}\n\ntemplate <class T>\nstd::string value_to_string(const\
    \ T& value) {\n    std::ostringstream output;\n    print_value(output, value);\n\
    \    return output.str();\n}\n\nstruct InteractionAbort {\n    RandomTestFailure\
    \ failure;\n    std::string message;\n};\n\nclass StandardStreamRedirect {\n \
    \  private:\n    std::streambuf* _cin_buffer;\n    std::streambuf* _cout_buffer;\n\
    \n   public:\n    StandardStreamRedirect(std::streambuf* input, std::streambuf*\
    \ output)\n        : _cin_buffer(std::cin.rdbuf()), _cout_buffer(std::cout.rdbuf())\
    \ {\n        std::cout.flush();\n        std::cin.rdbuf(input);\n        std::cout.rdbuf(output);\n\
    \        std::cin.clear();\n        std::cout.clear();\n    }\n\n    StandardStreamRedirect(const\
    \ StandardStreamRedirect&) = delete;\n    StandardStreamRedirect& operator=(const\
    \ StandardStreamRedirect&) = delete;\n\n    ~StandardStreamRedirect() {\n    \
    \    std::cout.flush();\n        std::cin.rdbuf(_cin_buffer);\n        std::cout.rdbuf(_cout_buffer);\n\
    \        std::cin.clear();\n        std::cout.clear();\n    }\n};\n\ntemplate\
    \ <class Generator>\nstd::string generate_stream_input(Generator& generator, Random&\
    \ random,\n                                  int trial) {\n    std::ostringstream\
    \ output;\n    if constexpr (std::invocable<Generator&, Random&, std::ostream&,\
    \ int>) {\n        std::invoke(generator, random, output, trial);\n    } else\
    \ {\n        static_assert(std::invocable<Generator&, Random&, std::ostream&>);\n\
    \        std::invoke(generator, random, output);\n    }\n    return output.str();\n\
    }\n\ntemplate <class Generator>\ndecltype(auto) generate_interactive_stream_input(Generator&\
    \ generator,\n                                                 Random& random,\n\
    \                                                 std::ostream& output,\n    \
    \                                             int trial) {\n    if constexpr (std::invocable<Generator&,\
    \ Random&, std::ostream&, int>) {\n        return std::invoke(generator, random,\
    \ output, trial);\n    } else {\n        static_assert(std::invocable<Generator&,\
    \ Random&, std::ostream&>);\n        return std::invoke(generator, random, output);\n\
    \    }\n}\n\ntemplate <class Solution>\nstd::string run_with_standard_streams(const\
    \ std::string& input,\n                                      Solution& solution)\
    \ {\n    std::istringstream input_stream(input);\n    std::ostringstream output_stream;\n\
    \    {\n        StandardStreamRedirect redirect(input_stream.rdbuf(),\n      \
    \                                  output_stream.rdbuf());\n        std::invoke(solution);\n\
    \    }\n    return output_stream.str();\n}\n\ninline std::string trim_line_breaks(std::string\
    \ text) {\n    while (!text.empty() &&\n           (text.back() == '\\n' || text.back()\
    \ == '\\r')) {\n        text.pop_back();\n    }\n    return text;\n}\n\ntemplate\
    \ <class State, class QueryHandler>\nclass InteractiveStreamBuffer : public std::streambuf\
    \ {\n   private:\n    State* _state;\n    QueryHandler* _query_handler;\n    std::stringbuf*\
    \ _candidate_output;\n    std::size_t _output_cursor = 0;\n    int _query_limit;\n\
    \    int _query_count = 0;\n    std::string _input_chunk;\n    InteractionTranscript\
    \ _transcript;\n    RandomTestFailure _failure = RandomTestFailure::none;\n  \
    \  std::exception_ptr _exception;\n\n    void set_input_chunk(std::string text)\
    \ {\n        text.push_back('\\n');\n        _input_chunk = std::move(text);\n\
    \        char* first = _input_chunk.data();\n        setg(first, first, first\
    \ + _input_chunk.size());\n    }\n\n    void fail(RandomTestFailure failure, std::string\
    \ message) {\n        _failure = failure;\n        _transcript.failure_message\
    \ = std::move(message);\n        setg(nullptr, nullptr, nullptr);\n    }\n\n \
    \  protected:\n    int_type underflow() override {\n        if (gptr() != nullptr\
    \ && gptr() < egptr()) {\n            return traits_type::to_int_type(*gptr());\n\
    \        }\n        if (_failure != RandomTestFailure::none || _exception) {\n\
    \            return traits_type::eof();\n        }\n\n        std::string all_output\
    \ = _candidate_output->str();\n        std::string query = all_output.substr(_output_cursor);\n\
    \        _output_cursor = all_output.size();\n        if (query.empty()) {\n \
    \           fail(RandomTestFailure::invalid_query,\n                 \"solution\
    \ requested input without writing a query\");\n            return traits_type::eof();\n\
    \        }\n\n        InteractionExchange exchange;\n        exchange.query =\
    \ trim_line_breaks(query);\n        _transcript.exchanges.push_back(std::move(exchange));\n\
    \        _query_count++;\n        if (_query_limit < _query_count) {\n       \
    \     fail(RandomTestFailure::query_limit,\n                 \"attempted query\
    \ \" + std::to_string(_query_count) +\n                     \" with limit \" +\
    \ std::to_string(_query_limit));\n            return traits_type::eof();\n   \
    \     }\n\n        std::istringstream query_stream(query);\n        std::ostringstream\
    \ response_stream;\n        try {\n            std::invoke(*_query_handler, *_state,\
    \ query_stream,\n                        response_stream);\n        } catch (const\
    \ InteractionAbort& failure) {\n            fail(failure.failure, failure.message);\n\
    \            return traits_type::eof();\n        } catch (...) {\n           \
    \ _exception = std::current_exception();\n            return traits_type::eof();\n\
    \        }\n\n        std::string response = response_stream.str();\n        InteractionExchange&\
    \ recorded = _transcript.exchanges.back();\n        recorded.response = trim_line_breaks(response);\n\
    \        recorded.responded = true;\n        set_input_chunk(std::move(response));\n\
    \        return traits_type::to_int_type(*gptr());\n    }\n\n   public:\n    InteractiveStreamBuffer(State&\
    \ state, QueryHandler& query_handler,\n                            std::stringbuf&\
    \ candidate_output,\n                            std::string initial_input, int\
    \ query_limit)\n        : _state(&state),\n          _query_handler(&query_handler),\n\
    \          _candidate_output(&candidate_output),\n          _query_limit(query_limit)\
    \ {\n        set_input_chunk(std::move(initial_input));\n    }\n\n    void finish()\
    \ {\n        std::string all_output = _candidate_output->str();\n        _transcript.answer\
    \ = all_output.substr(_output_cursor);\n        _transcript.answered = true;\n\
    \    }\n\n    RandomTestFailure failure() const {\n        return _failure;\n\
    \    }\n\n    int query_count() const {\n        return _query_count;\n    }\n\
    \n    const InteractionTranscript& transcript() const {\n        return _transcript;\n\
    \    }\n\n    const std::exception_ptr& exception() const {\n        return _exception;\n\
    \    }\n};\n\ntemplate <class Solver, class Input, class Interaction>\ndecltype(auto)\
    \ invoke_interactive_solver(Solver& solver, const Input& input,\n            \
    \                             Interaction& interaction) {\n    if constexpr (std::invocable<Solver&,\
    \ const Input&, Interaction&>) {\n        return std::invoke(solver, input, interaction);\n\
    \    } else {\n        static_assert(std::invocable<Solver&, Interaction&>);\n\
    \        return std::invoke(solver, interaction);\n    }\n}\n\n}  // namespace\
    \ random_testing_detail\n\ntemplate <class Input, class State>\nstruct InteractiveTestCase\
    \ {\n    Input input;\n    State state;\n};\n\ntemplate <class Input, class State>\n\
    auto interactive_test_case(Input&& input, State&& state) {\n    return InteractiveTestCase<std::remove_cvref_t<Input>,\n\
    \                               std::remove_cvref_t<State>>{\n        std::forward<Input>(input),\
    \ std::forward<State>(state)};\n}\n\n// Call this from a query handler when the\
    \ candidate violates the protocol.\n[[noreturn]] inline void reject_query(std::string\
    \ message = {}) {\n    throw random_testing_detail::InteractionAbort{\n      \
    \  RandomTestFailure::invalid_query, std::move(message)};\n}\n\ntemplate <class\
    \ State, class QueryHandler>\nclass RandomInteraction {\n   private:\n    State*\
    \ _state;\n    QueryHandler* _query_handler;\n    int _query_limit;\n    int _query_count\
    \ = 0;\n    InteractionTranscript _transcript;\n\n   public:\n    RandomInteraction(State&\
    \ state, QueryHandler& query_handler,\n                      int query_limit)\n\
    \        : _state(&state),\n          _query_handler(&query_handler),\n      \
    \    _query_limit(query_limit) {}\n\n    RandomInteraction(const RandomInteraction&)\
    \ = delete;\n    RandomInteraction& operator=(const RandomInteraction&) = delete;\n\
    \    RandomInteraction(RandomInteraction&&) = delete;\n    RandomInteraction&\
    \ operator=(RandomInteraction&&) = delete;\n\n    template <class Query>\n   \
    \ auto ask(Query&& query) {\n        using Reply = std::remove_cvref_t<std::invoke_result_t<\n\
    \            QueryHandler&, State&, Query>>;\n        static_assert(!std::is_void_v<Reply>);\n\
    \n        InteractionExchange exchange;\n        exchange.query = random_testing_detail::value_to_string(query);\n\
    \        _transcript.exchanges.push_back(std::move(exchange));\n        _query_count++;\n\
    \        if (_query_limit < _query_count) {\n            throw random_testing_detail::InteractionAbort{\n\
    \                RandomTestFailure::query_limit,\n                \"attempted\
    \ query \" + std::to_string(_query_count) +\n                    \" with limit\
    \ \" + std::to_string(_query_limit)};\n        }\n\n        Reply reply = std::invoke(*_query_handler,\
    \ *_state,\n                                  std::forward<Query>(query));\n \
    \       InteractionExchange& recorded = _transcript.exchanges.back();\n      \
    \  recorded.response = random_testing_detail::value_to_string(reply);\n      \
    \  recorded.responded = true;\n        return reply;\n    }\n\n    int query_count()\
    \ const {\n        return _query_count;\n    }\n\n    const InteractionTranscript&\
    \ transcript() const {\n        return _transcript;\n    }\n\n    template <class\
    \ Answer>\n    void record_answer(const Answer& answer) {\n        _transcript.answer\
    \ =\n            random_testing_detail::value_to_string(answer);\n        _transcript.answered\
    \ = true;\n    }\n\n    void record_failure(std::string message) {\n        _transcript.failure_message\
    \ = std::move(message);\n    }\n};\n\nstruct PrintRandomTestFailure {\n    template\
    \ <class Case, class Expected, class Actual>\n    void operator()(const Case&\
    \ test_case, const Expected& expected,\n                    const Actual& actual,\
    \ int trial,\n                    std::uint64_t seed) const {\n        std::cerr\
    \ << \"random test failed: seed=\" << seed\n                  << \" trial=\" <<\
    \ trial << '\\n';\n        std::cerr << \"input: \";\n        random_testing_detail::print_value(std::cerr,\
    \ test_case);\n        std::cerr << \"\\nexpected: \";\n        random_testing_detail::print_value(std::cerr,\
    \ expected);\n        std::cerr << \"\\nactual: \";\n        random_testing_detail::print_value(std::cerr,\
    \ actual);\n        std::cerr << '\\n';\n    }\n};\n\nstruct PrintConstructiveTestFailure\
    \ {\n    template <class Case, class Answer>\n    void operator()(const Case&\
    \ test_case, const Answer& answer, int trial,\n                    std::uint64_t\
    \ seed) const {\n        std::cerr << \"constructive random test failed: seed=\"\
    \ << seed\n                  << \" trial=\" << trial << '\\n';\n        std::cerr\
    \ << \"input: \";\n        random_testing_detail::print_value(std::cerr, test_case);\n\
    \        std::cerr << \"\\noutput: \";\n        random_testing_detail::print_value(std::cerr,\
    \ answer);\n        std::cerr << '\\n';\n    }\n};\n\nstruct PrintStreamTestFailure\
    \ {\n    void operator()(const std::string& input, const std::string& output,\n\
    \                    int trial, std::uint64_t seed) const {\n        std::cerr\
    \ << \"stream random test failed: seed=\" << seed\n                  << \" trial=\"\
    \ << trial << \"\\ninput:\\n\"\n                  << input;\n        if (input.empty()\
    \ || input.back() != '\\n') std::cerr << '\\n';\n        std::cerr << \"output:\\\
    n\" << output;\n        if (output.empty() || output.back() != '\\n') std::cerr\
    \ << '\\n';\n    }\n};\n\nstruct PrintInteractiveTestFailure {\n    template <class\
    \ Input, class State>\n    void operator()(const InteractiveTestCase<Input, State>&\
    \ test_case,\n                    const InteractionTranscript& transcript, int\
    \ trial,\n                    std::uint64_t seed,\n                    RandomTestFailure\
    \ failure) const {\n        std::cerr << \"interactive random test failed: seed=\"\
    \ << seed\n                  << \" trial=\" << trial\n                  << \"\
    \ reason=\" << random_test_failure_name(failure) << '\\n';\n        std::cerr\
    \ << \"input: \";\n        random_testing_detail::print_value(std::cerr, test_case.input);\n\
    \        std::cerr << \"\\njudge state: \";\n        random_testing_detail::print_value(std::cerr,\
    \ test_case.state);\n        std::cerr << '\\n';\n        for (int index = 0;\
    \ index < int(transcript.exchanges.size()); index++) {\n            const InteractionExchange&\
    \ exchange = transcript.exchanges[index];\n            std::cerr << \"query \"\
    \ << index + 1 << \": \" << exchange.query;\n            if (exchange.responded)\
    \ {\n                std::cerr << \" -> \" << exchange.response;\n           \
    \ } else {\n                std::cerr << \" -> <no response>\";\n            }\n\
    \            std::cerr << '\\n';\n        }\n        if (transcript.answered)\
    \ {\n            std::cerr << \"answer: \" << transcript.answer << '\\n';\n  \
    \      }\n        if (!transcript.failure_message.empty()) {\n            std::cerr\
    \ << \"message: \" << transcript.failure_message << '\\n';\n        }\n    }\n\
    };\n\nstruct PrintInteractiveStreamTestFailure {\n    template <class State>\n\
    \    void operator()(const std::string& input, const State& state,\n         \
    \           const InteractionTranscript& transcript, int trial,\n            \
    \        std::uint64_t seed,\n                    RandomTestFailure failure) const\
    \ {\n        std::cerr << \"interactive stream random test failed: seed=\" <<\
    \ seed\n                  << \" trial=\" << trial\n                  << \" reason=\"\
    \ << random_test_failure_name(failure)\n                  << \"\\ninput:\\n\"\n\
    \                  << input;\n        if (input.empty() || input.back() != '\\\
    n') std::cerr << '\\n';\n        std::cerr << \"judge state: \";\n        random_testing_detail::print_value(std::cerr,\
    \ state);\n        std::cerr << '\\n';\n        for (int index = 0; index < int(transcript.exchanges.size());\
    \ index++) {\n            const InteractionExchange& exchange = transcript.exchanges[index];\n\
    \            std::cerr << \"query \" << index + 1 << \": \" << exchange.query;\n\
    \            if (exchange.responded) {\n                std::cerr << \" -> \"\
    \ << exchange.response;\n            } else {\n                std::cerr << \"\
    \ -> <no response>\";\n            }\n            std::cerr << '\\n';\n      \
    \  }\n        if (transcript.answered) {\n            std::cerr << \"answer: \"\
    \ << transcript.answer;\n            if (transcript.answer.empty() || transcript.answer.back()\
    \ != '\\n') {\n                std::cerr << '\\n';\n            }\n        }\n\
    \        if (!transcript.failure_message.empty()) {\n            std::cerr <<\
    \ \"message: \" << transcript.failure_message << '\\n';\n        }\n    }\n};\n\
    \n// Runs a property returning bool for every generated trial.\n// The property\
    \ may accept (Random&) or (Random&, int trial).\ntemplate <class Property>\nRandomTestResult\
    \ random_test(RandomTestConfig config, Property property) {\n    assert(0 <= config.trials);\n\
    \    if (config.trials < 0) config.trials = 0;\n    Random random(config.seed);\n\
    \    for (int trial = 0; trial < config.trials; trial++) {\n        static_assert(std::convertible_to<\n\
    \                      decltype(random_testing_detail::invoke_with_trial(\n  \
    \                        property, random, trial)),\n                      bool>);\n\
    \        bool passed = bool(\n            random_testing_detail::invoke_with_trial(property,\
    \ random, trial));\n        if (!passed) {\n            return random_testing_detail::failure_result(\n\
    \                config, trial, RandomTestFailure::property);\n        }\n   \
    \ }\n    return random_testing_detail::success_result(config);\n}\n\ntemplate\
    \ <class Property>\nRandomTestResult random_test(Property property) {\n    return\
    \ random_test(RandomTestConfig(), std::move(property));\n}\n\n// Generates a case,\
    \ runs an optimized solver and an oracle on separate copies,\n// and compares\
    \ their results. Stops at the first mismatch.\n//\n// generator: (Random&) or\
    \ (Random&, int trial) -> Case\n// solver/oracle: (Case&) -> result\n// on_failure:\
    \ (case, expected, actual, trial, seed) -> void\ntemplate <class Generator, class\
    \ Solver, class Oracle,\n          class OnFailure = IgnoreRandomTestFailure,\n\
    \          class Equal = std::equal_to<>>\nRandomTestResult compare_randomly(RandomTestConfig\
    \ config, Generator generator,\n                                  Solver solver,\
    \ Oracle oracle,\n                                  OnFailure on_failure = {},\
    \ Equal equal = {}) {\n    assert(0 <= config.trials);\n    if (config.trials\
    \ < 0) config.trials = 0;\n    Random random(config.seed);\n\n    for (int trial\
    \ = 0; trial < config.trials; trial++) {\n        auto test_case =\n         \
    \   random_testing_detail::invoke_with_trial(generator, random, trial);\n    \
    \    using Case = std::remove_cvref_t<decltype(test_case)>;\n        static_assert(std::copy_constructible<Case>);\n\
    \n        Case actual_input = test_case;\n        Case expected_input = test_case;\n\
    \        decltype(auto) actual = std::invoke(solver, actual_input);\n        decltype(auto)\
    \ expected = std::invoke(oracle, expected_input);\n        if (!bool(std::invoke(equal,\
    \ actual, expected))) {\n            std::invoke(on_failure, test_case, expected,\
    \ actual, trial,\n                        config.seed);\n            return random_testing_detail::failure_result(\n\
    \                config, trial, RandomTestFailure::mismatch);\n        }\n   \
    \ }\n    return random_testing_detail::success_result(config);\n}\n\ntemplate\
    \ <class Generator, class Solver, class Oracle>\nRandomTestResult compare_randomly(Generator\
    \ generator, Solver solver,\n                                  Oracle oracle)\
    \ {\n    return compare_randomly(RandomTestConfig(), std::move(generator),\n \
    \                           std::move(solver), std::move(oracle));\n}\n\n// Generates\
    \ an input, runs a constructive solver, and validates its output.\n// validator:\
    \ (const Case&, const Answer&) -> bool\ntemplate <class Generator, class Solver,\
    \ class Validator,\n          class OnFailure = IgnoreRandomTestFailure>\nRandomTestResult\
    \ test_constructively(RandomTestConfig config,\n                             \
    \        Generator generator, Solver solver,\n                               \
    \      Validator validator,\n                                     OnFailure on_failure\
    \ = {}) {\n    assert(0 <= config.trials);\n    if (config.trials < 0) config.trials\
    \ = 0;\n    Random random(config.seed);\n\n    for (int trial = 0; trial < config.trials;\
    \ trial++) {\n        auto test_case =\n            random_testing_detail::invoke_with_trial(generator,\
    \ random, trial);\n        using Case = std::remove_cvref_t<decltype(test_case)>;\n\
    \        static_assert(std::copy_constructible<Case>);\n        Case solver_input\
    \ = test_case;\n        auto answer = std::invoke(solver, solver_input);\n   \
    \     if (!bool(std::invoke(validator, std::as_const(test_case),\n           \
    \                   std::as_const(answer)))) {\n            std::invoke(on_failure,\
    \ std::as_const(test_case),\n                        std::as_const(answer), trial,\
    \ config.seed);\n            return random_testing_detail::failure_result(\n \
    \               config, trial, RandomTestFailure::rejected_output);\n        }\n\
    \    }\n    return random_testing_detail::success_result(config);\n}\n\ntemplate\
    \ <class Generator, class Solver, class Validator>\nRandomTestResult test_constructively(Generator\
    \ generator, Solver solver,\n                                     Validator validator)\
    \ {\n    return test_constructively(RandomTestConfig(), std::move(generator),\n\
    \                               std::move(solver), std::move(validator));\n}\n\
    \n// Runs an ordinary solution that reads std::cin and writes std::cout.\n// generator:\
    \ (Random&, ostream&) or (Random&, ostream&, trial) -> void\n// checker: (istream&\
    \ generated_input, istream& candidate_output) -> bool\ntemplate <class Generator,\
    \ class Solution, class Checker,\n          class OnFailure = IgnoreRandomTestFailure>\n\
    RandomTestResult test_streams(RandomTestConfig config, Generator generator,\n\
    \                              Solution solution, Checker checker,\n         \
    \                     OnFailure on_failure = {}) {\n    assert(0 <= config.trials);\n\
    \    if (config.trials < 0) config.trials = 0;\n    Random random(config.seed);\n\
    \n    for (int trial = 0; trial < config.trials; trial++) {\n        std::string\
    \ input = random_testing_detail::generate_stream_input(\n            generator,\
    \ random, trial);\n        std::string output =\n            random_testing_detail::run_with_standard_streams(input,\
    \ solution);\n        std::istringstream input_stream(input);\n        std::istringstream\
    \ output_stream(output);\n        if (!bool(std::invoke(checker, input_stream,\
    \ output_stream))) {\n            std::invoke(on_failure, std::as_const(input),\n\
    \                        std::as_const(output), trial, config.seed);\n       \
    \     return random_testing_detail::failure_result(\n                config, trial,\
    \ RandomTestFailure::rejected_output);\n        }\n    }\n    return random_testing_detail::success_result(config);\n\
    }\n\ntemplate <class Generator, class Solution, class Checker>\nRandomTestResult\
    \ test_streams(Generator generator, Solution solution,\n                     \
    \         Checker checker) {\n    return test_streams(RandomTestConfig(), std::move(generator),\n\
    \                        std::move(solution), std::move(checker));\n}\n\n// generator:\
    \ (Random&) or (Random&, trial) -> InteractiveTestCase<Input, State>\n// solver:\
    \ (const Input&, interaction) or (interaction) -> Answer\n// query_handler: (State&,\
    \ Query) -> Reply\n// validator: (const Input&, const State&, const Answer&) ->\
    \ bool\ntemplate <class Generator, class Solver, class QueryHandler, class Validator,\n\
    \          class OnFailure = IgnoreRandomTestFailure>\nRandomTestResult test_interactively(RandomTestConfig\
    \ config, int query_limit,\n                                    Generator generator,\
    \ Solver solver,\n                                    QueryHandler query_handler,\n\
    \                                    Validator validator,\n                  \
    \                  OnFailure on_failure = {}) {\n    assert(0 <= config.trials);\n\
    \    assert(0 <= query_limit);\n    if (config.trials < 0) config.trials = 0;\n\
    \    if (query_limit < 0) query_limit = 0;\n    Random random(config.seed);\n\n\
    \    for (int trial = 0; trial < config.trials; trial++) {\n        auto test_case\
    \ =\n            random_testing_detail::invoke_with_trial(generator, random, trial);\n\
    \        using State = std::remove_cvref_t<decltype(test_case.state)>;\n     \
    \   RandomInteraction<State, QueryHandler> interaction(\n            test_case.state,\
    \ query_handler, query_limit);\n\n        try {\n            auto answer = random_testing_detail::invoke_interactive_solver(\n\
    \                solver, std::as_const(test_case.input), interaction);\n     \
    \       interaction.record_answer(answer);\n            if (!bool(std::invoke(validator,\
    \ std::as_const(test_case.input),\n                                  std::as_const(test_case.state),\n\
    \                                  std::as_const(answer)))) {\n              \
    \  RandomTestResult result =\n                    random_testing_detail::failure_result(\n\
    \                        config, trial, RandomTestFailure::rejected_output,\n\
    \                        interaction.query_count());\n                std::invoke(on_failure,\
    \ std::as_const(test_case),\n                            interaction.transcript(),\
    \ trial, config.seed,\n                            result.failure);\n        \
    \        return result;\n            }\n        } catch (const random_testing_detail::InteractionAbort&\
    \ failure) {\n            interaction.record_failure(failure.message);\n     \
    \       RandomTestResult result = random_testing_detail::failure_result(\n   \
    \             config, trial, failure.failure, interaction.query_count());\n  \
    \          std::invoke(on_failure, std::as_const(test_case),\n               \
    \         interaction.transcript(), trial, config.seed,\n                    \
    \    result.failure);\n            return result;\n        }\n    }\n    return\
    \ random_testing_detail::success_result(config);\n}\n\ntemplate <class Generator,\
    \ class Solver, class QueryHandler, class Validator>\nRandomTestResult test_interactively(int\
    \ query_limit, Generator generator,\n                                    Solver\
    \ solver, QueryHandler query_handler,\n                                    Validator\
    \ validator) {\n    return test_interactively(RandomTestConfig(), query_limit,\n\
    \                              std::move(generator), std::move(solver),\n    \
    \                          std::move(query_handler), std::move(validator));\n\
    }\n\n// Runs an ordinary interactive solution using std::cin and std::cout.\n\
    // generator: (Random&, ostream&) or (Random&, ostream&, trial) -> JudgeState\n\
    // query_handler: (JudgeState&, istream& query, ostream& response) -> void\n//\
    \ checker: (istream& public_input, const JudgeState&,\n//           istream& final_output)\
    \ -> bool\ntemplate <class Generator, class Solution, class QueryHandler, class\
    \ Checker,\n          class OnFailure = IgnoreRandomTestFailure>\nRandomTestResult\
    \ test_interactive_streams(\n    RandomTestConfig config, int query_limit, Generator\
    \ generator,\n    Solution solution, QueryHandler query_handler, Checker checker,\n\
    \    OnFailure on_failure = {}) {\n    assert(0 <= config.trials);\n    assert(0\
    \ <= query_limit);\n    if (config.trials < 0) config.trials = 0;\n    if (query_limit\
    \ < 0) query_limit = 0;\n    Random random(config.seed);\n\n    for (int trial\
    \ = 0; trial < config.trials; trial++) {\n        std::ostringstream generated_input;\n\
    \        auto state =\n            random_testing_detail::generate_interactive_stream_input(\n\
    \                generator, random, generated_input, trial);\n        std::string\
    \ input = generated_input.str();\n        std::stringbuf candidate_output(std::ios::out);\n\
    \        using State = std::remove_cvref_t<decltype(state)>;\n        random_testing_detail::InteractiveStreamBuffer<State,\
    \ QueryHandler>\n            input_buffer(state, query_handler, candidate_output,\
    \ input,\n                         query_limit);\n        {\n            random_testing_detail::StandardStreamRedirect\
    \ redirect(\n                &input_buffer, &candidate_output);\n            std::invoke(solution);\n\
    \        }\n        input_buffer.finish();\n        if (input_buffer.exception())\
    \ {\n            std::rethrow_exception(input_buffer.exception());\n        }\n\
    \n        RandomTestFailure failure = input_buffer.failure();\n        if (failure\
    \ != RandomTestFailure::none) {\n            RandomTestResult result = random_testing_detail::failure_result(\n\
    \                config, trial, failure, input_buffer.query_count());\n      \
    \      std::invoke(on_failure, std::as_const(input),\n                       \
    \ std::as_const(state), input_buffer.transcript(), trial,\n                  \
    \      config.seed, failure);\n            return result;\n        }\n\n     \
    \   std::istringstream input_stream(input);\n        std::istringstream output_stream(input_buffer.transcript().answer);\n\
    \        if (!bool(std::invoke(checker, input_stream, std::as_const(state),\n\
    \                              output_stream))) {\n            RandomTestResult\
    \ result = random_testing_detail::failure_result(\n                config, trial,\
    \ RandomTestFailure::rejected_output,\n                input_buffer.query_count());\n\
    \            std::invoke(on_failure, std::as_const(input),\n                 \
    \       std::as_const(state), input_buffer.transcript(), trial,\n            \
    \            config.seed, result.failure);\n            return result;\n     \
    \   }\n    }\n    return random_testing_detail::success_result(config);\n}\n\n\
    template <class Generator, class Solution, class QueryHandler, class Checker>\n\
    RandomTestResult test_interactive_streams(\n    int query_limit, Generator generator,\
    \ Solution solution,\n    QueryHandler query_handler, Checker checker) {\n   \
    \ return test_interactive_streams(\n        RandomTestConfig(), query_limit, std::move(generator),\n\
    \        std::move(solution), std::move(query_handler), std::move(checker));\n\
    }\n\n// Short contest interface. Prints failure metadata and terminates on failure.\n\
    template <class Property>\nRandomTestResult stress_test(Property property, int\
    \ trials = 1000,\n                             std::uint64_t seed = default_random_test_seed)\
    \ {\n    RandomTestConfig config;\n    config.trials = trials;\n    config.seed\
    \ = seed;\n    RandomTestResult result = random_test(config, std::move(property));\n\
    \    if (!result) {\n        std::cerr << \"random test failed: seed=\" << result.seed\n\
    \                  << \" trial=\" << result.failed_trial << '\\n';\n        std::abort();\n\
    \    }\n    return result;\n}\n\n// Short optimized-versus-brute-force interface.\n\
    template <class Generator, class Solver, class Oracle>\nrequires(!std::integral<std::remove_cvref_t<Solver>>\
    \ &&\n         !std::integral<std::remove_cvref_t<Oracle>>)\nRandomTestResult\
    \ stress_test(Generator generator, Solver solver, Oracle oracle,\n           \
    \                  int trials = 1000,\n                             std::uint64_t\
    \ seed = default_random_test_seed) {\n    RandomTestConfig config;\n    config.trials\
    \ = trials;\n    config.seed = seed;\n    RandomTestResult result = compare_randomly(\n\
    \        config, std::move(generator), std::move(solver), std::move(oracle),\n\
    \        PrintRandomTestFailure());\n    if (!result) std::abort();\n    return\
    \ result;\n}\n\ntemplate <class Generator, class Solver, class Validator>\nRandomTestResult\
    \ constructive_stress_test(\n    Generator generator, Solver solver, Validator\
    \ validator,\n    int trials = 1000, std::uint64_t seed = default_random_test_seed)\
    \ {\n    RandomTestConfig config;\n    config.trials = trials;\n    config.seed\
    \ = seed;\n    RandomTestResult result = test_constructively(\n        config,\
    \ std::move(generator), std::move(solver),\n        std::move(validator), PrintConstructiveTestFailure());\n\
    \    if (!result) std::abort();\n    return result;\n}\n\ntemplate <class Generator,\
    \ class Solution, class Checker>\nRandomTestResult stream_stress_test(\n    Generator\
    \ generator, Solution solution, Checker checker,\n    int trials = 1000, std::uint64_t\
    \ seed = default_random_test_seed) {\n    RandomTestConfig config;\n    config.trials\
    \ = trials;\n    config.seed = seed;\n    RandomTestResult result = test_streams(\n\
    \        config, std::move(generator), std::move(solution),\n        std::move(checker),\
    \ PrintStreamTestFailure());\n    if (!result) std::abort();\n    return result;\n\
    }\n\ntemplate <class Generator, class Solver, class QueryHandler, class Validator>\n\
    RandomTestResult interactive_stress_test(\n    int query_limit, Generator generator,\
    \ Solver solver,\n    QueryHandler query_handler, Validator validator, int trials\
    \ = 1000,\n    std::uint64_t seed = default_random_test_seed) {\n    RandomTestConfig\
    \ config;\n    config.trials = trials;\n    config.seed = seed;\n    RandomTestResult\
    \ result = test_interactively(\n        config, query_limit, std::move(generator),\
    \ std::move(solver),\n        std::move(query_handler), std::move(validator),\n\
    \        PrintInteractiveTestFailure());\n    if (!result) std::abort();\n   \
    \ return result;\n}\n\ntemplate <class Generator, class Solution, class QueryHandler,\
    \ class Checker>\nRandomTestResult interactive_stream_stress_test(\n    int query_limit,\
    \ Generator generator, Solution solution,\n    QueryHandler query_handler, Checker\
    \ checker, int trials = 1000,\n    std::uint64_t seed = default_random_test_seed)\
    \ {\n    RandomTestConfig config;\n    config.trials = trials;\n    config.seed\
    \ = seed;\n    RandomTestResult result = test_interactive_streams(\n        config,\
    \ query_limit, std::move(generator), std::move(solution),\n        std::move(query_handler),\
    \ std::move(checker),\n        PrintInteractiveStreamTestFailure());\n    if (!result)\
    \ std::abort();\n    return result;\n}\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/utilities/random_testing.test.cpp\"\n\n#line 1 \"\
    utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#line 15 \"utilities/fast_io.hpp\"\
    \n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/utilities/random_testing.test.cpp\"\
    \n\n#ifndef NDEBUG\nvoid test_properties() {\n    using namespace m1une::utilities;\n\
    \n    RandomTestConfig config;\n    config.trials = 100;\n    config.seed = 12345;\n\
    \    RandomTestResult success = random_test(config, [](Random& random) {\n   \
    \     long long value = random.uniform(-1000, 1000);\n        return value * value\
    \ >= 0;\n    });\n    assert(success.passed());\n    assert(bool(success));\n\
    \    assert(success.completed_trials == 100);\n    assert(success.failed_trial\
    \ == -1);\n    assert(success.seed == config.seed);\n\n    RandomTestResult failure\
    \ = random_test(\n        config, [](Random&, int trial) { return trial != 17;\
    \ });\n    assert(!failure.passed());\n    assert(!bool(failure));\n    assert(failure.completed_trials\
    \ == 17);\n    assert(failure.failed_trial == 17);\n    assert(failure.failure\
    \ == RandomTestFailure::property);\n\n    auto shorthand = random_test([](Random&,\
    \ int trial) { return trial < 1000; });\n    assert(shorthand.passed());\n   \
    \ auto required = stress_test(\n        [](Random&, int trial) { return trial\
    \ < 25; }, 25, 777);\n    assert(required.passed());\n    assert(required.seed\
    \ == 777);\n}\n\nvoid test_comparison() {\n    using namespace m1une::utilities;\n\
    \n    RandomTestConfig config;\n    config.trials = 500;\n    config.seed = 67890;\n\
    \    auto success = compare_randomly(\n        config,\n        [](Random& random)\
    \ {\n            int size = int(random.uniform(0, 20));\n            std::vector<int>\
    \ values(size);\n            for (int& value : values) value = int(random.uniform(-20,\
    \ 20));\n            return values;\n        },\n        [](std::vector<int>&\
    \ values) {\n            std::sort(values.begin(), values.end());\n          \
    \  return values;\n        },\n        [](std::vector<int>& values) {\n      \
    \      for (int i = 0; i < int(values.size()); i++) {\n                for (int\
    \ j = i + 1; j < int(values.size()); j++) {\n                    if (values[j]\
    \ < values[i]) std::swap(values[i], values[j]);\n                }\n         \
    \   }\n            return values;\n        });\n    assert(success.passed());\n\
    \n    auto mutation_isolated = compare_randomly(\n        config,\n        [](Random&\
    \ random) {\n            int size = int(random.uniform(0, 20));\n            std::vector<int>\
    \ values(size);\n            for (int& value : values) value = int(random.uniform(-20,\
    \ 20));\n            return values;\n        },\n        [](std::vector<int>&\
    \ values) {\n            int sum = std::accumulate(values.begin(), values.end(),\
    \ 0);\n            values.clear();\n            return sum;\n        },\n    \
    \    [](std::vector<int>& values) {\n            return std::accumulate(values.begin(),\
    \ values.end(), 0);\n        });\n    assert(mutation_isolated.passed());\n\n\
    \    auto quick = stress_test(\n        [](Random& random) { return int(random.uniform(-10,\
    \ 10)); },\n        [](int& value) { return value * value; },\n        [](int&\
    \ value) {\n            int magnitude = value < 0 ? -value : value;\n        \
    \    int result = 0;\n            for (int i = 0; i < magnitude; i++) result +=\
    \ magnitude;\n            return result;\n        },\n        50, 999);\n    assert(quick.passed());\n\
    \n    int callback_count = 0;\n    int callback_trial = -1;\n    int callback_case\
    \ = -1;\n    int callback_expected = -1;\n    int callback_actual = -1;\n    std::uint64_t\
    \ callback_seed = 0;\n    auto failure = compare_randomly(\n        config,\n\
    \        [](Random&, int trial) { return trial; },\n        [](int& value) { return\
    \ value == 23 ? value + 1 : value; },\n        [](int& value) { return value;\
    \ },\n        [&](int input, int expected, int actual, int trial,\n          \
    \  std::uint64_t seed) {\n            callback_count++;\n            callback_trial\
    \ = trial;\n            callback_case = input;\n            callback_expected\
    \ = expected;\n            callback_actual = actual;\n            callback_seed\
    \ = seed;\n        });\n    assert(failure.failed_trial == 23);\n    assert(failure.failure\
    \ == RandomTestFailure::mismatch);\n    assert(callback_count == 1);\n    assert(callback_trial\
    \ == 23);\n    assert(callback_case == 23);\n    assert(callback_expected == 23);\n\
    \    assert(callback_actual == 24);\n    assert(callback_seed == config.seed);\n\
    \n    RandomTestConfig empty_config;\n    empty_config.trials = 0;\n    auto empty\
    \ = random_test(empty_config, [](Random&) { return false; });\n    assert(empty.passed());\n\
    \    assert(empty.completed_trials == 0);\n}\n\nvoid test_constructive() {\n \
    \   using namespace m1une::utilities;\n\n    RandomTestConfig config;\n    config.trials\
    \ = 200;\n    config.seed = 13579;\n    auto success = test_constructively(\n\
    \        config,\n        [](Random& random) {\n            int size = int(random.uniform(0,\
    \ 30));\n            return random.sequence(size, -20, 20);\n        },\n    \
    \    [](std::vector<int>& values) {\n            std::vector<int> order(values.size());\n\
    \            std::iota(order.begin(), order.end(), 0);\n            std::sort(order.begin(),\
    \ order.end(), [&](int first, int second) {\n                return values[first]\
    \ < values[second];\n            });\n            values.clear();\n          \
    \  return order;\n        },\n        [](const std::vector<int>& values, const\
    \ std::vector<int>& order) {\n            if (values.size() != order.size()) return\
    \ false;\n            std::vector<bool> used(values.size());\n            for\
    \ (int index = 0; index < int(order.size()); index++) {\n                if (order[index]\
    \ < 0 || int(values.size()) <= order[index]) {\n                    return false;\n\
    \                }\n                if (used[order[index]]) return false;\n  \
    \              used[order[index]] = true;\n                if (0 < index &&\n\
    \                    values[order[index]] < values[order[index - 1]]) {\n    \
    \                return false;\n                }\n            }\n           \
    \ return true;\n        });\n    assert(success.passed());\n\n    int callback_count\
    \ = 0;\n    auto failure = test_constructively(\n        config, [](Random&, int\
    \ trial) { return trial + 1; },\n        [](int& value) { return value == 8 ?\
    \ 0 : value; },\n        [](int input, int answer) { return input == answer; },\n\
    \        [&](int input, int answer, int trial, std::uint64_t seed) {\n       \
    \     callback_count++;\n            assert(input == 8);\n            assert(answer\
    \ == 0);\n            assert(trial == 7);\n            assert(seed == config.seed);\n\
    \        });\n    assert(failure.failed_trial == 7);\n    assert(failure.failure\
    \ == RandomTestFailure::rejected_output);\n    assert(callback_count == 1);\n\n\
    \    auto quick = constructive_stress_test(\n        [](Random& random) { return\
    \ int(random.uniform(0, 100)); },\n        [](int& value) { return value; },\n\
    \        [](const int& input, const int& answer) { return input == answer; },\n\
    \        20, 97531);\n    assert(quick.passed());\n}\n\nvoid test_interactive()\
    \ {\n    using namespace m1une::utilities;\n\n    RandomTestConfig config;\n \
    \   config.trials = 300;\n    config.seed = 24680;\n    auto success = test_interactively(\n\
    \        config, 10,\n        [](Random& random) {\n            int upper = int(random.uniform(1,\
    \ 1000));\n            int secret = int(random.uniform(0, upper));\n         \
    \   return interactive_test_case(upper, secret);\n        },\n        [](const\
    \ int& upper, auto& interaction) {\n            int low = 0;\n            int\
    \ high = upper;\n            while (low < high) {\n                int middle\
    \ = (low + high) / 2;\n                int comparison = interaction.ask(middle);\n\
    \                if (comparison <= 0) {\n                    high = middle;\n\
    \                } else {\n                    low = middle + 1;\n           \
    \     }\n            }\n            return low;\n        },\n        [](int& secret,\
    \ int guess) {\n            if (guess < 0) reject_query(\"negative guess\");\n\
    \            if (secret < guess) return -1;\n            if (guess < secret) return\
    \ 1;\n            return 0;\n        },\n        [](const int& upper, const int&\
    \ secret, const int& answer) {\n            return 0 <= answer && answer <= upper\
    \ && answer == secret;\n        });\n    assert(success.passed());\n\n    RandomTestConfig\
    \ one_trial;\n    one_trial.trials = 1;\n    one_trial.seed = 112233;\n    int\
    \ callback_count = 0;\n    auto invalid = test_interactively(\n        one_trial,\
    \ 5,\n        [](Random&) { return interactive_test_case(10, 4); },\n        [](const\
    \ int&, auto& interaction) {\n            interaction.ask(-1);\n            return\
    \ 0;\n        },\n        [](int&, int query) {\n            if (query < 0) reject_query(\"\
    query is outside [0, 10]\");\n            return 0;\n        },\n        [](const\
    \ int&, const int&, const int&) { return true; },\n        [&](const auto&, const\
    \ InteractionTranscript& transcript, int trial,\n            std::uint64_t seed,\
    \ RandomTestFailure reason) {\n            callback_count++;\n            assert(trial\
    \ == 0);\n            assert(seed == one_trial.seed);\n            assert(reason\
    \ == RandomTestFailure::invalid_query);\n            assert(transcript.exchanges.size()\
    \ == 1);\n            assert(transcript.exchanges[0].query == \"-1\");\n     \
    \       assert(!transcript.exchanges[0].responded);\n            assert(transcript.failure_message\
    \ ==\n                   \"query is outside [0, 10]\");\n        });\n    assert(invalid.failure\
    \ == RandomTestFailure::invalid_query);\n    assert(invalid.query_count == 1);\n\
    \    assert(callback_count == 1);\n\n    auto too_many_queries = test_interactively(\n\
    \        one_trial, 1,\n        [](Random&) { return interactive_test_case(0,\
    \ 0); },\n        [](auto& interaction) {\n            interaction.ask(1);\n \
    \           interaction.ask(2);\n            return 0;\n        },\n        [](int&,\
    \ int query) { return query; },\n        [](const int&, const int&, const int&)\
    \ { return true; });\n    assert(too_many_queries.failure == RandomTestFailure::query_limit);\n\
    \    assert(too_many_queries.query_count == 2);\n\n    auto wrong_answer = test_interactively(\n\
    \        one_trial, 0,\n        [](Random&) { return interactive_test_case(10,\
    \ 7); },\n        [](const int&, auto&) { return 6; },\n        [](int&, int query)\
    \ { return query; },\n        [](const int&, const int& secret, const int& answer)\
    \ {\n            return secret == answer;\n        });\n    assert(wrong_answer.failure\
    \ == RandomTestFailure::rejected_output);\n    assert(wrong_answer.query_count\
    \ == 0);\n\n    auto quick = interactive_stress_test(\n        0,\n        [](Random&\
    \ random) {\n            int value = int(random.uniform(-100, 100));\n       \
    \     return interactive_test_case(value, value);\n        },\n        [](const\
    \ int& input, auto&) { return input; },\n        [](int&, int query) { return\
    \ query; },\n        [](const int&, const int& state, const int& answer) {\n \
    \           return state == answer;\n        },\n        20, 86420);\n    assert(quick.passed());\n\
    }\n\nvoid test_stream_interface() {\n    using namespace m1une::utilities;\n\n\
    \    RandomTestConfig config;\n    config.trials = 200;\n    config.seed = 424242;\n\
    \    auto generate = [](Random& random, std::ostream& input) {\n        int size\
    \ = int(random.uniform(0, 30));\n        input << size << '\\n';\n        for\
    \ (int value : random.sequence(size, -20, 20)) {\n            input << value <<\
    \ ' ';\n        }\n        input << '\\n';\n    };\n    auto solve = [] {\n  \
    \      int size;\n        std::cin >> size;\n        std::vector<int> values(size);\n\
    \        for (int& value : values) std::cin >> value;\n        std::sort(values.begin(),\
    \ values.end());\n        for (int value : values) std::cout << value << ' ';\n\
    \        std::cout << '\\n';\n    };\n    auto check = [](std::istream& input,\
    \ std::istream& output) {\n        int size;\n        input >> size;\n       \
    \ std::vector<int> expected(size);\n        for (int& value : expected) input\
    \ >> value;\n        std::sort(expected.begin(), expected.end());\n        std::vector<int>\
    \ actual(size);\n        for (int& value : actual) {\n            if (!(output\
    \ >> value)) return false;\n        }\n        std::string extra;\n        return\
    \ expected == actual && !(output >> extra);\n    };\n    auto success = test_streams(config,\
    \ generate, solve, check);\n    assert(success.passed());\n\n    int callback_count\
    \ = 0;\n    RandomTestConfig one_trial;\n    one_trial.trials = 1;\n    one_trial.seed\
    \ = 515151;\n    auto failure = test_streams(\n        one_trial,\n        [](Random&,\
    \ std::ostream& input) { input << \"3\\n1 2 3\\n\"; },\n        [] {\n       \
    \     int size;\n            std::cin >> size;\n            std::cout << size\
    \ - 1 << '\\n';\n        },\n        [](std::istream&, std::istream& output) {\n\
    \            int answer;\n            return bool(output >> answer) && answer\
    \ == 3;\n        },\n        [&](const std::string& input, const std::string&\
    \ output, int trial,\n            std::uint64_t seed) {\n            callback_count++;\n\
    \            assert(input == \"3\\n1 2 3\\n\");\n            assert(output ==\
    \ \"2\\n\");\n            assert(trial == 0);\n            assert(seed == one_trial.seed);\n\
    \        });\n    assert(failure.failure == RandomTestFailure::rejected_output);\n\
    \    assert(callback_count == 1);\n\n    auto quick = stream_stress_test(generate,\
    \ solve, check, 20, 616161);\n    assert(quick.passed());\n}\n\nvoid test_interactive_stream_interface()\
    \ {\n    using namespace m1une::utilities;\n\n    auto generate = [](Random& random,\
    \ std::ostream& input) {\n        int upper = int(random.uniform(1, 1000));\n\
    \        input << upper << '\\n';\n        return int(random.uniform(0, upper));\n\
    \    };\n    auto solve = [] {\n        int upper;\n        std::cin >> upper;\n\
    \        int low = 0;\n        int high = upper;\n        while (low < high) {\n\
    \            int middle = (low + high) / 2;\n            std::cout << \"? \" <<\
    \ middle << std::endl;\n            int comparison;\n            std::cin >> comparison;\n\
    \            if (comparison <= 0) high = middle;\n            else low = middle\
    \ + 1;\n        }\n        std::cout << \"! \" << low << std::endl;\n    };\n\
    \    auto reply = [](int& secret, std::istream& query,\n                    std::ostream&\
    \ response) {\n        char type;\n        int guess;\n        std::string extra;\n\
    \        if (!(query >> type >> guess) || type != '?' || query >> extra) {\n \
    \           reject_query(\"expected: ? x\");\n        }\n        if (secret <\
    \ guess) response << -1;\n        else if (guess < secret) response << 1;\n  \
    \      else response << 0;\n    };\n    auto check = [](std::istream& input, const\
    \ int& secret,\n                    std::istream& output) {\n        int upper;\n\
    \        char type;\n        int answer;\n        std::string extra;\n       \
    \ input >> upper;\n        return bool(output >> type >> answer) && type == '!'\
    \ &&\n               0 <= answer && answer <= upper && answer == secret &&\n \
    \              !(output >> extra);\n    };\n\n    auto success = interactive_stream_stress_test(\n\
    \        10, generate, solve, reply, check, 200, 717171);\n    assert(success.passed());\n\
    \n    RandomTestConfig one_trial;\n    one_trial.trials = 1;\n    one_trial.seed\
    \ = 818181;\n    int callback_count = 0;\n    auto invalid = test_interactive_streams(\n\
    \        one_trial, 1,\n        [](Random&, std::ostream& input) {\n         \
    \   input << \"10\\n\";\n            return 5;\n        },\n        [] {\n   \
    \         int upper;\n            std::cin >> upper;\n            std::cout <<\
    \ \"invalid query\" << std::endl;\n            int response;\n            std::cin\
    \ >> response;\n        },\n        reply, check,\n        [&](const std::string&\
    \ input, const int& state,\n            const InteractionTranscript& transcript,\
    \ int trial,\n            std::uint64_t seed, RandomTestFailure reason) {\n  \
    \          callback_count++;\n            assert(input == \"10\\n\");\n      \
    \      assert(state == 5);\n            assert(transcript.exchanges.size() ==\
    \ 1);\n            assert(transcript.exchanges[0].query == \"invalid query\");\n\
    \            assert(!transcript.exchanges[0].responded);\n            assert(transcript.failure_message\
    \ == \"expected: ? x\");\n            assert(trial == 0);\n            assert(seed\
    \ == one_trial.seed);\n            assert(reason == RandomTestFailure::invalid_query);\n\
    \        });\n    assert(invalid.failure == RandomTestFailure::invalid_query);\n\
    \    assert(invalid.query_count == 1);\n    assert(callback_count == 1);\n\n \
    \   auto query_limit = test_interactive_streams(\n        one_trial, 0,\n    \
    \    [](Random&, std::ostream& input) {\n            input << \"10\\n\";\n   \
    \         return 5;\n        },\n        [] {\n            int upper;\n      \
    \      std::cin >> upper;\n            std::cout << \"? 5\" << std::endl;\n  \
    \          int response;\n            std::cin >> response;\n        },\n    \
    \    reply, check);\n    assert(query_limit.failure == RandomTestFailure::query_limit);\n\
    \    assert(query_limit.query_count == 1);\n}\n#endif\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n#ifndef NDEBUG\n\
    \    test_properties();\n    test_comparison();\n    test_constructive();\n  \
    \  test_interactive();\n    test_stream_interface();\n    test_interactive_stream_interface();\n\
    #endif\n\n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a\
    \ + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../utilities/random_testing.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <numeric>\n\
    #include <string>\n#include <vector>\n\n#ifndef NDEBUG\nvoid test_properties()\
    \ {\n    using namespace m1une::utilities;\n\n    RandomTestConfig config;\n \
    \   config.trials = 100;\n    config.seed = 12345;\n    RandomTestResult success\
    \ = random_test(config, [](Random& random) {\n        long long value = random.uniform(-1000,\
    \ 1000);\n        return value * value >= 0;\n    });\n    assert(success.passed());\n\
    \    assert(bool(success));\n    assert(success.completed_trials == 100);\n  \
    \  assert(success.failed_trial == -1);\n    assert(success.seed == config.seed);\n\
    \n    RandomTestResult failure = random_test(\n        config, [](Random&, int\
    \ trial) { return trial != 17; });\n    assert(!failure.passed());\n    assert(!bool(failure));\n\
    \    assert(failure.completed_trials == 17);\n    assert(failure.failed_trial\
    \ == 17);\n    assert(failure.failure == RandomTestFailure::property);\n\n   \
    \ auto shorthand = random_test([](Random&, int trial) { return trial < 1000; });\n\
    \    assert(shorthand.passed());\n    auto required = stress_test(\n        [](Random&,\
    \ int trial) { return trial < 25; }, 25, 777);\n    assert(required.passed());\n\
    \    assert(required.seed == 777);\n}\n\nvoid test_comparison() {\n    using namespace\
    \ m1une::utilities;\n\n    RandomTestConfig config;\n    config.trials = 500;\n\
    \    config.seed = 67890;\n    auto success = compare_randomly(\n        config,\n\
    \        [](Random& random) {\n            int size = int(random.uniform(0, 20));\n\
    \            std::vector<int> values(size);\n            for (int& value : values)\
    \ value = int(random.uniform(-20, 20));\n            return values;\n        },\n\
    \        [](std::vector<int>& values) {\n            std::sort(values.begin(),\
    \ values.end());\n            return values;\n        },\n        [](std::vector<int>&\
    \ values) {\n            for (int i = 0; i < int(values.size()); i++) {\n    \
    \            for (int j = i + 1; j < int(values.size()); j++) {\n            \
    \        if (values[j] < values[i]) std::swap(values[i], values[j]);\n       \
    \         }\n            }\n            return values;\n        });\n    assert(success.passed());\n\
    \n    auto mutation_isolated = compare_randomly(\n        config,\n        [](Random&\
    \ random) {\n            int size = int(random.uniform(0, 20));\n            std::vector<int>\
    \ values(size);\n            for (int& value : values) value = int(random.uniform(-20,\
    \ 20));\n            return values;\n        },\n        [](std::vector<int>&\
    \ values) {\n            int sum = std::accumulate(values.begin(), values.end(),\
    \ 0);\n            values.clear();\n            return sum;\n        },\n    \
    \    [](std::vector<int>& values) {\n            return std::accumulate(values.begin(),\
    \ values.end(), 0);\n        });\n    assert(mutation_isolated.passed());\n\n\
    \    auto quick = stress_test(\n        [](Random& random) { return int(random.uniform(-10,\
    \ 10)); },\n        [](int& value) { return value * value; },\n        [](int&\
    \ value) {\n            int magnitude = value < 0 ? -value : value;\n        \
    \    int result = 0;\n            for (int i = 0; i < magnitude; i++) result +=\
    \ magnitude;\n            return result;\n        },\n        50, 999);\n    assert(quick.passed());\n\
    \n    int callback_count = 0;\n    int callback_trial = -1;\n    int callback_case\
    \ = -1;\n    int callback_expected = -1;\n    int callback_actual = -1;\n    std::uint64_t\
    \ callback_seed = 0;\n    auto failure = compare_randomly(\n        config,\n\
    \        [](Random&, int trial) { return trial; },\n        [](int& value) { return\
    \ value == 23 ? value + 1 : value; },\n        [](int& value) { return value;\
    \ },\n        [&](int input, int expected, int actual, int trial,\n          \
    \  std::uint64_t seed) {\n            callback_count++;\n            callback_trial\
    \ = trial;\n            callback_case = input;\n            callback_expected\
    \ = expected;\n            callback_actual = actual;\n            callback_seed\
    \ = seed;\n        });\n    assert(failure.failed_trial == 23);\n    assert(failure.failure\
    \ == RandomTestFailure::mismatch);\n    assert(callback_count == 1);\n    assert(callback_trial\
    \ == 23);\n    assert(callback_case == 23);\n    assert(callback_expected == 23);\n\
    \    assert(callback_actual == 24);\n    assert(callback_seed == config.seed);\n\
    \n    RandomTestConfig empty_config;\n    empty_config.trials = 0;\n    auto empty\
    \ = random_test(empty_config, [](Random&) { return false; });\n    assert(empty.passed());\n\
    \    assert(empty.completed_trials == 0);\n}\n\nvoid test_constructive() {\n \
    \   using namespace m1une::utilities;\n\n    RandomTestConfig config;\n    config.trials\
    \ = 200;\n    config.seed = 13579;\n    auto success = test_constructively(\n\
    \        config,\n        [](Random& random) {\n            int size = int(random.uniform(0,\
    \ 30));\n            return random.sequence(size, -20, 20);\n        },\n    \
    \    [](std::vector<int>& values) {\n            std::vector<int> order(values.size());\n\
    \            std::iota(order.begin(), order.end(), 0);\n            std::sort(order.begin(),\
    \ order.end(), [&](int first, int second) {\n                return values[first]\
    \ < values[second];\n            });\n            values.clear();\n          \
    \  return order;\n        },\n        [](const std::vector<int>& values, const\
    \ std::vector<int>& order) {\n            if (values.size() != order.size()) return\
    \ false;\n            std::vector<bool> used(values.size());\n            for\
    \ (int index = 0; index < int(order.size()); index++) {\n                if (order[index]\
    \ < 0 || int(values.size()) <= order[index]) {\n                    return false;\n\
    \                }\n                if (used[order[index]]) return false;\n  \
    \              used[order[index]] = true;\n                if (0 < index &&\n\
    \                    values[order[index]] < values[order[index - 1]]) {\n    \
    \                return false;\n                }\n            }\n           \
    \ return true;\n        });\n    assert(success.passed());\n\n    int callback_count\
    \ = 0;\n    auto failure = test_constructively(\n        config, [](Random&, int\
    \ trial) { return trial + 1; },\n        [](int& value) { return value == 8 ?\
    \ 0 : value; },\n        [](int input, int answer) { return input == answer; },\n\
    \        [&](int input, int answer, int trial, std::uint64_t seed) {\n       \
    \     callback_count++;\n            assert(input == 8);\n            assert(answer\
    \ == 0);\n            assert(trial == 7);\n            assert(seed == config.seed);\n\
    \        });\n    assert(failure.failed_trial == 7);\n    assert(failure.failure\
    \ == RandomTestFailure::rejected_output);\n    assert(callback_count == 1);\n\n\
    \    auto quick = constructive_stress_test(\n        [](Random& random) { return\
    \ int(random.uniform(0, 100)); },\n        [](int& value) { return value; },\n\
    \        [](const int& input, const int& answer) { return input == answer; },\n\
    \        20, 97531);\n    assert(quick.passed());\n}\n\nvoid test_interactive()\
    \ {\n    using namespace m1une::utilities;\n\n    RandomTestConfig config;\n \
    \   config.trials = 300;\n    config.seed = 24680;\n    auto success = test_interactively(\n\
    \        config, 10,\n        [](Random& random) {\n            int upper = int(random.uniform(1,\
    \ 1000));\n            int secret = int(random.uniform(0, upper));\n         \
    \   return interactive_test_case(upper, secret);\n        },\n        [](const\
    \ int& upper, auto& interaction) {\n            int low = 0;\n            int\
    \ high = upper;\n            while (low < high) {\n                int middle\
    \ = (low + high) / 2;\n                int comparison = interaction.ask(middle);\n\
    \                if (comparison <= 0) {\n                    high = middle;\n\
    \                } else {\n                    low = middle + 1;\n           \
    \     }\n            }\n            return low;\n        },\n        [](int& secret,\
    \ int guess) {\n            if (guess < 0) reject_query(\"negative guess\");\n\
    \            if (secret < guess) return -1;\n            if (guess < secret) return\
    \ 1;\n            return 0;\n        },\n        [](const int& upper, const int&\
    \ secret, const int& answer) {\n            return 0 <= answer && answer <= upper\
    \ && answer == secret;\n        });\n    assert(success.passed());\n\n    RandomTestConfig\
    \ one_trial;\n    one_trial.trials = 1;\n    one_trial.seed = 112233;\n    int\
    \ callback_count = 0;\n    auto invalid = test_interactively(\n        one_trial,\
    \ 5,\n        [](Random&) { return interactive_test_case(10, 4); },\n        [](const\
    \ int&, auto& interaction) {\n            interaction.ask(-1);\n            return\
    \ 0;\n        },\n        [](int&, int query) {\n            if (query < 0) reject_query(\"\
    query is outside [0, 10]\");\n            return 0;\n        },\n        [](const\
    \ int&, const int&, const int&) { return true; },\n        [&](const auto&, const\
    \ InteractionTranscript& transcript, int trial,\n            std::uint64_t seed,\
    \ RandomTestFailure reason) {\n            callback_count++;\n            assert(trial\
    \ == 0);\n            assert(seed == one_trial.seed);\n            assert(reason\
    \ == RandomTestFailure::invalid_query);\n            assert(transcript.exchanges.size()\
    \ == 1);\n            assert(transcript.exchanges[0].query == \"-1\");\n     \
    \       assert(!transcript.exchanges[0].responded);\n            assert(transcript.failure_message\
    \ ==\n                   \"query is outside [0, 10]\");\n        });\n    assert(invalid.failure\
    \ == RandomTestFailure::invalid_query);\n    assert(invalid.query_count == 1);\n\
    \    assert(callback_count == 1);\n\n    auto too_many_queries = test_interactively(\n\
    \        one_trial, 1,\n        [](Random&) { return interactive_test_case(0,\
    \ 0); },\n        [](auto& interaction) {\n            interaction.ask(1);\n \
    \           interaction.ask(2);\n            return 0;\n        },\n        [](int&,\
    \ int query) { return query; },\n        [](const int&, const int&, const int&)\
    \ { return true; });\n    assert(too_many_queries.failure == RandomTestFailure::query_limit);\n\
    \    assert(too_many_queries.query_count == 2);\n\n    auto wrong_answer = test_interactively(\n\
    \        one_trial, 0,\n        [](Random&) { return interactive_test_case(10,\
    \ 7); },\n        [](const int&, auto&) { return 6; },\n        [](int&, int query)\
    \ { return query; },\n        [](const int&, const int& secret, const int& answer)\
    \ {\n            return secret == answer;\n        });\n    assert(wrong_answer.failure\
    \ == RandomTestFailure::rejected_output);\n    assert(wrong_answer.query_count\
    \ == 0);\n\n    auto quick = interactive_stress_test(\n        0,\n        [](Random&\
    \ random) {\n            int value = int(random.uniform(-100, 100));\n       \
    \     return interactive_test_case(value, value);\n        },\n        [](const\
    \ int& input, auto&) { return input; },\n        [](int&, int query) { return\
    \ query; },\n        [](const int&, const int& state, const int& answer) {\n \
    \           return state == answer;\n        },\n        20, 86420);\n    assert(quick.passed());\n\
    }\n\nvoid test_stream_interface() {\n    using namespace m1une::utilities;\n\n\
    \    RandomTestConfig config;\n    config.trials = 200;\n    config.seed = 424242;\n\
    \    auto generate = [](Random& random, std::ostream& input) {\n        int size\
    \ = int(random.uniform(0, 30));\n        input << size << '\\n';\n        for\
    \ (int value : random.sequence(size, -20, 20)) {\n            input << value <<\
    \ ' ';\n        }\n        input << '\\n';\n    };\n    auto solve = [] {\n  \
    \      int size;\n        std::cin >> size;\n        std::vector<int> values(size);\n\
    \        for (int& value : values) std::cin >> value;\n        std::sort(values.begin(),\
    \ values.end());\n        for (int value : values) std::cout << value << ' ';\n\
    \        std::cout << '\\n';\n    };\n    auto check = [](std::istream& input,\
    \ std::istream& output) {\n        int size;\n        input >> size;\n       \
    \ std::vector<int> expected(size);\n        for (int& value : expected) input\
    \ >> value;\n        std::sort(expected.begin(), expected.end());\n        std::vector<int>\
    \ actual(size);\n        for (int& value : actual) {\n            if (!(output\
    \ >> value)) return false;\n        }\n        std::string extra;\n        return\
    \ expected == actual && !(output >> extra);\n    };\n    auto success = test_streams(config,\
    \ generate, solve, check);\n    assert(success.passed());\n\n    int callback_count\
    \ = 0;\n    RandomTestConfig one_trial;\n    one_trial.trials = 1;\n    one_trial.seed\
    \ = 515151;\n    auto failure = test_streams(\n        one_trial,\n        [](Random&,\
    \ std::ostream& input) { input << \"3\\n1 2 3\\n\"; },\n        [] {\n       \
    \     int size;\n            std::cin >> size;\n            std::cout << size\
    \ - 1 << '\\n';\n        },\n        [](std::istream&, std::istream& output) {\n\
    \            int answer;\n            return bool(output >> answer) && answer\
    \ == 3;\n        },\n        [&](const std::string& input, const std::string&\
    \ output, int trial,\n            std::uint64_t seed) {\n            callback_count++;\n\
    \            assert(input == \"3\\n1 2 3\\n\");\n            assert(output ==\
    \ \"2\\n\");\n            assert(trial == 0);\n            assert(seed == one_trial.seed);\n\
    \        });\n    assert(failure.failure == RandomTestFailure::rejected_output);\n\
    \    assert(callback_count == 1);\n\n    auto quick = stream_stress_test(generate,\
    \ solve, check, 20, 616161);\n    assert(quick.passed());\n}\n\nvoid test_interactive_stream_interface()\
    \ {\n    using namespace m1une::utilities;\n\n    auto generate = [](Random& random,\
    \ std::ostream& input) {\n        int upper = int(random.uniform(1, 1000));\n\
    \        input << upper << '\\n';\n        return int(random.uniform(0, upper));\n\
    \    };\n    auto solve = [] {\n        int upper;\n        std::cin >> upper;\n\
    \        int low = 0;\n        int high = upper;\n        while (low < high) {\n\
    \            int middle = (low + high) / 2;\n            std::cout << \"? \" <<\
    \ middle << std::endl;\n            int comparison;\n            std::cin >> comparison;\n\
    \            if (comparison <= 0) high = middle;\n            else low = middle\
    \ + 1;\n        }\n        std::cout << \"! \" << low << std::endl;\n    };\n\
    \    auto reply = [](int& secret, std::istream& query,\n                    std::ostream&\
    \ response) {\n        char type;\n        int guess;\n        std::string extra;\n\
    \        if (!(query >> type >> guess) || type != '?' || query >> extra) {\n \
    \           reject_query(\"expected: ? x\");\n        }\n        if (secret <\
    \ guess) response << -1;\n        else if (guess < secret) response << 1;\n  \
    \      else response << 0;\n    };\n    auto check = [](std::istream& input, const\
    \ int& secret,\n                    std::istream& output) {\n        int upper;\n\
    \        char type;\n        int answer;\n        std::string extra;\n       \
    \ input >> upper;\n        return bool(output >> type >> answer) && type == '!'\
    \ &&\n               0 <= answer && answer <= upper && answer == secret &&\n \
    \              !(output >> extra);\n    };\n\n    auto success = interactive_stream_stress_test(\n\
    \        10, generate, solve, reply, check, 200, 717171);\n    assert(success.passed());\n\
    \n    RandomTestConfig one_trial;\n    one_trial.trials = 1;\n    one_trial.seed\
    \ = 818181;\n    int callback_count = 0;\n    auto invalid = test_interactive_streams(\n\
    \        one_trial, 1,\n        [](Random&, std::ostream& input) {\n         \
    \   input << \"10\\n\";\n            return 5;\n        },\n        [] {\n   \
    \         int upper;\n            std::cin >> upper;\n            std::cout <<\
    \ \"invalid query\" << std::endl;\n            int response;\n            std::cin\
    \ >> response;\n        },\n        reply, check,\n        [&](const std::string&\
    \ input, const int& state,\n            const InteractionTranscript& transcript,\
    \ int trial,\n            std::uint64_t seed, RandomTestFailure reason) {\n  \
    \          callback_count++;\n            assert(input == \"10\\n\");\n      \
    \      assert(state == 5);\n            assert(transcript.exchanges.size() ==\
    \ 1);\n            assert(transcript.exchanges[0].query == \"invalid query\");\n\
    \            assert(!transcript.exchanges[0].responded);\n            assert(transcript.failure_message\
    \ == \"expected: ? x\");\n            assert(trial == 0);\n            assert(seed\
    \ == one_trial.seed);\n            assert(reason == RandomTestFailure::invalid_query);\n\
    \        });\n    assert(invalid.failure == RandomTestFailure::invalid_query);\n\
    \    assert(invalid.query_count == 1);\n    assert(callback_count == 1);\n\n \
    \   auto query_limit = test_interactive_streams(\n        one_trial, 0,\n    \
    \    [](Random&, std::ostream& input) {\n            input << \"10\\n\";\n   \
    \         return 5;\n        },\n        [] {\n            int upper;\n      \
    \      std::cin >> upper;\n            std::cout << \"? 5\" << std::endl;\n  \
    \          int response;\n            std::cin >> response;\n        },\n    \
    \    reply, check);\n    assert(query_limit.failure == RandomTestFailure::query_limit);\n\
    \    assert(query_limit.query_count == 1);\n}\n#endif\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n#ifndef NDEBUG\n\
    \    test_properties();\n    test_comparison();\n    test_constructive();\n  \
    \  test_interactive();\n    test_stream_interface();\n    test_interactive_stream_interface();\n\
    #endif\n\n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a\
    \ + b << '\\n';\n}\n"
  dependsOn:
  - utilities/random_testing.hpp
  - utilities/random.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/utilities/random_testing.test.cpp
  requiredBy: []
  timestamp: '2026-08-11 14:24:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/random_testing.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/random_testing.test.cpp
- /verify/verify/utilities/random_testing.test.cpp.html
title: verify/utilities/random_testing.test.cpp
---
