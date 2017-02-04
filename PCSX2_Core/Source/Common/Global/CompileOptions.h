#pragma once

#include "Common/Global/Macros.h"

///////////////////
// Debug Options //
///////////////////

/*
Define if the emulator should log host Memory_t allocations or not. 
Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_MEMORY_LOG_ALLOCATIONS 0
#else
 #define DEBUG_MEMORY_LOG_ALLOCATIONS 0
#endif

/*
When debugging memory accesses (see DebugMemory_t), choose if to log values read/written as hex instead of decimal.
*/
#if defined(BUILD_DEBUG)
#define DEBUG_MEMORY_LOG_VALUE_AS_HEX 1
#else
#define DEBUG_MEMORY_LOG_VALUE_AS_HEX 0
#endif

/*
Define if the emulator should log EE SIO messages (serial I/O port). 
See PS2Resources/EE/Types/EERegsiters_t/EERegister_SIO_t for where the SIO is implemented.
Only enabled when a debug build is selected.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_SIO_LOG_MESSAGES 1
#else
 #define DEBUG_SIO_LOG_MESSAGES 0
#endif

/*
Debug log EECore and IOPCore syscalls. See the SYSCALL() instructions in each one.
*/
#if defined(BUILD_DEBUG)
#define DEBUG_SYSCALL_LOG 0
#else
#define DEBUG_SYSCALL_LOG 0
#endif

/*
Option of whether to throw a runtime error on index out of bounds access for BitfieldRegister32_t. 
Turn off if you are sure that no errors will occur and want to debug quicker.
*/
#if defined(BUILD_DEBUG)
#define ERROR_BR32_FIELD_INDEX_RANGE 0
#else
#define ERROR_BR32_FIELD_INDEX_RANGE 0
#endif