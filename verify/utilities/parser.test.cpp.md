---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: utilities/parser.hpp
    title: Parser
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/utilities/parser.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"utilities/parser.hpp\"\n\n\n\n#include <cctype>\n#include <cmath>\n\
    #include <cstddef>\n#include <limits>\n#include <optional>\n#include <stdexcept>\n\
    #include <string>\n#include <string_view>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nclass ParseError : public std::runtime_error\
    \ {\nprivate:\n    std::size_t position_;\n\npublic:\n    ParseError(std::size_t\
    \ position, const std::string& message)\n        : std::runtime_error(message\
    \ + \" at position \" + std::to_string(position)),\n          position_(position)\
    \ {}\n\n    [[nodiscard]] std::size_t position() const noexcept {\n        return\
    \ position_;\n    }\n};\n\nclass Parser {\npublic:\n    using mark_type = std::size_t;\n\
    \n    class Checkpoint {\n    private:\n        Parser* parser_;\n        mark_type\
    \ position_;\n\n    public:\n        explicit Checkpoint(Parser& parser) noexcept\n\
    \            : parser_(&parser), position_(parser.position()) {}\n\n        Checkpoint(const\
    \ Checkpoint&) = delete;\n        Checkpoint& operator=(const Checkpoint&) = delete;\n\
    \n        Checkpoint(Checkpoint&& other) noexcept\n            : parser_(std::exchange(other.parser_,\
    \ nullptr)),\n              position_(other.position_) {}\n\n        Checkpoint&\
    \ operator=(Checkpoint&&) = delete;\n\n        ~Checkpoint() {\n            rollback();\n\
    \        }\n\n        void commit() noexcept {\n            parser_ = nullptr;\n\
    \        }\n\n        void rollback() noexcept {\n            if (parser_ != nullptr)\
    \ {\n                parser_->position_ = position_;\n                parser_\
    \ = nullptr;\n            }\n        }\n    };\n\nprivate:\n    std::string_view\
    \ input_;\n    std::size_t position_ = 0;\n\n    static int digit_value(char character)\
    \ noexcept {\n        if ('0' <= character && character <= '9') {\n          \
    \  return character - '0';\n        }\n        if ('a' <= character && character\
    \ <= 'z') {\n            return character - 'a' + 10;\n        }\n        if ('A'\
    \ <= character && character <= 'Z') {\n            return character - 'A' + 10;\n\
    \        }\n        return -1;\n    }\n\n    [[noreturn]] void fail(const std::string&\
    \ message) const {\n        throw ParseError(position_, message);\n    }\n\npublic:\n\
    \    Parser() = default;\n\n    explicit Parser(std::string_view input) noexcept\
    \ : input_(input) {}\n\n    [[nodiscard]] std::string_view source() const noexcept\
    \ {\n        return input_;\n    }\n\n    [[nodiscard]] std::size_t size() const\
    \ noexcept {\n        return input_.size();\n    }\n\n    [[nodiscard]] std::size_t\
    \ position() const noexcept {\n        return position_;\n    }\n\n    [[nodiscard]]\
    \ bool eof() const noexcept {\n        return position_ == input_.size();\n  \
    \  }\n\n    [[nodiscard]] std::string_view remaining() const noexcept {\n    \
    \    return input_.substr(position_);\n    }\n\n    [[nodiscard]] std::optional<char>\
    \ peek(std::size_t offset = 0) const noexcept {\n        if (offset >= input_.size()\
    \ - position_) {\n            return std::nullopt;\n        }\n        return\
    \ input_[position_ + offset];\n    }\n\n    [[nodiscard]] mark_type mark() const\
    \ noexcept {\n        return position_;\n    }\n\n    void restore(mark_type saved_position)\
    \ {\n        if (saved_position > input_.size()) {\n            throw std::out_of_range(\"\
    parser position is outside the input\");\n        }\n        position_ = saved_position;\n\
    \    }\n\n    [[nodiscard]] Checkpoint checkpoint() noexcept {\n        return\
    \ Checkpoint(*this);\n    }\n\n    template <typename Predicate>\n    std::string_view\
    \ read_while(Predicate predicate) {\n        std::size_t begin = position_;\n\
    \        while (!eof() && predicate(input_[position_])) {\n            ++position_;\n\
    \        }\n        return input_.substr(begin, position_ - begin);\n    }\n\n\
    \    std::size_t skip_whitespace() noexcept {\n        std::size_t begin = position_;\n\
    \        while (!eof() && std::isspace(static_cast<unsigned char>(input_[position_])))\
    \ {\n            ++position_;\n        }\n        return position_ - begin;\n\
    \    }\n\n    bool consume(char expected) noexcept {\n        if (eof() || input_[position_]\
    \ != expected) {\n            return false;\n        }\n        ++position_;\n\
    \        return true;\n    }\n\n    bool consume(std::string_view expected) noexcept\
    \ {\n        if (remaining().substr(0, expected.size()) != expected) {\n     \
    \       return false;\n        }\n        position_ += expected.size();\n    \
    \    return true;\n    }\n\n    template <typename Predicate>\n    bool consume_if(Predicate\
    \ predicate) {\n        if (eof() || !predicate(input_[position_])) {\n      \
    \      return false;\n        }\n        ++position_;\n        return true;\n\
    \    }\n\n    void expect(char expected) {\n        if (!consume(expected)) {\n\
    \            fail(std::string(\"expected '\") + expected + \"'\");\n        }\n\
    \    }\n\n    void expect(std::string_view expected) {\n        if (!consume(expected))\
    \ {\n            fail(\"expected \\\"\" + std::string(expected) + \"\\\"\");\n\
    \        }\n    }\n\n    std::optional<std::string_view> take(std::size_t count)\
    \ noexcept {\n        if (count > input_.size() - position_) {\n            return\
    \ std::nullopt;\n        }\n        std::string_view result = input_.substr(position_,\
    \ count);\n        position_ += count;\n        return result;\n    }\n\n    std::string_view\
    \ read_until(char delimiter, bool consume_delimiter = false) noexcept {\n    \
    \    std::size_t begin = position_;\n        std::size_t found = input_.find(delimiter,\
    \ position_);\n        if (found == std::string_view::npos) {\n            position_\
    \ = input_.size();\n            return input_.substr(begin);\n        }\n    \
    \    position_ = found + (consume_delimiter ? 1 : 0);\n        return input_.substr(begin,\
    \ found - begin);\n    }\n\n    std::optional<std::string_view> try_token() noexcept\
    \ {\n        mark_type begin_attempt = mark();\n        skip_whitespace();\n \
    \       std::size_t begin = position_;\n        while (!eof() && !std::isspace(static_cast<unsigned\
    \ char>(input_[position_]))) {\n            ++position_;\n        }\n        if\
    \ (begin == position_) {\n            position_ = begin_attempt;\n           \
    \ return std::nullopt;\n        }\n        return input_.substr(begin, position_\
    \ - begin);\n    }\n\n    std::string_view token() {\n        std::size_t error_position\
    \ = position_;\n        std::optional<std::string_view> result = try_token();\n\
    \        if (!result.has_value()) {\n            position_ = error_position;\n\
    \            fail(\"expected token\");\n        }\n        return *result;\n \
    \   }\n\n    std::optional<std::string_view> try_identifier() noexcept {\n   \
    \     mark_type begin_attempt = mark();\n        skip_whitespace();\n        if\
    \ (eof()) {\n            position_ = begin_attempt;\n            return std::nullopt;\n\
    \        }\n\n        unsigned char first = static_cast<unsigned char>(input_[position_]);\n\
    \        if (!(std::isalpha(first) || input_[position_] == '_')) {\n         \
    \   position_ = begin_attempt;\n            return std::nullopt;\n        }\n\n\
    \        std::size_t begin = position_++;\n        while (!eof()) {\n        \
    \    unsigned char current = static_cast<unsigned char>(input_[position_]);\n\
    \            if (!(std::isalnum(current) || input_[position_] == '_')) {\n   \
    \             break;\n            }\n            ++position_;\n        }\n   \
    \     return input_.substr(begin, position_ - begin);\n    }\n\n    std::string_view\
    \ identifier() {\n        std::size_t error_position = position_;\n        std::optional<std::string_view>\
    \ result = try_identifier();\n        if (!result.has_value()) {\n           \
    \ position_ = error_position;\n            fail(\"expected identifier\");\n  \
    \      }\n        return *result;\n    }\n\n    template <typename Integer>\n\
    \    std::optional<Integer> try_integer(int base = 10) {\n        static_assert(\n\
    \            std::is_integral_v<Integer> && !std::is_same_v<Integer, bool>,\n\
    \            \"Integer must be a non-bool integral type\"\n        );\n      \
    \  if (base < 2 || base > 36) {\n            throw std::invalid_argument(\"integer\
    \ base must be in [2, 36]\");\n        }\n\n        mark_type begin_attempt =\
    \ mark();\n        skip_whitespace();\n\n        bool negative = false;\n    \
    \    if (consume('+')) {\n            // The sign is already consumed.\n     \
    \   } else if (consume('-')) {\n            if constexpr (std::is_unsigned_v<Integer>)\
    \ {\n                position_ = begin_attempt;\n                return std::nullopt;\n\
    \            } else {\n                negative = true;\n            }\n     \
    \   }\n\n        using Unsigned = std::make_unsigned_t<Integer>;\n        Unsigned\
    \ limit = std::numeric_limits<Integer>::max();\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            if (negative) {\n                limit += Unsigned(1);\n    \
    \        }\n        }\n\n        Unsigned value = 0;\n        std::size_t digit_count\
    \ = 0;\n        while (!eof()) {\n            int digit = digit_value(input_[position_]);\n\
    \            if (digit < 0 || digit >= base) {\n                break;\n     \
    \       }\n            Unsigned unsigned_digit = static_cast<Unsigned>(digit);\n\
    \            if (value > (limit - unsigned_digit) / static_cast<Unsigned>(base))\
    \ {\n                position_ = begin_attempt;\n                return std::nullopt;\n\
    \            }\n            value = value * static_cast<Unsigned>(base) + unsigned_digit;\n\
    \            ++position_;\n            ++digit_count;\n        }\n\n        if\
    \ (digit_count == 0) {\n            position_ = begin_attempt;\n            return\
    \ std::nullopt;\n        }\n\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            if (negative) {\n                if (value == static_cast<Unsigned>(std::numeric_limits<Integer>::max())\
    \ + 1) {\n                    return std::numeric_limits<Integer>::min();\n  \
    \              }\n                return static_cast<Integer>(-static_cast<Integer>(value));\n\
    \            }\n        }\n        return static_cast<Integer>(value);\n    }\n\
    \n    template <typename Integer>\n    Integer integer(int base = 10) {\n    \
    \    std::size_t error_position = position_;\n        std::optional<Integer> result\
    \ = try_integer<Integer>(base);\n        if (!result.has_value()) {\n        \
    \    position_ = error_position;\n            fail(\"expected integer\");\n  \
    \      }\n        return *result;\n    }\n\n    std::optional<long double> try_real()\
    \ noexcept {\n        mark_type begin_attempt = mark();\n        skip_whitespace();\n\
    \n        bool negative = false;\n        if (consume('+')) {\n            //\
    \ The sign is already consumed.\n        } else if (consume('-')) {\n        \
    \    negative = true;\n        }\n\n        long double value = 0;\n        std::size_t\
    \ digit_count = 0;\n        while (!eof() && std::isdigit(static_cast<unsigned\
    \ char>(input_[position_]))) {\n            value = value * 10 + (input_[position_]\
    \ - '0');\n            ++position_;\n            ++digit_count;\n        }\n\n\
    \        if (consume('.')) {\n            long double place = 0.1L;\n        \
    \    while (!eof() && std::isdigit(static_cast<unsigned char>(input_[position_])))\
    \ {\n                value += (input_[position_] - '0') * place;\n           \
    \     place *= 0.1L;\n                ++position_;\n                ++digit_count;\n\
    \            }\n        }\n\n        if (digit_count == 0) {\n            position_\
    \ = begin_attempt;\n            return std::nullopt;\n        }\n\n        mark_type\
    \ exponent_begin = mark();\n        int exponent = 0;\n        bool exponent_negative\
    \ = false;\n        if (consume('e') || consume('E')) {\n            if (consume('+'))\
    \ {\n                // The sign is already consumed.\n            } else if (consume('-'))\
    \ {\n                exponent_negative = true;\n            }\n\n            std::size_t\
    \ exponent_digits = 0;\n            while (!eof() && std::isdigit(static_cast<unsigned\
    \ char>(input_[position_]))) {\n                if (exponent < 1000000) {\n  \
    \                  exponent = exponent * 10 + (input_[position_] - '0');\n   \
    \             }\n                ++position_;\n                ++exponent_digits;\n\
    \            }\n            if (exponent_digits == 0) {\n                position_\
    \ = exponent_begin;\n                exponent = 0;\n                exponent_negative\
    \ = false;\n            }\n        }\n\n        if (exponent != 0) {\n       \
    \     long double scale = std::pow(10.0L, exponent);\n            value = exponent_negative\
    \ ? value / scale : value * scale;\n        }\n        return negative ? -value\
    \ : value;\n    }\n\n    long double real() {\n        std::size_t error_position\
    \ = position_;\n        std::optional<long double> result = try_real();\n    \
    \    if (!result.has_value()) {\n            position_ = error_position;\n   \
    \         fail(\"expected real number\");\n        }\n        return *result;\n\
    \    }\n\n    std::optional<std::string_view> try_balanced(\n        char opening\
    \ = '(',\n        char closing = ')'\n    ) {\n        if (opening == closing)\
    \ {\n            throw std::invalid_argument(\"balanced delimiters must be different\"\
    );\n        }\n\n        mark_type begin_attempt = mark();\n        skip_whitespace();\n\
    \        if (!consume(opening)) {\n            position_ = begin_attempt;\n  \
    \          return std::nullopt;\n        }\n\n        std::size_t content_begin\
    \ = position_;\n        int depth = 1;\n        while (!eof()) {\n           \
    \ char current = input_[position_++];\n            if (current == opening) {\n\
    \                ++depth;\n            } else if (current == closing) {\n    \
    \            --depth;\n                if (depth == 0) {\n                   \
    \ return input_.substr(content_begin, position_ - content_begin - 1);\n      \
    \          }\n            }\n        }\n\n        position_ = begin_attempt;\n\
    \        return std::nullopt;\n    }\n\n    std::string_view balanced(char opening\
    \ = '(', char closing = ')') {\n        std::size_t error_position = position_;\n\
    \        std::optional<std::string_view> result = try_balanced(opening, closing);\n\
    \        if (!result.has_value()) {\n            position_ = error_position;\n\
    \            fail(\"expected balanced delimiters\");\n        }\n        return\
    \ *result;\n    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n\
    #line 4 \"verify/utilities/parser.test.cpp\"\n\n#include <cassert>\n#line 7 \"\
    verify/utilities/parser.test.cpp\"\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#line 14 \"utilities/fast_io.hpp\"\n\
    #include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
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
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
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
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 15 \"verify/utilities/parser.test.cpp\"\
    \n\nnamespace {\n\nusing m1une::utilities::ParseError;\nusing m1une::utilities::Parser;\n\
    \nvoid test_cursor_and_text() {\n    Parser parser(\"  alpha::beta,tail\");\n\
    \    assert(parser.position() == 0);\n    assert(parser.peek() == ' ');\n    assert(parser.skip_whitespace()\
    \ == 2);\n    assert(parser.try_identifier() == std::optional<std::string_view>(\"\
    alpha\"));\n\n    Parser::mark_type separator = parser.mark();\n    assert(parser.consume(\"\
    ::\"));\n    assert(parser.identifier() == \"beta\");\n    parser.restore(separator);\n\
    \    assert(parser.remaining() == \"::beta,tail\");\n\n    assert(parser.take(2)\
    \ == std::optional<std::string_view>(\"::\"));\n    assert(parser.read_until(',',\
    \ true) == \"beta\");\n    assert(parser.remaining() == \"tail\");\n    assert(!parser.take(5).has_value());\n\
    \    assert(parser.remaining() == \"tail\");\n\n    std::string_view letters =\
    \ parser.read_while([](char character) {\n        return 'a' <= character && character\
    \ <= 'z';\n    });\n    assert(letters == \"tail\");\n    assert(parser.eof());\n\
    \    assert(!parser.peek().has_value());\n}\n\nvoid test_checkpoints() {\n   \
    \ Parser parser(\"first second\");\n    {\n        auto attempt = parser.checkpoint();\n\
    \        assert(parser.token() == \"first\");\n    }\n    assert(parser.position()\
    \ == 0);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"first\");\n        attempt.commit();\n    }\n    assert(parser.position()\
    \ == 5);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"second\");\n        attempt.rollback();\n    }\n    assert(parser.position()\
    \ == 5);\n}\n\nvoid test_integers() {\n    Parser parser(\" -9223372036854775808\
    \ 9223372036854775807 +255 ff 101101\");\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::min());\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::max());\n    assert(parser.integer<unsigned>()\
    \ == 255U);\n    assert(parser.integer<int>(16) == 255);\n    assert(parser.integer<int>(2)\
    \ == 45);\n\n    Parser overflow(\" 9223372036854775808\");\n    assert(!overflow.try_integer<long\
    \ long>().has_value());\n    assert(overflow.position() == 0);\n\n    Parser negative_unsigned(\"\
    \ -1\");\n    assert(!negative_unsigned.try_integer<unsigned>().has_value());\n\
    \    assert(negative_unsigned.position() == 0);\n\n    Parser invalid(\" + xyz\"\
    );\n    assert(!invalid.try_integer<int>().has_value());\n    assert(invalid.position()\
    \ == 0);\n\n    bool rejected_base = false;\n    try {\n        (void)invalid.try_integer<int>(1);\n\
    \    } catch (const std::invalid_argument&) {\n        rejected_base = true;\n\
    \    }\n    assert(rejected_base);\n}\n\nvoid test_reals_and_balancing() {\n \
    \   Parser parser(\" -.5 12.25e2 3E-1 1e remainder\");\n    assert(std::abs(parser.real()\
    \ + 0.5L) < 1e-18L);\n    assert(std::abs(parser.real() - 1225.0L) < 1e-15L);\n\
    \    assert(std::abs(parser.real() - 0.3L) < 1e-18L);\n    assert(parser.real()\
    \ == 1.0L);\n    assert(parser.peek() == 'e');\n    assert(parser.token() == \"\
    e\");\n    assert(parser.token() == \"remainder\");\n\n    Parser nested(\" [a[b]c]\
    \ suffix\");\n    assert(nested.balanced('[', ']') == \"a[b]c\");\n    assert(nested.token()\
    \ == \"suffix\");\n\n    Parser unclosed(\" (abc\");\n    assert(!unclosed.try_balanced().has_value());\n\
    \    assert(unclosed.position() == 0);\n\n    bool caught = false;\n    try {\n\
    \        Parser bad(\"xyz\");\n        bad.expect(\"abc\");\n    } catch (const\
    \ ParseError& error) {\n        caught = true;\n        assert(error.position()\
    \ == 0);\n    }\n    assert(caught);\n}\n\nlong long parse_expression(Parser&\
    \ parser);\n\nlong long parse_atom(Parser& parser) {\n    parser.skip_whitespace();\n\
    \    if (parser.consume('(')) {\n        long long value = parse_expression(parser);\n\
    \        parser.skip_whitespace();\n        parser.expect(')');\n        return\
    \ value;\n    }\n    return parser.integer<long long>();\n}\n\nlong long parse_expression(Parser&\
    \ parser) {\n    long long value = parse_atom(parser);\n    while (true) {\n \
    \       parser.skip_whitespace();\n        if (parser.consume('+')) {\n      \
    \      value += parse_atom(parser);\n        } else if (parser.consume('-')) {\n\
    \            value -= parse_atom(parser);\n        } else {\n            return\
    \ value;\n        }\n    }\n}\n\nstd::pair<std::string, long long> make_expression(std::uint64_t&\
    \ state, int depth) {\n    state ^= state << 7;\n    state ^= state >> 9;\n  \
    \  if (depth == 0 || state % 4 == 0) {\n        long long value = static_cast<long\
    \ long>(state % 201) - 100;\n        return std::make_pair(std::to_string(value),\
    \ value);\n    }\n\n    std::pair<std::string, long long> left = make_expression(state,\
    \ depth - 1);\n    std::pair<std::string, long long> right = make_expression(state,\
    \ depth - 1);\n    bool add = (state >> 10) & 1;\n    std::string text = \"( \"\
    \ + left.first + (add ? \" + \" : \" - \") + right.first + \" )\";\n    long long\
    \ value = add ? left.second + right.second : left.second - right.second;\n   \
    \ return std::make_pair(std::move(text), value);\n}\n\nvoid test_random_expressions()\
    \ {\n    std::uint64_t state = 0x123456789abcdefULL;\n    for (int trial = 0;\
    \ trial < 5000; ++trial) {\n        std::pair<std::string, long long> generated\
    \ = make_expression(state, 6);\n        Parser parser(generated.first);\n    \
    \    assert(parse_expression(parser) == generated.second);\n        parser.skip_whitespace();\n\
    \        assert(parser.eof());\n    }\n}\n\nvoid test_bulk_integer_parsing() {\n\
    \    constexpr int count = 200000;\n    std::string input;\n    input.reserve(count\
    \ * 5);\n    long long expected = 0;\n    for (int index = 0; index < count; ++index)\
    \ {\n        int value = index % 1000 - 500;\n        input += std::to_string(value);\n\
    \        input.push_back(index + 1 == count ? '\\n' : ' ');\n        expected\
    \ += value;\n    }\n\n    Parser parser(input);\n    long long actual = 0;\n \
    \   for (int index = 0; index < count; ++index) {\n        actual += parser.integer<int>();\n\
    \    }\n    parser.skip_whitespace();\n    assert(parser.eof());\n    assert(actual\
    \ == expected);\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_cursor_and_text();\n\
    \    test_checkpoints();\n    test_integers();\n    test_reals_and_balancing();\n\
    \    test_random_expressions();\n    test_bulk_integer_parsing();\n\n    std::string\
    \ input_text;\n    int character = fast_input.read_char_raw();\n    while (character\
    \ != EOF) {\n        input_text.push_back(char(character));\n        character\
    \ = fast_input.read_char_raw();\n    }\n    Parser parser(input_text);\n    long\
    \ long a = parser.integer<long long>();\n    long long b = parser.integer<long\
    \ long>();\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../utilities/parser.hpp\"\n\n#include <cassert>\n#include <cmath>\n#include\
    \ <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <iterator>\n#include\
    \ <limits>\n#include <optional>\n#include <string>\n#include <string_view>\n#include\
    \ <utility>\n\nnamespace {\n\nusing m1une::utilities::ParseError;\nusing m1une::utilities::Parser;\n\
    \nvoid test_cursor_and_text() {\n    Parser parser(\"  alpha::beta,tail\");\n\
    \    assert(parser.position() == 0);\n    assert(parser.peek() == ' ');\n    assert(parser.skip_whitespace()\
    \ == 2);\n    assert(parser.try_identifier() == std::optional<std::string_view>(\"\
    alpha\"));\n\n    Parser::mark_type separator = parser.mark();\n    assert(parser.consume(\"\
    ::\"));\n    assert(parser.identifier() == \"beta\");\n    parser.restore(separator);\n\
    \    assert(parser.remaining() == \"::beta,tail\");\n\n    assert(parser.take(2)\
    \ == std::optional<std::string_view>(\"::\"));\n    assert(parser.read_until(',',\
    \ true) == \"beta\");\n    assert(parser.remaining() == \"tail\");\n    assert(!parser.take(5).has_value());\n\
    \    assert(parser.remaining() == \"tail\");\n\n    std::string_view letters =\
    \ parser.read_while([](char character) {\n        return 'a' <= character && character\
    \ <= 'z';\n    });\n    assert(letters == \"tail\");\n    assert(parser.eof());\n\
    \    assert(!parser.peek().has_value());\n}\n\nvoid test_checkpoints() {\n   \
    \ Parser parser(\"first second\");\n    {\n        auto attempt = parser.checkpoint();\n\
    \        assert(parser.token() == \"first\");\n    }\n    assert(parser.position()\
    \ == 0);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"first\");\n        attempt.commit();\n    }\n    assert(parser.position()\
    \ == 5);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"second\");\n        attempt.rollback();\n    }\n    assert(parser.position()\
    \ == 5);\n}\n\nvoid test_integers() {\n    Parser parser(\" -9223372036854775808\
    \ 9223372036854775807 +255 ff 101101\");\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::min());\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::max());\n    assert(parser.integer<unsigned>()\
    \ == 255U);\n    assert(parser.integer<int>(16) == 255);\n    assert(parser.integer<int>(2)\
    \ == 45);\n\n    Parser overflow(\" 9223372036854775808\");\n    assert(!overflow.try_integer<long\
    \ long>().has_value());\n    assert(overflow.position() == 0);\n\n    Parser negative_unsigned(\"\
    \ -1\");\n    assert(!negative_unsigned.try_integer<unsigned>().has_value());\n\
    \    assert(negative_unsigned.position() == 0);\n\n    Parser invalid(\" + xyz\"\
    );\n    assert(!invalid.try_integer<int>().has_value());\n    assert(invalid.position()\
    \ == 0);\n\n    bool rejected_base = false;\n    try {\n        (void)invalid.try_integer<int>(1);\n\
    \    } catch (const std::invalid_argument&) {\n        rejected_base = true;\n\
    \    }\n    assert(rejected_base);\n}\n\nvoid test_reals_and_balancing() {\n \
    \   Parser parser(\" -.5 12.25e2 3E-1 1e remainder\");\n    assert(std::abs(parser.real()\
    \ + 0.5L) < 1e-18L);\n    assert(std::abs(parser.real() - 1225.0L) < 1e-15L);\n\
    \    assert(std::abs(parser.real() - 0.3L) < 1e-18L);\n    assert(parser.real()\
    \ == 1.0L);\n    assert(parser.peek() == 'e');\n    assert(parser.token() == \"\
    e\");\n    assert(parser.token() == \"remainder\");\n\n    Parser nested(\" [a[b]c]\
    \ suffix\");\n    assert(nested.balanced('[', ']') == \"a[b]c\");\n    assert(nested.token()\
    \ == \"suffix\");\n\n    Parser unclosed(\" (abc\");\n    assert(!unclosed.try_balanced().has_value());\n\
    \    assert(unclosed.position() == 0);\n\n    bool caught = false;\n    try {\n\
    \        Parser bad(\"xyz\");\n        bad.expect(\"abc\");\n    } catch (const\
    \ ParseError& error) {\n        caught = true;\n        assert(error.position()\
    \ == 0);\n    }\n    assert(caught);\n}\n\nlong long parse_expression(Parser&\
    \ parser);\n\nlong long parse_atom(Parser& parser) {\n    parser.skip_whitespace();\n\
    \    if (parser.consume('(')) {\n        long long value = parse_expression(parser);\n\
    \        parser.skip_whitespace();\n        parser.expect(')');\n        return\
    \ value;\n    }\n    return parser.integer<long long>();\n}\n\nlong long parse_expression(Parser&\
    \ parser) {\n    long long value = parse_atom(parser);\n    while (true) {\n \
    \       parser.skip_whitespace();\n        if (parser.consume('+')) {\n      \
    \      value += parse_atom(parser);\n        } else if (parser.consume('-')) {\n\
    \            value -= parse_atom(parser);\n        } else {\n            return\
    \ value;\n        }\n    }\n}\n\nstd::pair<std::string, long long> make_expression(std::uint64_t&\
    \ state, int depth) {\n    state ^= state << 7;\n    state ^= state >> 9;\n  \
    \  if (depth == 0 || state % 4 == 0) {\n        long long value = static_cast<long\
    \ long>(state % 201) - 100;\n        return std::make_pair(std::to_string(value),\
    \ value);\n    }\n\n    std::pair<std::string, long long> left = make_expression(state,\
    \ depth - 1);\n    std::pair<std::string, long long> right = make_expression(state,\
    \ depth - 1);\n    bool add = (state >> 10) & 1;\n    std::string text = \"( \"\
    \ + left.first + (add ? \" + \" : \" - \") + right.first + \" )\";\n    long long\
    \ value = add ? left.second + right.second : left.second - right.second;\n   \
    \ return std::make_pair(std::move(text), value);\n}\n\nvoid test_random_expressions()\
    \ {\n    std::uint64_t state = 0x123456789abcdefULL;\n    for (int trial = 0;\
    \ trial < 5000; ++trial) {\n        std::pair<std::string, long long> generated\
    \ = make_expression(state, 6);\n        Parser parser(generated.first);\n    \
    \    assert(parse_expression(parser) == generated.second);\n        parser.skip_whitespace();\n\
    \        assert(parser.eof());\n    }\n}\n\nvoid test_bulk_integer_parsing() {\n\
    \    constexpr int count = 200000;\n    std::string input;\n    input.reserve(count\
    \ * 5);\n    long long expected = 0;\n    for (int index = 0; index < count; ++index)\
    \ {\n        int value = index % 1000 - 500;\n        input += std::to_string(value);\n\
    \        input.push_back(index + 1 == count ? '\\n' : ' ');\n        expected\
    \ += value;\n    }\n\n    Parser parser(input);\n    long long actual = 0;\n \
    \   for (int index = 0; index < count; ++index) {\n        actual += parser.integer<int>();\n\
    \    }\n    parser.skip_whitespace();\n    assert(parser.eof());\n    assert(actual\
    \ == expected);\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_cursor_and_text();\n\
    \    test_checkpoints();\n    test_integers();\n    test_reals_and_balancing();\n\
    \    test_random_expressions();\n    test_bulk_integer_parsing();\n\n    std::string\
    \ input_text;\n    int character = fast_input.read_char_raw();\n    while (character\
    \ != EOF) {\n        input_text.push_back(char(character));\n        character\
    \ = fast_input.read_char_raw();\n    }\n    Parser parser(input_text);\n    long\
    \ long a = parser.integer<long long>();\n    long long b = parser.integer<long\
    \ long>();\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/parser.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/utilities/parser.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/parser.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/parser.test.cpp
- /verify/verify/utilities/parser.test.cpp.html
title: verify/utilities/parser.test.cpp
---
