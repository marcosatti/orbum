#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/Registers/FPRegister128_t.h"

/*
A transition layer, allowing a register to be mapped into the PS2 physical memory space.
Ie: translates from byte index accesses into size index accesses.
If the underlying register size is larger than the access size, the LSB's will be returned. 
On byte/hword access, a runtime_error is thrown, reason being that the underlying FPRegister128_t does not implement these.
If the underlying register size is smaller than the access size, a runtime_error is thrown.
The storageIndex param must be equal to 0, otherwise a runtime_error is thrown (alignment conditions).
TODO: look into size conditions - the EE manual mentions "... only accessible by word ...", but this allows any size.
*/
class MappedFPRegister128_t : public PhysicalMapped
{
public:
	explicit MappedFPRegister128_t(const u32& physicalAddress, const std::shared_ptr<FPRegister128_t> & fpRegister128);
	virtual ~MappedFPRegister128_t();

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