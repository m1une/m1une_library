#ifndef M1UNE_ORDERED_MULTISET_HPP
#define M1UNE_ORDERED_MULTISET_HPP 1

#include <cassert>
#include <chrono>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <typename T, typename Compare = std::less<T>>
struct OrderedMultiset {
   private:
    struct Node {
        T key;
        int priority;
        int count;
        int size;
        int distinct_size;
        Node* l;
        Node* r;

        Node(T value, int node_priority, int multiplicity)
            : key(std::move(value)),
              priority(node_priority),
              count(multiplicity),
              size(multiplicity),
              distinct_size(1),
              l(nullptr),
              r(nullptr) {}
    };

    static constexpr int pool_block_bits = 14;
    static constexpr int pool_block_size = 1 << pool_block_bits;

    struct Pool {
        std::vector<std::vector<Node>> blocks;

        template <class... Args>
        Node* emplace(Args&&... args) {
            if (blocks.empty() || int(blocks.back().size()) == pool_block_size) {
                blocks.emplace_back();
                blocks.back().reserve(pool_block_size);
            }
            blocks.back().emplace_back(std::forward<Args>(args)...);
            return &blocks.back().back();
        }
    };

    struct Ownership {
        std::shared_ptr<Pool> pool;
        std::shared_ptr<Ownership> l;
        std::shared_ptr<Ownership> r;

        explicit Ownership(std::shared_ptr<Pool> node_pool) : pool(std::move(node_pool)) {}
        Ownership(std::shared_ptr<Ownership> left, std::shared_ptr<Ownership> right)
            : l(std::move(left)), r(std::move(right)) {}
    };

    std::shared_ptr<Pool> allocation_pool;
    std::shared_ptr<Ownership> ownership;
    Node* root;
    std::uint32_t rng_state;
    Compare comp;

    static int subtree_size(const Node* t) {
        return t == nullptr ? 0 : t->size;
    }

    static int subtree_distinct_size(const Node* t) {
        return t == nullptr ? 0 : t->distinct_size;
    }

    bool equal(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }

    int next_priority() {
        rng_state ^= rng_state << 13;
        rng_state ^= rng_state >> 17;
        rng_state ^= rng_state << 5;
        if (rng_state == 0) rng_state = 1;
        return int(rng_state);
    }

    Node* new_node(T key, int multiplicity) {
        return allocation_pool->emplace(std::move(key), next_priority(), multiplicity);
    }

    static void update(Node* t) {
        if (t == nullptr) return;
        t->size = t->count + subtree_size(t->l) + subtree_size(t->r);
        t->distinct_size = 1 + subtree_distinct_size(t->l) + subtree_distinct_size(t->r);
    }

    static Node* merge_nodes(Node* l, Node* r) {
        if (l == nullptr || r == nullptr) return l == nullptr ? r : l;
        if (l->priority > r->priority) {
            l->r = merge_nodes(l->r, r);
            update(l);
            return l;
        }
        r->l = merge_nodes(l, r->l);
        update(r);
        return r;
    }

    std::pair<Node*, Node*> split_nodes(Node* t, const T& key) {
        if (t == nullptr) return {nullptr, nullptr};
        if (comp(t->key, key)) {
            auto [l, r] = split_nodes(t->r, key);
            t->r = l;
            update(t);
            return {t, r};
        }
        auto [l, r] = split_nodes(t->l, key);
        t->l = r;
        update(t);
        return {l, t};
    }

    void rotate_right(Node*& t) {
        Node* s = t->l;
        t->l = s->r;
        s->r = t;
        update(t);
        update(s);
        t = s;
    }

    void rotate_left(Node*& t) {
        Node* s = t->r;
        t->r = s->l;
        s->l = t;
        update(t);
        update(s);
        t = s;
    }

    Node* insert_impl(Node* t, T& key, int multiplicity) {
        if (t == nullptr) return new_node(std::move(key), multiplicity);
        if (equal(key, t->key)) {
            t->count += multiplicity;
            update(t);
            return t;
        }
        if (comp(key, t->key)) {
            t->l = insert_impl(t->l, key, multiplicity);
            if (t->l->priority > t->priority) rotate_right(t);
        } else {
            t->r = insert_impl(t->r, key, multiplicity);
            if (t->r->priority > t->priority) rotate_left(t);
        }
        update(t);
        return t;
    }

