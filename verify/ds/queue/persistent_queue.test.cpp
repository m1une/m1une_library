#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "../../../ds/queue/persistent_queue.hpp"
#include "../../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <deque>
#include <memory>
#include <utility>
#include <vector>

namespace {

void test_randomized() {
    using Queue = m1une::ds::PersistentQueue<int>;

    std::uint64_t state = 32452843ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    std::vector<std::pair<Queue, std::deque<int>>> versions;
    versions.emplace_back();
    for (int step = 0; step < 5000; step++) {
        int version = int(random() % versions.size());
        const Queue& current = versions[version].first;
        const std::deque<int>& expected = versions[version].second;
        assert(current.size() == int(expected.size()));
        assert(current.empty() == expected.empty());
        if (!expected.empty()) {
            assert(current.front() == expected.front());
            assert(current.back() == expected.back());
        }

        Queue next = current;
        std::deque<int> next_expected = expected;
        if (expected.empty() || random() % 3 != 0) {
            int value = int(random() % 1000000);
            next = current.push(value);
            next_expected.push_back(value);
        } else {
            next = current.pop();
            next_expected.pop_front();
        }
        assert(current.size() == int(expected.size()));
        if (!expected.empty()) assert(current.front() == expected.front());
        assert(next.size() == int(next_expected.size()));
        if (!next_expected.empty()) {
            assert(next.front() == next_expected.front());
            assert(next.back() == next_expected.back());
        }
        versions.emplace_back(std::move(next), std::move(next_expected));
    }

    Queue stable = Queue().push(1);
    const int& reference = stable.front();
    Queue growing = stable;
    for (int value = 2; value <= 1000; value++) {
        growing = growing.push_back(value);
    }
    assert(reference == 1);
    assert(growing.back() == 1000);
    assert(growing.clear().empty());

    m1une::ds::PersistentQueue<std::unique_ptr<int>> move_only;
    auto first = move_only.push(std::make_unique<int>(4));
    auto second = first.push(std::make_unique<int>(9));
    assert(*first.front() == 4);
    assert(*second.front() == 4);
    assert(*second.back() == 9);
    assert(*second.pop_front().front() == 9);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int query_count = 0;
    fast_input >> query_count;
    using Queue = m1une::ds::PersistentQueue<int>;
    Queue empty;
    std::vector<Queue> versions(query_count + 1, empty);
    for (int query = 0; query < query_count; query++) {
        int type = 0, base = 0;
        fast_input >> type >> base;
        const auto& source = versions[base + 1];
        if (type == 0) {
            int value = 0;
            fast_input >> value;
            versions[query + 1] = source.push(value);
        } else {
            fast_output << source.front() << '\n';
            versions[query + 1] = source.pop();
        }
    }
}
