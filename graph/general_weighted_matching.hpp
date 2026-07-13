#ifndef M1UNE_GRAPH_GENERAL_WEIGHTED_MATCHING_HPP
#define M1UNE_GRAPH_GENERAL_WEIGHTED_MATCHING_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <limits>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {
namespace internal {

// Primal-dual weighted blossom algorithm using Gabow's event queues.
// Reference: H. N. Gabow, "Data Structures for Weighted Matching and
// Extensions to b-matching and f-factors", 2016.
// Vertices 1..n are atoms; larger indices represent contracted blossoms.
template <class Cost, class TotalCost>
class WeightedBlossomSolver {
   public:
    using cost_type = Cost;
    using total_type = TotalCost;

   private:
    enum BlossomLabel : int {
        separated_label = -2,
        inner_label = -1,
        free_label = 0,
        outer_label = 1
    };
    static constexpr cost_type infinity = cost_type(1) << (sizeof(cost_type) * 8 - 2);

    template <class T>
    class MutableBinaryHeap {
       public:
        struct Node {
            bool operator<(const Node& rhs) const {
                if (value < rhs.value) {
                    return true;
                }
                if (rhs.value < value) {
                    return false;
                }
                return id < rhs.id;
            }
            T value;
            int id;
        };

        MutableBinaryHeap() = default;
        explicit MutableBinaryHeap(int capacity) : _size(0), _nodes(capacity + 1), _position(capacity, 0) {
        }

        bool empty() const {
            return _size == 0;
        }
        void clear() {
            while (_size > 0) {
                _position[_nodes[_size].id] = 0;
                _size--;
            }
        }
        T min() const {
            return _nodes[1].value;
        }
        int argmin() const {
            return _nodes[1].id;
        }
        void pop() {
            if (_size > 0) pop(1);
        }
        void erase(int id) {
            if (_position[id]) pop(_position[id]);
        }
        bool has(int id) const {
            return _position[id] != 0;
        }
        void update(int id, T v) {
            if (!has(id)) return push(id, v);
            bool up = (v < _nodes[_position[id]].value);
            _nodes[_position[id]].value = v;
            if (up) {
                up_heap(_position[id]);
            } else {
                down_heap(_position[id]);
            }
        }
        void decrease_key(int id, T v) {
            if (!has(id)) return push(id, v);
            if (v < _nodes[_position[id]].value) {
                _nodes[_position[id]].value = v;
                up_heap(_position[id]);
            }
        }
        void push(int id, T v) {
            _position[id] = ++_size;
            _nodes[_size] = {v, id};
            up_heap(_size);
        }

       private:
        void pop(int pos) {
            _position[_nodes[pos].id] = 0;
            if (pos == _size) {
                --_size;
                return;
            }
            bool up = (_nodes[_size].value < _nodes[pos].value);
            _nodes[pos] = _nodes[_size--];
            _position[_nodes[pos].id] = pos;
            if (up) {
                up_heap(pos);
            } else {
                down_heap(pos);
            }
        }
        void swap_node(int a, int b) {
            std::swap(_nodes[a], _nodes[b]);
            _position[_nodes[a].id] = a;
            _position[_nodes[b].id] = b;
        }
        void down_heap(int pos) {
            for (int current = pos;;) {
                int next = current;
                if (2 * current <= _size && _nodes[2 * current] < _nodes[next]) {
                    next = 2 * current;
                }
                if (2 * current + 1 <= _size && _nodes[2 * current + 1] < _nodes[next]) {
                    next = 2 * current + 1;
                }
                if (next == current) break;
                swap_node(current, next);
                current = next;
            }
        }
        void up_heap(int pos) {
            for (int current = pos; current > 1 && _nodes[current] < _nodes[current >> 1]; current >>= 1) {
                swap_node(current, current >> 1);
            }
        }
        int _size;
        std::vector<Node> _nodes;
        std::vector<int> _position;
    };

    template <class Key>
    class DisjointPairingHeaps {
       private:
        struct Node {
            Node() : key(), child(0), next(0), prev(-1) {
            }
            explicit Node(Key value) : key(value), child(0), next(0), prev(0) {
            }
            Key key;
            int child;
            int next;
            int prev;
        };

       public:
        DisjointPairingHeaps(int heap_count, int node_count) : _roots(heap_count), _nodes(node_count) {
        }

        void clear(int h) {
            if (_roots[h]) {
                clear_rec(_roots[h]);
                _roots[h] = 0;
            }
        }
        bool empty(int h) const {
            return !_roots[h];
        }
        bool used(int v) const {
            return _nodes[v].prev >= 0;
        }
        Key min(int h) const {
            return _nodes[_roots[h]].key;
        }
        void push(int h, int v, Key key) {
            _nodes[v] = Node(key);
            _roots[h] = merge(_roots[h], v);
        }
        void erase(int h, int v) {
            if (!used(v)) return;
            int w = two_pass_pairing(_nodes[v].child);
            if (!_nodes[v].prev) {
                _roots[h] = w;
            } else {
                cut(v);
                _roots[h] = merge(_roots[h], w);
            }
            _nodes[v].prev = -1;
        }
        void decrease_key(int h, int v, Key key) {
            if (!used(v)) return push(h, v, key);
            if (!_nodes[v].prev) {
                _nodes[v].key = key;
            } else {
                cut(v);
                _nodes[v].key = key;
                _roots[h] = merge(_roots[h], v);
            }
        }

