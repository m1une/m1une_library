#ifndef M1UNE_DS_DETAIL_ROLLBACK_JOURNAL_HPP
#define M1UNE_DS_DETAIL_ROLLBACK_JOURNAL_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {
namespace detail {

template <class Node>
struct RollbackJournal {
    struct Change {
        int index;
        Node value;
    };

    struct Checkpoint {
        std::size_t change_size;
        std::size_t node_size;
        std::uint64_t epoch;
    };

    std::vector<Node> nodes;
    std::vector<Change> changes;
    std::vector<Checkpoint> checkpoints;
    std::vector<std::uint64_t> saved_epoch;
    std::uint64_t next_epoch = 1;

    std::uint64_t new_epoch() {
        if (next_epoch == 0) {
            std::fill(saved_epoch.begin(), saved_epoch.end(), 0);
            next_epoch = 1;
        }
        return next_epoch++;
    }

    int size() const { return int(nodes.size()); }

    Node& operator[](int index) { return nodes[index]; }
    const Node& operator[](int index) const { return nodes[index]; }

    template <class... Args>
    int emplace(Args&&... args) {
        assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        int index = int(nodes.size());
        nodes.emplace_back(std::forward<Args>(args)...);
        saved_epoch.push_back(0);
        return index;
    }

    int snapshot() {
        assert(checkpoints.size() < std::size_t(std::numeric_limits<int>::max()));
        checkpoints.push_back(Checkpoint{changes.size(), nodes.size(), new_epoch()});
        return int(checkpoints.size());
    }

    void touch(int index) {
        assert(0 <= index && index < size());
        if (checkpoints.empty()) return;
        const Checkpoint& checkpoint = checkpoints.back();
        if (std::size_t(index) >= checkpoint.node_size) return;
        if (saved_epoch[index] == checkpoint.epoch) return;
        saved_epoch[index] = checkpoint.epoch;
        changes.push_back(Change{index, nodes[index]});
    }

    int snapshot_count() const { return int(checkpoints.size()); }

    void reserve_snapshots(int count) {
        assert(0 <= count);
        checkpoints.reserve(count);
    }

    void reserve_changes(std::size_t count) { changes.reserve(count); }

    void rollback(int state) {
        assert(1 <= state && state <= snapshot_count());
        Checkpoint checkpoint = checkpoints[state - 1];
        while (changes.size() > checkpoint.change_size) {
            Change change = std::move(changes.back());
            changes.pop_back();
            nodes[change.index] = std::move(change.value);
        }
        nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());
        saved_epoch.resize(checkpoint.node_size);
        checkpoints.resize(state);
        checkpoints.back().change_size = changes.size();
        checkpoints.back().node_size = nodes.size();
        checkpoints.back().epoch = new_epoch();
    }

    void clear_history() {
        changes.clear();
        checkpoints.clear();
        std::fill(saved_epoch.begin(), saved_epoch.end(), 0);
    }

    void clear() {
        nodes.clear();
        changes.clear();
        checkpoints.clear();
        saved_epoch.clear();
        next_epoch = 1;
    }
};

}  // namespace detail
}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DETAIL_ROLLBACK_JOURNAL_HPP
