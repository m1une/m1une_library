#ifndef M1UNE_HEURISTIC_SIMULATED_ANNEALING_HPP
#define M1UNE_HEURISTIC_SIMULATED_ANNEALING_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>

#include "objective.hpp"

namespace m1une {
namespace heuristic {

using AnnealingObjective = Objective;

enum class AnnealingCooling {
    linear,
    exponential,
};

class SimulatedAnnealing {
   private:
    double _start_temperature;
    double _end_temperature;
    AnnealingObjective _objective;
    AnnealingCooling _cooling;

    long double directed_delta(long double candidate_minus_current) const {
        if (_objective == AnnealingObjective::maximize) {
            return candidate_minus_current;
        }
        return -candidate_minus_current;
    }

   public:
    SimulatedAnnealing(
        double start_temperature, double end_temperature,
        AnnealingObjective objective = AnnealingObjective::maximize,
        AnnealingCooling cooling = AnnealingCooling::exponential)
        : _start_temperature(start_temperature),
          _end_temperature(end_temperature),
          _objective(objective),
          _cooling(cooling) {
        assert(std::isfinite(start_temperature));
        assert(std::isfinite(end_temperature));
        assert(0.0 <= end_temperature);
        assert(end_temperature <= start_temperature);
        assert(cooling != AnnealingCooling::exponential ||
               0.0 < end_temperature);
    }

    double temperature(double progress) const {
        assert(std::isfinite(progress));
        assert(0.0 <= progress && progress <= 1.0);
        progress = std::clamp(progress, 0.0, 1.0);
        if (_cooling == AnnealingCooling::linear) {
            return _start_temperature +
                   (_end_temperature - _start_temperature) * progress;
        }
        return _start_temperature *
               std::pow(_end_temperature / _start_temperature, progress);
    }

    double acceptance_probability_delta(
        long double candidate_minus_current, double progress) const {
        long double improvement = directed_delta(candidate_minus_current);
        if (0.0L <= improvement) return 1.0;
        double current_temperature = temperature(progress);
        if (current_temperature == 0.0) return 0.0;
        return std::exp(static_cast<double>(
            improvement / static_cast<long double>(current_temperature)));
    }

    bool accept_delta(long double candidate_minus_current, double progress,
                      double random01) const {
        assert(std::isfinite(random01));
        assert(0.0 <= random01 && random01 < 1.0);
        return random01 <
               acceptance_probability_delta(candidate_minus_current, progress);
    }

    template <std::convertible_to<long double> CurrentScore,
              std::convertible_to<long double> CandidateScore>
    double acceptance_probability(CurrentScore current_score,
                                  CandidateScore candidate_score,
                                  double progress) const {
        long double delta = static_cast<long double>(candidate_score) -
                            static_cast<long double>(current_score);
        return acceptance_probability_delta(delta, progress);
    }

    template <std::convertible_to<long double> CurrentScore,
              std::convertible_to<long double> CandidateScore>
    bool accept(CurrentScore current_score, CandidateScore candidate_score,
                double progress, double random01) const {
        long double delta = static_cast<long double>(candidate_score) -
                            static_cast<long double>(current_score);
        return accept_delta(delta, progress, random01);
    }
};

}  // namespace heuristic
}  // namespace m1une

#endif  // M1UNE_HEURISTIC_SIMULATED_ANNEALING_HPP
