#pragma once

#include "Common/Global/Globals.h"

/*
Parameters describe information needed for a TLB * exception to process. 
These fields are not used for all TLB exception types, but are related to the TLB. Consult the ExceptionHandler for which TLB exceptions access what fields.
*/
struct TLBExceptionInfo_t
{
	u32 PS2VirtualAddress;		 // The full virtual address that caused the exception.
	u32 PageTableAddress;		 // The address of the OS's page table // TODO: Uhhhhh how do I know this???
	u32 PS2VirtualAddress_HI_19; // High order 19-bits of the VA that caused the exception.
	u32 ASID;					 // ASID.
	u32 TLBIndex;				 // TLB index pointing to a new entry.
};