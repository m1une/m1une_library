#ifndef M1UNE_DS_PERSISTENT_SEGTREE_BEATS_HPP
#define M1UNE_DS_PERSISTENT_SEGTREE_BEATS_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "../../beats_acted_monoid/concept.hpp"
#include "persistent_node_pool.hpp"

namespace m1une {
namespace ds {

// A persistent Segment Tree Beats for fallible monoid actions.
template <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>
struct PersistentSegtreeBeats {
    using value_type = typename ActedMonoid::value_type;
    using operator_type = typename ActedMonoid::operator_type;
    using T = value_type;
    using F = operator_type;

   private:
    struct Node {
        T val;
        F lazy;
        int left;
        int right;
        int references;
        bool has_lazy;

        Node()
            : val(ActedMonoid::id()),
              lazy(ActedMonoid::op_id()),
              left(0),
              right(0),
              references(0),
              has_lazy(false) {}

        explicit Node(T value)
            : val(std::move(value)),
              lazy(ActedMonoid::op_id()),
              left(0),
              right(0),
              references(0),
              has_lazy(false) {}

        Node(T value, int left_child, int right_child)
            : val(std::move(value)),
              lazy(ActedMonoid::op_id()),
              left(left_child),
              right(right_child),
              references(0),
              has_lazy(false) {}
    };

    using Pool = detail::PersistentNodePool<Node>;

    int _n;
    int _root;
    std::shared_ptr<Pool> _pool;

    explicit PersistentSegtreeBeats(
        int n,
        int root,
        std::shared_ptr<Pool> pool
    ) : _n(n), _root(root), _pool(std::move(pool)) {
        _pool->retain(_root);
    }

    int new_node(const Node& node) const {
        return _pool->emplace(node);
    }

    int new_node(Node&& node) const {
        return _pool->emplace(std::move(node));
    }

    int clone_node(int node) const {
        return _pool->clone(node);
    }

