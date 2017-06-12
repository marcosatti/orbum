#pragma once

#include <map>
#include <utility>
#include <memory>

#include <boost/lockfree/spsc_queue.hpp>

#include "Common/Types/System/Context_t.h"
#include "Common/Types/System/Event_t.h"
#include "Common/Types/Util/EnumMap_t.h"

/*
Events_t helps with synchronisation across components.
Any events for systems are held in an event queue, which are handled when they run.
The majority of events come from clock ticks, in which separate functionality is provided for easier event generation.
TODO: Pixel clock not handled yet - not sure what the IOP bios expects yet in terms of granularity/accuracy.
      Generating a pixel clock event directly in the CRTC on every pixel might be too intensive.
TODO: CRTC clock speed needs to be dynamic to support different refresh rates - look into for later. For now, assume NTSC (480i) defaults.
*/
class Events_t
{
public:
	Events_t();

	///////////////////////////////
	// Event Queue Functionality //
	///////////////////////////////

	/*
	Returns a mutable reference to the system event queue. Systems use this to process events.
	Events are added through the clock tick state functionality, or through addEvent(), which can then be popped off from the queue.

	Although there may be multiple producers within the emulator (VM and CRTC), they will not be running at the same time, meaning using a SPSC queue for this is ok.
	There should only ever be one consumer (the system).
	*/
	std::shared_ptr<boost::lockfree::spsc_queue<Event_t>> & getEvents(const Context_t system);

	/*
	Adds an event to the given systems queue.
	*/
	void addEvent(const Context_t system, const Event_t & event);

	/////////////////////////////////////////////////////////////////////////
	// Clock Tick State Functionality                                      //
	// Note: this is used by the VM, put here to support saving the state. //
	/////////////////////////////////////////////////////////////////////////

	/*
	Sets the system biases, used when adding clock ticks to a source.
	When ticks are added to a system, the ticks are multiplied by the bias (regardless of which clock source it is for).
	*/
	void setClockBias(const std::map<Context_t, double> & biases);

	/*
	Given a time delta (in ms), adds ticks to the internal clock state by multiplying against the clock speed and bias, for all systems.
	Once ticks > 1.0 have been reached for a system, they are subtracted from the state and added to that system's event queue.
	*/
	void addClockTime(const double timeDelta);

private:
	/*
	Event state.
	*/
	EnumMap_t<Context_t, std::shared_ptr<boost::lockfree::spsc_queue<Event_t>>> mSystemEvents;

	/*
	System clock/tick state map.
	Pair.first = bias multiplier, pair.second = clock ticks.
	*/
	EnumMap_t<Context_t, std::pair<double, double>> mSystemClockTicks;

	// DEBUG: time elapsed counter (us).
	double DEBUG_TIME_ELAPSED_CURRENT;
	double DEBUG_TIME_ELAPSED_LAST;
};

