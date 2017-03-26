#pragma once

#include "Common/Global/Macros.h"

/*
Defines contexts that are used within the PS2 system, when accessing memory mapped I/O (registers, memory, etc).
Based on the provided context, special functionality can be implemented.
A raw context is provided that should be used within VM system logic code (ie: reading a register so it doesn't trigger bits).
Note: don't use enum class as it clutters the code up heavily.
*/
enum Context_t
{
	RAW,
	EE,
	IOP,

	COUNT
};

#if defined(BUILD_DEBUG)
/*
Static array of names used for debug logging.
*/
static constexpr char * CONTEXT_STR[static_cast<int>(COUNT)] = { "RAW", "EE", "IOP" };
static const char* getContextStr(const Context_t context)
{
	return CONTEXT_STR[static_cast<int>(context)];
}
#endif
