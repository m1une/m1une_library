#ifndef M1UNE_STRING_MINIMUM_ROTATION_HPP
#define M1UNE_STRING_MINIMUM_ROTATION_HPP 1

namespace m1une {
namespace string {

// Returns the smallest starting index of a lexicographically minimum cyclic shift.
template <class Sequence>
int minimum_cyclic_shift(const Sequence& sequence) {
    const int size = int(sequence.size());
    if (size == 0) return 0;

    auto less = [&](int left, int right) {
        return sequence[left < size ? left : left - size] <
               sequence[right < size ? right : right - size];
    };

    int answer = 0;
    int start = 0;
    while (start < size) {
        answer = start;
        int scan = start + 1;
        int matched = start;
        while (scan < 2 * size && !less(scan, matched)) {
            if (less(matched, scan)) {
                matched = start;
            } else {
                matched++;
            }
            scan++;
        }

        const int period = scan - matched;
        while (start <= matched) start += period;
    }
    return answer;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_MINIMUM_ROTATION_HPP
