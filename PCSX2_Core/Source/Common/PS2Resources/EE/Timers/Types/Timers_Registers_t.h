#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

/*
The Timer Mode register type. See EE Users Manual page 36.
Writing 1 to the Equal flag or Overflow flag will clear it (bits 10 and 11, behaves like a XOR write).

Needs a reference to the associated Count register as it will reset the value when CUE is set to 1.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used.
*/
class TimersRegisterMode_t : public BitfieldRegister32_t, public PS2ResourcesSubobject
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

	TimersRegisterMode_t(const PS2Resources_t *const PS2Resources, const u32 & timerID);

	void writeWordU(u32 value) override;

private:
	/*
	The timer ID that this object belongs to.
	*/
	const u32 mTimerID;
};

/*
The Timer Count register type. See EE Users Manual page 37.
Provides the increment function, which also wraps the u32 value around once overflow (> u16) happens (an internal flag is set).
Can also reset the counter.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used (but are used to check for overflow).
*/
class TimersRegisterCount_t : public Register32_t
{
public:
	TimersRegisterCount_t();

	void increment(u16 value);
	bool isOverflowed();
	void reset();

private:
	/*
	Internal overflow flag. Use isOverflowed() to get the status and to reset the flag.
	*/
	bool mIsOverflowed;
};