#include "stdafx.h"

#include "Common/PS2Resources/EE/DMAC/Types/DMADataUnit_t.h"

DMADataUnit_t::DMADataUnit_t(u64 lower, u64 upper) :
	mDataUnit{lower, upper}
{
}
