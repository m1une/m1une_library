#define PROBLEM "https://judge.yosupo.jp/problem/wildcard_pattern_matching"

#include "../../string/wildcard_pattern_matching.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <string>
#include <vector>

namespace {

std::vector<bool> naive_matching(
    const std::string& text,
    const std::string& pattern,
    char wildcard = '*'
) {
    int n = int(text.size());
    int m = int(pattern.size());
    if (n < m) return {};
    std::vector<bool> result(n - m + 1, true);
    for (int start = 0; start <= n - m; start++) {
        for (int i = 0; i < m; i++) {
            if (
                text[start + i] != wildcard &&
                pattern[i] != wildcard &&
                text[start + i] != pattern[i]
            ) {
                result[start] = false;
                break;
            }
        }
    }
    return result;
}

void test_edge_cases() {
    assert(
        m1une::string::wildcard_pattern_matching(std::string(), std::string()) ==
        std::vector<bool>(1, true)
    );
    assert(
        m1une::string::wildcard_pattern_matching(std::string("abc"), std::string()) ==
        std::vector<bool>(4, true)
    );
    assert(
        m1une::string::wildcard_pattern_matching(std::string("ab"), std::string("abc")).empty()
    );
    assert(
        m1une::string::wildcard_pattern_matching(std::string("abc"), std::string("***")) ==
        std::vector<bool>(1, true)
    );
    assert(
        m1une::string::wildcard_pattern_matching(std::string("***"), std::string("abc")) ==
        std::vector<bool>(1, true)
    );
    assert(
        m1une::string::wildcard_pattern_matching(
            std::string("abcxabc"),
            std::string("a?c"),
            '?'
        ) == std::vector<bool>({true, false, false, false, true})
    );
}

void test_randomized() {
    std::uint64_t state = 20260713;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int n = int(random() % 80);
        int m = int(random() % 90);
        std::string text(n, 'a');
        std::string pattern(m, 'a');
        for (char& character : text) {
            int value = int(random() % 6);
            character = value == 5 ? '*' : char('a' + value);
        }
        for (char& character : pattern) {
            int value = int(random() % 6);
            character = value == 5 ? '*' : char('a' + value);
        }
        assert(
            m1une::string::wildcard_pattern_matching(text, pattern) ==
            naive_matching(text, pattern)
        );
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();
    std::string text, pattern;
    fast_input >> text >> pattern;
    std::vector<bool> matches =
        m1une::string::wildcard_pattern_matching(text, pattern);
    for (bool matches_here : matches) fast_output << int(matches_here);
    fast_output << '\n';
}
