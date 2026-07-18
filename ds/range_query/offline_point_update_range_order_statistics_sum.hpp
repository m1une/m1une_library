#ifndef M1UNE_DS_RANGE_QUERY_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_HPP
#define M1UNE_DS_RANGE_QUERY_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
#include <chrono>
#include <cstdint>
#endif

namespace m1une {
namespace ds {

namespace offline_point_update_range_order_statistics_sum_detail {

#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
struct ConstructionProfile {
    std::int64_t registration_nanoseconds = 0;
    std::int64_t flatten_nanoseconds = 0;
    std::int64_t handle_nanoseconds = 0;
    std::int64_t initialization_nanoseconds = 0;
};

inline ConstructionProfile construction_profile;

inline ConstructionProfile get_construction_profile() {
    return construction_profile;
}
#endif

}  // namespace offline_point_update_range_order_statistics_sum_detail

// Fixed-length point updates and range order statistics with offline keys.
template <class T, class Sum = T>
class OfflinePointUpdateRangeOrderStatisticsSum {
   private:
    struct Aggregate {
        int count = 0;
        Sum sum{};
    };

    struct NodeInfo {
        int position_offset = 0;
        int position_count = 0;
        int fenwick_offset = 0;
    };

    struct Handle {
        int node = 0;
        int local_position = 0;
    };

    struct CandidateState {
        int key_index = 0;
        int handle_offset = 0;
    };

    int _size = 0;
    int _key_count = 0;
    int _tree_base = 1;
    int _height = 0;
    std::vector<T> _compressed_keys;
    std::vector<NodeInfo> _nodes;
    std::vector<int> _registered_positions;
    std::vector<int> _fenwick_counts;
    std::vector<Sum> _fenwick_sums;
    std::vector<int> _state_offsets;
    std::vector<CandidateState> _states;
    std::vector<Handle> _handles;
    std::vector<int> _current_states;
    std::vector<Sum> _current_weights;

    static bool equivalent(const T& left, const T& right) {
        return !(left < right) && !(right < left);
    }

    static int as_int(std::size_t value) {
        assert(value <= std::size_t(std::numeric_limits<int>::max()));
        return int(value);
    }

    int key_index(const T& key) const {
        auto iterator =
            std::lower_bound(_compressed_keys.begin(), _compressed_keys.end(), key);
        if (iterator == _compressed_keys.end() ||
            !equivalent(*iterator, key)) {
            return -1;
        }
        return int(iterator - _compressed_keys.begin());
    }

    int find_candidate_state(int position, const T& key) const {
        assert(0 <= position && position < _size);
        auto first = _states.begin() + _state_offsets[position];
        auto last = _states.begin() + _state_offsets[position + 1];
        auto iterator = std::lower_bound(
            first,
            last,
            key,
            [&](const CandidateState& state, const T& value) {
                return _compressed_keys[state.key_index] < value;
            }
        );
        if (iterator == last ||
            !equivalent(_compressed_keys[iterator->key_index], key)) {
            return -1;
        }
        return int(iterator - _states.begin());
    }

    int node_position_lower_bound(int node, int original_position) const {
        const NodeInfo& info = _nodes[node];
        auto first =
            _registered_positions.begin() + info.position_offset;
        auto last = first + info.position_count;
        return int(std::lower_bound(first, last, original_position) - first);
    }

    int fenwick_prefix_count(int node, int right) const {
        const NodeInfo& info = _nodes[node];
        int result = 0;
        for (int position = right; position > 0;
             position -= position & -position) {
            result +=
                _fenwick_counts[info.fenwick_offset + position - 1];
        }
        return result;
    }

    Sum fenwick_prefix_sum(int node, int right) const {
        const NodeInfo& info = _nodes[node];
        Sum result{};
        for (int position = right; position > 0;
             position -= position & -position) {
            result = result +
                     _fenwick_sums[info.fenwick_offset + position - 1];
        }
        return result;
    }

