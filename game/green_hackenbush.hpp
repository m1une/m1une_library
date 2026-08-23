#ifndef M1UNE_GAME_GREEN_HACKENBUSH_HPP
#define M1UNE_GAME_GREEN_HACKENBUSH_HPP 1

#include <cassert>
#include <cstdint>
#include <vector>

namespace m1une {
namespace game {

// Every vertex represents one green edge. parent[v] == -1 attaches that edge
// to the ground; otherwise it attaches it above the edge parent[v].
inline uint64_t green_hackenbush_grundy(const std::vector<int>& parent) {
    const int size = int(parent.size());
    std::vector<std::vector<int>> children(size);
    std::vector<int> roots;
    for (int edge = 0; edge < size; ++edge) {
        assert(-1 <= parent[edge] && parent[edge] < size);
        assert(parent[edge] != edge);
        if (parent[edge] == -1) {
            roots.push_back(edge);
        } else {
            children[parent[edge]].push_back(edge);
        }
    }

    std::vector<int> order = roots;
    order.reserve(size);
    for (int position = 0; position < int(order.size()); ++position) {
        const int edge = order[position];
        for (int child : children[edge]) order.push_back(child);
    }
    assert(int(order.size()) == size);

    std::vector<uint64_t> branch(size);
    for (int position = size - 1; position >= 0; --position) {
        const int edge = order[position];
        uint64_t children_grundy = 0;
        for (int child : children[edge]) children_grundy ^= branch[child];
        branch[edge] = children_grundy + 1;
    }

    uint64_t result = 0;
    for (int root : roots) result ^= branch[root];
    return result;
}

inline bool green_hackenbush_first_player_wins(
    const std::vector<int>& parent
) {
    return green_hackenbush_grundy(parent) != 0;
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_GREEN_HACKENBUSH_HPP