       private:
        void clear_rec(int v) {
            for (; v; v = _nodes[v].next) {
                if (_nodes[v].child) clear_rec(_nodes[v].child);
                _nodes[v].prev = -1;
            }
        }

        inline void cut(int v) {
            auto& n = _nodes[v];
            int previous = n.prev;
            int next = n.next;
            auto& previous_node = _nodes[previous];
            if (previous_node.child == v) {
                previous_node.child = next;
            } else {
                previous_node.next = next;
            }
            _nodes[next].prev = previous;
            n.next = n.prev = 0;
        }

        int merge(int l, int r) {
            if (!l) return r;
            if (!r) return l;
            if (_nodes[l].key > _nodes[r].key) std::swap(l, r);
            int lc = _nodes[r].next = _nodes[l].child;
            _nodes[l].child = _nodes[lc].prev = r;
            return _nodes[r].prev = l;
        }

        int two_pass_pairing(int root) {
            if (!root) return 0;
            int a = root;
            root = 0;
            while (a) {
                int b = _nodes[a].next;
                int next_a = 0;
                _nodes[a].prev = _nodes[a].next = 0;
                if (b) {
                    next_a = _nodes[b].next;
                    _nodes[b].prev = _nodes[b].next = 0;
                }
                a = merge(a, b);
                _nodes[a].next = root;
                root = a;
                a = next_a;
            }
            int s = _nodes[root].next;
            _nodes[root].next = 0;
            while (s) {
                int t = _nodes[s].next;
                _nodes[s].next = 0;
                root = merge(root, s);
                s = t;
            }
            return root;
        }

       private:
        std::vector<int> _roots;
        std::vector<Node> _nodes;
    };

    template <class T>
    struct ReservablePriorityQueue : public std::priority_queue<T, std::vector<T>, std::greater<T>> {
        ReservablePriorityQueue() = default;
        explicit ReservablePriorityQueue(int capacity) {
            this->c.reserve(capacity);
        }
        T min() const {
            return this->top();
        }
        void clear() {
            this->c.clear();
        }
    };

    template <class T>
    struct FixedQueue {
        FixedQueue() = default;
        explicit FixedQueue(int capacity) : _head(0), _tail(0), _data(capacity) {
        }
        void enqueue(int u) {
            _data[_tail++] = u;
        }
        int dequeue() {
            return _data[_head++];
        }
        bool empty() const {
            return _head == _tail;
        }
        void clear() {
            _head = _tail = 0;
        }
        int _head = 0;
        int _tail = 0;
        std::vector<T> _data;
    };

   public:
    struct InputEdge {
        int from;
        int to;
        cost_type cost;
    };

   private:
    struct SolverEdge {
        int to;
        cost_type cost;
    };

    struct BlossomLink {
        int from;
        int to;
    };

    struct BlossomNode {
        struct CycleLink {
            int blossom;
            int vertex;
        };

        BlossomNode() = default;
        explicit BlossomNode(int vertex) : parent(0), size(1) {
            cycle[0] = cycle[1] = CycleLink{vertex, vertex};
        }

        int next_v() const {
            return cycle[0].vertex;
        }
        int next_b() const {
            return cycle[0].blossom;
        }
        int prev_v() const {
            return cycle[1].vertex;
        }
        int prev_b() const {
            return cycle[1].blossom;
        }

        int parent = 0;
        int size = 0;
        CycleLink cycle[2];
    };

    struct VertexEvent {
        VertexEvent() = default;
        VertexEvent(cost_type event_time, int vertex) : time(event_time), id(vertex) {
        }

        bool operator<(const VertexEvent& rhs) const {
            if (time < rhs.time) {
                return true;
            }
            if (rhs.time < time) {
                return false;
            }
            return id < rhs.id;
        }
        bool operator>(const VertexEvent& rhs) const {
            return rhs < *this;
        }

        cost_type time = cost_type();
        int id = 0;
    };

    struct EdgeEvent {
        EdgeEvent() = default;
        EdgeEvent(cost_type event_time, int from_, int to_) : time(event_time), from(from_), to(to_) {
        }

        bool operator<(const EdgeEvent& rhs) const {
            if (time < rhs.time) {
                return true;
            }
            if (time > rhs.time) {
                return false;
            }
            return std::make_pair(from, to) < std::make_pair(rhs.from, rhs.to);
        }
        bool operator>(const EdgeEvent& rhs) const {
            return rhs < *this;
        }

        cost_type time = cost_type();
        int from = 0;
        int to = 0;
    };

