#include "stdafx.h"

#include <stdexcept>

#include "Common/Types/Context_t.h"
#include "Common/Tables/IOPCoreSyscallTable/IOPCoreSyscallTable.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"

void IOPCoreInterpreter::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& Exceptions = getResources()->IOP->IOPCore->Exceptions;
	Exceptions->setException(IOPCoreException_t(ExType::EX_BREAK));
}

void IOPCoreInterpreter::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& Exceptions = getResources()->IOP->IOPCore->Exceptions;
	Exceptions->setException(IOPCoreException_t(ExType::EX_SYSTEMCALL));

#if DEBUG_LOG_SYSCALLS
	// Debug print the syscall mnemonic.
	// The convention is to store the syscall number in register $v0 ($2), then use the syscall instruction (the 'code' field within the syscall instruction is apparently unused).
	// When the syscall number is loaded into $v0, it is done so through
	//   ADDIU $v0, $0, number.
	// The IOP OS only defines handlers for syscall numbers 0 -> 15 (16 total). 
	u8 index = getResources()->IOP->IOPCore->R3000->GPR[2]->readByte(Context_t::IOP, 0);
	logDebug("IOPCore Syscall, number %d (%s).", index, IOPCoreSyscallTable::getSyscallMnemonic(index));
#endif
}

void IOPCoreInterpreter::TLBP()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter::TLBR()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter::TLBWI()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter::TLBWR()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter::LWC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::SWC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::CFC0()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::CTC0()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::RFE()
{
	// Pop the COP0.Status exception state.
	auto& COP0 = getResources()->IOP->IOPCore->COP0;
	COP0->Status->popExStack();
}

void IOPCoreInterpreter::RTPS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::NCLIP()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::OP()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::DPCS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::INTPL()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::MVMVA()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::NCDS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::CDP()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::NCDT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::NCCS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::CC()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::NCS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::NCT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::SQR()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::DCPL()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::DPCT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::AVSZ3()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::AVSZ4()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::RTPT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::GPF()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::GPL()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::MFC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::CFC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::MTC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter::CTC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}
