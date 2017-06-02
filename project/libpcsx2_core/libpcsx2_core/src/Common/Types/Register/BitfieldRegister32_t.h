#pragma once

#include <vector>

#include "Common/Types/Register/Register32_t.h"

/*
A 32-bit bitfield register where the user can access defined fields with keys.
Sync'ing with the bitfield map is provided automatically with the write{Byte,Hword,Word} functions, from which you can extract bitfields easily (using getFieldValue()).
Setting bitfields using setFieldValue() will also automatically sync with the register.
*/
class BitfieldRegister32_t : public Register32_t
{
public:
	BitfieldRegister32_t(const char * mnemonic, bool debugReads, bool debugWrites);
	virtual ~BitfieldRegister32_t() = default;

	/*
	Initialise register with default field values.
	*/
	void initialise() override;

	/*
	Reset the bitfield register by initialising all fields to its initial value defined in the BitfieldProperties_t.
	*/
	void initialiseAllFields();

	/*
	Override write functions to sync with the bitfield map.
	If enabled, log all field contents on read/write.
	*/
	u8 readByte(const Context_t context, const size_t arrayIndex) override;
	void writeByte(const Context_t context, const size_t arrayIndex, const u8 value) override;
	u16 readHword(const Context_t context, const size_t arrayIndex) override;
	void writeHword(const Context_t context, const size_t arrayIndex, const u16 value) override;
	u32 readWord(const Context_t context) override;
	void writeWord(const Context_t context, const u32 value) override;

	/*
	Registers a field that can be used with this class. Must be done first before any other methods can be used to manipulate fields.
	Requires: a unique field index (fieldIndex), a mnemonic (fieldMnemonic), a bitfield starting position (fieldStartPosition), how long the bitfield is (fieldLength), and an initial value (fieldInitialValue).
	*/
	void registerField(const int fieldIndex, const char * fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u32 fieldInitialValue);

	/*
	Returns the value associated with the parsed field. fieldName must reference an already registered field name otherwise the class will be left in an inconsistent state and undefined results may happen.
	*/
	virtual u32 getFieldValue(const Context_t context, const int fieldIndex);

	/*
	Sets a field value using the parsed value. fieldName must reference an already registered field name otherwise the class will be left in an inconsitent state and undefined results may happen.
	*/
	virtual void setFieldValue(const Context_t context, const int fieldIndex, const u32 value);

	/*
	Debug logs all bitfield mnemonics with values.
	*/
	void logDebugAllFields() const;

private:
	// For debug purposes.
	friend class EECoreInterpreter_s;
	friend class IOPCoreInterpreter_s;

	/*
	Container which stores all of the registered fields, along with their associated properties.
	*/
	struct BitfieldProperties32_t
	{
		std::string mMnemonic;
		int mStartPosition;
		int mLength;
		u32 mInitialValue;
	};
	std::vector<BitfieldProperties32_t> mFields;
};

