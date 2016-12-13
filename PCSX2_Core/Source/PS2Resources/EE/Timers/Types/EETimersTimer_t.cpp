#include "stdafx.h"

#include "PS2Resources/EE/Timers/Types/EETimersTimer_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"

EETimersTimer_t::EETimersTimer_t(const u32& timerID, bool isHoldDefined) :
	mTimerID(timerID),
	COUNT(std::make_shared<EETimersTimerRegister_COUNT_t>()),
	MODE(std::make_shared<EETimersTimerRegister_MODE_t>(COUNT)),
	COMP(std::make_shared<Register32_t>()),
	HOLD(nullptr)
{
	if (isHoldDefined)
		HOLD = std::make_shared<Register32_t>();
}
