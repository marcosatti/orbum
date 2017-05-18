#include "Common/Tables/EECoreSyscallTable.h"

constexpr EECoreSyscallTable::EECoreSyscallInfo_t EECoreSyscallTable::EECORE_SYSCALL_TABLE[Constants::EE::EECore::R5900::NUMBER_SYSCALLS];

const EECoreSyscallTable::EECoreSyscallInfo_t * EECoreSyscallTable::getInfo(const int syscallNumber)
{
	return &EECORE_SYSCALL_TABLE[syscallNumber];
}