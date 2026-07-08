#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "../../string/lce.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

int naive_lce(const std::string& text, int i, int j) {
    int n = int(text.size());
    int result = 0;
    while (i + result < n && j + result < n && text[i + result] == text[j + result]) {
        result++;
    }
    return result;
}

int sign(int value) {
    if (value < 0) return -1;
    if (value > 0) return 1;
    return 0;
}

void test_fixed() {
    std::string empty;
    m1une::string::LCE<> empty_lce(empty);
    assert(empty_lce.empty());
    assert(empty_lce.lce(0, 0) == 0);
    assert(empty_lce.compare_suffix(0, 0) == 0);
    assert(empty_lce.compare(0, 0, 0, 0) == 0);
    assert(empty_lce.suffix_array().empty());
    assert(empty_lce.rank().empty());
    assert(empty_lce.lcp_array().empty());

    std::string text = "banana";
    m1une::string::LCE<> lce(text);
    assert(lce.size() == 6);
    assert(lce.sequence() == text);
    assert(lce.lce(1, 3) == 3);
    assert(lce.lce(2, 4) == 2);
    assert(lce.lce(0, 2) == 0);
    assert(lce.lce(6, 1) == 0);
    assert(lce.lce(2, 2) == 4);
    assert(lce.lce(1, 3, 2) == 2);
    assert(lce.lcp(1, 3) == 3);
    assert(lce(1, 3) == 3);
    assert(lce.compare_suffix(1, 3) == 1);
    assert(lce.compare_suffix(3, 1) == -1);
    assert(lce.compare(1, 4, 3, 6) == 0);
    assert(lce.compare(1, 5, 3, 6) == 1);
    assert(lce.compare(0, 0, 1, 2) == -1);

    std::vector<int> values;
    values.push_back(2);
    values.push_back(1);
    values.push_back(2);
    values.push_back(1);
    values.push_back(2);
    m1une::string::LCE<std::vector<int>> vector_lce(values);
    assert(vector_lce.lce(0, 2) == 3);
    assert(vector_lce.lce(1, 3) == 2);
    assert(vector_lce.compare(0, 3, 2, 5) == 0);
}

void test_randomized() {
    std::uint64_t state = 20240709;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; trial++) {
        int n = int(random() % 50);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 5);
        m1une::string::LCE<> lce(text);

        const std::vector<int>& suffixes = lce.suffix_array();
        const std::vector<int>& rank = lce.rank();
        for (int i = 0; i < n; i++) {
            assert(0 <= suffixes[i] && suffixes[i] < n);
            assert(rank[suffixes[i]] == i);
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                int expected = naive_lce(text, i, j);
                assert(lce.lce(i, j) == expected);
                int limit = int(random() % (n + 1));
                assert(lce.lce(i, j, limit) == std::min(expected, limit));

                std::string suffix_i = text.substr(i);
                std::string suffix_j = text.substr(j);
                assert(lce.compare_suffix(i, j) == sign(suffix_i.compare(suffix_j)));
            }
        }

        for (int query = 0; query < 200; query++) {
            int l1 = int(random() % (n + 1));
            int r1 = l1 + int(random() % (n - l1 + 1));
            int l2 = int(random() % (n + 1));
            int r2 = l2 + int(random() % (n - l2 + 1));
            std::string first = text.substr(l1, r1 - l1);
            std::string second = text.substr(l2, r2 - l2);
            assert(lce.compare(l1, r1, l2, r2) == sign(first.compare(second)));
        }
    }
}

std::vector<int> combine_strings(const std::string& first, const std::string& second) {
    std::vector<int> combined;
    combined.reserve(first.size() + second.size() + 1);
    for (unsigned char character : first) combined.push_back(int(character) + 2);
    combined.push_back(1);
    for (unsigned char character : second) combined.push_back(int(character) + 2);
    return combined;
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string first, second;
    std::cin >> first >> second;

    int n = int(first.size());
    int m = int(second.size());
    std::vector<int> combined = combine_strings(first, second);
    m1une::string::LCE<std::vector<int>> lce(combined);

    int best_first = 0;
    int best_second = 0;
    int best_length = 0;
    const std::vector<int>& suffixes = lce.suffix_array();
    for (int i = 0; i + 1 < int(suffixes.size()); i++) {
        int a = suffixes[i];
        int b = suffixes[i + 1];
        bool a_first = a < n;
        bool b_first = b < n;
        bool a_second = n < a;
        bool b_second = n < b;
        if (a_first == b_first || a_second == b_second) continue;
        if ((!a_first && !a_second) || (!b_first && !b_second)) continue;

        int first_pos = a_first ? a : b;
        int second_pos = a_first ? b - n - 1 : a - n - 1;
        int length = lce.lce(a, b);
        length = std::min(length, n - first_pos);
        length = std::min(length, m - second_pos);
        if (length > best_length) {
            best_length = length;
            best_first = first_pos;
            best_second = second_pos;
        }
    }

    std::cout << best_first << ' ' << best_first + best_length << ' '
              << best_second << ' ' << best_second + best_length << '\n';
}
