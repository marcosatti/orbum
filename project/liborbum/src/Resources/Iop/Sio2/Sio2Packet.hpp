#pragma once

/*
Describes a DMA argument type within a SIO2 packet.
For both in and out arguments.
TODO: document properly after I have figured it out.
*/
// struct SIO2DmaArgument_t
// {
// 	uword    mAddress;
// 	size_t mSize;
// 	size_t mCount;
// };

/*
Describes a SIO2 packet.
See IopSio2.h and also the PS2SDK: https://github.com/ps2dev/ps2sdk/blob/master/iop/system/sio2log/include/sio2man.h.
TODO: document properly after I have figured it out.
*/
// struct SIO2Packet_t
// {
// 	uword mRecieveValue0;
// 	uword mSendValues0[4];
// 	uword mSendValues1[4];
// 	uword mRecieveValue1;
// 	uword mSendValues2[16];
// 	uword mRecieveValue2;
// 	size_t mSendSize;
// 	size_t mRecieveSize;
// 	uword mSendAddress;
// 	uword mRecieveAddress;

// 	SIO2DmaArgument_t mInDmaArgument;
// 	SIO2DmaArgument_t mOutDmaArgument;
// };