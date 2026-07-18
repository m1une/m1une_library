#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp"
#include "../../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

namespace {

using Matrix = m1une::ds::DynamicWaveletMatrixSum<int, long long>;

std::uint64_t random_state = 0x6a09e667f3bcc909ULL;

std::uint64_t random_value() {
    random_state ^= random_state << 7;
    random_state ^= random_state >> 9;
    return random_state;
}

int random_int(int lower, int upper) {
    return lower + int(random_value() % std::uint64_t(upper - lower + 1));
}

void check_queries(
    const Matrix& matrix,
    const std::vector<int>& values,
    const std::vector<long long>& weights
) {
    assert(values.size() == weights.size());
    assert(matrix.size() == int(values.size()));
    assert(matrix.empty() == values.empty());
    for (int i = 0; i < int(values.size()); i++) {
        assert(matrix.access(i) == values[i]);
        assert(matrix[i] == values[i]);
        assert(matrix.weight(i) == weights[i]);
        std::pair<int, long long> expected(values[i], weights[i]);
        assert(matrix.get(i) == expected);
    }

    int left = int(random_value() % (values.size() + 1));
    int right = int(random_value() % (values.size() + 1));
    if (right < left) std::swap(left, right);
    int lower = random_int(-25, 25);
    int upper = random_int(-25, 25);
    if (upper < lower) std::swap(lower, upper);

    long long total = 0;
    long long below = 0;
    long long between = 0;
    int frequency = 0;
    std::vector<std::pair<int, int>> order;
    for (int i = left; i < right; i++) {
        total += weights[i];
        if (values[i] < upper) below += weights[i];
        if (lower <= values[i] && values[i] < upper) {
            between += weights[i];
            frequency++;
        }
        order.emplace_back(values[i], i);
    }
    std::stable_sort(
        order.begin(),
        order.end(),
        [](const auto& first, const auto& second) {
            return first.first < second.first;
        }
    );

    assert(matrix.range_sum(left, right) == total);
    assert(matrix.range_sum(left, right, upper) == below);
    assert(matrix.range_sum(left, right, lower, upper) == between);
    assert(matrix.range_freq(left, right, lower, upper) == frequency);

    long long smallest_sum = 0;
    long long largest_sum = 0;
    for (int k = 0; k <= int(order.size()); k++) {
        assert(matrix.sum_k_smallest(left, right, k) == smallest_sum);
        assert(matrix.sum_k_largest(left, right, k) == largest_sum);
        if (k < int(order.size())) {
            smallest_sum += weights[order[k].second];
            largest_sum += weights[order[order.size() - 1 - k].second];
        }
    }

    if (!order.empty()) {
        int k = int(random_value() % order.size());
        assert(matrix.kth_smallest(left, right, k) == order[k].first);
        assert(
            matrix.kth_largest(left, right, k) ==
            order[order.size() - 1 - k].first
        );
    }

    int value = random_int(-20, 20);
    assert(
        matrix.rank(value, left, right) ==
        int(std::count(values.begin() + left, values.begin() + right, value))
    );
    assert(
        matrix.rank(value, right) ==
        int(std::count(values.begin(), values.begin() + right, value))
    );

    std::optional<int> previous;
    std::optional<int> next;
    for (int i = left; i < right; i++) {
        if (values[i] < upper &&
            (!previous.has_value() || previous.value() < values[i])) {
            previous = values[i];
        }
        if (lower <= values[i] &&
            (!next.has_value() || values[i] < next.value())) {
            next = values[i];
        }
    }
    assert(matrix.prev_value(left, right, upper) == previous);
    assert(matrix.next_value(left, right, lower) == next);
}

void test_randomized() {
    std::vector<int> default_values;
    default_values.push_back(std::numeric_limits<int>::min());
    default_values.push_back(-2);
    default_values.push_back(0);
    default_values.push_back(std::numeric_limits<int>::max());
    m1une::ds::DynamicWaveletMatrixSum<int, long long> default_matrix(
        default_values
    );
    assert(
        default_matrix.range_sum(0, 4) ==
        static_cast<long long>(std::numeric_limits<int>::min()) - 2 +
            std::numeric_limits<int>::max()
    );
    default_matrix.set(1, 10);
    assert(default_matrix.weight(1) == 10);
    default_matrix.insert(2, -7);
    assert(default_matrix.weight(2) == -7);

    std::vector<unsigned long long> unsigned_values;
    unsigned_values.push_back(0);
    unsigned_values.push_back(std::numeric_limits<unsigned long long>::max());
    std::vector<long long> unsigned_weights;
    unsigned_weights.push_back(3);
    unsigned_weights.push_back(4);
    m1une::ds::DynamicWaveletMatrixSum<unsigned long long, long long>
        unsigned_matrix(unsigned_values, unsigned_weights);
    assert(unsigned_matrix.kth_largest(0, 2, 0) == unsigned_values[1]);
    assert(unsigned_matrix.range_sum(0, 2) == 7);
    unsigned_matrix.clear();
    assert(unsigned_matrix.empty());

    for (int trial = 0; trial < 80; trial++) {
        int initial_size = random_int(0, 60);
        std::vector<int> values(initial_size);
        std::vector<long long> weights(initial_size);
        for (int i = 0; i < initial_size; i++) {
            values[i] = random_int(-20, 20);
            weights[i] = random_int(-50, 50);
        }
        Matrix matrix(values, weights);

        for (int operation = 0; operation < 220; operation++) {
            int type = int(random_value() % 8);
            if (values.empty()) type = 0;
            if (type == 0) {
                int position = int(random_value() % (values.size() + 1));
                int value = random_int(-20, 20);
                long long weight = random_int(-50, 50);
                values.insert(values.begin() + position, value);
                weights.insert(weights.begin() + position, weight);
                matrix.insert(position, value, weight);
            } else if (type == 1) {
                int position = int(random_value() % values.size());
                std::pair<int, long long> expected(
                    values[position],
                    weights[position]
                );
                values.erase(values.begin() + position);
                weights.erase(weights.begin() + position);
                assert(matrix.erase(position) == expected);
            } else if (type == 2) {
                int position = int(random_value() % values.size());
                int value = random_int(-20, 20);
                long long weight = random_int(-50, 50);
                values[position] = value;
                weights[position] = weight;
                matrix.set(position, value, weight);
            } else if (type == 3) {
                int position = int(random_value() % values.size());
                int value = random_int(-20, 20);
                values[position] = value;
                matrix.set_value(position, value);
            } else if (type == 4) {
                int position = int(random_value() % values.size());
                long long weight = random_int(-50, 50);
                weights[position] = weight;
                matrix.set_weight(position, weight);
            } else if (type == 5) {
                int position = int(random_value() % values.size());
                long long delta = random_int(-20, 20);
                weights[position] += delta;
                matrix.add_weight(position, delta);
            } else if (type == 6) {
                int value = random_int(-20, 20);
                values.push_back(value);
                weights.push_back(value);
                matrix.push_back(value);
            } else {
                int position = int(random_value() % values.size());
                int value = random_int(-20, 20);
                values[position] = value;
                weights[position] = value;
                matrix.set(position, value);
            }
            check_queries(matrix, values, weights);
        }
    }

    std::vector<int> values(700);
    std::vector<long long> weights(700);
    for (int i = 0; i < int(values.size()); i++) {
        values[i] = random_int(-100, 100);
        weights[i] = random_int(-1000, 1000);
    }
    Matrix matrix(values, weights);
    for (int operation = 0; operation < 2500; operation++) {
        int from = int(random_value() % values.size());
        int to = int(random_value() % values.size());
        int value = values[from];
        long long weight = weights[from];
        values.erase(values.begin() + from);
        weights.erase(weights.begin() + from);
        std::pair<int, long long> expected(value, weight);
        assert(matrix.erase(from) == expected);
        values.insert(values.begin() + to, value);
        weights.insert(weights.begin() + to, weight);
        matrix.insert(to, value, weight);
        if (operation % 25 == 0) check_queries(matrix, values, weights);
    }
}

void test_boundary_search() {
    {
        std::vector<int> equal_values(700, 7);
        std::vector<long long> equal_weights(700);
        for (int i = 0; i < int(equal_weights.size()); i++) {
            equal_weights[i] = i % 17 + 1;
        }
        Matrix equal_matrix(equal_values, equal_weights);
        for (int operation = 0; operation < 300; operation++) {
            int type = int(random_value() % 3);
            if (type == 0) {
                int position =
                    int(random_value() % (equal_values.size() + 1));
                long long weight = random_int(1, 20);
                equal_values.insert(equal_values.begin() + position, 7);
                equal_weights.insert(
                    equal_weights.begin() + position,
                    weight
                );
                equal_matrix.insert(position, 7, weight);
            } else if (type == 1 && equal_values.size() > 300) {
                int position = int(random_value() % equal_values.size());
                equal_values.erase(equal_values.begin() + position);
                equal_weights.erase(equal_weights.begin() + position);
                equal_matrix.erase(position);
            } else {
                int position = int(random_value() % equal_values.size());
                equal_weights[position] = random_int(1, 20);
                equal_matrix.set_weight(position, equal_weights[position]);
            }

            int left = int(random_value() % (equal_values.size() + 1));
            int right = int(random_value() % (equal_values.size() + 1));
            if (right < left) std::swap(left, right);
            long long total = 0;
            for (int i = left; i < right; i++) total += equal_weights[i];
            long long limit = static_cast<long long>(
                random_value() % std::uint64_t(total + 21)
            );
            auto predicate = [limit](long long sum) {
                return sum <= limit;
            };

            long long sum = 0;
            int smallest = 0;
            while (left + smallest < right &&
                   sum + equal_weights[left + smallest] <= limit) {
                sum += equal_weights[left + smallest];
                smallest++;
            }
            assert(
                equal_matrix.max_count_smallest(
                    left,
                    right,
                    predicate
                ) == smallest
            );

            sum = 0;
            int largest = 0;
            while (left + largest < right &&
                   sum + equal_weights[right - 1 - largest] <= limit) {
                sum += equal_weights[right - 1 - largest];
                largest++;
            }
            assert(
                equal_matrix.max_count_largest(left, right, predicate) ==
                largest
            );
        }
    }

    std::vector<int> values(700);
    std::vector<long long> weights(700);
    for (int i = 0; i < int(values.size()); i++) {
        values[i] = random_int(-30, 30);
        weights[i] = random_int(1, 20);
    }
    Matrix matrix(values, weights);

    for (int operation = 0; operation < 700; operation++) {
        int type = int(random_value() % 4);
        if (type == 0) {
            int position = int(random_value() % (values.size() + 1));
            int value = random_int(-30, 30);
            long long weight = random_int(1, 20);
            values.insert(values.begin() + position, value);
            weights.insert(weights.begin() + position, weight);
            matrix.insert(position, value, weight);
        } else if (type == 1 && values.size() > 300) {
            int position = int(random_value() % values.size());
            values.erase(values.begin() + position);
            weights.erase(weights.begin() + position);
            matrix.erase(position);
        } else if (type == 2) {
            int position = int(random_value() % values.size());
            values[position] = random_int(-30, 30);
            matrix.set_value(position, values[position]);
        } else {
            int position = int(random_value() % values.size());
            weights[position] = random_int(1, 20);
            matrix.set_weight(position, weights[position]);
        }

        int left = int(random_value() % (values.size() + 1));
        int right = int(random_value() % (values.size() + 1));
        if (right < left) std::swap(left, right);
        std::vector<std::pair<int, int>> order;
        long long total = 0;
        for (int i = left; i < right; i++) {
            order.emplace_back(values[i], i);
            total += weights[i];
        }
        std::stable_sort(
            order.begin(),
            order.end(),
            [](const auto& first, const auto& second) {
                return first.first < second.first;
            }
        );
        long long limit = static_cast<long long>(
            random_value() % std::uint64_t(total + 21)
        );
        auto predicate = [limit](long long sum) { return sum <= limit; };

        long long sum = 0;
        int smallest = 0;
        while (smallest < int(order.size()) &&
               sum + weights[order[smallest].second] <= limit) {
            sum += weights[order[smallest].second];
            smallest++;
        }
        assert(
            matrix.max_count_smallest(left, right, predicate) == smallest
        );

        sum = 0;
        int largest = 0;
        while (largest < int(order.size()) &&
               sum + weights[order[order.size() - 1 - largest].second] <=
                   limit) {
            sum += weights[order[order.size() - 1 - largest].second];
            largest++;
        }
        assert(matrix.max_count_largest(left, right, predicate) == largest);
    }
}

struct Point {
    int x = 0;
    int y = 0;
    long long weight = 0;
    int query_index = -1;
};

struct Query {
    int type = 0;
    int first = 0;
    int second = 0;
    int third = 0;
    int fourth = 0;
    long long weight = 0;
    int position = -1;
};

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();
    test_boundary_search();

