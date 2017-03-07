#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Types/ClockSource_t.h"

/*
The base Timer Count register type.
Subclasses are provided for 16-bit (default) mode (for timers 0 -> 2) or 32-bit (word) mode (for timers 3 -> 5).
Upon hitting overflow conditions (either in 16-bit or 32-bit mode), the value is wrapped around and an internal flag is set.
The flag can be checked with isOverflowed().
*/
class IOPTimersTimerRegister_COUNT_t : public Register32_t
{
public:
	IOPTimersTimerRegister_COUNT_t(const char * mnemonic);

	/*
	Increments the timer by the amount specified (controlling prescalling when required).
	Updates the overflow status.
	*/
	virtual void increment(u16 value) = 0;

	/*
	Returns if the register has overflowed or not, and resets the flag.
	*/
	bool isOverflowed();

	/*
	Resets the count to 0.
	*/
	void reset();

	/*
	Sets the prescale (ie: needs x amount before 1 is added to the count).
	*/
	void setPrescale(const int prescale);

protected:
	/*
	Internal overflow flag. Use isOverflowed() to get the status and to reset the flag.
	*/
	bool mIsOverflowed;

	/*
	Prescale functionality.
	*/
	int mPrescale;
	int mPrescaleCount;
};

/*
The 16-bit (hword) version of the IOP Timers Count register.
*/
class IOPTimersTimerRegister_HWORD_COUNT_t : public IOPTimersTimerRegister_COUNT_t
{
public:
	IOPTimersTimerRegister_HWORD_COUNT_t(const char * mnemonic);

	/*
	Checks for 16-bit overflow.
	*/
	void increment(u16 value) override;
};

/*
The 16-bit (word) version of the IOP Timers Count register.
*/
class IOPTimersTimerRegister_WORD_COUNT_t : public IOPTimersTimerRegister_COUNT_t
{
public:
	IOPTimersTimerRegister_WORD_COUNT_t(const char * mnemonic);

	/*
	Checks for 32-bit overflow.
	*/
	void increment(u16 value) override;
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

	IOPTimersTimerRegister_MODE_t(const char * mnemonic, const int timerIndex, const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count);

	/*
	When written to, will cache if the timer is enabled and the correct emulator clock source that the system logic should use.
	Also resets the count register on write.
	*/
	void writeHword(const Context_t& context, size_t arrayIndex, u16 value) override;
	void writeWord(const Context_t& context, u32 value) override;

	/*
	Returns if the timer is "enabled" by returning if either of the interrupt bits have been set (otherwise the timer is useless).
	*/
	bool isEnabled() const;

	/*
	Returns the cached emulator clock source.
	*/
	ClockSource_t getClockSource() const;

private:
	/*
	The timer index this mode register belongs to. Used to calculate the correct clock source when written to (cache the result).
	*/
	int mTimerIndex;

	/*
	Sets the internal clock source based on the register state.
	*/
	void handleClockSourceUpdate();

	/*
	Holds the result of if the timer is enabled, based on the interrupt bits set.
	*/
	bool mIsEnabled;

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