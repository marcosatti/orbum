#pragma once

#include <vector>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMBaseComponent.h"
#include "PS2Resources/Clock/Types/ClockSource_t.h"

/*
Base class for a PS2 system compnent - either triggered to run by a clock source (proactive), or by another PS2 system component (reactive).
*/

class VMMain;

class VMExecutionCoreComponent : public VMBaseComponent
{
public:
	explicit VMExecutionCoreComponent(VMMain * vmMain);
	virtual ~VMExecutionCoreComponent();

	/*
	For each execution core component, this is called as a way to initalise/reset the state.
	This does not have to be implemented for all components (ie: for reactive components).
	*/
	virtual void initalise();

	/*
	Executes a "cycle", in which the return value should be indicative of how many real world cycles would have happened (for that clock source).
	For example, in the EE Core, calling executionStep() will run an instruction instead of 1 real world cycle - usually an instruction is on the order of 10 cycles.
	This does not have to be implemented for all components (ie: for reactive components).

	It is possible to return a negative cycle count, which outside of the context of the EE Core (as this is the control, see below), 
	 means that this component requests more time to be run.
	*/
	virtual s64 executionStep(const ClockSource_t & clockSource);



	// Clock/Tick functionality. 
	// Note that the functionality doesn't have to be used, in the case of reactive components.
	// See Interpreter::exceutionStep() as an example on how it is used.
	// The EE Core should be used as the control component for timing all others.

	/*
	Gives this component the specified number of PS2CLK ticks that happened (adds).
	From this, use isTicked() to determine if the component should run.

	As the EE Core is used as the control in this emulator, PS2CLKTicks should always be equal to the number of EE Core cycles that just occurred.
	*/
	void produceTicks(const ClockSource_t & clockSource, const s64 & PS2CLKTicks);

	/*
	Determines if the component should be allowed to run, by checking the number of produced ticks against the 
	 clock ratio. Returns true if the number of produced ticks is higher than the clock speed ratio.

	This should be used in a while loop ( while(isTicked()) ), in conjuction with consumeTicks after the component has been allowed to run.
	This will make sure that the component is allowed to run for the approoriate time.
	*/
	bool isTicked(const ClockSource_t & clockSource) const;

	/*
	Consumes ticks from this component, for the given clock source.
	This decreases the number of ticks by the amount of ticks * ratio.

	It should be used after running executionStep(), with the ticks parameter equal to the return value of executionStep().
	*/
	void consumeTicks(const ClockSource_t & clockSource, const s64 & clockSourceTicks);

private:

	/*
	Records the number of PS2CLK ticks available for each clock source, used to control the timing of this component.
	See produceTicks(), isTicked() and consumeTicks() functions above on how these are used.
	*/
	s64 mClockTicks[static_cast<u32>(ClockSource_t::NUM_SOURCES)];

};