    bool erase_one_impl(Node*& t, const T& key) {
        if (t == nullptr) return false;
        bool erased;
        if (equal(key, t->key)) {
            if (t->count > 1) {
                --t->count;
                erased = true;
            } else {
                t = merge_nodes(t->l, t->r);
                return true;
            }
        } else if (comp(key, t->key)) {
            erased = erase_one_impl(t->l, key);
        } else {
            erased = erase_one_impl(t->r, key);
        }
        update(t);
        return erased;
    }

    int erase_all_impl(Node*& t, const T& key) {
        if (t == nullptr) return 0;
        int erased;
        if (equal(key, t->key)) {
            erased = t->count;
            t = merge_nodes(t->l, t->r);
            return erased;
        }
        if (comp(key, t->key)) {
            erased = erase_all_impl(t->l, key);
        } else {
            erased = erase_all_impl(t->r, key);
        }
        update(t);
        return erased;
    }

    static const T* kth_impl(const Node* t, int k) {
        while (t != nullptr) {
            int left_size = subtree_size(t->l);
            if (k < left_size) {
                t = t->l;
            } else if (k < left_size + t->count) {
                return &t->key;
            } else {
                k -= left_size + t->count;
                t = t->r;
            }
        }
        return nullptr;
    }

    int count_impl(const Node* t, const T& key) const {
        while (t != nullptr) {
            if (equal(key, t->key)) return t->count;
            t = comp(key, t->key) ? t->l : t->r;
        }
        return 0;
    }

    int order_of_key_impl(const Node* t, const T& key, bool upper) const {
        int result = 0;
        while (t != nullptr) {
            const bool take = upper ? !comp(key, t->key) : comp(t->key, key);
            if (take) {
                result += subtree_size(t->l) + t->count;
                t = t->r;
            } else {
                t = t->l;
            }
        }
        return result;
    }

    const T* lower_bound_impl(const Node* t, const T& key, bool strict) const {
        const T* result = nullptr;
        while (t != nullptr) {
            const bool candidate = strict ? comp(key, t->key) : !comp(t->key, key);
            if (candidate) {
                result = &t->key;
                t = t->l;
            } else {
                t = t->r;
            }
        }
        return result;
    }

    const T* max_less_impl(const Node* t, const T& key, bool strict) const {
        const T* result = nullptr;
        while (t != nullptr) {
            const bool candidate = strict ? comp(t->key, key) : !comp(key, t->key);
            if (candidate) {
                result = &t->key;
                t = t->r;
            } else {
                t = t->l;
            }
        }
        return result;
    }

    static void dump_impl(const Node* t, std::vector<T>& result) {
        if (t == nullptr) return;
        dump_impl(t->l, result);
        for (int i = 0; i < t->count; ++i) result.push_back(t->key);
        dump_impl(t->r, result);
    }

    Node* clone_impl(const Node* t) {
        if (t == nullptr) return nullptr;
        Node* result = allocation_pool->emplace(t->key, t->priority, t->count);
        result->l = clone_impl(t->l);
        result->r = clone_impl(t->r);
        update(result);
        return result;
    }

    OrderedMultiset(Node* node, std::uint32_t state, Compare compare,
                    std::shared_ptr<Pool> node_pool, std::shared_ptr<Ownership> node_ownership)
        : allocation_pool(std::move(node_pool)),
          ownership(std::move(node_ownership)),
          root(node),
          rng_state(state),
          comp(std::move(compare)) {}

