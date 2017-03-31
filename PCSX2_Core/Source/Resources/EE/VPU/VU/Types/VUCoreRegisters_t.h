#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Util/FPUUtil/FPUFlags_t.h"

/*
The VU unit Status flags register.
See VU Users Manual page 39.

Declared before the MAC register due to dependency.
*/
class VUCoreRegister_Status_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int Z = 0;
		static constexpr int S = 1;
		static constexpr int U = 2;
		static constexpr int O = 3;
		static constexpr int I = 4;
		static constexpr int D = 5;
		static constexpr int ZS = 6;
		static constexpr int SS = 7;
		static constexpr int US = 8;
		static constexpr int OS = 9;
		static constexpr int IS = 10;
		static constexpr int DS = 11;
	};

	VUCoreRegister_Status_t();

	/*
	Overriden write functions to trigger the update of the sticky bit flags.
	See VU Users Manual page 40.
	*/
	void setFieldValueSticky(const int fieldIndex, const u32 value);

	/*
	Clear the non-sticky flags, which should be done on each instruction that modifies this register.
	*/
	void clearFlags();
};

/*
The VU unit MAC flags register.
See VU Users Manual page 39.

Needs a reference to the associated Status register for its special functionality.
*/
class VUCoreRegister_MAC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int Zw = 0;
		static constexpr int Zz = 1;
		static constexpr int Zy = 2;
		static constexpr int Zx = 3;
		static constexpr int Sw = 4;
		static constexpr int Sz = 5;
		static constexpr int Sy = 6;
		static constexpr int Sx = 7;
		static constexpr int Uw = 8;
		static constexpr int Uz = 9;
		static constexpr int Uy = 10;
		static constexpr int Ux = 11;
		static constexpr int Ow = 12;
		static constexpr int Oz = 13;
		static constexpr int Oy = 14;
		static constexpr int Ox = 15;

		static constexpr int X_FLAGS[] = { Zx, Sx, Ux, Ox };
		static constexpr int Y_FLAGS[] = { Zy, Sy, Uy, Oy };
		static constexpr int Z_FLAGS[] = { Zz, Sz, Uz, Oz };
		static constexpr int W_FLAGS[] = { Zw, Sw, Uw, Ow };
	};

	VUCoreRegister_MAC_t(const std::shared_ptr<VUCoreRegister_Status_t> & status);

	/*
	Set bit field function to trigger changes to the associated VU status register.
	See VU Users Manual page 39.
	*/
	void setFieldValueStatus(const int fieldIndex, const u32 value);

	/*
	Updates or clear all flags (Z, S, U, O) for the given vector field, of which at least one function should be run on each instruction that modifies this register.
	Mapping: fieldIndex    0 -> 3
	         vector field  x -> w
	*/
	void updateVectorField(const int fieldIndex, const FPUFlags_t & flags);
	void clearVectorField(const int fieldIndex);

private:

	/*
	A reference to the VU status flags register, which fields are changed when various MAC register write conditions occur.
	See VU Users Manual page 39.
	*/
	std::shared_ptr<VUCoreRegister_Status_t> mStatus;
};

/*
The VU unit Clipping flags register.
See VU Users Manual page 39.

Bitfields are organsied by {Neg/Pos}{X/Y/Z}_{digit below} for:
- Current judgement = 0.
- Previous judgement = 1.
- 2nd previous judgement = 2.
- 3rd previous judgement = 3.
*/
class VUCoreRegister_Clipping_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int NegX_0 = 0;
		static constexpr int PosX_0 = 1;
		static constexpr int NegY_0 = 2;
		static constexpr int PosY_0 = 3;
		static constexpr int NegZ_0 = 4;
		static constexpr int PosZ_0 = 5;
		static constexpr int NegX_1 = 6;
		static constexpr int PosX_1 = 7;
		static constexpr int NegY_1 = 8;
		static constexpr int PosY_1 = 9;
		static constexpr int NegZ_1 = 10;
		static constexpr int PosZ_1 = 11;
		static constexpr int NegX_2 = 12;
		static constexpr int PosX_2 = 13;
		static constexpr int NegY_2 = 14;
		static constexpr int PosY_2 = 15;
		static constexpr int NegZ_2 = 16;
		static constexpr int PosZ_2 = 17;
		static constexpr int NegX_3 = 18;
		static constexpr int PosX_3 = 19;
		static constexpr int NegY_3 = 20;
		static constexpr int PosY_3 = 21;
		static constexpr int NegZ_3 = 22;
		static constexpr int PosZ_3 = 23;
	};

	VUCoreRegister_Clipping_t();

	/*
	Shifts the register 6-bits (judgement) right, evicting the MSB 6-bits (LSB's set to 0).
	Bits 24-31 are always set to 0 when this function is run.
	See VU Users Manual page 75 & 202.
	Designed to be used in the CLIP instruction first, then set the clipping results with setFieldValue()
	*/
	void shiftJudgement();
};

/*
The VU unit CMSAR register.
See VU Users Manual page 202.

CMSAR0 and CMSAR1 are the same register, so it is defined simply as CMSAR.
*/
class VUCoreRegister_CMSAR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int CMSAR = 0;
	};

	VUCoreRegister_CMSAR_t();
};
