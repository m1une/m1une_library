#ifndef M1UNE_HEURISTIC_OBJECTIVE_HPP
#define M1UNE_HEURISTIC_OBJECTIVE_HPP 1

namespace m1une {
namespace heuristic {

enum class Objective {
    minimize,
    maximize,
};

template <class Score>
bool better_score(const Score& first, const Score& second,
                  Objective objective) {
    if (objective == Objective::maximize) return second < first;
    return first < second;
}

}  // namespace heuristic
}  // namespace m1une

#endif  // M1UNE_HEURISTIC_OBJECTIVE_HPP
