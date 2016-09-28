#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAPacket_t.h"
#include "Common/PS2Constants/PS2Constants.h"

/*
The InterpreterDMAC class controls the execution of the DMAC and transfers through DMA.

It is called InterpreterDMAC as it is actually a micro controller (duh) with its own language (DMAtag)!
Therefore we are still required to interpret these instructions.

The DMAC is synced to the BUSCLK clock source, and at most transfers a qword (a 4 x 32-bit "packet") every tick (128 bits) on slice and burst channels 
 (since the bus is 128-bit long).
In a slice physical transfer mode, 8 qwords are transfered before the DMAC releases the bus to the CPU - it waits for a 'DMA request' command before continuing.
In a burst physical transfer mode, n qwords are transfered all at once - the CPU must wait for the DMAC to release the bus.

See EE Users Manual page 41 onwards.

Some notes:
 - From what I gather, when the manual talks about a peripheral processors, ie: "transfering data to or from", there is a FIFO queue 128 bytes long
    which stores the DMA channel data? Since you can't specify the dest/src address, except for when accessing SPR or main mem...
 - EERegisterDMACDChcr_t sets PS2Resources->EE->DMAC->PacketCountState[channelID] to 0 everytime CHCR.STR has 1 written to it (at the start of a new transfer).

TODO: Speedups can be done here:
 - Dont need to transfer 1-qword at a time.
 - Dont need to turn on cycle stealing if requested? Kind of redundant in an emulator.
*/

class InterpreterDMAC : VMExecutionCoreComponent
{
public:
	explicit InterpreterDMAC(VMMain * vmMain);
	~InterpreterDMAC();

	/*
	Check through the channels and initate data transfers. 
	Slice channels transfer 8 qwords (128 bytes) each step, where as burst channels transfer all data in one step.
	TODO: Currently it is assumed that the software uses the DMAC correctly (such as using correct chain mode for a channel). Need to add in checks?
	*/
	void executionStep() override;

private:
	/*
	Define the DMA channel properties, as listed on EE Users Manual page 42.
	*/
	enum class ChannelID_t
	{
		VIF0    = 0,
		VIF1    = 1,
		GIF     = 2,
		fromIPU = 3,
		toIPU   = 4,
		SIF0    = 5,
		SIF1    = 6,
		SIF2    = 7,
		fromSPR = 8, // From scratchpad ram.
		toSPR   = 9  // To scratchpad ram.
	};
	enum class Direction_t
	{
		// Do not change order! Sync'd to Dn_CHCR.DIR order (needed in order to static_cast<Direction_t>), 
		//  except for BOTH in which case the direction is determined at runtime.
		FROM = 0,
		TO   = 1,
		BOTH = 2
	};
	enum class PhysicalMode_t
	{
		SLICE = 0,
		BURST = 1
	};
	struct ChannelProperties_t
	{
		ChannelID_t    ChannelID;
		Direction_t    Direction;
		PhysicalMode_t PhysicalMode;
	};
	static constexpr ChannelProperties_t ChannelProperties[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS]
	{
		{ ChannelID_t::VIF0,    Direction_t::TO,   PhysicalMode_t::SLICE },
		{ ChannelID_t::VIF1,    Direction_t::BOTH, PhysicalMode_t::SLICE },
		{ ChannelID_t::GIF,     Direction_t::TO,   PhysicalMode_t::SLICE },
		{ ChannelID_t::fromIPU, Direction_t::FROM, PhysicalMode_t::SLICE },
		{ ChannelID_t::toIPU,   Direction_t::TO,   PhysicalMode_t::SLICE },
		{ ChannelID_t::SIF0,    Direction_t::FROM, PhysicalMode_t::SLICE },
		{ ChannelID_t::SIF1,    Direction_t::TO,   PhysicalMode_t::SLICE },
		{ ChannelID_t::SIF2,    Direction_t::BOTH, PhysicalMode_t::SLICE },
		{ ChannelID_t::fromSPR, Direction_t::FROM, PhysicalMode_t::BURST },
		{ ChannelID_t::toSPR,   Direction_t::TO,   PhysicalMode_t::BURST }
	};

	/*
	Do a Normal logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Normal(u32 channelID);

	/*
	Do a Normal logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Chain(u32 channelID);

	/*
	Do a Normal logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Interleaved(u32 channelID);

	/*
	Transfer a packet using the DMA channel register settings. This is common to both Slice and Burst channels (done on every BUSCLK tick).
	Updates the PS2Resources->EE->DMAC->PacketCountState[channelID] by 1 whenever called.
	*/
	void transferPacket(u32 channelID);

	/*
	Read and write a qword from the specified peripheral FIFO queue, or from physical memory (either main memory or SPR (scratchpad ram)).
	*/
	DMAPacket_t readQwordChannel(ChannelID_t channel);
	void writeQwordChannel(ChannelID_t channel, DMAPacket_t packet);
	DMAPacket_t readQwordMemory(u32 PhysicalAddressOffset, bool SPRAccess);
	void writeQwordMemory(u32 PhysicalAddressOffset, bool SPRAccess, DMAPacket_t packet);

};

