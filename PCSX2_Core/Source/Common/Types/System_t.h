#pragma once

#include "Common/Global/Globals.h"

/*
Represents a list of systems included in the PS2.
*/
enum class System_t
{
	EECore,
	EEDmac,
	EETimers,
	EEIntc,
	GIF,
	IPU,
	VIF0,
	VU0,
	VIF1,
	VU1,
	IOPCore,
	IOPDmac,
	IOPTimers,
	IOPIntc,
	CDVD,
	SPU2,
	GSCore,
	CRTC,

	COUNT
};

#if defined(BUILD_DEBUG)
/*
Static array of names used for debug logging.
*/
static constexpr char * SYSTEM_STR[static_cast<int>(System_t::COUNT)] = 
{ 
	"EECore", 
	"EEDmac", 
	"EETimers", 
	"EEIntc", 
	"GIF", 
	"IPU", 
	"VIF0", 
	"VU0", 
	"VIF1",
	"VU1",
	"IOPCore", 
	"IOPDmac",
	"IOPTimers",
	"IOPIntc",
	"CDVD",
	"SPU2"
	"GSCore",
	"PCRTC"
};
static const char* getSystemStr(const System_t & system)
{
	return SYSTEM_STR[static_cast<int>(system)];
}
#endif