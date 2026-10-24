#ifndef M1UNE_CONVEX_MONGE_ANTI_MONGE_SHORTEST_PATH_HPP
#define M1UNE_CONVEX_MONGE_ANTI_MONGE_SHORTEST_PATH_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "smawk.hpp"

namespace m1une {
namespace convex {

template <class T>
struct AntiMongeShortestPathResult {
    std::vector<T> distance;
    std::vector<int> parent;
};

// dist[j] = min(dist[i] + cost(i, j)), where j - i >= minimum_step.
// cost must be finite and anti-Monge on valid rectangles; see the docs.
// O(N log N + N * minimum_step) time for O(1) cost evaluations.
// In particular, minimum_step = 1 or 2 gives O(N log N) time.
template <class T, class Cost>
AntiMongeShortestPathResult<T> anti_monge_shortest_path(
    int vertex_count, Cost cost, T infinity, int minimum_step = 1) {
    assert(vertex_count >= 0);
    assert(minimum_step >= 1);
    assert(T() < infinity);

    AntiMongeShortestPathResult<T> result;
    result.distance.assign(vertex_count, infinity);
    result.parent.assign(vertex_count, -1);
    if (vertex_count == 0) return result;
    result.distance[0] = T();
    if (minimum_step >= vertex_count) return result;

    auto relax = [&](int from, int to) {
        if (result.distance[from] == infinity) return;
        T candidate = result.distance[from] + cost(from, to);
        if (candidate < result.distance[to] ||
            (candidate == result.distance[to] && from > result.parent[to])) {
            result.distance[to] = candidate;
            result.parent[to] = from;
        }
    };

    // All pairs in this rectangle are valid. Remove unreachable columns,
    // then reverse the remaining columns to turn anti-Monge into Monge.
    auto rectangle = [&](int first, int last, int top, int bottom) {
        if (first == last || top == bottom) return;
        std::vector<int> sources;
        for (int from = last; from > first;) {
            --from;
            if (result.distance[from] != infinity) sources.push_back(from);
        }
        if (sources.empty()) return;
        if (sources.size() == 1) {
            for (int to = top; to < bottom; to++) relax(sources[0], to);
            return;
        }
        auto argmin = smawk_row_argmin(
            bottom - top, int(sources.size()), [&](int row, int column) -> T {
                int from = sources[column];
                return result.distance[from] + cost(from, top + row);
            });
        for (int row = 0; row < bottom - top; row++) {
            relax(sources[argmin[row]], top + row);
        }
    };

    auto solve = [&](auto& self, int left, int right) -> void {
        // Such a block contains no valid internal edge.
        if (right - left <= minimum_step) return;
        int middle = left + (right - left) / 2;
        self(self, left, middle);

        // Two valid rectangles and a small corner partition the cross edges.
        int source_end = std::max(left, middle - (minimum_step - 1));
        int target_begin = middle + std::min(right - middle, minimum_step - 1);
        rectangle(left, middle, target_begin, right);
        rectangle(left, source_end, middle, target_begin);
        for (int from = source_end; from < middle; from++) {
            // Subtraction avoids overflow when minimum_step is large.
            if (minimum_step >= target_begin - from) continue;
            for (int to = std::max(middle, from + minimum_step);
                 to < target_begin; to++) {
                relax(from, to);
            }
        }

        // Incoming transitions must be applied BEFORE solving the right half.
        self(self, middle, right);
    };
    solve(solve, 0, vertex_count);
    return result;
}

}  // namespace convex
}  // namespace m1une

#endif  // M1UNE_CONVEX_MONGE_ANTI_MONGE_SHORTEST_PATH_HPP
