#define PROBLEM "https://judge.yosupo.jp/problem/static_range_lis_query"

#include "../../../ds/range_query/range_lis_query.hpp"
#include "../../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

namespace {

int brute(const std::vector<int>& values, int left, int right) {
    std::vector<int> tails;
    for (int i = left; i < right; i++) {
        auto position = std::lower_bound(
            tails.begin(),
            tails.end(),
            values[i]
        );
        if (position == tails.end()) {
            tails.push_back(values[i]);
        } else {
            *position = values[i];
        }
    }
    return int(tails.size());
}

void test_randomized() {
    m1une::ds::RangeLisQuery<int> empty(std::vector<int>{});
    assert(empty.empty());
    assert(empty.query(0, 0) == 0);

    std::uint64_t state = 3141592653ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int n = int(random() % 36);
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 11) - 5;
        m1une::ds::RangeLisQuery<int> structure(values);
        assert(structure.size() == n);
        assert(structure.empty() == (n == 0));

        for (int left = 0; left <= n; left++) {
            for (int right = left; right <= n; right++) {
                int expected = brute(values, left, right);
                assert(structure.query(left, right) == expected);
                assert(structure.lis_length(left, right) == expected);
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
    std::vector<int> permutation(n);
    for (int& value : permutation) input.read(value);

    m1une::ds::RangeLisQuery<int> structure(permutation);
    while (query_count--) {
        int left = 0, right = 0;
        input.read(left, right);
        output.println(structure.query(left, right));
    }
}
