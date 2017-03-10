#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

class Register32_t;
class FIFOQueue32_t;
class IOPDmacChannelRegister_BCR_t;
class IOPDmacChannelRegister_CHCR_t;
class IOPDmacChannelRegister_MADR_t;
class IOPDmacChannelRegister_TADR_t;
class IOPDmacRegister_PCR0_t;
class IOPDmacRegister_ICR0_t;
class IOPDmacRegister_PCR1_t;
class IOPDmacRegister_ICR1_t;

/*
A base type representing an IOP DMAC Channel.
*/
class IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_t(const int channelID, const std::shared_ptr<FIFOQueue32_t> & fifoQueue);
	virtual ~IOPDmacChannel_t() = default;

	/*
	IOP DMAC Channel Registers.
	*/
	std::shared_ptr<IOPDmacChannelRegister_MADR_t> MADR;
	std::shared_ptr<IOPDmacChannelRegister_BCR_t>  BCR;
	std::shared_ptr<IOPDmacChannelRegister_CHCR_t> CHCR;
	std::shared_ptr<IOPDmacChannelRegister_TADR_t> TADR;

	/*
	A reference to the associated FIFO queue, from which data (words) can be read/written to.
	*/
	std::shared_ptr<FIFOQueue32_t> mFIFOQueue;

	/*
	Returns the ID of this channel.
	*/
	int getChannelID() const;

	/*
	Returns the constant channel properties.
	*/
	const IOPDmacChannelTable::ChannelProperties_t * getChannelProperties() const;

private:
	/*
	The index of this channel.
	*/
	const int mChannelID;
};

/*
Represents IOP DMAC channel 0 - the fromMDEC channel.
The fromMDEC channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_fromMDEC_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_fromMDEC_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 0;
};

/*
Represents IOP DMAC channel 1 - the toMDEC channel.
The toMDEC channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_toMDEC_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_toMDEC_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 1;
};

/*
Represents IOP DMAC channel 2 - the SIF2/GPU channel.
It is called SIF2 under a PS2 context, where as it is used as the GPU channel in a psx context.
The SIF2/GPU channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_SIF2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SIF2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240);

	static constexpr int CHANNEL_ID = 2;
};

/*
Represents IOP DMAC channel 3 - the CDROM channel.
The CDROM channel inherits a base IOP DMAC channel.
TODO: is this the same as CDVD?
*/
class IOPDmacChannel_CDROM_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_CDROM_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 3;
};

/*
Represents IOP DMAC channel 4 - the SPU2c1 channel.
The SPU2c1 channel inherits a base IOP DMAC channel.
Also contains a TADR register.
*/
class IOPDmacChannel_SPU2c1_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SPU2c1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 4;
};

/*
Represents IOP DMAC channel 5 - PIO (parallel I/O?) channel.
This channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_PIO_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_PIO_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 5;
};

/*
Represents IOP DMAC channel 6 - the OTClear channel.
The OTClear channel inherits a base IOP DMAC channel.
TODO: what is this???
*/
class IOPDmacChannel_OTClear_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_OTClear_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 6;
};

/*
Represents IOP DMAC channel 7 - the SPU2c2 channel.
The SPU2c2 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_SPU2c2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SPU2c2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 7;
};

/*
Represents IOP DMAC channel 8 - the DEV9 channel.
The DEV9 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_DEV9_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_DEV9_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 8;
};

/*
Represents IOP DMAC channel 9 - the SIF0 channel.
The SIF0 channel inherits a base IOP DMAC channel.
Also contains a TADR register.
*/
class IOPDmacChannel_SIF0_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SIF0_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240);

	static constexpr int CHANNEL_ID = 9;
};

/*
Represents IOP DMAC channel 10 - the SIF1 channel.
The SIF1 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_SIF1_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_SIF1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240);

	static constexpr int CHANNEL_ID = 10;
};

/*
Represents IOP DMAC channel 11 - the fromSIO2 channel.
The fromSIO2 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_fromSIO2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_fromSIO2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 11;
};

/*
Represents IOP DMAC channel 12 - the toSIO2 channel.
The toSIO2 channel inherits a base IOP DMAC channel.
*/
class IOPDmacChannel_toSIO2_t : public IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_toSIO2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 12;
};