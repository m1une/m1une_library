#ifndef M1UNE_GRAPH_COUNTING_HPP
#define M1UNE_GRAPH_COUNTING_HPP 1

#include <cassert>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#include "../fps/convolution.hpp"
#include "../fps/formal_power_series.hpp"
#include "../math/combinatorics.hpp"

namespace m1une {
namespace graph {

namespace graph_counting_detail {

template <class Mint>
using Fps = fps::FormalPowerSeries<Mint>;

template <class Mint>
void assert_maximum(int maximum) {
    assert(maximum >= 0);
    assert(static_cast<uint64_t>(maximum) < Mint::mod());
}

template <class Mint>
Mint inverse_two() {
    assert(Mint::mod() != 2);
    return Mint(2).inv();
}

template <class Mint>
std::vector<Mint> to_egf(
    std::vector<Mint> values,
    const math::Combinatorics<Mint>& combinations
) {
    for (int i = 0; i < int(values.size()); i++) {
        values[i] *= combinations.inverse_factorial(i);
    }
    return values;
}

template <class Mint>
std::vector<Mint> from_egf(
    std::vector<Mint> coefficients,
    const math::Combinatorics<Mint>& combinations
) {
    for (int i = 0; i < int(coefficients.size()); i++) {
        coefficients[i] *= combinations.factorial(i);
    }
    return coefficients;
}

template <class Mint>
std::vector<Mint> two_to_binom2(int maximum) {
    std::vector<Mint> result(maximum + 1);
    result[0] = 1;
    Mint multiplier = 1;
    for (int n = 1; n <= maximum; n++) {
        result[n] = result[n - 1] * multiplier;
        multiplier += multiplier;
    }
    return result;
}

template <class Mint>
Fps<Mint> colored_bipartite_egf(
    int maximum,
    const math::Combinatorics<Mint>& combinations
) {
    const Mint half = inverse_two<Mint>();

    Fps<Mint> kernel(maximum + 1);
    kernel[0] = 1;
    Mint multiplier = 1;
    for (int i = 1; i <= maximum; i++) {
        kernel[i] = kernel[i - 1] * multiplier;
        multiplier *= half;
    }
    for (int i = 0; i <= maximum; i++) {
        kernel[i] *= combinations.inverse_factorial(i);
    }

    Fps<Mint> result = (kernel * kernel).pre(maximum + 1);
    std::vector<Mint> edge_powers = two_to_binom2<Mint>(maximum);
    for (int i = 0; i <= maximum; i++) result[i] *= edge_powers[i];
    return result;
}

}  // namespace graph_counting_detail

template <class Mint>
std::vector<Mint> count_labeled_undirected_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    return graph_counting_detail::two_to_binom2<Mint>(maximum);
}

template <class Mint>
std::vector<Mint> count_labeled_connected_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    graph_counting_detail::Fps<Mint> egf =
        graph_counting_detail::to_egf(count_labeled_undirected_graphs<Mint>(maximum), combinations);
    egf = egf.log(maximum + 1);
    return graph_counting_detail::from_egf(std::move(egf), combinations);
}

template <class Mint>
std::vector<Mint> count_labeled_trees(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);

    std::vector<Mint> result(maximum + 1);
    for (int n = 1; n <= maximum; n++) {
        result[n] = (n == 1 ? Mint(1) : Mint(n).pow(n - 2));
    }
    return result;
}

template <class Mint>
std::vector<Mint> count_labeled_forests(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    graph_counting_detail::Fps<Mint> egf =
        graph_counting_detail::to_egf(count_labeled_trees<Mint>(maximum), combinations);
    egf = egf.exp(maximum + 1);
    return graph_counting_detail::from_egf(std::move(egf), combinations);
}

template <class Mint>
std::vector<Mint> count_labeled_unicyclic_connected_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);
    using Fps = graph_counting_detail::Fps<Mint>;

    Fps rooted_tree_egf(maximum + 1);
    for (int n = 1; n <= maximum; n++) {
        rooted_tree_egf[n] =
            Mint(n).pow(n - 1) * combinations.inverse_factorial(n);
    }

    Fps one_minus_rooted(maximum + 1);
    one_minus_rooted[0] = 1;
    for (int i = 1; i <= maximum; i++) {
        one_minus_rooted[i] = Mint(0) - rooted_tree_egf[i];
    }

    Fps egf = one_minus_rooted.log(maximum + 1);
    for (Mint& coefficient : egf) coefficient = Mint(0) - coefficient;
    egf -= rooted_tree_egf;
    egf -= ((rooted_tree_egf * rooted_tree_egf).pre(maximum + 1) *
            graph_counting_detail::inverse_two<Mint>());
    egf *= graph_counting_detail::inverse_two<Mint>();
    return graph_counting_detail::from_egf(std::move(egf), combinations);
}

