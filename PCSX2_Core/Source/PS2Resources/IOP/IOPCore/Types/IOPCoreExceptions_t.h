#pragma once

#include <memory>

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

class IOPCoreCOP0_t;

/*
IOP Core exception state functionality.
*/
class IOPCoreExceptions_t
{
public:
	explicit IOPCoreExceptions_t(const std::shared_ptr<IOPCoreCOP0_t> & cop0);

	/*
	TODO: Check thread safety (std::mutex). Also, add in prioritisation through the setException() function.
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

	/*
	Pointer to the IOP Core COP0 coprocessor, needed for the Status register.
	*/
	std::shared_ptr<IOPCoreCOP0_t> mCOP0;
};
