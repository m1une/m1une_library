#ifndef M1UNE_STRING_WILDCARD_PATTERN_MATCHING_HPP
#define M1UNE_STRING_WILDCARD_PATTERN_MATCHING_HPP 1

#include <array>
#include <string>
#include <vector>

#include "../math/fps/convolution.hpp"

namespace m1une {
namespace string {

namespace internal {

template <class Mint>
std::vector<Mint> wildcard_mismatch_scores(
    const std::string& text,
    const std::string& pattern,
    char wildcard
) {
    int n = int(text.size());
    int m = int(pattern.size());
    std::array<std::vector<Mint>, 3> text_powers;
    std::array<std::vector<Mint>, 3> pattern_powers;
    for (auto& powers : text_powers) powers.resize(n);
    for (auto& powers : pattern_powers) powers.resize(m);

    auto encode = [wildcard](char character) {
        if (character == wildcard) return 0;
        return int(static_cast<unsigned char>(character)) + 1;
    };
    for (int i = 0; i < n; i++) {
        Mint value = encode(text[i]);
        text_powers[0][i] = value;
        text_powers[1][i] = value * value;
        text_powers[2][i] = value * value * value;
    }
    for (int i = 0; i < m; i++) {
        Mint value = encode(pattern[m - 1 - i]);
        pattern_powers[0][i] = value;
        pattern_powers[1][i] = value * value;
        pattern_powers[2][i] = value * value * value;
    }

    std::vector<Mint> scores(n - m + 1);
    for (int power = 0; power < 3; power++) {
        std::vector<Mint> product = fps::convolution(
            text_powers[power],
            pattern_powers[2 - power]
        );
        Mint multiplier = power == 1 ? Mint(-2) : Mint(1);
        for (int start = 0; start <= n - m; start++) {
            scores[start] += multiplier * product[start + m - 1];
        }
    }
    return scores;
}

}  // namespace internal

// result[i] is true exactly when pattern matches text[i, i + pattern.size()).
// The wildcard character matches every character on either side.
inline std::vector<bool> wildcard_pattern_matching(
    const std::string& text,
    const std::string& pattern,
    char wildcard = '*'
) {
    int n = int(text.size());
    int m = int(pattern.size());
    if (m == 0) return std::vector<bool>(n + 1, true);
    if (n < m) return {};

    using Mint1 = math::ModInt<469762049>;
    using Mint2 = math::ModInt<754974721>;
    std::vector<Mint1> first_scores =
        internal::wildcard_mismatch_scores<Mint1>(text, pattern, wildcard);
    std::vector<Mint2> second_scores =
        internal::wildcard_mismatch_scores<Mint2>(text, pattern, wildcard);

    std::vector<bool> result(n - m + 1, false);
    for (int start = 0; start <= n - m; start++) {
        result[start] = first_scores[start].val() == 0 &&
                        second_scores[start].val() == 0;
    }
    return result;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_WILDCARD_PATTERN_MATCHING_HPP
