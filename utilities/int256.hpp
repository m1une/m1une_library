#ifndef M1UNE_UTILITIES_INT256_HPP
#define M1UNE_UTILITIES_INT256_HPP 1

#include <string>
#include <string_view>

#include "detail/fixed_int.hpp"

namespace m1une {
namespace utilities {

using Int256 = detail::FixedInt<256>;
using i256 = Int256;

inline Int256 parse_int256(std::string_view text) {
    return Int256(text);
}

inline std::string to_string(const Int256& value) {
    return value.to_string();
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_INT256_HPP
