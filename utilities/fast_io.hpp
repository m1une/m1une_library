#ifndef M1UNE_FAST_IO_HPP
#define M1UNE_FAST_IO_HPP 1

#include <array>
#include <charconv>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <unistd.h>

namespace m1une {
namespace utilities {
namespace internal {

// Detect std::begin(x), std::end(x).
template <class T, class = void>
struct is_range : std::false_type {};

template <class T>
struct is_range<T, std::void_t<
    decltype(std::begin(std::declval<T&>())),
    decltype(std::end(std::declval<T&>()))
>> : std::true_type {};

template <class T>
inline constexpr bool is_range_v = is_range<T>::value;

template <class T>
using range_reference_t = decltype(*std::begin(std::declval<T&>()));

template <class T>
using range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;

template <class T, class = void>
struct range_stored_value {
    using type = range_value_t<T>;
};

template <class T>
struct range_stored_value<T, std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>> {
    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;
};

template <class T>
using range_stored_value_t = typename range_stored_value<T>::type;

// Treat strings and C strings as scalar output objects, not as ranges.
template <class T>
struct is_char_array : std::false_type {};

template <class T, std::size_t N>
struct is_char_array<T[N]>
    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>, char>> {};

template <class T>
struct is_string_like
    : std::bool_constant<
          std::is_same_v<std::decay_t<T>, std::string>
          || std::is_same_v<std::decay_t<T>, const char*>
          || std::is_same_v<std::decay_t<T>, char*>
          || is_char_array<std::remove_reference_t<T>>::value
      > {};

template <class T>
inline constexpr bool is_string_like_v = is_string_like<T>::value;

// ModInt-like type: x.val() is printable, and x can be assigned from long long.
template <class T, class = void>
struct has_val_method : std::false_type {};

template <class T>
struct has_val_method<T, std::void_t<decltype(std::declval<const T&>().val())>>
    : std::true_type {};

template <class T>
inline constexpr bool has_val_method_v = has_val_method<T>::value;

template <class T, class = void>
struct has_static_mod_raw : std::false_type {};

template <class T>
struct has_static_mod_raw<
    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>
    : std::true_type {};

template <class T>
inline constexpr bool has_static_mod_raw_v = has_static_mod_raw<T>::value;

// libstdc++ before GCC 16 does not classify __int128 as an integral type in
// strict ISO modes such as -std=c++23. Keep the fast-I/O interface independent
// of that implementation detail.
template <class T>
inline constexpr bool is_integral_v =
    std::is_integral_v<T>
    || std::is_same_v<std::remove_cv_t<T>, __int128_t>
    || std::is_same_v<std::remove_cv_t<T>, __uint128_t>;

template <class T>
inline constexpr bool is_signed_v =
    std::is_signed_v<T>
    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;

template <class T>
struct make_unsigned {
    using type = std::make_unsigned_t<T>;
};

template <>
struct make_unsigned<__int128_t> {
    using type = __uint128_t;
};

template <>
struct make_unsigned<__uint128_t> {
    using type = __uint128_t;
};

template <class T>
using make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;

}  // namespace internal

struct FastInput {
    static constexpr int buffer_size = 1 << 20;

   private:
    std::FILE* _stream;
    char _buffer[buffer_size];
    int _position;
    int _length;
    bool _terminal;

    bool refill() {
        _position = 0;
        if (_terminal) {
            if (std::fgets(_buffer, buffer_size, _stream) == nullptr) {
                _length = 0;
                return false;
            }
            _length = int(std::strlen(_buffer));
        } else {
            _length = int(std::fread(_buffer, 1, buffer_size, _stream));
        }
        return _length != 0;
    }

    template <class T>
    bool read_integer_from_terminal(T& value) {
        if (!skip_spaces()) return false;
        int c = read_char_raw();

        bool negative = false;
        if (c == '-') {
            negative = true;
            c = read_char_raw();
        }

        if constexpr (internal::is_signed_v<T>) {
            T result = 0;
            while ('0' <= c && c <= '9') {
                result = negative ? result * 10 - (c - '0')
                                  : result * 10 + (c - '0');
                c = read_char_raw();
            }
            value = result;
        } else {
            T result = 0;
            while ('0' <= c && c <= '9') {
                result = result * 10 + T(c - '0');
                c = read_char_raw();
            }
            value = negative ? T(0) - result : result;
        }
        return true;
    }

    bool prepare_number() {
        if (_length - _position >= 64) return true;
        const int remaining = _length - _position;
        if (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);
        const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining, _stream));
        _position = 0;
        _length = remaining + added;
        if (_length < buffer_size) _buffer[_length] = '\0';
        return _length != 0;
    }

   public:
    explicit FastInput(std::FILE* stream = stdin)
        : _stream(stream),
          _position(0),
          _length(0),
          _terminal(::isatty(::fileno(stream)) != 0) {}

    FastInput(const FastInput&) = delete;
    FastInput& operator=(const FastInput&) = delete;

    int read_char_raw() {
        if (_position == _length && !refill()) return EOF;
        return _buffer[_position++];
    }

