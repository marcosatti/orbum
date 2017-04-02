#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMapped_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"

/*
A transition layer, allowing a Memory_t object to be mapped into a PhysicalMMU_t.
The API between PhysicalMMU_t and Memory_t is directly compatible, so this class just forwards on the request.
*/
class MappedMemory_t : public PhysicalMapped_t
{
public:
	explicit MappedMemory_t(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t> & memory);

	/*
	Read or Write to the underlying memory.
	*/
	u8 readByte(const System_t context, size_t storageIndex) override;
	void writeByte(const System_t context, size_t storageIndex, u8 value) override;
	u16 readHword(const System_t context, size_t storageIndex) override;
	void writeHword(const System_t context, size_t storageIndex, u16 value) override;
	u32 readWord(const System_t context, size_t storageIndex) override;
	void writeWord(const System_t context, size_t storageIndex, u32 value) override;
	u64 readDword(const System_t context, size_t storageIndex) override;
	void writeDword(const System_t context, size_t storageIndex, u64 value) override;
	u128 readQword(const System_t context, size_t storageIndex) override;
	void writeQword(const System_t context, size_t storageIndex, u128 value) override;

	/*
	Gets the underlying storage length, needed by the Physical MMU handler in order to map it.
	*/
	size_t getSize() override;

	/*
	Get the underlying storage mnemonic, used for debug.
	*/
	const char * getMnemonic() const override;

private:
	/*
	The underlying memory this class maps to.
	*/
	std::shared_ptr<ByteMemory_t> mMemory;
};