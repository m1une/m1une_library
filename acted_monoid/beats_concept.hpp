#ifndef M1UNE_ACTED_MONOID_BEATS_CONCEPT_HPP
#define M1UNE_ACTED_MONOID_BEATS_CONCEPT_HPP 1

#include <concepts>

#include "concept.hpp"

namespace m1une {
namespace acted_monoid {

// An acted monoid whose action may require descent before it can be applied.
template <typename AM>
concept IsBeatsActedMonoid = IsActedMonoid<AM> &&
    requires(typename AM::value_type x, typename AM::operator_type f) {
        { AM::can_apply(f, x) } -> std::same_as<bool>;
    };

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_BEATS_CONCEPT_HPP
