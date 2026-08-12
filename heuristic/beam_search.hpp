#ifndef M1UNE_HEURISTIC_BEAM_SEARCH_HPP
#define M1UNE_HEURISTIC_BEAM_SEARCH_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

#include "objective.hpp"

namespace m1une {
namespace heuristic {

template <class State, class Score>
struct BeamSearchResult {
    State state;
    Score score;
    int depth;
    std::size_t expanded_states;
    std::size_t generated_states;
};

namespace beam_search_detail {

template <class State, class Score>
struct Node {
    State state;
    Score score;
    std::size_t order;
};

template <class State, class Score>
struct BetterNode {
    Objective objective;

    bool operator()(const Node<State, Score>& first,
                    const Node<State, Score>& second) const {
        if (better_score(first.score, second.score, objective)) return true;
        if (better_score(second.score, first.score, objective)) return false;
        return first.order < second.order;
    }
};

}  // namespace beam_search_detail

// expand(state, next_depth) may return a range of children. For allocation-free
// generation, expand(state, next_depth, emit) may instead call emit(child).
// evaluate(state) returns its score. The best beam_width states are retained at
// every depth, and the best state in the last non-empty layer is returned.
template <class State, class Expand, class Evaluate>
auto beam_search(State initial_state, int depth_limit, int beam_width,
                 Expand expand, Evaluate evaluate,
                 Objective objective = Objective::maximize) {
    assert(0 <= depth_limit);
    assert(0 < beam_width);

    using Score = std::remove_cvref_t<
        std::invoke_result_t<Evaluate&, const State&>>;
    using Node = beam_search_detail::Node<State, Score>;
    using Better = beam_search_detail::BetterNode<State, Score>;

    Score initial_score = std::invoke(evaluate, initial_state);
    std::vector<Node> beam;
    beam.push_back(Node{std::move(initial_state),
                        std::move(initial_score), 0});

    std::size_t expanded_states = 0;
    std::size_t generated_states = 0;
    int reached_depth = 0;
    if (depth_limit < 0 || beam_width <= 0) depth_limit = 0;

    Better better{objective};
    for (int next_depth = 1; next_depth <= depth_limit; next_depth++) {
        std::vector<Node> candidates;
        candidates.reserve(static_cast<std::size_t>(beam_width));
        std::size_t order = 0;

        for (const Node& node : beam) {
            expanded_states++;
            auto emit = [&](auto&& candidate_state) {
                using Candidate = decltype(candidate_state);
                static_assert(std::is_constructible_v<State, Candidate>);
                State state(std::forward<Candidate>(candidate_state));
                Score candidate_score = std::invoke(evaluate, state);
                Node candidate{std::move(state), std::move(candidate_score),
                               order++};
                generated_states++;
                if (int(candidates.size()) < beam_width) {
                    candidates.push_back(std::move(candidate));
                    std::push_heap(candidates.begin(), candidates.end(), better);
                } else if (better(candidate, candidates.front())) {
                    std::pop_heap(candidates.begin(), candidates.end(), better);
                    candidates.back() = std::move(candidate);
                    std::push_heap(candidates.begin(), candidates.end(), better);
                }
            };
            if constexpr (std::invocable<Expand&, const State&, int>) {
                auto next_states =
                    std::invoke(expand, node.state, next_depth);
                for (auto& candidate_state : next_states) {
                    emit(std::move(candidate_state));
                }
            } else if constexpr (std::invocable<Expand&, const State&>) {
                auto next_states = std::invoke(expand, node.state);
                for (auto& candidate_state : next_states) {
                    emit(std::move(candidate_state));
                }
            } else {
                std::invoke(expand, node.state, next_depth, emit);
            }
        }

        if (candidates.empty()) break;
        beam = std::move(candidates);
        reached_depth = next_depth;
    }

    int best = 0;
    for (int index = 1; index < int(beam.size()); index++) {
        if (better(beam[index], beam[best])) best = index;
    }
    return BeamSearchResult<State, Score>{
        std::move(beam[best].state), std::move(beam[best].score),
        reached_depth, expanded_states, generated_states};
}

}  // namespace heuristic
}  // namespace m1une

#endif  // M1UNE_HEURISTIC_BEAM_SEARCH_HPP
