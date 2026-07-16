#define PROBLEM "https://judge.yosupo.jp/problem/prefix_substring_lcs"

#include "../../string/prefix_substring_lcs.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

template <class FirstSequence, class SecondSequence>
int naive_lcs(
    const FirstSequence& first,
    int first_prefix,
    const SecondSequence& second,
    int second_left,
    int second_right
) {
    std::vector<int> dp(second_right - second_left + 1, 0);
    for (int i = 0; i < first_prefix; i++) {
        int diagonal = 0;
        for (int j = second_left; j < second_right; j++) {
            const int up = dp[j - second_left + 1];
            if (first[i] == second[j]) {
                dp[j - second_left + 1] = diagonal + 1;
            } else {
                dp[j - second_left + 1] = std::max(
                    dp[j - second_left + 1],
                    dp[j - second_left]
                );
            }
            diagonal = up;
        }
    }
    return dp.back();
}

void test_fixed() {
    std::string first = "abac";
    std::string second = "cababa";
    m1une::string::PrefixSubstringLcs solver(first, second);
    assert(solver.first_size() == 4);
    assert(solver.second_size() == 6);
    assert(solver.empty());
    solver.reserve(8);

    assert(solver.add_query(0, 0, 6) == 0);
    assert(solver.add_query(4, 3, 3) == 1);
    assert(solver.add_query(3, 1, 5) == 2);
    assert(solver.add_query(4, 0, 3) == 3);
    assert(solver.query_count() == 4);
    std::vector<int> expected;
    expected.push_back(0);
    expected.push_back(0);
    expected.push_back(3);
    expected.push_back(2);
    assert(solver.calculate() == expected);
    assert(solver.calculate() == expected);

    solver.clear();
    assert(solver.empty());
    assert(solver.first_size() == 4);
    assert(solver.calculate().empty());

    std::string empty_first;
    std::string empty_second;
    m1une::string::PrefixSubstringLcs empty_solver(
        empty_first,
        empty_second
    );
    empty_solver.add_query(0, 0, 0);
    assert(empty_solver.calculate()[0] == 0);

    std::vector<int> first_values;
    first_values.push_back(1);
    first_values.push_back(3);
    first_values.push_back(2);
    std::vector<int> second_values;
    second_values.push_back(3);
    second_values.push_back(1);
    second_values.push_back(2);
    second_values.push_back(3);
    m1une::string::PrefixSubstringLcs vector_solver(
        first_values,
        second_values
    );
    vector_solver.add_query(3, 0, 4);
    vector_solver.add_query(2, 2, 4);
    expected.clear();
    expected.push_back(2);
    expected.push_back(1);
    assert(vector_solver.calculate() == expected);
}

void test_randomized() {
    std::uint64_t state = 20260716;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        const int n = int(random() % 13);
        const int m = int(random() % 13);
        std::string first(n, 'a');
        std::string second(m, 'a');
        for (char& value : first) value = char('a' + random() % 4);
        for (char& value : second) value = char('a' + random() % 4);

        m1une::string::PrefixSubstringLcs solver(first, second);
        const int query_count = 100;
        solver.reserve(query_count);
        std::vector<int> expected;
        expected.reserve(query_count);
        for (int query = 0; query < query_count; query++) {
            const int prefix = int(random() % (n + 1));
            int left = int(random() % (m + 1));
            int right = int(random() % (m + 1));
            if (left > right) std::swap(left, right);
            assert(solver.add_query(prefix, left, right) == query);
            expected.push_back(
                naive_lcs(first, prefix, second, left, right)
            );
        }
        assert(solver.calculate() == expected);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int query_count;
    fast_input >> query_count;
    std::string first, second;
    fast_input >> first >> second;

    m1une::string::PrefixSubstringLcs solver(
        std::move(first),
        std::move(second)
    );
    solver.reserve(query_count);
    while (query_count--) {
        int prefix, left, right;
        fast_input >> prefix >> left >> right;
        solver.add_query(prefix, left, right);
    }
    for (int answer : solver.calculate()) fast_output << answer << '\n';
}
