---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
    title: benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/offline_point_update_range_order_statistics_sum.hpp\"\
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
    \ namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_HPP\n\
    #define M1UNE_DS_RANGE_QUERY_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
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
    \ namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_OFFLINE_POINT_UPDATE_RANGE_ORDER_STATISTICS_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/offline_point_update_range_order_statistics_sum.hpp
  requiredBy:
  - benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp
  timestamp: '2026-07-19 03:31:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/range_query/offline_point_update_range_order_statistics_sum.hpp
layout: document
title: Offline-Registered Point-Update Range Order Statistics with Sums
---

## Overview

`OfflinePointUpdateRangeOrderStatisticsSum<T, Sum>` maintains a fixed-length
sequence of `(key, weight)` pairs. It supports point replacement, range
frequencies and order statistics, sums selected by key order, and direct
minimum-count threshold searches.

The structure is intended for problems in which every key that may be assigned
to each position is known before processing begins. Initial keys are registered
automatically; future `(position, key)` states are passed to the constructor.
Weights need not be known in advance. Query and update processing is still
sequential: only the possible update states are collected offline.

This is not a fully dynamic wavelet matrix. The sequence length never changes,
and there is no insertion or erasure API. In exchange, precomputed update
handles and flat Fenwick storage make point updates substantially cheaper than
rerouting elements through mutable sequence trees.

## Requirements

`T` must be copyable, sortable by `operator<`, and equality comparable under
the induced ordering. Values `a` and `b` are equivalent when neither `a < b`
nor `b < a` holds.

`Sum{}` must be the additive identity. `Sum` must support copying, addition,
and subtraction. The key-only constructor and `set(position, key)` additionally
require `T` to be convertible to `Sum`. Arithmetic overflow is unchecked.

Every key assigned to a position must have been registered for that position.
Initial keys are always registered. Duplicate candidate pairs and arbitrary
candidate order are accepted and deduplicated. Candidate positions and
unregistered updates are asserted in debug builds; an unregistered update is
an invalid operation.

## Public Interface

All positions are zero-based and all index and key ranges are half-open.

```cpp
template <class T, class Sum = T>
class OfflinePointUpdateRangeOrderStatisticsSum;
```

Let `N` be the fixed sequence length, `V` the number of distinct registered
keys, `H = ceil(log2(V))`, and `M` the number of distinct registered
`(position, key)` states.

### Construction and access

| Method | Description | Complexity |
| --- | --- | --- |
| `OfflinePointUpdateRangeOrderStatisticsSum(const vector<T>& initial_values, const vector<pair<int, T>>& update_candidates)` | Registers candidates and uses every initial key as its weight. | $O(MH\log N)$ time, $O(MH)$ memory |
| `OfflinePointUpdateRangeOrderStatisticsSum(const vector<T>& initial_keys, const vector<Sum>& initial_weights, const vector<pair<int, T>>& update_candidates)` | Registers candidates and builds separate initial weights. | $O(MH\log N)$ time, $O(MH)$ memory |
| `int size() const` | Returns the fixed sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int position) const` | Returns the active key. | $O(1)$ |
| `T operator[](int position) const` | Equivalent to `access(position)`. | $O(1)$ |
| `Sum weight(int position) const` | Returns the active weight. | $O(1)$ |
| `pair<T, Sum> get(int position) const` | Returns the active key and weight. | $O(1)$ |

Candidate sorting and key compression also cost
`O((N + candidates) log(N + candidates))`; the displayed construction bound
covers the root-to-leaf registrations, handle lookup, and activation work.

### Point updates

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int position, T key)` | Replaces both key and weight with `key`. | $O(H\log N)$ |
| `void set(int position, T key, const Sum& weight)` | Replaces both key and weight. | $O(H\log N)$ |
| `void set_value(int position, T key)` | Replaces the key and preserves the weight. | $O(H\log N)$ |
| `void set_weight(int position, const Sum& weight)` | Replaces the weight and preserves the key. | $O(H\log N)$ |
| `void add_weight(int position, const Sum& delta)` | Adds to the weight and preserves the key. | $O(H\log N)$ |

The hot path performs one candidate-list binary search, then follows
precomputed Fenwick-local handles. It performs no per-level `lower_bound` and
does not allocate.

### Order-statistic queries

