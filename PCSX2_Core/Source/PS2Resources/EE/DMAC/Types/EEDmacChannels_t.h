#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"
#include <Common/Types/Memory/ConstantMemory_t.h>

/*
EEDmacChannels_t defines all of the channels available in the EE DMAC.
These include (see EE Users Manual page 73):
 - VIF0
 - VIF1
 - GIF
 - fromIPU
 - toIPU
 - SIF0
 - SIF1
 - SIF2
 - fromSPR
 - toSPR

They are subclassed from the base channel class - EEDmacChannel_t.
*/

/*
A base type representing an EE DMAC channel.
See EE Users Manual page 73 for the list of registers declared forming this type.

Subclassed by EE DMAC channels 0-9 (see EEDmacChannel_VIF0_t - EEDmacChannel_toSPR_t).
Not all of the registers are implemented in this base class for each channel.
*/

using ChannelProperties_t = EEDmacChannelTable::ChannelProperties_t;

class EEDmacChannelRegister_CHCR_t;
class EEDmacChannelRegister_MADR_t;
class EEDmacChannelRegister_QWC_t;
class EEDmacChannelRegister_TADR_t;
class EEDmacChannelRegister_ASR_t;
class EEDmacChannelRegister_SADR_t;

class EEDmacChannel_t
{
public:
	explicit EEDmacChannel_t(const u32 & channelID);

	/*
	The ID of this channel. Used to look up properties in the EEDmacChannelTable, which lists the physical mode, direction etc listed on EE Users Manual page 42.
	*/
	const u32 mChannelID;
	const ChannelProperties_t * getChannelProperties() const;

	/*
	EE DMAC channel registers.
	See EE Users Manual page 73.

	CHCR, MADR and QWC is always defined for each channel - they are initalised in this base class.
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
	A DMAC channel transfer count save array, needed to determine how many data units (qwords) have been transfered since start, which is used to
	determine if the DMAC should stop transferring in slice mode (after 8 qwords).
	Only used for slice channels.

	Reset to 0 whenever CHCR.STR bit is set to 1 (ie: when starting/restarting a transfer).
	The CHCR register is supplied a reference to this count variable, and has writeWordU() overriden.
	*/
	u32 mSliceCountState;

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
	u8 mChainStackLevelState;

	/*
	Interleaved transfer state variables. Used to determine when to transfer data and when to skip data.
	Only used for interleave channels.
	*/
	bool mInterleavedSkipState;
	u8 mInterleavedCountState;

};

/*
Represents EE DMAC channel 0 - the VIF0 channel.
The VIF0 channel inherits a base EE DMAC channel, additionally with TADR and ASR0/1 registers defined. 
The SADR register is left undefined.
*/
class EEDmacChannel_VIF0_t : public EEDmacChannel_t
{
public:
	explicit EEDmacChannel_VIF0_t();

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
	explicit EEDmacChannel_VIF1_t();

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
	explicit EEDmacChannel_GIF_t();

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
	explicit EEDmacChannel_fromIPU_t();

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
	explicit EEDmacChannel_toIPU_t();

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
	explicit EEDmacChannel_SIF0_t();

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
	explicit EEDmacChannel_SIF1_t();

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
	explicit EEDmacChannel_SIF2_t();

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