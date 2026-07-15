#include "pch.hpp"

auto& fastin = m1une::template_io::input();
auto& fastout = m1une::template_io::output();

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
