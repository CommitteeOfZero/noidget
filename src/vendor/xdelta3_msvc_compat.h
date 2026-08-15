#pragma once
// Force-included (see conf.pri) ahead of xdelta3.h on MSVC builds: xdelta3.h
// uses GCC/Clang-only __attribute__((__format__(...))) syntax behind an
// #ifndef PRINTF_ATTRIBUTE guard. Defining it here (a real #define, unlike a
// command-line /D which MSVC's cl.exe doesn't expand for function-like
// macros) neutralizes it without touching the vendored header.
#define PRINTF_ATTRIBUTE(x, y)
