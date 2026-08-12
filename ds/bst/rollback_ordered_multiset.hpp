#ifndef M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP
#define M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP 1

#include <cassert>
#include <functional>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

#include "ordered_multiset.hpp"

namespace m1une {
namespace ds {

template <class T, class Compare = std::less<T>>
struct RollbackOrderedMultiset {
   private:
    enum class Kind { key, clear, merge };
    struct Entry {
        Kind kind;
        std::optional<T> key;
        int old_count;
        std::vector<T> values;
    };

    OrderedMultiset<T, Compare> _data;
    std::vector<Entry> _history;
    std::vector<std::size_t> _checkpoints;

    void restore_count(const T& key, int count) {
        _data.erase_all(key);
        if (count > 0) _data.insert(key, count);
    }

   public:
    explicit RollbackOrderedMultiset(Compare compare)
        : _data(std::move(compare)) {}
    RollbackOrderedMultiset() = default;

    RollbackOrderedMultiset(
        std::initializer_list<T> init,
        Compare compare = Compare()
    ) : _data(init, std::move(compare)) {}

    template <class Iterator>
    RollbackOrderedMultiset(
        Iterator first,
        Iterator last,
        Compare compare = Compare()
    ) : _data(first, last, std::move(compare)) {}

    int size() const { return _data.size(); }
    int unique_size() const { return _data.unique_size(); }
    bool empty() const { return _data.empty(); }
    std::size_t node_count() const { return std::size_t(unique_size()); }

    void clear() {
        if (_checkpoints.empty()) {
            _data.clear();
            return;
        }
        Entry entry{Kind::clear, std::nullopt, 0, {}};
        entry.values = _data.to_vector();
        _data.clear();
        _history.push_back(std::move(entry));
    }

    void insert(T key, int multiplicity = 1) {
        assert(multiplicity > 0);
        if (_checkpoints.empty()) {
            _data.insert(std::move(key), multiplicity);
            return;
        }
        Entry entry{Kind::key, std::optional<T>(key), _data.count(key), {}};
        _data.insert(std::move(key), multiplicity);
        _history.push_back(std::move(entry));
    }

    void insert_inplace(T key, int multiplicity = 1) {
        insert(std::move(key), multiplicity);
    }

    bool erase_one(const T& key) {
        if (_checkpoints.empty()) return _data.erase_one(key);
        int old_count = _data.count(key);
        Entry entry{Kind::key, std::optional<T>(key), old_count, {}};
        bool erased = _data.erase_one(key);
        _history.push_back(std::move(entry));
        return erased;
    }

    bool erase(const T& key) { return erase_one(key); }
    bool erase_one_inplace(const T& key) { return erase_one(key); }
    bool erase_inplace(const T& key) { return erase_one(key); }

    int erase_all(const T& key) {
        int old_count = _data.count(key);
        if (_checkpoints.empty()) {
            _data.erase_all(key);
            return old_count;
        }
        Entry entry{Kind::key, std::optional<T>(key), old_count, {}};
        _data.erase_all(key);
        _history.push_back(std::move(entry));
        return old_count;
    }

    bool erase_all_inplace(const T& key) { return erase_all(key) != 0; }

    void merge(const RollbackOrderedMultiset& other) {
        std::vector<T> values = other.to_vector();
        for (const T& value : values) _data.insert(value);
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::merge, std::nullopt, 0, std::move(values)});
        }
    }

    void merge(const OrderedMultiset<T, Compare>& other) {
        std::vector<T> values = other.to_vector();
        for (const T& value : values) _data.insert(value);
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::merge, std::nullopt, 0, std::move(values)});
        }
    }

    bool contains(const T& key) const { return _data.contains(key); }
    int count(const T& key) const { return _data.count(key); }
    const T* find_by_order(int order) const { return _data.find_by_order(order); }
    T kth(int order) const { return _data.kth(order); }
    int order_of_key(const T& key) const { return _data.order_of_key(key); }
    int count_less(const T& key) const { return _data.count_less(key); }
    int count_less_equal(const T& key) const { return _data.count_less_equal(key); }
    int count_greater(const T& key) const { return _data.count_greater(key); }
    int count_greater_equal(const T& key) const { return _data.count_greater_equal(key); }
    const T* lower_bound(const T& key) const { return _data.lower_bound(key); }
    const T* upper_bound(const T& key) const { return _data.upper_bound(key); }
    const T* min_ge(const T& key) const { return _data.min_ge(key); }
    const T* min_gt(const T& key) const { return _data.min_gt(key); }
    const T* max_le(const T& key) const { return _data.max_le(key); }
    const T* max_lt(const T& key) const { return _data.max_lt(key); }
    const T* min() const { return _data.min(); }
    const T* max() const { return _data.max(); }
    std::vector<T> to_vector() const { return _data.to_vector(); }

    int snapshot() { _checkpoints.push_back(_history.size()); return int(_checkpoints.size()); }
    int snapshot_count() const { return int(_checkpoints.size()); }

    void reserve_snapshots(int count) {
        assert(0 <= count);
        _checkpoints.reserve(count);
    }

   private:
    void restore_one() {
        Entry entry = std::move(_history.back());
        _history.pop_back();
        if (entry.kind == Kind::key) {
            restore_count(*entry.key, entry.old_count);
        } else if (entry.kind == Kind::clear) {
            for (T& value : entry.values) _data.insert(std::move(value));
        } else {
            for (const T& value : entry.values) _data.erase_one(value);
        }
    }

   public:

    void rollback(int state) {
        assert(1 <= state && state <= snapshot_count());
        while (_history.size() > _checkpoints[state - 1]) restore_one();
        _checkpoints.resize(state);
    }

    void clear_history() { _history.clear(); _checkpoints.clear(); }

    void release() {
        _data.clear();
        _history.clear();
        _checkpoints.clear();
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP
