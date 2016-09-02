#pragma once

#include <memory>

#include "Common/Global/Globals.h"

/*
Lists all of the 20 exceptions that can be encountered when running a PS2 system. For reference, see EE Core Users Manual page 94.
Due to macro issues caused by <math>, all of the exceptions have EX_ as a prefix.

See the ExceptionHandler class for how they are handled, and the EE Core Users Manual.

NOTE: Do NOT change the order - they are sync'd with the ExceptionHandler::ExceptionProperties[] array. If you change one you must reflect the changes in the other.
*/

// Forward declarations - see below for definitions.
struct TLBExceptionInfo_t;
struct IntExceptionInfo_t;
struct COPExceptionInfo_t;

class EECoreException_t
{
public:
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
	} const mExType;

	/*
	Pointers below are set when the relevant type of exception is generated - otherwise they are set to nullptr.
	*/
	std::shared_ptr<TLBExceptionInfo_t> mTLBExceptionInfo;
	std::shared_ptr<IntExceptionInfo_t> mIntExceptionInfo;
	std::shared_ptr<COPExceptionInfo_t> mCOPExceptionInfo;

	/*
	The simplified constructor, which sets the extra parameters above to nullptr.
	*/
	explicit EECoreException_t(ExType type);

	/*
	The additional constructor, which sets the extra paramters above to a COPY of what was provided.
	A copy is needed as the exception is a stateful object (depends on paramters at time of creation, not when handled).
	*/
	explicit EECoreException_t(ExType type, TLBExceptionInfo_t* TLBExceptionInfo, IntExceptionInfo_t* IntExceptionInfo, COPExceptionInfo_t* COPExceptionInfo);
};

/*
Parameters describe information needed for a TLB * exception to process.
These fields are not used for all TLB exception types, but are related to the TLB. Consult the ExceptionHandler for which TLB exceptions access what fields.
*/
struct TLBExceptionInfo_t
{
	u32 mPS2VirtualAddress;		  // The full virtual address that caused the exception.
	u32 mPageTableAddress;		  // The address of the OS's page table // TODO: Uhhhhh how do I know this???
	u32 mPS2VirtualAddress_HI_19; // High order 19-bits of the VA that caused the exception.
	u32 mASID;					  // ASID.
	s32 mTLBIndex;				  // TLB index pointing to a new entry.
};

/*
Parameters describe information needed for a interrupt exception to process.
All three paramters describe the interrupt signal that was generated. If only one signal, eg: Int7 was raised, then only mInt7 needs to be 1.
Any other signals unused must be set to 0 upon creation, as the exception handler sets them all at once.
*/
struct IntExceptionInfo_t
{
	u32 mInt2;
	u32 mInt3;
	u32 mInt7;
};

/*
Parameters desribe information needed for a coprocessor unusable exception to process.
The single parameter is set to the number of the coprocessor which was accessed & unavaliable at the time.
*/
struct COPExceptionInfo_t
{
	u32 mCOPUnusable;
};