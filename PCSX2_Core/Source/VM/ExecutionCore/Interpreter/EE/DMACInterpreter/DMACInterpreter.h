#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMADataUnit_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"
#include "Common/PS2Constants/PS2Constants.h"

/*
The InterpreterDMAC class controls the execution of the DMAC and transfers through DMA.

It is called InterpreterDMAC as it is actually a micro controller (duh) with its own language (DMAtag)!
Therefore we are still required to interpret these instructions.

The DMAC is synced to the BUSCLK clock source, and at most transfers a qword (a 4 x 32-bit data unit) every tick (128 bits) on slice and burst channels 
 (since the bus is 128-bit long).
In a slice physical transfer mode, 8 qwords are transfered before the DMAC releases the bus to the CPU - it waits for a 'DMA request' command before continuing.
In a burst physical transfer mode, n qwords are transfered all at once - the CPU must wait for the DMAC to release the bus.

See EE Users Manual page 41 onwards.

Some notes:
 - From what I gather, when the manual talks about a peripheral processors, ie: "transfering data to or from", there is a FIFO queue 128 bytes long
    which stores the DMA channel data? Since you can't specify the dest/src address, except for when accessing SPR or main mem...
 - EERegisterDMACDChcr_t sets PS2Resources->EE->DMAC->SliceCountState[Channel ID] to 0 everytime CHCR.STR has 1 written to it (at the start of a new/resumed transfer).

TODO: Speedups can be done here:
 - Dont need to transfer 1-qword at a time.
 - Dont need to turn on cycle stealing if requested? Kind of redundant in an emulator.
*/

class DMACInterpreter : VMExecutionCoreComponent
{
public:
	explicit DMACInterpreter(VMMain * vmMain);
	~DMACInterpreter();

	/*
	Check through the channels and initate data transfers. 
	Slice channels transfer 8 qwords (128 bytes) before suspending transfer, where as burst channels transfer all data without suspending.
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
	enum class ChainMode_t
	{
		SOURCE = 0,
		DEST   = 1, // Destination.
		NONE   = 2
	};
	struct ChannelProperties_t
	{
		ChannelID_t    ChannelID;
		Direction_t    Direction;
		PhysicalMode_t PhysicalMode;
		ChainMode_t    ChainMode;
	};
	static constexpr ChannelProperties_t ChannelProperties[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS]
	{
		{ ChannelID_t::VIF0,    Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ ChannelID_t::VIF1,    Direction_t::BOTH, PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ ChannelID_t::GIF,     Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ ChannelID_t::fromIPU, Direction_t::FROM, PhysicalMode_t::SLICE, ChainMode_t::NONE   },
		{ ChannelID_t::toIPU,   Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ ChannelID_t::SIF0,    Direction_t::FROM, PhysicalMode_t::SLICE, ChainMode_t::DEST   },
		{ ChannelID_t::SIF1,    Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ ChannelID_t::SIF2,    Direction_t::BOTH, PhysicalMode_t::SLICE, ChainMode_t::NONE   },
		{ ChannelID_t::fromSPR, Direction_t::FROM, PhysicalMode_t::BURST, ChainMode_t::DEST   },
		{ ChannelID_t::toSPR,   Direction_t::TO,   PhysicalMode_t::BURST, ChainMode_t::SOURCE }
	};



	/*
	Context variables. Used by most of the functions below.
	*/
	u32 mChannelID;
	DMAtag_t mDMAtag;



	// Logical mode functions.

	/*
	Do a normal logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Normal() const;

	/*
	Do a chain logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Chain();

	/*
	Do a interleaved logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Interleaved();



	// Common functions (for Normal, Chain, Interleaved modes).

	/*
	Checks the slice channel quota limit, and suspends transfer if it has been reached.
	*/
	void checkSliceQuota() const;

	/*
	Suspends the current DMA transfer by:
	- Setting the appropriate interrupt (CIS) bit of the D_STAT register.
	- Setting CHCH.STR to 0.
	*/
	void suspendTransfer() const;

	/*
	Checks for D_STAT CIS & CIM conditions, and sends interrupt if the AND of both is 1.
	*/
	void checkInterruptStatus() const;



	// Data transfer functions (for Normal, Chain, Interleaved modes).

	/*
	Transfer one data unit using the DMA channel register settings. This is common to both Slice and Burst channels.
	*/
	void transferDataUnit() const;

	/*
	Read and write a qword from the specified peripheral, or from physical memory (either main memory or SPR (scratchpad ram)).
	Note: the DMAC operates on physical addresses only - the TLB/PS2 MMU is not involved.
	*/
	DMADataUnit_t readDataChannel() const;
	void writeDataChannel(DMADataUnit_t data) const;
	DMADataUnit_t readDataMemory(u32 PhysicalAddressOffset, bool SPRAccess) const;
	void writeDataMemory(u32 PhysicalAddressOffset, bool SPRAccess, DMADataUnit_t data) const;



	// Chain mode functions.

	/*
	Reads in a DMAtag given the channel ID (from the TADR register).
	*/
	DMAtag_t readDMAtag() const;

	/*
	Transfer a DMAtag. It is only defined one way, from memory to peripheral (as it is only effective in source chain mode).
	Therefore do not need to update MADR and QWC.
	*/
	void transferDMAtag() const;

	/*
	Checks if a DMAtag transfer should be suspended at the end of the packet transfer (QWC == 0 and TAG.IRQ/CHCR.TIE condition). Use bit 31 of CHCH.TAG to do this.
	*/
	void checkDMAtagPacketInterrupt() const;

	/*
	Checks if we are in a tag instruction that ends the transfer after the packet has completed. If so, changes the channel to a suspended state.
	*/
	void checkChainExit() const;

	/*
	Chain DMAtag handler functions. Consult page 59 and 60 of EE Users Manual.
	*/
	void INSTRUCTION_UNSUPPORTED();
	void REFE();
	void CNT();
	void NEXT();
	void REF();
	void REFS();
	void CALL();
	void RET();
	void END();
	void CNTS();

	/*
	Static arrays needed to call the appropriate DMAtag handler function.
	There is one for source and destination chain modes. See page 60 and 61 of EE Users Manual for the list of applicable DMAtag instructions.
	*/
	void(DMACInterpreter::*const SRC_CHAIN_INSTRUCTION_TABLE[PS2Constants::EE::DMAC::NUMBER_CHAIN_INSTRUCTIONS])() =
	{
		&DMACInterpreter::REFE,
		&DMACInterpreter::CNT,
		&DMACInterpreter::NEXT,
		&DMACInterpreter::REF,
		&DMACInterpreter::REFS,
		&DMACInterpreter::CALL,
		&DMACInterpreter::RET,
		&DMACInterpreter::END
	};
	void(DMACInterpreter::*const DST_CHAIN_INSTRUCTION_TABLE[PS2Constants::EE::DMAC::NUMBER_CHAIN_INSTRUCTIONS])() =
	{
		&DMACInterpreter::CNTS,
		&DMACInterpreter::CNT,
		&DMACInterpreter::INSTRUCTION_UNSUPPORTED,
		&DMACInterpreter::INSTRUCTION_UNSUPPORTED,
		&DMACInterpreter::INSTRUCTION_UNSUPPORTED,
		&DMACInterpreter::INSTRUCTION_UNSUPPORTED,
		&DMACInterpreter::INSTRUCTION_UNSUPPORTED,
		&DMACInterpreter::END,
	};
};

