#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The VU Status flags register.
See VU Users Manual page 39.

Declared before the MAC register due to dependency.
*/
class VectorUnitRegister_Status_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Z = 0;
		static constexpr u8 S = 1;
		static constexpr u8 U = 2;
		static constexpr u8 O = 3;
		static constexpr u8 I = 4;
		static constexpr u8 D = 5;
		static constexpr u8 ZS = 6;
		static constexpr u8 SS = 7;
		static constexpr u8 US = 8;
		static constexpr u8 OS = 9;
		static constexpr u8 IS = 10;
		static constexpr u8 DS = 11;
	};

	VectorUnitRegister_Status_t();

	/*
	Overriden write functions to trigger the update of the sticky bit flags.
	See VU Users Manual page 40.
	*/
	void setFieldValue(const u8& fieldIndex, const u32& value) override;
};

/*
The VU MAC flags register.
See VU Users Manual page 39.

Needs a reference to the associated Status register for its special functionality.
*/
class VectorUnitRegister_MAC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Zw = 0;
		static constexpr u8 Zz = 1;
		static constexpr u8 Zy = 2;
		static constexpr u8 Zx = 3;
		static constexpr u8 Sw = 4;
		static constexpr u8 Sz = 5;
		static constexpr u8 Sy = 6;
		static constexpr u8 Sx = 7;
		static constexpr u8 Uw = 8;
		static constexpr u8 Uz = 9;
		static constexpr u8 Uy = 10;
		static constexpr u8 Ux = 11;
		static constexpr u8 Ow = 12;
		static constexpr u8 Oz = 13;
		static constexpr u8 Oy = 14;
		static constexpr u8 Ox = 15;
	};

	VectorUnitRegister_MAC_t(const std::shared_ptr<VectorUnitRegister_Status_t> & status);

	/*
	Overriden set bit field function to trigger changes to the associated VU status register.
	See VU Users Manual page 39.
	*/
	void setFieldValue(const u8& fieldIndex, const u32& value) override;

private:

	/*
	A reference to the VU status flags register, which fields are changed when various MAC register write conditions occur.
	See VU Users Manual page 39.
	*/
	const std::shared_ptr<VectorUnitRegister_Status_t> mStatus;
};

/*
The VU Clipping flags register.
See VU Users Manual page 39.

Bitfields are organsied by {Neg/Pos}{X/Y/Z}_{digit below} for:
- Current judgement = 0.
- Previous judgement = 1.
- 2nd previous judgement = 2.
- 3rd previous judgement = 3.
*/
class VectorUnitRegister_Clipping_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 NegX_0 = 0;
		static constexpr u8 PosX_0 = 1;
		static constexpr u8 NegY_0 = 2;
		static constexpr u8 PosY_0 = 3;
		static constexpr u8 NegZ_0 = 4;
		static constexpr u8 PosZ_0 = 5;
		static constexpr u8 NegX_1 = 6;
		static constexpr u8 PosX_1 = 7;
		static constexpr u8 NegY_1 = 8;
		static constexpr u8 PosY_1 = 9;
		static constexpr u8 NegZ_1 = 10;
		static constexpr u8 PosZ_1 = 11;
		static constexpr u8 NegX_2 = 12;
		static constexpr u8 PosX_2 = 13;
		static constexpr u8 NegY_2 = 14;
		static constexpr u8 PosY_2 = 15;
		static constexpr u8 NegZ_2 = 16;
		static constexpr u8 PosZ_2 = 17;
		static constexpr u8 NegX_3 = 18;
		static constexpr u8 PosX_3 = 19;
		static constexpr u8 NegY_3 = 20;
		static constexpr u8 PosY_3 = 21;
		static constexpr u8 NegZ_3 = 22;
		static constexpr u8 PosZ_3 = 23;
	};

	VectorUnitRegister_Clipping_t();

	/*
	Shifts the register 6-bits (judgement) right, evicting the MSB 6-bits (LSB's set to 0).
	Bits 24-31 are always set to 0 when this function is run.
	See VU Users Manual page 75 & 202.
	Designed to be used in the CLIP instruction first, then set the clipping results with setFieldValue()
	*/
	void shiftJudgement();
};

/*
The VU CMSAR register.
See VU Users Manual page 202.

CMSAR0 and CMSAR1 are the same register, so it is defined simply as CMSAR.
*/
class VectorUnitRegister_CMSAR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 CMSAR = 0;
	};

	VectorUnitRegister_CMSAR_t();
};
