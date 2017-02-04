#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Resources/Clock/Clock_t.h"

Clock_t::Clock_t() :
	mSystemClockStates
	{
		{ { ClockSource_t::EECore, 1.0, 0.0 } }, // EECore
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // EEDmac
		{ { ClockSource_t::EEBus, 1.0, 0.0 }, { ClockSource_t::EEBus16, 1.0, 0.0 } , { ClockSource_t::EEBus256, 1.0, 0.0 } , { ClockSource_t::HBLNK, 1.0, 0.0 } }, // EETimers
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // EEIntc
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // GIF
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // IPU
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // VIF0
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // VU0
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // VIF1
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // VU1
		{ { ClockSource_t::IOPCore, 1.0, 0.0 } }, // IOPCore
		{ { ClockSource_t::IOPBus, 1.0, 0.0 } }, // IOPDmac
		{ { ClockSource_t::IOPBus, 1.0, 0.0 }, { ClockSource_t::IOPBus8, 1.0, 0.0 }, { ClockSource_t::IOPBus16, 1.0, 0.0 }, { ClockSource_t::IOPBus256, 1.0, 0.0 } }, // IOPTimers
		{ { ClockSource_t::IOPBus, 1.0, 0.0 } }, // IOPIntc
		{ { ClockSource_t::IOPBus, 1.0, 0.0 } }, // CDVD
		{ { ClockSource_t::EEBus, 1.0, 0.0 } }, // GS
	}
{
}

std::vector<SystemClockState_t>& Clock_t::getSystemClockState(const System_t& system)
{
	return mSystemClockStates[static_cast<int>(system)];
}

void Clock_t::setSystemSpeedBias(const System_t& system, const double& bias)
{
	for (auto& s : mSystemClockStates[static_cast<int>(system)])
		s.mClockBias = bias;
}

const double& Clock_t::getBaseClockSpeed(const ClockSource_t & source)
{
	switch (source)
	{
	case ClockSource_t::EECore:
		return Constants::EE::EECore::EECORE_CLK_SPEED;
	case ClockSource_t::EEBus:
		return Constants::EE::EEBUS_CLK_SPEED;
	case ClockSource_t::EEBus16:
		return Constants::EE::EEBUS16_CLK_SPEED;
	case ClockSource_t::EEBus256:
		return Constants::EE::EEBUS256_CLK_SPEED;
	case ClockSource_t::IOPCore:
		return Constants::IOP::IOPCore::IOPCORE_CLK_SPEED;
	case ClockSource_t::IOPBus:
		return Constants::IOP::IOPBUS_CLK_SPEED;
	case ClockSource_t::IOPBus8:
		return Constants::IOP::IOPBUS8_CLK_SPEED; 
	case ClockSource_t::IOPBus16:
		return Constants::IOP::IOPBUS16_CLK_SPEED;
	case ClockSource_t::IOPBus256:
		return Constants::IOP::IOPBUS256_CLK_SPEED; 
	case ClockSource_t::HBLNK:
		return Constants::GS::PCRTC::HBLNK_CLK_SPEED;
	default:
		throw std::runtime_error("Could not determine default clock speed.");
	}
}
