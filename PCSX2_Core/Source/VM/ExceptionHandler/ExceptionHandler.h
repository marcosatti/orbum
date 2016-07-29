#pragma once

#include "../../Common/Global/Globals.h"

#include "../Component Interfaces/VMExceptionHandlerComponent.h"
#include "../../Common/PS2 Types/PS2Exception/PS2Exception_t.h"

/*
TODO: Fill in documentation.
*/

class VMMain;

class ExceptionHandler : public VMExceptionHandlerComponent
{
public:
	/*
	ExceptionProperties_t describes the exception context parameters to be set when an exception of that type is handled.
	*/
	struct ExceptionProperties_t
	{
		PS2Exception_t::ExceptionType mExceptionType;
		u8 mLevel;
		s8 mExeCode;
		s8 mEXC2;
	};
	static constexpr ExceptionProperties_t ExceptionProperties[] = {
		{PS2Exception_t::EX_RESET, 2, -1, 0 },
		{PS2Exception_t::EX_NMI, 2, -1, 1 },
		{PS2Exception_t::EX_PERFORMANCE_COUNTER, 2, -1, 2 },
		{PS2Exception_t::EX_DEBUG, 2, -1, 4 },
		{PS2Exception_t::EX_INTERRUPT, 1, 0, -1 },
		{PS2Exception_t::EX_TLB_MODIFIED, 1, 1, -1 },
		{PS2Exception_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD, 1, 2, -1 },
		{PS2Exception_t::EX_TLB_REFILL_STORE, 1, 3, -1 },
		{PS2Exception_t::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD, 1, 2, -1 },
		{PS2Exception_t::EX_TLB_INVALID_STORE, 1, 3, -1 },
		{PS2Exception_t::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD, 1, 4, -1 },
		{PS2Exception_t::EX_ADDRESS_ERROR_STORE, 1, 5, -1 },
		{PS2Exception_t::EX_BUS_ERROR_INSTRUCTION_FETCH, 1, 6, -1 },
		{PS2Exception_t::EX_BUS_ERROR_LOAD_STORE, 1, 7, -1 },
		{PS2Exception_t::EX_SYSTEMCALL, 1, 8, -1 },
		{PS2Exception_t::EX_BREAK, 1, 9, -1 },
		{PS2Exception_t::EX_RESERVED_INSTRUCTION, 1, 10, -1 },
		{PS2Exception_t::EX_COPROCESSOR_UNUSABLE, 1, 11, -1 },
		{PS2Exception_t::EX_OVERFLOW, 1, 12, -1 },
		{PS2Exception_t::EX_TRAP, 1, 13, -1 }
	};

	explicit ExceptionHandler(const VMMain *const vmMain);

	void handleException(const PS2Exception_t& PS2Exception) override;

private:
	void handleException_L1(const ExceptionProperties_t & exceptionProperties) const;
	void handleException_L2(const ExceptionProperties_t & exceptionProperties) const;
};