    bool skip_spaces() {
        int c = read_char_raw();
        while (c != EOF && c <= ' ') c = read_char_raw();
        if (c == EOF) return false;
        --_position;
        return true;
    }

    bool read(char& value) {
        if (!skip_spaces()) return false;
        value = char(read_char_raw());
        return true;
    }

    bool read(std::string& value) {
        if (!skip_spaces()) return false;
        value.clear();
        int c = read_char_raw();
        while (c != EOF && c > ' ') {
            value.push_back(char(c));
            c = read_char_raw();
        }
        return true;
    }

    bool read(bool& value) {
        int x;
        if (!read(x)) return false;
        value = x != 0;
        return true;
    }

    template <class T>
    std::enable_if_t<
        internal::is_integral_v<T>
            && !std::is_same_v<std::remove_cv_t<T>, bool>
            && !std::is_same_v<std::remove_cv_t<T>, char>,
        bool
    >
    read(T& value) {
        if (_terminal) return read_integer_from_terminal(value);
        if (!prepare_number()) return false;
        int c = static_cast<unsigned char>(_buffer[_position++]);
        while (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);

        bool negative = false;
        if (c == '-') {
            negative = true;
            c = static_cast<unsigned char>(_buffer[_position++]);
        }

        if constexpr (internal::is_signed_v<T>) {
            T result = 0;
            while ('0' <= c && c <= '9') {
                const int first = c - '0';
                const int second = static_cast<unsigned char>(_buffer[_position]) - '0';
                if (0 <= second && second <= 9) {
                    result = negative ? result * 100 - (first * 10 + second)
                                      : result * 100 + (first * 10 + second);
                    ++_position;
                } else {
                    result = negative ? result * 10 - first : result * 10 + first;
                }
                c = static_cast<unsigned char>(_buffer[_position++]);
            }
            value = result;
        } else {
            T result = 0;
            while ('0' <= c && c <= '9') {
                const unsigned first = unsigned(c - '0');
                const int second = static_cast<unsigned char>(_buffer[_position]) - '0';
                if (0 <= second && second <= 9) {
                    result = result * 100 + T(first * 10 + unsigned(second));
                    ++_position;
                } else {
                    result = result * 10 + T(first);
                }
                c = static_cast<unsigned char>(_buffer[_position++]);
            }
            value = negative ? T(0) - result : result;
        }
        if (_position > _length) _position = _length;
        return true;
    }

    template <class T>
    std::enable_if_t<std::is_floating_point_v<T>, bool>
    read(T& value) {
        if (!skip_spaces()) return false;
        int c = read_char_raw();
        bool negative = false;
        if (c == '-' || c == '+') {
            negative = c == '-';
            c = read_char_raw();
        }

        long double result = 0;
        while ('0' <= c && c <= '9') {
            result = result * 10 + (c - '0');
            c = read_char_raw();
        }
        if (c == '.') {
            long double place = 0.1L;
            c = read_char_raw();
            while ('0' <= c && c <= '9') {
                result += (c - '0') * place;
                place *= 0.1L;
                c = read_char_raw();
            }
        }
        if (c == 'e' || c == 'E') {
            c = read_char_raw();
            bool exponent_negative = false;
            if (c == '-' || c == '+') {
                exponent_negative = c == '-';
                c = read_char_raw();
            }
            int exponent = 0;
            while ('0' <= c && c <= '9') {
                exponent = exponent * 10 + (c - '0');
                c = read_char_raw();
            }
            long double scale = 1;
            long double power = 10;
            while (exponent > 0) {
                if (exponent & 1) scale *= power;
                power *= power;
                exponent >>= 1;
            }
            result = exponent_negative ? result / scale : result * scale;
        }
        value = static_cast<T>(negative ? -result : result);
        return true;
    }

    template <class T>
    std::enable_if_t<
        internal::has_val_method_v<T>
            && !internal::is_integral_v<T>
            && !internal::is_range_v<T>,
        bool
    >
    read(T& value) {
        long long x;
        if (!read(x)) return false;
        if constexpr (internal::has_static_mod_raw_v<T>) {
            if (x >= 0 && uint64_t(x) < uint64_t(T::mod())) {
                value = T::raw(uint32_t(x));
            } else {
                value = T(x);
            }
        } else {
            value = T(x);
        }
        return true;
    }

    template <class First, class Second>
    bool read(std::pair<First, Second>& value) {
        if (!read(value.first)) return false;
        return read(value.second);
    }

    template <class Range>
    std::enable_if_t<
        internal::is_range_v<Range>
            && !internal::is_string_like_v<Range>,
        bool
    >
    read(Range& range) {
        using StoredValue = internal::range_stored_value_t<Range>;
        constexpr bool nested = internal::is_range_v<StoredValue>
                                && !internal::is_string_like_v<StoredValue>;

        for (auto&& value : range) {
            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {
                bool x;
                if (!read(x)) return false;
                value = x;
            } else {
                if (!read(value)) return false;
            }
        }
        return true;
    }

    template <class First, class Second, class... Rest>
    bool read(First& first, Second& second, Rest&... rest) {
        if (!read(first)) return false;
        return read(second, rest...);
    }

