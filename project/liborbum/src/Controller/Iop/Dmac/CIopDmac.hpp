#pragma once

#include "Controller/CController.hpp"

#include "Resources/Iop/Dmac/IopDmacChannels.hpp"

class Core;

/// The IOP DMAC system logic.
/// It operates using 32-bit data units and can operate in burst, slice, linked-list or chain modes.
/// Logic adapted from PCSX2, nocash PSX docs (http://problemkaputt.de/psx-spx.htm), 
/// and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
/// Pretty similar to the EE DMAC, and a lot of code has been adopted to suit.
/// If transfering data from memory to a peripheral, it will wait until the data has been received (FIFO size is 0) before interrupting the IOP INTC.
/// TODO: PCSX2 (unintentionally?) does this, and seems to be required for communicating with SPU2... look into it a bit more.
class CIopDmac : public CController
{
public:
	CIopDmac(Core * core);

	void handle_event(const ControllerEvent & event) override;
	
	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);
	
	/// Check through the channels and initate data transfers.
	/// If a channel is enabled for transfer, data units (32-bit) are sent.
	int time_step(const int ticks_available);

	/////////////////////////////////
	// DMAC Logical Mode Functions //
	/////////////////////////////////

	/// Do a normal/block logical mode transfer through the specified DMA channel.
	bool transfer_normal_burst(IopDmacChannel & channel);

	/// Do a normal/slice logical mode transfer through the specified DMA channel.
	bool transfer_normal_slice(IopDmacChannel & channel);

	/// Do a chain logical mode transfer through the specified DMA channel.
	bool transfer_chain(IopDmacChannel & channel);

	///////////////////////////
	// DMAC Helper Functions //
	///////////////////////////

	/// Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the IOP Core (through the INTC).
	void handle_interrupt_check();

	/// Transfers data units (32-bits) between mem <-> channel.
	/// Returns the number of data units transfered.
	/// On the condition that the channel FIFO is empty (source) or full (drain), returns 0.
	int transfer_data(IopDmacChannel & channel);

	/// Sets the DMAC and channel state for suspend conditions.
	void set_state_suspended(IopDmacChannel & channel);

	/// Returns if the channel is enabled, based on the index (use PCR0 or PCR1).
	bool is_channel_enabled(IopDmacChannel & channel);

	/// Returns if the channel is enabled for an IRQ tag interrupt (checks PCR1).
	bool is_channel_irq_enabled(IopDmacChannel & channel);

	/////////////////////////////////
	// Chain Mode Helper Functions //
	/////////////////////////////////

	/// Sets mDMAtag to the tag from the TADR register.
	bool read_chain_source_tag(IopDmacChannel & channel);

	/// Sets mDMAtag to the tag from the channel queue.
	bool read_chain_dest_tag(IopDmacChannel & channel);
};