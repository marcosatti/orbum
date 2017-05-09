#pragma once

#include "Common/Global/Globals.h"

class SPU2Core_t;

/*
Contains static channel properties for the SPU2 Cores.
See SPU2 Overview manual.
*/
struct SPU2CoreTable
{
	struct SPU2CoreInfo_t
	{
		const char * mMnemonic; 
		u32 mBaseTSALeft;       // The base TSA start hword addresses come from the SPU2 Overview manual page 28. For the left audio channel in stereo mode (TODO: also used for mono?).
		u32 mBaseTSARight;      // The base TSA start hword addresses come from the SPU2 Overview manual page 28. For the right audio channel in stereo mode.
	};
	static constexpr SPU2CoreInfo_t SPU2_CORE_TABLE[Constants::SPU2::NUMBER_CORES] =
	{
		{ "Core 0", 0x2000, 0x2200 },
		{ "Core 1", 0x2400, 0x2600 },
	};

	/*
	Returns the channel properties given the index.
	*/
	static const SPU2CoreInfo_t * getInfo(const SPU2Core_t * channel);
};

