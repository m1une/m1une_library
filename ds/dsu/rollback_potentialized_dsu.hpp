#ifndef M1UNE_DS_DSU_ROLLBACK_POTENTIALIZED_DSU_HPP
#define M1UNE_DS_DSU_ROLLBACK_POTENTIALIZED_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsGroup Group>
    requires std::equality_comparable<typename Group::value_type>
struct RollbackPotentializedDsu {
    using T = typename Group::value_type;

   private:
    struct HistoryEntry {
        int first;
        int first_value;
        int second;
        int second_value;
        T second_diff;

        HistoryEntry(int first_index, int first_parent, int second_index,
                     int second_parent, T diff)
            : first(first_index),
              first_value(first_parent),
              second(second_index),
              second_value(second_parent),
              second_diff(std::move(diff)) {}
    };

    int _n;
    int _component_count;
    std::vector<int> _parent_or_size;
    std::vector<T> _diff_to_parent;
    std::vector<HistoryEntry> _history;

    static int check_size(int n) {
        assert(0 <= n);
        return n;
    }

    std::pair<int, T> leader_and_potential(int vertex) const {
        assert(0 <= vertex && vertex < _n);
        T result = Group::id();
        while (_parent_or_size[vertex] >= 0) {
            result = Group::op(_diff_to_parent[vertex], result);
            vertex = _parent_or_size[vertex];
        }
        return {vertex, std::move(result)};
    }

   public:
    RollbackPotentializedDsu() : RollbackPotentializedDsu(0) {}

    explicit RollbackPotentializedDsu(int n)
        : _n(check_size(n)),
          _component_count(_n),
          _parent_or_size(_n, -1),
          _diff_to_parent(_n, Group::id()) {}

    int size() const { return _n; }
    bool empty() const { return _n == 0; }
    int component_count() const { return _component_count; }
    int history_size() const { return int(_history.size()); }

    void reserve_history(int count) {
        assert(0 <= count);
        _history.reserve(count);
    }

    int leader(int vertex) const {
        return leader_and_potential(vertex).first;
    }

    bool same(int first, int second) const {
        return leader(first) == leader(second);
    }

    int group_size(int vertex) const {
        return -_parent_or_size[leader(vertex)];
    }

    int size(int vertex) const { return group_size(vertex); }

    T potential(int vertex) const {
        return leader_and_potential(vertex).second;
    }

    T diff(int first, int second) const {
        assert(same(first, second));
        return Group::op(Group::inv(potential(first)), potential(second));
    }

    int parent_or_size(int vertex) const {
        assert(0 <= vertex && vertex < _n);
        return _parent_or_size[vertex];
    }

    bool merge(int first, int second, const T& difference) {
        auto [first_root, first_potential] = leader_and_potential(first);
        auto [second_root, second_potential] = leader_and_potential(second);
        if (first_root == second_root) {
            _history.emplace_back(-1, 0, -1, 0, Group::id());
            return Group::op(Group::inv(first_potential), second_potential) == difference;
        }

        T second_from_first = Group::op(
            Group::op(first_potential, difference),
            Group::inv(second_potential)
        );
        if (-_parent_or_size[first_root] < -_parent_or_size[second_root]) {
            std::swap(first_root, second_root);
            second_from_first = Group::inv(second_from_first);
        }

        _history.emplace_back(
            first_root, _parent_or_size[first_root], second_root,
            _parent_or_size[second_root], _diff_to_parent[second_root]
        );
        _parent_or_size[first_root] += _parent_or_size[second_root];
        _parent_or_size[second_root] = first_root;
        _diff_to_parent[second_root] = std::move(second_from_first);
        --_component_count;
        return true;
    }

    bool undo() {
        if (_history.empty()) return false;
        HistoryEntry entry = std::move(_history.back());
        _history.pop_back();
        if (entry.first == -1) return true;
        _parent_or_size[entry.first] = entry.first_value;
        _parent_or_size[entry.second] = entry.second_value;
        _diff_to_parent[entry.second] = std::move(entry.second_diff);
        ++_component_count;
        return true;
    }

    int snapshot() const { return history_size(); }

    void rollback(int state) {
        assert(0 <= state && state <= history_size());
        while (history_size() > state) undo();
    }

    std::vector<std::vector<int>> groups() const {
        std::vector<int> leaders(_n);
        std::vector<int> sizes(_n);
        for (int vertex = 0; vertex < _n; ++vertex) {
            leaders[vertex] = leader(vertex);
            ++sizes[leaders[vertex]];
        }
        std::vector<std::vector<int>> result(_n);
        for (int vertex = 0; vertex < _n; ++vertex) {
            result[vertex].reserve(sizes[vertex]);
        }
        for (int vertex = 0; vertex < _n; ++vertex) {
            result[leaders[vertex]].push_back(vertex);
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

#endif  // M1UNE_DS_DSU_ROLLBACK_POTENTIALIZED_DSU_HPP
