#ifndef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_BENCHMARK_LEGACY
#define M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE 1
#endif

#include "../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sys/resource.h>
#include <utility>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
using Nanoseconds = std::chrono::nanoseconds;
#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_BENCHMARK_FULL_WIDTH
using Matrix =
    m1une::ds::DynamicWaveletMatrixSum<std::uint32_t, long long>;
#else
using Matrix = m1une::ds::DynamicWaveletMatrixSum<
    std::uint32_t,
    long long,
    18
>;
#endif

struct Operation {
    int position = 0;
    long long value = 0;
    std::uint32_t key = 0;
    int left = 0;
    int right = 0;
    long long target = 1;
};

std::uint64_t random_state = 0x6a09e667f3bcc909ULL;

std::uint64_t random_value() {
    random_state ^= random_state << 7;
    random_state ^= random_state >> 9;
    return random_state;
}

long long generated_value() {
    return 1 + static_cast<long long>(random_value() % 1000000000ULL);
}

double milliseconds(Nanoseconds duration) {
    return std::chrono::duration<double, std::milli>(duration).count();
}

long long peak_memory_bytes() {
    rusage usage{};
    if (getrusage(RUSAGE_SELF, &usage) != 0) return -1;
#ifdef __APPLE__
    return usage.ru_maxrss;
#else
    return usage.ru_maxrss * 1024LL;
#endif
}

}  // namespace

int main(int argc, char** argv) {
    int n = argc >= 2 ? std::atoi(argv[1]) : 100000;
    int q = argc >= 3 ? std::atoi(argv[2]) : 100000;
    if (n <= 0 || q < 0 || n + q > (1 << 18)) return 2;

    std::vector<long long> initial_values(n);
    for (long long& value : initial_values) value = generated_value();
    std::vector<long long> current_values = initial_values;
    std::vector<Operation> operations(q);
    std::vector<long long> coordinates = initial_values;
    coordinates.reserve(std::size_t(n) + q);

    for (int query = 0; query < q; query++) {
        Operation& operation = operations[query];
        if (query % 8 == 0) {
            operation.position = (query / 8) % std::min(n, 32);
        } else {
            operation.position = int(random_value() % std::uint64_t(n));
        }

        if (query % 7 == 0) {
            operation.value = current_values[operation.position];
        } else if (query % 11 == 0) {
            operation.value = 1 + (query % 97);
        } else {
            operation.value = generated_value();
        }
        current_values[operation.position] = operation.value;
        coordinates.push_back(operation.value);

        if (query % 3 == 0) {
            int length = 1 + int(random_value() % 64);
            operation.left =
                int(random_value() % std::uint64_t(n - length + 1));
            operation.right = operation.left + length;
        } else if (query % 3 == 1) {
            int maximum = std::min(n, 10000);
            int minimum = std::min(maximum, 1000);
            int length = minimum +
                         int(random_value() %
                             std::uint64_t(maximum - minimum + 1));
            operation.left =
                int(random_value() % std::uint64_t(n - length + 1));
            operation.right = operation.left + length;
        } else {
            operation.left = 0;
            operation.right = n;
        }

        if (query % 5 == 0) {
            operation.target = std::numeric_limits<long long>::max() / 4;
        } else if (query % 5 == 1) {
            operation.target = 1;
        } else {
            long long length = operation.right - operation.left;
            operation.target =
                1 + static_cast<long long>(random_value() %
                    std::uint64_t(length * 500000000LL + 1));
        }
    }

    std::sort(coordinates.begin(), coordinates.end());
    coordinates.erase(
        std::unique(coordinates.begin(), coordinates.end()),
        coordinates.end()
    );
    if (coordinates.size() > (1U << 18)) return 3;
    auto compressed_key = [&](long long value) {
        return std::uint32_t(
            std::lower_bound(coordinates.begin(), coordinates.end(), value) -
            coordinates.begin()
        );
    };

    std::vector<std::uint32_t> keys(n);
    std::vector<long long> weights = initial_values;
    for (int position = 0; position < n; position++) {
        keys[position] = compressed_key(initial_values[position]);
    }
    for (Operation& operation : operations) {
        operation.key = compressed_key(operation.value);
    }

    auto total_start = Clock::now();
    auto construction_start = Clock::now();
    Matrix matrix(keys, weights);
    auto construction_end = Clock::now();
#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE
    m1une::ds::dynamic_wavelet_matrix_sum_detail::reset_profile();
#endif

    Nanoseconds replacement_time(0);
    Nanoseconds query_time(0);
    std::uint64_t checksum = 0;
    for (const Operation& operation : operations) {
        auto replacement_start = Clock::now();
        matrix.set(
            operation.position,
            operation.key,
            operation.value
        );
        auto replacement_end = Clock::now();
        int count;
        auto query_start = Clock::now();
        count = matrix.max_count_largest(
            operation.left,
            operation.right,
            [&](long long sum) { return sum < operation.target; }
        );
        auto query_end = Clock::now();
        replacement_time += replacement_end - replacement_start;
        query_time += query_end - query_start;
        checksum = checksum * 1000003ULL + std::uint64_t(count + 1);
    }
    auto total_end = Clock::now();

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "N " << n << '\n';
    std::cout << "Q " << q << '\n';
    std::cout << "distinct_keys " << coordinates.size() << '\n';
#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE
    std::cout << "chunk_capacity "
              << m1une::ds::dynamic_wavelet_matrix_sum_detail::
                     configured_chunk_capacity
              << '\n';
    std::cout << "group_size "
              << m1une::ds::dynamic_wavelet_matrix_sum_detail::
                     configured_group_size
              << '\n';
#endif
    std::cout << "construction_ms "
              << milliseconds(construction_end - construction_start) << '\n';
    std::cout << "replacement_ms " << milliseconds(replacement_time) << '\n';
    std::cout << "query_ms " << milliseconds(query_time) << '\n';
    std::cout << "total_ms " << milliseconds(total_end - total_start) << '\n';
    std::cout << "peak_memory_mib "
              << double(peak_memory_bytes()) / (1024.0 * 1024.0) << '\n';
#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE
    auto profile =
        m1une::ds::dynamic_wavelet_matrix_sum_detail::get_profile();
    std::cout << "bitvector_tree_traversals "
              << profile.bitvector_tree_traversals << '\n';
    std::cout << "weight_tree_traversals "
              << profile.weight_tree_traversals << '\n';
    std::cout << "chunk_splits " << profile.chunk_splits << '\n';
    std::cout << "chunk_merges " << profile.chunk_merges << '\n';
    std::cout << "local_element_moves " << profile.local_element_moves
              << '\n';
    std::cout << "full_chunk_rebuilds " << profile.full_chunk_rebuilds
              << '\n';
#endif
    std::cout << "checksum " << checksum << '\n';
}
