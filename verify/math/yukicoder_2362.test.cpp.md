---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/generalized_floor_sum.hpp
    title: Generalized Floor Sum
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
    PROBLEM: https://yukicoder.me/problems/no/2362
    links:
    - https://yukicoder.me/problems/no/2362
  bundledCode: "#line 1 \"verify/math/yukicoder_2362.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/2362\"\n\n#line 1 \"math/generalized_floor_sum.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class T,\
    \ int MaxPower, int MaxFloorPower>\nusing GeneralizedFloorSumTable =\n    std::array<std::array<T,\
    \ MaxFloorPower + 1>, MaxPower + 1>;\n\nnamespace generalized_floor_sum_detail\
    \ {\n\nusing SignedWide = __int128_t;\nusing UnsignedWide = __uint128_t;\n\ntemplate\
    \ <class T>\nT from_wide(SignedWide value) {\n    bool negative = value < 0;\n\
    \    UnsignedWide magnitude;\n    if (negative) {\n        magnitude = static_cast<UnsignedWide>(-(value\
    \ + 1));\n        ++magnitude;\n    } else {\n        magnitude = static_cast<UnsignedWide>(value);\n\
    \    }\n\n    T result = T();\n    T binary_place = T(1);\n    while (magnitude\
    \ > 0) {\n        if ((magnitude & 1) != 0) result += binary_place;\n        magnitude\
    \ >>= 1;\n        if (magnitude > 0) binary_place += binary_place;\n    }\n  \
    \  return negative ? T() - result : result;\n}\n\ninline SignedWide floor_div(SignedWide\
    \ numerator, SignedWide denominator) {\n    assert(denominator > 0);\n    SignedWide\
    \ quotient = numerator / denominator;\n    if (numerator % denominator < 0) --quotient;\n\
    \    return quotient;\n}\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\n\
    class MomentMonoid {\n   public:\n    using Table = GeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower>;\n\n    struct Data {\n        Table sums{};\n    \
    \    T delta_x = T();\n        T delta_y = T();\n    };\n\n    static constexpr\
    \ int MaximumDegree =\n        MaxPower > MaxFloorPower ? MaxPower : MaxFloorPower;\n\
    \n    MomentMonoid() {\n        binomial_[0][0] = T(1);\n        for (int degree\
    \ = 0; degree < MaximumDegree; ++degree) {\n            for (int index = 0; index\
    \ <= degree; ++index) {\n                binomial_[degree + 1][index] += binomial_[degree][index];\n\
    \                binomial_[degree + 1][index + 1] +=\n                    binomial_[degree][index];\n\
    \            }\n        }\n    }\n\n    const T& binomial(int n, int k) const\
    \ {\n        assert(0 <= k && k <= n && n <= MaximumDegree);\n        return binomial_[n][k];\n\
    \    }\n\n    Data unit() const {\n        return Data();\n    }\n\n    Data x_step()\
    \ const {\n        Data result;\n        result.sums[0][0] = T(1);\n        result.delta_x\
    \ = T(1);\n        return result;\n    }\n\n    Data y_step() const {\n      \
    \  Data result;\n        result.delta_y = T(1);\n        return result;\n    }\n\
    \n    Data concatenate(Data left, Data right) const {\n        std::array<T, MaxPower\
    \ + 1> x_powers{};\n        std::array<T, MaxFloorPower + 1> y_powers{};\n   \
    \     x_powers[0] = T(1);\n        y_powers[0] = T(1);\n        for (int power\
    \ = 0; power < MaxPower; ++power) {\n            x_powers[power + 1] = x_powers[power]\
    \ * left.delta_x;\n        }\n        for (int power = 0; power < MaxFloorPower;\
    \ ++power) {\n            y_powers[power + 1] = y_powers[power] * left.delta_y;\n\
    \        }\n\n        // Shift the y-coordinate of every sampled x-step in the\
    \ right path.\n        for (int x_power = 0; x_power <= MaxPower; ++x_power) {\n\
    \            for (int old_power = MaxFloorPower; old_power >= 0; --old_power)\
    \ {\n                T source = right.sums[x_power][old_power];\n            \
    \    for (int new_power = old_power + 1;\n                     new_power <= MaxFloorPower;\n\
    \                     ++new_power) {\n                    right.sums[x_power][new_power]\
    \ +=\n                        binomial_[new_power][old_power] *\n            \
    \            y_powers[new_power - old_power] * source;\n                }\n  \
    \          }\n        }\n\n        // Shift x, then append all samples from the\
    \ right path.\n        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power)\
    \ {\n            for (int old_power = 0; old_power <= MaxPower; ++old_power) {\n\
    \                T source = right.sums[old_power][y_power];\n                for\
    \ (int new_power = old_power;\n                     new_power <= MaxPower;\n \
    \                    ++new_power) {\n                    left.sums[new_power][y_power]\
    \ +=\n                        binomial_[new_power][old_power] *\n            \
    \            x_powers[new_power - old_power] * source;\n                }\n  \
    \          }\n        }\n\n        left.delta_x += right.delta_x;\n        left.delta_y\
    \ += right.delta_y;\n        return left;\n    }\n\n   private:\n    std::array<std::array<T,\
    \ MaximumDegree + 1>, MaximumDegree + 1>\n        binomial_{};\n};\n\ntemplate\
    \ <class Monoid>\ntypename Monoid::Data monoid_power(\n    const Monoid& monoid,\n\
    \    typename Monoid::Data base,\n    UnsignedWide exponent\n) {\n    typename\
    \ Monoid::Data result = monoid.unit();\n    while (exponent > 0) {\n        if\
    \ ((exponent & 1) != 0) {\n            result = monoid.concatenate(std::move(result),\
    \ base);\n        }\n        exponent >>= 1;\n        if (exponent > 0) {\n  \
    \          base = monoid.concatenate(base, base);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <class Monoid>\ntypename Monoid::Data floor_path_product(\n\
    \    const Monoid& monoid,\n    UnsignedWide n,\n    UnsignedWide a,\n    UnsignedWide\
    \ b,\n    UnsignedWide modulus\n) {\n    assert(modulus > 0);\n    UnsignedWide\
    \ height = (a * n + b) / modulus;\n    typename Monoid::Data x = monoid.x_step();\n\
    \    typename Monoid::Data y = monoid.y_step();\n    typename Monoid::Data prefix\
    \ = monoid.unit();\n    typename Monoid::Data suffix = monoid.unit();\n\n    while\
    \ (true) {\n        UnsignedWide slope_quotient = a / modulus;\n        UnsignedWide\
    \ intercept_quotient = b / modulus;\n        a %= modulus;\n        b %= modulus;\n\
    \n        x = monoid.concatenate(\n            std::move(x),\n            monoid_power(monoid,\
    \ y, slope_quotient)\n        );\n        prefix = monoid.concatenate(\n     \
    \       std::move(prefix),\n            monoid_power(monoid, y, intercept_quotient)\n\
    \        );\n        height -= slope_quotient * n + intercept_quotient;\n    \
    \    if (height == 0) break;\n\n        assert(a > 0);\n        UnsignedWide boundary\
    \ =\n            (modulus * height - b - 1) / a + 1;\n        suffix = monoid.concatenate(\n\
    \            y,\n            monoid.concatenate(\n                monoid_power(monoid,\
    \ x, n - boundary),\n                std::move(suffix)\n            )\n      \
    \  );\n        b = modulus - b - 1 + a;\n        n = height - 1;\n        height\
    \ = boundary;\n        std::swap(modulus, a);\n        std::swap(x, y);\n    }\n\
    \n    x = monoid_power(monoid, x, n);\n    return monoid.concatenate(\n      \
    \  monoid.concatenate(std::move(prefix), std::move(x)),\n        std::move(suffix)\n\
    \    );\n}\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\nGeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower>\nnonnegative_slope_table(\n    const MomentMonoid<T,\
    \ MaxPower, MaxFloorPower>& monoid,\n    SignedWide n,\n    SignedWide modulus,\n\
    \    SignedWide a,\n    SignedWide b\n) {\n    assert(n >= 0 && modulus > 0 &&\
    \ a >= 0);\n    SignedWide y_offset = floor_div(b, modulus);\n    SignedWide normalized_b\
    \ = b - y_offset * modulus;\n\n    auto path = floor_path_product(\n        monoid,\n\
    \        static_cast<UnsignedWide>(n),\n        static_cast<UnsignedWide>(a),\n\
    \        static_cast<UnsignedWide>(normalized_b),\n        static_cast<UnsignedWide>(modulus)\n\
    \    );\n\n    std::array<T, MaxFloorPower + 1> offset_powers{};\n    offset_powers[0]\
    \ = T(1);\n    T offset = from_wide<T>(y_offset);\n    for (int power = 0; power\
    \ < MaxFloorPower; ++power) {\n        offset_powers[power + 1] = offset_powers[power]\
    \ * offset;\n    }\n\n    GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>\
    \ result{};\n    for (int x_power = 0; x_power <= MaxPower; ++x_power) {\n   \
    \     for (int y_power = 0; y_power <= MaxFloorPower; ++y_power) {\n         \
    \   for (int inner_power = 0;\n                 inner_power <= y_power;\n    \
    \             ++inner_power) {\n                result[x_power][y_power] +=\n\
    \                    monoid.binomial(y_power, inner_power) *\n               \
    \     offset_powers[y_power - inner_power] *\n                    path.sums[x_power][inner_power];\n\
    \            }\n        }\n    }\n    return result;\n}\n\n}  // namespace generalized_floor_sum_detail\n\
    \n// Returns every sum of x^p * floor((a*x+b)/mod)^q for 0 <= x < n,\n// 0 <=\
    \ p <= MaxPower, and 0 <= q <= MaxFloorPower.\ntemplate <class T, int MaxPower,\
    \ int MaxFloorPower, class I>\nGeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>\n\
    generalized_floor_sum_table(I n, I mod, I a, I b) {\n    static_assert(MaxPower\
    \ >= 0 && MaxFloorPower >= 0);\n    static_assert(\n        std::is_integral_v<I>\
    \ && std::is_signed_v<I> && sizeof(I) <= 8,\n        \"generalized_floor_sum_table\
    \ requires signed integer arguments\"\n    );\n    assert(n >= 0);\n    assert(mod\
    \ > 0);\n\n    namespace detail = generalized_floor_sum_detail;\n    using Monoid\
    \ = detail::MomentMonoid<T, MaxPower, MaxFloorPower>;\n    static const Monoid\
    \ monoid;\n\n    detail::SignedWide wide_n = n;\n    detail::SignedWide wide_mod\
    \ = mod;\n    detail::SignedWide wide_a = a;\n    detail::SignedWide wide_b =\
    \ b;\n    if (wide_n == 0) {\n        return GeneralizedFloorSumTable<T, MaxPower,\
    \ MaxFloorPower>();\n    }\n    if (wide_a >= 0) {\n        return detail::nonnegative_slope_table(\n\
    \            monoid,\n            wide_n,\n            wide_mod,\n           \
    \ wide_a,\n            wide_b\n        );\n    }\n\n    // Substitute x = n -\
    \ 1 - t to make the slope nonnegative.\n    auto reflected = detail::nonnegative_slope_table(\n\
    \        monoid,\n        wide_n,\n        wide_mod,\n        -wide_a,\n     \
    \   wide_a * (wide_n - 1) + wide_b\n    );\n    std::array<T, MaxPower + 1> offset_powers{};\n\
    \    offset_powers[0] = T(1);\n    T offset = detail::from_wide<T>(wide_n - 1);\n\
    \    for (int power = 0; power < MaxPower; ++power) {\n        offset_powers[power\
    \ + 1] = offset_powers[power] * offset;\n    }\n\n    GeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower> result{};\n    for (int x_power = 0; x_power <= MaxPower;\
    \ ++x_power) {\n        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power)\
    \ {\n            for (int inner_power = 0;\n                 inner_power <= x_power;\n\
    \                 ++inner_power) {\n                T coefficient =\n        \
    \            monoid.binomial(x_power, inner_power) *\n                    offset_powers[x_power\
    \ - inner_power];\n                if ((inner_power & 1) != 0) coefficient = T()\
    \ - coefficient;\n                result[x_power][y_power] +=\n              \
    \      coefficient * reflected[inner_power][y_power];\n            }\n       \
    \ }\n    }\n    return result;\n}\n\ntemplate <class T, int Power, int FloorPower,\
    \ class I>\nT generalized_floor_sum(I n, I mod, I a, I b) {\n    return generalized_floor_sum_table<T,\
    \ Power, FloorPower>(n, mod, a, b)\n        [Power][FloorPower];\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 4 \"verify/math/yukicoder_2362.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ m1une\n\n\n#line 7 \"verify/math/yukicoder_2362.test.cpp\"\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int test_count;\n    fast_input >> test_count;\n    while\
    \ (test_count--) {\n        long long n, mod, x, y;\n        fast_input >> n >>\
    \ mod >> x >> y;\n\n        auto without_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           0LL\n            );\n        auto with_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           y\n            );\n\n        std::uint64_t answer = 0;\n        answer\
    \ -= without_offset[0][1] * static_cast<std::uint64_t>(n) -\n                \
    \  without_offset[1][1];\n        answer -= with_offset[0][1] * static_cast<std::uint64_t>(n\
    \ - 1) -\n                  2 * with_offset[1][1];\n        fast_output << answer\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2362\"\n\n#include \"\
    ../../math/generalized_floor_sum.hpp\"\n\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int test_count;\n    fast_input >> test_count;\n    while\
    \ (test_count--) {\n        long long n, mod, x, y;\n        fast_input >> n >>\
    \ mod >> x >> y;\n\n        auto without_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           0LL\n            );\n        auto with_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           y\n            );\n\n        std::uint64_t answer = 0;\n        answer\
    \ -= without_offset[0][1] * static_cast<std::uint64_t>(n) -\n                \
    \  without_offset[1][1];\n        answer -= with_offset[0][1] * static_cast<std::uint64_t>(n\
    \ - 1) -\n                  2 * with_offset[1][1];\n        fast_output << answer\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - math/generalized_floor_sum.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/yukicoder_2362.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/yukicoder_2362.test.cpp
layout: document
redirect_from:
- /verify/verify/math/yukicoder_2362.test.cpp
- /verify/verify/math/yukicoder_2362.test.cpp.html
title: verify/math/yukicoder_2362.test.cpp
---
