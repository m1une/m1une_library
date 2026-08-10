#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"

#pragma GCC optimize("O3")

#include <cassert>
#include <cstdint>
#include <vector>

#include "../../math/modint.hpp"
#include "../../math/multivariate_convolution.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using mint = m1une::math::modint998244353;

std::vector<mint> naive(
    const std::vector<int>& dimensions,
    const std::vector<mint>& first,
    const std::vector<mint>& second
) {
    const int size = int(first.size());
    std::vector<mint> result(size);
    for (int left = 0; left < size; left++) {
        for (int right = 0; right < size; right++) {
            int left_index = left;
            int right_index = right;
            int target = 0;
            int stride = 1;
            bool fits = true;
            for (int dimension : dimensions) {
                const int coordinate =
                    left_index % dimension + right_index % dimension;
                if (coordinate >= dimension) {
                    fits = false;
                    break;
                }
                target += stride * coordinate;
                stride *= dimension;
                left_index /= dimension;
                right_index /= dimension;
            }
            if (fits) result[target] += first[left] * second[right];
        }
    }
    return result;
}

void test_randomized() {
    uint64_t state = 0x123456789abcdefULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; trial++) {
        const int variable_count = int(random() % 4);
        std::vector<int> dimensions(variable_count);
        int size = 1;
        for (int& dimension : dimensions) {
            dimension = 1 + int(random() % 4);
            size *= dimension;
        }
        std::vector<mint> first(size), second(size);
        for (mint& value : first) value = int(random() % 101) - 50;
        for (mint& value : second) value = int(random() % 101) - 50;
        assert(
            m1une::math::multivariate_convolution_truncated(
                dimensions, first, second
            ) == naive(dimensions, first, second)
        );
    }
}

void test_nested_vectors() {
    std::vector<std::vector<mint>> first(3, std::vector<mint>(2));
    std::vector<std::vector<mint>> second(3, std::vector<mint>(2));
    int value = 1;
    for (auto& row : first) {
        for (mint& coefficient : row) coefficient = value++;
    }
    value = 7;
    for (auto& row : second) {
        for (mint& coefficient : row) coefficient = value++;
    }

    std::vector<mint> flattened_first, flattened_second;
    for (const auto& row : first) {
        flattened_first.insert(flattened_first.end(), row.begin(), row.end());
    }
    for (const auto& row : second) {
        flattened_second.insert(flattened_second.end(), row.begin(), row.end());
    }
    std::vector<mint> expected = naive(
        std::vector<int>{2, 3}, flattened_first, flattened_second
    );
    const auto result =
        m1une::math::multivariate_convolution_truncated(first, second);
    int index = 0;
    for (const auto& row : result) {
        for (mint coefficient : row) assert(coefficient == expected[index++]);
    }

    using Cube = std::vector<std::vector<std::vector<mint>>>;
    Cube cube_first(2, std::vector<std::vector<mint>>(2, std::vector<mint>(2)));
    Cube cube_second = cube_first;
    cube_first[0][0][0] = 2;
    cube_first[1][1][1] = 3;
    cube_second[0][0][0] = 5;
    const Cube cube_result =
        m1une::math::multivariate_convolution_truncated(cube_first, cube_second);
    assert(cube_result[0][0][0] == 10);
    assert(cube_result[1][1][1] == 15);
}

}  // namespace

int main() {
    test_randomized();
    test_nested_vectors();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int variable_count = 0;
    input.read(variable_count);
    std::vector<int> dimensions(variable_count);
    input.read(dimensions);
    int size = 1;
    for (int dimension : dimensions) size *= dimension;
    std::vector<mint> first(size), second(size);
    input.read(first);
    input.read(second);
    output.println(
        m1une::math::multivariate_convolution_truncated(
            dimensions, first, second
        )
    );
}
