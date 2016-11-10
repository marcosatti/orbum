#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/Registers/Register32_t.h"

/*
A transition layer, allowing a register to be mapped into the PS2 physical memory space.
Ie: translates from byte index accesses into size index accesses.
*/

class MappedRegister32_t : public PhysicalMapped
{
public:
	explicit MappedRegister32_t(const u32& physicalAddress, const std::shared_ptr<Register32_t> & register32);
	virtual ~MappedRegister32_t();

	/*
	For 32-bit registers, only read/writeWord is allowed. All others throw a runtime exception.
	This is provided to mimic the PS2 alginment conditions, for example, with the EE registers defined in the EE Users Manual ("...only word accessible...").
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
	const std::shared_ptr<Register32_t> mRegister32;
};