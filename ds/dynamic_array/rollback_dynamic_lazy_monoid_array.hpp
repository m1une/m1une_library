#ifndef M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP
#define M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <vector>

#include "../../acted_monoid/concept.hpp"
#include "../detail/rollback_journal.hpp"

namespace m1une {
namespace ds {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct RollbackDynamicLazyMonoidArray {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    static constexpr bool value_commutative = [] {
        if constexpr (requires { ActedMonoid::commutative; }) {
            return bool(ActedMonoid::commutative);
        } else {
            return false;
        }
    }();

    struct EmptyReverseProduct {};
    using ReverseProduct = std::conditional_t<value_commutative, EmptyReverseProduct, T>;

    static constexpr bool count_stored_in_value = requires(const T& value) {
        { ActedMonoid::size(value) } -> std::convertible_to<int>;
    };

    struct EmptyCount {};
    using Count = std::conditional_t<count_stored_in_value, EmptyCount, int>;

    static ReverseProduct make_reverse_product(const T& value) {
        if constexpr (value_commutative) {
            return {};
        } else {
            return value;
        }
    }

    static Count make_count(int count) {
        if constexpr (count_stored_in_value) {
            return {};
        } else {
            return count;
        }
    }

    struct Node {
        T val;
        T prod;
        [[no_unique_address]] ReverseProduct rprod;
        F lazy;
        std::uint32_t priority : 30;
        std::uint32_t rev : 1;
        std::uint32_t has_lazy : 1;
        [[no_unique_address]] Count count;
        int l, r;

        Node()
            : val(ActedMonoid::id()),
              prod(ActedMonoid::id()),
              rprod(make_reverse_product(prod)),
              lazy(ActedMonoid::op_id()),
              priority(0),
              rev(false),
              has_lazy(false),
              count(make_count(0)),
              l(0),
              r(0) {}

        Node(T value, int node_priority)
            : val(std::move(value)),
              prod(val),
              rprod(make_reverse_product(val)),
              lazy(ActedMonoid::op_id()),
              priority(std::uint32_t(node_priority)),
              rev(false),
              has_lazy(false),
              count(make_count(1)),
              l(0),
              r(0) {}
    };

    detail::RollbackJournal<Node> _journal;
    struct StateCheckpoint { int root; int free_head; };
    std::vector<StateCheckpoint> _state_checkpoints;
    int root;
    int free_head;
    std::uint32_t rng_state;

    int node_count(int t) const {
        if constexpr (count_stored_in_value) {
            return int(ActedMonoid::size(_journal[t].prod));
        } else {
            return _journal[t].count;
        }
    }

    void set_node_count(int t, int count) {
        _journal.touch(t);
        if constexpr (!count_stored_in_value) {
            _journal[t].count = count;
        }
    }

    template <typename U>
    static T make_value(const U& value) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else {
            return static_cast<T>(value);
        }
    }

