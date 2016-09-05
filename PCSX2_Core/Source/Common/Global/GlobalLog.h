#pragma once

#include "GlobalMacros.h"

/*
Global logging functions.
Do not write a new line character - this is done automatically.
*/

#if defined(BUILD_DEBUG)
void logDebug(const char * format, ...);
#endif
void logInfo(const char * format, ...);