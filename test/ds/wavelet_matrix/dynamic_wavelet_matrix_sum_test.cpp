#include "../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

namespace {

using Key = std::uint32_t;
using Matrix = m1une::ds::DynamicWaveletMatrixSum<Key, long long, 6>;

std::uint64_t random_state = 0x243f6a8885a308d3ULL;

std::uint64_t random_value() {
    random_state ^= random_state << 7;
    random_state ^= random_state >> 9;
    return random_state;
}

int random_int(int lower, int upper) {
    return lower + int(random_value() % std::uint64_t(upper - lower + 1));
}

std::vector<int> sorted_indices(
    const std::vector<Key>& keys,
    int left,
    int right
) {
    std::vector<int> order;
    for (int position = left; position < right; position++) {
        order.push_back(position);
    }
    std::stable_sort(
        order.begin(),
        order.end(),
        [&](int first, int second) { return keys[first] < keys[second]; }
    );
    return order;
}

void check_state(
    const Matrix& matrix,
    const std::vector<Key>& keys,
    const std::vector<long long>& weights
) {
    assert(matrix.size() == int(keys.size()));
    assert(matrix.empty() == keys.empty());
    for (int position = 0; position < int(keys.size()); position++) {
        assert(matrix.access(position) == keys[position]);
        assert(matrix[position] == keys[position]);
        assert(matrix.weight(position) == weights[position]);
        std::pair<Key, long long> expected(
            keys[position],
            weights[position]
        );
        assert(matrix.get(position) == expected);
    }

    int left = random_int(0, int(keys.size()));
    int right = random_int(0, int(keys.size()));
    if (right < left) std::swap(left, right);
    Key lower = Key(random_int(0, 64));
    Key upper = Key(random_int(0, 64));
    if (upper < lower) std::swap(lower, upper);

    long long total = 0;
    long long below = 0;
    long long between = 0;
    int frequency = 0;
    for (int position = left; position < right; position++) {
        total += weights[position];
        if (keys[position] < upper) below += weights[position];
        if (lower <= keys[position] && keys[position] < upper) {
            between += weights[position];
            frequency++;
        }
    }
    assert(matrix.range_sum(left, right) == total);
    assert(matrix.range_sum(left, right, upper) == below);
    assert(matrix.range_sum(left, right, lower, upper) == between);
    assert(matrix.range_freq(left, right, upper) ==
           int(std::count_if(
               keys.begin() + left,
               keys.begin() + right,
               [&](Key key) { return key < upper; }
           )));
    assert(matrix.range_freq(left, right, lower, upper) == frequency);

    Key value = Key(random_int(0, 64));
    assert(matrix.rank(value, left, right) ==
           int(std::count(
               keys.begin() + left,
               keys.begin() + right,
               value
           )));
    assert(matrix.rank(value, right) ==
           int(std::count(keys.begin(), keys.begin() + right, value)));

    std::optional<Key> previous;
    std::optional<Key> next;
    for (int position = left; position < right; position++) {
        if (keys[position] < upper &&
            (!previous.has_value() || previous.value() < keys[position])) {
            previous = keys[position];
        }
        if (lower <= keys[position] &&
            (!next.has_value() || keys[position] < next.value())) {
            next = keys[position];
        }
    }
    assert(matrix.prev_value(left, right, upper) == previous);
    assert(matrix.next_value(left, right, lower) == next);

    std::vector<int> order = sorted_indices(keys, left, right);
    long long smallest_sum = 0;
    long long largest_sum = 0;
    for (int k = 0; k <= int(order.size()); k++) {
        assert(matrix.sum_k_smallest(left, right, k) == smallest_sum);
        assert(matrix.sum_k_largest(left, right, k) == largest_sum);
        if (k < int(order.size())) {
            smallest_sum += weights[order[k]];
            largest_sum += weights[order[order.size() - 1 - k]];
        }
    }
    if (!order.empty()) {
        int k = random_int(0, int(order.size()) - 1);
        assert(matrix.kth_smallest(left, right, k) == keys[order[k]]);
        assert(
            matrix.kth_largest(left, right, k) ==
            keys[order[order.size() - 1 - k]]
        );
    }
}

void check_boundaries(
    const Matrix& matrix,
    const std::vector<Key>& keys,
    const std::vector<long long>& weights,
    int left,
    int right,
    long long limit
) {
    std::vector<int> order = sorted_indices(keys, left, right);
    auto predicate = [limit](long long sum) { return sum <= limit; };

    long long sum = 0;
    int smallest = 0;
    while (smallest < int(order.size()) &&
           sum + weights[order[smallest]] <= limit) {
        sum += weights[order[smallest]];
        smallest++;
    }
    assert(
        matrix.max_count_smallest(left, right, predicate) == smallest
    );

    sum = 0;
    int largest = 0;
    while (largest < int(order.size()) &&
           sum + weights[order[order.size() - 1 - largest]] <= limit) {
        sum += weights[order[order.size() - 1 - largest]];
        largest++;
    }
    assert(matrix.max_count_largest(left, right, predicate) == largest);
}

void test_deterministic() {
    Matrix empty;
    assert(empty.empty());
    assert(empty.range_sum(0, 0) == 0);
    assert(empty.max_count_smallest(0, 0, [](long long) { return true; }) == 0);
    assert(empty.max_count_largest(0, 0, [](long long) { return true; }) == 0);

    std::vector<Key> keys = {63, 7, 7, 0, 7};
    std::vector<long long> weights = {0, 2, 0, 4, 8};
    Matrix matrix(keys, weights);
    check_state(matrix, keys, weights);
    check_boundaries(matrix, keys, weights, 0, 5, 0);
    check_boundaries(matrix, keys, weights, 0, 5, 6);
    check_boundaries(matrix, keys, weights, 0, 5, 100);
    assert(matrix.range_freq(0, 5, Key(64)) == 5);
    assert(matrix.range_sum(0, 5, Key(64)) == 14);

    matrix.insert(2, 7, 16);
    keys.insert(keys.begin() + 2, 7);
    weights.insert(weights.begin() + 2, 16);
    matrix.push_back(63, 1);
    keys.push_back(63);
    weights.push_back(1);
    matrix.set(0, 1, 3);
    keys[0] = 1;
    weights[0] = 3;
    matrix.set_value(1, 63);
    keys[1] = 63;
    matrix.set_weight(2, 5);
    weights[2] = 5;
    matrix.add_weight(3, 6);
    weights[3] += 6;
    std::pair<Key, long long> erased(keys[4], weights[4]);
    assert(matrix.erase(4) == erased);
    keys.erase(keys.begin() + 4);
    weights.erase(weights.begin() + 4);
    check_state(matrix, keys, weights);

    std::vector<Key> negative_keys = {0, 1, 2};
    std::vector<long long> negative_weights = {-3, 5, 20};
    Matrix negative(negative_keys, negative_weights);
    check_boundaries(negative, negative_keys, negative_weights, 0, 3, 10);

    using SignedMatrix =
        m1une::ds::DynamicWaveletMatrixSum<int, long long>;
    std::vector<int> signed_keys;
    signed_keys.push_back(std::numeric_limits<int>::min());
    signed_keys.push_back(-1);
    signed_keys.push_back(0);
    signed_keys.push_back(std::numeric_limits<int>::max());
    SignedMatrix signed_matrix(signed_keys);
    for (int k = 0; k < 4; k++) {
        assert(signed_matrix.kth_smallest(0, 4, k) == signed_keys[k]);
    }
}

void test_randomized() {
    std::vector<Key> keys;
    std::vector<long long> weights;
    Matrix matrix;
    for (int operation = 0; operation < 5000; operation++) {
        int type = random_int(0, 7);
        if (keys.empty()) type = 0;
        if (type == 0) {
            int position = random_int(0, int(keys.size()));
            Key key = Key(random_int(0, 63));
            long long weight = random_int(0, 20);
            keys.insert(keys.begin() + position, key);
            weights.insert(weights.begin() + position, weight);
            matrix.insert(position, key, weight);
        } else if (type == 1 && keys.size() < 160) {
            Key key = Key(random_int(0, 63));
            long long weight = random_int(0, 20);
            keys.push_back(key);
            weights.push_back(weight);
            matrix.push_back(key, weight);
        } else if (type == 2 && keys.size() > 20) {
            int position = random_int(0, int(keys.size()) - 1);
            std::pair<Key, long long> erased(
                keys[position],
                weights[position]
            );
            assert(matrix.erase(position) == erased);
            keys.erase(keys.begin() + position);
            weights.erase(weights.begin() + position);
        } else if (type == 3) {
            int position = random_int(0, int(keys.size()) - 1);
            keys[position] = Key(random_int(0, 63));
            weights[position] = random_int(0, 20);
            matrix.set(position, keys[position], weights[position]);
        } else if (type == 4) {
            int position = random_int(0, int(keys.size()) - 1);
            keys[position] = Key(random_int(0, 63));
            matrix.set_value(position, keys[position]);
        } else if (type == 5) {
            int position = random_int(0, int(keys.size()) - 1);
            weights[position] = random_int(0, 20);
            matrix.set_weight(position, weights[position]);
        } else if (type == 6) {
            int position = random_int(0, int(keys.size()) - 1);
            long long delta = random_int(0, 5);
            weights[position] += delta;
            matrix.add_weight(position, delta);
        } else {
            int position = random_int(0, int(keys.size()) - 1);
            Key key = Key(random_int(0, 63));
            keys[position] = key;
            weights[position] = key;
            matrix.set(position, key);
        }

        if (operation % 7 == 0) check_state(matrix, keys, weights);
        int left = random_int(0, int(keys.size()));
        int right = random_int(0, int(keys.size()));
        if (right < left) std::swap(left, right);
        long long total = 0;
        for (int position = left; position < right; position++) {
            total += weights[position];
        }
        long long limit = random_int(0, int(total + 20));
        check_boundaries(matrix, keys, weights, left, right, limit);
    }
}

}  // namespace

int main() {
    test_deterministic();
    test_randomized();
}