   public:
    explicit OrderedMultiset(Compare compare)
        : allocation_pool(std::make_shared<Pool>()),
          ownership(std::make_shared<Ownership>(allocation_pool)),
          root(nullptr),
          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),
          comp(std::move(compare)) {
        if (rng_state == 0) rng_state = 1;
    }

    OrderedMultiset() : OrderedMultiset(Compare()) {}

    OrderedMultiset(std::initializer_list<T> init, Compare compare = Compare()) : OrderedMultiset(std::move(compare)) {
        for (const T& x : init) insert(x);
    }

    template <typename Iterator>
    OrderedMultiset(Iterator first, Iterator last, Compare compare = Compare()) : OrderedMultiset(std::move(compare)) {
        while (first != last) insert(*first++);
    }

    OrderedMultiset(const OrderedMultiset& other)
        : allocation_pool(std::make_shared<Pool>()),
          ownership(std::make_shared<Ownership>(allocation_pool)),
          root(nullptr),
          rng_state(other.rng_state),
          comp(other.comp) {
        root = clone_impl(other.root);
    }

    OrderedMultiset(OrderedMultiset&&) noexcept = default;

    OrderedMultiset& operator=(OrderedMultiset other) {
        swap(other);
        return *this;
    }

    void swap(OrderedMultiset& other) noexcept {
        using std::swap;
        swap(allocation_pool, other.allocation_pool);
        swap(ownership, other.ownership);
        swap(root, other.root);
        swap(rng_state, other.rng_state);
        swap(comp, other.comp);
    }

    int size() const { return subtree_size(root); }
    int unique_size() const { return subtree_distinct_size(root); }
    bool empty() const { return root == nullptr; }

    void clear() {
        allocation_pool = std::make_shared<Pool>();
        ownership = std::make_shared<Ownership>(allocation_pool);
        root = nullptr;
    }

    void insert(T key, int multiplicity = 1) {
        assert(multiplicity > 0);
        root = insert_impl(root, key, multiplicity);
    }

    bool erase_one(const T& key) { return erase_one_impl(root, key); }
    bool erase(const T& key) { return erase_one(key); }
    int erase_all(const T& key) { return erase_all_impl(root, key); }
    bool contains(const T& key) const { return count(key) > 0; }
    int count(const T& key) const { return count_impl(root, key); }

    const T* find_by_order(int k) const {
        assert(0 <= k && k < size());
        return kth_impl(root, k);
    }

    T kth(int k) const { return *find_by_order(k); }
    int order_of_key(const T& key) const { return order_of_key_impl(root, key, false); }
    int count_less(const T& key) const { return order_of_key(key); }
    int count_less_equal(const T& key) const { return order_of_key_impl(root, key, true); }
    int count_greater(const T& key) const { return size() - count_less_equal(key); }
    int count_greater_equal(const T& key) const { return size() - count_less(key); }
    const T* lower_bound(const T& key) const { return lower_bound_impl(root, key, false); }
    const T* upper_bound(const T& key) const { return lower_bound_impl(root, key, true); }
    const T* min_ge(const T& key) const { return lower_bound(key); }
    const T* min_gt(const T& key) const { return upper_bound(key); }
    const T* max_le(const T& key) const { return max_less_impl(root, key, false); }
    const T* max_lt(const T& key) const { return max_less_impl(root, key, true); }
    const T* min() const { return empty() ? nullptr : kth_impl(root, 0); }
    const T* max() const { return empty() ? nullptr : kth_impl(root, size() - 1); }

    std::pair<OrderedMultiset, OrderedMultiset> split(const T& key) && {
        auto [l, r] = split_nodes(root, key);
        root = nullptr;
        return {OrderedMultiset(l, rng_state, comp, allocation_pool, ownership),
                OrderedMultiset(r, rng_state, std::move(comp),
                                std::move(allocation_pool), std::move(ownership))};
    }

    OrderedMultiset merge(OrderedMultiset other) && {
        assert(empty() || other.empty() || comp(*max(), *other.min()));
        root = merge_nodes(root, other.root);
        other.root = nullptr;
        if (ownership != other.ownership) {
            ownership = std::make_shared<Ownership>(std::move(ownership),
                                                    std::move(other.ownership));
        }
        return std::move(*this);
    }

    std::vector<T> to_vector() const {
        std::vector<T> result;
        result.reserve(size());
        dump_impl(root, result);
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_ORDERED_MULTISET_HPP
