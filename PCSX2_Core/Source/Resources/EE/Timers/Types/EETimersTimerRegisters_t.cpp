#include "stdafx.h"

#include "Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "Resources/EE/Timers/EETimers_t.h"

EETimersTimerRegister_COUNT_t::EETimersTimerRegister_COUNT_t(const char * mnemonic) :
	Register32_t(mnemonic),
	mIsOverflowed(false),
	mPrescale(1),
	mPrescaleCount(0)
{
}

void EETimersTimerRegister_COUNT_t::increment(u16 value)
{
	mPrescaleCount += value;
	while (mPrescaleCount >= mPrescale)
	{
		u32 temp = readWord(RAW) + value;

		if (temp > Constants::VALUE_U16_MAX)
		{
			// Set overflow flag and wrap value around.
			mIsOverflowed = true;
			temp = temp % Constants::VALUE_U16_MAX;
		}

		writeWord(RAW, temp);
		mPrescaleCount -= mPrescale;
	}
}

bool EETimersTimerRegister_COUNT_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void EETimersTimerRegister_COUNT_t::reset()
{
	writeWord(RAW, 0);
}

void EETimersTimerRegister_COUNT_t::setPrescale(const int prescale)
{
	// Prescale can only be 1 (no prescale) or above.
	if (prescale > 0)
		mPrescale = prescale;
	else
		mPrescale = 1;

	mPrescaleCount = 0;
}

EETimersTimerRegister_MODE_t::EETimersTimerRegister_MODE_t(const char * mnemonic, const std::shared_ptr<EETimersTimerRegister_COUNT_t> & count) :
	BitfieldRegister32_t(mnemonic, false, false),
	mCount(count),
	mClockSource(ClockSource_t::EEBusClock)
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

void EETimersTimerRegister_MODE_t::writeWord(const Context_t & context, u32 value)
{
	// Clear bits 10 and 11 (0xC00) when a 1 is written to them.
	if (context == EE)
	{
		u32 regValue = readWord(context);
		value = (regValue & 0xFFFFF3FF) | ((regValue & 0xC00) & (~(value & 0xC00)));
	}
	
	BitfieldRegister32_t::writeWord(context, value);
	
	// Test if the CUE flag is 1 - need to reset the associated Count register if set.
	if (context == EE)
	{
		if (getFieldValue(Fields::CUE))
			mCount->reset();
	}
}

bool EETimersTimerRegister_MODE_t::isGateHBLNKSpecial() const
{
	return ((getFieldValue(Fields::CLKS) == 3) && (getFieldValue(Fields::GATS) == 0));
}

ClockSource_t EETimersTimerRegister_MODE_t::getClockSource() const
{
	return mClockSource;
}

void EETimersTimerRegister_MODE_t::handleClockSourceUpdate()
{
	if (getFieldValue(Fields::CLKS) == 0x3)
	{
		mClockSource = ClockSource_t::HBlankClock;
	}
	else
	{
		mClockSource = ClockSource_t::EEBusClock;

		// Set prescale.
		if (getFieldValue(Fields::CLKS) == 0x1)
			mCount->setPrescale(16);
		else if (getFieldValue(Fields::CLKS) == 0x2)
			mCount->setPrescale(256);
	}
}
