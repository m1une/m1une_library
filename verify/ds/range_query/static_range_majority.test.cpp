#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/range_query/static_range_majority.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <vector>

namespace {

std::optional<int> brute(
    const std::vector<int>& values,
    int left,
    int right
) {
    std::map<int, int> frequency;
    for (int index = left; index < right; index++) {
        int count = ++frequency[values[index]];
        if (count * 2 > right - left) return values[index];
    }
    return std::nullopt;
}

void test_randomized() {
    m1une::ds::StaticRangeMajority<int> empty;
    assert(empty.empty());
    assert(empty.size() == 0);

    std::uint64_t state = 1414213562ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        int n = int(random() % 80) + 1;
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 15) - 7;

        m1une::ds::StaticRangeMajority<int> structure(values);
        assert(structure.size() == n);
        assert(!structure.empty());
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right <= n; right++) {
                std::optional<int> expected = brute(values, left, right);
                assert(structure.query(left, right) == expected);
                assert(structure.majority(left, right) == expected);
            }
        }
    }
}

}  // namespace

int main() {
    test_randomized();

    long long first, second;
    std::cin >> first >> second;
    std::cout << first + second << '\n';
}
