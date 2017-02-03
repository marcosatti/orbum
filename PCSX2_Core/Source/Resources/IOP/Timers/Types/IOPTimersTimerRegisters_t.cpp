#include "stdafx.h"

#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"

IOPTimersTimerRegister_COUNT_t::IOPTimersTimerRegister_COUNT_t(const char * mnemonic, const bool & wordMode) :
	Register32_t(mnemonic, false, false),
	mIsOverflowed(false),
	mWordMode(wordMode)
{
}

void IOPTimersTimerRegister_COUNT_t::increment(u16 value)
{
	u32 temp = readWord(RAW);

	// Test for 16/32-bit mode.
	if (!mWordMode)
	{
		temp = temp + value;
		if (temp > Constants::VALUE_U16_MAX)
		{
			// Set overflow flag and wrap value around.
			mIsOverflowed = true;
			temp = temp % Constants::VALUE_U16_MAX;
		}
	}
	else
	{
		u64 temp32 = temp + value;
		if (temp32 > Constants::VALUE_U32_MAX)
		{
			// Set overflow flag and wrap value around.
			mIsOverflowed = true;
			temp = temp32 % Constants::VALUE_U32_MAX;
		}
		else
		{
			temp = static_cast<u32>(temp32);
		}
	}
	
	writeWord(RAW, temp);
}

bool IOPTimersTimerRegister_COUNT_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void IOPTimersTimerRegister_COUNT_t::reset()
{
	writeWord(RAW, 0);
}

IOPTimersTimerRegister_MODE_t::IOPTimersTimerRegister_MODE_t(const char * mnemonic, const u8 & timerIndex, const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count) :
	BitfieldRegister32_t(mnemonic, false, false),
	mTimerIndex(timerIndex),
	mClockSource(ClockSource_t::IOPBus),
	mCount(count)
{
	registerField(Fields::SyncEnable, "SyncEnable", 0, 1, 0);
	registerField(Fields::SyncMode, "SyncMode", 1, 2, 0);
	registerField(Fields::ResetMode, "ResetMode", 3, 1, 0);
	registerField(Fields::IrqOnTarget, "IrqOnTarget", 4, 1, 0);
	registerField(Fields::IrqOnOF, "IrqOnOF", 5, 1, 0);
	registerField(Fields::IrqRepeat, "IrqRepeat", 6, 1, 0);
	registerField(Fields::IrqToggle, "IrqToggle", 7, 1, 0);
	registerField(Fields::ClockSrc, "ClockSrc", 8, 1, 0);
	registerField(Fields::Prescale0, "Prescale0", 9, 1, 0);
	registerField(Fields::IrqRequest, "IrqRequest", 10, 1, 0);
	registerField(Fields::ReachTarget, "ReachTarget", 11, 1, 0);
	registerField(Fields::ReachOF, "ReachOF", 12, 1, 0);
	registerField(Fields::Prescale1, "Prescale1", 13, 2, 0);
}

void IOPTimersTimerRegister_MODE_t::writeHword(const Context& context, size_t arrayIndex, u16 value)
{
	BitfieldRegister32_t::writeHword(context, arrayIndex, value);

	if (context != RAW)
	{
		mCount->reset();
		handleClockSourceUpdate();
	}
}

void IOPTimersTimerRegister_MODE_t::writeWord(const Context& context, u32 value)
{
	BitfieldRegister32_t::writeWord(context, value);

	if (context != RAW)
	{
		mCount->reset();
		handleClockSourceUpdate();
	}
}

ClockSource_t IOPTimersTimerRegister_MODE_t::getClockSource() const
{
	return mClockSource;
}

void IOPTimersTimerRegister_MODE_t::handleClockSourceUpdate()
{
	if (mTimerIndex > 5)
		throw std::runtime_error("Invalid IOP timer index to determine clock source!");
	
	// Sources are majorly different for each type of timer... no easy way of doing this... time for spaghetti code! TODO: maybe use a table for this?
	// Prescale works by needing that number of clock ticks for a timer tick to occur (works similar to EE timers).
	// For example with a prescale of 8, there would need to be 8 clocks (of the required source) before a timer tick occurs.
	if (mTimerIndex < 3)
	{
		// Check for Prescale8 (bit 9).
		if (getFieldValue(Fields::Prescale0) > 0)
		{
			throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
		}
		else
		{
			if (getFieldValue(Fields::ClockSrc) == 0)
			{
				mClockSource = ClockSource_t::IOPBus;
			}
			else
			{
				throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
			}
		}
	}
	else
	{
		// Check for Prescale8/16/256 (bits 13 and 14).
		if (getFieldValue(Fields::Prescale1) > 0)
		{
			throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
		}
		else
		{
			if (getFieldValue(Fields::ClockSrc) == 0)
			{
				mClockSource = ClockSource_t::IOPBus;
			}
			else
			{
				throw std::runtime_error("handleClockSourceUpdate() not fully implemented.");
			}
		}
	}
}
