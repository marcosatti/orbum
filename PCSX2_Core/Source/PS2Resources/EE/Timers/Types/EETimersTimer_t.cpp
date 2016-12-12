#include "stdafx.h"

#include "PS2Resources/EE/Timers/Types/EETimersTimer_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"

EETimersTimer_t::EETimersTimer_t(const u32& timerID, bool isHoldDefined) :
	mTimerID(timerID),
	Count(std::make_shared<EETimersTimerRegister_Count_t>()),
	Mode(std::make_shared<EETimersTimerRegister_Mode_t>(Count)),
	Compare(std::make_shared<Register32_t>()),
	Hold(nullptr)
{
	if (isHoldDefined)
		Hold = std::make_shared<Register32_t>();
}
