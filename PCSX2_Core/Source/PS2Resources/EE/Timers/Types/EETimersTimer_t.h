#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class EETimersTimerRegister_MODE_t;
class EETimersTimerRegister_COUNT_t;
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
	The MODE, COUNT and COMP registers are always defined for each timer, and HOLD only for timers 0 and 1.
	COUNT must be initalised before MODE due to dependency.
	*/
	std::shared_ptr<EETimersTimerRegister_COUNT_t> COUNT;
	std::shared_ptr<EETimersTimerRegister_MODE_t>  MODE;
	std::shared_ptr<Register32_t>                  COMP;
	std::shared_ptr<Register32_t>                  HOLD;
};
