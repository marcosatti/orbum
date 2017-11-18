#pragma once

#include "Common/Global/Macros.h"

////////////////////////////////////////////
// Debug Options                          //
// (Only enabled if using a debug build.) //
////////////////////////////////////////////

/*
Define if the emulator should log host *Memory_t allocations or not. 
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_MEMORY_ALLOCATIONS 0
#else
 #define DEBUG_LOG_MEMORY_ALLOCATIONS 0
#endif

/*
When outputting values, choose if to log values read/written as hex instead of decimal.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_VALUE_AS_HEX 1
#else
 #define DEBUG_LOG_VALUE_AS_HEX 0
#endif

/*
Define if the emulator should log a combination of Memory_t, Register_t and SpscFifoQueue read and writes (global enable). 
Parameters still need to be set upon constructing the object.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_MEMORY_READ_WRITE 1
 #define DEBUG_LOG_REGISTER_READ_WRITE 1
 #define DEBUG_LOG_FIFOQUEUE_READ_WRITE 1
#else
 #define DEBUG_LOG_MEMORY_READ_WRITE 0
 #define DEBUG_LOG_REGISTER_READ_WRITE 0
 #define DEBUG_LOG_FIFOQUEUE_READ_WRITE 0
#endif

/*
Define if the emulator should log EE and IOP DMAC transfer and/or tag activity (source/chain/list modes).
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_EE_DMAC_XFERS 0
 #define DEBUG_LOG_IOP_DMAC_XFERS 0
 #define DEBUG_LOG_EE_DMAC_TAGS 0
 #define DEBUG_LOG_IOP_DMAC_TAGS 0
#else
 #define DEBUG_LOG_EE_DMA_TAGS 0
 #define DEBUG_LOG_IOP_DMA_TAGS 0
#endif

/*
Define if the emulator should log EE SIO messages (serial I/O port). 
See Resources/Ee/EeRegister_Sio for where the SIO is implemented.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_SIO_MESSAGES 1
#else
 #define DEBUG_LOG_SIO_MESSAGES 0
#endif

/*
Debug log options for the EECore and IOPCore, including:
 - Syscall logging (see SYSCALL() instructions).
 - Interrupt logging.
*/
#if defined(BUILD_DEBUG)
 #define DEBUG_LOG_EE_SYSCALLS 0
 #define DEBUG_LOG_IOP_SYSCALLS 0
 #define DEBUG_LOG_EE_INTERRUPTS 1
 #define DEBUG_LOG_IOP_INTERRUPTS 1
#else
 #define DEBUG_LOG_EE_SYSCALLS 0
 #define DEBUG_LOG_IOP_SYSCALLS 0
 #define DEBUG_LOG_EE_INTERRUPTS 0
 #define DEBUG_LOG_IOP_INTERRUPTS 0
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