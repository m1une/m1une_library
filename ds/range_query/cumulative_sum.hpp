#ifndef M1UNE_DS_CUMULATIVE_SUM_HPP
#define M1UNE_DS_CUMULATIVE_SUM_HPP 1

#include <cassert>
#include <cstddef>
#include <vector>

namespace m1une {
namespace ds {

// Static one-dimensional cumulative sums.
template <typename T>
struct CumulativeSum1D {
   private:
    std::vector<T> _prefix;

   public:
    CumulativeSum1D() : _prefix(1, T{}) {}

    explicit CumulativeSum1D(const std::vector<T>& values)
        : _prefix(values.size() + 1, T{}) {
        for (std::size_t i = 0; i < values.size(); ++i) {
            _prefix[i + 1] = _prefix[i] + values[i];
        }
    }

    int size() const {
        return int(_prefix.size()) - 1;
    }

    bool empty() const {
        return size() == 0;
    }

    // Returns the sum of [0, r).
    T sum(int r) const {
        assert(0 <= r && r <= size());
        return _prefix[r];
    }

    // Returns the sum of [l, r).
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        return _prefix[r] - _prefix[l];
    }
};

// The unsuffixed name is an alias for the one-dimensional structure.
template <typename T>
using CumulativeSum = CumulativeSum1D<T>;

// Static two-dimensional cumulative sums over a rectangular row-major grid.
template <typename T>
struct CumulativeSum2D {
   private:
    int _height;
    int _width;
    std::vector<T> _prefix;

    std::size_t index(int y, int x) const {
        return std::size_t(y) * std::size_t(_width + 1) + std::size_t(x);
    }

   public:
    CumulativeSum2D() : _height(0), _width(0), _prefix(1, T{}) {}

    explicit CumulativeSum2D(const std::vector<std::vector<T>>& values)
        : _height(int(values.size())),
          _width(values.empty() ? 0 : int(values.front().size())),
          _prefix(
              std::size_t(_height + 1) * std::size_t(_width + 1), T{}
          ) {
        for (const auto& row : values) {
            assert(int(row.size()) == _width);
        }

        for (int y = 1; y <= _height; ++y) {
            for (int x = 1; x <= _width; ++x) {
                _prefix[index(y, x)] =
                    values[y - 1][x - 1] + _prefix[index(y - 1, x)]
                    + _prefix[index(y, x - 1)] - _prefix[index(y - 1, x - 1)];
            }
        }
    }

    int height() const {
        return _height;
    }

    int width() const {
        return _width;
    }

    bool empty() const {
        return _height == 0 || _width == 0;
    }

    // Returns the sum of [0, y) x [0, x).
    T sum(int y, int x) const {
        assert(0 <= y && y <= _height);
        assert(0 <= x && x <= _width);
        return _prefix[index(y, x)];
    }

    // Returns the sum of [y1, y2) x [x1, x2).
    T sum(int y1, int y2, int x1, int x2) const {
        assert(0 <= y1 && y1 <= y2 && y2 <= _height);
        assert(0 <= x1 && x1 <= x2 && x2 <= _width);
        return _prefix[index(y2, x2)] - _prefix[index(y1, x2)]
               - _prefix[index(y2, x1)] + _prefix[index(y1, x1)];
    }
};

// Static three-dimensional cumulative sums over a rectangular z-y-x grid.
template <typename T>
struct CumulativeSum3D {
   private:
    int _depth;
    int _height;
    int _width;
    std::vector<T> _prefix;

    std::size_t index(int z, int y, int x) const {
        return (std::size_t(z) * std::size_t(_height + 1) + std::size_t(y))
                   * std::size_t(_width + 1)
               + std::size_t(x);
    }

   public:
    CumulativeSum3D()
        : _depth(0), _height(0), _width(0), _prefix(1, T{}) {}

    explicit CumulativeSum3D(
        const std::vector<std::vector<std::vector<T>>>& values
    )
        : _depth(int(values.size())),
          _height(values.empty() ? 0 : int(values.front().size())),
          _width(
              values.empty() || values.front().empty()
                  ? 0
                  : int(values.front().front().size())
          ),
          _prefix(
              std::size_t(_depth + 1) * std::size_t(_height + 1)
                  * std::size_t(_width + 1),
              T{}
          ) {
        for (const auto& plane : values) {
            assert(int(plane.size()) == _height);
            for (const auto& row : plane) {
                assert(int(row.size()) == _width);
            }
        }

        for (int z = 1; z <= _depth; ++z) {
            for (int y = 1; y <= _height; ++y) {
                for (int x = 1; x <= _width; ++x) {
                    _prefix[index(z, y, x)] =
                        values[z - 1][y - 1][x - 1]
                        + _prefix[index(z - 1, y, x)]
                        + _prefix[index(z, y - 1, x)]
                        + _prefix[index(z, y, x - 1)]
                        - _prefix[index(z - 1, y - 1, x)]
                        - _prefix[index(z - 1, y, x - 1)]
                        - _prefix[index(z, y - 1, x - 1)]
                        + _prefix[index(z - 1, y - 1, x - 1)];
                }
            }
        }
    }

    int depth() const {
        return _depth;
    }

    int height() const {
        return _height;
    }

    int width() const {
        return _width;
    }

    bool empty() const {
        return _depth == 0 || _height == 0 || _width == 0;
    }

    // Returns the sum of [0, z) x [0, y) x [0, x).
    T sum(int z, int y, int x) const {
        assert(0 <= z && z <= _depth);
        assert(0 <= y && y <= _height);
        assert(0 <= x && x <= _width);
        return _prefix[index(z, y, x)];
    }

    // Returns the sum of [z1, z2) x [y1, y2) x [x1, x2).
    T sum(int z1, int z2, int y1, int y2, int x1, int x2) const {
        assert(0 <= z1 && z1 <= z2 && z2 <= _depth);
        assert(0 <= y1 && y1 <= y2 && y2 <= _height);
        assert(0 <= x1 && x1 <= x2 && x2 <= _width);
        return _prefix[index(z2, y2, x2)] - _prefix[index(z1, y2, x2)]
               - _prefix[index(z2, y1, x2)] - _prefix[index(z2, y2, x1)]
               + _prefix[index(z1, y1, x2)] + _prefix[index(z1, y2, x1)]
               + _prefix[index(z2, y1, x1)] - _prefix[index(z1, y1, x1)];
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_CUMULATIVE_SUM_HPP
