---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/random_testing.test.cpp
    title: verify/utilities/random_testing.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/random_testing.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <cstdlib>\n#include <exception>\n\
    #include <functional>\n#include <iostream>\n#include <iterator>\n#include <sstream>\n\
    #include <string>\n#include <tuple>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"utilities/random.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 6 \"utilities/random.hpp\"\n#include <chrono>\n#line 10 \"utilities/random.hpp\"\
    \n#include <numeric>\n#include <queue>\n#include <random>\n#line 14 \"utilities/random.hpp\"\
    \n#include <string_view>\n#line 17 \"utilities/random.hpp\"\n#include <unordered_set>\n\
    #line 20 \"utilities/random.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    \nstruct RandomGraphOptions {\n    bool directed = false;\n    bool allow_self_loops\
    \ = false;\n    bool allow_parallel_edges = false;\n};\n\nstruct Random {\n  \
    \ private:\n    std::mt19937_64 _engine;\n\n    static unsigned long long chrono_seed()\
    \ {\n        return static_cast<unsigned long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
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
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_RANDOM_TESTING_HPP\n#define M1UNE_RANDOM_TESTING_HPP 1\n\n\
    #include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <cstdlib>\n\
    #include <exception>\n#include <functional>\n#include <iostream>\n#include <iterator>\n\
    #include <sstream>\n#include <string>\n#include <tuple>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#include \"random.hpp\"\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\ninline constexpr std::uint64_t default_random_test_seed\
    \ =\n    0x243f6a8885a308d3ULL;\n\nstruct RandomTestConfig {\n    int trials =\
    \ 1000;\n    std::uint64_t seed = default_random_test_seed;\n};\n\nenum class\
    \ RandomTestFailure {\n    none,\n    property,\n    mismatch,\n    rejected_output,\n\
    \    query_limit,\n    invalid_query,\n};\n\ninline const char* random_test_failure_name(RandomTestFailure\
    \ failure) {\n    switch (failure) {\n        case RandomTestFailure::none:\n\
    \            return \"none\";\n        case RandomTestFailure::property:\n   \
    \         return \"property\";\n        case RandomTestFailure::mismatch:\n  \
    \          return \"mismatch\";\n        case RandomTestFailure::rejected_output:\n\
    \            return \"rejected output\";\n        case RandomTestFailure::query_limit:\n\
    \            return \"query limit exceeded\";\n        case RandomTestFailure::invalid_query:\n\
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
    \ m1une\n\n#endif  // M1UNE_RANDOM_TESTING_HPP\n"
  dependsOn:
  - utilities/random.hpp
  isVerificationFile: false
  path: utilities/random_testing.hpp
  requiredBy: []
  timestamp: '2026-08-11 14:24:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/random_testing.test.cpp
documentation_of: utilities/random_testing.hpp
layout: document
title: Random Testing
---

## The Quick Way

You do not need to rewrite a solution to return custom input and answer types.
Keep ordinary contest code that reads `std::cin` and writes `std::cout`:

```cpp
void solve() {
    // The same code used in the submission.
}
```

Then choose one helper:

| Problem | Helper |
| --- | --- |
| Non-interactive or constructive | `stream_stress_test(generate, solve, check)` |
| Interactive | `interactive_stream_stress_test(limit, generate, solve, reply, check)` |

The helper redirects `std::cin` and `std::cout` for every random case. You only
write the random input generator and checker. On failure it prints the input,
output or interaction transcript, seed, and zero-based trial.

```cpp
#include "utilities/random_testing.hpp"

using namespace m1une::utilities;
```

## Non-Interactive and Constructive Recipe

Write these three pieces:

```cpp
auto generate = [](Random& random, std::ostream& input) {
    // Write one small random case to input.
};

void solve() {
    // Read std::cin and write std::cout as usual.
}

auto check = [](std::istream& input, std::istream& output) {
    // Read the original input and candidate output.
    return true;  // Return whether the output is valid.
};

int main() {
    stream_stress_test(generate, solve, check);
}
```

This works for constructive problems because `check` validates the output; it
does not compare against one fixed answer.

### Complete example

The following tester checks ordinary code that prints the values in sorted
order:

```cpp
#include "utilities/random_testing.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace m1une::utilities;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;

    std::sort(values.begin(), values.end());
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
}

int main() {
    auto generate = [](Random& random, std::ostream& input) {
        int n = int(random.uniform(0, 20));
        input << n << '\n';
        for (int value : random.sequence(n, -10, 10)) {
            input << value << ' ';
        }
        input << '\n';
    };

    auto check = [](std::istream& input, std::istream& output) {
        int n;
        input >> n;
        std::vector<int> expected(n);
        for (int& value : expected) input >> value;
        std::sort(expected.begin(), expected.end());

        std::vector<int> actual(n);
        for (int& value : actual) {
            if (!(output >> value)) return false;
        }
        std::string extra;
        return actual == expected && !(output >> extra);
    };

    stream_stress_test(generate, solve, check);
}
```

Usually the generator is just a few `random.uniform(...)` calls and `<<`
operations. The checker can reuse input constraints and validation logic from
the problem statement.

The default is 1000 cases with a fixed seed. Add a trial count and seed at the
end when needed:

```cpp
stream_stress_test(generate, solve, check, 10000, 123456789);
```

## Interactive Recipe

The submitted solution can keep the ordinary protocol:

```cpp
std::cout << "? " << query << std::endl;
std::cin >> reply;
// ...
std::cout << "! " << answer << std::endl;
```

The tester needs four pieces:

1. `generate` writes the public input and returns hidden judge state;
2. `solve` is the ordinary interactive solution;
3. `reply` reads one query and writes the mock judge's response;
4. `check` validates the final output.

### Complete example

```cpp
#include "utilities/random_testing.hpp"

#include <iostream>
#include <string>

using namespace m1une::utilities;

void solve() {
    int upper;
    std::cin >> upper;

    int low = 0;
    int high = upper;
    while (low < high) {
        int middle = (low + high) / 2;
        std::cout << "? " << middle << std::endl;

        int comparison;
        std::cin >> comparison;
        if (comparison <= 0) high = middle;
        else low = middle + 1;
    }
    std::cout << "! " << low << std::endl;
}

int main() {
    auto generate = [](Random& random, std::ostream& input) {
        int upper = 1000;
        input << upper << '\n';
        return int(random.uniform(0, upper));  // Hidden number.
    };

    auto reply = [](int& secret, std::istream& query,
                    std::ostream& response) {
        char type;
        int guess;
        std::string extra;
        if (!(query >> type >> guess) || type != '?' || query >> extra) {
            reject_query("expected: ? x");
        }

        if (secret < guess) response << -1;
        else if (guess < secret) response << 1;
        else response << 0;
    };

    auto check = [](std::istream& input, const int& secret,
                    std::istream& output) {
        int upper;
        char type;
        int answer;
        std::string extra;
        input >> upper;
        return bool(output >> type >> answer) && type == '!' &&
               0 <= answer && answer <= upper && answer == secret &&
               !(output >> extra);
    };

    interactive_stream_stress_test(10, generate, solve, reply, check);
}
```

When `solve` tries to read after printing, the helper sends that pending output
to `reply` and feeds the generated response back through `std::cin`. Output
remaining when `solve` returns is passed to `check` as the final answer.

Call `reject_query("reason")` for malformed or forbidden queries. The first
query beyond the limit also fails. Both failures include the full query/reply
transcript.

Select trials and a seed with trailing arguments:

```cpp
interactive_stream_stress_test(
    query_limit, generate, solve, reply, check, 10000, 123456789);
```

## Practical Limitations

The stream helpers redirect C++ `std::cin` and `std::cout`. They cannot capture
`scanf`, `printf`, `fread`, `FastInput`, or other code that accesses the C file
handles directly. Keep a `std::cin`/`std::cout` version while stress testing, or
move only the algorithm into a shared function used by both I/O frontends.

Call `std::ios::sync_with_stdio(false)` before starting the tester, not inside
`solve`, because changing synchronization can replace standard stream buffers.

The interactive helper runs in one process without real pipes. It checks the
algorithm and protocol, but it does not detect missing flushes, deadlocks, or
timing problems.

## Typed Helpers (Optional)

Use the typed interface only when the solution already accepts values and
returns an answer.

For ordinary optimized-vs-brute testing:

```cpp
stress_test(generate, solve, brute);
```

For constructive testing:

```cpp
constructive_stress_test(
    generate,
    solve,
    [](const Input& input, const Answer& answer) {
        return is_valid(input, answer);
    });
```

For a typed interactive solution, generate public input and hidden state with
`interactive_test_case(input, state)`. The solution receives the public input
and an object providing `interaction.ask(query)`:

```cpp
interactive_stress_test(
    query_limit, generate, solve, reply, check);
```

The stream and typed interfaces use the same deterministic seeds, failure
categories, query limits, and transcript reporting.

## Handle Failure Without Aborting

The `*_stress_test` helpers print a failure and call `std::abort`. Use the
lower-level version to inspect a result instead:

```cpp
RandomTestConfig config;
config.trials = 10000;
config.seed = 123456789;

auto result = test_streams(config, generate, solve, check);
if (!result) {
    // result.seed
    // result.failed_trial
    // result.failure
}
```

The interactive equivalent is:

```cpp
auto result = test_interactive_streams(
    config, query_limit, generate, solve, reply, check);
```

| Result field | Meaning |
| --- | --- |
| `seed` | Seed used by the generator. |
| `requested_trials` | Number of requested cases. |
| `completed_trials` | Cases that passed before the failure. |
| `failed_trial` | Zero-based failed case, or `-1` on success. |
| `failure` | `property`, `mismatch`, `rejected_output`, `query_limit`, or `invalid_query`. |
| `query_count` | Attempted queries on an interactive failure, otherwise `-1`. |

`result.passed()` and `bool(result)` report success.

## Interface Reference

```cpp
template <class Generator, class Solution, class Checker>
RandomTestResult stream_stress_test(
    Generator generator,
    Solution solution,
    Checker checker,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);

template <class Generator, class Solution, class QueryHandler, class Checker>
RandomTestResult interactive_stream_stress_test(
    int query_limit,
    Generator generator,
    Solution solution,
    QueryHandler query_handler,
    Checker checker,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);
```

The lower-level forms add a configuration and optional failure callback:

```cpp
template <class Generator, class Solution, class Checker,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_streams(
    RandomTestConfig config,
    Generator generator,
    Solution solution,
    Checker checker,
    OnFailure on_failure = {});

template <class Generator, class Solution, class QueryHandler, class Checker,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_interactive_streams(
    RandomTestConfig config,
    int query_limit,
    Generator generator,
    Solution solution,
    QueryHandler query_handler,
    Checker checker,
    OnFailure on_failure = {});
```

The non-interactive callback is called as
`on_failure(input_text, output_text, trial, seed)`. The interactive callback is
called as `on_failure(input_text, state, transcript, trial, seed, failure)`.

Generators may also accept a final `int trial`. The non-interactive generator
returns `void`; the interactive generator returns the hidden state. Query
handlers return `void` and write their response to the supplied output stream.

The harness adds $O(1)$ work per trial apart from the supplied functions and
the size of generated/captured text. Interactive transcript time and memory are
linear in the total query and response text.
