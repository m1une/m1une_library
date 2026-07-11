#ifndef M1UNE_STATIC_RECTANGLE_SUM_HPP
#define M1UNE_STATIC_RECTANGLE_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

#include "wavelet_matrix_sum.hpp"

namespace m1une {
namespace ds {

template <class X, class Y = X, class Sum = long long>
class StaticRectangleSum {
   public:
    using x_type = X;
    using y_type = Y;
    using sum_type = Sum;
    using weighted_point_type = std::tuple<X, Y, Sum>;

   private:
    std::vector<X> _x_coordinates;
    std::vector<Y> _y_coordinates;
    WaveletMatrixSum<int, Sum> _matrix;

   public:
    StaticRectangleSum() = default;

    explicit StaticRectangleSum(
        const std::vector<weighted_point_type>& points
    ) {
        build(points);
    }

    StaticRectangleSum(
        const std::vector<X>& x_coordinates,
        const std::vector<Y>& y_coordinates,
        const std::vector<Sum>& weights
    ) {
        build(x_coordinates, y_coordinates, weights);
    }

    void build(std::vector<weighted_point_type> points) {
        std::sort(
            points.begin(),
            points.end(),
            [](const weighted_point_type& first,
               const weighted_point_type& second) {
                if (std::get<0>(first) < std::get<0>(second)) return true;
                if (std::get<0>(second) < std::get<0>(first)) return false;
                return std::get<1>(first) < std::get<1>(second);
            }
        );

        const int n = int(points.size());
        _x_coordinates.resize(n);
        _y_coordinates.clear();
        _y_coordinates.reserve(n);
        for (const auto& point : points) {
            _y_coordinates.push_back(std::get<1>(point));
        }
        std::sort(_y_coordinates.begin(), _y_coordinates.end());
        _y_coordinates.erase(
            std::unique(
                _y_coordinates.begin(),
                _y_coordinates.end(),
                [](const Y& first, const Y& second) {
                    return !(first < second) && !(second < first);
                }
            ),
            _y_coordinates.end()
        );

        std::vector<int> y_rank(n);
        std::vector<Sum> weights(n);
        for (int index = 0; index < n; index++) {
            _x_coordinates[index] = std::get<0>(points[index]);
            y_rank[index] = int(
                std::lower_bound(
                    _y_coordinates.begin(),
                    _y_coordinates.end(),
                    std::get<1>(points[index])
                ) - _y_coordinates.begin()
            );
            weights[index] = std::get<2>(points[index]);
        }
        _matrix = WaveletMatrixSum<int, Sum>(y_rank, weights);
    }

    void build(
        const std::vector<X>& x_coordinates,
        const std::vector<Y>& y_coordinates,
        const std::vector<Sum>& weights
    ) {
        assert(x_coordinates.size() == y_coordinates.size());
        assert(x_coordinates.size() == weights.size());
        std::vector<weighted_point_type> points;
        points.reserve(x_coordinates.size());
        for (int index = 0; index < int(x_coordinates.size()); index++) {
            points.emplace_back(
                x_coordinates[index],
                y_coordinates[index],
                weights[index]
            );
        }
        build(std::move(points));
    }

    int size() const {
        return int(_x_coordinates.size());
    }

    bool empty() const {
        return _x_coordinates.empty();
    }

    Sum sum(
        const X& left,
        const X& right,
        const Y& lower,
        const Y& upper
    ) const {
        assert(!(right < left));
        assert(!(upper < lower));
        int x_left = int(
            std::lower_bound(
                _x_coordinates.begin(),
                _x_coordinates.end(),
                left
            ) - _x_coordinates.begin()
        );
        int x_right = int(
            std::lower_bound(
                _x_coordinates.begin(),
                _x_coordinates.end(),
                right
            ) - _x_coordinates.begin()
        );
        int y_lower = int(
            std::lower_bound(
                _y_coordinates.begin(),
                _y_coordinates.end(),
                lower
            ) - _y_coordinates.begin()
        );
        int y_upper = int(
            std::lower_bound(
                _y_coordinates.begin(),
                _y_coordinates.end(),
                upper
            ) - _y_coordinates.begin()
        );
        return _matrix.range_sum(x_left, x_right, y_lower, y_upper);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_STATIC_RECTANGLE_SUM_HPP
