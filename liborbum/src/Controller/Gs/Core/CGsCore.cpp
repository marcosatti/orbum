#include "Core.hpp"

#include "Controller/Gs/Core/CGsCore.hpp"

#include "Resources/RResources.hpp"

CGsCore::CGsCore(Core * core) : 
	CController(core)
{
}

void CGsCore::handle_event(const ControllerEvent & event)
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
		throw std::runtime_error("CGsCore event handler not implemented - please fix!");
	}
	}
}

int CGsCore::time_to_ticks(const double time_us)
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::GS::GSCore::GSCORE_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::GsCore]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "GS Core ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CGsCore::time_step(const int ticks_available)
{
	// Not yet implemented.
	return ticks_available;
}