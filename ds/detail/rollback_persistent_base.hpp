#ifndef M1UNE_DS_DETAIL_ROLLBACK_PERSISTENT_BASE_HPP
#define M1UNE_DS_DETAIL_ROLLBACK_PERSISTENT_BASE_HPP 1

#include <cassert>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {
namespace detail {

template <class Persistent>
struct RollbackPersistentBase : Persistent {
   private:
    std::vector<Persistent> _history;

   protected:
    using Persistent::Persistent;

    const Persistent& persistent() const {
        return *this;
    }

    void commit(Persistent next) {
        assert(_history.size() < std::size_t(std::numeric_limits<int>::max()));
        _history.emplace_back(persistent());
        Persistent::operator=(std::move(next));
    }

   public:
    RollbackPersistentBase() = default;

    explicit RollbackPersistentBase(Persistent initial)
        : Persistent(std::move(initial)) {}

    int history_size() const {
        return int(_history.size());
    }

    void reserve_history(int count) {
        assert(0 <= count);
        _history.reserve(count);
    }

    bool undo() {
        if (_history.empty()) return false;
        Persistent::operator=(std::move(_history.back()));
        _history.pop_back();
        return true;
    }

    int snapshot() const {
        return history_size();
    }

    void rollback(int state) {
        assert(0 <= state && state <= history_size());
        while (history_size() > state) undo();
    }

    void clear_history() {
        _history.clear();
    }

    void release() {
        _history.clear();
        Persistent::release();
    }

    const Persistent& current_version() const {
        return persistent();
    }
};

}  // namespace detail
}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DETAIL_ROLLBACK_PERSISTENT_BASE_HPP
