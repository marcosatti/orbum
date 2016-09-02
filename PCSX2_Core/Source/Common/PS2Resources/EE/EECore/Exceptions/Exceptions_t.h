#pragma once

#include <memory>
#include <queue>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class PS2Resources_t;
class EECoreException_t;

class Exceptions_t : public PS2ResourcesSubobject
{
public:
	explicit Exceptions_t(const PS2Resources_t* const PS2Resources);

	// Global exception functionality.
	/*
	Exception Queue. Any exceptions generated should come through here.
	This is also thread safe and can be accessed by other threads.
	TODO: May need to look into prioritisation (extend the std::queue class).

	For queuing an exception, use the push() function, for getting the oldest exception (FIFO queue), use front() followed by pop().
	See the EE Core execution core's for how they are used.
	*/
	std::shared_ptr<std::queue<EECoreException_t>> ExceptionQueue;
};
