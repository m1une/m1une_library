#ifndef M1UNE_GRAPH_CHROMATIC_NUMBER_HPP
#define M1UNE_GRAPH_CHROMATIC_NUMBER_HPP 1

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

namespace detail {

struct ChromaticResidues {
    static constexpr std::array<std::uint32_t, 14> mod = {
        1000000007, 1000000009, 998244353, 985661441, 943718401, 935329793, 918552577,
        897581057,  880803841,  754974721, 645922817, 595591169, 469762049, 167772161,
    };

    std::array<std::uint32_t, 14> value;

    explicit ChromaticResidues(std::uint32_t x = 0) {
        value.fill(x);
    }

    void multiply(std::uint32_t x) {
        for (int i = 0; i < int(mod.size()); i++) {
            value[i] = std::uint32_t(std::uint64_t(value[i]) * x % mod[i]);
        }
    }
};

}  // namespace detail

template <class T>
int chromatic_number(const Graph<T>& g) {
    int n = g.size();
    assert(n <= 20);
    if (n == 0) return 0;

    std::vector<std::uint32_t> adjacent(n, 0);
    for (const auto& e : g.edges()) {
        if (e.from == e.to) continue;
        adjacent[e.from] |= std::uint32_t(1) << e.to;
        adjacent[e.to] |= std::uint32_t(1) << e.from;
    }

    std::uint32_t subset_count = std::uint32_t(1) << n;
    std::vector<std::uint32_t> independent_count(subset_count, 0);
    independent_count[0] = 1;
    for (std::uint32_t mask = 1; mask < subset_count; mask++) {
        int v = std::countr_zero(mask);
        std::uint32_t rest = mask ^ (std::uint32_t(1) << v);
        independent_count[mask] =
            independent_count[rest] + independent_count[rest & ~adjacent[v]];
    }

    std::vector<detail::ChromaticResidues> power(subset_count, detail::ChromaticResidues(1));
    for (int colors = 1; colors <= n; colors++) {
        std::array<std::uint32_t, 14> sum = {};
        for (std::uint32_t mask = 0; mask < subset_count; mask++) {
            power[mask].multiply(independent_count[mask]);
            bool positive = ((n - std::popcount(mask)) & 1) == 0;
            for (int i = 0; i < int(sum.size()); i++) {
                std::uint32_t x = power[mask].value[i];
                if (positive) {
                    sum[i] += x;
                    if (sum[i] >= detail::ChromaticResidues::mod[i]) {
                        sum[i] -= detail::ChromaticResidues::mod[i];
                    }
                } else {
                    sum[i] = (sum[i] >= x ? sum[i] - x
                                          : sum[i] + detail::ChromaticResidues::mod[i] - x);
                }
            }
        }
        for (std::uint32_t x : sum) {
            if (x != 0) return colors;
        }
    }
    return n;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_CHROMATIC_NUMBER_HPP
