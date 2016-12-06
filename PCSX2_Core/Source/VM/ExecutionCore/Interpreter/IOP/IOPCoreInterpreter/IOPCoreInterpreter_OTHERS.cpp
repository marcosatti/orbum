#include "stdafx.h"

#include <stdexcept>

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"

void IOPCoreInterpreter::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
	Exceptions->setException(IOPCoreException_t(ExType::EX_BREAK));
}

void IOPCoreInterpreter::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
	Exceptions->setException(IOPCoreException_t(ExType::EX_SYSTEMCALL));
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
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;
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