| Method | Description | Complexity |
| --- | --- | --- |
| `int rank(T key, int right) const` | Counts `key` in `[0, right)`. | $O(\log N)$ |
| `int rank(T key, int left, int right) const` | Counts `key` in the index range. | $O(\log N)$ |
| `int range_freq(int left, int right, T upper) const` | Counts keys less than `upper`. | $O(H\log N)$ |
| `int range_freq(int left, int right, T lower, T upper) const` | Counts keys in `[lower, upper)`. | $O(H\log N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest key. | $O(H\log N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest key. | $O(H\log N)$ |
| `optional<T> prev_value(int left, int right, T upper) const` | Returns the greatest key below `upper`, or `nullopt`. | $O(H\log N)$ |
| `optional<T> next_value(int left, int right, T lower) const` | Returns the smallest key at least `lower`, or `nullopt`. | $O(H\log N)$ |

The `k`-th methods require `0 <= k < right - left`.

### Sum and threshold queries

| Method | Description | Complexity |
| --- | --- | --- |
| `Sum range_sum(int left, int right) const` | Sums every active weight in the index range. | $O(\log N)$ |
| `Sum range_sum(int left, int right, T upper) const` | Sums weights whose keys are less than `upper`. | $O(H\log N)$ |
| `Sum range_sum(int left, int right, T lower, T upper) const` | Sums weights whose keys are in `[lower, upper)`. | $O(H\log N)$ |
| `Sum sum_k_smallest(int left, int right, int k) const` | Sums the first `k` elements in ascending key order. | $O(H\log N)$ |
| `Sum sum_k_largest(int left, int right, int k) const` | Sums the first `k` elements in descending key order. | $O(H\log N)$ |
| `optional<int> min_count_smallest_sum_at_least(int left, int right, const Sum& target) const` | Returns the minimum ascending-order count whose sum reaches `target`. | $O(H\log N)$ |
| `optional<int> min_count_largest_sum_at_least(int left, int right, const Sum& target) const` | Returns the minimum descending-order count whose sum reaches `target`. | $O(H\log N)$ |

Sum methods allow `0 <= k <= right - left`. Equal keys use increasing current
sequence index for `smallest` and decreasing current sequence index for
`largest`.

The threshold methods require `Sum{} < target` and all active weights in the
structure to be nonnegative while either threshold method is used. They return
`nullopt` when the index-range sum is below `target`. Zero weights are selected
and counted when they occur before the element that reaches the threshold.
Threshold traversal descends the value tree once and uses Fenwick prefix-sum
selection at the final equal-key leaf; it does not binary-search an answer or
call a `sum_k` query repeatedly.

## Implementation

Keys are coordinate-compressed and form the leaves of a value segment tree.
Every registered state contributes its original position to each node on its
root-to-leaf value path. Construction deduplicates those positions and flattens
all node coordinates and Fenwick arrays into CSR-like global vectors.

Each active position contributes count one and its current weight along one
value path. A candidate state stores precomputed `(node, local_position)`
handles, so replacement removes the old path and activates the new path without
searching node coordinate arrays. Ordinary updates and queries allocate no
memory.

## ABC467 G-style example

```cpp
#include "ds/range_query/offline_point_update_range_order_statistics_sum.hpp"

#include <optional>
#include <utility>
#include <vector>

struct Query {
    int position;
    int value;
    int left;
    int right;
    long long target;
};

int main() {
    int n = read_int();
    int q = read_int();
    std::vector<int> initial_values(n);
    read(initial_values);

    std::vector<Query> queries(q);
    std::vector<std::pair<int, int>> candidates;
    candidates.reserve(q);
    for (Query& query : queries) {
        read(
            query.position,
            query.value,
            query.left,
            query.right,
            query.target
        );
        query.position--;
        query.left--;
        candidates.emplace_back(query.position, query.value);
    }

    using Matrix =
        m1une::ds::OfflinePointUpdateRangeOrderStatisticsSum<int, long long>;
    Matrix matrix(initial_values, candidates);
    for (const Query& query : queries) {
        matrix.set(query.position, query.value);
        std::optional<int> answer =
            matrix.min_count_largest_sum_at_least(
                query.left,
                query.right,
                query.target
            );
        print(answer.has_value() ? answer.value() : -1);
    }
}
```

A complete compilable example is under `examples/ds/range_query/`. It is not an
`oj-verify` target.

## Limitations

The sequence length and candidate states are fixed after construction. Memory
is proportional to every distinct registered state times its value-tree path,
so registering many keys for every position can be expensive. Construction is
also heavier than a dynamic wavelet matrix built only from the initial state.
Use the fully dynamic structure when insertion, erasure, or previously unknown
keys are required.