    void fenwick_add(
        const Handle& handle,
        int count_delta,
        const Sum& sum_delta
    ) {
        const NodeInfo& info = _nodes[handle.node];
        for (int position = handle.local_position + 1;
             position <= info.position_count;
             position += position & -position) {
            int index = info.fenwick_offset + position - 1;
            _fenwick_counts[index] += count_delta;
            _fenwick_sums[index] = _fenwick_sums[index] + sum_delta;
        }
    }

    void fenwick_subtract(
        const Handle& handle,
        int count_delta,
        const Sum& sum_delta
    ) {
        const NodeInfo& info = _nodes[handle.node];
        for (int position = handle.local_position + 1;
             position <= info.position_count;
             position += position & -position) {
            int index = info.fenwick_offset + position - 1;
            _fenwick_counts[index] -= count_delta;
            _fenwick_sums[index] = _fenwick_sums[index] - sum_delta;
        }
    }

    void activate_state(int state, const Sum& weight) {
        int handle_offset = _states[state].handle_offset;
        for (int depth = 0; depth <= _height; depth++) {
            fenwick_add(_handles[handle_offset + depth], 1, weight);
        }
    }

    void deactivate_state(int state, const Sum& weight) {
        int handle_offset = _states[state].handle_offset;
        for (int depth = 0; depth <= _height; depth++) {
            fenwick_subtract(_handles[handle_offset + depth], 1, weight);
        }
    }

    void add_to_state(int state, const Sum& delta) {
        int handle_offset = _states[state].handle_offset;
        for (int depth = 0; depth <= _height; depth++) {
            fenwick_add(_handles[handle_offset + depth], 0, delta);
        }
    }

    Aggregate range_query(int node, int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        int local_left = node_position_lower_bound(node, left);
        int local_right = node_position_lower_bound(node, right);
        return Aggregate{
            fenwick_prefix_count(node, local_right) -
                fenwick_prefix_count(node, local_left),
            fenwick_prefix_sum(node, local_right) -
                fenwick_prefix_sum(node, local_left)
        };
    }

    Aggregate key_range_query(
        int left,
        int right,
        int first_key,
        int last_key
    ) const {
        Aggregate result;
        int first = _tree_base + first_key;
        int last = _tree_base + last_key;
        while (first < last) {
            if (first & 1) {
                Aggregate current = range_query(first++, left, right);
                result.count += current.count;
                result.sum = result.sum + current.sum;
            }
            if (last & 1) {
                Aggregate current = range_query(--last, left, right);
                result.count += current.count;
                result.sum = result.sum + current.sum;
            }
            first >>= 1;
            last >>= 1;
        }
        return result;
    }

    int fenwick_lower_bound_count(int node, int target) const {
        const NodeInfo& info = _nodes[node];
        assert(1 <= target);
        assert(target <= fenwick_prefix_count(node, info.position_count));
        int position = 0;
        int accumulated = 0;
        int step = 1;
        while ((step << 1) <= info.position_count) step <<= 1;
        for (; step != 0; step >>= 1) {
            int next = position + step;
            if (next <= info.position_count &&
                accumulated +
                        _fenwick_counts[info.fenwick_offset + next - 1] <
                    target) {
                position = next;
                accumulated +=
                    _fenwick_counts[info.fenwick_offset + next - 1];
            }
        }
        return position;
    }

    int fenwick_lower_bound_sum(int node, const Sum& target) const {
        const NodeInfo& info = _nodes[node];
        int position = 0;
        Sum accumulated{};
        int step = 1;
        while ((step << 1) <= info.position_count) step <<= 1;
        for (; step != 0; step >>= 1) {
            int next = position + step;
            if (next <= info.position_count) {
                Sum candidate =
                    accumulated +
                    _fenwick_sums[info.fenwick_offset + next - 1];
                if (candidate < target) {
                    position = next;
                    accumulated = candidate;
                }
            }
        }
        return position;
    }

