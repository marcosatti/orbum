#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/Registers/FPRegister128_t.h"

/*
A transition layer, allowing a register to be mapped into the PS2 physical memory space.
Ie: translates from byte index accesses into size index accesses.
*/

class MappedFPRegister128_t : public PhysicalMapped
{
public:
	explicit MappedFPRegister128_t(const u32& physicalAddress, const std::shared_ptr<FPRegister128_t> & fpRegister128);
	virtual ~MappedFPRegister128_t();

	/*
	For 128-bit FPRegisters, only read/writeWord and Dword is allowed. All others throw a runtime exception.
	Access must conform to alignment conditions. ie: for word access, storage index must be (storageIndex % 4 == 0),
	 however it is up to the user to correctly align the mapping to the physical memory space.
	A runtime exception is thrown on unaligned conditions.
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
	const std::shared_ptr<FPRegister128_t> mFPRegister128;
};