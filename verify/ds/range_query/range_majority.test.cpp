#define PROBLEM "https://judge.yosupo.jp/problem/majority_voting"

#include "../../../ds/range_query/range_majority.hpp"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <map>
#include <optional>
#include <utility>
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
    m1une::ds::RangeMajority<int> empty;
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

        m1une::ds::RangeMajority<int> structure(values);
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

    for (int trial = 0; trial < 500; trial++) {
        int n = int(random() % 80) + 1;
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 15) - 7;

        m1une::ds::RangeMajority<int> structure(values);
        for (int operation = 0; operation < 500; operation++) {
            if (random() % 2 == 0) {
                int index = int(random() % n);
                int value = int(random() % 31) - 15;
                structure.set(index, value);
                values[index] = value;
            } else {
                int left = int(random() % n);
                int right = int(random() % n);
                if (left > right) std::swap(left, right);
                ++right;
                std::optional<int> expected = brute(values, left, right);
                assert(structure.query(left, right) == expected);
                assert(structure.majority(left, right) == expected);
            }
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int size, query_count;
    fast_input >> size >> query_count;
    std::vector<int> values(size);
    for (int& value : values) fast_input >> value;

    m1une::ds::RangeMajority<int> structure(values);
    while (query_count--) {
        int type, first, second;
        fast_input >> type >> first >> second;
        if (type == 0) {
            structure.set(first, second);
        } else {
            std::optional<int> result = structure.majority(first, second);
            fast_output << (result.has_value() ? *result : -1) << '\n';
        }
    }
}
