#define PROBLEM "https://judge.yosupo.jp/problem/factorization_of_polynomials"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <type_traits>
#include <vector>

#include "../../../math/fps/polynomial_factorization.hpp"
#include "../../../math/modint.hpp"

namespace {

struct DynamicModInt {
   private:
    inline static uint32_t modulus_ = 2;
    uint32_t value_ = 0;

   public:
    static void set_mod(uint32_t modulus) {
        modulus_ = modulus;
    }

    static uint32_t mod() {
        return modulus_;
    }

    DynamicModInt() = default;

    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
    DynamicModInt(Integer value) {
        if constexpr (std::is_signed_v<Integer>) {
            int64_t reduced = int64_t(value) % int64_t(modulus_);
            if (reduced < 0) reduced += modulus_;
            value_ = uint32_t(reduced);
        } else {
            value_ = uint32_t(uint64_t(value) % modulus_);
        }
    }

    uint32_t val() const {
        return value_;
    }

    DynamicModInt& operator+=(DynamicModInt rhs) {
        value_ += rhs.value_;
        if (value_ >= modulus_) value_ -= modulus_;
        return *this;
    }

    DynamicModInt& operator-=(DynamicModInt rhs) {
        value_ -= rhs.value_;
        if (value_ >= modulus_) value_ += modulus_;
        return *this;
    }

    DynamicModInt& operator*=(DynamicModInt rhs) {
        value_ = uint32_t(uint64_t(value_) * rhs.value_ % modulus_);
        return *this;
    }

    DynamicModInt& operator/=(DynamicModInt rhs) {
        return *this *= rhs.inv();
    }

    DynamicModInt pow(uint64_t exponent) const {
        DynamicModInt result = 1;
        DynamicModInt base = *this;
        while (exponent > 0) {
            if (exponent & 1) result *= base;
            base *= base;
            exponent >>= 1;
        }
        return result;
    }

    DynamicModInt inv() const {
        assert(value_ != 0);
        return pow(modulus_ - 2);
    }

    friend DynamicModInt operator+(DynamicModInt lhs, DynamicModInt rhs) {
        return lhs += rhs;
    }

    friend DynamicModInt operator-(DynamicModInt lhs, DynamicModInt rhs) {
        return lhs -= rhs;
    }

    friend DynamicModInt operator*(DynamicModInt lhs, DynamicModInt rhs) {
        return lhs *= rhs;
    }

    friend DynamicModInt operator/(DynamicModInt lhs, DynamicModInt rhs) {
        return lhs /= rhs;
    }

    friend bool operator==(DynamicModInt lhs, DynamicModInt rhs) {
        return lhs.value_ == rhs.value_;
    }

    friend bool operator!=(DynamicModInt lhs, DynamicModInt rhs) {
        return !(lhs == rhs);
    }
};

template <class Mint>
using Fps = m1une::fps::FormalPowerSeries<Mint>;

template <class Mint>
Fps<Mint> multiply(const Fps<Mint>& first, const Fps<Mint>& second) {
    if (first.empty() || second.empty()) return {};
    Fps<Mint> result(first.size() + second.size() - 1);
    for (int i = 0; i < int(first.size()); i++) {
        for (int j = 0; j < int(second.size()); j++) {
            result[i + j] += first[i] * second[j];
        }
    }
    result.shrink();
    return result;
}

#ifndef NDEBUG
void focused_tests() {
    using Mint = m1une::math::ModInt<17>;
    const Fps<Mint> linear_a({Mint(14), Mint(1)});
    const Fps<Mint> linear_b({Mint(12), Mint(1)});
    const Fps<Mint> quadratic({Mint(3), Mint(0), Mint(1)});

    Fps<Mint> polynomial(1, Mint(7));
    for (int i = 0; i < 3; i++) polynomial = multiply(polynomial, linear_a);
    for (int i = 0; i < 2; i++) polynomial = multiply(polynomial, linear_b);
    polynomial = multiply(polynomial, quadratic);

    auto result = m1une::fps::polynomial_factorize(polynomial);
    assert(result.leading_coefficient == Mint(7));
    assert(result.factors.size() == 3);

    Fps<Mint> restored(1, result.leading_coefficient);
    for (const auto& factor : result.factors) {
        assert(factor.polynomial.back() == Mint(1));
        for (int copy = 0; copy < factor.multiplicity; copy++) {
            restored = multiply(restored, factor.polynomial);
        }
    }
    assert(restored == polynomial);

    auto constant = m1une::fps::polynomial_factorize(Fps<Mint>(1, Mint(11)));
    assert(constant.leading_coefficient == Mint(11));
    assert(constant.factors.empty());

    DynamicModInt::set_mod(2);
    Fps<DynamicModInt> repeated({DynamicModInt(1), DynamicModInt(0),
                                 DynamicModInt(1), DynamicModInt(0),
                                 DynamicModInt(1)});
    auto characteristic_two = m1une::fps::polynomial_factorize(repeated);
    Fps<DynamicModInt> restored_two(1, characteristic_two.leading_coefficient);
    for (const auto& factor : characteristic_two.factors) {
        for (int copy = 0; copy < factor.multiplicity; copy++) {
            restored_two = multiply(restored_two, factor.polynomial);
        }
    }
    assert(restored_two == repeated);
}
#endif

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

#ifndef NDEBUG
    focused_tests();
#endif
    int degree;
    uint32_t prime;
    fast_input >> degree >> prime;
    DynamicModInt::set_mod(prime);

    Fps<DynamicModInt> polynomial(degree + 1);
    for (DynamicModInt& coefficient : polynomial) {
        uint32_t value;
        fast_input >> value;
        coefficient = DynamicModInt(value);
    }

    auto result = m1une::fps::polynomial_factorize(std::move(polynomial));
    fast_output << result.factors.size() << '\n';
    for (const auto& factor : result.factors) {
        fast_output << factor.multiplicity << ' ' << factor.polynomial.size() - 1;
        for (DynamicModInt coefficient : factor.polynomial) {
            fast_output << ' ' << coefficient.val();
        }
        fast_output << '\n';
    }
}
