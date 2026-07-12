#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

#include "../../../ds/heap/double_ended_priority_queue.hpp"

namespace {

void test_fixed() {
    m1une::ds::DoubleEndedPriorityQueue<int> queue = {3, 1, 7, 7, -2};
    assert(queue.size() == 5);
    assert(queue.min() == -2);
    assert(queue.max() == 7);

    queue.pop_min();
    assert(queue.min() == 1);
    queue.pop_max();
    assert(queue.max() == 7);
    queue.pop_max();
    assert(queue.max() == 3);
    queue.emplace(10);
    assert(queue.max() == 10);

    m1une::ds::MinMaxHeap<int, std::greater<int>> reversed;
    reversed.push(2);
    reversed.push(8);
    reversed.push(5);
    assert(reversed.min() == 8);
    assert(reversed.max() == 2);
    reversed.clear();
    assert(reversed.empty());
}

void test_randomized() {
    uint64_t state = 0x92d68ca2ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    m1une::ds::DoubleEndedPriorityQueue<int> queue;
    std::multiset<int> expected;
    for (int operation = 0; operation < 300000; operation++) {
        const int type = expected.size() < 1000 ? 0 : int(random() % 3);
        if (type == 0) {
            const int value = int(random() % 2001) - 1000;
            queue.push(value);
            expected.insert(value);
        } else if (type == 1) {
            assert(queue.min() == *expected.begin());
            queue.pop_min();
            expected.erase(expected.begin());
        } else {
            auto iterator = std::prev(expected.end());
            assert(queue.max() == *iterator);
            queue.pop_max();
            expected.erase(iterator);
        }

        assert(queue.size() == expected.size());
        assert(queue.empty() == expected.empty());
        if (!expected.empty()) {
            assert(queue.min() == *expected.begin());
            assert(queue.max() == *std::prev(expected.end()));
        }
    }

    bool remove_minimum = false;
    while (!expected.empty()) {
        remove_minimum = !remove_minimum;
        if (remove_minimum) {
            assert(queue.min() == *expected.begin());
            queue.pop_min();
            expected.erase(expected.begin());
        } else {
            auto iterator = std::prev(expected.end());
            assert(queue.max() == *iterator);
            queue.pop_max();
            expected.erase(iterator);
        }
    }
    assert(queue.empty());
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_fixed();
    test_randomized();

    int initial_size, query_count;
    std::cin >> initial_size >> query_count;
    m1une::ds::DoubleEndedPriorityQueue<int> queue;
    for (int i = 0; i < initial_size; i++) {
        int value;
        std::cin >> value;
        queue.push(value);
    }
    while (query_count--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int value;
            std::cin >> value;
            queue.push(value);
        } else if (type == 1) {
            std::cout << queue.min() << '\n';
            queue.pop_min();
        } else {
            std::cout << queue.max() << '\n';
            queue.pop_max();
        }
    }
}
