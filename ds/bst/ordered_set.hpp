#ifndef M1UNE_ORDERED_SET_HPP
#define M1UNE_ORDERED_SET_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <typename T, typename Compare = std::less<T>>
struct OrderedSet {
   private:
    struct Node {
        T key;
        int size;
        int height;
        Node* l;
        Node* r;

        explicit Node(T value)
            : key(std::move(value)), size(1), height(1), l(nullptr), r(nullptr) {}
    };

    static constexpr int pool_block_size = 1 << 15;

    struct Pool {
        std::vector<std::vector<Node>> blocks;
        std::vector<Node*> free_nodes;

        template <class... Args>
        Node* emplace(Args&&... args) {
            if (!free_nodes.empty()) {
                Node* result = free_nodes.back();
                free_nodes.pop_back();
                std::destroy_at(result);
                std::construct_at(result, std::forward<Args>(args)...);
                return result;
            }
            if (blocks.empty() || int(blocks.back().size()) == pool_block_size) {
                blocks.emplace_back();
                blocks.back().reserve(pool_block_size);
            }
            blocks.back().emplace_back(std::forward<Args>(args)...);
            return &blocks.back().back();
        }

        void recycle(Node* node) {
            free_nodes.push_back(node);
        }
    };

    inline static Pool pool;

    Node* root;
    Compare comp;

    static int subtree_size(const Node* t) {
        return t == nullptr ? 0 : t->size;
    }

    static int subtree_height(const Node* t) {
        return t == nullptr ? 0 : t->height;
    }

    Node* new_node(T key) {
        return pool.emplace(std::move(key));
    }

    static void update(Node* t) {
        t->size = 1 + subtree_size(t->l) + subtree_size(t->r);
        t->height = 1 + std::max(subtree_height(t->l), subtree_height(t->r));
    }

    static Node* rotate_right(Node* t) {
        Node* s = t->l;
        t->l = s->r;
        s->r = t;
        update(t);
        update(s);
        return s;
    }

    static Node* rotate_left(Node* t) {
        Node* s = t->r;
        t->r = s->l;
        s->l = t;
        update(t);
        update(s);
        return s;
    }

    static Node* balance(Node* t) {
        if (t == nullptr) return nullptr;
        update(t);
        const int balance_factor = subtree_height(t->l) - subtree_height(t->r);
        if (balance_factor > 1) {
            if (subtree_height(t->l->l) < subtree_height(t->l->r)) {
                t->l = rotate_left(t->l);
            }
            return rotate_right(t);
        }
        if (balance_factor < -1) {
            if (subtree_height(t->r->r) < subtree_height(t->r->l)) {
                t->r = rotate_right(t->r);
            }
            return rotate_left(t);
        }
        return t;
    }

    static Node* join_with_root(Node* l, Node* middle, Node* r) {
        if (subtree_height(l) > subtree_height(r) + 1) {
            l->r = join_with_root(l->r, middle, r);
            return balance(l);
        }
        if (subtree_height(r) > subtree_height(l) + 1) {
            r->l = join_with_root(l, middle, r->l);
            return balance(r);
        }
        middle->l = l;
        middle->r = r;
        return balance(middle);
    }

    static Node* detach_max(Node* t, Node*& maximum) {
        if (t->r == nullptr) {
            maximum = t;
            return t->l;
        }
        t->r = detach_max(t->r, maximum);
        return balance(t);
    }

    static Node* merge_nodes(Node* l, Node* r) {
        if (l == nullptr || r == nullptr) return l == nullptr ? r : l;
        Node* middle;
        l = detach_max(l, middle);
        return join_with_root(l, middle, r);
    }

    std::pair<Node*, Node*> split_nodes(Node* t, const T& key) {
        if (t == nullptr) return {nullptr, nullptr};
        Node* left = t->l;
        Node* right = t->r;
        t->l = nullptr;
        t->r = nullptr;
        if (comp(t->key, key)) {
            auto [l, r] = split_nodes(right, key);
            return {join_with_root(left, t, l), r};
        }
        auto [l, r] = split_nodes(left, key);
        return {l, join_with_root(r, t, right)};
    }

    Node* insert_impl(Node* t, T& key, bool& inserted, bool& grew) {
        if (t == nullptr) {
            inserted = true;
            grew = true;
            return new_node(std::move(key));
        }
        const int old_height = t->height;
        if (comp(key, t->key)) {
            t->l = insert_impl(t->l, key, inserted, grew);
        } else if (comp(t->key, key)) {
            t->r = insert_impl(t->r, key, inserted, grew);
        } else {
            grew = false;
            return t;
        }
        if (!inserted) return t;
        if (!grew) {
            ++t->size;
            return t;
        }
        t = balance(t);
        grew = t->height > old_height;
        return t;
    }

