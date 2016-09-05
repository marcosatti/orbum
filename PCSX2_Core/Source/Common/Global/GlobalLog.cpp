#include "stdafx.h"

#include <cstdarg>
#include <cstdio>

#include "GlobalMacros.h"

// Thanks to http://stackoverflow.com/questions/17936786/prepend-or-append-to-every-printf-call for the method of customising printf calls.

#if defined(BUILD_DEBUG)
void logDebug(const char * format, ...)
{
	printf("[DEBUG] ");
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\n");
}
#endif

void logInfo(const char * format, ...)
{
	printf("[INFO] ");
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\n");
}