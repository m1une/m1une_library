#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct"

#include "../../../ds/range_query/static_range_count_distinct.hpp"
#include "../../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

namespace {

int brute(const std::vector<int>& values, int left, int right) {
    std::vector<int> distinct(values.begin() + left, values.begin() + right);
    std::sort(distinct.begin(), distinct.end());
    return int(std::unique(distinct.begin(), distinct.end()) - distinct.begin());
}

void test_randomized() {
    m1une::ds::StaticRangeCountDistinct<int> empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.query(0, 0) == 0);

    std::uint64_t state = 1618033988ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int n = int(random() % 80);
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 21) - 10;
        m1une::ds::StaticRangeCountDistinct<int> structure(values);
        assert(structure.size() == n);

        for (int query = 0; query < 500; query++) {
            int left = int(random() % std::uint64_t(n + 1));
            int right = int(random() % std::uint64_t(n + 1));
            if (right < left) std::swap(left, right);
            int expected = brute(values, left, right);
            assert(structure.query(left, right) == expected);
            assert(structure.count_distinct(left, right) == expected);
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

    m1une::ds::StaticRangeCountDistinct<int> structure(values);
    while (query_count--) {
        int left = 0, right = 0;
        input.read(left, right);
        output.println(structure.query(left, right));
    }
}
