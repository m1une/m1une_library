---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_set.hpp
    title: Ordered Set
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"verify/ds/bst/ordered_set.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/ordered_set\"\n\n#line 1 \"ds/bst/ordered_set.hpp\"\
    \n\n\n\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct\
    \ OrderedSet {\n   private:\n    struct Node {\n        T key;\n        int size;\n\
    \        Node* l;\n        Node* r;\n\n        explicit Node(T value)\n      \
    \      : key(std::move(value)), size(1), l(nullptr), r(nullptr) {}\n    };\n\n\
    \    static constexpr int pool_block_size = 1 << 15;\n\n    struct Pool {\n  \
    \      std::vector<std::vector<Node>> blocks;\n        std::vector<Node*> free_nodes;\n\
    \n        template <class... Args>\n        Node* emplace(Args&&... args) {\n\
    \            if (!free_nodes.empty()) {\n                Node* result = free_nodes.back();\n\
    \                free_nodes.pop_back();\n                std::destroy_at(result);\n\
    \                std::construct_at(result, std::forward<Args>(args)...);\n   \
    \             return result;\n            }\n            if (blocks.empty() ||\
    \ int(blocks.back().size()) == pool_block_size) {\n                blocks.emplace_back();\n\
    \                blocks.back().reserve(pool_block_size);\n            }\n    \
    \        blocks.back().emplace_back(std::forward<Args>(args)...);\n          \
    \  return &blocks.back().back();\n        }\n\n        void recycle(Node* node)\
    \ {\n            free_nodes.push_back(node);\n        }\n    };\n\n    inline\
    \ static Pool pool;\n\n    Node* root;\n    Compare comp;\n\n    static int subtree_size(const\
    \ Node* t) {\n        return t == nullptr ? 0 : t->size;\n    }\n\n    Node* new_node(T\
    \ key) {\n        return pool.emplace(std::move(key));\n    }\n\n    static void\
    \ update(Node* t) {\n        t->size = 1 + subtree_size(t->l) + subtree_size(t->r);\n\
    \    }\n\n    static Node* rotate_right(Node* t) {\n        Node* s = t->l;\n\
    \        t->l = s->r;\n        s->r = t;\n        update(t);\n        update(s);\n\
    \        return s;\n    }\n\n    static Node* rotate_left(Node* t) {\n       \
    \ Node* s = t->r;\n        t->r = s->l;\n        s->l = t;\n        update(t);\n\
    \        update(s);\n        return s;\n    }\n\n    static Node* balance(Node*\
    \ t) {\n        if (t == nullptr) return nullptr;\n        const int left_size\
    \ = subtree_size(t->l);\n        const int right_size = subtree_size(t->r);\n\
    \        if (left_size + right_size > 1 && left_size > 3LL * right_size) {\n \
    \           if (subtree_size(t->l->r) >= 2LL * subtree_size(t->l->l)) {\n    \
    \            t->l = rotate_left(t->l);\n            }\n            return rotate_right(t);\n\
    \        }\n        if (left_size + right_size > 1 && right_size > 3LL * left_size)\
    \ {\n            if (subtree_size(t->r->l) >= 2LL * subtree_size(t->r->r)) {\n\
    \                t->r = rotate_right(t->r);\n            }\n            return\
    \ rotate_left(t);\n        }\n        update(t);\n        return t;\n    }\n\n\
    \    static Node* join_with_root(Node* l, Node* middle, Node* r) {\n        const\
    \ int left_size = subtree_size(l);\n        const int right_size = subtree_size(r);\n\
    \        if (left_size > 3LL * (right_size + 1)) {\n            l->r = join_with_root(l->r,\
    \ middle, r);\n            return balance(l);\n        }\n        if (right_size\
    \ > 3LL * (left_size + 1)) {\n            r->l = join_with_root(l, middle, r->l);\n\
    \            return balance(r);\n        }\n        middle->l = l;\n        middle->r\
    \ = r;\n        return balance(middle);\n    }\n\n    static Node* detach_max(Node*\
    \ t, Node*& maximum) {\n        if (t->r == nullptr) {\n            maximum =\
    \ t;\n            return t->l;\n        }\n        t->r = detach_max(t->r, maximum);\n\
    \        return balance(t);\n    }\n\n    static Node* merge_nodes(Node* l, Node*\
    \ r) {\n        if (l == nullptr || r == nullptr) return l == nullptr ? r : l;\n\
    \        Node* middle;\n        l = detach_max(l, middle);\n        return join_with_root(l,\
    \ middle, r);\n    }\n\n    std::pair<Node*, Node*> split_nodes(Node* t, const\
    \ T& key) {\n        if (t == nullptr) return {nullptr, nullptr};\n        Node*\
    \ left = t->l;\n        Node* right = t->r;\n        t->l = nullptr;\n       \
    \ t->r = nullptr;\n        if (comp(t->key, key)) {\n            auto [l, r] =\
    \ split_nodes(right, key);\n            return {join_with_root(left, t, l), r};\n\
    \        }\n        auto [l, r] = split_nodes(left, key);\n        return {l,\
    \ join_with_root(r, t, right)};\n    }\n\n    Node* insert_impl(Node* t, T& key,\
    \ bool& inserted) {\n        if (t == nullptr) {\n            inserted = true;\n\
    \            return new_node(std::move(key));\n        }\n        if (comp(key,\
    \ t->key)) {\n            t->l = insert_impl(t->l, key, inserted);\n        }\
    \ else if (comp(t->key, key)) {\n            t->r = insert_impl(t->r, key, inserted);\n\
    \        } else {\n            return t;\n        }\n        if (!inserted) return\
    \ t;\n        return balance(t);\n    }\n\n    Node* erase_impl(Node* t, const\
    \ T& key, bool& erased) {\n        if (t == nullptr) return nullptr;\n       \
    \ if (comp(key, t->key)) {\n            t->l = erase_impl(t->l, key, erased);\n\
    \        } else if (comp(t->key, key)) {\n            t->r = erase_impl(t->r,\
    \ key, erased);\n        } else {\n            erased = true;\n            Node*\
    \ l = t->l;\n            Node* r = t->r;\n            pool.recycle(t);\n     \
    \       return merge_nodes(l, r);\n        }\n        if (!erased) return t;\n\
    \        return balance(t);\n    }\n\n    static const T* kth_impl(const Node*\
    \ t, int k) {\n        while (t != nullptr) {\n            const int left_size\
    \ = subtree_size(t->l);\n            if (k < left_size) {\n                t =\
    \ t->l;\n            } else if (k == left_size) {\n                return &t->key;\n\
    \            } else {\n                k -= left_size + 1;\n                t\
    \ = t->r;\n            }\n        }\n        return nullptr;\n    }\n\n    int\
    \ order_of_key_impl(const Node* t, const T& key, bool upper) const {\n       \
    \ int result = 0;\n        while (t != nullptr) {\n            const bool take\
    \ = upper ? !comp(key, t->key) : comp(t->key, key);\n            if (take) {\n\
    \                result += subtree_size(t->l) + 1;\n                t = t->r;\n\
    \            } else {\n                t = t->l;\n            }\n        }\n \
    \       return result;\n    }\n\n    const T* lower_bound_impl(const Node* t,\
    \ const T& key, bool strict) const {\n        const T* result = nullptr;\n   \
    \     while (t != nullptr) {\n            const bool candidate = strict ? comp(key,\
    \ t->key) : !comp(t->key, key);\n            if (candidate) {\n              \
    \  result = &t->key;\n                t = t->l;\n            } else {\n      \
    \          t = t->r;\n            }\n        }\n        return result;\n    }\n\
    \n    const T* max_less_impl(const Node* t, const T& key, bool strict) const {\n\
    \        const T* result = nullptr;\n        while (t != nullptr) {\n        \
    \    const bool candidate = strict ? comp(t->key, key) : !comp(key, t->key);\n\
    \            if (candidate) {\n                result = &t->key;\n           \
    \     t = t->r;\n            } else {\n                t = t->l;\n           \
    \ }\n        }\n        return result;\n    }\n\n    bool contains_impl(const\
    \ Node* t, const T& key) const {\n        while (t != nullptr) {\n           \
    \ if (comp(key, t->key)) {\n                t = t->l;\n            } else if (comp(t->key,\
    \ key)) {\n                t = t->r;\n            } else {\n                return\
    \ true;\n            }\n        }\n        return false;\n    }\n\n    static\
    \ void dump_impl(const Node* t, std::vector<T>& result) {\n        if (t == nullptr)\
    \ return;\n        dump_impl(t->l, result);\n        result.push_back(t->key);\n\
    \        dump_impl(t->r, result);\n    }\n\n    static void recycle_impl(Node*\
    \ t) {\n        if (t == nullptr) return;\n        recycle_impl(t->l);\n     \
    \   recycle_impl(t->r);\n        pool.recycle(t);\n    }\n\n    Node* clone_impl(const\
    \ Node* t) {\n        if (t == nullptr) return nullptr;\n        Node* result\
    \ = new_node(t->key);\n        result->l = clone_impl(t->l);\n        result->r\
    \ = clone_impl(t->r);\n        update(result);\n        return result;\n    }\n\
    \n    OrderedSet(Node* node, Compare compare) : root(node), comp(std::move(compare))\
    \ {}\n\n   public:\n    explicit OrderedSet(Compare compare)\n        : root(nullptr),\
    \ comp(std::move(compare)) {}\n\n    OrderedSet() : OrderedSet(Compare()) {}\n\
    \n    OrderedSet(std::initializer_list<T> init, Compare compare = Compare()) :\
    \ OrderedSet(std::move(compare)) {\n        for (const T& x : init) insert(x);\n\
    \    }\n\n    template <typename Iterator>\n    OrderedSet(Iterator first, Iterator\
    \ last, Compare compare = Compare()) : OrderedSet(std::move(compare)) {\n    \
    \    while (first != last) insert(*first++);\n    }\n\n    OrderedSet(const OrderedSet&\
    \ other)\n        : root(nullptr), comp(other.comp) {\n        root = clone_impl(other.root);\n\
    \    }\n\n    OrderedSet(OrderedSet&& other) noexcept\n        : root(std::exchange(other.root,\
    \ nullptr)), comp(std::move(other.comp)) {}\n\n    ~OrderedSet() {\n        recycle_impl(root);\n\
    \    }\n\n    OrderedSet& operator=(OrderedSet other) {\n        swap(other);\n\
    \        return *this;\n    }\n\n    void swap(OrderedSet& other) noexcept {\n\
    \        using std::swap;\n        swap(root, other.root);\n        swap(comp,\
    \ other.comp);\n    }\n\n    int size() const { return subtree_size(root); }\n\
    \    int unique_size() const { return size(); }\n    bool empty() const { return\
    \ root == nullptr; }\n\n    void clear() {\n        recycle_impl(root);\n    \
    \    root = nullptr;\n    }\n\n    bool insert(T key) {\n        bool inserted\
    \ = false;\n        root = insert_impl(root, key, inserted);\n        return inserted;\n\
    \    }\n\n    bool erase(const T& key) {\n        bool erased = false;\n     \
    \   root = erase_impl(root, key, erased);\n        return erased;\n    }\n\n \
    \   bool contains(const T& key) const { return contains_impl(root, key); }\n \
    \   int count(const T& key) const { return contains(key) ? 1 : 0; }\n\n    const\
    \ T* find_by_order(int k) const {\n        assert(0 <= k && k < size());\n   \
    \     return kth_impl(root, k);\n    }\n\n    T kth(int k) const { return *find_by_order(k);\
    \ }\n    int order_of_key(const T& key) const { return order_of_key_impl(root,\
    \ key, false); }\n    int count_less(const T& key) const { return order_of_key(key);\
    \ }\n    int count_less_equal(const T& key) const { return order_of_key_impl(root,\
    \ key, true); }\n    int count_greater(const T& key) const { return size() - count_less_equal(key);\
    \ }\n    int count_greater_equal(const T& key) const { return size() - count_less(key);\
    \ }\n    const T* lower_bound(const T& key) const { return lower_bound_impl(root,\
    \ key, false); }\n    const T* upper_bound(const T& key) const { return lower_bound_impl(root,\
    \ key, true); }\n    const T* min_ge(const T& key) const { return lower_bound(key);\
    \ }\n    const T* min_gt(const T& key) const { return upper_bound(key); }\n  \
    \  const T* max_le(const T& key) const { return max_less_impl(root, key, false);\
    \ }\n    const T* max_lt(const T& key) const { return max_less_impl(root, key,\
    \ true); }\n    const T* min() const { return empty() ? nullptr : kth_impl(root,\
    \ 0); }\n    const T* max() const { return empty() ? nullptr : kth_impl(root,\
    \ size() - 1); }\n\n    std::pair<OrderedSet, OrderedSet> split(const T& key)\
    \ && {\n        auto [l, r] = split_nodes(root, key);\n        root = nullptr;\n\
    \        return {OrderedSet(l, comp), OrderedSet(r, std::move(comp))};\n    }\n\
    \n    OrderedSet merge(OrderedSet other) && {\n        assert(empty() || other.empty()\
    \ || comp(*max(), *other.min()));\n        root = merge_nodes(root, other.root);\n\
    \        other.root = nullptr;\n        return std::move(*this);\n    }\n\n  \
    \  std::vector<T> to_vector() const {\n        std::vector<T> result;\n      \
    \  result.reserve(size());\n        dump_impl(root, result);\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/bst/ordered_set.test.cpp\"\
    \n\n#line 6 \"verify/ds/bst/ordered_set.test.cpp\"\n#include <cstdint>\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    namespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 9 \"verify/ds/bst/ordered_set.test.cpp\"\n#include <set>\n\
    #line 12 \"verify/ds/bst/ordered_set.test.cpp\"\n\nvoid randomized_test() {\n\
    \    m1une::ds::OrderedSet<int> tree;\n    std::set<int> expected;\n    std::uint64_t\
    \ state = 123456789;\n    for (int query = 0; query < 10000; ++query) {\n    \
    \    state = state * 6364136223846793005ULL + 1442695040888963407ULL;\n      \
    \  const int key = int(state >> 32) % 1000;\n        const int type = int(state\
    \ % 5);\n        if (type <= 1) {\n            assert(tree.insert(key) == expected.insert(key).second);\n\
    \        } else if (type == 2) {\n            assert(tree.erase(key) == (expected.erase(key)\
    \ != 0));\n        } else if (type == 3) {\n            assert(tree.contains(key)\
    \ == expected.contains(key));\n            assert(tree.order_of_key(key) == int(std::distance(expected.begin(),\
    \ expected.lower_bound(key))));\n        } else {\n            auto copy = tree;\n\
    \            auto [left, right] = std::move(tree).split(key);\n            std::vector<int>\
    \ expected_left(expected.begin(), expected.lower_bound(key));\n            std::vector<int>\
    \ expected_right(expected.lower_bound(key), expected.end());\n            assert(left.to_vector()\
    \ == expected_left);\n            assert(right.to_vector() == expected_right);\n\
    \            tree = std::move(left).merge(std::move(right));\n            assert(copy.to_vector()\
    \ == tree.to_vector());\n        }\n        assert(tree.size() == int(expected.size()));\n\
    \        assert(tree.to_vector() == std::vector<int>(expected.begin(), expected.end()));\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    randomized_test();\n\n    m1une::ds::OrderedSet<int> split_test\
    \ = {1, 3, 5};\n    auto [small, large] = std::move(split_test).split(3);\n  \
    \  split_test = std::move(small).merge(std::move(large));\n    assert(split_test.size()\
    \ == 3 && split_test.kth(1) == 3);\n\n    int N, Q;\n    fast_input >> N >> Q;\n\
    \n    m1une::ds::OrderedSet<int> st;\n    for (int i = 0; i < N; i++) {\n    \
    \    int a;\n        fast_input >> a;\n        st.insert(a);\n    }\n\n    while\
    \ (Q--) {\n        int type, x;\n        fast_input >> type >> x;\n\n        if\
    \ (type == 0) {\n            st.insert(x);\n        } else if (type == 1) {\n\
    \            st.erase(x);\n        } else if (type == 2) {\n            if (st.size()\
    \ < x) {\n                fast_output << -1 << '\\n';\n            } else {\n\
    \                fast_output << st.kth(x - 1) << '\\n';\n            }\n     \
    \   } else if (type == 3) {\n            fast_output << st.count_less_equal(x)\
    \ << '\\n';\n        } else if (type == 4) {\n            const int* ans = st.max_le(x);\n\
    \            fast_output << (ans ? *ans : -1) << '\\n';\n        } else {\n  \
    \          const int* ans = st.min_ge(x);\n            fast_output << (ans ? *ans\
    \ : -1) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ \"../../../ds/bst/ordered_set.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include \"../../../utilities/fast_io.hpp\"\n#include <iterator>\n#include <set>\n\
    #include <utility>\n#include <vector>\n\nvoid randomized_test() {\n    m1une::ds::OrderedSet<int>\
    \ tree;\n    std::set<int> expected;\n    std::uint64_t state = 123456789;\n \
    \   for (int query = 0; query < 10000; ++query) {\n        state = state * 6364136223846793005ULL\
    \ + 1442695040888963407ULL;\n        const int key = int(state >> 32) % 1000;\n\
    \        const int type = int(state % 5);\n        if (type <= 1) {\n        \
    \    assert(tree.insert(key) == expected.insert(key).second);\n        } else\
    \ if (type == 2) {\n            assert(tree.erase(key) == (expected.erase(key)\
    \ != 0));\n        } else if (type == 3) {\n            assert(tree.contains(key)\
    \ == expected.contains(key));\n            assert(tree.order_of_key(key) == int(std::distance(expected.begin(),\
    \ expected.lower_bound(key))));\n        } else {\n            auto copy = tree;\n\
    \            auto [left, right] = std::move(tree).split(key);\n            std::vector<int>\
    \ expected_left(expected.begin(), expected.lower_bound(key));\n            std::vector<int>\
    \ expected_right(expected.lower_bound(key), expected.end());\n            assert(left.to_vector()\
    \ == expected_left);\n            assert(right.to_vector() == expected_right);\n\
    \            tree = std::move(left).merge(std::move(right));\n            assert(copy.to_vector()\
    \ == tree.to_vector());\n        }\n        assert(tree.size() == int(expected.size()));\n\
    \        assert(tree.to_vector() == std::vector<int>(expected.begin(), expected.end()));\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    randomized_test();\n\n    m1une::ds::OrderedSet<int> split_test\
    \ = {1, 3, 5};\n    auto [small, large] = std::move(split_test).split(3);\n  \
    \  split_test = std::move(small).merge(std::move(large));\n    assert(split_test.size()\
    \ == 3 && split_test.kth(1) == 3);\n\n    int N, Q;\n    fast_input >> N >> Q;\n\
    \n    m1une::ds::OrderedSet<int> st;\n    for (int i = 0; i < N; i++) {\n    \
    \    int a;\n        fast_input >> a;\n        st.insert(a);\n    }\n\n    while\
    \ (Q--) {\n        int type, x;\n        fast_input >> type >> x;\n\n        if\
    \ (type == 0) {\n            st.insert(x);\n        } else if (type == 1) {\n\
    \            st.erase(x);\n        } else if (type == 2) {\n            if (st.size()\
    \ < x) {\n                fast_output << -1 << '\\n';\n            } else {\n\
    \                fast_output << st.kth(x - 1) << '\\n';\n            }\n     \
    \   } else if (type == 3) {\n            fast_output << st.count_less_equal(x)\
    \ << '\\n';\n        } else if (type == 4) {\n            const int* ans = st.max_le(x);\n\
    \            fast_output << (ans ? *ans : -1) << '\\n';\n        } else {\n  \
    \          const int* ans = st.min_ge(x);\n            fast_output << (ans ? *ans\
    \ : -1) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/bst/ordered_set.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/bst/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/ordered_set.test.cpp
- /verify/verify/ds/bst/ordered_set.test.cpp.html
title: verify/ds/bst/ordered_set.test.cpp
---
