#pragma once

#include <string.h>

/// Platform macros, to make sure they are universal.
#if defined(__WINDOWS__) || defined(_WIN32) || defined(_WIN64)
 #define ENV_WINDOWS
#elif defined(__UNIX) || defined(__UNIX__) || defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(unix) || defined(linux) || defined(__unix__) || defined(__linux__)
 #define ENV_UNIX
#endif

/// Get the filename only from __FILENAME__, thanks to:
/// http://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#if defined(ENV_WINDOWS)
 #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
 #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

/// Export/import macros.
#if defined(ENV_WINDOWS)
#define SHARED_EXPORT __declspec(dllexport)
#define SHARED_IMPORT __declspec(dllimport)
#else
#define SHARED_EXPORT 
#define SHARED_IMPORT
#endif