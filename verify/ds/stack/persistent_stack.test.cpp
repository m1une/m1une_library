#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_2_A"

#include "../../../ds/stack/persistent_stack.hpp"
#include "../../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace {

void test_randomized() {
    using Stack = m1une::ds::PersistentStack<int>;

    std::uint64_t state = 49979687ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    std::vector<std::pair<Stack, std::vector<int>>> versions;
    versions.emplace_back();
    for (int step = 0; step < 10000; step++) {
        int version = int(random() % versions.size());
        const Stack& current = versions[version].first;
        const std::vector<int>& expected = versions[version].second;
        assert(current.size() == int(expected.size()));
        assert(current.empty() == expected.empty());
        if (!expected.empty()) assert(current.top() == expected.back());

        Stack next = current;
        std::vector<int> next_expected = expected;
        if (expected.empty() || random() % 3 != 0) {
            int value = int(random() % 1000000);
            next = current.push(value);
            next_expected.push_back(value);
        } else {
            next = current.pop();
            next_expected.pop_back();
        }
        assert(current.size() == int(expected.size()));
        if (!expected.empty()) assert(current.top() == expected.back());
        assert(next.size() == int(next_expected.size()));
        if (!next_expected.empty()) assert(next.top() == next_expected.back());
        versions.emplace_back(std::move(next), std::move(next_expected));
    }

    Stack stable = Stack().emplace(1);
    const int& reference = stable.top();
    Stack growing = stable;
    for (int value = 2; value <= 1000; value++) growing = growing.push(value);
    assert(reference == 1);
    assert(growing.top() == 1000);
    assert(growing.clear().empty());

    m1une::ds::PersistentStack<std::unique_ptr<int>> move_only;
    auto first = move_only.push(std::make_unique<int>(4));
    auto second = first.emplace(new int(9));
    assert(*first.top() == 4);
    assert(*second.top() == 9);
    assert(*second.pop().top() == 4);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int stack_count = 0, query_count = 0;
    fast_input >> stack_count >> query_count;
    using Stack = m1une::ds::PersistentStack<int>;
    Stack empty;
    std::vector<Stack> stacks(stack_count, empty);
    while (query_count--) {
        int type = 0, stack = 0;
        fast_input >> type >> stack;
        if (type == 0) {
            int value = 0;
            fast_input >> value;
            stacks[stack] = stacks[stack].push(value);
        } else if (type == 1) {
            if (!stacks[stack].empty()) fast_output << stacks[stack].top() << '\n';
        } else if (!stacks[stack].empty()) {
            stacks[stack] = stacks[stack].pop();
        }
    }
}
