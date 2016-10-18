#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMADataUnit_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/Tables/EEDmacTable/EEDmacTable.h"

using ChannelProperties_t = EEDmacTable::ChannelProperties_t;
using Direction_t = EEDmacTable::Direction_t;

/*
The InterpreterDMAC class controls the execution of the DMAC and transfers through DMA.

It is called InterpreterDMAC as it is actually a micro controller (duh) with its own language (DMAtag)!
Therefore we are still required to interpret these instructions, although it probably doesn't warrant a recompiler.

The DMAC is synced to the BUSCLK clock source, and at most transfers a qword (a 4 x 32-bit data unit) every tick (128 bits) on slice and burst channels 
 (since the bus is 128-bit long).
In a slice physical transfer mode, 8 qwords are transfered before the DMAC releases the bus to the CPU - it waits for a 'DMA request' command before continuing.
In a burst physical transfer mode, n qwords are transfered all at once - the CPU must wait for the DMAC to release the bus.

See EE Users Manual page 41 onwards.

Some notes:
 - From what I gather, when the manual talks about a peripheral processors, ie: "transfering data to or from", there is a FIFO queue 128 bytes long
    which stores the DMA channel data? Since you can't specify the dest/src address, except for when accessing SPR or main mem...
 - EERegisterDMACDChcr_t sets PS2Resources->EE->DMAC->SliceCountState[Channel ID] to 0 everytime CHCR.STR has 1 written to it (at the start of a new/resumed transfer).

TODO: Not implemented:
 - MFIFO handling.
 - D_ENABLER/W handling.
 - Cycle stealing.

TODO: Speedups can be done here:
 - Dont need to transfer 1-qword at a time.
 - Dont need to turn on cycle stealing if requested? Kind of redundant in an emulator.
*/

class DMACInterpreter : public VMExecutionCoreComponent
{
public:
	explicit DMACInterpreter(VMMain * vmMain);
	~DMACInterpreter();

	/*
	See VMExecutionCoreComponent for documentation.
	*/
	std::vector<ClockSource_t> mClockSources;
	const std::vector<ClockSource_t> & getClockSources() override;

	/*
	Check through the channels and initate data transfers. 
	Slice channels transfer 8 qwords (128 bytes) before suspending transfer, where as burst channels transfer all data without suspending.
	TODO: Currently it is assumed that the software uses the DMAC correctly (such as using correct chain mode for a channel). Need to add in checks?
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

private:
	/*
	Temporary context variables set by executionStep() in each cycle. Used by all of the functions below (ie: in Normal, Chain or Interleaved mode).
	*/
	u32 mChannelIndex;
	const ChannelProperties_t * mChannelProperties;



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
	void executionStep_Interleaved() const;



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

	/*
	Gets the runtime direction. Useful for channels where it can be either way.
	*/
	Direction_t getRuntimeDirection() const;

	/*
	Returns if source stall control checks should occur, by checking the channel direction and D_CTRL.STS.
	*/
	bool isSourceStallControlOn() const;

	/*
	Returns if drain stall control checks should occur, by checking the channel direction and D_CTRL.STD.
	*/
	bool isDrainStallControlOn() const;

	/*
	Updates STADR from the MADR register (from source channels). Use with isSourceStallControlOn().
	*/
	void updateSourceStallControlAddress() const;

	/*
	Returns true if MADR + 8 > STADR, which is the condition a drain channel stalls on with stall control.
	Also controls the D_STAT.SISn bit - sets to 1 if a stall occurred.
	TODO: According to the docs, "SIS bit doesn't change even if the transfer restarts"! PS2 OS sets it back to 0?
	*/
	bool isDrainStallControlWaiting() const;



	// Data transfer functions (for Normal, Chain, Interleaved modes).

	/*
	Transfer one data unit using the DMA channel register settings. This is common to both Slice and Burst channels.
	*/
	void transferDataUnit() const;

	/*
	Read and write a qword from the specified peripheral, or from physical memory (either main memory or SPR (scratchpad ram)).
	Note: the DMAC operates on physical addresses only - the TLB/PS2 EECoreMMU is not involved.
	*/
	DMADataUnit_t readDataChannel() const;
	void writeDataChannel(DMADataUnit_t data) const;
	DMADataUnit_t readDataMemory(u32 PhysicalAddressOffset, bool SPRAccess) const;
	void writeDataMemory(u32 PhysicalAddressOffset, bool SPRAccess, DMADataUnit_t data) const;



	// Chain mode functions.

	/*
	Temporary context variables, set by the chain mode functions.
	*/
	DMAtag_t mDMAtag;

	/*
	Sets mDMAtag to the tag read from memory/SPR (from the TADR register).
	Also sets the CHCH.TAG field to bits 16-31 of the DMAtag read.
	*/
	void readDMAtag();

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



	// Interleaved Mode Functions.

	/*
	Checks if the InterleavedCountState has reached the approriate state (limit of transferred data or skip data), and toggles the state.
	*/
	void checkInterleaveCount() const;
};

