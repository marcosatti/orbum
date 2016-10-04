#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2Constants/PS2Constants.h"

class DMAC_t
{
public:
	explicit DMAC_t();

	/*
	A DMAC channel transfer count save array, needed to determine how many data units (qwords) have been transfered since start, which is used to
	 determine if the DMAC should stop transferring in slice mode (after 8 units).
	Not all of the array will be used (only for slice channels).
	*/
	u32 SliceCountState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];

	/*
	A chain mode exit status for each channel. When an exiting DMAtag instruction such as end is called, true is written to the appropriate index,
	 signaling that the DMAC should exit after the next packet transfer is completed.
	Not all of the array will be used (only for channels that support chain mode).
	*/
	bool ChainExitState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];
};

