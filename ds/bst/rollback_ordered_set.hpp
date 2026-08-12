#ifndef M1UNE_DS_BST_ROLLBACK_ORDERED_SET_HPP
#define M1UNE_DS_BST_ROLLBACK_ORDERED_SET_HPP 1

#include <cassert>
#include <functional>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

#include "ordered_set.hpp"

namespace m1une {
namespace ds {

template <class T, class Compare = std::less<T>>
struct RollbackOrderedSet {
   private:
    enum class Kind { insert, erase, clear, merge };
    struct Entry {
        Kind kind;
        bool changed;
        std::optional<T> key;
        std::vector<T> keys;
    };

    OrderedSet<T, Compare> _data;
    std::vector<Entry> _history;
    std::vector<std::size_t> _checkpoints;

   public:
    explicit RollbackOrderedSet(Compare compare)
        : _data(std::move(compare)) {}
    RollbackOrderedSet() = default;

    RollbackOrderedSet(
        std::initializer_list<T> init,
        Compare compare = Compare()
    ) : _data(init, std::move(compare)) {}

    template <class Iterator>
    RollbackOrderedSet(
        Iterator first,
        Iterator last,
        Compare compare = Compare()
    ) : _data(first, last, std::move(compare)) {}

    int size() const { return _data.size(); }
    int unique_size() const { return _data.size(); }
    bool empty() const { return _data.empty(); }
    std::size_t node_count() const { return std::size_t(size()); }

    void clear() {
        if (_checkpoints.empty()) {
            _data.clear();
            return;
        }
        Entry entry{Kind::clear, !empty(), std::nullopt, {}};
        if (!empty()) entry.keys = _data.to_vector();
        _data.clear();
        _history.push_back(std::move(entry));
    }

    bool insert(T key) {
        if (_checkpoints.empty()) return _data.insert(std::move(key));
        bool changed = !_data.contains(key);
        Entry entry{Kind::insert, changed, std::nullopt, {}};
        if (changed) entry.key.emplace(key);
        _data.insert(std::move(key));
        _history.push_back(std::move(entry));
        return changed;
    }

    bool erase(const T& key) {
        if (_checkpoints.empty()) return _data.erase(key);
        bool changed = _data.contains(key);
        Entry entry{Kind::erase, changed, std::nullopt, {}};
        if (changed) entry.key.emplace(key);
        _data.erase(key);
        _history.push_back(std::move(entry));
        return changed;
    }

    void merge(const RollbackOrderedSet& other) {
        std::vector<T> keys = other.to_vector();
        for (const T& key : keys) {
            bool inserted = _data.insert(key);
            assert(inserted);
        }
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::merge, !keys.empty(), std::nullopt, std::move(keys)});
        }
    }

    void merge(const OrderedSet<T, Compare>& other) {
        std::vector<T> keys = other.to_vector();
        for (const T& key : keys) {
            bool inserted = _data.insert(key);
            assert(inserted);
        }
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::merge, !keys.empty(), std::nullopt, std::move(keys)});
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
        if (!entry.changed) return;
        if (entry.kind == Kind::insert) {
            _data.erase(*entry.key);
        } else if (entry.kind == Kind::erase) {
            _data.insert(std::move(*entry.key));
        } else if (entry.kind == Kind::clear) {
            for (T& key : entry.keys) _data.insert(std::move(key));
        } else {
            for (const T& key : entry.keys) _data.erase(key);
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

#endif  // M1UNE_DS_BST_ROLLBACK_ORDERED_SET_HPP
