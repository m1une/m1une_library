#ifndef M1UNE_ACTED_MONOID_RANGE_BITWISE_AND_OR_XOR_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_BITWISE_AND_OR_XOR_RANGE_SUM_HPP 1

#include <array>
#include <limits>
#include <type_traits>

namespace m1une {
namespace acted_monoid {

template <typename T, int BITS>
struct RangeBitwiseAndOrXorRangeSumNode {
    T sum;
    std::array<long long, BITS> bit_count;
    long long size;
};

// Acted monoid for range bitwise AND, OR, and XOR updates and range sum queries.
template <typename T, int BITS = 30>
struct RangeBitwiseAndOrXorRangeSum {
    static_assert(std::is_integral_v<T> && !std::is_same_v<std::remove_cv_t<T>, bool>);
    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);

    using value_type = RangeBitwiseAndOrXorRangeSumNode<T, BITS>;

    // Represents f(x) = (x & and_mask) ^ xor_mask on the lowest BITS bits.
    struct operator_type {
        T and_mask;
        T xor_mask;
    };

    static constexpr bool commutative = true;
    static constexpr bool operator_commutative = false;

    static constexpr T bit_mask() {
        if constexpr (std::is_unsigned_v<T> && BITS == std::numeric_limits<T>::digits) {
            return ~T(0);
        } else {
            return (T(1) << (BITS - 1)) | ((T(1) << (BITS - 1)) - 1);
        }
    }

    static constexpr value_type id() {
        value_type res;
        res.sum = T(0);
        res.bit_count.fill(0);
        res.size = 0;
        return res;
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res;
        res.sum = a.sum + b.sum;
        res.size = a.size + b.size;
        for (int i = 0; i < BITS; ++i) {
            res.bit_count[i] = a.bit_count[i] + b.bit_count[i];
        }
        return res;
    }

    static constexpr operator_type op_id() {
        return {bit_mask(), T(0)};
    }

    // Returns f(g(x)).
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return {f.and_mask & g.and_mask, (g.xor_mask & f.and_mask) ^ f.xor_mask};
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        value_type res = x;
        res.sum = T(0);
        for (int i = 0; i < BITS; ++i) {
            long long count = ((f.and_mask >> i) & T(1)) ? x.bit_count[i] : 0;
            if ((f.xor_mask >> i) & T(1)) count = x.size - count;
            res.bit_count[i] = count;
            res.sum += static_cast<T>(count) * (T(1) << i);
        }
        return res;
    }

    static constexpr value_type make(const T& value) {
        value_type res;
        res.sum = value;
        res.size = 1;
        for (int i = 0; i < BITS; ++i) {
            res.bit_count[i] = (value >> i) & T(1);
        }
        return res;
    }

    static constexpr operator_type make_and(const T& mask) {
        return {mask & bit_mask(), T(0)};
    }

    static constexpr operator_type make_or(const T& mask) {
        T normalized = mask & bit_mask();
        return {bit_mask() ^ normalized, normalized};
    }

    static constexpr operator_type make_xor(const T& mask) {
        return {bit_mask(), mask & bit_mask()};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_BITWISE_AND_OR_XOR_RANGE_SUM_HPP
