#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../template.hpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <vector>

std::FILE* helper_output = std::tmpfile();

void test_output_helpers() {
    assert(helper_output != nullptr);
    const int saved_stdout = ::dup(::fileno(stdout));
    assert(saved_stdout != -1);
    assert(::dup2(::fileno(helper_output), ::fileno(stdout)) != -1);

    print();
    print(1, "two");

    std::vector<int> values(3);
    values[0] = 3;
    values[1] = 4;
    values[2] = 5;
    print(values);

    const std::pair<int, int> edge(6, 7);
    print(edge);

    m1une::template_io::output().set_range_separator('\n');
    print(values);
    m1une::template_io::output().set_range_separator(' ');

    YESNO(true);
    YESNO(false);
    YesNo(true);
    YesNo(false);
    YES();
    NO();
    Yes();
    No();
    m1une::template_io::output().flush();
    std::fflush(stdout);
    assert(::dup2(saved_stdout, ::fileno(stdout)) != -1);
    ::close(saved_stdout);

    std::rewind(helper_output);
    char buffer[128];
    const std::size_t length = std::fread(buffer, 1, sizeof(buffer), helper_output);
    const std::string result(buffer, buffer + length);
    assert(
        result
        == "\n1 two\n3 4 5\n6 7\n3\n4\n5\n"
           "YES\nNO\nYes\nNo\nYES\nNO\nYes\nNo\n"
    );
}

int main() {
    test_output_helpers();

    long long a, b;
    std::scanf("%lld%lld", &a, &b);
    print(a + b);
}
