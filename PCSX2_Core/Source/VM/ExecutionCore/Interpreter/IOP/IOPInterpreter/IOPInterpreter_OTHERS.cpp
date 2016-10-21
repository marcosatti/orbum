#include "stdafx.h"

#include <stdexcept>

#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPMMUHandler/IOPMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/IOPExceptions_t.h"

void IOPInterpreter::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& Exceptions = getVM()->getResources()->IOP->Exceptions;
	Exceptions->setException(IOPException_t(IOPException_t::ExType::EX_BREAK));
}

void IOPInterpreter::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& Exceptions = getVM()->getResources()->IOP->Exceptions;
	Exceptions->setException(IOPException_t(IOPException_t::ExType::EX_SYSTEMCALL));
}

void IOPInterpreter::TLBP()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPInterpreter::TLBR()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPInterpreter::TLBWI()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPInterpreter::TLBWR()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPInterpreter::LWC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::SWC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::CFC0()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::CTC0()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::RFE()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::RTPS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::NCLIP()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::OP()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::DPCS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::INTPL()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::MVMVA()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::NCDS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::CDP()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::NCDT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::NCCS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::CC()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::NCS()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::NCT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::SQR()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::DCPL()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::DPCT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::AVSZ3()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::AVSZ4()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::RTPT()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::GPF()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::GPL()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::MFC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::CFC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::MTC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPInterpreter::CTC2()
{
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}
