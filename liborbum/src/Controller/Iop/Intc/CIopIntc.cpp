#include "Core.hpp"

#include "Controller/Iop/Intc/CIopIntc.hpp"

#include "Resources/RResources.hpp"

CIopIntc::CIopIntc(Core * core) : 
	CController(core)
{
}

void CIopIntc::handle_event(const ControllerEvent & event)
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
		throw std::runtime_error("CIopIntc event handler not implemented - please fix!");
	}
	}
}

int CIopIntc::time_to_ticks(const double time_us)
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * core->get_options().system_bias_iopintc);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "IopDmac ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CIopIntc::time_step(const int ticks_available)
{
	auto& r = core->get_resources();
	auto& ctrl = r.iop.intc.ctrl;
	auto& stat = r.iop.intc.stat;
	auto& mask = r.iop.intc.mask;
	auto& cause = r.iop.core.cop0.cause;

	// Check the master CTRL register and STAT register.
	bool interrupt = false;
	if (ctrl.read_uword() > 0)
	{
		if (stat.read_uword() & mask.read_uword())
			interrupt = true;
	}

	// Set IRQ line 2 on IOP Core if an interrupt occured.
	if (interrupt)
		cause.set_irq_line(2);
	else
		cause.clear_irq_line(2);

	return 1;
}
