#pragma once

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/IOP/IOPExceptions/Types/IOPException_t.h"

using ExType = IOPException_t::ExType;
class PS2Resources_t;

/*
IOP exception state functionality.
*/
class IOPExceptions_t : public PS2ResourcesSubobject
{
public:
	explicit IOPExceptions_t(const PS2Resources_t* const PS2Resources);

	/*
	TODO: Check thread safety (std::atomic?). Also, add in prioritisation through the setException() function.
	The EE Core exception functionality.
	Use setException() to indicate that an exception occurred.

	Within the EE Core, a call should be made to hasExceptionOccurred(), and if true, details can be retrieved by getException().
	A call to hasExceptionOccurred() will reset the exception state (ie: returns false on next call, if no other exception occurred during the calls).
	*/
	bool hasExceptionOccurred();
	const IOPException_t & getException() const;
	void setException(const IOPException_t & exception);

private:
	/*
	EE Core Exception state, see above.
	*/
	bool ExceptionOccurred;
	IOPException_t Exception;
};
