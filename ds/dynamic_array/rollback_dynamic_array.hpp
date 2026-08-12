#ifndef M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_ARRAY_HPP
#define M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_ARRAY_HPP 1

#include <cassert>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

#include "dynamic_array.hpp"

namespace m1une {
namespace ds {

template <class T>
struct RollbackDynamicArray {
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

    DynamicArray<T> _data;
    std::vector<Entry> _history;
    std::vector<std::size_t> _checkpoints;

    void record_insert(int pos, int count) {
        if (!_checkpoints.empty()) {
            _history.push_back(Entry{Kind::insert, pos, count, 0, std::nullopt, {}});
        }
    }

   public:
    RollbackDynamicArray() = default;
    explicit RollbackDynamicArray(int n) : _data(n) {}
    RollbackDynamicArray(int n, const T& value) : _data(n, value) {}
    explicit RollbackDynamicArray(const std::vector<T>& values) : _data(values) {}
    explicit RollbackDynamicArray(std::vector<T>&& values) : _data(std::move(values)) {}
    RollbackDynamicArray(std::initializer_list<T> init) : _data(init) {}

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

    void insert(int pos, const RollbackDynamicArray& other) {
        insert(pos, other.to_vector());
    }

    void insert(int pos, const DynamicArray<T>& other) {
        insert(pos, other.to_vector());
    }

    void push_back(T value) { insert(size(), std::move(value)); }
    void push_front(T value) { insert(0, std::move(value)); }
    void append(const std::vector<T>& values) { insert(size(), values); }
    void append(std::vector<T>&& values) { insert(size(), std::move(values)); }
    void append(const RollbackDynamicArray& other) { insert(size(), other); }
    void append(const DynamicArray<T>& other) { insert(size(), other); }

    void erase(int pos) { erase(pos, pos + 1); }

    void erase(int left, int right) {
        assert(0 <= left && left <= right && right <= size());
        Entry entry{Kind::erase, left, 0, 0, std::nullopt, {}};
        if (!_checkpoints.empty()) entry.values = _data.to_vector(left, right);
        _data.erase(left, right);
        if (!_checkpoints.empty()) _history.push_back(std::move(entry));
    }

    void pop_back() {
        assert(!empty());
        erase(size() - 1);
    }

    void pop_front() {
        assert(!empty());
        erase(0);
    }

    const T& at(int pos) const { return _data.at(pos); }
    const T& operator[](int pos) const { return _data[pos]; }
    const T& front() const { return _data.front(); }
    const T& back() const { return _data.back(); }
    T get(int pos) const { return _data.get(pos); }

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

    std::vector<T> to_vector() const { return _data.to_vector(); }
    std::vector<T> to_vector(int left, int right) const { return _data.to_vector(left, right); }

    std::pair<DynamicArray<T>, DynamicArray<T>> split(int pos) const {
        assert(0 <= pos && pos <= size());
        DynamicArray<T> left = _data;
        DynamicArray<T> right = left.split_off(pos);
        return {std::move(left), std::move(right)};
    }

    DynamicArray<T> split_off(int pos) const {
        return split(pos).second;
    }

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
        if (entry.kind == Kind::insert) {
            _data.erase(entry.first, entry.first + entry.second);
        } else if (entry.kind == Kind::erase) {
            _data.insert(entry.first, std::move(entry.values));
        } else if (entry.kind == Kind::set) {
            _data.set(entry.first, std::move(*entry.value));
        } else if (entry.kind == Kind::reverse) {
            _data.reverse(entry.first, entry.second);
        } else if (entry.kind == Kind::rotate) {
            int new_middle = entry.first + entry.third - entry.second;
            _data.rotate(entry.first, new_middle, entry.third);
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

    void release() {
        _data.clear();
        _history.clear();
        _checkpoints.clear();
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_ARRAY_HPP
