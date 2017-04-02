#pragma once

#include "Common/Global/Macros.h"

////////////////////////////////////////////
// Debug Options                          //
// (Only enabled if using a debug build.) //
////////////////////////////////////////////

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
#define DEBUG_EE_SYSCALL_LOG 0
#define DEBUG_IOP_SYSCALL_LOG 0
#else
#define DEBUG_EE_SYSCALL_LOG 0
#define DEBUG_IOP_SYSCALL_LOG 0
#endif

/*
Option of whether to throw a runtime error on index out of bounds access for BitfieldRegisterXX_t. 
Turn off if you are sure that no errors will occur and want to debug quicker.
*/
#if defined(BUILD_DEBUG)
#define DEBUG_ERROR_BR_FIELD_INDEX_RANGE 0
#else
#define DEBUG_ERROR_BR_FIELD_INDEX_RANGE 0
#endif

//////////////////////
// Accuracy Options //
//////////////////////

/*
Option to consume all available ticks on a system run through if there is no work to be done.
It is up to the implementing system to decide on the criteria for this to happen.
The end user needs to be aware of the interaction of this with the bias given as a runtime option!
For single threaded mode, this should do no harm.
TODO: Not tested under multi threaded mode!
*/
#define ACCURACY_SKIP_TICKS_ON_NO_WORK 1