#include "Core.hpp"

#include "Controller/Iop/Sio0/CSio0.hpp"

#include "Resources/RResources.hpp"

CSio0::CSio0(Core * core) : 
	CController(core)
{
}

void CSio0::handle_event(const ControllerEvent & event) const
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

int CSio0::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::SIO0::SIO0_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::Sio0]);
	
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

int CSio0::time_step(const int ticks_available) const
{
	// Not yet implemented.
	return ticks_available;
}