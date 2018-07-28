#pragma once

#include "Controller/CController.hpp"
#include "Controller/ControllerEvent.hpp"
#include "Resources/Iop/Timers/IopTimersUnits.hpp"

/// IOPTimers updates TIM0, TIM1, TIM2, TIM3, TIM4, TIM5.
/// If interrupt conditions are met, sets the corresponding interrupt bit in the IOP INTC.
/// The IOP Timers are dynamic and can be updated on the IOP system clock, pixel clock or HLINE clocks.
class CIopTimers : public CController
{
public:
    CIopTimers(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    /// Updates the timers with the specified clock source type.
    void tick_timer(const ControllerEvent::Type ce_type);

    /// Checks the timer status and count values for interrupt conditions.
    void handle_timer_interrupt(IopTimersUnit_Base* unit, const bool has_overflowed, const bool has_reached_target);

    /// Checks for overflow conditions and handles certain conditions.
    /// Returns if a timer overflow event happened.
    bool handle_timer_overflow(IopTimersUnit_Base* unit);

    /// Checks for target conditions and handles certain conditions.
    /// Returns if a timer target event happened.
    bool handle_timer_target(IopTimersUnit_Base* unit);
};
