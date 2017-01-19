#include "stdafx.h"

#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "PS2Resources/IOP/Timers/IOPTimers_t.h"

IOPTimersTimerRegister_COUNT_t::IOPTimersTimerRegister_COUNT_t(const char * mnemonic) :
	Register32_t(mnemonic, false, true),
	mIsOverflowed(false)
{
}

void IOPTimersTimerRegister_COUNT_t::increment(u16 value)
{
	u32 temp = readWord(Context_t::RAW) + value;

	if (temp > Constants::VALUE_U16_MAX)
	{
		// Set overflow flag and wrap value around.
		mIsOverflowed = true;
		temp = temp % Constants::VALUE_U16_MAX;
	}

	writeWord(Context_t::RAW, temp);
}

bool IOPTimersTimerRegister_COUNT_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void IOPTimersTimerRegister_COUNT_t::reset()
{
	writeWord(Context_t::RAW, 0);
}

IOPTimersTimerRegister_MODE_t::IOPTimersTimerRegister_MODE_t(const char * mnemonic, const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count) :
	BitfieldRegister32_t(mnemonic, false, true),
	mCount(count)
{
	registerField(Fields::SyncEnable, "SyncEnable", 0, 1, 0);
	registerField(Fields::SyncMode, "SyncMode", 1, 2, 0);
	registerField(Fields::ResetMode, "ResetMode", 3, 1, 0);
	registerField(Fields::IrqOnTarget, "IrqOnTarget", 4, 1, 0);
	registerField(Fields::IrqOnOF, "IrqOnOF", 5, 1, 0);
	registerField(Fields::IrqRepeat, "IrqRepeat", 6, 1, 0);
	registerField(Fields::IrqToggle, "IrqToggle", 7, 1, 0);
	registerField(Fields::ClockSrc, "ClockSrc", 8, 2, 0);
	registerField(Fields::IrqRequest, "IrqRequest", 10, 1, 0);
	registerField(Fields::ReachTarget, "ReachTarget", 11, 1, 0);
	registerField(Fields::ReachOF, "ReachOF", 12, 1, 0);
}