#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Tables/EEDmacChannelTable.h"

class EEDmacChannelRegister_CHCR_t;
class EEDmacChannelRegister_MADR_t;
class EEDmacChannelRegister_QWC_t;
class EEDmacChannelRegister_TADR_t;
class EEDmacChannelRegister_ASR_t;
class EEDmacChannelRegister_SADR_t;
class FIFOQueue32_t;
class ConstantByteMemory_t;
class PhysicalMMU_t;
class Register32_t;

/*
A base type representing an EE DMAC channel.
See EE Users Manual page 73 for the list of registers declared forming this type.

Subclassed by EE DMAC channels 0-9 (see EEDmacChannel_VIF0_t - EEDmacChannel_toSPR_t).
Not all of the registers are implemented in this base class for each channel.
*/
class EEDmacChannel_t
{
public:
	explicit EEDmacChannel_t(const int channelID, const std::shared_ptr<FIFOQueue32_t> & fifoQueue); // Default constructor for most channels.
	explicit EEDmacChannel_t(const int channelID); // Provided for the to/fromSPR channels where a FIFO queue is not used (set to nullptr).

	/*
	EE DMAC channel registers. See EE Users Manual page 73.
	CHCR, MADR and QWC are always defined for each channel.
	TADR, ASR0/1 and SADR are initalised by sub-classes when required.
	*/
	std::shared_ptr<EEDmacChannelRegister_CHCR_t> CHCR;
	std::shared_ptr<EEDmacChannelRegister_MADR_t> MADR;
	std::shared_ptr<EEDmacChannelRegister_QWC_t>  QWC;
	std::shared_ptr<EEDmacChannelRegister_TADR_t> TADR;
	std::shared_ptr<EEDmacChannelRegister_ASR_t>  ASR0;
	std::shared_ptr<EEDmacChannelRegister_ASR_t>  ASR1;
	std::shared_ptr<EEDmacChannelRegister_SADR_t> SADR;

	/*
	ASR array used for iterations/indexing (ASR0 and ASR1).
	*/
	std::shared_ptr<EEDmacChannelRegister_ASR_t> ASR[2];

	/*
	A reference to the associated FIFO queue, set at creation.
	*/
	std::shared_ptr<FIFOQueue32_t> mFIFOQueue;

	/*
	Returns the ID of this channel.
	*/
	int getChannelID() const;

	/*
	Returns the constant properties for this channel.
	*/
	const EEDmacChannelTable::EEDmacChannelInfo_t * getInfo();

private:
	/*
	The index of this channel.
	*/
	int mChannelID;

	/*
	Constant channel properties.
	*/
	const EEDmacChannelTable::EEDmacChannelInfo_t * mInfo;
};

/*
Represents EE DMAC channel 0 - the VIF0 channel.
The VIF0 channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined. 
The SADR register is left undefined.
*/
class EEDmacChannel_VIF0_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_VIF0_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 0;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_8060;
};

/*
Represents EE DMAC channel 1 - the VIF1 channel.
The VIF1 channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined.
The SADR register is left undefined.
*/
class EEDmacChannel_VIF1_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_VIF1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 1;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_9060;
};

/*
Represents EE DMAC channel 2 - the GIF channel.
The GIF channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined.
The SADR register is left undefined.
*/
class EEDmacChannel_GIF_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_GIF_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 2;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_A060;
};

/*
Represents EE DMAC channel 3 - the fromIPU channel.
The fromIPU channel inherits a base EE DMAC channel.
The TADR, ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_fromIPU_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_fromIPU_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 3;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_B030;
};

/*
Represents EE DMAC channel 4 - the toIPU channel.
The fromIPU channel inherits a base EE DMAC channel, additionally with TADR defined.
The ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_toIPU_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_toIPU_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue);

	static constexpr int CHANNEL_ID = 4;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_B440;
};

/*
Represents EE DMAC channel 5 - the SIF0 channel.
The SIF0 channel inherits a base EE DMAC channel.
The TADR, ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_SIF0_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_SIF0_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240);

	static constexpr int CHANNEL_ID = 5;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_C030;
};

/*
Represents EE DMAC channel 6 - the SIF1 channel.
The SIF1 channel inherits a base EE DMAC channel additionally with TADR defined.
The ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_SIF1_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_SIF1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240);

	static constexpr int CHANNEL_ID = 6;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_C440;
};

/*
Represents EE DMAC channel 7 - the SIF2 channel.
The SIF2 channel inherits a base EE DMAC channel.
The TADR, ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_SIF2_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_SIF2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240);

	static constexpr int CHANNEL_ID = 7;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_C830;
};

/*
Represents EE DMAC channel 8 - the fromSPR channel.
The SIF2 channel inherits a base EE DMAC channel additionally with SADR defined.
The TADR and ASR0/1 registers are left undefined.
There is no FIFO queue associated with this channel.
*/
class EEDmacChannel_fromSPR_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_fromSPR_t();

	static constexpr int CHANNEL_ID = 8;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_D030;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_D090;
};

/*
Represents EE DMAC channel 8 - the fromSPR channel.
The SIF2 channel inherits a base EE DMAC channel additionally with TADR and SADR defined.
The ASR0/1 registers are left undefined.
There is no FIFO queue associated with this channel.
*/
class EEDmacChannel_toSPR_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_toSPR_t();

	static constexpr int CHANNEL_ID = 9;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantByteMemory_t> MEMORY_D440;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_D490;
};