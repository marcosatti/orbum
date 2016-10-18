#pragma once

#include <vector>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMBaseComponent.h"
#include "Common/PS2Resources/Clock/Types/ClockSource_t.h"

/*
TODO: Fill in documentation.
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

	For example, in the EE Core, calling executionStep() will run an instruction instead of 1 cycle.
	In this case, the return value indicates the number of cycles that instruction took to execute in the real world (as PS2CLK's).
	*/
	virtual s64 executionStep(const ClockSource_t & clockSource);



	// Clock/Tick functionality. 
	// Note that the functionality doesn't have to be used, in which case the values do not matter.
	// See Interpreter::exceutionStep() for how it is used.

	/*
	Gives this component the specified number of PS2CLK ticks that happened (adds).
	From this, use isTicked() to determine if the component should run.

	As the EE Core is used as the control in this emulator, ticksPS2CLK should always be equal to the number of EE Core 
	 cycles that just occurred.
	*/
	void produceTicks(const s64 & PS2CLKTicks);

	/*
	Determines if the component should be allowed to run, by checking the number of produced ticks against the 
	 clock ratio. Returns true if the number of produced ticks is higher than the clock speed ratio.

	This should be used in a while loop ( while(isTicked()) ), in conjuction with consumeTicks after the component has been allowed to run.
	This will make sure that the component is allowed to run for the approoriate time instead of just once.
	*/
	bool isTicked(const ClockSource_t & clockSource) const;

	/*
	Consumes ticks from this component, for the given clock source.
	This decreases the number of ticks by the amount of ticks * ratio.

	It should be used after running executionStep(), with the ticks parameter equal to the return value of executionStep().
	*/
	void consumeTicks(const ClockSource_t & clockSource, const s64 & clockSourceTicks);

	/*
	Returns a list of clock sources that this component is "subscribed" to (in an event fashion).
	The values in the list returned can be used in the executionStep(), isTicked() and consumeTicks() functions as parameters.
	*/
	virtual const std::vector<ClockSource_t> & getClockSources() = 0;

private:

	/*
	Records the number of PS2CLK's for each clock source available.
	Not all of the array will be used, only the clock sources listed by getClockSources() will be used.

	The values recorded can be used to check if the component should run.
	See produceTicks(), isTicked() and consumeTicks() functions.
	*/
	s64 mNumTicksPS2CLK[static_cast<u32>(ClockSource_t::NUMBER_SOURCES)];

};

