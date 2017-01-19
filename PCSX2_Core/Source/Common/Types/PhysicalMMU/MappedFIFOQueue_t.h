#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

/*
A transition layer, allowing a FIFO queue to be mapped into the PS2 physical memory space.
Only read/writeWord and Qword is allowed on non-zero storage indexes - all other combinations throw a runtime error.
*/
class MappedFIFOQueue_t : public PhysicalMapped
{
public:
	explicit MappedFIFOQueue_t(const u32& physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue);
	virtual ~MappedFIFOQueue_t();

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
	std::shared_ptr<FIFOQueue_t> mFIFOQueue;
};