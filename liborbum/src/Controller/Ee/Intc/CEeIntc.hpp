#pragma once

#include "Controller/CController.hpp"

class Core;

/// Checks the I_STAT register for any pending interrupts. If there are, AND's it with the I_MASK register and checks for any interrupts to send to the EE Core to process.
/// Note that the maximum time resolution that this can run at is limited to BUSCLK - the reason for this being that all interrupt sources runat BUSCLK or less.
/// Therefore it should be included with the BUSCLK events in the main emulation loop.
class CEeIntc : public CController
{
public:
    CEeIntc(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    /// Checks the INTC STAT and MASK registers and sends an interrupt to the EE Core on the INT0 line.
    /// See EE Core Users Manual page 73-75 for the EE Core details. Note that on page 75, there is a typo, where the INTx lines are mixed up on bits 10 and 11 (verified through running through bios code).
    int time_step(const int ticks_available);
};
