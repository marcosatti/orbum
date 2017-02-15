#pragma once

#include "Common/Types/Registers/Register32_t.h"

/*
A 32-bit bitfield register where the user can access defined fields with keys.
Sync'ing with the bitfield map is provided automatically with the write{Byte,Hword,Word} functions, from which you can extract bitfields easily (using getFieldValue()).
Setting bitfields using setFieldValue() will also automatically sync with the register.
*/
class BitfieldRegister32_t : public Register32_t
{
public:
	explicit BitfieldRegister32_t();
	explicit BitfieldRegister32_t(const char * mnemonic);

#if defined(BUILD_DEBUG)
	explicit BitfieldRegister32_t(const char * mnemonic, bool debugReads, bool debugWrites); // Turn on/off debugging functionality.
	bool mDebugReads, mDebugWrites;
#endif

	virtual ~BitfieldRegister32_t();

	/*
	Initalise register with default field values.
	*/
	void initalise() override;

#if defined(BUILD_DEBUG)
	/*
	Debug logs all bitfield mnemonics with values.
	*/
	void logDebugAllFields() const;

	/*
	If enabled, log all field contents on read.
	*/
	u8 readByte(const Context& context, size_t arrayIndex) override;
	u16 readHword(const Context& context, size_t arrayIndex) override;
	u32 readWord(const Context& context) override;
#endif

	/*
	Override write functions to sync with the bitfield map.
	If enabled, log all field contents on write.
	*/
	void writeByte(const Context& context, size_t arrayIndex, u8 value) override;
	void writeHword(const Context& context, size_t arrayIndex, u16 value) override;
	void writeWord(const Context & context, u32 value) override;

	/*
	Registers a field that can be used with this class. Must be done first before any other methods can be used to manipulate fields.
	Requires: a unique field index (fieldIndex), a mnemonic (fieldMnemonic), a bitfield starting position (fieldStartPosition), how long the bitfield is (fieldLength), and an initial value (fieldInitialValue).
	*/
	void registerField(const u8 & fieldIndex, const char * fieldMnemonic, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue);

	/*
	Returns the value associated with the parsed field. fieldName must reference an already registered field name otherwise the class will be left in an inconsistent state and undefined results may happen.
	*/
	inline virtual const u32 & getFieldValue(const u8 & fieldIndex) const;

	/*
	Sets a field value using the parsed value. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	inline virtual void setFieldValue(const u8 & fieldIndex, const u32 & value);

	/*
	Reset the bitfield register by initalising all fields to its initial value defined in the BitfieldProperties_t.
	*/
	void initaliseAllFields();

private:
	/*
	Arrays which stores all of the registered fields, along with their associated properties.
	*/
	friend class EECoreInterpreter_s;
	friend class IOPCoreInterpreter_s;
	static constexpr u8 FIELD_MAP_SIZE = 32;
	struct
	{
		std::string mMnemonic;
		u8 mStartPosition;
		u8 mLength;
		u32 mValue;
		u32 mInitialValue;
	} mFields[FIELD_MAP_SIZE];
};

