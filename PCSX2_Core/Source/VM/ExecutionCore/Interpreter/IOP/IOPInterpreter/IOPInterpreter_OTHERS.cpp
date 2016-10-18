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
}

void IOPInterpreter::SWC2()
{
}

void IOPInterpreter::CFC0()
{
}

void IOPInterpreter::CTC0()
{
}

void IOPInterpreter::RFE()
{
}

void IOPInterpreter::RTPS()
{
}

void IOPInterpreter::NCLIP()
{
}

void IOPInterpreter::OP()
{
}

void IOPInterpreter::DPCS()
{
}

void IOPInterpreter::INTPL()
{
}

void IOPInterpreter::MVMVA()
{
}

void IOPInterpreter::NCDS()
{
}

void IOPInterpreter::CDP()
{
}

void IOPInterpreter::NCDT()
{
}

void IOPInterpreter::NCCS()
{
}

void IOPInterpreter::CC()
{
}

void IOPInterpreter::NCS()
{
}

void IOPInterpreter::NCT()
{
}

void IOPInterpreter::SQR()
{
}

void IOPInterpreter::DCPL()
{
}

void IOPInterpreter::DPCT()
{
}

void IOPInterpreter::AVSZ3()
{
}

void IOPInterpreter::AVSZ4()
{
}

void IOPInterpreter::RTPT()
{
}

void IOPInterpreter::GPF()
{
}

void IOPInterpreter::GPL()
{
}

void IOPInterpreter::MFC2()
{
}

void IOPInterpreter::CFC2()
{
}

void IOPInterpreter::MTC2()
{
}

void IOPInterpreter::CTC2()
{
}
