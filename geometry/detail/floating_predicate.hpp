#ifndef M1UNE_GEOMETRY_DETAIL_FLOATING_PREDICATE_HPP
#define M1UNE_GEOMETRY_DETAIL_FLOATING_PREDICATE_HPP 1

namespace m1une {
namespace geometry {
namespace predicate_detail {

template <typename T>
constexpr T absolute(T value) {
    return value < T(0) ? -value : value;
}

template <typename T>
constexpr T max_value(T first, T second) {
    return first < second ? second : first;
}

template <typename T>
constexpr T vector_scale(T x, T y) {
    return max_value(absolute(x), absolute(y));
}

template <bool Exact, typename T>
constexpr int scaled_sign(T value, T scale, long double eps) {
    if constexpr (Exact) {
        return (value > T(0)) - (value < T(0));
    } else {
        const T tolerance = T(eps) * scale;
        return (value > tolerance) - (value < -tolerance);
    }
}

template <bool Exact, typename T>
constexpr T determinant_scale(T ax, T ay, T bx, T by) {
    if constexpr (Exact) {
        return T(0);
    } else {
        return vector_scale(ax, ay) * vector_scale(bx, by);
    }
}

template <bool Exact, typename T>
constexpr int determinant_sign(
    T ax,
    T ay,
    T bx,
    T by,
    long double eps
) {
    const T determinant = ax * by - ay * bx;
    return scaled_sign<Exact>(
        determinant,
        determinant_scale<Exact>(ax, ay, bx, by),
        eps
    );
}

template <bool Exact, typename T>
constexpr int orientation_sign(
    T direction_x,
    T direction_y,
    T offset_x,
    T offset_y,
    long double eps
) {
    const T determinant =
        direction_x * offset_y - direction_y * offset_x;
    T scale = T(0);
    if constexpr (!Exact) {
        const T direction_scale =
            vector_scale(direction_x, direction_y);
        scale = direction_scale * max_value(
            direction_scale,
            vector_scale(offset_x, offset_y)
        );
    }
    return scaled_sign<Exact>(determinant, scale, eps);
}

template <bool Exact, typename T>
constexpr int dot_sign(
    T ax,
    T ay,
    T bx,
    T by,
    long double eps
) {
    const T value = ax * bx + ay * by;
    T scale = T(0);
    if constexpr (!Exact) {
        scale = vector_scale(ax, ay) * vector_scale(bx, by);
    }
    return scaled_sign<Exact>(value, scale, eps);
}

}  // namespace predicate_detail
}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_DETAIL_FLOATING_PREDICATE_HPP
