#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include "../../../algo/offline/mo_with_updates.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <string>
#include <vector>

#include "../../../utilities/fast_io.hpp"

namespace {

using Mo = m1une::algo::MoWithUpdates;

struct Change {
    int position;
    int before;
    int after;
};

struct Counts {
    int inside_apply = 0;
    int outside_apply = 0;
    int inside_undo = 0;
    int outside_undo = 0;
};

std::vector<int> frequencies(const Mo& mo, const std::vector<int>& initial,
                             const std::vector<Change>& changes, const std::vector<int>& targets,
                             int alphabet, int block_size = 0, Counts* counts = nullptr) {
    std::vector<int> values = initial;
    std::vector<int> frequency(alphabet, 0), result(mo.query_count(), -1);
    int time = 0;
    int length = 0;
    auto add = [&](int index) {
        ++frequency[values[index]];
        ++length;
    };
    auto remove = [&](int index) {
        assert(frequency[values[index]] > 0);
        --frequency[values[index]];
        --length;
    };
    auto replace = [&](int id, int left, int right, bool forward) {
        const Change& change = changes[id];
        const int old_value = forward ? change.before : change.after;
        const int new_value = forward ? change.after : change.before;
        assert(values[change.position] == old_value);
        (void)old_value;
        const bool inside = left <= change.position && change.position < right;
        if (inside) remove(change.position);
        values[change.position] = new_value;
        if (inside) add(change.position);
        if (counts != nullptr) {
            if (forward && inside) ++counts->inside_apply;
            if (forward && !inside) ++counts->outside_apply;
            if (!forward && inside) ++counts->inside_undo;
            if (!forward && !inside) ++counts->outside_undo;
        }
    };
    mo.run(add, remove,
        [&](int id, int left, int right) {
            assert(id == time);
            replace(id, left, right, true);
            ++time;
        },
        [&](int id, int left, int right) {
            assert(id == time - 1);
            replace(id, left, right, false);
            --time;
        },
        [&](int id) {
            const auto& query = mo.queries()[id];
            assert(time == query.time && length == query.right - query.left);
            assert(result[id] == -1);
            (void)query;
            result[id] = frequency[targets[id]];
        }, block_size);
    return result;
}

void check_directional(const Mo& mo, const std::vector<int>& initial,
                       const std::vector<Change>& changes,
                       const std::vector<std::vector<int>>& states, int block_size) {
    std::vector<int> values = initial;
    std::string word;
    int left = 0, right = 0, time = 0, answered = 0;
    auto replace = [&](int id, int l, int r, bool forward) {
        assert(l == left && r == right && int(word.size()) == r - l);
        const Change& change = changes[id];
        assert(values[change.position] == (forward ? change.before : change.after));
        values[change.position] = forward ? change.after : change.before;
        if (l <= change.position && change.position < r) {
            word[change.position - l] = char('a' + values[change.position]);
        }
    };
    mo.run(
        [&](int index) {
            assert(index == left - 1);
            --left;
            word.insert(word.begin(), char('a' + values[index]));
        },
        [&](int index) {
            assert(index == right);
            ++right;
            word.push_back(char('a' + values[index]));
        },
        [&](int index) {
            assert(index == left && !word.empty());
            assert(word.front() == char('a' + values[index]));
            ++left;
            word.erase(word.begin());
        },
        [&](int index) {
            assert(index == right - 1 && !word.empty());
            assert(word.back() == char('a' + values[index]));
            --right;
            word.pop_back();
        },
        [&](int id, int l, int r) {
            assert(id == time);
            replace(id, l, r, true);
            ++time;
        },
        [&](int id, int l, int r) {
            assert(id == time - 1);
            replace(id, l, r, false);
            --time;
        },
        [&](int id) {
            const auto& query = mo.queries()[id];
            assert(left == query.left && right == query.right && time == query.time);
            assert(values == states[time]);
            std::string expected;
            for (int i = left; i < right; ++i) expected += char('a' + states[time][i]);
            assert(word == expected);
            ++answered;
            (void)query;
        }, block_size);
    assert(answered == mo.query_count());
}

void test_boundaries() {
    Mo empty;
    assert(empty.size() == 0 && empty.empty());
    assert(empty.query_count() == 0 && empty.update_count() == 0);
    assert(empty.order().empty());
    int calls = 0;
    empty.run([&](int) { ++calls; }, [&](int) { ++calls; },
        [&](int, int, int) { ++calls; }, [&](int, int, int) { ++calls; },
        [&](int) { ++calls; });
    assert(calls == 0);
    int id = empty.add_query(0, 0);
    assert(id == 0);
    empty.run([&](int) { assert(false); }, [&](int) { assert(false); },
        [&](int, int, int) { assert(false); }, [&](int, int, int) { assert(false); },
        [&](int id) { assert(id == 0); ++calls; });
    assert(calls == 1);
    empty.clear();
    assert(empty.empty() && empty.update_count() == 0);

    Mo updates_only(6);
    updates_only.reserve(10);
    id = updates_only.add_update();
    assert(id == 0);
    id = updates_only.add_update();
    assert(id == 1);
    assert(updates_only.empty());
    updates_only.run([](int) { assert(false); }, [](int) { assert(false); },
        [](int, int, int) { assert(false); }, [](int, int, int) { assert(false); },
        [](int) { assert(false); });
    id = updates_only.add_query(0, 1, 2);
    assert(id == 0);
    id = updates_only.add_query(1, 2, 0);
    assert(id == 1);
    id = updates_only.add_query(2, 3);
    assert(id == 2);
    id = updates_only.add_query(4, 5, 0);
    assert(id == 3);
    const std::vector<int> initial = {0, 1, 2, 3, 4, 5};
    std::vector<Change> changes;
    changes.push_back(Change{0, 0, 5});
    changes.push_back(Change{1, 1, 5});
    Counts counts;
    const auto result = frequencies(updates_only, initial, changes, std::vector<int>(4, 5), 6, 1, &counts);
    const std::vector<int> expected = {1, 0, 0, 0};
    assert(result == expected);
    assert(counts.inside_apply > 0 && counts.outside_apply > 0);
    assert(counts.inside_undo > 0 && counts.outside_undo > 0);
    updates_only.clear();
    assert(updates_only.size() == 6 && updates_only.update_count() == 0);
    id = updates_only.add_update();
    assert(id == 0);
    id = updates_only.add_query(0, 6);
    assert(id == 0);
    assert(updates_only.queries()[0].time == 1);
    (void)id;
}

void test_randomized() {
    std::uint64_t seed = 20261117;
    auto random = [&]() {
        seed ^= seed << 7;
        seed ^= seed >> 9;
        return seed;
    };
    for (int trial = 0; trial < 250; ++trial) {
        const int n = int(random() % 26);
        std::vector<int> initial(n);
        for (int& value : initial) value = int(random() % 6);
        std::vector<int> current = initial;
        std::vector<std::vector<int>> states;
        states.push_back(initial);
        std::vector<Change> changes;
        std::vector<int> targets, expected;
        Mo mo(n);
        mo.reserve(100);
        auto query = [&](int time, bool explicit_time) {
            int left = int(random() % (n + 1));
            int right = int(random() % (n + 1));
            if (left > right) std::swap(left, right);
            const int value = int(random() % 7);
            const int id = explicit_time ? mo.add_query(left, right, time) : mo.add_query(left, right);
            assert(id == int(targets.size()));
            (void)id;
            targets.push_back(value);
            expected.push_back(int(std::count(states[time].begin() + left, states[time].begin() + right, value)));
        };
        const int events = int(random() % 100);
        for (int event = 0; event < events; ++event) {
            if (n > 0 && random() % 2 == 0) {
                const int position = int(random() % n);
                const int value = int(random() % 6);
                const int id = mo.add_update();
                assert(id == int(changes.size()));
                (void)id;
                changes.push_back(Change{position, current[position], value});
                current[position] = value;
                states.push_back(current);
            } else {
                query(mo.update_count(), false);
            }
        }
        for (int i = 0; i < 8; ++i) query(int(random() % states.size()), true);

        for (int block_size : std::vector<int>{0, 1, 3, n + 1, -1}) {
            const auto order = mo.order(block_size);
            assert(order == mo.order(block_size));
            auto sorted = order;
            std::sort(sorted.begin(), sorted.end());
            std::vector<int> ids(mo.query_count());
            std::iota(ids.begin(), ids.end(), 0);
            assert(sorted == ids);
            const auto actual = frequencies(mo, initial, changes, targets, 7, block_size);
            assert(actual == expected);
        }
        check_directional(mo, initial, changes, states, 2);
        // A second run starts from a fresh array and aggregate; the schedule is unchanged.
        const auto repeated = frequencies(mo, initial, changes, targets, 7);
        assert(repeated == expected);
    }
}

}  // namespace