    template <typename U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else if constexpr (requires(U x, int i) {
            ActedMonoid::make(x, i);
        }) {
            return ActedMonoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    static T mapping_at(const F& f, const T& value, long long ordinal) {
        if constexpr (requires(F g, T x, long long i) {
            ActedMonoid::mapping(g, x, i);
        }) {
            return ActedMonoid::mapping(f, value, ordinal);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static bool can_apply_at(
        const F& f,
        const T& value,
        long long ordinal
    ) {
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

    int build(int left, int right, const std::vector<T>& values) const {
        if (left == right) return 0;
        if (right - left == 1) return new_node(Node(values[left]));
        int middle = left + (right - left) / 2;
        int left_child = build(left, middle, values);
        int right_child = build(middle, right, values);
        return new_node(Node(
            ActedMonoid::op(
                (*_pool)[left_child].val,
                (*_pool)[right_child].val
            ),
            left_child,
            right_child
        ));
    }

    int build(int left, int right, std::vector<T>& values) const {
        if (left == right) return 0;
        if (right - left == 1) {
            return new_node(Node(std::move(values[left])));
        }
        int middle = left + (right - left) / 2;
        int left_child = build(left, middle, values);
        int right_child = build(middle, right, values);
        return new_node(Node(
            ActedMonoid::op(
                (*_pool)[left_child].val,
                (*_pool)[right_child].val
            ),
            left_child,
            right_child
        ));
    }

    template <typename U>
    int build_from_values(
        int left,
        int right,
        const std::vector<U>& values
    ) const {
        if (left == right) return 0;
        if (right - left == 1) {
            return new_node(Node(make_value(values[left], left)));
        }
        int middle = left + (right - left) / 2;
        int left_child = build_from_values(left, middle, values);
        int right_child = build_from_values(middle, right, values);
        return new_node(Node(
            ActedMonoid::op(
                (*_pool)[left_child].val,
                (*_pool)[right_child].val
            ),
            left_child,
            right_child
        ));
    }

    void update(int node) const {
        Node& current = (*_pool)[node];
        current.val = ActedMonoid::op(
            (*_pool)[current.left].val,
            (*_pool)[current.right].val
        );
    }

    int all_apply_clone(
        int node,
        int left,
        int right,
        const F& f,
        bool copy_on_write = false
    ) const {
        int result = copy_on_write ? _pool->clone_if_shared(node) : clone_node(node);
        Node& current = (*_pool)[result];
        if (can_apply_at(f, current.val, 0)) {
            current.val = mapping_at(f, current.val, 0);
            if (right - left > 1) {
                current.lazy = ActedMonoid::op_comp(f, current.lazy);
                current.has_lazy = true;
            }
            return result;
        }

        assert(right - left > 1);
        push(result, left, right, copy_on_write);
        int middle = left + (right - left) / 2;
        int left_child = all_apply_clone(
            (*_pool)[result].left,
            left,
            middle,
            f,
            copy_on_write
        );
        int right_child = all_apply_clone(
            (*_pool)[result].right,
            middle,
            right,
            shift_operator(f, middle - left),
            copy_on_write
        );
        _pool->replace((*_pool)[result].left, left_child);
        _pool->replace((*_pool)[result].right, right_child);
        update(result);
        return result;
    }

    void push(
        int node,
        int left,
        int right,
        bool copy_on_write = false
    ) const {
        if (!(*_pool)[node].has_lazy) return;
        assert(right - left > 1);

        F lazy = (*_pool)[node].lazy;
        int middle = left + (right - left) / 2;
        int left_child = all_apply_clone(
            (*_pool)[node].left,
            left,
            middle,
            lazy,
            copy_on_write
        );
        int right_child = all_apply_clone(
            (*_pool)[node].right,
            middle,
            right,
            shift_operator(lazy, middle - left),
            copy_on_write
        );
        _pool->replace((*_pool)[node].left, left_child);
        _pool->replace((*_pool)[node].right, right_child);
        Node& current = (*_pool)[node];
        current.lazy = ActedMonoid::op_id();
        current.has_lazy = false;
    }

    int set_node(
        int node,
        int left,
        int right,
        int index,
        T value,
        bool copy_on_write = false
    ) const {
        int result = copy_on_write ? _pool->clone_if_shared(node) : clone_node(node);
        if (right - left == 1) {
            Node& current = (*_pool)[result];
            current.val = std::move(value);
            current.lazy = ActedMonoid::op_id();
            current.has_lazy = false;
            return result;
        }

        push(result, left, right, copy_on_write);
        int middle = left + (right - left) / 2;
        if (index < middle) {
            int child = set_node(
                (*_pool)[result].left,
                left,
                middle,
                index,
                std::move(value),
                copy_on_write
            );
            _pool->replace((*_pool)[result].left, child);
        } else {
            int child = set_node(
                (*_pool)[result].right,
                middle,
                right,
                index,
                std::move(value),
                copy_on_write
            );
            _pool->replace((*_pool)[result].right, child);
        }
        update(result);
        return result;
    }

    int apply_node(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        const F& f,
        bool copy_on_write = false
    ) const {
        if (query_right <= left || right <= query_left) return node;
        if (query_left <= left && right <= query_right) {
            return all_apply_clone(
                node,
                left,
                right,
                shift_operator(f, left - query_left),
                copy_on_write
            );
        }

        int result = copy_on_write ? _pool->clone_if_shared(node) : clone_node(node);
        push(result, left, right, copy_on_write);
        int middle = left + (right - left) / 2;
        int left_child = apply_node(
            (*_pool)[result].left,
            left,
            middle,
            query_left,
            query_right,
            f,
            copy_on_write
        );
        int right_child = apply_node(
            (*_pool)[result].right,
            middle,
            right,
            query_left,
            query_right,
            f,
            copy_on_write
        );
        _pool->replace((*_pool)[result].left, left_child);
        _pool->replace((*_pool)[result].right, right_child);
        update(result);
        return result;
    }

    int copy_range_node(
        int target,
        int source,
        int left,
        int right,
        int query_left,
        int query_right
    ) const {
        if (query_right <= left || right <= query_left) return target;
        if (query_left <= left && right <= query_right) return source;

        int result = clone_node(target);
        int materialized_source = clone_node(source);
        _pool->retain(materialized_source);
        push(result, left, right);
        push(materialized_source, left, right);

        int middle = left + (right - left) / 2;
        int left_child = copy_range_node(
            (*_pool)[result].left,
            (*_pool)[materialized_source].left,
            left,
            middle,
            query_left,
            query_right
        );
        int right_child = copy_range_node(
            (*_pool)[result].right,
            (*_pool)[materialized_source].right,
            middle,
            right,
            query_left,
            query_right
        );
        _pool->replace((*_pool)[result].left, left_child);
        _pool->replace((*_pool)[result].right, right_child);
        update(result);
        _pool->release(materialized_source);
        return result;
    }

    F compose_for_child(
        const F& inherited,
        const Node& node,
        long long ordinal
    ) const {
        F shifted = shift_operator(inherited, ordinal);
        if (!node.has_lazy) return shifted;
        return ActedMonoid::op_comp(
            shifted,
            shift_operator(node.lazy, ordinal)
        );
    }

    T evaluate_node(
        int node,
        int left,
        int right,
        const F& inherited
    ) const {
        const Node& current = (*_pool)[node];
        if (can_apply_at(inherited, current.val, 0)) {
            return mapping_at(inherited, current.val, 0);
        }

        assert(right - left > 1);
        int middle = left + (right - left) / 2;
        return ActedMonoid::op(
            evaluate_node(
                current.left,
                left,
                middle,
                compose_for_child(inherited, current, 0)
            ),
            evaluate_node(
                current.right,
                middle,
                right,
                compose_for_child(inherited, current, middle - left)
            )
        );
    }

    T prod_node(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        const F& inherited
    ) const {
        if (query_right <= left || right <= query_left) {
            return ActedMonoid::id();
        }
        if (query_left <= left && right <= query_right) {
            return evaluate_node(node, left, right, inherited);
        }

        const Node& current = (*_pool)[node];
        int middle = left + (right - left) / 2;
        return ActedMonoid::op(
            prod_node(
                current.left,
                left,
                middle,
                query_left,
                query_right,
                compose_for_child(inherited, current, 0)
            ),
            prod_node(
                current.right,
                middle,
                right,
                query_left,
                query_right,
                compose_for_child(inherited, current, middle - left)
            )
        );
    }

    void collect_node(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        const F& inherited,
        std::vector<T>& result
    ) const {
        if (query_right <= left || right <= query_left) return;
        const Node& current = (*_pool)[node];
        if (right - left == 1) {
            result.push_back(mapping_at(inherited, current.val, 0));
            return;
        }

        int middle = left + (right - left) / 2;
        collect_node(
            current.left,
            left,
            middle,
            query_left,
            query_right,
            compose_for_child(inherited, current, 0),
            result
        );
        collect_node(
            current.right,
            middle,
            right,
            query_left,
            query_right,
            compose_for_child(inherited, current, middle - left),
            result
        );
    }

    template <class Predicate>
    int max_right_node(
        int node,
        int left,
        int right,
        int query_left,
        T& product,
        const F& inherited,
        Predicate& predicate
    ) const {
        if (right <= query_left) return right;
        if (query_left <= left) {
            T next = ActedMonoid::op(
                product,
                evaluate_node(node, left, right, inherited)
            );
            if (predicate(next)) {
                product = std::move(next);
                return right;
            }
            if (right - left == 1) return left;
        }

        const Node& current = (*_pool)[node];
        int middle = left + (right - left) / 2;
        int result = max_right_node(
            current.left,
            left,
            middle,
            query_left,
            product,
            compose_for_child(inherited, current, 0),
            predicate
        );
        if (result < middle) return result;
        return max_right_node(
            current.right,
            middle,
            right,
            query_left,
            product,
            compose_for_child(inherited, current, middle - left),
            predicate
        );
    }

    template <class Predicate>
    int min_left_node(
        int node,
        int left,
        int right,
        int query_right,
        T& product,
        const F& inherited,
        Predicate& predicate
    ) const {
        if (query_right <= left) return left;
        if (right <= query_right) {
            T next = ActedMonoid::op(
                evaluate_node(node, left, right, inherited),
                product
            );
            if (predicate(next)) {
                product = std::move(next);
                return left;
            }
            if (right - left == 1) return right;
        }

        const Node& current = (*_pool)[node];
        int middle = left + (right - left) / 2;
        int result = min_left_node(
            current.right,
            middle,
            right,
            query_right,
            product,
            compose_for_child(inherited, current, middle - left),
            predicate
        );
        if (middle < result) return result;
        return min_left_node(
            current.left,
            left,
            middle,
            query_right,
            product,
            compose_for_child(inherited, current, 0),
            predicate
        );
    }

   public:
    PersistentSegtreeBeats() : PersistentSegtreeBeats(0) {}

    explicit PersistentSegtreeBeats(int n)
        : _n(n), _root(0), _pool(std::make_shared<Pool>()) {
        assert(0 <= n);
        if (_n > 0) {
            std::vector<T> values(_n, ActedMonoid::id());
            _root = build(0, _n, values);
        }
        _pool->retain(_root);
    }

    explicit PersistentSegtreeBeats(const std::vector<T>& values)
        : _n(int(values.size())),
          _root(0),
          _pool(std::make_shared<Pool>()) {
        _pool->reserve(values.size() * 2);
        if (_n > 0) _root = build(0, _n, values);
        _pool->retain(_root);
    }

    explicit PersistentSegtreeBeats(std::vector<T>&& values)
        : _n(int(values.size())),
          _root(0),
          _pool(std::make_shared<Pool>()) {
        _pool->reserve(values.size() * 2);
        if (_n > 0) _root = build(0, _n, values);
        _pool->retain(_root);
    }

    template <typename U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit PersistentSegtreeBeats(const std::vector<U>& values)
        : _n(int(values.size())),
          _root(0),
          _pool(std::make_shared<Pool>()) {
        _pool->reserve(values.size() * 2);
        if (_n > 0) _root = build_from_values(0, _n, values);
        _pool->retain(_root);
    }

    PersistentSegtreeBeats(const PersistentSegtreeBeats& other)
        : _n(other._n), _root(other._root), _pool(other._pool) {
        if (_pool) _pool->retain(_root);
    }

    PersistentSegtreeBeats(PersistentSegtreeBeats&& other) noexcept
        : _n(other._n),
          _root(other._root),
          _pool(std::move(other._pool)) {
        other._n = 0;
        other._root = 0;
    }

    PersistentSegtreeBeats& operator=(
        const PersistentSegtreeBeats& other
    ) {
        if (this == &other) return *this;
        if (other._pool) other._pool->retain(other._root);
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = other._pool;
        return *this;
    }

    PersistentSegtreeBeats& operator=(
        PersistentSegtreeBeats&& other
    ) noexcept {
        if (this == &other) return *this;
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = std::move(other._pool);
        other._n = 0;
        other._root = 0;
        return *this;
    }

    ~PersistentSegtreeBeats() {
        if (_pool) _pool->release(_root);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    void release() {
        if (_pool) _pool->release(_root);
        _pool = std::make_shared<Pool>();
        _root = 0;
        _n = 0;
    }

    std::size_t node_count() const {
        return _pool ? _pool->size() : 0;
    }

    PersistentSegtreeBeats set(int index, T value) const {
        assert(0 <= index && index < _n);
        return PersistentSegtreeBeats(
            _n,
            set_node(_root, 0, _n, index, std::move(value)),
            _pool
        );
    }

    void set_inplace(int index, T value) {
        assert(0 <= index && index < _n);
        int root = set_node(
            _root,
            0,
            _n,
            index,
            std::move(value),
            true
        );
        _pool->replace(_root, root);
    }

    T get(int index) const {
        assert(0 <= index && index < _n);
        return prod(index, index + 1);
    }

    T operator[](int index) const {
        return get(index);
    }

    T prod(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return ActedMonoid::id();
        return prod_node(
            _root,
            0,
            _n,
            left,
            right,
            ActedMonoid::op_id()
        );
    }

    T all_prod() const {
        return _root ? (*_pool)[_root].val : ActedMonoid::id();
    }

    PersistentSegtreeBeats apply(int index, const F& f) const {
        assert(0 <= index && index < _n);
        return apply(index, index + 1, f);
    }

    PersistentSegtreeBeats apply(
        int left,
        int right,
        const F& f
    ) const {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return *this;
        return PersistentSegtreeBeats(
            _n,
            apply_node(_root, 0, _n, left, right, f),
            _pool
        );
    }

    void apply_inplace(int index, const F& f) {
        assert(0 <= index && index < _n);
        apply_inplace(index, index + 1, f);
    }

    void apply_inplace(int left, int right, const F& f) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return;
        int root = apply_node(
            _root,
            0,
            _n,
            left,
            right,
            f,
            true
        );
        _pool->replace(_root, root);
    }

    PersistentSegtreeBeats copy_range_from(
        const PersistentSegtreeBeats& source,
        int left,
        int right
    ) const {
        assert(_n == source._n);
        assert(_pool == source._pool);
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return *this;
        return PersistentSegtreeBeats(
            _n,
            copy_range_node(
                _root,
                source._root,
                0,
                _n,
                left,
                right
            ),
            _pool
        );
    }

    std::vector<T> to_vector() const {
        return to_vector(0, _n);
    }

    std::vector<T> to_vector(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        std::vector<T> result;
        result.reserve(right - left);
        if (left != right) {
            collect_node(
                _root,
                0,
                _n,
                left,
                right,
                ActedMonoid::op_id(),
                result
            );
        }
        return result;
    }

    template <class Predicate>
    int max_right(int left, Predicate predicate) const {
        assert(0 <= left && left <= _n);
        assert(predicate(ActedMonoid::id()));
        if (left == _n) return _n;
        T product = ActedMonoid::id();
        return max_right_node(
            _root,
            0,
            _n,
            left,
            product,
            ActedMonoid::op_id(),
            predicate
        );
    }

    template <class Predicate>
    int min_left(int right, Predicate predicate) const {
        assert(0 <= right && right <= _n);
        assert(predicate(ActedMonoid::id()));
        if (right == 0) return 0;
        T product = ActedMonoid::id();
        return min_left_node(
            _root,
            0,
            _n,
            right,
            product,
            ActedMonoid::op_id(),
            predicate
        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_PERSISTENT_SEGTREE_BEATS_HPP
