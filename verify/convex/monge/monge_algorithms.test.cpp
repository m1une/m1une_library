#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

#include "../../../convex/monge/all.hpp"

template <class Value, class Compare>
std::vector<int> brute_row_optima(int rows, int columns, Value value, Compare compare) {
    std::vector<int> result(rows, -1);
    if (columns == 0) return result;
    for (int row = 0; row < rows; row++) {
        result[row] = 0;
        for (int column = 1; column < columns; column++) {
            if (compare(value(row, column), value(row, result[row]))) {
                result[row] = column;
            }
        }
    }
    return result;
}

void test_smawk_monge() {
    for (int rows = 0; rows <= 40; rows++) {
        for (int columns = 0; columns <= 40; columns++) {
            auto value = [&](int row, int column) {
                long long difference = row * 3LL - column * 2LL;
                return difference * difference + row * 7LL + column * 5LL;
            };
            auto expected = brute_row_optima(rows, columns, value, std::less<>());
            assert(m1une::convex::smawk_row_argmin(rows, columns, value) == expected);
        }
    }
}

void test_smawk_totally_monotone_and_ties() {
    for (int rows = 1; rows <= 50; rows++) {
        for (int columns = 1; columns <= 50; columns++) {
            std::vector<int> threshold(rows);
            for (int row = 0; row < rows; row++) {
                threshold[row] = std::min(columns - 1, (row * 7 + rows) / 5);
            }
            auto value = [&](int row, int column) {
                int difference = column - threshold[row];
                return difference * difference;
            };
            auto result = m1une::convex::smawk_row_argmin(rows, columns, value);
            assert(result == threshold);
        }
    }

    auto constant = [](int, int) { return 0; };
    auto result = m1une::convex::smawk_row_argmin(20, 30, constant);
    assert(result == std::vector<int>(20, 0));
}

void test_smawk_max() {
    auto value = [](int row, int column) {
        long long difference = row - column;
        return -difference * difference;
    };
    auto expected = brute_row_optima(30, 25, value, std::greater<>());
    assert(m1une::convex::smawk_row_argmax(30, 25, value) == expected);
}

void test_smawk_matrix_overload_and_evaluations() {
    std::vector<std::vector<long long>> matrix(17, std::vector<long long>(23));
    for (int row = 0; row < 17; row++) {
        for (int column = 0; column < 23; column++) {
            long long difference = row * 2LL - column;
            matrix[row][column] = difference * difference;
        }
    }
    auto expected = brute_row_optima(
        17, 23, [&](int row, int column) { return matrix[row][column]; }, std::less<>());
    assert(m1une::convex::smawk_row_argmin(matrix) == expected);

    for (auto sizes : std::vector<std::pair<int, int>>{
             std::pair<int, int>{10, 1000},
             std::pair<int, int>{1000, 10},
             std::pair<int, int>{700, 900},
         }) {
        int evaluations = 0;
        auto value = [&](int row, int column) {
            evaluations++;
            long long difference = row * 3LL - column * 2LL;
            return difference * difference;
        };
        auto result = m1une::convex::smawk_row_argmin(sizes.first, sizes.second, value);
        assert(int(result.size()) == sizes.first);
        assert(evaluations <= 20 * (sizes.first + sizes.second));
    }
}

void test_monotone_minima() {
    for (int rows = 1; rows <= 40; rows++) {
        for (int columns = 1; columns <= 40; columns++) {
            std::vector<int> optimum(rows);
            for (int row = 0; row < rows; row++) {
                optimum[row] = std::min(columns - 1, row * columns / rows);
            }
            auto value = [&](int row, int column) {
                if (column == optimum[row]) return 0;
                return 1000 + (row * 97 + column * 53) % 101;
            };
            auto result = m1une::convex::monotone_row_argmin(rows, columns, value);
            assert(result == optimum);
        }
    }

    auto empty = m1une::convex::monotone_row_argmin(5, 0, [](int, int) { return 0; });
    assert(empty == std::vector<int>(5, -1));

    std::vector<std::vector<int>> matrix;
    matrix.emplace_back(std::vector<int>{0, 5, 7});
    matrix.emplace_back(std::vector<int>{4, 0, 8});
    matrix.emplace_back(std::vector<int>{9, 3, 0});
    assert(m1une::convex::monotone_row_argmin(matrix) == std::vector<int>({0, 1, 2}));
}

void test_monge_checks() {
    std::vector<std::vector<long long>> matrix(8, std::vector<long long>(11));
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 11; column++) {
            long long difference = row - column;
            matrix[row][column] = difference * difference;
        }
    }
    assert(m1une::convex::is_monge(matrix));
    assert(!m1une::convex::is_anti_monge(matrix));

    for (auto& row : matrix) {
        for (auto& value : row) value = -value;
    }
    assert(!m1une::convex::is_monge(matrix));
    assert(m1une::convex::is_anti_monge(matrix));

    std::vector<std::vector<int>> empty;
    assert(m1une::convex::is_monge(empty));
    assert(m1une::convex::is_anti_monge(empty));
}

