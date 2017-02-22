#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

class Register32_t;
class FIFOQueue_t;
class IOPDmacChannelRegister_BCR_t;
class IOPDmacChannelRegister_CHCR_t;
class IOPDmacChannelRegister_MADR_t;
class IOPDmacChannelRegister_TADR_t;

/*
A base type representing an IOP DMAC Channel.
*/
class IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_t(const u32 & channelID, const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	/*
	The ID of this channel. Used to look up properties in the IOPDmacChannelTable, which the static properties.
	*/
	const u32 mChannelID;
	const IOPDmacChannelTable::ChannelProperties_t * getChannelProperties() const;

	/*
	IOP DMAC Channel Registers.
	*/
	std::shared_ptr<IOPDmacChannelRegister_MADR_t> MADR;
	std::shared_ptr<IOPDmacChannelRegister_BCR_t>  BCR;
	std::shared_ptr<IOPDmacChannelRegister_CHCR_t> CHCR;
	std::shared_ptr<IOPDmacChannelRegister_TADR_t> TADR;

	/*
	A reference to the associated FIFO queue, set at creation.
	*/
	std::shared_ptr<FIFOQueue_t> mFIFOQueue;

	/////////////////////////////
	// Common Helper Functions //
	/////////////////////////////

	/*
	Returns the channel runtime logical mode its operating in.
	*/
	IOPDmacChannelTable::LogicalMode_t getRuntimeLogicalMode() const;

};

/*
Represents IOP DMAC channel 0 - the fromMDEC channel.
The fromMDEC channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_fromMDEC_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_fromMDEC_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 0;
};

/*
Represents IOP DMAC channel 1 - the toMDEC channel.
The toMDEC channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_toMDEC_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_toMDEC_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 1;
};

/*
Represents IOP DMAC channel 2 - the GPU channel.
The GPU channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_GPU_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_GPU_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 2;
};

/*
Represents IOP DMAC channel 3 - the CDROM channel.
The CDROM channel inherits a base IOP DMAC channel.
TODO: is this the same as CDVD?
*/
class IOPDmacChannel_CDROM_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_CDROM_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 3;
};

/*
Represents IOP DMAC channel 4 - the SPU2c1 channel.
The SPU2c1 channel inherits a base IOP DMAC channel.
Also contains a TADR register.
*/
class IOPDmacChannel_SPU2c1_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SPU2c1_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 4;
};

/*
Represents IOP DMAC channel 5 - PIO (parallel I/O?) channel.
This channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_PIO_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_PIO_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 5;
};

/*
Represents IOP DMAC channel 6 - the OTClear channel.
The OTClear channel inherits a base IOP DMAC channel.
TODO: what is this???
*/
class IOPDmacChannel_OTClear_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_OTClear_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 6;
};

/*
Represents IOP DMAC channel 7 - the SPU2c2 channel.
The SPU2c2 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_SPU2c2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SPU2c2_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 7;
};

/*
Represents IOP DMAC channel 8 - the DEV9 channel.
The DEV9 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_DEV9_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_DEV9_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 8;
};

/*
Represents IOP DMAC channel 9 - the SIF0 channel.
The SIF0 channel inherits a base IOP DMAC channel.
Also contains a TADR register.
*/
class IOPDmacChannel_SIF0_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SIF0_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 9;
};

/*
Represents IOP DMAC channel 10 - the SIF1 channel.
The SIF1 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_SIF1_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SIF1_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 10;
};

/*
Represents IOP DMAC channel 11 - the fromSIO2 channel.
The fromSIO2 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_fromSIO2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_fromSIO2_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 11;
};

/*
Represents IOP DMAC channel 12 - the toSIO2 channel.
The toSIO2 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_toSIO2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_toSIO2_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr u32 CHANNEL_ID = 12;
};