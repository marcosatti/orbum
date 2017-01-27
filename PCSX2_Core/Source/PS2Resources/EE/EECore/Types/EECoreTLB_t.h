#pragma once

#include "Common/Global/Globals.h"

#include "PS2Constants/PS2Constants.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLBEntry_t.h"

class EECoreTLB_t
{
public:
	explicit EECoreTLB_t();

	/*
	Performs an iterative lookup on the TLB for the given VPN contained in the PS2VirtualAddress.
	A return value of -1 indicates an entry was not found. 
	Any functions that call this may throw a TLB refill exception if an entry was not found (this function doesn't do this automatically).
	The process is based on EE Core Users Manual page 120.
	*/
	s32 findTLBIndex(u32 PS2VirtualAddress) const;

	/*
	Gets the TLB entry at the specified index - use findTLBIndex() to make sure it exists first.
	*/
	const EECoreTLBEntry_t & getTLBEntry(s32 index) const;

	/*
	Copies the TLB entry info to the specified index.
	*/
	void setTLBEntry(const EECoreTLBEntry_t & entry, const s32 & index);

	/*
	Gets an index to a new TLB entry position.
	This is used whenever a MMU exception error is raised.
	See for example EE Users Manual page 101.
	TODO: currently not working properly.
	*/
	s32 getNewTLBIndex();

	/*
	A zeroed-TLB entry, pointed to by the MMUHandler initially.
	*/
	static constexpr EECoreTLBEntry_t EMPTY_TLB_ENTRY = {0};

private:
	/*
	TLB entries. See EE Core Users Manual page 120.
	In total there are 48 entries.
	*/
	EECoreTLBEntry_t mTLBEntries[PS2Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES];
};

