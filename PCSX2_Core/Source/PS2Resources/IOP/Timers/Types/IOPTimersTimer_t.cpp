#include "stdafx.h"

#include "PS2Resources/IOP/Timers/Types/IOPTimersTimer_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

IOPTimersTimer_t::IOPTimersTimer_t(const u32& timerID) :
	mTimerID(timerID),
	COUNT(std::make_shared<IOPTimersTimerRegister_COUNT_t>()),
	MODE(std::make_shared<IOPTimersTimerRegister_MODE_t>(COUNT)),
	COMP(std::make_shared<Register32_t>())
{
}
