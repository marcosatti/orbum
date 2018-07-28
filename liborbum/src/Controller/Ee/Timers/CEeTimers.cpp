#include "Controller/Ee/Timers/CEeTimers.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CEeTimers::CEeTimers(Core* core) :
    CController(core)
{
}

void CEeTimers::handle_event(const ControllerEvent& event)
{
    switch (event.type)
    {
    case ControllerEvent::Type::Time:
    {
        int ticks = time_to_ticks(event.data.time_us);
        for (int i = 0; i < ticks; i++)
            tick_timer(ControllerEvent::Type::Time);
        break;
    }
    case ControllerEvent::Type::HBlank:
    {
        for (int i = 0; i < event.data.amount; i++)
            tick_timer(ControllerEvent::Type::HBlank);
        break;
    }
    default:
    {
        throw std::runtime_error("CEeTimers event handler not implemented - please fix!");
    }
    }
}

int CEeTimers::time_to_ticks(const double time_us)
{
    // TODO: find out for sure.
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_bias_eetimers);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "EeTimers ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

void CEeTimers::tick_timer(const ControllerEvent::Type ce_type)
{
    auto& r = core->get_resources();

    // Update the timers which are set to count based on the type of event received.
    for (auto& unit : r.ee.timers.units)
    {
        auto _lock = unit.mode->scope_lock();

        // Check if we need to perform reset proceedures.
        if (unit.mode->write_latch)
        {
            // Reset the count register.
            uword prescale = unit.mode->calculate_prescale_and_set_event();
            unit.count->reset_prescale(prescale);

            unit.mode->write_latch = false;
        }

        // Count only if enabled.
        bool unit_enabled = unit.mode->extract_field(EeTimersUnitRegister_Mode::CUE);
        bool is_same_clk_source = ce_type == unit.mode->event_type;
        if (!unit_enabled || !is_same_clk_source)
            continue;

        // Next check for the gate function. Also check for a special gate condition,
        // for when CLKS == H_BLNK and GATS == HBLNK, in which case count normally.
        bool gated_mode = unit.mode->extract_field(EeTimersUnitRegister_Mode::GATE) > 0;
        if (gated_mode && !unit.mode->is_gate_hblnk_special())
        {
            throw std::runtime_error("EE Timers gated mode not fully implemented.");
        }
        else
        {
            // Count normally without gate.
            unit.count->increment(1);
        }

        // Check for interrupt conditions on the timer.
        handle_timer_interrupt(unit);

        // Check for zero return (ZRET) conditions (perform after interrupt check, otherwise this may cause interrupt to be missed).
        handle_timer_zret(unit);
    }
}

void CEeTimers::handle_timer_interrupt(EeTimersUnit& unit)
{
    auto& r = core->get_resources();

    bool interrupt = false;

    // Check for Compare-Interrupt.
    if (unit.mode->extract_field(EeTimersUnitRegister_Mode::CMPE))
    {
        if (unit.count->read_uword() == unit.compare->read_uword())
            interrupt = true;
    }

    // Check for Overflow-Interrupt.
    if (unit.mode->extract_field(EeTimersUnitRegister_Mode::OVFE))
    {
        if (unit.count->is_overflowed_and_reset())
            interrupt = true;
    }

    // Assert interrupt bit if flag set. IRQ line for timers is 9 -> 12.
    if (interrupt)
    {
        auto _lock = r.ee.intc.stat.scope_lock();
        r.ee.intc.stat.insert_field(EeIntcRegister_Stat::TIM_KEYS[*unit.unit_id], 1);
    }
}

void CEeTimers::handle_timer_zret(EeTimersUnit& unit)
{
    // Check for ZRET condition.
    if (unit.mode->extract_field(EeTimersUnitRegister_Mode::ZRET))
    {
        // Check for Count >= Compare.
        if (unit.count->read_uword() == unit.compare->read_uword())
        {
            // Set Count to 0.
            unit.count->write_uword(0);
        }
    }
}
