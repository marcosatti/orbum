#include "stdafx.h"

#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "PS2Resources/EE/Timers/EETimers_t.h"

EETimersTimerRegister_Mode_t::EETimersTimerRegister_Mode_t(const std::shared_ptr<EETimersTimerRegister_Count_t> & count) :
	mCount(count)
{
	registerField(Fields::CLKS, "CLKS", 0, 2, 0);
	registerField(Fields::GATE, "GATE", 2, 1, 0);
	registerField(Fields::GATS, "GATS", 3, 1, 0);
	registerField(Fields::GATM, "GATM", 4, 2, 0);
	registerField(Fields::ZRET, "ZRET", 6, 1, 0);
	registerField(Fields::CUE, "CUE", 7, 1, 0);
	registerField(Fields::CMPE, "CMPE", 8, 1, 0);
	registerField(Fields::OVFE, "OVFE", 9, 1, 0);
	registerField(Fields::EQUF, "EQUF", 10, 1, 0);
	registerField(Fields::OVFF, "OVFF", 11, 1, 0);
}

void EETimersTimerRegister_Mode_t::writeWordU(u32 value)
{
	// Clear bits 10 and 11 (0xC00) when a 1 is written to them.
	u32 originalValue = BitfieldRegister32_t::readWordU();
	u32 newValue = (~(value & 0xC00) & (originalValue & 0xC00)) | (value & ~0xC00);
	BitfieldRegister32_t::writeWordU(newValue);
	
	// Test if the CUE flag is 1 - need to reset the associated Count register if set.
	if (getFieldValue(Fields::CUE))
		mCount->reset();
}

EETimersTimerRegister_Count_t::EETimersTimerRegister_Count_t() :
	mIsOverflowed(false)
{
}

void EETimersTimerRegister_Count_t::increment(u16 value)
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

bool EETimersTimerRegister_Count_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void EETimersTimerRegister_Count_t::reset()
{
	writeWordU(0);
}