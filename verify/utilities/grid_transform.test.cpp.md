---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/grid_transform.hpp
    title: Grid Transform
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
  bundledCode: "#line 1 \"verify/utilities/grid_transform.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"utilities/grid_transform.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <class\
    \ T>\nusing Vector2D = std::vector<std::vector<T>>;\n\nnamespace grid_transform_detail\
    \ {\n\ntemplate <class Row>\nvoid reserve_if_possible(Row& row, std::size_t size)\
    \ {\n    if constexpr (requires { row.reserve(size); }) {\n        row.reserve(size);\n\
    \    }\n}\n\ntemplate <class Row>\nstd::vector<Row> make_rows(std::size_t row_count,\
    \ std::size_t row_size) {\n    std::vector<Row> result(row_count);\n    for (Row&\
    \ row : result) reserve_if_possible(row, row_size);\n    return result;\n}\n\n\
    }  // namespace grid_transform_detail\n\ntemplate <class Row>\nbool is_rectangular(const\
    \ std::vector<Row>& grid) {\n    if (grid.empty()) return true;\n    const std::size_t\
    \ row_size = grid[0].size();\n    for (const Row& row : grid) {\n        if (row.size()\
    \ != row_size) return false;\n    }\n    return true;\n}\n\ntemplate <class Row>\n\
    std::size_t height(const std::vector<Row>& grid) {\n    return grid.size();\n\
    }\n\ntemplate <class Row>\nstd::size_t width(const std::vector<Row>& grid) {\n\
    \    assert(is_rectangular(grid));\n    return grid.empty() ? 0 : grid[0].size();\n\
    }\n\ntemplate <class Row>\nstd::vector<Row> transpose(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    const std::size_t h = height(grid);\n\
    \    const std::size_t w = width(grid);\n\n    std::vector<Row> result =\n   \
    \     grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t y = 0;\
    \ y < h; y++) {\n        for (std::size_t x = 0; x < w; x++) {\n            result[x].push_back(grid[y][x]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ flip_horizontal(const std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n\
    \    std::vector<Row> result = grid;\n    for (Row& row : result) {\n        std::reverse(row.begin(),\
    \ row.end());\n    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ flip_vertical(const std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n\
    \    std::vector<Row> result = grid;\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate90(const\
    \ std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n    const std::size_t\
    \ h = height(grid);\n    const std::size_t w = width(grid);\n\n    std::vector<Row>\
    \ result =\n        grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t\
    \ x = 0; x < w; x++) {\n        for (std::size_t y = h; y > 0; y--) {\n      \
    \      result[x].push_back(grid[y - 1][x]);\n        }\n    }\n    return result;\n\
    }\n\ntemplate <class Row>\nstd::vector<Row> rotate180(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    std::vector<Row> result = flip_vertical(grid);\n\
    \    for (Row& row : result) {\n        std::reverse(row.begin(), row.end());\n\
    \    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate270(const\
    \ std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n    const std::size_t\
    \ h = height(grid);\n    const std::size_t w = width(grid);\n\n    std::vector<Row>\
    \ result =\n        grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t\
    \ x = 0; x < w; x++) {\n        for (std::size_t y = 0; y < h; y++) {\n      \
    \      result[w - 1 - x].push_back(grid[y][x]);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate_clockwise(const\
    \ std::vector<Row>& grid) {\n    return rotate90(grid);\n}\n\ntemplate <class\
    \ Row>\nstd::vector<Row> rotate_counterclockwise(const std::vector<Row>& grid)\
    \ {\n    return rotate270(grid);\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ rotate(const std::vector<Row>& grid, int clockwise_quarter_turns) {\n    assert(is_rectangular(grid));\n\
    \    int turns = clockwise_quarter_turns % 4;\n    if (turns < 0) turns += 4;\n\
    \    if (turns == 0) return grid;\n    if (turns == 1) return rotate90(grid);\n\
    \    if (turns == 2) return rotate180(grid);\n    return rotate270(grid);\n}\n\
    \ntemplate <class Row>\nstd::array<std::vector<Row>, 4> rotations(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    return std::array<std::vector<Row>,\
    \ 4>{\n        grid,\n        rotate90(grid),\n        rotate180(grid),\n    \
    \    rotate270(grid)\n    };\n}\n\ntemplate <class Row>\nstd::array<std::vector<Row>,\
    \ 8> dihedral_transforms(\n    const std::vector<Row>& grid\n) {\n    assert(is_rectangular(grid));\n\
    \    const std::vector<Row> mirrored = flip_horizontal(grid);\n    return std::array<std::vector<Row>,\
    \ 8>{\n        grid,\n        rotate90(grid),\n        rotate180(grid),\n    \
    \    rotate270(grid),\n        mirrored,\n        rotate90(mirrored),\n      \
    \  rotate180(mirrored),\n        rotate270(mirrored)\n    };\n}\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/random.hpp\"\n\n\n\
    \n#line 6 \"utilities/random.hpp\"\n#include <chrono>\n#include <concepts>\n#include\
    \ <cstdint>\n#include <functional>\n#include <numeric>\n#include <queue>\n#include\
    \ <random>\n#include <string>\n#include <string_view>\n#include <tuple>\n#include\
    \ <type_traits>\n#include <unordered_set>\n#include <utility>\n#line 20 \"utilities/random.hpp\"\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/utilities/grid_transform.test.cpp\"\
    \n\n#line 7 \"verify/utilities/grid_transform.test.cpp\"\n#include <iostream>\n\
    #line 10 \"verify/utilities/grid_transform.test.cpp\"\n\nnamespace {\n\nusing\
    \ m1une::utilities::dihedral_transforms;\nusing m1une::utilities::flip_horizontal;\n\
    using m1une::utilities::flip_vertical;\nusing m1une::utilities::height;\nusing\
    \ m1une::utilities::is_rectangular;\nusing m1une::utilities::rotate;\nusing m1une::utilities::rotate180;\n\
    using m1une::utilities::rotate270;\nusing m1une::utilities::rotate90;\nusing m1une::utilities::rotate_clockwise;\n\
    using m1une::utilities::rotate_counterclockwise;\nusing m1une::utilities::rotations;\n\
    using m1une::utilities::transpose;\nusing m1une::utilities::Vector2D;\nusing m1une::utilities::width;\n\
    \nvoid assert_shape(const Vector2D<int>& grid, int h, int w) {\n    assert(static_cast<int>(grid.size())\
    \ == h);\n    for (const std::vector<int>& row : grid) {\n        assert(static_cast<int>(row.size())\
    \ == w);\n    }\n}\n\nvoid check_coordinate_mappings(const Vector2D<int>& grid)\
    \ {\n    assert(is_rectangular(grid));\n    const int h = static_cast<int>(grid.size());\n\
    \    const int w = h == 0 ? 0 : static_cast<int>(grid[0].size());\n    assert(static_cast<int>(height(grid))\
    \ == h);\n    assert(static_cast<int>(width(grid)) == w);\n\n    const Vector2D<int>\
    \ transposed = transpose(grid);\n    assert_shape(transposed, w, h);\n    for\
    \ (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n         \
    \   assert(transposed[x][y] == grid[y][x]);\n        }\n    }\n\n    const Vector2D<int>\
    \ horizontal = flip_horizontal(grid);\n    assert_shape(horizontal, h, w);\n \
    \   for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n   \
    \         assert(horizontal[y][w - 1 - x] == grid[y][x]);\n        }\n    }\n\n\
    \    const Vector2D<int> vertical = flip_vertical(grid);\n    assert_shape(vertical,\
    \ h, w);\n    for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++)\
    \ {\n            assert(vertical[h - 1 - y][x] == grid[y][x]);\n        }\n  \
    \  }\n\n    const Vector2D<int> clockwise = rotate90(grid);\n    assert_shape(clockwise,\
    \ w, h);\n    for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++)\
    \ {\n            assert(clockwise[x][h - 1 - y] == grid[y][x]);\n        }\n \
    \   }\n    assert(rotate_clockwise(grid) == clockwise);\n\n    const Vector2D<int>\
    \ half_turn = rotate180(grid);\n    assert_shape(half_turn, h, w);\n    for (int\
    \ y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n            assert(half_turn[h\
    \ - 1 - y][w - 1 - x] == grid[y][x]);\n        }\n    }\n\n    const Vector2D<int>\
    \ counterclockwise = rotate270(grid);\n    assert_shape(counterclockwise, w, h);\n\
    \    for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n  \
    \          assert(counterclockwise[w - 1 - x][y] == grid[y][x]);\n        }\n\
    \    }\n    assert(rotate_counterclockwise(grid) == counterclockwise);\n\n   \
    \ assert(rotate(grid, 0) == grid);\n    assert(rotate(grid, 1) == clockwise);\n\
    \    assert(rotate(grid, 2) == half_turn);\n    assert(rotate(grid, 3) == counterclockwise);\n\
    \    assert(rotate(grid, 4) == grid);\n    assert(rotate(grid, -1) == counterclockwise);\n\
    \    assert(rotate(grid, -2) == half_turn);\n    assert(rotate(grid, 5) == clockwise);\n\
    \n    const auto all_rotations = rotations(grid);\n    assert(all_rotations[0]\
    \ == grid);\n    assert(all_rotations[1] == clockwise);\n    assert(all_rotations[2]\
    \ == half_turn);\n    assert(all_rotations[3] == counterclockwise);\n\n    const\
    \ auto all_dihedral = dihedral_transforms(grid);\n    assert(all_dihedral[0] ==\
    \ grid);\n    assert(all_dihedral[1] == clockwise);\n    assert(all_dihedral[2]\
    \ == half_turn);\n    assert(all_dihedral[3] == counterclockwise);\n    assert(all_dihedral[4]\
    \ == horizontal);\n    assert(all_dihedral[5] == rotate90(horizontal));\n    assert(all_dihedral[6]\
    \ == rotate180(horizontal));\n    assert(all_dihedral[7] == rotate270(horizontal));\n\
    }\n\nvoid test_fixed_vector_grids() {\n    Vector2D<int> grid;\n    grid.emplace_back(std::vector<int>{1,\
    \ 2, 3});\n    grid.emplace_back(std::vector<int>{4, 5, 6});\n    check_coordinate_mappings(grid);\n\
    \n    Vector2D<int> empty;\n    check_coordinate_mappings(empty);\n\n    Vector2D<int>\
    \ zero_width(3);\n    check_coordinate_mappings(zero_width);\n\n    std::vector<std::vector<int>>\
    \ ragged;\n    ragged.emplace_back(std::vector<int>{1, 2});\n    ragged.emplace_back(std::vector<int>{3});\n\
    \    assert(!is_rectangular(ragged));\n}\n\nvoid test_string_grids() {\n    std::vector<std::string>\
    \ grid;\n    grid.emplace_back(\"abc\");\n    grid.emplace_back(\"def\");\n\n\
    \    std::vector<std::string> expected_transpose;\n    expected_transpose.emplace_back(\"\
    ad\");\n    expected_transpose.emplace_back(\"be\");\n    expected_transpose.emplace_back(\"\
    cf\");\n    assert(transpose(grid) == expected_transpose);\n\n    std::vector<std::string>\
    \ expected_clockwise;\n    expected_clockwise.emplace_back(\"da\");\n    expected_clockwise.emplace_back(\"\
    eb\");\n    expected_clockwise.emplace_back(\"fc\");\n    assert(rotate90(grid)\
    \ == expected_clockwise);\n\n    std::vector<std::string> expected_half_turn;\n\
    \    expected_half_turn.emplace_back(\"fed\");\n    expected_half_turn.emplace_back(\"\
    cba\");\n    assert(rotate180(grid) == expected_half_turn);\n\n    std::vector<std::string>\
    \ expected_counterclockwise;\n    expected_counterclockwise.emplace_back(\"cf\"\
    );\n    expected_counterclockwise.emplace_back(\"be\");\n    expected_counterclockwise.emplace_back(\"\
    ad\");\n    assert(rotate270(grid) == expected_counterclockwise);\n\n    std::vector<std::string>\
    \ expected_horizontal;\n    expected_horizontal.emplace_back(\"cba\");\n    expected_horizontal.emplace_back(\"\
    fed\");\n    assert(flip_horizontal(grid) == expected_horizontal);\n\n    std::vector<std::string>\
    \ expected_vertical;\n    expected_vertical.emplace_back(\"def\");\n    expected_vertical.emplace_back(\"\
    abc\");\n    assert(flip_vertical(grid) == expected_vertical);\n}\n\nvoid test_random_grids()\
    \ {\n    m1une::utilities::Random random(0x7a5a2d11ULL);\n    for (int trial =\
    \ 0; trial < 1000; trial++) {\n        const int h = static_cast<int>(random.uniform(0,\
    \ 8));\n        const int w = static_cast<int>(random.uniform(0, 8));\n      \
    \  Vector2D<int> grid(h, std::vector<int>(w));\n        for (std::vector<int>&\
    \ row : grid) {\n            for (int& value : row) {\n                value =\
    \ static_cast<int>(random.uniform(-1000, 1000));\n            }\n        }\n \
    \       check_coordinate_mappings(grid);\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_fixed_vector_grids();\n    test_string_grids();\n    test_random_grids();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../utilities/grid_transform.hpp\"\n#include \"../../utilities/random.hpp\"\n\
    \n#include <cassert>\n#include <iostream>\n#include <string>\n#include <vector>\n\
    \nnamespace {\n\nusing m1une::utilities::dihedral_transforms;\nusing m1une::utilities::flip_horizontal;\n\
    using m1une::utilities::flip_vertical;\nusing m1une::utilities::height;\nusing\
    \ m1une::utilities::is_rectangular;\nusing m1une::utilities::rotate;\nusing m1une::utilities::rotate180;\n\
    using m1une::utilities::rotate270;\nusing m1une::utilities::rotate90;\nusing m1une::utilities::rotate_clockwise;\n\
    using m1une::utilities::rotate_counterclockwise;\nusing m1une::utilities::rotations;\n\
    using m1une::utilities::transpose;\nusing m1une::utilities::Vector2D;\nusing m1une::utilities::width;\n\
    \nvoid assert_shape(const Vector2D<int>& grid, int h, int w) {\n    assert(static_cast<int>(grid.size())\
    \ == h);\n    for (const std::vector<int>& row : grid) {\n        assert(static_cast<int>(row.size())\
    \ == w);\n    }\n}\n\nvoid check_coordinate_mappings(const Vector2D<int>& grid)\
    \ {\n    assert(is_rectangular(grid));\n    const int h = static_cast<int>(grid.size());\n\
    \    const int w = h == 0 ? 0 : static_cast<int>(grid[0].size());\n    assert(static_cast<int>(height(grid))\
    \ == h);\n    assert(static_cast<int>(width(grid)) == w);\n\n    const Vector2D<int>\
    \ transposed = transpose(grid);\n    assert_shape(transposed, w, h);\n    for\
    \ (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n         \
    \   assert(transposed[x][y] == grid[y][x]);\n        }\n    }\n\n    const Vector2D<int>\
    \ horizontal = flip_horizontal(grid);\n    assert_shape(horizontal, h, w);\n \
    \   for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n   \
    \         assert(horizontal[y][w - 1 - x] == grid[y][x]);\n        }\n    }\n\n\
    \    const Vector2D<int> vertical = flip_vertical(grid);\n    assert_shape(vertical,\
    \ h, w);\n    for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++)\
    \ {\n            assert(vertical[h - 1 - y][x] == grid[y][x]);\n        }\n  \
    \  }\n\n    const Vector2D<int> clockwise = rotate90(grid);\n    assert_shape(clockwise,\
    \ w, h);\n    for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++)\
    \ {\n            assert(clockwise[x][h - 1 - y] == grid[y][x]);\n        }\n \
    \   }\n    assert(rotate_clockwise(grid) == clockwise);\n\n    const Vector2D<int>\
    \ half_turn = rotate180(grid);\n    assert_shape(half_turn, h, w);\n    for (int\
    \ y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n            assert(half_turn[h\
    \ - 1 - y][w - 1 - x] == grid[y][x]);\n        }\n    }\n\n    const Vector2D<int>\
    \ counterclockwise = rotate270(grid);\n    assert_shape(counterclockwise, w, h);\n\
    \    for (int y = 0; y < h; y++) {\n        for (int x = 0; x < w; x++) {\n  \
    \          assert(counterclockwise[w - 1 - x][y] == grid[y][x]);\n        }\n\
    \    }\n    assert(rotate_counterclockwise(grid) == counterclockwise);\n\n   \
    \ assert(rotate(grid, 0) == grid);\n    assert(rotate(grid, 1) == clockwise);\n\
    \    assert(rotate(grid, 2) == half_turn);\n    assert(rotate(grid, 3) == counterclockwise);\n\
    \    assert(rotate(grid, 4) == grid);\n    assert(rotate(grid, -1) == counterclockwise);\n\
    \    assert(rotate(grid, -2) == half_turn);\n    assert(rotate(grid, 5) == clockwise);\n\
    \n    const auto all_rotations = rotations(grid);\n    assert(all_rotations[0]\
    \ == grid);\n    assert(all_rotations[1] == clockwise);\n    assert(all_rotations[2]\
    \ == half_turn);\n    assert(all_rotations[3] == counterclockwise);\n\n    const\
    \ auto all_dihedral = dihedral_transforms(grid);\n    assert(all_dihedral[0] ==\
    \ grid);\n    assert(all_dihedral[1] == clockwise);\n    assert(all_dihedral[2]\
    \ == half_turn);\n    assert(all_dihedral[3] == counterclockwise);\n    assert(all_dihedral[4]\
    \ == horizontal);\n    assert(all_dihedral[5] == rotate90(horizontal));\n    assert(all_dihedral[6]\
    \ == rotate180(horizontal));\n    assert(all_dihedral[7] == rotate270(horizontal));\n\
    }\n\nvoid test_fixed_vector_grids() {\n    Vector2D<int> grid;\n    grid.emplace_back(std::vector<int>{1,\
    \ 2, 3});\n    grid.emplace_back(std::vector<int>{4, 5, 6});\n    check_coordinate_mappings(grid);\n\
    \n    Vector2D<int> empty;\n    check_coordinate_mappings(empty);\n\n    Vector2D<int>\
    \ zero_width(3);\n    check_coordinate_mappings(zero_width);\n\n    std::vector<std::vector<int>>\
    \ ragged;\n    ragged.emplace_back(std::vector<int>{1, 2});\n    ragged.emplace_back(std::vector<int>{3});\n\
    \    assert(!is_rectangular(ragged));\n}\n\nvoid test_string_grids() {\n    std::vector<std::string>\
    \ grid;\n    grid.emplace_back(\"abc\");\n    grid.emplace_back(\"def\");\n\n\
    \    std::vector<std::string> expected_transpose;\n    expected_transpose.emplace_back(\"\
    ad\");\n    expected_transpose.emplace_back(\"be\");\n    expected_transpose.emplace_back(\"\
    cf\");\n    assert(transpose(grid) == expected_transpose);\n\n    std::vector<std::string>\
    \ expected_clockwise;\n    expected_clockwise.emplace_back(\"da\");\n    expected_clockwise.emplace_back(\"\
    eb\");\n    expected_clockwise.emplace_back(\"fc\");\n    assert(rotate90(grid)\
    \ == expected_clockwise);\n\n    std::vector<std::string> expected_half_turn;\n\
    \    expected_half_turn.emplace_back(\"fed\");\n    expected_half_turn.emplace_back(\"\
    cba\");\n    assert(rotate180(grid) == expected_half_turn);\n\n    std::vector<std::string>\
    \ expected_counterclockwise;\n    expected_counterclockwise.emplace_back(\"cf\"\
    );\n    expected_counterclockwise.emplace_back(\"be\");\n    expected_counterclockwise.emplace_back(\"\
    ad\");\n    assert(rotate270(grid) == expected_counterclockwise);\n\n    std::vector<std::string>\
    \ expected_horizontal;\n    expected_horizontal.emplace_back(\"cba\");\n    expected_horizontal.emplace_back(\"\
    fed\");\n    assert(flip_horizontal(grid) == expected_horizontal);\n\n    std::vector<std::string>\
    \ expected_vertical;\n    expected_vertical.emplace_back(\"def\");\n    expected_vertical.emplace_back(\"\
    abc\");\n    assert(flip_vertical(grid) == expected_vertical);\n}\n\nvoid test_random_grids()\
    \ {\n    m1une::utilities::Random random(0x7a5a2d11ULL);\n    for (int trial =\
    \ 0; trial < 1000; trial++) {\n        const int h = static_cast<int>(random.uniform(0,\
    \ 8));\n        const int w = static_cast<int>(random.uniform(0, 8));\n      \
    \  Vector2D<int> grid(h, std::vector<int>(w));\n        for (std::vector<int>&\
    \ row : grid) {\n            for (int& value : row) {\n                value =\
    \ static_cast<int>(random.uniform(-1000, 1000));\n            }\n        }\n \
    \       check_coordinate_mappings(grid);\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_fixed_vector_grids();\n    test_string_grids();\n    test_random_grids();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - utilities/grid_transform.hpp
  - utilities/random.hpp
  isVerificationFile: true
  path: verify/utilities/grid_transform.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 23:06:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/grid_transform.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/grid_transform.test.cpp
- /verify/verify/utilities/grid_transform.test.cpp.html
title: verify/utilities/grid_transform.test.cpp
---