    int fenwick_max_prefix_sum_at_most(
        int node,
        const Sum& target,
        int maximum_length
    ) const {
        const NodeInfo& info = _nodes[node];
        assert(0 <= maximum_length &&
               maximum_length <= info.position_count);
        int position = 0;
        Sum accumulated{};
        int step = 1;
        while ((step << 1) <= info.position_count) step <<= 1;
        for (; step != 0; step >>= 1) {
            int next = position + step;
            if (next <= maximum_length) {
                Sum candidate =
                    accumulated +
                    _fenwick_sums[info.fenwick_offset + next - 1];
                if (!(target < candidate)) {
                    position = next;
                    accumulated = candidate;
                }
            }
        }
        return position;
    }

    Sum sum_first_active(
        int node,
        int original_left,
        int original_right,
        int count
    ) const {
        if (count == 0) return Sum{};
        int local_left = node_position_lower_bound(node, original_left);
        int local_right = node_position_lower_bound(node, original_right);
        int count_before = fenwick_prefix_count(node, local_left);
        int range_count =
            fenwick_prefix_count(node, local_right) - count_before;
        assert(0 <= count && count <= range_count);
        int boundary =
            fenwick_lower_bound_count(node, count_before + count);
        assert(boundary < local_right);
        return fenwick_prefix_sum(node, boundary + 1) -
               fenwick_prefix_sum(node, local_left);
    }

    Sum sum_last_active(
        int node,
        int original_left,
        int original_right,
        int count
    ) const {
        if (count == 0) return Sum{};
        int local_left = node_position_lower_bound(node, original_left);
        int local_right = node_position_lower_bound(node, original_right);
        int count_through = fenwick_prefix_count(node, local_right);
        int range_count =
            count_through - fenwick_prefix_count(node, local_left);
        assert(0 <= count && count <= range_count);
        int boundary =
            fenwick_lower_bound_count(node, count_through - count + 1);
        assert(local_left <= boundary);
        return fenwick_prefix_sum(node, local_right) -
               fenwick_prefix_sum(node, boundary);
    }

    int min_count_first_active_sum_at_least(
        int node,
        int original_left,
        int original_right,
        const Sum& target
    ) const {
        int local_left = node_position_lower_bound(node, original_left);
        int local_right = node_position_lower_bound(node, original_right);
        Sum sum_before = fenwick_prefix_sum(node, local_left);
        int boundary =
            fenwick_lower_bound_sum(node, sum_before + target);
        assert(boundary < local_right);
        return fenwick_prefix_count(node, boundary + 1) -
               fenwick_prefix_count(node, local_left);
    }

    int min_count_last_active_sum_at_least(
        int node,
        int original_left,
        int original_right,
        const Sum& target
    ) const {
        (void)original_left;
        int local_right = node_position_lower_bound(node, original_right);
        Sum sum_through = fenwick_prefix_sum(node, local_right);
        int prefix_length = fenwick_max_prefix_sum_at_most(
            node,
            sum_through - target,
            local_right
        );
        assert(
            node_position_lower_bound(node, original_left) <= prefix_length
        );
        return fenwick_prefix_count(node, local_right) -
               fenwick_prefix_count(node, prefix_length);
    }

    void replace(int position, int state, const Sum& weight) {
        int old_state = _current_states[position];
        Sum old_weight = _current_weights[position];
        if (state == old_state) {
            add_to_state(state, weight - old_weight);
        } else {
            deactivate_state(old_state, old_weight);
            activate_state(state, weight);
            _current_states[position] = state;
        }
        _current_weights[position] = weight;
    }