    static T mapping_at(const F& f, const T& value, long long ord) {
        if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {
            return ActedMonoid::mapping(f, value, ord);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static F shift_operator(const F& f, long long ord) {
        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {
            return ActedMonoid::op_shift(f, ord);
        } else {
            return f;
        }
    }

    static F reverse_operator(const F& f, long long size) {
        if constexpr (requires(F g, long long n) { ActedMonoid::op_reverse(g, n); }) {
            return ActedMonoid::op_reverse(f, size);
        } else {
            return f;
        }
    }

    int new_node(T value) {
        int priority = next_priority();
        if (free_head) {
            int res = free_head;
            _journal.touch(res);
            free_head = _journal[res].l;
            _journal[res] = Node(std::move(value), priority);
            return res;
        }
        _journal.emplace(std::move(value), priority);
        return int(_journal.nodes.size()) - 1;
    }

    void release_node(int t) {
        _journal.touch(t);
        _journal[t].l = free_head;
        free_head = t;
    }

    int next_priority() {
        rng_state ^= rng_state << 13;
        rng_state ^= rng_state >> 17;
        rng_state ^= rng_state << 5;
        return int(rng_state);
    }

    void update(int t) {
        if (!t) return;
        _journal.touch(t);
        int l = _journal[t].l;
        int r = _journal[t].r;
        set_node_count(t, 1 + node_count(l) + node_count(r));
        _journal[t].prod = ActedMonoid::op(ActedMonoid::op(_journal[l].prod, _journal[t].val), _journal[r].prod);
        if constexpr (!value_commutative) {
            _journal[t].rprod = ActedMonoid::op(ActedMonoid::op(_journal[r].rprod, _journal[t].val), _journal[l].rprod);
        }
    }

    void all_apply(int t, const F& f) {
        if (!t) return;
        _journal.touch(t);
        int left_count = node_count(_journal[t].l);
        _journal[t].val = mapping_at(f, _journal[t].val, left_count);
        _journal[t].prod = mapping_at(f, _journal[t].prod, 0);
        if constexpr (!value_commutative) {
            _journal[t].rprod = mapping_at(reverse_operator(f, node_count(t)), _journal[t].rprod, 0);
        }
        _journal[t].lazy = ActedMonoid::op_comp(f, _journal[t].lazy);
        _journal[t].has_lazy = true;
    }

    void apply_reverse(int t) {
        if (!t) return;
        _journal.touch(t);
        std::swap(_journal[t].l, _journal[t].r);
        _journal[t].rev = !_journal[t].rev;
        if constexpr (!value_commutative) {
            std::swap(_journal[t].prod, _journal[t].rprod);
        }
        if (_journal[t].has_lazy) {
            _journal[t].lazy = reverse_operator(_journal[t].lazy, node_count(t));
        }
    }

    void push(int t) {
        if (!t) return;
        _journal.touch(t);
        if (_journal[t].rev) {
            apply_reverse(_journal[t].l);
            apply_reverse(_journal[t].r);
            _journal[t].rev = false;
        }
        if (_journal[t].has_lazy) {
            all_apply(_journal[t].l, _journal[t].lazy);
            all_apply(_journal[t].r, shift_operator(_journal[t].lazy, node_count(_journal[t].l) + 1));
            _journal[t].lazy = ActedMonoid::op_id();
            _journal[t].has_lazy = false;
        }
    }

    void split(int t, int pos, int& l, int& r) {
        if (!t) {
            l = r = 0;
            return;
        }
        if (pos == 0) {
            l = 0;
            r = t;
            return;
        }
        if (pos == node_count(t)) {
            l = t;
            r = 0;
            return;
        }
        _journal.touch(t);
        push(t);
        int left_count = node_count(_journal[t].l);
        if (pos == left_count) {
            l = _journal[t].l;
            _journal[t].l = 0;
            update(t);
            r = t;
            return;
        }
        if (pos == left_count + 1) {
            r = _journal[t].r;
            _journal[t].r = 0;
            update(t);
            l = t;
            return;
        }
        if (pos <= left_count) {
            split(_journal[t].l, pos, l, _journal[t].l);
            r = t;
        } else {
            split(_journal[t].r, pos - left_count - 1, _journal[t].r, r);
            l = t;
        }
        update(t);
    }

    int merge(int l, int r) {
        if (!l || !r) return l ? l : r;
        if (_journal[l].priority > _journal[r].priority) {
            push(l);
            _journal.touch(l);
            if (_journal[l].r) {
                _journal[l].r = merge(_journal[l].r, r);
            } else {
                _journal[l].r = r;
            }
            update(l);
            return l;
        } else {
            push(r);
            _journal.touch(r);
            if (_journal[r].l) {
                _journal[r].l = merge(l, _journal[r].l);
            } else {
                _journal[r].l = l;
            }
            update(r);
            return r;
        }
    }

    void split_three(int t, int ql, int qr, int& a, int& b, int& c) {
        if (ql == qr) {
            split(t, ql, a, c);
            b = 0;
            return;
        }
        if (ql == 0 && qr == node_count(t)) {
            a = c = 0;
            b = t;
            return;
        }
        _journal.touch(t);
        push(t);
        int left_count = node_count(_journal[t].l);
        if (qr <= left_count) {
            split_three(_journal[t].l, ql, qr, a, b, _journal[t].l);
            c = t;
            update(t);
        } else if (left_count < ql) {
            split_three(_journal[t].r, ql - left_count - 1, qr - left_count - 1, _journal[t].r, b, c);
            a = t;
            update(t);
        } else {
            split(_journal[t].l, ql, a, _journal[t].l);
            split(_journal[t].r, qr - left_count - 1, _journal[t].r, c);
            b = t;
            update(t);
        }
    }

    int merge_three(int a, int b, int c) {
        if (!a) return merge(b, c);
        if (!b) return merge(a, c);
        if (!c) return merge(a, b);
        std::uint32_t pa = _journal[a].priority;
        std::uint32_t pb = _journal[b].priority;
        std::uint32_t pc = _journal[c].priority;
        if (pb >= pa && pb >= pc) {
            push(b);
            _journal.touch(b);
            _journal[b].l = merge(a, _journal[b].l);
            _journal[b].r = merge(_journal[b].r, c);
            update(b);
            return b;
        }
        if (pa >= pc) {
            push(a);
            _journal.touch(a);
            _journal[a].r = merge_three(_journal[a].r, b, c);
            update(a);
            return a;
        }
        push(c);
        _journal.touch(c);
        _journal[c].l = merge_three(a, b, _journal[c].l);
        update(c);
        return c;
    }

    int insert_node(int t, int pos, int node) {
        if (!t) return node;
        if (_journal[node].priority > _journal[t].priority) {
            _journal.touch(node);
            split(t, pos, _journal[node].l, _journal[node].r);
            update(node);
            return node;
        }
        push(t);
        _journal.touch(t);
        int left_count = node_count(_journal[t].l);
        if (pos <= left_count) {
            _journal[t].l = insert_node(_journal[t].l, pos, node);
        } else {
            _journal[t].r = insert_node(_journal[t].r, pos - left_count - 1, node);
        }
        update(t);
        return t;
    }

    int erase_node(int t, int pos) {
        push(t);
        _journal.touch(t);
        int left_count = node_count(_journal[t].l);
        if (pos < left_count) {
            _journal[t].l = erase_node(_journal[t].l, pos);
            update(t);
            return t;
        }
        if (pos == left_count) {
            int res = merge(_journal[t].l, _journal[t].r);
            release_node(t);
            return res;
        }
        _journal[t].r = erase_node(_journal[t].r, pos - left_count - 1);
        update(t);
        return t;
    }

    void set_node(int t, int pos, T value) {
        push(t);
        _journal.touch(t);
        int left_count = node_count(_journal[t].l);
        if (pos < left_count) {
            set_node(_journal[t].l, pos, std::move(value));
        } else if (pos == left_count) {
            _journal[t].val = std::move(value);
        } else {
            set_node(_journal[t].r, pos - left_count - 1, std::move(value));
        }
        update(t);
    }

    void apply_node(int t, int pos, const F& f) {
        push(t);
        _journal.touch(t);
        int left_count = node_count(_journal[t].l);
        if (pos < left_count) {
            apply_node(_journal[t].l, pos, f);
        } else if (pos == left_count) {
            _journal[t].val = mapping_at(f, _journal[t].val, 0);
        } else {
            apply_node(_journal[t].r, pos - left_count - 1, f);
        }
        update(t);
    }

    void apply_range(int t, int ql, int qr, const F& f) {
        if (ql == 0 && qr == node_count(t)) {
            all_apply(t, f);
            return;
        }
        push(t);
        _journal.touch(t);
        int left_count = node_count(_journal[t].l);
        if (qr <= left_count) {
            apply_range(_journal[t].l, ql, qr, f);
        } else if (left_count < ql) {
            apply_range(_journal[t].r, ql - left_count - 1, qr - left_count - 1, f);
        } else {
            if (ql < left_count) {
                apply_range(_journal[t].l, ql, left_count, f);
            }
            _journal[t].val = mapping_at(f, _journal[t].val, left_count - ql);
            if (left_count + 1 < qr) {
                apply_range(_journal[t].r, 0, qr - left_count - 1,
                            shift_operator(f, left_count + 1 - ql));
            }
        }
        update(t);
    }

    T prod_range(int t, int ql, int qr) {
        if (ql == 0 && qr == node_count(t)) return _journal[t].prod;
        push(t);
        int left_count = node_count(_journal[t].l);
        if (qr <= left_count) {
            return prod_range(_journal[t].l, ql, qr);
        }
        if (left_count < ql) {
            return prod_range(_journal[t].r, ql - left_count - 1, qr - left_count - 1);
        }
        T res = _journal[t].val;
        if (ql < left_count) {
            res = ActedMonoid::op(prod_range(_journal[t].l, ql, left_count), res);
        }
        if (left_count + 1 < qr) {
            res = ActedMonoid::op(res, prod_range(_journal[t].r, 0, qr - left_count - 1));
        }
        return res;
    }

    int find_node(int t, int pos) {
        while (t) {
            push(t);
            int left_count = node_count(_journal[t].l);
            if (pos < left_count) {
                t = _journal[t].l;
            } else if (pos == left_count) {
                return t;
            } else {
                pos -= left_count + 1;
                t = _journal[t].r;
            }
        }
        return 0;
    }

    void dump_dfs(int t, std::vector<T>& res) {
        if (!t) return;
        push(t);
        dump_dfs(_journal[t].l, res);
        res.push_back(_journal[t].val);
        dump_dfs(_journal[t].r, res);
        update(t);
    }

    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>& res) {
        if (!t || qr <= offset || offset + node_count(t) <= ql) return;
        push(t);
        int left_count = node_count(_journal[t].l);
        int node_pos = offset + left_count;
        dump_range_dfs(_journal[t].l, ql, qr, offset, res);
        if (ql <= node_pos && node_pos < qr) {
            res.push_back(_journal[t].val);
        }
        dump_range_dfs(_journal[t].r, ql, qr, node_pos + 1, res);
        update(t);
    }

    int clone_subtree_from(const RollbackDynamicLazyMonoidArray& other, int t) {
        if (!t) return 0;
        Node source = other._journal[t];
        int res = int(_journal.nodes.size());
        _journal.emplace(std::move(source));
        _journal[res].l = clone_subtree_from(other, other._journal[t].l);
        _journal[res].r = clone_subtree_from(other, other._journal[t].r);
        return res;
    }

    void update_dfs(int t) {
        if (!t) return;
        update_dfs(_journal[t].l);
        update_dfs(_journal[t].r);
        update(t);
    }

    int build_cartesian(int first, int last) {
        if (first == last) return 0;
        std::vector<int> stack;
        stack.reserve(last - first);
        for (int i = first; i < last; i++) {
            int left_child = 0;
            while (!stack.empty() && _journal[stack.back()].priority < _journal[i].priority) {
                left_child = stack.back();
                stack.pop_back();
            }
            _journal[i].l = left_child;
            if (!stack.empty()) {
                _journal[stack.back()].r = i;
            }
            stack.push_back(i);
        }
        int res = stack.front();
        update_dfs(res);
        return res;
    }

    int build_from_vector(const std::vector<T>& v) {
        int saved_free_head = std::exchange(free_head, 0);
        int first = int(_journal.nodes.size());
        _journal.nodes.reserve(_journal.nodes.size() + v.size());
        for (const T& x : v) {
            new_node(x);
        }
        int result = build_cartesian(first, int(_journal.nodes.size()));
        free_head = saved_free_head;
        return result;
    }

    int build_from_vector(std::vector<T>&& v) {
        int saved_free_head = std::exchange(free_head, 0);
        int first = int(_journal.nodes.size());
        _journal.nodes.reserve(_journal.nodes.size() + v.size());
        for (T& x : v) {
            new_node(std::move(x));
        }
        int result = build_cartesian(first, int(_journal.nodes.size()));
        free_head = saved_free_head;
        return result;
    }

    template <typename U>
    int build_from_values(const std::vector<U>& v) {
        int saved_free_head = std::exchange(free_head, 0);
        int first = int(_journal.nodes.size());
        _journal.nodes.reserve(_journal.nodes.size() + v.size());
        for (const U& x : v) {
            new_node(make_value(x));
        }
        int result = build_cartesian(first, int(_journal.nodes.size()));
        free_head = saved_free_head;
        return result;
    }

    void release_subtree(int t) {
        if (!t) return;
        std::vector<int> stack(1, t);
        while (!stack.empty()) {
            int node = stack.back();
            stack.pop_back();
            int left = _journal[node].l;
            int right = _journal[node].r;
            if (left) stack.push_back(left);
            if (right) stack.push_back(right);
            release_node(node);
        }
    }

    void reset_to_empty() {
        _journal.clear();
        _journal.emplace();
        root = 0;
        _state_checkpoints.clear();
        free_head = 0;
    }

   public:
    RollbackDynamicLazyMonoidArray()
        : root(0),
          free_head(0),
          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())) {
        _journal.emplace();
        if (rng_state == 0) rng_state = 1;
    }

