#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

class FPRegister32_t;

/*
Wrapper for a FPRegister32_t to be used as a Register32_t.
TODO: Currently the underlying Register32_t is allocated memory.. Need to separate the interface from implementation. However probably not worth it since it is only used for 16 VI registers and nothing else.
*/
class WrapperF32Register32_t : public Register32_t
{
public:
	explicit WrapperF32Register32_t(const std::shared_ptr<FPRegister32_t> & fpRegister32);
	explicit WrapperF32Register32_t(const char * mnemonic, const std::shared_ptr<FPRegister32_t> & fpRegister32);

	u8 readByte(const System_t context, size_t arrayIndex) override;
	void writeByte(const System_t context, size_t arrayIndex, u8 value) override;
	u16 readHword(const System_t context, size_t arrayIndex) override;
	void writeHword(const System_t context, size_t arrayIndex, u16 value) override;
	u32 readWord(const System_t context) override;
	void writeWord(const System_t context, u32 value) override;

	/*
	Initalise register (initalise underlying register).
	*/
	void initalise() override;

private:
	/*
	Reference to the underlying FPRegister32_t that the above read/write calls translate to.
	*/
	std::shared_ptr<FPRegister32_t> mFPRegister32;
};