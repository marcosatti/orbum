#include "stdafx.h"

#include <iostream>

#include "GlobalMacros.h"

#if defined(PCSX2_DEBUG)
INLINE void logDebug(const char * message)
{
	std::cout << "[DEBUG] " << message << std::endl;
}
#endif

INLINE void logInfo(const char * message)
{
	std::cout << "[INFO] " << message << std::endl;
}