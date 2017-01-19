#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/Memory/Memory_t.h"

/*
A transition layer, allowing a Memory_t object to be mapped into a PhysicalMMU_t.
The API between PhysicalMMU_t and Memory_t is directly compatible, so this class just forwards on the request.
Requires a mnemonic (for debug) and a PS2 physical address of where it should be mapped from.
*/
class MappedMemory_t : public PhysicalMapped
{
public:
	explicit MappedMemory_t(const u32& physicalAddress, const std::shared_ptr<Memory_t> & memory);
	virtual ~MappedMemory_t();

	/*
	Read or Write to the underlying memory.
	*/
	u8 readByte(const Context_t& context, u32 storageIndex) override;
	void writeByte(const Context_t& context, u32 storageIndex, u8 value) override;
	u16 readHword(const Context_t& context, u32 storageIndex) override;
	void writeHword(const Context_t& context, u32 storageIndex, u16 value) override;
	u32 readWord(const Context_t& context, u32 storageIndex) override;
	void writeWord(const Context_t& context, u32 storageIndex, u32 value) override;
	u64 readDword(const Context_t& context, u32 storageIndex) override;
	void writeDword(const Context_t& context, u32 storageIndex, u64 value) override;
	u128 readQword(const Context_t& context, u32 storageIndex) override;
	void writeQword(const Context_t& context, u32 storageIndex, u128 value) override;

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
	std::shared_ptr<Memory_t> mMemory;
};