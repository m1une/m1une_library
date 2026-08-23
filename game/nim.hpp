#ifndef M1UNE_GAME_NIM_HPP
#define M1UNE_GAME_NIM_HPP 1

#include <iterator>
#include <optional>
#include <type_traits>
#include <utility>

namespace m1une {
namespace game {

template <typename T>
struct NimMove {
    int heap;
    T new_size;
};

template <typename Iterator>
auto nim_sum(Iterator first, Iterator last) {
    using T = typename std::iterator_traits<Iterator>::value_type;
    T result{};
    while (first != last) {
        result ^= *first;
        ++first;
    }
    return result;
}

template <typename Range>
auto nim_sum(const Range& heaps) {
    using std::begin;
    using std::end;
    return nim_sum(begin(heaps), end(heaps));
}

template <typename Range>
bool nim_first_player_wins(const Range& heaps) {
    return nim_sum(heaps) != 0;
}

template <typename Range>
auto nim_winning_move(const Range& heaps) {
    using std::begin;
    using std::end;
    using T = std::decay_t<decltype(*begin(heaps))>;

    const T sum = nim_sum(heaps);
    if (sum == 0) return std::optional<NimMove<T>>{};
    int index = 0;
    for (
        auto iterator = begin(heaps);
        iterator != end(heaps);
        ++iterator, ++index
    ) {
        const T new_size = *iterator ^ sum;
        if (new_size < *iterator) return std::optional(NimMove<T>{index, new_size});
    }
    return std::optional<NimMove<T>>{};
}

template <typename Range>
bool misere_nim_first_player_wins(const Range& heaps) {
    using std::begin;
    using std::end;

    auto first = begin(heaps);
    const auto last = end(heaps);
    bool odd_nonzero_heaps = false;
    bool has_large_heap = false;
    using T = typename std::iterator_traits<decltype(first)>::value_type;
    T sum{};
    for (; first != last; ++first) {
        sum ^= *first;
        if (*first != 0) {
            odd_nonzero_heaps = !odd_nonzero_heaps;
        }
        if (*first > 1) has_large_heap = true;
    }
    return has_large_heap ? sum != 0 : !odd_nonzero_heaps;
}

template <typename Range>
auto misere_nim_winning_move(const Range& heaps) {
    using std::begin;
    using std::end;
    using T = std::decay_t<decltype(*begin(heaps))>;

    T sum{};
    int ones = 0;
    int large_heaps = 0;
    int only_large_heap = -1;
    int index = 0;
    for (
        auto iterator = begin(heaps);
        iterator != end(heaps);
        ++iterator, ++index
    ) {
        sum ^= *iterator;
        if (*iterator == 1) ones++;
        if (*iterator > 1) {
            large_heaps++;
            only_large_heap = index;
        }
    }

    if (large_heaps == 0) {
        if (ones == 0 || ones % 2 == 1) return std::optional<NimMove<T>>{};
        index = 0;
        for (
            auto iterator = begin(heaps);
            iterator != end(heaps);
            ++iterator, ++index
        ) {
            if (*iterator == 1) return std::optional(NimMove<T>{index, T(0)});
        }
    }
    if (large_heaps == 1) {
        const T new_size = ones % 2 == 0 ? T(1) : T(0);
        return std::optional(NimMove<T>{only_large_heap, new_size});
    }
    if (sum == 0) return std::optional<NimMove<T>>{};

    index = 0;
    for (auto iterator = begin(heaps); iterator != end(heaps); ++iterator, ++index) {
        const T new_size = *iterator ^ sum;
        if (new_size < *iterator) return std::optional(NimMove<T>{index, new_size});
    }
    return std::optional<NimMove<T>>{};
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_NIM_HPP