    int point_count = 0;
    int query_count = 0;
    fast_input >> point_count >> query_count;
    std::vector<Point> points(point_count);
    for (Point& point : points) {
        fast_input >> point.x >> point.y >> point.weight;
    }

    std::vector<Query> queries(query_count);
    for (int query_index = 0; query_index < query_count; query_index++) {
        Query& query = queries[query_index];
        fast_input >> query.type;
        if (query.type == 0) {
            fast_input >> query.first >> query.second >> query.weight;
            Point point;
            point.x = query.first;
            point.y = query.second;
            point.query_index = query_index;
            points.push_back(point);
        } else {
            fast_input >> query.first >> query.second >> query.third >>
                query.fourth;
        }
    }

    std::stable_sort(
        points.begin(),
        points.end(),
        [](const Point& first, const Point& second) {
            return first.x < second.x;
        }
    );
    std::vector<int> xs(points.size());
    std::vector<int> ys(points.size());
    std::vector<long long> weights(points.size());
    for (int i = 0; i < int(points.size()); i++) {
        xs[i] = points[i].x;
        ys[i] = points[i].y;
        weights[i] = points[i].weight;
        if (points[i].query_index != -1) {
            queries[points[i].query_index].position = i;
        }
    }

    Matrix matrix(ys, weights);
    for (const Query& query : queries) {
        if (query.type == 0) {
            matrix.set_weight(query.position, query.weight);
        } else {
            int left = int(std::lower_bound(
                               xs.begin(),
                               xs.end(),
                               query.first
                           ) -
                           xs.begin());
            int right = int(std::lower_bound(
                                xs.begin(),
                                xs.end(),
                                query.third
                            ) -
                            xs.begin());
            fast_output << matrix.range_sum(
                               left,
                               right,
                               query.second,
                               query.fourth
                           )
                        << '\n';
        }
    }
}