template <class T, class Compare>
std::vector<T> brute_convolution(const std::vector<T>& first, const std::vector<T>& second,
                                 Compare compare) {
    if (first.empty() || second.empty()) return {};
    std::vector<T> result(first.size() + second.size() - 1);
    for (int index = 0; index < int(result.size()); index++) {
        int left = std::max(0, index - int(second.size()) + 1);
        int right = std::min(int(first.size()), index + 1);
        result[index] = first[left] + second[index - left];
        for (int i = left + 1; i < right; i++) {
            T value = first[i] + second[index - i];
            if (compare(value, result[index])) result[index] = value;
        }
    }
    return result;
}

template <class T, class Compare>
std::vector<T> brute_convolution_with_infinity(const std::vector<T>& first,
                                               const std::vector<T>& second,
                                               Compare compare,
                                               const T& infinity) {
    if (first.empty() || second.empty()) return {};
    std::vector<T> result(first.size() + second.size() - 1, infinity);
    for (int i = 0; i < int(first.size()); i++) {
        for (int j = 0; j < int(second.size()); j++) {
            if (first[i] == infinity || second[j] == infinity) continue;
            T value = first[i] + second[j];
            if (result[i + j] == infinity || compare(value, result[i + j])) {
                result[i + j] = value;
            }
        }
    }
    return result;
}

