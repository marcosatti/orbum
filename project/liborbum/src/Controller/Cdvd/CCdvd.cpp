#include <stdexcept>

#include "Core.hpp"
#include "Controller/Cdvd/CCdvd.hpp"

#include "Resources/RResources.hpp"

CCdvd::CCdvd(Core * core) :
	CController(core)
{
}

void CCdvd::handle_event(const ControllerEvent & event)
{
	auto& r = core->get_resources();

	switch (event.type)
	{
	case ControllerEvent::Type::Time:
	{
		int ticks_remaining = time_to_ticks(event.data.time_us);
		while (ticks_remaining > 0)
			ticks_remaining -= time_step(ticks_remaining);

		handle_rtc_increment(event.data.time_us);
		
		break;
	}
	default:
	{
		throw std::runtime_error("CDVD event handler not implemented - please fix!");
	}
	}
}

int CCdvd::time_to_ticks(const double time_us)
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::CDVD::CDVD_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::Cdvd]);

	if (ticks < 5)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "CDVD ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CCdvd::time_step(const int ticks_available)
{
	auto& r = core->get_resources();

	// 2 types of commands to process: N-type, and S-type.
	// Process N-type.
	if (r.cdvd.n_command.write_latch)
	{
        auto _lock = r.cdvd.n_command.scope_lock();

		// Run the N function based upon the N_COMMAND index.
		(this->*NCMD_INSTRUCTION_TABLE[r.cdvd.n_command.read_ubyte()])();
		r.cdvd.n_rdy_din.ready.insert_field(CdvdRegister_Ns_Rdy_Din::READY_BUSY, 0);
		r.cdvd.n_command.write_latch = false;
	}

	// Process S-type.
	// Check for a pending command, only process if set.
	if (r.cdvd.s_command.write_latch)
	{
        auto _lock = r.cdvd.s_command.scope_lock();

		// Run the S function based upon the S_COMMAND index.
		(this->*SCMD_INSTRUCTION_TABLE[r.cdvd.s_command.read_ubyte()])();
		r.cdvd.s_rdy_din.ready.insert_field(CdvdRegister_Ns_Rdy_Din::READY_BUSY, 0);
		r.cdvd.s_command.write_latch = false;
	}

	return 1;
}

void CCdvd::handle_rtc_increment(const double time_us)
{
	auto& r = core->get_resources();
	auto& rtc = r.cdvd.rtc;

	rtc.increment(time_us);
}

void CCdvd::NCMD_INSTRUCTION_UNKNOWN()
{
	throw std::runtime_error("CDVD N_CMD unknown instruction called");
}

void CCdvd::SCMD_INSTRUCTION_UNKNOWN()
{
	throw std::runtime_error("CDVD S_CMD unknown instruction called");
}
