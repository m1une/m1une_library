#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "../../string/longest_common_substring.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

template <class Sequence>
bool equal_substring(
    const Sequence& first,
    int first_left,
    const Sequence& second,
    int second_left,
    int length
) {
    for (int i = 0; i < length; i++) {
        if (first[first_left + i] != second[second_left + i]) return false;
    }
    return true;
}

template <class Sequence>
int naive_length(const Sequence& first, const Sequence& second) {
    int n = int(first.size());
    int m = int(second.size());
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int length = 0;
            while (
                i + length < n &&
                j + length < m &&
                first[i + length] == second[j + length]
            ) {
                length++;
            }
            result = std::max(result, length);
        }
    }
    return result;
}

template <class Sequence>
void check_result(const Sequence& first, const Sequence& second) {
    auto result = m1une::string::longest_common_substring(first, second);
    int n = int(first.size());
    int m = int(second.size());
    int length = result.length();
    assert(0 <= result.first_left && result.first_left <= result.first_right && result.first_right <= n);
    assert(0 <= result.second_left && result.second_left <= result.second_right && result.second_right <= m);
    assert(result.second_right - result.second_left == length);
    assert(equal_substring(first, result.first_left, second, result.second_left, length));
    assert(length == naive_length(first, second));
    if (length == 0) {
        assert(result.first_left == 0);
        assert(result.first_right == 0);
        assert(result.second_left == 0);
        assert(result.second_right == 0);
        assert(result.empty());
    }
}

void test_fixed() {
    check_result(std::string(), std::string());
    check_result(std::string("abc"), std::string());
    check_result(std::string(), std::string("abc"));
    check_result(std::string("abc"), std::string("def"));
    check_result(std::string("xabxac"), std::string("abcabxabcd"));
    check_result(std::string("banana"), std::string("ananas"));

    auto result = m1une::string::longest_common_substring(
        std::string("xabxac"),
        std::string("abcabxabcd")
    );
    assert(result.length() == 4);
    assert((result.first_interval() == std::make_pair(result.first_left, result.first_right)));
    assert((result.second_interval() == std::make_pair(result.second_left, result.second_right)));

    std::vector<int> first;
    first.push_back(3);
    first.push_back(-1);
    first.push_back(4);
    first.push_back(-1);
    first.push_back(5);
    std::vector<int> second;
    second.push_back(9);
    second.push_back(4);
    second.push_back(-1);
    second.push_back(5);
    second.push_back(9);
    check_result(first, second);
    auto vector_result = m1une::string::longest_common_substring(first, second);
    assert(vector_result.length() == 3);
}

void test_randomized() {
    std::uint64_t state = 20260709;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; trial++) {
        int n = int(random() % 35);
        int m = int(random() % 35);
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

    std::string first, second;
    std::cin >> first >> second;

    auto result = m1une::string::longest_common_substring(first, second);
    std::cout << result.first_left << ' ' << result.first_right << ' '
              << result.second_left << ' ' << result.second_right << '\n';
}
