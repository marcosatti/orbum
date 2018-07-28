#include "Controller/Iop/Timers/CIopTimers.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CIopTimers::CIopTimers(Core* core) :
    CController(core)
{
}

void CIopTimers::handle_event(const ControllerEvent& event)
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
        throw std::runtime_error("CIopTimers event handler not implemented - please fix!");
    }
    }
}

int CIopTimers::time_to_ticks(const double time_us)
{
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * core->get_options().system_bias_ioptimers);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "IopTimers ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

void CIopTimers::tick_timer(const ControllerEvent::Type ce_type)
{
    auto& r = core->get_resources();

    // Update the timers which are set to count based on the type of event recieved.
    for (auto& unit : r.iop.timers.units)
    {
        auto _lock = unit->mode.scope_lock();

        // Check if we need to perform reset proceedures.
        if (unit->mode.write_latch)
        {
            // Work out if the timer is used meaningfully (enabled).
            bool irq_on_of = unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_ON_OF) > 0;
            bool irq_on_target = unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_ON_TARGET) > 0;
            unit->mode.is_enabled = irq_on_of || irq_on_target;

            // Reset the count register.
            uword prescale = unit->mode.calculate_prescale_and_set_event(unit->unit_id);
            unit->count.reset_prescale(prescale);

            unit->mode.write_latch = false;
        }

        // Count only if the timer is "enabled", and mode is equal to the event source.
        if (!unit->mode.is_enabled || ce_type != unit->mode.event_type)
            continue;

        // Perform a gated tick if on, else increment normally.
        bool gated_tick = unit->mode.extract_field(IopTimersUnitRegister_Mode::SYNC_ENABLE) > 0;
        if (gated_tick)
        {
            throw std::runtime_error("IOP Timers sync mode (gate) = 1, but not implemented.");
        }
        else
        {
            unit->count.increment(1);
        }

        // Check for interrupt conditions on the timer.
        bool has_overflowed = handle_timer_overflow(unit);
        bool has_reached_target = handle_timer_target(unit);
        handle_timer_interrupt(unit, has_overflowed, has_reached_target);
    }
}

void CIopTimers::handle_timer_interrupt(IopTimersUnit_Base* unit, const bool has_overflowed, const bool has_reached_target)
{
    auto& r = core->get_resources();

    bool interrupt = false;

    // Check for Compare-Interrupt.
    if (unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_ON_TARGET))
    {
        if (has_reached_target)
            interrupt = true;
    }

    // Check for Overflow-Interrupt.
    if (unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_ON_OF))
    {
        if (has_overflowed)
            interrupt = true;
    }

    // Handle internal interrupt bit if interrupt flag set.
    // TODO: needs work. I dont know how the IOP expects this to work and I cant figure out what PCSX2 does.
    if (interrupt)
    {
        // If after this code block has run, and the internal IrqRequest bit is low (0), then an external interrupt should be generated (ie: to INTC).
        // Check if we are using one-shot or repeat.
        if (unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_REPEAT))
        {
            // Check for IRQ toggle mode.
            if (unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_TOGGLE))
            {
                // Toggle bit.
                throw std::runtime_error("IOP Timers int toggle mode not implemented.");
                // uword value = unit->mode.extract_field(IopTimersUnitRegister_Mode::IrqRequest);
                // unit->mode.insert_field(IopTimersUnitRegister_Mode::IrqRequest, value ^ 1);
            }
            else
            {
                // Set bit low (0).
                unit->mode.insert_field(IopTimersUnitRegister_Mode::IRQ_REQUEST, 0);
            }
        }
        else
        {
            throw std::runtime_error("IOP Timers int oneshot mode not implemented.");
        }

        // Check for internal interrupt bit is low, and send INTC interrupt.
        if (unit->mode.extract_field(IopTimersUnitRegister_Mode::IRQ_REQUEST) == 0)
        {
            // Raise IRQ.
            auto _lock = r.iop.intc.stat.scope_lock();
            r.iop.intc.stat.insert_field(IopIntcRegister_Stat::TMR_KEYS[unit->unit_id], 1);
        }
    }
}

bool CIopTimers::handle_timer_overflow(IopTimersUnit_Base* unit)
{
    if (unit->count.is_overflowed_and_reset())
    {
        // Reset the count register if that mode is selected.
        if (unit->mode.extract_field(IopTimersUnitRegister_Mode::RESET_MODE) == 0)
            unit->count.write_uword(0);

        unit->mode.insert_field(IopTimersUnitRegister_Mode::REACH_OF, 1);
        return true;
    }

    return false;
}

bool CIopTimers::handle_timer_target(IopTimersUnit_Base* unit)
{
    if (unit->count.read_uword() == unit->compare.read_uword())
    {
        // Reset the count register if that mode is selected.
        if (unit->mode.extract_field(IopTimersUnitRegister_Mode::RESET_MODE) > 0)
            unit->count.write_uword(0);

        unit->mode.insert_field(IopTimersUnitRegister_Mode::REACH_TARGET, 1);
        return true;
    }

    return false;
}
