#include "Common/Tables/IOPCoreSyscallTable.h"

constexpr IOPCoreSyscallTable::IOPCoreSyscallInfo_t IOPCoreSyscallTable::IOPCORE_SYSCALL_TABLE[Constants::IOP::IOPCore::R3000::NUMBER_SYSCALLS];

const IOPCoreSyscallTable::IOPCoreSyscallInfo_t * IOPCoreSyscallTable::getInfo(const int syscallNumber)
{
	return &IOPCORE_SYSCALL_TABLE[syscallNumber];
}