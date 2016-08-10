#pragma once

#include "Common/PS2 Types/Registers/BitfieldRegister32_t.h"

/*
COP1_BitfieldRegister_t.h implements all of the bitfields in each of the COP1 control registers. This is used primarily by COP1_t.h.
Each register will have documentation attached to it.
Note: where register fields have a constant 0, this is already done due to the base classes initalisation code.

It is recommended that you read the documentation of the BitfieldRegister32_t class, which documents how to access bitfields.
All of the fields available within each register are defined within the Fields struct located inside.
ie: to access a field in a register object from outside this file, you would use:
- RegisterIndex.setFieldValue(RegisterIndex::Fields::Index, u32 value) or
- u32 value = RegisterIndex.getFieldValue(RegisterIndex::Fields::Index)
All of the available field functions are listed in the BitfieldRegister32_t class.
*/

/*
The IRR (Implementation and Revision Register (FCR0)) of COP1, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 158.

Bitfield map (defined as constants in the class below):
- Bits 0-7 (length 8): "Rev".
- Bits 8-15 (length 8): "Imp".
- Bits 16-31 (length 16): Constant 0.
*/
class RegisterIRR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr auto Rev = "Rev";
		static constexpr auto Imp = "Imp";
	};

	RegisterIRR_t()
	{
		registerField(Fields::Rev, 0, 8, 0);
		registerField(Fields::Imp, 8, 8, 0x2E);
	}
};

/*
The CSR (Control/Status Register (FCR31)) of COP1, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 158.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): Constant 1.
- Bits 1 (length 1): Constant 0.
- Bits 2 (length 1): Constant 0.
- Bits 3 (length 1): "SU".
- Bits 4 (length 1): "SO".
- Bits 5 (length 1): "SD".
- Bits 6 (length 1): "SI".
- Bits 7-13 (length 7): Constant 0.
- Bits 14 (length 1): "U".
- Bits 15 (length 1): "O".
- Bits 16 (length 1): "D".
- Bits 17 (length 1): "I".
- Bits 18-22 (length 5): Constant 0.
- Bits 23 (length 1): "C".
- Bits 24 (length 1): Constant 1.
- Bits 25-31 (length 7): Constant 0.
*/
class RegisterCSR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr auto SU = "SU";
		static constexpr auto SO = "SO";
		static constexpr auto SD = "SD";
		static constexpr auto SI = "SI";
		static constexpr auto U = "U";
		static constexpr auto O = "O";
		static constexpr auto D = "D";
		static constexpr auto I = "I";
		static constexpr auto C = "C";
	};

	RegisterCSR_t()
	{
		registerField(Fields::SU, 3, 1, 0);
		registerField(Fields::SO, 4, 1, 0);
		registerField(Fields::SD, 5, 1, 0);
		registerField(Fields::SI, 6, 1, 0);
		registerField(Fields::U, 14, 1, 0);
		registerField(Fields::O, 15, 1, 0);
		registerField(Fields::D, 16, 1, 0);
		registerField(Fields::I, 17, 1, 0);
		registerField(Fields::C, 23, 1, 0);
	}
};