#include "Core.hpp"

#include "Controller/Iop/Sio0/CSio0.hpp"

#include "Resources/RResources.hpp"

CSio0::CSio0(Core * core) : 
	CController(core)
{
}

void CSio0::handle_event(const ControllerEvent & event)
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
		throw std::runtime_error("CSio0 event handler not implemented - please fix!");
	}
	}
}

int CSio0::time_to_ticks(const double time_us)
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::SIO0::SIO0_CLK_SPEED * core->get_options().system_bias_sio0);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "Sio0 ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CSio0::time_step(const int ticks_available)
{
	handle_reset_check();
	handle_irq_check();

	return ticks_available;
}

void CSio0::handle_reset_check()
{
	auto& r = core->get_resources();
	auto& ctrl = r.iop.sio0.ctrl;
	auto& stat = r.iop.sio0.stat;
	
	// Perform SIO0 reset (all relevant bits).
	if (ctrl.extract_field(Sio0Register_Ctrl::SIO_RESET))
	{
		auto _ctrl_lock = ctrl.scope_lock();
		auto _stat_lock = stat.scope_lock();

		ctrl.insert_field(Sio0Register_Ctrl::RESET_IRQ, 0);
		stat.insert_field(Sio0Register_Stat::TX_RDY, 1);
		stat.insert_field(Sio0Register_Stat::TX_EMPTY, 1);
		stat.insert_field(Sio0Register_Stat::IRQ, 0);
	}
}

void CSio0::handle_irq_check() 
{
	auto& r = core->get_resources();
	auto& ctrl = r.iop.sio0.ctrl;
	auto& stat = r.iop.sio0.stat;
	
	// Reset IRQ bit if it has been acknowledged by IOP.
	if (ctrl.extract_field(Sio0Register_Ctrl::RESET_IRQ))
	{
		auto _ctrl_lock = ctrl.scope_lock();
		auto _stat_lock = stat.scope_lock();

		stat.insert_field(Sio0Register_Stat::IRQ, 0);
		ctrl.insert_field(Sio0Register_Ctrl::RESET_IRQ, 0);
	}

	// Raise IOP INTC IRQ if requested.
	if (stat.extract_field(Sio0Register_Stat::IRQ)) 
	{
		auto _lock = r.iop.intc.stat.scope_lock();
		r.iop.intc.stat.insert_field(IopIntcRegister_Stat::SIO0, 1);
	}
}