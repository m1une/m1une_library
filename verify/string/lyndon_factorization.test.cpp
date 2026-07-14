#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"

#include "../../string/lyndon_factorization.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <string>
#include <utility>
#include <vector>

namespace {

bool is_strictly_smaller_rotation(const std::string& word, int offset) {
    int n = int(word.size());
    for (int i = 0; i < n; i++) {
        char a = word[i];
        char b = word[(offset + i) % n];
        if (a != b) return a < b;
    }
    return false;
}

bool is_lyndon_word(const std::string& word) {
    if (word.empty()) return false;
    for (int offset = 1; offset < int(word.size()); offset++) {
        if (!is_strictly_smaller_rotation(word, offset)) return false;
    }
    return true;
}

std::vector<std::vector<int>> enumerate_factorizations(int n) {
    std::vector<std::vector<int>> result;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        std::vector<int> boundaries;
        boundaries.push_back(0);
        for (int i = 1; i < n; i++) {
            if ((mask >> (i - 1)) & 1) boundaries.push_back(i);
        }
        boundaries.push_back(n);
        result.push_back(boundaries);
    }
    return result;
}

std::vector<int> naive_lyndon_factor_boundaries(const std::string& text) {
    int n = int(text.size());
    if (n == 0) return std::vector<int>(1, 0);

    std::vector<int> best;
    for (const std::vector<int>& boundaries : enumerate_factorizations(n)) {
        bool valid = true;
        std::vector<std::string> factors;
        for (int i = 0; i + 1 < int(boundaries.size()); i++) {
            std::string word =
                text.substr(boundaries[i], boundaries[i + 1] - boundaries[i]);
            if (!is_lyndon_word(word)) {
                valid = false;
                break;
            }
            factors.push_back(word);
        }
        for (int i = 0; i + 1 < int(factors.size()); i++) {
            if (factors[i] < factors[i + 1]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            assert(best.empty());
            best = boundaries;
        }
    }
    assert(!best.empty());
    return best;
}

std::string cyclic_shift(const std::string& text, int start) {
    return text.substr(start) + text.substr(0, start);
}

int naive_minimum_cyclic_shift(const std::string& text) {
    int n = int(text.size());
    if (n == 0) return 0;

    int best = 0;
    for (int start = 1; start < n; start++) {
        if (cyclic_shift(text, start) < cyclic_shift(text, best)) {
            best = start;
        }
    }
    return best;
}

void test_edge_cases() {
    std::string empty;
    assert(m1une::string::lyndon_factor_boundaries(empty) == std::vector<int>(1, 0));
    assert(m1une::string::lyndon_factorization(empty).empty());
    assert(m1une::string::minimum_cyclic_shift(empty) == 0);

    assert(
        m1une::string::lyndon_factor_boundaries(std::string("aaaa")) ==
        std::vector<int>({0, 1, 2, 3, 4})
    );
    assert(m1une::string::minimum_cyclic_shift(std::string("aaaa")) == 0);
    assert(m1une::string::minimum_cyclic_shift(std::string("abab")) == 0);
    assert(m1une::string::minimum_cyclic_shift(std::string("banana")) == 5);
    assert(m1une::string::minimum_cyclic_shift(std::string("baca")) == 3);

    std::vector<std::pair<int, int>> expected;
    expected.emplace_back(0, 1);
    expected.emplace_back(1, 3);
    expected.emplace_back(3, 4);
    assert(m1une::string::lyndon_factorization(std::string("baca")) == expected);

    std::vector<int> values;
    values.push_back(2);
    values.push_back(1);
    values.push_back(3);
    values.push_back(1);
    assert(
        m1une::string::lyndon_factor_boundaries(values) ==
        std::vector<int>({0, 1, 3, 4})
    );
    assert(m1une::string::minimum_cyclic_shift(values) == 3);
}

void test_randomized() {
    std::uint64_t state = 20260709;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1200; trial++) {
        int n = int(random() % 10);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 4);

        std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);
        std::vector<int> expected = naive_lyndon_factor_boundaries(text);
        assert(boundaries == expected);
        assert(
            m1une::string::minimum_cyclic_shift(text) ==
            naive_minimum_cyclic_shift(text)
        );

        std::vector<std::pair<int, int>> factors = m1une::string::lyndon_factorization(text);
        assert(int(factors.size()) + 1 == int(boundaries.size()));
        for (int i = 0; i < int(factors.size()); i++) {
            assert(factors[i].first == boundaries[i]);
            assert(factors[i].second == boundaries[i + 1]);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();
    std::string text;
    fast_input >> text;
    std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);
    for (int i = 0; i < int(boundaries.size()); i++) {
        if (i > 0) fast_output << ' ';
        fast_output << boundaries[i];
    }
    fast_output << '\n';
}
