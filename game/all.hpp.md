---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: game/green_hackenbush.hpp
    title: Green Hackenbush
  - icon: ':heavy_check_mark:'
    path: game/grundy.hpp
    title: Grundy Numbers
  - icon: ':heavy_check_mark:'
    path: game/minimax.hpp
    title: DAG Minimax
  - icon: ':heavy_check_mark:'
    path: game/nim.hpp
    title: Nim
  - icon: ':heavy_check_mark:'
    path: game/nim_product.hpp
    title: Nim Product
  - icon: ':heavy_check_mark:'
    path: game/partisan_game.hpp
    title: Partisan Game Outcomes
  - icon: ':heavy_check_mark:'
    path: game/retrograde_analysis.hpp
    title: Game Retrograde Analysis
  - icon: ':heavy_check_mark:'
    path: game/silver_dollar_game.hpp
    title: Silver Dollar Game
  - icon: ':heavy_check_mark:'
    path: game/subtraction_game.hpp
    title: Subtraction Game
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/game/game_algorithms.test.cpp
    title: verify/game/game_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/all.hpp\"\n\n\n\n#line 1 \"game/green_hackenbush.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace game {\n\n// Every vertex represents one green edge. parent[v]\
    \ == -1 attaches that edge\n// to the ground; otherwise it attaches it above the\
    \ edge parent[v].\ninline uint64_t green_hackenbush_grundy(const std::vector<int>&\
    \ parent) {\n    const int size = int(parent.size());\n    std::vector<std::vector<int>>\
    \ children(size);\n    std::vector<int> roots;\n    for (int edge = 0; edge <\
    \ size; ++edge) {\n        assert(-1 <= parent[edge] && parent[edge] < size);\n\
    \        assert(parent[edge] != edge);\n        if (parent[edge] == -1) {\n  \
    \          roots.push_back(edge);\n        } else {\n            children[parent[edge]].push_back(edge);\n\
    \        }\n    }\n\n    std::vector<int> order = roots;\n    order.reserve(size);\n\
    \    for (int position = 0; position < int(order.size()); ++position) {\n    \
    \    const int edge = order[position];\n        for (int child : children[edge])\
    \ order.push_back(child);\n    }\n    assert(int(order.size()) == size);\n\n \
    \   std::vector<uint64_t> branch(size);\n    for (int position = size - 1; position\
    \ >= 0; --position) {\n        const int edge = order[position];\n        uint64_t\
    \ children_grundy = 0;\n        for (int child : children[edge]) children_grundy\
    \ ^= branch[child];\n        branch[edge] = children_grundy + 1;\n    }\n\n  \
    \  uint64_t result = 0;\n    for (int root : roots) result ^= branch[root];\n\
    \    return result;\n}\n\ninline bool green_hackenbush_first_player_wins(\n  \
    \  const std::vector<int>& parent\n) {\n    return green_hackenbush_grundy(parent)\
    \ != 0;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line 1 \"game/grundy.hpp\"\
    \n\n\n\n#line 5 \"game/grundy.hpp\"\n#include <queue>\n#line 7 \"game/grundy.hpp\"\
    \n\nnamespace m1une {\nnamespace game {\n\n// graph[v] contains the states reachable\
    \ from v in one move.\n// The graph must be a DAG.\ntemplate <typename Graph>\n\
    std::vector<int> grundy_numbers(const Graph& graph) {\n    const int size = int(graph.size());\n\
    \    std::vector<int> indegree(size);\n    for (int vertex = 0; vertex < size;\
    \ ++vertex) {\n        for (int next : graph[vertex]) {\n            assert(0\
    \ <= next && next < size);\n            indegree[next]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    for (int vertex = 0; vertex < size; ++vertex)\
    \ {\n        if (indegree[vertex] == 0) queue.push(vertex);\n    }\n    std::vector<int>\
    \ order;\n    order.reserve(size);\n    while (!queue.empty()) {\n        const\
    \ int vertex = queue.front();\n        queue.pop();\n        order.push_back(vertex);\n\
    \        for (int next : graph[vertex]) {\n            if (--indegree[next] ==\
    \ 0) queue.push(next);\n        }\n    }\n    assert(int(order.size()) == size);\n\
    \n    std::vector<int> grundy(size);\n    std::vector<int> seen(size + 1, -1);\n\
    \    for (int position = size - 1; position >= 0; --position) {\n        const\
    \ int vertex = order[position];\n        for (int next : graph[vertex]) {\n  \
    \          const int value = grundy[next];\n            if (value <= size) seen[value]\
    \ = vertex;\n        }\n        while (grundy[vertex] <= size && seen[grundy[vertex]]\
    \ == vertex) {\n            grundy[vertex]++;\n        }\n    }\n    return grundy;\n\
    }\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line 1 \"game/minimax.hpp\"\
    \n\n\n\n#line 6 \"game/minimax.hpp\"\n#include <utility>\n#line 8 \"game/minimax.hpp\"\
    \n\nnamespace m1une {\nnamespace game {\n\ntemplate <typename T>\nstruct MinimaxResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> move;\n};\n\ntemplate <typename\
    \ T>\nMinimaxResult<T> dag_minimax(\n    const std::vector<std::vector<int>>&\
    \ graph,\n    const std::vector<T>& terminal_value,\n    const std::vector<bool>&\
    \ maximize\n) {\n    const int size = int(graph.size());\n    assert(int(terminal_value.size())\
    \ == size);\n    assert(int(maximize.size()) == size);\n\n    std::vector<int>\
    \ indegree(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n     \
    \   for (int next : graph[vertex]) {\n            assert(0 <= next && next < size);\n\
    \            indegree[next]++;\n        }\n    }\n\n    std::queue<int> queue;\n\
    \    for (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex]\
    \ == 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ graph[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n    }\n    assert(int(order.size()) == size);\n\n    std::vector<T>\
    \ value = terminal_value;\n    std::vector<int> move(size, -1);\n    for (int\
    \ position = size - 1; position >= 0; --position) {\n        const int vertex\
    \ = order[position];\n        if (graph[vertex].empty()) {\n            value[vertex]\
    \ = terminal_value[vertex];\n            continue;\n        }\n\n        move[vertex]\
    \ = graph[vertex][0];\n        value[vertex] = value[move[vertex]];\n        for\
    \ (int next : graph[vertex]) {\n            const bool improves = maximize[vertex]\n\
    \                                      ? value[vertex] < value[next]\n       \
    \                               : value[next] < value[vertex];\n            if\
    \ (improves) {\n                value[vertex] = value[next];\n               \
    \ move[vertex] = next;\n            }\n        }\n    }\n    return {std::move(value),\
    \ std::move(move)};\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line\
    \ 1 \"game/nim.hpp\"\n\n\n\n#include <iterator>\n#include <optional>\n#include\
    \ <type_traits>\n#line 8 \"game/nim.hpp\"\n\nnamespace m1une {\nnamespace game\
    \ {\n\ntemplate <typename T>\nstruct NimMove {\n    int heap;\n    T new_size;\n\
    };\n\ntemplate <typename Iterator>\nauto nim_sum(Iterator first, Iterator last)\
    \ {\n    using T = typename std::iterator_traits<Iterator>::value_type;\n    T\
    \ result{};\n    while (first != last) {\n        result ^= *first;\n        ++first;\n\
    \    }\n    return result;\n}\n\ntemplate <typename Range>\nauto nim_sum(const\
    \ Range& heaps) {\n    using std::begin;\n    using std::end;\n    return nim_sum(begin(heaps),\
    \ end(heaps));\n}\n\ntemplate <typename Range>\nbool nim_first_player_wins(const\
    \ Range& heaps) {\n    return nim_sum(heaps) != 0;\n}\n\ntemplate <typename Range>\n\
    auto nim_winning_move(const Range& heaps) {\n    using std::begin;\n    using\
    \ std::end;\n    using T = std::decay_t<decltype(*begin(heaps))>;\n\n    const\
    \ T sum = nim_sum(heaps);\n    if (sum == 0) return std::optional<NimMove<T>>{};\n\
    \    int index = 0;\n    for (\n        auto iterator = begin(heaps);\n      \
    \  iterator != end(heaps);\n        ++iterator, ++index\n    ) {\n        const\
    \ T new_size = *iterator ^ sum;\n        if (new_size < *iterator) return std::optional(NimMove<T>{index,\
    \ new_size});\n    }\n    return std::optional<NimMove<T>>{};\n}\n\ntemplate <typename\
    \ Range>\nbool misere_nim_first_player_wins(const Range& heaps) {\n    using std::begin;\n\
    \    using std::end;\n\n    auto first = begin(heaps);\n    const auto last =\
    \ end(heaps);\n    bool odd_nonzero_heaps = false;\n    bool has_large_heap =\
    \ false;\n    using T = typename std::iterator_traits<decltype(first)>::value_type;\n\
    \    T sum{};\n    for (; first != last; ++first) {\n        sum ^= *first;\n\
    \        if (*first != 0) {\n            odd_nonzero_heaps = !odd_nonzero_heaps;\n\
    \        }\n        if (*first > 1) has_large_heap = true;\n    }\n    return\
    \ has_large_heap ? sum != 0 : !odd_nonzero_heaps;\n}\n\ntemplate <typename Range>\n\
    auto misere_nim_winning_move(const Range& heaps) {\n    using std::begin;\n  \
    \  using std::end;\n    using T = std::decay_t<decltype(*begin(heaps))>;\n\n \
    \   T sum{};\n    int ones = 0;\n    int large_heaps = 0;\n    int only_large_heap\
    \ = -1;\n    int index = 0;\n    for (\n        auto iterator = begin(heaps);\n\
    \        iterator != end(heaps);\n        ++iterator, ++index\n    ) {\n     \
    \   sum ^= *iterator;\n        if (*iterator == 1) ones++;\n        if (*iterator\
    \ > 1) {\n            large_heaps++;\n            only_large_heap = index;\n \
    \       }\n    }\n\n    if (large_heaps == 0) {\n        if (ones == 0 || ones\
    \ % 2 == 1) return std::optional<NimMove<T>>{};\n        index = 0;\n        for\
    \ (\n            auto iterator = begin(heaps);\n            iterator != end(heaps);\n\
    \            ++iterator, ++index\n        ) {\n            if (*iterator == 1)\
    \ return std::optional(NimMove<T>{index, T(0)});\n        }\n    }\n    if (large_heaps\
    \ == 1) {\n        const T new_size = ones % 2 == 0 ? T(1) : T(0);\n        return\
    \ std::optional(NimMove<T>{only_large_heap, new_size});\n    }\n    if (sum ==\
    \ 0) return std::optional<NimMove<T>>{};\n\n    index = 0;\n    for (auto iterator\
    \ = begin(heaps); iterator != end(heaps); ++iterator, ++index) {\n        const\
    \ T new_size = *iterator ^ sum;\n        if (new_size < *iterator) return std::optional(NimMove<T>{index,\
    \ new_size});\n    }\n    return std::optional<NimMove<T>>{};\n}\n\n}  // namespace\
    \ game\n}  // namespace m1une\n\n\n#line 1 \"game/nim_product.hpp\"\n\n\n\n#include\
    \ <array>\n#line 7 \"game/nim_product.hpp\"\n#include <limits>\n\nnamespace m1une\
    \ {\nnamespace game {\nnamespace internal {\n\ninline uint64_t nim_product_small(uint64_t\
    \ x, uint64_t y) {\n    if (x < 2 || y < 2) return x * y;\n\n    int shift = 1;\n\
    \    const uint64_t largest = x | y;\n    while ((uint64_t(1) << (shift * 2))\
    \ <= largest) shift *= 2;\n    const uint64_t mask = (uint64_t(1) << shift) -\
    \ 1;\n    const uint64_t x_high = x >> shift;\n    const uint64_t x_low = x &\
    \ mask;\n    const uint64_t y_high = y >> shift;\n    const uint64_t y_low = y\
    \ & mask;\n\n    const uint64_t high_product = nim_product_small(x_high, y_high);\n\
    \    const uint64_t low_product = nim_product_small(x_low, y_low);\n    const\
    \ uint64_t mixed_product =\n        nim_product_small(x_high ^ x_low, y_high ^\
    \ y_low);\n    return ((mixed_product ^ low_product) << shift) ^ low_product\n\
    \           ^ nim_product_small(high_product, uint64_t(1) << (shift - 1));\n}\n\
    \ninline const std::array<uint8_t, 1 << 16>& nim_product_8_table() {\n    static\
    \ const auto table = [] {\n        std::array<uint8_t, 1 << 16> result{};\n  \
    \      for (int x = 0; x < 256; ++x) {\n            for (int y = 0; y < 256; ++y)\
    \ {\n                result[(x << 8) | y] = uint8_t(nim_product_small(x, y));\n\
    \            }\n        }\n        return result;\n    }();\n    return table;\n\
    }\n\ninline uint64_t nim_product_8(uint64_t x, uint64_t y) {\n    return nim_product_8_table()[(x\
    \ << 8) | y];\n}\n\ntemplate <int Bits>\ninline uint64_t nim_product_fixed(uint64_t\
    \ x, uint64_t y) {\n    if constexpr (Bits == 8) {\n        return nim_product_8(x,\
    \ y);\n    } else {\n        constexpr int shift = Bits / 2;\n        constexpr\
    \ uint64_t mask = (uint64_t(1) << shift) - 1;\n        const uint64_t x_high =\
    \ x >> shift;\n        const uint64_t x_low = x & mask;\n        const uint64_t\
    \ y_high = y >> shift;\n        const uint64_t y_low = y & mask;\n\n        const\
    \ uint64_t high_product =\n            nim_product_fixed<shift>(x_high, y_high);\n\
    \        const uint64_t low_product = nim_product_fixed<shift>(x_low, y_low);\n\
    \        const uint64_t mixed_product = nim_product_fixed<shift>(\n          \
    \  x_high ^ x_low,\n            y_high ^ y_low\n        );\n        return ((mixed_product\
    \ ^ low_product) << shift) ^ low_product\n               ^ nim_product_fixed<shift>(\n\
    \                   high_product,\n                   uint64_t(1) << (shift -\
    \ 1)\n               );\n    }\n}\n\n}  // namespace internal\n\ninline uint64_t\
    \ nim_product(uint64_t x, uint64_t y) {\n    return internal::nim_product_fixed<64>(x,\
    \ y);\n}\n\ninline uint64_t nim_power(uint64_t base, uint64_t exponent) {\n  \
    \  uint64_t result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ result = nim_product(result, base);\n        base = nim_product(base, base);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t nim_inverse(uint64_t\
    \ value) {\n    assert(value != 0);\n    return nim_power(value, std::numeric_limits<uint64_t>::max()\
    \ - 1);\n}\n\ninline uint64_t nim_quotient(uint64_t numerator, uint64_t denominator)\
    \ {\n    assert(denominator != 0);\n    return nim_product(numerator, nim_inverse(denominator));\n\
    }\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line 1 \"game/partisan_game.hpp\"\
    \n\n\n\n#line 7 \"game/partisan_game.hpp\"\n\nnamespace m1une {\nnamespace game\
    \ {\n\nenum class PartisanOutcome { Left, Right, Next, Previous };\n\ninline std::vector<PartisanOutcome>\
    \ partisan_outcomes(\n    const std::vector<std::vector<int>>& left_moves,\n \
    \   const std::vector<std::vector<int>>& right_moves\n) {\n    const int size\
    \ = int(left_moves.size());\n    assert(int(right_moves.size()) == size);\n\n\
    \    std::vector<int> indegree(size);\n    for (int vertex = 0; vertex < size;\
    \ ++vertex) {\n        for (int next : left_moves[vertex]) {\n            assert(0\
    \ <= next && next < size);\n            indegree[next]++;\n        }\n       \
    \ for (int next : right_moves[vertex]) {\n            assert(0 <= next && next\
    \ < size);\n            indegree[next]++;\n        }\n    }\n\n    std::queue<int>\
    \ queue;\n    for (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex]\
    \ == 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ left_moves[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n        for (int next : right_moves[vertex]) {\n            if (--indegree[next]\
    \ == 0) queue.push(next);\n        }\n    }\n    assert(int(order.size()) == size);\n\
    \n    std::vector<bool> left_wins_moving(size);\n    std::vector<bool> left_wins_waiting(size);\n\
    \    std::vector<PartisanOutcome> outcome(size);\n    for (int position = size\
    \ - 1; position >= 0; --position) {\n        const int vertex = order[position];\n\
    \        for (int next : left_moves[vertex]) {\n            if (left_wins_waiting[next])\
    \ left_wins_moving[vertex] = true;\n        }\n        left_wins_waiting[vertex]\
    \ = true;\n        for (int next : right_moves[vertex]) {\n            if (!left_wins_moving[next])\
    \ left_wins_waiting[vertex] = false;\n        }\n\n        if (left_wins_moving[vertex]\
    \ && left_wins_waiting[vertex]) {\n            outcome[vertex] = PartisanOutcome::Left;\n\
    \        } else if (!left_wins_moving[vertex] && !left_wins_waiting[vertex]) {\n\
    \            outcome[vertex] = PartisanOutcome::Right;\n        } else if (left_wins_moving[vertex])\
    \ {\n            outcome[vertex] = PartisanOutcome::Next;\n        } else {\n\
    \            outcome[vertex] = PartisanOutcome::Previous;\n        }\n    }\n\
    \    return outcome;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line\
    \ 1 \"game/retrograde_analysis.hpp\"\n\n\n\n#line 8 \"game/retrograde_analysis.hpp\"\
    \n\nnamespace m1une {\nnamespace game {\n\nenum class GameOutcome { Win, Lose,\
    \ Draw };\n\nstruct RetrogradeResult {\n    std::vector<GameOutcome> outcome;\n\
    \    std::vector<int> distance;\n    std::vector<int> move;\n};\n\n// graph[v]\
    \ contains the states reachable from v in one move.\ninline RetrogradeResult retrograde_analysis(\n\
    \    const std::vector<std::vector<int>>& graph\n) {\n    const int size = int(graph.size());\n\
    \    std::vector<std::vector<int>> reverse_graph(size);\n    std::vector<int>\
    \ remaining(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n    \
    \    remaining[vertex] = int(graph[vertex].size());\n        for (int next : graph[vertex])\
    \ {\n            assert(0 <= next && next < size);\n            reverse_graph[next].push_back(vertex);\n\
    \        }\n    }\n\n    std::vector<GameOutcome> outcome(size, GameOutcome::Draw);\n\
    \    std::vector<int> distance(size, -1);\n    std::vector<int> move(size, -1);\n\
    \    std::vector<int> longest_win_successor(size);\n    std::vector<int> longest_win_move(size,\
    \ -1);\n    std::vector<bool> decided(size);\n    std::queue<int> queue;\n   \
    \ for (int vertex = 0; vertex < size; ++vertex) {\n        if (remaining[vertex]\
    \ == 0) {\n            outcome[vertex] = GameOutcome::Lose;\n            distance[vertex]\
    \ = 0;\n            decided[vertex] = true;\n            queue.push(vertex);\n\
    \        }\n    }\n\n    while (!queue.empty()) {\n        const int vertex =\
    \ queue.front();\n        queue.pop();\n        for (int previous : reverse_graph[vertex])\
    \ {\n            if (decided[previous]) continue;\n            if (outcome[vertex]\
    \ == GameOutcome::Lose) {\n                outcome[previous] = GameOutcome::Win;\n\
    \                distance[previous] = distance[vertex] + 1;\n                move[previous]\
    \ = vertex;\n                decided[previous] = true;\n                queue.push(previous);\n\
    \            } else {\n                if (longest_win_move[previous] == -1\n\
    \                    || longest_win_successor[previous] < distance[vertex]) {\n\
    \                    longest_win_successor[previous] = distance[vertex];\n   \
    \                 longest_win_move[previous] = vertex;\n                }\n  \
    \              if (--remaining[previous] == 0) {\n                    outcome[previous]\
    \ = GameOutcome::Lose;\n                    distance[previous] = longest_win_successor[previous]\
    \ + 1;\n                    move[previous] = longest_win_move[previous];\n   \
    \                 decided[previous] = true;\n                    queue.push(previous);\n\
    \                }\n            }\n        }\n    }\n    for (int vertex = 0;\
    \ vertex < size; ++vertex) {\n        if (outcome[vertex] != GameOutcome::Draw)\
    \ continue;\n        for (int next : graph[vertex]) {\n            if (outcome[next]\
    \ == GameOutcome::Draw) {\n                move[vertex] = next;\n            \
    \    break;\n            }\n        }\n    }\n    return {std::move(outcome),\
    \ std::move(distance), std::move(move)};\n}\n\n}  // namespace game\n}  // namespace\
    \ m1une\n\n\n#line 1 \"game/silver_dollar_game.hpp\"\n\n\n\n#line 7 \"game/silver_dollar_game.hpp\"\
    \n\nnamespace m1une {\nnamespace game {\n\ntemplate <typename T>\nT silver_dollar_grundy(const\
    \ std::vector<T>& coins) {\n    for (int index = 0; index < int(coins.size());\
    \ ++index) {\n        if constexpr (std::is_signed_v<T>) assert(coins[index] >=\
    \ 0);\n        if (index != 0) assert(coins[index - 1] < coins[index]);\n    }\n\
    \n    T result{};\n    int index = int(coins.size()) % 2;\n    if (index == 1)\
    \ result ^= coins[0];\n    for (; index + 1 < int(coins.size()); index += 2) {\n\
    \        result ^= coins[index + 1] - coins[index] - 1;\n    }\n    return result;\n\
    }\n\ntemplate <typename T>\nbool silver_dollar_first_player_wins(const std::vector<T>&\
    \ coins) {\n    return silver_dollar_grundy(coins) != 0;\n}\n\n}  // namespace\
    \ game\n}  // namespace m1une\n\n\n#line 1 \"game/subtraction_game.hpp\"\n\n\n\
    \n#include <algorithm>\n#line 7 \"game/subtraction_game.hpp\"\n\nnamespace m1une\
    \ {\nnamespace game {\n\ninline std::vector<int> subtraction_game_grundy(\n  \
    \  int max_heap,\n    const std::vector<int>& moves\n) {\n    assert(max_heap\
    \ >= 0);\n    for (int move : moves) assert(move > 0);\n\n    std::vector<int>\
    \ grundy(max_heap + 1);\n    std::vector<int> seen(moves.size() + 1, -1);\n  \
    \  for (int heap = 1; heap <= max_heap; ++heap) {\n        for (int move : moves)\
    \ {\n            if (move > heap) continue;\n            const int value = grundy[heap\
    \ - move];\n            if (value < int(seen.size())) seen[value] = heap;\n  \
    \      }\n        while (\n            grundy[heap] < int(seen.size())\n     \
    \       && seen[grundy[heap]] == heap\n        ) {\n            grundy[heap]++;\n\
    \        }\n    }\n    return grundy;\n}\n\ninline int subtraction_game_nim_sum(\n\
    \    const std::vector<int>& heaps,\n    const std::vector<int>& moves\n) {\n\
    \    int max_heap = 0;\n    for (int heap : heaps) {\n        assert(heap >= 0);\n\
    \        max_heap = std::max(max_heap, heap);\n    }\n    const std::vector<int>\
    \ grundy = subtraction_game_grundy(max_heap, moves);\n    int result = 0;\n  \
    \  for (int heap : heaps) result ^= grundy[heap];\n    return result;\n}\n\ninline\
    \ bool subtraction_game_first_player_wins(\n    const std::vector<int>& heaps,\n\
    \    const std::vector<int>& moves\n) {\n    return subtraction_game_nim_sum(heaps,\
    \ moves) != 0;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line 13\
    \ \"game/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_GAME_ALL_HPP

    #define M1UNE_GAME_ALL_HPP 1


    #include "green_hackenbush.hpp"

    #include "grundy.hpp"

    #include "minimax.hpp"

    #include "nim.hpp"

    #include "nim_product.hpp"

    #include "partisan_game.hpp"

    #include "retrograde_analysis.hpp"

    #include "silver_dollar_game.hpp"

    #include "subtraction_game.hpp"


    #endif  // M1UNE_GAME_ALL_HPP

    '
  dependsOn:
  - game/green_hackenbush.hpp
  - game/grundy.hpp
  - game/minimax.hpp
  - game/nim.hpp
  - game/nim_product.hpp
  - game/partisan_game.hpp
  - game/retrograde_analysis.hpp
  - game/silver_dollar_game.hpp
  - game/subtraction_game.hpp
  isVerificationFile: false
  path: game/all.hpp
  requiredBy: []
  timestamp: '2026-08-24 02:13:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
documentation_of: game/all.hpp
layout: document
title: Game Library
---

## Overview

`game/all.hpp` includes the game-theory library. Public APIs use the
`m1une::game` namespace.

## Included Headers

| Header | Contents |
| --- | --- |
| `game/nim.hpp` | Ordinary and misere Nim outcomes and winning moves. |
| `game/nim_product.hpp` | 64-bit nimber multiplication, powers, inverses, and quotients. |
| `game/grundy.hpp` | Linear-time Sprague-Grundy numbers for finite DAG games. |
| `game/retrograde_analysis.hpp` | Win/lose/draw classification and strategy recovery for finite directed games, including cycles. |
| `game/partisan_game.hpp` | Four outcome classes for finite short partisan games. |
| `game/minimax.hpp` | Backward-induction values and optimal moves for scoring games on DAGs. |
| `game/subtraction_game.hpp` | Grundy tables and multi-heap outcomes for subtraction games. |
| `game/green_hackenbush.hpp` | Linear-time Grundy numbers for Green Hackenbush forests. |
| `game/silver_dollar_game.hpp` | Linear-time Grundy numbers for coin-sliding positions. |