   public:
    WeightedBlossomSolver(int n, const std::vector<InputEdge>& input_edges)
        : _vertex_count(n),
          _blossom_count((n - 1) / 2),
          _state_count(n + _blossom_count + 1),
          _offset(n + 2),
          _edges(input_edges.size() * 2),
          _grow_heap(_state_count),
          _blossom_grow_heaps(_state_count, _state_count),
          _contract_heap(int(_edges.size())),
          _expand_heap(_state_count) {
        for (const InputEdge& edge : input_edges) {
            _offset[edge.from + 1]++;
            _offset[edge.to + 1]++;
        }
        for (int i = 1; i <= _vertex_count + 1; i++) _offset[i] += _offset[i - 1];
        for (const InputEdge& edge : input_edges) {
            _edges[_offset[edge.from]++] = SolverEdge{edge.to, edge.cost * 2};
            _edges[_offset[edge.to]++] = SolverEdge{edge.from, edge.cost * 2};
        }
        for (int i = _vertex_count + 1; i > 0; i--) _offset[i] = _offset[i - 1];
        _offset[0] = 0;
    }

    total_type solve(std::vector<std::pair<int, int>>& matching) {
        initialize_state();
        initialize_potentials();
        for (int vertex = 1; vertex <= _vertex_count; vertex++) {
            if (_mate[vertex] == 0) augment_from(vertex);
        }

        matching.clear();
        for (int vertex = 1; vertex <= _vertex_count; vertex++) {
            if (_mate[vertex] > vertex) matching.emplace_back(vertex, _mate[vertex]);
        }
        return compute_matching_weight();
    }

   private:
    total_type compute_matching_weight() const {
        total_type result = 0;
        for (int vertex = 1; vertex <= _vertex_count; vertex++) {
            if (_mate[vertex] > vertex) {
                cost_type best_cost = 0;
                for (int edge_id = _offset[vertex]; edge_id < _offset[vertex + 1]; edge_id++) {
                    if (_edges[edge_id].to == _mate[vertex]) {
                        best_cost = std::max(best_cost, _edges[edge_id].cost);
                    }
                }
                result += best_cost;
            }
        }
        return result >> 1;
    }

    total_type reduced_cost(int from, int to, const SolverEdge& edge) const {
        return total_type(_potential[from]) + _potential[to] - edge.cost;
    }

    void rematch(int vertex, int new_mate) {
        int old_mate = _mate[vertex];
        _mate[vertex] = new_mate;
        if (_mate[old_mate] != vertex) return;
        if (_tree_link[vertex].to == _surface[_tree_link[vertex].to]) {
            _mate[old_mate] = _tree_link[vertex].from;
            rematch(_mate[old_mate], old_mate);
        } else {
            int from = _tree_link[vertex].from;
            int to = _tree_link[vertex].to;
            rematch(from, to);
            rematch(to, from);
        }
    }

    void repair_matching(int blossom) {
        if (blossom <= _vertex_count) return;
        int child = _base[blossom];
        int first_vertex = _nodes[child].cycle[0].vertex;
        int first_neighbor = _nodes[child].cycle[0].blossom;
        int direction = (_nodes[first_neighbor].cycle[1].vertex == _mate[first_vertex]) ? 0 : 1;
        while (true) {
            int matched_vertex = _nodes[child].cycle[direction].vertex;
            int matched_child = _nodes[child].cycle[direction].blossom;
            if (_nodes[matched_child].cycle[1 ^ direction].vertex != _mate[matched_vertex]) break;
            repair_matching(child);
            repair_matching(matched_child);
            child = _nodes[matched_child].cycle[direction].blossom;
        }
        _base[blossom] = child;
        repair_matching(child);
        _mate[blossom] = _mate[child];
    }

    void reset_clock() {
        _time = 0;
        _vertex_event = {infinity, 0};
    }

    void reset_blossom(int blossom) {
        _label[blossom] = free_label;
        _tree_link[blossom].from = 0;
        _slack[blossom] = infinity;
        _lazy[blossom] = 0;
    }

    void reset_search_state() {
        _label[0] = free_label;
        _tree_link[0].from = 0;
        for (int vertex = 1; vertex <= _vertex_count; vertex++) {
            if (_label[vertex] == outer_label) {
                _potential[vertex] -= _time;
            } else {
                int blossom = _surface[vertex];
                _potential[vertex] += _lazy[blossom];
                if (_label[blossom] == inner_label) {
                    _potential[vertex] += _time - _created_at[blossom];
                }
            }
            reset_blossom(vertex);
        }
        int remaining_blossoms = _blossom_count - _unused_count;
        for (int blossom = _vertex_count + 1; remaining_blossoms > 0 && blossom < _state_count; blossom++) {
            if (_base[blossom] != blossom) {
                if (_surface[blossom] == blossom) {
                    repair_matching(blossom);
                    if (_label[blossom] == outer_label) {
                        _potential[blossom] += (_time - _created_at[blossom]) << 1;
                    } else if (_label[blossom] == inner_label) {
                        materialize_potential<inner_label>(blossom);
                    } else {
                        materialize_potential<free_label>(blossom);
                    }
                }
                _blossom_grow_heaps.clear(blossom);
                reset_blossom(blossom);
                remaining_blossoms--;
            }
        }

        _queue.clear();
        reset_clock();
        _grow_heap.clear();
        _contract_heap.clear();
        _expand_heap.clear();
    }

