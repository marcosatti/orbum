#pragma once

#include "Controller/CController.hpp"

class CSio0 : public CController
{
public:
    CSio0(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    int time_step(const int ticks_available);

    /// Performs a reset if needed.
    void handle_reset_check();

    /// Handles raising IRQ's with the IOP and resetting the state.
    void handle_irq_check();
};
