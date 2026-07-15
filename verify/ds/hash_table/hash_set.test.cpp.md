---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/hash_table/hash_common.hpp
    title: ds/hash_table/hash_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/hash_table/hash_set.hpp
    title: Hash Set
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
  bundledCode: "#line 1 \"verify/ds/hash_table/hash_set.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\n\n\
    #line 1 \"ds/hash_table/hash_set.hpp\"\n\n\n\n#line 1 \"ds/hash_table/hash_common.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <chrono>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <new>\n#include <type_traits>\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace ds {\nnamespace detail {\n\ninline std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n    x += 0x9e3779b97f4a7c15;\n    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n    return x ^ (x >> 31);\n}\n\
    \ntemplate <typename Key, typename Hash>\nstd::size_t mixed_hash(const Key& key,\
    \ const Hash& hash) {\n    static const std::uint64_t fixed_random =\n       \
    \ std::chrono::steady_clock::now().time_since_epoch().count();\n    return static_cast<std::size_t>(splitmix64(static_cast<std::uint64_t>(hash(key))\
    \ + fixed_random));\n}\n\ninline std::size_t bit_ceil(std::size_t n) {\n    std::size_t\
    \ result = 1;\n    while (result < n) result <<= 1;\n    return result;\n}\n\n\
    inline std::size_t bucket_count_for(std::size_t expected_size) {\n    return bit_ceil(std::max<std::size_t>(16,\
    \ expected_size * 10 / 7 + 1));\n}\n\ntemplate <typename T>\nstruct Slot {\n \
    \   alignas(T) unsigned char storage[sizeof(T)];\n\n    T* ptr() {\n        return\
    \ std::launder(reinterpret_cast<T*>(storage));\n    }\n\n    const T* ptr() const\
    \ {\n        return std::launder(reinterpret_cast<const T*>(storage));\n    }\n\
    \n    template <typename... Args>\n    void construct(Args&&... args) {\n    \
    \    ::new (static_cast<void*>(storage)) T(std::forward<Args>(args)...);\n   \
    \ }\n\n    void destroy() {\n        if constexpr (!std::is_trivially_destructible_v<T>)\
    \ {\n            ptr()->~T();\n        }\n    }\n};\n\n}  // namespace detail\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 5 \"ds/hash_table/hash_set.hpp\"\
    \n\n#line 8 \"ds/hash_table/hash_set.hpp\"\n#include <functional>\n#include <initializer_list>\n\
    #line 11 \"ds/hash_table/hash_set.hpp\"\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename T, typename Hash = std::hash<T>, typename\
    \ KeyEqual = std::equal_to<T>>\nstruct HashSet {\n   private:\n    static constexpr\
    \ unsigned char EMPTY = 0;\n    static constexpr unsigned char DELETED = 1;\n\
    \    static constexpr std::size_t npos = static_cast<std::size_t>(-1);\n\n   \
    \ std::vector<unsigned char> ctrl;\n    std::vector<detail::Slot<T>> data;\n \
    \   std::size_t _size = 0;\n    std::size_t _deleted = 0;\n    Hash hasher;\n\
    \    KeyEqual key_equal;\n\n    std::size_t mask() const {\n        return ctrl.size()\
    \ - 1;\n    }\n\n    std::size_t make_hash(const T& key) const {\n        return\
    \ detail::mixed_hash(key, hasher);\n    }\n\n    static unsigned char fingerprint(std::size_t\
    \ h) {\n        return static_cast<unsigned char>(2 + (h >> (sizeof(std::size_t)\
    \ * 8 - 7)));\n    }\n\n    static bool occupied(unsigned char c) {\n        return\
    \ c >= 2;\n    }\n\n    T* value_at(std::size_t i) {\n        return data[i].ptr();\n\
    \    }\n\n    const T* value_at(std::size_t i) const {\n        return data[i].ptr();\n\
    \    }\n\n    void destroy_all() {\n        for (std::size_t i = 0; i < ctrl.size();\
    \ i++) {\n            if (occupied(ctrl[i])) data[i].destroy();\n        }\n \
    \   }\n\n    void reset(std::size_t bucket_count) {\n        destroy_all();\n\
    \        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));\n\
    \        ctrl.assign(bucket_count, EMPTY);\n        data.clear();\n        data.resize(bucket_count);\n\
    \        _size = 0;\n        _deleted = 0;\n    }\n\n    std::size_t find_index_with_hash(const\
    \ T& key, std::size_t h) const {\n        const unsigned char fp = fingerprint(h);\n\
    \        std::size_t i = h & mask();\n        while (true) {\n            const\
    \ unsigned char c = ctrl[i];\n            if (c == EMPTY) return npos;\n     \
    \       if (c == fp && key_equal(*value_at(i), key)) return i;\n            i\
    \ = (i + 1) & mask();\n        }\n    }\n\n    std::size_t find_index(const T&\
    \ key) const {\n        return find_index_with_hash(key, make_hash(key));\n  \
    \  }\n\n    template <typename U>\n    void insert_existing(U&& key, std::size_t\
    \ h) {\n        std::size_t i = h & mask();\n        while (occupied(ctrl[i]))\
    \ i = (i + 1) & mask();\n        ctrl[i] = fingerprint(h);\n        data[i].construct(std::forward<U>(key));\n\
    \        _size++;\n    }\n\n    void rebuild(std::size_t bucket_count) {\n   \
    \     std::vector<unsigned char> old_ctrl = std::move(ctrl);\n        std::vector<detail::Slot<T>>\
    \ old_data = std::move(data);\n\n        ctrl.clear();\n        data.clear();\n\
    \        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));\n\
    \        ctrl.assign(bucket_count, EMPTY);\n        data.resize(bucket_count);\n\
    \        _size = 0;\n        _deleted = 0;\n\n        for (std::size_t i = 0;\
    \ i < old_ctrl.size(); i++) {\n            if (occupied(old_ctrl[i])) {\n    \
    \            T* value = old_data[i].ptr();\n                insert_existing(std::move(*value),\
    \ make_hash(*value));\n                old_data[i].destroy();\n            }\n\
    \        }\n    }\n\n    void ensure_for_insert() {\n        const std::size_t\
    \ used = _size + _deleted;\n        if ((used + 1) * 10 >= ctrl.size() * 7) {\n\
    \            rebuild(ctrl.size() * 2);\n        } else if (_deleted > _size &&\
    \ (_size + 1) * 10 < ctrl.size() * 7) {\n            rebuild(ctrl.size());\n \
    \       }\n    }\n\n    template <typename U>\n    bool insert_impl(U&& key) {\n\
    \        ensure_for_insert();\n\n        const std::size_t h = make_hash(key);\n\
    \        const unsigned char fp = fingerprint(h);\n        std::size_t first_deleted\
    \ = npos;\n        std::size_t i = h & mask();\n        while (true) {\n     \
    \       const unsigned char c = ctrl[i];\n            if (occupied(c)) {\n   \
    \             if (c == fp && key_equal(*value_at(i), key)) return false;\n   \
    \         } else if (c == DELETED) {\n                if (first_deleted == npos)\
    \ first_deleted = i;\n            } else {\n                const std::size_t\
    \ pos = first_deleted == npos ? i : first_deleted;\n                if (first_deleted\
    \ != npos) _deleted--;\n                ctrl[pos] = fp;\n                data[pos].construct(std::forward<U>(key));\n\
    \                _size++;\n                return true;\n            }\n     \
    \       i = (i + 1) & mask();\n        }\n    }\n\n   public:\n    HashSet() :\
    \ hasher(Hash()), key_equal(KeyEqual()) {\n        reset(16);\n    }\n\n    explicit\
    \ HashSet(std::size_t reserve_count, Hash hash_fn = Hash(), KeyEqual equal_fn\
    \ = KeyEqual())\n        : hasher(std::move(hash_fn)), key_equal(std::move(equal_fn))\
    \ {\n        reset(detail::bucket_count_for(reserve_count));\n    }\n\n    HashSet(std::initializer_list<T>\
    \ init, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())\n        : HashSet(init.size(),\
    \ std::move(hash_fn), std::move(equal_fn)) {\n        for (const T& x : init)\
    \ insert(x);\n    }\n\n    template <typename Iterator>\n    HashSet(Iterator\
    \ first, Iterator last, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())\n\
    \        : HashSet(0, std::move(hash_fn), std::move(equal_fn)) {\n        while\
    \ (first != last) {\n            insert(*first);\n            ++first;\n     \
    \   }\n    }\n\n    HashSet(const HashSet& other) : hasher(other.hasher), key_equal(other.key_equal)\
    \ {\n        ctrl.assign(other.ctrl.size(), EMPTY);\n        data.resize(other.data.size());\n\
    \        for (std::size_t i = 0; i < other.ctrl.size(); i++) {\n            ctrl[i]\
    \ = other.ctrl[i];\n            if (occupied(other.ctrl[i])) data[i].construct(*other.value_at(i));\n\
    \        }\n        _size = other._size;\n        _deleted = other._deleted;\n\
    \    }\n\n    HashSet(HashSet&& other) noexcept\n        : ctrl(std::move(other.ctrl)),\n\
    \          data(std::move(other.data)),\n          _size(other._size),\n     \
    \     _deleted(other._deleted),\n          hasher(std::move(other.hasher)),\n\
    \          key_equal(std::move(other.key_equal)) {\n        other.ctrl.clear();\n\
    \        other.data.clear();\n        other._size = 0;\n        other._deleted\
    \ = 0;\n    }\n\n    HashSet& operator=(const HashSet& other) {\n        if (this\
    \ == &other) return *this;\n        HashSet copy(other);\n        *this = std::move(copy);\n\
    \        return *this;\n    }\n\n    HashSet& operator=(HashSet&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        destroy_all();\n     \
    \   ctrl = std::move(other.ctrl);\n        data = std::move(other.data);\n   \
    \     _size = other._size;\n        _deleted = other._deleted;\n        hasher\
    \ = std::move(other.hasher);\n        key_equal = std::move(other.key_equal);\n\
    \        other.ctrl.clear();\n        other.data.clear();\n        other._size\
    \ = 0;\n        other._deleted = 0;\n        return *this;\n    }\n\n    ~HashSet()\
    \ {\n        destroy_all();\n    }\n\n    int size() const {\n        return static_cast<int>(_size);\n\
    \    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\n    std::size_t\
    \ bucket_count() const {\n        return ctrl.size();\n    }\n\n    double load_factor()\
    \ const {\n        return static_cast<double>(_size) / static_cast<double>(ctrl.size());\n\
    \    }\n\n    void clear() {\n        reset(ctrl.size());\n    }\n\n    void reserve(std::size_t\
    \ count) {\n        const std::size_t target = detail::bucket_count_for(count);\n\
    \        if (target > ctrl.size() || _deleted > 0) rebuild(std::max(target, ctrl.size()));\n\
    \    }\n\n    bool insert(const T& key) {\n        return insert_impl(key);\n\
    \    }\n\n    bool insert(T&& key) {\n        return insert_impl(std::move(key));\n\
    \    }\n\n    bool erase(const T& key) {\n        const std::size_t h = make_hash(key);\n\
    \        const std::size_t i = find_index_with_hash(key, h);\n        if (i ==\
    \ npos) return false;\n        data[i].destroy();\n        ctrl[i] = DELETED;\n\
    \        _size--;\n        _deleted++;\n        return true;\n    }\n\n    const\
    \ T* find(const T& key) const {\n        const std::size_t i = find_index(key);\n\
    \        return i == npos ? nullptr : value_at(i);\n    }\n\n    bool contains(const\
    \ T& key) const {\n        return find_index(key) != npos;\n    }\n\n    int count(const\
    \ T& key) const {\n        return contains(key) ? 1 : 0;\n    }\n\n    std::vector<T>\
    \ to_vector() const {\n        std::vector<T> result;\n        result.reserve(_size);\n\
    \        for (std::size_t i = 0; i < ctrl.size(); i++) {\n            if (occupied(ctrl[i]))\
    \ result.push_back(*value_at(i));\n        }\n        return result;\n    }\n\
    };\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/hash_table/hash_set.test.cpp\"\
    \n\n#include <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <charconv>\n#line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include\
    \ <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#line 15 \"utilities/fast_io.hpp\"\n#include\
    \ <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\
    \n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct\
    \ is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/ds/hash_table/hash_set.test.cpp\"\
    \n#include <unordered_set>\n#line 10 \"verify/ds/hash_table/hash_set.test.cpp\"\
    \n\nvoid self_test() {\n    m1une::ds::HashSet<long long> st;\n    assert(st.empty());\n\
    \    assert(st.insert(5));\n    assert(!st.insert(5));\n    assert(st.insert(1));\n\
    \    assert(st.contains(5));\n    assert(st.count(1) == 1);\n    assert(st.erase(5));\n\
    \    assert(!st.contains(5));\n    assert(!st.erase(5));\n\n    std::vector<long\
    \ long> xs;\n    for (int i = 0; i < 1000; i++) xs.push_back(i * 1000000007LL);\n\
    \    m1une::ds::HashSet<long long> large(xs.begin(), xs.end());\n    for (long\
    \ long x : xs) assert(large.contains(x));\n    for (int i = 0; i < 500; i++) assert(large.erase(xs[i]));\n\
    \    for (int i = 0; i < 500; i++) assert(!large.contains(xs[i]));\n    for (int\
    \ i = 500; i < 1000; i++) assert(large.contains(xs[i]));\n    auto copied_large\
    \ = large;\n    auto moved_large = std::move(copied_large);\n    for (int i =\
    \ 500; i < 1000; i++) assert(moved_large.contains(xs[i]));\n\n    m1une::ds::HashSet<int>\
    \ tested;\n    std::unordered_set<int> expected;\n    unsigned long long seed\
    \ = 123456789;\n    for (int q = 0; q < 10000; q++) {\n        seed = seed * 6364136223846793005ULL\
    \ + 1442695040888963407ULL;\n        int x = static_cast<int>((seed >> 32) % 400)\
    \ - 200;\n        int type = static_cast<int>(seed % 4);\n        if (type ==\
    \ 0) {\n            assert(tested.insert(x) == (expected.insert(x).second));\n\
    \        } else if (type == 1) {\n            assert(tested.erase(x) == (expected.erase(x)\
    \ == 1));\n        } else {\n            assert(tested.contains(x) == (expected.find(x)\
    \ != expected.end()));\n            assert(tested.count(x) == static_cast<int>(expected.count(x)));\n\
    \        }\n        assert(tested.size() == static_cast<int>(expected.size()));\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    self_test();\n    int n;\n    fast_input >> n;\n    m1une::ds::HashSet<std::string>\
    \ dictionary;\n    while (n--) {\n        std::string command, word;\n       \
    \ fast_input >> command >> word;\n        if (command == \"insert\") {\n     \
    \       dictionary.insert(word);\n        } else {\n            fast_output <<\
    \ (dictionary.contains(word) ? \"yes\" : \"no\") << '\\n';\n        }\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n\n#include \"../../../ds/hash_table/hash_set.hpp\"\n\n#include <cassert>\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n#include <string>\n#include <unordered_set>\n\
    #include <vector>\n\nvoid self_test() {\n    m1une::ds::HashSet<long long> st;\n\
    \    assert(st.empty());\n    assert(st.insert(5));\n    assert(!st.insert(5));\n\
    \    assert(st.insert(1));\n    assert(st.contains(5));\n    assert(st.count(1)\
    \ == 1);\n    assert(st.erase(5));\n    assert(!st.contains(5));\n    assert(!st.erase(5));\n\
    \n    std::vector<long long> xs;\n    for (int i = 0; i < 1000; i++) xs.push_back(i\
    \ * 1000000007LL);\n    m1une::ds::HashSet<long long> large(xs.begin(), xs.end());\n\
    \    for (long long x : xs) assert(large.contains(x));\n    for (int i = 0; i\
    \ < 500; i++) assert(large.erase(xs[i]));\n    for (int i = 0; i < 500; i++) assert(!large.contains(xs[i]));\n\
    \    for (int i = 500; i < 1000; i++) assert(large.contains(xs[i]));\n    auto\
    \ copied_large = large;\n    auto moved_large = std::move(copied_large);\n   \
    \ for (int i = 500; i < 1000; i++) assert(moved_large.contains(xs[i]));\n\n  \
    \  m1une::ds::HashSet<int> tested;\n    std::unordered_set<int> expected;\n  \
    \  unsigned long long seed = 123456789;\n    for (int q = 0; q < 10000; q++) {\n\
    \        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n    \
    \    int x = static_cast<int>((seed >> 32) % 400) - 200;\n        int type = static_cast<int>(seed\
    \ % 4);\n        if (type == 0) {\n            assert(tested.insert(x) == (expected.insert(x).second));\n\
    \        } else if (type == 1) {\n            assert(tested.erase(x) == (expected.erase(x)\
    \ == 1));\n        } else {\n            assert(tested.contains(x) == (expected.find(x)\
    \ != expected.end()));\n            assert(tested.count(x) == static_cast<int>(expected.count(x)));\n\
    \        }\n        assert(tested.size() == static_cast<int>(expected.size()));\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    self_test();\n    int n;\n    fast_input >> n;\n    m1une::ds::HashSet<std::string>\
    \ dictionary;\n    while (n--) {\n        std::string command, word;\n       \
    \ fast_input >> command >> word;\n        if (command == \"insert\") {\n     \
    \       dictionary.insert(word);\n        } else {\n            fast_output <<\
    \ (dictionary.contains(word) ? \"yes\" : \"no\") << '\\n';\n        }\n    }\n\
    }\n"
  dependsOn:
  - ds/hash_table/hash_set.hpp
  - ds/hash_table/hash_common.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/hash_table/hash_set.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/hash_table/hash_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/hash_table/hash_set.test.cpp
- /verify/verify/ds/hash_table/hash_set.test.cpp.html
title: verify/ds/hash_table/hash_set.test.cpp
---
