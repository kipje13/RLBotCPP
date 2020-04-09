#pragma once

// Indicates that the compiler should use unix headers.
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) ||               \
                         (defined(__APPLE__) && defined(__MACH__)))
#define OS_UNIX
#endif

// Indicates that the compiler should use windows headers.
#if defined(_WIN32)
#define OS_WINDOWS
#endif

// Indicates that the program should dynamically link linux libraries (.so)
#if defined(__linux__)
#define OS_DL_LINUX
#endif

// Indicates that the program should dynamically link windows libraries (.dll)
#if defined(_WIN32) || defined(__CYGWIN__)
#define OS_DL_WINDOWS
#endif

// Detect what environment we are compiling for, 32 or 64-bit.
#include <cstdint>
#if INTPTR_MAX == INT32_MAX
#define OS_32
#elif INTPTR_MAX == INT64_MAX
#define OS_64
#else
#error "Environment not 32 or 64-bit."
#endif
