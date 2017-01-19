#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/Registers/Register16_t.h"

/*
A transition layer, allowing a register to be mapped into the PS2 physical memory space.
Ie: translates from byte index accesses into size index accesses.
If the access size is smaller than the register size, but aligned on a boundary, then the appropriate array index will be accessed in the register.
For example, for a 32-bit register mapped @ 0x1F801470 accessed by readHword(0x1F801472) will return Register32->UH[1].
If the access is not aligned on the appropriate boundary, then a runtime_error is thrown.
If the access size is larger than the register size, a runtime_error is thrown.
TODO: look into size conditions - the EE manual mentions "... only accessible by word ...", but this allows any size.
*/
class MappedRegister16_t : public PhysicalMapped
{
public:
	explicit MappedRegister16_t(const u32& physicalAddress, const std::shared_ptr<Register16_t> & register16);
	virtual ~MappedRegister16_t();

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
	The underlying register this class maps to.
	*/
	std::shared_ptr<Register16_t> mRegister16;
};