#pragma once

#include "GlobalMacros.h"

/*
Global logging functions.
*/

#if defined(BUILD_DEBUG)
void logDebug(char * message);
#endif
void logInfo(char * message);