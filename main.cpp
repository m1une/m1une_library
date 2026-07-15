#ifdef LOCAL
#define _GLIBCXX_DEBUG
#pragma GCC optimize("O0")
#else
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#endif

#ifdef LOCAL
// https://zenn.dev/sassan/articles/19db660e4da0a4
#include "cpp-dump/cpp-dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)
#endif

#include "template.hpp"

#include "utilities/fast_io.hpp"
m1une::utilities::FastInput fastin;
m1une::utilities::FastOutput fastout;

void solve() {
    
}

int main() {
    CPP_DUMP_SET_OPTION(max_line_width, 80);
    CPP_DUMP_SET_OPTION(log_label_func, cpp_dump::log_label::filename());
    CPP_DUMP_SET_OPTION(enable_asterisk, true);
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}
