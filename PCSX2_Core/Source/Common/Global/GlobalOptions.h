#pragma once

#include "Common/Global/GlobalMacros.h"

/*
Define if the emulator should log client memory allocations or not. Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_ALLOCATIONS 0
#else
 #define DEBUG_LOG_ALLOCATIONS 0
#endif

/*
Define if the emulator should log SIO messages (serial I/O port). See Common/PS2Resources/EE/Types/EERegsiters_t -> EERegisterSIO_t 
 for where the SIO is implemented.
Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_SIO_MESSAGES 1
#else
 #define DEBUG_LOG_SIO_MESSAGES 0
#endif

/*
Define if the emulator should print a warning when a read only mapped memory object is written to.
*/
#if defined(BUILD_DEBUG)
#define DEBUG_LOG_RO_MM_WRITES 0
#else
#define DEBUG_LOG_RO_MM_WRITES 0
#endif