#pragma once

#include "Resources/Ee/Vpu/VifCoreRegisters.hpp"

// A base class for a VIF core.
class VifCore_Base
{
public:
	VifCore_Base(const int core_id);

	/// ID of the VIF unit.
	int core_id;

	/// VIF registers. See page 124 of EE Users Manual.
	SizedWordRegister     r0;
	SizedWordRegister     r1;
	SizedWordRegister     r2;
	SizedWordRegister     r3;
	SizedWordRegister     c0;
	SizedWordRegister     c1;
	SizedWordRegister     c2;
	SizedWordRegister     c3;
	VifCoreRegister_Cycle cycle;
	VifCoreRegister_Mask  mask;
	VifCoreRegister_Mode  mode;
	VifCoreRegister_Itop  itop;
	VifCoreRegister_Itops itops;
	VifCoreRegister_Base  base;
	VifCoreRegister_Ofst  ofst;
	VifCoreRegister_Top   top;
	VifCoreRegister_Tops  tops;
	VifCoreRegister_Mask  mark;
	VifCoreRegister_Num   num;
	VifCoreRegister_Code  code;
	VifCoreRegister_Stat  stat;
	VifCoreRegister_Fbrst fbrst;
	VifCoreRegister_Err   err;
};