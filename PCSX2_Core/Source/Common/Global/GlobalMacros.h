#pragma once

/*
Platform macros, to make sure they are universal.
*/
#if defined(__WINDOWS__) || defined(_WIN32) || defined(_WIN64)
#define ENV_WINDOWS
#elif defined(__UNIX) || defined(__UNIX__) || defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__)
#define ENV_UNIX
#endif

/*
Enable the BUILD_DEBUG token if a debug build configuration is detected.
*/
#if defined(_DEBUG) || defined(_DEBUG_BUILD)
#define BUILD_DEBUG
#endif

/*
Get the filename only from __FILENAME__, thanks to http://stackoverflow.com/questions/8487986/file-macro-shows-full-path.
*/
#include <string.h>

#if defined(ENV_WINDOWS)
 #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
 #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif