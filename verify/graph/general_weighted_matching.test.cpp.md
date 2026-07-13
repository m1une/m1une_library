---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/general_weighted_matching.hpp
    title: General Weighted Matching
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/general_weighted_matching
    links:
    - https://judge.yosupo.jp/problem/general_weighted_matching
  bundledCode: "#line 1 \"verify/graph/general_weighted_matching.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/general_weighted_matching\"\n\n#line\
    \ 1 \"graph/general_weighted_matching.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <functional>\n#include <limits>\n#include\
    \ <queue>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 15 \"graph/general_weighted_matching.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\nnamespace internal {\n\n// Primal-dual weighted blossom\
    \ algorithm using Gabow's event queues.\n// Reference: H. N. Gabow, \"Data Structures\
    \ for Weighted Matching and\n// Extensions to b-matching and f-factors\", 2016.\n\
    // Vertices 1..n are atoms; larger indices represent contracted blossoms.\ntemplate\
    \ <class Cost, class TotalCost>\nclass WeightedBlossomSolver {\n   public:\n \
    \   using cost_type = Cost;\n    using total_type = TotalCost;\n\n   private:\n\
    \    enum BlossomLabel : int {\n        separated_label = -2,\n        inner_label\
    \ = -1,\n        free_label = 0,\n        outer_label = 1\n    };\n    static\
    \ constexpr cost_type infinity = cost_type(1) << (sizeof(cost_type) * 8 - 2);\n\
    \n    template <class T>\n    class MutableBinaryHeap {\n       public:\n    \
    \    struct Node {\n            bool operator<(const Node& rhs) const {\n    \
    \            if (value < rhs.value) {\n                    return true;\n    \
    \            }\n                if (rhs.value < value) {\n                   \
    \ return false;\n                }\n                return id < rhs.id;\n    \
    \        }\n            T value;\n            int id;\n        };\n\n        MutableBinaryHeap()\
    \ = default;\n        explicit MutableBinaryHeap(int capacity) : _size(0), _nodes(capacity\
    \ + 1), _position(capacity, 0) {\n        }\n\n        bool empty() const {\n\
    \            return _size == 0;\n        }\n        void clear() {\n         \
    \   while (_size > 0) {\n                _position[_nodes[_size].id] = 0;\n  \
    \              _size--;\n            }\n        }\n        T min() const {\n \
    \           return _nodes[1].value;\n        }\n        int argmin() const {\n\
    \            return _nodes[1].id;\n        }\n        void pop() {\n         \
    \   if (_size > 0) pop(1);\n        }\n        void erase(int id) {\n        \
    \    if (_position[id]) pop(_position[id]);\n        }\n        bool has(int id)\
    \ const {\n            return _position[id] != 0;\n        }\n        void update(int\
    \ id, T v) {\n            if (!has(id)) return push(id, v);\n            bool\
    \ up = (v < _nodes[_position[id]].value);\n            _nodes[_position[id]].value\
    \ = v;\n            if (up) {\n                up_heap(_position[id]);\n     \
    \       } else {\n                down_heap(_position[id]);\n            }\n \
    \       }\n        void decrease_key(int id, T v) {\n            if (!has(id))\
    \ return push(id, v);\n            if (v < _nodes[_position[id]].value) {\n  \
    \              _nodes[_position[id]].value = v;\n                up_heap(_position[id]);\n\
    \            }\n        }\n        void push(int id, T v) {\n            _position[id]\
    \ = ++_size;\n            _nodes[_size] = {v, id};\n            up_heap(_size);\n\
    \        }\n\n       private:\n        void pop(int pos) {\n            _position[_nodes[pos].id]\
    \ = 0;\n            if (pos == _size) {\n                --_size;\n          \
    \      return;\n            }\n            bool up = (_nodes[_size].value < _nodes[pos].value);\n\
    \            _nodes[pos] = _nodes[_size--];\n            _position[_nodes[pos].id]\
    \ = pos;\n            if (up) {\n                up_heap(pos);\n            }\
    \ else {\n                down_heap(pos);\n            }\n        }\n        void\
    \ swap_node(int a, int b) {\n            std::swap(_nodes[a], _nodes[b]);\n  \
    \          _position[_nodes[a].id] = a;\n            _position[_nodes[b].id] =\
    \ b;\n        }\n        void down_heap(int pos) {\n            for (int current\
    \ = pos;;) {\n                int next = current;\n                if (2 * current\
    \ <= _size && _nodes[2 * current] < _nodes[next]) {\n                    next\
    \ = 2 * current;\n                }\n                if (2 * current + 1 <= _size\
    \ && _nodes[2 * current + 1] < _nodes[next]) {\n                    next = 2 *\
    \ current + 1;\n                }\n                if (next == current) break;\n\
    \                swap_node(current, next);\n                current = next;\n\
    \            }\n        }\n        void up_heap(int pos) {\n            for (int\
    \ current = pos; current > 1 && _nodes[current] < _nodes[current >> 1]; current\
    \ >>= 1) {\n                swap_node(current, current >> 1);\n            }\n\
    \        }\n        int _size;\n        std::vector<Node> _nodes;\n        std::vector<int>\
    \ _position;\n    };\n\n    template <class Key>\n    class DisjointPairingHeaps\
    \ {\n       private:\n        struct Node {\n            Node() : key(), child(0),\
    \ next(0), prev(-1) {\n            }\n            explicit Node(Key value) : key(value),\
    \ child(0), next(0), prev(0) {\n            }\n            Key key;\n        \
    \    int child;\n            int next;\n            int prev;\n        };\n\n\
    \       public:\n        DisjointPairingHeaps(int heap_count, int node_count)\
    \ : _roots(heap_count), _nodes(node_count) {\n        }\n\n        void clear(int\
    \ h) {\n            if (_roots[h]) {\n                clear_rec(_roots[h]);\n\
    \                _roots[h] = 0;\n            }\n        }\n        bool empty(int\
    \ h) const {\n            return !_roots[h];\n        }\n        bool used(int\
    \ v) const {\n            return _nodes[v].prev >= 0;\n        }\n        Key\
    \ min(int h) const {\n            return _nodes[_roots[h]].key;\n        }\n \
    \       void push(int h, int v, Key key) {\n            _nodes[v] = Node(key);\n\
    \            _roots[h] = merge(_roots[h], v);\n        }\n        void erase(int\
    \ h, int v) {\n            if (!used(v)) return;\n            int w = two_pass_pairing(_nodes[v].child);\n\
    \            if (!_nodes[v].prev) {\n                _roots[h] = w;\n        \
    \    } else {\n                cut(v);\n                _roots[h] = merge(_roots[h],\
    \ w);\n            }\n            _nodes[v].prev = -1;\n        }\n        void\
    \ decrease_key(int h, int v, Key key) {\n            if (!used(v)) return push(h,\
    \ v, key);\n            if (!_nodes[v].prev) {\n                _nodes[v].key\
    \ = key;\n            } else {\n                cut(v);\n                _nodes[v].key\
    \ = key;\n                _roots[h] = merge(_roots[h], v);\n            }\n  \
    \      }\n\n       private:\n        void clear_rec(int v) {\n            for\
    \ (; v; v = _nodes[v].next) {\n                if (_nodes[v].child) clear_rec(_nodes[v].child);\n\
    \                _nodes[v].prev = -1;\n            }\n        }\n\n        inline\
    \ void cut(int v) {\n            auto& n = _nodes[v];\n            int previous\
    \ = n.prev;\n            int next = n.next;\n            auto& previous_node =\
    \ _nodes[previous];\n            if (previous_node.child == v) {\n           \
    \     previous_node.child = next;\n            } else {\n                previous_node.next\
    \ = next;\n            }\n            _nodes[next].prev = previous;\n        \
    \    n.next = n.prev = 0;\n        }\n\n        int merge(int l, int r) {\n  \
    \          if (!l) return r;\n            if (!r) return l;\n            if (_nodes[l].key\
    \ > _nodes[r].key) std::swap(l, r);\n            int lc = _nodes[r].next = _nodes[l].child;\n\
    \            _nodes[l].child = _nodes[lc].prev = r;\n            return _nodes[r].prev\
    \ = l;\n        }\n\n        int two_pass_pairing(int root) {\n            if\
    \ (!root) return 0;\n            int a = root;\n            root = 0;\n      \
    \      while (a) {\n                int b = _nodes[a].next;\n                int\
    \ next_a = 0;\n                _nodes[a].prev = _nodes[a].next = 0;\n        \
    \        if (b) {\n                    next_a = _nodes[b].next;\n            \
    \        _nodes[b].prev = _nodes[b].next = 0;\n                }\n           \
    \     a = merge(a, b);\n                _nodes[a].next = root;\n             \
    \   root = a;\n                a = next_a;\n            }\n            int s =\
    \ _nodes[root].next;\n            _nodes[root].next = 0;\n            while (s)\
    \ {\n                int t = _nodes[s].next;\n                _nodes[s].next =\
    \ 0;\n                root = merge(root, s);\n                s = t;\n       \
    \     }\n            return root;\n        }\n\n       private:\n        std::vector<int>\
    \ _roots;\n        std::vector<Node> _nodes;\n    };\n\n    template <class T>\n\
    \    struct ReservablePriorityQueue : public std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> {\n        ReservablePriorityQueue() = default;\n        explicit\
    \ ReservablePriorityQueue(int capacity) {\n            this->c.reserve(capacity);\n\
    \        }\n        T min() const {\n            return this->top();\n       \
    \ }\n        void clear() {\n            this->c.clear();\n        }\n    };\n\
    \n    template <class T>\n    struct FixedQueue {\n        FixedQueue() = default;\n\
    \        explicit FixedQueue(int capacity) : _head(0), _tail(0), _data(capacity)\
    \ {\n        }\n        void enqueue(int u) {\n            _data[_tail++] = u;\n\
    \        }\n        int dequeue() {\n            return _data[_head++];\n    \
    \    }\n        bool empty() const {\n            return _head == _tail;\n   \
    \     }\n        void clear() {\n            _head = _tail = 0;\n        }\n \
    \       int _head = 0;\n        int _tail = 0;\n        std::vector<T> _data;\n\
    \    };\n\n   public:\n    struct InputEdge {\n        int from;\n        int\
    \ to;\n        cost_type cost;\n    };\n\n   private:\n    struct SolverEdge {\n\
    \        int to;\n        cost_type cost;\n    };\n\n    struct BlossomLink {\n\
    \        int from;\n        int to;\n    };\n\n    struct BlossomNode {\n    \
    \    struct CycleLink {\n            int blossom;\n            int vertex;\n \
    \       };\n\n        BlossomNode() = default;\n        explicit BlossomNode(int\
    \ vertex) : parent(0), size(1) {\n            cycle[0] = cycle[1] = CycleLink{vertex,\
    \ vertex};\n        }\n\n        int next_v() const {\n            return cycle[0].vertex;\n\
    \        }\n        int next_b() const {\n            return cycle[0].blossom;\n\
    \        }\n        int prev_v() const {\n            return cycle[1].vertex;\n\
    \        }\n        int prev_b() const {\n            return cycle[1].blossom;\n\
    \        }\n\n        int parent = 0;\n        int size = 0;\n        CycleLink\
    \ cycle[2];\n    };\n\n    struct VertexEvent {\n        VertexEvent() = default;\n\
    \        VertexEvent(cost_type event_time, int vertex) : time(event_time), id(vertex)\
    \ {\n        }\n\n        bool operator<(const VertexEvent& rhs) const {\n   \
    \         if (time < rhs.time) {\n                return true;\n            }\n\
    \            if (rhs.time < time) {\n                return false;\n         \
    \   }\n            return id < rhs.id;\n        }\n        bool operator>(const\
    \ VertexEvent& rhs) const {\n            return rhs < *this;\n        }\n\n  \
    \      cost_type time = cost_type();\n        int id = 0;\n    };\n\n    struct\
    \ EdgeEvent {\n        EdgeEvent() = default;\n        EdgeEvent(cost_type event_time,\
    \ int from_, int to_) : time(event_time), from(from_), to(to_) {\n        }\n\n\
    \        bool operator<(const EdgeEvent& rhs) const {\n            if (time <\
    \ rhs.time) {\n                return true;\n            }\n            if (time\
    \ > rhs.time) {\n                return false;\n            }\n            return\
    \ std::make_pair(from, to) < std::make_pair(rhs.from, rhs.to);\n        }\n  \
    \      bool operator>(const EdgeEvent& rhs) const {\n            return rhs <\
    \ *this;\n        }\n\n        cost_type time = cost_type();\n        int from\
    \ = 0;\n        int to = 0;\n    };\n\n   public:\n    WeightedBlossomSolver(int\
    \ n, const std::vector<InputEdge>& input_edges)\n        : _vertex_count(n),\n\
    \          _blossom_count((n - 1) / 2),\n          _state_count(n + _blossom_count\
    \ + 1),\n          _offset(n + 2),\n          _edges(input_edges.size() * 2),\n\
    \          _grow_heap(_state_count),\n          _blossom_grow_heaps(_state_count,\
    \ _state_count),\n          _contract_heap(int(_edges.size())),\n          _expand_heap(_state_count)\
    \ {\n        for (const InputEdge& edge : input_edges) {\n            _offset[edge.from\
    \ + 1]++;\n            _offset[edge.to + 1]++;\n        }\n        for (int i\
    \ = 1; i <= _vertex_count + 1; i++) _offset[i] += _offset[i - 1];\n        for\
    \ (const InputEdge& edge : input_edges) {\n            _edges[_offset[edge.from]++]\
    \ = SolverEdge{edge.to, edge.cost * 2};\n            _edges[_offset[edge.to]++]\
    \ = SolverEdge{edge.from, edge.cost * 2};\n        }\n        for (int i = _vertex_count\
    \ + 1; i > 0; i--) _offset[i] = _offset[i - 1];\n        _offset[0] = 0;\n   \
    \ }\n\n    total_type solve(std::vector<std::pair<int, int>>& matching) {\n  \
    \      initialize_state();\n        initialize_potentials();\n        for (int\
    \ vertex = 1; vertex <= _vertex_count; vertex++) {\n            if (_mate[vertex]\
    \ == 0) augment_from(vertex);\n        }\n\n        matching.clear();\n      \
    \  for (int vertex = 1; vertex <= _vertex_count; vertex++) {\n            if (_mate[vertex]\
    \ > vertex) matching.emplace_back(vertex, _mate[vertex]);\n        }\n       \
    \ return compute_matching_weight();\n    }\n\n   private:\n    total_type compute_matching_weight()\
    \ const {\n        total_type result = 0;\n        for (int vertex = 1; vertex\
    \ <= _vertex_count; vertex++) {\n            if (_mate[vertex] > vertex) {\n \
    \               cost_type best_cost = 0;\n                for (int edge_id = _offset[vertex];\
    \ edge_id < _offset[vertex + 1]; edge_id++) {\n                    if (_edges[edge_id].to\
    \ == _mate[vertex]) {\n                        best_cost = std::max(best_cost,\
    \ _edges[edge_id].cost);\n                    }\n                }\n         \
    \       result += best_cost;\n            }\n        }\n        return result\
    \ >> 1;\n    }\n\n    total_type reduced_cost(int from, int to, const SolverEdge&\
    \ edge) const {\n        return total_type(_potential[from]) + _potential[to]\
    \ - edge.cost;\n    }\n\n    void rematch(int vertex, int new_mate) {\n      \
    \  int old_mate = _mate[vertex];\n        _mate[vertex] = new_mate;\n        if\
    \ (_mate[old_mate] != vertex) return;\n        if (_tree_link[vertex].to == _surface[_tree_link[vertex].to])\
    \ {\n            _mate[old_mate] = _tree_link[vertex].from;\n            rematch(_mate[old_mate],\
    \ old_mate);\n        } else {\n            int from = _tree_link[vertex].from;\n\
    \            int to = _tree_link[vertex].to;\n            rematch(from, to);\n\
    \            rematch(to, from);\n        }\n    }\n\n    void repair_matching(int\
    \ blossom) {\n        if (blossom <= _vertex_count) return;\n        int child\
    \ = _base[blossom];\n        int first_vertex = _nodes[child].cycle[0].vertex;\n\
    \        int first_neighbor = _nodes[child].cycle[0].blossom;\n        int direction\
    \ = (_nodes[first_neighbor].cycle[1].vertex == _mate[first_vertex]) ? 0 : 1;\n\
    \        while (true) {\n            int matched_vertex = _nodes[child].cycle[direction].vertex;\n\
    \            int matched_child = _nodes[child].cycle[direction].blossom;\n   \
    \         if (_nodes[matched_child].cycle[1 ^ direction].vertex != _mate[matched_vertex])\
    \ break;\n            repair_matching(child);\n            repair_matching(matched_child);\n\
    \            child = _nodes[matched_child].cycle[direction].blossom;\n       \
    \ }\n        _base[blossom] = child;\n        repair_matching(child);\n      \
    \  _mate[blossom] = _mate[child];\n    }\n\n    void reset_clock() {\n       \
    \ _time = 0;\n        _vertex_event = {infinity, 0};\n    }\n\n    void reset_blossom(int\
    \ blossom) {\n        _label[blossom] = free_label;\n        _tree_link[blossom].from\
    \ = 0;\n        _slack[blossom] = infinity;\n        _lazy[blossom] = 0;\n   \
    \ }\n\n    void reset_search_state() {\n        _label[0] = free_label;\n    \
    \    _tree_link[0].from = 0;\n        for (int vertex = 1; vertex <= _vertex_count;\
    \ vertex++) {\n            if (_label[vertex] == outer_label) {\n            \
    \    _potential[vertex] -= _time;\n            } else {\n                int blossom\
    \ = _surface[vertex];\n                _potential[vertex] += _lazy[blossom];\n\
    \                if (_label[blossom] == inner_label) {\n                    _potential[vertex]\
    \ += _time - _created_at[blossom];\n                }\n            }\n       \
    \     reset_blossom(vertex);\n        }\n        int remaining_blossoms = _blossom_count\
    \ - _unused_count;\n        for (int blossom = _vertex_count + 1; remaining_blossoms\
    \ > 0 && blossom < _state_count; blossom++) {\n            if (_base[blossom]\
    \ != blossom) {\n                if (_surface[blossom] == blossom) {\n       \
    \             repair_matching(blossom);\n                    if (_label[blossom]\
    \ == outer_label) {\n                        _potential[blossom] += (_time - _created_at[blossom])\
    \ << 1;\n                    } else if (_label[blossom] == inner_label) {\n  \
    \                      materialize_potential<inner_label>(blossom);\n        \
    \            } else {\n                        materialize_potential<free_label>(blossom);\n\
    \                    }\n                }\n                _blossom_grow_heaps.clear(blossom);\n\
    \                reset_blossom(blossom);\n                remaining_blossoms--;\n\
    \            }\n        }\n\n        _queue.clear();\n        reset_clock();\n\
    \        _grow_heap.clear();\n        _contract_heap.clear();\n        _expand_heap.clear();\n\
    \    }\n\n    void augment_from(int root) {\n        if (_potential[root] == 0)\
    \ return;\n        link_blossom(_surface[root], {0, 0});\n        make_outer(_surface[root],\
    \ 0);\n        for (bool augmented = false; !augmented;) {\n            augmented\
    \ = scan_tight_edges(root);\n            if (augmented) break;\n            augmented\
    \ = advance_dual(root);\n        }\n        reset_search_state();\n    }\n\n \
    \   template <BlossomLabel target_label>\n    cost_type materialize_potential(int\
    \ blossom) {\n        cost_type delta = _lazy[blossom];\n        _lazy[blossom]\
    \ = 0;\n        if (target_label == inner_label) {\n            cost_type elapsed\
    \ = _time - _created_at[blossom];\n            if (blossom > _vertex_count) _potential[blossom]\
    \ -= elapsed << 1;\n            delta += elapsed;\n        }\n        return delta;\n\
    \    }\n\n    template <BlossomLabel target_label>\n    void update_grow_event(int\
    \ from, int to, int to_blossom, cost_type slack) {\n        if (slack >= _slack[to])\
    \ return;\n        _slack[to] = slack;\n        _best_from[to] = from;\n     \
    \   if (to == to_blossom) {\n            if (target_label != inner_label) {\n\
    \                _grow_heap.decrease_key(to, EdgeEvent(slack + _lazy[to], from,\
    \ to));\n            }\n        } else {\n            int to_group = _group[to];\n\
    \            if (to_group != to) {\n                if (slack >= _slack[to_group])\
    \ return;\n                _slack[to_group] = slack;\n            }\n        \
    \    _blossom_grow_heaps.decrease_key(to_blossom, to_group, EdgeEvent(slack, from,\
    \ to));\n            if (target_label == inner_label) return;\n            EdgeEvent\
    \ event = _blossom_grow_heaps.min(to_blossom);\n            _grow_heap.decrease_key(to_blossom,\n\
    \                                    EdgeEvent(event.time + _lazy[to_blossom],\
    \ event.from, event.to));\n        }\n    }\n\n    void activate_grow_event(int\
    \ blossom) {\n        if (blossom <= _vertex_count) {\n            if (_slack[blossom]\
    \ < infinity) {\n                _grow_heap.push(blossom,\n                  \
    \              EdgeEvent(_slack[blossom] + _lazy[blossom], _best_from[blossom],\
    \ blossom));\n            }\n        } else {\n            if (_blossom_grow_heaps.empty(blossom))\
    \ return;\n            EdgeEvent event = _blossom_grow_heaps.min(blossom);\n \
    \           _grow_heap.push(blossom, EdgeEvent(event.time + _lazy[blossom], event.from,\
    \ event.to));\n        }\n    }\n\n    void swap_blossoms(int a, int b) {\n  \
    \      // b is a maximal blossom.\n        std::swap(_base[a], _base[b]);\n  \
    \      if (_base[a] == a) _base[a] = b;\n        std::swap(_heavy[a], _heavy[b]);\n\
    \        if (_heavy[a] == a) _heavy[a] = b;\n        std::swap(_tree_link[a],\
    \ _tree_link[b]);\n        std::swap(_mate[a], _mate[b]);\n        std::swap(_potential[a],\
    \ _potential[b]);\n        std::swap(_lazy[a], _lazy[b]);\n        std::swap(_created_at[a],\
    \ _created_at[b]);\n        for (int direction = 0; direction < 2; direction++)\
    \ {\n            int child = _nodes[a].cycle[direction].blossom;\n           \
    \ _nodes[child].cycle[1 ^ direction].blossom = b;\n        }\n        std::swap(_nodes[a],\
    \ _nodes[b]);\n    }\n\n    void assign_surface(int blossom, int surface, int\
    \ group) {\n        _surface[blossom] = surface;\n        _group[blossom] = group;\n\
    \        if (blossom <= _vertex_count) return;\n        for (int child = _base[blossom];\
    \ _surface[child] != surface; child = _nodes[child].next_b()) {\n            assign_surface(child,\
    \ surface, group);\n        }\n    }\n\n    void merge_blossom_children(int blossom)\
    \ {\n        int largest_child = blossom;\n        int largest_size = 1;\n   \
    \     int first_child = _base[blossom];\n        for (int child = first_child;;\
    \ child = _nodes[child].next_b()) {\n            if (_nodes[child].size > largest_size)\
    \ {\n                largest_size = _nodes[child].size;\n                largest_child\
    \ = child;\n            }\n            if (_nodes[child].next_b() == first_child)\
    \ break;\n        }\n        for (int child = first_child;; child = _nodes[child].next_b())\
    \ {\n            if (child != largest_child) assign_surface(child, largest_child,\
    \ child);\n            if (_nodes[child].next_b() == first_child) break;\n   \
    \     }\n        _group[largest_child] = largest_child;\n        if (largest_size\
    \ > 1) {\n            _surface[blossom] = _heavy[blossom] = largest_child;\n \
    \           swap_blossoms(largest_child, blossom);\n        } else {\n       \
    \     _heavy[blossom] = 0;\n        }\n    }\n\n    void contract_blossom(int\
    \ x, int y, int edge_id) {\n        int x_blossom = _surface[x];\n        int\
    \ y_blossom = _surface[y];\n        assert(x_blossom != y_blossom);\n        const\
    \ int visit_mark = -(edge_id + 1);\n        _tree_link[_surface[_mate[x_blossom]]].from\
    \ = visit_mark;\n        _tree_link[_surface[_mate[y_blossom]]].from = visit_mark;\n\
    \n        int lca = -1;\n        while (true) {\n            if (_mate[y_blossom]\
    \ != 0) std::swap(x_blossom, y_blossom);\n            x_blossom = lca = _surface[_tree_link[x_blossom].from];\n\
    \            if (_tree_link[_surface[_mate[x_blossom]]].from == visit_mark) break;\n\
    \            _tree_link[_surface[_mate[x_blossom]]].from = visit_mark;\n     \
    \   }\n\n        const int blossom = _unused_blossoms[--_unused_count];\n    \
    \    assert(_unused_count >= 0);\n        int tree_size = 0;\n        for (int\
    \ direction = 0; direction < 2; direction++) {\n            for (int child = _surface[x];\
    \ child != lca;) {\n                int matched_vertex = _mate[child];\n     \
    \           int matched_child = _surface[matched_vertex];\n                int\
    \ vertex = _mate[matched_vertex];\n                int link_from = _tree_link[vertex].from;\n\
    \                int link_to = _tree_link[vertex].to;\n                tree_size\
    \ += _nodes[child].size + _nodes[matched_child].size;\n                _tree_link[matched_vertex]\
    \ = {x, y};\n\n                if (child > _vertex_count) {\n                \
    \    _potential[child] += (_time - _created_at[child]) << 1;\n               \
    \ }\n                if (matched_child > _vertex_count) _expand_heap.erase(matched_child);\n\
    \                make_outer(matched_child, materialize_potential<inner_label>(matched_child));\n\
    \n                _nodes[child].cycle[direction] = {matched_child, matched_vertex};\n\
    \                _nodes[matched_child].cycle[1 ^ direction] = {child, vertex};\n\
    \                child = _surface[link_from];\n                _nodes[matched_child].cycle[direction]\
    \ = {child, link_from};\n                _nodes[child].cycle[1 ^ direction] =\
    \ {matched_child, link_to};\n            }\n            _nodes[_surface[x]].cycle[1\
    \ ^ direction] = {_surface[y], y};\n            std::swap(x, y);\n        }\n\
    \        if (lca > _vertex_count) _potential[lca] += (_time - _created_at[lca])\
    \ << 1;\n        _nodes[blossom].size = tree_size + _nodes[lca].size;\n      \
    \  _base[blossom] = lca;\n        _tree_link[blossom] = _tree_link[lca];\n   \
    \     _mate[blossom] = _mate[lca];\n        _label[blossom] = outer_label;\n \
    \       _surface[blossom] = blossom;\n        _created_at[blossom] = _time;\n\
    \        _potential[blossom] = 0;\n        _lazy[blossom] = 0;\n\n        merge_blossom_children(blossom);\n\
    \    }\n\n    void link_blossom(int blossom, BlossomLink link) {\n        _tree_link[blossom]\
    \ = link;\n        if (blossom <= _vertex_count) return;\n        int first_child\
    \ = _base[blossom];\n        link_blossom(first_child, link);\n        int previous_child\
    \ = _nodes[first_child].prev_b();\n        link = {_nodes[previous_child].next_v(),\
    \ _nodes[first_child].prev_v()};\n        for (int child = first_child;;) {\n\
    \            int next_child = _nodes[child].next_b();\n            if (next_child\
    \ == first_child) break;\n            link_blossom(next_child, link);\n      \
    \      BlossomLink next_link = {_nodes[next_child].prev_v(), _nodes[child].next_v()};\n\
    \            child = _nodes[next_child].next_b();\n            link_blossom(child,\
    \ next_link);\n        }\n    }\n\n    void make_outer(int blossom, cost_type\
    \ delta) {\n        _label[blossom] = outer_label;\n        if (blossom > _vertex_count)\
    \ {\n            for (int child = _base[blossom]; _label[child] != outer_label;\
    \ child = _nodes[child].next_b()) {\n                make_outer(child, delta);\n\
    \            }\n        } else {\n            _potential[blossom] += _time + delta;\n\
    \            if (_potential[blossom] < _vertex_event.time) {\n               \
    \ _vertex_event = {_potential[blossom], blossom};\n            }\n           \
    \ _queue.enqueue(blossom);\n        }\n    }\n\n    bool grow_tree(int from, int\
    \ to) {\n        int inner_blossom = _surface[to];\n        bool visited = (_label[inner_blossom]\
    \ != free_label);\n        if (!visited) link_blossom(inner_blossom, {0, 0});\n\
    \        _label[inner_blossom] = inner_label;\n        _created_at[inner_blossom]\
    \ = _time;\n        _grow_heap.erase(inner_blossom);\n        if (to != inner_blossom)\
    \ {\n            _expand_heap.update(inner_blossom, _time + (_potential[inner_blossom]\
    \ >> 1));\n        }\n        int matched_vertex = _mate[inner_blossom];\n   \
    \     if (matched_vertex == 0) {\n            rematch(from, to);\n           \
    \ rematch(to, from);\n            return true;\n        }\n        int outer_blossom\
    \ = _surface[matched_vertex];\n        if (!visited) {\n            link_blossom(outer_blossom,\
    \ {from, to});\n        } else {\n            _tree_link[outer_blossom] = _tree_link[matched_vertex]\
    \ = {from, to};\n        }\n        make_outer(outer_blossom, materialize_potential<free_label>(outer_blossom));\n\
    \        _created_at[outer_blossom] = _time;\n        _grow_heap.erase(outer_blossom);\n\
    \        return false;\n    }\n\n    void release_blossom(int blossom) {\n   \
    \     _unused_blossoms[_unused_count++] = blossom;\n        _base[blossom] = blossom;\n\
    \    }\n\n    int recompute_slack(int blossom, int group) {\n        if (blossom\
    \ <= _vertex_count) {\n            if (_slack[blossom] >= _slack[group]) return\
    \ 0;\n            _slack[group] = _slack[blossom];\n            _best_from[group]\
    \ = _best_from[blossom];\n            return blossom;\n        }\n        int\
    \ destination = 0;\n        int first_child = _base[blossom];\n        for (int\
    \ child = first_child;; child = _nodes[child].next_b()) {\n            int candidate\
    \ = recompute_slack(child, group);\n            if (candidate != 0) destination\
    \ = candidate;\n            if (_nodes[child].next_b() == first_child) break;\n\
    \        }\n        return destination;\n    }\n\n    void rebuild_components(int\
    \ blossom, int surface, int group) {\n        _surface[blossom] = surface;\n \
    \       _group[blossom] = group;\n        if (blossom <= _vertex_count) return;\n\
    \        for (int child = _base[blossom]; _surface[child] != surface; child =\
    \ _nodes[child].next_b()) {\n            if (child == _heavy[blossom]) {\n   \
    \             rebuild_components(child, surface, group);\n            } else {\n\
    \                assign_surface(child, surface, child);\n                int destination\
    \ = 0;\n                if (child > _vertex_count) {\n                    _slack[child]\
    \ = infinity;\n                    destination = recompute_slack(child, child);\n\
    \                } else if (_slack[child] < infinity) {\n                    destination\
    \ = child;\n                }\n                if (destination > 0) {\n      \
    \              _blossom_grow_heaps.push(surface, child,\n                    \
    \                         EdgeEvent(_slack[child], _best_from[child], destination));\n\
    \                }\n            }\n        }\n    }\n\n    void promote_largest_child(int\
    \ blossom) {\n        int largest_child = _heavy[blossom];\n        cost_type\
    \ delta = (_time - _created_at[blossom]) + _lazy[blossom];\n        _lazy[blossom]\
    \ = 0;\n        int first_child = _base[blossom];\n        for (int child = first_child;;\
    \ child = _nodes[child].next_b()) {\n            _created_at[child] = _time;\n\
    \            _lazy[child] = delta;\n            if (child != largest_child) {\n\
    \                rebuild_components(child, child, child);\n                _blossom_grow_heaps.erase(blossom,\
    \ child);\n            }\n            if (_nodes[child].next_b() == first_child)\
    \ break;\n        }\n        if (largest_child > 0) {\n            swap_blossoms(largest_child,\
    \ blossom);\n            blossom = largest_child;\n        }\n        release_blossom(blossom);\n\
    \    }\n\n    void expand_blossom(int blossom) {\n        int matched_vertex =\
    \ _mate[_base[blossom]];\n        promote_largest_child(blossom);\n        BlossomLink\
    \ old_link = _tree_link[matched_vertex];\n        int old_base = _surface[_mate[matched_vertex]];\n\
    \        int root = _surface[old_link.to];\n        int direction = (_mate[root]\
    \ == _nodes[root].cycle[0].vertex) ? 1 : 0;\n        for (int child = _nodes[old_base].cycle[direction\
    \ ^ 1].blossom; child != root;) {\n            _label[child] = separated_label;\n\
    \            activate_grow_event(child);\n            child = _nodes[child].cycle[direction\
    \ ^ 1].blossom;\n            _label[child] = separated_label;\n            activate_grow_event(child);\n\
    \            child = _nodes[child].cycle[direction ^ 1].blossom;\n        }\n\
    \        for (int child = old_base;; child = _nodes[child].cycle[direction].blossom)\
    \ {\n            _label[child] = inner_label;\n            int next_child = _nodes[child].cycle[direction].blossom;\n\
    \            if (child == root) {\n                _tree_link[_mate[child]] =\
    \ old_link;\n            } else {\n                _tree_link[_mate[child]] =\
    \ {_nodes[child].cycle[direction].vertex,\n                                  \
    \          _nodes[next_child].cycle[direction ^ 1].vertex};\n            }\n \
    \           _tree_link[_surface[_mate[child]]] = _tree_link[_mate[child]];\n \
    \           if (child > _vertex_count) {\n                if (_potential[child]\
    \ == 0) {\n                    expand_blossom(child);\n                } else\
    \ {\n                    _expand_heap.push(child, _time + (_potential[child] >>\
    \ 1));\n                }\n            }\n            if (child == root) break;\n\
    \            child = next_child;\n            make_outer(next_child, materialize_potential<inner_label>(next_child));\n\
    \        }\n    }\n\n    bool scan_tight_edges(int root) {\n        while (!_queue.empty())\
    \ {\n            int from = _queue.dequeue();\n            int from_blossom =\
    \ _surface[from];\n            if (_potential[from] == _time) {\n            \
    \    if (from != root) rematch(from, 0);\n                return true;\n     \
    \       }\n            for (int edge_id = _offset[from]; edge_id < _offset[from\
    \ + 1]; edge_id++) {\n                const SolverEdge& edge = _edges[edge_id];\n\
    \                int to = edge.to;\n                int to_blossom = _surface[to];\n\
    \                if (from_blossom == to_blossom) continue;\n                BlossomLabel\
    \ to_label = _label[to_blossom];\n                if (to_label == outer_label)\
    \ {\n                    cost_type event_time = cost_type(reduced_cost(from, to,\
    \ edge) >> 1);\n                    if (event_time == _time) {\n             \
    \           contract_blossom(from, to, edge_id);\n                        from_blossom\
    \ = _surface[from];\n                    } else if (event_time < _vertex_event.time)\
    \ {\n                        _contract_heap.emplace(event_time, from, edge_id);\n\
    \                    }\n                } else {\n                    total_type\
    \ event_time = reduced_cost(from, to, edge);\n                    if (event_time\
    \ >= infinity) continue;\n                    if (to_label != inner_label) {\n\
    \                        if (cost_type(event_time) + _lazy[to_blossom] == _time)\
    \ {\n                            if (grow_tree(from, to)) return true;\n     \
    \                   } else {\n                            update_grow_event<free_label>(from,\
    \ to, to_blossom, cost_type(event_time));\n                        }\n       \
    \             } else if (_mate[from] != to) {\n                        update_grow_event<inner_label>(from,\
    \ to, to_blossom, cost_type(event_time));\n                    }\n           \
    \     }\n            }\n        }\n        return false;\n    }\n\n    bool advance_dual(int\
    \ root) {\n        cost_type rematch_time = _vertex_event.time;\n        cost_type\
    \ grow_time = infinity;\n        if (!_grow_heap.empty()) grow_time = _grow_heap.min().time;\n\
    \n        cost_type contract_time = infinity;\n        while (!_contract_heap.empty())\
    \ {\n            EdgeEvent event = _contract_heap.min();\n            int from\
    \ = event.from;\n            int to = _edges[event.to].to;\n            if (_surface[from]\
    \ != _surface[to]) {\n                contract_time = event.time;\n          \
    \      break;\n            } else {\n                _contract_heap.pop();\n \
    \           }\n        }\n\n        cost_type expand_time = infinity;\n      \
    \  if (!_expand_heap.empty()) expand_time = _expand_heap.min();\n\n        cost_type\
    \ next_time =\n            std::min(std::min(rematch_time, grow_time), std::min(contract_time,\
    \ expand_time));\n        assert(_time <= next_time && next_time < infinity);\n\
    \        _time = next_time;\n\n        if (_time == _vertex_event.time) {\n  \
    \          int x = _vertex_event.id;\n            if (x != root) rematch(x, 0);\n\
    \            return true;\n        }\n        while (!_grow_heap.empty() && _grow_heap.min().time\
    \ == _time) {\n            int from = _grow_heap.min().from;\n            int\
    \ to = _grow_heap.min().to;\n            if (grow_tree(from, to)) return true;\n\
    \        }\n        while (!_contract_heap.empty() && _contract_heap.min().time\
    \ == _time) {\n            int from = _contract_heap.min().from;\n           \
    \ int edge_id = _contract_heap.min().to;\n            int to = _edges[edge_id].to;\n\
    \            _contract_heap.pop();\n            if (_surface[from] == _surface[to])\
    \ continue;\n            contract_blossom(from, to, edge_id);\n        }\n   \
    \     while (!_expand_heap.empty() && _expand_heap.min() == _time) {\n       \
    \     int blossom = _expand_heap.argmin();\n            _expand_heap.pop();\n\
    \            expand_blossom(blossom);\n        }\n        return false;\n    }\n\
    \n   private:\n    void initialize_state() {\n        _queue = FixedQueue<int>(_vertex_count);\n\
    \        _mate.assign(_state_count, 0);\n        _tree_link.assign(_state_count,\
    \ {0, 0});\n        _label.assign(_state_count, free_label);\n        _base.resize(_state_count);\n\
    \        for (int state = 1; state < _state_count; state++) _base[state] = state;\n\
    \        _surface.resize(_state_count);\n        for (int state = 1; state < _state_count;\
    \ state++) _surface[state] = state;\n\n        _potential.resize(_state_count);\n\
    \        _nodes.resize(_state_count);\n        for (int state = 1; state < _state_count;\
    \ state++) {\n            _nodes[state] = BlossomNode(state);\n        }\n\n \
    \       _unused_blossoms.resize(_blossom_count);\n        for (int i = 0; i <\
    \ _blossom_count; i++) {\n            _unused_blossoms[i] = _vertex_count + _blossom_count\
    \ - i;\n        }\n        _unused_count = _blossom_count;\n\n        reset_clock();\n\
    \        _created_at.resize(_state_count);\n        _slack.assign(_state_count,\
    \ infinity);\n        _best_from.assign(_state_count, 0);\n        _heavy.assign(_state_count,\
    \ 0);\n        _lazy.assign(_state_count, 0);\n        _group.resize(_state_count);\n\
    \        for (int state = 0; state < _state_count; state++) _group[state] = state;\n\
    \    }\n\n    void initialize_potentials() {\n        for (int vertex = 1; vertex\
    \ <= _vertex_count; vertex++) {\n            cost_type maximum_cost = 0;\n   \
    \         for (int edge_id = _offset[vertex]; edge_id < _offset[vertex + 1]; edge_id++)\
    \ {\n                maximum_cost = std::max(maximum_cost, _edges[edge_id].cost);\n\
    \            }\n            _potential[vertex] = maximum_cost >> 1;\n        }\n\
    \    }\n\n    const int _vertex_count;\n    const int _blossom_count;\n    const\
    \ int _state_count;\n    std::vector<int> _offset;\n    std::vector<SolverEdge>\
    \ _edges;\n\n    FixedQueue<int> _queue;\n    std::vector<int> _mate;\n    std::vector<int>\
    \ _surface;\n    std::vector<int> _base;\n    std::vector<BlossomLink> _tree_link;\n\
    \    std::vector<BlossomLabel> _label;\n    std::vector<cost_type> _potential;\n\
    \n    std::vector<int> _unused_blossoms;\n    int _unused_count;\n    std::vector<BlossomNode>\
    \ _nodes;\n\n    // Heavy children and event queues keep each search phase at\
    \ O(m log n).\n    std::vector<int> _heavy;\n    std::vector<int> _group;\n  \
    \  std::vector<cost_type> _created_at;\n    std::vector<cost_type> _lazy;\n  \
    \  std::vector<cost_type> _slack;\n    std::vector<int> _best_from;\n\n    cost_type\
    \ _time;\n    VertexEvent _vertex_event;\n    MutableBinaryHeap<EdgeEvent> _grow_heap;\n\
    \    DisjointPairingHeaps<EdgeEvent> _blossom_grow_heaps;\n    ReservablePriorityQueue<EdgeEvent>\
    \ _contract_heap;\n    MutableBinaryHeap<cost_type> _expand_heap;\n};\n\n}  //\
    \ namespace internal\n\ntemplate <class Cost, class TotalCost = Cost>\nstruct\
    \ GeneralWeightedMatching {\n    static_assert(std::is_integral_v<Cost> && std::is_signed_v<Cost>);\n\
    \    static_assert(std::is_integral_v<TotalCost> && std::is_signed_v<TotalCost>);\n\
    \n    struct Edge {\n        int from;\n        int to;\n        Cost cost;\n\
    \        int id;\n        bool alive;\n\n        int other(int vertex) const {\n\
    \            assert(vertex == from || vertex == to);\n            return from\
    \ ^ to ^ vertex;\n        }\n    };\n\n    struct Pair {\n        int from;\n\
    \        int to;\n        Cost cost;\n        int edge_id;\n    };\n\n   private:\n\
    \    int _n;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<int> _mate;\n    std::vector<int> _mate_edge;\n    TotalCost\
    \ _matching_weight;\n    bool _calculated;\n\n    void invalidate() {\n      \
    \  _calculated = false;\n    }\n\n    void ensure_matching() {\n        if (!_calculated)\
    \ max_weight_matching();\n    }\n\n   public:\n    GeneralWeightedMatching() :\
    \ GeneralWeightedMatching(0) {\n    }\n\n    explicit GeneralWeightedMatching(int\
    \ n)\n        : _n(n), _adj(n), _mate(n, -1), _mate_edge(n, -1), _matching_weight(),\
    \ _calculated(false) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int edge_count() const {\n        return\
    \ int(_edges.size());\n    }\n\n    int add_edge(int from, int to, Cost cost)\
    \ {\n        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(from != to);\n        assert(cost <= std::numeric_limits<Cost>::max()\
    \ / Cost(2));\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, cost, id, true});\n        _adj[from].push_back(id);\n        _adj[to].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int id)\
    \ const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id];\n    }\n\n    std::vector<Edge> edges(bool include_inactive = false)\
    \ const {\n        std::vector<Edge> result;\n        result.reserve(_edges.size());\n\
    \        for (const Edge& edge : _edges) {\n            if (include_inactive ||\
    \ edge.alive) result.push_back(edge);\n        }\n        return result;\n   \
    \ }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0 <= id &&\
    \ id < int(_edges.size()));\n        _edges[id].alive = alive;\n        invalidate();\n\
    \    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < int(_edges.size()));\n        return _edges[id].alive;\n    }\n\n    TotalCost\
    \ max_weight_matching() {\n        using Solver = internal::WeightedBlossomSolver<Cost,\
    \ TotalCost>;\n        std::vector<typename Solver::InputEdge> input;\n      \
    \  input.reserve(_edges.size());\n        for (const Edge& edge : _edges) {\n\
    \            if (!edge.alive || edge.cost <= Cost()) continue;\n            input.push_back(typename\
    \ Solver::InputEdge{edge.from + 1, edge.to + 1, edge.cost});\n        }\n\n  \
    \      Solver solver(_n, input);\n        std::vector<std::pair<int, int>> vertex_pairs;\n\
    \        solver.solve(vertex_pairs);\n\n        _mate.assign(_n, -1);\n      \
    \  _mate_edge.assign(_n, -1);\n        _matching_weight = TotalCost();\n     \
    \   for (auto [one_based_from, one_based_to] : vertex_pairs) {\n            int\
    \ from = one_based_from - 1;\n            int to = one_based_to - 1;\n       \
    \     int best_edge = -1;\n            for (int id : _adj[from]) {\n         \
    \       const Edge& edge = _edges[id];\n                if (!edge.alive || edge.other(from)\
    \ != to || edge.cost <= Cost()) continue;\n                if (best_edge == -1\
    \ || _edges[best_edge].cost < edge.cost) best_edge = id;\n            }\n    \
    \        assert(best_edge != -1);\n            _mate[from] = to;\n           \
    \ _mate[to] = from;\n            _mate_edge[from] = best_edge;\n            _mate_edge[to]\
    \ = best_edge;\n            _matching_weight += static_cast<TotalCost>(_edges[best_edge].cost);\n\
    \        }\n\n        _calculated = true;\n        return _matching_weight;\n\
    \    }\n\n    TotalCost matching_weight() {\n        ensure_matching();\n    \
    \    return _matching_weight;\n    }\n\n    int matching_size() {\n        ensure_matching();\n\
    \        int result = 0;\n        for (int vertex = 0; vertex < _n; vertex++)\
    \ {\n            if (vertex < _mate[vertex]) result++;\n        }\n        return\
    \ result;\n    }\n\n    std::vector<int> mate() {\n        ensure_matching();\n\
    \        return _mate;\n    }\n\n    std::vector<int> mate_edge() {\n        ensure_matching();\n\
    \        return _mate_edge;\n    }\n\n    std::vector<Pair> matching() {\n   \
    \     ensure_matching();\n        std::vector<Pair> result;\n        for (int\
    \ vertex = 0; vertex < _n; vertex++) {\n            if (vertex < _mate[vertex])\
    \ {\n                int id = _mate_edge[vertex];\n                result.push_back(Pair{vertex,\
    \ _mate[vertex], _edges[id].cost, id});\n            }\n        }\n        return\
    \ result;\n    }\n};\n\ntemplate <class Cost, class TotalCost = Cost>\nstruct\
    \ GeneralWeightedMatchingGraph {\n    GeneralWeightedMatching<Cost, TotalCost>\
    \ matching;\n    std::vector<int> original_edge_id;\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    GeneralWeightedMatchingGraph<T> make_general_weighted_matching(const Graph<T>&\
    \ graph) {\n    GeneralWeightedMatchingGraph<T> result;\n    result.matching =\
    \ GeneralWeightedMatching<T>(graph.size());\n    for (const auto& edge : graph.edges())\
    \ {\n        int id = result.matching.add_edge(edge.from, edge.to, edge.cost);\n\
    \        if (int(result.original_edge_id.size()) <= id) {\n            result.original_edge_id.resize(id\
    \ + 1);\n        }\n        result.original_edge_id[id] = edge.id;\n    }\n  \
    \  return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/graph/general_weighted_matching.test.cpp\"\n\n#line 7 \"verify/graph/general_weighted_matching.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 11 \"verify/graph/general_weighted_matching.test.cpp\"\
    \n\nnamespace {\n\nusing Matching = m1une::graph::GeneralWeightedMatching<int,\
    \ long long>;\n\nlong long naive(const Matching& graph) {\n    int n = graph.size();\n\
    \    std::vector<long long> dp(1 << n, std::numeric_limits<long long>::min());\n\
    \    dp[0] = 0;\n    for (int mask = 0; mask < (1 << n); mask++) {\n        if\
    \ (dp[mask] == std::numeric_limits<long long>::min()) continue;\n        int from\
    \ = 0;\n        while (from < n && (mask >> from & 1)) from++;\n        if (from\
    \ == n) continue;\n        dp[mask | (1 << from)] = std::max(dp[mask | (1 << from)],\
    \ dp[mask]);\n        for (const auto& edge : graph.edges()) {\n            if\
    \ (edge.cost <= 0) continue;\n            int to = -1;\n            if (edge.from\
    \ == from) to = edge.to;\n            if (edge.to == from) to = edge.from;\n \
    \           if (to == -1 || (mask >> to & 1)) continue;\n            int next\
    \ = mask | (1 << from) | (1 << to);\n            dp[next] = std::max(dp[next],\
    \ dp[mask] + edge.cost);\n        }\n    }\n    return *std::max_element(dp.begin(),\
    \ dp.end());\n}\n\nvoid validate(Matching& graph) {\n    long long expected =\
    \ naive(graph);\n    assert(graph.max_weight_matching() == expected);\n    assert(graph.matching_weight()\
    \ == expected);\n\n    std::vector<char> used(graph.size(), false);\n    long\
    \ long actual = 0;\n    for (const auto& pair : graph.matching()) {\n        assert(!used[pair.from]\
    \ && !used[pair.to]);\n        used[pair.from] = used[pair.to] = true;\n     \
    \   auto edge = graph.get_edge(pair.edge_id);\n        assert(edge.alive);\n \
    \       assert(edge.cost == pair.cost);\n        assert((edge.from == pair.from\
    \ && edge.to == pair.to) ||\n               (edge.from == pair.to && edge.to ==\
    \ pair.from));\n        actual += pair.cost;\n    }\n    assert(actual == expected);\n\
    \n    auto mate = graph.mate();\n    auto mate_edge = graph.mate_edge();\n   \
    \ for (int vertex = 0; vertex < graph.size(); vertex++) {\n        if (mate[vertex]\
    \ == -1) {\n            assert(mate_edge[vertex] == -1);\n        } else {\n \
    \           assert(mate[mate[vertex]] == vertex);\n            assert(mate_edge[mate[vertex]]\
    \ == mate_edge[vertex]);\n        }\n    }\n}\n\nvoid test_fixed() {\n    Matching\
    \ empty;\n    validate(empty);\n\n    Matching graph(6);\n    int edge_01 = graph.add_edge(0,\
    \ 1, 8);\n    graph.add_edge(1, 2, 9);\n    graph.add_edge(2, 0, 10);\n    graph.add_edge(2,\
    \ 3, 7);\n    graph.add_edge(3, 4, 6);\n    graph.add_edge(4, 5, 5);\n    graph.add_edge(5,\
    \ 3, 4);\n    graph.add_edge(0, 1, 11);\n    graph.add_edge(0, 5, -100);\n   \
    \ validate(graph);\n\n    graph.erase_edge(edge_01);\n    assert(!graph.is_edge_alive(edge_01));\n\
    \    validate(graph);\n    graph.revive_edge(edge_01);\n    validate(graph);\n\
    \n    m1une::graph::Graph<int> source(3);\n    int original_01 = source.add_edge(0,\
    \ 1, 4);\n    source.add_edge(1, 2, 7);\n    int inactive = source.add_edge(0,\
    \ 2, 100);\n    source.erase_edge(inactive);\n    auto built = m1une::graph::make_general_weighted_matching(source);\n\
    \    assert(built.matching.edge_count() == 2);\n    assert(built.matching.max_weight_matching()\
    \ == 7);\n    assert(built.original_edge(0) == original_01);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 123456789;\n    auto random = [&]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1000; trial++) {\n        int n = int(random()\
    \ % 10);\n        Matching graph(n);\n        int edge_count = int(random() %\
    \ 35);\n        for (int i = 0; i < edge_count && n >= 2; i++) {\n           \
    \ int from = int(random() % n);\n            int to = int(random() % n);\n   \
    \         if (from == to) continue;\n            int cost = int(random() % 31)\
    \ - 10;\n            int id = graph.add_edge(from, to, cost);\n            if\
    \ (random() % 7 == 0) graph.erase_edge(id);\n        }\n        validate(graph);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, edge_count;\n    std::cin >> n >> edge_count;\n    Matching graph(n);\n \
    \   while (edge_count--) {\n        int from, to, cost;\n        std::cin >> from\
    \ >> to >> cost;\n        graph.add_edge(from, to, cost);\n    }\n\n    long long\
    \ weight = graph.max_weight_matching();\n    auto matching = graph.matching();\n\
    \    std::cout << matching.size() << ' ' << weight << '\\n';\n    for (const auto&\
    \ pair : matching) {\n        std::cout << pair.from << ' ' << pair.to << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/general_weighted_matching\"\
    \n\n#include \"../../graph/general_weighted_matching.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <vector>\n\nnamespace {\n\nusing Matching = m1une::graph::GeneralWeightedMatching<int,\
    \ long long>;\n\nlong long naive(const Matching& graph) {\n    int n = graph.size();\n\
    \    std::vector<long long> dp(1 << n, std::numeric_limits<long long>::min());\n\
    \    dp[0] = 0;\n    for (int mask = 0; mask < (1 << n); mask++) {\n        if\
    \ (dp[mask] == std::numeric_limits<long long>::min()) continue;\n        int from\
    \ = 0;\n        while (from < n && (mask >> from & 1)) from++;\n        if (from\
    \ == n) continue;\n        dp[mask | (1 << from)] = std::max(dp[mask | (1 << from)],\
    \ dp[mask]);\n        for (const auto& edge : graph.edges()) {\n            if\
    \ (edge.cost <= 0) continue;\n            int to = -1;\n            if (edge.from\
    \ == from) to = edge.to;\n            if (edge.to == from) to = edge.from;\n \
    \           if (to == -1 || (mask >> to & 1)) continue;\n            int next\
    \ = mask | (1 << from) | (1 << to);\n            dp[next] = std::max(dp[next],\
    \ dp[mask] + edge.cost);\n        }\n    }\n    return *std::max_element(dp.begin(),\
    \ dp.end());\n}\n\nvoid validate(Matching& graph) {\n    long long expected =\
    \ naive(graph);\n    assert(graph.max_weight_matching() == expected);\n    assert(graph.matching_weight()\
    \ == expected);\n\n    std::vector<char> used(graph.size(), false);\n    long\
    \ long actual = 0;\n    for (const auto& pair : graph.matching()) {\n        assert(!used[pair.from]\
    \ && !used[pair.to]);\n        used[pair.from] = used[pair.to] = true;\n     \
    \   auto edge = graph.get_edge(pair.edge_id);\n        assert(edge.alive);\n \
    \       assert(edge.cost == pair.cost);\n        assert((edge.from == pair.from\
    \ && edge.to == pair.to) ||\n               (edge.from == pair.to && edge.to ==\
    \ pair.from));\n        actual += pair.cost;\n    }\n    assert(actual == expected);\n\
    \n    auto mate = graph.mate();\n    auto mate_edge = graph.mate_edge();\n   \
    \ for (int vertex = 0; vertex < graph.size(); vertex++) {\n        if (mate[vertex]\
    \ == -1) {\n            assert(mate_edge[vertex] == -1);\n        } else {\n \
    \           assert(mate[mate[vertex]] == vertex);\n            assert(mate_edge[mate[vertex]]\
    \ == mate_edge[vertex]);\n        }\n    }\n}\n\nvoid test_fixed() {\n    Matching\
    \ empty;\n    validate(empty);\n\n    Matching graph(6);\n    int edge_01 = graph.add_edge(0,\
    \ 1, 8);\n    graph.add_edge(1, 2, 9);\n    graph.add_edge(2, 0, 10);\n    graph.add_edge(2,\
    \ 3, 7);\n    graph.add_edge(3, 4, 6);\n    graph.add_edge(4, 5, 5);\n    graph.add_edge(5,\
    \ 3, 4);\n    graph.add_edge(0, 1, 11);\n    graph.add_edge(0, 5, -100);\n   \
    \ validate(graph);\n\n    graph.erase_edge(edge_01);\n    assert(!graph.is_edge_alive(edge_01));\n\
    \    validate(graph);\n    graph.revive_edge(edge_01);\n    validate(graph);\n\
    \n    m1une::graph::Graph<int> source(3);\n    int original_01 = source.add_edge(0,\
    \ 1, 4);\n    source.add_edge(1, 2, 7);\n    int inactive = source.add_edge(0,\
    \ 2, 100);\n    source.erase_edge(inactive);\n    auto built = m1une::graph::make_general_weighted_matching(source);\n\
    \    assert(built.matching.edge_count() == 2);\n    assert(built.matching.max_weight_matching()\
    \ == 7);\n    assert(built.original_edge(0) == original_01);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 123456789;\n    auto random = [&]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 1000; trial++) {\n        int n = int(random()\
    \ % 10);\n        Matching graph(n);\n        int edge_count = int(random() %\
    \ 35);\n        for (int i = 0; i < edge_count && n >= 2; i++) {\n           \
    \ int from = int(random() % n);\n            int to = int(random() % n);\n   \
    \         if (from == to) continue;\n            int cost = int(random() % 31)\
    \ - 10;\n            int id = graph.add_edge(from, to, cost);\n            if\
    \ (random() % 7 == 0) graph.erase_edge(id);\n        }\n        validate(graph);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, edge_count;\n    std::cin >> n >> edge_count;\n    Matching graph(n);\n \
    \   while (edge_count--) {\n        int from, to, cost;\n        std::cin >> from\
    \ >> to >> cost;\n        graph.add_edge(from, to, cost);\n    }\n\n    long long\
    \ weight = graph.max_weight_matching();\n    auto matching = graph.matching();\n\
    \    std::cout << matching.size() << ' ' << weight << '\\n';\n    for (const auto&\
    \ pair : matching) {\n        std::cout << pair.from << ' ' << pair.to << '\\\
    n';\n    }\n}\n"
  dependsOn:
  - graph/general_weighted_matching.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/general_weighted_matching.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 02:19:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/general_weighted_matching.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/general_weighted_matching.test.cpp
- /verify/verify/graph/general_weighted_matching.test.cpp.html
title: verify/graph/general_weighted_matching.test.cpp
---
