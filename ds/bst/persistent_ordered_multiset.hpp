#ifndef M1UNE_PERSISTENT_ORDERED_MULTISET_HPP
#define M1UNE_PERSISTENT_ORDERED_MULTISET_HPP 1

#include <cassert>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <typename T, typename Compare = std::less<T>>
struct PersistentOrderedMultiset {
   private:
    struct Node {
        T key;
        int count;
        int size;
        int distinct_size;
        int rank;
        int l;
        int r;
        bool black;
        bool leaf;

        Node(T value, int multiplicity)
            : key(std::move(value)),
              count(multiplicity),
              size(multiplicity),
              distinct_size(1),
              rank(0),
              l(-1),
              r(-1),
              black(true),
              leaf(true) {}

        Node(T separator, int subtree_size, int unique_count, int node_rank,
             int left, int right, bool is_black)
            : key(std::move(separator)),
              count(0),
              size(subtree_size),
              distinct_size(unique_count),
              rank(node_rank),
              l(left),
              r(right),
              black(is_black),
              leaf(false) {}
    };

    static constexpr int pool_block_bits = 16;
    static constexpr int pool_block_size = 1 << pool_block_bits;
    static constexpr int pool_block_mask = pool_block_size - 1;

    struct Pool {
        std::vector<std::vector<Node>> blocks;
        int node_count = 0;

        const Node& operator[](int index) const {
            return blocks[index >> pool_block_bits][index & pool_block_mask];
        }

        template <class... Args>
        int emplace(Args&&... args) {
            if ((node_count & pool_block_mask) == 0) {
                blocks.emplace_back();
                blocks.back().reserve(pool_block_size);
            }
            blocks.back().emplace_back(std::forward<Args>(args)...);
            return node_count++;
        }
    };

    inline static Pool pool;

    int root;
    Compare comp;

    static int subtree_size(int t) { return t == -1 ? 0 : pool[t].size; }
    static int subtree_distinct_size(int t) { return t == -1 ? 0 : pool[t].distinct_size; }

    bool equal(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }

    static int make_leaf(T key, int count) {
        return pool.emplace(std::move(key), count);
    }

    static int make_node(int l, int r, bool black) {
        assert(l != -1 && r != -1);
        const int rank = pool[l].rank + int(pool[l].black);
        assert(rank == pool[r].rank + int(pool[r].black));
        return pool.emplace(pool[r].key,
                            subtree_size(l) + subtree_size(r),
                            subtree_distinct_size(l) + subtree_distinct_size(r),
                            rank, l, r, black);
    }

    static int as_root(int t) {
        if (t == -1 || pool[t].black) return t;
        return make_node(pool[t].l, pool[t].r, true);
    }

    static int merge_sub(int a, int b) {
        assert(a != -1 && b != -1);
        if (pool[a].rank < pool[b].rank) {
            const Node& right = pool[b];
            int c = merge_sub(a, right.l);
            if (right.black && !pool[c].black && !pool[pool[c].l].black) {
                const Node& middle = pool[c];
                if (pool[right.r].black) {
                    return make_node(middle.l,
                                     make_node(middle.r, right.r, false),
                                     true);
                }
                const Node& far = pool[right.r];
                return make_node(make_node(middle.l, middle.r, true),
                                 make_node(far.l, far.r, true),
                                 false);
            }
            return make_node(c, right.r, right.black);
        }
        if (pool[a].rank > pool[b].rank) {
            const Node& left = pool[a];
            int c = merge_sub(left.r, b);
            if (left.black && !pool[c].black && !pool[pool[c].r].black) {
                const Node& middle = pool[c];
                if (pool[left.l].black) {
                    return make_node(make_node(left.l, middle.l, false),
                                     middle.r, true);
                }
                const Node& far = pool[left.l];
                return make_node(make_node(far.l, far.r, true),
                                 make_node(middle.l, middle.r, true),
                                 false);
            }
            return make_node(left.l, c, left.black);
        }
        return make_node(a, b, false);
    }

    static int merge_nodes(int a, int b) {
        if (a == -1 || b == -1) return a == -1 ? b : a;
        return as_root(merge_sub(as_root(a), as_root(b)));
    }

    std::pair<int, int> split_nodes(int t, const T& key) const {
        if (t == -1) return {-1, -1};
        const Node& node = pool[t];
        if (node.leaf) return comp(node.key, key) ? std::pair{t, -1} : std::pair{-1, t};
        if (comp(pool[node.l].key, key)) {
            auto [l, r] = split_nodes(node.r, key);
            return {merge_nodes(as_root(node.l), l), r};
        }
        auto [l, r] = split_nodes(node.l, key);
        return {l, merge_nodes(r, as_root(node.r))};
    }

    int set_count_impl(int t, const T& key, int count) const {
        const Node& node = pool[t];
        if (node.leaf) {
            assert(equal(node.key, key));
            return make_leaf(node.key, count);
        }
        if (!comp(pool[node.l].key, key)) {
            return make_node(set_count_impl(node.l, key, count), node.r, node.black);
        }
        return make_node(node.l, set_count_impl(node.r, key, count), node.black);
    }

    int count_impl(int t, const T& key) const {
        if (t == -1) return 0;
        while (!pool[t].leaf) {
            t = !comp(pool[pool[t].l].key, key) ? pool[t].l : pool[t].r;
        }
        return equal(pool[t].key, key) ? pool[t].count : 0;
    }

    const T* kth_impl(int t, int k) const {
        while (!pool[t].leaf) {
            const int left_size = subtree_size(pool[t].l);
            if (k < left_size) {
                t = pool[t].l;
            } else {
                k -= left_size;
                t = pool[t].r;
            }
        }
        return &pool[t].key;
    }

