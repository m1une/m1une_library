#ifndef M1UNE_DS_HEAP_DOUBLE_ENDED_PRIORITY_QUEUE_HPP
#define M1UNE_DS_HEAP_DOUBLE_ENDED_PRIORITY_QUEUE_HPP 1

#include <bit>
#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Min-max heap supporting access to both extremes of a total ordering.
template <class T, class Compare = std::less<T>>
class DoubleEndedPriorityQueue {
   private:
    std::vector<T> _values;
    [[no_unique_address]] Compare _compare;

    static std::size_t parent(std::size_t index) {
        return (index - 1) / 2;
    }

    static std::size_t grandparent(std::size_t index) {
        return (index - 3) / 4;
    }

    static bool is_min_level(std::size_t index) {
        const int level = int(std::bit_width(index + 1)) - 1;
        return level % 2 == 0;
    }

    void bubble_up_min(std::size_t index) {
        while (index >= 3) {
            const std::size_t ancestor = grandparent(index);
            if (!_compare(_values[index], _values[ancestor])) break;
            std::swap(_values[index], _values[ancestor]);
            index = ancestor;
        }
    }

    void bubble_up_max(std::size_t index) {
        while (index >= 3) {
            const std::size_t ancestor = grandparent(index);
            if (!_compare(_values[ancestor], _values[index])) break;
            std::swap(_values[index], _values[ancestor]);
            index = ancestor;
        }
    }

    std::size_t minimum_descendant(std::size_t index) const {
        std::size_t result = _values.size();
        const std::size_t first_child = index * 2 + 1;
        const std::size_t first_grandchild = index * 4 + 3;
        for (std::size_t candidate = first_child;
             candidate < _values.size() && candidate < first_child + 2;
             candidate++) {
            if (result == _values.size() ||
                _compare(_values[candidate], _values[result])) {
                result = candidate;
            }
        }
        for (std::size_t candidate = first_grandchild;
             candidate < _values.size() && candidate < first_grandchild + 4;
             candidate++) {
            if (result == _values.size() ||
                _compare(_values[candidate], _values[result])) {
                result = candidate;
            }
        }
        return result;
    }

    std::size_t maximum_descendant(std::size_t index) const {
        std::size_t result = _values.size();
        const std::size_t first_child = index * 2 + 1;
        const std::size_t first_grandchild = index * 4 + 3;
        for (std::size_t candidate = first_child;
             candidate < _values.size() && candidate < first_child + 2;
             candidate++) {
            if (result == _values.size() ||
                _compare(_values[result], _values[candidate])) {
                result = candidate;
            }
        }
        for (std::size_t candidate = first_grandchild;
             candidate < _values.size() && candidate < first_grandchild + 4;
             candidate++) {
            if (result == _values.size() ||
                _compare(_values[result], _values[candidate])) {
                result = candidate;
            }
        }
        return result;
    }

    void trickle_down_min(std::size_t index) {
        while (true) {
            const std::size_t descendant = minimum_descendant(index);
            if (descendant == _values.size()) return;
            if (parent(descendant) == index) {
                if (_compare(_values[descendant], _values[index])) {
                    std::swap(_values[descendant], _values[index]);
                }
                return;
            }
            if (!_compare(_values[descendant], _values[index])) return;
            std::swap(_values[descendant], _values[index]);
            const std::size_t descendant_parent = parent(descendant);
            if (_compare(_values[descendant_parent], _values[descendant])) {
                std::swap(_values[descendant_parent], _values[descendant]);
            }
            index = descendant;
        }
    }

    void trickle_down_max(std::size_t index) {
        while (true) {
            const std::size_t descendant = maximum_descendant(index);
            if (descendant == _values.size()) return;
            if (parent(descendant) == index) {
                if (_compare(_values[index], _values[descendant])) {
                    std::swap(_values[descendant], _values[index]);
                }
                return;
            }
            if (!_compare(_values[index], _values[descendant])) return;
            std::swap(_values[descendant], _values[index]);
            const std::size_t descendant_parent = parent(descendant);
            if (_compare(_values[descendant], _values[descendant_parent])) {
                std::swap(_values[descendant_parent], _values[descendant]);
            }
            index = descendant;
        }
    }

    void restore_after_push(std::size_t index) {
        if (index == 0) return;
        const std::size_t ancestor = parent(index);
        if (is_min_level(index)) {
            if (_compare(_values[ancestor], _values[index])) {
                std::swap(_values[ancestor], _values[index]);
                bubble_up_max(ancestor);
            } else {
                bubble_up_min(index);
            }
        } else {
            if (_compare(_values[index], _values[ancestor])) {
                std::swap(_values[ancestor], _values[index]);
                bubble_up_min(ancestor);
            } else {
                bubble_up_max(index);
            }
        }
    }

    std::size_t maximum_index() const {
        assert(!_values.empty());
        if (_values.size() == 1) return 0;
        if (_values.size() == 2 || !_compare(_values[1], _values[2])) return 1;
        return 2;
    }

   public:
    DoubleEndedPriorityQueue() = default;

    explicit DoubleEndedPriorityQueue(Compare compare)
        : _compare(std::move(compare)) {}

    DoubleEndedPriorityQueue(std::initializer_list<T> values,
                             Compare compare = Compare())
        : DoubleEndedPriorityQueue(std::move(compare)) {
        for (const T& value : values) push(value);
    }

    template <class Iterator>
    DoubleEndedPriorityQueue(Iterator first, Iterator last,
                             Compare compare = Compare())
        : DoubleEndedPriorityQueue(std::move(compare)) {
        while (first != last) {
            push(*first);
            ++first;
        }
    }

    std::size_t size() const {
        return _values.size();
    }

    bool empty() const {
        return _values.empty();
    }

    const T& min() const {
        assert(!empty());
        return _values[0];
    }

    const T& max() const {
        return _values[maximum_index()];
    }

    void clear() {
        _values.clear();
    }

    template <class... Args>
    void emplace(Args&&... args) {
        _values.emplace_back(std::forward<Args>(args)...);
        restore_after_push(_values.size() - 1);
    }

    void push(const T& value) {
        emplace(value);
    }

    void push(T&& value) {
        emplace(std::move(value));
    }

    void pop_min() {
        assert(!empty());
        if (_values.size() == 1) {
            _values.pop_back();
            return;
        }
        _values[0] = std::move(_values.back());
        _values.pop_back();
        trickle_down_min(0);
    }

    void pop_max() {
        assert(!empty());
        const std::size_t index = maximum_index();
        if (index == _values.size() - 1) {
            _values.pop_back();
            return;
        }
        _values[index] = std::move(_values.back());
        _values.pop_back();
        trickle_down_max(index);
    }

    const Compare& comparator() const {
        return _compare;
    }
};

template <class T, class Compare = std::less<T>>
using MinMaxHeap = DoubleEndedPriorityQueue<T, Compare>;

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_HEAP_DOUBLE_ENDED_PRIORITY_QUEUE_HPP
