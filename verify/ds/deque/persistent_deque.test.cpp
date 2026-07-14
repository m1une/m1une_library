#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "../../../ds/deque/persistent_deque.hpp"
#include "../../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <deque>
#include <memory>
#include <utility>
#include <vector>

namespace {

using Deque = m1une::ds::PersistentDeque<int>;

void assert_ends(const Deque& actual, const std::deque<int>& expected) {
    assert(actual.size() == int(expected.size()));
    assert(actual.empty() == expected.empty());
    if (expected.empty()) return;
    assert(actual.front() == expected.front());
    assert(actual.back() == expected.back());
}

void assert_all(Deque actual, std::deque<int> expected) {
    assert_ends(actual, expected);
    while (!expected.empty()) {
        assert(actual.front() == expected.front());
        actual = actual.pop_front();
        expected.pop_front();
    }
    assert(actual.empty());
}

void test_randomized() {
    std::uint64_t state = 49979687ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    std::vector<std::pair<Deque, std::deque<int>>> versions;
    versions.emplace_back();
    for (int step = 0; step < 10000; step++) {
        int version = int(random() % versions.size());
        const Deque& current = versions[version].first;
        const std::deque<int>& expected = versions[version].second;
        assert_ends(current, expected);

        Deque next = current;
        std::deque<int> next_expected = expected;
        int operation = expected.empty() ? int(random() % 2) : int(random() % 4);
        if (operation == 0) {
            int value = int(random() % 1000000);
            next = current.push_front(value);
            next_expected.push_front(value);
        } else if (operation == 1) {
            int value = int(random() % 1000000);
            next = current.push_back(value);
            next_expected.push_back(value);
        } else if (operation == 2) {
            next = current.pop_front();
            next_expected.pop_front();
        } else {
            next = current.pop_back();
            next_expected.pop_back();
        }

        assert_ends(current, expected);
        assert_ends(next, next_expected);
        if (step % 127 == 0) assert_all(next, next_expected);
        versions.emplace_back(std::move(next), std::move(next_expected));
    }
}

void test_adversarial() {
    Deque deque;
    std::deque<int> expected;
    for (int value = 0; value < 50000; value++) {
        if (value % 2 == 0) {
            deque = deque.push_front(value);
            expected.push_front(value);
        } else {
            deque = deque.push_back(value);
            expected.push_back(value);
        }
        assert_ends(deque, expected);
    }
    for (int step = 0; step < 50000; step++) {
        if (step % 2 == 0) {
            deque = deque.pop_back();
            expected.pop_back();
        } else {
            deque = deque.pop_front();
            expected.pop_front();
        }
        assert_ends(deque, expected);
    }
    assert(deque.empty());

    Deque one_sided;
    for (int value = 0; value < 50000; value++) {
        one_sided = one_sided.push_front(value);
    }
    for (int value = 0; value < 50000; value++) {
        assert(one_sided.back() == value);
        one_sided = one_sided.pop_back();
    }
    assert(one_sided.empty());

    Deque stable = Deque().push_back(4);
    const int& reference = stable.front();
    Deque growing = stable;
    for (int value = 5; value <= 10000; value++) {
        growing = growing.push_front(value).push_back(-value);
    }
    assert(reference == 4);
    assert(growing.front() == 10000);
    assert(growing.back() == -10000);
    assert(stable.front() == 4);
    assert(growing.clear().empty());

    m1une::ds::PersistentDeque<std::unique_ptr<int>> move_only;
    auto first = move_only.push_front(std::make_unique<int>(7));
    auto second = first.push_back(std::make_unique<int>(11));
    auto branch = first.push_front(std::make_unique<int>(3));
    assert(*first.front() == 7);
    assert(*second.back() == 11);
    assert(*second.pop_front().front() == 11);
    assert(*branch.front() == 3);
    assert(*branch.back() == 7);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();
    test_adversarial();

    int query_count = 0;
    fast_input >> query_count;
    Deque empty;
    std::vector<Deque> versions(query_count + 1, empty);
    for (int query = 0; query < query_count; query++) {
        int type = 0, base = 0;
        fast_input >> type >> base;
        const Deque& source = versions[base + 1];
        if (type == 0) {
            int value = 0;
            fast_input >> value;
            versions[query + 1] = source.push_back(value);
        } else {
            fast_output << source.front() << '\n';
            versions[query + 1] = source.pop_front();
        }
    }
}
