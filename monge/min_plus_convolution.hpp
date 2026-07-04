#ifndef M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
#define M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP 1

#include <functional>
#include <vector>

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
    std::vector<T> result(result_size);

    auto solve = [&](auto self, int result_left, int result_right, int candidate_left,
                     int candidate_right) -> void {
        if (result_left == result_right) return;
        int index = (result_left + result_right) / 2;
        int left = candidate_left > index - second_size + 1 ? candidate_left
                                                            : index - second_size + 1;
        int right = candidate_right < index + 1 ? candidate_right : index + 1;

        int best = left;
        T best_value = arbitrary[best] + structured[index - best];
        for (int candidate = left + 1; candidate < right; candidate++) {
            T current = arbitrary[candidate] + structured[index - candidate];
            if (compare(current, best_value)) {
                best = candidate;
                best_value = current;
            }
        }
        result[index] = best_value;
        self(self, result_left, index, candidate_left, best + 1);
        self(self, index + 1, result_right, best, candidate_right);
    };

    solve(solve, 0, result_size, 0, first_size);
    return result;
}

template <class T, class Compare>
std::vector<T> linear_structured_convolution(const std::vector<T>& first,
                                             const std::vector<T>& second,
                                             Compare compare) {
    if (first.empty() || second.empty()) return {};

    int first_size = int(first.size());
    int second_size = int(second.size());
    std::vector<T> result(first_size + second_size - 1);
    result[0] = first[0] + second[0];

    int first_index = 1;
    int second_index = 1;
    int result_index = 1;
    while (first_index < first_size && second_index < second_size) {
        T first_difference = first[first_index] - first[first_index - 1];
        T second_difference = second[second_index] - second[second_index - 1];
        if (compare(second_difference, first_difference)) {
            result[result_index] = result[result_index - 1] + second_difference;
            second_index++;
        } else {
            result[result_index] = result[result_index - 1] + first_difference;
            first_index++;
        }
        result_index++;
    }
    while (first_index < first_size) {
        T difference = first[first_index] - first[first_index - 1];
        result[result_index] = result[result_index - 1] + difference;
        first_index++;
        result_index++;
    }
    while (second_index < second_size) {
        T difference = second[second_index] - second[second_index - 1];
        result[result_index] = result[result_index - 1] + difference;
        second_index++;
        result_index++;
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
std::vector<T> min_plus_convolution_convex_convex(const std::vector<T>& first,
                                                  const std::vector<T>& second) {
    return convolution_detail::linear_structured_convolution(first, second, std::less<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave(const std::vector<T>& arbitrary,
                                            const std::vector<T>& concave) {
    return convolution_detail::structured_convolution(arbitrary, concave, std::greater<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave_concave(const std::vector<T>& first,
                                                    const std::vector<T>& second) {
    return convolution_detail::linear_structured_convolution(first, second, std::greater<>());
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
