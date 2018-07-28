#pragma once

#include "Controller/CController.hpp"
#include "Resources/Ee/Timers/EeTimersUnits.hpp"

class Core;

/// EE Timers updates the 4 timer units as defined in the EE Users Manual, starting on page 33.
/// If interrupt conditions are met, sets the corresponding interrupt bit in the EE INTC.
/// The EE Timers are dynamic and can be updated on the BUSCLK, BUSCLK16, BUSCLK256 or HBLNK clocks.
class CEeTimers : public CController
{
public:
    CEeTimers(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    /// Updates the timers with the specified clock source type.
    void tick_timer(const ControllerEvent::Type ce_type);

    /// Checks the timer status and count values for interrupt conditions.
    void handle_timer_interrupt(EeTimersUnit& unit);

    /// Check for the ZRET condition and reset counter if enabled/met.
    void handle_timer_zret(EeTimersUnit& unit);
};
