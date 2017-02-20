#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/Memory_t.h"

/*
A constant memory object, where reads return the constant u64 value (downcasted where appropriate) set at creation and writes do nothing.
For a 128-bit read, the u64 is returned in the lower and upper 64-bits.
Currently used for 'reserved' memory regions (ie: some EE registers) and debugging purposes.
The size parameter in the constructor is used only for Physical MMU mapping purposes.
The parsed size is not allocated (always set to 0 in the underlying Memory_t).
*/
class ConstantMemory_t : public Memory_t
{
public:
	ConstantMemory_t(const size_t & size, const u64 D = 0);
	ConstantMemory_t(const size_t & size, const char * mnemonic, const u64 D = 0);
	~ConstantMemory_t();

	u8 readByte(const Context_t& context, size_t storageIndex) override;
	void writeByte(const Context_t& context, size_t storageIndex, u8 value) override;
	u16 readHword(const Context_t& context, size_t storageIndex) override;
	void writeHword(const Context_t& context, size_t storageIndex, u16 value) override;
	u32 readWord(const Context_t& context, size_t storageIndex) override;
	void writeWord(const Context_t& context, size_t storageIndex, u32 value) override;
	u64 readDword(const Context_t& context, size_t storageIndex) override;
	void writeDword(const Context_t& context, size_t storageIndex, u64 value) override;
	u128 readQword(const Context_t& context, size_t storageIndex) override;
	void writeQword(const Context_t& context, size_t storageIndex, u128 value) override;

	/*
	Needed by the Physical MMU handler in order to map it. 
	Instead of the normal Memory_t::getSize(), return the size set when the object is created.
	*/
	size_t getSize() override;

private:
	const size_t mSize;
	const u64 mConstantValue; // Set at creation, returned in the read function calls.
};

