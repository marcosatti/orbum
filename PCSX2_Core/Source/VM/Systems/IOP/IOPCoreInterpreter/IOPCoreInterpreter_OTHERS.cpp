#include "stdafx.h"

#include <stdexcept>

#include "Common/Global/Globals.h"
#include "Common/Tables/IOPCoreSyscallTable.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

void IOPCoreInterpreter_s::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	handleException(IOPCoreException_t::EX_BREAK);
}

void IOPCoreInterpreter_s::SYSCALL()
{
#if DEBUG_IOP_SYSCALL_LOG
	// Debug print the syscall mnemonic.
	// The convention is to store the syscall number in register $v0 ($2), then use the syscall instruction (the 'code' field within the syscall instruction is apparently unused).
	// When the syscall number is loaded into $v0, it is done so through
	//   ADDIU $v0, $0, number.
	// The IOP OS only defines handlers for syscall numbers 0 -> ??? (? total). TODO: figure out number of syscalls.
	u8 index = mIOPCore->R3000->GPR[2]->readByte(getContext(), 0);
	log(Debug, "IOPCore Syscall, number %d (%s) @ cycle = 0x%llX.", index, IOPCoreSyscallTable::getSyscallInfo(index)->mMnemonic, DEBUG_LOOP_COUNTER);
#endif

	// EXCEPTION(SYSCALL)
	handleException(IOPCoreException_t::EX_SYSTEMCALL);
}

void IOPCoreInterpreter_s::TLBP()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter_s::TLBR()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter_s::TLBWI()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter_s::TLBWR()
{
	throw std::runtime_error("IOP TLB instructions not implemented.");
}

void IOPCoreInterpreter_s::LWC2()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::SWC2()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::CFC0()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::CTC0()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::RFE()
{
	// Pop the COP0.Status exception state.
	mIOPCore->COP0->Status->popExceptionStack(getContext());
}

void IOPCoreInterpreter_s::RTPS()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::NCLIP()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::OP()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::DPCS()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::INTPL()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::MVMVA()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::NCDS()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::CDP()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::NCDT()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::NCCS()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::CC()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::NCS()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::NCT()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::SQR()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::DCPL()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::DPCT()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::AVSZ3()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::AVSZ4()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::RTPT()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::GPF()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::GPL()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::MFC2()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::CFC2()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::MTC2()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}

void IOPCoreInterpreter_s::CTC2()
{
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 opcode encountered (%s)!", __FILENAME__, __LINE__, __FUNCTION__);
#endif
}
