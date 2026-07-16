#ifndef M1UNE_OFFLINE_RECTANGLE_ADD_RECTANGLE_SUM_HPP
#define M1UNE_OFFLINE_RECTANGLE_ADD_RECTANGLE_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "fenwick_tree.hpp"

namespace m1une {
namespace ds {

// Records rectangle additions and rectangle-sum queries, then evaluates the
// complete static batch with an offline sweep.
template <class T, class X = long long, class Y = X>
class OfflineRectangleAddRectangleSum {
   public:
    using value_type = T;
    using x_type = X;
    using y_type = Y;

   private:
    struct Update {
        X x_lower;
        X x_upper;
        Y y_lower;
        Y y_upper;
        T value;
    };

    struct Query {
        X x_lower;
        X x_upper;
        Y y_lower;
        Y y_upper;
    };

    struct Coefficient {
        T xy{};
        T x{};
        T y{};
        T constant{};

        Coefficient& operator+=(const Coefficient& other) {
            xy += other.xy;
            x += other.x;
            y += other.y;
            constant += other.constant;
            return *this;
        }
    };

    struct PointEvent {
        X x;
        Y y;
        Coefficient coefficient;
    };

    struct PrefixEvent {
        X x;
        Y y;
        int query_id;
        bool subtract;
    };

    std::vector<Update> _updates;
    std::vector<Query> _queries;

    template <class Coordinate>
    static bool equivalent(const Coordinate& first, const Coordinate& second) {
        return !(first < second) && !(second < first);
    }

    static Coefficient make_coefficient(
        const X& x,
        const Y& y,
        const T& signed_value
    ) {
        const T converted_x(x);
        const T converted_y(y);
        return {
            signed_value,
            T{} - signed_value * converted_y,
            T{} - signed_value * converted_x,
            signed_value * converted_x * converted_y
        };
    }

    static T evaluate(
        const Coefficient& coefficient,
        const X& x,
        const Y& y
    ) {
        const T converted_x(x);
        const T converted_y(y);
        return coefficient.xy * converted_x * converted_y +
               coefficient.x * converted_x +
               coefficient.y * converted_y +
               coefficient.constant;
    }

   public:
    int update_count() const {
        return int(_updates.size());
    }

    int query_count() const {
        return int(_queries.size());
    }

    bool empty() const {
        return _updates.empty() && _queries.empty();
    }

    void reserve_updates(int capacity) {
        assert(0 <= capacity);
        _updates.reserve(capacity);
    }

    void reserve_queries(int capacity) {
        assert(0 <= capacity);
        _queries.reserve(capacity);
    }

    void clear() {
        _updates.clear();
        _queries.clear();
    }

    int add_rectangle(
        const X& x_lower,
        const X& x_upper,
        const Y& y_lower,
        const Y& y_upper,
        const T& value
    ) {
        assert(!(x_upper < x_lower));
        assert(!(y_upper < y_lower));
        const int id = update_count();
        _updates.push_back(Update{x_lower, x_upper, y_lower, y_upper, value});
        return id;
    }

    int add_query(
        const X& x_lower,
        const X& x_upper,
        const Y& y_lower,
        const Y& y_upper
    ) {
        assert(!(x_upper < x_lower));
        assert(!(y_upper < y_lower));
        const int id = query_count();
        _queries.push_back(Query{x_lower, x_upper, y_lower, y_upper});
        return id;
    }

    std::vector<T> calculate() const {
        std::vector<T> answers(_queries.size(), T{});
        if (_queries.empty() || _updates.empty()) return answers;

        std::vector<PointEvent> point_events;
        point_events.reserve(4 * _updates.size());
        std::vector<Y> y_coordinates;
        y_coordinates.reserve(2 * _updates.size());
        for (const Update& update : _updates) {
            if (equivalent(update.x_lower, update.x_upper) ||
                equivalent(update.y_lower, update.y_upper)) {
                continue;
            }
            const T negative_value = T{} - update.value;
            point_events.push_back(PointEvent{
                update.x_lower,
                update.y_lower,
                make_coefficient(update.x_lower, update.y_lower, update.value)
            });
            point_events.push_back(PointEvent{
                update.x_lower,
                update.y_upper,
                make_coefficient(update.x_lower, update.y_upper, negative_value)
            });
            point_events.push_back(PointEvent{
                update.x_upper,
                update.y_lower,
                make_coefficient(update.x_upper, update.y_lower, negative_value)
            });
            point_events.push_back(PointEvent{
                update.x_upper,
                update.y_upper,
                make_coefficient(update.x_upper, update.y_upper, update.value)
            });
            y_coordinates.push_back(update.y_lower);
            y_coordinates.push_back(update.y_upper);
        }
        if (point_events.empty()) return answers;

        std::sort(y_coordinates.begin(), y_coordinates.end());
        y_coordinates.erase(
            std::unique(
                y_coordinates.begin(),
                y_coordinates.end(),
                [](const Y& first, const Y& second) {
                    return equivalent(first, second);
                }
            ),
            y_coordinates.end()
        );
        std::sort(
            point_events.begin(),
            point_events.end(),
            [](const PointEvent& first, const PointEvent& second) {
                return first.x < second.x;
            }
        );

        std::vector<PrefixEvent> prefix_events;
        prefix_events.reserve(4 * _queries.size());
        for (int query_id = 0; query_id < query_count(); query_id++) {
            const Query& query = _queries[query_id];
            prefix_events.push_back(PrefixEvent{
                query.x_upper, query.y_upper, query_id, false
            });
            prefix_events.push_back(PrefixEvent{
                query.x_lower, query.y_upper, query_id, true
            });
            prefix_events.push_back(PrefixEvent{
                query.x_upper, query.y_lower, query_id, true
            });
            prefix_events.push_back(PrefixEvent{
                query.x_lower, query.y_lower, query_id, false
            });
        }
        std::sort(
            prefix_events.begin(),
            prefix_events.end(),
            [](const PrefixEvent& first, const PrefixEvent& second) {
                return first.x < second.x;
            }
        );

        FenwickTree<Coefficient> fenwick(int(y_coordinates.size()));
        int point_index = 0;
        for (const PrefixEvent& event : prefix_events) {
            while (
                point_index < int(point_events.size()) &&
                point_events[point_index].x < event.x
            ) {
                const PointEvent& point = point_events[point_index];
                const int y_index = int(
                    std::lower_bound(
                        y_coordinates.begin(), y_coordinates.end(), point.y
                    ) - y_coordinates.begin()
                );
                fenwick.add(y_index, point.coefficient);
                point_index++;
            }
            const int y_count = int(
                std::lower_bound(
                    y_coordinates.begin(), y_coordinates.end(), event.y
                ) - y_coordinates.begin()
            );
            const T value = evaluate(fenwick.sum(y_count), event.x, event.y);
            if (event.subtract) {
                answers[event.query_id] -= value;
            } else {
                answers[event.query_id] += value;
            }
        }
        return answers;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_OFFLINE_RECTANGLE_ADD_RECTANGLE_SUM_HPP