    void build(
        const std::vector<T>& initial_keys,
        const std::vector<Sum>& initial_weights,
        const std::vector<std::pair<int, T>>& update_candidates
    ) {
#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
        using ProfileClock = std::chrono::steady_clock;
        using namespace offline_point_update_range_order_statistics_sum_detail;
        construction_profile = ConstructionProfile();
        auto registration_start = ProfileClock::now();
#endif
        assert(initial_keys.size() == initial_weights.size());
        assert(initial_keys.size() <=
               std::size_t(std::numeric_limits<int>::max()));
        _size = int(initial_keys.size());
        _compressed_keys = initial_keys;
        _compressed_keys.reserve(initial_keys.size() + update_candidates.size());
        for (const auto& candidate : update_candidates) {
            assert(0 <= candidate.first && candidate.first < _size);
            _compressed_keys.push_back(candidate.second);
        }
        std::sort(_compressed_keys.begin(), _compressed_keys.end());
        _compressed_keys.erase(
            std::unique(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                [](const T& left, const T& right) {
                    return equivalent(left, right);
                }
            ),
            _compressed_keys.end()
        );
        _key_count = as_int(_compressed_keys.size());
        _tree_base = 1;
        _height = 0;
        while (_tree_base < std::max(1, _key_count)) {
            assert(_tree_base <= std::numeric_limits<int>::max() / 2);
            _tree_base <<= 1;
            _height++;
        }

        std::vector<std::vector<int>> candidate_keys(_size);
        for (int position = 0; position < _size; position++) {
            int compressed = key_index(initial_keys[position]);
            assert(compressed != -1);
            candidate_keys[position].push_back(compressed);
        }
        for (const auto& candidate : update_candidates) {
            int compressed = key_index(candidate.second);
            assert(compressed != -1);
            candidate_keys[candidate.first].push_back(compressed);
        }

        std::size_t state_count = 0;
        for (auto& keys : candidate_keys) {
            std::sort(keys.begin(), keys.end());
            keys.erase(std::unique(keys.begin(), keys.end()), keys.end());
            state_count += keys.size();
        }
        assert(state_count <=
               std::size_t(std::numeric_limits<int>::max()));
        assert(state_count * std::size_t(_height + 1) <=
               std::size_t(std::numeric_limits<int>::max()));

        std::vector<std::vector<int>> registrations(2 * _tree_base);
        for (int position = 0; position < _size; position++) {
            for (int compressed : candidate_keys[position]) {
                int leaf = _tree_base + compressed;
                for (int shift = _height; shift >= 0; shift--) {
                    registrations[leaf >> shift].push_back(position);
                }
            }
        }
#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
        auto registration_end = ProfileClock::now();
        construction_profile.registration_nanoseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                registration_end - registration_start
            ).count();
        auto flatten_start = ProfileClock::now();
#endif

        _nodes.assign(2 * _tree_base, NodeInfo());
        _registered_positions.clear();
        _registered_positions.reserve(
            state_count * std::size_t(_height + 1)
        );
        for (int node = 1; node < 2 * _tree_base; node++) {
            auto& positions = registrations[node];
            positions.erase(
                std::unique(positions.begin(), positions.end()),
                positions.end()
            );
            NodeInfo& info = _nodes[node];
            info.position_offset = as_int(_registered_positions.size());
            info.position_count = as_int(positions.size());
            info.fenwick_offset = info.position_offset;
            _registered_positions.insert(
                _registered_positions.end(),
                positions.begin(),
                positions.end()
            );
        }
        std::vector<std::vector<int>>().swap(registrations);
        _fenwick_counts.assign(_registered_positions.size(), 0);
        _fenwick_sums.assign(_registered_positions.size(), Sum{});
#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
        auto flatten_end = ProfileClock::now();
        construction_profile.flatten_nanoseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                flatten_end - flatten_start
            ).count();
        auto handle_start = ProfileClock::now();
#endif

        _state_offsets.assign(_size + 1, 0);
        _states.clear();
        _states.reserve(state_count);
        _handles.clear();
        _handles.reserve(state_count * std::size_t(_height + 1));
        for (int position = 0; position < _size; position++) {
            _state_offsets[position] = as_int(_states.size());
            for (int compressed : candidate_keys[position]) {
                CandidateState state;
                state.key_index = compressed;
                state.handle_offset = as_int(_handles.size());
                _states.push_back(state);
                int leaf = _tree_base + compressed;
                for (int shift = _height; shift >= 0; shift--) {
                    int node = leaf >> shift;
                    int local_position =
                        node_position_lower_bound(node, position);
                    assert(local_position < _nodes[node].position_count);
                    assert(
                        _registered_positions[
                            _nodes[node].position_offset + local_position
                        ] == position
                    );
                    _handles.push_back(Handle{node, local_position});
                }
            }
        }
        _state_offsets[_size] = as_int(_states.size());
        std::vector<std::vector<int>>().swap(candidate_keys);
#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
        auto handle_end = ProfileClock::now();
        construction_profile.handle_nanoseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                handle_end - handle_start
            ).count();
        auto initialization_start = ProfileClock::now();
#endif

