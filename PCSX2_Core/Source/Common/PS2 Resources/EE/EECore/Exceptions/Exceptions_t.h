#pragma once

#include <memory>
#include <queue>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ToggleRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/PS2 Resources/EE/EECore/Exceptions/Types/TLBExceptionInfo_t.h"
#include "Common/Types/PS2Exception/PS2Exception_t.h"

class Exceptions_t
{
public:
	// Global state functionality.
	/*
	Exception Queue. Any exceptions generated should come through here.
	This is also thread safe and can be accessed by other threads.
	TODO: finish implementing exception queue. May need to look into prioritisation (extend the std::queue class).
	*/
	std::shared_ptr<std::queue<PS2Exception_t>> ExceptionQueue = std::make_shared<std::queue<PS2Exception_t>>();

	// "INTERRUPT" exception functionality.
	/*
	ToggleRegister32_t's below are used to store the state of EXTERNAL interrupt requests.
	They are named with IRQ and suffixed with the number corresponding to the COP0.Status.IM[7, 3, 2] fields.
	These are used for communication between components, for example the INTC component. Whenever an EX_INTERRUPT exception is generated, 
	 the handler will check these values to determine what type of interrupt it was.
	TODO: Update comments next to the IRQ's, when proper names are found for them.
	*/
	std::shared_ptr<ToggleRegister32_t> IRQ2 = std::make_shared<ToggleRegister32_t>(); // Status of the Int[1] signal.
	std::shared_ptr<ToggleRegister32_t> IRQ3 = std::make_shared<ToggleRegister32_t>(); // Status of the Int[0] signal.
	std::shared_ptr<ToggleRegister32_t> IRQ7 = std::make_shared<ToggleRegister32_t>(); // Status of the internal timer interrupt signal.

	// "COPROCESSOR UNAVAILABLE" exception functionality.
	/*
	ToggleRegister32_t below describes which coprocessor was unavailable at the time the exception was raised.
	*/
	std::shared_ptr<Register32_t> COPUnavailable = std::make_shared<Register32_t>();

	// "TLB *" & "ADDRESS ERROR" exception functionality.
	/*
	TLBExceptionInfo_t below holds information needed for the types of TLB and address error exceptions.
	*/
	std::shared_ptr<TLBExceptionInfo_t> TLBExceptionInfo = std::make_shared<TLBExceptionInfo_t>();
};
