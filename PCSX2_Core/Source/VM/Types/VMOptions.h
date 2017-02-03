#pragma once

#include <string>

#include "Common/Global/Log.h"

struct VMOptions
{
	// Notes: Log function pointer must be thread-safe, locking is NOT done within PCSX2_Core.
	//        ST = single-threaded.
	//        MT = multi-threaded.
	//        us = microseconds.

	//////////////////////
	// General options. //
	//////////////////////

	/* Log function pointer.            */ void        (*LOG_CALLBACK_FUNCPTR)(const LogLevel_t level, const std::string message);

	/* Boot ROM file path.              */ std::string BOOT_ROM_PATH;
	/* ROM1 file path.                  */ std::string ROM1_PATH;
	/* ROM2 file path.                  */ std::string ROM2_PATH;
	/* EROM file path.                  */ std::string EROM_PATH;

	//////////////////////
	// Runtime options. //
	//////////////////////

	/* Time slice per block in us (ST). */ double      TIME_SLICE_ST;
	/* Time slice per block in us (MT). */ double      TIME_SLICE_MT;

	/* Use multithreaded systems.       */ bool        USE_MULTI_THREADED_SYSTEMS;

	/* EECore speed bias.               */ double      EE_CORE_BIAS;
	/* EEDmac speed bias.               */ double      EE_DMAC_BIAS;
	/* EETimers speed bias.             */ double      EE_TIMERS_BIAS;
	/* EEIntc speed bias.               */ double      EE_INTC_BIAS;
	/* VIF0 speed bias.                 */ double      VIF0_BIAS;
	/* VU0 speed bias.                  */ double      VU0_BIAS;
	/* VIF1 speed bias.                 */ double      VIF1_BIAS;
	/* VU1 speed bias.                  */ double      VU1_BIAS;
	/* IOPCore speed bias.              */ double      IOP_CORE_BIAS;
	/* IOPDmac speed bias.              */ double      IOP_DMAC_BIAS;
	/* IOPTimers speed bias.            */ double      IOP_TIMERS_BIAS;
	/* IOPIntc speed bias.              */ double      IOP_INTC_BIAS;
};
