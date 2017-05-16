#include "Common/Tables/EECoreSyscallTable.h"

const EECoreSyscallTable::EECoreSyscallInfo_t * EECoreSyscallTable::getInfo(const int syscallNumber)
{
	return &EECORE_SYSCALL_TABLE[syscallNumber];
}