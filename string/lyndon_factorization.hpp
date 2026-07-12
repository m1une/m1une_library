#ifndef M1UNE_STRING_LYNDON_FACTORIZATION_HPP
#define M1UNE_STRING_LYNDON_FACTORIZATION_HPP 1

#include <utility>
#include <vector>

#include "minimum_rotation.hpp"

namespace m1une {
namespace string {

// Returns boundaries 0 = a[0] < a[1] < ... < a[k] = sequence.size()
// of the Lyndon factorization.
template <class Sequence>
std::vector<int> lyndon_factor_boundaries(const Sequence& sequence) {
    int n = int(sequence.size());
    std::vector<int> boundaries;
    boundaries.push_back(0);

    int i = 0;
    while (i < n) {
        int j = i + 1;
        int k = i;
        while (j < n && !(sequence[j] < sequence[k])) {
            if (sequence[k] < sequence[j]) {
                k = i;
            } else {
                k++;
            }
            j++;
        }

        int length = j - k;
        while (i <= k) {
            i += length;
            boundaries.push_back(i);
        }
    }
    return boundaries;
}

// Returns half-open intervals [left, right) of the Lyndon factorization.
template <class Sequence>
std::vector<std::pair<int, int>> lyndon_factorization(const Sequence& sequence) {
    std::vector<int> boundaries = lyndon_factor_boundaries(sequence);
    std::vector<std::pair<int, int>> factors;
    factors.reserve(boundaries.size() - 1);
    for (int i = 0; i + 1 < int(boundaries.size()); i++) {
        factors.emplace_back(boundaries[i], boundaries[i + 1]);
    }
    return factors;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_LYNDON_FACTORIZATION_HPP
