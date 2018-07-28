#include "Resources/Ee/Timers/EeTimersUnitRegisters.hpp"

#include "Core.hpp"
#include "Resources/Ee/Timers/REeTimers.hpp"

EeTimersUnitRegister_Count::EeTimersUnitRegister_Count() :
    is_overflowed(false),
    prescale_target(1),
    prescale_count(0)
{
}

void EeTimersUnitRegister_Count::increment(const uhword value)
{
    // Update only if the prescale threshold has been reached.
    prescale_count += static_cast<int>(value);
    if (prescale_count >= prescale_target)
    {
        uword count = read_uword();

        while (prescale_count >= prescale_target)
        {
            count += 1;
            prescale_count -= prescale_target;
        }

        if (count > VALUE_UHWORD_MAX)
        {
            count %= VALUE_UHWORD_MAX;
            is_overflowed = true;
        }

        write_uword(count);
    }
}

bool EeTimersUnitRegister_Count::is_overflowed_and_reset()
{
    bool temp = is_overflowed;
    is_overflowed = false;
    return temp;
}

void EeTimersUnitRegister_Count::reset_prescale(const int prescale_target)
{
    write_uword(0);

    this->prescale_target = prescale_target;
    prescale_count = 0;
}

EeTimersUnitRegister_Mode::EeTimersUnitRegister_Mode() :
    write_latch(false),
    event_type(ControllerEventType::Time)
{
}

void EeTimersUnitRegister_Mode::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (write_latch)
        BOOST_LOG(Core::get_logger()) << "EE Timer unit write latch was already set - please check (might be ok)!";

    // Clear bits 10 and 11 (0xC00) when a 1 is written to them.
    uword temp = value;
    if (context == BusContext::Ee)
    {
        uword reg_value = read_uword();
        temp = (reg_value & 0xFFFFF3FF) | ((reg_value & 0xC00) & (~(value & 0xC00)));
    }

    write_uword(temp);

    // Signal a timer unit reset is required.
    write_latch = true;
}

bool EeTimersUnitRegister_Mode::is_gate_hblnk_special()
{
    return ((extract_field(CLKS) == 3) && (extract_field(GATS) == 0));
}

uword EeTimersUnitRegister_Mode::calculate_prescale_and_set_event()
{
    uword source = extract_field(CLKS);
    if (source == 0x0)
    {
        event_type = ControllerEventType::Time;
        return 1;
    }
    else if (source == 0x1)
    {
        event_type = ControllerEventType::Time;
        return 16;
    }
    else if (source == 0x2)
    {
        event_type = ControllerEventType::Time;
        return 256;
    }
    else if (source == 0x3)
    {
        event_type = ControllerEventType::HBlank;
        return 1;
    }
    else
    {
        throw std::runtime_error("EE Timers unit mode: failed to get prescale - please debug!");
    }
}
