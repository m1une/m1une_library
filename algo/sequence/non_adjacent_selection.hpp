#ifndef M1UNE_ALGO_SEQUENCE_NON_ADJACENT_SELECTION_HPP
#define M1UNE_ALGO_SEQUENCE_NON_ADJACENT_SELECTION_HPP 1

#include <functional>
#include <queue>
#include <vector>

namespace m1une {
namespace algo {

namespace detail {

template <typename T>
struct NonAdjacentSelectionEntry {
    T value;
    int index;
};

template <typename T, typename Better>
struct NonAdjacentSelectionCompare {
    Better better;

    bool operator()(
        const NonAdjacentSelectionEntry<T>& lhs,
        const NonAdjacentSelectionEntry<T>& rhs
    ) const {
        if (better(lhs.value, rhs.value)) return false;
        if (better(rhs.value, lhs.value)) return true;
        return lhs.index > rhs.index;
    }
};

template <typename T, typename Better>
std::vector<T> non_adjacent_selection_sums(const std::vector<T>& values, Better better) {
    const int n = int(values.size());
    std::vector<T> weight = values;
    std::vector<int> left(n), right(n);
    std::vector<char> alive(n, true);
    for (int i = 0; i < n; ++i) {
        left[i] = i - 1;
        right[i] = (i + 1 == n ? -1 : i + 1);
    }

    using Entry = NonAdjacentSelectionEntry<T>;
    using Compare = NonAdjacentSelectionCompare<T, Better>;
    std::priority_queue<Entry, std::vector<Entry>, Compare> heap(Compare{better});
    for (int i = 0; i < n; ++i) heap.push(Entry{weight[i], i});

    std::vector<T> result;
    result.reserve((n + 1) / 2);
    T sum{};
    while (int(result.size()) < (n + 1) / 2) {
        while (!alive[heap.top().index]) heap.pop();
        const int current = heap.top().index;
        heap.pop();

        sum += weight[current];
        result.push_back(sum);

        const int l = left[current];
        const int r = right[current];
        if (l != -1 && r != -1) {
            weight[current] = weight[l] + weight[r] - weight[current];

            const int ll = left[l];
            const int rr = right[r];
            alive[l] = false;
            alive[r] = false;
            left[current] = ll;
            right[current] = rr;
            if (ll != -1) right[ll] = current;
            if (rr != -1) left[rr] = current;
            heap.push(Entry{weight[current], current});
        } else {
            const int ll = (l == -1 ? -1 : left[l]);
            const int rr = (r == -1 ? -1 : right[r]);
            alive[current] = false;
            if (l != -1) alive[l] = false;
            if (r != -1) alive[r] = false;
            if (ll != -1) right[ll] = rr;
            if (rr != -1) left[rr] = ll;
        }
    }
    return result;
}

}  // namespace detail

// Entry k - 1 is the maximum sum obtained by selecting exactly k values, with
// no two selected indices adjacent.
template <typename T>
std::vector<T> maximum_non_adjacent_selection_sums(const std::vector<T>& values) {
    return detail::non_adjacent_selection_sums(values, std::greater<T>{});
}

// Entry k - 1 is the minimum sum obtained by selecting exactly k values, with
// no two selected indices adjacent.
template <typename T>
std::vector<T> minimum_non_adjacent_selection_sums(const std::vector<T>& values) {
    return detail::non_adjacent_selection_sums(values, std::less<T>{});
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_SEQUENCE_NON_ADJACENT_SELECTION_HPP
