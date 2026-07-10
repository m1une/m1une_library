#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

void test_fast_input() {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);
    std::fputs(" -123 456 token Z 1\n", file);
    std::rewind(file);

    m1une::utilities::FastInput input(file);
    int a;
    unsigned int b;
    std::string s;
    char c;
    bool flag;
    assert(input.read(a, b, s, c, flag));
    assert(a == -123);
    assert(b == 456);
    assert(s == "token");
    assert(c == 'Z');
    assert(flag);
    std::fclose(file);
}

void test_fast_output() {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);

    {
        m1une::utilities::FastOutput output(file);
        output.println("answer", -42, 17u);
        output.println(false);
        output.flush();
    }

    std::rewind(file);
    char buffer[64];
    std::size_t length = std::fread(buffer, 1, sizeof(buffer), file);
    std::string result(buffer, buffer + length);
    assert(result == "answer -42 17\n0\n");
    std::fclose(file);
}

void test_stream_operators_and_vectors() {
    std::FILE* input_file = std::tmpfile();
    assert(input_file != nullptr);
    std::fputs("2 3 1 2 3 4 5 6", input_file);
    std::rewind(input_file);

    int h, w;
    m1une::utilities::FastInput input(input_file);
    input >> h >> w;
    std::vector<std::vector<int>> matrix(h, std::vector<int>(w));
    input >> matrix;
    assert(matrix[0][0] == 1);
    assert(matrix[1][2] == 6);
    std::fclose(input_file);

    std::FILE* output_file = std::tmpfile();
    assert(output_file != nullptr);
    {
        m1une::utilities::FastOutput output(output_file);
        output << "matrix\n" << matrix << '\n';
        output.flush();
    }

    std::rewind(output_file);
    char buffer[64];
    std::size_t length = std::fread(buffer, 1, sizeof(buffer), output_file);
    std::string result(buffer, buffer + length);
    assert(result == "matrix\n1 2 3\n4 5 6\n");
    std::fclose(output_file);
}

int main() {
    test_fast_input();
    test_fast_output();
    test_stream_operators_and_vectors();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    long long a, b;
    input >> a >> b;
    output << a + b << '\n';
}
