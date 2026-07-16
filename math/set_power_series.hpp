#ifndef M1UNE_MATH_SET_POWER_SERIES_HPP
#define M1UNE_MATH_SET_POWER_SERIES_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

#include "subset_convolution.hpp"

namespace m1une {
namespace math {

namespace set_power_series_detail {

inline bool is_power_of_two(std::size_t size) {
    return size != 0 && (size & (size - 1)) == 0;
}

template <class T>
std::vector<T> divide(
    const std::vector<T>& numerator,
    const std::vector<T>& denominator
) {
    assert(numerator.size() == denominator.size());
    assert(is_power_of_two(numerator.size()));
    assert(denominator[0] != T{});

    const std::size_t size = numerator.size();
    const int bit_count = std::countr_zero(size);
    const std::size_t rank_count = std::size_t(bit_count) + 1;
    std::vector<T> denominator_ranked(size * rank_count);
    std::vector<T> quotient_ranked(size * rank_count);

    for (std::size_t mask = 0; mask < size; mask++) {
        std::size_t rank = std::popcount(mask);
        denominator_ranked[mask * rank_count + rank] = denominator[mask];
    }
    for (std::size_t bit = 1; bit < size; bit <<= 1) {
        for (std::size_t mask = 0; mask < size; mask++) {
            if ((mask & bit) == 0) continue;
            std::size_t source_mask = mask ^ bit;
            std::size_t source = source_mask * rank_count;
            std::size_t destination = mask * rank_count;
            std::size_t rank_limit = std::popcount(source_mask);
            for (std::size_t rank = 0; rank <= rank_limit; rank++) {
                denominator_ranked[destination + rank] +=
                    denominator_ranked[source + rank];
            }
        }
    }

    const T inverse_constant = T(1) / denominator[0];
    std::vector<T> transformed_product(size);
    std::vector<T> quotient(size);
    for (int rank = 0; rank <= bit_count; rank++) {
        std::fill(
            transformed_product.begin(),
            transformed_product.end(),
            T{}
        );
        for (std::size_t mask = 0; mask < size; mask++) {
            std::size_t offset = mask * rank_count;
            for (int left_rank = 0; left_rank <= rank; left_rank++) {
                transformed_product[mask] +=
                    denominator_ranked[offset + left_rank] *
                    quotient_ranked[offset + rank - left_rank];
            }
        }

        for (std::size_t bit = 1; bit < size; bit <<= 1) {
            for (std::size_t mask = 0; mask < size; mask++) {
                if (mask & bit) {
                    transformed_product[mask] -=
                        transformed_product[mask ^ bit];
                }
            }
        }

        for (std::size_t mask = 0; mask < size; mask++) {
            if (int(std::popcount(mask)) != rank) continue;
            quotient[mask] =
                (numerator[mask] - transformed_product[mask]) *
                inverse_constant;
            quotient_ranked[mask * rank_count + rank] = quotient[mask];
        }

        for (std::size_t bit = 1; bit < size; bit <<= 1) {
            for (std::size_t mask = 0; mask < size; mask++) {
                if (mask & bit) {
                    quotient_ranked[mask * rank_count + rank] +=
                        quotient_ranked[(mask ^ bit) * rank_count + rank];
                }
            }
        }
    }
    return quotient;
}

template <class T>
std::vector<T> normalized_power(std::vector<T> series, T exponent) {
    assert(is_power_of_two(series.size()));
    assert(series[0] == T(1));
    std::vector<T> logarithm(series.size());
    logarithm[0] = T{};
    for (std::size_t half = 1; half < series.size(); half <<= 1) {
        std::vector<T> low(series.begin(), series.begin() + half);
        std::vector<T> high(
            series.begin() + half,
            series.begin() + 2 * half
        );
        std::vector<T> next = divide(high, low);
        std::move(next.begin(), next.end(), logarithm.begin() + half);
    }
    for (T& value : logarithm) value *= exponent;

    std::vector<T> result(1, T(1));
    result.reserve(series.size());
    for (std::size_t half = 1; half < series.size(); half <<= 1) {
        std::vector<T> high(
            logarithm.begin() + half,
            logarithm.begin() + 2 * half
        );
        std::vector<T> next = subset_convolution(std::move(high), result);
        result.insert(
            result.end(),
            std::make_move_iterator(next.begin()),
            std::make_move_iterator(next.end())
        );
    }
    return result;
}

}  // namespace set_power_series_detail

// Returns numerator / denominator under subset convolution.
template <class T>
std::vector<T> set_power_series_divide(
    const std::vector<T>& numerator,
    const std::vector<T>& denominator
) {
    return set_power_series_detail::divide(numerator, denominator);
}

template <class T>
std::vector<T> set_power_series_inverse(const std::vector<T>& series) {
    assert(set_power_series_detail::is_power_of_two(series.size()));
    std::vector<T> identity(series.size());
    identity[0] = T(1);
    return set_power_series_divide(identity, series);
}

template <class T>
std::vector<T> set_power_series_exp(const std::vector<T>& series) {
    assert(set_power_series_detail::is_power_of_two(series.size()));
    assert(series[0] == T{});
    std::vector<T> result(1, T(1));
    result.reserve(series.size());
    for (std::size_t half = 1; half < series.size(); half <<= 1) {
        std::vector<T> high(
            series.begin() + half,
            series.begin() + 2 * half
        );
        std::vector<T> next = subset_convolution(std::move(high), result);
        result.insert(
            result.end(),
            std::make_move_iterator(next.begin()),
            std::make_move_iterator(next.end())
        );
    }
    return result;
}

template <class T>
std::vector<T> set_power_series_log(const std::vector<T>& series) {
    assert(set_power_series_detail::is_power_of_two(series.size()));
    assert(series[0] == T(1));
    std::vector<T> result(series.size());
    for (std::size_t half = 1; half < series.size(); half <<= 1) {
        std::vector<T> low(series.begin(), series.begin() + half);
        std::vector<T> high(
            series.begin() + half,
            series.begin() + 2 * half
        );
        std::vector<T> next = set_power_series_divide(high, low);
        std::move(next.begin(), next.end(), result.begin() + half);
    }
    return result;
}

template <class T>
std::vector<T> set_power_series_pow(
    const std::vector<T>& series,
    long long exponent
) {
    return set_power_series_detail::normalized_power(
        series,
        T(exponent)
    );
}

template <class T>
std::vector<T> set_power_series_sqrt(const std::vector<T>& series) {
    return set_power_series_detail::normalized_power(
        series,
        T(1) / T(2)
    );
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_SET_POWER_SERIES_HPP