    void augment_from(int root) {
        if (_potential[root] == 0) return;
        link_blossom(_surface[root], {0, 0});
        make_outer(_surface[root], 0);
        for (bool augmented = false; !augmented;) {
            augmented = scan_tight_edges(root);
            if (augmented) break;
            augmented = advance_dual(root);
        }
        reset_search_state();
    }

    template <BlossomLabel target_label>
    cost_type materialize_potential(int blossom) {
        cost_type delta = _lazy[blossom];
        _lazy[blossom] = 0;
        if (target_label == inner_label) {
            cost_type elapsed = _time - _created_at[blossom];
            if (blossom > _vertex_count) _potential[blossom] -= elapsed << 1;
            delta += elapsed;
        }
        return delta;
    }

    template <BlossomLabel target_label>
    void update_grow_event(int from, int to, int to_blossom, cost_type slack) {
        if (slack >= _slack[to]) return;
        _slack[to] = slack;
        _best_from[to] = from;
        if (to == to_blossom) {
            if (target_label != inner_label) {
                _grow_heap.decrease_key(to, EdgeEvent(slack + _lazy[to], from, to));
            }
        } else {
            int to_group = _group[to];
            if (to_group != to) {
                if (slack >= _slack[to_group]) return;
                _slack[to_group] = slack;
            }
            _blossom_grow_heaps.decrease_key(to_blossom, to_group, EdgeEvent(slack, from, to));
            if (target_label == inner_label) return;
            EdgeEvent event = _blossom_grow_heaps.min(to_blossom);
            _grow_heap.decrease_key(to_blossom,
                                    EdgeEvent(event.time + _lazy[to_blossom], event.from, event.to));
        }
    }

    void activate_grow_event(int blossom) {
        if (blossom <= _vertex_count) {
            if (_slack[blossom] < infinity) {
                _grow_heap.push(blossom,
                                EdgeEvent(_slack[blossom] + _lazy[blossom], _best_from[blossom], blossom));
            }
        } else {
            if (_blossom_grow_heaps.empty(blossom)) return;
            EdgeEvent event = _blossom_grow_heaps.min(blossom);
            _grow_heap.push(blossom, EdgeEvent(event.time + _lazy[blossom], event.from, event.to));
        }
    }

    void swap_blossoms(int a, int b) {
        // b is a maximal blossom.
        std::swap(_base[a], _base[b]);
        if (_base[a] == a) _base[a] = b;
        std::swap(_heavy[a], _heavy[b]);
        if (_heavy[a] == a) _heavy[a] = b;
        std::swap(_tree_link[a], _tree_link[b]);
        std::swap(_mate[a], _mate[b]);
        std::swap(_potential[a], _potential[b]);
        std::swap(_lazy[a], _lazy[b]);
        std::swap(_created_at[a], _created_at[b]);
        for (int direction = 0; direction < 2; direction++) {
            int child = _nodes[a].cycle[direction].blossom;
            _nodes[child].cycle[1 ^ direction].blossom = b;
        }
        std::swap(_nodes[a], _nodes[b]);
    }

    void assign_surface(int blossom, int surface, int group) {
        _surface[blossom] = surface;
        _group[blossom] = group;
        if (blossom <= _vertex_count) return;
        for (int child = _base[blossom]; _surface[child] != surface; child = _nodes[child].next_b()) {
            assign_surface(child, surface, group);
        }
    }

    void merge_blossom_children(int blossom) {
        int largest_child = blossom;
        int largest_size = 1;
        int first_child = _base[blossom];
        for (int child = first_child;; child = _nodes[child].next_b()) {
            if (_nodes[child].size > largest_size) {
                largest_size = _nodes[child].size;
                largest_child = child;
            }
            if (_nodes[child].next_b() == first_child) break;
        }
        for (int child = first_child;; child = _nodes[child].next_b()) {
            if (child != largest_child) assign_surface(child, largest_child, child);
            if (_nodes[child].next_b() == first_child) break;
        }
        _group[largest_child] = largest_child;
        if (largest_size > 1) {
            _surface[blossom] = _heavy[blossom] = largest_child;
            swap_blossoms(largest_child, blossom);
        } else {
            _heavy[blossom] = 0;
        }
    }

