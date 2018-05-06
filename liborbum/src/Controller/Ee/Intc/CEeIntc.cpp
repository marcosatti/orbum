#include "Core.hpp"

#include "Controller/Ee/Intc/CEeIntc.hpp"

#include "Resources/RResources.hpp"

CEeIntc::CEeIntc(Core * core) :
	CController(core)
{
}

void CEeIntc::handle_event(const ControllerEvent & event)
{
	switch (event.type)
	{
	case ControllerEvent::Type::Time:
	{
		int ticks_remaining = time_to_ticks(event.data.time_us);
		while (ticks_remaining > 0)
			ticks_remaining -= time_step(ticks_remaining);
		break;
	}
	default:
	{
		throw std::runtime_error("CEeIntc event handler not implemented - please fix!");
	}
	}
}

int CEeIntc::time_to_ticks(const double time_us)
{
	// TODO: find out for sure.
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_bias_eeintc);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "EeIntc ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CEeIntc::time_step(const int ticks_available)
{
	auto& r = core->get_resources();
	auto& cause = r.ee.core.cop0.cause;
	auto& stat = r.ee.intc.stat;
	auto& mask = r.ee.intc.mask;

	// Check the interrupt status on the stat register.
	if (stat.read_uword() & mask.read_uword())
		cause.set_irq_line(2);
	else
		cause.clear_irq_line(2);

	return 1;
}
