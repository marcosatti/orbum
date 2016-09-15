#pragma once

#include <memory>
#include <queue>

#include "Common/Global/Globals.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

using EECoreInstructionInfo_t = EECoreInstructionUtil::EECoreInstructionInfo_t;
struct TimerEvent_t;

/*
Class implements functionality for the EE timers TIMER0, TIMER1, TIMER2, TIMER3.
The associated registers are defined in the EE_t class, along with the other EE registers.
*/
class Timers_t 
{
public:
	explicit Timers_t();

	/*
	The functions below are for updating the timers based on when events occur, such as the PS2CLK (used instead of BUSCLK, see below), or the H-BLNK signals.
	They should be called from the EE Core (PS2CLK event) or the GS(?) (HBLNK event).

	Why is PS2CLK used instead of BUSCLK?
	Here PS2CLK means the cycle rate of the EE/EE Core (main cpu).
	In order to implement BUSCLK properly, we would need a dedicated client thread (or using some other method) responsible for counting at exactly the rate specified (147.456 MHz),
	 and somehow synchronise it with the rest of the emulator.
	This is a waste of resources and complexity, simply because we can approximate it with the EE Core instruction execution instead.
	With the EE/EE Core, its cycle rate is approximately twice that of the BUSCLK (294 MHz). Therefore, for every 2 cycles of the EE that occur, 1 cycle of the BUSCLK will occur.

	When an EE Core instruction is run, there are details about the number of cycles it takes to execute it on a real PS2 (accessed through EECoreInstructionInfo_t::mCycles), so we can
	 use this info to update the timers.
	Again - it is impossible to update it accurately without added complexity. The cycles parameter is a cummulative sum of the cycles needed to run an instruction.

	In the case of PS2CLK, when the number of PS2CLK's needed to generate a BUSCLK is reached, then an internal BUSCLK event will be generated (done by internal counter mNumPS2CLKEvents).

	TODO: Finish implementing the H-BLNK signal. For the H-BLNK signal, this is updated by the GS?
	*/
	u64 mNumPS2CLKEvents;
	void raiseTimerEventPS2CLK(const u32 & cycles);
	void raiseTimerEventHBLNK();

	/*
	The timers event queue, which holds information about a counter event, such as when a PS2CLK / 2 (BUSCLK) or H-BLNK clock happens.
	This should only be accessed by the TimerHandler class - the events in this queue must have already been checked for the gate condition (automatically done through the class' API functions).
	See the TimerHandler class for more information and how these events are processed.
	*/
	std::shared_ptr<std::queue<TimerEvent_t>> TimerEventQueue;
};

