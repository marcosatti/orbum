#include <stdexcept>

#include "Resources/Iop/Timers/IopTimersUnitRegisters.hpp"

IopTimersUnitRegister_Count::IopTimersUnitRegister_Count(const int timer_id) :
	timer_id(timer_id),
	is_overflowed(false),
	prescale_target(1),
	prescale_count(0)
{
}

void IopTimersUnitRegister_Count::increment(const uword value)
{
	if (timer_id >= 0 && timer_id < 3)
		increment_16(value);
	else if (timer_id >= 3 && timer_id < 6)
		increment_32(value);
	else
		throw std::runtime_error("Invalid IOP timer id specified.");
}

bool IopTimersUnitRegister_Count::is_overflowed_and_reset()
{
	bool temp = is_overflowed;
	is_overflowed = false;
	return temp;
}

void IopTimersUnitRegister_Count::reset_prescale(const int prescale_target)
{
	write_uword(0);

	this->prescale_target = prescale_target;
	prescale_count = 0;
}

void IopTimersUnitRegister_Count::increment_16(const uhword value)
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

void IopTimersUnitRegister_Count::increment_32(const uword value)
{
	// Update only if the prescale threshold has been reached.
	prescale_count += static_cast<int>(value);
	if (prescale_count >= prescale_target)
	{
		udword count = static_cast<udword>(read_uword());

		while (prescale_count >= prescale_target)
		{
			count += 1;
			prescale_count -= prescale_target;
		}

		if (count > VALUE_UWORD_MAX)
		{
			count %= VALUE_UWORD_MAX;
			is_overflowed = true;
		}

		write_uword(static_cast<uword>(count));
	}
}

IopTimersUnitRegister_Mode::IopTimersUnitRegister_Mode(const int timer_id) :
	is_enabled(false),
	event_type(ControllerEventType::Time),
	write_latch(false),
	count_reset_prescale_target(1),
	timer_id(timer_id)
{
}

void IopTimersUnitRegister_Mode::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	if (offset != 0)
		throw std::runtime_error("Iop timers write hword offset not 0.");

	auto _lock = scope_lock();
	
	// Signal a timer unit reset is required.
	if (write_latch)
		throw std::runtime_error("IOP Timer unit write latch was already set - please debug!");
	write_latch = true;

	// Update event type source.
	handle_event_type_update();

	// Check through either of the interrupt bits for "enabled".
	is_enabled = (IRQ_ON_OF.extract_from(value) || IRQ_ON_TARGET.extract_from(value));

	write_uhword(offset, value);
}

void IopTimersUnitRegister_Mode::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();
	
	// Signal a timer unit reset is required.
	if (write_latch)
		throw std::runtime_error("IOP Timer unit write latch was already set - please debug!");
	write_latch = true;

	// Update event type source.
	handle_event_type_update();
		
	// Check through either of the interrupt bits for "enabled".
	is_enabled = (IRQ_ON_OF.extract_from(value) || IRQ_ON_TARGET.extract_from(value));

	write_uword(value);
}

void IopTimersUnitRegister_Mode::handle_event_type_update()
{
	if (timer_id < 0 || timer_id > 5)
		throw std::runtime_error("Invalid IOP timer index to determine clock source!");

	// Sources are majorly different for each type of timer... no easy way of doing this... :( .
	if (timer_id < 3)
	{
		// Check for Prescale8 (bit 9).
		if (extract_field(PRESCALE0) > 0)
		{
			throw std::runtime_error("IOP Timers handleEventSourceUpdate() not fully implemented [0].");
		}
		else
		{
			if (extract_field(EVENT_SRC) == 0)
			{
				event_type = ControllerEventType::Time;
				count_reset_prescale_target = 1;
			}
			else
			{
				event_type = ControllerEventType::HBlank;
				count_reset_prescale_target = 1;
			}
		}
	}
	else
	{
		// Check for Prescale8/16/256 (bits 13 and 14).
		if (extract_field(PRESCALE1) > 0)
		{
			throw std::runtime_error("IOP Timers handleEventSourceUpdate() not fully implemented [1].");
		}
		else
		{
			if (extract_field(EVENT_SRC) == 0)
			{
				event_type = ControllerEventType::Time;
				count_reset_prescale_target = 1;
			}
			else
			{
				throw std::runtime_error("IOP Timers handleEventSourceUpdate() not fully implemented [2].");
			}
		}
	}
}