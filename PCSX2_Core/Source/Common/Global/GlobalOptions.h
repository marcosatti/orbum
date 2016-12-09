#pragma once

#include "Common/Global/GlobalMacros.h"

/*
Define if the emulator should log host memory allocations or not. 
Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_ALLOCATIONS 0
#else
 #define DEBUG_LOG_ALLOCATIONS 0
#endif

/*
Define if the emulator should log SIO messages (serial I/O port). See PS2Resources/EE/Types/EERegsiters_t -> EERegister_SIO_t 
 for where the SIO is implemented.
Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_SIO_MESSAGES 1
#else
 #define DEBUG_LOG_SIO_MESSAGES 0
#endif

/*
Define if the emulator should print a warning when a read only mapped memory object has tried to be written to.
This does not always indicate abnormal behaviour!
Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
#define DEBUG_LOG_RO_MM_WRITES 0
#else
#define DEBUG_LOG_RO_MM_WRITES 0
#endif

/*
When debugging memory accesses (see DebugMemory_t), choose if to log values read/written as hex instead of decimal.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_MEM_LOG_VALUE_AS_HEX 1
#endif