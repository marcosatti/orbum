#pragma once

#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

/*
COP0_BitfieldRegister_t.h implements common COP0 control registers. This is used primarily by EECoreCOP0_t.h and IOPCoreCOP0_t.h.
Each register will have documentation attached to it, and is prefixed with COP0Register.
Note: where register fields have a constant 0, this is already done due to the base classes initalisation code.

It is recommended that you read the documentation of the BitfieldRegister32_t class, which documents how to access bitfields.
All of the fields available within each register are defined within the Fields struct located inside.
ie: to access a field in a register object from outside this file, you would use:
- RegisterIndex.setFieldValue(RegisterIndex::Fields::Index, u32 value) or
- u32 value = RegisterIndex.getFieldValue(RegisterIndex::Fields::Index)
All of the available field functions are listed in the BitfieldRegister32_t class.

The actual fields are defined at runtime within the COP0_BitfieldRegisters_t.cpp file.
*/

/*
COP0RegisterReserved_t represents an unknown (blank) register. It is up to the user at runtime to define fields.
*/
class COP0RegisterReserved_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
	};

	explicit COP0RegisterReserved_t();
};

/*
The EPC register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 76.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "EPC".
*/
class COP0RegisterEPC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 EPC = 0;
	};

	explicit COP0RegisterEPC_t();
};