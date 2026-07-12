#ifndef M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_DEQUE_HPP
#define M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_DEQUE_HPP 1

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// A deque supporting the ordered product of all elements in amortized O(1).
template <m1une::monoid::IsMonoid Monoid>
struct SlidingWindowAggregationDeque {
    using T = typename Monoid::value_type;

   private:
    struct Entry {
        T value;
        T product;
    };

    // The back of _front is the front of the deque. _back is in deque order.
    std::vector<Entry> _front;
    std::vector<Entry> _back;

    void rebalance(bool need_front) {
        assert(empty() == false);

        std::vector<T> values;
        values.reserve(size());
        for (auto iter = _front.rbegin(); iter != _front.rend(); ++iter) {
            values.push_back(std::move(iter->value));
        }
        for (Entry& entry : _back) values.push_back(std::move(entry.value));

        _front.clear();
        _back.clear();

        const std::size_t front_size = need_front ? (values.size() + 1) / 2 : values.size() / 2;
        for (std::size_t index = front_size; index > 0; --index) {
            push_front(std::move(values[index - 1]));
        }
        for (std::size_t index = front_size; index < values.size(); ++index) {
            push_back(std::move(values[index]));
        }
    }

    void ensure_front() {
        if (_front.empty()) rebalance(true);
    }

    void ensure_back() {
        if (_back.empty()) rebalance(false);
    }

   public:
    SlidingWindowAggregationDeque() = default;

    explicit SlidingWindowAggregationDeque(const std::vector<T>& values) {
        reserve(values.size());
        for (const T& value : values) push_back(value);
    }

    explicit SlidingWindowAggregationDeque(std::vector<T>&& values) {
        reserve(values.size());
        for (T& value : values) push_back(std::move(value));
    }

    std::size_t size() const {
        return _front.size() + _back.size();
    }

    bool empty() const {
        return _front.empty() && _back.empty();
    }

    void reserve(std::size_t capacity) {
        _front.reserve(capacity);
        _back.reserve(capacity);
    }

    void clear() {
        _front.clear();
        _back.clear();
    }

    void push_front(T value) {
        T product = _front.empty() ? value : Monoid::op(value, _front.back().product);
        _front.push_back(Entry{
            std::move(value),
            std::move(product),
        });
    }

    void push_back(T value) {
        T product = _back.empty() ? value : Monoid::op(_back.back().product, value);
        _back.push_back(Entry{
            std::move(value),
            std::move(product),
        });
    }

    void pop_front() {
        assert(!empty());
        ensure_front();
        _front.pop_back();
    }

    void pop_back() {
        assert(!empty());
        ensure_back();
        _back.pop_back();
    }

    const T& front() {
        assert(!empty());
        ensure_front();
        return _front.back().value;
    }

    const T& back() {
        assert(!empty());
        ensure_back();
        return _back.back().value;
    }

    // Returns the product in deque order, or the identity when empty.
    T prod() const {
        if (_front.empty()) {
            return _back.empty() ? Monoid::id() : _back.back().product;
        }
        if (_back.empty()) return _front.back().product;
        return Monoid::op(_front.back().product, _back.back().product);
    }

    T all_prod() const {
        return prod();
    }
};

template <m1une::monoid::IsMonoid Monoid>
using SwagDeque = SlidingWindowAggregationDeque<Monoid>;

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_DEQUE_HPP
