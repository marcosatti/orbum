#pragma once

#include "GlobalMacros.h"

/*
Global logging functions.
*/

#if defined(PCSX2_DEBUG)
INLINE void logDebug(const char * message);
#endif
INLINE void logInfo(const char * message);