    Node* erase_impl(Node* t, const T& key, bool& erased, bool& shrunk) {
        if (t == nullptr) {
            shrunk = false;
            return nullptr;
        }
        const int old_height = t->height;
        if (comp(key, t->key)) {
            t->l = erase_impl(t->l, key, erased, shrunk);
        } else if (comp(t->key, key)) {
            t->r = erase_impl(t->r, key, erased, shrunk);
        } else {
            erased = true;
            Node* l = t->l;
            Node* r = t->r;
            pool.recycle(t);
            Node* result = merge_nodes(l, r);
            shrunk = subtree_height(result) < old_height;
            return result;
        }
        if (!erased) return t;
        if (!shrunk) {
            --t->size;
            return t;
        }
        t = balance(t);
        shrunk = t->height < old_height;
        return t;
    }

    static const T* kth_impl(const Node* t, int k) {
        while (t != nullptr) {
            const int left_size = subtree_size(t->l);
            if (k < left_size) {
                t = t->l;
            } else if (k == left_size) {
                return &t->key;
            } else {
                k -= left_size + 1;
                t = t->r;
            }
        }
        return nullptr;
    }

    int order_of_key_impl(const Node* t, const T& key, bool upper) const {
        int result = 0;
        while (t != nullptr) {
            const bool take = upper ? !comp(key, t->key) : comp(t->key, key);
            if (take) {
                result += subtree_size(t->l) + 1;
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

    bool contains_impl(const Node* t, const T& key) const {
        while (t != nullptr) {
            if (comp(key, t->key)) {
                t = t->l;
            } else if (comp(t->key, key)) {
                t = t->r;
            } else {
                return true;
            }
        }
        return false;
    }

    static void dump_impl(const Node* t, std::vector<T>& result) {
        if (t == nullptr) return;
        dump_impl(t->l, result);
        result.push_back(t->key);
        dump_impl(t->r, result);
    }

    static void recycle_impl(Node* t) {
        if (t == nullptr) return;
        recycle_impl(t->l);
        recycle_impl(t->r);
        pool.recycle(t);
    }

    Node* clone_impl(const Node* t) {
        if (t == nullptr) return nullptr;
        Node* result = new_node(t->key);
        result->l = clone_impl(t->l);
        result->r = clone_impl(t->r);
        update(result);
        return result;
    }

    OrderedSet(Node* node, Compare compare) : root(node), comp(std::move(compare)) {}

   public:
    explicit OrderedSet(Compare compare)
        : root(nullptr), comp(std::move(compare)) {}

    OrderedSet() : OrderedSet(Compare()) {}

    OrderedSet(std::initializer_list<T> init, Compare compare = Compare()) : OrderedSet(std::move(compare)) {
        for (const T& x : init) insert(x);
    }

    template <typename Iterator>
    OrderedSet(Iterator first, Iterator last, Compare compare = Compare()) : OrderedSet(std::move(compare)) {
        while (first != last) insert(*first++);
    }

    OrderedSet(const OrderedSet& other)
        : root(nullptr), comp(other.comp) {
        root = clone_impl(other.root);
    }

    OrderedSet(OrderedSet&& other) noexcept
        : root(std::exchange(other.root, nullptr)), comp(std::move(other.comp)) {}

    ~OrderedSet() {
        recycle_impl(root);
    }

    OrderedSet& operator=(OrderedSet other) {
        swap(other);
        return *this;
    }

    void swap(OrderedSet& other) noexcept {
        using std::swap;
        swap(root, other.root);
        swap(comp, other.comp);
    }

    int size() const { return subtree_size(root); }
    int unique_size() const { return size(); }
    bool empty() const { return root == nullptr; }

    void clear() {
        recycle_impl(root);
        root = nullptr;
    }

    bool insert(T key) {
        bool inserted = false;
        bool grew = false;
        root = insert_impl(root, key, inserted, grew);
        return inserted;
    }

    bool erase(const T& key) {
        bool erased = false;
        bool shrunk = false;
        root = erase_impl(root, key, erased, shrunk);
        return erased;
    }

    bool contains(const T& key) const { return contains_impl(root, key); }
    int count(const T& key) const { return contains(key) ? 1 : 0; }

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

    std::pair<OrderedSet, OrderedSet> split(const T& key) && {
        auto [l, r] = split_nodes(root, key);
        root = nullptr;
        return {OrderedSet(l, comp), OrderedSet(r, std::move(comp))};
    }

    OrderedSet merge(OrderedSet other) && {
        assert(empty() || other.empty() || comp(*max(), *other.min()));
        root = merge_nodes(root, other.root);
        other.root = nullptr;
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

#endif  // M1UNE_ORDERED_SET_HPP
