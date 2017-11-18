#pragma once

#include "VM/Types/VMSystem_t.h"

class SPU2_t;
class RIopIntc;
class IOPDmac_t;
class SPU2Core_t;

/*
SPU2 system logic.
2 steps involved:
 1. Check through the DMA channels, and send/recieve data as necessary.
 2. Process audio and play samples at 44.1 or 48.0 kHz.
*/
class SPU2_s : public VMSystem_t
{
public:
	SPU2_s(VM * vm);
	virtual ~SPU2_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the SPU2 state, performing the following tasks:
	 - Check and process incoming/outgoing DMA data transfers.
	 - Do sound generation and interfacing with the VM / user.
	 - Check for any IRQ's pending and notify the IOP INTC.
	*/
	int step(const Event_t & event) override;

	/*
	Context resources needed.
	*/
	SPU2_t mSPU2;
	RIopIntc mINTC;
	IOPDmac_t mDMAC;
	SPU2Core_t * mCore;

	///////////////////////////
	// SPU2 Helper Functions //
	///////////////////////////

	/*
	Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the IOP Core (through the INTC).
	*/
	void handleInterruptCheck() const;

	/*
	Checks the DMA status, and initiates transfers if enabled and data is ready.
	An IOP interrupt is generated after a buffer has been filled - this is 256 hwords in stereo mode, 512 hwords in mono mode.
	Return value indicates if one or more DMA transfers occurred.
	*/
	bool handleDMATransfer();

	/*
	Transfers data between the SPU2 FIFO and the SPU2 memory.
	Returns the number of data packets transfered.
	On the condition that the channel FIFO is empty (source) or full (drain), returns 0.
	There are separate read/write functions for both manual DMA (MDMA) and auto DMA (ADMA) modes - see inside the functions for more info.
	*/
	int transferData_ADMA_Write() const;
	int transferData_ADMA_Read() const;
	int transferData_MDMA_Write() const;
	int transferData_MDMA_Read() const;

	/*
	Read or write hwords to the SPU2 memory, while automatically setting the core IRQ status if the address is the same as the IRQA register.
	Careful: the address supplied is in terms of a hword offset, not byte offset.
	See SPU2 Overview manual page 36 for more info.
	TODO: Very basic IRQ condition checking. Probably needs work.
	*/
	uhword readHwordMemory(const uptr address) const;
	void writeHwordMemory(const uptr address, const uhword value) const;

	///////////////////////////////////////
	// Sound Generation Helper Functions //
	///////////////////////////////////////

	/*
	Handles the sound generation by processing data in the SPU2.
	Interfaces with the emulator to play sound.
	Return value indicates if sound was generated (always true, except if core is disabled).
	*/
	bool handleSoundGeneration();
};

