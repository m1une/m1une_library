#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#include "../../math/modint.hpp"
#include "../../matroid/linear_matroid.hpp"
#include "../../matroid/linear_matroid_intersection.hpp"
#include "../../utilities/fast_io.hpp"

using mint = m1une::math::modint998244353;

int brute_force(const std::vector<std::vector<mint>>& first,
                const std::vector<std::vector<mint>>& second) {
    m1une::matroid::LinearMatroid<mint> first_matroid(first);
    m1une::matroid::LinearMatroid<mint> second_matroid(second);
    const int ground_size = int(first.size());
    int answer = 0;
    for (int mask = 0; mask < (1 << ground_size); mask++) {
        std::vector<int> subset;
        for (int element = 0; element < ground_size; element++) {
            if (mask >> element & 1) subset.push_back(element);
        }
        if (first_matroid(subset) && second_matroid(subset)) {
            answer = std::max(answer, int(subset.size()));
        }
    }
    return answer;
}

void test_examples() {
    std::vector<std::vector<mint>> first(4), second(4);
    first[0] = {1, 0, 0};
    first[1] = {0, 1, 0};
    first[2] = {1, 1, 0};
    first[3] = {0, 0, 1};
    second[0] = {1, 0};
    second[1] = {1, 0};
    second[2] = {0, 1};
    second[3] = {0, 1};

    std::vector<mint> weights = {1, 2, 4, 8};
    assert(m1une::matroid::linear_matroid_intersection_size_with_weights(
               first, second, weights) == 2);
    assert(m1une::matroid::linear_matroid_intersection_size(first, second) == 2);

    std::vector<std::vector<mint>> empty;
    assert(m1une::matroid::linear_matroid_intersection_size(empty, empty) == 0);

    std::vector<std::vector<mint>> zero_dimension(3);
    assert(m1une::matroid::linear_matroid_intersection_size(
               zero_dimension, zero_dimension) == 0);
}

void test_random() {
    std::mt19937 random(123456789);
    for (int test = 0; test < 500; test++) {
        int ground_size = random() % 9;
        int first_dimension = 1 + random() % 5;
        int second_dimension = 1 + random() % 5;
        std::vector<std::vector<mint>> first(
            ground_size, std::vector<mint>(first_dimension));
        std::vector<std::vector<mint>> second(
            ground_size, std::vector<mint>(second_dimension));
        for (auto& vector : first) {
            for (mint& value : vector) value = int(random() % 7) - 3;
        }
        for (auto& vector : second) {
            for (mint& value : vector) value = int(random() % 7) - 3;
        }

        int expected = brute_force(first, second);
        int actual =
            m1une::matroid::linear_matroid_intersection_size(first, second, random);
        assert(actual == expected);
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_examples();
    test_random();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
