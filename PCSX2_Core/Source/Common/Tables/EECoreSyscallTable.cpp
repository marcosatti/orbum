#include "stdafx.h"

#include "Common/Tables/EECoreSyscallTable.h"

const EECoreSyscallTable::EECoreSyscallInfo_t * EECoreSyscallTable::getSyscallInfo(const int syscallNumber)
{
	return &EECORE_SYSCALL_TABLE[syscallNumber];
}