#pragma once

#include <string>

#include "Common/Global/Globals.h"

// Option of whether to throw a runtime error on index out of bounds access. 
// Turn off if you are sure that no errors will occur and want to debug quicker.
// Disabled anyway on release builds.
#if defined(BUILD_DEBUG)
 #define ERROR_ON_FIELD_INDEX_RANGE 0
#else
 #define ERROR_ON_FIELD_INDEX_RANGE 0
#endif

/*
BitfieldMap32_t provides a bitfield implementation, which can be used as an abstraction over some memory (which is 32-bits long).

In order to use this, first you must register a field with the registerField() function.
Once done, you may get and set the fields using the UNIQUE u8 index value you provided to registerField() function.

It is the users responsibility to make sure the values set are appropriate. For example if you:
1) Have declared a field to be 3 bits long.
2) Set the field value to a number which requires more than 3 bits (eg: decimal 10).
3) Sync the map to the underlying 32-bit value.
You will only get 3 bits worth back, even though the field value may still reflect decimal 10.

Syncing between the fields and the u32 value:
- The underlying u32 value when a field is changed automatically (ie: through setFieldValue and others). It can always be called manually through syncMemoryFromMap().
- It is up to an implementing class if it should sync with the fields whenever the u32 value is changed. The function to do this is syncMapFromMemory().

A class that extends this class must implement get/setBitRange32() in order to sync between the map <==> u32 value.
*/
class BitfieldMap32_t
{
public:
	BitfieldMap32_t();
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
	void registerField(const u8 & fieldIndex, const std::string & fieldName, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue);

	/*
	Returns the value associated with the parsed field. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	inline const u32 & getFieldValue(const u8 & fieldIndex) const;

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
	// Friend the BitfieldRegister32_t class to access the field map directly (used in debug).
	friend class BitfieldRegister32_t;

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
	BitfieldProperties_t mFieldMap[FIELD_MAP_SIZE];
};

const u32 & BitfieldMap32_t::getFieldValue(const u8 & fieldIndex) const
{
#if ERROR_ON_FIELD_INDEX_RANGE
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");
#endif

	return mFieldMap[fieldIndex].mFieldValue;
}
