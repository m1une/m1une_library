#ifndef M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
#define M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP 1

#include <functional>
#include <utility>
#include <vector>

#include "smawk.hpp"

namespace m1une {
namespace monge {

namespace convolution_detail {

template <class T, class Compare, class Add>
std::vector<T> structured_convolution(const std::vector<T>& arbitrary,
                                      const std::vector<T>& structured,
                                      Compare compare, Add add) {
    if (arbitrary.empty() || structured.empty()) return {};

    int first_size = int(arbitrary.size());
    int second_size = int(structured.size());
    int result_size = first_size + second_size - 1;
    auto select = [&](int index, int current, int candidate) {
        if (index < candidate) return false;
        if (index - current >= second_size) return true;
        T current_value = add(arbitrary[current], structured[index - current]);
        T candidate_value = add(arbitrary[candidate], structured[index - candidate]);
        return !compare(current_value, candidate_value);
    };

    std::vector<int> optima =
        smawk_detail::row_optima(result_size, first_size, select);
    std::vector<T> result;
    result.reserve(result_size);
    for (int index = 0; index < result_size; index++) {
        int first_index = optima[index];
        result.emplace_back(add(arbitrary[first_index],
                                structured[index - first_index]));
    }
    return result;
}

template <class T>
std::pair<int, int> finite_interval(const std::vector<T>& sequence,
                                    const T& infinity) {
    int left = 0;
    while (left < int(sequence.size()) && sequence[left] == infinity) left++;
    int right = int(sequence.size());
    while (right > left && sequence[right - 1] == infinity) right--;
    return {left, right};
}

template <class T, class Compare>
std::vector<T> structured_convolution_with_infinity(
    const std::vector<T>& arbitrary, const std::vector<T>& structured,
    const T& infinity, Compare compare) {
    if (arbitrary.empty() || structured.empty()) return {};

    auto [left, right] = finite_interval(structured, infinity);
    int result_size = int(arbitrary.size() + structured.size() - 1);
    std::vector<T> result(result_size, infinity);
    if (left == right) return result;

    std::vector<int> columns;
    columns.reserve(arbitrary.size());
    for (int i = 0; i < int(arbitrary.size()); i++) {
        if (arbitrary[i] != infinity) columns.push_back(i);
    }
    if (columns.empty()) return result;

    int finite_size = right - left;
    int middle_size = int(arbitrary.size()) + finite_size - 1;
    std::vector<int> rows;
    rows.reserve(middle_size);
    int active = 0;
    for (int row = 0; row < middle_size; row++) {
        if (row < int(arbitrary.size()) && arbitrary[row] != infinity) active++;
        if (row >= finite_size && arbitrary[row - finite_size] != infinity) active--;
        if (active > 0) rows.push_back(row);
    }

    auto select = [&](int index, int current, int candidate) {
        if (index < candidate) return false;
        if (index - current >= finite_size) return true;
        T current_value =
            arbitrary[current] + structured[left + index - current];
        T candidate_value =
            arbitrary[candidate] + structured[left + index - candidate];
        return !compare(current_value, candidate_value);
    };
    std::vector<int> optima(middle_size, -1);
    smawk_detail::solve(rows, columns, select, optima);
    for (int row : rows) {
        int first_index = optima[row];
        result[left + row] =
            arbitrary[first_index] + structured[left + row - first_index];
    }
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

template <class T, class Compare>
std::vector<T> linear_structured_convolution_with_infinity(
    const std::vector<T>& first, const std::vector<T>& second,
    const T& infinity, Compare compare) {
    if (first.empty() || second.empty()) return {};

    auto [first_left, first_right] = finite_interval(first, infinity);
    auto [second_left, second_right] = finite_interval(second, infinity);
    int result_size = int(first.size() + second.size() - 1);
    std::vector<T> result(result_size, infinity);
    if (first_left == first_right || second_left == second_right) return result;

    int offset = first_left + second_left;
    result[offset] = first[first_left] + second[second_left];

    int first_index = first_left + 1;
    int second_index = second_left + 1;
    int result_index = offset + 1;
    while (first_index < first_right && second_index < second_right) {
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
    while (first_index < first_right) {
        T difference = first[first_index] - first[first_index - 1];
        result[result_index] = result[result_index - 1] + difference;
        first_index++;
        result_index++;
    }
    while (second_index < second_right) {
        T difference = second[second_index] - second[second_index - 1];
        result[result_index] = result[result_index - 1] + difference;
        second_index++;
        result_index++;
    }
    return result;
}

template <class T, class Compare>
bool is_structured_sequence_with_infinity(const std::vector<T>& sequence,
                                          const T& infinity, Compare violation) {
    auto [left, right] = finite_interval(sequence, infinity);
    for (int i = left; i < right; i++) {
        if (sequence[i] == infinity) return false;
    }
    for (int i = left + 1; i + 1 < right; i++) {
        T first_difference = sequence[i] - sequence[i - 1];
        T second_difference = sequence[i + 1] - sequence[i];
        if (violation(first_difference, second_difference)) return false;
    }
    return true;
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
bool is_convex_sequence(const std::vector<T>& sequence, const T& infinity) {
    return convolution_detail::is_structured_sequence_with_infinity(
        sequence, infinity, std::greater<>());
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
bool is_concave_sequence(const std::vector<T>& sequence,
                         const T& negative_infinity) {
    return convolution_detail::is_structured_sequence_with_infinity(
        sequence, negative_infinity, std::less<>());
}

template <class T>
std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,
                                           const std::vector<T>& convex) {
    auto add = [](const T& first, const T& second) { return first + second; };
    return convolution_detail::structured_convolution(arbitrary, convex,
                                                      std::less<>(), add);
}

template <class T>
std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,
                                           const std::vector<T>& convex,
                                           const T& infinity) {
    return convolution_detail::structured_convolution_with_infinity(
        arbitrary, convex, infinity, std::less<>());
}

template <class T>
std::vector<T> min_plus_convolution_convex_convex(const std::vector<T>& first,
                                                  const std::vector<T>& second) {
    return convolution_detail::linear_structured_convolution(first, second, std::less<>());
}

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first, const std::vector<T>& second,
    const T& infinity) {
    return convolution_detail::linear_structured_convolution_with_infinity(
        first, second, infinity, std::less<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave(const std::vector<T>& arbitrary,
                                            const std::vector<T>& concave) {
    auto add = [](const T& first, const T& second) { return first + second; };
    return convolution_detail::structured_convolution(arbitrary, concave,
                                                      std::greater<>(), add);
}

template <class T>
std::vector<T> max_plus_convolution_concave(const std::vector<T>& arbitrary,
                                            const std::vector<T>& concave,
                                            const T& negative_infinity) {
    return convolution_detail::structured_convolution_with_infinity(
        arbitrary, concave, negative_infinity, std::greater<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave_concave(const std::vector<T>& first,
                                                    const std::vector<T>& second) {
    return convolution_detail::linear_structured_convolution(first, second, std::greater<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave_concave(
    const std::vector<T>& first, const std::vector<T>& second,
    const T& negative_infinity) {
    return convolution_detail::linear_structured_convolution_with_infinity(
        first, second, negative_infinity, std::greater<>());
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
