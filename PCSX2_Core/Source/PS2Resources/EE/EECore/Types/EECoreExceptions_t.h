#pragma once

#include <memory>

#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

using ExType = EECoreException_t::ExType;
class EECoreCOP0_t;

/*
EE Core exceptions state functionality.
*/
class EECoreExceptions_t
{
public:
	explicit EECoreExceptions_t(const std::shared_ptr<EECoreCOP0_t> & cop0);

	/*
	TODO: Check thread safety (std::atomic?). Also, add in prioritisation through the setException() function.
	The EE Core exception functionality.
	Use setException() to indicate that an exception occurred. It will check that the appropriate COP0 bits are set before reflecting the exception.
	If the exception is masked, it is silently discarded.

	Within the EE Core, a call should be made to hasExceptionOccurred(), and if true, details can be retrieved by getException().
	A call to hasExceptionOccurred() will reset the exception state (ie: returns false on next call, if no other exception occurred during the calls).
	*/
	bool hasExceptionOccurred();
	const EECoreException_t & getException() const;
	void setException(const EECoreException_t & exception);

private:
	/*
	EE Core Exception state, see above.
	*/
	bool ExceptionOccurred;
	EECoreException_t Exception;

	/*
	Pointer to the EE Core COP0 coprocessor, needed for the Status register.
	*/
	const std::shared_ptr<EECoreCOP0_t> COP0;
};
