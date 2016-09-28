#pragma once

#include "Common/Global/Globals.h"

/*
Simple type to hold 4 x 32 bits, which is the size of 1 DMA transfer on each cycle.
See EE Users manual page 41.
*/
struct DMAPacket_t
{
	u32 data[4];
};

