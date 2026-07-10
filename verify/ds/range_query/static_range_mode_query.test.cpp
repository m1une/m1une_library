#define PROBLEM "https://judge.yosupo.jp/problem/static_range_mode_query"

#include "../../../ds/range_query/static_range_mode_query.hpp"
#include "../../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <map>
#include <utility>
#include <vector>

namespace {

std::pair<int, int> brute(
    const std::vector<int>& values,
    int left,
    int right
) {
    std::map<int, int> frequency;
    std::pair<int, int> result{values[left], 0};
    for (int i = left; i < right; i++) {
        int count = ++frequency[values[i]];
        if (count > result.second) result = {values[i], count};
    }
    return result;
}

void test_randomized() {
    m1une::ds::StaticRangeModeQuery<int> empty;
    assert(empty.empty());
    assert(empty.size() == 0);

    std::uint64_t state = 2718281828ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int n = int(random() % 50) + 1;
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 13) - 6;
        m1une::ds::StaticRangeModeQuery<int> structure(values);
        assert(structure.size() == n);
        assert(!structure.empty());

        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right <= n; right++) {
                auto [value, frequency] = structure.query(left, right);
                auto expected = brute(values, left, right);
                assert(frequency == expected.second);
                assert(
                    std::count(
                        values.begin() + left,
                        values.begin() + right,
                        value
                    ) == frequency
                );
            }
        }
    }
}

}  // namespace

int main() {
    test_randomized();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n = 0, query_count = 0;
    input.read(n, query_count);
    std::vector<int> values(n);
    for (int& value : values) input.read(value);

    m1une::ds::StaticRangeModeQuery<int> structure(values);
    while (query_count--) {
        int left = 0, right = 0;
        input.read(left, right);
        auto [mode, frequency] = structure.query(left, right);
        output.println(mode, frequency);
    }
}
