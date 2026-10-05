#define PROBLEM "https://yukicoder.me/problems/no/3075"

#include "../../../algo/sequence/mex.hpp"
#include "../../../ds/bst/mex_multiset.hpp"
#include "../../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <random>
#include <set>
#include <vector>

namespace {

template <class T>
int naive_mex(const std::vector<T>& values) {
    std::set<T> present(values.begin(), values.end());
    int answer = 0;
    while (present.contains(T(answer))) ++answer;
    return answer;
}

void test_static() {
    using m1une::algo::mex;
    assert(mex(std::vector<int>()) == 0);
    assert(mex(std::vector<int>{0, 1, 1, 3}) == 2);
    assert(mex(std::vector<int>{1, 2, 3}) == 0);
    assert(mex(std::vector<long long>{
        std::numeric_limits<long long>::min(), 0, 1,
        std::numeric_limits<long long>::max()
    }) == 2);
    assert(mex(std::vector<std::uint64_t>{
        0, 1, std::numeric_limits<std::uint64_t>::max()
    }) == 2);
    assert(mex(std::vector<bool>{false, true}) == 2);

    // Exhaust all short vectors over an alphabet containing a negative value.
    int cases = 1;
    for (int n = 0; n <= 6; ++n, cases *= 6) {
        for (int code = 0; code < cases; ++code) {
            int remaining = code;
            std::vector<int> values(n);
            for (int& value : values) {
                value = remaining % 6 - 1;
                remaining /= 6;
            }
            const auto original = values;
            assert(mex(values) == naive_mex(values));
            assert(values == original);
        }
    }

    std::mt19937_64 random(1602176623);
    for (int iteration = 0; iteration < 5000; ++iteration) {
        const int n = int(random() % 200);
        std::vector<long long> values(n);
        for (long long& value : values) {
            value = static_cast<long long>(random() % (2 * n + 3)) - n / 2;
        }
        assert(mex(values) == naive_mex(values));
        std::vector<std::uint64_t> unsigned_values(n);
        for (auto& value : unsigned_values) {
            value = random() % 3 == 0 ? random() : random() % (n + 1);
        }
        assert(mex(unsigned_values) == naive_mex(unsigned_values));
    }
}

void test_boundaries() {
    using m1une::ds::MexMultiset;
    MexMultiset empty;
    assert(empty.universe_size() == 0);
    empty.insert(0);
    empty.insert(-1);
    assert(!empty.erase(0));
    assert(empty.count(0) == 0);
    assert(empty.mex() == 0);

    for (int n : {0, 1, 2, 63, 64, 65, 127, 128, 129, 4095, 4096, 4097, 262145}) {
        MexMultiset values(n);
        const MexMultiset& query = values;
        for (int value = 0; value < n; ++value) {
            assert(query.mex() == value);
            values.insert(value);
            values.insert(value);
            assert(query.count(value) == 2);
            assert(query.mex() == value + 1);
            assert(values.erase(value));
            assert(query.mex() == value + 1);
        }
        assert(query.mex() == n);
        values.insert(std::numeric_limits<long long>::min());
        values.insert(std::numeric_limits<long long>::max());
        values.insert(n);
        assert(!values.erase(-1));
        assert(!values.erase(n));
        assert(query.count(-1) == 0);
        assert(query.count(n) == 0);
        assert(query.mex() == n);

        const MexMultiset original = values;
        for (int hole : {0, 63, 64, 127, 128, 4095, 4096, 262143, 262144}) {
            if (hole >= n) continue;
            assert(values.erase(hole));
            assert(!values.erase(hole));
            assert(query.mex() == hole);
            assert(original.mex() == n);
            values.insert(hole);
            assert(query.mex() == n);
        }
        for (int value = n - 1; value >= 0; --value) {
            assert(values.erase(value));
            assert(query.mex() == value);
        }

        std::vector<int> permutation(n);
        std::iota(permutation.begin(), permutation.end(), 0);
        const MexMultiset built(permutation);
        assert(built.universe_size() == n);
        assert(built.mex() == n);
    }

    const MexMultiset wide(std::vector<std::uint64_t>{
        0, 1, std::numeric_limits<std::uint64_t>::max()
    });
    assert(wide.mex() == 2);
    assert(wide.count(0) == 1);
    assert(wide.count(1) == 1);
    assert(wide.count(2) == 0);
    assert(MexMultiset(std::vector<bool>{false, true}).mex() == 2);
}

void test_randomized_updates() {
    std::mt19937 random(314159265);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const int n = int(random() % 257);
        std::vector<long long> initial(n);
        std::vector<int> counts(n, 0);
        for (long long& value : initial) {
            value = int(random() % (n + 7)) - 3;
            if (0 <= value && value < n) ++counts[int(value)];
        }
        m1une::ds::MexMultiset values(initial);
        assert(values.mex() == naive_mex(initial));
        for (int step = 0; step < 2000; ++step) {
            const int key = int(random() % (n + 7)) - 3;
            if (random() % 2 == 0) {
                values.insert(key);
                if (0 <= key && key < n) ++counts[key];
            } else {
                const bool exists = 0 <= key && key < n && counts[key] != 0;
                assert(values.erase(key) == exists);
                if (exists) --counts[key];
            }
            int expected = 0;
            while (expected < n && counts[expected] != 0) ++expected;
            assert(values.mex() == expected);
            assert(values.count(key) == (0 <= key && key < n ? counts[key] : 0));
        }
    }
}

long long recurrence_term(std::vector<long long> window, long long index) {
    const int n = int(window.size());
    if (index <= n) return window[int(index - 1)];
    m1une::ds::MexMultiset values(window);
    assert(values.mex() == m1une::algo::mex(window));
    std::vector<int> period(n + 1);
    for (int step = 0; step <= n; ++step) {
        const int next = values.mex();
        period[step] = next;
        values.erase(window[step % n]);
        values.insert(next);
        window[step % n] = next;
    }
    // Consecutive generated terms cannot repeat within N positions.
    // These N+1 terms are therefore a permutation of [0, N], which repeats.
    return period[static_cast<std::size_t>((index - n - 1) % (n + 1))];
}

void test_recurrence() {
    std::mt19937 random(271828182);
    for (int iteration = 0; iteration < 300; ++iteration) {
        const int n = 1 + int(random() % 30);
        std::vector<long long> initial(n);
        for (auto& value : initial) value = random() % (2 * n + 5);
        std::vector<long long> sequence = initial;
        for (int index = n; index < 5 * n + 10; ++index) {
            std::vector<long long> window(sequence.end() - n, sequence.end());
            sequence.push_back(naive_mex(window));
        }
        for (int index = 1; index <= int(sequence.size()); ++index) {
            assert(recurrence_term(initial, index) == sequence[index - 1]);
        }
        const long long distant = 1000000000000000000LL;
        const int equivalent = n + 1 + int((distant - n - 1) % (n + 1));
        assert(recurrence_term(initial, distant) == sequence[equivalent - 1]);
    }
}

}  // namespace

int main() {
    test_static();
    test_boundaries();
    test_randomized_updates();
    test_recurrence();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n = 0;
    long long index = 0;
    input.read(n, index);
    std::vector<long long> initial(n);
    for (auto& value : initial) input.read(value);
    output.println(recurrence_term(initial, index));
}
