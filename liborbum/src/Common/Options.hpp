#pragma once

////////////////////////////////////////////
// Debug Options                          //
// (Only enabled if using a debug build.) //
////////////////////////////////////////////

/// Define if the emulator should log EE and IOP DMAC transfer and/or tag activity (source/chain/list modes).
#if defined(BUILD_DEBUG)
#define DEBUG_LOG_EE_DMAC_XFERS 0
#define DEBUG_LOG_IOP_DMAC_XFERS 0
#define DEBUG_LOG_EE_DMAC_TAGS 0
#define DEBUG_LOG_IOP_DMAC_TAGS 0
#else
#define DEBUG_LOG_EE_DMAC_XFERS 0
#define DEBUG_LOG_IOP_DMAC_XFERS 0
#define DEBUG_LOG_EE_DMA_TAGS 0
#define DEBUG_LOG_IOP_DMA_TAGS 0
#endif

/// Define if the emulator should log EE SIO messages (serial I/O port).
/// See Resources/Ee/EeRegister_Sio for where the SIO is implemented.
#if defined(BUILD_DEBUG)
#define DEBUG_LOG_SIO_MESSAGES 1
#else
#define DEBUG_LOG_SIO_MESSAGES 0
#endif

/// Debug log options for the EECore and IOPCore, including:
/// - Syscall logging (see SYSCALL() instructions).
/// - Interrupt logging.
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
