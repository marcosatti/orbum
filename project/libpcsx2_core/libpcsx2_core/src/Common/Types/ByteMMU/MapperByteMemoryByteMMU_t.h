#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperBaseObjectByteMMU_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"

/*
A transition layer, allowing a ByteMemory_t object to be mapped into a ByteMMU_t.
The API between ByteMMU_t and ByteMemory_t is directly compatible, so this class just forwards on the request.
*/
class MapperByteMemoryByteMMU_t : public MapperBaseObjectByteMMU_t
{
public:
	MapperByteMemoryByteMMU_t(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t> & memory);

	/*
	Read or Write to the underlying memory.
	*/
	u8 readByte(const Context_t context, const size_t storageIndex) override;
	void writeByte(const Context_t context, const size_t storageIndex, const u8 value) override;
	u16 readHword(const Context_t context, const size_t storageIndex) override;
	void writeHword(const Context_t context, const size_t storageIndex, const u16 value) override;
	u32 readWord(const Context_t context, const size_t storageIndex) override;
	void writeWord(const Context_t context, const size_t storageIndex, const u32 value) override;
	u64 readDword(const Context_t context, const size_t storageIndex) override;
	void writeDword(const Context_t context, const size_t storageIndex, const u64 value) override;
	u128 readQword(const Context_t context, const size_t storageIndex) override;
	void writeQword(const Context_t context, const size_t storageIndex, const u128 value) override;

	/*
	Gets the storage length, needed by the ByteMMU_t handler in order to map it.
	*/
	size_t getSize() override;

private:
	/*
	The underlying memory this class maps to.
	*/
	std::shared_ptr<ByteMemory_t> mMemory;
};