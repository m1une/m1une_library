#ifndef M1UNE_HEURISTIC_HILL_CLIMBING_HPP
#define M1UNE_HEURISTIC_HILL_CLIMBING_HPP 1

#include <concepts>

#include "objective.hpp"

namespace m1une {
namespace heuristic {

using HillClimbingObjective = Objective;

class HillClimbing {
   private:
    Objective _objective;
    bool _accept_equal;

   public:
    explicit HillClimbing(Objective objective = Objective::maximize,
                          bool accept_equal = false)
        : _objective(objective), _accept_equal(accept_equal) {}

    bool accept_delta(long double candidate_minus_current) const {
        if (_objective == Objective::maximize) {
            return _accept_equal ? 0.0L <= candidate_minus_current
                                 : 0.0L < candidate_minus_current;
        }
        return _accept_equal ? candidate_minus_current <= 0.0L
                             : candidate_minus_current < 0.0L;
    }

    template <std::convertible_to<long double> CurrentScore,
              std::convertible_to<long double> CandidateScore>
    bool accept(CurrentScore current_score,
                CandidateScore candidate_score) const {
        long double delta = static_cast<long double>(candidate_score) -
                            static_cast<long double>(current_score);
        return accept_delta(delta);
    }
};

}  // namespace heuristic
}  // namespace m1une

#endif  // M1UNE_HEURISTIC_HILL_CLIMBING_HPP
