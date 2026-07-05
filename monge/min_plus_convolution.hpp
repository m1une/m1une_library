#ifndef M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
#define M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP 1

#include <functional>
#include <vector>

#include "smawk.hpp"

namespace m1une {
namespace monge {

namespace convolution_detail {

template <class T, class Compare>
std::vector<T> structured_convolution(const std::vector<T>& arbitrary,
                                      const std::vector<T>& structured,
                                      Compare compare) {
    if (arbitrary.empty() || structured.empty()) return {};

    int first_size = int(arbitrary.size());
    int second_size = int(structured.size());
    int result_size = first_size + second_size - 1;
    auto select = [&](int index, int current, int candidate) {
        if (index < candidate) return false;
        if (index - current >= second_size) return true;
        T current_value = arbitrary[current] + structured[index - current];
        T candidate_value = arbitrary[candidate] + structured[index - candidate];
        return !compare(current_value, candidate_value);
    };

    std::vector<int> optima =
        smawk_detail::row_optima(result_size, first_size, select);
    std::vector<T> result;
    result.reserve(result_size);
    for (int index = 0; index < result_size; index++) {
        int first_index = optima[index];
        result.emplace_back(arbitrary[first_index] + structured[index - first_index]);
    }
    return result;
}

}  // namespace convolution_detail

template <class T>
bool is_convex_sequence(const std::vector<T>& sequence) {
    for (int i = 1; i + 1 < int(sequence.size()); i++) {
        if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence) {
    for (int i = 1; i + 1 < int(sequence.size()); i++) {
        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,
                                           const std::vector<T>& convex) {
    return convolution_detail::structured_convolution(arbitrary, convex, std::less<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave(const std::vector<T>& arbitrary,
                                            const std::vector<T>& concave) {
    return convolution_detail::structured_convolution(arbitrary, concave, std::greater<>());
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
