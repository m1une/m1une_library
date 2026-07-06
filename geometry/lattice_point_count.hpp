#ifndef M1UNE_GEOMETRY_LATTICE_POINT_COUNT_HPP
#define M1UNE_GEOMETRY_LATTICE_POINT_COUNT_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

namespace m1une {
namespace geometry {

template <class T>
struct LinearInequality {
    T a;
    T b;
    T c;
};

namespace lattice_point_count_detail {

using Integer = boost::multiprecision::int256_t;

struct Fraction {
    Integer numerator = 0;
    Integer denominator = 1;

    Fraction() = default;

    Fraction(Integer numerator_value, Integer denominator_value)
        : numerator(numerator_value), denominator(denominator_value) {
        assert(denominator != 0);
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
};

inline bool operator<(const Fraction& left, const Fraction& right) {
    return left.numerator * right.denominator <
           right.numerator * left.denominator;
}

inline bool operator==(const Fraction& left, const Fraction& right) {
    return left.numerator * right.denominator ==
           right.numerator * left.denominator;
}

inline bool operator<=(const Fraction& left, const Fraction& right) {
    return !(right < left);
}

struct Bound {
    // -1 is negative infinity, 0 is finite, and 1 is positive infinity.
    int infinity = 0;
    Fraction value;

    static Bound negative_infinity() {
        Bound result;
        result.infinity = -1;
        return result;
    }

    static Bound positive_infinity() {
        Bound result;
        result.infinity = 1;
        return result;
    }

