#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Tables/EECoreSyscallTable/EECoreSyscallTable.h"

const char * EECoreSyscallTable::getSyscallMnemonic(const u32& syscallNumber)
{
	if (!(syscallNumber < PS2Constants::EE::EECore::R5900::NUMBER_SYSCALLS))
		return UNKNOWN;

	return SYSCALL_MNEMONICS[syscallNumber];
}