    int order_of_key_impl(int t, const T& key, bool upper) const {
        int result = 0;
        while (t != -1 && !pool[t].leaf) {
            const Node& node = pool[t];
            const T& separator = pool[node.l].key;
            const bool take_left = upper ? !comp(key, separator) : comp(separator, key);
            if (take_left) {
                result += subtree_size(node.l);
                t = node.r;
            } else {
                t = node.l;
            }
        }
        if (t != -1) {
            const bool take_leaf = upper ? !comp(key, pool[t].key) : comp(pool[t].key, key);
            if (take_leaf) result += pool[t].count;
        }
        return result;
    }

    const T* lower_bound_impl(int t, const T& key, bool strict) const {
        const T* result = nullptr;
        while (t != -1) {
            const Node& node = pool[t];
            if (node.leaf) {
                const bool candidate = strict ? comp(key, node.key) : !comp(node.key, key);
                return candidate ? &node.key : result;
            }
            const T& separator = pool[node.l].key;
            const bool go_left = strict ? comp(key, separator) : !comp(separator, key);
            if (go_left) {
                int candidate = node.r;
                while (!pool[candidate].leaf) candidate = pool[candidate].l;
                result = &pool[candidate].key;
                t = node.l;
            } else {
                t = node.r;
            }
        }
        return result;
    }

    const T* max_less_impl(int t, const T& key, bool strict) const {
        const T* result = nullptr;
        while (t != -1) {
            const Node& node = pool[t];
            if (node.leaf) {
                const bool candidate = strict ? comp(node.key, key) : !comp(key, node.key);
                return candidate ? &node.key : result;
            }
            const T& separator = pool[node.l].key;
            const bool take_left = strict ? comp(separator, key) : !comp(key, separator);
            if (take_left) {
                result = &separator;
                t = node.r;
            } else {
                t = node.l;
            }
        }
        return result;
    }

    static void dump_impl(int t, std::vector<T>& result) {
        if (t == -1) return;
        const Node& node = pool[t];
        if (node.leaf) {
            for (int i = 0; i < node.count; ++i) result.push_back(node.key);
            return;
        }
        dump_impl(node.l, result);
        dump_impl(node.r, result);
    }

    static std::pair<int, int> pop_min(int t) {
        assert(t != -1);
        const Node& node = pool[t];
        if (node.leaf) return {t, -1};
        auto [minimum, rest] = pop_min(node.l);
        return {minimum, merge_nodes(rest, as_root(node.r))};
    }

    PersistentOrderedMultiset(int node, Compare compare) : root(node), comp(std::move(compare)) {}

   public:
    explicit PersistentOrderedMultiset(Compare compare) : root(-1), comp(std::move(compare)) {}
    PersistentOrderedMultiset() : PersistentOrderedMultiset(Compare()) {}

    PersistentOrderedMultiset(std::initializer_list<T> init, Compare compare = Compare())
        : PersistentOrderedMultiset(std::move(compare)) {
        for (const T& x : init) *this = insert(x);
    }

    template <typename Iterator>
    PersistentOrderedMultiset(Iterator first, Iterator last, Compare compare = Compare())
        : PersistentOrderedMultiset(std::move(compare)) {
        while (first != last) *this = insert(*first++);
    }

    int size() const { return subtree_size(root); }
    int unique_size() const { return subtree_distinct_size(root); }
    bool empty() const { return root == -1; }
    PersistentOrderedMultiset clear() const { return PersistentOrderedMultiset(-1, comp); }

    PersistentOrderedMultiset insert(T key, int multiplicity = 1) const {
        assert(multiplicity > 0);
        const int old_count = count(key);
        if (old_count != 0) {
            return PersistentOrderedMultiset(set_count_impl(root, key, old_count + multiplicity), comp);
        }
        auto [l, r] = split_nodes(root, key);
        return PersistentOrderedMultiset(merge_nodes(merge_nodes(l, make_leaf(std::move(key), multiplicity)), r), comp);
    }

    PersistentOrderedMultiset erase_one(const T& key) const {
        const int old_count = count(key);
        if (old_count == 0) return *this;
        if (old_count > 1) return PersistentOrderedMultiset(set_count_impl(root, key, old_count - 1), comp);
        auto [l, r] = split_nodes(root, key);
        auto [discarded, rest] = pop_min(r);
        assert(equal(pool[discarded].key, key));
        return PersistentOrderedMultiset(merge_nodes(l, rest), comp);
    }

    PersistentOrderedMultiset erase(const T& key) const { return erase_one(key); }

    PersistentOrderedMultiset erase_all(const T& key) const {
        const int old_count = count(key);
        if (old_count == 0) return *this;
        PersistentOrderedMultiset result = *this;
        if (old_count > 1) result = PersistentOrderedMultiset(set_count_impl(root, key, 1), comp);
        return result.erase_one(key);
    }

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
    const T* max() const { return empty() ? nullptr : &pool[root].key; }

    std::pair<PersistentOrderedMultiset, PersistentOrderedMultiset> split(const T& key) const {
        auto [l, r] = split_nodes(root, key);
        return {PersistentOrderedMultiset(l, comp), PersistentOrderedMultiset(r, comp)};
    }

    PersistentOrderedMultiset merge(const PersistentOrderedMultiset& other) const {
        assert(empty() || other.empty() || comp(*max(), *other.min()));
        return PersistentOrderedMultiset(merge_nodes(root, other.root), comp);
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

#endif  // M1UNE_PERSISTENT_ORDERED_MULTISET_HPP
