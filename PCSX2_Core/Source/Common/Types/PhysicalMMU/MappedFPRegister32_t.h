#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMapped_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"

/*
A transition layer, allowing a register to be mapped into the PS2 physical memory space.
Ie: translates from byte index accesses into size index accesses.
If the access size is smaller than the register size, but aligned on a boundary, then the appropriate array index will be accessed in the register.
For example, for a 32-bit register mapped @ 0x1F801470 accessed by readHword(0x1F801472) will return Register32->UH[1].
If the access is not aligned on the appropriate boundary, then a runtime_error is thrown.
If the access size is larger than the register size, a runtime_error is thrown.
TODO: look into size conditions - the EE manual mentions "... only accessible by word ...", but this allows any size.
On byte/hword access, a runtime_error is thrown, reason being that the underlying FPRegister32_t does not implement these.
*/
class MappedFPRegister32_t : public PhysicalMapped_t
{
public:
	explicit MappedFPRegister32_t(const u32 physicalAddress, const std::shared_ptr<FPRegister32_t> & fpRegister32);

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
	Gets the storage length, needed by the Physical MMU handler in order to map it.
	*/
	size_t getSize() override;

	/*
	Get the storage mnemonic, used for debug.
	*/
	const char * getMnemonic() const override;

private:
	/*
	The underlying register this class maps to.
	*/
	std::shared_ptr<FPRegister32_t> mFPRegister32;
};