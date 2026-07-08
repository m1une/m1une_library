#ifndef M1UNE_STRING_LONGEST_COMMON_SUBSEQUENCE_HPP
#define M1UNE_STRING_LONGEST_COMMON_SUBSEQUENCE_HPP 1

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

struct LongestCommonSubsequence {
    std::vector<std::pair<int, int>> matches;

    int length() const {
        return int(matches.size());
    }

    bool empty() const {
        return matches.empty();
    }

    std::vector<int> first_indices() const {
        std::vector<int> result;
        result.reserve(matches.size());
        for (auto [i, j] : matches) {
            (void)j;
            result.push_back(i);
        }
        return result;
    }

    std::vector<int> second_indices() const {
        std::vector<int> result;
        result.reserve(matches.size());
        for (auto [i, j] : matches) {
            (void)i;
            result.push_back(j);
        }
        return result;
    }

    template <class Sequence>
    std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const Sequence&>()[0])>>>
    values_from_first(const Sequence& first) const {
        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const Sequence&>()[0])>>;
        std::vector<Value> result;
        result.reserve(matches.size());
        for (auto [i, j] : matches) {
            (void)j;
            result.push_back(first[i]);
        }
        return result;
    }

    template <class Sequence>
    std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const Sequence&>()[0])>>>
    values_from_second(const Sequence& second) const {
        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const Sequence&>()[0])>>;
        std::vector<Value> result;
        result.reserve(matches.size());
        for (auto [i, j] : matches) {
            (void)i;
            result.push_back(second[j]);
        }
        return result;
    }
};

template <class FirstSequence, class SecondSequence>
int longest_common_subsequence_length(const FirstSequence& first, const SecondSequence& second) {
    int n = int(first.size());
    int m = int(second.size());
    if (m <= n) {
        std::vector<int> dp(m + 1, 0);
        for (int i = 0; i < n; i++) {
            int diagonal = 0;
            for (int j = 0; j < m; j++) {
                int up = dp[j + 1];
                if (first[i] == second[j]) {
                    dp[j + 1] = diagonal + 1;
                } else {
                    dp[j + 1] = std::max(dp[j + 1], dp[j]);
                }
                diagonal = up;
            }
        }
        return dp[m];
    } else {
        std::vector<int> dp(n + 1, 0);
        for (int j = 0; j < m; j++) {
            int diagonal = 0;
            for (int i = 0; i < n; i++) {
                int up = dp[i + 1];
                if (first[i] == second[j]) {
                    dp[i + 1] = diagonal + 1;
                } else {
                    dp[i + 1] = std::max(dp[i + 1], dp[i]);
                }
                diagonal = up;
            }
        }
        return dp[n];
    }
}

template <class FirstSequence, class SecondSequence>
LongestCommonSubsequence longest_common_subsequence(
    const FirstSequence& first,
    const SecondSequence& second
) {
    int n = int(first.size());
    int m = int(second.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (first[i] == second[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    LongestCommonSubsequence result;
    result.matches.reserve(dp[n][m]);
    int i = n;
    int j = m;
    while (i > 0 && j > 0) {
        if (first[i - 1] == second[j - 1]) {
            result.matches.emplace_back(i - 1, j - 1);
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    std::reverse(result.matches.begin(), result.matches.end());
    return result;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_LONGEST_COMMON_SUBSEQUENCE_HPP
