#ifndef M1UNE_STRING_LONGEST_COMMON_SUBSTRING_HPP
#define M1UNE_STRING_LONGEST_COMMON_SUBSTRING_HPP 1

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

#include "suffix_array.hpp"

namespace m1une {
namespace string {

struct LongestCommonSubstring {
    int first_left = 0;
    int first_right = 0;
    int second_left = 0;
    int second_right = 0;

    int length() const {
        assert(first_right - first_left == second_right - second_left);
        return first_right - first_left;
    }

    bool empty() const {
        return length() == 0;
    }

    std::pair<int, int> first_interval() const {
        return {first_left, first_right};
    }

    std::pair<int, int> second_interval() const {
        return {second_left, second_right};
    }
};

namespace detail {

template <class Sequence>
std::vector<int> compressed_join_with_separator(const Sequence& first, const Sequence& second) {
    using Value = std::remove_cv_t<std::remove_reference_t<decltype(first[0])>>;

    std::vector<Value> values;
    values.reserve(first.size() + second.size());
    for (const auto& value : first) values.push_back(value);
    for (const auto& value : second) values.push_back(value);
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    std::vector<int> joined;
    joined.reserve(first.size() + second.size() + 1);
    for (const auto& value : first) {
        joined.push_back(int(std::lower_bound(values.begin(), values.end(), value) - values.begin()) + 2);
    }
    joined.push_back(1);
    for (const auto& value : second) {
        joined.push_back(int(std::lower_bound(values.begin(), values.end(), value) - values.begin()) + 2);
    }
    return joined;
}

}  // namespace detail

template <class Sequence>
LongestCommonSubstring longest_common_substring(const Sequence& first, const Sequence& second) {
    int n = int(first.size());
    int m = int(second.size());
    std::vector<int> joined = detail::compressed_join_with_separator(first, second);
    std::vector<int> suffixes = suffix_array(joined);
    std::vector<int> lcp = lcp_array(joined, suffixes);

    LongestCommonSubstring result;
    for (int i = 0; i + 1 < int(suffixes.size()); i++) {
        int a = suffixes[i];
        int b = suffixes[i + 1];
        if (a == n || b == n) continue;

        bool a_first = a < n;
        bool b_first = b < n;
        if (a_first == b_first) continue;

        int first_left = a_first ? a : b;
        int second_left = a_first ? b - n - 1 : a - n - 1;
        int length = lcp[i];
        length = std::min(length, n - first_left);
        length = std::min(length, m - second_left);
        if (length > result.length()) {
            result.first_left = first_left;
            result.first_right = first_left + length;
            result.second_left = second_left;
            result.second_right = second_left + length;
        }
    }
    return result;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_LONGEST_COMMON_SUBSTRING_HPP
