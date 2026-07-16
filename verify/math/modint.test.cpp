#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <limits>
#include <random>
#include <type_traits>

#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;

static_assert(std::is_constructible_v<mint, signed char>);
static_assert(std::is_constructible_v<mint, unsigned char>);
static_assert(std::is_constructible_v<mint, short>);
static_assert(std::is_constructible_v<mint, unsigned short>);
static_assert(std::is_constructible_v<mint, int>);
static_assert(std::is_constructible_v<mint, unsigned int>);
static_assert(std::is_constructible_v<mint, long>);
static_assert(std::is_constructible_v<mint, unsigned long>);
static_assert(std::is_constructible_v<mint, long long>);
static_assert(std::is_constructible_v<mint, unsigned long long>);

constexpr bool test_constexpr_construction() {
    constexpr std::uint64_t mod = mint::mod();
    constexpr long long signed_value = std::numeric_limits<long long>::min();
    constexpr unsigned long long unsigned_value =
        std::numeric_limits<unsigned long long>::max();

    mint from_signed = signed_value;
    mint from_unsigned = unsigned_value;
    std::int64_t signed_remainder = signed_value % std::int64_t(mod);
    if (signed_remainder < 0) signed_remainder += mod;
    return from_signed.val() == std::uint64_t(signed_remainder) &&
           from_unsigned.val() == unsigned_value % mod;
}

static_assert(test_constexpr_construction());
static_assert(mint(2).pow(-1) * mint(2) == mint(1));
static_assert(mint(2).pow(-3) == mint(8).inv());

void test_integral_construction() {
    assert(mint(-1).val() == mint::mod() - 1);
    assert(mint(std::numeric_limits<unsigned long long>::max()).val() ==
           std::numeric_limits<unsigned long long>::max() % mint::mod());

    std::mt19937 random(123456789);
    mint from_random = random();
    assert(from_random.val() < mint::mod());
    from_random = random() % 100;
    assert(from_random.val() < 100);
}

void test_static_modint_pow() {
    [[maybe_unused]] constexpr long long minimum =
        std::numeric_limits<long long>::min();
    assert(mint(3).pow(-1) * mint(3) == mint(1));
    assert(mint(3).pow(-5) == mint(3).pow(5).inv());
    assert(mint(2).pow(minimum) * mint(2).pow(minimum + 1).inv() ==
           mint(2).inv());
}

void test_dynamic_modint() {
    using dynamic_mint = m1une::math::DynamicModInt<0>;
    using other_dynamic_mint = m1une::math::DynamicModInt<1>;
    dynamic_mint::set_mod(11);
    other_dynamic_mint::set_mod(7);

    assert(dynamic_mint(-1).val() == 10);
    assert((dynamic_mint(8) + dynamic_mint(7)).val() == 4);
    assert((dynamic_mint(8) - dynamic_mint(10)).val() == 9);
    assert((dynamic_mint(8) * dynamic_mint(7)).val() == 1);
    assert(dynamic_mint(3).pow(5).val() == 1);
    assert(dynamic_mint(3).pow(-1).val() == 4);
    assert(dynamic_mint(3).pow(-2).val() == 5);
    [[maybe_unused]] constexpr long long minimum =
        std::numeric_limits<long long>::min();
    assert(dynamic_mint(2).pow(minimum) *
               dynamic_mint(2).pow(minimum + 1).inv() ==
           dynamic_mint(2).inv());
    assert(dynamic_mint(3).inv().val() == 4);
    assert(other_dynamic_mint(8).val() == 1);
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_integral_construction();
    test_static_modint_pow();
    test_dynamic_modint();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
