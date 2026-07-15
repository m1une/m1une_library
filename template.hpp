#ifndef M1UNE_TEMPLATE_HPP
#define M1UNE_TEMPLATE_HPP 1

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <codecvt>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <coroutine>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <initializer_list>
#include <iostream>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

#include "utilities/fast_io.hpp"
using namespace std;

namespace m1une {
namespace template_io {

inline utilities::FastInput& input() {
    static utilities::FastInput instance;
    return instance;
}

inline utilities::FastOutput& output() {
    static utilities::FastOutput instance;
    return instance;
}

}  // namespace template_io
}  // namespace m1une

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
#ifdef __SIZEOF_FLOAT128__
using f128 = __float128;
#endif

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'000'000'000;
template <>
constexpr ll infty<ll> = ll(infty<int>) * infty<int> * 2;
template <>
constexpr u32 infty<u32> = infty<int>;
template <>
constexpr u64 infty<u64> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * infty<ll>;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
using vvi = vvc<int>;
using vvl = vvc<ll>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
template <class T>
using vvvvvc = vector<vvvvc<T>>;
template <class T>
using pqg = std::priority_queue<T, vector<T>, greater<T>>;
template <class T, class U>
using umap = unordered_map<T, U>;

// template <typename K>
// using tree = __gnu_pbds::tree<K, __gnu_pbds::null_type, std::less<>,
//                               __gnu_pbds::rb_tree_tag,
//                               __gnu_pbds::tree_order_statistics_node_update>;

#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...) \
    vector<vector<vector<type>>> name(h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)         \
    vector<vector<vector<vector<type>>>> name( \
        a, vector<vector<vector<type>>>(b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d

// FOR(a) :=  for (ll _ = 0; _ < (ll)a; ++_)
// FOR(i, a) := for (ll i = 0; i < (ll)a; ++i)
// FOR(i, a, b) := for (ll i = a; i < (ll)b; ++i)
// FOR(i, a, b, c) := for (ll i = a; i < (ll)b; i += (c))
// FOR_R(a) := for (ll i = (a) - 1; i >= 0; --i)
// FOR_R(i, a) := for (ll i = (a) - 1; i >= 0; --i)
// FOR_R(i, a, b) := for (ll i = (b) - 1; i >= (ll)a; --i)
#define FOR1(a) for (ll _ = 0; _ < (ll)a; ++_)
#define FOR2(i, a) for (ll i = 0; i < (ll)a; ++i)
#define FOR3(i, a, b) for (ll i = a; i < (ll)b; ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < (ll)b; i += (c))
#define FOR1_R(a) for (ll i = (a) - 1; i >= 0; --i)
#define FOR2_R(i, a) for (ll i = (a) - 1; i >= 0; --i)
#define FOR3_R(i, a, b) for (ll i = (b) - 1; i >= (ll)a; --i)
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define FORI1(a) for (int _ = 0; _ < (int)a; ++_)
#define FORI2(i, a) for (int i = 0; i < (int)a; ++i)
#define FORI3(i, a, b) for (int i = a; i < (int)b; ++i)
#define FORI4(i, a, b, c) for (int i = a; i < (int)b; i += (c))
#define FORI1_R(a) for (int i = (a) - 1; i >= 0; --i)
#define FORI2_R(i, a) for (int i = (a) - 1; i >= 0; --i)
#define FORI3_R(i, a, b) for (int i = (b) - 1; i >= (int)a; --i)
#define FORI(...) overload4(__VA_ARGS__, FORI4, FORI3, FORI2, FORI1)(__VA_ARGS__)
#define FORI_R(...) overload3(__VA_ARGS__, FORI3_R, FORI2_R, FORI1_R)(__VA_ARGS__)

#define FOR_subset(t, s) for (int t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

int popcnt(int x) {
    return __builtin_popcount(x);
}
int popcnt(u32 x) {
    return __builtin_popcount(x);
}
int popcnt(ll x) {
    return __builtin_popcountll(x);
}
int popcnt(u64 x) {
    return __builtin_popcountll(x);
}
int popcnt_mod_2(int x) {
    return __builtin_parity(x);
}
int popcnt_mod_2(u32 x) {
    return __builtin_parity(x);
}
int popcnt_mod_2(ll x) {
    return __builtin_parityll(x);
}
int popcnt_mod_2(u64 x) {
    return __builtin_parityll(x);
}
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) {
    return (x == 0 ? -1 : 31 - __builtin_clz(x));
}
int topbit(u32 x) {
    return (x == 0 ? -1 : 31 - __builtin_clz(x));
}
int topbit(ll x) {
    return (x == 0 ? -1 : 63 - __builtin_clzll(x));
}
int topbit(u64 x) {
    return (x == 0 ? -1 : 63 - __builtin_clzll(x));
}
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) {
    return (x == 0 ? -1 : __builtin_ctz(x));
}
int lowbit(u32 x) {
    return (x == 0 ? -1 : __builtin_ctz(x));
}
int lowbit(ll x) {
    return (x == 0 ? -1 : __builtin_ctzll(x));
}
int lowbit(u64 x) {
    return (x == 0 ? -1 : __builtin_ctzll(x));
}

template <typename T>
T floor(T a, T b) {
    return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
    return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
    return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
    T q = floor(x, y);
    return {q, x - q * y};
}

template <typename T, typename U>
T POW(U x_, int n) {
    T x = x_;
    T ret = 1;
    while (n > 0) {
        if (n & 1) ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

template <typename T, typename U>
T SUM(const vector<U>& A) {
    T sm = 0;
    for (auto&& a : A) sm += a;
    return sm;
}

#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <class T, class S>
inline bool chmax(T& a, const S& b) {
    return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T& a, const S& b) {
    return (a > b ? a = b, 1 : 0);
}

// ? は -1
vc<int> s_to_vi(const string& S, char first_char) {
    vc<int> A(S.size());
    FOR(i, S.size()) {
        A[i] = (S[i] != '?' ? S[i] - first_char : -1);
    }
    return A;
}

template <typename T, typename U>
vector<T> cumsum(vector<U>& A, int off = 1) {
    int N = A.size();
    vector<T> B(N + 1);
    FOR(i, N) {
        B[i + 1] = B[i] + A[i];
    }
    if (off == 0) B.erase(B.begin());
    return B;
}

template <typename T>
vector<int> argsort(const vector<T>& A) {
    vector<int> ids(A.size());
    iota(all(ids), 0);
    sort(all(ids), [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
    return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T>& A, const vc<int>& I) {
    vc<T> B(I.size());
    FOR(i, I.size()) B[i] = A[I[i]];
    return B;
}

template <class... T>
constexpr auto min(T... a) {
    return min(initializer_list<common_type_t<T...>>{a...});
}
template <class... T>
constexpr auto max(T... a) {
    return max(initializer_list<common_type_t<T...>>{a...});
}

template <class... Ts>
void print(const Ts&... values) {
    m1une::template_io::output().println(values...);
}
void YESNO(bool b) {
    m1une::template_io::output().println(b ? "YES" : "NO");
}
void YesNo(bool b) {
    m1une::template_io::output().println(b ? "Yes" : "No");
}
void YES() {
    m1une::template_io::output().println("YES");
}
void NO() {
    m1une::template_io::output().println("NO");
}
void Yes() {
    m1une::template_io::output().println("Yes");
}
void No() {
    m1une::template_io::output().println("No");
}
#endif  // M1UNE_TEMPLATE_HPP
