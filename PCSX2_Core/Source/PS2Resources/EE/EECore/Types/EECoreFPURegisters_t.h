#pragma once

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
FPURegisters_t.h implements all of the bitfields in each of the FPU control registers. This is used primarily by EECoreFPU_t.h.
Each register will have documentation attached to it, and is prefixed by COP1Register.
Note: where register fields have a constant 0, this is already done due to the base classes initalisation code.

It is recommended that you read the documentation of the BitfieldRegister32_t class, which documents how to access bitfields.
All of the fields available within each register are defined within the Fields struct located inside.
ie: to access a field in a register object from outside this file, you would use:
- RegisterIndex.setFieldValue(RegisterIndex::Fields::Index, u32 value) or
- u32 value = RegisterIndex.getFieldValue(RegisterIndex::Fields::Index)
All of the available field functions are listed in the BitfieldRegister32_t class.

The actual fields are defined at runtime within the COP1_BitfieldRegisters_t.cpp file.
*/

struct FPUFlags_t;

/*
The IRR (Implementation and Revision Register (FCR0)) of FPU, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 158.

Bitfield map (defined as constants in the class below):
- Bits 0-7 (length 8): "Rev".
- Bits 8-15 (length 8): "Imp".
- Bits 16-31 (length 16): Constant 0.
*/
class EECoreFPURegister_IRR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Rev = 0;
		static constexpr u8 Imp = 1;
	};

	explicit EECoreFPURegister_IRR_t();
};

/*
The CSR (Control/Status Register (FCR31)) of FPU, subclassed off the base BitfieldRegister32_t & Register32_t class.
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
class EECoreFPURegister_CSR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 SU = 0;
		static constexpr u8 SO = 1;
		static constexpr u8 SD = 2;
		static constexpr u8 SI = 3;
		static constexpr u8 U = 4;
		static constexpr u8 O = 5;
		static constexpr u8 D = 6;
		static constexpr u8 I = 7;
		static constexpr u8 C = 8;
	};

	explicit EECoreFPURegister_CSR_t();

	/*
	Set bit field function to trigger update of the sticky flags (SU, SO, SD, SI).
	See EE Core Users Manual page 159.
	*/
	void setFieldValueSticky(const u8& fieldIndex, const u32& value);

	/*
	Update or clears the U, O, (D, I) flags, which both should be done on each instruction that modifies this register.
	The C flag is not changed! Needs to be done manually.
	*/
	void updateResultFlags(const FPUFlags_t & flags);
	void clearFlags(); // Clears the D and I flags too.
};