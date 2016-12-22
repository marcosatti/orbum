#include "stdafx.h"

#include "Common/Global/GlobalTypes.h"

u128::u128():
	hi(0),
	lo(0)
{
}

u128::u128(const u64 & lower, const u64 & upper) :
	hi(upper),
	lo(lower)
{
}

u128::u128(const u32& w0, const u32& w1, const u32& w2, const u32& w3) :
	UW{ w0, w1, w2, w3 }
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
