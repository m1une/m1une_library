---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: ds/range_query/offline_point_update_range_order_statistics_sum.hpp
    title: Offline-Registered Point-Update Range Order Statistics with Sums
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
    title: Dynamic Wavelet Matrix
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
    title: Dynamic Wavelet Matrix with Sums
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp\"\
    \n#define M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE 1\n\n\
    #line 1 \"ds/range_query/offline_point_update_range_order_statistics_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\n\
    #include <chrono>\n#include <cstdint>\n#endif\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nnamespace offline_point_update_range_order_statistics_sum_detail {\n\
    \n#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\nstruct\
    \ ConstructionProfile {\n    std::int64_t registration_nanoseconds = 0;\n    std::int64_t\
    \ flatten_nanoseconds = 0;\n    std::int64_t handle_nanoseconds = 0;\n    std::int64_t\
    \ initialization_nanoseconds = 0;\n};\n\ninline ConstructionProfile construction_profile;\n\
    \ninline ConstructionProfile get_construction_profile() {\n    return construction_profile;\n\
    }\n#endif\n\n}  // namespace offline_point_update_range_order_statistics_sum_detail\n\
    \n// Fixed-length point updates and range order statistics with offline keys.\n\
    template <class T, class Sum = T>\nclass OfflinePointUpdateRangeOrderStatisticsSum\
    \ {\n   private:\n    struct Aggregate {\n        int count = 0;\n        Sum\
    \ sum{};\n    };\n\n    struct NodeInfo {\n        int position_offset = 0;\n\
    \        int position_count = 0;\n        int fenwick_offset = 0;\n    };\n\n\
    \    struct Handle {\n        int node = 0;\n        int local_position = 0;\n\
    \    };\n\n    struct CandidateState {\n        int key_index = 0;\n        int\
    \ handle_offset = 0;\n    };\n\n    int _size = 0;\n    int _key_count = 0;\n\
    \    int _tree_base = 1;\n    int _height = 0;\n    std::vector<T> _compressed_keys;\n\
    \    std::vector<NodeInfo> _nodes;\n    std::vector<int> _registered_positions;\n\
    \    std::vector<int> _fenwick_counts;\n    std::vector<Sum> _fenwick_sums;\n\
    \    std::vector<int> _state_offsets;\n    std::vector<CandidateState> _states;\n\
    \    std::vector<Handle> _handles;\n    std::vector<int> _current_states;\n  \
    \  std::vector<Sum> _current_weights;\n\n    static bool equivalent(const T& left,\
    \ const T& right) {\n        return !(left < right) && !(right < left);\n    }\n\
    \n    static int as_int(std::size_t value) {\n        assert(value <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        return int(value);\n    }\n\n    int key_index(const T& key) const {\n\
    \        auto iterator =\n            std::lower_bound(_compressed_keys.begin(),\
    \ _compressed_keys.end(), key);\n        if (iterator == _compressed_keys.end()\
    \ ||\n            !equivalent(*iterator, key)) {\n            return -1;\n   \
    \     }\n        return int(iterator - _compressed_keys.begin());\n    }\n\n \
    \   int find_candidate_state(int position, const T& key) const {\n        assert(0\
    \ <= position && position < _size);\n        auto first = _states.begin() + _state_offsets[position];\n\
    \        auto last = _states.begin() + _state_offsets[position + 1];\n       \
    \ auto iterator = std::lower_bound(\n            first,\n            last,\n \
    \           key,\n            [&](const CandidateState& state, const T& value)\
    \ {\n                return _compressed_keys[state.key_index] < value;\n     \
    \       }\n        );\n        if (iterator == last ||\n            !equivalent(_compressed_keys[iterator->key_index],\
    \ key)) {\n            return -1;\n        }\n        return int(iterator - _states.begin());\n\
    \    }\n\n    int node_position_lower_bound(int node, int original_position) const\
    \ {\n        const NodeInfo& info = _nodes[node];\n        auto first =\n    \
    \        _registered_positions.begin() + info.position_offset;\n        auto last\
    \ = first + info.position_count;\n        return int(std::lower_bound(first, last,\
    \ original_position) - first);\n    }\n\n    int fenwick_prefix_count(int node,\
    \ int right) const {\n        const NodeInfo& info = _nodes[node];\n        int\
    \ result = 0;\n        for (int position = right; position > 0;\n            \
    \ position -= position & -position) {\n            result +=\n               \
    \ _fenwick_counts[info.fenwick_offset + position - 1];\n        }\n        return\
    \ result;\n    }\n\n    Sum fenwick_prefix_sum(int node, int right) const {\n\
    \        const NodeInfo& info = _nodes[node];\n        Sum result{};\n       \
    \ for (int position = right; position > 0;\n             position -= position\
    \ & -position) {\n            result = result +\n                     _fenwick_sums[info.fenwick_offset\
    \ + position - 1];\n        }\n        return result;\n    }\n\n    void fenwick_add(\n\
    \        const Handle& handle,\n        int count_delta,\n        const Sum& sum_delta\n\
    \    ) {\n        const NodeInfo& info = _nodes[handle.node];\n        for (int\
    \ position = handle.local_position + 1;\n             position <= info.position_count;\n\
    \             position += position & -position) {\n            int index = info.fenwick_offset\
    \ + position - 1;\n            _fenwick_counts[index] += count_delta;\n      \
    \      _fenwick_sums[index] = _fenwick_sums[index] + sum_delta;\n        }\n \
    \   }\n\n    void fenwick_subtract(\n        const Handle& handle,\n        int\
    \ count_delta,\n        const Sum& sum_delta\n    ) {\n        const NodeInfo&\
    \ info = _nodes[handle.node];\n        for (int position = handle.local_position\
    \ + 1;\n             position <= info.position_count;\n             position +=\
    \ position & -position) {\n            int index = info.fenwick_offset + position\
    \ - 1;\n            _fenwick_counts[index] -= count_delta;\n            _fenwick_sums[index]\
    \ = _fenwick_sums[index] - sum_delta;\n        }\n    }\n\n    void activate_state(int\
    \ state, const Sum& weight) {\n        int handle_offset = _states[state].handle_offset;\n\
    \        for (int depth = 0; depth <= _height; depth++) {\n            fenwick_add(_handles[handle_offset\
    \ + depth], 1, weight);\n        }\n    }\n\n    void deactivate_state(int state,\
    \ const Sum& weight) {\n        int handle_offset = _states[state].handle_offset;\n\
    \        for (int depth = 0; depth <= _height; depth++) {\n            fenwick_subtract(_handles[handle_offset\
    \ + depth], 1, weight);\n        }\n    }\n\n    void add_to_state(int state,\
    \ const Sum& delta) {\n        int handle_offset = _states[state].handle_offset;\n\
    \        for (int depth = 0; depth <= _height; depth++) {\n            fenwick_add(_handles[handle_offset\
    \ + depth], 0, delta);\n        }\n    }\n\n    Aggregate range_query(int node,\
    \ int left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _size);\n        int local_left = node_position_lower_bound(node, left);\n\
    \        int local_right = node_position_lower_bound(node, right);\n        return\
    \ Aggregate{\n            fenwick_prefix_count(node, local_right) -\n        \
    \        fenwick_prefix_count(node, local_left),\n            fenwick_prefix_sum(node,\
    \ local_right) -\n                fenwick_prefix_sum(node, local_left)\n     \
    \   };\n    }\n\n    Aggregate key_range_query(\n        int left,\n        int\
    \ right,\n        int first_key,\n        int last_key\n    ) const {\n      \
    \  Aggregate result;\n        int first = _tree_base + first_key;\n        int\
    \ last = _tree_base + last_key;\n        while (first < last) {\n            if\
    \ (first & 1) {\n                Aggregate current = range_query(first++, left,\
    \ right);\n                result.count += current.count;\n                result.sum\
    \ = result.sum + current.sum;\n            }\n            if (last & 1) {\n  \
    \              Aggregate current = range_query(--last, left, right);\n       \
    \         result.count += current.count;\n                result.sum = result.sum\
    \ + current.sum;\n            }\n            first >>= 1;\n            last >>=\
    \ 1;\n        }\n        return result;\n    }\n\n    int fenwick_lower_bound_count(int\
    \ node, int target) const {\n        const NodeInfo& info = _nodes[node];\n  \
    \      assert(1 <= target);\n        assert(target <= fenwick_prefix_count(node,\
    \ info.position_count));\n        int position = 0;\n        int accumulated =\
    \ 0;\n        int step = 1;\n        while ((step << 1) <= info.position_count)\
    \ step <<= 1;\n        for (; step != 0; step >>= 1) {\n            int next =\
    \ position + step;\n            if (next <= info.position_count &&\n         \
    \       accumulated +\n                        _fenwick_counts[info.fenwick_offset\
    \ + next - 1] <\n                    target) {\n                position = next;\n\
    \                accumulated +=\n                    _fenwick_counts[info.fenwick_offset\
    \ + next - 1];\n            }\n        }\n        return position;\n    }\n\n\
    \    int fenwick_lower_bound_sum(int node, const Sum& target) const {\n      \
    \  const NodeInfo& info = _nodes[node];\n        int position = 0;\n        Sum\
    \ accumulated{};\n        int step = 1;\n        while ((step << 1) <= info.position_count)\
    \ step <<= 1;\n        for (; step != 0; step >>= 1) {\n            int next =\
    \ position + step;\n            if (next <= info.position_count) {\n         \
    \       Sum candidate =\n                    accumulated +\n                 \
    \   _fenwick_sums[info.fenwick_offset + next - 1];\n                if (candidate\
    \ < target) {\n                    position = next;\n                    accumulated\
    \ = candidate;\n                }\n            }\n        }\n        return position;\n\
    \    }\n\n    int fenwick_max_prefix_sum_at_most(\n        int node,\n       \
    \ const Sum& target,\n        int maximum_length\n    ) const {\n        const\
    \ NodeInfo& info = _nodes[node];\n        assert(0 <= maximum_length &&\n    \
    \           maximum_length <= info.position_count);\n        int position = 0;\n\
    \        Sum accumulated{};\n        int step = 1;\n        while ((step << 1)\
    \ <= info.position_count) step <<= 1;\n        for (; step != 0; step >>= 1) {\n\
    \            int next = position + step;\n            if (next <= maximum_length)\
    \ {\n                Sum candidate =\n                    accumulated +\n    \
    \                _fenwick_sums[info.fenwick_offset + next - 1];\n            \
    \    if (!(target < candidate)) {\n                    position = next;\n    \
    \                accumulated = candidate;\n                }\n            }\n\
    \        }\n        return position;\n    }\n\n    Sum sum_first_active(\n   \
    \     int node,\n        int original_left,\n        int original_right,\n   \
    \     int count\n    ) const {\n        if (count == 0) return Sum{};\n      \
    \  int local_left = node_position_lower_bound(node, original_left);\n        int\
    \ local_right = node_position_lower_bound(node, original_right);\n        int\
    \ count_before = fenwick_prefix_count(node, local_left);\n        int range_count\
    \ =\n            fenwick_prefix_count(node, local_right) - count_before;\n   \
    \     assert(0 <= count && count <= range_count);\n        int boundary =\n  \
    \          fenwick_lower_bound_count(node, count_before + count);\n        assert(boundary\
    \ < local_right);\n        return fenwick_prefix_sum(node, boundary + 1) -\n \
    \              fenwick_prefix_sum(node, local_left);\n    }\n\n    Sum sum_last_active(\n\
    \        int node,\n        int original_left,\n        int original_right,\n\
    \        int count\n    ) const {\n        if (count == 0) return Sum{};\n   \
    \     int local_left = node_position_lower_bound(node, original_left);\n     \
    \   int local_right = node_position_lower_bound(node, original_right);\n     \
    \   int count_through = fenwick_prefix_count(node, local_right);\n        int\
    \ range_count =\n            count_through - fenwick_prefix_count(node, local_left);\n\
    \        assert(0 <= count && count <= range_count);\n        int boundary =\n\
    \            fenwick_lower_bound_count(node, count_through - count + 1);\n   \
    \     assert(local_left <= boundary);\n        return fenwick_prefix_sum(node,\
    \ local_right) -\n               fenwick_prefix_sum(node, boundary);\n    }\n\n\
    \    int min_count_first_active_sum_at_least(\n        int node,\n        int\
    \ original_left,\n        int original_right,\n        const Sum& target\n   \
    \ ) const {\n        int local_left = node_position_lower_bound(node, original_left);\n\
    \        int local_right = node_position_lower_bound(node, original_right);\n\
    \        Sum sum_before = fenwick_prefix_sum(node, local_left);\n        int boundary\
    \ =\n            fenwick_lower_bound_sum(node, sum_before + target);\n       \
    \ assert(boundary < local_right);\n        return fenwick_prefix_count(node, boundary\
    \ + 1) -\n               fenwick_prefix_count(node, local_left);\n    }\n\n  \
    \  int min_count_last_active_sum_at_least(\n        int node,\n        int original_left,\n\
    \        int original_right,\n        const Sum& target\n    ) const {\n     \
    \   (void)original_left;\n        int local_right = node_position_lower_bound(node,\
    \ original_right);\n        Sum sum_through = fenwick_prefix_sum(node, local_right);\n\
    \        int prefix_length = fenwick_max_prefix_sum_at_most(\n            node,\n\
    \            sum_through - target,\n            local_right\n        );\n    \
    \    assert(\n            node_position_lower_bound(node, original_left) <= prefix_length\n\
    \        );\n        return fenwick_prefix_count(node, local_right) -\n      \
    \         fenwick_prefix_count(node, prefix_length);\n    }\n\n    void replace(int\
    \ position, int state, const Sum& weight) {\n        int old_state = _current_states[position];\n\
    \        Sum old_weight = _current_weights[position];\n        if (state == old_state)\
    \ {\n            add_to_state(state, weight - old_weight);\n        } else {\n\
    \            deactivate_state(old_state, old_weight);\n            activate_state(state,\
    \ weight);\n            _current_states[position] = state;\n        }\n      \
    \  _current_weights[position] = weight;\n    }\n\n    void build(\n        const\
    \ std::vector<T>& initial_keys,\n        const std::vector<Sum>& initial_weights,\n\
    \        const std::vector<std::pair<int, T>>& update_candidates\n    ) {\n#ifdef\
    \ M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\n        using\
    \ ProfileClock = std::chrono::steady_clock;\n        using namespace offline_point_update_range_order_statistics_sum_detail;\n\
    \        construction_profile = ConstructionProfile();\n        auto registration_start\
    \ = ProfileClock::now();\n#endif\n        assert(initial_keys.size() == initial_weights.size());\n\
    \        assert(initial_keys.size() <=\n               std::size_t(std::numeric_limits<int>::max()));\n\
    \        _size = int(initial_keys.size());\n        _compressed_keys = initial_keys;\n\
    \        _compressed_keys.reserve(initial_keys.size() + update_candidates.size());\n\
    \        for (const auto& candidate : update_candidates) {\n            assert(0\
    \ <= candidate.first && candidate.first < _size);\n            _compressed_keys.push_back(candidate.second);\n\
    \        }\n        std::sort(_compressed_keys.begin(), _compressed_keys.end());\n\
    \        _compressed_keys.erase(\n            std::unique(\n                _compressed_keys.begin(),\n\
    \                _compressed_keys.end(),\n                [](const T& left, const\
    \ T& right) {\n                    return equivalent(left, right);\n         \
    \       }\n            ),\n            _compressed_keys.end()\n        );\n  \
    \      _key_count = as_int(_compressed_keys.size());\n        _tree_base = 1;\n\
    \        _height = 0;\n        while (_tree_base < std::max(1, _key_count)) {\n\
    \            assert(_tree_base <= std::numeric_limits<int>::max() / 2);\n    \
    \        _tree_base <<= 1;\n            _height++;\n        }\n\n        std::vector<std::vector<int>>\
    \ candidate_keys(_size);\n        for (int position = 0; position < _size; position++)\
    \ {\n            int compressed = key_index(initial_keys[position]);\n       \
    \     assert(compressed != -1);\n            candidate_keys[position].push_back(compressed);\n\
    \        }\n        for (const auto& candidate : update_candidates) {\n      \
    \      int compressed = key_index(candidate.second);\n            assert(compressed\
    \ != -1);\n            candidate_keys[candidate.first].push_back(compressed);\n\
    \        }\n\n        std::size_t state_count = 0;\n        for (auto& keys :\
    \ candidate_keys) {\n            std::sort(keys.begin(), keys.end());\n      \
    \      keys.erase(std::unique(keys.begin(), keys.end()), keys.end());\n      \
    \      state_count += keys.size();\n        }\n        assert(state_count <=\n\
    \               std::size_t(std::numeric_limits<int>::max()));\n        assert(state_count\
    \ * std::size_t(_height + 1) <=\n               std::size_t(std::numeric_limits<int>::max()));\n\
    \n        std::vector<std::vector<int>> registrations(2 * _tree_base);\n     \
    \   for (int position = 0; position < _size; position++) {\n            for (int\
    \ compressed : candidate_keys[position]) {\n                int leaf = _tree_base\
    \ + compressed;\n                for (int shift = _height; shift >= 0; shift--)\
    \ {\n                    registrations[leaf >> shift].push_back(position);\n \
    \               }\n            }\n        }\n#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\n\
    \        auto registration_end = ProfileClock::now();\n        construction_profile.registration_nanoseconds\
    \ =\n            std::chrono::duration_cast<std::chrono::nanoseconds>(\n     \
    \           registration_end - registration_start\n            ).count();\n  \
    \      auto flatten_start = ProfileClock::now();\n#endif\n\n        _nodes.assign(2\
    \ * _tree_base, NodeInfo());\n        _registered_positions.clear();\n       \
    \ _registered_positions.reserve(\n            state_count * std::size_t(_height\
    \ + 1)\n        );\n        for (int node = 1; node < 2 * _tree_base; node++)\
    \ {\n            auto& positions = registrations[node];\n            positions.erase(\n\
    \                std::unique(positions.begin(), positions.end()),\n          \
    \      positions.end()\n            );\n            NodeInfo& info = _nodes[node];\n\
    \            info.position_offset = as_int(_registered_positions.size());\n  \
    \          info.position_count = as_int(positions.size());\n            info.fenwick_offset\
    \ = info.position_offset;\n            _registered_positions.insert(\n       \
    \         _registered_positions.end(),\n                positions.begin(),\n \
    \               positions.end()\n            );\n        }\n        std::vector<std::vector<int>>().swap(registrations);\n\
    \        _fenwick_counts.assign(_registered_positions.size(), 0);\n        _fenwick_sums.assign(_registered_positions.size(),\
    \ Sum{});\n#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\n\
    \        auto flatten_end = ProfileClock::now();\n        construction_profile.flatten_nanoseconds\
    \ =\n            std::chrono::duration_cast<std::chrono::nanoseconds>(\n     \
    \           flatten_end - flatten_start\n            ).count();\n        auto\
    \ handle_start = ProfileClock::now();\n#endif\n\n        _state_offsets.assign(_size\
    \ + 1, 0);\n        _states.clear();\n        _states.reserve(state_count);\n\
    \        _handles.clear();\n        _handles.reserve(state_count * std::size_t(_height\
    \ + 1));\n        for (int position = 0; position < _size; position++) {\n   \
    \         _state_offsets[position] = as_int(_states.size());\n            for\
    \ (int compressed : candidate_keys[position]) {\n                CandidateState\
    \ state;\n                state.key_index = compressed;\n                state.handle_offset\
    \ = as_int(_handles.size());\n                _states.push_back(state);\n    \
    \            int leaf = _tree_base + compressed;\n                for (int shift\
    \ = _height; shift >= 0; shift--) {\n                    int node = leaf >> shift;\n\
    \                    int local_position =\n                        node_position_lower_bound(node,\
    \ position);\n                    assert(local_position < _nodes[node].position_count);\n\
    \                    assert(\n                        _registered_positions[\n\
    \                            _nodes[node].position_offset + local_position\n \
    \                       ] == position\n                    );\n              \
    \      _handles.push_back(Handle{node, local_position});\n                }\n\
    \            }\n        }\n        _state_offsets[_size] = as_int(_states.size());\n\
    \        std::vector<std::vector<int>>().swap(candidate_keys);\n#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\n\
    \        auto handle_end = ProfileClock::now();\n        construction_profile.handle_nanoseconds\
    \ =\n            std::chrono::duration_cast<std::chrono::nanoseconds>(\n     \
    \           handle_end - handle_start\n            ).count();\n        auto initialization_start\
    \ = ProfileClock::now();\n#endif\n\n        _current_states.resize(_size);\n \
    \       _current_weights = initial_weights;\n        for (int position = 0; position\
    \ < _size; position++) {\n            int state = find_candidate_state(position,\
    \ initial_keys[position]);\n            assert(state != -1);\n            _current_states[position]\
    \ = state;\n            activate_state(state, initial_weights[position]);\n  \
    \      }\n#ifdef M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE\n\
    \        auto initialization_end = ProfileClock::now();\n        construction_profile.initialization_nanoseconds\
    \ =\n            std::chrono::duration_cast<std::chrono::nanoseconds>(\n     \
    \           initialization_end - initialization_start\n            ).count();\n\
    #endif\n    }\n\n   public:\n    OfflinePointUpdateRangeOrderStatisticsSum(\n\
    \        const std::vector<T>& initial_values,\n        const std::vector<std::pair<int,\
    \ T>>& update_candidates\n    ) requires std::convertible_to<T, Sum> {\n     \
    \   std::vector<Sum> weights;\n        weights.reserve(initial_values.size());\n\
    \        for (const T& value : initial_values) {\n            weights.push_back(static_cast<Sum>(value));\n\
    \        }\n        build(initial_values, weights, update_candidates);\n    }\n\
    \n    OfflinePointUpdateRangeOrderStatisticsSum(\n        const std::vector<T>&\
    \ initial_keys,\n        const std::vector<Sum>& initial_weights,\n        const\
    \ std::vector<std::pair<int, T>>& update_candidates\n    ) {\n        build(initial_keys,\
    \ initial_weights, update_candidates);\n    }\n\n    int size() const {\n    \
    \    return _size;\n    }\n\n    bool empty() const {\n        return _size ==\
    \ 0;\n    }\n\n    T access(int position) const {\n        assert(0 <= position\
    \ && position < _size);\n        return _compressed_keys[\n            _states[_current_states[position]].key_index\n\
    \        ];\n    }\n\n    T operator[](int position) const {\n        return access(position);\n\
    \    }\n\n    Sum weight(int position) const {\n        assert(0 <= position &&\
    \ position < _size);\n        return _current_weights[position];\n    }\n\n  \
    \  std::pair<T, Sum> get(int position) const {\n        assert(0 <= position &&\
    \ position < _size);\n        return std::pair<T, Sum>(access(position), weight(position));\n\
    \    }\n\n    void set(int position, T key)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        set(position, key, static_cast<Sum>(key));\n    }\n\n \
    \   void set(int position, T key, const Sum& new_weight) {\n        assert(0 <=\
    \ position && position < _size);\n        int state = find_candidate_state(position,\
    \ key);\n        assert(state != -1);\n        if (state == -1) return;\n    \
    \    replace(position, state, new_weight);\n    }\n\n    void set_value(int position,\
    \ T key) {\n        assert(0 <= position && position < _size);\n        int state\
    \ = find_candidate_state(position, key);\n        assert(state != -1);\n     \
    \   if (state == -1) return;\n        if (state == _current_states[position])\
    \ return;\n        replace(position, state, _current_weights[position]);\n   \
    \ }\n\n    void set_weight(int position, const Sum& new_weight) {\n        assert(0\
    \ <= position && position < _size);\n        replace(position, _current_states[position],\
    \ new_weight);\n    }\n\n    void add_weight(int position, const Sum& delta) {\n\
    \        assert(0 <= position && position < _size);\n        add_to_state(_current_states[position],\
    \ delta);\n        _current_weights[position] = _current_weights[position] + delta;\n\
    \    }\n\n    int rank(T key, int right) const {\n        assert(0 <= right &&\
    \ right <= _size);\n        return rank(key, 0, right);\n    }\n\n    int rank(T\
    \ key, int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _size);\n        int compressed = key_index(key);\n        if (compressed\
    \ == -1) return 0;\n        return range_query(_tree_base + compressed, left,\
    \ right).count;\n    }\n\n    int range_freq(int left, int right, T upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        int\
    \ upper_index = int(\n            std::lower_bound(\n                _compressed_keys.begin(),\n\
    \                _compressed_keys.end(),\n                upper\n            )\
    \ - _compressed_keys.begin()\n        );\n        return key_range_query(left,\
    \ right, 0, upper_index).count;\n    }\n\n    int range_freq(int left, int right,\
    \ T lower, T upper) const {\n        assert(0 <= left && left <= right && right\
    \ <= _size);\n        if (!(lower < upper)) return 0;\n        int lower_index\
    \ = int(\n            std::lower_bound(\n                _compressed_keys.begin(),\n\
    \                _compressed_keys.end(),\n                lower\n            )\
    \ - _compressed_keys.begin()\n        );\n        int upper_index = int(\n   \
    \         std::lower_bound(\n                _compressed_keys.begin(),\n     \
    \           _compressed_keys.end(),\n                upper\n            ) - _compressed_keys.begin()\n\
    \        );\n        return key_range_query(\n            left,\n            right,\n\
    \            lower_index,\n            upper_index\n        ).count;\n    }\n\n\
    \    T kth_smallest(int left, int right, int k) const {\n        assert(0 <= left\
    \ && left <= right && right <= _size);\n        assert(0 <= k && k < right - left);\n\
    \        int node = 1;\n        while (node < _tree_base) {\n            Aggregate\
    \ left_result = range_query(2 * node, left, right);\n            if (k < left_result.count)\
    \ {\n                node *= 2;\n            } else {\n                k -= left_result.count;\n\
    \                node = 2 * node + 1;\n            }\n        }\n        int compressed\
    \ = node - _tree_base;\n        assert(0 <= compressed && compressed < _key_count);\n\
    \        return _compressed_keys[compressed];\n    }\n\n    T kth_largest(int\
    \ left, int right, int k) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _size);\n        assert(0 <= k && k < right - left);\n        int node\
    \ = 1;\n        while (node < _tree_base) {\n            Aggregate right_result\
    \ = range_query(2 * node + 1, left, right);\n            if (k < right_result.count)\
    \ {\n                node = 2 * node + 1;\n            } else {\n            \
    \    k -= right_result.count;\n                node *= 2;\n            }\n   \
    \     }\n        int compressed = node - _tree_base;\n        assert(0 <= compressed\
    \ && compressed < _key_count);\n        return _compressed_keys[compressed];\n\
    \    }\n\n    std::optional<T> prev_value(int left, int right, T upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        int\
    \ count = range_freq(left, right, upper);\n        if (count == 0) return std::nullopt;\n\
    \        return kth_smallest(left, right, count - 1);\n    }\n\n    std::optional<T>\
    \ next_value(int left, int right, T lower) const {\n        assert(0 <= left &&\
    \ left <= right && right <= _size);\n        int count = range_freq(left, right,\
    \ lower);\n        if (count == right - left) return std::nullopt;\n        return\
    \ kth_smallest(left, right, count);\n    }\n\n    Sum range_sum(int left, int\
    \ right) const {\n        assert(0 <= left && left <= right && right <= _size);\n\
    \        return range_query(1, left, right).sum;\n    }\n\n    Sum range_sum(int\
    \ left, int right, T upper) const {\n        assert(0 <= left && left <= right\
    \ && right <= _size);\n        int upper_index = int(\n            std::lower_bound(\n\
    \                _compressed_keys.begin(),\n                _compressed_keys.end(),\n\
    \                upper\n            ) - _compressed_keys.begin()\n        );\n\
    \        return key_range_query(left, right, 0, upper_index).sum;\n    }\n\n \
    \   Sum range_sum(int left, int right, T lower, T upper) const {\n        assert(0\
    \ <= left && left <= right && right <= _size);\n        if (!(lower < upper))\
    \ return Sum{};\n        int lower_index = int(\n            std::lower_bound(\n\
    \                _compressed_keys.begin(),\n                _compressed_keys.end(),\n\
    \                lower\n            ) - _compressed_keys.begin()\n        );\n\
    \        int upper_index = int(\n            std::lower_bound(\n             \
    \   _compressed_keys.begin(),\n                _compressed_keys.end(),\n     \
    \           upper\n            ) - _compressed_keys.begin()\n        );\n    \
    \    return key_range_query(\n            left,\n            right,\n        \
    \    lower_index,\n            upper_index\n        ).sum;\n    }\n\n    Sum sum_k_smallest(int\
    \ left, int right, int k) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _size);\n        assert(0 <= k && k <= right - left);\n        if (k\
    \ == 0) return Sum{};\n        Sum result{};\n        int node = 1;\n        while\
    \ (node < _tree_base) {\n            Aggregate left_result = range_query(2 * node,\
    \ left, right);\n            if (k <= left_result.count) {\n                node\
    \ *= 2;\n            } else {\n                result = result + left_result.sum;\n\
    \                k -= left_result.count;\n                node = 2 * node + 1;\n\
    \            }\n        }\n        return result + sum_first_active(node, left,\
    \ right, k);\n    }\n\n    Sum sum_k_largest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k <= right - left);\n        if (k == 0) return Sum{};\n        Sum\
    \ result{};\n        int node = 1;\n        while (node < _tree_base) {\n    \
    \        Aggregate right_result = range_query(2 * node + 1, left, right);\n  \
    \          if (k <= right_result.count) {\n                node = 2 * node + 1;\n\
    \            } else {\n                result = result + right_result.sum;\n \
    \               k -= right_result.count;\n                node *= 2;\n       \
    \     }\n        }\n        return result + sum_last_active(node, left, right,\
    \ k);\n    }\n\n    std::optional<int> min_count_smallest_sum_at_least(\n    \
    \    int left,\n        int right,\n        const Sum& target\n    ) const {\n\
    \        assert(0 <= left && left <= right && right <= _size);\n        assert(Sum{}\
    \ < target);\n        Aggregate available = range_query(1, left, right);\n   \
    \     if (available.sum < target) return std::nullopt;\n        int answer = 0;\n\
    \        Sum remaining = target;\n        int node = 1;\n        while (node <\
    \ _tree_base) {\n            Aggregate left_result = range_query(2 * node, left,\
    \ right);\n            if (!(left_result.sum < remaining)) {\n               \
    \ node *= 2;\n            } else {\n                answer += left_result.count;\n\
    \                remaining = remaining - left_result.sum;\n                node\
    \ = 2 * node + 1;\n            }\n        }\n        return answer + min_count_first_active_sum_at_least(\n\
    \                            node,\n                            left,\n      \
    \                      right,\n                            remaining\n       \
    \                 );\n    }\n\n    std::optional<int> min_count_largest_sum_at_least(\n\
    \        int left,\n        int right,\n        const Sum& target\n    ) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(Sum{}\
    \ < target);\n        Aggregate available = range_query(1, left, right);\n   \
    \     if (available.sum < target) return std::nullopt;\n        int answer = 0;\n\
    \        Sum remaining = target;\n        int node = 1;\n        while (node <\
    \ _tree_base) {\n            Aggregate right_result = range_query(2 * node + 1,\
    \ left, right);\n            if (!(right_result.sum < remaining)) {\n        \
    \        node = 2 * node + 1;\n            } else {\n                answer +=\
    \ right_result.count;\n                remaining = remaining - right_result.sum;\n\
    \                node *= 2;\n            }\n        }\n        return answer +\
    \ min_count_last_active_sum_at_least(\n                            node,\n   \
    \                         left,\n                            right,\n        \
    \                    remaining\n                        );\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\
    \n\n\n\n#line 5 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\n#include\
    \ <array>\n#include <bit>\n#line 9 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\
    \n#include <cstdint>\n#line 15 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\
    \n\n#line 1 \"ds/wavelet_matrix/dynamic_wavelet_matrix.hpp\"\n\n\n\n#line 15 \"\
    ds/wavelet_matrix/dynamic_wavelet_matrix.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nnamespace dynamic_wavelet_matrix_detail {\n\n// A dynamic bit vector\
    \ stored as an implicit treap of small packed chunks.\nclass DynamicRankBitVector\
    \ {\n   public:\n    struct AccessRankResult {\n        bool value;\n        int\
    \ ones_before;\n    };\n\n    struct EraseRankResult {\n        bool value;\n\
    \        int ones_before;\n    };\n\n    struct RankPair {\n        int left_ones;\n\
    \        int right_ones;\n    };\n\n   private:\n    static constexpr int word_bits\
    \ = 64;\n    static constexpr int chunk_words = 4;\n    static constexpr int chunk_capacity\
    \ = word_bits * chunk_words;\n    static constexpr int minimum_chunk_size = chunk_capacity\
    \ / 2;\n\n    struct Node {\n        std::array<std::uint64_t, chunk_words> bits{};\n\
    \        std::uint32_t priority = 0;\n        int left = 0;\n        int right\
    \ = 0;\n        int subtree_size = 0;\n        int subtree_ones = 0;\n       \
    \ std::uint16_t length = 0;\n        std::uint16_t chunk_ones = 0;\n    };\n\n\
    \    std::vector<Node> _nodes;\n    std::vector<int> _free_nodes;\n    int _root\
    \ = 0;\n    std::uint32_t _random_state = 1;\n\n    int size_of(int node) const\
    \ {\n        return _nodes[node].subtree_size;\n    }\n\n    int ones_of(int node)\
    \ const {\n        return _nodes[node].subtree_ones;\n    }\n\n    std::uint32_t\
    \ next_priority() {\n        _random_state ^= _random_state << 13;\n        _random_state\
    \ ^= _random_state >> 17;\n        _random_state ^= _random_state << 5;\n    \
    \    if (_random_state == 0) _random_state = 1;\n        return _random_state;\n\
    \    }\n\n    void update(int node) {\n        if (node == 0) return;\n      \
    \  _nodes[node].subtree_size =\n            size_of(_nodes[node].left) + int(_nodes[node].length)\
    \ +\n            size_of(_nodes[node].right);\n        _nodes[node].subtree_ones\
    \ =\n            ones_of(_nodes[node].left) + int(_nodes[node].chunk_ones) +\n\
    \            ones_of(_nodes[node].right);\n    }\n\n    bool local_get(int node,\
    \ int position) const {\n        return (_nodes[node].bits[position / word_bits]\
    \ >>\n                (position % word_bits)) &\n               1U;\n    }\n\n\
    \    void local_set(int node, int position, bool value) {\n        std::uint64_t\
    \ mask =\n            std::uint64_t(1) << (position % word_bits);\n        std::uint64_t&\
    \ word = _nodes[node].bits[position / word_bits];\n        if (value) {\n    \
    \        word |= mask;\n        } else {\n            word &= ~mask;\n       \
    \ }\n    }\n\n    int local_rank1(int node, int right) const {\n        int full_words\
    \ = right / word_bits;\n        int result = 0;\n        for (int word = 0; word\
    \ < full_words; word++) {\n            result += std::popcount(_nodes[node].bits[word]);\n\
    \        }\n        int remainder = right % word_bits;\n        if (remainder\
    \ != 0) {\n            result += std::popcount(\n                _nodes[node].bits[full_words]\
    \ &\n                ((std::uint64_t(1) << remainder) - 1)\n            );\n \
    \       }\n        return result;\n    }\n\n    void clear_unused_bits(int node)\
    \ {\n        int length = _nodes[node].length;\n        int word = length / word_bits;\n\
    \        int remainder = length % word_bits;\n        if (word < chunk_words)\
    \ {\n            if (remainder == 0) {\n                _nodes[node].bits[word]\
    \ = 0;\n            } else {\n                _nodes[node].bits[word] &=\n   \
    \                 (std::uint64_t(1) << remainder) - 1;\n                word++;\n\
    \            }\n            for (; word < chunk_words; word++) {\n           \
    \     _nodes[node].bits[word] = 0;\n            }\n        }\n    }\n\n    void\
    \ local_insert(int node, int position, bool value) {\n        Node& current =\
    \ _nodes[node];\n        assert(0 <= position && position <= current.length);\n\
    \        assert(current.length < chunk_capacity);\n\n        int first_word =\
    \ position / word_bits;\n        int offset = position % word_bits;\n        for\
    \ (int word = chunk_words - 1; word > first_word; word--) {\n            current.bits[word]\
    \ =\n                (current.bits[word] << 1) |\n                (current.bits[word\
    \ - 1] >> (word_bits - 1));\n        }\n        std::uint64_t lower_mask =\n \
    \           offset == 0 ? 0 : (std::uint64_t(1) << offset) - 1;\n        current.bits[first_word]\
    \ =\n            (current.bits[first_word] & lower_mask) |\n            ((current.bits[first_word]\
    \ & ~lower_mask) << 1);\n        if (value) {\n            current.bits[first_word]\
    \ |= std::uint64_t(1) << offset;\n        }\n        current.length++;\n     \
    \   current.chunk_ones += value;\n        clear_unused_bits(node);\n        update(node);\n\
    \    }\n\n    bool local_erase(int node, int position) {\n        Node& current\
    \ = _nodes[node];\n        assert(0 <= position && position < current.length);\n\
    \        bool value = local_get(node, position);\n        int first_word = position\
    \ / word_bits;\n        int offset = position % word_bits;\n        std::uint64_t\
    \ lower_mask =\n            offset == 0 ? 0 : (std::uint64_t(1) << offset) - 1;\n\
    \        std::uint64_t shifted =\n            offset == word_bits - 1\n      \
    \          ? 0\n                : (current.bits[first_word] >> (offset + 1)) <<\
    \ offset;\n        std::uint64_t carry =\n            first_word + 1 < chunk_words\n\
    \                ? (current.bits[first_word + 1] & 1U) << (word_bits - 1)\n  \
    \              : 0;\n        current.bits[first_word] =\n            (current.bits[first_word]\
    \ & lower_mask) | shifted | carry;\n        for (int word = first_word + 1; word\
    \ < chunk_words; word++) {\n            std::uint64_t next_carry =\n         \
    \       word + 1 < chunk_words\n                    ? (current.bits[word + 1]\
    \ & 1U) << (word_bits - 1)\n                    : 0;\n            current.bits[word]\
    \ = (current.bits[word] >> 1) | next_carry;\n        }\n        current.length--;\n\
    \        current.chunk_ones -= value;\n        clear_unused_bits(node);\n    \
    \    update(node);\n        return value;\n    }\n\n    int new_node() {\n   \
    \     int node;\n        if (_free_nodes.empty()) {\n            node = int(_nodes.size());\n\
    \            _nodes.emplace_back();\n        } else {\n            node = _free_nodes.back();\n\
    \            _free_nodes.pop_back();\n            _nodes[node] = Node();\n   \
    \     }\n        _nodes[node].priority = next_priority();\n        return node;\n\
    \    }\n\n    int new_node(const std::vector<std::uint8_t>& bits, int first, int\
    \ last) {\n        int node = new_node();\n        _nodes[node].length = std::uint16_t(last\
    \ - first);\n        for (int position = first; position < last; position++) {\n\
    \            if (bits[position]) {\n                local_set(node, position -\
    \ first, true);\n                _nodes[node].chunk_ones++;\n            }\n \
    \       }\n        update(node);\n        return node;\n    }\n\n    void recycle_node(int\
    \ node) {\n        assert(node != 0);\n        _nodes[node] = Node();\n      \
    \  _free_nodes.push_back(node);\n    }\n\n    int merge(int left, int right) {\n\
    \        if (left == 0 || right == 0) return left != 0 ? left : right;\n     \
    \   if (_nodes[left].priority > _nodes[right].priority) {\n            _nodes[left].right\
    \ = merge(_nodes[left].right, right);\n            update(left);\n           \
    \ return left;\n        }\n        _nodes[right].left = merge(left, _nodes[right].left);\n\
    \        update(right);\n        return right;\n    }\n\n    int rotate_right(int\
    \ tree) {\n        int result = _nodes[tree].left;\n        _nodes[tree].left\
    \ = _nodes[result].right;\n        _nodes[result].right = tree;\n        update(tree);\n\
    \        update(result);\n        return result;\n    }\n\n    int rotate_left(int\
    \ tree) {\n        int result = _nodes[tree].right;\n        _nodes[tree].right\
    \ = _nodes[result].left;\n        _nodes[result].left = tree;\n        update(tree);\n\
    \        update(result);\n        return result;\n    }\n\n    int extract_leftmost(int\
    \ tree, int& extracted) {\n        if (_nodes[tree].left == 0) {\n           \
    \ extracted = tree;\n            int result = _nodes[tree].right;\n          \
    \  _nodes[tree].right = 0;\n            update(tree);\n            return result;\n\
    \        }\n        _nodes[tree].left = extract_leftmost(_nodes[tree].left, extracted);\n\
    \        update(tree);\n        return tree;\n    }\n\n    int extract_rightmost(int\
    \ tree, int& extracted) {\n        if (_nodes[tree].right == 0) {\n          \
    \  extracted = tree;\n            int result = _nodes[tree].left;\n          \
    \  _nodes[tree].left = 0;\n            update(tree);\n            return result;\n\
    \        }\n        _nodes[tree].right = extract_rightmost(_nodes[tree].right,\
    \ extracted);\n        update(tree);\n        return tree;\n    }\n\n    void\
    \ assign_concatenation(\n        int destination,\n        int first,\n      \
    \  int second,\n        int begin,\n        int length\n    ) {\n        std::array<std::uint64_t,\
    \ chunk_words> bits{};\n        int ones = 0;\n        int first_length = _nodes[first].length;\n\
    \        for (int position = 0; position < length; position++) {\n           \
    \ int source_position = begin + position;\n            bool value = source_position\
    \ < first_length\n                             ? local_get(first, source_position)\n\
    \                             : local_get(\n                                 \
    \  second,\n                                   source_position - first_length\n\
    \                               );\n            if (value) {\n               \
    \ bits[position / word_bits] |=\n                    std::uint64_t(1) << (position\
    \ % word_bits);\n                ones++;\n            }\n        }\n        _nodes[destination].bits\
    \ = bits;\n        _nodes[destination].length = std::uint16_t(length);\n     \
    \   _nodes[destination].chunk_ones = std::uint16_t(ones);\n        update(destination);\n\
    \    }\n\n    int rebalance(int node) {\n        if (_nodes[node].length >= minimum_chunk_size)\
    \ return node;\n\n        if (_nodes[node].right != 0) {\n            int neighbor\
    \ = 0;\n            _nodes[node].right =\n                extract_leftmost(_nodes[node].right,\
    \ neighbor);\n            int total = _nodes[node].length + _nodes[neighbor].length;\n\
    \            if (total <= chunk_capacity) {\n                assign_concatenation(node,\
    \ node, neighbor, 0, total);\n                recycle_node(neighbor);\n      \
    \      } else {\n                int left_length = total / 2;\n              \
    \  std::array<std::uint8_t, chunk_capacity * 2> values{};\n                for\
    \ (int i = 0; i < _nodes[node].length; i++) {\n                    values[i] =\
    \ local_get(node, i);\n                }\n                int old_length = _nodes[node].length;\n\
    \                for (int i = 0; i < _nodes[neighbor].length; i++) {\n       \
    \             values[old_length + i] = local_get(neighbor, i);\n             \
    \   }\n                std::vector<std::uint8_t> packed(values.begin(), values.begin()\
    \ + total);\n                assign_from_values(node, packed, 0, left_length);\n\
    \                assign_from_values(neighbor, packed, left_length, total);\n \
    \               _nodes[node].right = merge(neighbor, _nodes[node].right);\n  \
    \          }\n            update(node);\n            return node;\n        }\n\
    \n        if (_nodes[node].left != 0) {\n            int neighbor = 0;\n     \
    \       _nodes[node].left =\n                extract_rightmost(_nodes[node].left,\
    \ neighbor);\n            int total = _nodes[neighbor].length + _nodes[node].length;\n\
    \            std::array<std::uint8_t, chunk_capacity * 2> values{};\n        \
    \    for (int i = 0; i < _nodes[neighbor].length; i++) {\n                values[i]\
    \ = local_get(neighbor, i);\n            }\n            int neighbor_length =\
    \ _nodes[neighbor].length;\n            for (int i = 0; i < _nodes[node].length;\
    \ i++) {\n                values[neighbor_length + i] = local_get(node, i);\n\
    \            }\n            std::vector<std::uint8_t> packed(values.begin(), values.begin()\
    \ + total);\n            if (total <= chunk_capacity) {\n                assign_from_values(node,\
    \ packed, 0, total);\n                recycle_node(neighbor);\n            } else\
    \ {\n                int left_length = total / 2;\n                assign_from_values(neighbor,\
    \ packed, 0, left_length);\n                assign_from_values(node, packed, left_length,\
    \ total);\n                _nodes[node].left = merge(_nodes[node].left, neighbor);\n\
    \            }\n            update(node);\n        }\n        return node;\n \
    \   }\n\n    void assign_from_values(\n        int node,\n        const std::vector<std::uint8_t>&\
    \ values,\n        int first,\n        int last\n    ) {\n        _nodes[node].bits.fill(0);\n\
    \        _nodes[node].length = std::uint16_t(last - first);\n        _nodes[node].chunk_ones\
    \ = 0;\n        for (int i = first; i < last; i++) {\n            if (values[i])\
    \ {\n                local_set(node, i - first, true);\n                _nodes[node].chunk_ones++;\n\
    \            }\n        }\n        update(node);\n    }\n\n    int prefix_rank1_impl(int\
    \ tree, int right) const {\n        int result = 0;\n        while (tree != 0\
    \ && right != 0) {\n            int left_size = size_of(_nodes[tree].left);\n\
    \            if (right <= left_size) {\n                tree = _nodes[tree].left;\n\
    \                continue;\n            }\n            result += ones_of(_nodes[tree].left);\n\
    \            right -= left_size;\n            int take = std::min(right, int(_nodes[tree].length));\n\
    \            result += local_rank1(tree, take);\n            right -= take;\n\
    \            if (right == 0) break;\n            tree = _nodes[tree].right;\n\
    \        }\n        return result;\n    }\n\n    RankPair rank1_pair_impl(int\
    \ tree, int left, int right) const {\n        if (left == right) {\n         \
    \   int ones = prefix_rank1_impl(tree, left);\n            return RankPair{ones,\
    \ ones};\n        }\n        if (tree == 0 || right == 0) return RankPair{0, 0};\n\
    \n        int left_size = size_of(_nodes[tree].left);\n        int chunk_end =\
    \ left_size + _nodes[tree].length;\n        if (right <= left_size) {\n      \
    \      return rank1_pair_impl(_nodes[tree].left, left, right);\n        }\n  \
    \      if (chunk_end <= left) {\n            int base =\n                ones_of(_nodes[tree].left)\
    \ + _nodes[tree].chunk_ones;\n            RankPair result = rank1_pair_impl(\n\
    \                _nodes[tree].right,\n                left - chunk_end,\n    \
    \            right - chunk_end\n            );\n            result.left_ones +=\
    \ base;\n            result.right_ones += base;\n            return result;\n\
    \        }\n\n        int left_ones;\n        if (left <= left_size) {\n     \
    \       left_ones = prefix_rank1_impl(_nodes[tree].left, left);\n        } else\
    \ {\n            left_ones = ones_of(_nodes[tree].left) +\n                  \
    \      local_rank1(tree, left - left_size);\n        }\n\n        int right_ones;\n\
    \        if (right <= chunk_end) {\n            right_ones = ones_of(_nodes[tree].left)\
    \ +\n                         local_rank1(tree, right - left_size);\n        }\
    \ else {\n            right_ones = ones_of(_nodes[tree].left) +\n            \
    \             _nodes[tree].chunk_ones +\n                         prefix_rank1_impl(\n\
    \                             _nodes[tree].right,\n                          \
    \   right - chunk_end\n                         );\n        }\n        return\
    \ RankPair{left_ones, right_ones};\n    }\n\n    int insert_impl(\n        int\
    \ tree,\n        int position,\n        bool value,\n        int& ones_before\n\
    \    ) {\n        if (tree == 0) {\n            int node = new_node();\n     \
    \       local_insert(node, 0, value);\n            return node;\n        }\n\n\
    \        int left_size = size_of(_nodes[tree].left);\n        int length = _nodes[tree].length;\n\
    \        if (position < left_size) {\n            _nodes[tree].left = insert_impl(\n\
    \                _nodes[tree].left,\n                position,\n             \
    \   value,\n                ones_before\n            );\n            update(tree);\n\
    \            if (_nodes[_nodes[tree].left].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_right(tree);\n            }\n            return\
    \ tree;\n        }\n        if (position > left_size + length) {\n           \
    \ ones_before +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = insert_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                value,\n    \
    \            ones_before\n            );\n            update(tree);\n        \
    \    if (_nodes[_nodes[tree].right].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_left(tree);\n            }\n            return\
    \ tree;\n        }\n\n        int local_position = position - left_size;\n   \
    \     ones_before += ones_of(_nodes[tree].left) +\n                       local_rank1(tree,\
    \ local_position);\n        if (length < chunk_capacity) {\n            local_insert(tree,\
    \ local_position, value);\n            return tree;\n        }\n\n        std::vector<std::uint8_t>\
    \ values(chunk_capacity);\n        for (int i = 0; i < chunk_capacity; i++) {\n\
    \            values[i] = local_get(tree, i);\n        }\n        int right_chunk\
    \ = new_node();\n        int middle = chunk_capacity / 2;\n        assign_from_values(tree,\
    \ values, 0, middle);\n        assign_from_values(right_chunk, values, middle,\
    \ chunk_capacity);\n        if (local_position <= middle) {\n            local_insert(tree,\
    \ local_position, value);\n        } else {\n            local_insert(right_chunk,\
    \ local_position - middle, value);\n        }\n\n        int old_right = _nodes[tree].right;\n\
    \        _nodes[tree].right = 0;\n        update(tree);\n        return merge(merge(tree,\
    \ right_chunk), old_right);\n    }\n\n    int erase_impl(\n        int tree,\n\
    \        int position,\n        EraseRankResult& result\n    ) {\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int length = _nodes[tree].length;\n\
    \        if (position < left_size) {\n            _nodes[tree].left = erase_impl(\n\
    \                _nodes[tree].left,\n                position,\n             \
    \   result\n            );\n            update(tree);\n            return tree;\n\
    \        }\n        if (position >= left_size + length) {\n            result.ones_before\
    \ +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = erase_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                result\n    \
    \        );\n            update(tree);\n            return tree;\n        }\n\n\
    \        int local_position = position - left_size;\n        result.ones_before\
    \ += ones_of(_nodes[tree].left) +\n                              local_rank1(tree,\
    \ local_position);\n        result.value = local_erase(tree, local_position);\n\
    \        if (_nodes[tree].length == 0) {\n            int merged = merge(_nodes[tree].left,\
    \ _nodes[tree].right);\n            recycle_node(tree);\n            return merged;\n\
    \        }\n        return rebalance(tree);\n    }\n\n    void update_subtree(int\
    \ tree) {\n        if (tree == 0) return;\n        update_subtree(_nodes[tree].left);\n\
    \        update_subtree(_nodes[tree].right);\n        update(tree);\n    }\n\n\
    \    void build(const std::vector<std::uint8_t>& bits) {\n        _nodes.clear();\n\
    \        _nodes.emplace_back();\n        _free_nodes.clear();\n        _root =\
    \ 0;\n        _nodes.reserve(bits.size() / minimum_chunk_size + 2);\n\n      \
    \  std::vector<int> stack;\n        for (int first = 0; first < int(bits.size());\
    \ first += chunk_capacity) {\n            int last = std::min(first + chunk_capacity,\
    \ int(bits.size()));\n            int node = new_node(bits, first, last);\n  \
    \          int left = 0;\n            while (!stack.empty() &&\n             \
    \      _nodes[stack.back()].priority < _nodes[node].priority) {\n            \
    \    left = stack.back();\n                stack.pop_back();\n            }\n\
    \            _nodes[node].left = left;\n            if (!stack.empty()) _nodes[stack.back()].right\
    \ = node;\n            stack.push_back(node);\n        }\n        if (!stack.empty())\
    \ _root = stack.front();\n        update_subtree(_root);\n    }\n\n   public:\n\
    \    DynamicRankBitVector() : _nodes(1) {}\n\n    explicit DynamicRankBitVector(\n\
    \        const std::vector<std::uint8_t>& bits,\n        std::uint32_t seed =\
    \ 1\n    ) : _random_state(seed == 0 ? 1 : seed) {\n        build(bits);\n   \
    \ }\n\n    int size() const {\n        return size_of(_root);\n    }\n\n    bool\
    \ get(int position) const {\n        return access_with_rank(position).value;\n\
    \    }\n\n    AccessRankResult access_with_rank(int position) const {\n      \
    \  assert(0 <= position && position < size());\n        int ones_before = 0;\n\
    \        int tree = _root;\n        while (tree != 0) {\n            int left_size\
    \ = size_of(_nodes[tree].left);\n            if (position < left_size) {\n   \
    \             tree = _nodes[tree].left;\n            } else if (position < left_size\
    \ + _nodes[tree].length) {\n                int local_position = position - left_size;\n\
    \                ones_before += ones_of(_nodes[tree].left) +\n               \
    \                local_rank1(tree, local_position);\n                return AccessRankResult{\n\
    \                    local_get(tree, local_position),\n                    ones_before\n\
    \                };\n            } else {\n                ones_before +=\n  \
    \                  ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n   \
    \             position -= left_size + _nodes[tree].length;\n                tree\
    \ = _nodes[tree].right;\n            }\n        }\n        assert(false);\n  \
    \      return AccessRankResult{false, 0};\n    }\n\n    int rank1(int right) const\
    \ {\n        assert(0 <= right && right <= size());\n        return prefix_rank1_impl(_root,\
    \ right);\n    }\n\n    RankPair rank1_pair(int left, int right) const {\n   \
    \     assert(0 <= left && left <= right && right <= size());\n        return rank1_pair_impl(_root,\
    \ left, right);\n    }\n\n    void insert(int position, bool value) {\n      \
    \  insert_with_rank(position, value);\n    }\n\n    int insert_with_rank(int position,\
    \ bool value) {\n        assert(0 <= position && position <= size());\n      \
    \  int ones_before = 0;\n        _root = insert_impl(_root, position, value, ones_before);\n\
    \        return ones_before;\n    }\n\n    bool erase(int position) {\n      \
    \  return erase_with_rank(position).value;\n    }\n\n    EraseRankResult erase_with_rank(int\
    \ position) {\n        assert(0 <= position && position < size());\n        EraseRankResult\
    \ result{false, 0};\n        _root = erase_impl(_root, position, result);\n  \
    \      return result;\n    }\n};\n\n}  // namespace dynamic_wavelet_matrix_detail\n\
    \n// A dynamic wavelet matrix for integral sequences.\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nclass DynamicWaveletMatrix\
    \ {\n   public:\n    using value_type = T;\n    using unsigned_type = std::make_unsigned_t<T>;\n\
    \n   private:\n    static constexpr int bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (bit_width - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    int _size =\
    \ 0;\n    std::vector<dynamic_wavelet_matrix_detail::DynamicRankBitVector> _matrix;\n\
    \    std::array<int, bit_width> _zero_count{};\n\n    static unsigned_type encode(T\
    \ value) {\n        unsigned_type bits;\n        if constexpr (std::signed_integral<T>)\
    \ {\n            bits = std::bit_cast<unsigned_type>(value);\n        } else {\n\
    \            bits = value;\n        }\n        return bits ^ sign_mask;\n    }\n\
    \n    static T decode(unsigned_type key) {\n        unsigned_type bits = key ^\
    \ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n            return\
    \ std::bit_cast<T>(bits);\n        } else {\n            return bits;\n      \
    \  }\n    }\n\n    static bool bit(unsigned_type key, int level) {\n        return\
    \ (key >> (bit_width - 1 - level)) & unsigned_type(1);\n    }\n\n    void insert_encoded(int\
    \ position, unsigned_type key) {\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            if (bit(key, level)) {\n                int ones_before\
    \ =\n                    _matrix[level].insert_with_rank(position, true);\n  \
    \              int next_position = _zero_count[level] + ones_before;\n       \
    \         position = next_position;\n            } else {\n                int\
    \ ones_before =\n                    _matrix[level].insert_with_rank(position,\
    \ false);\n                int next_position = position - ones_before;\n     \
    \           _zero_count[level]++;\n                position = next_position;\n\
    \            }\n        }\n        _size++;\n    }\n\n    void erase_encoded(int\
    \ position) {\n        for (int level = 0; level < bit_width; level++) {\n   \
    \         auto erased = _matrix[level].erase_with_rank(position);\n          \
    \  int next_position;\n            if (erased.value) {\n                next_position\
    \ = _zero_count[level] + erased.ones_before;\n            } else {\n         \
    \       next_position = position - erased.ones_before;\n                _zero_count[level]--;\n\
    \            }\n            position = next_position;\n        }\n        _size--;\n\
    \    }\n\n    int count_less_encoded(int left, int right, unsigned_type upper)\
    \ const {\n        int result = 0;\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            auto ranks = _matrix[level].rank1_pair(left, right);\n\
    \            int left_ones = ranks.left_ones;\n            int right_ones = ranks.right_ones;\n\
    \            if (bit(upper, level)) {\n                result += (right - left)\
    \ - (right_ones - left_ones);\n                left = _zero_count[level] + left_ones;\n\
    \                right = _zero_count[level] + right_ones;\n            } else\
    \ {\n                left -= left_ones;\n                right -= right_ones;\n\
    \            }\n        }\n        return result;\n    }\n\n   public:\n    DynamicWaveletMatrix()\
    \ : _matrix(bit_width) {}\n\n    explicit DynamicWaveletMatrix(const std::vector<T>&\
    \ values)\n        : _size(int(values.size())) {\n        std::vector<unsigned_type>\
    \ current(_size);\n        std::vector<unsigned_type> next(_size);\n        for\
    \ (int i = 0; i < _size; i++) current[i] = encode(values[i]);\n\n        _matrix.reserve(bit_width);\n\
    \        for (int level = 0; level < bit_width; level++) {\n            std::vector<std::uint8_t>\
    \ bits(_size);\n            int zeros = 0;\n            for (int i = 0; i < _size;\
    \ i++) {\n                bits[i] = bit(current[i], level);\n                zeros\
    \ += !bits[i];\n            }\n            _zero_count[level] = zeros;\n     \
    \       int zero_position = 0;\n            int one_position = zeros;\n      \
    \      for (int i = 0; i < _size; i++) {\n                if (bits[i]) {\n   \
    \                 next[one_position++] = current[i];\n                } else {\n\
    \                    next[zero_position++] = current[i];\n                }\n\
    \            }\n            _matrix.emplace_back(\n                bits,\n   \
    \             std::uint32_t(0x9e3779b9U + level * 0x85ebca6bU)\n            );\n\
    \            current.swap(next);\n        }\n    }\n\n    int size() const {\n\
    \        return _size;\n    }\n\n    bool empty() const {\n        return _size\
    \ == 0;\n    }\n\n    void clear() {\n        *this = DynamicWaveletMatrix();\n\
    \    }\n\n    T access(int position) const {\n        assert(0 <= position &&\
    \ position < _size);\n        unsigned_type key = 0;\n        for (int level =\
    \ 0; level < bit_width; level++) {\n            auto accessed = _matrix[level].access_with_rank(position);\n\
    \            if (accessed.value) {\n                key |= unsigned_type(1) <<\
    \ (bit_width - 1 - level);\n                position = _zero_count[level] + accessed.ones_before;\n\
    \            } else {\n                position -= accessed.ones_before;\n   \
    \         }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ position) const {\n        return access(position);\n    }\n\n    void insert(int\
    \ position, T value) {\n        assert(0 <= position && position <= _size);\n\
    \        insert_encoded(position, encode(value));\n    }\n\n    void push_back(T\
    \ value) {\n        insert(_size, value);\n    }\n\n    T erase(int position)\
    \ {\n        assert(0 <= position && position < _size);\n        T value = access(position);\n\
    \        erase_encoded(position);\n        return value;\n    }\n\n    void set(int\
    \ position, T value) {\n        assert(0 <= position && position < _size);\n \
    \       if (access(position) == value) return;\n        erase_encoded(position);\n\
    \        insert_encoded(position, encode(value));\n    }\n\n    int rank(T value,\
    \ int right) const {\n        assert(0 <= right && right <= _size);\n        return\
    \ rank(value, 0, right);\n    }\n\n    int rank(T value, int left, int right)\
    \ const {\n        assert(0 <= left && left <= right && right <= _size);\n   \
    \     unsigned_type key = encode(value);\n        for (int level = 0; level <\
    \ bit_width; level++) {\n            auto ranks = _matrix[level].rank1_pair(left,\
    \ right);\n            int left_ones = ranks.left_ones;\n            int right_ones\
    \ = ranks.right_ones;\n            if (bit(key, level)) {\n                left\
    \ = _zero_count[level] + left_ones;\n                right = _zero_count[level]\
    \ + right_ones;\n            } else {\n                left -= left_ones;\n  \
    \              right -= right_ones;\n            }\n        }\n        return\
    \ right - left;\n    }\n\n    T kth_smallest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        unsigned_type key = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            auto ranks = _matrix[level].rank1_pair(left,\
    \ right);\n            int left_ones = ranks.left_ones;\n            int right_ones\
    \ = ranks.right_ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            if (k < zeros) {\n                left = left_zeros;\n\
    \                right = right_zeros;\n            } else {\n                k\
    \ -= zeros;\n                key |= unsigned_type(1) << (bit_width - 1 - level);\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            }\n        }\n        return\
    \ decode(key);\n    }\n\n    T kth_largest(int left, int right, int k) const {\n\
    \        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        return kth_smallest(left, right, right -\
    \ left - 1 - k);\n    }\n\n    int range_freq(int left, int right, T upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        return\
    \ count_less_encoded(left, right, encode(upper));\n    }\n\n    int range_freq(int\
    \ left, int right, T lower, T upper) const {\n        assert(0 <= left && left\
    \ <= right && right <= _size);\n        if (upper <= lower) return 0;\n      \
    \  return range_freq(left, right, upper) -\n               range_freq(left, right,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int left, int right, T upper)\
    \ const {\n        assert(0 <= left && left <= right && right <= _size);\n   \
    \     int count = range_freq(left, right, upper);\n        if (count == 0) return\
    \ std::nullopt;\n        return kth_smallest(left, right, count - 1);\n    }\n\
    \n    std::optional<T> next_value(int left, int right, T lower) const {\n    \
    \    assert(0 <= left && left <= right && right <= _size);\n        int count\
    \ = range_freq(left, right, lower);\n        if (count == right - left) return\
    \ std::nullopt;\n        return kth_smallest(left, right, count);\n    }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 17 \"ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nnamespace dynamic_wavelet_matrix_sum_detail\
    \ {\n\n#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE\nstruct DynamicWaveletMatrixSumProfile\
    \ {\n    std::uint64_t bitvector_tree_traversals = 0;\n    std::uint64_t weight_tree_traversals\
    \ = 0;\n    std::uint64_t chunk_splits = 0;\n    std::uint64_t chunk_merges =\
    \ 0;\n    std::uint64_t local_element_moves = 0;\n    std::uint64_t full_chunk_rebuilds\
    \ = 0;\n};\n\ninline DynamicWaveletMatrixSumProfile profile;\n\ninline void reset_profile()\
    \ {\n    profile = DynamicWaveletMatrixSumProfile();\n}\n\ninline DynamicWaveletMatrixSumProfile\
    \ get_profile() {\n    return profile;\n}\n\n#define M1UNE_DWM_SUM_PROFILE_ADD(field,\
    \ amount) \\\n    (::m1une::ds::dynamic_wavelet_matrix_sum_detail::profile.field\
    \ += \\\n     (amount))\n#else\n#define M1UNE_DWM_SUM_PROFILE_ADD(field, amount)\
    \ ((void)0)\n#endif\n\n#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_CHUNK_CAPACITY\n\
    inline constexpr int configured_chunk_capacity =\n    M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_CHUNK_CAPACITY;\n\
    #else\ninline constexpr int configured_chunk_capacity = 64;\n#endif\n\n#ifdef\
    \ M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_GROUP_SIZE\ninline constexpr int configured_group_size\
    \ =\n    M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_GROUP_SIZE;\n#else\ninline constexpr\
    \ int configured_group_size = 16;\n#endif\n\n// A chunked implicit treap storing\
    \ routing bits and additive weights together.\ntemplate <\n    typename Sum,\n\
    \    int ChunkCapacity = configured_chunk_capacity,\n    int GroupSize = configured_group_size\n\
    >\nclass DynamicWeightedRankSequence {\n   public:\n    struct AccessRankResult\
    \ {\n        bool bit;\n        Sum weight;\n        int ones_before;\n    };\n\
    \n    struct EraseRankResult {\n        bool bit;\n        Sum weight;\n     \
    \   int ones_before;\n    };\n\n    struct PrefixStats {\n        int ones = 0;\n\
    \        Sum total_sum{};\n        Sum zero_sum{};\n    };\n\n    struct PrefixStatsPair\
    \ {\n        PrefixStats left;\n        PrefixStats right;\n    };\n\n   private:\n\
    \    static_assert(2 <= ChunkCapacity);\n    static_assert(\n        ChunkCapacity\
    \ <= std::numeric_limits<std::uint16_t>::max()\n    );\n    static_assert(0 <\
    \ GroupSize && GroupSize <= ChunkCapacity);\n    static_assert(ChunkCapacity %\
    \ GroupSize == 0);\n    static constexpr int word_bits = 64;\n    static constexpr\
    \ int word_count =\n        (ChunkCapacity + word_bits - 1) / word_bits;\n   \
    \ static constexpr int group_count = ChunkCapacity / GroupSize;\n    static constexpr\
    \ int minimum_chunk_size = ChunkCapacity / 2;\n\n    struct Node {\n        std::array<Sum,\
    \ ChunkCapacity> weights{};\n        std::array<Sum, group_count> group_total_sums{};\n\
    \        std::array<Sum, group_count> group_zero_sums{};\n        std::array<std::uint64_t,\
    \ word_count> bits{};\n        Sum chunk_total_sum{};\n        Sum chunk_zero_sum{};\n\
    \        Sum subtree_total_sum{};\n        Sum subtree_zero_sum{};\n        std::uint32_t\
    \ priority = 0;\n        int left = 0;\n        int right = 0;\n        int subtree_size\
    \ = 0;\n        int subtree_ones = 0;\n        std::uint16_t length = 0;\n   \
    \     std::uint16_t chunk_ones = 0;\n    };\n\n    std::vector<Node> _nodes;\n\
    \    std::vector<int> _free_nodes;\n    int _root = 0;\n    std::uint32_t _random_state\
    \ = 1;\n\n    int size_of(int node) const {\n        return _nodes[node].subtree_size;\n\
    \    }\n\n    int ones_of(int node) const {\n        return _nodes[node].subtree_ones;\n\
    \    }\n\n    const Sum& total_sum_of(int node) const {\n        return _nodes[node].subtree_total_sum;\n\
    \    }\n\n    const Sum& zero_sum_of(int node) const {\n        return _nodes[node].subtree_zero_sum;\n\
    \    }\n\n    std::uint32_t next_priority() {\n        _random_state ^= _random_state\
    \ << 13;\n        _random_state ^= _random_state >> 17;\n        _random_state\
    \ ^= _random_state << 5;\n        if (_random_state == 0) _random_state = 1;\n\
    \        return _random_state;\n    }\n\n    bool local_bit(int node, int position)\
    \ const {\n        return (_nodes[node].bits[position / word_bits] >>\n      \
    \          (position % word_bits)) &\n               1U;\n    }\n\n    void local_set_bit(int\
    \ node, int position, bool bit) {\n        std::uint64_t mask =\n            std::uint64_t(1)\
    \ << (position % word_bits);\n        std::uint64_t& word = _nodes[node].bits[position\
    \ / word_bits];\n        if (bit) {\n            word |= mask;\n        } else\
    \ {\n            word &= ~mask;\n        }\n    }\n\n    int local_rank1(int node,\
    \ int right) const {\n        int full_words = right / word_bits;\n        int\
    \ result = 0;\n        for (int word = 0; word < full_words; word++) {\n     \
    \       result += std::popcount(_nodes[node].bits[word]);\n        }\n       \
    \ int remainder = right % word_bits;\n        if (remainder != 0) {\n        \
    \    result += std::popcount(\n                _nodes[node].bits[full_words] &\n\
    \                ((std::uint64_t(1) << remainder) - 1)\n            );\n     \
    \   }\n        return result;\n    }\n\n    void update(int node) {\n        if\
    \ (node == 0) return;\n        Node& current = _nodes[node];\n        current.subtree_size\
    \ =\n            size_of(current.left) + int(current.length) +\n            size_of(current.right);\n\
    \        current.subtree_ones =\n            ones_of(current.left) + int(current.chunk_ones)\
    \ +\n            ones_of(current.right);\n        current.subtree_total_sum =\n\
    \            total_sum_of(current.left) + current.chunk_total_sum +\n        \
    \    total_sum_of(current.right);\n        current.subtree_zero_sum =\n      \
    \      zero_sum_of(current.left) + current.chunk_zero_sum +\n            zero_sum_of(current.right);\n\
    \    }\n\n    void rebuild_chunk(int node) {\n        M1UNE_DWM_SUM_PROFILE_ADD(full_chunk_rebuilds,\
    \ 1);\n        Node& current = _nodes[node];\n        current.group_total_sums.fill(Sum{});\n\
    \        current.group_zero_sums.fill(Sum{});\n        current.chunk_total_sum\
    \ = Sum{};\n        current.chunk_zero_sum = Sum{};\n        current.chunk_ones\
    \ = 0;\n        for (int position = 0; position < current.length; position++)\
    \ {\n            int group = position / GroupSize;\n            const Sum& weight\
    \ = current.weights[position];\n            current.group_total_sums[group] =\n\
    \                current.group_total_sums[group] + weight;\n            current.chunk_total_sum\
    \ = current.chunk_total_sum + weight;\n            if (local_bit(node, position))\
    \ {\n                current.chunk_ones++;\n            } else {\n           \
    \     current.group_zero_sums[group] =\n                    current.group_zero_sums[group]\
    \ + weight;\n                current.chunk_zero_sum = current.chunk_zero_sum +\
    \ weight;\n            }\n        }\n        update(node);\n    }\n\n    PrefixStats\
    \ local_prefix_stats(int node, int right) const {\n        PrefixStats result;\n\
    \        result.ones = local_rank1(node, right);\n        int full_groups = right\
    \ / GroupSize;\n        for (int group = 0; group < full_groups; group++) {\n\
    \            result.total_sum =\n                result.total_sum + _nodes[node].group_total_sums[group];\n\
    \            result.zero_sum =\n                result.zero_sum + _nodes[node].group_zero_sums[group];\n\
    \        }\n        for (int position = full_groups * GroupSize; position < right;\n\
    \             position++) {\n            const Sum& weight = _nodes[node].weights[position];\n\
    \            result.total_sum = result.total_sum + weight;\n            if (!local_bit(node,\
    \ position)) {\n                result.zero_sum = result.zero_sum + weight;\n\
    \            }\n        }\n        return result;\n    }\n\n    static void add_stats(PrefixStats&\
    \ destination, const PrefixStats& value) {\n        destination.ones += value.ones;\n\
    \        destination.total_sum = destination.total_sum + value.total_sum;\n  \
    \      destination.zero_sum = destination.zero_sum + value.zero_sum;\n    }\n\n\
    \    PrefixStats subtree_stats(int node) const {\n        return PrefixStats{\n\
    \            ones_of(node),\n            total_sum_of(node),\n            zero_sum_of(node)\n\
    \        };\n    }\n\n    void local_insert(int node, int position, bool bit,\
    \ const Sum& weight) {\n        Node& current = _nodes[node];\n        assert(0\
    \ <= position && position <= current.length);\n        assert(current.length <\
    \ ChunkCapacity);\n        M1UNE_DWM_SUM_PROFILE_ADD(\n            local_element_moves,\n\
    \            int(current.length) - position\n        );\n        for (int i =\
    \ current.length; position < i; i--) {\n            current.weights[i] = current.weights[i\
    \ - 1];\n            local_set_bit(node, i, local_bit(node, i - 1));\n       \
    \ }\n        current.weights[position] = weight;\n        local_set_bit(node,\
    \ position, bit);\n        current.length++;\n        rebuild_chunk(node);\n \
    \   }\n\n    EraseRankResult local_erase(int node, int position) {\n        Node&\
    \ current = _nodes[node];\n        assert(0 <= position && position < current.length);\n\
    \        M1UNE_DWM_SUM_PROFILE_ADD(\n            local_element_moves,\n      \
    \      int(current.length) - position - 1\n        );\n        EraseRankResult\
    \ result{\n            local_bit(node, position),\n            current.weights[position],\n\
    \            0\n        };\n        for (int i = position; i + 1 < current.length;\
    \ i++) {\n            current.weights[i] = current.weights[i + 1];\n         \
    \   local_set_bit(node, i, local_bit(node, i + 1));\n        }\n        current.length--;\n\
    \        current.weights[current.length] = Sum{};\n        local_set_bit(node,\
    \ current.length, false);\n        rebuild_chunk(node);\n        return result;\n\
    \    }\n\n    Sum local_set_weight(int node, int position, const Sum& weight)\
    \ {\n        Node& current = _nodes[node];\n        Sum old_weight = current.weights[position];\n\
    \        Sum delta = weight - old_weight;\n        current.weights[position] =\
    \ weight;\n        int group = position / GroupSize;\n        current.group_total_sums[group]\
    \ =\n            current.group_total_sums[group] + delta;\n        current.chunk_total_sum\
    \ = current.chunk_total_sum + delta;\n        if (!local_bit(node, position))\
    \ {\n            current.group_zero_sums[group] =\n                current.group_zero_sums[group]\
    \ + delta;\n            current.chunk_zero_sum = current.chunk_zero_sum + delta;\n\
    \        }\n        update(node);\n        return old_weight;\n    }\n\n    Sum\
    \ local_add_weight(int node, int position, const Sum& delta) {\n        return\
    \ local_set_weight(\n            node,\n            position,\n            _nodes[node].weights[position]\
    \ + delta\n        );\n    }\n\n    int new_node() {\n        int node;\n    \
    \    if (_free_nodes.empty()) {\n            node = int(_nodes.size());\n    \
    \        _nodes.emplace_back();\n        } else {\n            node = _free_nodes.back();\n\
    \            _free_nodes.pop_back();\n            _nodes[node] = Node();\n   \
    \     }\n        _nodes[node].priority = next_priority();\n        return node;\n\
    \    }\n\n    template <std::size_t Capacity>\n    void assign_from_values(\n\
    \        int node,\n        const std::array<std::uint8_t, Capacity>& bits,\n\
    \        const std::array<Sum, Capacity>& weights,\n        int first,\n     \
    \   int last\n    ) {\n        Node& current = _nodes[node];\n        current.bits.fill(0);\n\
    \        current.weights.fill(Sum{});\n        current.length = std::uint16_t(last\
    \ - first);\n        for (int position = first; position < last; position++) {\n\
    \            int destination = position - first;\n            current.weights[destination]\
    \ = weights[position];\n            if (bits[position]) local_set_bit(node, destination,\
    \ true);\n        }\n        rebuild_chunk(node);\n    }\n\n    void assign_from_values(\n\
    \        int node,\n        const std::vector<std::uint8_t>& bits,\n        const\
    \ std::vector<Sum>& weights,\n        int first,\n        int last\n    ) {\n\
    \        Node& current = _nodes[node];\n        current.bits.fill(0);\n      \
    \  current.weights.fill(Sum{});\n        current.length = std::uint16_t(last -\
    \ first);\n        for (int position = first; position < last; position++) {\n\
    \            int destination = position - first;\n            current.weights[destination]\
    \ = weights[position];\n            if (bits[position]) local_set_bit(node, destination,\
    \ true);\n        }\n        rebuild_chunk(node);\n    }\n\n    int new_node(\n\
    \        const std::vector<std::uint8_t>& bits,\n        const std::vector<Sum>&\
    \ weights,\n        int first,\n        int last\n    ) {\n        int node =\
    \ new_node();\n        assign_from_values(node, bits, weights, first, last);\n\
    \        return node;\n    }\n\n    void recycle_node(int node) {\n        assert(node\
    \ != 0);\n        _nodes[node] = Node();\n        _free_nodes.push_back(node);\n\
    \    }\n\n    int merge(int left, int right) {\n        if (left == 0 || right\
    \ == 0) return left != 0 ? left : right;\n        if (_nodes[left].priority >\
    \ _nodes[right].priority) {\n            _nodes[left].right = merge(_nodes[left].right,\
    \ right);\n            update(left);\n            return left;\n        }\n  \
    \      _nodes[right].left = merge(left, _nodes[right].left);\n        update(right);\n\
    \        return right;\n    }\n\n    int rotate_right(int tree) {\n        int\
    \ result = _nodes[tree].left;\n        _nodes[tree].left = _nodes[result].right;\n\
    \        _nodes[result].right = tree;\n        update(tree);\n        update(result);\n\
    \        return result;\n    }\n\n    int rotate_left(int tree) {\n        int\
    \ result = _nodes[tree].right;\n        _nodes[tree].right = _nodes[result].left;\n\
    \        _nodes[result].left = tree;\n        update(tree);\n        update(result);\n\
    \        return result;\n    }\n\n    int extract_leftmost(int tree, int& extracted)\
    \ {\n        if (_nodes[tree].left == 0) {\n            extracted = tree;\n  \
    \          int result = _nodes[tree].right;\n            _nodes[tree].right =\
    \ 0;\n            update(tree);\n            return result;\n        }\n     \
    \   _nodes[tree].left = extract_leftmost(_nodes[tree].left, extracted);\n    \
    \    update(tree);\n        return tree;\n    }\n\n    int extract_rightmost(int\
    \ tree, int& extracted) {\n        if (_nodes[tree].right == 0) {\n          \
    \  extracted = tree;\n            int result = _nodes[tree].left;\n          \
    \  _nodes[tree].left = 0;\n            update(tree);\n            return result;\n\
    \        }\n        _nodes[tree].right = extract_rightmost(_nodes[tree].right,\
    \ extracted);\n        update(tree);\n        return tree;\n    }\n\n    int rebalance(int\
    \ node) {\n        if (_nodes[node].length >= minimum_chunk_size) return node;\n\
    \n        if (_nodes[node].right != 0) {\n            int neighbor = 0;\n    \
    \        _nodes[node].right =\n                extract_leftmost(_nodes[node].right,\
    \ neighbor);\n            int node_length = _nodes[node].length;\n           \
    \ int neighbor_length = _nodes[neighbor].length;\n            int total = node_length\
    \ + neighbor_length;\n            std::array<std::uint8_t, ChunkCapacity * 2>\
    \ bits{};\n            std::array<Sum, ChunkCapacity * 2> weights{};\n       \
    \     for (int i = 0; i < node_length; i++) {\n                bits[i] = local_bit(node,\
    \ i);\n                weights[i] = _nodes[node].weights[i];\n            }\n\
    \            for (int i = 0; i < neighbor_length; i++) {\n                bits[node_length\
    \ + i] = local_bit(neighbor, i);\n                weights[node_length + i] = _nodes[neighbor].weights[i];\n\
    \            }\n            if (total <= ChunkCapacity) {\n                M1UNE_DWM_SUM_PROFILE_ADD(chunk_merges,\
    \ 1);\n                assign_from_values(node, bits, weights, 0, total);\n  \
    \              recycle_node(neighbor);\n            } else {\n               \
    \ int left_length = total / 2;\n                assign_from_values(node, bits,\
    \ weights, 0, left_length);\n                assign_from_values(\n           \
    \         neighbor,\n                    bits,\n                    weights,\n\
    \                    left_length,\n                    total\n               \
    \ );\n                _nodes[node].right = merge(neighbor, _nodes[node].right);\n\
    \            }\n            update(node);\n            return node;\n        }\n\
    \n        if (_nodes[node].left != 0) {\n            int neighbor = 0;\n     \
    \       _nodes[node].left =\n                extract_rightmost(_nodes[node].left,\
    \ neighbor);\n            int neighbor_length = _nodes[neighbor].length;\n   \
    \         int node_length = _nodes[node].length;\n            int total = neighbor_length\
    \ + node_length;\n            std::array<std::uint8_t, ChunkCapacity * 2> bits{};\n\
    \            std::array<Sum, ChunkCapacity * 2> weights{};\n            for (int\
    \ i = 0; i < neighbor_length; i++) {\n                bits[i] = local_bit(neighbor,\
    \ i);\n                weights[i] = _nodes[neighbor].weights[i];\n           \
    \ }\n            for (int i = 0; i < node_length; i++) {\n                bits[neighbor_length\
    \ + i] = local_bit(node, i);\n                weights[neighbor_length + i] = _nodes[node].weights[i];\n\
    \            }\n            if (total <= ChunkCapacity) {\n                M1UNE_DWM_SUM_PROFILE_ADD(chunk_merges,\
    \ 1);\n                assign_from_values(node, bits, weights, 0, total);\n  \
    \              recycle_node(neighbor);\n            } else {\n               \
    \ int left_length = total / 2;\n                assign_from_values(\n        \
    \            neighbor,\n                    bits,\n                    weights,\n\
    \                    0,\n                    left_length\n                );\n\
    \                assign_from_values(\n                    node,\n            \
    \        bits,\n                    weights,\n                    left_length,\n\
    \                    total\n                );\n                _nodes[node].left\
    \ = merge(_nodes[node].left, neighbor);\n            }\n            update(node);\n\
    \        }\n        return node;\n    }\n\n    int insert_impl(\n        int tree,\n\
    \        int position,\n        bool bit,\n        const Sum& weight,\n      \
    \  int& ones_before\n    ) {\n        if (tree == 0) {\n            int node =\
    \ new_node();\n            local_insert(node, 0, bit, weight);\n            return\
    \ node;\n        }\n\n        int left_size = size_of(_nodes[tree].left);\n  \
    \      int length = _nodes[tree].length;\n        if (position < left_size) {\n\
    \            _nodes[tree].left = insert_impl(\n                _nodes[tree].left,\n\
    \                position,\n                bit,\n                weight,\n  \
    \              ones_before\n            );\n            update(tree);\n      \
    \      if (_nodes[_nodes[tree].left].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_right(tree);\n            }\n            return\
    \ tree;\n        }\n        if (position > left_size + length) {\n           \
    \ ones_before +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = insert_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                bit,\n      \
    \          weight,\n                ones_before\n            );\n            update(tree);\n\
    \            if (_nodes[_nodes[tree].right].priority >\n                _nodes[tree].priority)\
    \ {\n                tree = rotate_left(tree);\n            }\n            return\
    \ tree;\n        }\n\n        int local_position = position - left_size;\n   \
    \     ones_before += ones_of(_nodes[tree].left) +\n                       local_rank1(tree,\
    \ local_position);\n        if (length < ChunkCapacity) {\n            local_insert(tree,\
    \ local_position, bit, weight);\n            return tree;\n        }\n\n     \
    \   std::array<std::uint8_t, ChunkCapacity> bits{};\n        std::array<Sum, ChunkCapacity>\
    \ weights{};\n        M1UNE_DWM_SUM_PROFILE_ADD(chunk_splits, 1);\n        for\
    \ (int i = 0; i < ChunkCapacity; i++) {\n            bits[i] = local_bit(tree,\
    \ i);\n            weights[i] = _nodes[tree].weights[i];\n        }\n        int\
    \ right_chunk = new_node();\n        int middle = ChunkCapacity / 2;\n       \
    \ assign_from_values(tree, bits, weights, 0, middle);\n        assign_from_values(\n\
    \            right_chunk,\n            bits,\n            weights,\n         \
    \   middle,\n            ChunkCapacity\n        );\n        if (local_position\
    \ <= middle) {\n            local_insert(tree, local_position, bit, weight);\n\
    \        } else {\n            local_insert(\n                right_chunk,\n \
    \               local_position - middle,\n                bit,\n             \
    \   weight\n            );\n        }\n\n        int old_right = _nodes[tree].right;\n\
    \        _nodes[tree].right = 0;\n        update(tree);\n        return merge(merge(tree,\
    \ right_chunk), old_right);\n    }\n\n    int erase_impl(\n        int tree,\n\
    \        int position,\n        EraseRankResult& result\n    ) {\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int length = _nodes[tree].length;\n\
    \        if (position < left_size) {\n            _nodes[tree].left = erase_impl(\n\
    \                _nodes[tree].left,\n                position,\n             \
    \   result\n            );\n            update(tree);\n            return tree;\n\
    \        }\n        if (position >= left_size + length) {\n            result.ones_before\
    \ +=\n                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n\
    \            _nodes[tree].right = erase_impl(\n                _nodes[tree].right,\n\
    \                position - left_size - length,\n                result\n    \
    \        );\n            update(tree);\n            return tree;\n        }\n\n\
    \        int local_position = position - left_size;\n        result.ones_before\
    \ += ones_of(_nodes[tree].left) +\n                              local_rank1(tree,\
    \ local_position);\n        EraseRankResult local = local_erase(tree, local_position);\n\
    \        result.bit = local.bit;\n        result.weight = local.weight;\n    \
    \    if (_nodes[tree].length == 0) {\n            int merged = merge(_nodes[tree].left,\
    \ _nodes[tree].right);\n            recycle_node(tree);\n            return merged;\n\
    \        }\n        return rebalance(tree);\n    }\n\n    template <bool Add>\n\
    \    void change_weight_impl(\n        int tree,\n        int position,\n    \
    \    const Sum& value,\n        AccessRankResult& result\n    ) {\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        if (position < left_size) {\n\
    \            change_weight_impl<Add>(\n                _nodes[tree].left,\n  \
    \              position,\n                value,\n                result\n   \
    \         );\n        } else if (position < left_size + _nodes[tree].length) {\n\
    \            int local_position = position - left_size;\n            result.ones_before\
    \ += ones_of(_nodes[tree].left) +\n                                  local_rank1(tree,\
    \ local_position);\n            result.bit = local_bit(tree, local_position);\n\
    \            if constexpr (Add) {\n                result.weight = local_add_weight(tree,\
    \ local_position, value);\n            } else {\n                result.weight\
    \ = local_set_weight(tree, local_position, value);\n            }\n          \
    \  return;\n        } else {\n            result.ones_before +=\n            \
    \    ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;\n            change_weight_impl<Add>(\n\
    \                _nodes[tree].right,\n                position - left_size - _nodes[tree].length,\n\
    \                value,\n                result\n            );\n        }\n \
    \       update(tree);\n    }\n\n    PrefixStats prefix_stats_impl(int tree, int\
    \ right) const {\n        PrefixStats result;\n        while (tree != 0 && right\
    \ != 0) {\n            int left_size = size_of(_nodes[tree].left);\n         \
    \   if (right <= left_size) {\n                tree = _nodes[tree].left;\n   \
    \             continue;\n            }\n            add_stats(result, subtree_stats(_nodes[tree].left));\n\
    \            right -= left_size;\n            int take = std::min(right, int(_nodes[tree].length));\n\
    \            add_stats(result, local_prefix_stats(tree, take));\n            right\
    \ -= take;\n            if (right == 0) break;\n            tree = _nodes[tree].right;\n\
    \        }\n        return result;\n    }\n\n    PrefixStatsPair prefix_stats_pair_impl(\n\
    \        int tree,\n        int left,\n        int right\n    ) const {\n    \
    \    if (left == right) {\n            PrefixStats value = prefix_stats_impl(tree,\
    \ left);\n            return PrefixStatsPair{value, value};\n        }\n     \
    \   if (tree == 0 || right == 0) return PrefixStatsPair{};\n\n        int left_size\
    \ = size_of(_nodes[tree].left);\n        int chunk_end = left_size + _nodes[tree].length;\n\
    \        if (right <= left_size) {\n            return prefix_stats_pair_impl(\n\
    \                _nodes[tree].left,\n                left,\n                right\n\
    \            );\n        }\n        if (chunk_end <= left) {\n            PrefixStats\
    \ base = subtree_stats(_nodes[tree].left);\n            add_stats(base, local_prefix_stats(tree,\
    \ _nodes[tree].length));\n            PrefixStatsPair result = prefix_stats_pair_impl(\n\
    \                _nodes[tree].right,\n                left - chunk_end,\n    \
    \            right - chunk_end\n            );\n            add_stats(result.left,\
    \ base);\n            add_stats(result.right, base);\n            return result;\n\
    \        }\n\n        PrefixStats left_stats;\n        if (left <= left_size)\
    \ {\n            left_stats = prefix_stats_impl(_nodes[tree].left, left);\n  \
    \      } else {\n            left_stats = subtree_stats(_nodes[tree].left);\n\
    \            add_stats(\n                left_stats,\n                local_prefix_stats(tree,\
    \ left - left_size)\n            );\n        }\n\n        PrefixStats right_stats\
    \ = subtree_stats(_nodes[tree].left);\n        if (right <= chunk_end) {\n   \
    \         add_stats(\n                right_stats,\n                local_prefix_stats(tree,\
    \ right - left_size)\n            );\n        } else {\n            add_stats(\n\
    \                right_stats,\n                local_prefix_stats(tree, _nodes[tree].length)\n\
    \            );\n            add_stats(\n                right_stats,\n      \
    \          prefix_stats_impl(_nodes[tree].right, right - chunk_end)\n        \
    \    );\n        }\n        return PrefixStatsPair{left_stats, right_stats};\n\
    \    }\n\n    template <class Predicate>\n    int consume_chunk_prefix(\n    \
    \    int node,\n        int left,\n        int right,\n        Sum& sum,\n   \
    \     Predicate& predicate\n    ) const {\n        int position = left;\n    \
    \    while (position < right) {\n            if (position % GroupSize == 0 &&\n\
    \                position + GroupSize <= right) {\n                int group =\
    \ position / GroupSize;\n                Sum candidate =\n                   \
    \ sum + _nodes[node].group_total_sums[group];\n                if (predicate(candidate))\
    \ {\n                    sum = candidate;\n                    position += GroupSize;\n\
    \                    continue;\n                }\n            }\n           \
    \ Sum candidate = sum + _nodes[node].weights[position];\n            if (!predicate(candidate))\
    \ break;\n            sum = candidate;\n            position++;\n        }\n \
    \       return position - left;\n    }\n\n    template <class Predicate>\n   \
    \ int consume_chunk_suffix(\n        int node,\n        int left,\n        int\
    \ right,\n        Sum& sum,\n        Predicate& predicate\n    ) const {\n   \
    \     int position = right;\n        while (left < position) {\n            if\
    \ (position % GroupSize == 0 &&\n                left <= position - GroupSize)\
    \ {\n                int group = position / GroupSize - 1;\n                Sum\
    \ candidate =\n                    sum + _nodes[node].group_total_sums[group];\n\
    \                if (predicate(candidate)) {\n                    sum = candidate;\n\
    \                    position -= GroupSize;\n                    continue;\n \
    \               }\n            }\n            Sum candidate = sum + _nodes[node].weights[position\
    \ - 1];\n            if (!predicate(candidate)) break;\n            sum = candidate;\n\
    \            position--;\n        }\n        return right - position;\n    }\n\
    \n    template <class Predicate>\n    int max_prefix_impl(\n        int tree,\n\
    \        int left,\n        int right,\n        Sum& sum,\n        Predicate&\
    \ predicate\n    ) const {\n        assert(tree != 0);\n        assert(0 <= left\
    \ && left < right && right <= size_of(tree));\n        if (left == 0 && right\
    \ == size_of(tree)) {\n            Sum candidate = sum + total_sum_of(tree);\n\
    \            if (predicate(candidate)) {\n                sum = candidate;\n \
    \               return size_of(tree);\n            }\n        }\n\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int chunk_end = left_size +\
    \ _nodes[tree].length;\n        int count = 0;\n        if (left < left_size)\
    \ {\n            int subtree_right = std::min(right, left_size);\n           \
    \ int consumed = max_prefix_impl(\n                _nodes[tree].left,\n      \
    \          left,\n                subtree_right,\n                sum,\n     \
    \           predicate\n            );\n            count += consumed;\n      \
    \      if (consumed < subtree_right - left) return count;\n        }\n\n     \
    \   int chunk_left = std::max(left, left_size);\n        int chunk_right = std::min(right,\
    \ chunk_end);\n        if (chunk_left < chunk_right) {\n            int consumed\
    \ = consume_chunk_prefix(\n                tree,\n                chunk_left -\
    \ left_size,\n                chunk_right - left_size,\n                sum,\n\
    \                predicate\n            );\n            count += consumed;\n \
    \           if (consumed < chunk_right - chunk_left) return count;\n        }\n\
    \n        if (chunk_end < right) {\n            int subtree_left = std::max(left,\
    \ chunk_end) - chunk_end;\n            int subtree_right = right - chunk_end;\n\
    \            count += max_prefix_impl(\n                _nodes[tree].right,\n\
    \                subtree_left,\n                subtree_right,\n             \
    \   sum,\n                predicate\n            );\n        }\n        return\
    \ count;\n    }\n\n    template <class Predicate>\n    int max_suffix_impl(\n\
    \        int tree,\n        int left,\n        int right,\n        Sum& sum,\n\
    \        Predicate& predicate\n    ) const {\n        assert(tree != 0);\n   \
    \     assert(0 <= left && left < right && right <= size_of(tree));\n        if\
    \ (left == 0 && right == size_of(tree)) {\n            Sum candidate = sum + total_sum_of(tree);\n\
    \            if (predicate(candidate)) {\n                sum = candidate;\n \
    \               return size_of(tree);\n            }\n        }\n\n        int\
    \ left_size = size_of(_nodes[tree].left);\n        int chunk_end = left_size +\
    \ _nodes[tree].length;\n        int count = 0;\n        if (chunk_end < right)\
    \ {\n            int subtree_left = std::max(left, chunk_end) - chunk_end;\n \
    \           int subtree_right = right - chunk_end;\n            int consumed =\
    \ max_suffix_impl(\n                _nodes[tree].right,\n                subtree_left,\n\
    \                subtree_right,\n                sum,\n                predicate\n\
    \            );\n            count += consumed;\n            if (consumed < subtree_right\
    \ - subtree_left) return count;\n        }\n\n        int chunk_left = std::max(left,\
    \ left_size);\n        int chunk_right = std::min(right, chunk_end);\n       \
    \ if (chunk_left < chunk_right) {\n            int consumed = consume_chunk_suffix(\n\
    \                tree,\n                chunk_left - left_size,\n            \
    \    chunk_right - left_size,\n                sum,\n                predicate\n\
    \            );\n            count += consumed;\n            if (consumed < chunk_right\
    \ - chunk_left) return count;\n        }\n\n        if (left < left_size) {\n\
    \            int subtree_right = std::min(right, left_size);\n            count\
    \ += max_suffix_impl(\n                _nodes[tree].left,\n                left,\n\
    \                subtree_right,\n                sum,\n                predicate\n\
    \            );\n        }\n        return count;\n    }\n\n    void update_subtree(int\
    \ tree) {\n        if (tree == 0) return;\n        update_subtree(_nodes[tree].left);\n\
    \        update_subtree(_nodes[tree].right);\n        update(tree);\n    }\n\n\
    \    void build(\n        const std::vector<std::uint8_t>& bits,\n        const\
    \ std::vector<Sum>& weights\n    ) {\n        assert(bits.size() == weights.size());\n\
    \        _nodes.clear();\n        _nodes.emplace_back();\n        _free_nodes.clear();\n\
    \        _root = 0;\n        _nodes.reserve(weights.size() / minimum_chunk_size\
    \ + 2);\n\n        std::vector<int> stack;\n        for (int first = 0; first\
    \ < int(weights.size());\n             first += ChunkCapacity) {\n           \
    \ int last =\n                std::min(first + ChunkCapacity, int(weights.size()));\n\
    \            int node = new_node(bits, weights, first, last);\n            int\
    \ left = 0;\n            while (!stack.empty() &&\n                   _nodes[stack.back()].priority\
    \ < _nodes[node].priority) {\n                left = stack.back();\n         \
    \       stack.pop_back();\n            }\n            _nodes[node].left = left;\n\
    \            if (!stack.empty()) _nodes[stack.back()].right = node;\n        \
    \    stack.push_back(node);\n        }\n        if (!stack.empty()) _root = stack.front();\n\
    \        update_subtree(_root);\n    }\n\n   public:\n    DynamicWeightedRankSequence()\
    \ : _nodes(1) {}\n\n    DynamicWeightedRankSequence(\n        const std::vector<std::uint8_t>&\
    \ bits,\n        const std::vector<Sum>& weights,\n        std::uint32_t seed\
    \ = 1\n    ) : _random_state(seed == 0 ? 1 : seed) {\n        build(bits, weights);\n\
    \    }\n\n    explicit DynamicWeightedRankSequence(\n        const std::vector<Sum>&\
    \ weights,\n        std::uint32_t seed = 1\n    ) : _random_state(seed == 0 ?\
    \ 1 : seed) {\n        build(std::vector<std::uint8_t>(weights.size()), weights);\n\
    \    }\n\n    int size() const {\n        return size_of(_root);\n    }\n\n  \
    \  AccessRankResult access_with_rank(int position) const {\n        assert(0 <=\
    \ position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        int tree = _root;\n        int ones_before = 0;\n        while\
    \ (tree != 0) {\n            int left_size = size_of(_nodes[tree].left);\n   \
    \         if (position < left_size) {\n                tree = _nodes[tree].left;\n\
    \            } else if (position < left_size + _nodes[tree].length) {\n      \
    \          int local_position = position - left_size;\n                ones_before\
    \ += ones_of(_nodes[tree].left) +\n                               local_rank1(tree,\
    \ local_position);\n                return AccessRankResult{\n               \
    \     local_bit(tree, local_position),\n                    _nodes[tree].weights[local_position],\n\
    \                    ones_before\n                };\n            } else {\n \
    \               ones_before +=\n                    ones_of(_nodes[tree].left)\
    \ + _nodes[tree].chunk_ones;\n                position -= left_size + _nodes[tree].length;\n\
    \                tree = _nodes[tree].right;\n            }\n        }\n      \
    \  assert(false);\n        return AccessRankResult{false, Sum{}, 0};\n    }\n\n\
    \    PrefixStats prefix_stats(int right) const {\n        assert(0 <= right &&\
    \ right <= size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        return prefix_stats_impl(_root, right);\n    }\n\n    PrefixStatsPair\
    \ prefix_stats_pair(int left, int right) const {\n        assert(0 <= left &&\
    \ left <= right && right <= size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        return prefix_stats_pair_impl(_root, left, right);\n    }\n\n \
    \   Sum range_sum(int left, int right) const {\n        PrefixStatsPair stats\
    \ = prefix_stats_pair(left, right);\n        return stats.right.total_sum - stats.left.total_sum;\n\
    \    }\n\n    int insert_with_rank(\n        int position,\n        bool bit,\n\
    \        const Sum& weight\n    ) {\n        assert(0 <= position && position\
    \ <= size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);\n\
    \        int ones_before = 0;\n        _root = insert_impl(\n            _root,\n\
    \            position,\n            bit,\n            weight,\n            ones_before\n\
    \        );\n        return ones_before;\n    }\n\n    EraseRankResult erase_with_rank(int\
    \ position) {\n        assert(0 <= position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        EraseRankResult result{false, Sum{}, 0};\n        _root = erase_impl(_root,\
    \ position, result);\n        return result;\n    }\n\n    AccessRankResult set_weight_with_rank(\n\
    \        int position,\n        const Sum& weight\n    ) {\n        assert(0 <=\
    \ position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        AccessRankResult result{false, Sum{}, 0};\n        change_weight_impl<false>(_root,\
    \ position, weight, result);\n        return result;\n    }\n\n    AccessRankResult\
    \ add_weight_with_rank(\n        int position,\n        const Sum& delta\n   \
    \ ) {\n        assert(0 <= position && position < size());\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals,\
    \ 1);\n        AccessRankResult result{false, Sum{}, 0};\n        change_weight_impl<true>(_root,\
    \ position, delta, result);\n        return result;\n    }\n\n    template <class\
    \ Predicate>\n    int max_prefix(\n        int left,\n        int right,\n   \
    \     Sum& sum,\n        Predicate& predicate\n    ) const {\n        assert(0\
    \ <= left && left <= right && right <= size());\n        if (left == right) return\
    \ 0;\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);\n        return\
    \ max_prefix_impl(_root, left, right, sum, predicate);\n    }\n\n    template\
    \ <class Predicate>\n    int max_suffix(\n        int left,\n        int right,\n\
    \        Sum& sum,\n        Predicate& predicate\n    ) const {\n        assert(0\
    \ <= left && left <= right && right <= size());\n        if (left == right) return\
    \ 0;\n        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);\n        return\
    \ max_suffix_impl(_root, left, right, sum, predicate);\n    }\n};\n\n}  // namespace\
    \ dynamic_wavelet_matrix_sum_detail\n\n#undef M1UNE_DWM_SUM_PROFILE_ADD\n\n//\
    \ A dynamic wavelet matrix with additive weights.\n// By default, each value is\
    \ also used as its weight.\ntemplate <\n    std::integral T,\n    typename Sum\
    \ = T,\n    int BitWidth = std::numeric_limits<std::make_unsigned_t<T>>::digits\n\
    >\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nclass DynamicWaveletMatrixSum\
    \ {\n   public:\n    using value_type = T;\n    using sum_type = Sum;\n    using\
    \ unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n    static constexpr\
    \ int full_bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static_assert(1 <= BitWidth && BitWidth <= full_bit_width);\n    static_assert(\n\
    \        BitWidth == full_bit_width || std::unsigned_integral<T>,\n        \"\
    reduced-width keys must use an unsigned type\"\n    );\n\n    static constexpr\
    \ unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (BitWidth - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    static constexpr\
    \ unsigned_type reduced_limit = [] {\n        if constexpr (BitWidth < full_bit_width)\
    \ {\n            return unsigned_type(1) << BitWidth;\n        } else {\n    \
    \        return unsigned_type(0);\n        }\n    }();\n\n    using Level = dynamic_wavelet_matrix_sum_detail::\n\
    \        DynamicWeightedRankSequence<Sum>;\n\n    struct ErasedElement {\n   \
    \     unsigned_type key;\n        Sum weight;\n    };\n\n    int _size = 0;\n\
    \    std::vector<Level> _levels;\n    Level _final_weights;\n    std::array<int,\
    \ BitWidth> _zero_count{};\n\n    static bool key_fits(T value) {\n        if\
    \ constexpr (BitWidth < full_bit_width) {\n            return static_cast<unsigned_type>(value)\
    \ < reduced_limit;\n        } else {\n            return true;\n        }\n  \
    \  }\n\n    static unsigned_type encode_unchecked(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static unsigned_type\
    \ encode_key(T value) {\n        assert(key_fits(value));\n        return encode_unchecked(value);\n\
    \    }\n\n    static T decode(unsigned_type key) {\n        unsigned_type bits\
    \ = key ^ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n     \
    \       return std::bit_cast<T>(bits);\n        } else {\n            return bits;\n\
    \        }\n    }\n\n    static bool bit(unsigned_type key, int level) {\n   \
    \     return (key >> (BitWidth - 1 - level)) & unsigned_type(1);\n    }\n\n  \
    \  static Sum range_total(const typename Level::PrefixStatsPair& stats) {\n  \
    \      return stats.right.total_sum - stats.left.total_sum;\n    }\n\n    static\
    \ Sum range_zero(const typename Level::PrefixStatsPair& stats) {\n        return\
    \ stats.right.zero_sum - stats.left.zero_sum;\n    }\n\n    void build(const std::vector<T>&\
    \ values, const std::vector<Sum>& weights) {\n        assert(values.size() ==\
    \ weights.size());\n        _size = int(values.size());\n\n        std::vector<unsigned_type>\
    \ current_keys(_size);\n        std::vector<unsigned_type> next_keys(_size);\n\
    \        std::vector<Sum> current_weights(weights);\n        std::vector<Sum>\
    \ next_weights(_size);\n        for (int i = 0; i < _size; i++) {\n          \
    \  current_keys[i] = encode_key(values[i]);\n        }\n\n        _levels.clear();\n\
    \        _levels.reserve(BitWidth);\n        for (int level = 0; level < BitWidth;\
    \ level++) {\n            std::vector<std::uint8_t> bits(_size);\n           \
    \ int zeros = 0;\n            for (int i = 0; i < _size; i++) {\n            \
    \    bits[i] = bit(current_keys[i], level);\n                zeros += !bits[i];\n\
    \            }\n            _zero_count[level] = zeros;\n            _levels.emplace_back(\n\
    \                bits,\n                current_weights,\n                std::uint32_t(0x9e3779b9U\
    \ + level * 0x85ebca6bU)\n            );\n\n            int zero_position = 0;\n\
    \            int one_position = zeros;\n            for (int i = 0; i < _size;\
    \ i++) {\n                int next_position = bits[i] ? one_position++ : zero_position++;\n\
    \                next_keys[next_position] = current_keys[i];\n               \
    \ next_weights[next_position] = current_weights[i];\n            }\n         \
    \   current_keys.swap(next_keys);\n            current_weights.swap(next_weights);\n\
    \        }\n        _final_weights = Level(current_weights, 0xb7e15162U);\n  \
    \  }\n\n    void insert_encoded(int position, unsigned_type key, const Sum& weight)\
    \ {\n        for (int level = 0; level < BitWidth; level++) {\n            bool\
    \ one = bit(key, level);\n            int ones_before =\n                _levels[level].insert_with_rank(position,\
    \ one, weight);\n            int next_position;\n            if (one) {\n    \
    \            next_position = _zero_count[level] + ones_before;\n            }\
    \ else {\n                next_position = position - ones_before;\n          \
    \      _zero_count[level]++;\n            }\n            position = next_position;\n\
    \        }\n        _final_weights.insert_with_rank(position, false, weight);\n\
    \        _size++;\n    }\n\n    ErasedElement erase_encoded(int position) {\n\
    \        unsigned_type key = 0;\n        Sum weight{};\n        for (int level\
    \ = 0; level < BitWidth; level++) {\n            auto erased = _levels[level].erase_with_rank(position);\n\
    \            if (level == 0) weight = erased.weight;\n            int next_position;\n\
    \            if (erased.bit) {\n                key |= unsigned_type(1) << (BitWidth\
    \ - 1 - level);\n                next_position = _zero_count[level] + erased.ones_before;\n\
    \            } else {\n                next_position = position - erased.ones_before;\n\
    \                _zero_count[level]--;\n            }\n            position =\
    \ next_position;\n        }\n        _final_weights.erase_with_rank(position);\n\
    \        _size--;\n        return ErasedElement{key, weight};\n    }\n\n    int\
    \ count_less_encoded(int left, int right, unsigned_type upper) const {\n     \
    \   int result = 0;\n        for (int level = 0; level < BitWidth; level++) {\n\
    \            auto stats = _levels[level].prefix_stats_pair(left, right);\n   \
    \         int left_ones = stats.left.ones;\n            int right_ones = stats.right.ones;\n\
    \            if (bit(upper, level)) {\n                result += (right - left)\
    \ - (right_ones - left_ones);\n                left = _zero_count[level] + left_ones;\n\
    \                right = _zero_count[level] + right_ones;\n            } else\
    \ {\n                left -= left_ones;\n                right -= right_ones;\n\
    \            }\n        }\n        return result;\n    }\n\n    int count_less(int\
    \ left, int right, T upper) const {\n        if constexpr (BitWidth < full_bit_width)\
    \ {\n            if (!key_fits(upper)) return right - left;\n        }\n     \
    \   return count_less_encoded(left, right, encode_unchecked(upper));\n    }\n\n\
    \    Sum sum_less_encoded(int left, int right, unsigned_type upper) const {\n\
    \        Sum result{};\n        for (int level = 0; level < BitWidth; level++)\
    \ {\n            auto stats = _levels[level].prefix_stats_pair(left, right);\n\
    \            int left_ones = stats.left.ones;\n            int right_ones = stats.right.ones;\n\
    \            if (bit(upper, level)) {\n                result = result + range_zero(stats);\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            } else {\n                left\
    \ -= left_ones;\n                right -= right_ones;\n            }\n       \
    \ }\n        return result;\n    }\n\n    Sum sum_less(int left, int right, T\
    \ upper) const {\n        if constexpr (BitWidth < full_bit_width) {\n       \
    \     if (!key_fits(upper)) return range_sum(left, right);\n        }\n      \
    \  return sum_less_encoded(left, right, encode_unchecked(upper));\n    }\n\n \
    \  public:\n    DynamicWaveletMatrixSum() : _levels(BitWidth) {}\n\n    explicit\
    \ DynamicWaveletMatrixSum(const std::vector<T>& values)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        std::vector<Sum> weights;\n        weights.reserve(values.size());\n\
    \        for (T value : values) weights.push_back(static_cast<Sum>(value));\n\
    \        build(values, weights);\n    }\n\n    DynamicWaveletMatrixSum(\n    \
    \    const std::vector<T>& values,\n        const std::vector<Sum>& weights\n\
    \    ) {\n        build(values, weights);\n    }\n\n    int size() const {\n \
    \       return _size;\n    }\n\n    bool empty() const {\n        return _size\
    \ == 0;\n    }\n\n    void clear() {\n        *this = DynamicWaveletMatrixSum();\n\
    \    }\n\n    T access(int position) const {\n        assert(0 <= position &&\
    \ position < _size);\n        unsigned_type key = 0;\n        for (int level =\
    \ 0; level < BitWidth; level++) {\n            auto accessed = _levels[level].access_with_rank(position);\n\
    \            if (accessed.bit) {\n                key |= unsigned_type(1) << (BitWidth\
    \ - 1 - level);\n                position = _zero_count[level] + accessed.ones_before;\n\
    \            } else {\n                position -= accessed.ones_before;\n   \
    \         }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ position) const {\n        return access(position);\n    }\n\n    Sum weight(int\
    \ position) const {\n        assert(0 <= position && position < _size);\n    \
    \    return _levels[0].access_with_rank(position).weight;\n    }\n\n    std::pair<T,\
    \ Sum> get(int position) const {\n        assert(0 <= position && position < _size);\n\
    \        unsigned_type key = 0;\n        Sum result_weight{};\n        for (int\
    \ level = 0; level < BitWidth; level++) {\n            auto accessed = _levels[level].access_with_rank(position);\n\
    \            if (level == 0) result_weight = accessed.weight;\n            if\
    \ (accessed.bit) {\n                key |= unsigned_type(1) << (BitWidth - 1 -\
    \ level);\n                position = _zero_count[level] + accessed.ones_before;\n\
    \            } else {\n                position -= accessed.ones_before;\n   \
    \         }\n        }\n        return std::pair<T, Sum>(decode(key), result_weight);\n\
    \    }\n\n    void insert(int position, T value)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        insert(position, value, static_cast<Sum>(value));\n   \
    \ }\n\n    void insert(int position, T value, const Sum& weight) {\n        assert(0\
    \ <= position && position <= _size);\n        insert_encoded(position, encode_key(value),\
    \ weight);\n    }\n\n    void push_back(T value)\n        requires std::convertible_to<T,\
    \ Sum>\n    {\n        insert(_size, value);\n    }\n\n    void push_back(T value,\
    \ const Sum& weight) {\n        insert(_size, value, weight);\n    }\n\n    std::pair<T,\
    \ Sum> erase(int position) {\n        assert(0 <= position && position < _size);\n\
    \        ErasedElement erased = erase_encoded(position);\n        return std::pair<T,\
    \ Sum>(decode(erased.key), erased.weight);\n    }\n\n    void set(int position,\
    \ T value)\n        requires std::convertible_to<T, Sum>\n    {\n        set(position,\
    \ value, static_cast<Sum>(value));\n    }\n\n    void set(int position, T value,\
    \ const Sum& weight) {\n        assert(0 <= position && position < _size);\n \
    \       unsigned_type key = encode_key(value);\n        erase_encoded(position);\n\
    \        insert_encoded(position, key, weight);\n    }\n\n    void set_value(int\
    \ position, T value) {\n        assert(0 <= position && position < _size);\n \
    \       unsigned_type key = encode_key(value);\n        ErasedElement erased =\
    \ erase_encoded(position);\n        insert_encoded(position, key, erased.weight);\n\
    \    }\n\n    void set_weight(int position, const Sum& new_weight) {\n       \
    \ assert(0 <= position && position < _size);\n        for (int level = 0; level\
    \ < BitWidth; level++) {\n            auto accessed =\n                _levels[level].set_weight_with_rank(position,\
    \ new_weight);\n            if (accessed.bit) {\n                position = _zero_count[level]\
    \ + accessed.ones_before;\n            } else {\n                position -= accessed.ones_before;\n\
    \            }\n        }\n        _final_weights.set_weight_with_rank(position,\
    \ new_weight);\n    }\n\n    void add_weight(int position, const Sum& delta) {\n\
    \        assert(0 <= position && position < _size);\n        for (int level =\
    \ 0; level < BitWidth; level++) {\n            auto accessed =\n             \
    \   _levels[level].add_weight_with_rank(position, delta);\n            if (accessed.bit)\
    \ {\n                position = _zero_count[level] + accessed.ones_before;\n \
    \           } else {\n                position -= accessed.ones_before;\n    \
    \        }\n        }\n        _final_weights.add_weight_with_rank(position, delta);\n\
    \    }\n\n    int rank(T value, int right) const {\n        assert(0 <= right\
    \ && right <= _size);\n        return rank(value, 0, right);\n    }\n\n    int\
    \ rank(T value, int left, int right) const {\n        assert(0 <= left && left\
    \ <= right && right <= _size);\n        if constexpr (BitWidth < full_bit_width)\
    \ {\n            if (!key_fits(value)) return 0;\n        }\n        unsigned_type\
    \ key = encode_unchecked(value);\n        for (int level = 0; level < BitWidth;\
    \ level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            if (bit(key, level)) {\n                left\
    \ = _zero_count[level] + left_ones;\n                right = _zero_count[level]\
    \ + right_ones;\n            } else {\n                left -= left_ones;\n  \
    \              right -= right_ones;\n            }\n        }\n        return\
    \ right - left;\n    }\n\n    T kth_smallest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        unsigned_type key = 0;\n        for (int\
    \ level = 0; level < BitWidth; level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            if (k < zeros) {\n                left = left_zeros;\n\
    \                right = right_zeros;\n            } else {\n                k\
    \ -= zeros;\n                key |= unsigned_type(1) << (BitWidth - 1 - level);\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            }\n        }\n        return\
    \ decode(key);\n    }\n\n    T kth_largest(int left, int right, int k) const {\n\
    \        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k < right - left);\n        return kth_smallest(left, right, right -\
    \ left - 1 - k);\n    }\n\n    int range_freq(int left, int right, T upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        return\
    \ count_less(left, right, upper);\n    }\n\n    int range_freq(int left, int right,\
    \ T lower, T upper) const {\n        assert(0 <= left && left <= right && right\
    \ <= _size);\n        if (upper <= lower) return 0;\n        return count_less(left,\
    \ right, upper) -\n               count_less(left, right, lower);\n    }\n\n \
    \   std::optional<T> prev_value(int left, int right, T upper) const {\n      \
    \  assert(0 <= left && left <= right && right <= _size);\n        int count =\
    \ range_freq(left, right, upper);\n        if (count == 0) return std::nullopt;\n\
    \        return kth_smallest(left, right, count - 1);\n    }\n\n    std::optional<T>\
    \ next_value(int left, int right, T lower) const {\n        assert(0 <= left &&\
    \ left <= right && right <= _size);\n        int count = range_freq(left, right,\
    \ lower);\n        if (count == right - left) return std::nullopt;\n        return\
    \ kth_smallest(left, right, count);\n    }\n\n    Sum range_sum(int left, int\
    \ right) const {\n        assert(0 <= left && left <= right && right <= _size);\n\
    \        return _levels[0].range_sum(left, right);\n    }\n\n    Sum range_sum(int\
    \ left, int right, T upper) const {\n        assert(0 <= left && left <= right\
    \ && right <= _size);\n        return sum_less(left, right, upper);\n    }\n\n\
    \    Sum range_sum(int left, int right, T lower, T upper) const {\n        assert(0\
    \ <= left && left <= right && right <= _size);\n        if (upper <= lower) return\
    \ Sum{};\n        return sum_less(left, right, upper) -\n               sum_less(left,\
    \ right, lower);\n    }\n\n    Sum sum_k_smallest(int left, int right, int k)\
    \ const {\n        assert(0 <= left && left <= right && right <= _size);\n   \
    \     assert(0 <= k && k <= right - left);\n        Sum result{};\n        for\
    \ (int level = 0; level < BitWidth; level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            if (k < zeros) {\n                left = left_zeros;\n\
    \                right = right_zeros;\n            } else {\n                result\
    \ = result + range_zero(stats);\n                k -= zeros;\n               \
    \ left = _zero_count[level] + left_ones;\n                right = _zero_count[level]\
    \ + right_ones;\n            }\n        }\n        return result + _final_weights.range_sum(left,\
    \ left + k);\n    }\n\n    Sum sum_k_largest(int left, int right, int k) const\
    \ {\n        assert(0 <= left && left <= right && right <= _size);\n        assert(0\
    \ <= k && k <= right - left);\n        return range_sum(left, right) -\n     \
    \          sum_k_smallest(left, right, right - left - k);\n    }\n\n    template\
    \ <class Predicate>\n    int max_count_smallest(\n        int left,\n        int\
    \ right,\n        Predicate predicate\n    ) const {\n        assert(0 <= left\
    \ && left <= right && right <= _size);\n        assert(predicate(Sum{}));\n  \
    \      Sum result{};\n        int count = 0;\n        for (int level = 0; level\
    \ < BitWidth; level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int zeros = right_zeros\
    \ - left_zeros;\n            Sum candidate = result + range_zero(stats);\n   \
    \         if (predicate(candidate)) {\n                result = candidate;\n \
    \               count += zeros;\n                left = _zero_count[level] + left_ones;\n\
    \                right = _zero_count[level] + right_ones;\n            } else\
    \ {\n                left = left_zeros;\n                right = right_zeros;\n\
    \            }\n        }\n        return count +\n               _final_weights.max_prefix(\n\
    \                   left,\n                   right,\n                   result,\n\
    \                   predicate\n               );\n    }\n\n    template <class\
    \ Predicate>\n    int max_count_largest(\n        int left,\n        int right,\n\
    \        Predicate predicate\n    ) const {\n        assert(0 <= left && left\
    \ <= right && right <= _size);\n        assert(predicate(Sum{}));\n        Sum\
    \ result{};\n        int count = 0;\n        for (int level = 0; level < BitWidth;\
    \ level++) {\n            auto stats = _levels[level].prefix_stats_pair(left,\
    \ right);\n            int left_ones = stats.left.ones;\n            int right_ones\
    \ = stats.right.ones;\n            int left_zeros = left - left_ones;\n      \
    \      int right_zeros = right - right_ones;\n            int ones = right_ones\
    \ - left_ones;\n            Sum zero_result = range_zero(stats);\n           \
    \ Sum one_result = range_total(stats) - zero_result;\n            Sum candidate\
    \ = result + one_result;\n            if (predicate(candidate)) {\n          \
    \      result = candidate;\n                count += ones;\n                left\
    \ = left_zeros;\n                right = right_zeros;\n            } else {\n\
    \                left = _zero_count[level] + left_ones;\n                right\
    \ = _zero_count[level] + right_ones;\n            }\n        }\n        return\
    \ count +\n               _final_weights.max_suffix(\n                   left,\n\
    \                   right,\n                   result,\n                   predicate\n\
    \               );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n#line 5 \"benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp\"\
    \n\n#line 7 \"benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp\"\
    \n#include <chrono>\n#line 9 \"benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp\"\
    \n#include <cstdlib>\n#include <iomanip>\n#include <iostream>\n#line 14 \"benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp\"\
    \n#include <sys/resource.h>\n#line 17 \"benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp\"\
    \n\nnamespace {\n\nusing Clock = std::chrono::steady_clock;\nusing Nanoseconds\
    \ = std::chrono::nanoseconds;\nusing Key = std::uint32_t;\nusing OfflineMatrix\
    \ =\n    m1une::ds::OfflinePointUpdateRangeOrderStatisticsSum<Key, long long>;\n\
    using DynamicMatrix =\n    m1une::ds::DynamicWaveletMatrixSum<Key, long long,\
    \ 18>;\n\nstruct Operation {\n    int position = 0;\n    Key key = 0;\n    int\
    \ left = 0;\n    int right = 0;\n    long long target = 1;\n};\n\nstruct Result\
    \ {\n    Nanoseconds construction_time{};\n    Nanoseconds initialization_time{};\n\
    \    Nanoseconds update_time{};\n    Nanoseconds query_time{};\n    Nanoseconds\
    \ total_time{};\n    std::uint64_t checksum = 0;\n};\n\nstd::uint64_t random_state\
    \ = 0x243f6a8885a308d3ULL;\n\nstd::uint64_t random_value() {\n    random_state\
    \ ^= random_state << 7;\n    random_state ^= random_state >> 9;\n    return random_state;\n\
    }\n\nKey generated_key() {\n    return Key(1 + random_value() % 200000ULL);\n\
    }\n\ndouble milliseconds(Nanoseconds duration) {\n    return std::chrono::duration<double,\
    \ std::milli>(duration).count();\n}\n\nlong long peak_memory_bytes() {\n    rusage\
    \ usage{};\n    if (getrusage(RUSAGE_SELF, &usage) != 0) return -1;\n#ifdef __APPLE__\n\
    \    return usage.ru_maxrss;\n#else\n    return usage.ru_maxrss * 1024LL;\n#endif\n\
    }\n\nvoid add_checksum(std::uint64_t& checksum, std::optional<int> answer) {\n\
    \    std::uint64_t value = answer.has_value()\n                              ?\
    \ std::uint64_t(answer.value() + 1)\n                              : 0;\n    checksum\
    \ = checksum * 1000003ULL + value;\n}\n\nResult run_offline(\n    const std::vector<Key>&\
    \ initial,\n    const std::vector<std::pair<int, Key>>& candidates,\n    const\
    \ std::vector<Operation>& operations\n) {\n    Result result;\n    auto total_start\
    \ = Clock::now();\n    auto construction_start = Clock::now();\n    OfflineMatrix\
    \ matrix(initial, candidates);\n    auto construction_end = Clock::now();\n  \
    \  result.construction_time = construction_end - construction_start;\n    auto\
    \ profile = m1une::ds::\n        offline_point_update_range_order_statistics_sum_detail::\n\
    \            get_construction_profile();\n    result.initialization_time =\n \
    \       Nanoseconds(profile.initialization_nanoseconds);\n\n    for (const Operation&\
    \ operation : operations) {\n        auto update_start = Clock::now();\n     \
    \   matrix.set(operation.position, operation.key);\n        auto update_end =\
    \ Clock::now();\n        auto query_start = Clock::now();\n        std::optional<int>\
    \ answer =\n            matrix.min_count_largest_sum_at_least(\n             \
    \   operation.left,\n                operation.right,\n                operation.target\n\
    \            );\n        auto query_end = Clock::now();\n        result.update_time\
    \ += update_end - update_start;\n        result.query_time += query_end - query_start;\n\
    \        add_checksum(result.checksum, answer);\n    }\n    result.total_time\
    \ = Clock::now() - total_start;\n    return result;\n}\n\nResult run_dynamic(\n\
    \    const std::vector<Key>& initial,\n    const std::vector<Operation>& operations\n\
    ) {\n    Result result;\n    auto total_start = Clock::now();\n    auto construction_start\
    \ = Clock::now();\n    DynamicMatrix matrix(initial);\n    auto construction_end\
    \ = Clock::now();\n    result.construction_time = construction_end - construction_start;\n\
    \n    for (const Operation& operation : operations) {\n        auto update_start\
    \ = Clock::now();\n        matrix.set(operation.position, operation.key);\n  \
    \      auto update_end = Clock::now();\n        auto query_start = Clock::now();\n\
    \        int count = matrix.max_count_largest(\n            operation.left,\n\
    \            operation.right,\n            [&](long long sum) { return sum < operation.target;\
    \ }\n        );\n        std::optional<int> answer;\n        if (count != operation.right\
    \ - operation.left) {\n            answer = count + 1;\n        }\n        auto\
    \ query_end = Clock::now();\n        result.update_time += update_end - update_start;\n\
    \        result.query_time += query_end - query_start;\n        add_checksum(result.checksum,\
    \ answer);\n    }\n    result.total_time = Clock::now() - total_start;\n    return\
    \ result;\n}\n\nvoid print_result(const char* name, const Result& result) {\n\
    \    std::cout << name << \"_construction_ms \"\n              << milliseconds(result.construction_time)\
    \ << '\\n';\n    if (result.initialization_time != Nanoseconds()) {\n        std::cout\
    \ << name << \"_initialization_ms \"\n                  << milliseconds(result.initialization_time)\
    \ << '\\n';\n    }\n    std::cout << name << \"_update_ms \"\n              <<\
    \ milliseconds(result.update_time) << '\\n';\n    std::cout << name << \"_query_ms\
    \ \"\n              << milliseconds(result.query_time) << '\\n';\n    std::cout\
    \ << name << \"_total_ms \"\n              << milliseconds(result.total_time)\
    \ << '\\n';\n    std::cout << name << \"_checksum \" << result.checksum << '\\\
    n';\n}\n\n}  // namespace\n\nint main(int argc, char** argv) {\n    int n = argc\
    \ >= 2 ? std::atoi(argv[1]) : 100000;\n    int q = argc >= 3 ? std::atoi(argv[2])\
    \ : 100000;\n    if (n <= 0 || q < 0) return 2;\n\n    auto preparation_start\
    \ = Clock::now();\n    std::vector<Key> initial(n);\n    for (Key& key : initial)\
    \ key = generated_key();\n    std::vector<Key> current = initial;\n    std::vector<Operation>\
    \ operations(q);\n    std::vector<std::pair<int, Key>> candidates;\n    candidates.reserve(std::size_t(q)\
    \ + q / 8 + 1);\n\n    for (int query = 0; query < q; query++) {\n        Operation&\
    \ operation = operations[query];\n        if (query % 8 == 0) {\n            operation.position\
    \ = (query / 8) % std::min(n, 32);\n        } else {\n            operation.position\
    \ = int(random_value() % std::uint64_t(n));\n        }\n        if (query % 7\
    \ == 0) {\n            operation.key = current[operation.position];\n        }\
    \ else if (query % 11 == 0) {\n            operation.key = Key(1 + query % 97);\n\
    \        } else {\n            operation.key = generated_key();\n        }\n \
    \       current[operation.position] = operation.key;\n        candidates.emplace_back(operation.position,\
    \ operation.key);\n        if (query % 8 == 0) {\n            candidates.emplace_back(operation.position,\
    \ operation.key);\n        }\n\n        if (query % 3 == 0) {\n            int\
    \ length = 1 + int(random_value() % std::uint64_t(std::min(n, 128)));\n      \
    \      operation.left =\n                int(random_value() % std::uint64_t(n\
    \ - length + 1));\n            operation.right = operation.left + length;\n  \
    \      } else if (query % 3 == 1) {\n            int length = 1 + int(random_value()\
    \ % std::uint64_t(n));\n            operation.left =\n                int(random_value()\
    \ % std::uint64_t(n - length + 1));\n            operation.right = operation.left\
    \ + length;\n        } else {\n            operation.left = 0;\n            operation.right\
    \ = n;\n        }\n\n        if (query % 5 == 0) {\n            operation.target\
    \ = std::numeric_limits<long long>::max() / 4;\n        } else if (query % 5 ==\
    \ 1) {\n            operation.target = 1;\n        } else {\n            long\
    \ long length = operation.right - operation.left;\n            operation.target\
    \ =\n                1 + static_cast<long long>(random_value() %\n           \
    \         std::uint64_t(length * 100000LL + 1));\n        }\n    }\n    for (int\
    \ index = int(candidates.size()) - 1; 0 < index; index--) {\n        int other\
    \ = int(random_value() % std::uint64_t(index + 1));\n        std::swap(candidates[index],\
    \ candidates[other]);\n    }\n    Nanoseconds preparation_time = Clock::now()\
    \ - preparation_start;\n\n    Result offline = run_offline(initial, candidates,\
    \ operations);\n    Result dynamic = run_dynamic(initial, operations);\n    if\
    \ (offline.checksum != dynamic.checksum) return 3;\n\n    std::cout << std::fixed\
    \ << std::setprecision(3);\n    std::cout << \"N \" << n << '\\n';\n    std::cout\
    \ << \"Q \" << q << '\\n';\n    std::cout << \"registered_candidate_entries \"\
    \ << candidates.size() << '\\n';\n    std::cout << \"candidate_preparation_ms\
    \ \"\n              << milliseconds(preparation_time) << '\\n';\n    print_result(\"\
    offline\", offline);\n    print_result(\"dynamic\", dynamic);\n    std::cout <<\
    \ \"peak_memory_mib \"\n              << double(peak_memory_bytes()) / (1024.0\
    \ * 1024.0) << '\\n';\n}\n"
  code: "#define M1UNE_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_PROFILE 1\n\
    \n#include \"../../../ds/range_query/offline_point_update_range_order_statistics_sum.hpp\"\
    \n#include \"../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp\"\n\n#include\
    \ <algorithm>\n#include <chrono>\n#include <cstdint>\n#include <cstdlib>\n#include\
    \ <iomanip>\n#include <iostream>\n#include <limits>\n#include <optional>\n#include\
    \ <sys/resource.h>\n#include <utility>\n#include <vector>\n\nnamespace {\n\nusing\
    \ Clock = std::chrono::steady_clock;\nusing Nanoseconds = std::chrono::nanoseconds;\n\
    using Key = std::uint32_t;\nusing OfflineMatrix =\n    m1une::ds::OfflinePointUpdateRangeOrderStatisticsSum<Key,\
    \ long long>;\nusing DynamicMatrix =\n    m1une::ds::DynamicWaveletMatrixSum<Key,\
    \ long long, 18>;\n\nstruct Operation {\n    int position = 0;\n    Key key =\
    \ 0;\n    int left = 0;\n    int right = 0;\n    long long target = 1;\n};\n\n\
    struct Result {\n    Nanoseconds construction_time{};\n    Nanoseconds initialization_time{};\n\
    \    Nanoseconds update_time{};\n    Nanoseconds query_time{};\n    Nanoseconds\
    \ total_time{};\n    std::uint64_t checksum = 0;\n};\n\nstd::uint64_t random_state\
    \ = 0x243f6a8885a308d3ULL;\n\nstd::uint64_t random_value() {\n    random_state\
    \ ^= random_state << 7;\n    random_state ^= random_state >> 9;\n    return random_state;\n\
    }\n\nKey generated_key() {\n    return Key(1 + random_value() % 200000ULL);\n\
    }\n\ndouble milliseconds(Nanoseconds duration) {\n    return std::chrono::duration<double,\
    \ std::milli>(duration).count();\n}\n\nlong long peak_memory_bytes() {\n    rusage\
    \ usage{};\n    if (getrusage(RUSAGE_SELF, &usage) != 0) return -1;\n#ifdef __APPLE__\n\
    \    return usage.ru_maxrss;\n#else\n    return usage.ru_maxrss * 1024LL;\n#endif\n\
    }\n\nvoid add_checksum(std::uint64_t& checksum, std::optional<int> answer) {\n\
    \    std::uint64_t value = answer.has_value()\n                              ?\
    \ std::uint64_t(answer.value() + 1)\n                              : 0;\n    checksum\
    \ = checksum * 1000003ULL + value;\n}\n\nResult run_offline(\n    const std::vector<Key>&\
    \ initial,\n    const std::vector<std::pair<int, Key>>& candidates,\n    const\
    \ std::vector<Operation>& operations\n) {\n    Result result;\n    auto total_start\
    \ = Clock::now();\n    auto construction_start = Clock::now();\n    OfflineMatrix\
    \ matrix(initial, candidates);\n    auto construction_end = Clock::now();\n  \
    \  result.construction_time = construction_end - construction_start;\n    auto\
    \ profile = m1une::ds::\n        offline_point_update_range_order_statistics_sum_detail::\n\
    \            get_construction_profile();\n    result.initialization_time =\n \
    \       Nanoseconds(profile.initialization_nanoseconds);\n\n    for (const Operation&\
    \ operation : operations) {\n        auto update_start = Clock::now();\n     \
    \   matrix.set(operation.position, operation.key);\n        auto update_end =\
    \ Clock::now();\n        auto query_start = Clock::now();\n        std::optional<int>\
    \ answer =\n            matrix.min_count_largest_sum_at_least(\n             \
    \   operation.left,\n                operation.right,\n                operation.target\n\
    \            );\n        auto query_end = Clock::now();\n        result.update_time\
    \ += update_end - update_start;\n        result.query_time += query_end - query_start;\n\
    \        add_checksum(result.checksum, answer);\n    }\n    result.total_time\
    \ = Clock::now() - total_start;\n    return result;\n}\n\nResult run_dynamic(\n\
    \    const std::vector<Key>& initial,\n    const std::vector<Operation>& operations\n\
    ) {\n    Result result;\n    auto total_start = Clock::now();\n    auto construction_start\
    \ = Clock::now();\n    DynamicMatrix matrix(initial);\n    auto construction_end\
    \ = Clock::now();\n    result.construction_time = construction_end - construction_start;\n\
    \n    for (const Operation& operation : operations) {\n        auto update_start\
    \ = Clock::now();\n        matrix.set(operation.position, operation.key);\n  \
    \      auto update_end = Clock::now();\n        auto query_start = Clock::now();\n\
    \        int count = matrix.max_count_largest(\n            operation.left,\n\
    \            operation.right,\n            [&](long long sum) { return sum < operation.target;\
    \ }\n        );\n        std::optional<int> answer;\n        if (count != operation.right\
    \ - operation.left) {\n            answer = count + 1;\n        }\n        auto\
    \ query_end = Clock::now();\n        result.update_time += update_end - update_start;\n\
    \        result.query_time += query_end - query_start;\n        add_checksum(result.checksum,\
    \ answer);\n    }\n    result.total_time = Clock::now() - total_start;\n    return\
    \ result;\n}\n\nvoid print_result(const char* name, const Result& result) {\n\
    \    std::cout << name << \"_construction_ms \"\n              << milliseconds(result.construction_time)\
    \ << '\\n';\n    if (result.initialization_time != Nanoseconds()) {\n        std::cout\
    \ << name << \"_initialization_ms \"\n                  << milliseconds(result.initialization_time)\
    \ << '\\n';\n    }\n    std::cout << name << \"_update_ms \"\n              <<\
    \ milliseconds(result.update_time) << '\\n';\n    std::cout << name << \"_query_ms\
    \ \"\n              << milliseconds(result.query_time) << '\\n';\n    std::cout\
    \ << name << \"_total_ms \"\n              << milliseconds(result.total_time)\
    \ << '\\n';\n    std::cout << name << \"_checksum \" << result.checksum << '\\\
    n';\n}\n\n}  // namespace\n\nint main(int argc, char** argv) {\n    int n = argc\
    \ >= 2 ? std::atoi(argv[1]) : 100000;\n    int q = argc >= 3 ? std::atoi(argv[2])\
    \ : 100000;\n    if (n <= 0 || q < 0) return 2;\n\n    auto preparation_start\
    \ = Clock::now();\n    std::vector<Key> initial(n);\n    for (Key& key : initial)\
    \ key = generated_key();\n    std::vector<Key> current = initial;\n    std::vector<Operation>\
    \ operations(q);\n    std::vector<std::pair<int, Key>> candidates;\n    candidates.reserve(std::size_t(q)\
    \ + q / 8 + 1);\n\n    for (int query = 0; query < q; query++) {\n        Operation&\
    \ operation = operations[query];\n        if (query % 8 == 0) {\n            operation.position\
    \ = (query / 8) % std::min(n, 32);\n        } else {\n            operation.position\
    \ = int(random_value() % std::uint64_t(n));\n        }\n        if (query % 7\
    \ == 0) {\n            operation.key = current[operation.position];\n        }\
    \ else if (query % 11 == 0) {\n            operation.key = Key(1 + query % 97);\n\
    \        } else {\n            operation.key = generated_key();\n        }\n \
    \       current[operation.position] = operation.key;\n        candidates.emplace_back(operation.position,\
    \ operation.key);\n        if (query % 8 == 0) {\n            candidates.emplace_back(operation.position,\
    \ operation.key);\n        }\n\n        if (query % 3 == 0) {\n            int\
    \ length = 1 + int(random_value() % std::uint64_t(std::min(n, 128)));\n      \
    \      operation.left =\n                int(random_value() % std::uint64_t(n\
    \ - length + 1));\n            operation.right = operation.left + length;\n  \
    \      } else if (query % 3 == 1) {\n            int length = 1 + int(random_value()\
    \ % std::uint64_t(n));\n            operation.left =\n                int(random_value()\
    \ % std::uint64_t(n - length + 1));\n            operation.right = operation.left\
    \ + length;\n        } else {\n            operation.left = 0;\n            operation.right\
    \ = n;\n        }\n\n        if (query % 5 == 0) {\n            operation.target\
    \ = std::numeric_limits<long long>::max() / 4;\n        } else if (query % 5 ==\
    \ 1) {\n            operation.target = 1;\n        } else {\n            long\
    \ long length = operation.right - operation.left;\n            operation.target\
    \ =\n                1 + static_cast<long long>(random_value() %\n           \
    \         std::uint64_t(length * 100000LL + 1));\n        }\n    }\n    for (int\
    \ index = int(candidates.size()) - 1; 0 < index; index--) {\n        int other\
    \ = int(random_value() % std::uint64_t(index + 1));\n        std::swap(candidates[index],\
    \ candidates[other]);\n    }\n    Nanoseconds preparation_time = Clock::now()\
    \ - preparation_start;\n\n    Result offline = run_offline(initial, candidates,\
    \ operations);\n    Result dynamic = run_dynamic(initial, operations);\n    if\
    \ (offline.checksum != dynamic.checksum) return 3;\n\n    std::cout << std::fixed\
    \ << std::setprecision(3);\n    std::cout << \"N \" << n << '\\n';\n    std::cout\
    \ << \"Q \" << q << '\\n';\n    std::cout << \"registered_candidate_entries \"\
    \ << candidates.size() << '\\n';\n    std::cout << \"candidate_preparation_ms\
    \ \"\n              << milliseconds(preparation_time) << '\\n';\n    print_result(\"\
    offline\", offline);\n    print_result(\"dynamic\", dynamic);\n    std::cout <<\
    \ \"peak_memory_mib \"\n              << double(peak_memory_bytes()) / (1024.0\
    \ * 1024.0) << '\\n';\n}\n"
  dependsOn:
  - ds/range_query/offline_point_update_range_order_statistics_sum.hpp
  - ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
  - ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
  isVerificationFile: false
  path: benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
  requiredBy: []
  timestamp: '2026-07-19 03:31:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
layout: document
redirect_from:
- /library/benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
- /library/benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp.html
title: benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
---