    RollbackDynamicLazyMonoidArray(const RollbackDynamicLazyMonoidArray& other)
        : root(other.root), free_head(other.free_head), rng_state(other.rng_state) {
        _journal.nodes = other._journal.nodes;
        _journal.saved_epoch.assign(_journal.nodes.size(), 0);
    }

    RollbackDynamicLazyMonoidArray(RollbackDynamicLazyMonoidArray&& other) noexcept
        : _journal(std::move(other._journal)),
          _state_checkpoints(std::move(other._state_checkpoints)),
          root(other.root),
          free_head(other.free_head),
          rng_state(other.rng_state) {
        other.reset_to_empty();
    }

    RollbackDynamicLazyMonoidArray& operator=(const RollbackDynamicLazyMonoidArray& other) {
        if (this != &other) {
            _journal.nodes = other._journal.nodes;
            _journal.saved_epoch.assign(_journal.nodes.size(), 0);
            _journal.changes.clear();
            _journal.checkpoints.clear();
            _state_checkpoints.clear();
            root = other.root;
            free_head = other.free_head;
            rng_state = other.rng_state;
        }
        return *this;
    }

    RollbackDynamicLazyMonoidArray& operator=(RollbackDynamicLazyMonoidArray&& other) noexcept {
        if (this != &other) {
            _journal = std::move(other._journal);
            _state_checkpoints = std::move(other._state_checkpoints);
            root = other.root;
            free_head = other.free_head;
            rng_state = other.rng_state;
            other.reset_to_empty();
        }
        return *this;
    }

