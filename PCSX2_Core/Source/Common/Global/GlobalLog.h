#pragma once

#include "GlobalMacros.h"

/*
Global logging functions.
*/

#if defined(BUILD_DEBUG)
void logDebug(const char * const message);
#endif
void logInfo(const char * const message);