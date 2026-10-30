#ifndef M1UNE_CONVEX_MONGE_SHORTEST_PATH_HPP
#define M1UNE_CONVEX_MONGE_SHORTEST_PATH_HPP 1

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

#include "monge/larsch.hpp"
#include "monge/smawk.hpp"

namespace m1une {
namespace convex {

template <class T>
struct MongeShortestPathResult {
    std::vector<T> distance;
    std::vector<int> parent;
};

// Same-array forward recurrence: dp[j] = min(dp[i] + cost(i,j)), j-i >= D.
// Finite Monge costs on every fully valid rectangle. Smallest parent on ties.
// O(N) time/evaluations/memory, for any D >= 1. Never evaluates invalid edges
// or adds infinity. Vertices 1..D-1 are unreachable; all vertices >=D are reachable.
template <class T, class Cost>
MongeShortestPathResult<T> monge_shortest_path(
    int vertex_count, Cost cost, T infinity, int minimum_step = 1) {
    assert(vertex_count >= 0);
    assert(minimum_step >= 1);
    assert(T() < infinity);
    MongeShortestPathResult<T> result;
    result.distance.assign(vertex_count, infinity);
    result.parent.assign(vertex_count, -1);
    if (vertex_count == 0) return result;
    result.distance[0] = T();
    if (minimum_step >= vertex_count) return result;

    // Row r targets r+D. Columns 1..D-1 would be unreachable permanently;
    // duplicate source 0 instead. This nondecreasing source map preserves Monge.
    auto source = [&](int column) { return column < minimum_step ? 0 : column; };
    Larsch optimizer(vertex_count - minimum_step, [&](int row, int column) -> T {
        int from = source(column);
        return result.distance[from] + cost(from, row + minimum_step);
    });
    for (int to = minimum_step; to < vertex_count; ++to) {
        int from = source(optimizer.next_argmin());
        result.parent[to] = from;
        result.distance[to] = result.distance[from] + cost(from, to);
    }
    return result;
}

// dist[j] = min(dist[i] + cost(i, j)), where j - i >= minimum_step.
// Same-array recurrence. Finite anti-Monge costs on every valid rectangle.
// Largest parent on ties; O(N) memory. See docs for the numeric contract.
// O(N log N + N * minimum_step) time for O(1) cost evaluations.
// In particular, minimum_step = 1 or 2 gives O(N log N) time.
template <class T, class Cost>
MongeShortestPathResult<T> anti_monge_shortest_path(
    int vertex_count, Cost cost, T infinity, int minimum_step = 1) {
    assert(vertex_count >= 0);
    assert(minimum_step >= 1);
    assert(T() < infinity);

    MongeShortestPathResult<T> result;
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
        std::vector<int> targets(bottom - top);
        std::iota(targets.begin(), targets.end(), top);
        auto argmin = smawk_row_argmin(targets, sources, [&](int to, int from) -> T {
            return result.distance[from] + cost(from, to);
        });
        for (int row = 0; row < bottom - top; row++) relax(argmin[row], top + row);
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

#endif  // M1UNE_CONVEX_MONGE_SHORTEST_PATH_HPP
