#ifndef M1UNE_ALGO_ENUMERATION_SEGTREE_RANGE_HPP
#define M1UNE_ALGO_ENUMERATION_SEGTREE_RANGE_HPP 1

#include <bit>
#include <cassert>
#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace algo {

// Splits [left, right) into maximal segment-tree ranges from left to right.
template <std::integral Int>
requires(!std::same_as<std::remove_cv_t<Int>, bool>)
std::vector<std::pair<Int, Int>> split_segtree_range(Int left, Int right) {
    if constexpr (std::signed_integral<Int>) assert(Int(0) <= left);
    assert(left <= right);
    if constexpr (std::signed_integral<Int>) {
        if (left < 0) return {};
    }
    if (right < left) return {};

    using UInt = std::make_unsigned_t<Int>;
    UInt position = static_cast<UInt>(left);
    const UInt end = static_cast<UInt>(right);
    std::vector<std::pair<Int, Int>> result;
    if (position == end) return result;
    result.reserve(2 * std::bit_width(end - position));

    while (position < end) {
        UInt length = std::bit_floor(end - position);
        if (position != 0) {
            const UInt alignment = position & (~position + UInt(1));
            if (alignment < length) length = alignment;
        }
        const UInt next = position + length;
        result.emplace_back(
            static_cast<Int>(position), static_cast<Int>(next)
        );
        position = next;
    }
    return result;
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_ENUMERATION_SEGTREE_RANGE_HPP
