#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

/*
A transition layer, allowing a FIFO queue to be mapped into the PS2 physical memory space.
Only read/writeQwordU is allowed on aligned addresses - all other combinations throw a runtime error.
*/
class MappedFIFOQueue_t : public PhysicalMapped
{
public:
	explicit MappedFIFOQueue_t(const u32& physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue);
	virtual ~MappedFIFOQueue_t();

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
	u128 readQwordU(u32 storageIndex) override;
	void writeQwordU(u32 storageIndex, u128 value) override;

	/*
	Gets the storage length, needed by the Physical MMU handler in order to map it.
	*/
	size_t getSize() override;

	/*
	Get the storage mnemonic, used for debug.
	*/
	const char * getMnemonic() const override;

private:
	/*
	The underlying FIFO queue this class maps to.
	*/
	const std::shared_ptr<FIFOQueue_t> mFIFOQueue;
};