#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"

/*
TimerHandler updates TIMER0, TIMER1, TIMER2, TIMER3 as defined in the EE Users Manual, starting on page 33.
*/

class TimerHandler : VMExecutionCoreComponent
{
public:
	explicit TimerHandler(const VMMain* const vmMain);
	~TimerHandler();
	
	/*
	Update timers. Called on every loop of the emulator, which checks the TimerEventQueue for any pending events and updates the timers accordingly.
	If the gate function on any of the timers are enabled, it is checked here.
	*/
	void updateTimers();
};

