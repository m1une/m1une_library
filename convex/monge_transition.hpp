#ifndef M1UNE_CONVEX_MONGE_TRANSITION_HPP
#define M1UNE_CONVEX_MONGE_TRANSITION_HPP 1

#include <cassert>
#include <span>
#include <type_traits>
#include <utility>
#include <vector>

#include "monge/monotone_minima.hpp"
#include "monge/smawk.hpp"

namespace m1une {
namespace convex {

template <class T>
struct MatrixTransitionResult {
    std::vector<T> value;
    std::vector<int> argmin;
};

namespace monge_transition_detail {

template <class T, class Cost, class Source, class Target, class Search>
auto solve(const std::vector<T>& previous, int targets, int sources, Cost cost,
           Source source, Target target, Search search) {
    using R = std::decay_t<decltype(previous[0] + cost(0, 0))>;
    auto value = [&](int row, int column) -> R {
        return previous[source(column)] + cost(source(column), target(row));
    };
    MatrixTransitionResult<R> result;
    result.argmin = search(targets, sources, value);
    result.value.resize(targets);
    for (int row = 0; row < targets; ++row) {
        int& column = result.argmin[row];
        if (column == -1) continue;
        result.value[row] = value(row, column);
        column = source(column);
    }
    return result;
}

}  // namespace monge_transition_detail

// Offline layer: g[j] = min_i(previous[i] + cost(i,j)); previous is finalized.
// Leftmost minimizing sources must be nondecreasing with target index. This is
// weaker than total monotonicity. O(H + W log(H+1)) time, O(H) result memory.
// Ties select smallest source. Empty sources give argmin=-1, value=R().
template <class T, class Cost>
auto monotone_transition(const std::vector<T>& previous, int state_count, Cost cost) {
    auto identity = [](int i) { return i; };
    return monge_transition_detail::solve(previous, state_count, int(previous.size()),
        cost, identity, identity, [](int h, int w, auto value) {
            return monotone_row_argmin(h, w, value);
        });
}

// Same offline recurrence, with finite Monge cost(source,target). Adding source
// constants preserves Monge. O(H+W) time/memory; smallest source on ties.
template <class T, class Cost>
auto monge_transition(const std::vector<T>& previous, int state_count, Cost cost) {
    auto identity = [](int i) { return i; };
    return monge_transition_detail::solve(previous, state_count, int(previous.size()),
        cost, identity, identity, [](int h, int w, auto value) {
            return smawk_row_argmin(h, w, value);
        });
}

// Anti-Monge specialization: reverse source order internally. Largest source
// on ties; O(H+W) time/memory. All source-target pairs must be legal and finite.
template <class T, class Cost>
auto anti_monge_transition(const std::vector<T>& previous, int state_count, Cost cost) {
    int width = int(previous.size());
    return monge_transition_detail::solve(previous, state_count, width, cost,
        [=](int i) { return width - 1 - i; }, [](int i) { return i; },
        [](int h, int w, auto value) { return smawk_row_argmin(h, w, value); });
}

// Ordered variants: the virtual matrix is previous[sources[c]] +
// cost(sources[c], targets[r]). Return original source IDs, in target list order.
// IDs must be distinct/nonnegative; sources must index previous. Ties choose the
// first source in the supplied order. No same-array recurrence is computed.
template <class T, class Cost>
auto monotone_transition(const std::vector<T>& previous,
                         std::span<const int> targets, std::span<const int> sources,
                         Cost cost) {
    for (int i : sources) { assert(0 <= i && i < int(previous.size())); (void)i; }
    for (int j : targets) { assert(j >= 0); (void)j; }
    return monge_transition_detail::solve(previous, int(targets.size()),
        int(sources.size()), cost, [&](int i) { return sources[i]; },
        [&](int i) { return targets[i]; },
        [](int h, int w, auto value) { return monotone_row_argmin(h, w, value); });
}

template <class T, class Cost>
auto monge_transition(const std::vector<T>& previous,
                      std::span<const int> targets, std::span<const int> sources,
                      Cost cost) {
    for (int i : sources) { assert(0 <= i && i < int(previous.size())); (void)i; }
    for (int j : targets) { assert(j >= 0); (void)j; }
    return monge_transition_detail::solve(previous, int(targets.size()),
        int(sources.size()), cost, [&](int i) { return sources[i]; },
        [&](int i) { return targets[i]; },
        [](int h, int w, auto value) { return smawk_row_argmin(h, w, value); });
}

}  // namespace convex
}  // namespace m1une

#endif  // M1UNE_CONVEX_MONGE_TRANSITION_HPP
