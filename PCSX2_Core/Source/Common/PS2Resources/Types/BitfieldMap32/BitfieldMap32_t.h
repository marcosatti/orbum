#pragma once

#include <string>
#include <vector>

#include "Common/Global/Globals.h"

/*
BitfieldMap32_t provides a bitfield implementation, which can be used as an abstraction over some memory (which is 32-bits long).

In order to use this, first you must register a field with the registerField() function.
Once done, you may get and set the fields using the UNIQUE CHAR POINTER (constant field string) you provided to registerField() function.
The map WILL NOT return the same field if a different pointer is used (even with the same contents - it is not a std::string key'd map!).
The key type const char* is used for performance reasons.

It is the users responsibility to make sure the values set are appropriate. For example if you:
1) Have declared a field to be 3 bits long.
2) Set the field value to a number which requires more than 3 bits (eg: decimal 10).
3) Sync the map to the underlying 32-bit value.
You will only get 3 bits worth back, even though the field value may still reflect decimal 10.

It will automatically sync with the underlying memory when ever a field value is changed, if set at runtime (mAutoSync). Otherwise call syncMemoryfromMap().
For registerField(), it is always sync'd and cannot be changed.
However, the implementing class must make sure to sync with the bitfield everytime the 32 bit value is changed (if desired). 
This is done by calling syncMapFromMemory();

A class that extends this class must implement get/setBitRange32() in order to sync between the map <==> u32 value.
*/
class BitfieldMap32_t
{
public:
	BitfieldMap32_t(const bool & autoSync);
	virtual ~BitfieldMap32_t();

	/*
	get/setBitRange32() must be implemented as a way for compatibility and synchronisation between the bitfield map <==> u32 value.
	*/
	virtual u32 getBitRange32(u8 startPosition, u8 bitLength) = 0;
	virtual void setBitRange32(u8 startPosition, u8 bitLength, u32 value) = 0;

	/*
	Registers a field that can be used with this class. Must be done first before any other methods can be used to manipulate fields.
	Requires: a unique field name (fieldName), a bitfield starting position within the 32 bits (fieldStartPosition), how long the bitfield is (fieldLength), and an initial value (fieldInitialValue).
	*/
	virtual void registerField(const u8 & fieldIndex, const std::string & fieldName, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue);

	/*
	Returns the value associated with the parsed field. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	virtual const u32 & getFieldValue(const u8 & fieldIndex);

	/*
	Sets a field value using the parsed value. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	virtual void setFieldValue(const u8 & fieldIndex, const u32 & value);

	/*
	Reset the bitfield register by initalising all fields to its initial value defined in the BitfieldProperties_t.
	*/
	virtual void initaliseAllFields();

	/*
	Initalise a specific field to its initial value defined in the BitfieldProperties_t.
	*/
	virtual void initaliseField(const u8 & fieldIndex);

	/*
	If the underlying 32-bit value is changed directly, call this function to update and sync the bitfield map to reflect the same values.
	*/
	virtual void syncMapFromMemory();

	/*
	If the map bitfield values have been changed directly, call this function to update and sync the underlying 32-bit value.
	*/
	virtual void syncMemoryFromMap();

private:
	/*
	Used internally for storing the information parsed though registerField().
	This is used in the field map as well as the 'value' in the key-value pair.

	Note: Due to how the map container works, we can't make the constant properties (everything except mFieldValue) 'const'.
	*/
	struct BitfieldProperties_t
	{
		std::string mFieldName;
		u8 mFieldStartPosition;
		u8 mFieldLength;
		u32 mInitialFieldValue;
		u32 mFieldValue; // Set to mInitialFieldValue when created, but can be changed.
	};

	/*
	Map which stores all of the registered fields, along with their associated properties.
	*/
	static constexpr u8 FIELD_MAP_SIZE = 32;
	BitfieldProperties_t mFieldMap[32];

	/*
	Set at initalisation - does this class sync with the underlying memory everytime setFieldValue() (or anything that writes) is called?
	*/
	bool mAutoSync;
};

