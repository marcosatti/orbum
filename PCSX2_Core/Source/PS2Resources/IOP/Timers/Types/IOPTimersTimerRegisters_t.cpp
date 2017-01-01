#include "stdafx.h"

#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "PS2Resources/IOP/Timers/IOPTimers_t.h"

IOPTimersTimerRegister_MODE_t::IOPTimersTimerRegister_MODE_t(const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count) :
	mCount(count)
{
}

IOPTimersTimerRegister_COUNT_t::IOPTimersTimerRegister_COUNT_t() :
	mIsOverflowed(false)
{
}

void IOPTimersTimerRegister_COUNT_t::increment(u16 value)
{
	u32 temp = readWord() + value;

	if (temp > Constants::VALUE_U16_MAX)
	{
		// Set overflow flag and wrap value around.
		mIsOverflowed = true;
		temp = temp % Constants::VALUE_U16_MAX;
	}

	writeWord(temp);
}

bool IOPTimersTimerRegister_COUNT_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void IOPTimersTimerRegister_COUNT_t::reset()
{
	writeWord(0);
}