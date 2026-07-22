---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/convex_decomposition.hpp
    title: Convex Decomposition
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon.hpp
    title: Convex Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
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
    path: utilities/fast_io.hpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: utilities/int256.hpp
    title: Int256
  - icon: ':heavy_check_mark:'
    path: utilities/int512.hpp
    title: Int512
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
  bundledCode: "#line 1 \"verify/geometry/convex_decomposition.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\"\
    \n\n#line 1 \"geometry/convex_decomposition.hpp\"\n\n\n\n#include <algorithm>\n\
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
    std::optional<std::vector<std::vector<Point<T>>>>\napproximate_convex_decomposition(\n\
    \    std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    auto\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 1 \"geometry/convex_polygon.hpp\"\
    \n\n\n\n#line 12 \"geometry/convex_polygon.hpp\"\n#include <numbers>\n#line 16\
    \ \"geometry/convex_polygon.hpp\"\n\n#line 1 \"geometry/convex_hull.hpp\"\n\n\n\
    \n#line 8 \"geometry/convex_hull.hpp\"\n\n#line 10 \"geometry/convex_hull.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\n// Returns the convex hull counterclockwise\
    \ from its lexicographically smallest\n// point. The first point is not repeated\
    \ at the end.\ntemplate <Coordinate T>\nstd::vector<Point<T>> convex_hull(\n \
    \   std::vector<Point<T>> points,\n    bool include_collinear = false\n) {\n \
    \   std::sort(points.begin(), points.end());\n    points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n    std::size_t size = points.size();\n    if\
    \ (size <= 1) return points;\n\n    std::vector<Point<T>> hull;\n    hull.reserve(2\
    \ * size);\n    auto should_pop = [include_collinear](\n        const Point<T>&\
    \ first,\n        const Point<T>& second,\n        const Point<T>& third\n   \
    \ ) {\n        int turn = orientation(first, second, third);\n        return include_collinear\
    \ ? turn < 0 : turn <= 0;\n    };\n\n    for (const Point<T>& point : points)\
    \ {\n        while (\n            hull.size() >= 2 &&\n            should_pop(hull[hull.size()\
    \ - 2], hull.back(), point)\n        ) {\n            hull.pop_back();\n     \
    \   }\n        hull.push_back(point);\n    }\n\n    std::size_t lower_size = hull.size();\n\
    \    for (std::size_t index = size - 1; index-- > 0;) {\n        const Point<T>&\
    \ point = points[index];\n        while (\n            hull.size() > lower_size\
    \ &&\n            should_pop(hull[hull.size() - 2], hull.back(), point)\n    \
    \    ) {\n            hull.pop_back();\n        }\n        hull.push_back(point);\n\
    \    }\n    hull.pop_back();\n\n    if (include_collinear && hull.size() == 2\
    \ * points.size() - 2) {\n        hull = std::move(points);\n    }\n    return\
    \ hull;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 1 \"\
    geometry/half_plane_intersection.hpp\"\n\n\n\n#line 12 \"geometry/half_plane_intersection.hpp\"\
    \n#include <random>\n#line 15 \"geometry/half_plane_intersection.hpp\"\n\n#line\
    \ 17 \"geometry/half_plane_intersection.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nenum class HalfPlaneIntersectionStatus {\n    Empty,\n    Unbounded,\n\
    \    Degenerate,\n    Bounded,\n};\n\nstruct HalfPlaneIntersectionResult {\n \
    \   HalfPlaneIntersectionStatus status;\n    std::vector<Point<long double>> polygon;\n\
    };\n\nnamespace half_plane_intersection_detail {\n\nstruct HalfPlane {\n    Point<long\
    \ double> point;\n    Point<long double> direction;\n};\n\ninline int direction_half(const\
    \ Point<long double>& direction) {\n    return direction.y > 0 || (direction.y\
    \ == 0 && direction.x >= 0) ? 0 : 1;\n}\n\ninline bool direction_less(const HalfPlane&\
    \ first, const HalfPlane& second) {\n    int first_half = direction_half(first.direction);\n\
    \    int second_half = direction_half(second.direction);\n    if (first_half !=\
    \ second_half) return first_half < second_half;\n    return cross(first.direction,\
    \ second.direction) > 0;\n}\n\ninline bool parallel(\n    const HalfPlane& first,\n\
    \    const HalfPlane& second,\n    long double eps\n) {\n    return std::fabs(cross(first.direction,\
    \ second.direction)) <= eps;\n}\n\ninline bool same_direction(\n    const HalfPlane&\
    \ first,\n    const HalfPlane& second,\n    long double eps\n) {\n    return parallel(first,\
    \ second, eps) &&\n           dot(first.direction, second.direction) > 0;\n}\n\
    \ninline bool outside(\n    const HalfPlane& half_plane,\n    const Point<long\
    \ double>& point,\n    long double eps\n) {\n    return cross(half_plane.direction,\
    \ point - half_plane.point) < -eps;\n}\n\ninline bool more_restrictive(\n    const\
    \ HalfPlane& candidate,\n    const HalfPlane& current,\n    long double eps\n\
    ) {\n    return cross(\n        current.direction,\n        candidate.point -\
    \ current.point\n    ) > eps;\n}\n\ninline std::optional<Point<long double>> intersection(\n\
    \    const HalfPlane& first,\n    const HalfPlane& second,\n    long double eps\n\
    ) {\n    long double denominator = cross(first.direction, second.direction);\n\
    \    if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double\
    \ ratio = cross(\n        second.point - first.point,\n        second.direction\n\
    \    ) / denominator;\n    return first.point + first.direction * ratio;\n}\n\n\
    inline void merge_same_direction(\n    std::vector<HalfPlane>& half_planes,\n\
    \    const HalfPlane& half_plane,\n    long double eps\n) {\n    if (\n      \
    \  half_planes.empty() ||\n        !same_direction(half_planes.back(), half_plane,\
    \ eps)\n    ) {\n        half_planes.push_back(half_plane);\n        return;\n\
    \    }\n    if (more_restrictive(half_plane, half_planes.back(), eps)) {\n   \
    \     half_planes.back() = half_plane;\n    }\n}\n\ninline void merge_cyclic_ends(\n\
    \    std::vector<HalfPlane>& half_planes,\n    long double eps\n) {\n    if (\n\
    \        half_planes.size() < 2 ||\n        !same_direction(half_planes.front(),\
    \ half_planes.back(), eps)\n    ) {\n        return;\n    }\n    if (more_restrictive(half_planes.back(),\
    \ half_planes.front(), eps)) {\n        half_planes.front() = half_planes.back();\n\
    \    }\n    half_planes.pop_back();\n}\n\ninline bool has_feasible_point(\n  \
    \  std::vector<HalfPlane> half_planes,\n    long double eps\n) {\n    std::mt19937_64\
    \ generator(0x6a09e667f3bcc909ULL);\n    std::shuffle(half_planes.begin(), half_planes.end(),\
    \ generator);\n\n    Point<long double> feasible(0, 0);\n    for (std::size_t\
    \ index = 0; index < half_planes.size(); ++index) {\n        const HalfPlane&\
    \ current = half_planes[index];\n        if (!outside(current, feasible, eps))\
    \ continue;\n\n        Point<long double> normal(\n            -current.direction.y,\n\
    \            current.direction.x\n        );\n        Point<long double> base\
    \ = normal * dot(normal, current.point);\n        long double lower = -std::numeric_limits<long\
    \ double>::infinity();\n        long double upper = std::numeric_limits<long double>::infinity();\n\
    \        for (std::size_t previous_index = 0;\n             previous_index < index;\n\
    \             ++previous_index) {\n            const HalfPlane& previous = half_planes[previous_index];\n\
    \            long double coefficient = cross(\n                previous.direction,\n\
    \                current.direction\n            );\n            long double constant\
    \ = cross(\n                previous.direction,\n                base - previous.point\n\
    \            );\n            if (std::fabs(coefficient) <= eps) {\n          \
    \      if (constant < -eps) return false;\n                continue;\n       \
    \     }\n\n            long double bound = (-eps - constant) / coefficient;\n\
    \            if (coefficient > 0) {\n                lower = std::max(lower, bound);\n\
    \            } else {\n                upper = std::min(upper, bound);\n     \
    \       }\n            if (lower > upper) return false;\n        }\n\n       \
    \ long double parameter = 0;\n        if (parameter < lower) parameter = lower;\n\
    \        if (parameter > upper) parameter = upper;\n        feasible = base +\
    \ current.direction * parameter;\n    }\n    return true;\n}\n\ninline bool has_bounded_recession_cone(\n\
    \    const std::vector<HalfPlane>& half_planes,\n    long double eps\n) {\n  \
    \  if (half_planes.empty()) return false;\n\n    constexpr long double pi = std::numbers::pi_v<long\
    \ double>;\n    std::vector<long double> angles;\n    angles.reserve(half_planes.size());\n\
    \    for (const HalfPlane& half_plane : half_planes) {\n        long double angle\
    \ = std::atan2(\n            half_plane.direction.y,\n            half_plane.direction.x\n\
    \        );\n        if (angle < 0) angle += 2 * pi;\n        angles.push_back(angle);\n\
    \    }\n\n    long double maximum_gap = angles.front() + 2 * pi - angles.back();\n\
    \    for (std::size_t index = 1; index < angles.size(); ++index) {\n        maximum_gap\
    \ = std::max(\n            maximum_gap,\n            angles[index] - angles[index\
    \ - 1]\n        );\n    }\n    return maximum_gap < pi - eps;\n}\n\n}  // namespace\
    \ half_plane_intersection_detail\n\n// Each directed line keeps its closed left\
    \ half-plane. Returns the vertices of\n// a bounded intersection with positive\
    \ area in counterclockwise order. Empty,\n// unbounded, and bounded zero-area\
    \ intersections have distinct statuses.\ntemplate <Coordinate T>\nHalfPlaneIntersectionResult\
    \ half_plane_intersection(\n    const std::vector<Line<T>>& half_planes,\n   \
    \ long double eps = 1e-12L\n) {\n    using half_plane_intersection_detail::HalfPlane;\n\
    \    namespace detail = half_plane_intersection_detail;\n\n    assert(eps >= 0);\n\
    \    std::vector<HalfPlane> sorted;\n    sorted.reserve(half_planes.size());\n\
    \    for (const Line<T>& line : half_planes) {\n        assert(line.a != line.b);\n\
    \        Point<long double> point(line.a);\n        Point<long double> direction\
    \ = Point<long double>(line.b) - point;\n        long double length = norm(direction);\n\
    \        direction = direction / length;\n        sorted.push_back(HalfPlane{point,\
    \ direction});\n    }\n    if (!detail::has_feasible_point(sorted, eps)) {\n \
    \       return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Empty,\n\
    \            {},\n        };\n    }\n    std::sort(sorted.begin(), sorted.end(),\
    \ detail::direction_less);\n    if (!detail::has_bounded_recession_cone(sorted,\
    \ eps)) {\n        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Unbounded,\n\
    \            {},\n        };\n    }\n    if (sorted.size() < 3) {\n        return\
    \ HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::vector<HalfPlane> unique;\n  \
    \  unique.reserve(sorted.size());\n    for (const HalfPlane& half_plane : sorted)\
    \ {\n        detail::merge_same_direction(unique, half_plane, eps);\n    }\n \
    \   detail::merge_cyclic_ends(unique, eps);\n    if (unique.size() < 3) {\n  \
    \      return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::deque<HalfPlane> deque;\n    for\
    \ (const HalfPlane& half_plane : unique) {\n        while (deque.size() >= 2)\
    \ {\n            auto point = detail::intersection(\n                deque[deque.size()\
    \ - 2],\n                deque.back(),\n                eps\n            );\n\
    \            if (!point.has_value()) {\n                return HalfPlaneIntersectionResult{\n\
    \                    HalfPlaneIntersectionStatus::Degenerate,\n              \
    \      {},\n                };\n            }\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_back();\n        }\n        while\
    \ (deque.size() >= 2) {\n            auto point = detail::intersection(deque[0],\
    \ deque[1], eps);\n            if (!point.has_value()) {\n                return\
    \ HalfPlaneIntersectionResult{\n                    HalfPlaneIntersectionStatus::Degenerate,\n\
    \                    {},\n                };\n            }\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_front();\n        }\n        deque.push_back(half_plane);\n\
    \    }\n\n    while (deque.size() >= 3) {\n        auto point = detail::intersection(\n\
    \            deque[deque.size() - 2],\n            deque.back(),\n           \
    \ eps\n        );\n        if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (!detail::outside(deque.front(), *point,\
    \ eps)) break;\n        deque.pop_back();\n    }\n    while (deque.size() >= 3)\
    \ {\n        auto point = detail::intersection(deque[0], deque[1], eps);\n   \
    \     if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (!detail::outside(deque.back(), *point,\
    \ eps)) break;\n        deque.pop_front();\n    }\n    if (deque.size() < 3) {\n\
    \        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::vector<Point<long double>> polygon;\n\
    \    polygon.reserve(deque.size());\n    for (std::size_t index = 0; index < deque.size();\
    \ ++index) {\n        auto point = detail::intersection(\n            deque[index],\n\
    \            deque[(index + 1) % deque.size()],\n            eps\n        );\n\
    \        if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (\n            polygon.empty() ||\n   \
    \         distance(polygon.back(), *point) > eps\n        ) {\n            polygon.push_back(*point);\n\
    \        }\n    }\n    if (\n        polygon.size() >= 2 &&\n        distance(polygon.front(),\
    \ polygon.back()) <= eps\n    ) {\n        polygon.pop_back();\n    }\n    if\
    \ (polygon.size() < 3) {\n        return HalfPlaneIntersectionResult{\n      \
    \      HalfPlaneIntersectionStatus::Degenerate,\n            {},\n        };\n\
    \    }\n\n    long double signed_area2 = 0;\n    Point<long double> origin = polygon.front();\n\
    \    for (std::size_t index = 1; index + 1 < polygon.size(); ++index) {\n    \
    \    signed_area2 += cross(\n            polygon[index] - origin,\n          \
    \  polygon[index + 1] - origin\n        );\n    }\n    if (signed_area2 <= eps)\
    \ {\n        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    auto first = std::min_element(polygon.begin(),\
    \ polygon.end());\n    std::rotate(polygon.begin(), first, polygon.end());\n \
    \   return HalfPlaneIntersectionResult{\n        HalfPlaneIntersectionStatus::Bounded,\n\
    \        std::move(polygon),\n    };\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 20 \"geometry/convex_polygon.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nnamespace convex_polygon_detail {\n\ninline std::vector<Point<long\
    \ double>> clean_polygon(\n    std::vector<Point<long double>> polygon,\n    long\
    \ double eps\n) {\n    if (polygon.empty()) return polygon;\n\n    std::vector<Point<long\
    \ double>> deduplicated;\n    for (const Point<long double>& point : polygon)\
    \ {\n        if (\n            deduplicated.empty() ||\n            !polygon_detail::close(deduplicated.back(),\
    \ point, eps)\n        ) {\n            deduplicated.push_back(point);\n     \
    \   }\n    }\n    if (\n        deduplicated.size() >= 2 &&\n        polygon_detail::close(\n\
    \            deduplicated.front(),\n            deduplicated.back(),\n       \
    \     eps\n        )\n    ) {\n        deduplicated.pop_back();\n    }\n    if\
    \ (deduplicated.size() <= 2) return deduplicated;\n    std::vector<Point<long\
    \ double>> cleaned;\n    const std::size_t size = deduplicated.size();\n    cleaned.reserve(size);\n\
    \    for (std::size_t index = 0; index < size; ++index) {\n        const Point<long\
    \ double>& previous =\n            deduplicated[(index + size - 1) % size];\n\
    \        const Point<long double>& current = deduplicated[index];\n        const\
    \ Point<long double>& next =\n            deduplicated[(index + 1) % size];\n\
    \        if (\n            orientation(previous, current, next, eps) != 0 ||\n\
    \            dot(current - previous, next - current) < -eps\n        ) {\n   \
    \         cleaned.push_back(current);\n        }\n    }\n    return cleaned;\n\
    }\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> without_closing_point(std::vector<Point<T>>\
    \ polygon) {\n    if (\n        polygon.size() >= 2 &&\n        polygon.front()\
    \ == polygon.back()\n    ) {\n        polygon.pop_back();\n    }\n    return polygon;\n\
    }\n\n}  // namespace convex_polygon_detail\n\ntemplate <Coordinate T>\nbool is_convex_polygon(\n\
    \    const std::vector<Point<T>>& polygon,\n    bool strict = false,\n    long\
    \ double eps = 1e-12L\n) {\n    std::size_t size = polygon.size();\n    if (size\
    \ >= 2 && polygon.front() == polygon.back()) size--;\n    if (size < 3) return\
    \ false;\n\n    int direction = 0;\n    for (std::size_t index = 0; index < size;\
    \ ++index) {\n        const Point<T>& current = polygon[index];\n        const\
    \ Point<T>& next = polygon[(index + 1) % size];\n        const Point<T>& after\
    \ = polygon[(index + 2) % size];\n        if (current == next) return false;\n\
    \        const int turn = orientation(current, next, after, eps);\n        if\
    \ (turn == 0) {\n            if (strict) return false;\n            continue;\n\
    \        }\n        if (direction != 0 && direction != turn) return false;\n \
    \       direction = turn;\n    }\n    return !strict || direction != 0;\n}\n\n\
    template <Coordinate T>\nstd::vector<Point<T>> normalize_convex_polygon(\n   \
    \ std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    polygon\
    \ = convex_polygon_detail::without_closing_point(\n        std::move(polygon)\n\
    \    );\n    polygon.erase(\n        std::unique(polygon.begin(), polygon.end()),\n\
    \        polygon.end()\n    );\n    if (\n        polygon.size() >= 2 &&\n   \
    \     polygon.front() == polygon.back()\n    ) {\n        polygon.pop_back();\n\
    \    }\n    if (polygon.size() <= 1) return polygon;\n    if (\n        polygon.size()\
    \ >= 3 &&\n        sign<T>(polygon_area2(polygon), eps) < 0\n    ) {\n       \
    \ std::reverse(polygon.begin(), polygon.end());\n    }\n\n    auto start = std::min_element(\n\
    \        polygon.begin(),\n        polygon.end(),\n        [](const Point<T>&\
    \ first, const Point<T>& second) {\n            if (first.y != second.y) return\
    \ first.y < second.y;\n            return first.x < second.x;\n        }\n   \
    \ );\n    std::rotate(polygon.begin(), start, polygon.end());\n\n    if (polygon.size()\
    \ >= 3) {\n        std::vector<Point<T>> cleaned;\n        const std::size_t size\
    \ = polygon.size();\n        cleaned.reserve(size);\n        for (std::size_t\
    \ index = 0; index < size; ++index) {\n            const Point<T>& previous =\
    \ polygon[(index + size - 1) % size];\n            const Point<T>& current = polygon[index];\n\
    \            const Point<T>& next = polygon[(index + 1) % size];\n           \
    \ if (\n                orientation(previous, current, next, eps) != 0 ||\n  \
    \              sign<T>(dot(current - previous, next - current), eps) < 0\n   \
    \         ) {\n                cleaned.push_back(current);\n            }\n  \
    \      }\n        polygon = std::move(cleaned);\n    }\n    return polygon;\n\
    }\n\ntemplate <Coordinate T>\nPointInPolygon point_in_convex_polygon(\n    const\
    \ std::vector<Point<T>>& polygon,\n    const Point<T>& point,\n    long double\
    \ eps = 1e-12L\n) {\n    const std::size_t size = polygon.size();\n    if (size\
    \ == 0) return PointInPolygon::Outside;\n    if (size == 1) {\n        return\
    \ distance(polygon[0], point) <= eps\n            ? PointInPolygon::Boundary\n\
    \            : PointInPolygon::Outside;\n    }\n    if (size == 2) {\n       \
    \ return on_segment(Segment<T>{polygon[0], polygon[1]}, point, eps)\n        \
    \    ? PointInPolygon::Boundary\n            : PointInPolygon::Outside;\n    }\n\
    \n    const int order = orientation(\n        polygon[0],\n        polygon[1],\n\
    \        polygon[size - 1],\n        eps\n    );\n    if (order == 0) return point_in_polygon(polygon,\
    \ point, eps);\n    auto vertex = [&](std::size_t index) -> const Point<T>& {\n\
    \        if (order > 0 || index == 0) return polygon[index];\n        return polygon[size\
    \ - index];\n    };\n\n    const int first_side = orientation(vertex(0), vertex(1),\
    \ point, eps);\n    const int last_side =\n        orientation(vertex(0), vertex(size\
    \ - 1), point, eps);\n    if (first_side < 0 || last_side > 0) {\n        return\
    \ PointInPolygon::Outside;\n    }\n    if (first_side == 0) {\n        return\
    \ on_segment(Segment<T>{vertex(0), vertex(1)}, point, eps)\n            ? PointInPolygon::Boundary\n\
    \            : PointInPolygon::Outside;\n    }\n    if (last_side == 0) {\n  \
    \      return on_segment(\n            Segment<T>{vertex(0), vertex(size - 1)},\n\
    \            point,\n            eps\n        )\n            ? PointInPolygon::Boundary\n\
    \            : PointInPolygon::Outside;\n    }\n\n    std::size_t left = 1;\n\
    \    std::size_t right = size - 1;\n    while (right - left >= 2) {\n        const\
    \ std::size_t middle = (left + right) / 2;\n        if (orientation(vertex(0),\
    \ vertex(middle), point, eps) >= 0) {\n            left = middle;\n        } else\
    \ {\n            right = middle;\n        }\n    }\n    const int triangle_side\
    \ =\n        orientation(vertex(left), vertex(right), point, eps);\n    if (triangle_side\
    \ < 0) return PointInPolygon::Outside;\n    if (triangle_side == 0) return PointInPolygon::Boundary;\n\
    \    return PointInPolygon::Inside;\n}\n\ntemplate <Coordinate T>\nclass ConvexPolygon\
    \ {\n   public:\n    using Wide = wide_type<T>;\n\n   private:\n    std::vector<Point<T>>\
    \ points;\n    std::vector<Wide> area_prefix;\n    long double epsilon;\n\n  \
    \  template <class Compare>\n    int periodic_best(Compare better) const {\n \
    \       const int size = int(points.size());\n        int left = 0;\n        int\
    \ middle = size;\n        int right = 2 * size;\n        while (right - left >\
    \ 2) {\n            const int left_middle = (left + middle) / 2;\n           \
    \ const int right_middle = (middle + right + 1) / 2;\n            if (better(left_middle\
    \ % size, middle % size)) {\n                right = middle;\n               \
    \ middle = left_middle;\n            } else if (better(right_middle % size, middle\
    \ % size)) {\n                left = middle;\n                middle = right_middle;\n\
    \            } else {\n                left = left_middle;\n                right\
    \ = right_middle;\n            }\n        }\n        return middle % size;\n \
    \   }\n\n    int previous(int index) const {\n        return index == 0 ? int(points.size())\
    \ - 1 : index - 1;\n    }\n\n    int next(int index) const {\n        return index\
    \ + 1 == int(points.size()) ? 0 : index + 1;\n    }\n\n   public:\n    explicit\
    \ ConvexPolygon(\n        std::vector<Point<T>> polygon,\n        long double\
    \ eps = 1e-12L\n    )\n        : points(normalize_convex_polygon(std::move(polygon),\
    \ eps)),\n          epsilon(eps) {\n        assert(\n            points.size()\
    \ <=\n            static_cast<std::size_t>(\n                std::numeric_limits<int>::max()\
    \ / 2\n            )\n        );\n        assert(\n            points.size() <\
    \ 3 ||\n            is_convex_polygon(points, true, epsilon)\n        );\n   \
    \     area_prefix.resize(2 * points.size() + 1, Wide(0));\n        for (std::size_t\
    \ index = 0; index < 2 * points.size(); ++index) {\n            area_prefix[index\
    \ + 1] =\n                area_prefix[index] +\n                cross(\n     \
    \               points[index % points.size()],\n                    points[(index\
    \ + 1) % points.size()]\n                );\n        }\n    }\n\n    int size()\
    \ const noexcept {\n        return int(points.size());\n    }\n\n    bool empty()\
    \ const noexcept {\n        return points.empty();\n    }\n\n    const std::vector<Point<T>>&\
    \ vertices() const noexcept {\n        return points;\n    }\n\n    const Point<T>&\
    \ operator[](int index) const {\n        assert(0 <= index && index < size());\n\
    \        return points[index];\n    }\n\n    Wide area2() const {\n        if\
    \ (points.empty()) return Wide(0);\n        return area_prefix[points.size()];\n\
    \    }\n\n    Wide chain_area2(int first, int last) const {\n        assert(0\
    \ <= first && first < size());\n        assert(0 <= last && last < size());\n\
    \        int extended_last = last;\n        if (extended_last < first) extended_last\
    \ += size();\n        return\n            area_prefix[extended_last] - area_prefix[first]\
    \ +\n            cross(points[last], points[first]);\n    }\n\n    PointInPolygon\
    \ contains(const Point<T>& point) const {\n        return point_in_convex_polygon(points,\
    \ point, epsilon);\n    }\n\n    std::pair<Wide, int> min_dot(const Point<T>&\
    \ direction) const {\n        assert(!points.empty());\n        const int index\
    \ = periodic_best([&](int first, int second) {\n            return dot(points[first],\
    \ direction) <\n                   dot(points[second], direction);\n        });\n\
    \        return std::pair<Wide, int>(dot(points[index], direction), index);\n\
    \    }\n\n    std::pair<Wide, int> max_dot(const Point<T>& direction) const {\n\
    \        assert(!points.empty());\n        const int index = periodic_best([&](int\
    \ first, int second) {\n            return dot(points[first], direction) >\n \
    \                  dot(points[second], direction);\n        });\n        return\
    \ std::pair<Wide, int>(dot(points[index], direction), index);\n    }\n\n    std::pair<int,\
    \ int> tangent_vertices(const Point<T>& point) const {\n        assert(points.size()\
    \ >= 3);\n        assert(contains(point) == PointInPolygon::Outside);\n      \
    \  int first = periodic_best([&](int left, int right) {\n            return orientation(point,\
    \ points[left], points[right], epsilon) < 0;\n        });\n        int second\
    \ = periodic_best([&](int left, int right) {\n            return orientation(point,\
    \ points[left], points[right], epsilon) > 0;\n        });\n        if (\n    \
    \        orientation(\n                point,\n                points[first],\n\
    \                points[previous(first)],\n                epsilon\n         \
    \   ) == 0\n        ) {\n            first = previous(first);\n        }\n   \
    \     if (\n            orientation(\n                point,\n               \
    \ points[second],\n                points[next(second)],\n                epsilon\n\
    \            ) == 0\n        ) {\n            second = next(second);\n       \
    \ }\n        return std::pair<int, int>(first, second);\n    }\n};\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> centroid(\n    const ConvexPolygon<T>&\
    \ polygon,\n    long double eps = 1e-12L\n) {\n    return polygon_centroid(polygon.vertices(),\
    \ eps);\n}\n\nnamespace convex_polygon_detail {\n\ntemplate <Coordinate T>\nclass\
    \ MinkowskiDifferenceView {\n   private:\n    struct Cycle {\n        const ConvexPolygon<T>*\
    \ polygon;\n        int start;\n        bool negate;\n\n        int edge_count()\
    \ const {\n            return polygon->size() >= 2 ? polygon->size() : 0;\n  \
    \      }\n\n        Point<T> point(int index) const {\n            const int size\
    \ = polygon->size();\n            const Point<T>& result = (*polygon)[(start +\
    \ index) % size];\n            return negate ? -result : result;\n        }\n\n\
    \        Point<T> edge(int index) const {\n            return point((index + 1)\
    \ % polygon->size()) - point(index);\n        }\n    };\n\n    Cycle first;\n\
    \    Cycle second;\n\n    std::pair<int, int> prefixes(int rank) const {\n   \
    \     const int first_size = first.edge_count();\n        const int second_size\
    \ = second.edge_count();\n        if (first_size + second_size == 0) {\n     \
    \       return std::pair<int, int>(0, 0);\n        }\n\n        int low = std::max(0,\
    \ rank - second_size);\n        int high = std::min(rank, first_size);\n     \
    \   while (low <= high) {\n            const int first_prefix = (low + high) /\
    \ 2;\n            const int second_prefix = rank - first_prefix;\n           \
    \ if (\n                first_prefix > 0 &&\n                second_prefix < second_size\
    \ &&\n                entry_less(\n                    second.edge(second_prefix),\n\
    \                    1,\n                    first.edge(first_prefix - 1),\n \
    \                   0\n                )\n            ) {\n                high\
    \ = first_prefix - 1;\n                continue;\n            }\n            if\
    \ (\n                second_prefix > 0 &&\n                first_prefix < first_size\
    \ &&\n                entry_less(\n                    first.edge(first_prefix),\n\
    \                    0,\n                    second.edge(second_prefix - 1),\n\
    \                    1\n                )\n            ) {\n                low\
    \ = first_prefix + 1;\n                continue;\n            }\n            return\
    \ std::pair<int, int>(first_prefix, second_prefix);\n        }\n        assert(false);\n\
    \        return std::pair<int, int>(0, 0);\n    }\n\n    static int direction_half(const\
    \ Point<T>& direction) {\n        return\n            direction.y > 0 ||\n   \
    \         (direction.y == 0 && direction.x >= 0)\n            ? 0\n          \
    \  : 1;\n    }\n\n    static bool entry_less(\n        const Point<T>& left,\n\
    \        int left_cycle,\n        const Point<T>& right,\n        int right_cycle\n\
    \    ) {\n        if constexpr (std::floating_point<T>) {\n            long double\
    \ left_angle = std::atan2(\n                static_cast<long double>(left.y),\n\
    \                static_cast<long double>(left.x)\n            );\n          \
    \  long double right_angle = std::atan2(\n                static_cast<long double>(right.y),\n\
    \                static_cast<long double>(right.x)\n            );\n         \
    \   if (left_angle < 0) {\n                left_angle += 2 * std::numbers::pi_v<long\
    \ double>;\n            }\n            if (right_angle < 0) {\n              \
    \  right_angle += 2 * std::numbers::pi_v<long double>;\n            }\n      \
    \      if (left_angle != right_angle) return left_angle < right_angle;\n     \
    \       return left_cycle < right_cycle;\n        }\n        const int left_half\
    \ = direction_half(left);\n        const int right_half = direction_half(right);\n\
    \        if (left_half != right_half) return left_half < right_half;\n       \
    \ const auto turn = cross(left, right);\n        if (turn != 0) return turn >\
    \ 0;\n        return left_cycle < right_cycle;\n    }\n\n    static int negated_start(const\
    \ ConvexPolygon<T>& polygon) {\n        if (polygon.size() <= 1) return 0;\n \
    \       int result = polygon.max_dot(Point<T>(0, 1)).second;\n        const int\
    \ previous = result == 0 ? polygon.size() - 1 : result - 1;\n        const int\
    \ next = result + 1 == polygon.size() ? 0 : result + 1;\n        for (const int\
    \ candidate : {previous, next}) {\n            if (\n                polygon[candidate].y\
    \ == polygon[result].y &&\n                polygon[candidate].x > polygon[result].x\n\
    \            ) {\n                result = candidate;\n            }\n       \
    \ }\n        return result;\n    }\n\n   public:\n    MinkowskiDifferenceView(\n\
    \        const ConvexPolygon<T>& minuend,\n        const ConvexPolygon<T>& subtrahend\n\
    \    )\n        : first{&minuend, 0, false},\n          second{&subtrahend, negated_start(subtrahend),\
    \ true} {\n        assert(!minuend.empty());\n        assert(!subtrahend.empty());\n\
    \    }\n\n    int size() const {\n        const int edge_count =\n           \
    \ first.edge_count() + second.edge_count();\n        return edge_count == 0 ?\
    \ 1 : edge_count;\n    }\n\n    Point<T> operator[](int rank) const {\n      \
    \  assert(0 <= rank && rank < size());\n        const auto [first_prefix, second_prefix]\
    \ = prefixes(rank);\n        return\n            first.point(first_prefix % first.polygon->size())\
    \ +\n            second.point(second_prefix % second.polygon->size());\n    }\n\
    \n    std::pair<Point<T>, Point<T>> components(int rank) const {\n        assert(0\
    \ <= rank && rank < size());\n        const auto [first_prefix, second_prefix]\
    \ = prefixes(rank);\n        return std::pair<Point<T>, Point<T>>(\n         \
    \   first.point(first_prefix % first.polygon->size()),\n            -second.point(second_prefix\
    \ % second.polygon->size())\n        );\n    }\n};\n\nstruct OriginLocation {\n\
    \    PointInPolygon location;\n    int outside_edge;\n    std::array<int, 3> simplex;\n\
    \    int simplex_size;\n};\n\ntemplate <Coordinate T, class Polygon>\nOriginLocation\
    \ locate_origin(\n    const Polygon& polygon,\n    long double eps\n) {\n    const\
    \ int size = polygon.size();\n    assert(size >= 3);\n    const Point<T> origin;\n\
    \    const Point<T> base = polygon[0];\n    int first = 1;\n    if (\n       \
    \ size >= 4 &&\n        orientation(base, polygon[1], polygon[2], eps) == 0 &&\n\
    \        dot(polygon[1] - base, polygon[2] - polygon[1]) > 0\n    ) {\n      \
    \  first = 2;\n    }\n    const int last = size - 1;\n\n    const int first_side\
    \ = orientation(base, polygon[first], origin, eps);\n    const int last_side =\
    \ orientation(base, polygon[last], origin, eps);\n    if (first_side < 0) {\n\
    \        return OriginLocation{\n            PointInPolygon::Outside,\n      \
    \      0,\n            std::array<int, 3>{0, 0, 0},\n            0,\n        };\n\
    \    }\n    if (last_side > 0) {\n        return OriginLocation{\n           \
    \ PointInPolygon::Outside,\n            last,\n            std::array<int, 3>{0,\
    \ 0, 0},\n            0,\n        };\n    }\n    if (first_side == 0) {\n    \
    \    if (on_segment(Segment<T>{base, polygon[first]}, origin, eps)) {\n      \
    \      return OriginLocation{\n                PointInPolygon::Boundary,\n   \
    \             -1,\n                std::array<int, 3>{0, first, 0},\n        \
    \        2,\n            };\n        }\n        return OriginLocation{\n     \
    \       PointInPolygon::Outside,\n            first,\n            std::array<int,\
    \ 3>{0, 0, 0},\n            0,\n        };\n    }\n    if (last_side == 0) {\n\
    \        if (on_segment(Segment<T>{base, polygon[last]}, origin, eps)) {\n   \
    \         return OriginLocation{\n                PointInPolygon::Boundary,\n\
    \                -1,\n                std::array<int, 3>{0, last, 0},\n      \
    \          2,\n            };\n        }\n        return OriginLocation{\n   \
    \         PointInPolygon::Outside,\n            last - 1,\n            std::array<int,\
    \ 3>{0, 0, 0},\n            0,\n        };\n    }\n\n    int left = first;\n \
    \   int right = last;\n    while (right - left >= 2) {\n        const int middle\
    \ = (left + right) / 2;\n        if (orientation(base, polygon[middle], origin,\
    \ eps) >= 0) {\n            left = middle;\n        } else {\n            right\
    \ = middle;\n        }\n    }\n    const int side = orientation(polygon[left],\
    \ polygon[right], origin, eps);\n    if (side < 0) {\n        return OriginLocation{\n\
    \            PointInPolygon::Outside,\n            left,\n            std::array<int,\
    \ 3>{0, 0, 0},\n            0,\n        };\n    }\n    if (side == 0) {\n    \
    \    const bool boundary = on_segment(\n            Segment<T>{polygon[left],\
    \ polygon[right]},\n            origin,\n            eps\n        );\n       \
    \ return OriginLocation{\n            boundary ? PointInPolygon::Boundary : PointInPolygon::Outside,\n\
    \            boundary ? -1 : left,\n            std::array<int, 3>{left, right,\
    \ 0},\n            boundary ? 2 : 0,\n        };\n    }\n    return OriginLocation{\n\
    \        PointInPolygon::Inside,\n        -1,\n        std::array<int, 3>{0, left,\
    \ right},\n        3,\n    };\n}\n\ntemplate <class Compare>\nint periodic_best(int\
    \ size, Compare better) {\n    int left = 0;\n    int middle = size;\n    int\
    \ right = 2 * size;\n    while (right - left > 2) {\n        const int left_middle\
    \ = (left + middle) / 2;\n        const int right_middle = (middle + right + 1)\
    \ / 2;\n        if (better(left_middle % size, middle % size)) {\n           \
    \ right = middle;\n            middle = left_middle;\n        } else if (better(right_middle\
    \ % size, middle % size)) {\n            left = middle;\n            middle =\
    \ right_middle;\n        } else {\n            left = left_middle;\n         \
    \   right = right_middle;\n        }\n    }\n    return middle % size;\n}\n\n\
    template <Coordinate T, class Polygon>\nstd::pair<int, int> tangent_vertices_from_origin(\n\
    \    const Polygon& polygon,\n    long double eps\n) {\n    const int size = polygon.size();\n\
    \    const Point<T> origin;\n    int first = periodic_best(size, [&](int left,\
    \ int right) {\n        return orientation(origin, polygon[left], polygon[right],\
    \ eps) < 0;\n    });\n    int second = periodic_best(size, [&](int left, int right)\
    \ {\n        return orientation(origin, polygon[left], polygon[right], eps) >\
    \ 0;\n    });\n    const int previous = first == 0 ? size - 1 : first - 1;\n \
    \   if (orientation(origin, polygon[first], polygon[previous], eps) == 0) {\n\
    \        first = previous;\n    }\n    const int next = second + 1 == size ? 0\
    \ : second + 1;\n    if (orientation(origin, polygon[second], polygon[next], eps)\
    \ == 0) {\n        second = next;\n    }\n    return std::pair<int, int>(first,\
    \ second);\n}\n\nstruct ClosestBoundaryFeature {\n    int first;\n    int second;\n\
    \    long double ratio;\n    long double distance;\n};\n\ntemplate <Coordinate\
    \ T, class Polygon>\nClosestBoundaryFeature closest_boundary_feature(\n    const\
    \ Polygon& polygon,\n    const OriginLocation& location,\n    long double eps\n\
    ) {\n    const int size = polygon.size();\n    assert(size >= 3);\n    assert(location.location\
    \ == PointInPolygon::Outside);\n    const Point<T> origin;\n\n    const auto tangents\
    \ = tangent_vertices_from_origin<T>(polygon, eps);\n    auto visible = [&](int\
    \ index) {\n        return orientation(\n            polygon[index],\n       \
    \     polygon[(index + 1) % size],\n            origin,\n            eps\n   \
    \     ) < 0;\n    };\n    auto forward_edges = [&](int start, int finish) {\n\
    \        return finish >= start ? finish - start : finish + size - start;\n  \
    \  };\n\n    int witness = location.outside_edge;\n    if (!visible(witness))\
    \ {\n        const int previous = witness == 0 ? size - 1 : witness - 1;\n   \
    \     const int next = witness + 1 == size ? 0 : witness + 1;\n        if (visible(previous))\
    \ {\n            witness = previous;\n        } else if (visible(next)) {\n  \
    \          witness = next;\n        }\n    }\n\n    int start = tangents.first;\n\
    \    int finish = tangents.second;\n    if (forward_edges(start, witness) >= forward_edges(start,\
    \ finish)) {\n        std::swap(start, finish);\n    }\n    int edge_count = forward_edges(start,\
    \ finish);\n    if (edge_count == 0) {\n        start = location.outside_edge;\n\
    \        finish = (start + 1) % size;\n        edge_count = 1;\n    }\n\n    auto\
    \ vertex = [&](int offset) {\n        return polygon[(start + offset) % size];\n\
    \    };\n    int left = 0;\n    int right = edge_count;\n    while (left < right)\
    \ {\n        const int middle = (left + right) / 2;\n        if (norm2(vertex(middle))\
    \ <= norm2(vertex(middle + 1))) {\n            right = middle;\n        } else\
    \ {\n            left = middle + 1;\n        }\n    }\n\n    ClosestBoundaryFeature\
    \ result{\n        (start + left) % size,\n        (start + left) % size,\n  \
    \      0,\n        norm(vertex(left)),\n    };\n    auto consider_edge = [&](int\
    \ first_offset, int second_offset) {\n        const Point<long double> first_point(vertex(first_offset));\n\
    \        const Point<long double> second_point(vertex(second_offset));\n     \
    \   const Point<long double> direction = second_point - first_point;\n       \
    \ long double ratio =\n            -dot(first_point, direction) / dot(direction,\
    \ direction);\n        ratio = std::clamp(ratio, 0.0L, 1.0L);\n        const long\
    \ double candidate_distance =\n            norm(first_point + direction * ratio);\n\
    \        if (candidate_distance < result.distance) {\n            result = ClosestBoundaryFeature{\n\
    \                (start + first_offset) % size,\n                (start + second_offset)\
    \ % size,\n                ratio,\n                candidate_distance,\n     \
    \       };\n        }\n    };\n    if (left > 0) {\n        consider_edge(left\
    \ - 1, left);\n    }\n    if (left < edge_count) {\n        consider_edge(left,\
    \ left + 1);\n    }\n    return result;\n}\n\ntemplate <Coordinate T, class Polygon>\n\
    long double distance_from_origin(\n    const Polygon& polygon,\n    long double\
    \ eps\n) {\n    const OriginLocation location = locate_origin<T>(polygon, eps);\n\
    \    if (location.location != PointInPolygon::Outside) return 0;\n    return closest_boundary_feature<T>(polygon,\
    \ location, eps).distance;\n}\n\ninline Point<long double> interpolate(\n    const\
    \ Point<long double>& first,\n    const Point<long double>& second,\n    long\
    \ double ratio\n) {\n    return first + (second - first) * ratio;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::pair<Point<long double>, Point<long double>>\nclosest_points_from_difference(\n\
    \    const MinkowskiDifferenceView<T>& difference,\n    long double eps\n) {\n\
    \    const OriginLocation location = locate_origin<T>(difference, eps);\n    if\
    \ (location.location == PointInPolygon::Outside) {\n        const ClosestBoundaryFeature\
    \ feature =\n            closest_boundary_feature<T>(difference, location, eps);\n\
    \        const auto first_components = difference.components(feature.first);\n\
    \        const auto second_components = difference.components(feature.second);\n\
    \        return std::pair<Point<long double>, Point<long double>>(\n         \
    \   interpolate(\n                Point<long double>(first_components.first),\n\
    \                Point<long double>(second_components.first),\n              \
    \  feature.ratio\n            ),\n            interpolate(\n                Point<long\
    \ double>(first_components.second),\n                Point<long double>(second_components.second),\n\
    \                feature.ratio\n            )\n        );\n    }\n\n    assert(location.simplex_size\
    \ == 2 || location.simplex_size == 3);\n    std::array<long double, 3> weight{0,\
    \ 0, 0};\n    if (location.simplex_size == 2) {\n        const Point<long double>\
    \ first(difference[location.simplex[0]]);\n        const Point<long double> second(difference[location.simplex[1]]);\n\
    \        const Point<long double> direction = second - first;\n        weight[1]\
    \ = -dot(first, direction) / dot(direction, direction);\n        weight[1] = std::clamp(weight[1],\
    \ 0.0L, 1.0L);\n        weight[0] = 1 - weight[1];\n    } else {\n        const\
    \ Point<long double> first(difference[location.simplex[0]]);\n        const Point<long\
    \ double> second(difference[location.simplex[1]]);\n        const Point<long double>\
    \ third(difference[location.simplex[2]]);\n        const long double denominator\
    \ = cross(\n            second - first,\n            third - first\n        );\n\
    \        weight[0] = cross(second, third) / denominator;\n        weight[1] =\
    \ cross(third, first) / denominator;\n        weight[2] = cross(first, second)\
    \ / denominator;\n    }\n\n    Point<long double> first_result;\n    Point<long\
    \ double> second_result;\n    for (int index = 0; index < location.simplex_size;\
    \ ++index) {\n        const auto components = difference.components(\n       \
    \     location.simplex[index]\n        );\n        first_result += Point<long\
    \ double>(components.first) * weight[index];\n        second_result +=\n     \
    \       Point<long double>(components.second) * weight[index];\n    }\n    return\
    \ std::pair<Point<long double>, Point<long double>>(\n        first_result,\n\
    \        second_result\n    );\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ closest_point_on_segment(\n    const Segment<T>& segment,\n    const Point<T>&\
    \ point\n) {\n    const Point<long double> first(segment.a);\n    const Point<long\
    \ double> direction =\n        Point<long double>(segment.b) - first;\n    const\
    \ long double length2 = dot(direction, direction);\n    if (length2 == 0) return\
    \ first;\n    const long double ratio = std::clamp(\n        dot(Point<long double>(point)\
    \ - first, direction) / length2,\n        0.0L,\n        1.0L\n    );\n    return\
    \ first + direction * ratio;\n}\n\ntemplate <Coordinate T>\nstd::pair<Point<long\
    \ double>, Point<long double>>\nclosest_points_between_segments(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps\n) {\n    if (intersects(first,\
    \ second, eps)) {\n        for (const Point<T>& point : {first.a, first.b}) {\n\
    \            if (on_segment(second, point, eps)) {\n                const Point<long\
    \ double> common(point);\n                return std::pair<Point<long double>,\
    \ Point<long double>>(\n                    common,\n                    common\n\
    \                );\n            }\n        }\n        for (const Point<T>& point\
    \ : {second.a, second.b}) {\n            if (on_segment(first, point, eps)) {\n\
    \                const Point<long double> common(point);\n                return\
    \ std::pair<Point<long double>, Point<long double>>(\n                    common,\n\
    \                    common\n                );\n            }\n        }\n  \
    \      const auto common = line_intersection(\n            Line<T>{first.a, first.b},\n\
    \            Line<T>{second.a, second.b},\n            eps\n        );\n     \
    \   assert(common.has_value());\n        return std::pair<Point<long double>,\
    \ Point<long double>>(\n            *common,\n            *common\n        );\n\
    \    }\n\n    std::pair<Point<long double>, Point<long double>> result(\n    \
    \    Point<long double>(first.a),\n        closest_point_on_segment(second, first.a)\n\
    \    );\n    long double result_distance = distance(result.first, result.second);\n\
    \    auto consider = [&](const Point<long double>& first_point,\n            \
    \            const Point<long double>& second_point) {\n        const long double\
    \ candidate_distance =\n            distance(first_point, second_point);\n   \
    \     if (candidate_distance < result_distance) {\n            result = std::pair<Point<long\
    \ double>, Point<long double>>(\n                first_point,\n              \
    \  second_point\n            );\n            result_distance = candidate_distance;\n\
    \        }\n    };\n    consider(\n        Point<long double>(first.b),\n    \
    \    closest_point_on_segment(second, first.b)\n    );\n    consider(\n      \
    \  closest_point_on_segment(first, second.a),\n        Point<long double>(second.a)\n\
    \    );\n    consider(\n        closest_point_on_segment(first, second.b),\n \
    \       Point<long double>(second.b)\n    );\n    return result;\n}\n\n}  // namespace\
    \ convex_polygon_detail\n\ntemplate <Coordinate T>\nstd::vector<std::array<Point<T>,\
    \ 3>> triangulate_convex_polygon(\n    std::vector<Point<T>> polygon,\n    long\
    \ double eps = 1e-12L\n) {\n    polygon = normalize_convex_polygon(std::move(polygon),\
    \ eps);\n    if (polygon.size() < 3) return {};\n\n    std::vector<std::array<Point<T>,\
    \ 3>> result;\n    result.reserve(polygon.size() - 2);\n    for (std::size_t index\
    \ = 1; index + 1 < polygon.size(); ++index) {\n        std::array<Point<T>, 3>\
    \ triangle;\n        triangle[0] = polygon[0];\n        triangle[1] = polygon[index];\n\
    \        triangle[2] = polygon[index + 1];\n        result.push_back(std::move(triangle));\n\
    \    }\n    return result;\n}\n\ntemplate <Coordinate T>\nwide_type<T> convex_diameter2(\n\
    \    std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    polygon\
    \ = normalize_convex_polygon(std::move(polygon), eps);\n    const std::size_t\
    \ size = polygon.size();\n    if (size <= 1) return 0;\n    if (size == 2) return\
    \ distance2(polygon[1], polygon[0]);\n\n    wide_type<T> result = 0;\n    std::size_t\
    \ opposite = 1;\n    for (std::size_t index = 0; index < size; ++index) {\n  \
    \      const std::size_t next = (index + 1) % size;\n        while (true) {\n\
    \            const std::size_t candidate = (opposite + 1) % size;\n          \
    \  const auto current_area =\n                cross(polygon[index], polygon[next],\
    \ polygon[opposite]);\n            const auto candidate_area =\n             \
    \   cross(polygon[index], polygon[next], polygon[candidate]);\n            if\
    \ (candidate_area <= current_area) break;\n            opposite = candidate;\n\
    \        }\n        result = std::max(\n            result,\n            distance2(polygon[index],\
    \ polygon[opposite])\n        );\n        result = std::max(\n            result,\n\
    \            distance2(polygon[next], polygon[opposite])\n        );\n    }\n\
    \    return result;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long double>>\
    \ convex_cut(\n    const std::vector<Point<T>>& polygon,\n    const Line<T>& boundary,\n\
    \    long double eps = 1e-12L\n) {\n    assert(boundary.a != boundary.b);\n  \
    \  std::vector<Point<long double>> input;\n    input.reserve(polygon.size());\n\
    \    for (const Point<T>& point : polygon) input.emplace_back(point);\n    if\
    \ (input.empty()) return input;\n\n    const Point<long double> line_start(boundary.a);\n\
    \    const Point<long double> line_end(boundary.b);\n    const Line<long double>\
    \ line{line_start, line_end};\n    std::vector<Point<long double>> result;\n \
    \   Point<long double> previous = input.back();\n    int previous_side = orientation(line_start,\
    \ line_end, previous, eps);\n    for (const Point<long double>& current : input)\
    \ {\n        const int current_side =\n            orientation(line_start, line_end,\
    \ current, eps);\n        const bool previous_inside = previous_side >= 0;\n \
    \       const bool current_inside = current_side >= 0;\n        if (previous_inside\
    \ != current_inside) {\n            const Line<long double> crossing{previous,\
    \ current};\n            const std::optional<Point<long double>> intersection\
    \ =\n                line_intersection(line, crossing, eps);\n            if (intersection.has_value())\
    \ result.push_back(*intersection);\n        }\n        if (current_inside) result.push_back(current);\n\
    \        previous = current;\n        previous_side = current_side;\n    }\n \
    \   return convex_polygon_detail::clean_polygon(std::move(result), eps);\n}\n\n\
    template <Coordinate T>\nstd::vector<Point<T>> minkowski_sum(\n    std::vector<Point<T>>\
    \ first,\n    std::vector<Point<T>> second,\n    long double eps = 1e-12L\n) {\n\
    \    assert(!first.empty());\n    assert(!second.empty());\n    first = normalize_convex_polygon(std::move(first),\
    \ eps);\n    second = normalize_convex_polygon(std::move(second), eps);\n\n  \
    \  if (first.size() == 1 || second.size() == 1) {\n        if (second.size() ==\
    \ 1) std::swap(first, second);\n        for (Point<T>& point : second) {\n   \
    \         point += first[0];\n        }\n        return normalize_convex_polygon(std::move(second),\
    \ eps);\n    }\n\n    std::vector<Point<T>> first_edges;\n    std::vector<Point<T>>\
    \ second_edges;\n    first_edges.reserve(first.size());\n    second_edges.reserve(second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first_edges.push_back(\n\
    \            first[(index + 1) % first.size()] - first[index]\n        );\n  \
    \  }\n    for (std::size_t index = 0; index < second.size(); ++index) {\n    \
    \    second_edges.push_back(\n            second[(index + 1) % second.size()]\
    \ - second[index]\n        );\n    }\n\n    Point<T> current = first.front() +\
    \ second.front();\n    std::vector<Point<T>> result;\n    result.reserve(first.size()\
    \ + second.size());\n    result.push_back(current);\n    std::size_t first_index\
    \ = 0;\n    std::size_t second_index = 0;\n    while (\n        first_index <\
    \ first_edges.size() ||\n        second_index < second_edges.size()\n    ) {\n\
    \        Point<T> step;\n        if (first_index == first_edges.size()) {\n  \
    \          step = second_edges[second_index++];\n        } else if (second_index\
    \ == second_edges.size()) {\n            step = first_edges[first_index++];\n\
    \        } else {\n            const auto turn = cross(\n                first_edges[first_index],\n\
    \                second_edges[second_index]\n            );\n            if (turn\
    \ > 0) {\n                step = first_edges[first_index++];\n            } else\
    \ if (turn < 0) {\n                step = second_edges[second_index++];\n    \
    \        } else {\n                step =\n                    first_edges[first_index++]\
    \ +\n                    second_edges[second_index++];\n            }\n      \
    \  }\n        current += step;\n        if (\n            first_index < first_edges.size()\
    \ ||\n            second_index < second_edges.size()\n        ) {\n          \
    \  result.push_back(current);\n        }\n    }\n    return normalize_convex_polygon(std::move(result),\
    \ eps);\n}\n\ntemplate <Coordinate T>\nbool convex_polygons_intersect(\n    const\
    \ ConvexPolygon<T>& first,\n    const ConvexPolygon<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    if (first.size() <= 2 && second.size() <= 2) {\n        if (first.size()\
    \ == 1 && second.size() == 1) {\n            return distance(first[0], second[0])\
    \ <= eps;\n        }\n        if (first.size() == 1) {\n            return on_segment(\n\
    \                Segment<T>{second[0], second[1]},\n                first[0],\n\
    \                eps\n            );\n        }\n        if (second.size() ==\
    \ 1) {\n            return on_segment(\n                Segment<T>{first[0], first[1]},\n\
    \                second[0],\n                eps\n            );\n        }\n\
    \        return intersects(\n            Segment<T>{first[0], first[1]},\n   \
    \         Segment<T>{second[0], second[1]},\n            eps\n        );\n   \
    \ }\n\n    const convex_polygon_detail::MinkowskiDifferenceView<T> difference(\n\
    \        first,\n        second\n    );\n    return\n        convex_polygon_detail::locate_origin<T>(difference,\
    \ eps).location !=\n        PointInPolygon::Outside;\n}\n\ntemplate <Coordinate\
    \ T>\nbool convex_polygons_intersect(\n    const std::vector<Point<T>>& first,\n\
    \    const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n) {\n\
    \    assert(!first.empty());\n    assert(!second.empty());\n    std::vector<Point<T>>\
    \ negated;\n    negated.reserve(second.size());\n    for (const Point<T>& point\
    \ : second) negated.push_back(-point);\n    const std::vector<Point<T>> difference\
    \ =\n        minkowski_sum(first, std::move(negated), eps);\n    return\n    \
    \    point_in_convex_polygon(difference, Point<T>(), eps) !=\n        PointInPolygon::Outside;\n\
    }\n\ntemplate <Coordinate T>\nstd::pair<Point<long double>, Point<long double>>\n\
    convex_polygons_closest_points(\n    const ConvexPolygon<T>& first,\n    const\
    \ ConvexPolygon<T>& second,\n    long double eps = 1e-12L\n) {\n    assert(!first.empty());\n\
    \    assert(!second.empty());\n    if (first.size() <= 2 && second.size() <= 2)\
    \ {\n        return convex_polygon_detail::closest_points_between_segments(\n\
    \            Segment<T>{first[0], first[first.size() - 1]},\n            Segment<T>{second[0],\
    \ second[second.size() - 1]},\n            eps\n        );\n    }\n    const convex_polygon_detail::MinkowskiDifferenceView<T>\
    \ difference(\n        first,\n        second\n    );\n    return convex_polygon_detail::closest_points_from_difference(\n\
    \        difference,\n        eps\n    );\n}\n\ntemplate <Coordinate T>\nstd::pair<Point<long\
    \ double>, Point<long double>>\nconvex_polygons_closest_points(\n    const std::vector<Point<T>>&\
    \ first,\n    const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(!first.empty());\n    assert(!second.empty());\n    const ConvexPolygon<T>\
    \ first_query(first, eps);\n    const ConvexPolygon<T> second_query(second, eps);\n\
    \    return convex_polygons_closest_points(first_query, second_query, eps);\n\
    }\n\ntemplate <Coordinate T>\nlong double convex_polygons_distance(\n    const\
    \ ConvexPolygon<T>& first,\n    const ConvexPolygon<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    if (first.size() <= 2 && second.size() <= 2) {\n        if (convex_polygons_intersect(first,\
    \ second, eps)) return 0;\n        if (first.size() == 1 && second.size() == 1)\
    \ {\n            return distance(first[0], second[0]);\n        }\n        if\
    \ (first.size() == 1) {\n            return distance(\n                Segment<T>{second[0],\
    \ second[1]},\n                first[0]\n            );\n        }\n        if\
    \ (second.size() == 1) {\n            return distance(\n                Segment<T>{first[0],\
    \ first[1]},\n                second[0]\n            );\n        }\n        return\
    \ distance(\n            Segment<T>{first[0], first[1]},\n            Segment<T>{second[0],\
    \ second[1]}\n        );\n    }\n\n    const convex_polygon_detail::MinkowskiDifferenceView<T>\
    \ difference(\n        first,\n        second\n    );\n    return convex_polygon_detail::distance_from_origin<T>(difference,\
    \ eps);\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long double>> convex_polygon_intersection(\n\
    \    const std::vector<Point<T>>& first,\n    const std::vector<Point<T>>& second,\n\
    \    long double eps = 1e-12L\n) {\n    using HalfPlane = half_plane_intersection_detail::HalfPlane;\n\
    \    namespace detail = half_plane_intersection_detail;\n\n    const std::vector<Point<T>>\
    \ normalized_first =\n        normalize_convex_polygon(first, eps);\n    const\
    \ std::vector<Point<T>> normalized_second =\n        normalize_convex_polygon(second,\
    \ eps);\n    assert(normalized_first.size() >= 3);\n    assert(normalized_second.size()\
    \ >= 3);\n    assert(is_convex_polygon(normalized_first, true, eps));\n    assert(is_convex_polygon(normalized_second,\
    \ true, eps));\n    if (!convex_polygons_intersect(\n            normalized_first,\n\
    \            normalized_second,\n            eps\n        )) {\n        return\
    \ {};\n    }\n\n    auto boundaries = [](const std::vector<Point<T>>& polygon)\
    \ {\n        std::vector<HalfPlane> result;\n        result.reserve(polygon.size());\n\
    \        for (std::size_t index = 0; index < polygon.size(); ++index) {\n    \
    \        const Point<long double> point(polygon[index]);\n            Point<long\
    \ double> direction =\n                Point<long double>(polygon[(index + 1)\
    \ % polygon.size()]) -\n                point;\n            direction = direction\
    \ / norm(direction);\n            result.push_back(HalfPlane{point, direction});\n\
    \        }\n        return result;\n    };\n    const std::vector<HalfPlane> first_boundaries\
    \ =\n        boundaries(normalized_first);\n    const std::vector<HalfPlane> second_boundaries\
    \ =\n        boundaries(normalized_second);\n\n    std::vector<HalfPlane> merged;\n\
    \    merged.reserve(first_boundaries.size() + second_boundaries.size());\n   \
    \ std::size_t first_index = 0;\n    std::size_t second_index = 0;\n    while (\n\
    \        first_index < first_boundaries.size() ||\n        second_index < second_boundaries.size()\n\
    \    ) {\n        const bool take_first =\n            second_index == second_boundaries.size()\
    \ ||\n            (\n                first_index < first_boundaries.size() &&\n\
    \                detail::direction_less(\n                    first_boundaries[first_index],\n\
    \                    second_boundaries[second_index]\n                )\n    \
    \        );\n        if (take_first) {\n            detail::merge_same_direction(\n\
    \                merged,\n                first_boundaries[first_index++],\n \
    \               eps\n            );\n        } else {\n            detail::merge_same_direction(\n\
    \                merged,\n                second_boundaries[second_index++],\n\
    \                eps\n            );\n        }\n    }\n    detail::merge_cyclic_ends(merged,\
    \ eps);\n\n    std::deque<HalfPlane> active;\n    for (const HalfPlane& half_plane\
    \ : merged) {\n        while (active.size() >= 2) {\n            const std::optional<Point<long\
    \ double>> point =\n                detail::intersection(\n                  \
    \  active[active.size() - 2],\n                    active.back(),\n          \
    \          eps\n                );\n            if (\n                !point.has_value()\
    \ ||\n                !detail::outside(half_plane, *point, eps)\n            )\
    \ {\n                break;\n            }\n            active.pop_back();\n \
    \       }\n        while (active.size() >= 2) {\n            const std::optional<Point<long\
    \ double>> point =\n                detail::intersection(active[0], active[1],\
    \ eps);\n            if (\n                !point.has_value() ||\n           \
    \     !detail::outside(half_plane, *point, eps)\n            ) {\n           \
    \     break;\n            }\n            active.pop_front();\n        }\n    \
    \    active.push_back(half_plane);\n    }\n    while (active.size() >= 3) {\n\
    \        const std::optional<Point<long double>> point =\n            detail::intersection(\n\
    \                active[active.size() - 2],\n                active.back(),\n\
    \                eps\n            );\n        if (\n            !point.has_value()\
    \ ||\n            !detail::outside(active.front(), *point, eps)\n        ) {\n\
    \            break;\n        }\n        active.pop_back();\n    }\n    while (active.size()\
    \ >= 3) {\n        const std::optional<Point<long double>> point =\n         \
    \   detail::intersection(active[0], active[1], eps);\n        if (\n         \
    \   !point.has_value() ||\n            !detail::outside(active.back(), *point,\
    \ eps)\n        ) {\n            break;\n        }\n        active.pop_front();\n\
    \    }\n\n    std::vector<Point<long double>> result;\n    result.reserve(active.size());\n\
    \    for (std::size_t index = 0; index < active.size(); ++index) {\n        const\
    \ std::optional<Point<long double>> point =\n            detail::intersection(\n\
    \                active[index],\n                active[(index + 1) % active.size()],\n\
    \                eps\n            );\n        if (point.has_value()) result.push_back(*point);\n\
    \    }\n    return convex_polygon_detail::clean_polygon(std::move(result), eps);\n\
    }\n\ntemplate <Coordinate T>\nlong double convex_polygons_distance(\n    const\
    \ std::vector<Point<T>>& first,\n    const std::vector<Point<T>>& second,\n  \
    \  long double eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    std::vector<Point<T>> negated;\n    negated.reserve(second.size());\n   \
    \ for (const Point<T>& point : second) negated.push_back(-point);\n    const std::vector<Point<T>>\
    \ difference =\n        minkowski_sum(first, std::move(negated), eps);\n    const\
    \ Point<T> origin;\n    if (\n        point_in_convex_polygon(difference, origin,\
    \ eps) !=\n        PointInPolygon::Outside\n    ) {\n        return 0;\n    }\n\
    \    if (difference.size() == 1) return distance(difference[0], origin);\n\n \
    \   long double result = std::numeric_limits<long double>::infinity();\n    for\
    \ (std::size_t index = 0; index < difference.size(); ++index) {\n        if (difference.size()\
    \ == 2 && index == 1) break;\n        result = std::min(\n            result,\n\
    \            distance(\n                Segment<T>{\n                    difference[index],\n\
    \                    difference[(index + 1) % difference.size()]\n           \
    \     },\n                origin\n            )\n        );\n    }\n    return\
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 5 \"\
    verify/geometry/convex_decomposition.test.cpp\"\n\n#line 11 \"verify/geometry/convex_decomposition.test.cpp\"\
    \n#include <numeric>\n#line 13 \"verify/geometry/convex_decomposition.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#line 15 \"utilities/fast_io.hpp\"\n#include\
    \ <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 15 \"verify/geometry/convex_decomposition.test.cpp\"\
    \n\nnamespace {\n\nusing namespace m1une::geometry;\nusing P = Point<long long>;\n\
    \nstd::vector<P> points_from_indices(\n    const std::vector<P>& polygon,\n  \
    \  const std::vector<int>& indices\n) {\n    std::vector<P> result;\n    result.reserve(indices.size());\n\
    \    for (const int index : indices) result.push_back(polygon[index]);\n    return\
    \ result;\n}\n\nstd::vector<int> canonical_cycle(std::vector<int> cycle) {\n \
    \   const auto start = std::min_element(cycle.begin(), cycle.end());\n    std::rotate(cycle.begin(),\
    \ start, cycle.end());\n    return cycle;\n}\n\nint brute_minimum_decomposition(\n\
    \    const std::vector<P>& polygon,\n    std::vector<int> region,\n    std::map<std::vector<int>,\
    \ int>& memo\n) {\n    region = canonical_cycle(std::move(region));\n    const\
    \ auto found = memo.find(region);\n    if (found != memo.end()) return found->second;\n\
    \n    const std::vector<P> points = points_from_indices(polygon, region);\n  \
    \  if (is_convex_polygon(points)) return memo[region] = 1;\n\n    const int size\
    \ = static_cast<int>(region.size());\n    int answer = std::numeric_limits<int>::max()\
    \ / 4;\n    for (int first = 0; first < size; ++first) {\n        for (int last\
    \ = first + 2; last < size; ++last) {\n            if (first == 0 && last + 1\
    \ == size) continue;\n\n            std::vector<int> left;\n            for (int\
    \ index = first; index <= last; ++index) {\n                left.push_back(region[index]);\n\
    \            }\n            std::vector<int> right;\n            for (int index\
    \ = last; index < size; ++index) {\n                right.push_back(region[index]);\n\
    \            }\n            for (int index = 0; index <= first; ++index) {\n \
    \               right.push_back(region[index]);\n            }\n\n           \
    \ const std::vector<P> left_points =\n                points_from_indices(polygon,\
    \ left);\n            const std::vector<P> right_points =\n                points_from_indices(polygon,\
    \ right);\n            if (\n                polygon_area2(left_points) <= 0 ||\n\
    \                polygon_area2(right_points) <= 0 ||\n                !is_simple_polygon(left_points)\
    \ ||\n                !is_simple_polygon(right_points)\n            ) {\n    \
    \            continue;\n            }\n            answer = std::min(\n      \
    \          answer,\n                brute_minimum_decomposition(polygon, left,\
    \ memo) +\n                    brute_minimum_decomposition(polygon, right, memo)\n\
    \            );\n        }\n    }\n    assert(answer < std::numeric_limits<int>::max()\
    \ / 4);\n    return memo[region] = answer;\n}\n\nint brute_minimum_decomposition(const\
    \ std::vector<P>& polygon) {\n    std::vector<int> indices(polygon.size());\n\
    \    std::iota(indices.begin(), indices.end(), 0);\n    std::map<std::vector<int>,\
    \ int> memo;\n    return brute_minimum_decomposition(polygon, indices, memo);\n\
    }\n\nvoid assert_valid_decomposition(\n    const std::vector<P>& polygon,\n  \
    \  const std::vector<std::vector<P>>& decomposition\n) {\n    assert(!decomposition.empty());\n\
    \    long double area_sum = 0;\n    std::vector<Point<long double>> floating_polygon;\n\
    \    floating_polygon.reserve(polygon.size());\n    for (const P& point : polygon)\
    \ floating_polygon.emplace_back(point);\n\n    for (const auto& part : decomposition)\
    \ {\n        assert(part.size() >= 3);\n        assert(polygon_area2(part) > 0);\n\
    \        assert(is_convex_polygon(part));\n        area_sum += polygon_area(part);\n\
    \        for (const P& point : part) {\n            assert(\n                point_in_polygon(polygon,\
    \ point) != PointInPolygon::Outside\n            );\n        }\n        for (std::size_t\
    \ index = 0; index < part.size(); ++index) {\n            const P& first = part[index];\n\
    \            const P& second = part[(index + 1) % part.size()];\n            const\
    \ Point<long double> midpoint(\n                (\n                    static_cast<long\
    \ double>(first.x) +\n                    static_cast<long double>(second.x)\n\
    \                ) / 2,\n                (\n                    static_cast<long\
    \ double>(first.y) +\n                    static_cast<long double>(second.y)\n\
    \                ) / 2\n            );\n            assert(\n                point_in_polygon(floating_polygon,\
    \ midpoint) !=\n                PointInPolygon::Outside\n            );\n    \
    \    }\n    }\n    assert(std::fabs(area_sum - polygon_area(polygon)) <= 1e-9L);\n\
    }\n\nvoid test_predicate_width_selection() {\n    using PredicateWidth =\n   \
    \     convex_decomposition_detail::ExactPredicateWidth;\n    auto selected_for\
    \ = [](long long coordinate) {\n        std::vector<P> points;\n        points.emplace_back(coordinate,\
    \ 0);\n        return convex_decomposition_detail::select_exact_predicate_width(\n\
    \            points\n        );\n    };\n\n    assert(selected_for(1LL << 29)\
    \ == PredicateWidth::Int128);\n    assert(selected_for(1LL << 30) == PredicateWidth::Int256);\n\
    \    assert(selected_for(1LL << 61) == PredicateWidth::Int256);\n    assert(selected_for(1LL\
    \ << 62) == PredicateWidth::Int512);\n    assert(\n        selected_for(std::numeric_limits<long\
    \ long>::min()) ==\n        PredicateWidth::Int512\n    );\n}\n\nvoid test_fixed()\
    \ {\n    std::vector<P> convex;\n    convex.emplace_back(0, 0);\n    convex.emplace_back(5,\
    \ 0);\n    convex.emplace_back(6, 3);\n    convex.emplace_back(2, 5);\n    convex.emplace_back(-1,\
    \ 2);\n    const auto convex_fast = approximate_convex_decomposition(convex);\n\
    \    const auto convex_exact = minimum_convex_decomposition(convex);\n    assert(convex_fast.has_value()\
    \ && convex_fast->size() == 1);\n    assert(convex_exact.has_value() && convex_exact->size()\
    \ == 1);\n\n    std::vector<P> l_shape;\n    l_shape.emplace_back(0, 0);\n   \
    \ l_shape.emplace_back(5, 0);\n    l_shape.emplace_back(5, 2);\n    l_shape.emplace_back(2,\
    \ 2);\n    l_shape.emplace_back(2, 5);\n    l_shape.emplace_back(0, 5);\n    const\
    \ auto l_fast = approximate_convex_decomposition(l_shape);\n    const auto l_exact\
    \ = minimum_convex_decomposition(l_shape);\n    assert(l_fast.has_value());\n\
    \    assert(l_exact.has_value() && l_exact->size() == 2);\n    assert_valid_decomposition(l_shape,\
    \ *l_fast);\n    assert_valid_decomposition(l_shape, *l_exact);\n\n    std::vector<P>\
    \ reconstruction_regression;\n    reconstruction_regression.emplace_back(50, 0);\n\
    \    reconstruction_regression.emplace_back(12, 16);\n    reconstruction_regression.emplace_back(-2,\
    \ 10);\n    reconstruction_regression.emplace_back(-45, 20);\n    reconstruction_regression.emplace_back(-9,\
    \ -5);\n    reconstruction_regression.emplace_back(-8, -40);\n    reconstruction_regression.emplace_back(14,\
    \ -14);\n    const auto reconstructed =\n        minimum_convex_decomposition(reconstruction_regression);\n\
    \    assert(reconstructed.has_value() && reconstructed->size() == 3);\n    assert_valid_decomposition(reconstruction_regression,\
    \ *reconstructed);\n    using PredicateWidth =\n        convex_decomposition_detail::ExactPredicateWidth;\n\
    \    assert(\n        convex_decomposition_detail::select_exact_predicate_width(\n\
    \            reconstruction_regression\n        ) == PredicateWidth::Int128\n\
    \    );\n\n    std::reverse(l_shape.begin(), l_shape.end());\n    l_shape.push_back(l_shape.front());\n\
    \    const auto clockwise = minimum_convex_decomposition(l_shape);\n    assert(clockwise.has_value()\
    \ && clockwise->size() == 2);\n\n    std::vector<P> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(2, 0);\n    redundant.emplace_back(4, 0);\n\
    \    redundant.emplace_back(4, 3);\n    redundant.emplace_back(0, 3);\n    redundant.emplace_back(0,\
    \ 0);\n    const auto cleaned = minimum_convex_decomposition(redundant);\n   \
    \ assert(cleaned.has_value() && cleaned->size() == 1);\n\n    std::vector<P> bow_tie;\n\
    \    bow_tie.emplace_back(0, 0);\n    bow_tie.emplace_back(4, 4);\n    bow_tie.emplace_back(0,\
    \ 4);\n    bow_tie.emplace_back(4, 0);\n    assert(!approximate_convex_decomposition(bow_tie).has_value());\n\
    \    assert(!minimum_convex_decomposition(bow_tie).has_value());\n\n    std::vector<Point<double>>\
    \ floating;\n    floating.emplace_back(0.0, 0.0);\n    floating.emplace_back(5.0,\
    \ 0.0);\n    floating.emplace_back(5.0, 2.0);\n    floating.emplace_back(2.0,\
    \ 2.0);\n    floating.emplace_back(2.0, 5.0);\n    floating.emplace_back(0.0,\
    \ 5.0);\n    const auto floating_exact = minimum_convex_decomposition(floating);\n\
    \    assert(floating_exact.has_value() && floating_exact->size() == 2);\n\n  \
    \  constexpr long long medium_shift = 1'000'000'000'000'000'000LL;\n    std::vector<P>\
    \ medium_translated = reconstruction_regression;\n    for (P& point : medium_translated)\
    \ {\n        point.x += medium_shift;\n        point.y += medium_shift;\n    }\n\
    \    assert(\n        convex_decomposition_detail::select_exact_predicate_width(\n\
    \            medium_translated\n        ) == PredicateWidth::Int256\n    );\n\
    \    const auto medium_exact =\n        minimum_convex_decomposition(medium_translated);\n\
    \    assert(medium_exact.has_value());\n    assert(medium_exact->size() == reconstructed->size());\n\
    \    assert_valid_decomposition(medium_translated, *medium_exact);\n\n    constexpr\
    \ long long shift = 8'000'000'000'000'000'000LL;\n    std::vector<P> translated\
    \ = reconstruction_regression;\n    for (P& point : translated) {\n        point.x\
    \ += shift;\n        point.y += shift;\n    }\n    const auto translated_exact\
    \ = minimum_convex_decomposition(translated);\n    assert(\n        convex_decomposition_detail::select_exact_predicate_width(\n\
    \            translated\n        ) == PredicateWidth::Int512\n    );\n    assert(translated_exact.has_value());\n\
    \    assert(translated_exact->size() == reconstructed->size());\n    assert_valid_decomposition(translated,\
    \ *translated_exact);\n}\n\nvoid test_exhaustive_small_polygons() {\n    std::vector<P>\
    \ point_set;\n    point_set.emplace_back(-5, -1);\n    point_set.emplace_back(-3,\
    \ 5);\n    point_set.emplace_back(-1, 1);\n    point_set.emplace_back(1, -5);\n\
    \    point_set.emplace_back(2, 3);\n    point_set.emplace_back(5, 1);\n\n    std::vector<int>\
    \ permutation(point_set.size());\n    std::iota(permutation.begin(), permutation.end(),\
    \ 0);\n    int checked = 0;\n    do {\n        if (permutation.front() != 0) continue;\n\
    \        std::vector<P> polygon;\n        polygon.reserve(point_set.size());\n\
    \        for (const int index : permutation) {\n            polygon.push_back(point_set[index]);\n\
    \        }\n        if (polygon_area2(polygon) <= 0 || !is_simple_polygon(polygon))\
    \ {\n            continue;\n        }\n\n        const int expected = brute_minimum_decomposition(polygon);\n\
    \        const auto exact = minimum_convex_decomposition(polygon);\n        const\
    \ auto fast = approximate_convex_decomposition(polygon);\n        assert(exact.has_value());\n\
    \        assert(fast.has_value());\n        assert(static_cast<int>(exact->size())\
    \ == expected);\n        assert(fast->size() <= 4 * exact->size());\n        assert_valid_decomposition(polygon,\
    \ *exact);\n        assert_valid_decomposition(polygon, *fast);\n        ++checked;\n\
    \    } while (std::next_permutation(permutation.begin(), permutation.end()));\n\
    \    assert(checked >= 1);\n}\n\nvoid test_random_radial_polygons() {\n    std::vector<P>\
    \ directions;\n    directions.emplace_back(10, 0);\n    directions.emplace_back(6,\
    \ 8);\n    directions.emplace_back(-2, 10);\n    directions.emplace_back(-9, 4);\n\
    \    directions.emplace_back(-9, -5);\n    directions.emplace_back(-2, -10);\n\
    \n    unsigned long long state = 0x9e3779b97f4a7c15ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n    for (int trial = 0; trial < 500; ++trial) {\n        std::vector<P>\
    \ polygon;\n        for (const P& direction : directions) {\n            const\
    \ long long radius =\n                1 + static_cast<long long>(random() % 5);\n\
    \            polygon.emplace_back(\n                direction.x * radius,\n  \
    \              direction.y * radius\n            );\n        }\n        assert(polygon_area2(polygon)\
    \ > 0);\n        assert(is_simple_polygon(polygon));\n\n        const int expected\
    \ = brute_minimum_decomposition(polygon);\n        const auto exact = minimum_convex_decomposition(polygon);\n\
    \        const auto fast = approximate_convex_decomposition(polygon);\n      \
    \  assert(exact.has_value());\n        assert(fast.has_value());\n        assert(static_cast<int>(exact->size())\
    \ == expected);\n        assert(fast->size() <= 4 * exact->size());\n        assert_valid_decomposition(polygon,\
    \ *exact);\n        assert_valid_decomposition(polygon, *fast);\n    }\n}\n\n\
    void test_reflex_sensitive_reduction() {\n    std::vector<P> polygon;\n    polygon.emplace_back(10,\
    \ 0);\n    polygon.emplace_back(8, 6);\n    polygon.emplace_back(3, 10);\n   \
    \ polygon.emplace_back(0, 0);\n    polygon.emplace_back(-8, 6);\n    polygon.emplace_back(-10,\
    \ 0);\n    polygon.emplace_back(-8, -6);\n    polygon.emplace_back(-3, -10);\n\
    \    polygon.emplace_back(3, -10);\n    polygon.emplace_back(8, -6);\n    assert(polygon_area2(polygon)\
    \ > 0);\n    assert(is_simple_polygon(polygon));\n\n    int reflex_count = 0;\n\
    \    for (std::size_t index = 0; index < polygon.size(); ++index) {\n        if\
    \ (\n            orientation(\n                polygon[(index + polygon.size()\
    \ - 1) % polygon.size()],\n                polygon[index],\n                polygon[(index\
    \ + 1) % polygon.size()]\n            ) < 0\n        ) {\n            ++reflex_count;\n\
    \        }\n    }\n    assert(reflex_count == 1);\n    assert(\n        polygon.size()\
    \ >\n        static_cast<std::size_t>(reflex_count * reflex_count)\n    );\n\n\
    \    const auto exact = minimum_convex_decomposition(polygon);\n    assert(exact.has_value()\
    \ && exact->size() == 2);\n    assert_valid_decomposition(polygon, *exact);\n\n\
    \    std::vector<P> two_reflex;\n    two_reflex.emplace_back(10, 0);\n    two_reflex.emplace_back(8,\
    \ 5);\n    two_reflex.emplace_back(1, 2);\n    two_reflex.emplace_back(0, 10);\n\
    \    two_reflex.emplace_back(-5, 8);\n    two_reflex.emplace_back(-8, 5);\n  \
    \  two_reflex.emplace_back(-10, 0);\n    two_reflex.emplace_back(-8, -5);\n  \
    \  two_reflex.emplace_back(-1, -2);\n    two_reflex.emplace_back(0, -10);\n  \
    \  two_reflex.emplace_back(5, -8);\n    two_reflex.emplace_back(8, -5);\n    assert(is_simple_polygon(two_reflex));\n\
    \    int second_reflex_count = 0;\n    for (std::size_t index = 0; index < two_reflex.size();\
    \ ++index) {\n        if (\n            orientation(\n                two_reflex[\n\
    \                    (index + two_reflex.size() - 1) % two_reflex.size()\n   \
    \             ],\n                two_reflex[index],\n                two_reflex[(index\
    \ + 1) % two_reflex.size()]\n            ) < 0\n        ) {\n            ++second_reflex_count;\n\
    \        }\n    }\n    assert(second_reflex_count == 2);\n    assert(\n      \
    \  two_reflex.size() >\n        static_cast<std::size_t>(\n            second_reflex_count\
    \ * second_reflex_count\n        )\n    );\n\n    convex_decomposition_detail::KeilSnoeyinkDecomposition<\n\
    \        long long, __int128_t\n    > direct_solver(two_reflex, 1e-12L);\n   \
    \ const auto direct_diagonals = direct_solver.run();\n    const auto reduced_solution\
    \ =\n        minimum_convex_decomposition(two_reflex);\n    assert(direct_diagonals.has_value());\n\
    \    assert(reduced_solution.has_value());\n    assert(reduced_solution->size()\
    \ == direct_diagonals->size() + 1);\n    assert_valid_decomposition(two_reflex,\
    \ *reduced_solution);\n}\n\n}  // namespace\n\nint main() {\n    test_predicate_width_selection();\n\
    \    test_fixed();\n    test_exhaustive_small_polygons();\n    test_random_radial_polygons();\n\
    \    test_reflex_sensitive_reduction();\n\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n    int size;\n    fast_input\
    \ >> size;\n    std::vector<P> polygon(size);\n    for (P& point : polygon) fast_input\
    \ >> point.x >> point.y;\n    fast_output << (is_convex_polygon(polygon) ? 1 :\
    \ 0) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\"\
    \n\n#include \"../../geometry/convex_decomposition.hpp\"\n#include \"../../geometry/convex_polygon.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <limits>\n\
    #include <map>\n#include <numeric>\n#include <vector>\n\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nusing namespace m1une::geometry;\nusing P = Point<long long>;\n\
    \nstd::vector<P> points_from_indices(\n    const std::vector<P>& polygon,\n  \
    \  const std::vector<int>& indices\n) {\n    std::vector<P> result;\n    result.reserve(indices.size());\n\
    \    for (const int index : indices) result.push_back(polygon[index]);\n    return\
    \ result;\n}\n\nstd::vector<int> canonical_cycle(std::vector<int> cycle) {\n \
    \   const auto start = std::min_element(cycle.begin(), cycle.end());\n    std::rotate(cycle.begin(),\
    \ start, cycle.end());\n    return cycle;\n}\n\nint brute_minimum_decomposition(\n\
    \    const std::vector<P>& polygon,\n    std::vector<int> region,\n    std::map<std::vector<int>,\
    \ int>& memo\n) {\n    region = canonical_cycle(std::move(region));\n    const\
    \ auto found = memo.find(region);\n    if (found != memo.end()) return found->second;\n\
    \n    const std::vector<P> points = points_from_indices(polygon, region);\n  \
    \  if (is_convex_polygon(points)) return memo[region] = 1;\n\n    const int size\
    \ = static_cast<int>(region.size());\n    int answer = std::numeric_limits<int>::max()\
    \ / 4;\n    for (int first = 0; first < size; ++first) {\n        for (int last\
    \ = first + 2; last < size; ++last) {\n            if (first == 0 && last + 1\
    \ == size) continue;\n\n            std::vector<int> left;\n            for (int\
    \ index = first; index <= last; ++index) {\n                left.push_back(region[index]);\n\
    \            }\n            std::vector<int> right;\n            for (int index\
    \ = last; index < size; ++index) {\n                right.push_back(region[index]);\n\
    \            }\n            for (int index = 0; index <= first; ++index) {\n \
    \               right.push_back(region[index]);\n            }\n\n           \
    \ const std::vector<P> left_points =\n                points_from_indices(polygon,\
    \ left);\n            const std::vector<P> right_points =\n                points_from_indices(polygon,\
    \ right);\n            if (\n                polygon_area2(left_points) <= 0 ||\n\
    \                polygon_area2(right_points) <= 0 ||\n                !is_simple_polygon(left_points)\
    \ ||\n                !is_simple_polygon(right_points)\n            ) {\n    \
    \            continue;\n            }\n            answer = std::min(\n      \
    \          answer,\n                brute_minimum_decomposition(polygon, left,\
    \ memo) +\n                    brute_minimum_decomposition(polygon, right, memo)\n\
    \            );\n        }\n    }\n    assert(answer < std::numeric_limits<int>::max()\
    \ / 4);\n    return memo[region] = answer;\n}\n\nint brute_minimum_decomposition(const\
    \ std::vector<P>& polygon) {\n    std::vector<int> indices(polygon.size());\n\
    \    std::iota(indices.begin(), indices.end(), 0);\n    std::map<std::vector<int>,\
    \ int> memo;\n    return brute_minimum_decomposition(polygon, indices, memo);\n\
    }\n\nvoid assert_valid_decomposition(\n    const std::vector<P>& polygon,\n  \
    \  const std::vector<std::vector<P>>& decomposition\n) {\n    assert(!decomposition.empty());\n\
    \    long double area_sum = 0;\n    std::vector<Point<long double>> floating_polygon;\n\
    \    floating_polygon.reserve(polygon.size());\n    for (const P& point : polygon)\
    \ floating_polygon.emplace_back(point);\n\n    for (const auto& part : decomposition)\
    \ {\n        assert(part.size() >= 3);\n        assert(polygon_area2(part) > 0);\n\
    \        assert(is_convex_polygon(part));\n        area_sum += polygon_area(part);\n\
    \        for (const P& point : part) {\n            assert(\n                point_in_polygon(polygon,\
    \ point) != PointInPolygon::Outside\n            );\n        }\n        for (std::size_t\
    \ index = 0; index < part.size(); ++index) {\n            const P& first = part[index];\n\
    \            const P& second = part[(index + 1) % part.size()];\n            const\
    \ Point<long double> midpoint(\n                (\n                    static_cast<long\
    \ double>(first.x) +\n                    static_cast<long double>(second.x)\n\
    \                ) / 2,\n                (\n                    static_cast<long\
    \ double>(first.y) +\n                    static_cast<long double>(second.y)\n\
    \                ) / 2\n            );\n            assert(\n                point_in_polygon(floating_polygon,\
    \ midpoint) !=\n                PointInPolygon::Outside\n            );\n    \
    \    }\n    }\n    assert(std::fabs(area_sum - polygon_area(polygon)) <= 1e-9L);\n\
    }\n\nvoid test_predicate_width_selection() {\n    using PredicateWidth =\n   \
    \     convex_decomposition_detail::ExactPredicateWidth;\n    auto selected_for\
    \ = [](long long coordinate) {\n        std::vector<P> points;\n        points.emplace_back(coordinate,\
    \ 0);\n        return convex_decomposition_detail::select_exact_predicate_width(\n\
    \            points\n        );\n    };\n\n    assert(selected_for(1LL << 29)\
    \ == PredicateWidth::Int128);\n    assert(selected_for(1LL << 30) == PredicateWidth::Int256);\n\
    \    assert(selected_for(1LL << 61) == PredicateWidth::Int256);\n    assert(selected_for(1LL\
    \ << 62) == PredicateWidth::Int512);\n    assert(\n        selected_for(std::numeric_limits<long\
    \ long>::min()) ==\n        PredicateWidth::Int512\n    );\n}\n\nvoid test_fixed()\
    \ {\n    std::vector<P> convex;\n    convex.emplace_back(0, 0);\n    convex.emplace_back(5,\
    \ 0);\n    convex.emplace_back(6, 3);\n    convex.emplace_back(2, 5);\n    convex.emplace_back(-1,\
    \ 2);\n    const auto convex_fast = approximate_convex_decomposition(convex);\n\
    \    const auto convex_exact = minimum_convex_decomposition(convex);\n    assert(convex_fast.has_value()\
    \ && convex_fast->size() == 1);\n    assert(convex_exact.has_value() && convex_exact->size()\
    \ == 1);\n\n    std::vector<P> l_shape;\n    l_shape.emplace_back(0, 0);\n   \
    \ l_shape.emplace_back(5, 0);\n    l_shape.emplace_back(5, 2);\n    l_shape.emplace_back(2,\
    \ 2);\n    l_shape.emplace_back(2, 5);\n    l_shape.emplace_back(0, 5);\n    const\
    \ auto l_fast = approximate_convex_decomposition(l_shape);\n    const auto l_exact\
    \ = minimum_convex_decomposition(l_shape);\n    assert(l_fast.has_value());\n\
    \    assert(l_exact.has_value() && l_exact->size() == 2);\n    assert_valid_decomposition(l_shape,\
    \ *l_fast);\n    assert_valid_decomposition(l_shape, *l_exact);\n\n    std::vector<P>\
    \ reconstruction_regression;\n    reconstruction_regression.emplace_back(50, 0);\n\
    \    reconstruction_regression.emplace_back(12, 16);\n    reconstruction_regression.emplace_back(-2,\
    \ 10);\n    reconstruction_regression.emplace_back(-45, 20);\n    reconstruction_regression.emplace_back(-9,\
    \ -5);\n    reconstruction_regression.emplace_back(-8, -40);\n    reconstruction_regression.emplace_back(14,\
    \ -14);\n    const auto reconstructed =\n        minimum_convex_decomposition(reconstruction_regression);\n\
    \    assert(reconstructed.has_value() && reconstructed->size() == 3);\n    assert_valid_decomposition(reconstruction_regression,\
    \ *reconstructed);\n    using PredicateWidth =\n        convex_decomposition_detail::ExactPredicateWidth;\n\
    \    assert(\n        convex_decomposition_detail::select_exact_predicate_width(\n\
    \            reconstruction_regression\n        ) == PredicateWidth::Int128\n\
    \    );\n\n    std::reverse(l_shape.begin(), l_shape.end());\n    l_shape.push_back(l_shape.front());\n\
    \    const auto clockwise = minimum_convex_decomposition(l_shape);\n    assert(clockwise.has_value()\
    \ && clockwise->size() == 2);\n\n    std::vector<P> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(2, 0);\n    redundant.emplace_back(4, 0);\n\
    \    redundant.emplace_back(4, 3);\n    redundant.emplace_back(0, 3);\n    redundant.emplace_back(0,\
    \ 0);\n    const auto cleaned = minimum_convex_decomposition(redundant);\n   \
    \ assert(cleaned.has_value() && cleaned->size() == 1);\n\n    std::vector<P> bow_tie;\n\
    \    bow_tie.emplace_back(0, 0);\n    bow_tie.emplace_back(4, 4);\n    bow_tie.emplace_back(0,\
    \ 4);\n    bow_tie.emplace_back(4, 0);\n    assert(!approximate_convex_decomposition(bow_tie).has_value());\n\
    \    assert(!minimum_convex_decomposition(bow_tie).has_value());\n\n    std::vector<Point<double>>\
    \ floating;\n    floating.emplace_back(0.0, 0.0);\n    floating.emplace_back(5.0,\
    \ 0.0);\n    floating.emplace_back(5.0, 2.0);\n    floating.emplace_back(2.0,\
    \ 2.0);\n    floating.emplace_back(2.0, 5.0);\n    floating.emplace_back(0.0,\
    \ 5.0);\n    const auto floating_exact = minimum_convex_decomposition(floating);\n\
    \    assert(floating_exact.has_value() && floating_exact->size() == 2);\n\n  \
    \  constexpr long long medium_shift = 1'000'000'000'000'000'000LL;\n    std::vector<P>\
    \ medium_translated = reconstruction_regression;\n    for (P& point : medium_translated)\
    \ {\n        point.x += medium_shift;\n        point.y += medium_shift;\n    }\n\
    \    assert(\n        convex_decomposition_detail::select_exact_predicate_width(\n\
    \            medium_translated\n        ) == PredicateWidth::Int256\n    );\n\
    \    const auto medium_exact =\n        minimum_convex_decomposition(medium_translated);\n\
    \    assert(medium_exact.has_value());\n    assert(medium_exact->size() == reconstructed->size());\n\
    \    assert_valid_decomposition(medium_translated, *medium_exact);\n\n    constexpr\
    \ long long shift = 8'000'000'000'000'000'000LL;\n    std::vector<P> translated\
    \ = reconstruction_regression;\n    for (P& point : translated) {\n        point.x\
    \ += shift;\n        point.y += shift;\n    }\n    const auto translated_exact\
    \ = minimum_convex_decomposition(translated);\n    assert(\n        convex_decomposition_detail::select_exact_predicate_width(\n\
    \            translated\n        ) == PredicateWidth::Int512\n    );\n    assert(translated_exact.has_value());\n\
    \    assert(translated_exact->size() == reconstructed->size());\n    assert_valid_decomposition(translated,\
    \ *translated_exact);\n}\n\nvoid test_exhaustive_small_polygons() {\n    std::vector<P>\
    \ point_set;\n    point_set.emplace_back(-5, -1);\n    point_set.emplace_back(-3,\
    \ 5);\n    point_set.emplace_back(-1, 1);\n    point_set.emplace_back(1, -5);\n\
    \    point_set.emplace_back(2, 3);\n    point_set.emplace_back(5, 1);\n\n    std::vector<int>\
    \ permutation(point_set.size());\n    std::iota(permutation.begin(), permutation.end(),\
    \ 0);\n    int checked = 0;\n    do {\n        if (permutation.front() != 0) continue;\n\
    \        std::vector<P> polygon;\n        polygon.reserve(point_set.size());\n\
    \        for (const int index : permutation) {\n            polygon.push_back(point_set[index]);\n\
    \        }\n        if (polygon_area2(polygon) <= 0 || !is_simple_polygon(polygon))\
    \ {\n            continue;\n        }\n\n        const int expected = brute_minimum_decomposition(polygon);\n\
    \        const auto exact = minimum_convex_decomposition(polygon);\n        const\
    \ auto fast = approximate_convex_decomposition(polygon);\n        assert(exact.has_value());\n\
    \        assert(fast.has_value());\n        assert(static_cast<int>(exact->size())\
    \ == expected);\n        assert(fast->size() <= 4 * exact->size());\n        assert_valid_decomposition(polygon,\
    \ *exact);\n        assert_valid_decomposition(polygon, *fast);\n        ++checked;\n\
    \    } while (std::next_permutation(permutation.begin(), permutation.end()));\n\
    \    assert(checked >= 1);\n}\n\nvoid test_random_radial_polygons() {\n    std::vector<P>\
    \ directions;\n    directions.emplace_back(10, 0);\n    directions.emplace_back(6,\
    \ 8);\n    directions.emplace_back(-2, 10);\n    directions.emplace_back(-9, 4);\n\
    \    directions.emplace_back(-9, -5);\n    directions.emplace_back(-2, -10);\n\
    \n    unsigned long long state = 0x9e3779b97f4a7c15ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n    for (int trial = 0; trial < 500; ++trial) {\n        std::vector<P>\
    \ polygon;\n        for (const P& direction : directions) {\n            const\
    \ long long radius =\n                1 + static_cast<long long>(random() % 5);\n\
    \            polygon.emplace_back(\n                direction.x * radius,\n  \
    \              direction.y * radius\n            );\n        }\n        assert(polygon_area2(polygon)\
    \ > 0);\n        assert(is_simple_polygon(polygon));\n\n        const int expected\
    \ = brute_minimum_decomposition(polygon);\n        const auto exact = minimum_convex_decomposition(polygon);\n\
    \        const auto fast = approximate_convex_decomposition(polygon);\n      \
    \  assert(exact.has_value());\n        assert(fast.has_value());\n        assert(static_cast<int>(exact->size())\
    \ == expected);\n        assert(fast->size() <= 4 * exact->size());\n        assert_valid_decomposition(polygon,\
    \ *exact);\n        assert_valid_decomposition(polygon, *fast);\n    }\n}\n\n\
    void test_reflex_sensitive_reduction() {\n    std::vector<P> polygon;\n    polygon.emplace_back(10,\
    \ 0);\n    polygon.emplace_back(8, 6);\n    polygon.emplace_back(3, 10);\n   \
    \ polygon.emplace_back(0, 0);\n    polygon.emplace_back(-8, 6);\n    polygon.emplace_back(-10,\
    \ 0);\n    polygon.emplace_back(-8, -6);\n    polygon.emplace_back(-3, -10);\n\
    \    polygon.emplace_back(3, -10);\n    polygon.emplace_back(8, -6);\n    assert(polygon_area2(polygon)\
    \ > 0);\n    assert(is_simple_polygon(polygon));\n\n    int reflex_count = 0;\n\
    \    for (std::size_t index = 0; index < polygon.size(); ++index) {\n        if\
    \ (\n            orientation(\n                polygon[(index + polygon.size()\
    \ - 1) % polygon.size()],\n                polygon[index],\n                polygon[(index\
    \ + 1) % polygon.size()]\n            ) < 0\n        ) {\n            ++reflex_count;\n\
    \        }\n    }\n    assert(reflex_count == 1);\n    assert(\n        polygon.size()\
    \ >\n        static_cast<std::size_t>(reflex_count * reflex_count)\n    );\n\n\
    \    const auto exact = minimum_convex_decomposition(polygon);\n    assert(exact.has_value()\
    \ && exact->size() == 2);\n    assert_valid_decomposition(polygon, *exact);\n\n\
    \    std::vector<P> two_reflex;\n    two_reflex.emplace_back(10, 0);\n    two_reflex.emplace_back(8,\
    \ 5);\n    two_reflex.emplace_back(1, 2);\n    two_reflex.emplace_back(0, 10);\n\
    \    two_reflex.emplace_back(-5, 8);\n    two_reflex.emplace_back(-8, 5);\n  \
    \  two_reflex.emplace_back(-10, 0);\n    two_reflex.emplace_back(-8, -5);\n  \
    \  two_reflex.emplace_back(-1, -2);\n    two_reflex.emplace_back(0, -10);\n  \
    \  two_reflex.emplace_back(5, -8);\n    two_reflex.emplace_back(8, -5);\n    assert(is_simple_polygon(two_reflex));\n\
    \    int second_reflex_count = 0;\n    for (std::size_t index = 0; index < two_reflex.size();\
    \ ++index) {\n        if (\n            orientation(\n                two_reflex[\n\
    \                    (index + two_reflex.size() - 1) % two_reflex.size()\n   \
    \             ],\n                two_reflex[index],\n                two_reflex[(index\
    \ + 1) % two_reflex.size()]\n            ) < 0\n        ) {\n            ++second_reflex_count;\n\
    \        }\n    }\n    assert(second_reflex_count == 2);\n    assert(\n      \
    \  two_reflex.size() >\n        static_cast<std::size_t>(\n            second_reflex_count\
    \ * second_reflex_count\n        )\n    );\n\n    convex_decomposition_detail::KeilSnoeyinkDecomposition<\n\
    \        long long, __int128_t\n    > direct_solver(two_reflex, 1e-12L);\n   \
    \ const auto direct_diagonals = direct_solver.run();\n    const auto reduced_solution\
    \ =\n        minimum_convex_decomposition(two_reflex);\n    assert(direct_diagonals.has_value());\n\
    \    assert(reduced_solution.has_value());\n    assert(reduced_solution->size()\
    \ == direct_diagonals->size() + 1);\n    assert_valid_decomposition(two_reflex,\
    \ *reduced_solution);\n}\n\n}  // namespace\n\nint main() {\n    test_predicate_width_selection();\n\
    \    test_fixed();\n    test_exhaustive_small_polygons();\n    test_random_radial_polygons();\n\
    \    test_reflex_sensitive_reduction();\n\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n    int size;\n    fast_input\
    \ >> size;\n    std::vector<P> polygon(size);\n    for (P& point : polygon) fast_input\
    \ >> point.x >> point.y;\n    fast_output << (is_convex_polygon(polygon) ? 1 :\
    \ 0) << '\\n';\n}\n"
  dependsOn:
  - geometry/convex_decomposition.hpp
  - utilities/int256.hpp
  - utilities/detail/fixed_int.hpp
  - utilities/int512.hpp
  - geometry/polygon.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  - geometry/convex_polygon.hpp
  - geometry/convex_hull.hpp
  - geometry/half_plane_intersection.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/convex_decomposition.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 09:31:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/convex_decomposition.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/convex_decomposition.test.cpp
- /verify/verify/geometry/convex_decomposition.test.cpp.html
title: verify/geometry/convex_decomposition.test.cpp
---
