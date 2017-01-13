#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

#include "PS2Constants/PS2Constants.h"

class IOPDmac_t;
class IOPIntc_t;
class PhysicalMMU_t;
class IOPDmacChannel_t;

/*
The IOP DMAC system logic.
It operates using 32-bit data units.
Logic adapted from PCSX2 and PSX docs: http://problemkaputt.de/psx-spx.htm.
TODO: finish documentation.
*/
class IOPDmac : public VMExecutionCoreComponent
{
public:
	explicit IOPDmac(VMMain * vmMain);
	~IOPDmac();

	/*
	Check through the channels and initate data transfers.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

private:
	/*
	Context variables set by executionStep() in each cycle.
	Used by all of the functions below.
	*/
	u32 mChannelIndex;
	std::shared_ptr<IOPDmac_t> mDMAC;
	std::shared_ptr<PhysicalMMU_t> mIOPPhysicalMMU;
	std::shared_ptr<IOPIntc_t> mINTC;
	IOPDmacChannel_t * mChannel;

	///////////////////////////
	// DMAC Helper Functions //
	///////////////////////////

	/*
	Do a normal/block logical mode transfer through the specified DMA channel.
	*/
	void executionStep_Normal();

	/*
	Returns from the DMAC->PCR(2) register if the given channel is enabled.
	Automatically determines which PCR register to use based on ID context.
	*/
	bool isDMACChannelEnabled() const;

	/*
	Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the IOP Core (through the INTC).
	*/
	void handleInterruptCheck() const;

	/*
	Transfers data units (32-bits) between mem <-> channel.
	Returns the number of data units transfered.
	On the condition that the channel FIFO is empty (source) or full (drain), returns 0.
	*/
	u32 transferData() const;

	/*
	Sets the DMAC and channel state for suspend conditions.
	*/
	void setStateSuspended() const;

	/*
	Sets the DMAC and channel state for failed transfer conditions.
	TODO: not yet implemented, throws runtime_error.
	*/
	void setStateFailedTransfer() const;

	//////////////////////////////////////////
	// Raw Memory Transfer Helper Functions //
	//////////////////////////////////////////

	/*
	Reads a qword from memory using the address given.
	SPRAccess controls if the read is through the EE main memory or the EE Core scratchpad.
	*/
	u32 readDataMemory(u32 PhysicalAddressOffset) const;

	/*
	Writes a qword to memory using the address given.
	SPRAccess controls if the write is through the EE main memory or the EE Core scratchpad.
	*/
	void writeDataMemory(u32 PhysicalAddressOffset, u32 data) const;

};