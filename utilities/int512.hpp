#ifndef M1UNE_UTILITIES_INT512_HPP
#define M1UNE_UTILITIES_INT512_HPP 1

#include <string>
#include <string_view>

#include "detail/fixed_int.hpp"

namespace m1une {
namespace utilities {

using Int512 = detail::FixedInt<512>;
using i512 = Int512;

inline Int512 parse_int512(std::string_view text) {
    return Int512(text);
}

inline std::string to_string(const Int512& value) {
    return value.to_string();
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_INT512_HPP
