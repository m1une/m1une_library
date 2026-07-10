#ifndef M1UNE_ALGO_SEQUENCE_NUMBER_OF_SUBSEQUENCES_HPP
#define M1UNE_ALGO_SEQUENCE_NUMBER_OF_SUBSEQUENCES_HPP 1

#include <algorithm>
#include <vector>

namespace m1une {
namespace algo {

// Returns the number of distinct nonempty subsequences.
template <class Mint, class T>
Mint number_of_distinct_subsequences(const std::vector<T>& values) {
    std::vector<T> compressed = values;
    std::sort(compressed.begin(), compressed.end());
    compressed.erase(
        std::unique(compressed.begin(), compressed.end()),
        compressed.end()
    );

    std::vector<Mint> previous_total(compressed.size(), Mint(0));
    Mint total = 1;
    for (const T& value : values) {
        int rank = int(
            std::lower_bound(
                compressed.begin(),
                compressed.end(),
                value
            ) - compressed.begin()
        );
        Mint old_total = total;
        total = total + total - previous_total[rank];
        previous_total[rank] = old_total;
    }
    return total - Mint(1);
}

template <class Mint, class T>
Mint number_of_subsequences(const std::vector<T>& values) {
    return number_of_distinct_subsequences<Mint>(values);
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_SEQUENCE_NUMBER_OF_SUBSEQUENCES_HPP
