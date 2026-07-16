#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include "../../../ds/wavelet_matrix/dynamic_wavelet_matrix.hpp"
#include "../../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <vector>

namespace {

using Matrix = m1une::ds::DynamicWaveletMatrix<int>;

std::uint64_t random_state = 0x123456789abcdef0ULL;

std::uint64_t random_value() {
    random_state ^= random_state << 7;
    random_state ^= random_state >> 9;
    return random_state;
}

int random_int() {
    return int(std::uint32_t(random_value()));
}

void check_queries(const Matrix& matrix, const std::vector<int>& values) {
    assert(matrix.size() == int(values.size()));
    assert(matrix.empty() == values.empty());
    for (int i = 0; i < int(values.size()); i++) {
        assert(matrix[i] == values[i]);
    }
    if (values.empty()) return;

    int left = int(random_value() % values.size());
    int right = left + 1 + int(random_value() % (values.size() - left));
    int value = random_int();
    int rank = int(std::count(
        values.begin() + left,
        values.begin() + right,
        value
    ));
    assert(matrix.rank(value, left, right) == rank);
    assert(
        matrix.rank(value, right) ==
        int(std::count(values.begin(), values.begin() + right, value))
    );

    int first_bound = random_int();
    int second_bound = random_int();
    int lower = std::min(first_bound, second_bound);
    int upper = std::max(first_bound, second_bound);
    int below = 0;
    int between = 0;
    for (int i = left; i < right; i++) {
        below += values[i] < upper;
        between += lower <= values[i] && values[i] < upper;
    }
    assert(matrix.range_freq(left, right, upper) == below);
    assert(matrix.range_freq(left, right, lower, upper) == between);

    std::vector<int> sorted(values.begin() + left, values.begin() + right);
    std::sort(sorted.begin(), sorted.end());
    int k = int(random_value() % sorted.size());
    assert(matrix.kth_smallest(left, right, k) == sorted[k]);
    assert(
        matrix.kth_largest(left, right, k) ==
        sorted[sorted.size() - 1 - k]
    );

    auto expected_previous = std::lower_bound(sorted.begin(), sorted.end(), upper);
    std::optional<int> previous;
    if (expected_previous != sorted.begin()) previous = *--expected_previous;
    assert(matrix.prev_value(left, right, upper) == previous);

    auto expected_next = std::lower_bound(sorted.begin(), sorted.end(), lower);
    std::optional<int> next;
    if (expected_next != sorted.end()) next = *expected_next;
    assert(matrix.next_value(left, right, lower) == next);
}

void test_randomized() {
    std::vector<int> edge_values = {
        std::numeric_limits<int>::min(),
        -1,
        0,
        1,
        std::numeric_limits<int>::max()
    };
    Matrix edge_matrix(edge_values);
    check_queries(edge_matrix, edge_values);

    std::vector<signed char> byte_values = {-128, 5, -1, 127};
    m1une::ds::DynamicWaveletMatrix<signed char> byte_matrix(byte_values);
    assert(byte_matrix.kth_smallest(0, 4, 1) == -1);
    byte_matrix.set(1, -100);
    byte_matrix.insert(2, 100);
    assert(
        byte_matrix.range_freq(0, 5, static_cast<signed char>(0)) == 3
    );

    using Unsigned = unsigned long long;
    std::vector<Unsigned> unsigned_values = {
        0,
        std::numeric_limits<Unsigned>::max(),
        Unsigned(1) << 63
    };
    m1une::ds::DynamicWaveletMatrix<Unsigned> unsigned_matrix(
        unsigned_values
    );
    assert(
        unsigned_matrix.kth_largest(0, 3, 0) ==
        std::numeric_limits<Unsigned>::max()
    );
    unsigned_matrix.clear();
    assert(unsigned_matrix.empty());

    for (int trial = 0; trial < 120; trial++) {
        int initial_size = int(random_value() % 50);
        std::vector<int> values(initial_size);
        for (int& value : values) value = random_int();
        Matrix matrix(values);

        for (int operation = 0; operation < 250; operation++) {
            int type = int(random_value() % 5);
            if (values.empty()) type = 0;
            if (type == 0) {
                int position = int(random_value() % (values.size() + 1));
                int value = random_int();
                values.insert(values.begin() + position, value);
                matrix.insert(position, value);
            } else if (type == 1) {
                int position = int(random_value() % values.size());
                int expected = values[position];
                values.erase(values.begin() + position);
                assert(matrix.erase(position) == expected);
            } else if (type == 2) {
                int position = int(random_value() % values.size());
                int value = random_int();
                values[position] = value;
                matrix.set(position, value);
            } else if (type == 3) {
                int value = random_int();
                values.push_back(value);
                matrix.push_back(value);
            }
            check_queries(matrix, values);
        }
    }

    std::vector<int> values(900);
    for (int& value : values) value = random_int();
    Matrix matrix(values);
    for (int operation = 0; operation < 4000; operation++) {
        int from = int(random_value() % values.size());
        int to = int(random_value() % values.size());
        int value = values[from];
        values.erase(values.begin() + from);
        assert(matrix.erase(from) == value);
        values.insert(values.begin() + to, value);
        matrix.insert(to, value);
        if (operation % 20 == 0) check_queries(matrix, values);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int size = 0;
    int query_count = 0;
    fast_input >> size >> query_count;
    std::vector<int> values(size);
    for (int& value : values) fast_input >> value;
    Matrix matrix(values);
    while (query_count--) {
        int type = 0;
        fast_input >> type;
        if (type == 0) {
            int position = 0;
            int value = 0;
            fast_input >> position >> value;
            matrix.set(position, value);
        } else {
            int left = 0;
            int right = 0;
            int value = 0;
            fast_input >> left >> right >> value;
            fast_output << matrix.rank(value, left, right) << '\n';
        }
    }
}
