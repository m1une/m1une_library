---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/ray.hpp
    title: Rays
  - icon: ':heavy_check_mark:'
    path: utilities/detail/fixed_int.hpp
    title: utilities/detail/fixed_int.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/int256.hpp
    title: Int256
  - icon: ':heavy_check_mark:'
    path: utilities/int512.hpp
    title: Int512
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/convex_decomposition.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <cstddef>\n#include <cstdint>\n\
    #include <deque>\n#include <limits>\n#include <map>\n#include <memory>\n#include\
    \ <optional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    #line 1 \"utilities/int256.hpp\"\n\n\n\n#include <string>\n#include <string_view>\n\
    \n#line 1 \"utilities/detail/fixed_int.hpp\"\n\n\n\n#line 5 \"utilities/detail/fixed_int.hpp\"\
    \n#include <array>\n#include <concepts>\n#line 9 \"utilities/detail/fixed_int.hpp\"\
    \n#include <istream>\n#include <ostream>\n#include <stdexcept>\n#line 16 \"utilities/detail/fixed_int.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\nnamespace detail {\n\n// A signed\
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
    \ m1une\n\n\n#line 8 \"utilities/int256.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\nusing Int256 = detail::FixedInt<256>;\nusing i256 = Int256;\n\
    \ninline Int256 parse_int256(std::string_view text) {\n    return Int256(text);\n\
    }\n\ninline std::string to_string(const Int256& value) {\n    return value.to_string();\n\
    }\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/int512.hpp\"\
    \n\n\n\n#line 6 \"utilities/int512.hpp\"\n\n#line 8 \"utilities/int512.hpp\"\n\
    \nnamespace m1une {\nnamespace utilities {\n\nusing Int512 = detail::FixedInt<512>;\n\
    using i512 = Int512;\n\ninline Int512 parse_int512(std::string_view text) {\n\
    \    return Int512(text);\n}\n\ninline std::string to_string(const Int512& value)\
    \ {\n    return value.to_string();\n}\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 1 \"geometry/polygon.hpp\"\n\n\n\n#line 12 \"geometry/polygon.hpp\"\
    \n\n#line 1 \"geometry/ray.hpp\"\n\n\n\n#line 7 \"geometry/ray.hpp\"\n\n#line\
    \ 1 \"geometry/line.hpp\"\n\n\n\n#line 8 \"geometry/line.hpp\"\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#line 8 \"geometry/point.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T> &&\
    \ !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate <Coordinate T>\nusing\
    \ wide_type = std::conditional_t<std::integral<T>, __int128_t, long double>;\n\
    \ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\n    constexpr\
    \ Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value) : x(x_value),\
    \ y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr Point(const\
    \ Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n\n    constexpr Point& operator+=(const Point& other) {\n        x += other.x;\n\
    \        y += other.y;\n        return *this;\n    }\n\n    constexpr Point& operator-=(const\
    \ Point& other) {\n        x -= other.x;\n        y -= other.y;\n        return\
    \ *this;\n    }\n\n    constexpr Point operator+() const {\n        return *this;\n\
    \    }\n\n    constexpr Point operator-() const {\n        return Point(-x, -y);\n\
    \    }\n\n    friend constexpr Point operator+(Point left, const Point& right)\
    \ {\n        return left += right;\n    }\n\n    friend constexpr Point operator-(Point\
    \ left, const Point& right) {\n        return left -= right;\n    }\n\n    friend\
    \ constexpr bool operator==(const Point&, const Point&) = default;\n\n    friend\
    \ constexpr bool operator<(const Point& left, const Point& right) {\n        if\
    \ (left.x != right.x) return left.x < right.x;\n        return left.y < right.y;\n\
    \    }\n};\n\ntemplate <Coordinate T>\nconstexpr Point<long double> centroid(const\
    \ Point<T>& point) {\n    return Point<long double>(point);\n}\n\ntemplate <Coordinate\
    \ T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(const\
    \ Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
    \ Scalar>;\n    return Point<Result>(\n        Result(point.x) * Result(scalar),\n\
    \        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate <typename Scalar,\
    \ Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(Scalar\
    \ scalar, const Point<T>& point) {\n    return point * scalar;\n}\n\ntemplate\
    \ <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
    \ Scalar>;\n    return Point<Result>(\n        Result(point.x) / Result(scalar),\n\
    \        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> dot(const Point<T>& a, const Point<T>& b) {\n    using\
    \ W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y) - W(a.y) * W(b.x);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n    const Point<T>&\
    \ origin,\n    const Point<T>& a,\n    const Point<T>& b\n) {\n    using W = wide_type<T>;\n\
    \    W ax = W(a.x) - W(origin.x);\n    W ay = W(a.y) - W(origin.y);\n    W bx\
    \ = W(b.x) - W(origin.x);\n    W by = W(b.y) - W(origin.y);\n    return ax * by\
    \ - ay * bx;\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> norm2(const\
    \ Point<T>& point) {\n    return dot(point, point);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr wide_type<T> distance2(const Point<T>& a, const Point<T>& b) {\n\
    \    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n    W dy = W(a.y) -\
    \ W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate T>\nlong double\
    \ norm(const Point<T>& point) {\n    return std::hypot(\n        static_cast<long\
    \ double>(point.x),\n        static_cast<long double>(point.y)\n    );\n}\n\n\
    template <Coordinate T>\nlong double distance(const Point<T>& a, const Point<T>&\
    \ b) {\n    return std::hypot(\n        static_cast<long double>(a.x) - static_cast<long\
    \ double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long double>(b.y)\n\
    \    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> internal_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio +\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T, typename M, typename N>\nrequires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\n\
    constexpr Point<long double> external_division_point(\n    const Point<T>& a,\n\
    \    const Point<T>& b,\n    M m,\n    N n\n) {\n    long double first_ratio =\
    \ static_cast<long double>(m);\n    long double second_ratio = static_cast<long\
    \ double>(n);\n    long double denominator = first_ratio - second_ratio;\n   \
    \ assert(denominator != 0);\n    Point<long double> first(a);\n    Point<long\
    \ double> direction = Point<long double>(b) - first;\n    return first + direction\
    \ * (first_ratio / denominator);\n}\n\ntemplate <Coordinate T>\nconstexpr int\
    \ sign(wide_type<T> value, long double eps = 1e-12L) {\n    if constexpr (std::integral<T>)\
    \ {\n        return (value > 0) - (value < 0);\n    } else {\n        return (value\
    \ > eps) - (value < -eps);\n    }\n}\n\ntemplate <Coordinate T>\nconstexpr int\
    \ orientation(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return sign<T>(cross(a, b, c), eps);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr bool collinear(\n    const Point<T>& a,\n\
    \    const Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n\
    ) {\n    return orientation(a, b, c, eps) == 0;\n}\n\ntemplate <Coordinate T>\n\
    Point<long double> rotate(const Point<T>& point, long double angle) {\n    long\
    \ double cosine = std::cos(angle);\n    long double sine = std::sin(angle);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) * cosine\
    \ -\n            static_cast<long double>(point.y) * sine,\n        static_cast<long\
    \ double>(point.x) * sine +\n            static_cast<long double>(point.y) * cosine\n\
    \    );\n}\n\ntemplate <Coordinate T>\nPoint<long double> normalized(const Point<T>&\
    \ point) {\n    long double length = norm(point);\n    assert(length != 0);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) / length,\n\
    \        static_cast<long double>(point.y) / length\n    );\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/line.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct Line {\n  \
    \  Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nstruct Segment\
    \ {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nconstexpr\
    \ Point<long double> centroid(const Segment<T>& segment) {\n    return Point<long\
    \ double>(\n        (\n            static_cast<long double>(segment.a.x) +\n \
    \           static_cast<long double>(segment.b.x)\n        ) / 2,\n        (\n\
    \            static_cast<long double>(segment.a.y) +\n            static_cast<long\
    \ double>(segment.b.y)\n        ) / 2\n    );\n}\n\ntemplate <Coordinate T>\n\
    bool on_line(\n    const Line<T>& line,\n    const Point<T>& point,\n    long\
    \ double eps = 1e-12L\n) {\n    assert(line.a != line.b);\n    return orientation(line.a,\
    \ line.b, point, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool parallel(const\
    \ Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {\n    using\
    \ W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y\
    \ = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n\
    \    W second_y = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x *\
    \ second_y - first_y * second_x, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool\
    \ orthogonal(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L)\
    \ {\n    using W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n\
    \    W first_y = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x)\
    \ - W(second.a.x);\n    W second_y = W(second.b.y) - W(second.a.y);\n    return\
    \ sign<T>(first_x * second_x + first_y * second_y, eps) == 0;\n}\n\ntemplate <Coordinate\
    \ T>\nPoint<long double> projection(const Line<T>& line, const Point<T>& point)\
    \ {\n    assert(line.a != line.b);\n    Point<long double> a(line.a);\n    Point<long\
    \ double> direction(\n        static_cast<long double>(line.b.x) - static_cast<long\
    \ double>(line.a.x),\n        static_cast<long double>(line.b.y) - static_cast<long\
    \ double>(line.a.y)\n    );\n    Point<long double> offset(\n        static_cast<long\
    \ double>(point.x) - a.x,\n        static_cast<long double>(point.y) - a.y\n \
    \   );\n    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    return a + direction * ratio;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ reflection(const Line<T>& line, const Point<T>& point) {\n    Point<long double>\
    \ projected = projection(line, point);\n    return projected * 2.0L - Point<long\
    \ double>(point);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>&\
    \ line, const Point<T>& point) {\n    assert(line.a != line.b);\n    Point<long\
    \ double> direction(\n        static_cast<long double>(line.b.x) - static_cast<long\
    \ double>(line.a.x),\n        static_cast<long double>(line.b.y) - static_cast<long\
    \ double>(line.a.y)\n    );\n    Point<long double> offset(\n        static_cast<long\
    \ double>(point.x) - static_cast<long double>(line.a.x),\n        static_cast<long\
    \ double>(point.y) - static_cast<long double>(line.a.y)\n    );\n    return std::fabs(cross(direction,\
    \ offset)) / norm(direction);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Point<T>& point, const Line<T>& line) {\n    return distance(line, point);\n\
    }\n\ntemplate <Coordinate T>\nbool intersects(\n    const Line<T>& first,\n  \
    \  const Line<T>& second,\n    long double eps = 1e-12L\n) {\n    return !parallel(first,\
    \ second, eps) || on_line(first, second.a, eps);\n}\n\ntemplate <Coordinate T>\n\
    long double distance(const Line<T>& first, const Line<T>& second) {\n    return\
    \ intersects(first, second) ? 0 : distance(first, second.a);\n}\n\ntemplate <Coordinate\
    \ T>\nbool on_segment(\n    const Segment<T>& segment,\n    const Point<T>& point,\n\
    \    long double eps = 1e-12L\n) {\n    if (orientation(segment.a, segment.b,\
    \ point, eps) != 0) return false;\n    using W = wide_type<T>;\n    W px = W(point.x);\n\
    \    W py = W(point.y);\n    W min_x = std::min(W(segment.a.x), W(segment.b.x));\n\
    \    W max_x = std::max(W(segment.a.x), W(segment.b.x));\n    W min_y = std::min(W(segment.a.y),\
    \ W(segment.b.y));\n    W max_y = std::max(W(segment.a.y), W(segment.b.y));\n\
    \    if constexpr (std::integral<T>) {\n        return min_x <= px && px <= max_x\
    \ && min_y <= py && py <= max_y;\n    } else {\n        return min_x - eps <=\
    \ px && px <= max_x + eps &&\n               min_y - eps <= py && py <= max_y\
    \ + eps;\n    }\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps = 1e-12L\n) {\n \
    \   int abc = orientation(first.a, first.b, second.a, eps);\n    int abd = orientation(first.a,\
    \ first.b, second.b, eps);\n    int cda = orientation(second.a, second.b, first.a,\
    \ eps);\n    int cdb = orientation(second.a, second.b, first.b, eps);\n\n    if\
    \ (abc == 0 && on_segment(first, second.a, eps)) return true;\n    if (abd ==\
    \ 0 && on_segment(first, second.b, eps)) return true;\n    if (cda == 0 && on_segment(second,\
    \ first.a, eps)) return true;\n    if (cdb == 0 && on_segment(second, first.b,\
    \ eps)) return true;\n    return abc * abd < 0 && cda * cdb < 0;\n}\n\ntemplate\
    \ <Coordinate T>\nbool intersects(\n    const Line<T>& line,\n    const Segment<T>&\
    \ segment,\n    long double eps = 1e-12L\n) {\n    int first_side = orientation(line.a,\
    \ line.b, segment.a, eps);\n    int second_side = orientation(line.a, line.b,\
    \ segment.b, eps);\n    return first_side == 0 || second_side == 0 || first_side\
    \ != second_side;\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Segment<T>&\
    \ segment,\n    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n    return\
    \ intersects(line, segment, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Segment<T>& segment, const Point<T>& point) {\n    Point<long double> a(segment.a);\n\
    \    Point<long double> b(segment.b);\n    Point<long double> p(point);\n    Point<long\
    \ double> direction = b - a;\n    long double length_squared = dot(direction,\
    \ direction);\n    if (length_squared == 0) return geometry::distance(segment.a,\
    \ point);\n    long double ratio = dot(p - a, direction) / length_squared;\n \
    \   ratio = std::clamp(ratio, 0.0L, 1.0L);\n    Point<long double> closest = a\
    \ + direction * ratio;\n    return geometry::distance(closest, p);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(const Point<T>& point, const Segment<T>&\
    \ segment) {\n    return distance(segment, point);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& first, const Segment<T>& second)\
    \ {\n    if (intersects(first, second)) return 0;\n    return std::min({\n   \
    \     distance(first, second.a),\n        distance(first, second.b),\n       \
    \ distance(second, first.a),\n        distance(second, first.b),\n    });\n}\n\
    \ntemplate <Coordinate T>\nlong double distance(const Line<T>& line, const Segment<T>&\
    \ segment) {\n    if (intersects(line, segment)) return 0;\n    return std::min(distance(line,\
    \ segment.a), distance(line, segment.b));\n}\n\ntemplate <Coordinate T>\nlong\
    \ double distance(const Segment<T>& segment, const Line<T>& line) {\n    return\
    \ distance(line, segment);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> line_intersection(\n    const Line<T>& first,\n    const Line<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.a != first.b);\n    assert(second.a\
    \ != second.b);\n    Point<long double> p(first.a);\n    Point<long double> q(second.a);\n\
    \    Point<long double> r = Point<long double>(first.b) - p;\n    Point<long double>\
    \ s = Point<long double>(second.b) - q;\n    long double denominator = cross(r,\
    \ s);\n    if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double\
    \ ratio = cross(q - p, s) / denominator;\n    return p + r * ratio;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
    \    const Line<T>& line,\n    const Segment<T>& segment,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(line.a != line.b);\n    if (segment.a == segment.b)\
    \ {\n        if (on_line(line, segment.a, eps)) {\n            return Point<long\
    \ double>(segment.a);\n        }\n        return std::nullopt;\n    }\n    if\
    \ (!intersects(line, segment, eps)) return std::nullopt;\n    Line<T> supporting_line{segment.a,\
    \ segment.b};\n    return line_intersection(line, supporting_line, eps);\n}\n\n\
    template <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
    \    const Segment<T>& segment,\n    const Line<T>& line,\n    long double eps\
    \ = 1e-12L\n) {\n    return line_segment_intersection(line, segment, eps);\n}\n\
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 9 \"geometry/ray.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct\
    \ Ray {\n    Point<T> origin;\n    Point<T> through;\n};\n\nnamespace ray_detail\
    \ {\n\ntemplate <Coordinate T>\nstruct Parameters {\n    wide_type<T> denominator;\n\
    \    wide_type<T> first_numerator;\n    wide_type<T> second_numerator;\n};\n\n\
    template <Coordinate T>\nParameters<T> parameters(\n    const Point<T>& first_origin,\n\
    \    const Point<T>& first_through,\n    const Point<T>& second_origin,\n    const\
    \ Point<T>& second_through\n) {\n    using W = wide_type<T>;\n    W first_x =\
    \ W(first_through.x) - W(first_origin.x);\n    W first_y = W(first_through.y)\
    \ - W(first_origin.y);\n    W second_x = W(second_through.x) - W(second_origin.x);\n\
    \    W second_y = W(second_through.y) - W(second_origin.y);\n    W offset_x =\
    \ W(second_origin.x) - W(first_origin.x);\n    W offset_y = W(second_origin.y)\
    \ - W(first_origin.y);\n    return Parameters<T>{\n        first_x * second_y\
    \ - first_y * second_x,\n        offset_x * second_y - offset_y * second_x,\n\
    \        offset_x * first_y - offset_y * first_x\n    };\n}\n\ntemplate <Coordinate\
    \ T>\nbool ratio_nonnegative(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    int numerator_sign = sign<T>(numerator, eps);\n\
    \    int denominator_sign = sign<T>(denominator, eps);\n    return numerator_sign\
    \ == 0 || numerator_sign == denominator_sign;\n}\n\ntemplate <Coordinate T>\n\
    bool ratio_in_unit_interval(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    if (sign<T>(denominator, eps) > 0) {\n        return\
    \ sign<T>(numerator, eps) >= 0 &&\n               sign<T>(numerator - denominator,\
    \ eps) <= 0;\n    }\n    return sign<T>(numerator, eps) <= 0 &&\n           sign<T>(numerator\
    \ - denominator, eps) >= 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ point_at(\n    const Ray<T>& ray,\n    wide_type<T> numerator,\n    wide_type<T>\
    \ denominator\n) {\n    long double ratio =\n        static_cast<long double>(numerator)\
    \ /\n        static_cast<long double>(denominator);\n    Point<long double> origin(ray.origin);\n\
    \    Point<long double> direction =\n        Point<long double>(ray.through) -\
    \ origin;\n    return origin + direction * ratio;\n}\n\n}  // namespace ray_detail\n\
    \ntemplate <Coordinate T>\nbool on_ray(\n    const Ray<T>& ray,\n    const Point<T>&\
    \ point,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    if (orientation(ray.origin, ray.through, point, eps) != 0) return false;\n\
    \    using W = wide_type<T>;\n    W direction_x = W(ray.through.x) - W(ray.origin.x);\n\
    \    W direction_y = W(ray.through.y) - W(ray.origin.y);\n    W offset_x = W(point.x)\
    \ - W(ray.origin.x);\n    W offset_y = W(point.y) - W(ray.origin.y);\n    return\
    \ sign<T>(direction_x * offset_x + direction_y * offset_y, eps) >= 0;\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> projection(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    assert(ray.origin != ray.through);\n    Point<long double> origin(ray.origin);\n\
    \    Point<long double> direction =\n        Point<long double>(ray.through) -\
    \ origin;\n    Point<long double> offset = Point<long double>(point) - origin;\n\
    \    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    if (ratio < 0) ratio = 0;\n    return origin + direction * ratio;\n}\n\n\
    template <Coordinate T>\nlong double distance(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    return geometry::distance(projection(ray, point), Point<long double>(point));\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& point, const\
    \ Ray<T>& ray) {\n    return distance(ray, point);\n}\n\ntemplate <Coordinate\
    \ T>\nRay<long double> reflection(const Line<T>& line, const Ray<T>& ray) {\n\
    \    assert(ray.origin != ray.through);\n    return Ray<long double>{\n      \
    \  reflection(line, ray.origin),\n        reflection(line, ray.through)\n    };\n\
    }\n\ntemplate <Coordinate T>\nRay<long double> reflected_ray(\n    const Ray<T>&\
    \ incoming,\n    const Point<T>& hit,\n    const Line<T>& mirror,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(incoming.origin != incoming.through);\n    assert(on_line(mirror,\
    \ hit, eps));\n    Point<T> translated = hit + (incoming.through - incoming.origin);\n\
    \    return Ray<long double>{\n        Point<long double>(hit),\n        reflection(mirror,\
    \ translated)\n    };\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const\
    \ Ray<T>& ray,\n    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n\
    \    assert(ray.origin != ray.through);\n    assert(line.a != line.b);\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        line.a,\n        line.b\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        return on_line(line, ray.origin, eps);\n    }\n    return\
    \ ray_detail::ratio_nonnegative<T>(\n        values.first_numerator,\n       \
    \ values.denominator,\n        eps\n    );\n}\n\ntemplate <Coordinate T>\nbool\
    \ intersects(\n    const Line<T>& line,\n    const Ray<T>& ray,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(ray, line, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Ray<T>& ray, const Line<T>& line) {\n    return\
    \ intersects(ray, line) ? 0 : distance(line, ray.origin);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Line<T>& line, const Ray<T>& ray) {\n    return\
    \ distance(ray, line);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const\
    \ Ray<T>& ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n\
    ) {\n    assert(ray.origin != ray.through);\n    if (segment.a == segment.b) return\
    \ on_ray(ray, segment.a, eps);\n\n    ray_detail::Parameters<T> values = ray_detail::parameters(\n\
    \        ray.origin,\n        ray.through,\n        segment.a,\n        segment.b\n\
    \    );\n    if (sign<T>(values.denominator, eps) == 0) {\n        if (orientation(ray.origin,\
    \ ray.through, segment.a, eps) != 0) {\n            return false;\n        }\n\
    \        return on_ray(ray, segment.a, eps) ||\n               on_ray(ray, segment.b,\
    \ eps) ||\n               on_segment(segment, ray.origin, eps);\n    }\n    return\
    \ ray_detail::ratio_nonnegative<T>(\n               values.first_numerator,\n\
    \               values.denominator,\n               eps\n           ) &&\n   \
    \        ray_detail::ratio_in_unit_interval<T>(\n               values.second_numerator,\n\
    \               values.denominator,\n               eps\n           );\n}\n\n\
    template <Coordinate T>\nbool intersects(\n    const Segment<T>& segment,\n  \
    \  const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return intersects(ray,\
    \ segment, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Ray<T>&\
    \ ray, const Segment<T>& segment) {\n    if (intersects(ray, segment)) return\
    \ 0;\n    return std::min({\n        distance(ray, segment.a),\n        distance(ray,\
    \ segment.b),\n        distance(segment, ray.origin)\n    });\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& segment, const Ray<T>& ray) {\n \
    \   return distance(ray, segment);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const Ray<T>& first,\n    const Ray<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(first.origin != first.through);\n    assert(second.origin != second.through);\n\
    \    ray_detail::Parameters<T> values = ray_detail::parameters(\n        first.origin,\n\
    \        first.through,\n        second.origin,\n        second.through\n    );\n\
    \    if (sign<T>(values.denominator, eps) == 0) {\n        if (orientation(first.origin,\
    \ first.through, second.origin, eps) != 0) {\n            return false;\n    \
    \    }\n        return on_ray(first, second.origin, eps) ||\n               on_ray(second,\
    \ first.origin, eps);\n    }\n    return ray_detail::ratio_nonnegative<T>(\n \
    \              values.first_numerator,\n               values.denominator,\n \
    \              eps\n           ) &&\n           ray_detail::ratio_nonnegative<T>(\n\
    \               values.second_numerator,\n               values.denominator,\n\
    \               eps\n           );\n}\n\ntemplate <Coordinate T>\nlong double\
    \ distance(const Ray<T>& first, const Ray<T>& second) {\n    if (intersects(first,\
    \ second)) return 0;\n    return std::min(\n        distance(first, second.origin),\n\
    \        distance(second, first.origin)\n    );\n}\n\ntemplate <Coordinate T>\n\
    std::optional<Point<long double>> ray_line_intersection(\n    const Ray<T>& ray,\n\
    \    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin\
    \ != ray.through);\n    assert(line.a != line.b);\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        line.a,\n        line.b\n    );\n    if (\n        sign<T>(values.denominator,\
    \ eps) == 0 ||\n        !ray_detail::ratio_nonnegative<T>(\n            values.first_numerator,\n\
    \            values.denominator,\n            eps\n        )\n    ) {\n      \
    \  return std::nullopt;\n    }\n    return ray_detail::point_at(\n        ray,\n\
    \        values.first_numerator,\n        values.denominator\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> ray_line_intersection(\n \
    \   const Line<T>& line,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    return ray_line_intersection(ray, line, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nstd::optional<Point<long double>> ray_segment_intersection(\n    const Ray<T>&\
    \ ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n) {\n  \
    \  assert(ray.origin != ray.through);\n    if (segment.a == segment.b) {\n   \
    \     if (on_ray(ray, segment.a, eps)) {\n            return Point<long double>(segment.a);\n\
    \        }\n        return std::nullopt;\n    }\n\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        segment.a,\n        segment.b\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        if (orientation(ray.origin, ray.through, segment.a, eps)\
    \ != 0) {\n            return std::nullopt;\n        }\n        if (\n       \
    \     segment.a == ray.origin &&\n            !on_ray(ray, segment.b, eps)\n \
    \       ) {\n            return Point<long double>(ray.origin);\n        }\n \
    \       if (\n            segment.b == ray.origin &&\n            !on_ray(ray,\
    \ segment.a, eps)\n        ) {\n            return Point<long double>(ray.origin);\n\
    \        }\n        return std::nullopt;\n    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n\
    \            values.first_numerator,\n            values.denominator,\n      \
    \      eps\n        ) ||\n        !ray_detail::ratio_in_unit_interval<T>(\n  \
    \          values.second_numerator,\n            values.denominator,\n       \
    \     eps\n        )\n    ) {\n        return std::nullopt;\n    }\n    return\
    \ ray_detail::point_at(\n        ray,\n        values.first_numerator,\n     \
    \   values.denominator\n    );\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> ray_segment_intersection(\n    const Segment<T>& segment,\n    const\
    \ Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return ray_segment_intersection(ray,\
    \ segment, eps);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>>\
    \ ray_intersection(\n    const Ray<T>& first,\n    const Ray<T>& second,\n   \
    \ long double eps = 1e-12L\n) {\n    assert(first.origin != first.through);\n\
    \    assert(second.origin != second.through);\n    ray_detail::Parameters<T> values\
    \ = ray_detail::parameters(\n        first.origin,\n        first.through,\n \
    \       second.origin,\n        second.through\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        if (\n            first.origin != second.origin ||\n \
    \           orientation(\n                first.origin,\n                first.through,\n\
    \                second.through,\n                eps\n            ) != 0\n  \
    \      ) {\n            return std::nullopt;\n        }\n        using W = wide_type<T>;\n\
    \        W first_x = W(first.through.x) - W(first.origin.x);\n        W first_y\
    \ = W(first.through.y) - W(first.origin.y);\n        W second_x = W(second.through.x)\
    \ - W(second.origin.x);\n        W second_y = W(second.through.y) - W(second.origin.y);\n\
    \        if (sign<T>(first_x * second_x + first_y * second_y, eps) < 0) {\n  \
    \          return Point<long double>(first.origin);\n        }\n        return\
    \ std::nullopt;\n    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n\
    \            values.first_numerator,\n            values.denominator,\n      \
    \      eps\n        ) ||\n        !ray_detail::ratio_nonnegative<T>(\n       \
    \     values.second_numerator,\n            values.denominator,\n            eps\n\
    \        )\n    ) {\n        return std::nullopt;\n    }\n    return ray_detail::point_at(\n\
    \        first,\n        values.first_numerator,\n        values.denominator\n\
    \    );\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 14 \"\
    geometry/polygon.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\nenum class\
    \ PointInPolygon {\n    Outside = 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\
    \ntemplate <Coordinate T>\nconstexpr Point<long double> centroid(\n    const std::array<Point<T>,\
    \ 3>& triangle\n) {\n    return Point<long double>(\n        (\n            static_cast<long\
    \ double>(triangle[0].x) +\n            static_cast<long double>(triangle[1].x)\
    \ +\n            static_cast<long double>(triangle[2].x)\n        ) / 3,\n   \
    \     (\n            static_cast<long double>(triangle[0].y) +\n            static_cast<long\
    \ double>(triangle[1].y) +\n            static_cast<long double>(triangle[2].y)\n\
    \        ) / 3\n    );\n}\n\nnamespace polygon_detail {\n\ninline bool close(\n\
    \    const Point<long double>& first,\n    const Point<long double>& second,\n\
    \    long double eps\n) {\n    return geometry::distance(first, second) <= eps;\n\
    }\n\ninline void push_unique(\n    std::vector<Point<long double>>& points,\n\
    \    const Point<long double>& point,\n    long double eps\n) {\n    for (const\
    \ Point<long double>& existing : points) {\n        if (close(existing, point,\
    \ eps)) return;\n    }\n    points.push_back(point);\n}\n\ntemplate <Coordinate\
    \ T>\nstd::vector<Point<T>> clean_polygon_vertices(\n    std::vector<Point<T>>\
    \ polygon,\n    long double eps\n) {\n    if (\n        polygon.size() >= 2 &&\n\
    \        polygon.front() == polygon.back()\n    ) {\n        polygon.pop_back();\n\
    \    }\n\n    std::vector<Point<T>> deduplicated;\n    for (const Point<T>& point\
    \ : polygon) {\n        if (deduplicated.empty() || deduplicated.back() != point)\
    \ {\n            deduplicated.push_back(point);\n        }\n    }\n    if (\n\
    \        deduplicated.size() >= 2 &&\n        deduplicated.front() == deduplicated.back()\n\
    \    ) {\n        deduplicated.pop_back();\n    }\n\n    bool changed = true;\n\
    \    while (changed && deduplicated.size() >= 3) {\n        changed = false;\n\
    \        std::vector<Point<T>> cleaned;\n        std::size_t size = deduplicated.size();\n\
    \        for (std::size_t index = 0; index < size; ++index) {\n            const\
    \ Point<T>& previous =\n                deduplicated[(index + size - 1) % size];\n\
    \            const Point<T>& current = deduplicated[index];\n            const\
    \ Point<T>& next =\n                deduplicated[(index + 1) % size];\n      \
    \      if (\n                orientation(previous, current, next, eps) == 0 &&\n\
    \                sign<T>(dot(current - previous, next - current), eps) >= 0\n\
    \            ) {\n                changed = true;\n            } else {\n    \
    \            cleaned.push_back(current);\n            }\n        }\n        deduplicated\
    \ = std::move(cleaned);\n    }\n    return deduplicated;\n}\n\ntemplate <Coordinate\
    \ T>\nbool in_ccw_triangle(\n    const Point<T>& point,\n    const Point<T>& first,\n\
    \    const Point<T>& second,\n    const Point<T>& third,\n    long double eps\n\
    ) {\n    return\n        orientation(first, second, point, eps) >= 0 &&\n    \
    \    orientation(second, third, point, eps) >= 0 &&\n        orientation(third,\
    \ first, point, eps) >= 0;\n}\n\n}  // namespace polygon_detail\n\ntemplate <Coordinate\
    \ T>\nwide_type<T> polygon_area2(const std::vector<Point<T>>& polygon) {\n   \
    \ wide_type<T> result = 0;\n    std::size_t n = polygon.size();\n    for (std::size_t\
    \ i = 0; i < n; i++) {\n        result += cross(polygon[i], polygon[(i + 1) %\
    \ n]);\n    }\n    return result;\n}\n\ntemplate <Coordinate T>\nlong double polygon_area(const\
    \ std::vector<Point<T>>& polygon) {\n    return std::fabs(static_cast<long double>(polygon_area2(polygon)))\
    \ / 2;\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> polygon_centroid(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n\
    \    if (polygon.size() < 3) return std::nullopt;\n\n    wide_type<T> signed_area2\
    \ = polygon_area2(polygon);\n    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;\n\
    \n    long double x_numerator = 0;\n    long double y_numerator = 0;\n    std::size_t\
    \ size = polygon.size();\n    for (std::size_t index = 0; index < size; ++index)\
    \ {\n        const Point<T>& current = polygon[index];\n        const Point<T>&\
    \ next = polygon[(index + 1) % size];\n        long double weight = static_cast<long\
    \ double>(cross(current, next));\n        x_numerator +=\n            (static_cast<long\
    \ double>(current.x) +\n             static_cast<long double>(next.x)) *\n   \
    \         weight;\n        y_numerator +=\n            (static_cast<long double>(current.y)\
    \ +\n             static_cast<long double>(next.y)) *\n            weight;\n \
    \   }\n    long double denominator =\n        3.0L * static_cast<long double>(signed_area2);\n\
    \    return Point<long double>(\n        x_numerator / denominator,\n        y_numerator\
    \ / denominator\n    );\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> centroid(\n    const std::vector<Point<T>>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    return polygon_centroid(polygon, eps);\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> polygon_center_of_gravity(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n\
    \    return polygon_centroid(polygon, eps);\n}\n\ntemplate <Coordinate T>\nbool\
    \ is_simple_polygon(\n    const std::vector<Point<T>>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    if (polygon.size() < 3) return false;\n    std::size_t\
    \ size = polygon.size();\n    for (std::size_t index = 0; index < size; ++index)\
    \ {\n        const Point<T>& previous = polygon[(index + size - 1) % size];\n\
    \        const Point<T>& current = polygon[index];\n        const Point<T>& next\
    \ = polygon[(index + 1) % size];\n        if (current == next) return false;\n\
    \        if (\n            orientation(previous, current, next, eps) == 0 &&\n\
    \            sign<T>(dot(current - previous, next - current), eps) < 0\n     \
    \   ) {\n            return false;\n        }\n    }\n    for (std::size_t first_index\
    \ = 0; first_index < size; ++first_index) {\n        Segment<T> first{\n     \
    \       polygon[first_index],\n            polygon[(first_index + 1) % size]\n\
    \        };\n        for (\n            std::size_t second_index = first_index\
    \ + 1;\n            second_index < size;\n            ++second_index\n       \
    \ ) {\n            bool adjacent =\n                second_index == first_index\
    \ + 1 ||\n                (first_index == 0 && second_index + 1 == size);\n  \
    \          if (adjacent) continue;\n\n            Segment<T> second{\n       \
    \         polygon[second_index],\n                polygon[(second_index + 1) %\
    \ size]\n            };\n            if (intersects(first, second, eps)) return\
    \ false;\n        }\n    }\n    return true;\n}\n\ntemplate <Coordinate T>\nstd::optional<std::vector<std::array<Point<T>,\
    \ 3>>> triangulate_polygon(\n    std::vector<Point<T>> polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    polygon =\n        polygon_detail::clean_polygon_vertices(std::move(polygon),\
    \ eps);\n    if (polygon.size() < 3) return std::nullopt;\n\n    wide_type<T>\
    \ signed_area2 = polygon_area2(polygon);\n    if (sign<T>(signed_area2, eps) ==\
    \ 0) return std::nullopt;\n    if (!is_simple_polygon(polygon, eps)) return std::nullopt;\n\
    \    if (sign<T>(signed_area2, eps) < 0) {\n        std::reverse(polygon.begin(),\
    \ polygon.end());\n    }\n\n    std::vector<std::size_t> remaining(polygon.size());\n\
    \    for (std::size_t index = 0; index < polygon.size(); ++index) {\n        remaining[index]\
    \ = index;\n    }\n\n    std::vector<std::array<Point<T>, 3>> result;\n    result.reserve(polygon.size()\
    \ - 2);\n    while (remaining.size() > 3) {\n        bool found_ear = false;\n\
    \        std::size_t size = remaining.size();\n        for (std::size_t position\
    \ = 0; position < size; ++position) {\n            std::size_t previous_index\
    \ =\n                remaining[(position + size - 1) % size];\n            std::size_t\
    \ current_index = remaining[position];\n            std::size_t next_index =\n\
    \                remaining[(position + 1) % size];\n            const Point<T>&\
    \ previous = polygon[previous_index];\n            const Point<T>& current = polygon[current_index];\n\
    \            const Point<T>& next = polygon[next_index];\n            if (orientation(previous,\
    \ current, next, eps) <= 0) continue;\n\n            bool contains_vertex = false;\n\
    \            for (std::size_t other_index : remaining) {\n                if (\n\
    \                    other_index == previous_index ||\n                    other_index\
    \ == current_index ||\n                    other_index == next_index\n       \
    \         ) {\n                    continue;\n                }\n            \
    \    if (\n                    polygon_detail::in_ccw_triangle(\n            \
    \            polygon[other_index],\n                        previous,\n      \
    \                  current,\n                        next,\n                 \
    \       eps\n                    )\n                ) {\n                    contains_vertex\
    \ = true;\n                    break;\n                }\n            }\n    \
    \        if (contains_vertex) continue;\n\n            std::array<Point<T>, 3>\
    \ triangle;\n            triangle[0] = previous;\n            triangle[1] = current;\n\
    \            triangle[2] = next;\n            result.push_back(std::move(triangle));\n\
    \            remaining.erase(\n                remaining.begin() +\n         \
    \       static_cast<std::ptrdiff_t>(position)\n            );\n            found_ear\
    \ = true;\n            break;\n        }\n        if (!found_ear) return std::nullopt;\n\
    \    }\n\n    std::array<Point<T>, 3> triangle;\n    triangle[0] = polygon[remaining[0]];\n\
    \    triangle[1] = polygon[remaining[1]];\n    triangle[2] = polygon[remaining[2]];\n\
    \    if (orientation(triangle[0], triangle[1], triangle[2], eps) <= 0) {\n   \
    \     return std::nullopt;\n    }\n    result.push_back(std::move(triangle));\n\
    \    return result;\n}\n\ntemplate <Coordinate T>\nPointInPolygon point_in_polygon(\n\
    \    const std::vector<Point<T>>& polygon,\n    const Point<T>& point,\n    long\
    \ double eps = 1e-12L\n) {\n    bool inside = false;\n    std::size_t n = polygon.size();\n\
    \    for (std::size_t i = 0; i < n; i++) {\n        const Point<T>& a = polygon[i];\n\
    \        const Point<T>& b = polygon[(i + 1) % n];\n        if (on_segment(Segment<T>{a,\
    \ b}, point, eps)) {\n            return PointInPolygon::Boundary;\n        }\n\
    \n        if (a.y <= point.y) {\n            if (point.y < b.y && orientation(a,\
    \ b, point, eps) > 0) {\n                inside = !inside;\n            }\n  \
    \      } else if (b.y <= point.y && orientation(a, b, point, eps) < 0) {\n   \
    \         inside = !inside;\n        }\n    }\n    return inside ? PointInPolygon::Inside\
    \ : PointInPolygon::Outside;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long\
    \ double>> ray_polygon_intersections(\n    const Ray<T>& ray,\n    const std::vector<Point<T>>&\
    \ polygon,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    assert(polygon.size() >= 3);\n    std::vector<Point<long double>> result;\n\
    \    std::size_t size = polygon.size();\n    for (std::size_t index = 0; index\
    \ < size; ++index) {\n        Segment<T> edge{\n            polygon[index],\n\
    \            polygon[(index + 1) % size]\n        };\n        std::optional<Point<long\
    \ double>> point =\n            ray_segment_intersection(ray, edge, eps);\n  \
    \      if (point.has_value()) {\n            polygon_detail::push_unique(result,\
    \ *point, eps);\n            continue;\n        }\n        if (\n            orientation(ray.origin,\
    \ ray.through, edge.a, eps) == 0 &&\n            orientation(ray.origin, ray.through,\
    \ edge.b, eps) == 0\n        ) {\n            if (on_ray(ray, edge.a, eps)) {\n\
    \                polygon_detail::push_unique(\n                    result,\n \
    \                   Point<long double>(edge.a),\n                    eps\n   \
    \             );\n            }\n            if (on_ray(ray, edge.b, eps)) {\n\
    \                polygon_detail::push_unique(\n                    result,\n \
    \                   Point<long double>(edge.b),\n                    eps\n   \
    \             );\n            }\n            if (on_segment(edge, ray.origin,\
    \ eps)) {\n                polygon_detail::push_unique(\n                    result,\n\
    \                    Point<long double>(ray.origin),\n                    eps\n\
    \                );\n            }\n        }\n    }\n\n    Point<long double>\
    \ origin(ray.origin);\n    Point<long double> direction =\n        Point<long\
    \ double>(ray.through) - origin;\n    std::sort(\n        result.begin(),\n  \
    \      result.end(),\n        [&](const Point<long double>& first, const Point<long\
    \ double>& second) {\n            return dot(first - origin, direction) <\n  \
    \                 dot(second - origin, direction);\n        }\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> first_ray_polygon_intersection(\n\
    \    const Ray<T>& ray,\n    const std::vector<Point<T>>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    std::vector<Point<long double>> points =\n        ray_polygon_intersections(ray,\
    \ polygon, eps);\n    if (points.empty()) return std::nullopt;\n    return points.front();\n\
    }\n\ntemplate <Coordinate T>\nbool intersects(\n    const Ray<T>& ray,\n    const\
    \ std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n    assert(polygon.size()\
    \ >= 3);\n    if (point_in_polygon(polygon, ray.origin, eps) != PointInPolygon::Outside)\
    \ {\n        return true;\n    }\n    return !ray_polygon_intersections(ray, polygon,\
    \ eps).empty();\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const std::vector<Point<T>>&\
    \ polygon,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return\
    \ intersects(ray, polygon, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(\n\
    \    const Ray<T>& ray,\n    const std::vector<Point<T>>& polygon\n) {\n    assert(polygon.size()\
    \ >= 3);\n    if (intersects(ray, polygon)) return 0;\n    long double result\
    \ = std::numeric_limits<long double>::infinity();\n    std::size_t size = polygon.size();\n\
    \    for (std::size_t index = 0; index < size; ++index) {\n        result = std::min(\n\
    \            result,\n            distance(\n                ray,\n          \
    \      Segment<T>{\n                    polygon[index],\n                    polygon[(index\
    \ + 1) % size]\n                }\n            )\n        );\n    }\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nlong double distance(\n    const std::vector<Point<T>>&\
    \ polygon,\n    const Ray<T>& ray\n) {\n    return distance(ray, polygon);\n}\n\
    \ntemplate <Coordinate T>\nbool intersects(\n    const std::vector<Point<T>>&\
    \ first,\n    const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(first.size() >= 3);\n    assert(second.size() >= 3);\n    std::size_t\
    \ first_size = first.size();\n    std::size_t second_size = second.size();\n \
    \   for (\n        std::size_t first_index = 0;\n        first_index < first_size;\n\
    \        ++first_index\n    ) {\n        Segment<T> first_edge{\n            first[first_index],\n\
    \            first[(first_index + 1) % first_size]\n        };\n        for (\n\
    \            std::size_t second_index = 0;\n            second_index < second_size;\n\
    \            ++second_index\n        ) {\n            Segment<T> second_edge{\n\
    \                second[second_index],\n                second[(second_index +\
    \ 1) % second_size]\n            };\n            if (intersects(first_edge, second_edge,\
    \ eps)) return true;\n        }\n    }\n    return\n        point_in_polygon(first,\
    \ second.front(), eps) !=\n            PointInPolygon::Outside ||\n        point_in_polygon(second,\
    \ first.front(), eps) !=\n            PointInPolygon::Outside;\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(\n    const std::vector<Point<T>>& first,\n\
    \    const std::vector<Point<T>>& second\n) {\n    assert(first.size() >= 3);\n\
    \    assert(second.size() >= 3);\n    if (intersects(first, second)) return 0;\n\
    \n    long double result = std::numeric_limits<long double>::infinity();\n   \
    \ std::size_t first_size = first.size();\n    std::size_t second_size = second.size();\n\
    \    for (\n        std::size_t first_index = 0;\n        first_index < first_size;\n\
    \        ++first_index\n    ) {\n        Segment<T> first_edge{\n            first[first_index],\n\
    \            first[(first_index + 1) % first_size]\n        };\n        for (\n\
    \            std::size_t second_index = 0;\n            second_index < second_size;\n\
    \            ++second_index\n        ) {\n            Segment<T> second_edge{\n\
    \                second[second_index],\n                second[(second_index +\
    \ 1) % second_size]\n            };\n            result = std::min(result, distance(first_edge,\
    \ second_edge));\n        }\n    }\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 21 \"geometry/convex_decomposition.hpp\"\n\n\
    namespace m1une {\nnamespace geometry {\n\nnamespace convex_decomposition_detail\
    \ {\n\nusing Index = std::size_t;\nusing IndexPolygon = std::vector<Index>;\n\n\
    enum class ExactPredicateWidth { Int128, Int256, Int512 };\n\ntemplate <std::integral\
    \ T>\nstd::size_t coordinate_magnitude_bits(\n    const std::vector<Point<T>>&\
    \ polygon\n) {\n    using Unsigned = std::make_unsigned_t<T>;\n    std::size_t\
    \ result = 0;\n    auto update = [&](T coordinate) {\n        Unsigned magnitude\
    \ = static_cast<Unsigned>(coordinate);\n        if constexpr (std::signed_integral<T>)\
    \ {\n            if (coordinate < 0) magnitude = Unsigned(0) - magnitude;\n  \
    \      }\n        std::size_t bits = 0;\n        while (magnitude != 0) {\n  \
    \          ++bits;\n            magnitude >>= 1;\n        }\n        result =\
    \ std::max(result, bits);\n    };\n    for (const Point<T>& point : polygon) {\n\
    \        update(point.x);\n        update(point.y);\n    }\n    return result;\n\
    }\n\ntemplate <std::integral T>\nExactPredicateWidth select_exact_predicate_width(\n\
    \    const std::vector<Point<T>>& polygon\n) {\n    static_assert(sizeof(T) <=\
    \ sizeof(std::uint64_t));\n    const std::size_t coordinate_bits =\n        coordinate_magnitude_bits(polygon);\n\
    \    // Cross-multiplied ray parameters and projective visibility\n    // determinants\
    \ have magnitude below 2^(4 * coordinate_bits + 6).\n    const std::size_t required_bits\
    \ = 4 * coordinate_bits + 7;\n    if (required_bits <= 128) return ExactPredicateWidth::Int128;\n\
    \    if (required_bits <= 256) return ExactPredicateWidth::Int256;\n    assert(required_bits\
    \ <= 512);\n    return ExactPredicateWidth::Int512;\n}\n\ntemplate <typename Number,\
    \ Coordinate T>\nNumber predicate_number(T value) {\n    return static_cast<Number>(value);\n\
    }\n\ntemplate <Coordinate T, typename Number>\nint predicate_sign(const Number&\
    \ value, long double eps) {\n    if constexpr (std::integral<T>) {\n        return\
    \ (value > 0) - (value < 0);\n    } else {\n        return (value > eps) - (value\
    \ < -eps);\n    }\n}\n\ntemplate <Coordinate T>\nstd::optional<std::vector<Point<T>>>\
    \ prepare_polygon(\n    std::vector<Point<T>> polygon,\n    long double eps\n\
    ) {\n    polygon =\n        polygon_detail::clean_polygon_vertices(std::move(polygon),\
    \ eps);\n    if (polygon.size() < 3) return std::nullopt;\n    const int area_sign\
    \ = sign<T>(polygon_area2(polygon), eps);\n    if (area_sign == 0 || !is_simple_polygon(polygon,\
    \ eps)) {\n        return std::nullopt;\n    }\n    if (area_sign < 0) std::reverse(polygon.begin(),\
    \ polygon.end());\n    return polygon;\n}\n\ntemplate <Coordinate T>\nbool is_weakly_convex(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps\n) {\n    if (polygon.size()\
    \ < 3) return false;\n    for (Index index = 0; index < polygon.size(); ++index)\
    \ {\n        if (\n            orientation(\n                polygon[index],\n\
    \                polygon[(index + 1) % polygon.size()],\n                polygon[(index\
    \ + 2) % polygon.size()],\n                eps\n            ) < 0\n        ) {\n\
    \            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<std::vector<IndexPolygon>> triangulate_indices(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps\n) {\n    const\
    \ Index size = polygon.size();\n    std::vector<Index> previous(size), next(size);\n\
    \    std::vector<bool> active(size, true);\n    for (Index index = 0; index <\
    \ size; ++index) {\n        previous[index] = (index + size - 1) % size;\n   \
    \     next[index] = (index + 1) % size;\n    }\n\n    auto is_ear = [&](Index\
    \ index) {\n        if (!active[index]) return false;\n        const Index first\
    \ = previous[index];\n        const Index third = next[index];\n        if (\n\
    \            orientation(\n                polygon[first], polygon[index], polygon[third],\
    \ eps\n            ) <= 0\n        ) {\n            return false;\n        }\n\
    \        for (Index other = 0; other < size; ++other) {\n            if (\n  \
    \              !active[other] || other == first || other == index ||\n       \
    \         other == third\n            ) {\n                continue;\n       \
    \     }\n            if (\n                polygon_detail::in_ccw_triangle(\n\
    \                    polygon[other],\n                    polygon[first],\n  \
    \                  polygon[index],\n                    polygon[third],\n    \
    \                eps\n                )\n            ) {\n                return\
    \ false;\n            }\n        }\n        return true;\n    };\n\n    std::deque<Index>\
    \ ears;\n    for (Index index = 0; index < size; ++index) {\n        if (is_ear(index))\
    \ ears.push_back(index);\n    }\n\n    std::vector<IndexPolygon> triangles;\n\
    \    triangles.reserve(size - 2);\n    Index remaining = size;\n    while (remaining\
    \ > 3) {\n        while (!ears.empty() && !is_ear(ears.front())) {\n         \
    \   ears.pop_front();\n        }\n        if (ears.empty()) return std::nullopt;\n\
    \n        const Index ear = ears.front();\n        ears.pop_front();\n       \
    \ const Index first = previous[ear];\n        const Index third = next[ear];\n\
    \        triangles.push_back(IndexPolygon{first, ear, third});\n\n        active[ear]\
    \ = false;\n        next[first] = third;\n        previous[third] = first;\n \
    \       --remaining;\n        if (is_ear(first)) ears.push_back(first);\n    \
    \    if (is_ear(third)) ears.push_back(third);\n    }\n\n    Index first = 0;\n\
    \    while (first < size && !active[first]) ++first;\n    if (first == size) return\
    \ std::nullopt;\n    const Index second = next[first];\n    const Index third\
    \ = next[second];\n    if (\n        third == first || next[third] != first ||\n\
    \        orientation(\n            polygon[first], polygon[second], polygon[third],\
    \ eps\n        ) <= 0\n    ) {\n        return std::nullopt;\n    }\n    triangles.push_back(IndexPolygon{first,\
    \ second, third});\n    return triangles;\n}\n\ninline Index find_root(std::vector<Index>&\
    \ parent, Index index) {\n    Index root = index;\n    while (parent[root] !=\
    \ root) root = parent[root];\n    while (parent[index] != index) {\n        const\
    \ Index next = parent[index];\n        parent[index] = root;\n        index =\
    \ next;\n    }\n    return root;\n}\n\ninline std::optional<IndexPolygon> merge_across_edge(\n\
    \    const IndexPolygon& first,\n    const IndexPolygon& second,\n    Index edge_first,\n\
    \    Index edge_second\n) {\n    for (Index first_position = 0;\n         first_position\
    \ < first.size();\n         ++first_position) {\n        const Index first_next\
    \ = (first_position + 1) % first.size();\n        const Index from = first[first_position];\n\
    \        const Index to = first[first_next];\n        if (\n            !(\n \
    \               (from == edge_first && to == edge_second) ||\n               \
    \ (from == edge_second && to == edge_first)\n            )\n        ) {\n    \
    \        continue;\n        }\n\n        for (Index second_position = 0;\n   \
    \          second_position < second.size();\n             ++second_position) {\n\
    \            const Index second_next =\n                (second_position + 1)\
    \ % second.size();\n            if (\n                second[second_position]\
    \ != to ||\n                second[second_next] != from\n            ) {\n   \
    \             continue;\n            }\n\n            IndexPolygon merged;\n \
    \           merged.reserve(first.size() + second.size() - 2);\n            for\
    \ (Index position = first_next;\n                 position != first_position;\n\
    \                 position = (position + 1) % first.size()) {\n              \
    \  merged.push_back(first[position]);\n            }\n            for (Index position\
    \ = second_next;\n                 position != second_position;\n            \
    \     position = (position + 1) % second.size()) {\n                merged.push_back(second[position]);\n\
    \            }\n            return merged;\n        }\n    }\n    return std::nullopt;\n\
    }\n\ntemplate <Coordinate T>\nbool is_weakly_convex(\n    const IndexPolygon&\
    \ polygon,\n    const std::vector<Point<T>>& points,\n    long double eps\n) {\n\
    \    for (Index index = 0; index < polygon.size(); ++index) {\n        if (\n\
    \            orientation(\n                points[polygon[index]],\n         \
    \       points[polygon[(index + 1) % polygon.size()]],\n                points[polygon[(index\
    \ + 2) % polygon.size()]],\n                eps\n            ) < 0\n        )\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::vector<Point<T>> materialize(\n    const IndexPolygon&\
    \ indices,\n    const std::vector<Point<T>>& points,\n    long double eps\n) {\n\
    \    std::vector<Point<T>> polygon;\n    polygon.reserve(indices.size());\n  \
    \  for (const Index index : indices) polygon.push_back(points[index]);\n    return\
    \ polygon_detail::clean_polygon_vertices(std::move(polygon), eps);\n}\n\nstruct\
    \ Diagonal {\n    Index first;\n    Index second;\n};\n\ntemplate <Coordinate\
    \ T>\nstd::optional<std::vector<Point<T>>> prepare_minimum_polygon(\n    std::vector<Point<T>>\
    \ polygon,\n    long double eps\n) {\n    if (polygon.size() >= 2 && polygon.front()\
    \ == polygon.back()) {\n        polygon.pop_back();\n    }\n    std::vector<Point<T>>\
    \ distinct;\n    distinct.reserve(polygon.size());\n    for (const Point<T>& point\
    \ : polygon) {\n        if (distinct.empty() || distinct.back() != point) {\n\
    \            distinct.push_back(point);\n        }\n    }\n    if (distinct.size()\
    \ >= 2 && distinct.front() == distinct.back()) {\n        distinct.pop_back();\n\
    \    }\n    if (distinct.size() < 3) return std::nullopt;\n\n    const int original_size\
    \ = static_cast<int>(distinct.size());\n    std::vector<int> previous(original_size),\
    \ next(original_size);\n    std::vector<bool> removed(original_size, false);\n\
    \    std::deque<int> candidates;\n    for (int index = 0; index < original_size;\
    \ ++index) {\n        previous[index] = (index + original_size - 1) % original_size;\n\
    \        next[index] = (index + 1) % original_size;\n        candidates.push_back(index);\n\
    \    }\n    int remaining = original_size;\n    while (!candidates.empty() &&\
    \ remaining >= 3) {\n        const int index = candidates.front();\n        candidates.pop_front();\n\
    \        if (removed[index]) continue;\n        const int before = previous[index];\n\
    \        const int after = next[index];\n        if (\n            orientation(\n\
    \                distinct[before], distinct[index], distinct[after], eps\n   \
    \         ) != 0 ||\n            sign<T>(\n                dot(\n            \
    \        distinct[index] - distinct[before],\n                    distinct[after]\
    \ - distinct[index]\n                ),\n                eps\n            ) <\
    \ 0\n        ) {\n            continue;\n        }\n        removed[index] = true;\n\
    \        next[before] = after;\n        previous[after] = before;\n        --remaining;\n\
    \        candidates.push_back(before);\n        candidates.push_back(after);\n\
    \    }\n    if (remaining < 3) return std::nullopt;\n\n    std::vector<Point<T>>\
    \ cleaned;\n    cleaned.reserve(static_cast<Index>(remaining));\n    int first\
    \ = 0;\n    while (removed[first]) ++first;\n    int index = first;\n    do {\n\
    \        cleaned.push_back(distinct[index]);\n        index = next[index];\n \
    \   } while (index != first);\n\n    const int area_sign = sign<T>(polygon_area2(cleaned),\
    \ eps);\n    if (area_sign == 0) return std::nullopt;\n    if (area_sign < 0)\
    \ std::reverse(cleaned.begin(), cleaned.end());\n    return cleaned;\n}\n\ntemplate\
    \ <Coordinate T, typename Number>\nclass BiasedPolygonReduction {\n   private:\n\
    \    struct Vector {\n        Number x;\n        Number y;\n    };\n\n    struct\
    \ Fraction {\n        Number numerator;\n        Number denominator;\n    };\n\
    \n    struct Chain {\n        int first_edge;\n        int edge_count;\n    };\n\
    \n   public:\n    struct Result {\n        std::vector<Point<T>> polygon;\n  \
    \      std::vector<Index> original_index;\n    };\n\n    BiasedPolygonReduction(\n\
    \        const std::vector<Point<T>>& polygon,\n        long double eps\n    )\n\
    \        : polygon_(polygon),\n          eps_(eps),\n          size_(static_cast<int>(polygon.size())),\n\
    \          marked_edge_(polygon.size(), false) {\n        for (int index = 0;\
    \ index < size_; ++index) {\n            if (\n                orientation(\n\
    \                    polygon_[(index + size_ - 1) % size_],\n                \
    \    polygon_[index],\n                    polygon_[(index + 1) % size_],\n  \
    \                  eps_\n                ) < 0\n            ) {\n            \
    \    reflex_vertices_.push_back(index);\n            }\n        }\n        build_chains();\n\
    \    }\n\n    Result run() {\n        for (const int reflex : reflex_vertices_)\
    \ {\n            marked_edge_[(reflex + size_ - 1) % size_] = true;\n        \
    \    marked_edge_[reflex] = true;\n        }\n\n        std::vector<std::vector<int>>\
    \ extension_endpoints(size_);\n        for (const int reflex : reflex_vertices_)\
    \ {\n            const Vector direction = vector_between(\n                reflex,\
    \ (reflex + 1) % size_\n            );\n            for (const int edge : ray_shoot(reflex,\
    \ direction)) {\n                marked_edge_[edge] = true;\n                extension_endpoints[reflex].push_back(edge);\n\
    \                extension_endpoints[reflex].push_back((edge + 1) % size_);\n\
    \            }\n        }\n\n        for (Index first = 0; first < reflex_vertices_.size();\
    \ ++first) {\n            for (Index second = first + 1;\n                 second\
    \ < reflex_vertices_.size();\n                 ++second) {\n                const\
    \ int first_vertex = reflex_vertices_[first];\n                const int second_vertex\
    \ = reflex_vertices_[second];\n                mark_ray(\n                   \
    \ first_vertex,\n                    vector_between(first_vertex, second_vertex)\n\
    \                );\n                mark_ray(\n                    second_vertex,\n\
    \                    vector_between(second_vertex, first_vertex)\n           \
    \     );\n            }\n        }\n        for (const int reflex : reflex_vertices_)\
    \ {\n            auto& endpoints = extension_endpoints[reflex];\n            std::sort(endpoints.begin(),\
    \ endpoints.end());\n            endpoints.erase(\n                std::unique(endpoints.begin(),\
    \ endpoints.end()),\n                endpoints.end()\n            );\n       \
    \     for (const int endpoint : endpoints) {\n                if (endpoint ==\
    \ reflex) continue;\n                mark_ray(\n                    reflex, vector_between(reflex,\
    \ endpoint)\n                );\n            }\n        }\n\n        Result result;\n\
    \        for (int index = 0; index < size_; ++index) {\n            if (\n   \
    \             marked_edge_[index] ||\n                marked_edge_[(index + size_\
    \ - 1) % size_]\n            ) {\n                result.polygon.push_back(polygon_[index]);\n\
    \                result.original_index.push_back(static_cast<Index>(index));\n\
    \            }\n        }\n        return result;\n    }\n\n   private:\n    const\
    \ std::vector<Point<T>>& polygon_;\n    long double eps_;\n    int size_;\n  \
    \  std::vector<int> reflex_vertices_;\n    std::vector<Chain> chains_;\n    std::vector<bool>\
    \ marked_edge_;\n\n    Vector vector_between(int first, int second) const {\n\
    \        return {\n            predicate_number<Number>(polygon_[first].x) -\n\
    \                predicate_number<Number>(polygon_[second].x),\n            predicate_number<Number>(polygon_[first].y)\
    \ -\n                predicate_number<Number>(polygon_[second].y)\n        };\n\
    \    }\n\n    Number vector_cross(const Vector& first, const Vector& second) const\
    \ {\n        return first.x * second.y - first.y * second.x;\n    }\n\n    Number\
    \ vector_dot(const Vector& first, const Vector& second) const {\n        return\
    \ first.x * second.x + first.y * second.y;\n    }\n\n    int vector_sign(const\
    \ Number& value) const {\n        return predicate_sign<T>(value, eps_);\n   \
    \ }\n\n    int quadrant(const Vector& direction) const {\n        const int x_sign\
    \ = vector_sign(direction.x);\n        const int y_sign = vector_sign(direction.y);\n\
    \        if (y_sign >= 0) return x_sign >= 0 ? 0 : 1;\n        return x_sign <\
    \ 0 ? 2 : 3;\n    }\n\n    void build_chains() {\n        // Within one quadrant,\
    \ monotonically turning edge directions span at\n        // most pi/2. This gives\
    \ the bitonic sidedness needed by ray shooting\n        // without evaluating\
    \ an angle.\n        int first_edge = 0;\n        Vector previous_direction =\
    \ vector_between(1, 0);\n        int current_quadrant = quadrant(previous_direction);\n\
    \        for (int edge = 1; edge < size_; ++edge) {\n            const Vector\
    \ direction = vector_between(\n                (edge + 1) % size_, edge\n    \
    \        );\n            const int direction_quadrant = quadrant(direction);\n\
    \            if (\n                vector_sign(vector_cross(previous_direction,\
    \ direction)) <\n                    0 ||\n                direction_quadrant\
    \ != current_quadrant\n            ) {\n                chains_.push_back(Chain{\n\
    \                    first_edge, edge - first_edge\n                });\n    \
    \            first_edge = edge;\n                current_quadrant = direction_quadrant;\n\
    \            }\n            previous_direction = direction;\n        }\n     \
    \   chains_.push_back(Chain{first_edge, size_ - first_edge});\n    }\n\n    int\
    \ side(\n        int origin,\n        const Vector& direction,\n        int vertex\n\
    \    ) const {\n        return vector_sign(\n            vector_cross(\n     \
    \           direction,\n                vector_between(vertex % size_, origin)\n\
    \            )\n        );\n    }\n\n    int edge_side(const Vector& direction,\
    \ int edge) const {\n        return vector_sign(\n            vector_cross(\n\
    \                direction,\n                vector_between((edge + 1) % size_,\
    \ edge)\n            )\n        );\n    }\n\n    void crossing_on_monotone_part(\n\
    \        const Chain& chain,\n        int origin,\n        const Vector& direction,\n\
    \        int first_position,\n        int last_position,\n        std::vector<int>&\
    \ candidates\n    ) const {\n        if (first_position >= last_position) return;\n\
    \        const int first_sign = side(\n            origin,\n            direction,\n\
    \            chain.first_edge + first_position\n        );\n        const int\
    \ last_sign = side(\n            origin,\n            direction,\n           \
    \ chain.first_edge + last_position\n        );\n        if (first_sign == 0) {\n\
    \            candidates.push_back(\n                chain.first_edge + first_position\n\
    \            );\n        }\n        if (last_sign == 0) {\n            candidates.push_back(\n\
    \                chain.first_edge + last_position - 1\n            );\n      \
    \  }\n        if (first_sign == 0 || last_sign == 0 || first_sign == last_sign)\
    \ {\n            return;\n        }\n        int low = first_position;\n     \
    \   int high = last_position;\n        while (high - low > 1) {\n            const\
    \ int middle = (low + high) / 2;\n            const int middle_sign = side(\n\
    \                origin,\n                direction,\n                chain.first_edge\
    \ + middle\n            );\n            if (middle_sign == 0 || middle_sign !=\
    \ first_sign) {\n                high = middle;\n            } else {\n      \
    \          low = middle;\n            }\n        }\n        candidates.push_back(chain.first_edge\
    \ + high - 1);\n    }\n\n    void chain_candidates(\n        const Chain& chain,\n\
    \        int origin,\n        const Vector& direction,\n        std::vector<int>&\
    \ candidates\n    ) const {\n        int split = 0;\n        const int first_derivative\
    \ =\n            edge_side(direction, chain.first_edge);\n        const int last_derivative\
    \ = edge_side(\n            direction,\n            chain.first_edge + chain.edge_count\
    \ - 1\n        );\n        if (\n            first_derivative != 0 && last_derivative\
    \ != 0 &&\n            first_derivative != last_derivative\n        ) {\n    \
    \        int low = 0;\n            int high = chain.edge_count - 1;\n        \
    \    while (high - low > 1) {\n                const int middle = (low + high)\
    \ / 2;\n                const int middle_sign = edge_side(\n                 \
    \   direction, chain.first_edge + middle\n                );\n               \
    \ if (\n                    middle_sign == 0 ||\n                    middle_sign\
    \ != first_derivative\n                ) {\n                    high = middle;\n\
    \                } else {\n                    low = middle;\n               \
    \ }\n            }\n            split = high;\n        }\n        if (split ==\
    \ 0) {\n            crossing_on_monotone_part(\n                chain,\n     \
    \           origin,\n                direction,\n                0,\n        \
    \        chain.edge_count,\n                candidates\n            );\n     \
    \   } else {\n            crossing_on_monotone_part(\n                chain, origin,\
    \ direction, 0, split, candidates\n            );\n            crossing_on_monotone_part(\n\
    \                chain,\n                origin,\n                direction,\n\
    \                split,\n                chain.edge_count,\n                candidates\n\
    \            );\n        }\n    }\n\n    std::vector<int> ray_shoot(\n       \
    \ int origin,\n        const Vector& direction\n    ) const {\n        std::vector<int>\
    \ candidates;\n        for (const Chain& chain : chains_) {\n            chain_candidates(chain,\
    \ origin, direction, candidates);\n        }\n        std::sort(candidates.begin(),\
    \ candidates.end());\n        candidates.erase(\n            std::unique(candidates.begin(),\
    \ candidates.end()),\n            candidates.end()\n        );\n\n        if constexpr\
    \ (std::integral<T>) {\n            return exact_ray_shoot(origin, direction,\
    \ candidates);\n        } else {\n            return floating_ray_shoot(origin,\
    \ direction, candidates);\n        }\n    }\n\n    std::vector<int> exact_ray_shoot(\n\
    \        int origin,\n        const Vector& direction,\n        const std::vector<int>&\
    \ candidates\n    ) const {\n        // Intersections are rational parameters\
    \ along the ray. Keep their\n        // numerators and denominators and compare\
    \ them by cross products.\n        std::optional<Fraction> best;\n        std::vector<int>\
    \ result;\n        const Number direction_norm2 = vector_dot(direction, direction);\n\
    \        for (int edge : candidates) {\n            edge %= size_;\n         \
    \   const Vector first = vector_between(edge, origin);\n            const Vector\
    \ second = vector_between(\n                (edge + 1) % size_, origin\n     \
    \       );\n            const Vector edge_direction = vector_between(\n      \
    \          (edge + 1) % size_, edge\n            );\n            Number denominator\
    \ = vector_cross(direction, edge_direction);\n            Fraction parameter{0,\
    \ 1};\n            bool valid = false;\n            if (denominator == 0) {\n\
    \                if (vector_cross(direction, first) != 0) continue;\n        \
    \        const Number first_parameter =\n                    vector_dot(first,\
    \ direction);\n                const Number second_parameter =\n             \
    \       vector_dot(second, direction);\n                if (first_parameter >\
    \ 0) {\n                    parameter = Fraction{\n                        first_parameter,\
    \ direction_norm2\n                    };\n                    valid = true;\n\
    \                }\n                if (\n                    second_parameter\
    \ > 0 &&\n                    (!valid || second_parameter < parameter.numerator)\n\
    \                ) {\n                    parameter = Fraction{\n            \
    \            second_parameter, direction_norm2\n                    };\n     \
    \               valid = true;\n                }\n            } else {\n     \
    \           Number numerator = vector_cross(first, edge_direction);\n        \
    \        Number segment_numerator = vector_cross(first, direction);\n        \
    \        if (denominator < 0) {\n                    denominator = -denominator;\n\
    \                    numerator = -numerator;\n                    segment_numerator\
    \ = -segment_numerator;\n                }\n                if (\n           \
    \         numerator <= 0 || segment_numerator < 0 ||\n                    segment_numerator\
    \ > denominator\n                ) {\n                    continue;\n        \
    \        }\n                parameter = Fraction{numerator, denominator};\n  \
    \              valid = true;\n            }\n            if (!valid) continue;\n\
    \            if (!best.has_value()) {\n                best = parameter;\n   \
    \             result.assign(1, edge);\n                continue;\n           \
    \ }\n            const Number left =\n                parameter.numerator * best->denominator;\n\
    \            const Number right =\n                best->numerator * parameter.denominator;\n\
    \            if (left < right) {\n                best = parameter;\n        \
    \        result.assign(1, edge);\n            } else if (left == right) {\n  \
    \              result.push_back(edge);\n            }\n        }\n        return\
    \ result;\n    }\n\n    std::vector<int> floating_ray_shoot(\n        int origin,\n\
    \        const Vector& direction,\n        const std::vector<int>& candidates\n\
    \    ) const {\n        long double best = std::numeric_limits<long double>::infinity();\n\
    \        std::vector<int> result;\n        const long double direction_norm2 =\
    \ vector_dot(\n            direction, direction\n        );\n        for (int\
    \ edge : candidates) {\n            edge %= size_;\n            const Vector first\
    \ = vector_between(edge, origin);\n            const Vector second = vector_between(\n\
    \                (edge + 1) % size_, origin\n            );\n            const\
    \ Vector edge_direction = vector_between(\n                (edge + 1) % size_,\
    \ edge\n            );\n            const long double denominator = vector_cross(\n\
    \                direction, edge_direction\n            );\n            long double\
    \ parameter = -1;\n            if (std::fabs(denominator) <= eps_) {\n       \
    \         if (std::fabs(vector_cross(direction, first)) > eps_) {\n          \
    \          continue;\n                }\n                const long double first_parameter\
    \ =\n                    vector_dot(first, direction) / direction_norm2;\n   \
    \             const long double second_parameter =\n                    vector_dot(second,\
    \ direction) / direction_norm2;\n                if (first_parameter > eps_) parameter\
    \ = first_parameter;\n                if (\n                    second_parameter\
    \ > eps_ &&\n                    (parameter < 0 || second_parameter < parameter)\n\
    \                ) {\n                    parameter = second_parameter;\n    \
    \            }\n            } else {\n                parameter =\n          \
    \          vector_cross(first, edge_direction) / denominator;\n              \
    \  const long double segment_parameter =\n                    vector_cross(first,\
    \ direction) / denominator;\n                if (\n                    parameter\
    \ <= eps_ || segment_parameter < -eps_ ||\n                    segment_parameter\
    \ > 1 + eps_\n                ) {\n                    continue;\n           \
    \     }\n            }\n            if (parameter < 0) continue;\n           \
    \ if (parameter + eps_ < best) {\n                best = parameter;\n        \
    \        result.assign(1, edge);\n            } else if (std::fabs(parameter -\
    \ best) <= eps_) {\n                result.push_back(edge);\n            }\n \
    \       }\n        return result;\n    }\n\n    void mark_ray(int origin, const\
    \ Vector& direction) {\n        for (const int edge : ray_shoot(origin, direction))\
    \ {\n            marked_edge_[edge] = true;\n        }\n    }\n};\n\ntemplate\
    \ <Coordinate T, typename Number>\nclass KeilSnoeyinkDecomposition {\n   private:\n\
    \    static constexpr int infinity = 100000000;\n    static constexpr int bad\
    \ = 1000000000;\n\n    struct SolutionNode;\n    using NodePointer = std::shared_ptr<const\
    \ SolutionNode>;\n\n    struct SolutionNode {\n        NodePointer first;\n  \
    \      NodePointer second;\n        Diagonal diagonal{0, 0};\n        bool is_diagonal\
    \ = false;\n    };\n\n    struct NarrowPair {\n        int first;\n        int\
    \ second;\n        NodePointer solution;\n    };\n\n    // Two independently popped\
    \ views of the same narrowest-pair stack.\n    // Pairs are appended from back\
    \ to front in the terminology of the\n    // Keil--Snoeyink paper.\n    struct\
    \ PairDeque {\n        std::vector<NarrowPair> pairs;\n        int front = -1;\n\
    \        int back = 0;\n\n        bool empty_front() const { return front < 0;\
    \ }\n        bool more_front() const { return front > 0; }\n        bool empty_back()\
    \ const {\n            return back >= static_cast<int>(pairs.size());\n      \
    \  }\n        bool more_back() const {\n            return back + 1 < static_cast<int>(pairs.size());\n\
    \        }\n\n        const NarrowPair& front_pair() const { return pairs[front];\
    \ }\n        const NarrowPair& under_front() const {\n            return pairs[front\
    \ - 1];\n        }\n        const NarrowPair& back_pair() const { return pairs[back];\
    \ }\n        const NarrowPair& under_back() const {\n            return pairs[back\
    \ + 1];\n        }\n\n        void pop_front() { --front; }\n        void pop_back()\
    \ { ++back; }\n        void restore() {\n            front = static_cast<int>(pairs.size())\
    \ - 1;\n            back = 0;\n        }\n        void clear() {\n           \
    \ pairs.clear();\n            restore();\n        }\n        void push(int first,\
    \ int second, NodePointer solution = nullptr) {\n            pairs.push_back(NarrowPair{first,\
    \ second, std::move(solution)});\n            restore();\n        }\n        void\
    \ push_narrow(\n            int first,\n            int second,\n            NodePointer\
    \ solution\n        ) {\n            if (!empty_front() && first <= front_pair().first)\
    \ return;\n            while (!empty_front() && front_pair().second >= second)\
    \ {\n                pairs.pop_back();\n                --front;\n           \
    \ }\n            push(first, second, std::move(solution));\n        }\n    };\n\
    \n    struct State {\n        int weight = bad;\n        PairDeque pairs;\n  \
    \  };\n\n    using ProjectiveNumber = Number;\n\n    struct Homogeneous {\n  \
    \      ProjectiveNumber w;\n        ProjectiveNumber x;\n        ProjectiveNumber\
    \ y;\n\n        Homogeneous negated() const { return {-w, -x, -y}; }\n\n     \
    \   ProjectiveNumber side(const Point<T>& point) const {\n            return w\
    \ + x * predicate_number<ProjectiveNumber>(point.x) +\n                   y *\
    \ predicate_number<ProjectiveNumber>(point.y);\n        }\n\n        static Homogeneous\
    \ line(\n            const Point<T>& first,\n            const Point<T>& second\n\
    \        ) {\n            const ProjectiveNumber ax =\n                predicate_number<ProjectiveNumber>(first.x);\n\
    \            const ProjectiveNumber ay =\n                predicate_number<ProjectiveNumber>(first.y);\n\
    \            const ProjectiveNumber bx =\n                predicate_number<ProjectiveNumber>(second.x);\n\
    \            const ProjectiveNumber by =\n                predicate_number<ProjectiveNumber>(second.y);\n\
    \            return {ax * by - ay * bx, ay - by, bx - ax};\n        }\n\n    \
    \    static ProjectiveNumber determinant(\n            const Homogeneous& first,\n\
    \            const Homogeneous& second,\n            const Homogeneous& third\n\
    \        ) {\n            return\n                first.w *\n                \
    \    (second.x * third.y - second.y * third.x) -\n                second.w *\n\
    \                    (first.x * third.y - first.y * third.x) +\n             \
    \   third.w *\n                    (first.x * second.y - first.y * second.x);\n\
    \        }\n    };\n\n    // ElGindy--Avis visibility-polygon scan, specialized\
    \ to a polygon\n    // vertex. Only original polygon vertices are returned; artificial\
    \ lid\n    // intersections are discarded.\n    class VisibilityPolygon {\n  \
    \     private:\n        enum VertexType { right_lid, left_lid, right_wall, left_wall\
    \ };\n\n       public:\n        VisibilityPolygon(\n            const std::vector<Point<T>>&\
    \ polygon,\n            long double eps\n        )\n            : polygon_(polygon),\
    \ eps_(eps), size_(polygon.size()) {}\n\n        std::vector<Index> build(Index\
    \ origin_index) {\n            origin_ = &polygon_[origin_index];\n          \
    \  vertices_.clear();\n            types_.clear();\n            left_lid_index_\
    \ = not_saved;\n            right_lid_index_ = not_saved;\n\n            int vertex\
    \ = static_cast<int>(origin_index);\n            push(vertex++, right_wall);\n\
    \            do {\n                push(vertex++, right_wall);\n             \
    \   if (vertex >= static_cast<int>(size_ + origin_index)) {\n                \
    \    break;\n                }\n                Homogeneous edge = line(vertex\
    \ - 1, vertex);\n                if (left(edge, *origin_)) continue;\n\n     \
    \           if (!left(edge, point(vertex - 2))) {\n                    vertex\
    \ = exit_right_bay(\n                        vertex,\n                       \
    \ top(),\n                        Homogeneous{1, 0, 0}\n                    );\n\
    \                    push(vertex++, right_lid);\n                    continue;\n\
    \                }\n\n                save_lid();\n                for (;;) {\n\
    \                    if (\n                        orientation(\n            \
    \                *origin_, top(), point(vertex), eps_\n                      \
    \  ) > 0\n                    ) {\n                        if (\n            \
    \                orientation(\n                                point(vertex),\n\
    \                                point(vertex + 1),\n                        \
    \        *origin_,\n                                eps_\n                   \
    \         ) < 0\n                        ) {\n                            ++vertex;\n\
    \                        } else if (left(edge, point(vertex + 1))) {\n       \
    \                     vertex = exit_left_bay(\n                              \
    \  vertex,\n                                point(vertex),\n                 \
    \               line(left_lid_index_, left_lid_index_ - 1)\n                 \
    \           ) + 1;\n                        } else {\n                       \
    \     restore_lid();\n                            push(vertex++, left_wall);\n\
    \                            break;\n                        }\n             \
    \           edge = line(vertex - 1, vertex);\n                    } else if (!left(edge,\
    \ top())) {\n                        if (right_lid_index_ == not_saved) break;\n\
    \                        vertex = exit_right_bay(\n                          \
    \  vertex, top(), edge.negated()\n                        );\n               \
    \         push(vertex++, right_lid);\n                        break;\n       \
    \             } else {\n                        save_lid();\n                \
    \    }\n                }\n            } while (vertex < static_cast<int>(size_\
    \ + origin_index));\n\n            std::vector<Index> result;\n            while\
    \ (!vertices_.empty()) {\n                while (\n                    !vertices_.empty()\
    \ &&\n                    (types_.back() == right_lid ||\n                   \
    \  types_.back() == left_lid)\n                ) {\n                    vertices_.pop_back();\n\
    \                    types_.pop_back();\n                }\n                if\
    \ (vertices_.empty()) break;\n                result.push_back(\n            \
    \        static_cast<Index>(vertices_.back()) % size_\n                );\n  \
    \              vertices_.pop_back();\n                types_.pop_back();\n   \
    \         }\n            return result;\n        }\n\n       private:\n      \
    \  static constexpr int not_saved = -1;\n\n        const std::vector<Point<T>>&\
    \ polygon_;\n        long double eps_;\n        Index size_;\n        const Point<T>*\
    \ origin_ = nullptr;\n        std::vector<int> vertices_;\n        std::vector<VertexType>\
    \ types_;\n        int left_lid_index_ = not_saved;\n        int right_lid_index_\
    \ = not_saved;\n\n        const Point<T>& point(int index) const {\n         \
    \   int reduced = index % static_cast<int>(size_);\n            if (reduced <\
    \ 0) reduced += static_cast<int>(size_);\n            return polygon_[static_cast<Index>(reduced)];\n\
    \        }\n        const Point<T>& top() const { return point(vertices_.back());\
    \ }\n        Homogeneous line(int first, int second) const {\n            return\
    \ Homogeneous::line(point(first), point(second));\n        }\n        bool left(\n\
    \            const Homogeneous& line_value,\n            const Point<T>& point_value\n\
    \        ) const {\n            return\n                predicate_sign<T>(line_value.side(point_value),\
    \ eps_) > 0;\n        }\n        bool right(\n            const Homogeneous& line_value,\n\
    \            const Point<T>& point_value\n        ) const {\n            return\n\
    \                predicate_sign<T>(line_value.side(point_value), eps_) < 0;\n\
    \        }\n        bool clockwise(\n            const Homogeneous& first,\n \
    \           const Homogeneous& second,\n            const Homogeneous& third\n\
    \        ) const {\n            return predicate_sign<T>(\n                Homogeneous::determinant(first,\
    \ second, third), eps_\n            ) < 0;\n        }\n        void push(int index,\
    \ VertexType type) {\n            vertices_.push_back(index);\n            types_.push_back(type);\n\
    \        }\n\n        void save_lid() {\n            if (types_.back() == left_wall)\
    \ {\n                vertices_.pop_back();\n                types_.pop_back();\n\
    \            }\n            left_lid_index_ = vertices_.back();\n            vertices_.pop_back();\n\
    \            types_.pop_back();\n            if (types_.back() == right_lid) {\n\
    \                right_lid_index_ = vertices_.back();\n                vertices_.pop_back();\n\
    \                types_.pop_back();\n            } else {\n                right_lid_index_\
    \ = not_saved;\n            }\n        }\n\n        void restore_lid() {\n   \
    \         if (right_lid_index_ != not_saved) {\n                push(right_lid_index_,\
    \ right_lid);\n            }\n            push(left_lid_index_, left_lid);\n \
    \       }\n\n        int exit_right_bay(\n            int vertex,\n          \
    \  const Point<T>& bottom,\n            const Homogeneous& lid\n        ) const\
    \ {\n            int winding = 0;\n            const Homogeneous mouth = Homogeneous::line(*origin_,\
    \ bottom);\n            bool current_left = false;\n            while (++vertex\
    \ < 3 * static_cast<int>(size_)) {\n                const bool last_left = current_left;\n\
    \                current_left = left(mouth, point(vertex));\n                if\
    \ (\n                    current_left != last_left &&\n                    (orientation(\n\
    \                         point(vertex - 1),\n                         point(vertex),\n\
    \                         *origin_,\n                         eps_\n         \
    \            ) > 0) == current_left\n                ) {\n                   \
    \ if (!current_left) {\n                        --winding;\n                 \
    \   } else if (winding++ == 0) {\n                        const Homogeneous edge\
    \ = line(vertex - 1, vertex);\n                        if (\n                \
    \            left(edge, bottom) &&\n                            !clockwise(mouth,\
    \ edge, lid)\n                        ) {\n                            return\
    \ vertex - 1;\n                        }\n                    }\n            \
    \    }\n            }\n            return vertex;\n        }\n\n        int exit_left_bay(\n\
    \            int vertex,\n            const Point<T>& bottom,\n            const\
    \ Homogeneous& lid\n        ) const {\n            int winding = 0;\n        \
    \    const Homogeneous mouth = Homogeneous::line(*origin_, bottom);\n        \
    \    bool current_right = false;\n            while (++vertex < 3 * static_cast<int>(size_))\
    \ {\n                const bool last_right = current_right;\n                current_right\
    \ = right(mouth, point(vertex));\n                if (\n                    current_right\
    \ != last_right &&\n                    (orientation(\n                      \
    \   point(vertex - 1),\n                         point(vertex),\n            \
    \             *origin_,\n                         eps_\n                     )\
    \ < 0) == current_right\n                ) {\n                    if (!current_right)\
    \ {\n                        ++winding;\n                    } else if (winding--\
    \ == 0) {\n                        const Homogeneous edge = line(vertex - 1, vertex);\n\
    \                        if (\n                            right(edge, bottom)\
    \ &&\n                            !clockwise(mouth, edge, lid)\n             \
    \           ) {\n                            return vertex - 1;\n            \
    \            }\n                    }\n                }\n            }\n    \
    \        return vertex;\n        }\n    };\n\n   public:\n    KeilSnoeyinkDecomposition(\n\
    \        const std::vector<Point<T>>& polygon,\n        long double eps\n    )\n\
    \        : polygon_(polygon),\n          eps_(eps),\n          size_(polygon.size()),\n\
    \          reflex_(size_, false),\n          remapped_(size_) {}\n\n    std::optional<std::vector<Diagonal>>\
    \ run() {\n        initialize_reflex_vertices();\n        allocate_states();\n\
    \        initialize_visibility();\n        initialize_base_subproblems();\n\n\
    \        for (int span = 3; span < static_cast<int>(size_); ++span) {\n      \
    \      for (const int first : reflex_vertices_) {\n                const int last\
    \ = first + span;\n                if (last >= static_cast<int>(size_)) break;\n\
    \                if (!visible(first, last)) continue;\n                initialize_pairs(first,\
    \ last);\n                if (reflex_[last]) {\n                    for (int middle\
    \ = first + 1; middle < last; ++middle) {\n                        type_a(first,\
    \ middle, last);\n                    }\n                } else {\n          \
    \          for (const int middle : reflex_vertices_) {\n                     \
    \   if (middle <= first) continue;\n                        if (middle >= last\
    \ - 1) break;\n                        type_a(first, middle, last);\n        \
    \            }\n                    type_a(first, last - 1, last);\n         \
    \       }\n            }\n\n            for (const int last : reflex_vertices_)\
    \ {\n                if (last < span) continue;\n                const int first\
    \ = last - span;\n                if (reflex_[first] || !visible(first, last))\
    \ continue;\n                initialize_pairs(first, last);\n                type_b(first,\
    \ first + 1, last);\n                for (const int middle : reflex_vertices_)\
    \ {\n                    if (middle <= first + 1) continue;\n                \
    \    if (middle >= last) break;\n                    type_b(first, middle, last);\n\
    \                }\n            }\n        }\n\n        if (weight(0, static_cast<int>(size_)\
    \ - 1) >= infinity) {\n            return std::nullopt;\n        }\n        std::vector<Diagonal>\
    \ diagonals;\n        const PairDeque& root = state(0, static_cast<int>(size_)\
    \ - 1).pairs;\n        if (root.pairs.empty()) return std::nullopt;\n        flatten(root.pairs.front().solution,\
    \ diagonals);\n        for (Diagonal& diagonal : diagonals) {\n            if\
    \ (diagonal.second < diagonal.first) {\n                std::swap(diagonal.first,\
    \ diagonal.second);\n            }\n        }\n        std::sort(\n          \
    \  diagonals.begin(),\n            diagonals.end(),\n            [](const Diagonal&\
    \ first, const Diagonal& second) {\n                return std::pair(first.first,\
    \ first.second) <\n                       std::pair(second.first, second.second);\n\
    \            }\n        );\n        diagonals.erase(\n            std::unique(\n\
    \                diagonals.begin(),\n                diagonals.end(),\n      \
    \          [](const Diagonal& first, const Diagonal& second) {\n             \
    \       return\n                        first.first == second.first &&\n     \
    \                   first.second == second.second;\n                }\n      \
    \      ),\n            diagonals.end()\n        );\n        if (\n           \
    \ static_cast<int>(diagonals.size()) !=\n            weight(0, static_cast<int>(size_)\
    \ - 1)\n        ) {\n            return std::nullopt;\n        }\n        return\
    \ diagonals;\n    }\n\n   private:\n    const std::vector<Point<T>>& polygon_;\n\
    \    long double eps_;\n    Index size_;\n    std::vector<bool> reflex_;\n   \
    \ std::vector<int> reflex_vertices_;\n    std::vector<int> remapped_;\n    std::vector<std::vector<State>>\
    \ states_;\n\n    void initialize_reflex_vertices() {\n        for (int index\
    \ = 0; index < static_cast<int>(size_); ++index) {\n            reflex_[index]\
    \ = index == 0 || orientation(\n                polygon_[(index + static_cast<int>(size_)\
    \ - 1) % size_],\n                polygon_[index],\n                polygon_[(index\
    \ + 1) % size_],\n                eps_\n            ) < 0;\n            if (reflex_[index])\
    \ reflex_vertices_.push_back(index);\n        }\n    }\n\n    void allocate_states()\
    \ {\n        int next = 0;\n        for (const int index : reflex_vertices_) remapped_[index]\
    \ = next++;\n        for (int index = 0; index < static_cast<int>(size_); ++index)\
    \ {\n            if (!reflex_[index]) remapped_[index] = next++;\n        }\n\
    \        const int reflex_count = static_cast<int>(reflex_vertices_.size());\n\
    \        states_.resize(size_);\n        for (int index = 0; index < static_cast<int>(size_);\
    \ ++index) {\n            states_[index].resize(reflex_[index] ? size_ : reflex_count);\n\
    \        }\n    }\n\n    State& state(int first, int last) {\n        assert(first\
    \ <= last);\n        assert(reflex_[first] || reflex_[last]);\n        return\
    \ states_[first][remapped_[last]];\n    }\n    const State& state(int first, int\
    \ last) const {\n        assert(first <= last);\n        assert(reflex_[first]\
    \ || reflex_[last]);\n        return states_[first][remapped_[last]];\n    }\n\
    \    int weight(int first, int last) const {\n        return state(first, last).weight;\n\
    \    }\n    bool visible(int first, int last) const {\n        return weight(first,\
    \ last) < bad;\n    }\n\n    void initialize_visibility() {\n        VisibilityPolygon\
    \ visibility_polygon(polygon_, eps_);\n        for (const int reflex : reflex_vertices_)\
    \ {\n            for (const Index visible_vertex :\n                 visibility_polygon.build(static_cast<Index>(reflex)))\
    \ {\n                int first = reflex;\n                int last = static_cast<int>(visible_vertex);\n\
    \                if (last < first) std::swap(first, last);\n                if\
    \ (first == last) continue;\n                state(first, last).weight = infinity;\n\
    \            }\n        }\n        // The visibility scan treats the closing edge\
    \ like every other\n        // boundary edge, but make the DP convention explicit.\n\
    \        state(0, static_cast<int>(size_) - 1).weight = infinity;\n    }\n\n \
    \   void initialize_base_subproblems() {\n        const int size = static_cast<int>(size_);\n\
    \        for (const int index : reflex_vertices_) {\n            if (index + 1\
    \ < size) state(index, index + 1).weight = 0;\n            if (index > 0) state(index\
    \ - 1, index).weight = 0;\n            if (index + 2 < size && visible(index,\
    \ index + 2)) {\n                State& base = state(index, index + 2);\n    \
    \            base.weight = 0;\n                base.pairs.clear();\n         \
    \       base.pairs.push(index + 1, index + 1, nullptr);\n            }\n     \
    \       if (index >= 2 && visible(index - 2, index)) {\n                State&\
    \ base = state(index - 2, index);\n                base.weight = 0;\n        \
    \        base.pairs.clear();\n                base.pairs.push(index - 1, index\
    \ - 1, nullptr);\n            }\n        }\n    }\n\n    void initialize_pairs(int\
    \ first, int last) {\n        state(first, last).pairs.clear();\n    }\n\n   \
    \ void update(\n        int first,\n        int last,\n        int new_weight,\n\
    \        int pair_first,\n        int pair_second,\n        NodePointer solution\n\
    \    ) {\n        State& subproblem = state(first, last);\n        if (new_weight\
    \ > subproblem.weight) return;\n        if (new_weight < subproblem.weight) {\n\
    \            subproblem.weight = new_weight;\n            subproblem.pairs.clear();\n\
    \        }\n        subproblem.pairs.push_narrow(\n            pair_first, pair_second,\
    \ std::move(solution)\n        );\n    }\n\n    NodePointer concatenate(NodePointer\
    \ first, NodePointer second) const {\n        if (!first) return second;\n   \
    \     if (!second) return first;\n        SolutionNode node;\n        node.first\
    \ = std::move(first);\n        node.second = std::move(second);\n        return\
    \ std::make_shared<const SolutionNode>(std::move(node));\n    }\n\n    NodePointer\
    \ append_diagonal(\n        NodePointer solution,\n        int first,\n      \
    \  int last\n    ) const {\n        SolutionNode leaf;\n        leaf.diagonal\
    \ = Diagonal{\n            static_cast<Index>(first), static_cast<Index>(last)\n\
    \        };\n        leaf.is_diagonal = true;\n        return concatenate(\n \
    \           std::move(solution),\n            std::make_shared<const SolutionNode>(std::move(leaf))\n\
    \        );\n    }\n\n    NodePointer any_solution(int first, int last) const\
    \ {\n        const PairDeque& pairs = state(first, last).pairs;\n        assert(!pairs.pairs.empty());\n\
    \        return pairs.pairs.front().solution;\n    }\n\n    void type_a(int first,\
    \ int middle, int last) {\n        if (!visible(first, middle)) return;\n    \
    \    int top = middle;\n        int new_weight = weight(first, middle);\n    \
    \    NodePointer solution;\n        if (last - middle > 1) {\n            if (!visible(middle,\
    \ last)) return;\n            new_weight += weight(middle, last) + 1;\n      \
    \      solution = any_solution(middle, last);\n            solution = append_diagonal(\n\
    \                std::move(solution), middle, last\n            );\n        }\n\
    \        bool use_first_diagonal = false;\n        if (middle - first > 1) {\n\
    \            PairDeque& pairs = state(first, middle).pairs;\n            if (pairs.empty_back())\
    \ return;\n            if (\n                orientation(\n                  \
    \  polygon_[last],\n                    polygon_[middle],\n                  \
    \  polygon_[pairs.back_pair().second],\n                    eps_\n           \
    \     ) <= 0\n            ) {\n                while (\n                    pairs.more_back()\
    \ &&\n                    orientation(\n                        polygon_[last],\n\
    \                        polygon_[middle],\n                        polygon_[pairs.under_back().second],\n\
    \                        eps_\n                    ) <= 0\n                ) {\n\
    \                    pairs.pop_back();\n                }\n                if\
    \ (\n                    !pairs.empty_back() &&\n                    orientation(\n\
    \                        polygon_[last],\n                        polygon_[first],\n\
    \                        polygon_[pairs.back_pair().first],\n                \
    \        eps_\n                    ) >= 0\n                ) {\n             \
    \       top = pairs.back_pair().first;\n                } else {\n           \
    \         ++new_weight;\n                    use_first_diagonal = true;\n    \
    \            }\n            } else {\n                ++new_weight;\n        \
    \        use_first_diagonal = true;\n            }\n            solution = concatenate(\n\
    \                pairs.back_pair().solution, std::move(solution)\n           \
    \ );\n            if (use_first_diagonal) {\n                solution = append_diagonal(\n\
    \                    std::move(solution), first, middle\n                );\n\
    \            }\n        }\n        update(\n            first,\n            last,\n\
    \            new_weight,\n            top,\n            middle,\n            std::move(solution)\n\
    \        );\n    }\n\n    void type_b(int first, int middle, int last) {\n   \
    \     if (!visible(middle, last)) return;\n        int top = middle;\n       \
    \ int new_weight = weight(middle, last);\n        NodePointer solution;\n    \
    \    if (middle - first > 1) {\n            if (!visible(first, middle)) return;\n\
    \            new_weight += weight(first, middle) + 1;\n            solution =\
    \ any_solution(first, middle);\n            solution = append_diagonal(\n    \
    \            std::move(solution), first, middle\n            );\n        }\n \
    \       bool use_second_diagonal = false;\n        if (last - middle > 1) {\n\
    \            PairDeque& pairs = state(middle, last).pairs;\n            if (pairs.empty_front())\
    \ return;\n            if (\n                orientation(\n                  \
    \  polygon_[first],\n                    polygon_[middle],\n                 \
    \   polygon_[pairs.front_pair().first],\n                    eps_\n          \
    \      ) >= 0\n            ) {\n                while (\n                    pairs.more_front()\
    \ &&\n                    orientation(\n                        polygon_[first],\n\
    \                        polygon_[middle],\n                        polygon_[pairs.under_front().first],\n\
    \                        eps_\n                    ) >= 0\n                ) {\n\
    \                    pairs.pop_front();\n                }\n                if\
    \ (\n                    !pairs.empty_front() &&\n                    orientation(\n\
    \                        polygon_[first],\n                        polygon_[last],\n\
    \                        polygon_[pairs.front_pair().second],\n              \
    \          eps_\n                    ) <= 0\n                ) {\n           \
    \         top = pairs.front_pair().second;\n                } else {\n       \
    \             ++new_weight;\n                    use_second_diagonal = true;\n\
    \                }\n            } else {\n                ++new_weight;\n    \
    \            use_second_diagonal = true;\n            }\n            solution\
    \ = concatenate(\n                std::move(solution), pairs.front_pair().solution\n\
    \            );\n            if (use_second_diagonal) {\n                solution\
    \ = append_diagonal(\n                    std::move(solution), middle, last\n\
    \                );\n            }\n        }\n        update(\n            first,\n\
    \            last,\n            new_weight,\n            middle,\n           \
    \ top,\n            std::move(solution)\n        );\n    }\n\n    void flatten(\n\
    \        const NodePointer& node,\n        std::vector<Diagonal>& diagonals\n\
    \    ) const {\n        if (!node) return;\n        if (node->is_diagonal) {\n\
    \            diagonals.push_back(node->diagonal);\n            return;\n     \
    \   }\n        flatten(node->first, diagonals);\n        flatten(node->second,\
    \ diagonals);\n    }\n\n};\n\ntemplate <Coordinate T>\nstd::optional<std::vector<IndexPolygon>>\
    \ faces_from_diagonals(\n    const std::vector<Point<T>>& polygon,\n    const\
    \ std::vector<Diagonal>& diagonals,\n    long double eps\n) {\n    const Index\
    \ size = polygon.size();\n    std::vector<std::vector<Index>> adjacent(size);\n\
    \    auto add_edge = [&](Index first, Index second) {\n        adjacent[first].push_back(second);\n\
    \        adjacent[second].push_back(first);\n    };\n    for (Index index = 0;\
    \ index < size; ++index) {\n        add_edge(index, (index + 1) % size);\n   \
    \ }\n    for (const Diagonal& diagonal : diagonals) {\n        if (\n        \
    \    diagonal.first >= size || diagonal.second >= size ||\n            diagonal.first\
    \ == diagonal.second\n        ) {\n            return std::nullopt;\n        }\n\
    \        add_edge(diagonal.first, diagonal.second);\n    }\n\n    for (Index origin\
    \ = 0; origin < size; ++origin) {\n        auto upper_half = [&](Index target)\
    \ {\n            const auto direction = polygon[target] - polygon[origin];\n \
    \           const int y_sign = sign<T>(direction.y, eps);\n            return\n\
    \                y_sign > 0 ||\n                (y_sign == 0 && sign<T>(direction.x,\
    \ eps) >= 0);\n        };\n        std::sort(\n            adjacent[origin].begin(),\n\
    \            adjacent[origin].end(),\n            [&](Index first, Index second)\
    \ {\n                const bool first_upper = upper_half(first);\n           \
    \     const bool second_upper = upper_half(second);\n                if (first_upper\
    \ != second_upper) return first_upper;\n                const auto first_direction\
    \ =\n                    polygon[first] - polygon[origin];\n                const\
    \ auto second_direction =\n                    polygon[second] - polygon[origin];\n\
    \                const int turn = sign<T>(\n                    cross(first_direction,\
    \ second_direction), eps\n                );\n                if (turn != 0) return\
    \ turn > 0;\n                return\n                    norm2(first_direction)\
    \ < norm2(second_direction);\n            }\n        );\n        adjacent[origin].erase(\n\
    \            std::unique(\n                adjacent[origin].begin(), adjacent[origin].end()\n\
    \            ),\n            adjacent[origin].end()\n        );\n    }\n\n   \
    \ std::vector<std::vector<bool>> visited(size);\n    Index directed_edge_count\
    \ = 0;\n    for (Index index = 0; index < size; ++index) {\n        visited[index].assign(adjacent[index].size(),\
    \ false);\n        directed_edge_count += adjacent[index].size();\n    }\n\n \
    \   std::vector<IndexPolygon> result;\n    for (Index start = 0; start < size;\
    \ ++start) {\n        for (Index start_position = 0;\n             start_position\
    \ < adjacent[start].size();\n             ++start_position) {\n            if\
    \ (visited[start][start_position]) continue;\n            IndexPolygon face;\n\
    \            Index current = start;\n            Index position = start_position;\n\
    \            for (Index guard = 0;; ++guard) {\n                if (guard > directed_edge_count)\
    \ return std::nullopt;\n                if (visited[current][position]) {\n  \
    \                  if (current != start || position != start_position) {\n   \
    \                     return std::nullopt;\n                    }\n          \
    \          break;\n                }\n                visited[current][position]\
    \ = true;\n                face.push_back(current);\n                const Index\
    \ next = adjacent[current][position];\n                const auto reverse = std::find(\n\
    \                    adjacent[next].begin(), adjacent[next].end(), current\n \
    \               );\n                if (reverse == adjacent[next].end()) return\
    \ std::nullopt;\n                const Index reverse_position =\n            \
    \        static_cast<Index>(reverse - adjacent[next].begin());\n             \
    \   current = next;\n                position =\n                    (reverse_position\
    \ + adjacent[current].size() - 1) %\n                    adjacent[current].size();\n\
    \            }\n            if (face.size() < 3) continue;\n            std::vector<Point<T>>\
    \ points;\n            points.reserve(face.size());\n            for (const Index\
    \ index : face) points.push_back(polygon[index]);\n            if (sign<T>(polygon_area2(points),\
    \ eps) > 0) {\n                if (!is_weakly_convex(face, polygon, eps)) {\n\
    \                    return std::nullopt;\n                }\n               \
    \ result.push_back(std::move(face));\n            }\n        }\n    }\n    if\
    \ (result.size() != diagonals.size() + 1) return std::nullopt;\n    return result;\n\
    }\n\n}  // namespace convex_decomposition_detail\n\ntemplate <Coordinate T>\n\
    std::optional<std::vector<std::vector<Point<T>>>>\nconvex_decomposition(\n   \
    \ std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    auto\
    \ prepared = convex_decomposition_detail::prepare_polygon(\n        std::move(polygon),\
    \ eps\n    );\n    if (!prepared.has_value()) return std::nullopt;\n    polygon\
    \ = std::move(*prepared);\n    if (convex_decomposition_detail::is_weakly_convex(polygon,\
    \ eps)) {\n        return std::vector<std::vector<Point<T>>>{std::move(polygon)};\n\
    \    }\n\n    auto triangulation =\n        convex_decomposition_detail::triangulate_indices(polygon,\
    \ eps);\n    if (!triangulation.has_value()) return std::nullopt;\n\n    using\
    \ convex_decomposition_detail::Index;\n    using convex_decomposition_detail::IndexPolygon;\n\
    \    const Index triangle_count = triangulation->size();\n    const Index absent\
    \ = std::numeric_limits<Index>::max();\n    struct Owners {\n        Index first\
    \ = std::numeric_limits<Index>::max();\n        Index second = std::numeric_limits<Index>::max();\n\
    \    };\n    std::map<std::pair<Index, Index>, Owners> edge_owners;\n    for (Index\
    \ triangle = 0; triangle < triangle_count; ++triangle) {\n        for (Index edge\
    \ = 0; edge < 3; ++edge) {\n            Index first = (*triangulation)[triangle][edge];\n\
    \            Index second = (*triangulation)[triangle][(edge + 1) % 3];\n    \
    \        if (second < first) std::swap(first, second);\n            Owners& owners\
    \ = edge_owners[{first, second}];\n            if (owners.first == absent) {\n\
    \                owners.first = triangle;\n            } else {\n            \
    \    owners.second = triangle;\n            }\n        }\n    }\n\n    std::vector<Index>\
    \ parent(triangle_count);\n    std::vector<IndexPolygon> pieces = std::move(*triangulation);\n\
    \    for (Index index = 0; index < triangle_count; ++index) {\n        parent[index]\
    \ = index;\n    }\n    for (const auto& [edge, owners] : edge_owners) {\n    \
    \    if (owners.second == absent) continue;\n        Index first_root =\n    \
    \        convex_decomposition_detail::find_root(parent, owners.first);\n     \
    \   Index second_root =\n            convex_decomposition_detail::find_root(parent,\
    \ owners.second);\n        if (first_root == second_root) continue;\n\n      \
    \  auto merged = convex_decomposition_detail::merge_across_edge(\n           \
    \ pieces[first_root],\n            pieces[second_root],\n            edge.first,\n\
    \            edge.second\n        );\n        if (\n            !merged.has_value()\
    \ ||\n            !convex_decomposition_detail::is_weakly_convex(\n          \
    \      *merged, polygon, eps\n            )\n        ) {\n            continue;\n\
    \        }\n        pieces[first_root] = std::move(*merged);\n        pieces[second_root].clear();\n\
    \        parent[second_root] = first_root;\n    }\n\n    std::vector<std::vector<Point<T>>>\
    \ result;\n    for (Index index = 0; index < triangle_count; ++index) {\n    \
    \    if (convex_decomposition_detail::find_root(parent, index) != index) {\n \
    \           continue;\n        }\n        result.push_back(convex_decomposition_detail::materialize(\n\
    \            pieces[index], polygon, eps\n        ));\n    }\n    return result;\n\
    }\n\ntemplate <Coordinate T>\nstd::optional<std::vector<std::vector<Point<T>>>>\n\
    minimum_convex_decomposition(\n    std::vector<Point<T>> polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    auto prepared = convex_decomposition_detail::prepare_minimum_polygon(\n\
    \        std::move(polygon), eps\n    );\n    if (!prepared.has_value()) return\
    \ std::nullopt;\n    polygon = std::move(*prepared);\n    if (convex_decomposition_detail::is_weakly_convex(polygon,\
    \ eps)) {\n        return std::vector<std::vector<Point<T>>>{std::move(polygon)};\n\
    \    }\n\n    std::size_t first_reflex = polygon.size();\n    for (std::size_t\
    \ index = 0; index < polygon.size(); ++index) {\n        if (\n            orientation(\n\
    \                polygon[(index + polygon.size() - 1) % polygon.size()],\n   \
    \             polygon[index],\n                polygon[(index + 1) % polygon.size()],\n\
    \                eps\n            ) < 0\n        ) {\n            first_reflex\
    \ = index;\n            break;\n        }\n    }\n    assert(first_reflex < polygon.size());\n\
    \    std::rotate(\n        polygon.begin(), polygon.begin() + first_reflex, polygon.end()\n\
    \    );\n\n    std::size_t reflex_count = 0;\n    for (std::size_t index = 0;\
    \ index < polygon.size(); ++index) {\n        if (\n            orientation(\n\
    \                polygon[(index + polygon.size() - 1) % polygon.size()],\n   \
    \             polygon[index],\n                polygon[(index + 1) % polygon.size()],\n\
    \                eps\n            ) < 0\n        ) {\n            ++reflex_count;\n\
    \        }\n    }\n\n    auto solve = [&]<typename Number>()\n        -> std::optional<std::vector<std::vector<Point<T>>>>\
    \ {\n        std::vector<Point<T>> dynamic_polygon = polygon;\n        std::vector<convex_decomposition_detail::Index>\
    \ original_index(\n            polygon.size()\n        );\n        for (std::size_t\
    \ index = 0; index < polygon.size(); ++index) {\n            original_index[index]\
    \ = index;\n        }\n        if (\n            reflex_count > 0 &&\n       \
    \     polygon.size() / reflex_count > reflex_count\n        ) {\n            convex_decomposition_detail::BiasedPolygonReduction<T,\
    \ Number>\n                reduction(polygon, eps);\n            auto reduced\
    \ = reduction.run();\n            dynamic_polygon = std::move(reduced.polygon);\n\
    \            original_index = std::move(reduced.original_index);\n        }\n\n\
    \        convex_decomposition_detail::KeilSnoeyinkDecomposition<T, Number>\n \
    \           solver(dynamic_polygon, eps);\n        auto diagonals = solver.run();\n\
    \        if (!diagonals.has_value()) return std::nullopt;\n        for (auto&\
    \ diagonal : *diagonals) {\n            diagonal.first = original_index[diagonal.first];\n\
    \            diagonal.second = original_index[diagonal.second];\n        }\n \
    \       auto index_decomposition =\n            convex_decomposition_detail::faces_from_diagonals(\n\
    \                polygon, *diagonals, eps\n            );\n        if (!index_decomposition.has_value())\
    \ return std::nullopt;\n\n        std::vector<std::vector<Point<T>>> result;\n\
    \        result.reserve(index_decomposition->size());\n        for (const auto&\
    \ indices : *index_decomposition) {\n            result.push_back(convex_decomposition_detail::materialize(\n\
    \                indices, polygon, eps\n            ));\n        }\n        return\
    \ result;\n    };\n\n    if constexpr (std::integral<T>) {\n        using convex_decomposition_detail::ExactPredicateWidth;\n\
    \        switch (\n            convex_decomposition_detail::select_exact_predicate_width(\n\
    \                polygon\n            )\n        ) {\n            case ExactPredicateWidth::Int128:\n\
    \                return solve.template operator()<__int128_t>();\n           \
    \ case ExactPredicateWidth::Int256:\n                return solve.template operator()<\n\
    \                    m1une::utilities::Int256\n                >();\n        \
    \    case ExactPredicateWidth::Int512:\n                return solve.template\
    \ operator()<\n                    m1une::utilities::Int512\n                >();\n\
    \        }\n        assert(false);\n        return std::nullopt;\n    } else {\n\
    \        return solve.template operator()<long double>();\n    }\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_CONVEX_DECOMPOSITION_HPP\n#define M1UNE_GEOMETRY_CONVEX_DECOMPOSITION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstddef>\n\
    #include <cstdint>\n#include <deque>\n#include <limits>\n#include <map>\n#include\
    \ <memory>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"../utilities/int256.hpp\"\n#include \"../utilities/int512.hpp\"\
    \n#include \"polygon.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\nnamespace\
    \ convex_decomposition_detail {\n\nusing Index = std::size_t;\nusing IndexPolygon\
    \ = std::vector<Index>;\n\nenum class ExactPredicateWidth { Int128, Int256, Int512\
    \ };\n\ntemplate <std::integral T>\nstd::size_t coordinate_magnitude_bits(\n \
    \   const std::vector<Point<T>>& polygon\n) {\n    using Unsigned = std::make_unsigned_t<T>;\n\
    \    std::size_t result = 0;\n    auto update = [&](T coordinate) {\n        Unsigned\
    \ magnitude = static_cast<Unsigned>(coordinate);\n        if constexpr (std::signed_integral<T>)\
    \ {\n            if (coordinate < 0) magnitude = Unsigned(0) - magnitude;\n  \
    \      }\n        std::size_t bits = 0;\n        while (magnitude != 0) {\n  \
    \          ++bits;\n            magnitude >>= 1;\n        }\n        result =\
    \ std::max(result, bits);\n    };\n    for (const Point<T>& point : polygon) {\n\
    \        update(point.x);\n        update(point.y);\n    }\n    return result;\n\
    }\n\ntemplate <std::integral T>\nExactPredicateWidth select_exact_predicate_width(\n\
    \    const std::vector<Point<T>>& polygon\n) {\n    static_assert(sizeof(T) <=\
    \ sizeof(std::uint64_t));\n    const std::size_t coordinate_bits =\n        coordinate_magnitude_bits(polygon);\n\
    \    // Cross-multiplied ray parameters and projective visibility\n    // determinants\
    \ have magnitude below 2^(4 * coordinate_bits + 6).\n    const std::size_t required_bits\
    \ = 4 * coordinate_bits + 7;\n    if (required_bits <= 128) return ExactPredicateWidth::Int128;\n\
    \    if (required_bits <= 256) return ExactPredicateWidth::Int256;\n    assert(required_bits\
    \ <= 512);\n    return ExactPredicateWidth::Int512;\n}\n\ntemplate <typename Number,\
    \ Coordinate T>\nNumber predicate_number(T value) {\n    return static_cast<Number>(value);\n\
    }\n\ntemplate <Coordinate T, typename Number>\nint predicate_sign(const Number&\
    \ value, long double eps) {\n    if constexpr (std::integral<T>) {\n        return\
    \ (value > 0) - (value < 0);\n    } else {\n        return (value > eps) - (value\
    \ < -eps);\n    }\n}\n\ntemplate <Coordinate T>\nstd::optional<std::vector<Point<T>>>\
    \ prepare_polygon(\n    std::vector<Point<T>> polygon,\n    long double eps\n\
    ) {\n    polygon =\n        polygon_detail::clean_polygon_vertices(std::move(polygon),\
    \ eps);\n    if (polygon.size() < 3) return std::nullopt;\n    const int area_sign\
    \ = sign<T>(polygon_area2(polygon), eps);\n    if (area_sign == 0 || !is_simple_polygon(polygon,\
    \ eps)) {\n        return std::nullopt;\n    }\n    if (area_sign < 0) std::reverse(polygon.begin(),\
    \ polygon.end());\n    return polygon;\n}\n\ntemplate <Coordinate T>\nbool is_weakly_convex(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps\n) {\n    if (polygon.size()\
    \ < 3) return false;\n    for (Index index = 0; index < polygon.size(); ++index)\
    \ {\n        if (\n            orientation(\n                polygon[index],\n\
    \                polygon[(index + 1) % polygon.size()],\n                polygon[(index\
    \ + 2) % polygon.size()],\n                eps\n            ) < 0\n        ) {\n\
    \            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<std::vector<IndexPolygon>> triangulate_indices(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps\n) {\n    const\
    \ Index size = polygon.size();\n    std::vector<Index> previous(size), next(size);\n\
    \    std::vector<bool> active(size, true);\n    for (Index index = 0; index <\
    \ size; ++index) {\n        previous[index] = (index + size - 1) % size;\n   \
    \     next[index] = (index + 1) % size;\n    }\n\n    auto is_ear = [&](Index\
    \ index) {\n        if (!active[index]) return false;\n        const Index first\
    \ = previous[index];\n        const Index third = next[index];\n        if (\n\
    \            orientation(\n                polygon[first], polygon[index], polygon[third],\
    \ eps\n            ) <= 0\n        ) {\n            return false;\n        }\n\
    \        for (Index other = 0; other < size; ++other) {\n            if (\n  \
    \              !active[other] || other == first || other == index ||\n       \
    \         other == third\n            ) {\n                continue;\n       \
    \     }\n            if (\n                polygon_detail::in_ccw_triangle(\n\
    \                    polygon[other],\n                    polygon[first],\n  \
    \                  polygon[index],\n                    polygon[third],\n    \
    \                eps\n                )\n            ) {\n                return\
    \ false;\n            }\n        }\n        return true;\n    };\n\n    std::deque<Index>\
    \ ears;\n    for (Index index = 0; index < size; ++index) {\n        if (is_ear(index))\
    \ ears.push_back(index);\n    }\n\n    std::vector<IndexPolygon> triangles;\n\
    \    triangles.reserve(size - 2);\n    Index remaining = size;\n    while (remaining\
    \ > 3) {\n        while (!ears.empty() && !is_ear(ears.front())) {\n         \
    \   ears.pop_front();\n        }\n        if (ears.empty()) return std::nullopt;\n\
    \n        const Index ear = ears.front();\n        ears.pop_front();\n       \
    \ const Index first = previous[ear];\n        const Index third = next[ear];\n\
    \        triangles.push_back(IndexPolygon{first, ear, third});\n\n        active[ear]\
    \ = false;\n        next[first] = third;\n        previous[third] = first;\n \
    \       --remaining;\n        if (is_ear(first)) ears.push_back(first);\n    \
    \    if (is_ear(third)) ears.push_back(third);\n    }\n\n    Index first = 0;\n\
    \    while (first < size && !active[first]) ++first;\n    if (first == size) return\
    \ std::nullopt;\n    const Index second = next[first];\n    const Index third\
    \ = next[second];\n    if (\n        third == first || next[third] != first ||\n\
    \        orientation(\n            polygon[first], polygon[second], polygon[third],\
    \ eps\n        ) <= 0\n    ) {\n        return std::nullopt;\n    }\n    triangles.push_back(IndexPolygon{first,\
    \ second, third});\n    return triangles;\n}\n\ninline Index find_root(std::vector<Index>&\
    \ parent, Index index) {\n    Index root = index;\n    while (parent[root] !=\
    \ root) root = parent[root];\n    while (parent[index] != index) {\n        const\
    \ Index next = parent[index];\n        parent[index] = root;\n        index =\
    \ next;\n    }\n    return root;\n}\n\ninline std::optional<IndexPolygon> merge_across_edge(\n\
    \    const IndexPolygon& first,\n    const IndexPolygon& second,\n    Index edge_first,\n\
    \    Index edge_second\n) {\n    for (Index first_position = 0;\n         first_position\
    \ < first.size();\n         ++first_position) {\n        const Index first_next\
    \ = (first_position + 1) % first.size();\n        const Index from = first[first_position];\n\
    \        const Index to = first[first_next];\n        if (\n            !(\n \
    \               (from == edge_first && to == edge_second) ||\n               \
    \ (from == edge_second && to == edge_first)\n            )\n        ) {\n    \
    \        continue;\n        }\n\n        for (Index second_position = 0;\n   \
    \          second_position < second.size();\n             ++second_position) {\n\
    \            const Index second_next =\n                (second_position + 1)\
    \ % second.size();\n            if (\n                second[second_position]\
    \ != to ||\n                second[second_next] != from\n            ) {\n   \
    \             continue;\n            }\n\n            IndexPolygon merged;\n \
    \           merged.reserve(first.size() + second.size() - 2);\n            for\
    \ (Index position = first_next;\n                 position != first_position;\n\
    \                 position = (position + 1) % first.size()) {\n              \
    \  merged.push_back(first[position]);\n            }\n            for (Index position\
    \ = second_next;\n                 position != second_position;\n            \
    \     position = (position + 1) % second.size()) {\n                merged.push_back(second[position]);\n\
    \            }\n            return merged;\n        }\n    }\n    return std::nullopt;\n\
    }\n\ntemplate <Coordinate T>\nbool is_weakly_convex(\n    const IndexPolygon&\
    \ polygon,\n    const std::vector<Point<T>>& points,\n    long double eps\n) {\n\
    \    for (Index index = 0; index < polygon.size(); ++index) {\n        if (\n\
    \            orientation(\n                points[polygon[index]],\n         \
    \       points[polygon[(index + 1) % polygon.size()]],\n                points[polygon[(index\
    \ + 2) % polygon.size()]],\n                eps\n            ) < 0\n        )\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::vector<Point<T>> materialize(\n    const IndexPolygon&\
    \ indices,\n    const std::vector<Point<T>>& points,\n    long double eps\n) {\n\
    \    std::vector<Point<T>> polygon;\n    polygon.reserve(indices.size());\n  \
    \  for (const Index index : indices) polygon.push_back(points[index]);\n    return\
    \ polygon_detail::clean_polygon_vertices(std::move(polygon), eps);\n}\n\nstruct\
    \ Diagonal {\n    Index first;\n    Index second;\n};\n\ntemplate <Coordinate\
    \ T>\nstd::optional<std::vector<Point<T>>> prepare_minimum_polygon(\n    std::vector<Point<T>>\
    \ polygon,\n    long double eps\n) {\n    if (polygon.size() >= 2 && polygon.front()\
    \ == polygon.back()) {\n        polygon.pop_back();\n    }\n    std::vector<Point<T>>\
    \ distinct;\n    distinct.reserve(polygon.size());\n    for (const Point<T>& point\
    \ : polygon) {\n        if (distinct.empty() || distinct.back() != point) {\n\
    \            distinct.push_back(point);\n        }\n    }\n    if (distinct.size()\
    \ >= 2 && distinct.front() == distinct.back()) {\n        distinct.pop_back();\n\
    \    }\n    if (distinct.size() < 3) return std::nullopt;\n\n    const int original_size\
    \ = static_cast<int>(distinct.size());\n    std::vector<int> previous(original_size),\
    \ next(original_size);\n    std::vector<bool> removed(original_size, false);\n\
    \    std::deque<int> candidates;\n    for (int index = 0; index < original_size;\
    \ ++index) {\n        previous[index] = (index + original_size - 1) % original_size;\n\
    \        next[index] = (index + 1) % original_size;\n        candidates.push_back(index);\n\
    \    }\n    int remaining = original_size;\n    while (!candidates.empty() &&\
    \ remaining >= 3) {\n        const int index = candidates.front();\n        candidates.pop_front();\n\
    \        if (removed[index]) continue;\n        const int before = previous[index];\n\
    \        const int after = next[index];\n        if (\n            orientation(\n\
    \                distinct[before], distinct[index], distinct[after], eps\n   \
    \         ) != 0 ||\n            sign<T>(\n                dot(\n            \
    \        distinct[index] - distinct[before],\n                    distinct[after]\
    \ - distinct[index]\n                ),\n                eps\n            ) <\
    \ 0\n        ) {\n            continue;\n        }\n        removed[index] = true;\n\
    \        next[before] = after;\n        previous[after] = before;\n        --remaining;\n\
    \        candidates.push_back(before);\n        candidates.push_back(after);\n\
    \    }\n    if (remaining < 3) return std::nullopt;\n\n    std::vector<Point<T>>\
    \ cleaned;\n    cleaned.reserve(static_cast<Index>(remaining));\n    int first\
    \ = 0;\n    while (removed[first]) ++first;\n    int index = first;\n    do {\n\
    \        cleaned.push_back(distinct[index]);\n        index = next[index];\n \
    \   } while (index != first);\n\n    const int area_sign = sign<T>(polygon_area2(cleaned),\
    \ eps);\n    if (area_sign == 0) return std::nullopt;\n    if (area_sign < 0)\
    \ std::reverse(cleaned.begin(), cleaned.end());\n    return cleaned;\n}\n\ntemplate\
    \ <Coordinate T, typename Number>\nclass BiasedPolygonReduction {\n   private:\n\
    \    struct Vector {\n        Number x;\n        Number y;\n    };\n\n    struct\
    \ Fraction {\n        Number numerator;\n        Number denominator;\n    };\n\
    \n    struct Chain {\n        int first_edge;\n        int edge_count;\n    };\n\
    \n   public:\n    struct Result {\n        std::vector<Point<T>> polygon;\n  \
    \      std::vector<Index> original_index;\n    };\n\n    BiasedPolygonReduction(\n\
    \        const std::vector<Point<T>>& polygon,\n        long double eps\n    )\n\
    \        : polygon_(polygon),\n          eps_(eps),\n          size_(static_cast<int>(polygon.size())),\n\
    \          marked_edge_(polygon.size(), false) {\n        for (int index = 0;\
    \ index < size_; ++index) {\n            if (\n                orientation(\n\
    \                    polygon_[(index + size_ - 1) % size_],\n                \
    \    polygon_[index],\n                    polygon_[(index + 1) % size_],\n  \
    \                  eps_\n                ) < 0\n            ) {\n            \
    \    reflex_vertices_.push_back(index);\n            }\n        }\n        build_chains();\n\
    \    }\n\n    Result run() {\n        for (const int reflex : reflex_vertices_)\
    \ {\n            marked_edge_[(reflex + size_ - 1) % size_] = true;\n        \
    \    marked_edge_[reflex] = true;\n        }\n\n        std::vector<std::vector<int>>\
    \ extension_endpoints(size_);\n        for (const int reflex : reflex_vertices_)\
    \ {\n            const Vector direction = vector_between(\n                reflex,\
    \ (reflex + 1) % size_\n            );\n            for (const int edge : ray_shoot(reflex,\
    \ direction)) {\n                marked_edge_[edge] = true;\n                extension_endpoints[reflex].push_back(edge);\n\
    \                extension_endpoints[reflex].push_back((edge + 1) % size_);\n\
    \            }\n        }\n\n        for (Index first = 0; first < reflex_vertices_.size();\
    \ ++first) {\n            for (Index second = first + 1;\n                 second\
    \ < reflex_vertices_.size();\n                 ++second) {\n                const\
    \ int first_vertex = reflex_vertices_[first];\n                const int second_vertex\
    \ = reflex_vertices_[second];\n                mark_ray(\n                   \
    \ first_vertex,\n                    vector_between(first_vertex, second_vertex)\n\
    \                );\n                mark_ray(\n                    second_vertex,\n\
    \                    vector_between(second_vertex, first_vertex)\n           \
    \     );\n            }\n        }\n        for (const int reflex : reflex_vertices_)\
    \ {\n            auto& endpoints = extension_endpoints[reflex];\n            std::sort(endpoints.begin(),\
    \ endpoints.end());\n            endpoints.erase(\n                std::unique(endpoints.begin(),\
    \ endpoints.end()),\n                endpoints.end()\n            );\n       \
    \     for (const int endpoint : endpoints) {\n                if (endpoint ==\
    \ reflex) continue;\n                mark_ray(\n                    reflex, vector_between(reflex,\
    \ endpoint)\n                );\n            }\n        }\n\n        Result result;\n\
    \        for (int index = 0; index < size_; ++index) {\n            if (\n   \
    \             marked_edge_[index] ||\n                marked_edge_[(index + size_\
    \ - 1) % size_]\n            ) {\n                result.polygon.push_back(polygon_[index]);\n\
    \                result.original_index.push_back(static_cast<Index>(index));\n\
    \            }\n        }\n        return result;\n    }\n\n   private:\n    const\
    \ std::vector<Point<T>>& polygon_;\n    long double eps_;\n    int size_;\n  \
    \  std::vector<int> reflex_vertices_;\n    std::vector<Chain> chains_;\n    std::vector<bool>\
    \ marked_edge_;\n\n    Vector vector_between(int first, int second) const {\n\
    \        return {\n            predicate_number<Number>(polygon_[first].x) -\n\
    \                predicate_number<Number>(polygon_[second].x),\n            predicate_number<Number>(polygon_[first].y)\
    \ -\n                predicate_number<Number>(polygon_[second].y)\n        };\n\
    \    }\n\n    Number vector_cross(const Vector& first, const Vector& second) const\
    \ {\n        return first.x * second.y - first.y * second.x;\n    }\n\n    Number\
    \ vector_dot(const Vector& first, const Vector& second) const {\n        return\
    \ first.x * second.x + first.y * second.y;\n    }\n\n    int vector_sign(const\
    \ Number& value) const {\n        return predicate_sign<T>(value, eps_);\n   \
    \ }\n\n    int quadrant(const Vector& direction) const {\n        const int x_sign\
    \ = vector_sign(direction.x);\n        const int y_sign = vector_sign(direction.y);\n\
    \        if (y_sign >= 0) return x_sign >= 0 ? 0 : 1;\n        return x_sign <\
    \ 0 ? 2 : 3;\n    }\n\n    void build_chains() {\n        // Within one quadrant,\
    \ monotonically turning edge directions span at\n        // most pi/2. This gives\
    \ the bitonic sidedness needed by ray shooting\n        // without evaluating\
    \ an angle.\n        int first_edge = 0;\n        Vector previous_direction =\
    \ vector_between(1, 0);\n        int current_quadrant = quadrant(previous_direction);\n\
    \        for (int edge = 1; edge < size_; ++edge) {\n            const Vector\
    \ direction = vector_between(\n                (edge + 1) % size_, edge\n    \
    \        );\n            const int direction_quadrant = quadrant(direction);\n\
    \            if (\n                vector_sign(vector_cross(previous_direction,\
    \ direction)) <\n                    0 ||\n                direction_quadrant\
    \ != current_quadrant\n            ) {\n                chains_.push_back(Chain{\n\
    \                    first_edge, edge - first_edge\n                });\n    \
    \            first_edge = edge;\n                current_quadrant = direction_quadrant;\n\
    \            }\n            previous_direction = direction;\n        }\n     \
    \   chains_.push_back(Chain{first_edge, size_ - first_edge});\n    }\n\n    int\
    \ side(\n        int origin,\n        const Vector& direction,\n        int vertex\n\
    \    ) const {\n        return vector_sign(\n            vector_cross(\n     \
    \           direction,\n                vector_between(vertex % size_, origin)\n\
    \            )\n        );\n    }\n\n    int edge_side(const Vector& direction,\
    \ int edge) const {\n        return vector_sign(\n            vector_cross(\n\
    \                direction,\n                vector_between((edge + 1) % size_,\
    \ edge)\n            )\n        );\n    }\n\n    void crossing_on_monotone_part(\n\
    \        const Chain& chain,\n        int origin,\n        const Vector& direction,\n\
    \        int first_position,\n        int last_position,\n        std::vector<int>&\
    \ candidates\n    ) const {\n        if (first_position >= last_position) return;\n\
    \        const int first_sign = side(\n            origin,\n            direction,\n\
    \            chain.first_edge + first_position\n        );\n        const int\
    \ last_sign = side(\n            origin,\n            direction,\n           \
    \ chain.first_edge + last_position\n        );\n        if (first_sign == 0) {\n\
    \            candidates.push_back(\n                chain.first_edge + first_position\n\
    \            );\n        }\n        if (last_sign == 0) {\n            candidates.push_back(\n\
    \                chain.first_edge + last_position - 1\n            );\n      \
    \  }\n        if (first_sign == 0 || last_sign == 0 || first_sign == last_sign)\
    \ {\n            return;\n        }\n        int low = first_position;\n     \
    \   int high = last_position;\n        while (high - low > 1) {\n            const\
    \ int middle = (low + high) / 2;\n            const int middle_sign = side(\n\
    \                origin,\n                direction,\n                chain.first_edge\
    \ + middle\n            );\n            if (middle_sign == 0 || middle_sign !=\
    \ first_sign) {\n                high = middle;\n            } else {\n      \
    \          low = middle;\n            }\n        }\n        candidates.push_back(chain.first_edge\
    \ + high - 1);\n    }\n\n    void chain_candidates(\n        const Chain& chain,\n\
    \        int origin,\n        const Vector& direction,\n        std::vector<int>&\
    \ candidates\n    ) const {\n        int split = 0;\n        const int first_derivative\
    \ =\n            edge_side(direction, chain.first_edge);\n        const int last_derivative\
    \ = edge_side(\n            direction,\n            chain.first_edge + chain.edge_count\
    \ - 1\n        );\n        if (\n            first_derivative != 0 && last_derivative\
    \ != 0 &&\n            first_derivative != last_derivative\n        ) {\n    \
    \        int low = 0;\n            int high = chain.edge_count - 1;\n        \
    \    while (high - low > 1) {\n                const int middle = (low + high)\
    \ / 2;\n                const int middle_sign = edge_side(\n                 \
    \   direction, chain.first_edge + middle\n                );\n               \
    \ if (\n                    middle_sign == 0 ||\n                    middle_sign\
    \ != first_derivative\n                ) {\n                    high = middle;\n\
    \                } else {\n                    low = middle;\n               \
    \ }\n            }\n            split = high;\n        }\n        if (split ==\
    \ 0) {\n            crossing_on_monotone_part(\n                chain,\n     \
    \           origin,\n                direction,\n                0,\n        \
    \        chain.edge_count,\n                candidates\n            );\n     \
    \   } else {\n            crossing_on_monotone_part(\n                chain, origin,\
    \ direction, 0, split, candidates\n            );\n            crossing_on_monotone_part(\n\
    \                chain,\n                origin,\n                direction,\n\
    \                split,\n                chain.edge_count,\n                candidates\n\
    \            );\n        }\n    }\n\n    std::vector<int> ray_shoot(\n       \
    \ int origin,\n        const Vector& direction\n    ) const {\n        std::vector<int>\
    \ candidates;\n        for (const Chain& chain : chains_) {\n            chain_candidates(chain,\
    \ origin, direction, candidates);\n        }\n        std::sort(candidates.begin(),\
    \ candidates.end());\n        candidates.erase(\n            std::unique(candidates.begin(),\
    \ candidates.end()),\n            candidates.end()\n        );\n\n        if constexpr\
    \ (std::integral<T>) {\n            return exact_ray_shoot(origin, direction,\
    \ candidates);\n        } else {\n            return floating_ray_shoot(origin,\
    \ direction, candidates);\n        }\n    }\n\n    std::vector<int> exact_ray_shoot(\n\
    \        int origin,\n        const Vector& direction,\n        const std::vector<int>&\
    \ candidates\n    ) const {\n        // Intersections are rational parameters\
    \ along the ray. Keep their\n        // numerators and denominators and compare\
    \ them by cross products.\n        std::optional<Fraction> best;\n        std::vector<int>\
    \ result;\n        const Number direction_norm2 = vector_dot(direction, direction);\n\
    \        for (int edge : candidates) {\n            edge %= size_;\n         \
    \   const Vector first = vector_between(edge, origin);\n            const Vector\
    \ second = vector_between(\n                (edge + 1) % size_, origin\n     \
    \       );\n            const Vector edge_direction = vector_between(\n      \
    \          (edge + 1) % size_, edge\n            );\n            Number denominator\
    \ = vector_cross(direction, edge_direction);\n            Fraction parameter{0,\
    \ 1};\n            bool valid = false;\n            if (denominator == 0) {\n\
    \                if (vector_cross(direction, first) != 0) continue;\n        \
    \        const Number first_parameter =\n                    vector_dot(first,\
    \ direction);\n                const Number second_parameter =\n             \
    \       vector_dot(second, direction);\n                if (first_parameter >\
    \ 0) {\n                    parameter = Fraction{\n                        first_parameter,\
    \ direction_norm2\n                    };\n                    valid = true;\n\
    \                }\n                if (\n                    second_parameter\
    \ > 0 &&\n                    (!valid || second_parameter < parameter.numerator)\n\
    \                ) {\n                    parameter = Fraction{\n            \
    \            second_parameter, direction_norm2\n                    };\n     \
    \               valid = true;\n                }\n            } else {\n     \
    \           Number numerator = vector_cross(first, edge_direction);\n        \
    \        Number segment_numerator = vector_cross(first, direction);\n        \
    \        if (denominator < 0) {\n                    denominator = -denominator;\n\
    \                    numerator = -numerator;\n                    segment_numerator\
    \ = -segment_numerator;\n                }\n                if (\n           \
    \         numerator <= 0 || segment_numerator < 0 ||\n                    segment_numerator\
    \ > denominator\n                ) {\n                    continue;\n        \
    \        }\n                parameter = Fraction{numerator, denominator};\n  \
    \              valid = true;\n            }\n            if (!valid) continue;\n\
    \            if (!best.has_value()) {\n                best = parameter;\n   \
    \             result.assign(1, edge);\n                continue;\n           \
    \ }\n            const Number left =\n                parameter.numerator * best->denominator;\n\
    \            const Number right =\n                best->numerator * parameter.denominator;\n\
    \            if (left < right) {\n                best = parameter;\n        \
    \        result.assign(1, edge);\n            } else if (left == right) {\n  \
    \              result.push_back(edge);\n            }\n        }\n        return\
    \ result;\n    }\n\n    std::vector<int> floating_ray_shoot(\n        int origin,\n\
    \        const Vector& direction,\n        const std::vector<int>& candidates\n\
    \    ) const {\n        long double best = std::numeric_limits<long double>::infinity();\n\
    \        std::vector<int> result;\n        const long double direction_norm2 =\
    \ vector_dot(\n            direction, direction\n        );\n        for (int\
    \ edge : candidates) {\n            edge %= size_;\n            const Vector first\
    \ = vector_between(edge, origin);\n            const Vector second = vector_between(\n\
    \                (edge + 1) % size_, origin\n            );\n            const\
    \ Vector edge_direction = vector_between(\n                (edge + 1) % size_,\
    \ edge\n            );\n            const long double denominator = vector_cross(\n\
    \                direction, edge_direction\n            );\n            long double\
    \ parameter = -1;\n            if (std::fabs(denominator) <= eps_) {\n       \
    \         if (std::fabs(vector_cross(direction, first)) > eps_) {\n          \
    \          continue;\n                }\n                const long double first_parameter\
    \ =\n                    vector_dot(first, direction) / direction_norm2;\n   \
    \             const long double second_parameter =\n                    vector_dot(second,\
    \ direction) / direction_norm2;\n                if (first_parameter > eps_) parameter\
    \ = first_parameter;\n                if (\n                    second_parameter\
    \ > eps_ &&\n                    (parameter < 0 || second_parameter < parameter)\n\
    \                ) {\n                    parameter = second_parameter;\n    \
    \            }\n            } else {\n                parameter =\n          \
    \          vector_cross(first, edge_direction) / denominator;\n              \
    \  const long double segment_parameter =\n                    vector_cross(first,\
    \ direction) / denominator;\n                if (\n                    parameter\
    \ <= eps_ || segment_parameter < -eps_ ||\n                    segment_parameter\
    \ > 1 + eps_\n                ) {\n                    continue;\n           \
    \     }\n            }\n            if (parameter < 0) continue;\n           \
    \ if (parameter + eps_ < best) {\n                best = parameter;\n        \
    \        result.assign(1, edge);\n            } else if (std::fabs(parameter -\
    \ best) <= eps_) {\n                result.push_back(edge);\n            }\n \
    \       }\n        return result;\n    }\n\n    void mark_ray(int origin, const\
    \ Vector& direction) {\n        for (const int edge : ray_shoot(origin, direction))\
    \ {\n            marked_edge_[edge] = true;\n        }\n    }\n};\n\ntemplate\
    \ <Coordinate T, typename Number>\nclass KeilSnoeyinkDecomposition {\n   private:\n\
    \    static constexpr int infinity = 100000000;\n    static constexpr int bad\
    \ = 1000000000;\n\n    struct SolutionNode;\n    using NodePointer = std::shared_ptr<const\
    \ SolutionNode>;\n\n    struct SolutionNode {\n        NodePointer first;\n  \
    \      NodePointer second;\n        Diagonal diagonal{0, 0};\n        bool is_diagonal\
    \ = false;\n    };\n\n    struct NarrowPair {\n        int first;\n        int\
    \ second;\n        NodePointer solution;\n    };\n\n    // Two independently popped\
    \ views of the same narrowest-pair stack.\n    // Pairs are appended from back\
    \ to front in the terminology of the\n    // Keil--Snoeyink paper.\n    struct\
    \ PairDeque {\n        std::vector<NarrowPair> pairs;\n        int front = -1;\n\
    \        int back = 0;\n\n        bool empty_front() const { return front < 0;\
    \ }\n        bool more_front() const { return front > 0; }\n        bool empty_back()\
    \ const {\n            return back >= static_cast<int>(pairs.size());\n      \
    \  }\n        bool more_back() const {\n            return back + 1 < static_cast<int>(pairs.size());\n\
    \        }\n\n        const NarrowPair& front_pair() const { return pairs[front];\
    \ }\n        const NarrowPair& under_front() const {\n            return pairs[front\
    \ - 1];\n        }\n        const NarrowPair& back_pair() const { return pairs[back];\
    \ }\n        const NarrowPair& under_back() const {\n            return pairs[back\
    \ + 1];\n        }\n\n        void pop_front() { --front; }\n        void pop_back()\
    \ { ++back; }\n        void restore() {\n            front = static_cast<int>(pairs.size())\
    \ - 1;\n            back = 0;\n        }\n        void clear() {\n           \
    \ pairs.clear();\n            restore();\n        }\n        void push(int first,\
    \ int second, NodePointer solution = nullptr) {\n            pairs.push_back(NarrowPair{first,\
    \ second, std::move(solution)});\n            restore();\n        }\n        void\
    \ push_narrow(\n            int first,\n            int second,\n            NodePointer\
    \ solution\n        ) {\n            if (!empty_front() && first <= front_pair().first)\
    \ return;\n            while (!empty_front() && front_pair().second >= second)\
    \ {\n                pairs.pop_back();\n                --front;\n           \
    \ }\n            push(first, second, std::move(solution));\n        }\n    };\n\
    \n    struct State {\n        int weight = bad;\n        PairDeque pairs;\n  \
    \  };\n\n    using ProjectiveNumber = Number;\n\n    struct Homogeneous {\n  \
    \      ProjectiveNumber w;\n        ProjectiveNumber x;\n        ProjectiveNumber\
    \ y;\n\n        Homogeneous negated() const { return {-w, -x, -y}; }\n\n     \
    \   ProjectiveNumber side(const Point<T>& point) const {\n            return w\
    \ + x * predicate_number<ProjectiveNumber>(point.x) +\n                   y *\
    \ predicate_number<ProjectiveNumber>(point.y);\n        }\n\n        static Homogeneous\
    \ line(\n            const Point<T>& first,\n            const Point<T>& second\n\
    \        ) {\n            const ProjectiveNumber ax =\n                predicate_number<ProjectiveNumber>(first.x);\n\
    \            const ProjectiveNumber ay =\n                predicate_number<ProjectiveNumber>(first.y);\n\
    \            const ProjectiveNumber bx =\n                predicate_number<ProjectiveNumber>(second.x);\n\
    \            const ProjectiveNumber by =\n                predicate_number<ProjectiveNumber>(second.y);\n\
    \            return {ax * by - ay * bx, ay - by, bx - ax};\n        }\n\n    \
    \    static ProjectiveNumber determinant(\n            const Homogeneous& first,\n\
    \            const Homogeneous& second,\n            const Homogeneous& third\n\
    \        ) {\n            return\n                first.w *\n                \
    \    (second.x * third.y - second.y * third.x) -\n                second.w *\n\
    \                    (first.x * third.y - first.y * third.x) +\n             \
    \   third.w *\n                    (first.x * second.y - first.y * second.x);\n\
    \        }\n    };\n\n    // ElGindy--Avis visibility-polygon scan, specialized\
    \ to a polygon\n    // vertex. Only original polygon vertices are returned; artificial\
    \ lid\n    // intersections are discarded.\n    class VisibilityPolygon {\n  \
    \     private:\n        enum VertexType { right_lid, left_lid, right_wall, left_wall\
    \ };\n\n       public:\n        VisibilityPolygon(\n            const std::vector<Point<T>>&\
    \ polygon,\n            long double eps\n        )\n            : polygon_(polygon),\
    \ eps_(eps), size_(polygon.size()) {}\n\n        std::vector<Index> build(Index\
    \ origin_index) {\n            origin_ = &polygon_[origin_index];\n          \
    \  vertices_.clear();\n            types_.clear();\n            left_lid_index_\
    \ = not_saved;\n            right_lid_index_ = not_saved;\n\n            int vertex\
    \ = static_cast<int>(origin_index);\n            push(vertex++, right_wall);\n\
    \            do {\n                push(vertex++, right_wall);\n             \
    \   if (vertex >= static_cast<int>(size_ + origin_index)) {\n                \
    \    break;\n                }\n                Homogeneous edge = line(vertex\
    \ - 1, vertex);\n                if (left(edge, *origin_)) continue;\n\n     \
    \           if (!left(edge, point(vertex - 2))) {\n                    vertex\
    \ = exit_right_bay(\n                        vertex,\n                       \
    \ top(),\n                        Homogeneous{1, 0, 0}\n                    );\n\
    \                    push(vertex++, right_lid);\n                    continue;\n\
    \                }\n\n                save_lid();\n                for (;;) {\n\
    \                    if (\n                        orientation(\n            \
    \                *origin_, top(), point(vertex), eps_\n                      \
    \  ) > 0\n                    ) {\n                        if (\n            \
    \                orientation(\n                                point(vertex),\n\
    \                                point(vertex + 1),\n                        \
    \        *origin_,\n                                eps_\n                   \
    \         ) < 0\n                        ) {\n                            ++vertex;\n\
    \                        } else if (left(edge, point(vertex + 1))) {\n       \
    \                     vertex = exit_left_bay(\n                              \
    \  vertex,\n                                point(vertex),\n                 \
    \               line(left_lid_index_, left_lid_index_ - 1)\n                 \
    \           ) + 1;\n                        } else {\n                       \
    \     restore_lid();\n                            push(vertex++, left_wall);\n\
    \                            break;\n                        }\n             \
    \           edge = line(vertex - 1, vertex);\n                    } else if (!left(edge,\
    \ top())) {\n                        if (right_lid_index_ == not_saved) break;\n\
    \                        vertex = exit_right_bay(\n                          \
    \  vertex, top(), edge.negated()\n                        );\n               \
    \         push(vertex++, right_lid);\n                        break;\n       \
    \             } else {\n                        save_lid();\n                \
    \    }\n                }\n            } while (vertex < static_cast<int>(size_\
    \ + origin_index));\n\n            std::vector<Index> result;\n            while\
    \ (!vertices_.empty()) {\n                while (\n                    !vertices_.empty()\
    \ &&\n                    (types_.back() == right_lid ||\n                   \
    \  types_.back() == left_lid)\n                ) {\n                    vertices_.pop_back();\n\
    \                    types_.pop_back();\n                }\n                if\
    \ (vertices_.empty()) break;\n                result.push_back(\n            \
    \        static_cast<Index>(vertices_.back()) % size_\n                );\n  \
    \              vertices_.pop_back();\n                types_.pop_back();\n   \
    \         }\n            return result;\n        }\n\n       private:\n      \
    \  static constexpr int not_saved = -1;\n\n        const std::vector<Point<T>>&\
    \ polygon_;\n        long double eps_;\n        Index size_;\n        const Point<T>*\
    \ origin_ = nullptr;\n        std::vector<int> vertices_;\n        std::vector<VertexType>\
    \ types_;\n        int left_lid_index_ = not_saved;\n        int right_lid_index_\
    \ = not_saved;\n\n        const Point<T>& point(int index) const {\n         \
    \   int reduced = index % static_cast<int>(size_);\n            if (reduced <\
    \ 0) reduced += static_cast<int>(size_);\n            return polygon_[static_cast<Index>(reduced)];\n\
    \        }\n        const Point<T>& top() const { return point(vertices_.back());\
    \ }\n        Homogeneous line(int first, int second) const {\n            return\
    \ Homogeneous::line(point(first), point(second));\n        }\n        bool left(\n\
    \            const Homogeneous& line_value,\n            const Point<T>& point_value\n\
    \        ) const {\n            return\n                predicate_sign<T>(line_value.side(point_value),\
    \ eps_) > 0;\n        }\n        bool right(\n            const Homogeneous& line_value,\n\
    \            const Point<T>& point_value\n        ) const {\n            return\n\
    \                predicate_sign<T>(line_value.side(point_value), eps_) < 0;\n\
    \        }\n        bool clockwise(\n            const Homogeneous& first,\n \
    \           const Homogeneous& second,\n            const Homogeneous& third\n\
    \        ) const {\n            return predicate_sign<T>(\n                Homogeneous::determinant(first,\
    \ second, third), eps_\n            ) < 0;\n        }\n        void push(int index,\
    \ VertexType type) {\n            vertices_.push_back(index);\n            types_.push_back(type);\n\
    \        }\n\n        void save_lid() {\n            if (types_.back() == left_wall)\
    \ {\n                vertices_.pop_back();\n                types_.pop_back();\n\
    \            }\n            left_lid_index_ = vertices_.back();\n            vertices_.pop_back();\n\
    \            types_.pop_back();\n            if (types_.back() == right_lid) {\n\
    \                right_lid_index_ = vertices_.back();\n                vertices_.pop_back();\n\
    \                types_.pop_back();\n            } else {\n                right_lid_index_\
    \ = not_saved;\n            }\n        }\n\n        void restore_lid() {\n   \
    \         if (right_lid_index_ != not_saved) {\n                push(right_lid_index_,\
    \ right_lid);\n            }\n            push(left_lid_index_, left_lid);\n \
    \       }\n\n        int exit_right_bay(\n            int vertex,\n          \
    \  const Point<T>& bottom,\n            const Homogeneous& lid\n        ) const\
    \ {\n            int winding = 0;\n            const Homogeneous mouth = Homogeneous::line(*origin_,\
    \ bottom);\n            bool current_left = false;\n            while (++vertex\
    \ < 3 * static_cast<int>(size_)) {\n                const bool last_left = current_left;\n\
    \                current_left = left(mouth, point(vertex));\n                if\
    \ (\n                    current_left != last_left &&\n                    (orientation(\n\
    \                         point(vertex - 1),\n                         point(vertex),\n\
    \                         *origin_,\n                         eps_\n         \
    \            ) > 0) == current_left\n                ) {\n                   \
    \ if (!current_left) {\n                        --winding;\n                 \
    \   } else if (winding++ == 0) {\n                        const Homogeneous edge\
    \ = line(vertex - 1, vertex);\n                        if (\n                \
    \            left(edge, bottom) &&\n                            !clockwise(mouth,\
    \ edge, lid)\n                        ) {\n                            return\
    \ vertex - 1;\n                        }\n                    }\n            \
    \    }\n            }\n            return vertex;\n        }\n\n        int exit_left_bay(\n\
    \            int vertex,\n            const Point<T>& bottom,\n            const\
    \ Homogeneous& lid\n        ) const {\n            int winding = 0;\n        \
    \    const Homogeneous mouth = Homogeneous::line(*origin_, bottom);\n        \
    \    bool current_right = false;\n            while (++vertex < 3 * static_cast<int>(size_))\
    \ {\n                const bool last_right = current_right;\n                current_right\
    \ = right(mouth, point(vertex));\n                if (\n                    current_right\
    \ != last_right &&\n                    (orientation(\n                      \
    \   point(vertex - 1),\n                         point(vertex),\n            \
    \             *origin_,\n                         eps_\n                     )\
    \ < 0) == current_right\n                ) {\n                    if (!current_right)\
    \ {\n                        ++winding;\n                    } else if (winding--\
    \ == 0) {\n                        const Homogeneous edge = line(vertex - 1, vertex);\n\
    \                        if (\n                            right(edge, bottom)\
    \ &&\n                            !clockwise(mouth, edge, lid)\n             \
    \           ) {\n                            return vertex - 1;\n            \
    \            }\n                    }\n                }\n            }\n    \
    \        return vertex;\n        }\n    };\n\n   public:\n    KeilSnoeyinkDecomposition(\n\
    \        const std::vector<Point<T>>& polygon,\n        long double eps\n    )\n\
    \        : polygon_(polygon),\n          eps_(eps),\n          size_(polygon.size()),\n\
    \          reflex_(size_, false),\n          remapped_(size_) {}\n\n    std::optional<std::vector<Diagonal>>\
    \ run() {\n        initialize_reflex_vertices();\n        allocate_states();\n\
    \        initialize_visibility();\n        initialize_base_subproblems();\n\n\
    \        for (int span = 3; span < static_cast<int>(size_); ++span) {\n      \
    \      for (const int first : reflex_vertices_) {\n                const int last\
    \ = first + span;\n                if (last >= static_cast<int>(size_)) break;\n\
    \                if (!visible(first, last)) continue;\n                initialize_pairs(first,\
    \ last);\n                if (reflex_[last]) {\n                    for (int middle\
    \ = first + 1; middle < last; ++middle) {\n                        type_a(first,\
    \ middle, last);\n                    }\n                } else {\n          \
    \          for (const int middle : reflex_vertices_) {\n                     \
    \   if (middle <= first) continue;\n                        if (middle >= last\
    \ - 1) break;\n                        type_a(first, middle, last);\n        \
    \            }\n                    type_a(first, last - 1, last);\n         \
    \       }\n            }\n\n            for (const int last : reflex_vertices_)\
    \ {\n                if (last < span) continue;\n                const int first\
    \ = last - span;\n                if (reflex_[first] || !visible(first, last))\
    \ continue;\n                initialize_pairs(first, last);\n                type_b(first,\
    \ first + 1, last);\n                for (const int middle : reflex_vertices_)\
    \ {\n                    if (middle <= first + 1) continue;\n                \
    \    if (middle >= last) break;\n                    type_b(first, middle, last);\n\
    \                }\n            }\n        }\n\n        if (weight(0, static_cast<int>(size_)\
    \ - 1) >= infinity) {\n            return std::nullopt;\n        }\n        std::vector<Diagonal>\
    \ diagonals;\n        const PairDeque& root = state(0, static_cast<int>(size_)\
    \ - 1).pairs;\n        if (root.pairs.empty()) return std::nullopt;\n        flatten(root.pairs.front().solution,\
    \ diagonals);\n        for (Diagonal& diagonal : diagonals) {\n            if\
    \ (diagonal.second < diagonal.first) {\n                std::swap(diagonal.first,\
    \ diagonal.second);\n            }\n        }\n        std::sort(\n          \
    \  diagonals.begin(),\n            diagonals.end(),\n            [](const Diagonal&\
    \ first, const Diagonal& second) {\n                return std::pair(first.first,\
    \ first.second) <\n                       std::pair(second.first, second.second);\n\
    \            }\n        );\n        diagonals.erase(\n            std::unique(\n\
    \                diagonals.begin(),\n                diagonals.end(),\n      \
    \          [](const Diagonal& first, const Diagonal& second) {\n             \
    \       return\n                        first.first == second.first &&\n     \
    \                   first.second == second.second;\n                }\n      \
    \      ),\n            diagonals.end()\n        );\n        if (\n           \
    \ static_cast<int>(diagonals.size()) !=\n            weight(0, static_cast<int>(size_)\
    \ - 1)\n        ) {\n            return std::nullopt;\n        }\n        return\
    \ diagonals;\n    }\n\n   private:\n    const std::vector<Point<T>>& polygon_;\n\
    \    long double eps_;\n    Index size_;\n    std::vector<bool> reflex_;\n   \
    \ std::vector<int> reflex_vertices_;\n    std::vector<int> remapped_;\n    std::vector<std::vector<State>>\
    \ states_;\n\n    void initialize_reflex_vertices() {\n        for (int index\
    \ = 0; index < static_cast<int>(size_); ++index) {\n            reflex_[index]\
    \ = index == 0 || orientation(\n                polygon_[(index + static_cast<int>(size_)\
    \ - 1) % size_],\n                polygon_[index],\n                polygon_[(index\
    \ + 1) % size_],\n                eps_\n            ) < 0;\n            if (reflex_[index])\
    \ reflex_vertices_.push_back(index);\n        }\n    }\n\n    void allocate_states()\
    \ {\n        int next = 0;\n        for (const int index : reflex_vertices_) remapped_[index]\
    \ = next++;\n        for (int index = 0; index < static_cast<int>(size_); ++index)\
    \ {\n            if (!reflex_[index]) remapped_[index] = next++;\n        }\n\
    \        const int reflex_count = static_cast<int>(reflex_vertices_.size());\n\
    \        states_.resize(size_);\n        for (int index = 0; index < static_cast<int>(size_);\
    \ ++index) {\n            states_[index].resize(reflex_[index] ? size_ : reflex_count);\n\
    \        }\n    }\n\n    State& state(int first, int last) {\n        assert(first\
    \ <= last);\n        assert(reflex_[first] || reflex_[last]);\n        return\
    \ states_[first][remapped_[last]];\n    }\n    const State& state(int first, int\
    \ last) const {\n        assert(first <= last);\n        assert(reflex_[first]\
    \ || reflex_[last]);\n        return states_[first][remapped_[last]];\n    }\n\
    \    int weight(int first, int last) const {\n        return state(first, last).weight;\n\
    \    }\n    bool visible(int first, int last) const {\n        return weight(first,\
    \ last) < bad;\n    }\n\n    void initialize_visibility() {\n        VisibilityPolygon\
    \ visibility_polygon(polygon_, eps_);\n        for (const int reflex : reflex_vertices_)\
    \ {\n            for (const Index visible_vertex :\n                 visibility_polygon.build(static_cast<Index>(reflex)))\
    \ {\n                int first = reflex;\n                int last = static_cast<int>(visible_vertex);\n\
    \                if (last < first) std::swap(first, last);\n                if\
    \ (first == last) continue;\n                state(first, last).weight = infinity;\n\
    \            }\n        }\n        // The visibility scan treats the closing edge\
    \ like every other\n        // boundary edge, but make the DP convention explicit.\n\
    \        state(0, static_cast<int>(size_) - 1).weight = infinity;\n    }\n\n \
    \   void initialize_base_subproblems() {\n        const int size = static_cast<int>(size_);\n\
    \        for (const int index : reflex_vertices_) {\n            if (index + 1\
    \ < size) state(index, index + 1).weight = 0;\n            if (index > 0) state(index\
    \ - 1, index).weight = 0;\n            if (index + 2 < size && visible(index,\
    \ index + 2)) {\n                State& base = state(index, index + 2);\n    \
    \            base.weight = 0;\n                base.pairs.clear();\n         \
    \       base.pairs.push(index + 1, index + 1, nullptr);\n            }\n     \
    \       if (index >= 2 && visible(index - 2, index)) {\n                State&\
    \ base = state(index - 2, index);\n                base.weight = 0;\n        \
    \        base.pairs.clear();\n                base.pairs.push(index - 1, index\
    \ - 1, nullptr);\n            }\n        }\n    }\n\n    void initialize_pairs(int\
    \ first, int last) {\n        state(first, last).pairs.clear();\n    }\n\n   \
    \ void update(\n        int first,\n        int last,\n        int new_weight,\n\
    \        int pair_first,\n        int pair_second,\n        NodePointer solution\n\
    \    ) {\n        State& subproblem = state(first, last);\n        if (new_weight\
    \ > subproblem.weight) return;\n        if (new_weight < subproblem.weight) {\n\
    \            subproblem.weight = new_weight;\n            subproblem.pairs.clear();\n\
    \        }\n        subproblem.pairs.push_narrow(\n            pair_first, pair_second,\
    \ std::move(solution)\n        );\n    }\n\n    NodePointer concatenate(NodePointer\
    \ first, NodePointer second) const {\n        if (!first) return second;\n   \
    \     if (!second) return first;\n        SolutionNode node;\n        node.first\
    \ = std::move(first);\n        node.second = std::move(second);\n        return\
    \ std::make_shared<const SolutionNode>(std::move(node));\n    }\n\n    NodePointer\
    \ append_diagonal(\n        NodePointer solution,\n        int first,\n      \
    \  int last\n    ) const {\n        SolutionNode leaf;\n        leaf.diagonal\
    \ = Diagonal{\n            static_cast<Index>(first), static_cast<Index>(last)\n\
    \        };\n        leaf.is_diagonal = true;\n        return concatenate(\n \
    \           std::move(solution),\n            std::make_shared<const SolutionNode>(std::move(leaf))\n\
    \        );\n    }\n\n    NodePointer any_solution(int first, int last) const\
    \ {\n        const PairDeque& pairs = state(first, last).pairs;\n        assert(!pairs.pairs.empty());\n\
    \        return pairs.pairs.front().solution;\n    }\n\n    void type_a(int first,\
    \ int middle, int last) {\n        if (!visible(first, middle)) return;\n    \
    \    int top = middle;\n        int new_weight = weight(first, middle);\n    \
    \    NodePointer solution;\n        if (last - middle > 1) {\n            if (!visible(middle,\
    \ last)) return;\n            new_weight += weight(middle, last) + 1;\n      \
    \      solution = any_solution(middle, last);\n            solution = append_diagonal(\n\
    \                std::move(solution), middle, last\n            );\n        }\n\
    \        bool use_first_diagonal = false;\n        if (middle - first > 1) {\n\
    \            PairDeque& pairs = state(first, middle).pairs;\n            if (pairs.empty_back())\
    \ return;\n            if (\n                orientation(\n                  \
    \  polygon_[last],\n                    polygon_[middle],\n                  \
    \  polygon_[pairs.back_pair().second],\n                    eps_\n           \
    \     ) <= 0\n            ) {\n                while (\n                    pairs.more_back()\
    \ &&\n                    orientation(\n                        polygon_[last],\n\
    \                        polygon_[middle],\n                        polygon_[pairs.under_back().second],\n\
    \                        eps_\n                    ) <= 0\n                ) {\n\
    \                    pairs.pop_back();\n                }\n                if\
    \ (\n                    !pairs.empty_back() &&\n                    orientation(\n\
    \                        polygon_[last],\n                        polygon_[first],\n\
    \                        polygon_[pairs.back_pair().first],\n                \
    \        eps_\n                    ) >= 0\n                ) {\n             \
    \       top = pairs.back_pair().first;\n                } else {\n           \
    \         ++new_weight;\n                    use_first_diagonal = true;\n    \
    \            }\n            } else {\n                ++new_weight;\n        \
    \        use_first_diagonal = true;\n            }\n            solution = concatenate(\n\
    \                pairs.back_pair().solution, std::move(solution)\n           \
    \ );\n            if (use_first_diagonal) {\n                solution = append_diagonal(\n\
    \                    std::move(solution), first, middle\n                );\n\
    \            }\n        }\n        update(\n            first,\n            last,\n\
    \            new_weight,\n            top,\n            middle,\n            std::move(solution)\n\
    \        );\n    }\n\n    void type_b(int first, int middle, int last) {\n   \
    \     if (!visible(middle, last)) return;\n        int top = middle;\n       \
    \ int new_weight = weight(middle, last);\n        NodePointer solution;\n    \
    \    if (middle - first > 1) {\n            if (!visible(first, middle)) return;\n\
    \            new_weight += weight(first, middle) + 1;\n            solution =\
    \ any_solution(first, middle);\n            solution = append_diagonal(\n    \
    \            std::move(solution), first, middle\n            );\n        }\n \
    \       bool use_second_diagonal = false;\n        if (last - middle > 1) {\n\
    \            PairDeque& pairs = state(middle, last).pairs;\n            if (pairs.empty_front())\
    \ return;\n            if (\n                orientation(\n                  \
    \  polygon_[first],\n                    polygon_[middle],\n                 \
    \   polygon_[pairs.front_pair().first],\n                    eps_\n          \
    \      ) >= 0\n            ) {\n                while (\n                    pairs.more_front()\
    \ &&\n                    orientation(\n                        polygon_[first],\n\
    \                        polygon_[middle],\n                        polygon_[pairs.under_front().first],\n\
    \                        eps_\n                    ) >= 0\n                ) {\n\
    \                    pairs.pop_front();\n                }\n                if\
    \ (\n                    !pairs.empty_front() &&\n                    orientation(\n\
    \                        polygon_[first],\n                        polygon_[last],\n\
    \                        polygon_[pairs.front_pair().second],\n              \
    \          eps_\n                    ) <= 0\n                ) {\n           \
    \         top = pairs.front_pair().second;\n                } else {\n       \
    \             ++new_weight;\n                    use_second_diagonal = true;\n\
    \                }\n            } else {\n                ++new_weight;\n    \
    \            use_second_diagonal = true;\n            }\n            solution\
    \ = concatenate(\n                std::move(solution), pairs.front_pair().solution\n\
    \            );\n            if (use_second_diagonal) {\n                solution\
    \ = append_diagonal(\n                    std::move(solution), middle, last\n\
    \                );\n            }\n        }\n        update(\n            first,\n\
    \            last,\n            new_weight,\n            middle,\n           \
    \ top,\n            std::move(solution)\n        );\n    }\n\n    void flatten(\n\
    \        const NodePointer& node,\n        std::vector<Diagonal>& diagonals\n\
    \    ) const {\n        if (!node) return;\n        if (node->is_diagonal) {\n\
    \            diagonals.push_back(node->diagonal);\n            return;\n     \
    \   }\n        flatten(node->first, diagonals);\n        flatten(node->second,\
    \ diagonals);\n    }\n\n};\n\ntemplate <Coordinate T>\nstd::optional<std::vector<IndexPolygon>>\
    \ faces_from_diagonals(\n    const std::vector<Point<T>>& polygon,\n    const\
    \ std::vector<Diagonal>& diagonals,\n    long double eps\n) {\n    const Index\
    \ size = polygon.size();\n    std::vector<std::vector<Index>> adjacent(size);\n\
    \    auto add_edge = [&](Index first, Index second) {\n        adjacent[first].push_back(second);\n\
    \        adjacent[second].push_back(first);\n    };\n    for (Index index = 0;\
    \ index < size; ++index) {\n        add_edge(index, (index + 1) % size);\n   \
    \ }\n    for (const Diagonal& diagonal : diagonals) {\n        if (\n        \
    \    diagonal.first >= size || diagonal.second >= size ||\n            diagonal.first\
    \ == diagonal.second\n        ) {\n            return std::nullopt;\n        }\n\
    \        add_edge(diagonal.first, diagonal.second);\n    }\n\n    for (Index origin\
    \ = 0; origin < size; ++origin) {\n        auto upper_half = [&](Index target)\
    \ {\n            const auto direction = polygon[target] - polygon[origin];\n \
    \           const int y_sign = sign<T>(direction.y, eps);\n            return\n\
    \                y_sign > 0 ||\n                (y_sign == 0 && sign<T>(direction.x,\
    \ eps) >= 0);\n        };\n        std::sort(\n            adjacent[origin].begin(),\n\
    \            adjacent[origin].end(),\n            [&](Index first, Index second)\
    \ {\n                const bool first_upper = upper_half(first);\n           \
    \     const bool second_upper = upper_half(second);\n                if (first_upper\
    \ != second_upper) return first_upper;\n                const auto first_direction\
    \ =\n                    polygon[first] - polygon[origin];\n                const\
    \ auto second_direction =\n                    polygon[second] - polygon[origin];\n\
    \                const int turn = sign<T>(\n                    cross(first_direction,\
    \ second_direction), eps\n                );\n                if (turn != 0) return\
    \ turn > 0;\n                return\n                    norm2(first_direction)\
    \ < norm2(second_direction);\n            }\n        );\n        adjacent[origin].erase(\n\
    \            std::unique(\n                adjacent[origin].begin(), adjacent[origin].end()\n\
    \            ),\n            adjacent[origin].end()\n        );\n    }\n\n   \
    \ std::vector<std::vector<bool>> visited(size);\n    Index directed_edge_count\
    \ = 0;\n    for (Index index = 0; index < size; ++index) {\n        visited[index].assign(adjacent[index].size(),\
    \ false);\n        directed_edge_count += adjacent[index].size();\n    }\n\n \
    \   std::vector<IndexPolygon> result;\n    for (Index start = 0; start < size;\
    \ ++start) {\n        for (Index start_position = 0;\n             start_position\
    \ < adjacent[start].size();\n             ++start_position) {\n            if\
    \ (visited[start][start_position]) continue;\n            IndexPolygon face;\n\
    \            Index current = start;\n            Index position = start_position;\n\
    \            for (Index guard = 0;; ++guard) {\n                if (guard > directed_edge_count)\
    \ return std::nullopt;\n                if (visited[current][position]) {\n  \
    \                  if (current != start || position != start_position) {\n   \
    \                     return std::nullopt;\n                    }\n          \
    \          break;\n                }\n                visited[current][position]\
    \ = true;\n                face.push_back(current);\n                const Index\
    \ next = adjacent[current][position];\n                const auto reverse = std::find(\n\
    \                    adjacent[next].begin(), adjacent[next].end(), current\n \
    \               );\n                if (reverse == adjacent[next].end()) return\
    \ std::nullopt;\n                const Index reverse_position =\n            \
    \        static_cast<Index>(reverse - adjacent[next].begin());\n             \
    \   current = next;\n                position =\n                    (reverse_position\
    \ + adjacent[current].size() - 1) %\n                    adjacent[current].size();\n\
    \            }\n            if (face.size() < 3) continue;\n            std::vector<Point<T>>\
    \ points;\n            points.reserve(face.size());\n            for (const Index\
    \ index : face) points.push_back(polygon[index]);\n            if (sign<T>(polygon_area2(points),\
    \ eps) > 0) {\n                if (!is_weakly_convex(face, polygon, eps)) {\n\
    \                    return std::nullopt;\n                }\n               \
    \ result.push_back(std::move(face));\n            }\n        }\n    }\n    if\
    \ (result.size() != diagonals.size() + 1) return std::nullopt;\n    return result;\n\
    }\n\n}  // namespace convex_decomposition_detail\n\ntemplate <Coordinate T>\n\
    std::optional<std::vector<std::vector<Point<T>>>>\nconvex_decomposition(\n   \
    \ std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    auto\
    \ prepared = convex_decomposition_detail::prepare_polygon(\n        std::move(polygon),\
    \ eps\n    );\n    if (!prepared.has_value()) return std::nullopt;\n    polygon\
    \ = std::move(*prepared);\n    if (convex_decomposition_detail::is_weakly_convex(polygon,\
    \ eps)) {\n        return std::vector<std::vector<Point<T>>>{std::move(polygon)};\n\
    \    }\n\n    auto triangulation =\n        convex_decomposition_detail::triangulate_indices(polygon,\
    \ eps);\n    if (!triangulation.has_value()) return std::nullopt;\n\n    using\
    \ convex_decomposition_detail::Index;\n    using convex_decomposition_detail::IndexPolygon;\n\
    \    const Index triangle_count = triangulation->size();\n    const Index absent\
    \ = std::numeric_limits<Index>::max();\n    struct Owners {\n        Index first\
    \ = std::numeric_limits<Index>::max();\n        Index second = std::numeric_limits<Index>::max();\n\
    \    };\n    std::map<std::pair<Index, Index>, Owners> edge_owners;\n    for (Index\
    \ triangle = 0; triangle < triangle_count; ++triangle) {\n        for (Index edge\
    \ = 0; edge < 3; ++edge) {\n            Index first = (*triangulation)[triangle][edge];\n\
    \            Index second = (*triangulation)[triangle][(edge + 1) % 3];\n    \
    \        if (second < first) std::swap(first, second);\n            Owners& owners\
    \ = edge_owners[{first, second}];\n            if (owners.first == absent) {\n\
    \                owners.first = triangle;\n            } else {\n            \
    \    owners.second = triangle;\n            }\n        }\n    }\n\n    std::vector<Index>\
    \ parent(triangle_count);\n    std::vector<IndexPolygon> pieces = std::move(*triangulation);\n\
    \    for (Index index = 0; index < triangle_count; ++index) {\n        parent[index]\
    \ = index;\n    }\n    for (const auto& [edge, owners] : edge_owners) {\n    \
    \    if (owners.second == absent) continue;\n        Index first_root =\n    \
    \        convex_decomposition_detail::find_root(parent, owners.first);\n     \
    \   Index second_root =\n            convex_decomposition_detail::find_root(parent,\
    \ owners.second);\n        if (first_root == second_root) continue;\n\n      \
    \  auto merged = convex_decomposition_detail::merge_across_edge(\n           \
    \ pieces[first_root],\n            pieces[second_root],\n            edge.first,\n\
    \            edge.second\n        );\n        if (\n            !merged.has_value()\
    \ ||\n            !convex_decomposition_detail::is_weakly_convex(\n          \
    \      *merged, polygon, eps\n            )\n        ) {\n            continue;\n\
    \        }\n        pieces[first_root] = std::move(*merged);\n        pieces[second_root].clear();\n\
    \        parent[second_root] = first_root;\n    }\n\n    std::vector<std::vector<Point<T>>>\
    \ result;\n    for (Index index = 0; index < triangle_count; ++index) {\n    \
    \    if (convex_decomposition_detail::find_root(parent, index) != index) {\n \
    \           continue;\n        }\n        result.push_back(convex_decomposition_detail::materialize(\n\
    \            pieces[index], polygon, eps\n        ));\n    }\n    return result;\n\
    }\n\ntemplate <Coordinate T>\nstd::optional<std::vector<std::vector<Point<T>>>>\n\
    minimum_convex_decomposition(\n    std::vector<Point<T>> polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    auto prepared = convex_decomposition_detail::prepare_minimum_polygon(\n\
    \        std::move(polygon), eps\n    );\n    if (!prepared.has_value()) return\
    \ std::nullopt;\n    polygon = std::move(*prepared);\n    if (convex_decomposition_detail::is_weakly_convex(polygon,\
    \ eps)) {\n        return std::vector<std::vector<Point<T>>>{std::move(polygon)};\n\
    \    }\n\n    std::size_t first_reflex = polygon.size();\n    for (std::size_t\
    \ index = 0; index < polygon.size(); ++index) {\n        if (\n            orientation(\n\
    \                polygon[(index + polygon.size() - 1) % polygon.size()],\n   \
    \             polygon[index],\n                polygon[(index + 1) % polygon.size()],\n\
    \                eps\n            ) < 0\n        ) {\n            first_reflex\
    \ = index;\n            break;\n        }\n    }\n    assert(first_reflex < polygon.size());\n\
    \    std::rotate(\n        polygon.begin(), polygon.begin() + first_reflex, polygon.end()\n\
    \    );\n\n    std::size_t reflex_count = 0;\n    for (std::size_t index = 0;\
    \ index < polygon.size(); ++index) {\n        if (\n            orientation(\n\
    \                polygon[(index + polygon.size() - 1) % polygon.size()],\n   \
    \             polygon[index],\n                polygon[(index + 1) % polygon.size()],\n\
    \                eps\n            ) < 0\n        ) {\n            ++reflex_count;\n\
    \        }\n    }\n\n    auto solve = [&]<typename Number>()\n        -> std::optional<std::vector<std::vector<Point<T>>>>\
    \ {\n        std::vector<Point<T>> dynamic_polygon = polygon;\n        std::vector<convex_decomposition_detail::Index>\
    \ original_index(\n            polygon.size()\n        );\n        for (std::size_t\
    \ index = 0; index < polygon.size(); ++index) {\n            original_index[index]\
    \ = index;\n        }\n        if (\n            reflex_count > 0 &&\n       \
    \     polygon.size() / reflex_count > reflex_count\n        ) {\n            convex_decomposition_detail::BiasedPolygonReduction<T,\
    \ Number>\n                reduction(polygon, eps);\n            auto reduced\
    \ = reduction.run();\n            dynamic_polygon = std::move(reduced.polygon);\n\
    \            original_index = std::move(reduced.original_index);\n        }\n\n\
    \        convex_decomposition_detail::KeilSnoeyinkDecomposition<T, Number>\n \
    \           solver(dynamic_polygon, eps);\n        auto diagonals = solver.run();\n\
    \        if (!diagonals.has_value()) return std::nullopt;\n        for (auto&\
    \ diagonal : *diagonals) {\n            diagonal.first = original_index[diagonal.first];\n\
    \            diagonal.second = original_index[diagonal.second];\n        }\n \
    \       auto index_decomposition =\n            convex_decomposition_detail::faces_from_diagonals(\n\
    \                polygon, *diagonals, eps\n            );\n        if (!index_decomposition.has_value())\
    \ return std::nullopt;\n\n        std::vector<std::vector<Point<T>>> result;\n\
    \        result.reserve(index_decomposition->size());\n        for (const auto&\
    \ indices : *index_decomposition) {\n            result.push_back(convex_decomposition_detail::materialize(\n\
    \                indices, polygon, eps\n            ));\n        }\n        return\
    \ result;\n    };\n\n    if constexpr (std::integral<T>) {\n        using convex_decomposition_detail::ExactPredicateWidth;\n\
    \        switch (\n            convex_decomposition_detail::select_exact_predicate_width(\n\
    \                polygon\n            )\n        ) {\n            case ExactPredicateWidth::Int128:\n\
    \                return solve.template operator()<__int128_t>();\n           \
    \ case ExactPredicateWidth::Int256:\n                return solve.template operator()<\n\
    \                    m1une::utilities::Int256\n                >();\n        \
    \    case ExactPredicateWidth::Int512:\n                return solve.template\
    \ operator()<\n                    m1une::utilities::Int512\n                >();\n\
    \        }\n        assert(false);\n        return std::nullopt;\n    } else {\n\
    \        return solve.template operator()<long double>();\n    }\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_CONVEX_DECOMPOSITION_HPP\n"
  dependsOn:
  - utilities/int256.hpp
  - utilities/detail/fixed_int.hpp
  - utilities/int512.hpp
  - geometry/polygon.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/convex_decomposition.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 10:48:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/convex_decomposition.hpp
layout: document
title: Convex Decomposition
---

## Overview

This header partitions a simple polygon without holes into convex polygons. It
provides two choices:

* `convex_decomposition` triangulates the polygon and applies the
  Hertel--Mehlhorn diagonal-removal algorithm. It is the routine to use under
  ordinary contest constraints.
* `minimum_convex_decomposition` uses Keil--Snoeyink dynamic programming over
  visible diagonals and narrowest-pair stacks. It returns the smallest possible
  number of pieces. Its running time is sensitive to the number of reflex
  vertices rather than being quartic in the total vertex count.

Both algorithms return an exact geometric partition: the pieces have disjoint
interiors and their union is exactly the input polygon. The approximation
guarantee of `convex_decomposition` concerns only how many pieces it returns
compared with the minimum possible number.

Both algorithms use the **no-Steiner-point model**: every output vertex is an
input vertex, apart from removing redundant boundary vertices. This restriction
is important when interpreting the piece-count guarantee and the word
"minimum." For a floating-point decomposition that may introduce Steiner
vertices and guarantees fewer than twice the unrestricted optimum, see
[`steiner_convex_decomposition`](steiner_convex_decomposition.md).

## Functions

```cpp
template <Coordinate T>
std::optional<std::vector<std::vector<Point<T>>>>
convex_decomposition(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
std::optional<std::vector<std::vector<Point<T>>>>
minimum_convex_decomposition(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);
```

| Function | Result | Time | Memory |
| --- | --- | --- | --- |
| `convex_decomposition(polygon, eps)` | An exact partition containing at most four times the minimum number of convex pieces. | $O(N^2)$ | $O(N)$ |
| `minimum_convex_decomposition(polygon, eps)` | A decomposition with the minimum possible number of pieces. | $O(N + \min\lbrace NR^2, R^4 \rbrace)$ | $O(N + \min\lbrace NR^2, R^4 \rbrace)$ |

Here $N$ is the number of vertices after cleanup and $R$ is the number of
reflex vertices (vertices whose interior angle is greater than $\pi$).

The bound for the exact routine is easy to misread. The implementation chooses
between these two Keil--Snoeyink paths:

* The direct narrowest-pair DP stores only subproblems with at least one reflex
  endpoint and takes $O(NR^2)$ time and memory.
* When $R^2 < N$, biased-decomposition reduction retains the $O(R^2)$ vertices
  that can be endpoints of reflex extensions and diagonal extensions, and runs
  the same DP on that reduced polygon. Including reduction and reconstruction,
  this path takes $O(N + R^4)$ time and memory.

The minimum of those paths is therefore
$O(N + \min\lbrace NR^2, R^4 \rbrace)$. The reduction is internal: output pieces still
contain the original polygon boundary, including vertices omitted from the DP
instance. $R$ is not the number of vertices in the reduced polygon.

## Input and output rules

The input may be clockwise or counterclockwise. A repeated closing point,
consecutive duplicates, and redundant collinear boundary vertices are removed.
The polygon must be simple and have no holes. The exact routine treats
simplicity as a precondition so that it does not add an $O(N^2)$ validation step
to its reflex-sensitive bound. `convex_decomposition` validates simplicity.
The return value is `nullopt` when fewer than three effective vertices remain,
the area is zero, validation fails where performed, or construction fails.

Every returned polygon is counterclockwise, does not repeat its first point at
the end, and is convex in the non-strict sense. The pieces have disjoint
interiors and their union is the original closed polygon.

"Minimum" means the minimum **number of non-strictly convex pieces**, not that
each piece is strictly convex. Collinear vertices can therefore occur on an
output boundary. The approximation factor compares against the same
no-Steiner-point optimum.

For standard integral coordinate types up to 64 bits, the exact routine
performs no floating-point conversion. It scans the cleaned polygon once and
selects the smallest integer type that is provably wide enough for its
projective visibility predicates and rational ray-intersection comparisons:

| Largest coordinate magnitude | Predicate type |
| --- | --- |
| Fewer than $2^{30}$ | built-in `__int128_t` |
| Fewer than $2^{62}$ | [`Int256`](../utilities/int256.md) |
| Otherwise | [`Int512`](../utilities/int512.md) |

The largest intermediate has magnitude below $2^{4k+6}$ when coordinate
magnitudes use at most $k$ bits. Thus full-range 32-bit coordinates are not
dispatched to `__int128_t`, while the common bound
$|x|,|y|\le 10^9$ is.
Selection uses absolute coordinates rather than edge lengths because
homogeneous line coefficients are formed before translation-dependent terms
cancel; translating a polygon far from the origin can therefore select a wider
type. The scan costs $O(N)$ and does not change the overall bound.

Input turns still use the geometry module's ordinary widened integer type, so
results are exact as long as those ordinary predicates do not overflow. `eps`
has no effect on integral predicates.

For floating-point coordinates, visibility and ray shooting use `long double`,
and `eps` controls predicate tolerance.

## Example

```cpp
#include "geometry/convex_decomposition.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> polygon;
    polygon.emplace_back(0, 0);
    polygon.emplace_back(5, 0);
    polygon.emplace_back(5, 2);
    polygon.emplace_back(2, 2);
    polygon.emplace_back(2, 5);
    polygon.emplace_back(0, 5);

    auto parts = m1une::geometry::convex_decomposition(polygon);
    if (!parts.has_value()) return 0;
    std::cout << parts->size() << "\n";  // 2
}
```
