#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdio>
#include <string>
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

int main() {
    test_fast_input();
    test_fast_output();
    test_stream_operators_ranges_and_pairs();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    long long a, b;
    input >> a >> b;
    output << a + b << '\n';
}
