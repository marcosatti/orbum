#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/Memory_t.h"

/*
A 'Bus error' storage object, which will generate an exception on access.
The size parameter in the constructor is used only for Physical MMU mapping purposes.
The parsed size is not allocated (always set to 0 in the underlying MappedMemory_t).
TODO: Currently throws a runtime_error, need to implement the ps2 exception.
*/
class BusErrMemory_t : public Memory_t
{
public:
	BusErrMemory_t(const size_t & size, const char * mnemonic);
	~BusErrMemory_t();

	u8 readByte(u32 storageIndex) override;
	void writeByte(u32 storageIndex, u8 value) override;
	u16 readHword(u32 storageIndex) override;
	void writeHword(u32 storageIndex, u16 value) override;
	u32 readWord(u32 storageIndex) override;
	void writeWord(u32 storageIndex, u32 value) override;
	u64 readDword(u32 storageIndex) override;
	void writeDword(u32 storageIndex, u64 value) override;
	u128 readQword(u32 storageIndex) override;
	void writeQword(u32 storageIndex, u128 value) override;

	/*
	Needed by the Physical MMU handler in order to map it. Instead of the normal MappedMemory_t::getSize(), return the size set
	 when the object is created.
	*/
	size_t getSize() override;

private:
	size_t mSize; 
};

