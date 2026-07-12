#ifndef M1UNE_MATH_SUBSET_CONVOLUTION_HPP
#define M1UNE_MATH_SUBSET_CONVOLUTION_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace m1une {
namespace math {

template <typename T>
std::vector<T> subset_convolution(
    std::vector<T> first,
    std::vector<T> second
) {
    assert(first.size() == second.size());
    if (first.empty()) return {};
    assert((first.size() & (first.size() - 1)) == 0);

    const std::size_t size = first.size();
    std::size_t bit_count = 0;
    while ((std::size_t(1) << bit_count) < size) ++bit_count;
    const std::size_t rank_count = bit_count + 1;

    std::vector<T> first_ranked(size * rank_count);
    std::vector<T> second_ranked(size * rank_count);
    for (std::size_t mask = 0; mask < size; ++mask) {
        const std::size_t rank = std::popcount(mask);
        first_ranked[mask * rank_count + rank] = std::move(first[mask]);
        second_ranked[mask * rank_count + rank] = std::move(second[mask]);
    }

    for (std::size_t bit = 1; bit < size; bit <<= 1) {
        for (std::size_t mask = 0; mask < size; ++mask) {
            if ((mask & bit) == 0) continue;
            const std::size_t destination = mask * rank_count;
            const std::size_t source = (mask ^ bit) * rank_count;
            for (std::size_t rank = 0; rank < rank_count; ++rank) {
                first_ranked[destination + rank] +=
                    first_ranked[source + rank];
                second_ranked[destination + rank] +=
                    second_ranked[source + rank];
            }
        }
    }

    std::vector<T> product(rank_count);
    for (std::size_t mask = 0; mask < size; ++mask) {
        for (T& value : product) value = T{};
        const std::size_t offset = mask * rank_count;
        const std::size_t rank_limit = std::popcount(mask);
        for (std::size_t left = 0; left <= rank_limit; ++left) {
            const std::size_t right_limit =
                std::min(rank_limit, bit_count - left);
            for (std::size_t right = 0; right <= right_limit; ++right) {
                product[left + right] +=
                    first_ranked[offset + left] *
                    second_ranked[offset + right];
            }
        }
        for (std::size_t rank = 0; rank < rank_count; ++rank) {
            first_ranked[offset + rank] = std::move(product[rank]);
        }
    }

    for (std::size_t bit = 1; bit < size; bit <<= 1) {
        for (std::size_t mask = 0; mask < size; ++mask) {
            if ((mask & bit) == 0) continue;
            const std::size_t destination = mask * rank_count;
            const std::size_t source = (mask ^ bit) * rank_count;
            for (std::size_t rank = 0; rank < rank_count; ++rank) {
                first_ranked[destination + rank] -=
                    first_ranked[source + rank];
            }
        }
    }

    std::vector<T> result(size);
    for (std::size_t mask = 0; mask < size; ++mask) {
        result[mask] = std::move(
            first_ranked[mask * rank_count + std::popcount(mask)]
        );
    }
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_SUBSET_CONVOLUTION_HPP