    static Bound finite(const Fraction& fraction) {
        Bound result;
        result.value = fraction;
        return result;
    }
};

inline bool operator<(const Bound& left, const Bound& right) {
    if (left.infinity != right.infinity) {
        return left.infinity < right.infinity;
    }
    if (left.infinity != 0) return false;
    return left.value < right.value;
}

inline bool operator==(const Bound& left, const Bound& right) {
    if (left.infinity != right.infinity) return false;
    return left.infinity != 0 || left.value == right.value;
}

inline bool operator<=(const Bound& left, const Bound& right) {
    return !(right < left);
}

inline Bound maximum(const Bound& left, const Bound& right) {
    return left < right ? right : left;
}

inline Bound minimum(const Bound& left, const Bound& right) {
    return right < left ? right : left;
}

struct Line {
    // Represents (slope_numerator * x + intercept_numerator) / denominator.
    Integer slope_numerator;
    Integer intercept_numerator;
    Integer denominator;
};

inline bool slope_less(const Line& left, const Line& right) {
    return left.slope_numerator * right.denominator <
           right.slope_numerator * left.denominator;
}

inline bool same_slope(const Line& left, const Line& right) {
    return left.slope_numerator * right.denominator ==
           right.slope_numerator * left.denominator;
}

inline bool intercept_less(const Line& left, const Line& right) {
    return left.intercept_numerator * right.denominator <
           right.intercept_numerator * left.denominator;
}

inline Fraction intersection(const Line& left, const Line& right) {
    Integer numerator =
        left.intercept_numerator * right.denominator -
        right.intercept_numerator * left.denominator;
    Integer denominator =
        right.slope_numerator * left.denominator -
        left.slope_numerator * right.denominator;
    assert(denominator > 0);
    return Fraction(numerator, denominator);
}

struct Envelope {
    std::vector<Line> lines;
    // starts[i] is the finite x-coordinate where lines[i] becomes maximal.
    // starts[0] is unused because lines[0] starts at negative infinity.
    std::vector<Fraction> starts;
};

inline Envelope maximum_envelope(std::vector<Line> lines) {
    std::sort(
        lines.begin(),
        lines.end(),
        [](const Line& left, const Line& right) {
            if (!same_slope(left, right)) return slope_less(left, right);
            return intercept_less(right, left);
        }
    );

    std::vector<Line> unique;
    for (const Line& line : lines) {
        if (unique.empty() || !same_slope(unique.back(), line)) {
            unique.push_back(line);
        }
    }

    Envelope result;
    for (const Line& line : unique) {
        Fraction start;
        while (!result.lines.empty()) {
            start = intersection(result.lines.back(), line);
            if (
                result.lines.size() == 1 ||
                result.starts.back() < start
            ) {
                break;
            }
            result.lines.pop_back();
            result.starts.pop_back();
        }
        result.lines.push_back(line);
        if (result.lines.size() == 1) {
            result.starts.emplace_back();
        } else {
            result.starts.push_back(start);
        }
    }
    return result;
}

inline Bound segment_start(const Envelope& envelope, std::size_t index) {
    if (index == 0) return Bound::negative_infinity();
    return Bound::finite(envelope.starts[index]);
}

inline Bound segment_end(const Envelope& envelope, std::size_t index) {
    if (index + 1 == envelope.lines.size()) {
        return Bound::positive_infinity();
    }
    return Bound::finite(envelope.starts[index + 1]);
}

inline Integer floor_div(Integer numerator, const Integer& denominator) {
    assert(denominator > 0);
    Integer quotient = numerator / denominator;
    Integer remainder = numerator % denominator;
    if (remainder < 0) --quotient;
    return quotient;
}

inline Integer ceil_div(Integer numerator, const Integer& denominator) {
    return -floor_div(-numerator, denominator);
}

inline Integer floor_sum(
    Integer count,
    Integer modulus,
    Integer multiplier,
    Integer constant
) {
    assert(count >= 0);
    assert(modulus > 0);

    Integer answer = 0;
    Integer quotient = floor_div(multiplier, modulus);
    answer += quotient * count * (count - 1) / 2;
    multiplier -= quotient * modulus;

    quotient = floor_div(constant, modulus);
    answer += quotient * count;
    constant -= quotient * modulus;

    while (true) {
        if (multiplier >= modulus) {
            answer += count * (count - 1) / 2 * (multiplier / modulus);
            multiplier %= modulus;
        }
        if (constant >= modulus) {
            answer += count * (constant / modulus);
            constant %= modulus;
        }

        Integer maximum = multiplier * count + constant;
        if (maximum < modulus) break;
        count = maximum / modulus;
        constant = maximum % modulus;
        std::swap(modulus, multiplier);
    }
    return answer;
}

inline std::pair<Bound, Bound> feasible_projection(
    const Envelope& lower,
    const Envelope& negative_upper,
    Bound domain_lower,
    Bound domain_upper,
    bool& feasible
) {
    Bound result_lower = Bound::positive_infinity();
    Bound result_upper = Bound::negative_infinity();
    std::size_t lower_index = 0;
    std::size_t upper_index = 0;

    while (
        lower_index < lower.lines.size() &&
        upper_index < negative_upper.lines.size()
    ) {
        Bound lower_end = segment_end(lower, lower_index);
        Bound upper_end = segment_end(negative_upper, upper_index);
        Bound left = maximum(
            maximum(
                segment_start(lower, lower_index),
                segment_start(negative_upper, upper_index)
            ),
            domain_lower
        );
        Bound right = minimum(minimum(lower_end, upper_end), domain_upper);

        const Line& lower_line = lower.lines[lower_index];
        const Line& upper_line = negative_upper.lines[upper_index];
        Integer slope =
            lower_line.slope_numerator * upper_line.denominator +
            upper_line.slope_numerator * lower_line.denominator;
        Integer intercept =
            lower_line.intercept_numerator * upper_line.denominator +
            upper_line.intercept_numerator * lower_line.denominator;

        if (slope > 0) {
            right = minimum(
                right,
                Bound::finite(Fraction(-intercept, slope))
            );
        } else if (slope < 0) {
            left = maximum(
                left,
                Bound::finite(Fraction(-intercept, slope))
            );
        } else if (intercept > 0) {
            left = Bound::positive_infinity();
            right = Bound::negative_infinity();
        }

        if (left <= right) {
            if (!feasible) {
                result_lower = left;
                result_upper = right;
                feasible = true;
            } else {
                result_lower = minimum(result_lower, left);
                result_upper = maximum(result_upper, right);
            }
        }

        if (lower_end == upper_end) {
            ++lower_index;
            ++upper_index;
        } else if (lower_end < upper_end) {
            ++lower_index;
        } else {
            ++upper_index;
        }
    }
    return {result_lower, result_upper};
}

inline Integer sum_floor_of_negative(
    const Envelope& envelope,
    Integer first_x,
    Integer last_x
) {
    Integer answer = 0;
    for (std::size_t index = 0; index < envelope.lines.size(); ++index) {
        Integer left = first_x;
        Integer right = last_x;
        if (index > 0) {
            left = std::max(
                left,
                ceil_div(
                    envelope.starts[index].numerator,
                    envelope.starts[index].denominator
                )
            );
        }
        if (index + 1 < envelope.lines.size()) {
            right = std::min(
                right,
                ceil_div(
                    envelope.starts[index + 1].numerator,
                    envelope.starts[index + 1].denominator
                ) - 1
            );
        }
        if (right < left) continue;

        const Line& line = envelope.lines[index];
        Integer count = right - left + 1;
        Integer multiplier = -line.slope_numerator;
        Integer constant = -line.intercept_numerator + multiplier * left;
        answer += floor_sum(
            count,
            line.denominator,
            multiplier,
            constant
        );
    }
    return answer;
}

}  // namespace lattice_point_count_detail

// Counts integer pairs (x, y) satisfying every closed inequality
// a * x + b * y <= c. The real feasible region must be bounded.
template <class T>
__int128_t count_lattice_points(
    const std::vector<LinearInequality<T>>& inequalities
) {
    static_assert(
        std::is_integral_v<T> && std::is_signed_v<T> && sizeof(T) <= 8,
        "count_lattice_points requires a signed integer type of at most 64 bits"
    );
    namespace detail = lattice_point_count_detail;
    using detail::Bound;
    using detail::Envelope;
    using detail::Fraction;
    using detail::Integer;
    using detail::Line;

    std::vector<Line> lower_lines;
    std::vector<Line> negative_upper_lines;
    Bound domain_lower = Bound::negative_infinity();
    Bound domain_upper = Bound::positive_infinity();

    for (const LinearInequality<T>& inequality : inequalities) {
        Integer a = inequality.a;
        Integer b = inequality.b;
        Integer c = inequality.c;
        if (b < 0) {
            lower_lines.push_back(Line{a, -c, -b});
        } else if (b > 0) {
            negative_upper_lines.push_back(Line{a, -c, b});
        } else if (a > 0) {
            domain_upper = detail::minimum(
                domain_upper,
                Bound::finite(Fraction(c, a))
            );
        } else if (a < 0) {
            domain_lower = detail::maximum(
                domain_lower,
                Bound::finite(Fraction(c, a))
            );
        } else if (c < 0) {
            return 0;
        }
    }

    if (domain_upper < domain_lower) return 0;
    // Without both y-envelopes, every feasible x-column is unbounded.
    assert(!lower_lines.empty() && !negative_upper_lines.empty());

    Envelope lower = detail::maximum_envelope(std::move(lower_lines));
    Envelope negative_upper =
        detail::maximum_envelope(std::move(negative_upper_lines));

    bool feasible = false;
    auto projection = detail::feasible_projection(
        lower,
        negative_upper,
        domain_lower,
        domain_upper,
        feasible
    );
    if (!feasible) return 0;
    assert(projection.first.infinity == 0);
    assert(projection.second.infinity == 0);

    Integer first_x = detail::ceil_div(
        projection.first.value.numerator,
        projection.first.value.denominator
    );
    Integer last_x = detail::floor_div(
        projection.second.value.numerator,
        projection.second.value.denominator
    );
    if (last_x < first_x) return 0;
    assert(first_x >= std::numeric_limits<long long>::min());
    assert(first_x <= std::numeric_limits<long long>::max());
    assert(last_x >= std::numeric_limits<long long>::min());
    assert(last_x <= std::numeric_limits<long long>::max());

    Integer answer = last_x - first_x + 1;
    answer += detail::sum_floor_of_negative(
        negative_upper,
        first_x,
        last_x
    );
    answer += detail::sum_floor_of_negative(lower, first_x, last_x);

    assert(answer >= 0);
    assert(answer <= (Integer(1) << 127) - 1);
    return static_cast<__int128_t>(answer);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_LATTICE_POINT_COUNT_HPP
