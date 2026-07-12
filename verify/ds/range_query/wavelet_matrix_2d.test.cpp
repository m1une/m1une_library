#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../../ds/range_query/wavelet_matrix_2d.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

namespace {

using Matrix = m1une::ds::WaveletMatrix2D<int, int>;

#ifndef NDEBUG
void randomized_test() {
    Matrix empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.count(0, 0, -10, 10, -10, 10) == 0);

    std::uint64_t state = 20260713;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 80; trial++) {
        int n = int(random() % 40);
        std::vector<Matrix::value_type> values;
        std::vector<int> first;
        std::vector<int> second;
        values.reserve(n);
        first.reserve(n);
        second.reserve(n);
        for (int i = 0; i < n; i++) {
            int x = int(random() % 21) - 10;
            int y = int(random() % 21) - 10;
            values.emplace_back(x, y);
            first.push_back(x);
            second.push_back(y);
        }

        Matrix matrix(values);
        Matrix parallel(first, second);
        assert(matrix.size() == n);
        assert(matrix.empty() == (n == 0));
        for (int i = 0; i < n; i++) {
            assert(matrix[i] == values[i]);
            assert(parallel.access(i) == values[i]);
        }

        for (int query = 0; query < 150; query++) {
            int l = int(random() % std::uint64_t(n + 1));
            int r = int(random() % std::uint64_t(n + 1));
            if (r < l) std::swap(l, r);
            int first_lower = int(random() % 31) - 15;
            int first_upper = int(random() % 31) - 15;
            int second_lower = int(random() % 31) - 15;
            int second_upper = int(random() % 31) - 15;
            if (first_upper < first_lower) {
                std::swap(first_lower, first_upper);
            }
            if (second_upper < second_lower) {
                std::swap(second_lower, second_upper);
            }

            int expected_count = 0;
            std::vector<int> selected;
            for (int i = l; i < r; i++) {
                if (first_lower <= values[i].first &&
                    values[i].first < first_upper) {
                    selected.push_back(values[i].second);
                    if (second_lower <= values[i].second &&
                        values[i].second < second_upper) {
                        expected_count++;
                    }
                }
            }
            std::sort(selected.begin(), selected.end());

            assert(
                matrix.count(
                    l,
                    r,
                    first_lower,
                    first_upper,
                    second_lower,
                    second_upper
                ) == expected_count
            );
            assert(
                parallel.count(
                    l,
                    r,
                    first_lower,
                    first_upper,
                    second_lower,
                    second_upper
                ) == expected_count
            );
            for (int k = 0; k < int(selected.size()); k++) {
                assert(
                    matrix.quantile(
                        l,
                        r,
                        first_lower,
                        first_upper,
                        k
                    ) == selected[k]
                );
            }
        }
    }

    std::vector<Matrix::value_type> equal_values(20, Matrix::value_type(4, 7));
    Matrix equal_matrix(equal_values);
    assert(equal_matrix.count(3, 18, 4, 5, 7, 8) == 15);
    assert(equal_matrix.quantile(3, 18, 4, 5, 14) == 7);
}
#endif

}  // namespace

int main() {
#ifndef NDEBUG
    randomized_test();
#endif

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, query_count;
    std::cin >> n >> query_count;
    std::vector<std::pair<int, long long>> values(n);
    for (auto& value : values) {
        value.first = 0;
        std::cin >> value.second;
    }

    m1une::ds::WaveletMatrix2D<int, long long> matrix(values);
    while (query_count--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << matrix.quantile(l, r, 0, 1, k) << '\n';
    }
}
