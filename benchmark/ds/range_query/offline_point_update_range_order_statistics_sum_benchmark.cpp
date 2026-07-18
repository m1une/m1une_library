#define M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE 1

#include "../../../ds/range_query/offline_point_update_range_order_statistics_sum.hpp"
#include "../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
#include <sys/resource.h>
#include <utility>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
using Nanoseconds = std::chrono::nanoseconds;
using Key = std::uint32_t;
using OfflineMatrix =
    m1une::ds::OfflinePointUpdateRangeOrderStatisticsSum<Key, long long>;
using DynamicMatrix =
    m1une::ds::DynamicWaveletMatrixSum<Key, long long, 18>;

struct Operation {
    int position = 0;
    Key key = 0;
    int left = 0;
    int right = 0;
    long long target = 1;
};

struct Result {
    Nanoseconds construction_time{};
    Nanoseconds initialization_time{};
    Nanoseconds update_time{};
    Nanoseconds query_time{};
    Nanoseconds total_time{};
    std::uint64_t checksum = 0;
};

std::uint64_t random_state = 0x243f6a8885a308d3ULL;

std::uint64_t random_value() {
    random_state ^= random_state << 7;
    random_state ^= random_state >> 9;
    return random_state;
}

Key generated_key() {
    return Key(1 + random_value() % 200000ULL);
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

void add_checksum(std::uint64_t& checksum, std::optional<int> answer) {
    std::uint64_t value = answer.has_value()
                              ? std::uint64_t(answer.value() + 1)
                              : 0;
    checksum = checksum * 1000003ULL + value;
}

Result run_offline(
    const std::vector<Key>& initial,
    const std::vector<std::pair<int, Key>>& candidates,
    const std::vector<Operation>& operations
) {
    Result result;
    auto total_start = Clock::now();
    auto construction_start = Clock::now();
    OfflineMatrix matrix(initial, candidates);
    auto construction_end = Clock::now();
    result.construction_time = construction_end - construction_start;
    auto profile = m1une::ds::
        offline_point_update_range_order_statistics_sum_detail::
            get_construction_profile();
    result.initialization_time =
        Nanoseconds(profile.initialization_nanoseconds);

    for (const Operation& operation : operations) {
        auto update_start = Clock::now();
        matrix.set(operation.position, operation.key);
        auto update_end = Clock::now();
        auto query_start = Clock::now();
        std::optional<int> answer =
            matrix.min_count_largest_sum_at_least(
                operation.left,
                operation.right,
                operation.target
            );
        auto query_end = Clock::now();
        result.update_time += update_end - update_start;
        result.query_time += query_end - query_start;
        add_checksum(result.checksum, answer);
    }
    result.total_time = Clock::now() - total_start;
    return result;
}

Result run_dynamic(
    const std::vector<Key>& initial,
    const std::vector<Operation>& operations
) {
    Result result;
    auto total_start = Clock::now();
    auto construction_start = Clock::now();
    DynamicMatrix matrix(initial);
    auto construction_end = Clock::now();
    result.construction_time = construction_end - construction_start;

    for (const Operation& operation : operations) {
        auto update_start = Clock::now();
        matrix.set(operation.position, operation.key);
        auto update_end = Clock::now();
        auto query_start = Clock::now();
        int count = matrix.max_count_largest(
            operation.left,
            operation.right,
            [&](long long sum) { return sum < operation.target; }
        );
        std::optional<int> answer;
        if (count != operation.right - operation.left) {
            answer = count + 1;
        }
        auto query_end = Clock::now();
        result.update_time += update_end - update_start;
        result.query_time += query_end - query_start;
        add_checksum(result.checksum, answer);
    }
    result.total_time = Clock::now() - total_start;
    return result;
}

void print_result(const char* name, const Result& result) {
    std::cout << name << "_construction_ms "
              << milliseconds(result.construction_time) << '\n';
    if (result.initialization_time != Nanoseconds()) {
        std::cout << name << "_initialization_ms "
                  << milliseconds(result.initialization_time) << '\n';
    }
    std::cout << name << "_update_ms "
              << milliseconds(result.update_time) << '\n';
    std::cout << name << "_query_ms "
              << milliseconds(result.query_time) << '\n';
    std::cout << name << "_total_ms "
              << milliseconds(result.total_time) << '\n';
    std::cout << name << "_checksum " << result.checksum << '\n';
}

}  // namespace

int main(int argc, char** argv) {
    int n = argc >= 2 ? std::atoi(argv[1]) : 100000;
    int q = argc >= 3 ? std::atoi(argv[2]) : 100000;
    if (n <= 0 || q < 0) return 2;

    auto preparation_start = Clock::now();
    std::vector<Key> initial(n);
    for (Key& key : initial) key = generated_key();
    std::vector<Key> current = initial;
    std::vector<Operation> operations(q);
    std::vector<std::pair<int, Key>> candidates;
    candidates.reserve(std::size_t(q) + q / 8 + 1);

    for (int query = 0; query < q; query++) {
        Operation& operation = operations[query];
        if (query % 8 == 0) {
            operation.position = (query / 8) % std::min(n, 32);
        } else {
            operation.position = int(random_value() % std::uint64_t(n));
        }
        if (query % 7 == 0) {
            operation.key = current[operation.position];
        } else if (query % 11 == 0) {
            operation.key = Key(1 + query % 97);
        } else {
            operation.key = generated_key();
        }
        current[operation.position] = operation.key;
        candidates.emplace_back(operation.position, operation.key);
        if (query % 8 == 0) {
            candidates.emplace_back(operation.position, operation.key);
        }

        if (query % 3 == 0) {
            int length = 1 + int(random_value() % std::uint64_t(std::min(n, 128)));
            operation.left =
                int(random_value() % std::uint64_t(n - length + 1));
            operation.right = operation.left + length;
        } else if (query % 3 == 1) {
            int length = 1 + int(random_value() % std::uint64_t(n));
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
                    std::uint64_t(length * 100000LL + 1));
        }
    }
    for (int index = int(candidates.size()) - 1; 0 < index; index--) {
        int other = int(random_value() % std::uint64_t(index + 1));
        std::swap(candidates[index], candidates[other]);
    }
    Nanoseconds preparation_time = Clock::now() - preparation_start;

    Result offline = run_offline(initial, candidates, operations);
    Result dynamic = run_dynamic(initial, operations);
    if (offline.checksum != dynamic.checksum) return 3;

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "N " << n << '\n';
    std::cout << "Q " << q << '\n';
    std::cout << "registered_candidate_entries " << candidates.size() << '\n';
    std::cout << "candidate_preparation_ms "
              << milliseconds(preparation_time) << '\n';
    print_result("offline", offline);
    print_result("dynamic", dynamic);
    std::cout << "peak_memory_mib "
              << double(peak_memory_bytes()) / (1024.0 * 1024.0) << '\n';
}
