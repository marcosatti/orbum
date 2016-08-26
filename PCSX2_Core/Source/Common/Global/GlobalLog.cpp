#include "stdafx.h"

#include <iostream>

#include "GlobalMacros.h"

#if defined(BUILD_DEBUG)
void logDebug(const char * const message)
{
	std::cout << "[DEBUG] " << message << std::endl;
}
#endif

void logInfo(const char * const message)
{
	std::cout << "[INFO] " << message << std::endl;
}