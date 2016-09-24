#pragma once

#include "boost/container/flat_map.hpp"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/StorageObject32_t.h"

/*
BitfieldStorageObject32_t provides read or write access to the underlying 32-bit memory allocated, in terms of bitfields.

This is similar to BitfieldRegister32_t - see documentation on that.
However, it automatically syncs with the underlying memory and/or bitfield as soon as anything has been written to.
*/
class BitfieldStorageObject32_t : public StorageObject32_t
{
public:
	explicit BitfieldStorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~BitfieldStorageObject32_t();

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
	Reset the bitfield register by initalising all fields to its initial value defined in the BitfieldProperties_t.
	*/
	virtual void initaliseAllFields();

	/*
	Initalise a specific field to its initial value defined in the BitfieldProperties_t.
	*/
	virtual void initaliseField(const char * fieldName);

	/*
	Override writeWord[U/S] to sync with the bitfield map.
	*/
	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;

private:
	/*
	Used internally for storing the information parsed though registerField().
	This is used in the field map as well as the 'value' in the key-value pair.

	Note: Due to how map works, we can't make the constant properties (everything except mFieldValue) 'const'.
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
	boost::container::flat_map<const char *, BitfieldProperties_t> mFieldMap;
};

