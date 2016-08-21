#include "stdafx.h"

#include <iostream>

#include "GlobalMacros.h"

#if defined(BUILD_DEBUG)
void logDebug(char * message)
{
	std::cout << "[DEBUG] " << message << std::endl;
}
#endif

void logInfo(char * message)
{
	std::cout << "[INFO] " << message << std::endl;
}