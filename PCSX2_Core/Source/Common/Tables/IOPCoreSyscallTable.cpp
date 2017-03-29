#include "stdafx.h"

#include "Common/Tables/IOPCoreSyscallTable.h"

const IOPCoreSyscallTable::IOPCoreSyscallInfo_t * IOPCoreSyscallTable::getSyscallInfo(const int syscallNumber)
{
	return &IOPCORE_SYSCALL_TABLE[syscallNumber];
}