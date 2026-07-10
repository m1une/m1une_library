---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/rectangle_union_area.hpp
    title: Area of Union of Rectangles
  - icon: ':question:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/area_of_union_of_rectangles
    links:
    - https://judge.yosupo.jp/problem/area_of_union_of_rectangles
  bundledCode: "#line 1 \"verify/geometry/rectangle_union_area.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/area_of_union_of_rectangles\"\n\n\
    #line 1 \"geometry/rectangle_union_area.hpp\"\n\n\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#include <cmath>\n#include <concepts>\n#include <cassert>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace geometry {\n\ntemplate <typename T>\nconcept Coordinate\
    \ = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate\
    \ <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>, __int128_t,\
    \ long double>;\n\ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\
    \n    constexpr Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value)\
    \ : x(x_value), y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr\
    \ Point(const Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n\n    constexpr Point& operator+=(const Point& other) {\n        x += other.x;\n\
    \        y += other.y;\n        return *this;\n    }\n\n    constexpr Point& operator-=(const\
    \ Point& other) {\n        x -= other.x;\n        y -= other.y;\n        return\
    \ *this;\n    }\n\n    constexpr Point operator+() const {\n        return *this;\n\
    \    }\n\n    constexpr Point operator-() const {\n        return Point(-x, -y);\n\
    \    }\n\n    friend constexpr Point operator+(Point left, const Point& right)\
    \ {\n        return left += right;\n    }\n\n    friend constexpr Point operator-(Point\
    \ left, const Point& right) {\n        return left -= right;\n    }\n\n    friend\
    \ constexpr bool operator==(const Point&, const Point&) = default;\n\n    friend\
    \ constexpr bool operator<(const Point& left, const Point& right) {\n        if\
    \ (left.x != right.x) return left.x < right.x;\n        return left.y < right.y;\n\
    \    }\n};\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator*(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ * Result(scalar),\n        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate\
    \ <typename Scalar, Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator*(Scalar scalar, const Point<T>& point) {\n    return point * scalar;\n\
    }\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ / Result(scalar),\n        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> dot(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a,\
    \ const Point<T>& b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y)\
    \ - W(a.y) * W(b.x);\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n\
    \    const Point<T>& origin,\n    const Point<T>& a,\n    const Point<T>& b\n\
    ) {\n    using W = wide_type<T>;\n    W ax = W(a.x) - W(origin.x);\n    W ay =\
    \ W(a.y) - W(origin.y);\n    W bx = W(b.x) - W(origin.x);\n    W by = W(b.y) -\
    \ W(origin.y);\n    return ax * by - ay * bx;\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> norm2(const Point<T>& point) {\n    return dot(point, point);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> distance2(const Point<T>&\
    \ a, const Point<T>& b) {\n    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n\
    \    W dy = W(a.y) - W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double norm(const Point<T>& point) {\n    return std::hypot(\n    \
    \    static_cast<long double>(point.x),\n        static_cast<long double>(point.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& a,\
    \ const Point<T>& b) {\n    return std::hypot(\n        static_cast<long double>(a.x)\
    \ - static_cast<long double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long\
    \ double>(b.y)\n    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\n\
    requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\nconstexpr Point<long\
    \ double> internal_division_point(\n    const Point<T>& a,\n    const Point<T>&\
    \ b,\n    M m,\n    N n\n) {\n    long double first_ratio = static_cast<long double>(m);\n\
    \    long double second_ratio = static_cast<long double>(n);\n    long double\
    \ denominator = first_ratio + second_ratio;\n    assert(denominator != 0);\n \
    \   Point<long double> first(a);\n    Point<long double> direction = Point<long\
    \ double>(b) - first;\n    return first + direction * (first_ratio / denominator);\n\
    }\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> external_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio -\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr int sign(wide_type<T> value, long double eps = 1e-12L) {\n   \
    \ if constexpr (std::integral<T>) {\n        return (value > 0) - (value < 0);\n\
    \    } else {\n        return (value > eps) - (value < -eps);\n    }\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ bool collinear(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps)\
    \ == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> rotate(const Point<T>&\
    \ point, long double angle) {\n    long double cosine = std::cos(angle);\n   \
    \ long double sine = std::sin(angle);\n    return Point<long double>(\n      \
    \  static_cast<long double>(point.x) * cosine -\n            static_cast<long\
    \ double>(point.y) * sine,\n        static_cast<long double>(point.x) * sine +\n\
    \            static_cast<long double>(point.y) * cosine\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> normalized(const Point<T>& point) {\n   \
    \ long double length = norm(point);\n    assert(length != 0);\n    return Point<long\
    \ double>(\n        static_cast<long double>(point.x) / length,\n        static_cast<long\
    \ double>(point.y) / length\n    );\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 5 \"geometry/rectangle_union_area.hpp\"\n\n#include <algorithm>\n\
    #line 8 \"geometry/rectangle_union_area.hpp\"\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct AxisAlignedRectangle\
    \ {\n    T left;\n    T bottom;\n    T right;\n    T top;\n\n    constexpr AxisAlignedRectangle()\n\
    \        : left(0), bottom(0), right(0), top(0) {}\n\n    constexpr AxisAlignedRectangle(\n\
    \        T left_value,\n        T bottom_value,\n        T right_value,\n    \
    \    T top_value\n    )\n        : left(left_value),\n          bottom(bottom_value),\n\
    \          right(right_value),\n          top(top_value) {}\n\n    friend constexpr\
    \ bool operator==(\n        const AxisAlignedRectangle&,\n        const AxisAlignedRectangle&\n\
    \    ) = default;\n};\n\nnamespace rectangle_union_area_detail {\n\ntemplate <Coordinate\
    \ T>\nstruct Event {\n    T x;\n    T bottom;\n    T top;\n    int delta;\n\n\
    \    Event(T x_value, T bottom_value, T top_value, int delta_value)\n        :\
    \ x(x_value),\n          bottom(bottom_value),\n          top(top_value),\n  \
    \        delta(delta_value) {}\n};\n\ntemplate <Coordinate T>\nstruct CoveredLengthTree\
    \ {\n    using Wide = wide_type<T>;\n\n    int interval_count;\n    const std::vector<T>&\
    \ coordinates;\n    std::vector<int> cover;\n    std::vector<Wide> covered;\n\n\
    \    explicit CoveredLengthTree(const std::vector<T>& values)\n        : interval_count(std::max(0,\
    \ int(values.size()) - 1)),\n          coordinates(values),\n          cover(std::max(1,\
    \ 4 * interval_count), 0),\n          covered(std::max(1, 4 * interval_count),\
    \ Wide(0)) {}\n\n    void pull(int node, int left, int right) {\n        if (cover[node]\
    \ > 0) {\n            covered[node] =\n                Wide(coordinates[right])\
    \ - Wide(coordinates[left]);\n        } else if (right - left == 1) {\n      \
    \      covered[node] = 0;\n        } else {\n            covered[node] = covered[2\
    \ * node] + covered[2 * node + 1];\n        }\n    }\n\n    void add(\n      \
    \  int query_left,\n        int query_right,\n        int delta,\n        int\
    \ node,\n        int left,\n        int right\n    ) {\n        if (query_right\
    \ <= left || right <= query_left) return;\n        if (query_left <= left && right\
    \ <= query_right) {\n            cover[node] += delta;\n            assert(cover[node]\
    \ >= 0);\n            pull(node, left, right);\n            return;\n        }\n\
    \        int middle = (left + right) / 2;\n        add(query_left, query_right,\
    \ delta, 2 * node, left, middle);\n        add(\n            query_left,\n   \
    \         query_right,\n            delta,\n            2 * node + 1,\n      \
    \      middle,\n            right\n        );\n        pull(node, left, right);\n\
    \    }\n\n    void add(int left, int right, int delta) {\n        if (left >=\
    \ right) return;\n        assert(0 <= left && left < right && right <= interval_count);\n\
    \        add(left, right, delta, 1, 0, interval_count);\n    }\n\n    Wide length()\
    \ const {\n        return interval_count == 0 ? Wide(0) : covered[1];\n    }\n\
    };\n\n}  // namespace rectangle_union_area_detail\n\ntemplate <Coordinate T>\n\
    wide_type<T> rectangle_union_area(\n    const std::vector<AxisAlignedRectangle<T>>&\
    \ rectangles\n) {\n    using Wide = wide_type<T>;\n    using Event = rectangle_union_area_detail::Event<T>;\n\
    \n    std::vector<Event> events;\n    std::vector<T> y_coordinates;\n    events.reserve(2\
    \ * rectangles.size());\n    y_coordinates.reserve(2 * rectangles.size());\n \
    \   for (const AxisAlignedRectangle<T>& rectangle : rectangles) {\n        assert(rectangle.left\
    \ <= rectangle.right);\n        assert(rectangle.bottom <= rectangle.top);\n \
    \       if (\n            rectangle.left == rectangle.right ||\n            rectangle.bottom\
    \ == rectangle.top\n        ) {\n            continue;\n        }\n        events.emplace_back(\n\
    \            rectangle.left,\n            rectangle.bottom,\n            rectangle.top,\n\
    \            1\n        );\n        events.emplace_back(\n            rectangle.right,\n\
    \            rectangle.bottom,\n            rectangle.top,\n            -1\n \
    \       );\n        y_coordinates.push_back(rectangle.bottom);\n        y_coordinates.push_back(rectangle.top);\n\
    \    }\n    if (events.empty()) return Wide(0);\n\n    std::sort(y_coordinates.begin(),\
    \ y_coordinates.end());\n    y_coordinates.erase(\n        std::unique(y_coordinates.begin(),\
    \ y_coordinates.end()),\n        y_coordinates.end()\n    );\n    std::sort(events.begin(),\
    \ events.end(), [](const Event& a, const Event& b) {\n        return a.x < b.x;\n\
    \    });\n\n    rectangle_union_area_detail::CoveredLengthTree<T> tree(y_coordinates);\n\
    \    Wide area = 0;\n    T previous_x = events.front().x;\n    int event_index\
    \ = 0;\n    while (event_index < int(events.size())) {\n        T x = events[event_index].x;\n\
    \        area += tree.length() * (Wide(x) - Wide(previous_x));\n\n        int\
    \ next = event_index;\n        while (next < int(events.size()) && events[next].x\
    \ == x) {\n            int bottom = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(),\n                    y_coordinates.end(),\n\
    \                    events[next].bottom\n                ) - y_coordinates.begin()\n\
    \            );\n            int top = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(),\n                    y_coordinates.end(),\n\
    \                    events[next].top\n                ) - y_coordinates.begin()\n\
    \            );\n            tree.add(bottom, top, events[next].delta);\n    \
    \        next++;\n        }\n        previous_x = x;\n        event_index = next;\n\
    \    }\n    return area;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstring>\n#include <iterator>\n#include <string>\n\
    #line 11 \"utilities/fast_io.hpp\"\n#include <utility>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ bool has_val_method_v = has_val_method<T>::value;\n\n}  // namespace internal\n\
    \nstruct FastInput {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n\
    \    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int _position;\n\
    \    int _length;\n\n    bool prepare_number() {\n        if (_length - _position\
    \ >= 32) return true;\n        const int remaining = _length - _position;\n  \
    \      if (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n\
    \        const int added = int(std::fread(_buffer + remaining, 1, buffer_size\
    \ - remaining, _stream));\n        _position = 0;\n        _length = remaining\
    \ + added;\n        if (_length < buffer_size) _buffer[_length] = '\\0';\n   \
    \     return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
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
    \        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (std::is_signed_v<T>) {\n            T result = 0;\n  \
    \          while ('0' <= c && c <= '9') {\n                int digit = c - '0';\n\
    \                result = negative ? result * 10 - digit : result * 10 + digit;\n\
    \                c = static_cast<unsigned char>(_buffer[_position++]);\n     \
    \       }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                result = result\
    \ * 10 + T(c - '0');\n                c = static_cast<unsigned char>(_buffer[_position++]);\n\
    \            }\n            value = negative ? T(0) - result : result;\n     \
    \   }\n        if (_position > _length) _position = _length;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n\
    \            && !std::is_integral_v<T>\n            && !internal::is_range_v<T>,\n\
    \        bool\n    >\n    read(T& value) {\n        long long x;\n        if (!read(x))\
    \ return false;\n        value = T(x);\n        return true;\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \ <class T>\n    FastInput& operator>>(T& value) {\n        read(value);\n   \
    \     return *this;\n    }\n};\n\nstruct FastOutput {\n    static constexpr int\
    \ buffer_size = 1 << 20;\n\n   private:\n    inline static constexpr auto digit_quads\
    \ = [] {\n        std::array<char, 40000> result{};\n        for (int i = 0; i\
    \ < 10000; i++) {\n            int value = i;\n            for (int j = 3; j >=\
    \ 0; j--) {\n                result[4 * i + j] = char('0' + value % 10);\n   \
    \             value /= 10;\n            }\n        }\n        return result;\n\
    \    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int\
    \ _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream), _position(0) {}\n\n    FastOutput(const FastOutput&)\
    \ = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput()\
    \ {\n        flush();\n    }\n\n    void flush() {\n        if (_position == 0)\
    \ return;\n        std::fwrite(_buffer, 1, _position, _stream);\n        _position\
    \ = 0;\n    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        unsigned\
    \ chunks[16];\n        int count = 0;\n        while (magnitude >= 10000) {\n\
    \            const Unsigned quotient = magnitude / 10000;\n            chunks[count++]\
    \ = unsigned(magnitude - quotient * 10000);\n            magnitude = quotient;\n\
    \        }\n        if (_position > buffer_size - 64) flush();\n        const\
    \ unsigned leading = unsigned(magnitude);\n        const char* first = digit_quads.data()\
    \ + 4 * leading;\n        int skip = leading < 10 ? 3 : leading < 100 ? 2 : leading\
    \ < 1000 ? 1 : 0;\n        for (; skip < 4; skip++) _buffer[_position++] = first[skip];\n\
    \        while (count--) {\n            const char* digits = digit_quads.data()\
    \ + 4 * chunks[count];\n            std::memcpy(_buffer + _position, digits, 4);\n\
    \            _position += 4;\n        }\n    }\n\n    template <class T>\n   \
    \ std::enable_if_t<\n        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
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
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n\n    template <class T>\n    FastOutput&\
    \ operator<<(const T& value) {\n        write(value);\n        return *this;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 5 \"\
    verify/geometry/rectangle_union_area.test.cpp\"\n\n#line 8 \"verify/geometry/rectangle_union_area.test.cpp\"\
    \n#include <cstdint>\n#line 10 \"verify/geometry/rectangle_union_area.test.cpp\"\
    \n\nnamespace {\n\nusing Rectangle = m1une::geometry::AxisAlignedRectangle<long\
    \ long>;\n\nlong long brute(const std::vector<Rectangle>& rectangles) {\n    long\
    \ long result = 0;\n    for (int x = -8; x < 8; x++) {\n        for (int y = -8;\
    \ y < 8; y++) {\n            bool covered = false;\n            for (const Rectangle&\
    \ rectangle : rectangles) {\n                if (\n                    rectangle.left\
    \ <= x && x < rectangle.right &&\n                    rectangle.bottom <= y &&\
    \ y < rectangle.top\n                ) {\n                    covered = true;\n\
    \                }\n            }\n            result += covered;\n        }\n\
    \    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::vector<Rectangle>\
    \ rectangles;\n    assert(m1une::geometry::rectangle_union_area(rectangles) ==\
    \ 0);\n\n    rectangles.emplace_back(0, 0, 4, 3);\n    rectangles.emplace_back(2,\
    \ 1, 6, 5);\n    assert(m1une::geometry::rectangle_union_area(rectangles) == 24);\n\
    \n    rectangles.emplace_back(1, 1, 1, 10);\n    rectangles.emplace_back(-5, 2,\
    \ 8, 2);\n    assert(m1une::geometry::rectangle_union_area(rectangles) == 24);\n\
    \n    std::vector<Rectangle> large;\n    large.emplace_back(\n        -4'000'000'000LL,\n\
    \        -3'000'000'000LL,\n        4'000'000'000LL,\n        3'000'000'000LL\n\
    \    );\n    __int128 expected = __int128(8'000'000'000LL) * 6'000'000'000LL;\n\
    \    assert(m1une::geometry::rectangle_union_area(large) == expected);\n}\n\n\
    void test_randomized() {\n    std::uint64_t state = 1414213562ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    for (int trial = 0; trial < 5000; trial++) {\n\
    \        int count = int(random() % 15);\n        std::vector<Rectangle> rectangles;\n\
    \        for (int i = 0; i < count; i++) {\n            long long left = static_cast<long\
    \ long>(random() % 16) - 8;\n            long long right = static_cast<long long>(random()\
    \ % 16) - 8;\n            long long bottom = static_cast<long long>(random() %\
    \ 16) - 8;\n            long long top = static_cast<long long>(random() % 16)\
    \ - 8;\n            if (right < left) std::swap(left, right);\n            if\
    \ (top < bottom) std::swap(bottom, top);\n            rectangles.emplace_back(left,\
    \ bottom, right, top);\n        }\n        assert(\n            m1une::geometry::rectangle_union_area(rectangles)\n\
    \            == brute(rectangles)\n        );\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    test_edge_cases();\n    test_randomized();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    int n = 0;\n    input.read(n);\n\
    \    std::vector<Rectangle> rectangles;\n    rectangles.reserve(n);\n    for (int\
    \ i = 0; i < n; i++) {\n        long long left = 0, bottom = 0, right = 0, top\
    \ = 0;\n        input.read(left, bottom, right, top);\n        rectangles.emplace_back(left,\
    \ bottom, right, top);\n    }\n    long long answer = static_cast<long long>(\n\
    \        m1une::geometry::rectangle_union_area(rectangles)\n    );\n    output.println(answer);\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/area_of_union_of_rectangles\"\
    \n\n#include \"../../geometry/rectangle_union_area.hpp\"\n#include \"../../utilities/fast_io.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\
    \nnamespace {\n\nusing Rectangle = m1une::geometry::AxisAlignedRectangle<long\
    \ long>;\n\nlong long brute(const std::vector<Rectangle>& rectangles) {\n    long\
    \ long result = 0;\n    for (int x = -8; x < 8; x++) {\n        for (int y = -8;\
    \ y < 8; y++) {\n            bool covered = false;\n            for (const Rectangle&\
    \ rectangle : rectangles) {\n                if (\n                    rectangle.left\
    \ <= x && x < rectangle.right &&\n                    rectangle.bottom <= y &&\
    \ y < rectangle.top\n                ) {\n                    covered = true;\n\
    \                }\n            }\n            result += covered;\n        }\n\
    \    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::vector<Rectangle>\
    \ rectangles;\n    assert(m1une::geometry::rectangle_union_area(rectangles) ==\
    \ 0);\n\n    rectangles.emplace_back(0, 0, 4, 3);\n    rectangles.emplace_back(2,\
    \ 1, 6, 5);\n    assert(m1une::geometry::rectangle_union_area(rectangles) == 24);\n\
    \n    rectangles.emplace_back(1, 1, 1, 10);\n    rectangles.emplace_back(-5, 2,\
    \ 8, 2);\n    assert(m1une::geometry::rectangle_union_area(rectangles) == 24);\n\
    \n    std::vector<Rectangle> large;\n    large.emplace_back(\n        -4'000'000'000LL,\n\
    \        -3'000'000'000LL,\n        4'000'000'000LL,\n        3'000'000'000LL\n\
    \    );\n    __int128 expected = __int128(8'000'000'000LL) * 6'000'000'000LL;\n\
    \    assert(m1une::geometry::rectangle_union_area(large) == expected);\n}\n\n\
    void test_randomized() {\n    std::uint64_t state = 1414213562ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    for (int trial = 0; trial < 5000; trial++) {\n\
    \        int count = int(random() % 15);\n        std::vector<Rectangle> rectangles;\n\
    \        for (int i = 0; i < count; i++) {\n            long long left = static_cast<long\
    \ long>(random() % 16) - 8;\n            long long right = static_cast<long long>(random()\
    \ % 16) - 8;\n            long long bottom = static_cast<long long>(random() %\
    \ 16) - 8;\n            long long top = static_cast<long long>(random() % 16)\
    \ - 8;\n            if (right < left) std::swap(left, right);\n            if\
    \ (top < bottom) std::swap(bottom, top);\n            rectangles.emplace_back(left,\
    \ bottom, right, top);\n        }\n        assert(\n            m1une::geometry::rectangle_union_area(rectangles)\n\
    \            == brute(rectangles)\n        );\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    test_edge_cases();\n    test_randomized();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    int n = 0;\n    input.read(n);\n\
    \    std::vector<Rectangle> rectangles;\n    rectangles.reserve(n);\n    for (int\
    \ i = 0; i < n; i++) {\n        long long left = 0, bottom = 0, right = 0, top\
    \ = 0;\n        input.read(left, bottom, right, top);\n        rectangles.emplace_back(left,\
    \ bottom, right, top);\n    }\n    long long answer = static_cast<long long>(\n\
    \        m1une::geometry::rectangle_union_area(rectangles)\n    );\n    output.println(answer);\n\
    }\n"
  dependsOn:
  - geometry/rectangle_union_area.hpp
  - geometry/point.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/rectangle_union_area.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/rectangle_union_area.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/rectangle_union_area.test.cpp
- /verify/verify/geometry/rectangle_union_area.test.cpp.html
title: verify/geometry/rectangle_union_area.test.cpp
---
