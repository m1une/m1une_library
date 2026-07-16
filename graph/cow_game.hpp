#ifndef M1UNE_GRAPH_COW_GAME_HPP
#define M1UNE_GRAPH_COW_GAME_HPP 1

#include <cassert>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace graph {

template <class T>
struct CowGameConstraint {
    int a;
    int b;
    T upper_bound;
};

template <class T>
struct CowGameSolution {
    bool feasible = false;
    std::vector<T> value;

    bool is_feasible() const {
        return feasible;
    }
};

template <class T>
struct CowGameUpperBounds {
    bool feasible;
    std::vector<T> upper_bound;
    T inf;

    bool is_feasible() const {
        return feasible;
    }

    bool bounded(int variable) const {
        assert(0 <= variable && variable < int(upper_bound.size()));
        return feasible && upper_bound[variable] != inf;
    }
};

template <class T>
struct CowGameDifferenceBounds {
    bool feasible;
    std::optional<T> lower_bound;
    std::optional<T> upper_bound;

    bool is_feasible() const {
        return feasible;
    }

    bool bounded_below() const {
        return feasible && lower_bound.has_value();
    }

    bool bounded_above() const {
        return feasible && upper_bound.has_value();
    }
};

template <class T>
class CowGame {
    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);

    struct RelaxationResult {
        bool has_negative_cycle;
        std::vector<T> dist;
    };

    int _n;
    std::vector<CowGameConstraint<T>> _constraints;
    std::vector<std::vector<int>> _outgoing_constraints;
    bool _has_negative_upper_bound = false;
    mutable bool _solution_cached = false;
    mutable CowGameSolution<T> _cached_solution;

    void assert_variable(int variable) const {
        (void)variable;
        assert(0 <= variable && variable < _n);
    }

    T negate(T value) const {
        assert(value != std::numeric_limits<T>::lowest());
        return -value;
    }

    RelaxationResult check_feasibility() const {
        std::vector<T> dist(_n, T());
        for (int iteration = 0; iteration < _n; iteration++) {
            bool updated = false;
            for (const auto& constraint : _constraints) {
                T candidate = dist[constraint.b] + constraint.upper_bound;
                if (dist[constraint.a] <= candidate) continue;
                dist[constraint.a] = candidate;
                updated = true;
                if (iteration == _n - 1) return RelaxationResult{true, std::move(dist)};
            }
            if (!updated) break;
        }
        return RelaxationResult{false, std::move(dist)};
    }

    std::vector<T> shortest_paths(int source, T inf) const {
        const auto& potential = _cached_solution.value;
        std::vector<T> dist(_n, inf);
        std::vector<int> heap;
        // -1 is unseen, -2 is fixed, and every other value is a heap index.
        std::vector<int> position(_n, -1);
        heap.reserve(_n);

        auto swap_heap = [&](int i, int j) {
            std::swap(heap[i], heap[j]);
            position[heap[i]] = i;
            position[heap[j]] = j;
        };
        auto sift_up = [&](int i) {
            while (i > 0) {
                int parent = (i - 1) / 2;
                if (dist[heap[parent]] <= dist[heap[i]]) break;
                swap_heap(parent, i);
                i = parent;
            }
        };
        auto sift_down = [&](int i) {
            while (2 * i + 1 < int(heap.size())) {
                int child = 2 * i + 1;
                if (child + 1 < int(heap.size()) &&
                    dist[heap[child + 1]] < dist[heap[child]]) {
                    child++;
                }
                if (dist[heap[i]] <= dist[heap[child]]) break;
                swap_heap(i, child);
                i = child;
            }
        };

        dist[source] = T();
        position[source] = 0;
        heap.push_back(source);

        while (!heap.empty()) {
            int b = heap[0];
            position[b] = -2;
            int last = heap.back();
            heap.pop_back();
            if (!heap.empty()) {
                heap[0] = last;
                position[last] = 0;
                sift_down(0);
            }

            for (int id : _outgoing_constraints[b]) {
                const auto& constraint = _constraints[id];
                T cost = constraint.upper_bound + potential[b] -
                         potential[constraint.a];
                assert(cost >= T());
                T candidate = dist[b] + cost;
                if (dist[constraint.a] <= candidate) continue;
                dist[constraint.a] = candidate;
                assert(position[constraint.a] != -2);
                if (position[constraint.a] == -1) {
                    position[constraint.a] = int(heap.size());
                    heap.push_back(constraint.a);
                }
                sift_up(position[constraint.a]);
            }
        }

        for (int v = 0; v < _n; v++) {
            if (dist[v] == inf) continue;
            dist[v] = dist[v] - potential[source] + potential[v];
        }
        return dist;
    }

   public:
    CowGame() : CowGame(0) {}

    explicit CowGame(int variable_count)
        : _n(variable_count),
          _outgoing_constraints(variable_count < 0 ? 0 : variable_count) {
        assert(variable_count >= 0);
    }

    int size() const {
        return _n;
    }

    int constraint_count() const {
        return int(_constraints.size());
    }

    const CowGameConstraint<T>& get_constraint(int id) const {
        assert(0 <= id && id < int(_constraints.size()));
        return _constraints[id];
    }

    const std::vector<CowGameConstraint<T>>& constraints() const {
        return _constraints;
    }

    bool can_use_dijkstra() const {
        return !_has_negative_upper_bound ||
               (_solution_cached && _cached_solution.feasible);
    }

    int add_upper_bound(int a, int b, T upper_bound) {
        assert_variable(a);
        assert_variable(b);
        int id = int(_constraints.size());
        _constraints.push_back(CowGameConstraint<T>{a, b, upper_bound});
        _outgoing_constraints[b].push_back(id);
        _has_negative_upper_bound = _has_negative_upper_bound || upper_bound < T();
        _solution_cached = false;
        return id;
    }

    int add_constraint(int a, int b, T upper_bound) {
        return add_upper_bound(a, b, upper_bound);
    }

    int add_lower_bound(int a, int b, T lower_bound) {
        return add_upper_bound(b, a, negate(lower_bound));
    }

    void add_bounds(int a, int b, T lower_bound, T upper_bound) {
        assert(lower_bound <= upper_bound);
        add_lower_bound(a, b, lower_bound);
        add_upper_bound(a, b, upper_bound);
    }

    void add_equality(int a, int b, T difference) {
        add_bounds(a, b, difference, difference);
    }

    CowGameSolution<T> solve() const {
        if (_solution_cached) return _cached_solution;

        _cached_solution.feasible = true;
        _cached_solution.value.assign(_n, T());
        if (_has_negative_upper_bound) {
            auto result = check_feasibility();
            _cached_solution.feasible = !result.has_negative_cycle;
            _cached_solution.value.clear();
            if (_cached_solution.feasible) {
                _cached_solution.value = std::move(result.dist);
            }
        }
        _solution_cached = true;
        return _cached_solution;
    }

    bool is_feasible() const {
        if (!_solution_cached) (void)solve();
        return _cached_solution.feasible;
    }

    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {
        assert_variable(source);
        T inf = std::numeric_limits<T>::max() / T(4);
        CowGameUpperBounds<T> result;
        result.feasible = is_feasible();
        result.inf = inf;
        result.upper_bound.assign(_n, inf);
        if (!result.feasible) return result;

        result.upper_bound = shortest_paths(source, inf);
        return result;
    }

    CowGameDifferenceBounds<T> difference_bounds(int a, int b) const {
        assert_variable(a);
        assert_variable(b);
        T inf = std::numeric_limits<T>::max() / T(4);
        CowGameDifferenceBounds<T> result;
        result.feasible = is_feasible();
        if (!result.feasible) return result;

        auto upper = shortest_paths(b, inf);
        if (upper[a] != inf) result.upper_bound = upper[a];

        auto lower = shortest_paths(a, inf);
        if (lower[b] != inf) result.lower_bound = negate(lower[b]);
        return result;
    }
};

template <class T>
using DifferenceConstraints = CowGame<T>;

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_COW_GAME_HPP
