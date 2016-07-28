#pragma once

#include "GlobalMacros.h"

/*
Global logging functions.
*/

#if defined(BUILD_DEBUG)
INLINE void logDebug(const char * message);
#endif
INLINE void logInfo(const char * message);