int main() {
    test_boundaries();
    test_randomized();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n, q;
    if (!input.read(n, q)) return 0;
    std::vector<int> initial(n);
    for (int& value : initial) input >> value;
    std::vector<int> current = initial;
    std::vector<int> alphabet = initial;
    std::vector<Change> changes;
    std::vector<int> targets;
    Mo mo(n);
    mo.reserve(q);
    for (int event = 0; event < q; ++event) {
        int type;
        input >> type;
        if (type == 0) {
            int position, value;
            input >> position >> value;
            mo.add_update();
            changes.push_back(Change{position, current[position], value});
            current[position] = value;
            alphabet.push_back(value);
        } else {
            int left, right, value;
            input >> left >> right >> value;
            mo.add_query(left, right);
            targets.push_back(value);
            alphabet.push_back(value);
        }
    }
    std::sort(alphabet.begin(), alphabet.end());
    alphabet.erase(std::unique(alphabet.begin(), alphabet.end()), alphabet.end());
    auto compress = [&](int value) {
        return int(std::lower_bound(alphabet.begin(), alphabet.end(), value) - alphabet.begin());
    };
    for (int& value : initial) value = compress(value);
    for (auto& change : changes) {
        change.before = compress(change.before);
        change.after = compress(change.after);
    }
    for (int& value : targets) value = compress(value);
    for (int result : frequencies(mo, initial, changes, targets, int(alphabet.size()))) {
        output << result << '\n';
    }
}
