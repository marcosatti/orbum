#pragma once

#include "Controller/CController.hpp"

#include "Resources/Spu2/Spu2Cores.hpp"

/// SPU2 system logic.
/// 2 steps involved:
///  1. Check through the DMA channels, and send/recieve data as necessary.
///  2. Process audio and play samples at 44.1 or 48.0 kHz.
class CSpu2 : public CController
{
public:
	CSpu2(Core * core);

	void handle_event(const ControllerEvent & event) override;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);
	
	/// Steps through the SPU2 state, performing the following tasks:
	///  - Check and process incoming/outgoing DMA data transfers.
	///  - Do sound generation and interfacing with the VM / user.
	///  - Check for any IRQ's pending and notify the IOP INTC.
	int time_step(const int ticks_available);

	///////////////////////////
	// SPU2 Helper Functions //
	///////////////////////////

	/// Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the IOP Core (through the INTC).
	void handle_interrupt_check(Spu2Core_Base & spu2_core);

	/// Checks the DMA status, and initiates transfers if enabled and data is ready.
	/// An IOP interrupt is generated after a buffer has been filled - this is 256 hwords in stereo mode, 512 hwords in mono mode.
	/// Return value indicates if one or more DMA transfers occurred.
	bool handle_dma_transfer(Spu2Core_Base & spu2_core);

	/// Transfers data between the SPU2 FIFO and the SPU2 memory.
	/// Returns the number of data packets transfered.
	/// On the condition that the channel FIFO is empty (source) or full (drain), returns 0.
	/// There are separate read/write functions for both manual DMA (MDMA) and auto DMA (ADMA) modes - see inside the functions for more info.
	int transfer_data_adma_write(Spu2Core_Base & spu2_core);
	int transfer_data_adma_read(Spu2Core_Base & spu2_core);
	int transfer_data_mdma_write(Spu2Core_Base & spu2_core);
	int transfer_data_mdma_read(Spu2Core_Base & spu2_core);

	/// Read or write hwords to the SPU2 memory, while automatically setting the core IRQ status if the address is the same as the IRQA register.
	/// Careful: the address supplied is in terms of a hword offset, not byte offset.
	/// See SPU2 Overview manual page 36 for more info.
	/// TODO: Very basic IRQ condition checking. Probably needs work.
	uhword read_hword_memory(Spu2Core_Base & spu2_core, const uptr address);
	void write_hword_memory(Spu2Core_Base & spu2_core, const uptr address, const uhword value);

	///////////////////////////////////////
	// Sound Generation Helper Functions //
	///////////////////////////////////////

	/// Handles the sound generation by processing data in the SPU2.
	/// Interfaces with the emulator to play sound.
	/// Return value indicates if sound was generated (always true, except if core is disabled).
	bool handle_sound_generation(Spu2Core_Base & spu2_core);
};

