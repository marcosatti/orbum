#include "stdafx.h"

#include "PS2Resources/EE/VPU/VU/Types/VuUnitRegisters_t.h"

VuUnitRegister_Status_t::VuUnitRegister_Status_t()
{
	registerField(Fields::Z, "Z", 0, 1, 0);
	registerField(Fields::S, "S", 1, 1, 0);
	registerField(Fields::U, "U", 2, 1, 0);
	registerField(Fields::O, "O", 3, 1, 0);
	registerField(Fields::I, "I", 4, 1, 0);
	registerField(Fields::D, "D", 5, 1, 0);
	registerField(Fields::ZS, "ZS", 6, 1, 0);
	registerField(Fields::SS, "SS", 7, 1, 0);
	registerField(Fields::US, "US", 8, 1, 0);
	registerField(Fields::OS, "OS", 9, 1, 0);
	registerField(Fields::IS, "IS", 10, 1, 0);
	registerField(Fields::DS, "DS", 11, 1, 0);
}

void VuUnitRegister_Status_t::setFieldValueSticky(const u8& fieldIndex, const u32& value)
{
	BitfieldRegister32_t::setFieldValue(fieldIndex, value);

	// Check if the field index was for one of the regular bits, and update the sticky bit.
	// TODO: relies on the fact that the sticky bit is always N + 6 apart.
	if (fieldIndex >= Fields::Z && fieldIndex <= Fields::D)
	{
		u32 oldStickyValue = getFieldValue(fieldIndex + 6);
		BitfieldRegister32_t::setFieldValue(fieldIndex + 6, oldStickyValue | value);
	}
}

void VuUnitRegister_Status_t::clearFlags()
{
	setFieldValueSticky(Fields::Z, 0);
	setFieldValueSticky(Fields::S, 0);
	setFieldValueSticky(Fields::U, 0);
	setFieldValueSticky(Fields::O, 0);
	setFieldValueSticky(Fields::I, 0);
	setFieldValueSticky(Fields::D, 0);
}

VuUnitRegister_MAC_t::VuUnitRegister_MAC_t(const std::shared_ptr<VuUnitRegister_Status_t> & status) :
	mStatus(status)
{
	registerField(Fields::Zw, "Zw", 0, 1, 0);
	registerField(Fields::Zz, "Zz", 1, 1, 0);
	registerField(Fields::Zy, "Zy", 2, 1, 0);
	registerField(Fields::Zx, "Zx", 3, 1, 0);
	registerField(Fields::Sw, "Sw", 4, 1, 0);
	registerField(Fields::Sz, "Sz", 5, 1, 0);
	registerField(Fields::Sy, "Sy", 6, 1, 0);
	registerField(Fields::Sx, "Sx", 7, 1, 0);
	registerField(Fields::Uw, "Uw", 8, 1, 0);
	registerField(Fields::Uz, "Uz", 9, 1, 0);
	registerField(Fields::Uy, "Uy", 10, 1, 0);
	registerField(Fields::Ux, "Ux", 11, 1, 0);
	registerField(Fields::Ow, "Ow", 12, 1, 0);
	registerField(Fields::Oz, "Oz", 13, 1, 0);
	registerField(Fields::Oy, "Oy", 14, 1, 0);
	registerField(Fields::Ox, "Ox", 15, 1, 0);
}

void VuUnitRegister_MAC_t::setFieldValueStatus(const u8& fieldIndex, const u32& value)
{
	setFieldValue(fieldIndex, value);

	// Check which flag fieldIndex belongs to, and set the corresponding Status flag (OR with previous value).
	// Only valid if fieldIndex falls in the Zw -> Ox range, which should always be true...
	// TODO: relies on the fact that the MAC and Status registers have the same order of flags (ie: can use fieldIndex / 4).
	if (fieldIndex >= Fields::Zw && fieldIndex <= Fields::Ox)
		mStatus->setFieldValueSticky(fieldIndex / 4, mStatus->getFieldValue(fieldIndex / 4) | value);
	else
		throw std::runtime_error("VU MAC register set flag stick index out of range.");
}

