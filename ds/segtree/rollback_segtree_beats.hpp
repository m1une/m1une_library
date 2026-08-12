#ifndef M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_BEATS_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_BEATS_HPP 1

#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "../../beats_acted_monoid/concept.hpp"
#include "../../math/bit_ceil.hpp"
#include "../detail/rollback_journal.hpp"

namespace m1une {
namespace ds {

// Generic Segment Tree Beats for actions that may require recursive descent.
template <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>
struct RollbackSegtreeBeats {
    using value_type = typename ActedMonoid::value_type;
    using operator_type = typename ActedMonoid::operator_type;
    using T = value_type;
    using F = operator_type;

   private:
    int _n = 0;
    int _size = 1;
    struct Node {
        T value = ActedMonoid::id();
        F lazy = ActedMonoid::op_id();
        bool has_lazy = false;
    };

    detail::RollbackJournal<Node> _journal;

    static T mapping_at(const F& f, const T& value, long long ordinal) {
        if constexpr (requires(F g, T x, long long i) {
            ActedMonoid::mapping(g, x, i);
        }) {
            return ActedMonoid::mapping(f, value, ordinal);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static bool can_apply_at(const F& f, const T& value, long long ordinal) {
        if constexpr (requires(F g, T x, long long i) {
            ActedMonoid::can_apply(g, x, i);
        }) {
            return ActedMonoid::can_apply(f, value, ordinal);
        } else {
            return ActedMonoid::can_apply(f, value);
        }
    }

    static F shift_operator(const F& f, long long ordinal) {
        if constexpr (requires(F g, long long i) {
            ActedMonoid::op_shift(g, i);
        }) {
            return ActedMonoid::op_shift(f, ordinal);
        } else {
            return f;
        }
    }

    void initialize(std::vector<T>&& values) {
        _journal.clear();
        _n = int(values.size());
        _size = int(m1une::math::bit_ceil((unsigned int)_n));
        _journal.nodes.assign(2 * _size, Node());
        _journal.saved_epoch.assign(_journal.nodes.size(), 0);
        for (int i = 0; i < _n; ++i) {
            _journal[_size + i].value = std::move(values[i]);
        }
        for (int k = _size - 1; k >= 1; --k) update(k);
    }

    void update(int node) {
        _journal.touch(node);
        _journal[node].value = ActedMonoid::op(
            _journal[node * 2].value,
            _journal[node * 2 + 1].value
        );
    }

    void all_apply(int node, int left, int right, const F& f) {
        if (_n <= left) return;
        if (can_apply_at(f, _journal[node].value, 0)) {
            _journal.touch(node);
            _journal[node].value = mapping_at(f, _journal[node].value, 0);
            if (node < _size) {
                _journal[node].lazy = ActedMonoid::op_comp(f, _journal[node].lazy);
                _journal[node].has_lazy = true;
            }
            return;
        }

        assert(right - left > 1);
        push(node, left, right);
        int middle = left + (right - left) / 2;
        all_apply(node * 2, left, middle, f);
        all_apply(
            node * 2 + 1,
            middle,
            right,
            shift_operator(f, middle - left)
        );
        update(node);
    }

    void push(int node, int left, int right) {
        assert(right - left > 1);
        if (!_journal[node].has_lazy) return;
        int middle = left + (right - left) / 2;
        F f = _journal[node].lazy;
        _journal.touch(node);
        _journal[node].lazy = ActedMonoid::op_id();
        _journal[node].has_lazy = false;
        all_apply(node * 2, left, middle, f);
        all_apply(
            node * 2 + 1,
            middle,
            right,
            shift_operator(f, middle - left)
        );
    }

    void set_impl(
        int node,
        int left,
        int right,
        int index,
        T value
    ) {
        if (right - left == 1) {
            _journal.touch(node);
            _journal[node].value = std::move(value);
            return;
        }
        push(node, left, right);
        int middle = left + (right - left) / 2;
        if (index < middle) {
            set_impl(node * 2, left, middle, index, std::move(value));
        } else {
            set_impl(
                node * 2 + 1,
                middle,
                right,
                index,
                std::move(value)
            );
        }
        update(node);
    }

    T get_impl(int node, int left, int right, int index) {
        if (right - left == 1) return _journal[node].value;
        push(node, left, right);
        int middle = left + (right - left) / 2;
        if (index < middle) {
            return get_impl(node * 2, left, middle, index);
        }
        return get_impl(node * 2 + 1, middle, right, index);
    }

    T prod_impl(
        int node,
        int left,
        int right,
        int query_left,
        int query_right
    ) {
        if (
            query_right <= left || right <= query_left || _n <= left
        ) {
            return ActedMonoid::id();
        }
        if (query_left <= left && right <= query_right) {
            return _journal[node].value;
        }
        push(node, left, right);
        int middle = left + (right - left) / 2;
        return ActedMonoid::op(
            prod_impl(
                node * 2,
                left,
                middle,
                query_left,
                query_right
            ),
            prod_impl(
                node * 2 + 1,
                middle,
                right,
                query_left,
                query_right
            )
        );
    }

    void apply_impl(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        int base_left,
        const F& f
    ) {
        if (
            query_right <= left || right <= query_left || _n <= left
        ) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            all_apply(
                node,
                left,
                right,
                shift_operator(f, left - base_left)
            );
            return;
        }
        push(node, left, right);
        int middle = left + (right - left) / 2;
        apply_impl(
            node * 2,
            left,
            middle,
            query_left,
            query_right,
            base_left,
            f
        );
        apply_impl(
            node * 2 + 1,
            middle,
            right,
            query_left,
            query_right,
            base_left,
            f
        );
        update(node);
    }

    void collect_impl(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        std::vector<T>& result
    ) {
        if (
            query_right <= left || right <= query_left || _n <= left
        ) {
            return;
        }
        if (right - left == 1) {
            result.push_back(_journal[node].value);
            return;
        }
        push(node, left, right);
        int middle = left + (right - left) / 2;
        collect_impl(
            node * 2,
            left,
            middle,
            query_left,
            query_right,
            result
        );
        collect_impl(
            node * 2 + 1,
            middle,
            right,
            query_left,
            query_right,
            result
        );
    }

    template <class Predicate>
    bool max_right_impl(
        int node,
        int left,
        int right,
        int query_left,
        Predicate& predicate,
        T& product,
        int& answer
    ) {
        if (right <= query_left || _n <= left) return true;
        if (query_left <= left) {
            T next = ActedMonoid::op(product, _journal[node].value);
            if (predicate(next)) {
                product = std::move(next);
                return true;
            }
            if (right - left == 1) {
                answer = left;
                return false;
            }
        }
        push(node, left, right);
        int middle = left + (right - left) / 2;
        if (!max_right_impl(
                node * 2,
                left,
                middle,
                query_left,
                predicate,
                product,
                answer
            )) {
            return false;
        }
        return max_right_impl(
            node * 2 + 1,
            middle,
            right,
            query_left,
            predicate,
            product,
            answer
        );
    }

    template <class Predicate>
    bool min_left_impl(
        int node,
        int left,
        int right,
        int query_right,
        Predicate& predicate,
        T& product,
        int& answer
    ) {
        if (query_right <= left || _n <= left) return true;
        if (right <= query_right) {
            T next = ActedMonoid::op(_journal[node].value, product);
            if (predicate(next)) {
                product = std::move(next);
                return true;
            }
            if (right - left == 1) {
                answer = right;
                return false;
            }
        }
        push(node, left, right);
        int middle = left + (right - left) / 2;
        if (!min_left_impl(
                node * 2 + 1,
                middle,
                right,
                query_right,
                predicate,
                product,
                answer
            )) {
            return false;
        }
        return min_left_impl(
            node * 2,
            left,
            middle,
            query_right,
            predicate,
            product,
            answer
        );
    }

   public:
    RollbackSegtreeBeats() {
        initialize({});
    }

    explicit RollbackSegtreeBeats(int n) {
        assert(0 <= n);
        initialize(std::vector<T>(n, ActedMonoid::id()));
    }

    explicit RollbackSegtreeBeats(const std::vector<T>& values) {
        initialize(std::vector<T>(values));
    }

    explicit RollbackSegtreeBeats(std::vector<T>&& values) {
        initialize(std::move(values));
    }

    template <typename U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit RollbackSegtreeBeats(const std::vector<U>& values) {
        std::vector<T> converted;
        converted.reserve(values.size());
        for (int i = 0; i < int(values.size()); ++i) {
            if constexpr (requires(U x) { ActedMonoid::make(x); }) {
                converted.push_back(ActedMonoid::make(values[i]));
            } else if constexpr (requires(U x, int index) {
                ActedMonoid::make(x, index);
            }) {
                converted.push_back(ActedMonoid::make(values[i], i));
            } else {
                converted.push_back(static_cast<T>(values[i]));
            }
        }
        initialize(std::move(converted));
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    std::size_t node_count() const { return _journal.nodes.size(); }

    void set(int index, T value) {
        assert(0 <= index && index < _n);
        set_impl(1, 0, _size, index, std::move(value));
    }
    void set_inplace(int index, T value) { set(index, std::move(value)); }

    T get(int index) {
        assert(0 <= index && index < _n);
        return get_impl(1, 0, _size, index);
    }

    T operator[](int index) {
        return get(index);
    }

    T prod(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return ActedMonoid::id();
        return prod_impl(1, 0, _size, left, right);
    }

    T all_prod() const {
        return _journal[1].value;
    }

    void apply(int index, F f) {
        assert(0 <= index && index < _n);
        apply_impl(1, 0, _size, index, index + 1, index, f);
    }

    void apply(int left, int right, F f) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return;
        apply_impl(1, 0, _size, left, right, left, f);
    }
    void apply_inplace(int index, F f) { apply(index, std::move(f)); }
    void apply_inplace(int left, int right, F f) {
        apply(left, right, std::move(f));
    }

    std::vector<T> to_vector() {
        return to_vector(0, _n);
    }

    std::vector<T> to_vector(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        std::vector<T> result;
        result.reserve(right - left);
        collect_impl(1, 0, _size, left, right, result);
        return result;
    }

    template <class Predicate>
    int max_right(int left, Predicate predicate) {
        assert(0 <= left && left <= _n);
        assert(predicate(ActedMonoid::id()));
        if (left == _n) return _n;
        T product = ActedMonoid::id();
        int answer = _n;
        max_right_impl(
            1,
            0,
            _size,
            left,
            predicate,
            product,
            answer
        );
        return answer;
    }

    template <class Predicate>
    int min_left(int right, Predicate predicate) {
        assert(0 <= right && right <= _n);
        assert(predicate(ActedMonoid::id()));
        if (right == 0) return 0;
        T product = ActedMonoid::id();
        int answer = 0;
        min_left_impl(
            1,
            0,
            _size,
            right,
            predicate,
            product,
            answer
        );
        return answer;
    }

    int snapshot() { return _journal.snapshot(); }
    int snapshot_count() const { return _journal.snapshot_count(); }
    void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }
    void rollback(int state) { _journal.rollback(state); }
    void clear_history() { _journal.clear_history(); }
    void release() { initialize({}); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_BEATS_HPP
