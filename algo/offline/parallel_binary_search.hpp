#ifndef M1UNE_ALGO_OFFLINE_PARALLEL_BINARY_SEARCH_HPP
#define M1UNE_ALGO_OFFLINE_PARALLEL_BINARY_SEARCH_HPP 1

#include <cassert>
#include <vector>

namespace m1une {
namespace algo {

template <class Apply, class Check, class Reset>
std::vector<int> parallel_binary_search(
    int query_count,
    int event_count,
    Apply apply,
    Check check,
    Reset reset
) {
    assert(0 <= query_count);
    assert(0 <= event_count);

    std::vector<int> low(query_count, -1);
    std::vector<int> high(query_count, event_count + 1);
    std::vector<std::vector<int>> bucket(event_count + 1);

    while (true) {
        bool active = false;
        for (auto& queries : bucket) queries.clear();

        for (int query = 0; query < query_count; ++query) {
            if (high[query] - low[query] <= 1) continue;
            const int middle = low[query] + (high[query] - low[query]) / 2;
            bucket[middle].push_back(query);
            active = true;
        }
        if (!active) break;

        reset();
        int applied = 0;
        for (int middle = 0; middle <= event_count; ++middle) {
            while (applied < middle) {
                apply(applied);
                ++applied;
            }
            for (int query : bucket[middle]) {
                if (check(query)) {
                    high[query] = middle;
                } else {
                    low[query] = middle;
                }
            }
        }
    }

    return high;
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_OFFLINE_PARALLEL_BINARY_SEARCH_HPP