    void contract_blossom(int x, int y, int edge_id) {
        int x_blossom = _surface[x];
        int y_blossom = _surface[y];
        assert(x_blossom != y_blossom);
        const int visit_mark = -(edge_id + 1);
        _tree_link[_surface[_mate[x_blossom]]].from = visit_mark;
        _tree_link[_surface[_mate[y_blossom]]].from = visit_mark;

        int lca = -1;
        while (true) {
            if (_mate[y_blossom] != 0) std::swap(x_blossom, y_blossom);
            x_blossom = lca = _surface[_tree_link[x_blossom].from];
            if (_tree_link[_surface[_mate[x_blossom]]].from == visit_mark) break;
            _tree_link[_surface[_mate[x_blossom]]].from = visit_mark;
        }

        const int blossom = _unused_blossoms[--_unused_count];
        assert(_unused_count >= 0);
        int tree_size = 0;
        for (int direction = 0; direction < 2; direction++) {
            for (int child = _surface[x]; child != lca;) {
                int matched_vertex = _mate[child];
                int matched_child = _surface[matched_vertex];
                int vertex = _mate[matched_vertex];
                int link_from = _tree_link[vertex].from;
                int link_to = _tree_link[vertex].to;
                tree_size += _nodes[child].size + _nodes[matched_child].size;
                _tree_link[matched_vertex] = {x, y};

                if (child > _vertex_count) {
                    _potential[child] += (_time - _created_at[child]) << 1;
                }
                if (matched_child > _vertex_count) _expand_heap.erase(matched_child);
                make_outer(matched_child, materialize_potential<inner_label>(matched_child));

                _nodes[child].cycle[direction] = {matched_child, matched_vertex};
                _nodes[matched_child].cycle[1 ^ direction] = {child, vertex};
                child = _surface[link_from];
                _nodes[matched_child].cycle[direction] = {child, link_from};
                _nodes[child].cycle[1 ^ direction] = {matched_child, link_to};
            }
            _nodes[_surface[x]].cycle[1 ^ direction] = {_surface[y], y};
            std::swap(x, y);
        }
        if (lca > _vertex_count) _potential[lca] += (_time - _created_at[lca]) << 1;
        _nodes[blossom].size = tree_size + _nodes[lca].size;
        _base[blossom] = lca;
        _tree_link[blossom] = _tree_link[lca];
        _mate[blossom] = _mate[lca];
        _label[blossom] = outer_label;
        _surface[blossom] = blossom;
        _created_at[blossom] = _time;
        _potential[blossom] = 0;
        _lazy[blossom] = 0;

        merge_blossom_children(blossom);
    }

    void link_blossom(int blossom, BlossomLink link) {
        _tree_link[blossom] = link;
        if (blossom <= _vertex_count) return;
        int first_child = _base[blossom];
        link_blossom(first_child, link);
        int previous_child = _nodes[first_child].prev_b();
        link = {_nodes[previous_child].next_v(), _nodes[first_child].prev_v()};
        for (int child = first_child;;) {
            int next_child = _nodes[child].next_b();
            if (next_child == first_child) break;
            link_blossom(next_child, link);
            BlossomLink next_link = {_nodes[next_child].prev_v(), _nodes[child].next_v()};
            child = _nodes[next_child].next_b();
            link_blossom(child, next_link);
        }
    }

    void make_outer(int blossom, cost_type delta) {
        _label[blossom] = outer_label;
        if (blossom > _vertex_count) {
            for (int child = _base[blossom]; _label[child] != outer_label; child = _nodes[child].next_b()) {
                make_outer(child, delta);
            }
        } else {
            _potential[blossom] += _time + delta;
            if (_potential[blossom] < _vertex_event.time) {
                _vertex_event = {_potential[blossom], blossom};
            }
            _queue.enqueue(blossom);
        }
    }

    bool grow_tree(int from, int to) {
        int inner_blossom = _surface[to];
        bool visited = (_label[inner_blossom] != free_label);
        if (!visited) link_blossom(inner_blossom, {0, 0});
        _label[inner_blossom] = inner_label;
        _created_at[inner_blossom] = _time;
        _grow_heap.erase(inner_blossom);
        if (to != inner_blossom) {
            _expand_heap.update(inner_blossom, _time + (_potential[inner_blossom] >> 1));
        }
        int matched_vertex = _mate[inner_blossom];
        if (matched_vertex == 0) {
            rematch(from, to);
            rematch(to, from);
            return true;
        }
        int outer_blossom = _surface[matched_vertex];
        if (!visited) {
            link_blossom(outer_blossom, {from, to});
        } else {
            _tree_link[outer_blossom] = _tree_link[matched_vertex] = {from, to};
        }
        make_outer(outer_blossom, materialize_potential<free_label>(outer_blossom));
        _created_at[outer_blossom] = _time;
        _grow_heap.erase(outer_blossom);
        return false;
    }

    void release_blossom(int blossom) {
        _unused_blossoms[_unused_count++] = blossom;
        _base[blossom] = blossom;
    }

    int recompute_slack(int blossom, int group) {
        if (blossom <= _vertex_count) {
            if (_slack[blossom] >= _slack[group]) return 0;
            _slack[group] = _slack[blossom];
            _best_from[group] = _best_from[blossom];
            return blossom;
        }
        int destination = 0;
        int first_child = _base[blossom];
        for (int child = first_child;; child = _nodes[child].next_b()) {
            int candidate = recompute_slack(child, group);
            if (candidate != 0) destination = candidate;
            if (_nodes[child].next_b() == first_child) break;
        }
        return destination;
    }

