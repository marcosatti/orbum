#pragma once

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_s.h"

#include "Resources/IOP/DMAC/Types/IOPDMAtag_t.h"

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
class IOPDmac_s : public VMSystem_s
{
public:
	explicit IOPDmac_s(VM * vm);
	virtual ~IOPDmac_s() = default;

	/*
	Check through the channels and initate data transfers.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<IOPDmac_t> mDMAC;
	std::shared_ptr<PhysicalMMU_t> mIOPPhysicalMMU;
	std::shared_ptr<IOPIntc_t> mINTC;
	IOPDmacChannel_t * mChannel;

	/////////////////////////////////
	// DMAC Logical Mode Functions //
	/////////////////////////////////

	/*
	Do a normal/block logical mode transfer through the specified DMA channel.
	*/
	void transferNormalBurst();

	/*
	Do a normal/slice logical mode transfer through the specified DMA channel.
	*/
	void transferNormalSlice();

	/*
	Do a chain logical mode transfer through the specified DMA channel.
	*/
	void transferChain();

	///////////////////////////
	// DMAC Helper Functions //
	///////////////////////////

	/*
	Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the IOP Core (through the INTC).
	*/
	void handleInterruptCheck() const;

	/*
	Transfers data units (32-bits) between mem <-> channel.
	Returns the number of data units transfered.
	On the condition that the channel FIFO is empty (source) or full (drain), returns 0.
	*/
	int transferData() const;

	/*
	Sets the DMAC and channel state for suspend conditions.
	*/
	void setStateSuspended() const;

	/*
	Returns if the channel is enabled, based on the index (use PCR0 or PCR1).
	*/
	bool isChannelEnabled() const;

	/*
	Returns if the channel is enabled for an IRQ tag interrupt (checks PCR1).
	*/
	bool isChannelIRQEnabled() const;

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

	/////////////////////////////////
	// Chain Mode Helper Functions //
	/////////////////////////////////

	/*
	Temporary context variables, set by the chain mode functions.
	*/
	IOPDMAtag_t mDMAtag;

	/*
	Sets mDMAtag to the tag from the TADR register.
	Also sets the CHCH.TAG field to bits 16-31 of the DMAtag read. If CHCR.TTE is set, transfers the tag.
	Returns if it was successful (true) or not (false) - use to determine if an early exit should occur (need to wait for more data).
	*/
	bool readChainSourceTag();

	/*
	Sets mDMAtag to the tag from the channel queue.
	Also sets the CHCH.TAG field to bits 16-31 of the DMAtag read. If CHCR.TTE is set, transfers the tag.
	Returns if it was successful (true) or not (false) - use to determine if an early exit should occur (need to wait for more data).
	*/
	bool readChainDestTag();

};