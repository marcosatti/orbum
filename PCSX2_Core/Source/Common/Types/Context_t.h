#pragma once

/*
Currently used by memory mapped I/O (registers) to allow for different functionality based on what component accessed it.
*/
enum Context_t
{
	RAW, // Use for raw access (ie: within VM system logic code if needed).
	EE,
	IOP,
};

#if defined(BUILD_DEBUG)
/*
Static array of names used for debug logging.
*/
static constexpr char * CONTEXT_STR[3] = { "RAW", "EE", "IOP" };
static const char* getContextStr(const Context_t& context)
{
	return CONTEXT_STR[static_cast<u32>(context)];
}
#endif