        _current_states.resize(_size);
        _current_weights = initial_weights;
        for (int position = 0; position < _size; position++) {
            int state = find_candidate_state(position, initial_keys[position]);
            assert(state != -1);
            _current_states[position] = state;
            activate_state(state, initial_weights[position]);
        }
#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE
        auto initialization_end = ProfileClock::now();
        construction_profile.initialization_nanoseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                initialization_end - initialization_start
            ).count();
#endif
    }

   public:
    OfflinePointUpdateRangeOrderStatisticsSum(
        const std::vector<T>& initial_values,
        const std::vector<std::pair<int, T>>& update_candidates
    ) requires std::convertible_to<T, Sum> {
        std::vector<Sum> weights;
        weights.reserve(initial_values.size());
        for (const T& value : initial_values) {
            weights.push_back(static_cast<Sum>(value));
        }
        build(initial_values, weights, update_candidates);
    }

    OfflinePointUpdateRangeOrderStatisticsSum(
        const std::vector<T>& initial_keys,
        const std::vector<Sum>& initial_weights,
        const std::vector<std::pair<int, T>>& update_candidates
    ) {
        build(initial_keys, initial_weights, update_candidates);
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    T access(int position) const {
        assert(0 <= position && position < _size);
        return _compressed_keys[
            _states[_current_states[position]].key_index
        ];
    }

    T operator[](int position) const {
        return access(position);
    }

    Sum weight(int position) const {
        assert(0 <= position && position < _size);
        return _current_weights[position];
    }

    std::pair<T, Sum> get(int position) const {
        assert(0 <= position && position < _size);
        return std::pair<T, Sum>(access(position), weight(position));
    }

    void set(int position, T key)
        requires std::convertible_to<T, Sum>
    {
        set(position, key, static_cast<Sum>(key));
    }

    void set(int position, T key, const Sum& new_weight) {
        assert(0 <= position && position < _size);
        int state = find_candidate_state(position, key);
        assert(state != -1);
        if (state == -1) return;
        replace(position, state, new_weight);
    }

    void set_value(int position, T key) {
        assert(0 <= position && position < _size);
        int state = find_candidate_state(position, key);
        assert(state != -1);
        if (state == -1) return;
        if (state == _current_states[position]) return;
        replace(position, state, _current_weights[position]);
    }

    void set_weight(int position, const Sum& new_weight) {
        assert(0 <= position && position < _size);
        replace(position, _current_states[position], new_weight);
    }

    void add_weight(int position, const Sum& delta) {
        assert(0 <= position && position < _size);
        add_to_state(_current_states[position], delta);
        _current_weights[position] = _current_weights[position] + delta;
    }

    int rank(T key, int right) const {
        assert(0 <= right && right <= _size);
        return rank(key, 0, right);
    }

    int rank(T key, int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        int compressed = key_index(key);
        if (compressed == -1) return 0;
        return range_query(_tree_base + compressed, left, right).count;
    }

    int range_freq(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        int upper_index = int(
            std::lower_bound(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                upper
            ) - _compressed_keys.begin()
        );
        return key_range_query(left, right, 0, upper_index).count;
    }

    int range_freq(int left, int right, T lower, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        if (!(lower < upper)) return 0;
        int lower_index = int(
            std::lower_bound(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                lower
            ) - _compressed_keys.begin()
        );
        int upper_index = int(
            std::lower_bound(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                upper
            ) - _compressed_keys.begin()
        );
        return key_range_query(
            left,
            right,
            lower_index,
            upper_index
        ).count;
    }

    T kth_smallest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k < right - left);
        int node = 1;
        while (node < _tree_base) {
            Aggregate left_result = range_query(2 * node, left, right);
            if (k < left_result.count) {
                node *= 2;
            } else {
                k -= left_result.count;
                node = 2 * node + 1;
            }
        }
        int compressed = node - _tree_base;
        assert(0 <= compressed && compressed < _key_count);
        return _compressed_keys[compressed];
    }

    T kth_largest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k < right - left);
        int node = 1;
        while (node < _tree_base) {
            Aggregate right_result = range_query(2 * node + 1, left, right);
            if (k < right_result.count) {
                node = 2 * node + 1;
            } else {
                k -= right_result.count;
                node *= 2;
            }
        }
        int compressed = node - _tree_base;
        assert(0 <= compressed && compressed < _key_count);
        return _compressed_keys[compressed];
    }

    std::optional<T> prev_value(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        int count = range_freq(left, right, upper);
        if (count == 0) return std::nullopt;
        return kth_smallest(left, right, count - 1);
    }

    std::optional<T> next_value(int left, int right, T lower) const {
        assert(0 <= left && left <= right && right <= _size);
        int count = range_freq(left, right, lower);
        if (count == right - left) return std::nullopt;
        return kth_smallest(left, right, count);
    }

    Sum range_sum(int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        return range_query(1, left, right).sum;
    }

    Sum range_sum(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        int upper_index = int(
            std::lower_bound(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                upper
            ) - _compressed_keys.begin()
        );
        return key_range_query(left, right, 0, upper_index).sum;
    }

    Sum range_sum(int left, int right, T lower, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        if (!(lower < upper)) return Sum{};
        int lower_index = int(
            std::lower_bound(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                lower
            ) - _compressed_keys.begin()
        );
        int upper_index = int(
            std::lower_bound(
                _compressed_keys.begin(),
                _compressed_keys.end(),
                upper
            ) - _compressed_keys.begin()
        );
        return key_range_query(
            left,
            right,
            lower_index,
            upper_index
        ).sum;
    }

    Sum sum_k_smallest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k <= right - left);
        if (k == 0) return Sum{};
        Sum result{};
        int node = 1;
        while (node < _tree_base) {
            Aggregate left_result = range_query(2 * node, left, right);
            if (k <= left_result.count) {
                node *= 2;
            } else {
                result = result + left_result.sum;
                k -= left_result.count;
                node = 2 * node + 1;
            }
        }
        return result + sum_first_active(node, left, right, k);
    }

    Sum sum_k_largest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k <= right - left);
        if (k == 0) return Sum{};
        Sum result{};
        int node = 1;
        while (node < _tree_base) {
            Aggregate right_result = range_query(2 * node + 1, left, right);
            if (k <= right_result.count) {
                node = 2 * node + 1;
            } else {
                result = result + right_result.sum;
                k -= right_result.count;
                node *= 2;
            }
        }
        return result + sum_last_active(node, left, right, k);
    }

    std::optional<int> min_count_smallest_sum_at_least(
        int left,
        int right,
        const Sum& target
    ) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(Sum{} < target);
        Aggregate available = range_query(1, left, right);
        if (available.sum < target) return std::nullopt;
        int answer = 0;
        Sum remaining = target;
        int node = 1;
        while (node < _tree_base) {
            Aggregate left_result = range_query(2 * node, left, right);
            if (!(left_result.sum < remaining)) {
                node *= 2;
            } else {
                answer += left_result.count;
                remaining = remaining - left_result.sum;
                node = 2 * node + 1;
            }
        }
        return answer + min_count_first_active_sum_at_least(
                            node,
                            left,
                            right,
                            remaining
                        );
    }

    std::optional<int> min_count_largest_sum_at_least(
        int left,
        int right,
        const Sum& target
    ) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(Sum{} < target);
        Aggregate available = range_query(1, left, right);
        if (available.sum < target) return std::nullopt;
        int answer = 0;
        Sum remaining = target;
        int node = 1;
        while (node < _tree_base) {
            Aggregate right_result = range_query(2 * node + 1, left, right);
            if (!(right_result.sum < remaining)) {
                node = 2 * node + 1;
            } else {
                answer += right_result.count;
                remaining = remaining - right_result.sum;
                node *= 2;
            }
        }
        return answer + min_count_last_active_sum_at_least(
                            node,
                            left,
                            right,
                            remaining
                        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_HPP