template <class Mint>
std::vector<Mint> count_labeled_connected_eulerian_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    std::vector<Mint> all_even(maximum + 1);
    all_even[0] = 1;
    if (maximum >= 1) {
        std::vector<Mint> shifted = count_labeled_undirected_graphs<Mint>(maximum - 1);
        for (int n = 1; n <= maximum; n++) all_even[n] = shifted[n - 1];
    }

    graph_counting_detail::Fps<Mint> egf =
        graph_counting_detail::to_egf(std::move(all_even), combinations);
    egf = egf.log(maximum + 1);
    return graph_counting_detail::from_egf(std::move(egf), combinations);
}

template <class Mint>
std::vector<Mint> count_labeled_connected_bipartite_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    graph_counting_detail::Fps<Mint> egf =
        graph_counting_detail::colored_bipartite_egf(maximum, combinations).log(maximum + 1);
    egf *= graph_counting_detail::inverse_two<Mint>();
    return graph_counting_detail::from_egf(std::move(egf), combinations);
}

template <class Mint>
std::vector<Mint> count_labeled_bipartite_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    std::optional<graph_counting_detail::Fps<Mint>> egf =
        graph_counting_detail::colored_bipartite_egf(maximum, combinations).sqrt(maximum + 1);
    assert(egf.has_value());
    return graph_counting_detail::from_egf(std::move(*egf), combinations);
}

template <class Mint>
std::vector<Mint> count_labeled_directed_graphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);

    std::vector<Mint> result(maximum + 1);
    result[0] = 1;
    Mint multiplier = 1;
    const Mint four = 4;
    for (int n = 1; n <= maximum; n++) {
        result[n] = result[n - 1] * multiplier;
        multiplier *= four;
    }
    return result;
}

template <class Mint>
std::vector<Mint> count_labeled_dags(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);
    using Fps = graph_counting_detail::Fps<Mint>;

    Fps denominator(maximum + 1);
    Mint multiplier = 1;
    const Mint half = graph_counting_detail::inverse_two<Mint>();
    denominator[0] = 1;
    for (int n = 1; n <= maximum; n++) {
        denominator[n] = denominator[n - 1] * multiplier;
        multiplier *= half;
    }
    for (int n = 0; n <= maximum; n++) {
        denominator[n] *= combinations.inverse_factorial(n);
        if (n & 1) denominator[n] = Mint(0) - denominator[n];
    }

    Fps egf = denominator.inv(maximum + 1);
    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);
    for (int n = 0; n <= maximum; n++) {
        egf[n] *= combinations.factorial(n) * edge_powers[n];
    }
    return egf;
}

template <class Mint>
std::vector<Mint> count_labeled_strongly_connected_digraphs(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    graph_counting_detail::Fps<Mint> egf(maximum + 1);
    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);
    for (int n = 0; n <= maximum; n++) {
        egf[n] = edge_powers[n] * combinations.inverse_factorial(n);
    }

    egf = egf.inv(maximum + 1);
    for (int n = 0; n <= maximum; n++) egf[n] *= edge_powers[n];
    egf = egf.log(maximum + 1);
    for (int n = 0; n <= maximum; n++) {
        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);
    }
    return egf;
}

template <class Mint>
std::vector<Mint> count_labeled_tournaments(int maximum) {
    return count_labeled_undirected_graphs<Mint>(maximum);
}

template <class Mint>
std::vector<Mint> count_labeled_strongly_connected_tournaments(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    math::Combinatorics<Mint> combinations(maximum);

    graph_counting_detail::Fps<Mint> egf =
        graph_counting_detail::to_egf(count_labeled_tournaments<Mint>(maximum), combinations);
    egf = egf.inv(maximum + 1);
    if (!egf.empty()) egf[0] = 0;
    for (int n = 0; n <= maximum; n++) {
        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);
    }
    return egf;
}

template <class Mint>
std::vector<Mint> count_unlabeled_rooted_trees(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);

    std::vector<Mint> result(maximum + 1);
    if (maximum == 0) return result;

    std::vector<Mint> divisor_sum(maximum + 1);
    result[1] = 1;
    for (int multiple = 1; multiple <= maximum; multiple++) {
        divisor_sum[multiple] += result[1];
    }

    for (int n = 1; n < maximum; n++) {
        Mint sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += divisor_sum[i] * result[n - i + 1];
        }
        result[n + 1] = sum / Mint(n);

        const int size = n + 1;
        const Mint contribution = Mint(size) * result[size];
        for (int multiple = size; multiple <= maximum; multiple += size) {
            divisor_sum[multiple] += contribution;
        }
    }
    return result;
}

template <class Mint>
std::vector<Mint> count_unlabeled_trees(int maximum) {
    graph_counting_detail::assert_maximum<Mint>(maximum);
    using Fps = graph_counting_detail::Fps<Mint>;

    Fps rooted = count_unlabeled_rooted_trees<Mint>(maximum);
    Fps rooted_square = (rooted * rooted).pre(maximum + 1);
    const Mint half = graph_counting_detail::inverse_two<Mint>();

    std::vector<Mint> result(maximum + 1);
    for (int n = 1; n <= maximum; n++) {
        result[n] = rooted[n] - rooted_square[n] * half;
        if ((n & 1) == 0) result[n] += rooted[n / 2] * half;
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_COUNTING_HPP
