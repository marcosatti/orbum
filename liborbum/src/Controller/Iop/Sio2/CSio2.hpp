#pragma once

#include "Controller/CController.hpp"

/// SIO2 controller.
/// Basic operation from BIOS perspective:
/// 1. Set CTRL register value, for writing.
/// 2. For each port, set CTRL 1/2 registers (unused within emulator).
/// 3. For each port, set CTRL 3 registers.
/// 4. Send command data to the data_in FIFO.
/// 5. Turn on the SIO2 DMA channels for reading and writing.
/// 6. Set CTRL register value, for reading (based upon result from reading CTRL).
/// 7. Repeat.
class CSio2 : public CController
{
public:
	CSio2(Core * core);

	void handle_event(const ControllerEvent & event) override;
	
	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);
	
	/// Steps through the SIO2 state, initiating transfers with
	/// the SIO0 for each port enabled.
	int time_step(const int ticks_available);

	void handle_ctrl_check();

	/// Sets the SIO0 up for a reset.
	void handle_sio0_reset();

	void handle_port_trasnfer();

	void transfer_data_tx();

	void transfer_data_rx();

	void transfer_set_next_port();

	void transfer_stop(const bool raise_irq);
};

