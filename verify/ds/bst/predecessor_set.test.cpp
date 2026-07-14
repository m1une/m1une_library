#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include "../../../ds/bst/predecessor_set.hpp"
#include "../../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <set>
#include <string>

namespace {

int expected_successor(const std::set<int>& expected, int key) {
    auto iterator = expected.lower_bound(key);
    return iterator == expected.end() ? -1 : *iterator;
}

int expected_strict_successor(const std::set<int>& expected, int key) {
    auto iterator = expected.upper_bound(key);
    return iterator == expected.end() ? -1 : *iterator;
}

int expected_predecessor(const std::set<int>& expected, int key) {
    auto iterator = expected.upper_bound(key);
    if (iterator == expected.begin()) return -1;
    return *--iterator;
}

int expected_strict_predecessor(const std::set<int>& expected, int key) {
    auto iterator = expected.lower_bound(key);
    if (iterator == expected.begin()) return -1;
    return *--iterator;
}

void test_randomized() {
    m1une::ds::PredecessorSet empty;
    assert(empty.universe_size() == 0);
    assert(empty.size() == 0);
    assert(empty.empty());
    assert(empty.min() == -1);
    assert(empty.max() == -1);

    constexpr int universe_size = 5000;
    std::uint64_t state = 1602176623ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    std::string membership(universe_size, '0');
    std::set<int> expected;
    for (int key = 0; key < universe_size; key++) {
        if (random() % 11 == 0) {
            membership[key] = '1';
            expected.insert(key);
        }
    }
    m1une::ds::PredecessorSet set(membership);
    assert(set.universe_size() == universe_size);
    assert(set.size() == int(expected.size()));

    for (int query = 0; query < 50000; query++) {
        int key = int(random() % universe_size);
        int type = int(random() % 7);
        if (type == 0) {
            assert(set.insert(key) == expected.insert(key).second);
        } else if (type == 1) {
            assert(set.erase(key) == (expected.erase(key) != 0));
        } else if (type == 2) {
            assert(set.contains(key) == expected.contains(key));
        } else if (type == 3) {
            int answer = expected_successor(expected, key);
            assert(set.successor(key) == answer);
            assert(set.min_ge(key) == answer);
        } else if (type == 4) {
            int answer = expected_predecessor(expected, key);
            assert(set.predecessor(key) == answer);
            assert(set.max_le(key) == answer);
        } else if (type == 5) {
            assert(set.min_gt(key) == expected_strict_successor(expected, key));
        } else {
            assert(set.max_lt(key) == expected_strict_predecessor(expected, key));
        }

        if (query % 1000 == 0) {
            assert(set.size() == int(expected.size()));
            assert(set.empty() == expected.empty());
            assert(set.min() == expected_successor(expected, 0));
            assert(set.max() == expected_predecessor(expected, universe_size - 1));
            for (int boundary : {0, 63, 64, 4095, 4096, universe_size - 1}) {
                assert(set.contains(boundary) == expected.contains(boundary));
                assert(set.successor(boundary) == expected_successor(expected, boundary));
                assert(set.predecessor(boundary) == expected_predecessor(expected, boundary));
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
    std::string membership;
    input.read(n, query_count, membership);
    m1une::ds::PredecessorSet set(membership);
    assert(set.universe_size() == n);

    while (query_count--) {
        int type = 0, key = 0;
        input.read(type, key);
        if (type == 0) {
            set.insert(key);
        } else if (type == 1) {
            set.erase(key);
        } else if (type == 2) {
            output.println(set.contains(key));
        } else if (type == 3) {
            output.println(set.successor(key));
        } else {
            output.println(set.predecessor(key));
        }
    }
}
