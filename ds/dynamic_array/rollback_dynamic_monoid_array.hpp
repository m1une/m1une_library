#ifndef M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_MONOID_ARRAY_HPP
#define M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_MONOID_ARRAY_HPP 1

#include <cassert>
#include <concepts>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

#include "dynamic_monoid_array.hpp"

namespace m1une {
namespace ds {

template <class Monoid>
struct RollbackDynamicMonoidArray {
    using T = typename Monoid::value_type;

   private:
    enum class Kind { insert, erase, set, reverse, rotate, clear };
    struct Entry {
        Kind kind;
        int first;
        int second;
        int third;
        std::optional<T> value;
        std::vector<T> values;
    };

    DynamicMonoidArray<Monoid> _data;
    std::vector<Entry> _history;
    std::vector<std::size_t> _checkpoints;

    void record_insert(int pos, int count) {
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::insert, pos, count, 0, std::nullopt, {}});
        }
    }

   public:
    RollbackDynamicMonoidArray() = default;
    explicit RollbackDynamicMonoidArray(int n) : _data(n) {}
    RollbackDynamicMonoidArray(int n, const T& value) : _data(n, value) {}
    explicit RollbackDynamicMonoidArray(const std::vector<T>& values) : _data(values) {}
    explicit RollbackDynamicMonoidArray(std::vector<T>&& values) : _data(std::move(values)) {}

    template <class U>
        requires(!std::same_as<U, T>)
    explicit RollbackDynamicMonoidArray(const std::vector<U>& values) : _data(values) {}

    RollbackDynamicMonoidArray(std::initializer_list<T> init) : _data(init) {}

    int size() const { return _data.size(); }
    bool empty() const { return _data.empty(); }
    std::size_t node_count() const { return std::size_t(size()); }

    void clear() {
        Entry entry{Kind::clear, 0, 0, 0, std::nullopt, {}};
        if (!_checkpoints.empty()) entry.values = _data.to_vector();
        _data.clear();
        if (!_checkpoints.empty()) _history.push_back(std::move(entry));
    }

    void insert(int pos, T value) {
        _data.insert(pos, std::move(value));
        record_insert(pos, 1);
    }

    void insert(int pos, const std::vector<T>& values) {
        _data.insert(pos, values);
        record_insert(pos, int(values.size()));
    }

    void insert(int pos, std::vector<T>&& values) {
        int count = int(values.size());
        _data.insert(pos, std::move(values));
        record_insert(pos, count);
    }

    void insert(int pos, std::initializer_list<T> values) {
        insert(pos, std::vector<T>(values));
    }

    void insert(int pos, const RollbackDynamicMonoidArray& other) {
        insert(pos, other.to_vector());
    }

    void insert(int pos, const DynamicMonoidArray<Monoid>& other) {
        DynamicMonoidArray<Monoid> copy = other;
        insert(pos, copy.to_vector());
    }

    void push_back(T value) { insert(size(), std::move(value)); }
    void push_front(T value) { insert(0, std::move(value)); }
    void append(const std::vector<T>& values) { insert(size(), values); }
    void append(std::vector<T>&& values) { insert(size(), std::move(values)); }
    void append(const RollbackDynamicMonoidArray& other) { insert(size(), other); }
    void append(const DynamicMonoidArray<Monoid>& other) { insert(size(), other); }

    void erase(int pos) { erase(pos, pos + 1); }

    void erase(int left, int right) {
        assert(0 <= left && left <= right && right <= size());
        Entry entry{Kind::erase, left, 0, 0, std::nullopt, {}};
        if (!_checkpoints.empty()) entry.values = _data.to_vector(left, right);
        _data.erase(left, right);
        if (!_checkpoints.empty()) _history.push_back(std::move(entry));
    }

    void pop_back() { assert(!empty()); erase(size() - 1); }
    void pop_front() { assert(!empty()); erase(0); }

    T get(int pos) const { return _data.get(pos); }
    T operator[](int pos) const { return get(pos); }
    T front() const { assert(!empty()); return get(0); }
    T back() const { assert(!empty()); return get(size() - 1); }

    void set(int pos, T value) {
        Entry entry{Kind::set, pos, 0, 0, std::nullopt, {}};
        if (!_checkpoints.empty()) entry.value.emplace(_data.get(pos));
        _data.set(pos, std::move(value));
        if (!_checkpoints.empty()) _history.push_back(std::move(entry));
    }

    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    void reverse(int left, int right) {
        _data.reverse(left, right);
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::reverse, left, right, 0, std::nullopt, {}});
        }
    }

    void reverse() { reverse(0, size()); }

    void rotate(int left, int middle, int right) {
        _data.rotate(left, middle, right);
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::rotate, left, middle, right, std::nullopt, {}});
        }
    }

    T prod(int left, int right) { return _data.prod(left, right); }
    T all_prod() const { return _data.all_prod(); }
    std::vector<T> to_vector() { return _data.to_vector(); }
    std::vector<T> to_vector() const {
        DynamicMonoidArray<Monoid> copy = _data;
        return copy.to_vector();
    }
    std::vector<T> to_vector(int left, int right) { return _data.to_vector(left, right); }
    std::vector<T> to_vector(int left, int right) const {
        DynamicMonoidArray<Monoid> copy = _data;
        return copy.to_vector(left, right);
    }

    int snapshot() { _checkpoints.push_back(_history.size()); return int(_checkpoints.size()); }
    int snapshot_count() const { return int(_checkpoints.size()); }
    void reserve_snapshots(int count) { assert(0 <= count); _checkpoints.reserve(count); }

   private:
    void restore_one() {
        Entry entry = std::move(_history.back());
        _history.pop_back();
        if (entry.kind == Kind::insert) {
            _data.erase(entry.first, entry.first + entry.second);
        } else if (entry.kind == Kind::erase) {
            _data.insert(entry.first, std::move(entry.values));
        } else if (entry.kind == Kind::set) {
            _data.set(entry.first, std::move(*entry.value));
        } else if (entry.kind == Kind::reverse) {
            _data.reverse(entry.first, entry.second);
        } else if (entry.kind == Kind::rotate) {
            _data.rotate(entry.first, entry.first + entry.third - entry.second, entry.third);
        } else {
            _data.insert(0, std::move(entry.values));
        }
    }

   public:
    void rollback(int state) {
        assert(1 <= state && state <= snapshot_count());
        while (_history.size() > _checkpoints[state - 1]) restore_one();
        _checkpoints.resize(state);
    }
    void clear_history() { _history.clear(); _checkpoints.clear(); }
    void release() { _data.clear(); _history.clear(); _checkpoints.clear(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_MONOID_ARRAY_HPP
