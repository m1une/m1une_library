#ifndef M1UNE_MATH_GENERALIZED_FLOOR_SUM_HPP
#define M1UNE_MATH_GENERALIZED_FLOOR_SUM_HPP 1

#include <array>
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace m1une {
namespace math {

template <class T, int MaxPower, int MaxFloorPower>
using GeneralizedFloorSumTable =
    std::array<std::array<T, MaxFloorPower + 1>, MaxPower + 1>;

namespace generalized_floor_sum_detail {

using SignedWide = __int128_t;
using UnsignedWide = __uint128_t;

template <class T>
T from_wide(SignedWide value) {
    bool negative = value < 0;
    UnsignedWide magnitude;
    if (negative) {
        magnitude = static_cast<UnsignedWide>(-(value + 1));
        ++magnitude;
    } else {
        magnitude = static_cast<UnsignedWide>(value);
    }

    T result = T();
    T binary_place = T(1);
    while (magnitude > 0) {
        if ((magnitude & 1) != 0) result += binary_place;
        magnitude >>= 1;
        if (magnitude > 0) binary_place += binary_place;
    }
    return negative ? T() - result : result;
}

inline SignedWide floor_div(SignedWide numerator, SignedWide denominator) {
    assert(denominator > 0);
    SignedWide quotient = numerator / denominator;
    if (numerator % denominator < 0) --quotient;
    return quotient;
}

template <class T, int MaxPower, int MaxFloorPower>
class MomentMonoid {
   public:
    using Table = GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>;

    struct Data {
        Table sums{};
        T delta_x = T();
        T delta_y = T();
    };

    static constexpr int MaximumDegree =
        MaxPower > MaxFloorPower ? MaxPower : MaxFloorPower;

    MomentMonoid() {
        binomial_[0][0] = T(1);
        for (int degree = 0; degree < MaximumDegree; ++degree) {
            for (int index = 0; index <= degree; ++index) {
                binomial_[degree + 1][index] += binomial_[degree][index];
                binomial_[degree + 1][index + 1] +=
                    binomial_[degree][index];
            }
        }
    }

    const T& binomial(int n, int k) const {
        assert(0 <= k && k <= n && n <= MaximumDegree);
        return binomial_[n][k];
    }

    Data unit() const {
        return Data();
    }

    Data x_step() const {
        Data result;
        result.sums[0][0] = T(1);
        result.delta_x = T(1);
        return result;
    }

    Data y_step() const {
        Data result;
        result.delta_y = T(1);
        return result;
    }

    Data concatenate(Data left, Data right) const {
        std::array<T, MaxPower + 1> x_powers{};
        std::array<T, MaxFloorPower + 1> y_powers{};
        x_powers[0] = T(1);
        y_powers[0] = T(1);
        for (int power = 0; power < MaxPower; ++power) {
            x_powers[power + 1] = x_powers[power] * left.delta_x;
        }
        for (int power = 0; power < MaxFloorPower; ++power) {
            y_powers[power + 1] = y_powers[power] * left.delta_y;
        }

        // Shift the y-coordinate of every sampled x-step in the right path.
        for (int x_power = 0; x_power <= MaxPower; ++x_power) {
            for (int old_power = MaxFloorPower; old_power >= 0; --old_power) {
                T source = right.sums[x_power][old_power];
                for (int new_power = old_power + 1;
                     new_power <= MaxFloorPower;
                     ++new_power) {
                    right.sums[x_power][new_power] +=
                        binomial_[new_power][old_power] *
                        y_powers[new_power - old_power] * source;
                }
            }
        }

        // Shift x, then append all samples from the right path.
        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power) {
            for (int old_power = 0; old_power <= MaxPower; ++old_power) {
                T source = right.sums[old_power][y_power];
                for (int new_power = old_power;
                     new_power <= MaxPower;
                     ++new_power) {
                    left.sums[new_power][y_power] +=
                        binomial_[new_power][old_power] *
                        x_powers[new_power - old_power] * source;
                }
            }
        }

        left.delta_x += right.delta_x;
        left.delta_y += right.delta_y;
        return left;
    }

   private:
    std::array<std::array<T, MaximumDegree + 1>, MaximumDegree + 1>
        binomial_{};
};

template <class Monoid>
typename Monoid::Data monoid_power(
    const Monoid& monoid,
    typename Monoid::Data base,
    UnsignedWide exponent
) {
    typename Monoid::Data result = monoid.unit();
    while (exponent > 0) {
        if ((exponent & 1) != 0) {
            result = monoid.concatenate(std::move(result), base);
        }
        exponent >>= 1;
        if (exponent > 0) {
            base = monoid.concatenate(base, base);
        }
    }
    return result;
}

template <class Monoid>
typename Monoid::Data floor_path_product(
    const Monoid& monoid,
    UnsignedWide n,
    UnsignedWide a,
    UnsignedWide b,
    UnsignedWide modulus
) {
    assert(modulus > 0);
    UnsignedWide height = (a * n + b) / modulus;
    typename Monoid::Data x = monoid.x_step();
    typename Monoid::Data y = monoid.y_step();
    typename Monoid::Data prefix = monoid.unit();
    typename Monoid::Data suffix = monoid.unit();

    while (true) {
        UnsignedWide slope_quotient = a / modulus;
        UnsignedWide intercept_quotient = b / modulus;
        a %= modulus;
        b %= modulus;

        x = monoid.concatenate(
            std::move(x),
            monoid_power(monoid, y, slope_quotient)
        );
        prefix = monoid.concatenate(
            std::move(prefix),
            monoid_power(monoid, y, intercept_quotient)
        );
        height -= slope_quotient * n + intercept_quotient;
        if (height == 0) break;

        assert(a > 0);
        UnsignedWide boundary =
            (modulus * height - b - 1) / a + 1;
        suffix = monoid.concatenate(
            y,
            monoid.concatenate(
                monoid_power(monoid, x, n - boundary),
                std::move(suffix)
            )
        );
        b = modulus - b - 1 + a;
        n = height - 1;
        height = boundary;
        std::swap(modulus, a);
        std::swap(x, y);
    }

    x = monoid_power(monoid, x, n);
    return monoid.concatenate(
        monoid.concatenate(std::move(prefix), std::move(x)),
        std::move(suffix)
    );
}

template <class T, int MaxPower, int MaxFloorPower>
GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>
nonnegative_slope_table(
    const MomentMonoid<T, MaxPower, MaxFloorPower>& monoid,
    SignedWide n,
    SignedWide modulus,
    SignedWide a,
    SignedWide b
) {
    assert(n >= 0 && modulus > 0 && a >= 0);
    SignedWide y_offset = floor_div(b, modulus);
    SignedWide normalized_b = b - y_offset * modulus;

    auto path = floor_path_product(
        monoid,
        static_cast<UnsignedWide>(n),
        static_cast<UnsignedWide>(a),
        static_cast<UnsignedWide>(normalized_b),
        static_cast<UnsignedWide>(modulus)
    );

    std::array<T, MaxFloorPower + 1> offset_powers{};
    offset_powers[0] = T(1);
    T offset = from_wide<T>(y_offset);
    for (int power = 0; power < MaxFloorPower; ++power) {
        offset_powers[power + 1] = offset_powers[power] * offset;
    }

    GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower> result{};
    for (int x_power = 0; x_power <= MaxPower; ++x_power) {
        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power) {
            for (int inner_power = 0;
                 inner_power <= y_power;
                 ++inner_power) {
                result[x_power][y_power] +=
                    monoid.binomial(y_power, inner_power) *
                    offset_powers[y_power - inner_power] *
                    path.sums[x_power][inner_power];
            }
        }
    }
    return result;
}

}  // namespace generalized_floor_sum_detail

