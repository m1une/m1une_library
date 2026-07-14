#ifndef M1UNE_DS_BST_PREDECESSOR_SET_HPP
#define M1UNE_DS_BST_PREDECESSOR_SET_HPP 1

#include <bit>
#include <cassert>
#include <cstdint>
#include <limits>
#include <string_view>
#include <vector>

namespace m1une {
namespace ds {

// Fixed-universe integer set with predecessor and successor queries.
struct PredecessorSet {
   private:
    static constexpr int word_bits = 64;

    int _universe_size;
    int _size;
    std::vector<std::vector<std::uint64_t>> _levels;

    static int checked_size(std::string_view membership) {
        assert(
            membership.size()
            <= static_cast<std::size_t>(std::numeric_limits<int>::max())
        );
        return int(membership.size());
    }

    int next_index(int index) const {
        if (index >= _universe_size) return _universe_size;
        for (int level = 0; level < int(_levels.size()); level++) {
            if (index / word_bits >= int(_levels[level].size())) break;
            std::uint64_t word =
                _levels[level][index / word_bits] >> (index % word_bits);
            if (word == 0) {
                index = index / word_bits + 1;
                continue;
            }
            index += int(std::countr_zero(word));
            for (int lower = level - 1; lower >= 0; lower--) {
                index *= word_bits;
                std::uint64_t lower_word =
                    _levels[lower][index / word_bits];
                index += int(std::countr_zero(lower_word));
            }
            return index;
        }
        return _universe_size;
    }

    int previous_index(int index) const {
        if (_universe_size == 0 || index < 0) return -1;
        if (index >= _universe_size) index = _universe_size - 1;
        for (int level = 0; level < int(_levels.size()); level++) {
            int offset = index % word_bits;
            std::uint64_t word = _levels[level][index / word_bits];
            if (offset != word_bits - 1) {
                word &= (std::uint64_t(1) << (offset + 1)) - 1;
            }
            if (word == 0) {
                index = index / word_bits - 1;
                if (index < 0) break;
                continue;
            }
            index += word_bits - 1 - int(std::countl_zero(word)) - offset;
            for (int lower = level - 1; lower >= 0; lower--) {
                index *= word_bits;
                std::uint64_t lower_word =
                    _levels[lower][index / word_bits];
                index += word_bits - 1 - int(std::countl_zero(lower_word));
            }
            return index;
        }
        return -1;
    }

    static int not_found_if_end(int index, int universe_size) {
        return index == universe_size ? -1 : index;
    }

   public:
    PredecessorSet() : PredecessorSet(0) {}

    explicit PredecessorSet(int universe_size)
        : _universe_size(universe_size), _size(0) {
        assert(universe_size >= 0);
        int length = universe_size == 0 ? 1 : universe_size;
        do {
            int words = int((std::int64_t(length) + word_bits - 1) / word_bits);
            _levels.emplace_back(words, 0);
            length = words;
        } while (length > 1);
    }

    explicit PredecessorSet(std::string_view membership)
        : PredecessorSet(checked_size(membership)) {
        for (int index = 0; index < _universe_size; index++) {
            assert(membership[index] == '0' || membership[index] == '1');
            if (membership[index] == '1') {
                _levels[0][index / word_bits]
                    |= std::uint64_t(1) << (index % word_bits);
                _size++;
            }
        }
        for (int level = 1; level < int(_levels.size()); level++) {
            for (int index = 0; index < int(_levels[level - 1].size()); index++) {
                if (_levels[level - 1][index] != 0) {
                    _levels[level][index / word_bits]
                        |= std::uint64_t(1) << (index % word_bits);
                }
            }
        }
    }

    int universe_size() const {
        return _universe_size;
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    bool contains(int key) const {
        assert(0 <= key && key < _universe_size);
        return ((_levels[0][key / word_bits] >> (key % word_bits)) & 1U) != 0;
    }

    bool insert(int key) {
        assert(0 <= key && key < _universe_size);
        if (contains(key)) return false;
        int index = key;
        for (auto& level : _levels) {
            std::uint64_t& word = level[index / word_bits];
            bool was_empty = word == 0;
            word |= std::uint64_t(1) << (index % word_bits);
            if (!was_empty) break;
            index /= word_bits;
        }
        _size++;
        return true;
    }

    bool erase(int key) {
        assert(0 <= key && key < _universe_size);
        if (!contains(key)) return false;
        int index = key;
        for (auto& level : _levels) {
            std::uint64_t& word = level[index / word_bits];
            word &= ~(std::uint64_t(1) << (index % word_bits));
            if (word != 0) break;
            index /= word_bits;
        }
        _size--;
        return true;
    }

    // Returns the smallest key greater than or equal to key, or -1.
    int successor(int key) const {
        assert(0 <= key && key < _universe_size);
        return not_found_if_end(next_index(key), _universe_size);
    }

    // Returns the largest key less than or equal to key, or -1.
    int predecessor(int key) const {
        assert(0 <= key && key < _universe_size);
        return previous_index(key);
    }

    int min_ge(int key) const {
        return successor(key);
    }

    int min_gt(int key) const {
        assert(0 <= key && key < _universe_size);
        return not_found_if_end(next_index(key + 1), _universe_size);
    }

    int max_le(int key) const {
        return predecessor(key);
    }

    int max_lt(int key) const {
        assert(0 <= key && key < _universe_size);
        return previous_index(key - 1);
    }

    int min() const {
        return not_found_if_end(next_index(0), _universe_size);
    }

    int max() const {
        return previous_index(_universe_size - 1);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BST_PREDECESSOR_SET_HPP
