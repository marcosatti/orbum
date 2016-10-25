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

/*
Log delegate function - set at the VM initalisation.
All calls to log* will come through here, which can be redirected to the main UI or a file etc.
*/
extern void(*logDelegate)(const char * buffer);