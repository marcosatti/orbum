#pragma once

#include <string>
#include <map>

#include "Common/Global/Log.h"
#include "System.h"

struct VMOptions
{
	// Notes: Log function pointer must be thread-safe, locking is NOT done within PCSX2_Core.
	//        ST = single-threaded.
	//        MT = multi-threaded.
	//        us = microseconds.

	//////////////////////
	// General options. //
	//////////////////////

	/* Log function pointer.           */ void                    (*LOG_CALLBACK_FUNCPTR)(const LogLevel_t level, const std::string message);

	/* Boot ROM file path.             */ std::string             BOOT_ROM_PATH;
	/* ROM1 file path.                 */ std::string             ROM1_PATH;
	/* ROM2 file path.                 */ std::string             ROM2_PATH;
	/* EROM file path.                 */ std::string             EROM_PATH;

	//////////////////////
	// Runtime options. //
	//////////////////////

	/* Time slice per block run in us. */ double                   TIME_SLICE_PER_RUN;

	/* Use multithreaded systems.      */ bool                     USE_MULTI_THREADED_SYSTEMS;

	/* System speed biases.            */ std::map<System, double> SYSTEM_BIASES;

};