    void rebuild_components(int blossom, int surface, int group) {
        _surface[blossom] = surface;
        _group[blossom] = group;
        if (blossom <= _vertex_count) return;
        for (int child = _base[blossom]; _surface[child] != surface; child = _nodes[child].next_b()) {
            if (child == _heavy[blossom]) {
                rebuild_components(child, surface, group);
            } else {
                assign_surface(child, surface, child);
                int destination = 0;
                if (child > _vertex_count) {
                    _slack[child] = infinity;
                    destination = recompute_slack(child, child);
                } else if (_slack[child] < infinity) {
                    destination = child;
                }
                if (destination > 0) {
                    _blossom_grow_heaps.push(surface, child,
                                             EdgeEvent(_slack[child], _best_from[child], destination));
                }
            }
        }
    }

    void promote_largest_child(int blossom) {
        int largest_child = _heavy[blossom];
        cost_type delta = (_time - _created_at[blossom]) + _lazy[blossom];
        _lazy[blossom] = 0;
        int first_child = _base[blossom];
        for (int child = first_child;; child = _nodes[child].next_b()) {
            _created_at[child] = _time;
            _lazy[child] = delta;
            if (child != largest_child) {
                rebuild_components(child, child, child);
                _blossom_grow_heaps.erase(blossom, child);
            }
            if (_nodes[child].next_b() == first_child) break;
        }
        if (largest_child > 0) {
            swap_blossoms(largest_child, blossom);
            blossom = largest_child;
        }
        release_blossom(blossom);
    }

    void expand_blossom(int blossom) {
        int matched_vertex = _mate[_base[blossom]];
        promote_largest_child(blossom);
        BlossomLink old_link = _tree_link[matched_vertex];
        int old_base = _surface[_mate[matched_vertex]];
        int root = _surface[old_link.to];
        int direction = (_mate[root] == _nodes[root].cycle[0].vertex) ? 1 : 0;
        for (int child = _nodes[old_base].cycle[direction ^ 1].blossom; child != root;) {
            _label[child] = separated_label;
            activate_grow_event(child);
            child = _nodes[child].cycle[direction ^ 1].blossom;
            _label[child] = separated_label;
            activate_grow_event(child);
            child = _nodes[child].cycle[direction ^ 1].blossom;
        }
        for (int child = old_base;; child = _nodes[child].cycle[direction].blossom) {
            _label[child] = inner_label;
            int next_child = _nodes[child].cycle[direction].blossom;
            if (child == root) {
                _tree_link[_mate[child]] = old_link;
            } else {
                _tree_link[_mate[child]] = {_nodes[child].cycle[direction].vertex,
                                            _nodes[next_child].cycle[direction ^ 1].vertex};
            }
            _tree_link[_surface[_mate[child]]] = _tree_link[_mate[child]];
            if (child > _vertex_count) {
                if (_potential[child] == 0) {
                    expand_blossom(child);
                } else {
                    _expand_heap.push(child, _time + (_potential[child] >> 1));
                }
            }
            if (child == root) break;
            child = next_child;
            make_outer(next_child, materialize_potential<inner_label>(next_child));
        }
    }

    bool scan_tight_edges(int root) {
        while (!_queue.empty()) {
            int from = _queue.dequeue();
            int from_blossom = _surface[from];
            if (_potential[from] == _time) {
                if (from != root) rematch(from, 0);
                return true;
            }
            for (int edge_id = _offset[from]; edge_id < _offset[from + 1]; edge_id++) {
                const SolverEdge& edge = _edges[edge_id];
                int to = edge.to;
                int to_blossom = _surface[to];
                if (from_blossom == to_blossom) continue;
                BlossomLabel to_label = _label[to_blossom];
                if (to_label == outer_label) {
                    cost_type event_time = cost_type(reduced_cost(from, to, edge) >> 1);
                    if (event_time == _time) {
                        contract_blossom(from, to, edge_id);
                        from_blossom = _surface[from];
                    } else if (event_time < _vertex_event.time) {
                        _contract_heap.emplace(event_time, from, edge_id);
                    }
                } else {
                    total_type event_time = reduced_cost(from, to, edge);
                    if (event_time >= infinity) continue;
                    if (to_label != inner_label) {
                        if (cost_type(event_time) + _lazy[to_blossom] == _time) {
                            if (grow_tree(from, to)) return true;
                        } else {
                            update_grow_event<free_label>(from, to, to_blossom, cost_type(event_time));
                        }
                    } else if (_mate[from] != to) {
                        update_grow_event<inner_label>(from, to, to_blossom, cost_type(event_time));
                    }
                }
            }
        }
        return false;
    }

