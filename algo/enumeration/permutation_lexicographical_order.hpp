#ifndef M1UNE_ALGO_ENUMERATION_PERMUTATION_LEXICOGRAPHICAL_ORDER_HPP
#define M1UNE_ALGO_ENUMERATION_PERMUTATION_LEXICOGRAPHICAL_ORDER_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace algo {

namespace internal {

struct PermutationOrderFenwick {
    std::vector<int> data;

    explicit PermutationOrderFenwick(int size) : data(size + 1) {}

    void add(int index, int value) {
        for (index++; index < int(data.size()); index += index & -index) {
            data[index] += value;
        }
    }

    int prefix_sum(int right) const {
        int result = 0;
        for (; 0 < right; right -= right & -right) result += data[right];
        return result;
    }

    int kth(int order) const {
        int index = 0;
        int accumulated = 0;
        int step = 1;
        while (step < int(data.size())) step <<= 1;
        for (; 0 < step; step >>= 1) {
            const int next = index + step;
            if (next < int(data.size()) &&
                accumulated + data[next] <= order) {
                index = next;
                accumulated += data[next];
            }
        }
        return index;
    }
};

}  // namespace internal

// Returns the zero-based lexicographical rank of a permutation of [0, n).
// Returns nullopt when the sequence is invalid or the rank does not fit in UInt.
template <
    std::unsigned_integral UInt = std::uint64_t,
    class Permutation
>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
std::optional<UInt> checked_permutation_lexicographical_rank(
    const Permutation& permutation
) {
    const int size = int(permutation.size());
    internal::PermutationOrderFenwick fenwick(size);
    for (int value = 0; value < size; value++) fenwick.add(value, 1);

    UInt rank = 0;
    constexpr UInt limit = std::numeric_limits<UInt>::max();
    for (int index = 0; index < size; index++) {
        const auto& value_reference = permutation[index];
        using Value = std::remove_cvref_t<decltype(value_reference)>;
        static_assert(std::integral<Value>);
        static_assert(!std::same_as<Value, bool>);

        if (std::cmp_less(value_reference, 0) ||
            std::cmp_greater_equal(value_reference, size)) {
            return std::nullopt;
        }
        const int value = int(value_reference);
        if (fenwick.prefix_sum(value + 1) == fenwick.prefix_sum(value)) {
            return std::nullopt;
        }

        const std::uintmax_t smaller = fenwick.prefix_sum(value);
        const std::uintmax_t remaining = size - index;
        if (smaller > std::uintmax_t(limit) ||
            std::uintmax_t(rank) >
                (std::uintmax_t(limit) - smaller) / remaining) {
            return std::nullopt;
        }
        rank = UInt(std::uintmax_t(rank) * remaining + smaller);
        fenwick.add(value, -1);
    }
    return rank;
}

// Every value must occur exactly once in [0, n), and the rank must fit in UInt.
template <
    std::unsigned_integral UInt = std::uint64_t,
    class Permutation
>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
UInt permutation_lexicographical_rank(const Permutation& permutation) {
    const std::optional<UInt> result =
        checked_permutation_lexicographical_rank<UInt>(permutation);
    assert(result.has_value());
    return result.value_or(UInt(0));
}

// Returns the permutation of [0, size) with the given zero-based rank.
// Returns nullopt when size is negative or rank is at least size factorial.
template <std::unsigned_integral UInt = std::uint64_t>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
std::optional<std::vector<int>> checked_kth_lexicographical_permutation(
    int size,
    UInt rank
) {
    if (size < 0) return std::nullopt;

    std::vector<int> lehmer_code(size);
    UInt remaining_rank = rank;
    for (int base = 1; base <= size && remaining_rank != 0; base++) {
        lehmer_code[size - base] = int(remaining_rank % UInt(base));
        remaining_rank /= UInt(base);
    }
    if (remaining_rank != 0) return std::nullopt;

    internal::PermutationOrderFenwick fenwick(size);
    for (int value = 0; value < size; value++) fenwick.add(value, 1);

    std::vector<int> permutation(size);
    for (int index = 0; index < size; index++) {
        const int value = fenwick.kth(lehmer_code[index]);
        permutation[index] = value;
        fenwick.add(value, -1);
    }
    return permutation;
}

// Rank must be less than size factorial.
template <std::unsigned_integral UInt = std::uint64_t>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
std::vector<int> kth_lexicographical_permutation(int size, UInt rank) {
    std::optional<std::vector<int>> result =
        checked_kth_lexicographical_permutation(size, rank);
    assert(result.has_value());
    return result.value_or(std::vector<int>());
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_ENUMERATION_PERMUTATION_LEXICOGRAPHICAL_ORDER_HPP
