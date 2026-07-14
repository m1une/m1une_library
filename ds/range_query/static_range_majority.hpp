#ifndef M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MAJORITY_HPP
#define M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MAJORITY_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace m1une {
namespace ds {

// Static strict-majority queries in O(log N) time.
template <class T>
struct StaticRangeMajority {
    using result_type = std::optional<T>;

   private:
    struct Vote {
        int candidate = -1;
        int balance = 0;
    };

    int _n;
    int _tree_size;
    std::vector<T> _values;
    std::vector<std::vector<int>> _positions;
    std::vector<Vote> _tree;

    static Vote combine(Vote first, Vote second) {
        if (first.balance == 0) return second;
        if (second.balance == 0) return first;
        if (first.candidate == second.candidate) {
            return Vote{first.candidate, first.balance + second.balance};
        }
        if (first.balance > second.balance) {
            return Vote{first.candidate, first.balance - second.balance};
        }
        if (second.balance > first.balance) {
            return Vote{second.candidate, second.balance - first.balance};
        }
        return Vote();
    }

    Vote range_vote(int left, int right) const {
        Vote left_vote;
        Vote right_vote;
        left += _tree_size;
        right += _tree_size;
        while (left < right) {
            if (left & 1) left_vote = combine(left_vote, _tree[left++]);
            if (right & 1) right_vote = combine(_tree[--right], right_vote);
            left >>= 1;
            right >>= 1;
        }
        return combine(left_vote, right_vote);
    }

   public:
    StaticRangeMajority() : _n(0), _tree_size(1), _tree(2) {}

    explicit StaticRangeMajority(const std::vector<T>& values)
        : _n(int(values.size())), _tree_size(1), _values(values) {
        std::sort(_values.begin(), _values.end());
        _values.erase(
            std::unique(_values.begin(), _values.end()),
            _values.end()
        );
        _positions.resize(_values.size());

        while (_tree_size < _n) _tree_size <<= 1;
        _tree.assign(2 * _tree_size, Vote());
        for (int index = 0; index < _n; index++) {
            int rank = int(
                std::lower_bound(
                    _values.begin(), _values.end(), values[index]
                ) - _values.begin()
            );
            _positions[rank].push_back(index);
            _tree[_tree_size + index] = Vote{rank, 1};
        }
        for (int node = _tree_size - 1; node > 0; node--) {
            _tree[node] = combine(_tree[node << 1], _tree[(node << 1) | 1]);
        }
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    // Returns the unique value occurring more than half the time in
    // [left, right), or nullopt when no such value exists.
    result_type query(int left, int right) const {
        assert(0 <= left && left < right && right <= _n);
        Vote vote = range_vote(left, right);
        if (vote.balance == 0) return std::nullopt;

        const std::vector<int>& positions = _positions[vote.candidate];
        int frequency = int(
            std::lower_bound(positions.begin(), positions.end(), right)
            - std::lower_bound(positions.begin(), positions.end(), left)
        );
        if (2LL * frequency <= right - left) return std::nullopt;
        return _values[vote.candidate];
    }

    result_type majority(int left, int right) const {
        return query(left, right);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MAJORITY_HPP
