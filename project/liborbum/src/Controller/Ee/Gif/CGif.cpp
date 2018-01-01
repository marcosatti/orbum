#include "Core.hpp"

#include "Controller/Ee/Gif/CGif.hpp"

#include "Resources/RResources.hpp"

CGif::CGif(Core * core) : 
	CController(core)
{
}

void CGif::handle_event(const ControllerEvent & event) const
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
		throw std::runtime_error("CGif event handler not implemented - please fix!");
	}
	}
}

int CGif::time_to_ticks(const double time_us) const
{
	// TODO: find out for sure.
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::Gif]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "Gif ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CGif::time_step(const int ticks_available) const
{
	// Not yet implemented.
	return ticks_available;
}