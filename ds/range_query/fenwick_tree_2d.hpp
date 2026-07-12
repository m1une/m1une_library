#ifndef M1UNE_DS_FENWICK_TREE_2D_HPP
#define M1UNE_DS_FENWICK_TREE_2D_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <class T, class X = int, class Y = X>
class FenwickTree2D {
   public:
    using value_type = T;
    using point_type = std::pair<X, Y>;
    using weighted_point_type = std::tuple<X, Y, T>;

   private:
    std::vector<point_type> _points;
    std::vector<X> _xs;
    std::vector<std::vector<Y>> _ys;
    std::vector<std::vector<T>> _data;

    static std::vector<point_type> normalize_points(
        std::vector<point_type> points
    ) {
        std::sort(points.begin(), points.end());
        points.erase(std::unique(points.begin(), points.end()), points.end());
        return points;
    }

    T prefix_sum_by_x_count(int x_count, const Y& y_upper) const {
        T result{};
        for (int x_index = x_count; x_index > 0; x_index -= x_index & -x_index) {
            const std::vector<Y>& ys = _ys[std::size_t(x_index)];
            int y_index = int(
                std::lower_bound(ys.begin(), ys.end(), y_upper) - ys.begin()
            );
            const std::vector<T>& data = _data[std::size_t(x_index)];
            while (y_index > 0) {
                result += data[std::size_t(y_index)];
                y_index -= y_index & -y_index;
            }
        }
        return result;
    }

    T prefix_sum(const X& x_upper, const Y& y_upper) const {
        const int x_count = int(
            std::lower_bound(_xs.begin(), _xs.end(), x_upper) - _xs.begin()
        );
        return prefix_sum_by_x_count(x_count, y_upper);
    }

   public:
    FenwickTree2D() : _ys(1), _data(1) {}

    explicit FenwickTree2D(std::vector<point_type> points) {
        build(std::move(points));
    }

    explicit FenwickTree2D(
        const std::vector<weighted_point_type>& points
    ) {
        build(points);
    }

    void build(std::vector<point_type> points) {
        _points = normalize_points(std::move(points));
        _xs.clear();
        _xs.reserve(_points.size());
        for (const auto& [x, y] : _points) {
            (void)y;
            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);
        }

        const int x_size = int(_xs.size());
        _ys.assign(std::size_t(x_size + 1), {});
        for (const auto& [x, y] : _points) {
            int x_index = int(
                std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()
            ) + 1;
            while (x_index <= x_size) {
                _ys[std::size_t(x_index)].push_back(y);
                x_index += x_index & -x_index;
            }
        }

        _data.assign(std::size_t(x_size + 1), {});
        for (int x_index = 1; x_index <= x_size; x_index++) {
            std::vector<Y>& ys = _ys[std::size_t(x_index)];
            std::sort(ys.begin(), ys.end());
            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
            _data[std::size_t(x_index)].assign(ys.size() + 1, T{});
        }
    }

    void build(const std::vector<weighted_point_type>& points) {
        std::vector<point_type> coordinates;
        coordinates.reserve(points.size());
        for (const auto& [x, y, value] : points) {
            (void)value;
            coordinates.emplace_back(x, y);
        }
        build(std::move(coordinates));
        for (const auto& [x, y, value] : points) add(x, y, value);
    }

    int size() const {
        return int(_points.size());
    }

    bool empty() const {
        return _points.empty();
    }

    int x_size() const {
        return int(_xs.size());
    }

    const std::vector<X>& xs() const {
        return _xs;
    }

    bool contains_point(const X& x, const Y& y) const {
        return std::binary_search(_points.begin(), _points.end(), point_type(x, y));
    }

    void add(const X& x, const Y& y, const T& value) {
        assert(contains_point(x, y));
        int x_index = int(
            std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()
        ) + 1;
        while (x_index <= int(_xs.size())) {
            const std::vector<Y>& ys = _ys[std::size_t(x_index)];
            int y_index = int(
                std::lower_bound(ys.begin(), ys.end(), y) - ys.begin()
            ) + 1;
            std::vector<T>& data = _data[std::size_t(x_index)];
            while (y_index < int(data.size())) {
                data[std::size_t(y_index)] += value;
                y_index += y_index & -y_index;
            }
            x_index += x_index & -x_index;
        }
    }

    T sum(const X& x_upper, const Y& y_upper) const {
        return prefix_sum(x_upper, y_upper);
    }

    T sum(
        const X& x_lower,
        const X& x_upper,
        const Y& y_lower,
        const Y& y_upper
    ) const {
        assert(!(x_upper < x_lower));
        assert(!(y_upper < y_lower));
        return prefix_sum(x_upper, y_upper) -
               prefix_sum(x_lower, y_upper) -
               prefix_sum(x_upper, y_lower) +
               prefix_sum(x_lower, y_lower);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_FENWICK_TREE_2D_HPP
