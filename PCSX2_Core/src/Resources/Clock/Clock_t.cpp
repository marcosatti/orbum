#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"
#include "Common/Types/ClockSource_t.h"

#include "Resources/Clock/Clock_t.h"

Clock_t::Clock_t() :
	mPixelClockSpeed(Constants::GS::CRTC::PCRTC_CLK_SPEED_DEFAULT), 
	DEBUG_TIME_ELAPSED_CURRENT(0), 
	DEBUG_TIME_ELAPSED_LAST(0)
{
	// Set default system biases of 1.0.
	for (auto& system : mSystemTickState)
		system.second.bias = 1.0;
}

const EnumMap_t<ClockSource_t, double>& Clock_t::getSystemClockTicks(const System_t system)
{
	return mSystemTickState[system].state;
}

void Clock_t::setSystemClockBiases(const std::map<System_t, double> & biases)
{
	// Perform this while locked.
	std::lock_guard<std::mutex> lock(mSystemTickWriteMutex);

	// First set default bias of 1.0 (no change).
	for (auto& system : mSystemTickState)
	{
		system.second.bias = 1.0;
	}

	// Set individual biases if available in map.
	for (auto& entry : biases)
	{
		mSystemTickState[entry.first].bias = entry.second;
	}

	// Sanity check for any biases that are 0.0.
	for (auto& system : mSystemTickState)
	{
		if (system.second.bias <= 0.0)
		{
#if defined(BUILD_DEBUG)
			log(Warning, "Bias for system %s is set to %f - are you sure?", SYSTEM_STR[system.first], system.second.bias);
#else
			system.second.bias = 1.0;
#endif
		}
	}
}

void Clock_t::addSystemClockTicksAll(const double time)
{
	// Perform this while locked.
	std::lock_guard<std::mutex> lock(mSystemTickWriteMutex);

	// Produce EECoreClock ticks.
	mSystemTickState[System_t::EECore].state[ClockSource_t::EECoreClock] += time / 1.0e6 * Constants::EE::EECore::EECORE_CLK_SPEED * mSystemTickState[System_t::EECore].bias;

	// Produce EEBusClock ticks.
	mSystemTickState[System_t::EEDmac].state[ClockSource_t::EEBusClock] += time / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemTickState[System_t::EEDmac].bias;
	mSystemTickState[System_t::EETimers].state[ClockSource_t::EEBusClock] += time / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemTickState[System_t::EETimers].bias;
	mSystemTickState[System_t::EEIntc].state[ClockSource_t::EEBusClock] += time / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemTickState[System_t::EEIntc].bias;
	mSystemTickState[System_t::VIF0].state[ClockSource_t::EEBusClock] += time / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemTickState[System_t::VIF0].bias;
	mSystemTickState[System_t::VIF1].state[ClockSource_t::EEBusClock] += time / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * mSystemTickState[System_t::VIF1].bias;

	// Produce VUClock ticks.
	mSystemTickState[System_t::VU0].state[ClockSource_t::VUClock] += time / 1.0e6 * Constants::EE::VPU::VU::VU_CLK_SPEED * mSystemTickState[System_t::VU0].bias;
	mSystemTickState[System_t::VU1].state[ClockSource_t::VUClock] += time / 1.0e6 * Constants::EE::VPU::VU::VU_CLK_SPEED * mSystemTickState[System_t::VU1].bias;

	// Produce IOPCoreClock ticks.
	mSystemTickState[System_t::IOPCore].state[ClockSource_t::IOPCoreClock] += time / 1.0e6 * Constants::IOP::IOPCore::IOPCORE_CLK_SPEED * mSystemTickState[System_t::IOPCore].bias;

	// Produce IOPBusClock ticks.
	mSystemTickState[System_t::IOPDmac].state[ClockSource_t::IOPBusClock] += time / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * mSystemTickState[System_t::IOPDmac].bias;
	mSystemTickState[System_t::IOPTimers].state[ClockSource_t::IOPBusClock] += time / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * mSystemTickState[System_t::IOPTimers].bias;
	mSystemTickState[System_t::IOPIntc].state[ClockSource_t::IOPBusClock] += time / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * mSystemTickState[System_t::IOPIntc].bias;

	// Produce CDVDClock ticks.
	mSystemTickState[System_t::CDVD].state[ClockSource_t::CDVDClock] += time / 1.0e6 * Constants::CDVD::CDVD_CLK_SPEED * mSystemTickState[System_t::CDVD].bias;

	// Produce SPU2Clock ticks.
	mSystemTickState[System_t::SPU2].state[ClockSource_t::SPU2Clock] += time / 1.0e6 * Constants::SPU2::SPU2_CLK_SPEED * mSystemTickState[System_t::SPU2].bias;

	// Produce GSCoreClock ticks.
	mSystemTickState[System_t::GSCore].state[ClockSource_t::GSCoreClock] += time / 1.0e6 * Constants::GS::GSCore::GSCORE_CLK_SPEED * mSystemTickState[System_t::GSCore].bias;

	// Produce PixelClock ticks.
	mSystemTickState[System_t::CRTC].state[ClockSource_t::PixelClock] += time / 1.0e6 * mPixelClockSpeed * mSystemTickState[System_t::CRTC].bias;
	mSystemTickState[System_t::IOPTimers].state[ClockSource_t::PixelClock] += time / 1.0e6 * mPixelClockSpeed * mSystemTickState[System_t::IOPTimers].bias;

	// Debug log time elapsed every second.
	DEBUG_TIME_ELAPSED_CURRENT += time;
	if ((DEBUG_TIME_ELAPSED_CURRENT - DEBUG_TIME_ELAPSED_LAST) > 1.0e5)
	{
		log(Info, "Emulator time elapsed = %.2fs.", DEBUG_TIME_ELAPSED_CURRENT / 1.0e6);
		DEBUG_TIME_ELAPSED_LAST = DEBUG_TIME_ELAPSED_CURRENT;
	}
}

void Clock_t::addSystemClockTicks(const System_t system, const ClockSource_t clockSource, const int ticks)
{
	// Perform this while locked.
	std::lock_guard<std::mutex> lock(mSystemTickWriteMutex);

	mSystemTickState[system].state[clockSource] += static_cast<double>(ticks) * mSystemTickState[system].bias;
}

void Clock_t::subSystemClockTicks(const System_t system, const ClockSource_t clockSource, const int ticks)
{
	// Perform this while locked.
	std::lock_guard<std::mutex> lock(mSystemTickWriteMutex);

	mSystemTickState[system].state[clockSource] -= static_cast<double>(ticks);
}

void Clock_t::setPixelClockSpeed(const int resX, const double fH)
{
	// Working: period of 1 cycle, divided by half (actual render vs. hblank), divided by number of resX pixels, all inversed for Hz.
	mPixelClockSpeed = 1 / ((1 / fH) / 2 / resX); 
}