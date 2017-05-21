#pragma once

#include "Common/Types/EnumMap_t.h"

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
static constexpr EnumMap_t<System_t, const char *> DEBUG_SYSTEM_STRINGS = 
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
	"SPU2",
	"GSCore",
	"PCRTC"
};
#endif