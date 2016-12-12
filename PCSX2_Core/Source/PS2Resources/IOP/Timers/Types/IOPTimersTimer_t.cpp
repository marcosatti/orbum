#include "stdafx.h"

#include "PS2Resources/IOP/Timers/Types/IOPTimersTimer_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

IOPTimersTimer_t::IOPTimersTimer_t(const u32& timerID) :
	mTimerID(timerID),
	Count(std::make_shared<IOPTimersTimerRegister_Count_t>()),
	Mode(std::make_shared<IOPTimersTimerRegister_Mode_t>(Count)),
	Compare(std::make_shared<Register32_t>())
{
}
