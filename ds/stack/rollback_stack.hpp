#ifndef M1UNE_DS_STACK_ROLLBACK_STACK_HPP
#define M1UNE_DS_STACK_ROLLBACK_STACK_HPP 1

#include <cassert>
#include <optional>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <class T>
struct RollbackStack {
   private:
    enum class Kind { push, pop, clear };
    struct Entry {
        Kind kind;
        std::optional<T> value;
        std::vector<T> values;
    };

    std::vector<T> _values;
    std::vector<Entry> _history;
    std::vector<std::size_t> _checkpoints;
    std::size_t _stored_values = 0;

   public:
    RollbackStack() = default;

    int size() const { return int(_values.size()); }
    bool empty() const { return _values.empty(); }
    std::size_t node_count() const { return _stored_values; }

    const T& top() const {
        assert(!empty());
        return _values.back();
    }

    void push(T value) {
        if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt, {}});
        _values.push_back(std::move(value));
        ++_stored_values;
    }

    template <class... Args>
    void emplace(Args&&... args) {
        if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt, {}});
        _values.emplace_back(std::forward<Args>(args)...);
        ++_stored_values;
    }

    void pop() {
        assert(!empty());
        if (_checkpoints.empty()) {
            _values.pop_back();
            --_stored_values;
        } else {
            Entry entry{Kind::pop, std::nullopt, {}};
            entry.value.emplace(std::move(_values.back()));
            _values.pop_back();
            _history.push_back(std::move(entry));
        }
    }

    void clear() {
        if (_checkpoints.empty()) {
            _stored_values -= _values.size();
            _values.clear();
        } else {
            Entry entry{Kind::clear, std::nullopt, {}};
            entry.values = std::move(_values);
            _values.clear();
            _history.push_back(std::move(entry));
        }
    }

    int snapshot() {
        _checkpoints.push_back(_history.size());
        return int(_checkpoints.size());
    }
    int snapshot_count() const { return int(_checkpoints.size()); }

    void reserve_snapshots(int count) {
        assert(0 <= count);
        _checkpoints.reserve(count);
    }

   private:
    void restore_one() {
        Entry entry = std::move(_history.back());
        _history.pop_back();
        if (entry.kind == Kind::push) {
            _values.pop_back();
            --_stored_values;
        } else if (entry.kind == Kind::pop) {
            _values.push_back(std::move(*entry.value));
        } else {
            _values = std::move(entry.values);
        }
    }

   public:
    void rollback(int state) {
        assert(1 <= state && state <= snapshot_count());
        while (_history.size() > _checkpoints[state - 1]) restore_one();
        _checkpoints.resize(state);
    }

    void clear_history() {
        for (const Entry& entry : _history) {
            if (entry.value) --_stored_values;
            _stored_values -= entry.values.size();
        }
        _history.clear();
        _checkpoints.clear();
    }

    void release() {
        _values.clear();
        _history.clear();
        _checkpoints.clear();
        _stored_values = 0;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_STACK_ROLLBACK_STACK_HPP
