---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Roots and Powers
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modular_kth_root.hpp
    title: Modular Kth Root
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_root_mod
    links:
    - https://judge.yosupo.jp/problem/kth_root_mod
  bundledCode: "#line 1 \"verify/math/modular_kth_root.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/kth_root_mod\"\n\n#line 1 \"math/modular_kth_root.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <numeric>\n#include <optional>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"math/integer_arithmetic.hpp\"\n\n\n\n#line 5 \"math/integer_arithmetic.hpp\"\
    \n#include <concepts>\n#include <limits>\n#line 8 \"math/integer_arithmetic.hpp\"\
    \n#include <type_traits>\n\nnamespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail\
    \ {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr std::optional<T> checked_multiply(T first, T second) {\n \
    \   constexpr T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum\
    \ = std::numeric_limits<T>::max();\n\n    if constexpr (std::unsigned_integral<T>)\
    \ {\n        if (second != 0 && maximum / second < first) return std::nullopt;\n\
    \    } else {\n        if (0 < first) {\n            if (0 < second) {\n     \
    \           if (maximum / second < first) return std::nullopt;\n            }\
    \ else if (second < minimum / first) {\n                return std::nullopt;\n\
    \            }\n        } else if (first < 0) {\n            if (0 < second) {\n\
    \                if (first < minimum / second) return std::nullopt;\n        \
    \    } else if (second < maximum / first) {\n                return std::nullopt;\n\
    \            }\n        }\n    }\n    return T(first * second);\n}\n\ntemplate\
    \ <std::unsigned_integral T>\nconstexpr bool kth_power_leq(T base, unsigned exponent,\
    \ T limit) {\n    assert(exponent > 0);\n    if (base <= 1) return base <= limit;\n\
    \n    const T multiplication_limit = limit / base;\n    T product = 1;\n    for\
    \ (unsigned i = 0; i < exponent; i++) {\n        if (product > multiplication_limit)\
    \ return false;\n        product *= base;\n    }\n    return true;\n}\n\n}  //\
    \ namespace integer_arithmetic_detail\n\n// Returns floor(sqrt(value)) exactly,\
    \ without floating-point arithmetic.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ assert(0 <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n \
    \   T high = value / 2 + 1;\n    while (low < high) {\n        T middle = low\
    \ + (high - low + 1) / 2;\n        if (middle <= value / middle) {\n         \
    \   low = middle;\n        } else {\n            high = middle - 1;\n        }\n\
    \    }\n    return low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T floor_sqrt(T value) {\n    return isqrt(value);\n}\n\n//\
    \ Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nconstexpr\
    \ T ceil_sqrt(T value) {\n    T result = isqrt(value);\n    if (result == 0) return\
    \ 0;\n    if (result != 0 && value / result == result && value % result == 0)\
    \ {\n        return result;\n    }\n    return result + 1;\n}\n\n// Returns floor(value^(1\
    \ / degree)) exactly, without floating-point arithmetic.\ntemplate <std::integral\
    \ T, std::integral Degree>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Degree>, bool>\n)\nconstexpr T\
    \ floor_kth_root(T value, Degree degree) {\n    if constexpr (std::signed_integral<T>)\
    \ {\n        assert(0 <= value);\n        if (value < 0) return T();\n    }\n\
    \    assert(0 < degree);\n    if (degree <= 0) return T();\n    if (value <= 1\
    \ || degree == 1) return value;\n    if (degree == 2) return isqrt(value);\n\n\
    \    using U = std::make_unsigned_t<T>;\n    using UDegree = std::make_unsigned_t<Degree>;\n\
    \    constexpr int digits = std::numeric_limits<U>::digits;\n    const UDegree\
    \ unsigned_degree = static_cast<UDegree>(degree);\n    if (unsigned_degree >=\
    \ static_cast<UDegree>(digits)) return T(1);\n    const unsigned exponent = static_cast<unsigned>(unsigned_degree);\n\
    \    const U unsigned_value = static_cast<U>(value);\n\n    int bit_width = 0;\n\
    \    for (U remaining = unsigned_value; remaining != 0; remaining >>= 1) {\n \
    \       bit_width++;\n    }\n    const int root_bits =\n        (bit_width + static_cast<int>(exponent)\
    \ - 1) /\n        static_cast<int>(exponent);\n\n    U low = 1;\n    U high =\
    \ U(1) << root_bits;\n    while (high - low > 1) {\n        const U middle = low\
    \ + (high - low) / 2;\n        if (\n            integer_arithmetic_detail::kth_power_leq(\n\
    \                middle, exponent, unsigned_value\n            )\n        ) {\n\
    \            low = middle;\n        } else {\n            high = middle;\n   \
    \     }\n    }\n    return static_cast<T>(low);\n}\n\n// Returns base^exponent,\
    \ or nullopt when the result does not fit in T.\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr std::optional<T> checked_ipow(T base, Exponent exponent)\
    \ {\n    T result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ {\n            auto product =\n                integer_arithmetic_detail::checked_multiply(result,\
    \ base);\n            if (!product.has_value()) return std::nullopt;\n       \
    \     result = *product;\n        }\n        exponent >>= 1;\n        if (exponent\
    \ != 0) {\n            auto square =\n                integer_arithmetic_detail::checked_multiply(base,\
    \ base);\n            if (!square.has_value()) return std::nullopt;\n        \
    \    base = *square;\n        }\n    }\n    return result;\n}\n\ntemplate <std::integral\
    \ T, std::unsigned_integral Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Exponent>, bool>\n)\nconstexpr\
    \ std::optional<T> checked_integer_pow(T base, Exponent exponent) {\n    return\
    \ checked_ipow(base, exponent);\n}\n\n// Returns base^exponent. The result must\
    \ be representable by T.\ntemplate <std::integral T, std::unsigned_integral Exponent>\n\
    requires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T ipow(T base, Exponent exponent) {\n    std::optional<T>\
    \ result = checked_ipow(base, exponent);\n    assert(result.has_value());\n  \
    \  return result.value_or(T());\n}\n\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T integer_pow(T base, Exponent exponent) {\n    return ipow(base,\
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 13 \"\
    math/modular_kth_root.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ modular_kth_root_detail {\n\ninline uint64_t multiply(uint64_t first, uint64_t\
    \ second, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<__uint128_t>(first)\
    \ * second % mod);\n}\n\ninline uint64_t power(uint64_t base, uint64_t exponent,\
    \ uint64_t mod) {\n    uint64_t result = 1 % mod;\n    while (exponent != 0) {\n\
    \        if (exponent & 1) result = multiply(result, base, mod);\n        base\
    \ = multiply(base, base, mod);\n        exponent >>= 1;\n    }\n    return result;\n\
    }\n\ninline uint64_t integer_power(uint64_t base, int exponent) {\n    uint64_t\
    \ result = 1;\n    for (int i = 0; i < exponent; i++) result *= base;\n    return\
    \ result;\n}\n\ninline uint64_t inverse(uint64_t value, uint64_t mod) {\n    if\
    \ (mod == 1) return 0;\n    value %= mod;\n    uint64_t old_remainder = mod;\n\
    \    uint64_t remainder = value;\n    __int128_t old_coefficient = 0;\n    __int128_t\
    \ coefficient = 1;\n    while (remainder != 0) {\n        const uint64_t quotient\
    \ = old_remainder / remainder;\n        const uint64_t next_remainder =\n    \
    \        old_remainder - quotient * remainder;\n        old_remainder = remainder;\n\
    \        remainder = next_remainder;\n\n        const __int128_t next_coefficient\
    \ =\n            old_coefficient - static_cast<__int128_t>(quotient) * coefficient;\n\
    \        old_coefficient = coefficient;\n        coefficient = next_coefficient;\n\
    \    }\n    assert(old_remainder == 1);\n    old_coefficient %= static_cast<__int128_t>(mod);\n\
    \    if (old_coefficient < 0) old_coefficient += mod;\n    return static_cast<uint64_t>(old_coefficient);\n\
    }\n\ninline uint64_t extract_prime_power_root(\n    uint64_t value,\n    uint64_t\
    \ root_prime,\n    int exponent,\n    uint64_t prime\n) {\n    uint64_t coprime_part\
    \ = prime - 1;\n    int available_exponent = 0;\n    while (coprime_part % root_prime\
    \ == 0) {\n        coprime_part /= root_prime;\n        available_exponent++;\n\
    \    }\n    assert(exponent <= available_exponent);\n\n    const uint64_t root_prime_power\
    \ = integer_power(root_prime, exponent);\n    const uint64_t inverse_coprime_part\
    \ = inverse(\n        coprime_part, root_prime_power\n    );\n    const uint64_t\
    \ residue = static_cast<uint64_t>(\n        static_cast<__uint128_t>(root_prime_power\
    \ - 1) *\n        inverse_coprime_part % root_prime_power\n    );\n    const uint64_t\
    \ root_exponent = static_cast<uint64_t>(\n        (static_cast<__uint128_t>(residue)\
    \ * coprime_part + 1) /\n        root_prime_power\n    );\n    uint64_t root =\
    \ power(value, root_exponent, prime);\n    if (exponent == available_exponent)\
    \ return root;\n\n    uint64_t non_residue = 2;\n    while (power(non_residue,\
    \ (prime - 1) / root_prime, prime) == 1) {\n        non_residue++;\n    }\n  \
    \  const uint64_t generator = power(non_residue, coprime_part, prime);\n    const\
    \ uint64_t digit_generator = power(\n        generator,\n        integer_power(root_prime,\
    \ available_exponent - 1),\n        prime\n    );\n\n    const uint64_t step =\
    \ isqrt(\n        static_cast<uint64_t>(available_exponent - exponent) * root_prime\n\
    \    ) + 1;\n    const uint64_t giant_factor = power(digit_generator, step, prime);\n\
    \    std::vector<std::pair<uint64_t, uint64_t>> baby_steps;\n    baby_steps.reserve(step\
    \ + 1);\n    uint64_t current = 1;\n    for (uint64_t index = 0; index <= step;\
    \ index++) {\n        baby_steps.emplace_back(current, index);\n        current\
    \ = multiply(current, giant_factor, prime);\n    }\n    std::sort(baby_steps.begin(),\
    \ baby_steps.end());\n\n    const uint64_t inverse_digit_generator = power(\n\
    \        digit_generator, prime - 2, prime\n    );\n    for (int level = exponent;\
    \ level < available_exponent; level++) {\n        const uint64_t root_power =\
    \ power(root, root_prime_power, prime);\n        const uint64_t error = multiply(\n\
    \            power(root_power, prime - 2, prime), value, prime\n        );\n \
    \       uint64_t target = power(\n            error,\n            integer_power(root_prime,\
    \ available_exponent - 1 - level),\n            prime\n        );\n\n        bool\
    \ found = false;\n        uint64_t logarithm = 0;\n        for (uint64_t remainder\
    \ = 0; remainder <= step; remainder++) {\n            auto iterator = std::upper_bound(\n\
    \                baby_steps.begin(),\n                baby_steps.end(),\n    \
    \            target,\n                [](uint64_t key, const std::pair<uint64_t,\
    \ uint64_t>& entry) {\n                    return key < entry.first;\n       \
    \         }\n            );\n            if (iterator != baby_steps.begin()) {\n\
    \                --iterator;\n                if (iterator->first == target) {\n\
    \                    logarithm = remainder + step * iterator->second;\n      \
    \              found = true;\n                    break;\n                }\n\
    \            }\n            target = multiply(target, inverse_digit_generator,\
    \ prime);\n        }\n        assert(found);\n        if (!found) return 0;\n\n\
    \        const uint64_t correction_exponent =\n            logarithm * integer_power(root_prime,\
    \ level - exponent);\n        root = multiply(\n            root,\n          \
    \  power(generator, correction_exponent, prime),\n            prime\n        );\n\
    \    }\n    return root;\n}\n\n}  // namespace modular_kth_root_detail\n\n// Returns\
    \ x such that x^degree = value (mod prime), or nullopt when no root\n// exists.\
    \ The modulus must be prime.\ninline std::optional<uint64_t> modular_kth_root(\n\
    \    uint64_t value,\n    uint64_t degree,\n    uint64_t prime\n) {\n    assert(prime\
    \ >= 2);\n    value %= prime;\n    if (degree == 0) {\n        if (value == 1)\
    \ return uint64_t(0);\n        return std::nullopt;\n    }\n    if (value == 0)\
    \ return uint64_t(0);\n    if (prime == 2) return uint64_t(1);\n\n    const uint64_t\
    \ group_order = prime - 1;\n    degree %= group_order;\n    const uint64_t common_divisor\
    \ = std::gcd(degree, group_order);\n    if (\n        modular_kth_root_detail::power(\n\
    \            value, group_order / common_divisor, prime\n        ) != 1\n    )\
    \ {\n        return std::nullopt;\n    }\n\n    const uint64_t reduced_order =\
    \ group_order / common_divisor;\n    uint64_t transformed = 1;\n    if (reduced_order\
    \ != 1) {\n        const uint64_t inverse_degree = modular_kth_root_detail::inverse(\n\
    \            degree / common_divisor, reduced_order\n        );\n        transformed\
    \ = modular_kth_root_detail::power(\n            value, inverse_degree, prime\n\
    \        );\n    }\n\n    uint64_t remaining = common_divisor;\n    int exponent\
    \ = 0;\n    while ((remaining & 1) == 0) {\n        remaining >>= 1;\n       \
    \ exponent++;\n    }\n    if (exponent != 0) {\n        transformed = modular_kth_root_detail::extract_prime_power_root(\n\
    \            transformed, 2, exponent, prime\n        );\n    }\n    for (uint64_t\
    \ divisor = 3; divisor <= remaining / divisor; divisor += 2) {\n        exponent\
    \ = 0;\n        while (remaining % divisor == 0) {\n            remaining /= divisor;\n\
    \            exponent++;\n        }\n        if (exponent != 0) {\n          \
    \  transformed = modular_kth_root_detail::extract_prime_power_root(\n        \
    \        transformed, divisor, exponent, prime\n            );\n        }\n  \
    \  }\n    if (remaining != 1) {\n        transformed = modular_kth_root_detail::extract_prime_power_root(\n\
    \            transformed, remaining, 1, prime\n        );\n    }\n    return transformed;\n\
    }\n\ntemplate <class Mint>\nstd::optional<Mint> modular_kth_root(Mint value, uint64_t\
    \ degree) {\n    auto root = modular_kth_root(\n        static_cast<uint64_t>(value.val()),\n\
    \        degree,\n        static_cast<uint64_t>(Mint::mod())\n    );\n    if (!root.has_value())\
    \ return std::nullopt;\n    return Mint(*root);\n}\n\n}  // namespace math\n}\
    \  // namespace m1une\n\n\n#line 4 \"verify/math/modular_kth_root.test.cpp\"\n\
    \n#line 8 \"verify/math/modular_kth_root.test.cpp\"\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n#line 9 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n\
    \   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr ModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n  \
    \          if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include\
    \ <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/math/modular_kth_root.test.cpp\"\
    \n\nnamespace {\n\nuint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t\
    \ mod) {\n    uint64_t result = 1 % mod;\n    while (exponent != 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<uint64_t>(\n        \
    \        static_cast<__uint128_t>(result) * base % mod\n            );\n     \
    \   }\n        base = static_cast<uint64_t>(\n            static_cast<__uint128_t>(base)\
    \ * base % mod\n        );\n        exponent >>= 1;\n    }\n    return result;\n\
    }\n\nbool is_prime(uint64_t value) {\n    if (value < 2) return false;\n    for\
    \ (uint64_t divisor = 2; divisor <= value / divisor; divisor++) {\n        if\
    \ (value % divisor == 0) return false;\n    }\n    return true;\n}\n\nvoid test_exhaustive()\
    \ {\n    for (uint64_t prime = 2; prime <= 47; prime++) {\n        if (!is_prime(prime))\
    \ continue;\n        for (uint64_t degree = 0; degree <= 2 * prime; degree++)\
    \ {\n            std::vector<bool> exists(prime, false);\n            for (uint64_t\
    \ root = 0; root < prime; root++) {\n                exists[power_mod(root, degree,\
    \ prime)] = true;\n            }\n            for (uint64_t value = 0; value <\
    \ prime; value++) {\n                auto root = m1une::math::modular_kth_root(\n\
    \                    value, degree, prime\n                );\n              \
    \  assert(root.has_value() == exists[value]);\n                if (root.has_value())\
    \ {\n                    assert(*root < prime);\n                    assert(power_mod(*root,\
    \ degree, prime) == value);\n                }\n            }\n        }\n   \
    \ }\n\n    using Mint = m1une::math::ModInt<13>;\n    auto root = m1une::math::modular_kth_root(Mint(8),\
    \ 3);\n    assert(root.has_value());\n    assert(root->pow(3) == Mint(8));\n \
    \   assert(!m1une::math::modular_kth_root(Mint(2), 4).has_value());\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_exhaustive();\n\n    int\
    \ test_count;\n    fast_input >> test_count;\n    while (test_count--) {\n   \
    \     uint64_t degree, value, prime;\n        fast_input >> degree >> value >>\
    \ prime;\n        auto root = m1une::math::modular_kth_root(value, degree, prime);\n\
    \        if (root.has_value()) {\n            fast_output << *root << '\\n';\n\
    \        } else {\n            fast_output << -1 << '\\n';\n        }\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_mod\"\n\n#include\
    \ \"../../math/modular_kth_root.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <vector>\n\n#include \"../../math/modint.hpp\"\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nuint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t\
    \ mod) {\n    uint64_t result = 1 % mod;\n    while (exponent != 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<uint64_t>(\n        \
    \        static_cast<__uint128_t>(result) * base % mod\n            );\n     \
    \   }\n        base = static_cast<uint64_t>(\n            static_cast<__uint128_t>(base)\
    \ * base % mod\n        );\n        exponent >>= 1;\n    }\n    return result;\n\
    }\n\nbool is_prime(uint64_t value) {\n    if (value < 2) return false;\n    for\
    \ (uint64_t divisor = 2; divisor <= value / divisor; divisor++) {\n        if\
    \ (value % divisor == 0) return false;\n    }\n    return true;\n}\n\nvoid test_exhaustive()\
    \ {\n    for (uint64_t prime = 2; prime <= 47; prime++) {\n        if (!is_prime(prime))\
    \ continue;\n        for (uint64_t degree = 0; degree <= 2 * prime; degree++)\
    \ {\n            std::vector<bool> exists(prime, false);\n            for (uint64_t\
    \ root = 0; root < prime; root++) {\n                exists[power_mod(root, degree,\
    \ prime)] = true;\n            }\n            for (uint64_t value = 0; value <\
    \ prime; value++) {\n                auto root = m1une::math::modular_kth_root(\n\
    \                    value, degree, prime\n                );\n              \
    \  assert(root.has_value() == exists[value]);\n                if (root.has_value())\
    \ {\n                    assert(*root < prime);\n                    assert(power_mod(*root,\
    \ degree, prime) == value);\n                }\n            }\n        }\n   \
    \ }\n\n    using Mint = m1une::math::ModInt<13>;\n    auto root = m1une::math::modular_kth_root(Mint(8),\
    \ 3);\n    assert(root.has_value());\n    assert(root->pow(3) == Mint(8));\n \
    \   assert(!m1une::math::modular_kth_root(Mint(2), 4).has_value());\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_exhaustive();\n\n    int\
    \ test_count;\n    fast_input >> test_count;\n    while (test_count--) {\n   \
    \     uint64_t degree, value, prime;\n        fast_input >> degree >> value >>\
    \ prime;\n        auto root = m1une::math::modular_kth_root(value, degree, prime);\n\
    \        if (root.has_value()) {\n            fast_output << *root << '\\n';\n\
    \        } else {\n            fast_output << -1 << '\\n';\n        }\n    }\n\
    }\n"
  dependsOn:
  - math/modular_kth_root.hpp
  - math/integer_arithmetic.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/modular_kth_root.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/modular_kth_root.test.cpp
layout: document
redirect_from:
- /verify/verify/math/modular_kth_root.test.cpp
- /verify/verify/math/modular_kth_root.test.cpp.html
title: verify/math/modular_kth_root.test.cpp
---
