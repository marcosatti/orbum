#pragma once

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

using ExType = IOPCoreException_t::ExType;
class PS2Resources_t;

/*
IOP Core exception state functionality.
TODO: Finish implementing. Currently doesnt check the Status.IM bits etc.
*/
class IOPCoreExceptions_t : public PS2ResourcesSubobject
{
public:
	explicit IOPCoreExceptions_t(const PS2Resources_t* const PS2Resources);

	/*
	TODO: Check thread safety (std::atomic?). Also, add in prioritisation through the setException() function.
	The IOP Core exception functionality.
	Use setException() to indicate that an exception occurred.

	Within the IOP Core, a call should be made to hasExceptionOccurred(), and if true, details can be retrieved by getException().
	A call to hasExceptionOccurred() will reset the exception state (ie: returns false on next call, if no other exception occurred during the calls).
	*/
	bool hasExceptionOccurred();
	const IOPCoreException_t & getException() const;
	void setException(const IOPCoreException_t & exception);

private:
	/*
	IOP Core Exception state, see above.
	*/
	bool ExceptionOccurred;
	IOPCoreException_t Exception;
};
