---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/angle_sort.hpp
    title: Angle Sort
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
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
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"verify/geometry/angle_sort.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/sort_points_by_argument\"\n\n#line 1 \"geometry/angle_sort.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\n#line 1 \"geometry/point.hpp\"\
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
    \ m1une\n\n\n#line 8 \"geometry/angle_sort.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nenum class AngleSortStart {\n    NegativeXAxis,\n    PositiveXAxis,\n\
    };\n\ntemplate <Coordinate T>\nstruct AngleLess {\n    Point<T> origin;\n    AngleSortStart\
    \ start;\n\n    constexpr explicit AngleLess(\n        Point<T> origin_value =\
    \ Point<T>(),\n        AngleSortStart start_value = AngleSortStart::NegativeXAxis\n\
    \    ) : origin(origin_value), start(start_value) {}\n\n    constexpr bool operator()(\n\
    \        const Point<T>& first,\n        const Point<T>& second\n    ) const {\n\
    \        using W = wide_type<T>;\n        W first_x = W(first.x) - W(origin.x);\n\
    \        W first_y = W(first.y) - W(origin.y);\n        W second_x = W(second.x)\
    \ - W(origin.x);\n        W second_y = W(second.y) - W(origin.y);\n        W first_distance\
    \ = first_x * first_x + first_y * first_y;\n        W second_distance = second_x\
    \ * second_x + second_y * second_y;\n\n        // atan2(0, 0) is treated as angle\
    \ zero.\n        if (first_distance == 0) first_x = 1;\n        if (second_distance\
    \ == 0) second_x = 1;\n\n        auto half = [this](W x, W y) {\n            if\
    \ (start == AngleSortStart::PositiveXAxis) {\n                return y < 0 ||\
    \ (y == 0 && x < 0);\n            }\n            return y > 0 || (y == 0 && x\
    \ < 0);\n        };\n\n        bool first_half = half(first_x, first_y);\n   \
    \     bool second_half = half(second_x, second_y);\n        if (first_half !=\
    \ second_half) return first_half < second_half;\n\n        W product = first_x\
    \ * second_y - first_y * second_x;\n        if (product != 0) return product >\
    \ 0;\n\n        return first_distance < second_distance;\n    }\n};\n\n// Sorts\
    \ points counterclockwise by angle around `origin`.\ntemplate <Coordinate T>\n\
    void sort_by_angle(\n    std::vector<Point<T>>& points,\n    Point<T> origin =\
    \ Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n) {\n\
    \    std::sort(points.begin(), points.end(), AngleLess<T>(origin, start));\n}\n\
    \n// Returns a counterclockwise angle-sorted copy.\ntemplate <Coordinate T>\n\
    std::vector<Point<T>> angle_sorted(\n    std::vector<Point<T>> points,\n    Point<T>\
    \ origin = Point<T>(),\n    AngleSortStart start = AngleSortStart::NegativeXAxis\n\
    ) {\n    sort_by_angle(points, origin, start);\n    return points;\n}\n\n}  //\
    \ namespace geometry\n}  // namespace m1une\n\n\n#line 4 \"verify/geometry/angle_sort.test.cpp\"\
    \n\n#line 8 \"verify/geometry/angle_sort.test.cpp\"\n#include <cstdint>\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#line 14 \"utilities/fast_io.hpp\"\
    \n#include <utility>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ m1une\n\n\n#line 11 \"verify/geometry/angle_sort.test.cpp\"\n\nnamespace {\n\
    \nusing Point = m1une::geometry::Point<long long>;\n\nlong double argument(const\
    \ Point& point, const Point& origin) {\n    long double angle = std::atan2(\n\
    \        static_cast<long double>(point.y) - origin.y,\n        static_cast<long\
    \ double>(point.x) - origin.x\n    );\n    if (point == origin) return 0;\n  \
    \  return angle;\n}\n\nvoid test_fixed() {\n    std::vector<Point> points;\n \
    \   points.emplace_back(-1, 0);\n    points.emplace_back(0, 1);\n    points.emplace_back(2,\
    \ 0);\n    points.emplace_back(0, 0);\n    points.emplace_back(0, -1);\n    points.emplace_back(1,\
    \ 0);\n\n    m1une::geometry::sort_by_angle(points);\n    std::vector<Point> expected;\n\
    \    expected.emplace_back(0, -1);\n    expected.emplace_back(0, 0);\n    expected.emplace_back(1,\
    \ 0);\n    expected.emplace_back(2, 0);\n    expected.emplace_back(0, 1);\n  \
    \  expected.emplace_back(-1, 0);\n    assert(points == expected);\n\n    auto\
    \ positive = m1une::geometry::angle_sorted(\n        points,\n        Point(0,\
    \ 0),\n        m1une::geometry::AngleSortStart::PositiveXAxis\n    );\n    expected.clear();\n\
    \    expected.emplace_back(0, 0);\n    expected.emplace_back(1, 0);\n    expected.emplace_back(2,\
    \ 0);\n    expected.emplace_back(0, 1);\n    expected.emplace_back(-1, 0);\n \
    \   expected.emplace_back(0, -1);\n    assert(positive == expected);\n}\n\nvoid\
    \ test_randomized() {\n    std::uint64_t state = 239;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ Point origin(\n            static_cast<long long>(random() % 21) - 10,\n   \
    \         static_cast<long long>(random() % 21) - 10\n        );\n        int\
    \ size = int(random() % 40);\n        std::vector<Point> points;\n        points.reserve(size);\n\
    \        for (int index = 0; index < size; ++index) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 41) - 20,\n               \
    \ static_cast<long long>(random() % 41) - 20\n            );\n        }\n\n  \
    \      auto expected = points;\n        std::sort(expected.begin(), expected.end(),\
    \ [&origin](\n            const Point& first,\n            const Point& second\n\
    \        ) {\n            long double first_angle = argument(first, origin);\n\
    \            long double second_angle = argument(second, origin);\n          \
    \  if (first_angle != second_angle) return first_angle < second_angle;\n     \
    \       return m1une::geometry::distance2(first, origin)\n                   <\
    \ m1une::geometry::distance2(second, origin);\n        });\n\n        m1une::geometry::sort_by_angle(points,\
    \ origin);\n        assert(points == expected);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n\n    int n;\n  \
    \  fast_input >> n;\n    std::vector<Point> points(n);\n    for (Point& point\
    \ : points) fast_input >> point.x >> point.y;\n    m1une::geometry::sort_by_angle(points);\n\
    \    for (const Point& point : points) {\n        fast_output << point.x << '\
    \ ' << point.y << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n\n#include \"../../geometry/angle_sort.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nnamespace {\n\nusing Point = m1une::geometry::Point<long\
    \ long>;\n\nlong double argument(const Point& point, const Point& origin) {\n\
    \    long double angle = std::atan2(\n        static_cast<long double>(point.y)\
    \ - origin.y,\n        static_cast<long double>(point.x) - origin.x\n    );\n\
    \    if (point == origin) return 0;\n    return angle;\n}\n\nvoid test_fixed()\
    \ {\n    std::vector<Point> points;\n    points.emplace_back(-1, 0);\n    points.emplace_back(0,\
    \ 1);\n    points.emplace_back(2, 0);\n    points.emplace_back(0, 0);\n    points.emplace_back(0,\
    \ -1);\n    points.emplace_back(1, 0);\n\n    m1une::geometry::sort_by_angle(points);\n\
    \    std::vector<Point> expected;\n    expected.emplace_back(0, -1);\n    expected.emplace_back(0,\
    \ 0);\n    expected.emplace_back(1, 0);\n    expected.emplace_back(2, 0);\n  \
    \  expected.emplace_back(0, 1);\n    expected.emplace_back(-1, 0);\n    assert(points\
    \ == expected);\n\n    auto positive = m1une::geometry::angle_sorted(\n      \
    \  points,\n        Point(0, 0),\n        m1une::geometry::AngleSortStart::PositiveXAxis\n\
    \    );\n    expected.clear();\n    expected.emplace_back(0, 0);\n    expected.emplace_back(1,\
    \ 0);\n    expected.emplace_back(2, 0);\n    expected.emplace_back(0, 1);\n  \
    \  expected.emplace_back(-1, 0);\n    expected.emplace_back(0, -1);\n    assert(positive\
    \ == expected);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 239;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 5000; ++trial) {\n        Point origin(\n            static_cast<long long>(random()\
    \ % 21) - 10,\n            static_cast<long long>(random() % 21) - 10\n      \
    \  );\n        int size = int(random() % 40);\n        std::vector<Point> points;\n\
    \        points.reserve(size);\n        for (int index = 0; index < size; ++index)\
    \ {\n            points.emplace_back(\n                static_cast<long long>(random()\
    \ % 41) - 20,\n                static_cast<long long>(random() % 41) - 20\n  \
    \          );\n        }\n\n        auto expected = points;\n        std::sort(expected.begin(),\
    \ expected.end(), [&origin](\n            const Point& first,\n            const\
    \ Point& second\n        ) {\n            long double first_angle = argument(first,\
    \ origin);\n            long double second_angle = argument(second, origin);\n\
    \            if (first_angle != second_angle) return first_angle < second_angle;\n\
    \            return m1une::geometry::distance2(first, origin)\n              \
    \     < m1une::geometry::distance2(second, origin);\n        });\n\n        m1une::geometry::sort_by_angle(points,\
    \ origin);\n        assert(points == expected);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n\n    int n;\n  \
    \  fast_input >> n;\n    std::vector<Point> points(n);\n    for (Point& point\
    \ : points) fast_input >> point.x >> point.y;\n    m1une::geometry::sort_by_angle(points);\n\
    \    for (const Point& point : points) {\n        fast_output << point.x << '\
    \ ' << point.y << '\\n';\n    }\n}\n"
  dependsOn:
  - geometry/angle_sort.hpp
  - geometry/point.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/angle_sort.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/angle_sort.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/angle_sort.test.cpp
- /verify/verify/geometry/angle_sort.test.cpp.html
title: verify/geometry/angle_sort.test.cpp
---
