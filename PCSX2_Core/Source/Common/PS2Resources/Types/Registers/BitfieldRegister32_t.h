#pragma once

#include <unordered_map>

#include "Common/PS2Resources/Types/Registers/Register32_t.h"

/*
The BitfieldRegiser_t class extends the Register32_t class, providing methods for manipulating 32-bit bit fields.
Bitfields are implemented as full u32 fields instead of manipulating one u32 value directly.
It is probably faster when compiled to use a u32 for each field and perfoming one move instruction than perfoming multiple bitshift instructions, although I have not tested this.

In order to use this, first you must register a field with the registerField() function. 
Once done, you may get and set the fields using the UNIQUE CHAR POINTER (constant field string) you provided to registerField() function.
The map WILL NOT return the same field if a different pointer is used (even with the same contents - it is not a std::string key'd map!).
The key type const char* is used for performance reasons.

Compatibility with a hardware bitfield register is provided though the get and setRegisterValue() functions.
These functions manipulate the Register32_t.UW variable to produce the condensed u32 bitfield.
Note that the values set through setFieldValue() will not reflect through Register32_t.UW until getRegisterValue() is called. This is done to reduce overhead.

It is the users responsibility to make sure the values set are appropriate. For example if you:
 1) Have declared a field to be 3 bits long.
 2) Set the field value to a number which requires more than 3 bits (eg: decimal 10).
 3) Request the full bitfield through getRegisterValue().
You will only get 3 bits worth back, even though the field value may still reflect decimal 10.

TODO: Implement checks for invalid values on initalisation and get and setting fields.
*/
class BitfieldRegister32_t : public Register32_t
{
public:
	BitfieldRegister32_t();
	
	/*
	Registers a field that can be used with this class. Must be done first before any other methods can be used to manipulate fields.
	Requires: a unique field name (fieldName), a bitfield starting position within the 32 bits (fieldStartPosition), how long the bitfield is (fieldLength), and an initial value (fieldInitialValue).
	*/
	void registerField(const char * fieldName, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue);

	/*
	Returns the value associated with the parsed field. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	virtual u32 getFieldValue(const char * fieldName);

	/*
	Sets a field value using the parsed value. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	virtual void setFieldValue(const char * fieldName, const u32 & value);

	/*
	Gets the combined bitfield value from the individual fields. Also syncs Register32_t.UW to reflect the same value.
	*/
	virtual u32 getRegisterValue();

	/*
	Sets the Register32_t.UW register value to reflect the parsed value, and updates all of the registered fields to reflect the bitfield values from Register32_t.UW.
	*/
	virtual void setRegisterValue(const u32 & value);

	/*
	Reset the bitfield register by initalising all fields to its initial value defined in the BitfieldProperties_t.
	*/
	virtual void initaliseAllFields();

	/*
	Initalise a specific field to its initial value defined in the BitfieldProperties_t.
	*/
	virtual void initaliseField(const char * fieldName);

private:
	/*
	Used internally for storing the information parsed though registerField().
	This is used in the field map as well as the 'value' in the key-value pair.

	Note: Due to how map works, we can't make the constant properties 'const'.
	*/
	struct BitfieldProperties_t
	{
		const char * mFieldName;
		u8 mFieldStartPosition;
		u8 mFieldLength;
		u32 mInitialFieldValue;
		u32 mFieldValue; // Set to mInitialFieldValue when created, but can be changed.
	};

	/*
	Map which stores all of the registered fields, along with their associated properties.
	*/
	std::unordered_map<const char *, BitfieldProperties_t> mFieldMap;
};

