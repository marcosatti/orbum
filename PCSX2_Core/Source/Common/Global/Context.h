#pragma once

#include "Common/Global/Macros.h"

/*
Defines contexts that are used within the PS2 system.
*/
enum Context
{
	RAW, // Use for raw access (ie: within VM PS2 system logic code if needed).
	EE,
	IOP,
};

#if defined(BUILD_DEBUG)
/*
Static array of names used for debug logging.
*/
static constexpr char * CONTEXT_STR[3] = { "RAW", "EE", "IOP" };
static const char* getContextStr(const Context & context)
{
	return CONTEXT_STR[static_cast<int>(context)];
}
#endif
