#include "stdafx.h"

#include <cstdarg>
#include <cstdio>
#include <mutex>

#include "GlobalMacros.h"
#include "GlobalLog.h"

/*
Extern log delegate function, set by the VM at initalisation.
*/
void(*logDelegate)(const char * buffer);

// Thanks to http://stackoverflow.com/questions/17936786/prepend-or-append-to-every-printf-call for the method of customising printf calls.
#if defined(BUILD_DEBUG)
void logDebug(const char * format, ...)
{
	static std::mutex mutex;
	
	const size_t buffer_sz = 1024;
	size_t count = 0;

	char buffer[buffer_sz];
	count = snprintf(buffer + count, buffer_sz - count, "[DEBUG] ");

	va_list args;
	va_start(args, format);
	count += vsnprintf(buffer + count, buffer_sz - count, format, args);
	va_end(args);

	snprintf(buffer + count, buffer_sz - count, "\n");

	mutex.lock();
	logDelegate(buffer);
	mutex.unlock();
}
#endif

void logInfo(const char * format, ...)
{
	const size_t buffer_sz = 1024;
	size_t count = 0;

	char buffer[buffer_sz];
	count = snprintf(buffer + count, buffer_sz - count, "[INFO] ");

	va_list args;
	va_start(args, format);
	count += vsnprintf(buffer + count, buffer_sz - count, format, args);
	va_end(args);

	snprintf(buffer + count, buffer_sz - count, "\n");

	logDelegate(buffer);
}
