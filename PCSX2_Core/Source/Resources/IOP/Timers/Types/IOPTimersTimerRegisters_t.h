#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

#include "Resources/Clock/Types/ClockSource_t.h"

/*
The Timer Count register type.
The register can be set to 16-bit (default) mode (for timers 0 -> 2) or 32-bit (word) mode (for timers 3 -> 5).
Upon hitting overflow conditions (either in 16-bit or 32-bit mode), the value is wrapped around and an internal flag is set.
The flag can be checked with isOverflowed().
*/
class IOPTimersTimerRegister_COUNT_t : public Register32_t
{
public:
	IOPTimersTimerRegister_COUNT_t(const char * mnemonic, const bool & wordMode);

	/*
	Increments the timer by the amount specified while also updating the overflow status.
	*/
	void increment(u16 value);

	/*
	Returns if the register has overflowed or not, and resets the flag.
	*/
	bool isOverflowed();

	/*
	Resets the count to 0.
	*/
	void reset();

private:
	/*
	Internal overflow flag. Use isOverflowed() to get the status and to reset the flag.
	*/
	bool mIsOverflowed;

	/*
	Used to determine if the count register is in 16 or 32-bit mode.
	*/
	bool mWordMode;
};

/*
The Timer Mode register type.
The PS2SDK has some useful information: https://github.com/ps2dev/ps2sdk/blob/master/iop/kernel/include/timrman.h (carefull - the bit(s) column is 1-indexed, not 0-indexed!).
See also the No$PSX docs: http://problemkaputt.de/psx-spx.htm#timers.
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
		static constexpr u8 Prescale0 = 8;
		static constexpr u8 IrqRequest = 9;
		static constexpr u8 ReachTarget = 10;
		static constexpr u8 ReachOF = 11;
		static constexpr u8 Prescale1 = 12;
	};

	IOPTimersTimerRegister_MODE_t(const char * mnemonic, const u8 & timerIndex, const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count);

	/*
	When written to, will cache the correct emulator clock source that the system logic should use.
	Use getClockSource() to get the emulator clock source.
	Also resets the count register.
	*/
	void writeHword(const Context& context, size_t arrayIndex, u16 value) override;
	void writeWord(const Context& context, u32 value) override;

	/*
	Returns the cached emulator clock source.
	*/
	ClockSource_t getClockSource() const;

private:
	/*
	The timer index this mode register belongs to. Used to calculate the correct clock source when written to (cache the result).
	*/
	u8 mTimerIndex;

	/*
	Sets the internal clock source based on the register state.
	*/
	void handleClockSourceUpdate();

	/*
	Contains the emulation clock source updated through handleClockSourceUpdate().
	Retrieve through getClockSource().
	*/
	ClockSource_t mClockSource;

	/*
	A reference to the associated Count register, which is reset on certain conditions.
	*/
	std::shared_ptr<IOPTimersTimerRegister_COUNT_t> mCount;
};