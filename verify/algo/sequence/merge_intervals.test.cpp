#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <random>
#include <utility>
#include <vector>

#include "../../../algo/sequence/merge_intervals.hpp"
#include "../../../utilities/fast_io.hpp"

struct LessOnly {
    int value;

    explicit LessOnly(int value) : value(value) {}

    friend bool operator<(const LessOnly& lhs, const LessOnly& rhs) {
        return lhs.value < rhs.value;
    }
};

void test_examples() {
    using Interval = std::pair<int, int>;

    std::vector<Interval> intervals;
    intervals.emplace_back(5, 8);
    intervals.emplace_back(1, 3);
    intervals.emplace_back(3, 6);
    intervals.emplace_back(2, 4);
    intervals.emplace_back(9, 9);
    intervals.emplace_back(-2, 0);

    std::vector<Interval> expected;
    expected.emplace_back(-2, 0);
    expected.emplace_back(1, 8);
    assert(m1une::algo::merge_intervals(intervals) == expected);
    assert(intervals.size() == 6);

    assert(m1une::algo::merge_intervals(std::vector<Interval>()).empty());
    assert(m1une::algo::merge_intervals(
        std::vector<Interval>{Interval(4, 4)}
    ).empty());

    std::vector<std::pair<LessOnly, LessOnly>> less_only;
    less_only.emplace_back(LessOnly(2), LessOnly(5));
    less_only.emplace_back(LessOnly(1), LessOnly(3));
    auto less_only_merged = m1une::algo::merge_intervals(std::move(less_only));
    assert(less_only_merged.size() == 1);
    assert(less_only_merged[0].first.value == 1);
    assert(less_only_merged[0].second.value == 5);
}

void test_random() {
    constexpr int minimum = -20;
    constexpr int maximum = 20;
    std::mt19937 random(123456789);

    for (int iteration = 0; iteration < 5000; ++iteration) {
        const int interval_count = int(random() % 30);
        std::vector<std::pair<int, int>> intervals;
        std::vector<bool> covered(maximum - minimum, false);

        for (int index = 0; index < interval_count; ++index) {
            int left = minimum + int(random() % (maximum - minimum + 1));
            int right = minimum + int(random() % (maximum - minimum + 1));
            if (right < left) std::swap(left, right);
            intervals.emplace_back(left, right);
            for (int point = left; point < right; ++point) {
                covered[point - minimum] = true;
            }
        }

        const auto merged = m1une::algo::merge_intervals(intervals);
        for (int index = 0; index < int(merged.size()); ++index) {
            const auto [left, right] = merged[index];
            assert(left < right);
            if (index > 0) assert(merged[index - 1].second < left);
        }

        std::vector<bool> merged_covered(maximum - minimum, false);
        for (const auto& [left, right] : merged) {
            for (int point = left; point < right; ++point) {
                merged_covered[point - minimum] = true;
            }
        }
        assert(merged_covered == covered);
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_examples();
    test_random();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
