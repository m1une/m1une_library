#ifndef M1UNE_ALGO_SEQUENCE_MEX_HPP
#define M1UNE_ALGO_SEQUENCE_MEX_HPP 1

#include <cassert>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <vector>

namespace m1une {
namespace algo {

// Returns the smallest nonnegative integer absent from values.
template <class T>
int mex(const std::vector<T>& values) {
    static_assert(
        std::is_integral_v<T> && sizeof(T) <= sizeof(std::uintmax_t),
        "mex requires standard integral values"
    );
    assert(values.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()));
    const int n = int(values.size());
    std::vector<unsigned char> present(n, 0);
    for (T value : values) {
        if constexpr (std::is_signed_v<T>) {
            if (value < 0) continue;
        }
        if (static_cast<std::uintmax_t>(value) < static_cast<std::uintmax_t>(n)) {
            present[int(value)] = 1;
        }
    }
    int answer = 0;
    while (answer < n && present[answer]) ++answer;
    return answer;
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_SEQUENCE_MEX_HPP
