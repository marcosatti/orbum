#pragma once

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_s.h"

#include "Resources/EE/DMAC/Types/EEDMAtag_t.h"

class EEDmac_t;
class PhysicalMMU_t;
class EEDmacChannel_t;

/*
The EE DMAC system controls the execution of the EE DMAC and transfers through DMA.

The EE DMAC is synced to the BUSCLK clock source, and at most transfers a qword (a 128-bit data unit) every tick on slice and burst channels.
In a slice physical transfer mode, 8 qwords are transfered before the DMAC releases the bus to the CPU - it waits for a 'DMA request' command before continuing.
In a burst physical transfer mode, n qwords are transfered all at once - the CPU must wait for the DMAC to release the bus.

See EE Users Manual page 41 onwards.

TODO: Not implemented:
 - MFIFO handling.
 - D_ENABLER/W handling.
 - Cycle stealing.

TODO: Speedups can be done here:
 - Dont need to transfer 1-qword at a time.
 - Dont need to turn on cycle stealing if requested? Kind of redundant in an emulator.
*/
class EEDmac_s : public VMSystem_s
{
public:
	explicit EEDmac_s(VM * vm);
	virtual ~EEDmac_s();

	/*
	Check through the channels and initate data transfers.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<EEDmac_t> mDMAC;
	std::shared_ptr<PhysicalMMU_t> mEEPhysicalMMU;
	EEDmacChannel_t * mChannel;

	/////////////////////////////////
	// DMAC Logical Mode Functions //
	/////////////////////////////////

	/*
	Do a normal logical mode transfer through the specified DMA channel.
	*/
	void transferNormal();

	/*
	Do a chain logical mode transfer through the specified DMA channel.
	*/
	void transferChain();

	/*
	Do a interleaved logical mode transfer through the specified DMA channel.
	*/
	void transferInterleaved();

	///////////////////////////
	// DMAC Helper Functions //
	///////////////////////////

	/*
	Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the EE Core.
	*/
	void handleInterruptCheck() const;

	/*
	Transfers data units (128-bits) between mem <-> channel.
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
	u128 readDataMemory(u32 PhysicalAddressOffset, bool SPRAccess) const;

	/*
	Writes a qword to memory using the address given.
	SPRAccess controls if the write is through the EE main memory or the EE Core scratchpad.
	*/
	void writeDataMemory(u32 PhysicalAddressOffset, bool SPRAccess, u128 data) const;

	////////////////////////////////////
	// Stall Control Helper Functions //
	////////////////////////////////////

	/*
	Returns if source stall control checks should occur, by checking the channel direction and D_CTRL.STS.
	*/
	bool isSourceStallControlOn() const;

	/*
	Returns if drain stall control checks should occur, by checking the channel direction and D_CTRL.STD.
	*/
	bool isDrainStallControlOn() const;

	/*
	Returns true if MADR + 8 > STADR, which is the condition a drain channel stalls on with stall control.
	Callee is responsible for setting the D_STAT.SIS bit.
	TODO: According to the docs, "SIS bit doesn't change even if the transfer restarts"! PS2 OS sets it back to 0?
	*/
	bool isDrainStallControlWaiting() const;

	/*
	Sets the DMAC STADR register to the current channel conditions.
	*/
	void setDMACStallControlSTADR() const;

	/*
	Sets the DMAC STAT.SISx bit to the current channel.
	*/
	void setDMACStallControlSIS() const;
	
	/////////////////////////////////
	// Chain Mode Helper Functions //
	/////////////////////////////////

	/*
	Temporary context variables, set by the chain mode functions.
	*/
	EEDMAtag_t mDMAtag;

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

	/*
	Chain DMAtag handler functions. Consult page 59 - 61 of EE Users Manual.
	*/
	void CHAIN_TAGID_UNKNOWN();
	void CHAIN_SRC_CNT();
	void CHAIN_SRC_NEXT();
	void CHAIN_SRC_REF();
	void CHAIN_SRC_REFS();
	void CHAIN_SRC_REFE();
	void CHAIN_SRC_CALL();
	void CHAIN_SRC_RET();
	void CHAIN_SRC_END();
	void CHAIN_DST_CNT();
	void CHAIN_DST_CNTS();
	void CHAIN_DST_END();

	/*
	Static arrays needed to call the appropriate DMAtag handler function.
	There is one for source and destination chain modes. See page 60 and 61 of EE Users Manual for the list of applicable DMAtag instructions.
	*/
	void(EEDmac_s::* SRC_CHAIN_INSTRUCTION_TABLE[Constants::EE::DMAC::NUMBER_CHAIN_INSTRUCTIONS])() =
	{
		&EEDmac_s::CHAIN_SRC_REFE,
		&EEDmac_s::CHAIN_SRC_CNT,
		&EEDmac_s::CHAIN_SRC_NEXT,
		&EEDmac_s::CHAIN_SRC_REF,
		&EEDmac_s::CHAIN_SRC_REFS,
		&EEDmac_s::CHAIN_SRC_CALL,
		&EEDmac_s::CHAIN_SRC_RET,
		&EEDmac_s::CHAIN_SRC_END
	};
	void(EEDmac_s::* DST_CHAIN_INSTRUCTION_TABLE[Constants::EE::DMAC::NUMBER_CHAIN_INSTRUCTIONS])() =
	{
		&EEDmac_s::CHAIN_DST_CNTS,
		&EEDmac_s::CHAIN_DST_CNT,
		&EEDmac_s::CHAIN_TAGID_UNKNOWN,
		&EEDmac_s::CHAIN_TAGID_UNKNOWN,
		&EEDmac_s::CHAIN_TAGID_UNKNOWN,
		&EEDmac_s::CHAIN_TAGID_UNKNOWN,
		&EEDmac_s::CHAIN_TAGID_UNKNOWN,
		&EEDmac_s::CHAIN_DST_END,
	};
};