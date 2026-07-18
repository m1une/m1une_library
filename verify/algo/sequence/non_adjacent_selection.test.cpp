#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

#include "../../../algo/sequence/non_adjacent_selection.hpp"
#include "../../../utilities/fast_io.hpp"

std::vector<long long> naive_non_adjacent_selection_sums(
    const std::vector<long long>& values,
    bool maximize
) {
    const int n = int(values.size());
    const int count_limit = (n + 1) / 2;
    const long long inf = std::numeric_limits<long long>::max();
    std::vector<long long> result(count_limit, maximize ? -inf : inf);

    for (int mask = 0; mask < (1 << n); ++mask) {
        if ((mask & (mask << 1)) != 0) continue;
        const int count = __builtin_popcount(unsigned(mask));
        if (count == 0) continue;

        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) sum += values[i];
        }
        if (maximize) {
            result[count - 1] = std::max(result[count - 1], sum);
        } else {
            result[count - 1] = std::min(result[count - 1], sum);
        }
    }
    return result;
}

void test_examples_and_boundaries() {
    assert(m1une::algo::maximum_non_adjacent_selection_sums(std::vector<long long>{}).empty());
    assert(m1une::algo::minimum_non_adjacent_selection_sums(std::vector<long long>{}).empty());

    std::vector<long long> one = {-7};
    assert(m1une::algo::maximum_non_adjacent_selection_sums(one) == one);
    assert(m1une::algo::minimum_non_adjacent_selection_sums(one) == one);

    std::vector<long long> values = {4, 1, 7, 3};
    std::vector<long long> expected_maximum = {7, 11};
    std::vector<long long> expected_minimum = {1, 4};
    assert(m1une::algo::maximum_non_adjacent_selection_sums(values) == expected_maximum);
    assert(m1une::algo::minimum_non_adjacent_selection_sums(values) == expected_minimum);

    values = {1, 100, 1};
    expected_maximum = {100, 2};
    expected_minimum = {1, 2};
    assert(m1une::algo::maximum_non_adjacent_selection_sums(values) == expected_maximum);
    assert(m1une::algo::minimum_non_adjacent_selection_sums(values) == expected_minimum);
}

void test_randomized() {
    unsigned state = 123456789U;
    auto random = [&]() {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    };

    for (int n = 0; n <= 12; ++n) {
        for (int iteration = 0; iteration < 500; ++iteration) {
            std::vector<long long> values(n);
            for (long long& value : values) {
                value = static_cast<long long>(random() % 41) - 20;
            }

            assert(
                m1une::algo::maximum_non_adjacent_selection_sums(values)
                == naive_non_adjacent_selection_sums(values, true)
            );
            assert(
                m1une::algo::minimum_non_adjacent_selection_sums(values)
                == naive_non_adjacent_selection_sums(values, false)
            );
        }
    }
}

int main() {
    test_examples_and_boundaries();
    test_randomized();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long a, b;
    input >> a >> b;
    output << a + b << '\n';
}