void VuUnitRegister_MAC_t::updateVectorField(const u8& fieldIndex, const FPUFlags_t& flags)
{
	// Determine if its for x, y, z, w.
	// Note: currently there is a bug in the visual c++ compiler which prevents this array being defined in the Fields struct.
	const u8 * FIELD_FLAGS[] = { Fields::X_FLAGS, Fields::Y_FLAGS, Fields::Z_FLAGS, Fields::W_FLAGS };
	auto& FIELD_FLAGS_SET = FIELD_FLAGS[fieldIndex];

	// Set the relevant flags (Z, S, U, O).
	setFieldValueStatus(FIELD_FLAGS_SET[0], flags.ZF ? 1 : 0);
	setFieldValueStatus(FIELD_FLAGS_SET[1], flags.SF ? 1 : 0);
	setFieldValueStatus(FIELD_FLAGS_SET[2], flags.UF ? 1 : 0);
	setFieldValueStatus(FIELD_FLAGS_SET[3], flags.OF ? 1 : 0);
}

void VuUnitRegister_MAC_t::clearVectorField(const u8& fieldIndex)
{
	// Determine if its for x, y, z, w.
	// Note: currently there is a bug in the visual c++ compiler which prevents this array being defined in the Fields struct.
	const u8 * FIELD_FLAGS[] = { Fields::X_FLAGS, Fields::Y_FLAGS, Fields::Z_FLAGS, Fields::W_FLAGS };
	auto& FIELD_FLAGS_SET = FIELD_FLAGS[fieldIndex];

	// Clear the relevant flags (O, U, S, Z).
	for (auto i = 0; i < 4; i++)
		setFieldValueStatus(FIELD_FLAGS_SET[i], 0);
}

VuUnitRegister_Clipping_t::VuUnitRegister_Clipping_t()
{
	registerField(Fields::NegX_0, "NegX_0", 0, 1, 0);
	registerField(Fields::PosX_0, "PosX_0", 1, 1, 0);
	registerField(Fields::NegY_0, "NegY_0", 2, 1, 0);
	registerField(Fields::PosY_0, "PosY_0", 3, 1, 0);
	registerField(Fields::NegZ_0, "NegZ_0", 4, 1, 0);
	registerField(Fields::PosZ_0, "PosZ_0", 5, 1, 0);
	registerField(Fields::NegX_1, "NegX_1", 6, 1, 0);
	registerField(Fields::PosX_1, "PosX_1", 7, 1, 0);
	registerField(Fields::NegY_1, "NegY_1", 8, 1, 0);
	registerField(Fields::PosY_1, "PosY_1", 9, 1, 0);
	registerField(Fields::NegZ_1, "NegZ_1", 10, 1, 0);
	registerField(Fields::PosZ_1, "PosZ_1", 11, 1, 0);
	registerField(Fields::NegX_2, "NegX_2", 12, 1, 0);
	registerField(Fields::PosX_2, "PosX_2", 13, 1, 0);
	registerField(Fields::NegY_2, "NegY_2", 14, 1, 0);
	registerField(Fields::PosY_2, "PosY_2", 15, 1, 0);
	registerField(Fields::NegZ_2, "NegZ_2", 16, 1, 0);
	registerField(Fields::PosZ_2, "PosZ_2", 17, 1, 0);
	registerField(Fields::NegX_3, "NegX_3", 18, 1, 0);
	registerField(Fields::PosX_3, "PosX_3", 19, 1, 0);
	registerField(Fields::NegY_3, "NegY_3", 20, 1, 0);
	registerField(Fields::PosY_3, "PosY_3", 21, 1, 0);
	registerField(Fields::NegZ_3, "NegZ_3", 22, 1, 0);
	registerField(Fields::PosZ_3, "PosZ_3", 23, 1, 0);
}

void VuUnitRegister_Clipping_t::shiftJudgement()
{
	writeWord(RAW, (readWord(RAW) << 6) & 0x00FFFFFF);
}

VuUnitRegister_CMSAR_t::VuUnitRegister_CMSAR_t()
{
	registerField(Fields::CMSAR, "CMSAR", 0, 16, 0);
}
