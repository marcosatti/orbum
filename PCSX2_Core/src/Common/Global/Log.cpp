#include <cstdarg>

#include "Common/Global/Log.h"

void (*LOG_CALLBACK_FUNCPTR)(const LogLevel_t level, const std::string & message);

void log(const LogLevel_t level, const char* format, ...)
{
	// Construct message.
	va_list args;
	va_start(args, format);
	const size_t buffer_sz = 1024;
	char buffer[buffer_sz];
	vsnprintf(buffer, buffer_sz, format, args);
	va_end(args);

	// Call the frontend to log the message.
	if (LOG_CALLBACK_FUNCPTR != nullptr)
		LOG_CALLBACK_FUNCPTR(level, buffer);
}
