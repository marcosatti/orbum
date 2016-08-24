#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2 Resources/EE/EECore/COP1/Types/COP1ResourcesSubobject.h"

/*
FPRegister32_t is an additional register type defined within the PS2's floating point unit (COP1) system, which are used for operating on floating point numbers.
All FPR's are 32-bit according to the documentation, and the floating point value is accessed by the 'F' union field defined below.

See EE Core Users Manual, chapter 8, especially page 157 which define the aritmetic registers.

Code is based of the Register32_t implementation.
Some additional functions are exposed for manipulating the floating point fields (sign, exponent and fraction), which is done by manipulating the u32 UW in the union defined.

The COP1 and the floating point values in general are NOT FULLY IEEE-754 compliant (mostly, but not fully).
In particular, the COP1 does not support (in comparison to IEEE-754):
 - Denormalised numbers.
 - Plus and minus infinity.
 - 'NaN' (not a number) representation.
*/
class FPRegister32_t : public COP1ResourcesSubobject
{
public:

	explicit FPRegister32_t(const PS2Resources_t* const PS2Resources);

	virtual ~FPRegister32_t()
	{
	}

	union
	{
		u32 UW;
		s32 SW;
		f32 F;
	};

	/*
	Functions to access the register value - you should use these functions instead of accessing them directly.
	NOTE: IT IS UP TO THE USER TO MAKE SURE THE FLOAT VALUE WRITTEN IS COMPATIBLE WITH THE PS2! Use the EECoreCOP1Util static class functions to help with conversion.
	Accessing any of these functions will raise a coprocessor unavailable PS2Exception_t if the context is incorrect (ie: Status.CU[1] bit is not set or otherwise).
	*/
	virtual u32 readWordU();
	virtual void writeWordU(u32 value);	
	virtual s32 readWordS();
	virtual void writeWordS(s32 value);
	virtual f32 readFloat();
	virtual void writeFloat(f32 value);

	// Convenience function to access individual bits. The returned u8 value will either be 1 or 0.
	// Index must be between 0 -> 31.
	u8 getBit32(u8 index) const;

	// Convenience function to set individual bits. The bit value at index will be set to bitValue.
	// Index must be between 0 -> 31.
	void setBit32(u8 index, u32 bitValue);

	// Convenience function to get a value (bit array) with a specified length at startPos in the register.
	// This function is primarily used for getting a bitmask field in a register.
	u32 getBitRange32(u8 startPosition, u8 bitLength) const;

	// Convenience function to insert a value (bit array) with a specified length at startPos in the register.
	// This will overwrite the bits currently set at the startPos to (startPos + length).
	// This function is primarily used for setting bit masks in a register.
	// Note: If there are more bits set in value than bitLength allows for, the extra bits will not be written.
	void setBitRange32(u8 startPosition, u8 bitLength, u32 value);
};

