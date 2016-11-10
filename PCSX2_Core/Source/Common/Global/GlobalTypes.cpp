#include "stdafx.h"

#include "Common/Global/GlobalTypes.h"

u128::u128():
	hi(0),
	lo(0)
{
}

u128::u128(const u64 & upper, const u64 & lower) :
	hi(upper),
	lo(lower)
{
}

void u128::operator=(const u128& right)
{
	hi = right.hi;
	lo = right.lo;
}

bool u128::operator==(const u128& right) const
{
	return (lo == right.lo) && (hi == right.hi);
}

bool u128::operator!=(const u128& right) const
{
	return (lo != right.lo) || (hi != right.hi);
}