void test_structured_convolutions() {
    const long long infinity = 2'000'000'000'000'000'000LL;
    const long long negative_infinity = -infinity;
    for (int first_size = 0; first_size <= 35; first_size++) {
        for (int second_size = 0; second_size <= 35; second_size++) {
            for (int test = 0; test < 8; test++) {
                std::vector<long long> arbitrary(first_size);
                for (int i = 0; i < first_size; i++) {
                    arbitrary[i] = (test * 17 + i * 31 + first_size * 7) % 61 - 30;
                }

                std::vector<long long> convex(second_size);
                long long difference = -10 + test;
                for (int i = 1; i < second_size; i++) {
                    difference += (test * 3 + i * 5) % 4;
                    convex[i] = convex[i - 1] + difference;
                }
                assert(m1une::convex::is_convex_sequence(convex));
                auto expected_min = brute_convolution(arbitrary, convex, std::less<>());
                assert(m1une::convex::min_plus_convolution_convex(arbitrary, convex) ==
                       expected_min);

                std::vector<long long> arbitrary_extended = arbitrary;
                for (int i = 0; i < first_size; i++) {
                    if ((i + test) % 7 == 0) arbitrary_extended[i] = infinity;
                }
                std::vector<long long> convex_extended(second_size + 2, infinity);
                std::copy(convex.begin(), convex.end(), convex_extended.begin() + 1);
                assert(m1une::convex::is_convex_sequence(convex_extended, infinity));
                auto expected_extended_min = brute_convolution_with_infinity(
                    arbitrary_extended, convex_extended, std::less<>(), infinity);
                assert(m1une::convex::min_plus_convolution_convex(
                           arbitrary_extended, convex_extended, infinity) ==
                       expected_extended_min);

                std::vector<long long> first_convex(first_size);
                difference = -12 - test;
                for (int i = 1; i < first_size; i++) {
                    difference += (test * 5 + i * 7) % 5;
                    first_convex[i] = first_convex[i - 1] + difference;
                }
                assert(m1une::convex::is_convex_sequence(first_convex));
                auto expected_convex =
                    brute_convolution(first_convex, convex, std::less<>());
                assert(m1une::convex::min_plus_convolution_convex(first_convex, convex) ==
                       expected_convex);
                assert(m1une::convex::min_plus_convolution_convex(convex, first_convex) ==
                       expected_convex);
                assert(m1une::convex::min_plus_convolution_convex_convex(first_convex,
                                                                        convex) ==
                       expected_convex);
                assert(m1une::convex::min_plus_convolution_convex_convex(convex,
                                                                        first_convex) ==
                       expected_convex);

                std::vector<long long> first_convex_extended(first_size + 2,
                                                              infinity);
                std::copy(first_convex.begin(), first_convex.end(),
                          first_convex_extended.begin() + 1);
                auto expected_extended_convex = brute_convolution_with_infinity(
                    first_convex_extended, convex_extended, std::less<>(), infinity);
                assert(m1une::convex::min_plus_convolution_convex_convex(
                           first_convex_extended, convex_extended, infinity) ==
                       expected_extended_convex);

                std::vector<long long> concave = convex;
                for (auto& value : concave) value = -value;
                assert(m1une::convex::is_concave_sequence(concave));
                auto expected_max = brute_convolution(arbitrary, concave, std::greater<>());
                assert(m1une::convex::max_plus_convolution_concave(arbitrary, concave) ==
                       expected_max);

                std::vector<long long> first_concave = first_convex;
                for (auto& value : first_concave) value = -value;
                assert(m1une::convex::is_concave_sequence(first_concave));
                auto expected_concave =
                    brute_convolution(first_concave, concave, std::greater<>());
                assert(m1une::convex::max_plus_convolution_concave(first_concave, concave) ==
                       expected_concave);
                assert(m1une::convex::max_plus_convolution_concave(concave, first_concave) ==
                       expected_concave);
                assert(m1une::convex::max_plus_convolution_concave_concave(first_concave,
                                                                          concave) ==
                       expected_concave);
                assert(m1une::convex::max_plus_convolution_concave_concave(concave,
                                                                          first_concave) ==
                       expected_concave);

                std::vector<long long> arbitrary_max_extended = arbitrary_extended;
                for (long long& value : arbitrary_max_extended) {
                    value = value == infinity ? negative_infinity : -value;
                }
                std::vector<long long> concave_extended = convex_extended;
                for (long long& value : concave_extended) {
                    value = value == infinity ? negative_infinity : -value;
                }
                auto expected_extended_max = brute_convolution_with_infinity(
                    arbitrary_max_extended, concave_extended, std::greater<>(),
                    negative_infinity);
                assert(m1une::convex::max_plus_convolution_concave(
                           arbitrary_max_extended, concave_extended,
                           negative_infinity) == expected_extended_max);

                std::vector<long long> first_concave_extended =
                    first_convex_extended;
                for (long long& value : first_concave_extended) {
                    value = value == infinity ? negative_infinity : -value;
                }
                auto expected_extended_concave = brute_convolution_with_infinity(
                    first_concave_extended, concave_extended, std::greater<>(),
                    negative_infinity);
                assert(m1une::convex::max_plus_convolution_concave_concave(
                           first_concave_extended, concave_extended,
                           negative_infinity) == expected_extended_concave);
            }
        }
    }

    assert(!m1une::convex::is_convex_sequence(std::vector<int>{0, 2, 1}));
    assert(!m1une::convex::is_concave_sequence(std::vector<int>{0, -2, -1}));
    assert(!m1une::convex::is_convex_sequence(
        std::vector<long long>{1, infinity, infinity}));
    assert(m1une::convex::is_convex_sequence(
        std::vector<long long>{1, infinity, infinity}, infinity));
    assert(m1une::convex::is_convex_sequence(
        std::vector<long long>{infinity, 0, 1, 4, infinity}, infinity));
    assert(!m1une::convex::is_convex_sequence(
        std::vector<long long>{0, infinity, 1}, infinity));

    std::vector<long long> arbitrary = {infinity, 3, infinity, -2};
    std::vector<long long> convex = {infinity, 0, 1, 4, infinity, infinity};
    auto expected_min =
        brute_convolution_with_infinity(arbitrary, convex, std::less<>(), infinity);
    assert(m1une::convex::min_plus_convolution_convex(arbitrary, convex, infinity) ==
           expected_min);

    std::vector<long long> first_convex = {infinity, 2, 2, 3, infinity};
    expected_min = brute_convolution_with_infinity(first_convex, convex,
                                                   std::less<>(), infinity);
    assert(m1une::convex::min_plus_convolution_convex_convex(
               first_convex, convex, infinity) == expected_min);

    long long unordered_infinity = 7;
    std::vector<long long> large_arbitrary = {10, 20};
    std::vector<long long> small_convex = {0, 1};
    assert(m1une::convex::min_plus_convolution_convex(
               large_arbitrary, small_convex, unordered_infinity) ==
           std::vector<long long>({10, 11, 21}));

    std::vector<long long> arbitrary_max = {negative_infinity, 3,
                                             negative_infinity, -2};
    std::vector<long long> concave = {negative_infinity, 0, -1, -4,
                                      negative_infinity};
    assert(m1une::convex::is_concave_sequence(concave, negative_infinity));
    auto expected_max = brute_convolution_with_infinity(
        arbitrary_max, concave, std::greater<>(), negative_infinity);
    assert(m1une::convex::max_plus_convolution_concave(
               arbitrary_max, concave, negative_infinity) == expected_max);

    std::vector<long long> first_concave = {negative_infinity, 2, 2, 1,
                                            negative_infinity};
    expected_max = brute_convolution_with_infinity(
        first_concave, concave, std::greater<>(), negative_infinity);
    assert(m1une::convex::max_plus_convolution_concave_concave(
               first_concave, concave, negative_infinity) == expected_max);

    std::vector<long long> all_infinity(3, infinity);
    assert(m1une::convex::is_convex_sequence(all_infinity, infinity));
    assert(m1une::convex::min_plus_convolution_convex_convex(
               all_infinity, convex, infinity) ==
           std::vector<long long>(all_infinity.size() + convex.size() - 1,
                                  infinity));
}

int main() {
    test_smawk_monge();
    test_smawk_totally_monotone_and_ties();
    test_smawk_max();
    test_smawk_matrix_overload_and_evaluations();
    test_monotone_minima();
    test_monge_checks();
    test_structured_convolutions();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
