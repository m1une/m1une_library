#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "../../string/longest_common_extension.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <string>
#include <vector>

namespace {

int naive_longest_common_extension(const std::string& text, int i, int j) {
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
    m1une::string::LongestCommonExtension<> empty_extension(empty);
    assert(empty_extension.empty());
    assert(empty_extension.longest_common_extension(0, 0) == 0);
    assert(empty_extension.compare_suffix(0, 0) == 0);
    assert(empty_extension.compare(0, 0, 0, 0) == 0);
    assert(empty_extension.suffix_array().empty());
    assert(empty_extension.rank().empty());
    assert(empty_extension.lcp_array().empty());

    std::string text = "banana";
    m1une::string::LongestCommonExtension<> extension(text);
    assert(extension.size() == 6);
    assert(extension.sequence() == text);
    assert(extension.longest_common_extension(1, 3) == 3);
    assert(extension.longest_common_extension(2, 4) == 2);
    assert(extension.longest_common_extension(0, 2) == 0);
    assert(extension.longest_common_extension(6, 1) == 0);
    assert(extension.longest_common_extension(2, 2) == 4);
    assert(extension.longest_common_extension(1, 3, 2) == 2);
    assert(extension.lcp(1, 3) == 3);
    assert(extension(1, 3) == 3);
    assert(extension.compare_suffix(1, 3) == 1);
    assert(extension.compare_suffix(3, 1) == -1);
    assert(extension.compare(1, 4, 3, 6) == 0);
    assert(extension.compare(1, 5, 3, 6) == 1);
    assert(extension.compare(0, 0, 1, 2) == -1);

    std::vector<int> values;
    values.push_back(2);
    values.push_back(1);
    values.push_back(2);
    values.push_back(1);
    values.push_back(2);
    m1une::string::LongestCommonExtension<std::vector<int>> vector_extension(values);
    assert(vector_extension.longest_common_extension(0, 2) == 3);
    assert(vector_extension.longest_common_extension(1, 3) == 2);
    assert(vector_extension.compare(0, 3, 2, 5) == 0);
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
        m1une::string::LongestCommonExtension<> extension(text);

        const std::vector<int>& suffixes = extension.suffix_array();
        const std::vector<int>& rank = extension.rank();
        for (int i = 0; i < n; i++) {
            assert(0 <= suffixes[i] && suffixes[i] < n);
            assert(rank[suffixes[i]] == i);
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                int expected = naive_longest_common_extension(text, i, j);
                assert(extension.longest_common_extension(i, j) == expected);
                int limit = int(random() % (n + 1));
                assert(extension.longest_common_extension(i, j, limit) == std::min(expected, limit));

                std::string suffix_i = text.substr(i);
                std::string suffix_j = text.substr(j);
                assert(extension.compare_suffix(i, j) == sign(suffix_i.compare(suffix_j)));
            }
        }

        for (int query = 0; query < 200; query++) {
            int l1 = int(random() % (n + 1));
            int r1 = l1 + int(random() % (n - l1 + 1));
            int l2 = int(random() % (n + 1));
            int r2 = l2 + int(random() % (n - l2 + 1));
            std::string first = text.substr(l1, r1 - l1);
            std::string second = text.substr(l2, r2 - l2);
            assert(extension.compare(l1, r1, l2, r2) == sign(first.compare(second)));
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
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();
    std::string first, second;
    fast_input >> first >> second;

    int n = int(first.size());
    int m = int(second.size());
    std::vector<int> combined = combine_strings(first, second);
    m1une::string::LongestCommonExtension<std::vector<int>> extension(combined);

    int best_first = 0;
    int best_second = 0;
    int best_length = 0;
    const std::vector<int>& suffixes = extension.suffix_array();
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
        int length = extension.longest_common_extension(a, b);
        length = std::min(length, n - first_pos);
        length = std::min(length, m - second_pos);
        if (length > best_length) {
            best_length = length;
            best_first = first_pos;
            best_second = second_pos;
        }
    }

    fast_output << best_first << ' ' << best_first + best_length << ' '
              << best_second << ' ' << best_second + best_length << '\n';
}
