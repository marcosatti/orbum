#include "stdafx.h"

#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "PS2Resources/IOP/Timers/IOPTimers_t.h"

IOPTimersTimerRegister_Mode_t::IOPTimersTimerRegister_Mode_t(const std::shared_ptr<IOPTimersTimerRegister_Count_t> & count) :
	mCount(count)
{
}

IOPTimersTimerRegister_Count_t::IOPTimersTimerRegister_Count_t() :
	mIsOverflowed(false)
{
}

void IOPTimersTimerRegister_Count_t::increment(u16 value)
{
	u32 temp = readWordU() + value;

	if (temp > Constants::VALUE_U16_MAX)
	{
		// Set overflow flag and wrap value around.
		mIsOverflowed = true;
		temp = temp % Constants::VALUE_U16_MAX;
	}

	writeWordU(temp);
}

bool IOPTimersTimerRegister_Count_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void IOPTimersTimerRegister_Count_t::reset()
{
	writeWordU(0);
}