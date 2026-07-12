#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"

#include "../../string/runs.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool has_period(const std::string& text, int left, int right, int period) {
    for (int i = left; i + period < right; i++) {
        if (text[i] != text[i + period]) return false;
    }
    return true;
}

std::vector<m1une::string::Run> naive_runs(const std::string& text) {
    int n = int(text.size());
    std::vector<m1une::string::Run> result;
    for (int left = 0; left < n; left++) {
        for (int right = left + 2; right <= n; right++) {
            int minimum_period = right - left;
            for (int period = 1; period < right - left; period++) {
                if (has_period(text, left, right, period)) {
                    minimum_period = period;
                    break;
                }
            }
            if (right - left < 2 * minimum_period) continue;
            if (
                left > 0 &&
                text[left - 1] == text[left - 1 + minimum_period]
            ) {
                continue;
            }
            if (
                right < n &&
                text[right] == text[right - minimum_period]
            ) {
                continue;
            }
            result.push_back(m1une::string::Run{minimum_period, left, right});
        }
    }
    std::sort(result.begin(), result.end(), [](const auto& first, const auto& second) {
        if (first.period != second.period) return first.period < second.period;
        if (first.left != second.left) return first.left < second.left;
        return first.right < second.right;
    });
    return result;
}

void test_edge_cases() {
    std::string empty;
    assert(m1une::string::enumerate_runs(empty).empty());
    assert(m1une::string::enumerate_runs(std::string("a")).empty());

    std::vector<m1une::string::Run> equal_expected;
    equal_expected.push_back(m1une::string::Run{1, 0, 5});
    assert(m1une::string::enumerate_runs(std::string("aaaaa")) == equal_expected);

    std::vector<int> values;
    values.push_back(4);
    values.push_back(7);
    values.push_back(4);
    values.push_back(7);
    values.push_back(4);
    std::vector<m1une::string::Run> vector_expected;
    vector_expected.push_back(m1une::string::Run{2, 0, 5});
    assert(m1une::string::enumerate_runs(values) == vector_expected);

    std::vector<bool> bits(6, false);
    bits[1] = true;
    bits[3] = true;
    bits[5] = true;
    std::vector<m1une::string::Run> bit_expected;
    bit_expected.push_back(m1une::string::Run{2, 0, 6});
    assert(m1une::string::enumerate_runs(bits) == bit_expected);
}

void test_randomized() {
    std::uint64_t state = 20260713;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; trial++) {
        int n = int(random() % 14);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 4);
        assert(m1une::string::enumerate_runs(text) == naive_runs(text));
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;
    std::vector<m1une::string::Run> runs = m1une::string::enumerate_runs(text);
    std::cout << runs.size() << '\n';
    for (const auto& run : runs) {
        std::cout << run.period << ' ' << run.left << ' ' << run.right << '\n';
    }
}
