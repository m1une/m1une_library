---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':heavy_check_mark:'
    path: geometry/convex_decomposition.hpp
    title: Convex Decomposition
  - icon: ':heavy_check_mark:'
    path: utilities/int1024.hpp
    title: Int1024
  - icon: ':heavy_check_mark:'
    path: utilities/int256.hpp
    title: Int256
  - icon: ':heavy_check_mark:'
    path: utilities/int512.hpp
    title: Int512
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/centroid.test.cpp
    title: verify/geometry/centroid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/convex_decomposition.test.cpp
    title: verify/geometry/convex_decomposition.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/utilities/int1024.test.cpp
    title: verify/utilities/int1024.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/utilities/int256.test.cpp
    title: verify/utilities/int256.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/utilities/int512.test.cpp
    title: verify/utilities/int512.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/detail/fixed_int.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <concepts>\n#include <cstddef>\n#include <cstdint>\n\
    #include <istream>\n#include <ostream>\n#include <stdexcept>\n#include <string>\n\
    #include <string_view>\n#include <type_traits>\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace detail {\n\n// A signed two's-complement\
    \ integer whose arithmetic wraps modulo 2^Bits.\n// Public aliases select contest-friendly\
    \ fixed widths in int*.hpp.\ntemplate <std::size_t Bits>\nclass FixedInt {\n \
    \   static_assert(Bits >= 64);\n    static_assert(Bits % 64 == 0);\n\n   private:\n\
    \    static constexpr std::size_t limb_count = Bits / 64;\n    using LimbArray\
    \ = std::array<std::uint64_t, limb_count>;\n\n   public:\n    static constexpr\
    \ std::size_t bit_width = Bits;\n\n    constexpr FixedInt() = default;\n\n   \
    \ template <std::integral Integer>\n    constexpr FixedInt(Integer value) {\n\
    \        static_assert(sizeof(Integer) <= sizeof(std::uint64_t));\n        if\
    \ constexpr (std::signed_integral<Integer>) {\n            const std::uint64_t\
    \ extension =\n                value < 0 ? ~std::uint64_t(0) : std::uint64_t(0);\n\
    \            limbs_.fill(extension);\n            limbs_[0] = static_cast<std::uint64_t>(\n\
    \                static_cast<std::int64_t>(value)\n            );\n        } else\
    \ {\n            limbs_[0] = static_cast<std::uint64_t>(value);\n        }\n \
    \   }\n\n    explicit FixedInt(std::string_view text) { read(text); }\n\n    FixedInt&\
    \ operator=(std::string_view text) {\n        read(text);\n        return *this;\n\
    \    }\n\n    void read(std::string_view text) {\n        if (text.empty()) {\n\
    \            throw std::invalid_argument(\"empty fixed-width integer\");\n   \
    \     }\n        const bool negative = text.front() == '-';\n        std::size_t\
    \ position =\n            (text.front() == '-' || text.front() == '+') ? 1 : 0;\n\
    \        if (position == text.size()) {\n            throw std::invalid_argument(\"\
    invalid fixed-width integer\");\n        }\n\n        FixedInt result;\n     \
    \   for (; position < text.size(); ++position) {\n            const char digit\
    \ = text[position];\n            if (digit < '0' || digit > '9') {\n         \
    \       throw std::invalid_argument(\"invalid fixed-width integer\");\n      \
    \      }\n            result.multiply_small(10);\n            result += FixedInt(static_cast<unsigned>(digit\
    \ - '0'));\n        }\n        *this = negative ? -result : result;\n    }\n\n\
    \    constexpr bool is_zero() const {\n        for (const std::uint64_t limb :\
    \ limbs_) {\n            if (limb != 0) return false;\n        }\n        return\
    \ true;\n    }\n\n    constexpr bool is_negative() const {\n        return (limbs_.back()\
    \ >> 63) != 0;\n    }\n\n    constexpr int sign() const {\n        if (is_zero())\
    \ return 0;\n        return is_negative() ? -1 : 1;\n    }\n\n    constexpr FixedInt\
    \ operator+() const { return *this; }\n\n    constexpr FixedInt operator-() const\
    \ {\n        FixedInt result;\n        result.limbs_ = limbs_;\n        negate_unsigned(result.limbs_);\n\
    \        return result;\n    }\n\n    constexpr FixedInt& operator+=(const FixedInt&\
    \ other) {\n        __uint128_t carry = 0;\n        for (std::size_t index = 0;\
    \ index < limb_count; ++index) {\n            const __uint128_t current =\n  \
    \              __uint128_t(limbs_[index]) + other.limbs_[index] + carry;\n   \
    \         limbs_[index] = static_cast<std::uint64_t>(current);\n            carry\
    \ = current >> 64;\n        }\n        return *this;\n    }\n\n    constexpr FixedInt&\
    \ operator-=(const FixedInt& other) {\n        return *this += -other;\n    }\n\
    \n    constexpr FixedInt& operator*=(const FixedInt& other) {\n        LimbArray\
    \ product{};\n        for (std::size_t first = 0; first < limb_count; ++first)\
    \ {\n            __uint128_t carry = 0;\n            for (\n                std::size_t\
    \ second = 0;\n                first + second < limb_count;\n                ++second\n\
    \            ) {\n                const std::size_t position = first + second;\n\
    \                const __uint128_t current =\n                    __uint128_t(limbs_[first])\
    \ * other.limbs_[second] +\n                    product[position] + carry;\n \
    \               product[position] = static_cast<std::uint64_t>(current);\n   \
    \             carry = current >> 64;\n            }\n        }\n        limbs_\
    \ = product;\n        return *this;\n    }\n\n    constexpr FixedInt& operator/=(const\
    \ FixedInt& other) {\n        return *this = divmod(*this, other).first;\n   \
    \ }\n\n    constexpr FixedInt& operator%=(const FixedInt& other) {\n        return\
    \ *this = divmod(*this, other).second;\n    }\n\n    std::string to_string() const\
    \ {\n        if (is_zero()) return \"0\";\n        const bool negative = is_negative();\n\
    \        LimbArray magnitude = unsigned_magnitude();\n\n        std::string result;\n\
    \        while (!magnitude_is_zero(magnitude)) {\n            const unsigned digit\
    \ = divide_unsigned_by_ten(magnitude);\n            result.push_back(static_cast<char>('0'\
    \ + digit));\n        }\n        if (negative) result.push_back('-');\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    \n    friend constexpr std::pair<FixedInt, FixedInt> divmod(\n        const FixedInt&\
    \ dividend,\n        const FixedInt& divisor\n    ) {\n        if (divisor.is_zero())\
    \ {\n            throw std::domain_error(\"fixed-width integer division by zero\"\
    );\n        }\n\n        const bool quotient_negative =\n            dividend.is_negative()\
    \ != divisor.is_negative();\n        const bool remainder_negative = dividend.is_negative();\n\
    \        auto [quotient_limbs, remainder_limbs] = divide_unsigned(\n         \
    \   dividend.unsigned_magnitude(), divisor.unsigned_magnitude()\n        );\n\n\
    \        FixedInt quotient;\n        FixedInt remainder;\n        quotient.limbs_\
    \ = quotient_limbs;\n        remainder.limbs_ = remainder_limbs;\n        if (quotient_negative)\
    \ quotient = -quotient;\n        if (remainder_negative) remainder = -remainder;\n\
    \        return std::make_pair(quotient, remainder);\n    }\n\n    friend constexpr\
    \ FixedInt operator+(\n        FixedInt first,\n        const FixedInt& second\n\
    \    ) {\n        return first += second;\n    }\n\n    friend constexpr FixedInt\
    \ operator-(\n        FixedInt first,\n        const FixedInt& second\n    ) {\n\
    \        return first -= second;\n    }\n\n    friend constexpr FixedInt operator*(\n\
    \        FixedInt first,\n        const FixedInt& second\n    ) {\n        return\
    \ first *= second;\n    }\n\n    friend constexpr FixedInt operator/(\n      \
    \  FixedInt first,\n        const FixedInt& second\n    ) {\n        return first\
    \ /= second;\n    }\n\n    friend constexpr FixedInt operator%(\n        FixedInt\
    \ first,\n        const FixedInt& second\n    ) {\n        return first %= second;\n\
    \    }\n\n    friend constexpr bool operator==(\n        const FixedInt& first,\n\
    \        const FixedInt& second\n    ) = default;\n\n    friend constexpr bool\
    \ operator<(\n        const FixedInt& first,\n        const FixedInt& second\n\
    \    ) {\n        const bool first_negative = first.is_negative();\n        const\
    \ bool second_negative = second.is_negative();\n        if (first_negative !=\
    \ second_negative) return first_negative;\n        return compare_unsigned(first.limbs_,\
    \ second.limbs_) < 0;\n    }\n\n    friend constexpr bool operator!=(\n      \
    \  const FixedInt& first,\n        const FixedInt& second\n    ) {\n        return\
    \ !(first == second);\n    }\n\n    friend constexpr bool operator>(\n       \
    \ const FixedInt& first,\n        const FixedInt& second\n    ) {\n        return\
    \ second < first;\n    }\n\n    friend constexpr bool operator<=(\n        const\
    \ FixedInt& first,\n        const FixedInt& second\n    ) {\n        return !(second\
    \ < first);\n    }\n\n    friend constexpr bool operator>=(\n        const FixedInt&\
    \ first,\n        const FixedInt& second\n    ) {\n        return !(first < second);\n\
    \    }\n\n    friend std::ostream& operator<<(\n        std::ostream& output,\n\
    \        const FixedInt& value\n    ) {\n        return output << value.to_string();\n\
    \    }\n\n    friend std::istream& operator>>(\n        std::istream& input,\n\
    \        FixedInt& value\n    ) {\n        std::string text;\n        if (input\
    \ >> text) value.read(text);\n        return input;\n    }\n\n   private:\n  \
    \  LimbArray limbs_{};\n\n    constexpr LimbArray unsigned_magnitude() const {\n\
    \        LimbArray result = limbs_;\n        if (is_negative()) negate_unsigned(result);\n\
    \        return result;\n    }\n\n    constexpr void multiply_small(std::uint64_t\
    \ value) {\n        __uint128_t carry = 0;\n        for (std::size_t index = 0;\
    \ index < limb_count; ++index) {\n            const __uint128_t current =\n  \
    \              __uint128_t(limbs_[index]) * value + carry;\n            limbs_[index]\
    \ = static_cast<std::uint64_t>(current);\n            carry = current >> 64;\n\
    \        }\n    }\n\n    static constexpr void negate_unsigned(LimbArray& value)\
    \ {\n        for (std::uint64_t& limb : value) limb = ~limb;\n        for (std::size_t\
    \ index = 0; index < limb_count; ++index) {\n            if (++value[index] !=\
    \ 0) break;\n        }\n    }\n\n    static constexpr int compare_unsigned(\n\
    \        const LimbArray& first,\n        const LimbArray& second\n    ) {\n \
    \       for (std::size_t offset = 0; offset < limb_count; ++offset) {\n      \
    \      const std::size_t index = limb_count - 1 - offset;\n            if (first[index]\
    \ != second[index]) {\n                return first[index] < second[index] ? -1\
    \ : 1;\n            }\n        }\n        return 0;\n    }\n\n    static constexpr\
    \ void subtract_unsigned(\n        LimbArray& first,\n        const LimbArray&\
    \ second\n    ) {\n        std::uint64_t borrow = 0;\n        for (std::size_t\
    \ index = 0; index < limb_count; ++index) {\n            const std::uint64_t previous\
    \ = first[index];\n            first[index] -= second[index] + borrow;\n     \
    \       const bool addition_overflow =\n                borrow != 0 && second[index]\
    \ == ~std::uint64_t(0);\n            borrow = addition_overflow ||\n         \
    \            previous < second[index] + borrow;\n        }\n    }\n\n    static\
    \ constexpr void shift_left_one(LimbArray& value) {\n        std::uint64_t carry\
    \ = 0;\n        for (std::size_t index = 0; index < limb_count; ++index) {\n \
    \           const std::uint64_t next_carry = value[index] >> 63;\n           \
    \ value[index] = (value[index] << 1) | carry;\n            carry = next_carry;\n\
    \        }\n    }\n\n    static constexpr std::pair<LimbArray, LimbArray> divide_unsigned(\n\
    \        const LimbArray& dividend,\n        const LimbArray& divisor\n    ) {\n\
    \        LimbArray quotient{};\n        LimbArray remainder{};\n        for (std::size_t\
    \ offset = 0; offset < Bits; ++offset) {\n            const std::size_t bit =\
    \ Bits - 1 - offset;\n            shift_left_one(remainder);\n            remainder[0]\
    \ |=\n                (dividend[bit / 64] >> (bit % 64)) & std::uint64_t(1);\n\
    \            if (compare_unsigned(remainder, divisor) >= 0) {\n              \
    \  subtract_unsigned(remainder, divisor);\n                quotient[bit / 64]\
    \ |= std::uint64_t(1) << (bit % 64);\n            }\n        }\n        return\
    \ std::make_pair(quotient, remainder);\n    }\n\n    static bool magnitude_is_zero(const\
    \ LimbArray& value) {\n        for (const std::uint64_t limb : value) {\n    \
    \        if (limb != 0) return false;\n        }\n        return true;\n    }\n\
    \n    static unsigned divide_unsigned_by_ten(LimbArray& value) {\n        __uint128_t\
    \ remainder = 0;\n        for (std::size_t offset = 0; offset < limb_count; ++offset)\
    \ {\n            const std::size_t index = limb_count - 1 - offset;\n        \
    \    const __uint128_t current =\n                (remainder << 64) | value[index];\n\
    \            value[index] = static_cast<std::uint64_t>(current / 10);\n      \
    \      remainder = current % 10;\n        }\n        return static_cast<unsigned>(remainder);\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_UTILITIES_DETAIL_FIXED_INT_HPP\n#define M1UNE_UTILITIES_DETAIL_FIXED_INT_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <concepts>\n#include <cstddef>\n\
    #include <cstdint>\n#include <istream>\n#include <ostream>\n#include <stdexcept>\n\
    #include <string>\n#include <string_view>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace detail {\n\n// A signed\
    \ two's-complement integer whose arithmetic wraps modulo 2^Bits.\n// Public aliases\
    \ select contest-friendly fixed widths in int*.hpp.\ntemplate <std::size_t Bits>\n\
    class FixedInt {\n    static_assert(Bits >= 64);\n    static_assert(Bits % 64\
    \ == 0);\n\n   private:\n    static constexpr std::size_t limb_count = Bits /\
    \ 64;\n    using LimbArray = std::array<std::uint64_t, limb_count>;\n\n   public:\n\
    \    static constexpr std::size_t bit_width = Bits;\n\n    constexpr FixedInt()\
    \ = default;\n\n    template <std::integral Integer>\n    constexpr FixedInt(Integer\
    \ value) {\n        static_assert(sizeof(Integer) <= sizeof(std::uint64_t));\n\
    \        if constexpr (std::signed_integral<Integer>) {\n            const std::uint64_t\
    \ extension =\n                value < 0 ? ~std::uint64_t(0) : std::uint64_t(0);\n\
    \            limbs_.fill(extension);\n            limbs_[0] = static_cast<std::uint64_t>(\n\
    \                static_cast<std::int64_t>(value)\n            );\n        } else\
    \ {\n            limbs_[0] = static_cast<std::uint64_t>(value);\n        }\n \
    \   }\n\n    explicit FixedInt(std::string_view text) { read(text); }\n\n    FixedInt&\
    \ operator=(std::string_view text) {\n        read(text);\n        return *this;\n\
    \    }\n\n    void read(std::string_view text) {\n        if (text.empty()) {\n\
    \            throw std::invalid_argument(\"empty fixed-width integer\");\n   \
    \     }\n        const bool negative = text.front() == '-';\n        std::size_t\
    \ position =\n            (text.front() == '-' || text.front() == '+') ? 1 : 0;\n\
    \        if (position == text.size()) {\n            throw std::invalid_argument(\"\
    invalid fixed-width integer\");\n        }\n\n        FixedInt result;\n     \
    \   for (; position < text.size(); ++position) {\n            const char digit\
    \ = text[position];\n            if (digit < '0' || digit > '9') {\n         \
    \       throw std::invalid_argument(\"invalid fixed-width integer\");\n      \
    \      }\n            result.multiply_small(10);\n            result += FixedInt(static_cast<unsigned>(digit\
    \ - '0'));\n        }\n        *this = negative ? -result : result;\n    }\n\n\
    \    constexpr bool is_zero() const {\n        for (const std::uint64_t limb :\
    \ limbs_) {\n            if (limb != 0) return false;\n        }\n        return\
    \ true;\n    }\n\n    constexpr bool is_negative() const {\n        return (limbs_.back()\
    \ >> 63) != 0;\n    }\n\n    constexpr int sign() const {\n        if (is_zero())\
    \ return 0;\n        return is_negative() ? -1 : 1;\n    }\n\n    constexpr FixedInt\
    \ operator+() const { return *this; }\n\n    constexpr FixedInt operator-() const\
    \ {\n        FixedInt result;\n        result.limbs_ = limbs_;\n        negate_unsigned(result.limbs_);\n\
    \        return result;\n    }\n\n    constexpr FixedInt& operator+=(const FixedInt&\
    \ other) {\n        __uint128_t carry = 0;\n        for (std::size_t index = 0;\
    \ index < limb_count; ++index) {\n            const __uint128_t current =\n  \
    \              __uint128_t(limbs_[index]) + other.limbs_[index] + carry;\n   \
    \         limbs_[index] = static_cast<std::uint64_t>(current);\n            carry\
    \ = current >> 64;\n        }\n        return *this;\n    }\n\n    constexpr FixedInt&\
    \ operator-=(const FixedInt& other) {\n        return *this += -other;\n    }\n\
    \n    constexpr FixedInt& operator*=(const FixedInt& other) {\n        LimbArray\
    \ product{};\n        for (std::size_t first = 0; first < limb_count; ++first)\
    \ {\n            __uint128_t carry = 0;\n            for (\n                std::size_t\
    \ second = 0;\n                first + second < limb_count;\n                ++second\n\
    \            ) {\n                const std::size_t position = first + second;\n\
    \                const __uint128_t current =\n                    __uint128_t(limbs_[first])\
    \ * other.limbs_[second] +\n                    product[position] + carry;\n \
    \               product[position] = static_cast<std::uint64_t>(current);\n   \
    \             carry = current >> 64;\n            }\n        }\n        limbs_\
    \ = product;\n        return *this;\n    }\n\n    constexpr FixedInt& operator/=(const\
    \ FixedInt& other) {\n        return *this = divmod(*this, other).first;\n   \
    \ }\n\n    constexpr FixedInt& operator%=(const FixedInt& other) {\n        return\
    \ *this = divmod(*this, other).second;\n    }\n\n    std::string to_string() const\
    \ {\n        if (is_zero()) return \"0\";\n        const bool negative = is_negative();\n\
    \        LimbArray magnitude = unsigned_magnitude();\n\n        std::string result;\n\
    \        while (!magnitude_is_zero(magnitude)) {\n            const unsigned digit\
    \ = divide_unsigned_by_ten(magnitude);\n            result.push_back(static_cast<char>('0'\
    \ + digit));\n        }\n        if (negative) result.push_back('-');\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    \n    friend constexpr std::pair<FixedInt, FixedInt> divmod(\n        const FixedInt&\
    \ dividend,\n        const FixedInt& divisor\n    ) {\n        if (divisor.is_zero())\
    \ {\n            throw std::domain_error(\"fixed-width integer division by zero\"\
    );\n        }\n\n        const bool quotient_negative =\n            dividend.is_negative()\
    \ != divisor.is_negative();\n        const bool remainder_negative = dividend.is_negative();\n\
    \        auto [quotient_limbs, remainder_limbs] = divide_unsigned(\n         \
    \   dividend.unsigned_magnitude(), divisor.unsigned_magnitude()\n        );\n\n\
    \        FixedInt quotient;\n        FixedInt remainder;\n        quotient.limbs_\
    \ = quotient_limbs;\n        remainder.limbs_ = remainder_limbs;\n        if (quotient_negative)\
    \ quotient = -quotient;\n        if (remainder_negative) remainder = -remainder;\n\
    \        return std::make_pair(quotient, remainder);\n    }\n\n    friend constexpr\
    \ FixedInt operator+(\n        FixedInt first,\n        const FixedInt& second\n\
    \    ) {\n        return first += second;\n    }\n\n    friend constexpr FixedInt\
    \ operator-(\n        FixedInt first,\n        const FixedInt& second\n    ) {\n\
    \        return first -= second;\n    }\n\n    friend constexpr FixedInt operator*(\n\
    \        FixedInt first,\n        const FixedInt& second\n    ) {\n        return\
    \ first *= second;\n    }\n\n    friend constexpr FixedInt operator/(\n      \
    \  FixedInt first,\n        const FixedInt& second\n    ) {\n        return first\
    \ /= second;\n    }\n\n    friend constexpr FixedInt operator%(\n        FixedInt\
    \ first,\n        const FixedInt& second\n    ) {\n        return first %= second;\n\
    \    }\n\n    friend constexpr bool operator==(\n        const FixedInt& first,\n\
    \        const FixedInt& second\n    ) = default;\n\n    friend constexpr bool\
    \ operator<(\n        const FixedInt& first,\n        const FixedInt& second\n\
    \    ) {\n        const bool first_negative = first.is_negative();\n        const\
    \ bool second_negative = second.is_negative();\n        if (first_negative !=\
    \ second_negative) return first_negative;\n        return compare_unsigned(first.limbs_,\
    \ second.limbs_) < 0;\n    }\n\n    friend constexpr bool operator!=(\n      \
    \  const FixedInt& first,\n        const FixedInt& second\n    ) {\n        return\
    \ !(first == second);\n    }\n\n    friend constexpr bool operator>(\n       \
    \ const FixedInt& first,\n        const FixedInt& second\n    ) {\n        return\
    \ second < first;\n    }\n\n    friend constexpr bool operator<=(\n        const\
    \ FixedInt& first,\n        const FixedInt& second\n    ) {\n        return !(second\
    \ < first);\n    }\n\n    friend constexpr bool operator>=(\n        const FixedInt&\
    \ first,\n        const FixedInt& second\n    ) {\n        return !(first < second);\n\
    \    }\n\n    friend std::ostream& operator<<(\n        std::ostream& output,\n\
    \        const FixedInt& value\n    ) {\n        return output << value.to_string();\n\
    \    }\n\n    friend std::istream& operator>>(\n        std::istream& input,\n\
    \        FixedInt& value\n    ) {\n        std::string text;\n        if (input\
    \ >> text) value.read(text);\n        return input;\n    }\n\n   private:\n  \
    \  LimbArray limbs_{};\n\n    constexpr LimbArray unsigned_magnitude() const {\n\
    \        LimbArray result = limbs_;\n        if (is_negative()) negate_unsigned(result);\n\
    \        return result;\n    }\n\n    constexpr void multiply_small(std::uint64_t\
    \ value) {\n        __uint128_t carry = 0;\n        for (std::size_t index = 0;\
    \ index < limb_count; ++index) {\n            const __uint128_t current =\n  \
    \              __uint128_t(limbs_[index]) * value + carry;\n            limbs_[index]\
    \ = static_cast<std::uint64_t>(current);\n            carry = current >> 64;\n\
    \        }\n    }\n\n    static constexpr void negate_unsigned(LimbArray& value)\
    \ {\n        for (std::uint64_t& limb : value) limb = ~limb;\n        for (std::size_t\
    \ index = 0; index < limb_count; ++index) {\n            if (++value[index] !=\
    \ 0) break;\n        }\n    }\n\n    static constexpr int compare_unsigned(\n\
    \        const LimbArray& first,\n        const LimbArray& second\n    ) {\n \
    \       for (std::size_t offset = 0; offset < limb_count; ++offset) {\n      \
    \      const std::size_t index = limb_count - 1 - offset;\n            if (first[index]\
    \ != second[index]) {\n                return first[index] < second[index] ? -1\
    \ : 1;\n            }\n        }\n        return 0;\n    }\n\n    static constexpr\
    \ void subtract_unsigned(\n        LimbArray& first,\n        const LimbArray&\
    \ second\n    ) {\n        std::uint64_t borrow = 0;\n        for (std::size_t\
    \ index = 0; index < limb_count; ++index) {\n            const std::uint64_t previous\
    \ = first[index];\n            first[index] -= second[index] + borrow;\n     \
    \       const bool addition_overflow =\n                borrow != 0 && second[index]\
    \ == ~std::uint64_t(0);\n            borrow = addition_overflow ||\n         \
    \            previous < second[index] + borrow;\n        }\n    }\n\n    static\
    \ constexpr void shift_left_one(LimbArray& value) {\n        std::uint64_t carry\
    \ = 0;\n        for (std::size_t index = 0; index < limb_count; ++index) {\n \
    \           const std::uint64_t next_carry = value[index] >> 63;\n           \
    \ value[index] = (value[index] << 1) | carry;\n            carry = next_carry;\n\
    \        }\n    }\n\n    static constexpr std::pair<LimbArray, LimbArray> divide_unsigned(\n\
    \        const LimbArray& dividend,\n        const LimbArray& divisor\n    ) {\n\
    \        LimbArray quotient{};\n        LimbArray remainder{};\n        for (std::size_t\
    \ offset = 0; offset < Bits; ++offset) {\n            const std::size_t bit =\
    \ Bits - 1 - offset;\n            shift_left_one(remainder);\n            remainder[0]\
    \ |=\n                (dividend[bit / 64] >> (bit % 64)) & std::uint64_t(1);\n\
    \            if (compare_unsigned(remainder, divisor) >= 0) {\n              \
    \  subtract_unsigned(remainder, divisor);\n                quotient[bit / 64]\
    \ |= std::uint64_t(1) << (bit % 64);\n            }\n        }\n        return\
    \ std::make_pair(quotient, remainder);\n    }\n\n    static bool magnitude_is_zero(const\
    \ LimbArray& value) {\n        for (const std::uint64_t limb : value) {\n    \
    \        if (limb != 0) return false;\n        }\n        return true;\n    }\n\
    \n    static unsigned divide_unsigned_by_ten(LimbArray& value) {\n        __uint128_t\
    \ remainder = 0;\n        for (std::size_t offset = 0; offset < limb_count; ++offset)\
    \ {\n            const std::size_t index = limb_count - 1 - offset;\n        \
    \    const __uint128_t current =\n                (remainder << 64) | value[index];\n\
    \            value[index] = static_cast<std::uint64_t>(current / 10);\n      \
    \      remainder = current % 10;\n        }\n        return static_cast<unsigned>(remainder);\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_UTILITIES_DETAIL_FIXED_INT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/detail/fixed_int.hpp
  requiredBy:
  - utilities/int1024.hpp
  - utilities/int256.hpp
  - utilities/int512.hpp
  - geometry/all.hpp
  - geometry/convex_decomposition.hpp
  timestamp: '2026-07-22 04:04:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/int512.test.cpp
  - verify/utilities/int1024.test.cpp
  - verify/utilities/int256.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: utilities/detail/fixed_int.hpp
layout: document
redirect_from:
- /library/utilities/detail/fixed_int.hpp
- /library/utilities/detail/fixed_int.hpp.html
title: utilities/detail/fixed_int.hpp
---