// Returns every sum of x^p * floor((a*x+b)/mod)^q for 0 <= x < n,
// 0 <= p <= MaxPower, and 0 <= q <= MaxFloorPower.
template <class T, int MaxPower, int MaxFloorPower, class I>
GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>
generalized_floor_sum_table(I n, I mod, I a, I b) {
    static_assert(MaxPower >= 0 && MaxFloorPower >= 0);
    static_assert(
        std::is_integral_v<I> && std::is_signed_v<I> && sizeof(I) <= 8,
        "generalized_floor_sum_table requires signed integer arguments"
    );
    assert(n >= 0);
    assert(mod > 0);

    namespace detail = generalized_floor_sum_detail;
    using Monoid = detail::MomentMonoid<T, MaxPower, MaxFloorPower>;
    static const Monoid monoid;

    detail::SignedWide wide_n = n;
    detail::SignedWide wide_mod = mod;
    detail::SignedWide wide_a = a;
    detail::SignedWide wide_b = b;
    if (wide_n == 0) {
        return GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>();
    }
    if (wide_a >= 0) {
        return detail::nonnegative_slope_table(
            monoid,
            wide_n,
            wide_mod,
            wide_a,
            wide_b
        );
    }

    // Substitute x = n - 1 - t to make the slope nonnegative.
    auto reflected = detail::nonnegative_slope_table(
        monoid,
        wide_n,
        wide_mod,
        -wide_a,
        wide_a * (wide_n - 1) + wide_b
    );
    std::array<T, MaxPower + 1> offset_powers{};
    offset_powers[0] = T(1);
    T offset = detail::from_wide<T>(wide_n - 1);
    for (int power = 0; power < MaxPower; ++power) {
        offset_powers[power + 1] = offset_powers[power] * offset;
    }

    GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower> result{};
    for (int x_power = 0; x_power <= MaxPower; ++x_power) {
        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power) {
            for (int inner_power = 0;
                 inner_power <= x_power;
                 ++inner_power) {
                T coefficient =
                    monoid.binomial(x_power, inner_power) *
                    offset_powers[x_power - inner_power];
                if ((inner_power & 1) != 0) coefficient = T() - coefficient;
                result[x_power][y_power] +=
                    coefficient * reflected[inner_power][y_power];
            }
        }
    }
    return result;
}

template <class T, int Power, int FloorPower, class I>
T generalized_floor_sum(I n, I mod, I a, I b) {
    return generalized_floor_sum_table<T, Power, FloorPower>(n, mod, a, b)
        [Power][FloorPower];
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_GENERALIZED_FLOOR_SUM_HPP
