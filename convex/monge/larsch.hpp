#ifndef M1UNE_CONVEX_MONGE_LARSCH_HPP
#define M1UNE_CONVEX_MONGE_LARSCH_HPP 1

#include <cassert>
#include <utility>
#include <vector>

namespace m1une {
namespace convex {

// Online minima of a lower-triangular totally monotone matrix (column <= row).
// Leftmost ties. Before answering row r, only columns <= r are accessed, even
// when evaluating future rows. Finalize column r+1 after receiving answer r.
// O(N) total time/evaluations/memory; an individual next_argmin can take O(N).
// Value is stored directly, with no type-erased callable. Use CTAD: Larsch q(n,f).
template <class Value>
class Larsch {
    struct Level {
        int size;
        int row = 0;
        int column_row = 0;
        int boundary = 0;
        std::vector<int> columns;
        explicit Level(int n) : size(n) {}
    };

    int _size;
    Value _value;
    std::vector<Level> _levels;

    auto entry(int depth, int row, int column) {
        for (int d = depth; d > 0; --d) {
            row = row * 2 + 1;
            column = _levels[d].columns[column];
        }
        return _value(row, column);
    }

    int next_column(int depth) {
        auto& level = _levels[depth];
        int row = level.column_row++;
        int first = row == 0 ? 0 : row * 2 - 1;
        for (int column = first; column <= row * 2; ++column) {
            while (int(level.columns.size()) != row &&
                   entry(depth - 1, int(level.columns.size()) * 2 - 1,
                         level.columns.back()) >
                   entry(depth - 1, int(level.columns.size()) * 2 - 1, column)) {
                level.columns.pop_back();
            }
            if (int(level.columns.size()) != level.size) {
                level.columns.push_back(column);
            }
        }
        return level.columns[next_row(depth)];
    }

    int next_row(int depth) {
        auto& level = _levels[depth];
        int row = level.row++;
        if (row % 2 != 0) {
            return entry(depth, row, level.boundary) <= entry(depth, row, row)
                       ? level.boundary : row;
        }
        int previous = level.boundary;
        int next = row + 1 == level.size ? level.size - 1
                                        : next_column(depth + 1);
        level.boundary = next;
        int best = previous;
        for (int column = previous + 1; column <= next; ++column) {
            if (entry(depth, row, column) < entry(depth, row, best)) best = column;
        }
        return best;
    }

   public:
    explicit Larsch(int size, Value value) : _size(size), _value(std::move(value)) {
        assert(size >= 0);
        for (int n = size; n > 0; n /= 2) {
            _levels.emplace_back(n);
            if (_levels.size() > 1) _levels.back().columns.reserve(n);
        }
    }
    int size() const { return _size; }
    int processed_rows() const { return _size == 0 ? 0 : _levels[0].row; }
    bool finished() const { return processed_rows() == _size; }
    int next_argmin() {
        assert(!finished());
        return next_row(0);
    }
};

}  // namespace convex
}  // namespace m1une

#endif  // M1UNE_CONVEX_MONGE_LARSCH_HPP
