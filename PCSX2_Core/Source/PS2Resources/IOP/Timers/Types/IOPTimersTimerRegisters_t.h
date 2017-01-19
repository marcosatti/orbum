#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

class IOPTimersTimerRegister_COUNT_t; // Forward Decl - see below.

/*
The Timer Mode register type.
*/
class IOPTimersTimerRegister_MODE_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		// TODO: fill in.
	};

	IOPTimersTimerRegister_MODE_t(const std::shared_ptr<IOPTimersTimerRegister_COUNT_t> & count);

private:
	/*
	// TODO: fill in.
	*/
	std::shared_ptr<IOPTimersTimerRegister_COUNT_t> mCount;
};

/*
The Timer Count register type.
Provides the increment function, which also wraps the u32 value around once overflow (> u16) happens (an internal flag is set).
Can also reset the counter.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used (but are used to check for overflow).
*/
class IOPTimersTimerRegister_COUNT_t : public Register32_t
{
public:
	IOPTimersTimerRegister_COUNT_t();

	void increment(u16 value);
	bool isOverflowed();
	void reset();

private:
	/*
	Internal overflow flag. Use isOverflowed() to get the status and to reset the flag.
	*/
	bool mIsOverflowed;
};