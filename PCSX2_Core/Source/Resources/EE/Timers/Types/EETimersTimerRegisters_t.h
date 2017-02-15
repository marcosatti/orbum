#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

#include "Resources/Clock/Types/ClockSource_t.h"

/*
The Timer Count register type. See EE Users Manual page 37.
Provides the increment function, which also wraps the u32 value around once overflow (> u16) happens (an internal flag is set).
Can also reset the counter.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used (but are used to check for overflow).
*/
class EETimersTimerRegister_COUNT_t : public Register32_t
{
public:
	EETimersTimerRegister_COUNT_t(const char * mnemonic);

	void increment(u16 value);
	bool isOverflowed();
	void reset();
	void setPrescale(const int & prescale);

private:
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
The Timer Mode register type. See EE Users Manual page 36.
Writing 1 to the Equal flag or Overflow flag will clear it (bits 10 and 11).

Needs a reference to the associated Count register as it will reset the value when CUE is set to 1.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used.
*/
class EETimersTimerRegister_MODE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 CLKS = 0;
		static constexpr u8 GATE = 1;
		static constexpr u8 GATS = 2;
		static constexpr u8 GATM = 3;
		static constexpr u8 ZRET = 4;
		static constexpr u8 CUE = 5;
		static constexpr u8 CMPE = 6;
		static constexpr u8 OVFE = 7;
		static constexpr u8 EQUF = 8;
		static constexpr u8 OVFF = 9;
	};

	EETimersTimerRegister_MODE_t(const char * mnemonic, const std::shared_ptr<EETimersTimerRegister_COUNT_t> & count);

	/*
	Writing 1 to the Equal flag or Overflow flag will clear it (bits 10 and 11), 
	 will also reset the count register if CUE is 1 (both EE context only).
	*/
	void writeWord(const Context & context, u32 value) override;

	/*
	Returns if CLKS and GATS are both set to H-BLNK, which is used as a special condition.
	*/
	bool isGateHBLNKSpecial() const;

	/*
	Returns the cached emulator clock source.
	*/
	ClockSource_t getClockSource() const;

private:
	/*
	A reference to the associated Count register, which is reset when the CUE flag is set to 1.
	*/
	std::shared_ptr<EETimersTimerRegister_COUNT_t> mCount;

	/*
	Sets the internal clock source based on the register state.
	*/
	void handleClockSourceUpdate();

	/*
	Contains the emulation clock source updated through handleClockSourceUpdate().
	Retrieve through getClockSource().
	*/
	ClockSource_t mClockSource;
};

