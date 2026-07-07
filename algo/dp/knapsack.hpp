#ifndef M1UNE_ALGO_DP_KNAPSACK_HPP
#define M1UNE_ALGO_DP_KNAPSACK_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <deque>
#include <limits>
#include <vector>

namespace m1une {
namespace algo {

inline std::vector<char> subset_sum_reachable(const std::vector<int>& weights, int limit) {
    assert(0 <= limit);
    using Word = unsigned long long;
    constexpr int word_bits = std::numeric_limits<Word>::digits;

    const std::size_t bit_count = std::size_t(limit) + 1;
    std::vector<Word> bits((bit_count + word_bits - 1) / word_bits, Word(0));
    bits[0] = Word(1);

    auto trim = [&]() {
        const int extra = int(bit_count % word_bits);
        if (extra != 0) {
            bits.back() &= (Word(1) << extra) - Word(1);
        }
    };

    for (int weight : weights) {
        assert(0 <= weight);
        if (weight == 0 || limit < weight) continue;

        const std::size_t word_shift = std::size_t(weight / word_bits);
        const int bit_shift = weight % word_bits;
        for (std::size_t i = bits.size() - word_shift; i-- > 0;) {
            const Word source = bits[i];
            if (source == Word(0)) continue;
            const std::size_t target = i + word_shift;
            bits[target] |= source << bit_shift;
            if (bit_shift != 0 && target + 1 < bits.size()) {
                bits[target + 1] |= source >> (word_bits - bit_shift);
            }
        }
        trim();
    }

    std::vector<char> reachable(std::size_t(limit) + 1, 0);
    for (int sum = 0; sum <= limit; ++sum) {
        reachable[sum] = char((bits[std::size_t(sum / word_bits)] >> (sum % word_bits)) & Word(1));
    }
    return reachable;
}

template <typename Value = long long>
std::vector<Value> zero_one_knapsack_max_value(
    const std::vector<int>& weights,
    const std::vector<Value>& values,
    int capacity,
    Value neg_inf = std::numeric_limits<Value>::lowest() / Value(4)
) {
    assert(weights.size() == values.size());
    assert(0 <= capacity);

    std::vector<Value> dp(std::size_t(capacity) + 1, neg_inf);
    dp[0] = Value{};
    for (std::size_t item = 0; item < weights.size(); ++item) {
        const int weight = weights[item];
        assert(0 <= weight);
        for (int current = capacity; weight <= current; --current) {
            if (dp[current - weight] == neg_inf) continue;
            dp[current] = std::max(dp[current], dp[current - weight] + values[item]);
        }
    }

    for (int current = 1; current <= capacity; ++current) {
        dp[current] = std::max(dp[current], dp[current - 1]);
    }
    return dp;
}

template <typename Value = long long>
std::vector<Value> bounded_knapsack_max_value(
    const std::vector<int>& weights,
    const std::vector<Value>& values,
    const std::vector<int>& counts,
    int capacity,
    Value neg_inf = std::numeric_limits<Value>::lowest() / Value(4)
) {
    assert(weights.size() == values.size());
    assert(weights.size() == counts.size());
    assert(0 <= capacity);

    std::vector<Value> dp(std::size_t(capacity) + 1, neg_inf);
    dp[0] = Value{};

    for (std::size_t item = 0; item < weights.size(); ++item) {
        const int weight = weights[item];
        const Value value = values[item];
        const int count = counts[item];
        assert(0 <= weight);
        assert(0 <= count);
        if (count == 0) continue;

        if (weight == 0) {
            if (Value{} < value) {
                const Value gain = value * Value(count);
                for (Value& current : dp) {
                    if (current != neg_inf) current += gain;
                }
            }
            continue;
        }

        std::vector<Value> next = dp;
        for (int residue = 0; residue < weight && residue <= capacity; ++residue) {
            std::deque<int> indices;
            std::deque<Value> bases;
            int k = 0;
            for (int current = residue; current <= capacity; current += weight, ++k) {
                if (dp[current] != neg_inf) {
                    const Value base = dp[current] - Value(k) * value;
                    while (!bases.empty() && bases.back() <= base) {
                        bases.pop_back();
                        indices.pop_back();
                    }
                    bases.push_back(base);
                    indices.push_back(k);
                }

                while (!indices.empty() && indices.front() < k - count) {
                    indices.pop_front();
                    bases.pop_front();
                }
                if (!bases.empty()) {
                    next[current] = std::max(next[current], bases.front() + Value(k) * value);
                }
            }
        }
        dp.swap(next);
    }

    for (int current = 1; current <= capacity; ++current) {
        dp[current] = std::max(dp[current], dp[current - 1]);
    }
    return dp;
}

template <typename Weight = long long>
std::vector<Weight> zero_one_knapsack_min_weight_for_value(
    const std::vector<Weight>& weights,
    const std::vector<int>& values,
    int value_limit,
    Weight inf = std::numeric_limits<Weight>::max() / Weight(4)
) {
    assert(weights.size() == values.size());
    assert(0 <= value_limit);

    std::vector<Weight> dp(std::size_t(value_limit) + 1, inf);
    dp[0] = Weight{};
    for (std::size_t item = 0; item < weights.size(); ++item) {
        assert(Weight{} <= weights[item]);
        assert(0 <= values[item]);
        for (int value = value_limit; values[item] <= value; --value) {
            if (dp[value - values[item]] == inf) continue;
            dp[value] = std::min(dp[value], dp[value - values[item]] + weights[item]);
        }
    }
    return dp;
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_DP_KNAPSACK_HPP
