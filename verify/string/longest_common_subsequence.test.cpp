#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C"

#include "../../string/longest_common_subsequence.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

template <class FirstSequence, class SecondSequence>
int independent_lcs_length(const FirstSequence& first, const SecondSequence& second) {
    int n = int(first.size());
    int m = int(second.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (first[i] == second[j]) {
                dp[i][j] = dp[i + 1][j + 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }
    return dp[0][0];
}

template <class FirstSequence, class SecondSequence>
void check_result(const FirstSequence& first, const SecondSequence& second) {
    auto result = m1une::string::longest_common_subsequence(first, second);
    int expected = independent_lcs_length(first, second);
    assert(result.length() == expected);
    assert(result.empty() == (expected == 0));
    assert(
        m1une::string::longest_common_subsequence_length(first, second) ==
        expected
    );

    std::vector<int> first_indices = result.first_indices();
    std::vector<int> second_indices = result.second_indices();
    assert(int(first_indices.size()) == expected);
    assert(int(second_indices.size()) == expected);

    for (int k = 0; k < expected; k++) {
        int i = result.matches[k].first;
        int j = result.matches[k].second;
        assert(i == first_indices[k]);
        assert(j == second_indices[k]);
        assert(0 <= i && i < int(first.size()));
        assert(0 <= j && j < int(second.size()));
        assert(first[i] == second[j]);
        if (k > 0) {
            assert(result.matches[k - 1].first < i);
            assert(result.matches[k - 1].second < j);
        }
    }
}

void test_fixed() {
    check_result(std::string(), std::string());
    check_result(std::string("abc"), std::string());
    check_result(std::string(), std::string("abc"));
    check_result(std::string("abc"), std::string("def"));
    check_result(std::string("abcbdab"), std::string("bdcaba"));
    check_result(std::string("aaaa"), std::string("aa"));

    std::string first = "abcbdab";
    std::string second = "bdcaba";
    auto result = m1une::string::longest_common_subsequence(first, second);
    assert(result.length() == 4);
    assert(result.values_from_first(first) == result.values_from_second(second));

    std::vector<int> first_values;
    first_values.push_back(1);
    first_values.push_back(3);
    first_values.push_back(2);
    first_values.push_back(4);
    first_values.push_back(3);
    std::vector<int> second_values;
    second_values.push_back(3);
    second_values.push_back(1);
    second_values.push_back(2);
    second_values.push_back(3);
    check_result(first_values, second_values);
    auto vector_result = m1une::string::longest_common_subsequence(first_values, second_values);
    assert(vector_result.values_from_first(first_values) == vector_result.values_from_second(second_values));
}

void test_randomized() {
    std::uint64_t state = 20260709;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; trial++) {
        int n = int(random() % 30);
        int m = int(random() % 30);
        std::string first(n, 'a');
        std::string second(m, 'a');
        for (char& character : first) character = char('a' + random() % 5);
        for (char& character : second) character = char('a' + random() % 5);
        check_result(first, second);

        std::vector<int> first_values(n);
        std::vector<int> second_values(m);
        for (int& value : first_values) value = int(random() % 7) - 3;
        for (int& value : second_values) value = int(random() % 7) - 3;
        check_result(first_values, second_values);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    while (q--) {
        std::string first, second;
        std::cin >> first >> second;
        std::cout << m1une::string::longest_common_subsequence_length(first, second) << '\n';
    }
}