    explicit RollbackDynamicLazyMonoidArray(int n)
        : RollbackDynamicLazyMonoidArray(n, ActedMonoid::id()) {}

    RollbackDynamicLazyMonoidArray(int n, const T& value) : RollbackDynamicLazyMonoidArray() {
        assert(0 <= n);
        _journal.nodes.reserve(n + 1);
        int first = int(_journal.nodes.size());
        for (int i = 0; i < n; i++) {
            new_node(value);
        }
        root = build_cartesian(first, int(_journal.nodes.size()));
    }

    explicit RollbackDynamicLazyMonoidArray(const std::vector<T>& v) : RollbackDynamicLazyMonoidArray() {
        _journal.nodes.reserve(v.size() + 1);
        root = build_from_vector(v);
    }

    explicit RollbackDynamicLazyMonoidArray(std::vector<T>&& v) : RollbackDynamicLazyMonoidArray() {
        _journal.nodes.reserve(v.size() + 1);
        root = build_from_vector(std::move(v));
    }

    template <typename U>
        requires(!std::same_as<U, T>) && (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)
    explicit RollbackDynamicLazyMonoidArray(const std::vector<U>& v) : RollbackDynamicLazyMonoidArray() {
        _journal.nodes.reserve(v.size() + 1);
        root = build_from_values(v);
    }

