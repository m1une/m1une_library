#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_A"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../../sequence/subset_sum.hpp"

std::vector<long long> naive_subset_sums(const std::vector<long long>& values) {
    std::vector<long long> sums(1, 0);
    for (long long value : values) {
        const std::size_t size = sums.size();
        for (std::size_t mask = 0; mask < size; ++mask) {
            sums.push_back(sums[mask] + value);
        }
    }
    return sums;
}

long long naive_maximum_subset_sum(
    const std::vector<long long>& values,
    long long limit
) {
    long long answer = 0;
    for (long long sum : naive_subset_sums(values)) {
        if (sum <= limit) answer = std::max(answer, sum);
    }
    return answer;
}

void basic_test() {
    const std::vector<long long> empty;
    auto [empty_left, empty_right] =
        m1une::sequence::enumerate_half_subset_sums(empty);
    assert(empty_left == std::vector<long long>{0});
    assert(empty_right == std::vector<long long>{0});
    assert(m1une::sequence::maximum_subset_sum(empty, 10LL) == 0);

    const std::vector<long long> values = {3, -1, 3};
    auto [left_sums, right_sums] =
        m1une::sequence::enumerate_half_subset_sums(values);
    assert(left_sums == std::vector<long long>({0, 3}));
    assert(right_sums == std::vector<long long>({-1, 0, 2, 3}));
    assert(m1une::sequence::maximum_subset_sum(values, 4LL) == 3);
}

void randomized_test() {
    std::mt19937 random(123456789);
    for (int test = 0; test < 200; ++test) {
        const int n = int(random() % 16);
        std::vector<long long> values(n);
        for (long long& value : values) {
            value = int(random() % 21) - 10;
        }
        const long long limit = random() % 101;

        auto [left_sums, right_sums] =
            m1une::sequence::enumerate_half_subset_sums(values);
        assert(std::is_sorted(left_sums.begin(), left_sums.end()));
        assert(std::is_sorted(right_sums.begin(), right_sums.end()));
        assert(left_sums.size() == (std::size_t(1) << (n / 2)));
        assert(right_sums.size() == (std::size_t(1) << (n - n / 2)));

        std::vector<long long> actual;
        actual.reserve(left_sums.size() * right_sums.size());
        for (long long left : left_sums) {
            for (long long right : right_sums) {
                actual.push_back(left + right);
            }
        }
        std::vector<long long> expected = naive_subset_sums(values);
        std::sort(actual.begin(), actual.end());
        std::sort(expected.begin(), expected.end());
        assert(actual == expected);

        assert(
            m1une::sequence::maximum_subset_sum(values, limit) ==
            naive_maximum_subset_sum(values, limit)
        );
    }
}

int main() {
    basic_test();
    randomized_test();

    int n;
    std::cin >> n;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    int query_count;
    std::cin >> query_count;
    while (query_count--) {
        long long target;
        std::cin >> target;
        const bool found =
            m1une::sequence::maximum_subset_sum(values, target) == target;
        std::cout << (found ? "yes" : "no") << '\n';
    }
}