    bool advance_dual(int root) {
        cost_type rematch_time = _vertex_event.time;
        cost_type grow_time = infinity;
        if (!_grow_heap.empty()) grow_time = _grow_heap.min().time;

        cost_type contract_time = infinity;
        while (!_contract_heap.empty()) {
            EdgeEvent event = _contract_heap.min();
            int from = event.from;
            int to = _edges[event.to].to;
            if (_surface[from] != _surface[to]) {
                contract_time = event.time;
                break;
            } else {
                _contract_heap.pop();
            }
        }

        cost_type expand_time = infinity;
        if (!_expand_heap.empty()) expand_time = _expand_heap.min();

        cost_type next_time =
            std::min(std::min(rematch_time, grow_time), std::min(contract_time, expand_time));
        assert(_time <= next_time && next_time < infinity);
        _time = next_time;

        if (_time == _vertex_event.time) {
            int x = _vertex_event.id;
            if (x != root) rematch(x, 0);
            return true;
        }
        while (!_grow_heap.empty() && _grow_heap.min().time == _time) {
            int from = _grow_heap.min().from;
            int to = _grow_heap.min().to;
            if (grow_tree(from, to)) return true;
        }
        while (!_contract_heap.empty() && _contract_heap.min().time == _time) {
            int from = _contract_heap.min().from;
            int edge_id = _contract_heap.min().to;
            int to = _edges[edge_id].to;
            _contract_heap.pop();
            if (_surface[from] == _surface[to]) continue;
            contract_blossom(from, to, edge_id);
        }
        while (!_expand_heap.empty() && _expand_heap.min() == _time) {
            int blossom = _expand_heap.argmin();
            _expand_heap.pop();
            expand_blossom(blossom);
        }
        return false;
    }

   private:
    void initialize_state() {
        _queue = FixedQueue<int>(_vertex_count);
        _mate.assign(_state_count, 0);
        _tree_link.assign(_state_count, {0, 0});
        _label.assign(_state_count, free_label);
        _base.resize(_state_count);
        for (int state = 1; state < _state_count; state++) _base[state] = state;
        _surface.resize(_state_count);
        for (int state = 1; state < _state_count; state++) _surface[state] = state;

        _potential.resize(_state_count);
        _nodes.resize(_state_count);
        for (int state = 1; state < _state_count; state++) {
            _nodes[state] = BlossomNode(state);
        }

        _unused_blossoms.resize(_blossom_count);
        for (int i = 0; i < _blossom_count; i++) {
            _unused_blossoms[i] = _vertex_count + _blossom_count - i;
        }
        _unused_count = _blossom_count;

        reset_clock();
        _created_at.resize(_state_count);
        _slack.assign(_state_count, infinity);
        _best_from.assign(_state_count, 0);
        _heavy.assign(_state_count, 0);
        _lazy.assign(_state_count, 0);
        _group.resize(_state_count);
        for (int state = 0; state < _state_count; state++) _group[state] = state;
    }

    void initialize_potentials() {
        for (int vertex = 1; vertex <= _vertex_count; vertex++) {
            cost_type maximum_cost = 0;
            for (int edge_id = _offset[vertex]; edge_id < _offset[vertex + 1]; edge_id++) {
                maximum_cost = std::max(maximum_cost, _edges[edge_id].cost);
            }
            _potential[vertex] = maximum_cost >> 1;
        }
    }

    const int _vertex_count;
    const int _blossom_count;
    const int _state_count;
    std::vector<int> _offset;
    std::vector<SolverEdge> _edges;

    FixedQueue<int> _queue;
    std::vector<int> _mate;
    std::vector<int> _surface;
    std::vector<int> _base;
    std::vector<BlossomLink> _tree_link;
    std::vector<BlossomLabel> _label;
    std::vector<cost_type> _potential;

    std::vector<int> _unused_blossoms;
    int _unused_count;
    std::vector<BlossomNode> _nodes;

    // Heavy children and event queues keep each search phase at O(m log n).
    std::vector<int> _heavy;
    std::vector<int> _group;
    std::vector<cost_type> _created_at;
    std::vector<cost_type> _lazy;
    std::vector<cost_type> _slack;
    std::vector<int> _best_from;

    cost_type _time;
    VertexEvent _vertex_event;
    MutableBinaryHeap<EdgeEvent> _grow_heap;
    DisjointPairingHeaps<EdgeEvent> _blossom_grow_heaps;
    ReservablePriorityQueue<EdgeEvent> _contract_heap;
    MutableBinaryHeap<cost_type> _expand_heap;
};

}  // namespace internal

template <class Cost, class TotalCost = Cost>
struct GeneralWeightedMatching {
    static_assert(std::is_integral_v<Cost> && std::is_signed_v<Cost>);
    static_assert(std::is_integral_v<TotalCost> && std::is_signed_v<TotalCost>);

    struct Edge {
        int from;
        int to;
        Cost cost;
        int id;
        bool alive;

        int other(int vertex) const {
            assert(vertex == from || vertex == to);
            return from ^ to ^ vertex;
        }
    };

    struct Pair {
        int from;
        int to;
        Cost cost;
        int edge_id;
    };

