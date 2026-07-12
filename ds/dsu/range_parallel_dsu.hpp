#ifndef M1UNE_DS_DSU_RANGE_PARALLEL_DSU_HPP
#define M1UNE_DS_DSU_RANGE_PARALLEL_DSU_HPP 1

#include <bit>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Merges corresponding vertices of two equal-length ranges.
class RangeParallelDsu {
   private:
    struct LevelDsu {
        std::vector<int> parent_or_size;
        int component_count;

        explicit LevelDsu(int size = 0)
            : parent_or_size(std::size_t(size), -1), component_count(size) {}

        int leader(int vertex) {
            if (parent_or_size[vertex] < 0) return vertex;
            return parent_or_size[vertex] = leader(parent_or_size[vertex]);
        }

        int leader(int vertex) const {
            while (parent_or_size[vertex] >= 0) {
                vertex = parent_or_size[vertex];
            }
            return vertex;
        }

        std::pair<int, int> merge(int first, int second) {
            first = leader(first);
            second = leader(second);
            if (first == second) return {first, -1};
            if (-parent_or_size[first] < -parent_or_size[second]) {
                std::swap(first, second);
            }
            parent_or_size[first] += parent_or_size[second];
            parent_or_size[second] = first;
            component_count--;
            return {first, second};
        }
    };

    int _size;
    std::vector<LevelDsu> _levels;

    static int check_size(int size) {
        assert(size >= 0);
        return size;
    }

    void check_vertex(int vertex) const {
        assert(0 <= vertex && vertex < _size);
    }

    void check_range(int first, int length) const {
        assert(0 <= first && 0 <= length);
        assert(length <= _size);
        assert(first <= _size - length);
    }

    template <class Callback>
    int merge_block(int level, int first, int second, Callback& callback) {
        std::pair<int, int> merged = _levels[level].merge(first, second);
        if (merged.second == -1) return 0;
        if (level == 0) {
            callback(merged.first, merged.second);
            return 1;
        }

        const int half = 1 << (level - 1);
        int result = merge_block(level - 1, first, second, callback);
        result += merge_block(level - 1, first + half, second + half, callback);
        return result;
    }

   public:
    RangeParallelDsu() : RangeParallelDsu(0) {}

    explicit RangeParallelDsu(int size) : _size(check_size(size)) {
        _levels.emplace_back(_size);
        for (int block_size = 2; block_size < _size; block_size *= 2) {
            _levels.emplace_back(_size - block_size + 1);
            if (block_size > _size / 2) break;
        }
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    int component_count() const {
        return _levels[0].component_count;
    }

    int leader(int vertex) {
        check_vertex(vertex);
        return _levels[0].leader(vertex);
    }

    int leader(int vertex) const {
        check_vertex(vertex);
        return _levels[0].leader(vertex);
    }

    bool same(int first, int second) {
        return leader(first) == leader(second);
    }

    bool same(int first, int second) const {
        return leader(first) == leader(second);
    }

    int group_size(int vertex) {
        return -_levels[0].parent_or_size[leader(vertex)];
    }

    int group_size(int vertex) const {
        return -_levels[0].parent_or_size[leader(vertex)];
    }

    template <class Callback>
    int merge(int first, int second, int length, Callback&& callback) {
        check_range(first, length);
        check_range(second, length);
        if (length == 0) return 0;
        if (length == 1) {
            return merge_block(0, first, second, callback);
        }

        const int level = int(std::bit_width(unsigned(length - 1))) - 1;
        const int block_size = 1 << level;
        int result = merge_block(level, first, second, callback);
        result += merge_block(level, first + length - block_size,
                              second + length - block_size, callback);
        return result;
    }

    int merge(int first, int second, int length) {
        auto ignore = [](int, int) {};
        return merge(first, second, length, ignore);
    }

    template <class Callback>
    int merge_ranges(int first_left, int first_right, int second_left,
                     int second_right, Callback&& callback) {
        assert(first_right - first_left == second_right - second_left);
        return merge(first_left, second_left, first_right - first_left,
                     std::forward<Callback>(callback));
    }

    int merge_ranges(int first_left, int first_right, int second_left,
                     int second_right) {
        auto ignore = [](int, int) {};
        return merge_ranges(first_left, first_right, second_left, second_right,
                            ignore);
    }

    template <class Callback>
    int merge(int first, int second, Callback&& callback) {
        check_vertex(first);
        check_vertex(second);
        return merge_block(0, first, second, callback);
    }

    int merge(int first, int second) {
        auto ignore = [](int, int) {};
        return merge(first, second, ignore);
    }
};

using RangeParallelUnionFind = RangeParallelDsu;

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DSU_RANGE_PARALLEL_DSU_HPP
