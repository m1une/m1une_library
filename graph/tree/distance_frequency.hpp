#ifndef M1UNE_TREE_DISTANCE_FREQUENCY_HPP
#define M1UNE_TREE_DISTANCE_FREQUENCY_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "../../math/fps/convolution.hpp"
#include "../../math/modint.hpp"
#include "centroid_decomposition.hpp"

namespace m1une {
namespace tree {

namespace distance_frequency_detail {

template <class Mint, class T>
std::vector<Mint> count_ordered_pairs(
    const m1une::graph::Graph<T>& tree,
    const CentroidDecomposition<T>& decomposition
) {
    const int size = tree.size();
    std::vector<Mint> count(static_cast<std::size_t>(size));
    std::vector<char> removed(std::size_t(size), false);
    std::vector<Mint> histogram;
    std::vector<std::pair<int, int>> stack;
    std::vector<int> parent(std::size_t(size), -1);

    for (int centroid : decomposition.order) {
        std::vector<Mint> total(1, Mint(1));
        for (const auto& edge : tree[centroid]) {
            if (!edge.alive || removed[std::size_t(edge.to)]) continue;

            histogram.clear();
            stack.clear();
            stack.emplace_back(edge.to, 1);
            parent[std::size_t(edge.to)] = centroid;
            while (!stack.empty()) {
                const auto [vertex, distance] = stack.back();
                stack.pop_back();
                if (int(histogram.size()) <= distance) {
                    histogram.resize(std::size_t(distance + 1));
                }
                histogram[std::size_t(distance)] += Mint(1);

                for (const auto& next : tree[vertex]) {
                    if (!next.alive || removed[std::size_t(next.to)]) continue;
                    if (next.to == parent[std::size_t(vertex)]) continue;
                    parent[std::size_t(next.to)] = vertex;
                    stack.emplace_back(next.to, distance + 1);
                }
            }

            if (total.size() < histogram.size()) {
                total.resize(histogram.size());
            }
            for (std::size_t distance = 0; distance < histogram.size(); distance++) {
                total[distance] += histogram[distance];
            }

            const std::vector<Mint> within_component =
                m1une::fps::convolution(histogram, histogram);
            const std::size_t limit = std::min(count.size(), within_component.size());
            for (std::size_t distance = 0; distance < limit; distance++) {
                count[distance] -= within_component[distance];
            }
        }

        const std::vector<Mint> through_centroid =
            m1une::fps::convolution(total, total);
        const std::size_t limit = std::min(count.size(), through_centroid.size());
        for (std::size_t distance = 0; distance < limit; distance++) {
            count[distance] += through_centroid[distance];
        }
        removed[std::size_t(centroid)] = true;
    }
    return count;
}

inline std::uint64_t combine_residues(std::uint32_t first, std::uint32_t second) {
    using First = m1une::math::ModInt<998244353>;
    using Second = m1une::math::ModInt<924844033>;
    static const std::uint64_t inverse = Second(First::mod()).inv().val();
    const std::uint64_t offset =
        (std::uint64_t(second) + Second::mod() - first % Second::mod()) %
        Second::mod();
    const std::uint64_t multiplier = offset * inverse % Second::mod();
    return std::uint64_t(first) + std::uint64_t(First::mod()) * multiplier;
}

}  // namespace distance_frequency_detail

template <class T>
std::vector<long long> tree_distance_frequency(
    const m1une::graph::Graph<T>& tree
) {
    const int size = tree.size();
    assert(tree.edge_count() == std::max(0, size - 1));
    if (size == 0) return {};

    const CentroidDecomposition<T> decomposition(tree);
    assert(decomposition.roots.size() == 1);

    using First = m1une::math::ModInt<998244353>;
    using Second = m1une::math::ModInt<924844033>;
    assert(
        std::uint64_t(size) * std::uint64_t(size - 1) <
        std::uint64_t(First::mod()) * Second::mod()
    );
    const std::vector<First> first =
        distance_frequency_detail::count_ordered_pairs<First>(
            tree,
            decomposition
        );
    const std::vector<Second> second =
        distance_frequency_detail::count_ordered_pairs<Second>(
            tree,
            decomposition
        );

    std::vector<long long> result(static_cast<std::size_t>(size));
    result[0] = size;
    for (int distance = 1; distance < size; distance++) {
        const std::uint64_t ordered =
            distance_frequency_detail::combine_residues(
                first[std::size_t(distance)].val(),
                second[std::size_t(distance)].val()
            );
        assert((ordered & 1) == 0);
        result[std::size_t(distance)] = static_cast<long long>(ordered / 2);
    }
    return result;
}

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_DISTANCE_FREQUENCY_HPP
