#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class EETimersTimerRegister_Mode_t;
class EETimersTimerRegister_Count_t;
class Register32_t;

/*
A base type representing an EE Timers Timer.
See EE Users Manual page 35 for the list of registers declared forming this type.
If the timer contains a Hold register, set the constructor parameter to true. Hold is set to nullptr otherwise.
*/
class EETimersTimer_t
{
public:
	explicit EETimersTimer_t(const u32 & timerID, bool isHoldDefined);

	/*
	The ID of this timer. Used for debug.
	*/
	const u32 mTimerID;

	/*
	EE Timers timer registers.
	See EE Users Manual page 35.
	The Mode, Count and Compare registers are always defined for each timer, and Hold only for timers 0 and 1.
	COUNT must be initalised before MODE due to dependency.
	*/
	std::shared_ptr<EETimersTimerRegister_Count_t> Count;
	std::shared_ptr<EETimersTimerRegister_Mode_t>  Mode;
	std::shared_ptr<Register32_t>                  Compare;
	std::shared_ptr<Register32_t>                  Hold;
};
