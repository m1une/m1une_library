#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "../../math/gaussian_integer.hpp"
#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <limits>
#include <tuple>

namespace {

using Gaussian = m1une::math::GaussianInteger<long long>;

constexpr bool compile_time_tests() {
    constexpr Gaussian first(5, 7);
    constexpr Gaussian second(2, -1);
    static_assert(first + second == Gaussian(7, 6));
    static_assert(first - second == Gaussian(3, 8));
    static_assert(first * second == Gaussian(17, 9));
    static_assert(first.conjugate() == Gaussian(5, -7));
    static_assert(first.norm() == 74);
    static_assert(Gaussian(0, 1).is_unit());
    static_assert(!Gaussian(1, 1).is_unit());

    constexpr auto division = first.divmod(second);
    static_assert(division.first * second + division.second == first);
    static_assert(division.second.norm() < second.norm());

    static_assert(Gaussian(2, 3).normalized() == Gaussian(2, 3));
    static_assert(Gaussian(2, -3).normalized() == Gaussian(3, 2));
    static_assert(Gaussian(-2, -3).normalized() == Gaussian(2, 3));
    static_assert(Gaussian(-2, 3).normalized() == Gaussian(3, 2));
    static_assert(Gaussian(0, 4).normalized() == Gaussian(4, 0));
    static_assert(Gaussian(0, -4).normalized() == Gaussian(4, 0));
    return true;
}

static_assert(compile_time_tests());

void test_division() {
    const long long minimum = std::numeric_limits<long long>::min();
    const Gaussian extreme(minimum, minimum);
    assert(extreme.norm() == (__uint128_t(1) << 127));
    const auto extreme_division = Gaussian(minimum, 0).divmod(Gaussian(1, 0));
    assert(extreme_division.first == Gaussian(minimum, 0));
    assert(extreme_division.second.is_zero());

    for (long long first_real = -12; first_real <= 12; first_real++) {
        for (long long first_imag = -12; first_imag <= 12; first_imag++) {
            const Gaussian first(first_real, first_imag);
            for (long long second_real = -5; second_real <= 5; second_real++) {
                for (long long second_imag = -5; second_imag <= 5; second_imag++) {
                    const Gaussian second(second_real, second_imag);
                    if (second.is_zero()) continue;
                    const auto [quotient, remainder] = first.divmod(second);
                    assert(quotient * second + remainder == first);
                    assert(remainder.norm() < second.norm());
                    assert(first / second == quotient);
                    assert(first % second == remainder);
                    assert(m1une::math::gaussian_divides(second, first) ==
                           remainder.is_zero());
                }
            }
        }
    }
}

void test_gcd() {
    std::uint64_t state = UINT64_C(0x84a71c39d5e602fb);
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    const Gaussian units[4] = {
        Gaussian(1, 0),
        Gaussian(0, 1),
        Gaussian(-1, 0),
        Gaussian(0, -1)
    };

    for (int trial = 0; trial < 10000; trial++) {
        const Gaussian first(
            static_cast<long long>(random() % 2000001) - 1000000,
            static_cast<long long>(random() % 2000001) - 1000000
        );
        const Gaussian second(
            static_cast<long long>(random() % 2000001) - 1000000,
            static_cast<long long>(random() % 2000001) - 1000000
        );

        const Gaussian gcd = m1une::math::gaussian_gcd(first, second);
        assert(gcd.is_zero() || (0 < gcd.real && 0 <= gcd.imag));
        assert(m1une::math::gaussian_divides(gcd, first));
        assert(m1une::math::gaussian_divides(gcd, second));

        const auto [extended_gcd, first_coefficient, second_coefficient] =
            m1une::math::extended_gaussian_gcd(first, second);
        assert(extended_gcd == gcd);
        assert(first * first_coefficient + second * second_coefficient == gcd);

        const Gaussian first_unit = units[random() % 4];
        const Gaussian second_unit = units[random() % 4];
        assert(m1une::math::gaussian_gcd(
                   first * first_unit,
                   second * second_unit
               ) == gcd);
        assert(m1une::math::gaussian_associates(gcd, gcd * first_unit));

        if (trial < 1000) {
            for (long long real = -5; real <= 5; real++) {
                for (long long imag = -5; imag <= 5; imag++) {
                    const Gaussian divisor(real, imag);
                    if (m1une::math::gaussian_divides(divisor, first) &&
                        m1une::math::gaussian_divides(divisor, second)) {
                        assert(m1une::math::gaussian_divides(divisor, gcd));
                    }
                }
            }
        }
    }

    const Gaussian zero;
    assert(m1une::math::gaussian_gcd(zero, zero) == zero);
    assert(m1une::math::gaussian_divides(zero, zero));
    assert(!m1une::math::gaussian_divides(zero, Gaussian(1)));
}

}  // namespace

int main() {
    test_division();
    test_gcd();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        long long first_real, first_imag, second_real, second_imag;
        fast_input >> first_real >> first_imag >> second_real >> second_imag;
        const Gaussian gcd = m1une::math::gaussian_gcd(
            Gaussian(first_real, first_imag),
            Gaussian(second_real, second_imag)
        );
        fast_output << gcd.real << ' ' << gcd.imag << '\n';
    }
}
