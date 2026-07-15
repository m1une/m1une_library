#ifndef M1UNE_PCH_HPP
#define M1UNE_PCH_HPP 1

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("O0")
#endif
#else
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#endif
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

#endif  // M1UNE_PCH_HPP
