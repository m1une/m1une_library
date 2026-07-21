#ifndef M1UNE_UTILITIES_INT1024_HPP
#define M1UNE_UTILITIES_INT1024_HPP 1

#include <string>
#include <string_view>

#include "detail/fixed_int.hpp"

namespace m1une {
namespace utilities {

using Int1024 = detail::FixedInt<1024>;
using i1024 = Int1024;

inline Int1024 parse_int1024(std::string_view text) {
    return Int1024(text);
}

inline std::string to_string(const Int1024& value) {
    return value.to_string();
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_INT1024_HPP
