#pragma once

#include "VM/Types/VMSystem_s.h"

class SPU2_t;
class IOPIntc_t;
class SPU2Core_t;

/*
SPU2 system logic.
2 steps involved:
 1. Check through the DMA channels, and send/recieve data as necessary.
 2. Process audio and play samples at 44.1 or 48.0 kHz.
*/
class SPU2_s : public VMSystem_s
{
public:
	SPU2_s(VM * vm);
	virtual ~SPU2_s() = default;

	/*
	Initalisation.
	*/
	void initalise() override;

	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Context resources needed.
	*/
	std::shared_ptr<SPU2_t> mSPU2;
	std::shared_ptr<IOPIntc_t> mINTC;
	SPU2Core_t * mCore;

	/*
	Checks the DMA status, and initiates transfers if enabled and data is ready.
	An IOP interrupt is generated after a buffer has been filled - this is 256 hwords in stereo mode, 512 hwords in mono mode.
	Return value indicates if one or more DMA transfers occurred.
	*/
	bool handleDMATransfer();

	/*
	Handles the sound generation by processing data in the SPU2.
	Interfaces with the emulator to play sound.
	Return value indicates if sound was generated (always true, except if core is disabled).
	*/
	bool handleSoundGeneration();

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
};

