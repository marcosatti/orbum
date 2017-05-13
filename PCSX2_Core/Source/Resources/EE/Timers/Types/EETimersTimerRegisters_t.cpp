#include "stdafx.h"

#include "Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "Resources/EE/Timers/EETimers_t.h"

EETimersTimerRegister_COUNT_t::EETimersTimerRegister_COUNT_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites),
	mIsOverflowed(false),
	mPrescale(1),
	mPrescaleCount(0)
{
}

void EETimersTimerRegister_COUNT_t::increment(const System_t context, const size_t value)
{
	mPrescaleCount += value;
	while (mPrescaleCount >= mPrescale)
	{
		u32 temp = readWord(context) + static_cast<u32>(value);

		if (temp > Constants::VALUE_U16_MAX)
		{
			// Set overflow flag and wrap value around.
			mIsOverflowed = true;
			temp = temp % Constants::VALUE_U16_MAX;
		}

		writeWord(context, temp);
		mPrescaleCount -= mPrescale;
	}
}

bool EETimersTimerRegister_COUNT_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void EETimersTimerRegister_COUNT_t::reset(const System_t context)
{
	writeWord(context, 0);
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

EETimersTimerRegister_MODE_t::EETimersTimerRegister_MODE_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<EETimersTimerRegister_COUNT_t> & count) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites),
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

void EETimersTimerRegister_MODE_t::writeWord(const System_t context, const u32 value)
{
	// Clear bits 10 and 11 (0xC00) when a 1 is written to them.
	u32 temp = value;
	if (context == System_t::EECore)
	{
		u32 regValue = readWord(context);
		temp = (regValue & 0xFFFFF3FF) | ((regValue & 0xC00) & (~(value & 0xC00)));
	}
	
	BitfieldRegister32_t::writeWord(context, temp);
	
	// Test if the CUE flag is 1 - need to reset the associated Count register if set.
	if (context == System_t::EECore)
	{
		if (getFieldValue(context, Fields::CUE))
			mCount->reset(context);
	}
}

bool EETimersTimerRegister_MODE_t::isGateHBLNKSpecial(const System_t context) const
{
	return ((getFieldValue(context, Fields::CLKS) == 3) && (getFieldValue(context, Fields::GATS) == 0));
}

ClockSource_t EETimersTimerRegister_MODE_t::getClockSource() const
{
	return mClockSource;
}

void EETimersTimerRegister_MODE_t::handleClockSourceUpdate(const System_t context)
{
	if (getFieldValue(context, Fields::CLKS) == 0x3)
	{
		mClockSource = ClockSource_t::HBlankClock;
	}
	else
	{
		mClockSource = ClockSource_t::EEBusClock;

		// Set prescale.
		if (getFieldValue(context, Fields::CLKS) == 0x1)
			mCount->setPrescale(16);
		else if (getFieldValue(context, Fields::CLKS) == 0x2)
			mCount->setPrescale(256);
	}
}