    RollbackDynamicLazyMonoidArray(std::initializer_list<T> init) : RollbackDynamicLazyMonoidArray() {
        _journal.nodes.reserve(init.size() + 1);
        for (const T& x : init) push_back(x);
    }

    int size() const {
        return node_count(root);
    }

    std::size_t node_count() const { return _journal.nodes.size() - 1; }

    void reserve(std::size_t capacity) {
        _journal.nodes.reserve(capacity + 1);
        _journal.saved_epoch.reserve(capacity + 1);
    }

    bool empty() const {
        return size() == 0;
    }

    void clear() {
        release_subtree(root);
        root = 0;
    }

    void insert(int pos, T value) {
        assert(0 <= pos && pos <= size());
        root = insert_node(root, pos, new_node(std::move(value)));
    }

    void insert(int pos, const std::vector<T>& v) {
        assert(0 <= pos && pos <= size());
        _journal.nodes.reserve(_journal.nodes.size() + v.size());
        int mid = build_from_vector(v);
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void insert(int pos, std::vector<T>&& v) {
        assert(0 <= pos && pos <= size());
        _journal.nodes.reserve(_journal.nodes.size() + v.size());
        int mid = build_from_vector(std::move(v));
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void insert(int pos, std::initializer_list<T> init) {
        insert(pos, std::vector<T>(init));
    }

    void insert(int pos, const RollbackDynamicLazyMonoidArray& other) {
        assert(0 <= pos && pos <= size());
        if (other.empty()) return;
        _journal.nodes.reserve(_journal.nodes.size() + other.size());
        int mid = clone_subtree_from(other, other.root);
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void push_back(T value) {
        insert(size(), std::move(value));
    }

    void push_front(T value) {
        insert(0, std::move(value));
    }

    void append(const std::vector<T>& v) {
        insert(size(), v);
    }

    void append(std::vector<T>&& v) {
        insert(size(), std::move(v));
    }

    void append(const RollbackDynamicLazyMonoidArray& other) {
        insert(size(), other);
    }

    void erase(int pos) {
        assert(0 <= pos && pos < size());
        root = erase_node(root, pos);
    }

    void erase(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return;
        int a, b, c;
        split_three(root, l, r, a, b, c);
        release_subtree(b);
        root = merge(a, c);
    }

    void pop_back() {
        assert(!empty());
        erase(size() - 1);
    }

    void pop_front() {
        assert(!empty());
        erase(0);
    }

    T get(int pos) {
        assert(0 <= pos && pos < size());
        int t = find_node(root, pos);
        return _journal[t].val;
    }

    T operator[](int pos) {
        return get(pos);
    }

    T front() {
        assert(!empty());
        return get(0);
    }

    T back() {
        assert(!empty());
        return get(size() - 1);
    }

    void set(int pos, T value) {
        assert(0 <= pos && pos < size());
        set_node(root, pos, std::move(value));
    }

    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return;
        int a, b, c;
        split_three(root, l, r, a, b, c);
        apply_reverse(b);
        root = merge_three(a, b, c);
    }

    void reverse() {
        apply_reverse(root);
    }

    void rotate(int l, int m, int r) {
        assert(0 <= l && l <= m && m <= r && r <= size());
        if (l == m || m == r) return;
        int a, b, c, d;
        split(root, l, a, b);
        split(b, m - l, b, c);
        split(c, r - m, c, d);
        root = merge(merge(a, c), merge(b, d));
    }

    void apply(int pos, const F& f) {
        assert(0 <= pos && pos < size());
        apply_node(root, pos, f);
    }

    void apply(int l, int r, const F& f) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return;
        apply_range(root, l, r, f);
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return ActedMonoid::id();
        return prod_range(root, l, r);
    }

    T all_prod() const {
        return _journal[root].prod;
    }

    std::vector<T> to_vector() {
        std::vector<T> res;
        res.reserve(size());
        dump_dfs(root, res);
        return res;
    }

    std::vector<T> to_vector(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        std::vector<T> res;
        res.reserve(r - l);
        dump_range_dfs(root, l, r, 0, res);
        return res;
    }

    RollbackDynamicLazyMonoidArray split_off(int pos) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = l;

        RollbackDynamicLazyMonoidArray res;
        res._journal.nodes.reserve(node_count(r) + 1);
        res.root = res.clone_subtree_from(*this, r);
        release_subtree(r);
        return res;
    }

    void set_inplace(int pos, T value) { set(pos, std::move(value)); }
    void apply_inplace(int pos, const F& f) { apply(pos, f); }
    void apply_inplace(int left, int right, const F& f) { apply(left, right, f); }

    int snapshot() {
        int state = _journal.snapshot();
        _state_checkpoints.push_back(StateCheckpoint{root, free_head});
        assert(state == int(_state_checkpoints.size()));
        return state;
    }
    int snapshot_count() const { return int(_state_checkpoints.size()); }
    void reserve_snapshots(int count) {
        assert(0 <= count);
        _journal.reserve_snapshots(count);
        _state_checkpoints.reserve(count);
    }
    void rollback(int state) {
        assert(1 <= state && state <= snapshot_count());
        StateCheckpoint checkpoint = _state_checkpoints[state - 1];
        _journal.rollback(state);
        root = checkpoint.root;
        free_head = checkpoint.free_head;
        _state_checkpoints.resize(state);
    }
    void clear_history() {
        _journal.clear_history();
        _state_checkpoints.clear();
    }
    void release() { reset_to_empty(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP
