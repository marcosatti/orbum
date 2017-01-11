#include "stdafx.h"

#include "Common/Tables/IOPCoreExceptionsTable/IOPCoreExceptionsTable.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPCoreExceptions_t::IOPCoreExceptions_t(const std::shared_ptr<IOPCoreCOP0_t>& cop0) :
	ExceptionOccurred(false),
	Exception(),
	mCOP0(cop0)
{
}

bool IOPCoreExceptions_t::hasExceptionOccurred()
{
	bool temp = ExceptionOccurred;
	ExceptionOccurred = false;
	return temp;
}

const IOPCoreException_t& IOPCoreExceptions_t::getException() const
{
	return Exception;
}

void IOPCoreExceptions_t::setException(const IOPCoreException_t& exception)
{
	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows PCSX2's code and http://problemkaputt.de/psx-spx.htm (no$psx tech docs).

	// Determines if the exception should be raised at the end.
	bool masked = mCOP0->Status->isExceptionsMasked();

	// If its from an interrupt, need to check the interrupt source is not masked.
	if (exception.mExType == ExType::EX_INTERRUPT)
	{
		if (mCOP0->Status->isInterruptsMasked() || mCOP0->Status->isIRQMasked(exception.mIntExceptionInfo.mIRQLine))
			masked = true;
	}
	
	// TODO: need to add NMI checks here (always raised)?
	// if (exception.mExType == of NMI type (ie: reset))
	//     masked = false;

	// Finally raise the exception if not masked.
	if (!masked)
	{
		Exception = exception;
		ExceptionOccurred = true; 
	}
	else
	{
		//logDebug("IOP Exception raised (%s), but was masked!", IOPCoreExceptionsTable::getExceptionInfo(exception.mExType)->mMnemonic);
	}
}
