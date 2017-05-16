#pragma once

#include "Common/Global/Globals.h"

/*
Describes a DMA argument type within a SIO2 packet.
For both in and out arguments.
TODO: document properly after I have figured it out.
*/
struct SIO2DmaArgument_t
{
	u32    mAddress;
	size_t mSize;
	size_t mCount;
};

/*
Describes a SIO2 packet.
See IopSio2.h and also the PS2SDK: https://github.com/ps2dev/ps2sdk/blob/master/iop/system/sio2log/include/sio2man.h.
TODO: document properly after I have figured it out.
*/
struct SIO2Packet_t
{
	u32 mRecieveValue0;
	u32 mSendValues0[4];
	u32 mSendValues1[4];
	u32 mRecieveValue1;
	u32 mSendValues2[16];
	u32 mRecieveValue2;
	size_t mSendSize;
	size_t mRecieveSize;
	u32 mSendAddress;
	u32 mRecieveAddress;

	SIO2DmaArgument_t mInDmaArgument;
	SIO2DmaArgument_t mOutDmaArgument;
};