   private:
    int _n;
    std::vector<Edge> _edges;
    std::vector<std::vector<int>> _adj;
    std::vector<int> _mate;
    std::vector<int> _mate_edge;
    TotalCost _matching_weight;
    bool _calculated;

    void invalidate() {
        _calculated = false;
    }

    void ensure_matching() {
        if (!_calculated) max_weight_matching();
    }

   public:
    GeneralWeightedMatching() : GeneralWeightedMatching(0) {
    }

    explicit GeneralWeightedMatching(int n)
        : _n(n), _adj(n), _mate(n, -1), _mate_edge(n, -1), _matching_weight(), _calculated(false) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int from, int to, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(from != to);
        assert(cost <= std::numeric_limits<Cost>::max() / Cost(2));
        int id = int(_edges.size());
        _edges.push_back(Edge{from, to, cost, id, true});
        _adj[from].push_back(id);
        _adj[to].push_back(id);
        invalidate();
        return id;
    }

    Edge get_edge(int id) const {
        assert(0 <= id && id < int(_edges.size()));
        return _edges[id];
    }

    std::vector<Edge> edges(bool include_inactive = false) const {
        std::vector<Edge> result;
        result.reserve(_edges.size());
        for (const Edge& edge : _edges) {
            if (include_inactive || edge.alive) result.push_back(edge);
        }
        return result;
    }

    void set_edge_alive(int id, bool alive) {
        assert(0 <= id && id < int(_edges.size()));
        _edges[id].alive = alive;
        invalidate();
    }

    void erase_edge(int id) {
        set_edge_alive(id, false);
    }

    void revive_edge(int id) {
        set_edge_alive(id, true);
    }

    bool is_edge_alive(int id) const {
        assert(0 <= id && id < int(_edges.size()));
        return _edges[id].alive;
    }

    TotalCost max_weight_matching() {
        using Solver = internal::WeightedBlossomSolver<Cost, TotalCost>;
        std::vector<typename Solver::InputEdge> input;
        input.reserve(_edges.size());
        for (const Edge& edge : _edges) {
            if (!edge.alive || edge.cost <= Cost()) continue;
            input.push_back(typename Solver::InputEdge{edge.from + 1, edge.to + 1, edge.cost});
        }

        Solver solver(_n, input);
        std::vector<std::pair<int, int>> vertex_pairs;
        solver.solve(vertex_pairs);

        _mate.assign(_n, -1);
        _mate_edge.assign(_n, -1);
        _matching_weight = TotalCost();
        for (auto [one_based_from, one_based_to] : vertex_pairs) {
            int from = one_based_from - 1;
            int to = one_based_to - 1;
            int best_edge = -1;
            for (int id : _adj[from]) {
                const Edge& edge = _edges[id];
                if (!edge.alive || edge.other(from) != to || edge.cost <= Cost()) continue;
                if (best_edge == -1 || _edges[best_edge].cost < edge.cost) best_edge = id;
            }
            assert(best_edge != -1);
            _mate[from] = to;
            _mate[to] = from;
            _mate_edge[from] = best_edge;
            _mate_edge[to] = best_edge;
            _matching_weight += static_cast<TotalCost>(_edges[best_edge].cost);
        }

        _calculated = true;
        return _matching_weight;
    }

    TotalCost matching_weight() {
        ensure_matching();
        return _matching_weight;
    }

    int matching_size() {
        ensure_matching();
        int result = 0;
        for (int vertex = 0; vertex < _n; vertex++) {
            if (vertex < _mate[vertex]) result++;
        }
        return result;
    }

    std::vector<int> mate() {
        ensure_matching();
        return _mate;
    }

    std::vector<int> mate_edge() {
        ensure_matching();
        return _mate_edge;
    }

    std::vector<Pair> matching() {
        ensure_matching();
        std::vector<Pair> result;
        for (int vertex = 0; vertex < _n; vertex++) {
            if (vertex < _mate[vertex]) {
                int id = _mate_edge[vertex];
                result.push_back(Pair{vertex, _mate[vertex], _edges[id].cost, id});
            }
        }
        return result;
    }
};

template <class Cost, class TotalCost = Cost>
struct GeneralWeightedMatchingGraph {
    GeneralWeightedMatching<Cost, TotalCost> matching;
    std::vector<int> original_edge_id;

    int original_edge(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));
        return original_edge_id[edge_id];
    }
};

template <class T>
GeneralWeightedMatchingGraph<T> make_general_weighted_matching(const Graph<T>& graph) {
    GeneralWeightedMatchingGraph<T> result;
    result.matching = GeneralWeightedMatching<T>(graph.size());
    for (const auto& edge : graph.edges()) {
        int id = result.matching.add_edge(edge.from, edge.to, edge.cost);
        if (int(result.original_edge_id.size()) <= id) {
            result.original_edge_id.resize(id + 1);
        }
        result.original_edge_id[id] = edge.id;
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_GENERAL_WEIGHTED_MATCHING_HPP
