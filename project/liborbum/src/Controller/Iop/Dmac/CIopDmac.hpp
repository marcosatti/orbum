#pragma once



#include "VM/Types/VMSystem_t.h"

#include "Resources/Iop/Dmac/IopDmaTag.h"

class IOPDmac_t;
class RIopIntc;
class ByteBus;
class IopDmacChannel;

/*
The IOP DMAC system logic.
It operates using 32-bit data units and can operate in burst, slice, linked-list or chain modes.
Logic adapted from PCSX2, nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
Pretty similar to the EE DMAC, and a lot of code has been adopted to suit.

If transfering data from memory to a peripheral, it will wait until the data has been received (FIFO size is 0) before interrupting the IOP INTC.
*/
class IOPDmac_s : public VMSystem_t
{
public:
	IOPDmac_s(VM * vm);
	virtual ~IOPDmac_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Check through the channels and initate data transfers.
	If a channel is enabled for transfer, data units (32-bit) are sent.
	*/
	int step(const Event_t & event) override;

	/*
	Resources.
	*/
	IOPDmac_t mDMAC;
	ByteBus mIOPByteMMU;
	RIopIntc mINTC;
	IopDmacChannel * mChannel;

	/////////////////////////////////
	// DMAC Logical Mode Functions //
	/////////////////////////////////

	/*
	Do a normal/block logical mode transfer through the specified DMA channel.
	*/
	bool transferNormalBurst();

	/*
	Do a normal/slice logical mode transfer through the specified DMA channel.
	*/
	bool transferNormalSlice();

	/*
	Do a chain logical mode transfer through the specified DMA channel.
	*/
	bool transferChain();

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
	Reads a word from memory using the address given.
	*/
	uword readWordMemory(const uptr address) const;

	/*
	Writes a word to memory using the address given.
	*/
	void writeWordMemory(const uptr address, const uword data) const;

	/*
	Reads a qword from memory using the address given.
	*/
	uqword readQwordMemory(uword bytePhysicalAddress) const;

	/////////////////////////////////
	// Chain Mode Helper Functions //
	/////////////////////////////////

	/*
	Temporary context variables, set by the chain mode functions.
	*/
	IopDmaTag mDMAtag;

	/*
	Sets mDMAtag to the tag from the TADR register.
	*/
	bool readChainSourceTag();

	/*
	Sets mDMAtag to the tag from the channel queue.
	*/
	bool readChainDestTag();
};