---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Roots and Powers
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/modular_kth_root.test.cpp
    title: verify/math/modular_kth_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/modular_kth_root.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <numeric>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"math/integer_arithmetic.hpp\"\
    \n\n\n\n#line 5 \"math/integer_arithmetic.hpp\"\n#include <concepts>\n#include\
    \ <limits>\n#line 8 \"math/integer_arithmetic.hpp\"\n#include <type_traits>\n\n\
    namespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail {\n\
    \ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    constexpr std::optional<T> checked_multiply(T first, T second) {\n    constexpr\
    \ T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum = std::numeric_limits<T>::max();\n\
    \n    if constexpr (std::unsigned_integral<T>) {\n        if (second != 0 && maximum\
    \ / second < first) return std::nullopt;\n    } else {\n        if (0 < first)\
    \ {\n            if (0 < second) {\n                if (maximum / second < first)\
    \ return std::nullopt;\n            } else if (second < minimum / first) {\n \
    \               return std::nullopt;\n            }\n        } else if (first\
    \ < 0) {\n            if (0 < second) {\n                if (first < minimum /\
    \ second) return std::nullopt;\n            } else if (second < maximum / first)\
    \ {\n                return std::nullopt;\n            }\n        }\n    }\n \
    \   return T(first * second);\n}\n\ntemplate <std::unsigned_integral T>\nconstexpr\
    \ bool kth_power_leq(T base, unsigned exponent, T limit) {\n    assert(exponent\
    \ > 0);\n    if (base <= 1) return base <= limit;\n\n    const T multiplication_limit\
    \ = limit / base;\n    T product = 1;\n    for (unsigned i = 0; i < exponent;\
    \ i++) {\n        if (product > multiplication_limit) return false;\n        product\
    \ *= base;\n    }\n    return true;\n}\n\n}  // namespace integer_arithmetic_detail\n\
    \n// Returns floor(sqrt(value)) exactly, without floating-point arithmetic.\n\
    template <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    constexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>) assert(0\
    \ <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n    T high\
    \ = value / 2 + 1;\n    while (low < high) {\n        T middle = low + (high -\
    \ low + 1) / 2;\n        if (middle <= value / middle) {\n            low = middle;\n\
    \        } else {\n            high = middle - 1;\n        }\n    }\n    return\
    \ low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
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
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_MODULAR_KTH_ROOT_HPP\n#define M1UNE_MATH_MODULAR_KTH_ROOT_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <numeric>\n#include <optional>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"integer_arithmetic.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
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
    \  // namespace m1une\n\n#endif  // M1UNE_MATH_MODULAR_KTH_ROOT_HPP\n"
  dependsOn:
  - math/integer_arithmetic.hpp
  isVerificationFile: false
  path: math/modular_kth_root.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-16 21:30:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/modular_kth_root.test.cpp
documentation_of: math/modular_kth_root.hpp
layout: document
title: Modular Kth Root
---

## Overview

`modular_kth_root` solves

$$
x^k \equiv a \pmod p
$$

for a prime modulus $p$. It returns any valid root, or `std::nullopt` when no
root exists. The implementation reduces the exponent by
$\gcd(k,p-1)$ and extracts its prime-power factors with a generalized
Tonelli--Shanks algorithm.

## Interface

```cpp
std::optional<uint64_t> modular_kth_root(
    uint64_t value,
    uint64_t degree,
    uint64_t prime
);

template <class Mint>
std::optional<Mint> modular_kth_root(
    Mint value,
    uint64_t degree
);
```

| Function | Description |
| --- | --- |
| `modular_kth_root(value, degree, prime)` | Reduces `value` modulo `prime` and returns any kth root. |
| `modular_kth_root(value, degree)` | Uses `Mint::mod()` and returns the root as `Mint`. |

`prime` must be at least `2` and prime; primality is not tested. The modular
integer overload requires `val()`, static `mod()`, and construction from an
integer.

For `degree == 0`, exponentiation follows the convention $x^0=1$, including
$0^0=1$. The function therefore returns `0` when `value` is congruent to `1`
and no result otherwise. For positive degree, zero has root zero.

The answer is not canonical when several roots exist.

## Complexity

Let $g=\gcd(k,p-1)$. Factoring $g$ by trial division takes $O(\sqrt g)$
integer operations. For a prime factor $q^e$ of $g$, write
$p-1=mq^s$. Its generalized Tonelli--Shanks correction uses
$O(\sqrt{(s-e)q})$ stored group elements and $s-e$ correction rounds, plus a
search for a q-th non-residue. Every modular exponentiation costs $O(\log p)$
modular multiplications.

This is designed for the common competitive-programming regime of many prime
moduli up to about $10^9$ and avoids a full discrete logarithm per query.

## Example

```cpp
#include "math/modular_kth_root.hpp"

#include <cassert>

int main() {
    auto root = m1une::math::modular_kth_root(8, 3, 13);
    assert(root.has_value());
    assert(*root * *root % 13 * *root % 13 == 8);

    assert(!m1une::math::modular_kth_root(3, 2, 7).has_value());
}
```
