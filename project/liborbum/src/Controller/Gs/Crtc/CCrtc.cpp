#include <stdexcept>
#include <iostream>

#include "Core.hpp"

#include "Resources/RResources.hpp"

#include "Controller/Gs/Crtc/CCrtc.hpp"

CCrtc::CCrtc(Core * core) :
	CController(core)
{
}

void CCrtc::handle_event(const ControllerEvent & event) const
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
		throw std::runtime_error("CRTC event handler not implemented - please fix!");
	}
	}
}

int CCrtc::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::GS::CRTC::PCRTC_CLK_SPEED_DEFAULT * core->get_options().system_biases[ControllerType::Type::Crtc]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "CRTC ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CCrtc::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();

	// TODO: quick hack to get started...
	static int col = 0;
	static int row = 0;
	
	if (col == -1)
	{
		// Send HBlank end.
	}
	
	col++;
	
	if (col > 639)
	{
		col = -640;
			
		// Send HBlank start.
		auto hblank_event = ControllerEvent{ ControllerEvent::Type::HBlank, 1 };
		core->enqueue_controller_event(ControllerType::Type::EeTimers, hblank_event);
		core->enqueue_controller_event(ControllerType::Type::IopTimers, hblank_event);
	
		// Copy scanline to host render.
		// core->render_scan_line(&raw_row_pixels);
	
		if (row == -1)
		{
			// Send VBlank end.
			r.ee.intc.stat.insert_field(EeIntcRegister_Stat::VBOF, 1);
			r.iop.intc.stat.insert_field(IopIntcRegister_Stat::EVBLANK, 1);
			//BOOST_LOG(Core::get_logger()) << "EVBLANK fired!";
		}
	
		row++;
	
		if (row > 223)
		{
			row = -224;
	
			// Send VBlank start.
			r.ee.intc.stat.insert_field(EeIntcRegister_Stat::VBON, 1);
			r.iop.intc.stat.insert_field(IopIntcRegister_Stat::VBLANK, 1);
			//BOOST_LOG(Core::get_logger()) << "VBLANK fired!";
	
			// Tell core to render frame.
			// core->render_frame();
		}
	}

	return 1;
}
