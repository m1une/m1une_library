---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/rollback_segtree_beats.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"beats_acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"beats_acted_monoid/concept.hpp\"\
    \n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 7 \"beats_acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ beats_acted_monoid {\n\n// An acted monoid whose action may require descent\
    \ before it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid\
    \ = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T\
    \ x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n\n#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n\
    #include <algorithm>\n#line 6 \"ds/detail/rollback_journal.hpp\"\n#include <cstddef>\n\
    #include <cstdint>\n#include <limits>\n#line 11 \"ds/detail/rollback_journal.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\n\
    struct RollbackJournal {\n    struct Change {\n        int index;\n        Node\
    \ value;\n    };\n\n    struct Checkpoint {\n        std::size_t change_size;\n\
    \        std::size_t node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node>\
    \ nodes;\n    std::vector<Change> changes;\n    std::vector<Checkpoint> checkpoints;\n\
    \    std::vector<std::uint64_t> saved_epoch;\n    std::uint64_t next_epoch = 1;\n\
    \n    std::uint64_t new_epoch() {\n        if (next_epoch == 0) {\n          \
    \  std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n            next_epoch\
    \ = 1;\n        }\n        return next_epoch++;\n    }\n\n    int size() const\
    \ { return int(nodes.size()); }\n\n    Node& operator[](int index) { return nodes[index];\
    \ }\n    const Node& operator[](int index) const { return nodes[index]; }\n\n\
    \    template <class... Args>\n    int emplace(Args&&... args) {\n        assert(nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        int index = int(nodes.size());\n\
    \        nodes.emplace_back(std::forward<Args>(args)...);\n        saved_epoch.push_back(0);\n\
    \        return index;\n    }\n\n    int snapshot() {\n        assert(checkpoints.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        checkpoints.push_back(Checkpoint{changes.size(),\
    \ nodes.size(), new_epoch()});\n        return int(checkpoints.size());\n    }\n\
    \n    void touch(int index) {\n        assert(0 <= index && index < size());\n\
    \        if (checkpoints.empty()) return;\n        const Checkpoint& checkpoint\
    \ = checkpoints.back();\n        if (std::size_t(index) >= checkpoint.node_size)\
    \ return;\n        if (saved_epoch[index] == checkpoint.epoch) return;\n     \
    \   saved_epoch[index] = checkpoint.epoch;\n        changes.push_back(Change{index,\
    \ nodes[index]});\n    }\n\n    int snapshot_count() const { return int(checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        checkpoints.reserve(count);\n    }\n\n    void reserve_changes(std::size_t\
    \ count) { changes.reserve(count); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        Checkpoint checkpoint\
    \ = checkpoints[state - 1];\n        while (changes.size() > checkpoint.change_size)\
    \ {\n            Change change = std::move(changes.back());\n            changes.pop_back();\n\
    \            nodes[change.index] = std::move(change.value);\n        }\n     \
    \   nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n        saved_epoch.resize(checkpoint.node_size);\n\
    \        checkpoints.resize(state);\n        checkpoints.back().change_size =\
    \ changes.size();\n        checkpoints.back().node_size = nodes.size();\n    \
    \    checkpoints.back().epoch = new_epoch();\n    }\n\n    void clear_history()\
    \ {\n        changes.clear();\n        checkpoints.clear();\n        std::fill(saved_epoch.begin(),\
    \ saved_epoch.end(), 0);\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        changes.clear();\n        checkpoints.clear();\n        saved_epoch.clear();\n\
    \        next_epoch = 1;\n    }\n};\n\n}  // namespace detail\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/rollback_segtree_beats.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Generic Segment Tree Beats for actions\
    \ that may require recursive descent.\ntemplate <m1une::beats_acted_monoid::IsBeatsActedMonoid\
    \ ActedMonoid>\nstruct RollbackSegtreeBeats {\n    using value_type = typename\
    \ ActedMonoid::value_type;\n    using operator_type = typename ActedMonoid::operator_type;\n\
    \    using T = value_type;\n    using F = operator_type;\n\n   private:\n    int\
    \ _n = 0;\n    int _size = 1;\n    struct Node {\n        T value = ActedMonoid::id();\n\
    \        F lazy = ActedMonoid::op_id();\n        bool has_lazy = false;\n    };\n\
    \n    detail::RollbackJournal<Node> _journal;\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ordinal) {\n        if constexpr (requires(F\
    \ g, T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n       \
    \ }) {\n            return ActedMonoid::mapping(f, value, ordinal);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static bool can_apply_at(const F& f, const T& value, long long ordinal)\
    \ {\n        if constexpr (requires(F g, T x, long long i) {\n            ActedMonoid::can_apply(g,\
    \ x, i);\n        }) {\n            return ActedMonoid::can_apply(f, value, ordinal);\n\
    \        } else {\n            return ActedMonoid::can_apply(f, value);\n    \
    \    }\n    }\n\n    static F shift_operator(const F& f, long long ordinal) {\n\
    \        if constexpr (requires(F g, long long i) {\n            ActedMonoid::op_shift(g,\
    \ i);\n        }) {\n            return ActedMonoid::op_shift(f, ordinal);\n \
    \       } else {\n            return f;\n        }\n    }\n\n    void initialize(std::vector<T>&&\
    \ values) {\n        _journal.clear();\n        _n = int(values.size());\n   \
    \     _size = int(m1une::math::bit_ceil((unsigned int)_n));\n        _journal.nodes.assign(2\
    \ * _size, Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n        for (int i = 0; i < _n; ++i) {\n            _journal[_size + i].value\
    \ = std::move(values[i]);\n        }\n        for (int k = _size - 1; k >= 1;\
    \ --k) update(k);\n    }\n\n    void update(int node) {\n        _journal.touch(node);\n\
    \        _journal[node].value = ActedMonoid::op(\n            _journal[node *\
    \ 2].value,\n            _journal[node * 2 + 1].value\n        );\n    }\n\n \
    \   void all_apply(int node, int left, int right, const F& f) {\n        if (_n\
    \ <= left) return;\n        if (can_apply_at(f, _journal[node].value, 0)) {\n\
    \            _journal.touch(node);\n            _journal[node].value = mapping_at(f,\
    \ _journal[node].value, 0);\n            if (node < _size) {\n               \
    \ _journal[node].lazy = ActedMonoid::op_comp(f, _journal[node].lazy);\n      \
    \          _journal[node].has_lazy = true;\n            }\n            return;\n\
    \        }\n\n        assert(right - left > 1);\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        all_apply(node * 2,\
    \ left, middle, f);\n        all_apply(\n            node * 2 + 1,\n         \
    \   middle,\n            right,\n            shift_operator(f, middle - left)\n\
    \        );\n        update(node);\n    }\n\n    void push(int node, int left,\
    \ int right) {\n        assert(right - left > 1);\n        if (!_journal[node].has_lazy)\
    \ return;\n        int middle = left + (right - left) / 2;\n        F f = _journal[node].lazy;\n\
    \        _journal.touch(node);\n        _journal[node].lazy = ActedMonoid::op_id();\n\
    \        _journal[node].has_lazy = false;\n        all_apply(node * 2, left, middle,\
    \ f);\n        all_apply(\n            node * 2 + 1,\n            middle,\n  \
    \          right,\n            shift_operator(f, middle - left)\n        );\n\
    \    }\n\n    void set_impl(\n        int node,\n        int left,\n        int\
    \ right,\n        int index,\n        T value\n    ) {\n        if (right - left\
    \ == 1) {\n            _journal.touch(node);\n            _journal[node].value\
    \ = std::move(value);\n            return;\n        }\n        push(node, left,\
    \ right);\n        int middle = left + (right - left) / 2;\n        if (index\
    \ < middle) {\n            set_impl(node * 2, left, middle, index, std::move(value));\n\
    \        } else {\n            set_impl(\n                node * 2 + 1,\n    \
    \            middle,\n                right,\n                index,\n       \
    \         std::move(value)\n            );\n        }\n        update(node);\n\
    \    }\n\n    T get_impl(int node, int left, int right, int index) {\n       \
    \ if (right - left == 1) return _journal[node].value;\n        push(node, left,\
    \ right);\n        int middle = left + (right - left) / 2;\n        if (index\
    \ < middle) {\n            return get_impl(node * 2, left, middle, index);\n \
    \       }\n        return get_impl(node * 2 + 1, middle, right, index);\n    }\n\
    \n    T prod_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_left,\n        int query_right\n    ) {\n        if (\n   \
    \         query_right <= left || right <= query_left || _n <= left\n        )\
    \ {\n            return ActedMonoid::id();\n        }\n        if (query_left\
    \ <= left && right <= query_right) {\n            return _journal[node].value;\n\
    \        }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_impl(\n    \
    \            node * 2,\n                left,\n                middle,\n     \
    \           query_left,\n                query_right\n            ),\n       \
    \     prod_impl(\n                node * 2 + 1,\n                middle,\n   \
    \             right,\n                query_left,\n                query_right\n\
    \            )\n        );\n    }\n\n    void apply_impl(\n        int node,\n\
    \        int left,\n        int right,\n        int query_left,\n        int query_right,\n\
    \        int base_left,\n        const F& f\n    ) {\n        if (\n         \
    \   query_right <= left || right <= query_left || _n <= left\n        ) {\n  \
    \          return;\n        }\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                node,\n                left,\n  \
    \              right,\n                shift_operator(f, left - base_left)\n \
    \           );\n            return;\n        }\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        apply_impl(\n      \
    \      node * 2,\n            left,\n            middle,\n            query_left,\n\
    \            query_right,\n            base_left,\n            f\n        );\n\
    \        apply_impl(\n            node * 2 + 1,\n            middle,\n       \
    \     right,\n            query_left,\n            query_right,\n            base_left,\n\
    \            f\n        );\n        update(node);\n    }\n\n    void collect_impl(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        std::vector<T>& result\n    ) {\n        if\
    \ (\n            query_right <= left || right <= query_left || _n <= left\n  \
    \      ) {\n            return;\n        }\n        if (right - left == 1) {\n\
    \            result.push_back(_journal[node].value);\n            return;\n  \
    \      }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        collect_impl(\n            node * 2,\n            left,\n\
    \            middle,\n            query_left,\n            query_right,\n    \
    \        result\n        );\n        collect_impl(\n            node * 2 + 1,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  query_right,\n            result\n        );\n    }\n\n    template <class\
    \ Predicate>\n    bool max_right_impl(\n        int node,\n        int left,\n\
    \        int right,\n        int query_left,\n        Predicate& predicate,\n\
    \        T& product,\n        int& answer\n    ) {\n        if (right <= query_left\
    \ || _n <= left) return true;\n        if (query_left <= left) {\n           \
    \ T next = ActedMonoid::op(product, _journal[node].value);\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return true;\n\
    \            }\n            if (right - left == 1) {\n                answer =\
    \ left;\n                return false;\n            }\n        }\n        push(node,\
    \ left, right);\n        int middle = left + (right - left) / 2;\n        if (!max_right_impl(\n\
    \                node * 2,\n                left,\n                middle,\n \
    \               query_left,\n                predicate,\n                product,\n\
    \                answer\n            )) {\n            return false;\n       \
    \ }\n        return max_right_impl(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            predicate,\n       \
    \     product,\n            answer\n        );\n    }\n\n    template <class Predicate>\n\
    \    bool min_left_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        Predicate& predicate,\n        T& product,\n\
    \        int& answer\n    ) {\n        if (query_right <= left || _n <= left)\
    \ return true;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(_journal[node].value,\
    \ product);\n            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return true;\n            }\n            if (right - left ==\
    \ 1) {\n                answer = right;\n                return false;\n     \
    \       }\n        }\n        push(node, left, right);\n        int middle = left\
    \ + (right - left) / 2;\n        if (!min_left_impl(\n                node * 2\
    \ + 1,\n                middle,\n                right,\n                query_right,\n\
    \                predicate,\n                product,\n                answer\n\
    \            )) {\n            return false;\n        }\n        return min_left_impl(\n\
    \            node * 2,\n            left,\n            middle,\n            query_right,\n\
    \            predicate,\n            product,\n            answer\n        );\n\
    \    }\n\n   public:\n    RollbackSegtreeBeats() {\n        initialize({});\n\
    \    }\n\n    explicit RollbackSegtreeBeats(int n) {\n        assert(0 <= n);\n\
    \        initialize(std::vector<T>(n, ActedMonoid::id()));\n    }\n\n    explicit\
    \ RollbackSegtreeBeats(const std::vector<T>& values) {\n        initialize(std::vector<T>(values));\n\
    \    }\n\n    explicit RollbackSegtreeBeats(std::vector<T>&& values) {\n     \
    \   initialize(std::move(values));\n    }\n\n    template <typename U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit RollbackSegtreeBeats(const std::vector<U>& values) {\n\
    \        std::vector<T> converted;\n        converted.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); ++i) {\n            if constexpr\
    \ (requires(U x) { ActedMonoid::make(x); }) {\n                converted.push_back(ActedMonoid::make(values[i]));\n\
    \            } else if constexpr (requires(U x, int index) {\n               \
    \ ActedMonoid::make(x, index);\n            }) {\n                converted.push_back(ActedMonoid::make(values[i],\
    \ i));\n            } else {\n                converted.push_back(static_cast<T>(values[i]));\n\
    \            }\n        }\n        initialize(std::move(converted));\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    std::size_t node_count() const { return\
    \ _journal.nodes.size(); }\n\n    void set(int index, T value) {\n        assert(0\
    \ <= index && index < _n);\n        set_impl(1, 0, _size, index, std::move(value));\n\
    \    }\n    void set_inplace(int index, T value) { set(index, std::move(value));\
    \ }\n\n    T get(int index) {\n        assert(0 <= index && index < _n);\n   \
    \     return get_impl(1, 0, _size, index);\n    }\n\n    T operator[](int index)\
    \ {\n        return get(index);\n    }\n\n    T prod(int left, int right) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ == right) return ActedMonoid::id();\n        return prod_impl(1, 0, _size, left,\
    \ right);\n    }\n\n    T all_prod() const {\n        return _journal[1].value;\n\
    \    }\n\n    void apply(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        apply_impl(1, 0, _size, index, index + 1, index, f);\n    }\n\
    \n    void apply(int left, int right, F f) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        if (left == right) return;\n        apply_impl(1,\
    \ 0, _size, left, right, left, f);\n    }\n    void apply_inplace(int index, F\
    \ f) { apply(index, std::move(f)); }\n    void apply_inplace(int left, int right,\
    \ F f) {\n        apply(left, right, std::move(f));\n    }\n\n    std::vector<T>\
    \ to_vector() {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T>\
    \ to_vector(int left, int right) {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        std::vector<T> result;\n        result.reserve(right\
    \ - left);\n        collect_impl(1, 0, _size, left, right, result);\n        return\
    \ result;\n    }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        int answer = _n;\n        max_right_impl(\n            1,\n         \
    \   0,\n            _size,\n            left,\n            predicate,\n      \
    \      product,\n            answer\n        );\n        return answer;\n    }\n\
    \n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        T product = ActedMonoid::id();\n \
    \       int answer = 0;\n        min_left_impl(\n            1,\n            0,\n\
    \            _size,\n            right,\n            predicate,\n            product,\n\
    \            answer\n        );\n        return answer;\n    }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { initialize({}); }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_BEATS_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_BEATS_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../beats_acted_monoid/concept.hpp\"\n#include \"../../math/bit_ceil.hpp\"\
    \n#include \"../detail/rollback_journal.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// Generic Segment Tree Beats for actions that may require recursive\
    \ descent.\ntemplate <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>\n\
    struct RollbackSegtreeBeats {\n    using value_type = typename ActedMonoid::value_type;\n\
    \    using operator_type = typename ActedMonoid::operator_type;\n    using T =\
    \ value_type;\n    using F = operator_type;\n\n   private:\n    int _n = 0;\n\
    \    int _size = 1;\n    struct Node {\n        T value = ActedMonoid::id();\n\
    \        F lazy = ActedMonoid::op_id();\n        bool has_lazy = false;\n    };\n\
    \n    detail::RollbackJournal<Node> _journal;\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ordinal) {\n        if constexpr (requires(F\
    \ g, T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n       \
    \ }) {\n            return ActedMonoid::mapping(f, value, ordinal);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static bool can_apply_at(const F& f, const T& value, long long ordinal)\
    \ {\n        if constexpr (requires(F g, T x, long long i) {\n            ActedMonoid::can_apply(g,\
    \ x, i);\n        }) {\n            return ActedMonoid::can_apply(f, value, ordinal);\n\
    \        } else {\n            return ActedMonoid::can_apply(f, value);\n    \
    \    }\n    }\n\n    static F shift_operator(const F& f, long long ordinal) {\n\
    \        if constexpr (requires(F g, long long i) {\n            ActedMonoid::op_shift(g,\
    \ i);\n        }) {\n            return ActedMonoid::op_shift(f, ordinal);\n \
    \       } else {\n            return f;\n        }\n    }\n\n    void initialize(std::vector<T>&&\
    \ values) {\n        _journal.clear();\n        _n = int(values.size());\n   \
    \     _size = int(m1une::math::bit_ceil((unsigned int)_n));\n        _journal.nodes.assign(2\
    \ * _size, Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n        for (int i = 0; i < _n; ++i) {\n            _journal[_size + i].value\
    \ = std::move(values[i]);\n        }\n        for (int k = _size - 1; k >= 1;\
    \ --k) update(k);\n    }\n\n    void update(int node) {\n        _journal.touch(node);\n\
    \        _journal[node].value = ActedMonoid::op(\n            _journal[node *\
    \ 2].value,\n            _journal[node * 2 + 1].value\n        );\n    }\n\n \
    \   void all_apply(int node, int left, int right, const F& f) {\n        if (_n\
    \ <= left) return;\n        if (can_apply_at(f, _journal[node].value, 0)) {\n\
    \            _journal.touch(node);\n            _journal[node].value = mapping_at(f,\
    \ _journal[node].value, 0);\n            if (node < _size) {\n               \
    \ _journal[node].lazy = ActedMonoid::op_comp(f, _journal[node].lazy);\n      \
    \          _journal[node].has_lazy = true;\n            }\n            return;\n\
    \        }\n\n        assert(right - left > 1);\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        all_apply(node * 2,\
    \ left, middle, f);\n        all_apply(\n            node * 2 + 1,\n         \
    \   middle,\n            right,\n            shift_operator(f, middle - left)\n\
    \        );\n        update(node);\n    }\n\n    void push(int node, int left,\
    \ int right) {\n        assert(right - left > 1);\n        if (!_journal[node].has_lazy)\
    \ return;\n        int middle = left + (right - left) / 2;\n        F f = _journal[node].lazy;\n\
    \        _journal.touch(node);\n        _journal[node].lazy = ActedMonoid::op_id();\n\
    \        _journal[node].has_lazy = false;\n        all_apply(node * 2, left, middle,\
    \ f);\n        all_apply(\n            node * 2 + 1,\n            middle,\n  \
    \          right,\n            shift_operator(f, middle - left)\n        );\n\
    \    }\n\n    void set_impl(\n        int node,\n        int left,\n        int\
    \ right,\n        int index,\n        T value\n    ) {\n        if (right - left\
    \ == 1) {\n            _journal.touch(node);\n            _journal[node].value\
    \ = std::move(value);\n            return;\n        }\n        push(node, left,\
    \ right);\n        int middle = left + (right - left) / 2;\n        if (index\
    \ < middle) {\n            set_impl(node * 2, left, middle, index, std::move(value));\n\
    \        } else {\n            set_impl(\n                node * 2 + 1,\n    \
    \            middle,\n                right,\n                index,\n       \
    \         std::move(value)\n            );\n        }\n        update(node);\n\
    \    }\n\n    T get_impl(int node, int left, int right, int index) {\n       \
    \ if (right - left == 1) return _journal[node].value;\n        push(node, left,\
    \ right);\n        int middle = left + (right - left) / 2;\n        if (index\
    \ < middle) {\n            return get_impl(node * 2, left, middle, index);\n \
    \       }\n        return get_impl(node * 2 + 1, middle, right, index);\n    }\n\
    \n    T prod_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_left,\n        int query_right\n    ) {\n        if (\n   \
    \         query_right <= left || right <= query_left || _n <= left\n        )\
    \ {\n            return ActedMonoid::id();\n        }\n        if (query_left\
    \ <= left && right <= query_right) {\n            return _journal[node].value;\n\
    \        }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_impl(\n    \
    \            node * 2,\n                left,\n                middle,\n     \
    \           query_left,\n                query_right\n            ),\n       \
    \     prod_impl(\n                node * 2 + 1,\n                middle,\n   \
    \             right,\n                query_left,\n                query_right\n\
    \            )\n        );\n    }\n\n    void apply_impl(\n        int node,\n\
    \        int left,\n        int right,\n        int query_left,\n        int query_right,\n\
    \        int base_left,\n        const F& f\n    ) {\n        if (\n         \
    \   query_right <= left || right <= query_left || _n <= left\n        ) {\n  \
    \          return;\n        }\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                node,\n                left,\n  \
    \              right,\n                shift_operator(f, left - base_left)\n \
    \           );\n            return;\n        }\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        apply_impl(\n      \
    \      node * 2,\n            left,\n            middle,\n            query_left,\n\
    \            query_right,\n            base_left,\n            f\n        );\n\
    \        apply_impl(\n            node * 2 + 1,\n            middle,\n       \
    \     right,\n            query_left,\n            query_right,\n            base_left,\n\
    \            f\n        );\n        update(node);\n    }\n\n    void collect_impl(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        std::vector<T>& result\n    ) {\n        if\
    \ (\n            query_right <= left || right <= query_left || _n <= left\n  \
    \      ) {\n            return;\n        }\n        if (right - left == 1) {\n\
    \            result.push_back(_journal[node].value);\n            return;\n  \
    \      }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        collect_impl(\n            node * 2,\n            left,\n\
    \            middle,\n            query_left,\n            query_right,\n    \
    \        result\n        );\n        collect_impl(\n            node * 2 + 1,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  query_right,\n            result\n        );\n    }\n\n    template <class\
    \ Predicate>\n    bool max_right_impl(\n        int node,\n        int left,\n\
    \        int right,\n        int query_left,\n        Predicate& predicate,\n\
    \        T& product,\n        int& answer\n    ) {\n        if (right <= query_left\
    \ || _n <= left) return true;\n        if (query_left <= left) {\n           \
    \ T next = ActedMonoid::op(product, _journal[node].value);\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return true;\n\
    \            }\n            if (right - left == 1) {\n                answer =\
    \ left;\n                return false;\n            }\n        }\n        push(node,\
    \ left, right);\n        int middle = left + (right - left) / 2;\n        if (!max_right_impl(\n\
    \                node * 2,\n                left,\n                middle,\n \
    \               query_left,\n                predicate,\n                product,\n\
    \                answer\n            )) {\n            return false;\n       \
    \ }\n        return max_right_impl(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            predicate,\n       \
    \     product,\n            answer\n        );\n    }\n\n    template <class Predicate>\n\
    \    bool min_left_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        Predicate& predicate,\n        T& product,\n\
    \        int& answer\n    ) {\n        if (query_right <= left || _n <= left)\
    \ return true;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(_journal[node].value,\
    \ product);\n            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return true;\n            }\n            if (right - left ==\
    \ 1) {\n                answer = right;\n                return false;\n     \
    \       }\n        }\n        push(node, left, right);\n        int middle = left\
    \ + (right - left) / 2;\n        if (!min_left_impl(\n                node * 2\
    \ + 1,\n                middle,\n                right,\n                query_right,\n\
    \                predicate,\n                product,\n                answer\n\
    \            )) {\n            return false;\n        }\n        return min_left_impl(\n\
    \            node * 2,\n            left,\n            middle,\n            query_right,\n\
    \            predicate,\n            product,\n            answer\n        );\n\
    \    }\n\n   public:\n    RollbackSegtreeBeats() {\n        initialize({});\n\
    \    }\n\n    explicit RollbackSegtreeBeats(int n) {\n        assert(0 <= n);\n\
    \        initialize(std::vector<T>(n, ActedMonoid::id()));\n    }\n\n    explicit\
    \ RollbackSegtreeBeats(const std::vector<T>& values) {\n        initialize(std::vector<T>(values));\n\
    \    }\n\n    explicit RollbackSegtreeBeats(std::vector<T>&& values) {\n     \
    \   initialize(std::move(values));\n    }\n\n    template <typename U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit RollbackSegtreeBeats(const std::vector<U>& values) {\n\
    \        std::vector<T> converted;\n        converted.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); ++i) {\n            if constexpr\
    \ (requires(U x) { ActedMonoid::make(x); }) {\n                converted.push_back(ActedMonoid::make(values[i]));\n\
    \            } else if constexpr (requires(U x, int index) {\n               \
    \ ActedMonoid::make(x, index);\n            }) {\n                converted.push_back(ActedMonoid::make(values[i],\
    \ i));\n            } else {\n                converted.push_back(static_cast<T>(values[i]));\n\
    \            }\n        }\n        initialize(std::move(converted));\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    std::size_t node_count() const { return\
    \ _journal.nodes.size(); }\n\n    void set(int index, T value) {\n        assert(0\
    \ <= index && index < _n);\n        set_impl(1, 0, _size, index, std::move(value));\n\
    \    }\n    void set_inplace(int index, T value) { set(index, std::move(value));\
    \ }\n\n    T get(int index) {\n        assert(0 <= index && index < _n);\n   \
    \     return get_impl(1, 0, _size, index);\n    }\n\n    T operator[](int index)\
    \ {\n        return get(index);\n    }\n\n    T prod(int left, int right) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ == right) return ActedMonoid::id();\n        return prod_impl(1, 0, _size, left,\
    \ right);\n    }\n\n    T all_prod() const {\n        return _journal[1].value;\n\
    \    }\n\n    void apply(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        apply_impl(1, 0, _size, index, index + 1, index, f);\n    }\n\
    \n    void apply(int left, int right, F f) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        if (left == right) return;\n        apply_impl(1,\
    \ 0, _size, left, right, left, f);\n    }\n    void apply_inplace(int index, F\
    \ f) { apply(index, std::move(f)); }\n    void apply_inplace(int left, int right,\
    \ F f) {\n        apply(left, right, std::move(f));\n    }\n\n    std::vector<T>\
    \ to_vector() {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T>\
    \ to_vector(int left, int right) {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        std::vector<T> result;\n        result.reserve(right\
    \ - left);\n        collect_impl(1, 0, _size, left, right, result);\n        return\
    \ result;\n    }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        int answer = _n;\n        max_right_impl(\n            1,\n         \
    \   0,\n            _size,\n            left,\n            predicate,\n      \
    \      product,\n            answer\n        );\n        return answer;\n    }\n\
    \n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        T product = ActedMonoid::id();\n \
    \       int answer = 0;\n        min_left_impl(\n            1,\n            0,\n\
    \            _size,\n            right,\n            predicate,\n            product,\n\
    \            answer\n        );\n        return answer;\n    }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { initialize({}); }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_BEATS_HPP\n"
  dependsOn:
  - beats_acted_monoid/concept.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - ds/detail/rollback_journal.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_segtree_beats.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_segtree_beats.hpp
layout: document
title: Rollback Segment Tree Beats
---

## Overview

`RollbackSegtreeBeats<ActedMonoid>` is a mutable Segment Tree Beats with registered snapshots. `ActedMonoid` must satisfy
`m1une::beats_acted_monoid::IsBeatsActedMonoid`; failed whole-node actions
descend exactly as in the mutable structure.

## Methods

Constructors and read-only product, materialization, boundary-search, and node-count methods follow `SegtreeBeats<ActedMonoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies a fallible action. | Acted-monoid dependent, amortized as for Segment Tree Beats |
| `void apply_inplace(...)` | Aliases of `apply`. | Same as `apply` |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a tree node is saved only before its first mutation.

## Example

```cpp
#include "beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "ds/segtree/rollback_segtree_beats.hpp"

#include <vector>

using AM = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;
m1une::ds::RollbackSegtreeBeats<AM> seg(
    std::vector<long long>{1, 5, 3}
);
int state = seg.snapshot();
AM::operator_type add;
add.add = 2;
add.lower = AM::negative_infinity;
add.upper = AM::positive_infinity;
seg.apply(0, 3, add);
seg.rollback(state);
assert(seg.all_prod().sum == 9);
```
