#ifndef M1UNE_ALGO_OFFLINE_MO_WITH_UPDATES_HPP
#define M1UNE_ALGO_OFFLINE_MO_WITH_UPDATES_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <vector>

namespace m1une {
namespace algo {

// Offline Mo ordering in (left, right, update time). Array values and the
// before/after values of each point update are owned by the caller.
struct MoWithUpdates {
    struct Query {
        int left;
        int right;
        int time;
        int id;
    };

   private:
    int _n;
    int _update_count = 0;
    std::vector<Query> _queries;

   public:
    MoWithUpdates() : _n(0) {}

    explicit MoWithUpdates(int n) : _n(n) { assert(0 <= n); }

    int size() const { return _n; }

    int query_count() const { return int(_queries.size()); }

    int update_count() const { return _update_count; }

    bool empty() const { return _queries.empty(); }

    const std::vector<Query>& queries() const { return _queries; }

    void reserve(int query_capacity) {
        assert(0 <= query_capacity);
        _queries.reserve(query_capacity);
    }

    void clear() {
        _queries.clear();
        _update_count = 0;
    }

    // Registers one update and returns its zero-based ID. Time t means that
    // updates [0, t) have been applied, including any no-op assignments.
    int add_update() {
        assert(_update_count < std::numeric_limits<int>::max());
        return _update_count++;
    }

    int add_query(int left, int right) { return add_query(left, right, _update_count); }

    // Historical times are allowed, but the updates must already be registered.
    int add_query(int left, int right, int time) {
        assert(0 <= left && left <= right && right <= _n);
        assert(0 <= time && time <= _update_count);
        assert(_queries.size() < std::size_t(std::numeric_limits<int>::max()));
        const int id = query_count();
        _queries.push_back(Query{left, right, time, id});
        return id;
    }

    std::vector<int> order(int block_size = 0) const {
        const int q = query_count();
        if (q == 0) return {};
        auto times = std::minmax_element(_queries.begin(), _queries.end(),
            [](const Query& a, const Query& b) { return a.time < b.time; });
        const int time_span = times.second->time - times.first->time;
        if (block_size <= 0) {
            const double n = _n;
            const double static_size = n / std::sqrt(double(q));
            const double dynamic_size = std::cbrt(n * n * double(time_span) / double(q));
            const double estimate = std::max(static_size, dynamic_size);
            block_size = int(std::clamp(estimate, 1.0, double(std::max(1, _n))));
        }

        struct Entry {
            int left_block;
            int right_block;
            int time;
            int id;
        };
        std::vector<Entry> entries;
        entries.reserve(q);
        for (const Query& query : _queries) {
            entries.push_back(Entry{
                query.left / block_size, query.right / block_size, query.time, query.id});
        }
        std::sort(entries.begin(), entries.end(), [&](const Entry& a, const Entry& b) {
            if (a.left_block != b.left_block) return a.left_block < b.left_block;
            const bool reverse_right = (a.left_block & 1) != 0;
            if (time_span != 0) {
                if (a.right_block != b.right_block) {
                    return reverse_right ? a.right_block > b.right_block : a.right_block < b.right_block;
                }
                if (a.time != b.time) {
                    return ((a.left_block ^ a.right_block) & 1) ? a.time > b.time : a.time < b.time;
                }
            }
            const int a_right = _queries[a.id].right;
            const int b_right = _queries[b.id].right;
            if (a_right != b_right) return reverse_right ? a_right > b_right : a_right < b_right;
            return a.id < b.id;
        });
        std::vector<int> result;
        result.reserve(q);
        for (const Entry& entry : entries) result.push_back(entry.id);
        return result;
    }

    // apply(id, left, right) moves time id -> id + 1; undo(id, left, right)
    // reverses that update. Both must update the array even outside the active
    // range, and must repair the maintained answer when necessary inside it.
    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,
              class Apply, class Undo, class Answer>
    void run(AddLeft add_left, AddRight add_right, RemoveLeft remove_left, RemoveRight remove_right,
             Apply apply, Undo undo, Answer answer, int block_size = 0) const {
        int left = 0;
        int right = 0;
        int time = 0;
        for (int query_index : order(block_size)) {
            const Query& query = _queries[query_index];
            while (time < query.time) {
                apply(time, left, right);
                ++time;
            }
            while (query.time < time) {
                --time;
                undo(time, left, right);
            }
            while (query.left < left) add_left(--left);
            while (right < query.right) add_right(right++);
            while (left < query.left) remove_left(left++);
            while (query.right < right) remove_right(--right);
            answer(query.id);
        }
    }

    template <class Add, class Remove, class Apply, class Undo, class Answer>
    void run(Add add, Remove remove, Apply apply, Undo undo, Answer answer,
             int block_size = 0) const {
        run(add, add, remove, remove, apply, undo, answer, block_size);
    }
};

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_OFFLINE_MO_WITH_UPDATES_HPP
