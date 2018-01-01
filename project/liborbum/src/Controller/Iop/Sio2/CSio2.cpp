#include "Core.hpp"

#include "Controller/Iop/Sio2/CSio2.hpp"

#include "Resources/RResources.hpp"

CSio2::CSio2(Core * core) : 
	CController(core)
{
}

void CSio2::handle_event(const ControllerEvent & event) const
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
		throw std::runtime_error("CSio2 event handler not implemented - please fix!");
	}
	}
}

int CSio2::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::SIO2::SIO2_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::Sio2]);
	
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

int CSio2::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();
	
	if (r.iop.sio2.ctrl.write_latch)
	{
		/*
		if (r.iop.sio2.ctrl.extract_field(SIO2Register_CTRL_t::Reset) > 0)
		{
		}
		else
		{
	
		}
		*/
	
		// Raise IOP IRQ always.
		//r.iop.intc.stat.insert_field(IopIntcRegister_Stat::SIO2, 1);

		r.iop.sio2.ctrl.write_latch = false; 
	}

	return 1;
}