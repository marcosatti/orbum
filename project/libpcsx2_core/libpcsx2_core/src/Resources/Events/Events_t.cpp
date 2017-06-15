#include "Common/Global/Globals.h"
#include "Common/Types/System/Context_t.h"
#include "Common/Types/System/Event_t.h"

#include "Resources/Events/Events_t.h"

Events_t::Events_t() :
	DEBUG_TIME_ELAPSED_CURRENT(0), 
	DEBUG_TIME_ELAPSED_LAST(0)
{
	// Initialise event queues.
	for (auto& system : mSystemEvents)
		system.second = std::make_shared<boost::lockfree::spsc_queue<Event_t>>(16);

	// Set default system biases of 1.0.
	for (auto& system : mSystemClockTicks)
		system.second.first = 1.0;
}

std::shared_ptr<boost::lockfree::spsc_queue<Event_t>> & Events_t::getEvents(const Context_t system)
{
	return mSystemEvents[system];
}

void Events_t::addEvent(const Context_t system, const Event_t & event)
{
	if (!mSystemEvents[system]->push(event))
		throw std::runtime_error("Events_t::addEvent() couldn't add event to the system queue. No free space? Please debug!");
}

void Events_t::setClockBias(const std::map<Context_t, double> & biases)
{
	// Set individual biases if available in map.
	for (auto& entry : biases)
		mSystemClockTicks[entry.first].first = entry.second;

	// Sanity check for any biases that are < 0.1.
	for (auto& system : mSystemClockTicks)
	{
		if (system.second.first < 0.1)
			log(Warning, "Clock tick bias for system %s is set to %f - are you sure?", DEBUG_CONTEXT_STRINGS[system.first], system.second.first);
	}
}

void Events_t::addClockTime(const double timeDelta)
{
	// Add clock ticks by multiplying the time delta by the clock speed and bias.
	// The clock speeds come from either:
	//  1. Documentation, such as the SCE manuals or various internet sources.
	//  2. Guesses, based of transfer speeds, etc (ie: CDVD is based off DVD transfer rate).
	// Using doubles instead of ints allows for partial clock ticks, meaning it will not drift over time (ignoring floting point precision).
	mSystemClockTicks[Context_t::EECore].second += timeDelta / 1.0e6 * Constants::EE::EECore::EECORE_CLK_SPEED * mSystemClockTicks[Context_t::EECore].first;
	mSystemClockTicks[Context_t::EEDmac].second += timeDelta / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemClockTicks[Context_t::EEDmac].first;
	mSystemClockTicks[Context_t::EETimers].second += timeDelta / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemClockTicks[Context_t::EETimers].first;
	mSystemClockTicks[Context_t::EEIntc].second += timeDelta / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemClockTicks[Context_t::EEIntc].first;
	mSystemClockTicks[Context_t::VIF0].second += timeDelta / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemClockTicks[Context_t::VIF0].first;
	mSystemClockTicks[Context_t::VIF1].second += timeDelta / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemClockTicks[Context_t::VIF1].first;
	mSystemClockTicks[Context_t::VU0].second += timeDelta / 1.0e6 * Constants::EE::VPU::VU::VU_CLK_SPEED * mSystemClockTicks[Context_t::VU0].first;
	mSystemClockTicks[Context_t::VU1].second += timeDelta / 1.0e6 * Constants::EE::VPU::VU::VU_CLK_SPEED * mSystemClockTicks[Context_t::VU1].first;
	mSystemClockTicks[Context_t::IOPCore].second += timeDelta / 1.0e6 * Constants::IOP::IOPCore::IOPCORE_CLK_SPEED * mSystemClockTicks[Context_t::IOPCore].first;
	mSystemClockTicks[Context_t::IOPDmac].second += timeDelta / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * mSystemClockTicks[Context_t::IOPDmac].first;
	mSystemClockTicks[Context_t::IOPTimers].second += timeDelta / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * mSystemClockTicks[Context_t::IOPTimers].first;
	mSystemClockTicks[Context_t::IOPIntc].second += timeDelta / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * mSystemClockTicks[Context_t::IOPIntc].first;
	mSystemClockTicks[Context_t::CDVD].second += timeDelta / 1.0e6 * Constants::CDVD::CDVD_CLK_SPEED * mSystemClockTicks[Context_t::CDVD].first;
	mSystemClockTicks[Context_t::SPU2].second += timeDelta / 1.0e6 * Constants::SPU2::SPU2_CLK_SPEED * mSystemClockTicks[Context_t::SPU2].first;
	mSystemClockTicks[Context_t::GSCore].second += timeDelta / 1.0e6 * Constants::GS::GSCore::GSCORE_CLK_SPEED * mSystemClockTicks[Context_t::GSCore].first;
	mSystemClockTicks[Context_t::CRTC].second += timeDelta / 1.0e6 * Constants::GS::CRTC::PCRTC_CLK_SPEED_DEFAULT * mSystemClockTicks[Context_t::CRTC].first;
	mSystemClockTicks[Context_t::SIO2].second += timeDelta / 1.0e6 * Constants::SIO2::SIO2_CLK_SPEED * mSystemClockTicks[Context_t::SIO2].first;

	// Iterate through each of the systems; if the tick state is above 1.0, generate an event and add it to the system queue (use only whole ticks).
	for (auto& state : mSystemClockTicks)
	{
		int ticks = static_cast<int>(state.second.second);
		if (ticks > 0)
		{
			state.second.second -= ticks;
			addEvent(state.first, Event_t(Event_t::Source::ClockTick, ticks));
		}
	}

	// Debug log time elapsed every second.
	DEBUG_TIME_ELAPSED_CURRENT += timeDelta;
	if ((DEBUG_TIME_ELAPSED_CURRENT - DEBUG_TIME_ELAPSED_LAST) > 1.0e5)
	{
		log(Info, "Emulator time elapsed = %.2fs.", DEBUG_TIME_ELAPSED_CURRENT / 1.0e6);
		DEBUG_TIME_ELAPSED_LAST = DEBUG_TIME_ELAPSED_CURRENT;
	}
}