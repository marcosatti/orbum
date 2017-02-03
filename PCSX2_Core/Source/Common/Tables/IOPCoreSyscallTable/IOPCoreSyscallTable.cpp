#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Tables/IOPCoreSyscallTable/IOPCoreSyscallTable.h"

const char * IOPCoreSyscallTable::getSyscallMnemonic(const u32& syscallNumber)
{
	if (!(syscallNumber < Constants::IOP::IOPCore::R3000::NUMBER_SYSCALLS))
		return UNKNOWN;

	return SYSCALL_MNEMONICS[syscallNumber];
}
