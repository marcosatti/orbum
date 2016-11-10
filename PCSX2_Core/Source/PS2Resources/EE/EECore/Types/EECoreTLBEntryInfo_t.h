#pragma once

#include "Common/Global/Globals.h"

/*
TLB entry information. Used as the backbone of storing information in the EECore TLB.
A TLB entry is heavily related to the COP0 registers Entry{Hi, Lo0, Lo1}, PageMask and others.
See EE Core Users Manual page 120 - 123 about the TLB.

For the internal struct array below, index 0 corresponds to the Even infomation, and index 1 correponds to the Odd information.
*/
struct EECoreTLBEntryInfo_t
{
	u32 mMask;
	u32 mVPN2;
	u32 mG;
	u32 mASID;
	u32 mS;

	struct
	{
		u32 mPFN;
		u32 mC;
		u32 mD;
		u32 mV;
	} PhysicalInfo[2]; // Index 0 = Even, index 1 = Odd.
};