    template <class T>
    FastInput& operator>>(T& value) {
        if (!read(value)) std::abort();
        return *this;
    }
};

struct FastOutput {
    static constexpr int buffer_size = 1 << 20;

   private:
    inline static const auto digit_quads = [] {
        std::array<char, 40000> result{};
        for (int i = 0; i < 10000; i++) {
            int value = i;
            for (int j = 3; j >= 0; j--) {
                result[4 * i + j] = char('0' + value % 10);
                value /= 10;
            }
        }
        return result;
    }();

    std::FILE* _stream;
    char _buffer[buffer_size];
    int _position;
    int _precision;
    std::chars_format _float_format;

   public:
    explicit FastOutput(std::FILE* stream = stdout)
        : _stream(stream),
          _position(0),
          _precision(6),
          _float_format(std::chars_format::general) {}

    FastOutput(const FastOutput&) = delete;
    FastOutput& operator=(const FastOutput&) = delete;

    ~FastOutput() {
        flush();
    }

    void flush() {
        if (_position == 0) return;
        std::fwrite(_buffer, 1, _position, _stream);
        _position = 0;
    }

    void write_char(char c) {
        if (_position == buffer_size) flush();
        _buffer[_position++] = c;
    }

    void write(const char* s) {
        while (*s != '\0') write_char(*s++);
    }

    void write(const std::string& s) {
        for (char c : s) write_char(c);
    }

    void write(char c) {
        write_char(c);
    }

    void write(bool value) {
        write_char(value ? '1' : '0');
    }

    template <class T>
    std::enable_if_t<std::is_floating_point_v<T>>
    write(T value) {
        char digits[128];
        auto [end, error] = std::to_chars(
            digits,
            digits + sizeof(digits),
            value,
            _float_format,
            _precision
        );
        if (error != std::errc()) std::abort();
        for (const char* pointer = digits; pointer != end; pointer++) {
            write_char(*pointer);
        }
    }

    template <class T>
    std::enable_if_t<
        internal::is_integral_v<T>
            && !std::is_same_v<std::remove_cv_t<T>, bool>
            && !std::is_same_v<std::remove_cv_t<T>, char>
    >
    write(T value) {
        using Raw = std::remove_cv_t<T>;
        using Unsigned = internal::make_unsigned_t<Raw>;

        Unsigned magnitude;
        if constexpr (internal::is_signed_v<Raw>) {
            if (value < 0) {
                write_char('-');
                magnitude = Unsigned(0) - Unsigned(value);
            } else {
                magnitude = Unsigned(value);
            }
        } else {
            magnitude = value;
        }

        if (magnitude == 0) {
            write_char('0');
            return;
        }

        unsigned chunks[16];
        int count = 0;
        while (magnitude >= 10000) {
            const Unsigned quotient = magnitude / 10000;
            chunks[count++] = unsigned(magnitude - quotient * 10000);
            magnitude = quotient;
        }
        if (_position > buffer_size - 64) flush();
        const unsigned leading = unsigned(magnitude);
        const char* first = digit_quads.data() + 4 * leading;
        int skip = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;
        for (; skip < 4; skip++) _buffer[_position++] = first[skip];
        while (count--) {
            const char* digits = digit_quads.data() + 4 * chunks[count];
            std::memcpy(_buffer + _position, digits, 4);
            _position += 4;
        }
    }

    template <class T>
    std::enable_if_t<
        internal::has_val_method_v<T>
            && !internal::is_integral_v<T>
            && !internal::is_range_v<T>
    >
    write(const T& value) {
        write(value.val());
    }

    template <class First, class Second>
    void write(const std::pair<First, Second>& value) {
        write(value.first);
        write_char(' ');
        write(value.second);
    }

    template <class Range>
    std::enable_if_t<
        internal::is_range_v<Range>
            && !internal::is_string_like_v<Range>
    >
    write(const Range& range) {
        using StoredValue = internal::range_stored_value_t<const Range>;
        constexpr bool nested = internal::is_range_v<StoredValue>
                                && !internal::is_string_like_v<StoredValue>;

        bool first = true;
        for (const auto& value : range) {
            if (!first) write_char(nested ? '\n' : ' ');
            first = false;
            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {
                write(static_cast<bool>(value));
            } else {
                write(value);
            }
        }
    }

    template <class First, class... Rest>
    void print(const First& first, const Rest&... rest) {
        write(first);
        ((write_char(' '), write(rest)), ...);
    }

    void println() {
        write_char('\n');
    }

    void set_precision(int precision) {
        _precision = precision;
    }

    void set_fixed(int precision = 6) {
        _float_format = std::chars_format::fixed;
        _precision = precision;
    }

    void set_general(int precision = 6) {
        _float_format = std::chars_format::general;
        _precision = precision;
    }

    template <class... Args>
    void println(const Args&... args) {
        print(args...);
        write_char('\n');
    }

    template <class T>
    FastOutput& operator<<(const T& value) {
        write(value);
        return *this;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_FAST_IO_HPP
