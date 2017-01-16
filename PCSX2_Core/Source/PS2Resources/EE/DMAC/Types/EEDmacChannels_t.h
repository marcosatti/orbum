#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"

using ChannelProperties_t = EEDmacChannelTable::ChannelProperties_t;
using Direction_t = EEDmacChannelTable::Direction_t;
using LogicalMode_t = EEDmacChannelTable::LogicalMode_t;

class EEDmacChannelRegister_CHCR_t;
class EEDmacChannelRegister_MADR_t;
class EEDmacChannelRegister_QWC_t;
class EEDmacChannelRegister_TADR_t;
class EEDmacChannelRegister_ASR_t;
class EEDmacChannelRegister_SADR_t;
class FIFOQueue_t;
class ConstantMemory_t;

/*
A base type representing an EE DMAC channel.
See EE Users Manual page 73 for the list of registers declared forming this type.

Subclassed by EE DMAC channels 0-9 (see EEDmacChannel_VIF0_t - EEDmacChannel_toSPR_t).
Not all of the registers are implemented in this base class for each channel.
*/
class EEDmacChannel_t
{
public:
	explicit EEDmacChannel_t(const u32 & channelID, std::shared_ptr<FIFOQueue_t> & fifoQueue); // Default constructor for most channels.
	explicit EEDmacChannel_t(const u32 & channelID); // Sets mFIFOQueue to nullptr. Provided for the to/fromSPR channels where a FIFO queue is not used.
	
	/*
	The ID of this channel. Used to look up properties in the EEDmacChannelTable, which lists the physical mode, direction, etc listed on EE Users Manual page 42.
	*/
	const u32 mChannelID;
	const ChannelProperties_t * getChannelProperties() const;

	/*
	EE DMAC channel registers.
	See EE Users Manual page 73.

	CHCR, MADR and QWC is always defined for each channel - they are initalised in this base class.
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
	std::shared_ptr<FIFOQueue_t> mFIFOQueue;

	/////////////////////////////
	// Common Helper Functions //
	/////////////////////////////

	/*
	Returns the channel runtime logical mode its operating in.
	*/
	LogicalMode_t getRuntimeLogicalMode() const;

	/*
	Gets the runtime direction. Useful for channels where it can be either way.
	*/
	Direction_t getRuntimeDirection() const;

	/*
	Additional processing on channel transfer begin if needed (ie: SIF channels).
	*/
	virtual void preTransfer();

	/*
	Additional processing on channel transfer exit if needed (ie: SIF channels).
	*/
	virtual void postTransfer();

	/////////////////////////////////
	// Chain Mode Helper Functions //
	/////////////////////////////////

	/*
	Resets the channel chain mode context variables, needed for next time the channel is activated.
	*/
	void resetChainExitState();

	/*
	Sets the channel chain mode exit state to true, indicating the channel should quit transfering after the current tag.
	*/
	void setChainExitStateTrue();

	/*
	Returns if we are in a tag instruction that requires drain stall control to be used ("refs" tag).
	*/
	bool isChainInDrainStallControlTag() const;

	/*
	Returns if we are in a tag instruction that requires source stall control to be used ("cnts" tag).
	*/
	bool isChainInSourceStallControlTag() const;

	/*
	Returns if there is a pending tag interrupt requested.
	*/
	bool isChainInInterruptTag() const;

	/*
	Returns if there is a pending tag exit requested.
	*/
	bool isChainInExitTag() const;

	/*
	Returns if the stack has overflowed (over 2 levels), used when pushing a stack level.
	*/
	bool isChainStackOverflowed() const;

	/*
	Returns if the stack has underflowed (under 1 levels), used when poping a stack level.
	*/
	bool isChainStackUnderflowed() const;

	/*
	Pushes a chain level onto the stack, by setting the ASR register to the TADR register values and incrementing the stack level.
	*/
	void pushChainStack();

	/*
	Pops a chain level from the stack, by setting the TADR register to the ASR register values and decrementing the stack level.
	*/
	void popChainStack();

	//////////////////////////////////////
	// Interleave Mode Helper Functions //
	//////////////////////////////////////

	/*
	Gets the interleaved block count.
	*/
	u32 getInterleavedCount() const;

	/*
	Returns if the transfer should be skipped for the current cycle.
	*/
	bool isInterleaveInSkipMode() const;

	/*
	Toggles the interleave mode (skip/transfer).
	*/
	void toggleInterleaveMode();

	/*
	Increments the interleave mode count.
	*/
	void incrementInterleaveCount();

private:

	/*
	A chain mode exit status for each channel. When an exiting DMAtag instruction such as end is called, true is written to the appropriate index,
	signaling that the DMAC should exit after the next packet transfer is completed.
	Only used for chain mode channels.
	*/
	bool mChainExitState;

	/*
	A stack level count, for chain mode (CALL / RET instructions). Used to check if the DMA transfer should end.
	Only used for chain mode channels.
	*/
	u32 mChainStackLevelState;

	/*
	Interleaved transfer state variables. Used to determine when to transfer data and when to skip data.
	Only used for interleave channels.
	*/
	bool mInterleavedInSkipBlock;
	u32 mInterleavedBlockCount;

};

/*
Represents EE DMAC channel 0 - the VIF0 channel.
The VIF0 channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined. 
The SADR register is left undefined.
*/
class EEDmacChannel_VIF0_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_VIF0_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 0;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_8060;
};

/*
Represents EE DMAC channel 1 - the VIF1 channel.
The VIF1 channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined.
The SADR register is left undefined.
*/
class EEDmacChannel_VIF1_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_VIF1_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 1;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_9060;
};

/*
Represents EE DMAC channel 2 - the GIF channel.
The GIF channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined.
The SADR register is left undefined.
*/
class EEDmacChannel_GIF_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_GIF_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 2;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_A060;
};

/*
Represents EE DMAC channel 3 - the fromIPU channel.
The fromIPU channel inherits a base EE DMAC channel.
The TADR, ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_fromIPU_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_fromIPU_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 3;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_B030;
};

/*
Represents EE DMAC channel 4 - the toIPU channel.
The fromIPU channel inherits a base EE DMAC channel, additionally with TADR defined.
The ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_toIPU_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_toIPU_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 4;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_B440;
};

/*
Represents EE DMAC channel 5 - the SIF0 channel.
The SIF0 channel inherits a base EE DMAC channel.
The TADR, ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_SIF0_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_SIF0_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 5;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_C030;
};

/*
Represents EE DMAC channel 6 - the SIF1 channel.
The SIF1 channel inherits a base EE DMAC channel additionally with TADR defined.
The ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_SIF1_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_SIF1_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 6;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_C440;
};

/*
Represents EE DMAC channel 7 - the SIF2 channel.
The SIF2 channel inherits a base EE DMAC channel.
The TADR, ASR0/1 and SADR registers are left undefined.
*/
class EEDmacChannel_SIF2_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_SIF2_t(std::shared_ptr<FIFOQueue_t>& fifoQueue);

	static constexpr u32 CHANNEL_ID = 7;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_C830;
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

	static constexpr u32 CHANNEL_ID = 8;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_D030;
	std::shared_ptr<ConstantMemory_t> MEMORY_D090;
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

	static constexpr u32 CHANNEL_ID = 9;

	/*
	Mapped memory that is present at the end of this channel.
	See page 23 onwards of the EE Users Manual.
	This needs to be initalised into the EE memory map.
	*/
	std::shared_ptr<ConstantMemory_t> MEMORY_D440;
	std::shared_ptr<ConstantMemory_t> MEMORY_D490;
};