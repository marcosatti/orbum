#pragma once

#include <string>

/*
Enums of various log levels supported in the emulator.
TODO: move into a solution common folder.
*/
enum LogLevel_t
{
	Info,
	Warning,
	Debug
};

/*
Provides global logging.
Callback function is set by the VM upon initalisation.
*/
extern void (*LOG_CALLBACK_FUNCPTR)(const LogLevel_t level, const std::string message);
void log(const LogLevel_t level, const char * format, ...);