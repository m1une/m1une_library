#ifndef M1UNE_BEATS_ACTED_MONOID_CONCEPT_HPP
#define M1UNE_BEATS_ACTED_MONOID_CONCEPT_HPP 1

#include <concepts>

#include "../acted_monoid/concept.hpp"

namespace m1une {
namespace beats_acted_monoid {

// An acted monoid whose action may require descent before it can be applied.
template <typename AM>
concept IsBeatsActedMonoid = m1une::acted_monoid::IsActedMonoid<AM> &&
    requires(typename AM::value_type x, typename AM::operator_type f) {
        { AM::can_apply(f, x) } -> std::same_as<bool>;
    };

}  // namespace beats_acted_monoid
}  // namespace m1une

#endif  // M1UNE_BEATS_ACTED_MONOID_CONCEPT_HPP
