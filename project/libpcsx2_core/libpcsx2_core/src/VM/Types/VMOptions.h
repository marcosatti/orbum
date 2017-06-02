#pragma once

#include <string>
#include <map>

#include "Common/Global/Globals.h"
#include "Common/Types/System/Context_t.h"

struct VMOptions
{
	// Notes: If any system is not explicitly defined in the bias map, it is set to 1.0 internally.
	//        ST = single-threaded.
    //        MT_SEQ = multi-threaded sequential (only useful for debugging).
    //        MT_SIM = multi-threaded simultaneous (what most people expect & should use for performance).
    //        us = microseconds.

	//////////////////////
	// General options. //
	//////////////////////

	/* Log function pointer.           */ void                        (*LOG_CALLBACK_FUNCPTR)(const LogLevel_t level, const std::string & message);

	/* Boot ROM file path.             */ std::string                 BOOT_ROM_PATH;
	/* ROM1 file path.                 */ std::string                 ROM1_PATH;
	/* ROM2 file path.                 */ std::string                 ROM2_PATH;
	/* EROM file path.                 */ std::string                 EROM_PATH;

	//////////////////////
	// Runtime options. //
	//////////////////////

	/* Time slice per block run in us. */ double                      TIME_SLICE_PER_RUN;

    /* VM runtime execution mode.      */ enum { ST, MT_SEQ, MT_SIM } VM_RUNTIME_EXEC_MODE;

	/* System speed biases.            */ std::map<Context_t, double> SYSTEM_BIASES;

};
