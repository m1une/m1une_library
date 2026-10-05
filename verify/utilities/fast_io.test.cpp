#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <array>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <poll.h>
#include <random>
#include <signal.h>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

void test_fast_input() {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);
    std::fputs(
        " -123 456 token Z 1 -12.5 6.25e2 "
        "-170141183460469231731687303715884105728 "
        "340282366920938463463374607431768211455\n",
        file
    );
    std::rewind(file);

    m1une::utilities::FastInput input(file);
    int a;
    unsigned int b;
    std::string s;
    char c;
    bool flag;
    double decimal;
    long double exponent;
    __int128_t signed_wide;
    __uint128_t unsigned_wide;
    assert(input.read(
        a, b, s, c, flag, decimal, exponent, signed_wide, unsigned_wide
    ));
    assert(a == -123);
    assert(b == 456);
    assert(s == "token");
    assert(c == 'Z');
    assert(flag);
    assert(decimal == -12.5);
    assert(exponent == 625.0L);
    __int128_t signed_minimum = -(__int128_t(1) << 126);
    signed_minimum *= 2;
    assert(signed_wide == signed_minimum);
    assert(unsigned_wide == ~__uint128_t(0));
    std::fclose(file);
}

void test_large_string_io() {
    const std::string large(m1une::utilities::FastInput::buffer_size + 123, 'x');
    std::FILE* input_file = std::tmpfile();
    assert(input_file != nullptr);
    assert(std::fwrite(large.data(), 1, large.size(), input_file) == large.size());
    std::fputs(" tail", input_file);
    std::rewind(input_file);

    m1une::utilities::FastInput input(input_file);
    std::string actual, tail;
    input >> actual >> tail;
    assert(actual == large);
    assert(tail == "tail");
    std::fclose(input_file);

    std::FILE* output_file = std::tmpfile();
    assert(output_file != nullptr);
    {
        m1une::utilities::FastOutput output(output_file);
        output << large;
    }
    assert(std::ftell(output_file) == long(large.size()));
    std::rewind(output_file);
    std::string written(large.size(), '\0');
    assert(std::fread(written.data(), 1, written.size(), output_file) == written.size());
    assert(written == large);
    std::fclose(output_file);
}

void test_pipe_input_does_not_wait_for_eof() {
    int request[2];
    int response[2];
    assert(::pipe(request) == 0);
    assert(::pipe(response) == 0);

    const pid_t child = ::fork();
    assert(child >= 0);
    if (child == 0) {
        ::close(request[1]);
        ::close(response[0]);
        std::FILE* stream = ::fdopen(request[0], "r");
        if (stream == nullptr) _exit(1);

        m1une::utilities::FastInput input(stream);
        int value;
        const bool ok = input.read(value) && value == 123456789;
        if (ok) {
            const char byte = 'x';
            if (::write(response[1], &byte, 1) != 1) _exit(1);
        }
        std::fclose(stream);
        ::close(response[1]);
        _exit(ok ? 0 : 1);
    }

    ::close(request[0]);
    ::close(response[1]);
    const char query[] = "123456789\n";
    assert(
        ::write(request[1], query, sizeof(query) - 1)
        == ssize_t(sizeof(query) - 1)
    );

    pollfd event;
    event.fd = response[0];
    event.events = POLLIN;
    event.revents = 0;
    const int ready = ::poll(&event, 1, 1000);

    ::close(request[1]);
    if (ready <= 0) ::kill(child, SIGKILL);
    int status;
    assert(::waitpid(child, &status, 0) == child);
    assert(ready == 1);
    assert((event.revents & POLLIN) != 0);
    char byte;
    assert(::read(response[0], &byte, 1) == 1);
    assert(byte == 'x');
    assert(WIFEXITED(status) && WEXITSTATUS(status) == 0);
    ::close(response[0]);
}

