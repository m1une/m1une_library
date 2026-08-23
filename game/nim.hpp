#ifndef M1UNE_GAME_NIM_HPP
#define M1UNE_GAME_NIM_HPP 1

#include <iterator>

namespace m1une {
namespace game {

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

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_NIM_HPP
