#ifndef M1UNE_GRAPH_DOUBLING_HPP
#define M1UNE_GRAPH_DOUBLING_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

#include "../monoid/concept.hpp"

namespace m1une {
namespace graph {

// Static binary lifting with ordered aggregates. A step collects values[v]
// before moving to successor[v]. State -1 stays at -1 and contributes id().
template <m1une::monoid::IsMonoid Monoid>
class Doubling {
   public:
    using value_type = typename Monoid::value_type;

    struct Result {
        int vertex;
        value_type product;
    };

   private:
    int _n = 0;
    int _levels = 0;
    std::uint64_t _max_steps = 0;
    // Level-major flat tables: the entry at (bit, v) describes 2^bit steps.
    std::vector<int> _next;
    std::vector<value_type> _products;

    void check_query(int vertex, std::uint64_t steps) const {
        assert(-1 <= vertex && vertex < _n);
        assert(steps <= _max_steps);
        (void)vertex;
        (void)steps;
    }

   public:
    Doubling() = default;

    Doubling(const std::vector<int>& successor, const std::vector<value_type>& values,
             std::uint64_t max_steps) {
        build(successor, values, max_steps);
    }

    void build(const std::vector<int>& successor, const std::vector<value_type>& values,
               std::uint64_t max_steps) {
        assert(successor.size() == values.size());
        assert(successor.size() <= std::size_t(std::numeric_limits<int>::max()));
        const int n = int(successor.size());
        for (int to : successor) {
            assert(-1 <= to && to < n);
            (void)to;
        }
        _n = n;
        _levels = std::bit_width(max_steps);
        _max_steps = max_steps;
        assert(_levels == 0 || std::size_t(n) <=
                   std::numeric_limits<std::size_t>::max() / std::size_t(_levels));
        const std::size_t total = std::size_t(n) * std::size_t(_levels);
        _next = std::vector<int>(total, -1);
        _products = std::vector<value_type>(total, Monoid::id());
        if (_levels == 0) return;

        std::copy(successor.begin(), successor.end(), _next.begin());
        std::copy(values.begin(), values.end(), _products.begin());
        for (int bit = 1; bit < _levels; ++bit) {
            const std::size_t previous = std::size_t(bit - 1) * std::size_t(n);
            const std::size_t current = previous + std::size_t(n);
            for (int vertex = 0; vertex < n; ++vertex) {
                const int middle = _next[previous + vertex];
                if (middle == -1) {
                    _products[current + vertex] = _products[previous + vertex];
                } else {
                    _next[current + vertex] = _next[previous + middle];
                    _products[current + vertex] = Monoid::op(
                        _products[previous + vertex], _products[previous + middle]);
                }
            }
        }
    }

    int size() const { return _n; }

    bool empty() const { return _n == 0; }

    int levels() const { return _levels; }

    std::uint64_t max_steps() const { return _max_steps; }

    int jump(int vertex, std::uint64_t steps) const {
        check_query(vertex, steps);
        while (steps != 0 && vertex != -1) {
            const int bit = std::countr_zero(steps);
            vertex = _next[std::size_t(bit) * std::size_t(_n) + vertex];
            steps &= steps - 1;
        }
        return vertex;
    }

    Result walk(int vertex, std::uint64_t steps) const {
        check_query(vertex, steps);
        Result result{vertex, Monoid::id()};
        while (steps != 0 && result.vertex != -1) {
            const int bit = std::countr_zero(steps);
            const std::size_t index = std::size_t(bit) * std::size_t(_n) + result.vertex;
            result.product = Monoid::op(result.product, _products[index]);
            result.vertex = _next[index];
            steps &= steps - 1;
        }
        return result;
    }

    value_type prod(int vertex, std::uint64_t steps) const {
        return walk(vertex, steps).product;
    }
};

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DOUBLING_HPP
