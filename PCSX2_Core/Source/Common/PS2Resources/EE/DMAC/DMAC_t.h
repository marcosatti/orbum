#pragma once

#include "Common/Global/Globals.h"
#include <Common/PS2Constants/PS2Constants.h>

class DMAC_t
{
public:
	explicit DMAC_t();

	/*
	A DMAC channel transfer count save array, needed to determine how many packets (qwords) have been transfered since start, which can be used to:
	 - Determine if the DMAC should stop transferring in slice mode (after 8 packets).
	 - Use the correct memory address (need to increment addresses by size of a qword each cycle).
	*/
	u32 PacketCountState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];
};

