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
	u8 readByteU(u32 storageIndex) override;
	void writeByteU(u32 storageIndex, u8 value) override;
	s8 readByteS(u32 storageIndex) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	u16 readHwordU(u32 storageIndex) override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	s16 readHwordS(u32 storageIndex) override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	u32 readWordU(u32 storageIndex) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) override;
	void writeWordS(u32 storageIndex, s32 value) override;
	u64 readDwordU(u32 storageIndex) override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	s64 readDwordS(u32 storageIndex) override;
	void writeDwordS(u32 storageIndex, s64 value) override;

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
	const std::shared_ptr<Memory_t> mMemory;
};