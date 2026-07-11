#ifndef M1UNE_ROLLBACK_DSU_HPP
#define M1UNE_ROLLBACK_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace ds {

struct RollbackDsu {
   private:
    struct HistoryEntry {
        int first;
        int first_value;
        int second;
        int second_value;
    };

    int _n;
    int _component_count;
    std::vector<int> parent_or_size;
    std::vector<HistoryEntry> history;

    static int check_size(int n) {
        assert(0 <= n);
        return n;
    }

   public:
    RollbackDsu() : RollbackDsu(0) {}

    explicit RollbackDsu(int n)
        : _n(check_size(n)), _component_count(_n), parent_or_size(_n, -1) {}

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int component_count() const {
        return _component_count;
    }

    int history_size() const {
        return int(history.size());
    }

    void reserve_history(int count) {
        assert(0 <= count);
        history.reserve(count);
    }

    int leader(int vertex) const {
        assert(0 <= vertex && vertex < _n);
        while (parent_or_size[vertex] >= 0) vertex = parent_or_size[vertex];
        return vertex;
    }

    bool same(int first, int second) const {
        return leader(first) == leader(second);
    }

    int group_size(int vertex) const {
        return -parent_or_size[leader(vertex)];
    }

    int size(int vertex) const {
        return group_size(vertex);
    }

    bool merge(int first, int second) {
        first = leader(first);
        second = leader(second);
        if (first == second) {
            history.push_back(HistoryEntry{-1, 0, -1, 0});
            return false;
        }
        if (-parent_or_size[first] < -parent_or_size[second]) {
            std::swap(first, second);
        }
        history.push_back(HistoryEntry{
            first, parent_or_size[first], second, parent_or_size[second]
        });
        parent_or_size[first] += parent_or_size[second];
        parent_or_size[second] = first;
        _component_count--;
        return true;
    }

    bool undo() {
        if (history.empty()) return false;
        const HistoryEntry entry = history.back();
        history.pop_back();
        if (entry.first == -1) return true;
        parent_or_size[entry.first] = entry.first_value;
        parent_or_size[entry.second] = entry.second_value;
        _component_count++;
        return true;
    }

    int snapshot() const {
        return history_size();
    }

    void rollback(int state) {
        assert(0 <= state && state <= history_size());
        while (history_size() > state) undo();
    }

    std::vector<std::vector<int>> groups() const {
        std::vector<int> leader_buffer(_n);
        std::vector<int> group_sizes(_n, 0);
        for (int vertex = 0; vertex < _n; vertex++) {
            leader_buffer[vertex] = leader(vertex);
            group_sizes[leader_buffer[vertex]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int vertex = 0; vertex < _n; vertex++) {
            result[vertex].reserve(group_sizes[vertex]);
        }
        for (int vertex = 0; vertex < _n; vertex++) {
            result[leader_buffer[vertex]].push_back(vertex);
        }
        result.erase(
            std::remove_if(
                result.begin(), result.end(),
                [](const std::vector<int>& group) { return group.empty(); }
            ),
            result.end()
        );
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_ROLLBACK_DSU_HPP
