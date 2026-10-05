#ifndef M1UNE_DS_BST_MEX_MULTISET_HPP
#define M1UNE_DS_BST_MEX_MULTISET_HPP 1

#include <cassert>
#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

#include "predecessor_set.hpp"

namespace m1une {
namespace ds {

// Tracks multiplicities in [0, U) and returns min(actual mex, U).
struct MexMultiset {
   private:
    std::vector<int> _count;
    PredecessorSet _missing;
    int _mex;

    static int checked_universe_size(int universe_size) {
        assert(universe_size >= 0);
        return universe_size;
    }

    static int checked_size(std::size_t size) {
        assert(size <= static_cast<std::size_t>(std::numeric_limits<int>::max()));
        return int(size);
    }

   public:
    MexMultiset() : MexMultiset(0) {}

    explicit MexMultiset(int universe_size)
        : _count(checked_universe_size(universe_size), 0),
          _missing(std::string(universe_size, '1')), _mex(0) {}

    template <class T>
    explicit MexMultiset(const std::vector<T>& values)
        : _count(checked_size(values.size()), 0), _missing(0), _mex(0) {
        static_assert(
            std::is_integral_v<T> && sizeof(T) <= sizeof(std::uintmax_t),
            "MexMultiset requires standard integral values"
        );
        const int n = universe_size();
        for (T value : values) {
            if constexpr (std::is_signed_v<T>) {
                if (value < 0) continue;
            }
            if (static_cast<std::uintmax_t>(value) < static_cast<std::uintmax_t>(n)) {
                ++_count[int(value)];
            }
        }
        std::string membership(n, '1');
        for (int value = 0; value < n; ++value) {
            if (_count[value] != 0) membership[value] = '0';
        }
        _missing = PredecessorSet(membership);
        const int first = _missing.min();
        _mex = first == -1 ? n : first;
    }

    int universe_size() const {
        return int(_count.size());
    }

    int count(long long value) const {
        if (value < 0 || value >= universe_size()) return 0;
        return _count[int(value)];
    }

    void insert(long long value) {
        if (value < 0 || value >= universe_size()) return;
        const int key = int(value);
        assert(_count[key] < std::numeric_limits<int>::max());
        if (_count[key]++ != 0) return;
        _missing.erase(key);
        if (key == _mex) {
            const int first = _missing.min();
            _mex = first == -1 ? universe_size() : first;
        }
    }

    // Removes one occurrence; returns false for absent or untracked values.
    bool erase(long long value) {
        if (value < 0 || value >= universe_size()) return false;
        const int key = int(value);
        if (_count[key] == 0) return false;
        if (--_count[key] == 0) {
            _missing.insert(key);
            if (key < _mex) _mex = key;
        }
        return true;
    }

    int mex() const {
        return _mex;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BST_MEX_MULTISET_HPP