void test_fast_output() {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);

    {
        m1une::utilities::FastOutput output(file);
        output.println("answer", -42, 17u);
        output.println(false);
        output.set_fixed(2);
        output.println(1.25);
        __int128_t signed_minimum = -(__int128_t(1) << 126);
        signed_minimum *= 2;
        output.println(signed_minimum);
        output.println(~__uint128_t(0));
        output.flush();
    }

    std::rewind(file);
    char buffer[256];
    std::size_t length = std::fread(buffer, 1, sizeof(buffer), file);
    std::string result(buffer, buffer + length);
    assert(
        result
        == "answer -42 17\n0\n1.25\n"
           "-170141183460469231731687303715884105728\n"
           "340282366920938463463374607431768211455\n"
    );
    std::fclose(file);
}

void test_output_flush_reaches_pipe() {
    int descriptors[2];
    assert(::pipe(descriptors) == 0);
    std::FILE* stream = ::fdopen(descriptors[1], "w");
    assert(stream != nullptr);

    {
        m1une::utilities::FastOutput output(stream);
        output << "? 987654321\n";
        output.flush();

        pollfd event;
        event.fd = descriptors[0];
        event.events = POLLIN;
        event.revents = 0;
        assert(::poll(&event, 1, 1000) == 1);
        assert((event.revents & POLLIN) != 0);

        const char expected[] = "? 987654321\n";
        char actual[sizeof(expected) - 1];
        assert(
            ::read(descriptors[0], actual, sizeof(actual))
            == ssize_t(sizeof(actual))
        );
        assert(std::string(actual, actual + sizeof(actual)) == expected);
    }

    std::fclose(stream);
    ::close(descriptors[0]);
}

void test_stream_operators_ranges_and_pairs() {
    std::FILE* input_file = std::tmpfile();
    assert(input_file != nullptr);
    std::fputs(
        "2 3 1 2 3 4 5 6 label 7 8 9 10 11 12 13 14",
        input_file
    );
    std::rewind(input_file);

    int h, w;
    m1une::utilities::FastInput input(input_file);
    input >> h >> w;
    std::vector<std::vector<int>> matrix(h, std::vector<int>(w));
    input >> matrix;
    assert(matrix[0][0] == 1);
    assert(matrix[1][2] == 6);

    std::pair<std::string, int> item;
    input >> item;
    assert(item.first == "label");
    assert(item.second == 7);

    std::vector<std::pair<int, int>> pairs(2);
    input >> pairs;
    const std::pair<int, int> expected_first(8, 9);
    const std::pair<int, int> expected_second(10, 11);
    assert(pairs[0] == expected_first);
    assert(pairs[1] == expected_second);

    std::pair<std::vector<int>, int> grouped;
    grouped.first.resize(2);
    input >> grouped;
    assert(grouped.first[0] == 12);
    assert(grouped.first[1] == 13);
    assert(grouped.second == 14);
    std::fclose(input_file);

    std::FILE* output_file = std::tmpfile();
    assert(output_file != nullptr);
    {
        m1une::utilities::FastOutput output(output_file);
        output << "matrix\n" << matrix << '\n';
        output << item << '\n';
        output << pairs << '\n';
        output << grouped << '\n';
        output.set_range_separator('\n');
        output << pairs << '\n';
        output.set_range_separator(' ');
        output << grouped.first << '\n';
        output.flush();
    }

    std::rewind(output_file);
    char buffer[128];
    std::size_t length = std::fread(buffer, 1, sizeof(buffer), output_file);
    std::string result(buffer, buffer + length);
    assert(
        result
        == "matrix\n1 2 3\n4 5 6\nlabel 7\n8 9 10 11\n12 13 14\n"
           "8 9\n10 11\n12 13\n"
    );
    std::fclose(output_file);
}

template <class Function>
std::string capture_output(Function function) {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);
    {
        m1une::utilities::FastOutput output(file);
        function(output);
    }
    std::rewind(file);
    std::string result;
    char buffer[4096];
    while (const std::size_t length = std::fread(buffer, 1, sizeof(buffer), file)) {
        result.append(buffer, length);
    }
    std::fclose(file);
    return result;
}

