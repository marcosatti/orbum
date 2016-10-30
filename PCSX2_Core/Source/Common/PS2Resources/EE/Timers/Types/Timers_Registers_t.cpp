#include "stdafx.h"

#include "Common/PS2Resources/EE/Timers/Types/Timers_Registers_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/Timers/Timers_t.h"

TimersRegisterMode_t::TimersRegisterMode_t(const PS2Resources_t *const PS2Resources, const u32 & timerID) :
	PS2ResourcesSubobject(PS2Resources),
	mTimerID(timerID)
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

void TimersRegisterMode_t::writeWordU(u32 value)
{
	// Clear bits 10 and 11 (0xC00) when a 1 is written to them.
	u32 originalValue = Register32_t::readWordU();
	u32 newValue = ((value & 0xC00) ^ (originalValue & 0xC00)) | (value & ~0xC00);
	Register32_t::writeWordU(newValue);

	// Test if the CUE flag is 1 - need to reset the associated Count register if set.
	if (value & 0x80)
		getRootResources()->EE->Timers->TimerRegisters[mTimerID].Count->reset();
}

TimersRegisterCount_t::TimersRegisterCount_t() :
	mIsOverflowed(false)
{
}

void TimersRegisterCount_t::increment(u16 value)
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

bool TimersRegisterCount_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void TimersRegisterCount_t::reset()
{
	writeWordU(0);
}