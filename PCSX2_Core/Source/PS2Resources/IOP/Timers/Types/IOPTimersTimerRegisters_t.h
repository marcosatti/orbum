#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The Timer Count register type.
Provides the increment function, which also wraps the u32 value around once overflow (> u16) happens (an internal flag is set).
Can also reset the counter.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used (but are used to check for overflow).
*/
class IOPTimersTimerRegister_COUNT_t : public Register32_t
{
public:
	IOPTimersTimerRegister_COUNT_t(const char * mnemonic);

	void increment(u16 value);
	bool isOverflowed();
	void reset();

private:
	/*
	Internal overflow flag. Use isOverflowed() to get the status and to reset the flag.
	*/
	bool mIsOverflowed;
};

/*
The Timer Mode register type.
*/
class IOPTimersTimerRegister_MODE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 SyncEnable = 0;
		static constexpr u8 SyncMode = 1;
		static constexpr u8 ResetMode = 2;
		static constexpr u8 IrqOnTarget = 3;
		static constexpr u8 IrqOnOF = 4;
		static constexpr u8 IrqRepeat = 5;
		static constexpr u8 IrqToggle = 6;
		static constexpr u8 ClockSrc = 7;
		static constexpr u8 IrqRequest = 8;
		static constexpr u8 ReachTarget = 9;
		static constexpr u8 ReachOF = 10;
	};

	IOPTimersTimerRegister_MODE_t(const char * mnemonic, const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count);

private:
	/*
	A reference to the associated Count register, which is reset on certain conditions.
	*/
	std::shared_ptr<IOPTimersTimerRegister_COUNT_t> mCount;
};