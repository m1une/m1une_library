#ifndef M1UNE_ACTED_MONOID_BEATS_WRAPPER_HPP
#define M1UNE_ACTED_MONOID_BEATS_WRAPPER_HPP 1

#include <concepts>

namespace m1une {
namespace acted_monoid {

// Wrapper for defining a Beats acted monoid with callables supplied as NTTPs.
template <
    typename T,
    typename E,
    auto Op,
    auto Id,
    auto OpComp,
    auto OpId,
    auto Mapping,
    auto CanApply,
    auto Make = nullptr,
    auto MakeAt = nullptr,
    auto MappingAt = nullptr,
    auto CanApplyAt = nullptr,
    auto OpShift = nullptr,
    bool Commutative = false,
    bool OperatorCommutative = false
>
struct BeatsWrapper {
    using value_type = T;
    using operator_type = E;
    static constexpr bool commutative = Commutative;
    static constexpr bool operator_commutative = OperatorCommutative;

    static constexpr T id() {
        return Id();
    }

    static constexpr T op(const T& lhs, const T& rhs) {
        return Op(lhs, rhs);
    }

    static constexpr E op_id() {
        return OpId();
    }

    static constexpr E op_comp(const E& f, const E& g) {
        return OpComp(f, g);
    }

    static constexpr T mapping(const E& f, const T& x) {
        return Mapping(f, x);
    }

    static constexpr bool can_apply(const E& f, const T& x) {
        return CanApply(f, x);
    }

    template <typename U>
    requires requires(const U& value) {
        { Make(value) } -> std::convertible_to<T>;
    }
    static constexpr T make(const U& value) {
        return Make(value);
    }

    template <typename U>
    requires requires(const U& value, int index) {
        { MakeAt(value, index) } -> std::convertible_to<T>;
    }
    static constexpr T make(const U& value, int index) {
        return MakeAt(value, index);
    }

    static constexpr T mapping(const E& f, const T& x, long long ordinal)
    requires requires {
        { MappingAt(f, x, ordinal) } -> std::convertible_to<T>;
    }
    {
        return MappingAt(f, x, ordinal);
    }

    static constexpr bool can_apply(
        const E& f,
        const T& x,
        long long ordinal
    )
    requires requires {
        { CanApplyAt(f, x, ordinal) } -> std::convertible_to<bool>;
    }
    {
        return CanApplyAt(f, x, ordinal);
    }

    static constexpr E op_shift(const E& f, long long ordinal)
    requires requires {
        { OpShift(f, ordinal) } -> std::convertible_to<E>;
    }
    {
        return OpShift(f, ordinal);
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_BEATS_WRAPPER_HPP
