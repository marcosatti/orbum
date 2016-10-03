#pragma once

#include "Common/Global/Globals.h"

/*
Simple type to hold 128 bits, which is the size of 1 DMA data transfer on each cycle.
See EE Users manual page 41.
*/
struct DMADataUnit_t
{
	const u64 mDataUnit[Constants::NUMBER_DWORDS_IN_QWORD];

	DMADataUnit_t(u64 lower, u64 upper);
};
