#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution_cyclic"

#pragma GCC optimize("O3")

#include <cassert>
#include <cstdint>
#include <vector>

#include "../../math/modint.hpp"
#include "../../math/multivariate_convolution.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using mint = m1une::math::DynamicModInt<0>;

template <class Mint>
std::vector<Mint> naive(
    const std::vector<int>& dimensions,
    const std::vector<Mint>& first,
    const std::vector<Mint>& second
) {
    const int size = int(first.size());
    std::vector<Mint> result(size);
    for (int left = 0; left < size; left++) {
        for (int right = 0; right < size; right++) {
            int left_index = left;
            int right_index = right;
            int target = 0;
            int stride = 1;
            for (int dimension : dimensions) {
                const int coordinate =
                    (left_index % dimension + right_index % dimension) % dimension;
                target += stride * coordinate;
                stride *= dimension;
                left_index /= dimension;
                right_index /= dimension;
            }
            result[target] += first[left] * second[right];
        }
    }
    return result;
}

template <class Mint>
void test_fixed_mod_randomized(uint64_t seed) {
    uint64_t state = seed;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    const int dimensions_to_test[] = {1, 2, 3, 4, 5, 7, 8};
    for (int trial = 0; trial < 120; trial++) {
        const int variable_count = int(random() % 5);
        std::vector<int> dimensions(variable_count);
        int size = 1;
        for (int& dimension : dimensions) {
            dimension = dimensions_to_test[random() % 7];
            size *= dimension;
        }
        if (size > 140) {
            trial--;
            continue;
        }
        std::vector<Mint> first(size), second(size);
        for (Mint& value : first) value = random() % Mint::mod();
        for (Mint& value : second) value = random() % Mint::mod();
        assert(
            m1une::math::multivariate_convolution_cyclic(
                dimensions, first, second
            ) == naive(dimensions, first, second)
        );
    }
}

void test_randomized() {
    mint::set_mod(97);
    uint64_t state = 0xfedcba987654321ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    const int dimensions_to_test[] = {1, 2, 3, 4, 5, 6, 7, 8};

    for (int trial = 0; trial < 300; trial++) {
        const int variable_count = int(random() % 4);
        std::vector<int> dimensions(variable_count);
        int size = 1;
        for (int& dimension : dimensions) {
            dimension = dimensions_to_test[random() % 8];
            size *= dimension;
        }
        if (size > 200) {
            trial--;
            continue;
        }
        std::vector<mint> first(size), second(size);
        for (mint& value : first) value = random() % mint::mod();
        for (mint& value : second) value = random() % mint::mod();
        assert(
            m1une::math::multivariate_convolution_cyclic(
                dimensions, first, second
            ) == naive(dimensions, first, second)
        );
    }

    std::vector<int> dimensions = {96};
    std::vector<mint> first(96), second(96);
    for (mint& value : first) value = random() % mint::mod();
    for (mint& value : second) value = random() % mint::mod();
    assert(
        m1une::math::multivariate_convolution_cyclic(
            dimensions, first, second
        ) == naive(dimensions, first, second)
    );

    dimensions = {1, 5, 1, 7};
    first.assign(35, mint(0));
    second.assign(35, mint(0));
    for (mint& value : first) value = random() % mint::mod();
    for (mint& value : second) value = random() % mint::mod();
    assert(
        m1une::math::multivariate_convolution_cyclic(
            dimensions, first, second
        ) == naive(dimensions, first, second)
    );
}

void test_nested_vectors() {
    mint::set_mod(97);
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
    const auto result = m1une::math::multivariate_convolution_cyclic(first, second);
    int index = 0;
    for (const auto& row : result) {
        for (mint coefficient : row) assert(coefficient == expected[index++]);
    }

    // Dimension 5 does not divide 97 - 1, so this exercises the mixed-radix
    // fallback through the nested-vector overload.
    first.assign(5, std::vector<mint>(3));
    second.assign(5, std::vector<mint>(3));
    for (auto& row : first) {
        for (mint& coefficient : row) coefficient = value++;
    }
    for (auto& row : second) {
        for (mint& coefficient : row) coefficient = value++;
    }
    flattened_first.clear();
    flattened_second.clear();
    for (const auto& row : first) {
        flattened_first.insert(flattened_first.end(), row.begin(), row.end());
    }
    for (const auto& row : second) {
        flattened_second.insert(flattened_second.end(), row.begin(), row.end());
    }
    expected = naive(std::vector<int>{3, 5}, flattened_first, flattened_second);
    const auto fallback_result =
        m1une::math::multivariate_convolution_cyclic(first, second);
    index = 0;
    for (const auto& row : fallback_result) {
        for (mint coefficient : row) assert(coefficient == expected[index++]);
    }
}

}  // namespace

int main() {
    test_randomized();
    test_nested_vectors();
    test_fixed_mod_randomized<m1une::math::modint998244353>(0x123456789abcdefULL);
    test_fixed_mod_randomized<m1une::math::modint1000000007>(0x314159265358979ULL);

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    uint32_t modulus = 1;
    int variable_count = 0;
    input.read(modulus, variable_count);
    mint::set_mod(modulus);
    std::vector<int> dimensions(variable_count);
    input.read(dimensions);
    int size = 1;
    for (int dimension : dimensions) size *= dimension;
    std::vector<mint> first(size), second(size);
    input.read(first);
    input.read(second);
    output.println(
        m1une::math::multivariate_convolution_cyclic(
            dimensions, first, second
        )
    );
}
