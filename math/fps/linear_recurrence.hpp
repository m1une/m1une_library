#ifndef M1UNE_FPS_LINEAR_RECURRENCE_HPP
#define M1UNE_FPS_LINEAR_RECURRENCE_HPP 1

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

// Returns a shortest linear recurrence satisfied by the observed sequence.
// The returned coefficients use
// a[n] = recurrence[0] * a[n - 1] + ... + recurrence[d - 1] * a[n - d].
template <class Mint>
std::vector<Mint> berlekamp_massey(const std::vector<Mint>& sequence) {
    std::vector<Mint> connection(1, Mint(1));
    std::vector<Mint> previous(1, Mint(1));
    int order = 0;
    int shift = 1;
    Mint previous_discrepancy = Mint(1);

    for (int index = 0; index < int(sequence.size()); index++) {
        Mint discrepancy = sequence[index];
        for (int i = 1; i <= order; i++) {
            discrepancy += connection[i] * sequence[index - i];
        }
        if (discrepancy == Mint(0)) {
            shift++;
            continue;
        }

        const Mint scale = discrepancy / previous_discrepancy;
        std::vector<Mint> old_connection = connection;
        if (connection.size() < previous.size() + std::size_t(shift)) {
            connection.resize(previous.size() + std::size_t(shift));
        }
        for (int i = 0; i < int(previous.size()); i++) {
            connection[i + shift] -= scale * previous[i];
        }

        if (2 * order <= index) {
            order = index + 1 - order;
            previous = std::move(old_connection);
            previous_discrepancy = discrepancy;
            shift = 1;
        } else {
            shift++;
        }
    }

    std::vector<Mint> recurrence(order);
    for (int i = 0; i < order; i++) recurrence[i] = Mint(0) - connection[i + 1];
    return recurrence;
}

template <class Mint>
Mint coefficient_of_rational(FormalPowerSeries<Mint> numerator,
                             FormalPowerSeries<Mint> denominator, uint64_t index) {
    using Fps = FormalPowerSeries<Mint>;
    assert(!denominator.empty() && denominator[0] != Mint(0));

    while (index > 0) {
        Fps denominator_negative = denominator;
        for (int i = 1; i < int(denominator_negative.size()); i += 2) {
            denominator_negative[i] = Mint(0) - denominator_negative[i];
        }

        Fps numerator_product = numerator * denominator_negative;
        Fps denominator_product = denominator * denominator_negative;
        Fps next_numerator;
        Fps next_denominator;
        next_numerator.reserve((numerator_product.size() + 1) / 2);
        next_denominator.reserve((denominator_product.size() + 1) / 2);
        for (int i = int(index & 1); i < int(numerator_product.size()); i += 2) {
            next_numerator.emplace_back(numerator_product[i]);
        }
        for (int i = 0; i < int(denominator_product.size()); i += 2) {
            next_denominator.emplace_back(denominator_product[i]);
        }
        numerator = std::move(next_numerator);
        denominator = std::move(next_denominator);
        index >>= 1;
    }
    return numerator.empty() ? Mint(0) : numerator[0] / denominator[0];
}

template <class Mint>
Mint linear_recurrence_kth(const std::vector<Mint>& initial,
                           const std::vector<Mint>& recurrence, uint64_t index) {
    using Fps = FormalPowerSeries<Mint>;
    assert(!initial.empty() && initial.size() == recurrence.size());
    if (index < initial.size()) return initial[index];

    const int order = int(recurrence.size());
    Fps denominator(order + 1);
    denominator[0] = 1;
    for (int i = 0; i < order; i++) denominator[i + 1] = Mint(0) - recurrence[i];
    Fps numerator = (Fps(initial) * denominator).pre(order);
    return coefficient_of_rational(std::move(numerator), std::move(denominator), index);
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_LINEAR_RECURRENCE_HPP
