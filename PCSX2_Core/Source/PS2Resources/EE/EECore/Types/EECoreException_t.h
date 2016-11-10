#pragma once

#include "Common/Global/Globals.h"

/*
Parameters describe information needed for a TLB * exception to process.
These fields are not used for all TLB exception types, but are related to the TLB. Consult the EECoreExceptionHandler for which TLB exceptions access what fields.
*/
struct TLBExceptionInfo_t
{
	u32 mPS2VirtualAddress;		  // The full virtual address that caused the exception.
	u32 mPageTableAddress;		  // The address of the OS's page table, which is set by the OS into the PageEntry register (this means just copy the value).
	u32 mPS2VirtualAddress_HI_19; // High order 19-bits of the VA that caused the exception.
	u32 mASID;					  // ASID.
	s32 mTLBIndex;				  // TLB index pointing to a new entry.
};

/*
Parameters describe information needed for a interrupt exception to process. Set the corresponding interrupt signal to 1.
All three paramters describe the interrupt signal that was generated. If only one signal, eg: Int1 was raised, then only mInt1 needs to be 1.
Any other signals unused must be set to 0 upon creation, as the exception handler sets them all at once.
*/
struct IntExceptionInfo_t
{
	u32 mInt1;     // INT1 signal from the DMAC.
	u32 mInt0;     // INT0 signal from the INTC.
	u32 mTimerInt; // Timer signal from the EE Core Timer (COP0.Count/Compare registers).
};

/*
Parameters desribe information needed for a coprocessor unusable exception to process.
The single parameter is set to the number of the coprocessor which was accessed & unavaliable at the time.
*/
struct COPExceptionInfo_t
{
	u32 mCOPUnusable;
};

/*
Lists all of the 20 exceptions that can be encountered when running the EECore. For reference, see EE Core Users Manual page 94.
Due to macro issues caused by <math>, all of the exceptions have EX_ as a prefix.

See the EECoreExceptionHandler class for how they are handled, and the EE Core Users Manual.

NOTE: Do NOT change the order - they are sync'd with the EECoreExceptionsTable::ExceptionProperties[] array which is from the order in the manual.
*/
struct EECoreException_t
{
	/*
	Construct a blank exception - needed by the EECoreExceptions_t class as a holder.
	*/
	explicit EECoreException_t();

	/*
	Describes what type of exception was generated. For the TLB (& address error), COP unavailable, and interrupt, extra details are required,
	 set by the additional constructor provided.
	*/
	enum class ExType {
		EX_RESET = 0,
		EX_NMI = 1,
		EX_PERFORMANCE_COUNTER = 2,
		EX_DEBUG = 3,
		EX_INTERRUPT = 4,
		EX_TLB_MODIFIED = 5,
		EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD = 6,
		EX_TLB_REFILL_STORE = 7,
		EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD = 8,
		EX_TLB_INVALID_STORE = 9,
		EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD = 10,
		EX_ADDRESS_ERROR_STORE = 11,
		EX_BUS_ERROR_INSTRUCTION_FETCH = 12,
		EX_BUS_ERROR_LOAD_STORE = 13,
		EX_SYSTEMCALL = 14,
		EX_BREAK = 15,
		EX_RESERVED_INSTRUCTION = 16,
		EX_COPROCESSOR_UNUSABLE = 17,
		EX_OVERFLOW = 18,
		EX_TRAP = 19
	} mExType;

	/*
	Additional information below is set when the relevant type of exception is generated - otherwise they are not used & invalid.
	*/
	TLBExceptionInfo_t mTLBExceptionInfo;
	IntExceptionInfo_t mIntExceptionInfo;
	COPExceptionInfo_t mCOPExceptionInfo;

	/*
	The simplified constructor, which sets the extra parameters above to empty.
	*/
	explicit EECoreException_t(const ExType & type);

	/*
	The additional constructor, which sets the extra paramters above to a COPY of what was provided.
	A copy is needed as the exception is a stateful object (depends on paramters at time of creation, not when handled).
	Not all parameters need to have a valid pointer - if nullptr is parsed, then it will create a blank exception parameter.
	*/
	explicit EECoreException_t(const ExType & type, const TLBExceptionInfo_t * TLBExceptionInfo, const IntExceptionInfo_t * IntExceptionInfo, const COPExceptionInfo_t * COPExceptionInfo);
};

