#include "stdafx.h"

#include <cassert>

#include "Globals.h"

#include "Instruction_t.h"

int main(int argc, char * argv[])
{
	Instruction_t a;

	a.setInstruction(0x00622020); // add $4, $3, $2

	u32 b = a.getOpcode();
	assert(b == 0);
	u32 c = a.getRFunct();
	assert(c == 32);
	u32 d = a.getRRd();
	assert(d == 4);
	u32 e = a.getRRs();
	assert(e == 3);
	u32 f = a.getRRt();
	assert(f == 2);
	u32 g = a.getRShamt();
	assert(g == 0);

	/*
	a.setInstruction(0x00622020); // add $4, $3, $2

	u32 h = a.getOpcode();
	assert(b == 0);
	u32 i = a.getRFunct();
	assert(c == 32);
	u32 j = a.getRRd();
	assert(d == 4);
	u32 k = a.getRRs();
	assert(e == 3);
	u32 l = a.getRRt();
	assert(f == 2);
	u32 m = a.getRShamt();
	assert(g == 0);
	*/

	return 0;
}