void test_aligned_output() {
    const std::vector<std::vector<int>> matrix = {
        {1, -20, 300}, {4000, 5, -6}, {}, {7}
    };
    const auto original = matrix;
    assert(capture_output([&](auto& output) {
        output << "aligned\n";
        output.println_aligned(matrix);
        output << matrix << '\n';
        output.set_range_separator(',');
        output.write_aligned(matrix);
        output << '!';
        output.println_aligned(std::vector<std::vector<int>>{});
    }) == "aligned\n   1 -20 300\n4000   5  -6\n\n   7\n"
          "1 -20 300\n4000 5 -6\n\n7\n"
          "   1,-20,300\n4000,  5, -6\n\n   7!\n");
    assert(matrix == original);

    const std::vector<std::vector<double>> decimals = {
        {1.25, -0.5}, {100, 20.125}
    };
    assert(capture_output([&](auto& output) {
        output.set_fixed(2);
        output.println_aligned(decimals);
        output.set_general(3);
        output.println_aligned(decimals);
    }) == "  1.25 -0.50\n100.00 20.12\n1.25 -0.5\n 100 20.1\n");

    const std::vector<std::vector<std::string>> words = {
        {"x", "long"}, {"word", "y"}
    };
    const std::vector<std::vector<bool>> flags = {
        {true, false}, {false, true}
    };
    const int array[2][2] = { {1, 200}, {-30, 4} };
    const std::array<std::array<char, 2>, 2> chars = {
        std::array<char, 2>{'a', 'b'}, std::array<char, 2>{'c', 'd'}
    };
    const std::vector<std::vector<std::pair<int, int>>> pairs = {
        {std::pair<int, int>(1, 2)}, {std::pair<int, int>(100, -3)}
    };
    assert(capture_output([&](auto& output) {
        output.println_aligned(words);
        output.println_aligned(flags);
        output.println_aligned(array);
        output.println_aligned(chars);
        output.println_aligned(pairs);
    }) == "   x long\nword    y\n1 0\n0 1\n  1 200\n-30   4\na b\nc d\n"
          "   1 2\n100 -3\n");

    __int128_t minimum = -(__int128_t(1) << 126);
    minimum *= 2;
    const std::vector<std::vector<__int128_t>> wide = { {minimum}, {0} };
    const std::vector<std::vector<__uint128_t>> unsigned_wide = {
        {~__uint128_t(0)}, {1}
    };
    assert(capture_output([&](auto& output) {
        output.println_aligned(wide);
        output.println_aligned(unsigned_wide);
    }) == "-170141183460469231731687303715884105728\n"
          + std::string(39, ' ') + "0\n"
          + "340282366920938463463374607431768211455\n"
          + std::string(38, ' ') + "1\n");

    const std::string large(m1une::utilities::FastOutput::buffer_size + 123, 'x');
    const std::vector<std::vector<std::string>> long_cells = { {large}, {"y"} };
    assert(capture_output([&](auto& output) {
        output.println_aligned(long_cells);
        output.println(123456789);
    }) == large + '\n' + std::string(large.size() - 1, ' ') + "y\n123456789\n");
}

void test_random_aligned_output() {
    std::mt19937 random(20261005);
    for (int trial = 0; trial < 200; ++trial) {
        std::vector<std::vector<int>> matrix(random() % 9);
        std::vector<int> widths(8);
        for (auto& row : matrix) {
            row.resize(random() % 9);
            for (std::size_t j = 0; j < row.size(); ++j) {
                row[j] = int(random() % 2000001) - 1000000;
                if (random() % 10 == 0) row[j] = std::numeric_limits<int>::min();
                widths[j] = std::max(widths[j], int(std::to_string(row[j]).size()));
            }
        }
        std::ostringstream expected;
        for (std::size_t i = 0; i < matrix.size(); ++i) {
            if (i != 0) expected << '\n';
            for (std::size_t j = 0; j < matrix[i].size(); ++j) {
                if (j != 0) expected << ' ';
                expected << std::setw(widths[j]) << matrix[i][j];
            }
        }
        assert(capture_output([&](auto& output) {
            output.write_aligned(matrix);
        }) == expected.str());
    }
}

int main() {
    test_fast_input();
    test_large_string_io();
    test_pipe_input_does_not_wait_for_eof();
    test_fast_output();
    test_output_flush_reaches_pipe();
    test_stream_operators_ranges_and_pairs();
    test_aligned_output();
    test_random_aligned_output();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    long long a, b;
    input >> a >> b;
    output << a + b << '\n';
}
