#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"

#include "Resources/Ee/Timers/EeTimersUnitRegisters.hpp"

/// A base type representing an EE Timers Timer.
/// See EE Users Manual page 35.	
/// The MODE, COUNT and COMP registers are always defined for each timer.
class EeTimersUnit_Base
{
public:
	EeTimersUnit_Base(const int timer_id) :
		timer_id(timer_id)
	{
	}

	int timer_id;

	EeTimersUnitRegister_Count count;
	EeTimersUnitRegister_Mode  mode;
	SizedWordRegister          compare;
};

/// EE Timer with HOLD register, for timers 0 and 1.
class EeTimersUnit_Hold : public EeTimersUnit_Base
{
public:
	EeTimersUnit_Hold(const int timer_id) :
		EeTimersUnit_Base(timer_id)
	{
	}

	SizedWordRegister hold;
};