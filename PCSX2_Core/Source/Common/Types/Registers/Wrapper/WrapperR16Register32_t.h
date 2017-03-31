#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

class Register16_t;

/*
Allows a 16-bit register type to be used as a 32-bit register, with the upper 16-bits discarded on reads or writes.
This can only be accessed through read/writeWord calls. All other combinations throw an exception.
On reads, the upper 16-bits are always set to 0, which means it can never be sign-extended to eg. the s64 type (manual specs).
See for example the CFC2 instruction on page 234 of the VU Users Manual.
Currently used for implementing the VU0 COP2 control registers (CCR's), where the VI registers are used as CCR[0-15].
TODO: Currently the underlying Register32_t is allocated memory.. Need to separate the interface from implementation. However probably not worth it since it is only used for 16 VI registers and nothing else.
*/
class WrapperR16Register32_t : public Register32_t
{
public:
	explicit WrapperR16Register32_t(const std::shared_ptr<Register16_t> & register16);
	explicit WrapperR16Register32_t(const char * mnemonic, const std::shared_ptr<Register16_t> & register16);

	u8 readByte(const Context_t context, size_t arrayIndex) override;
	void writeByte(const Context_t context, size_t arrayIndex, u8 value) override;
	u16 readHword(const Context_t context, size_t arrayIndex) override;
	void writeHword(const Context_t context, size_t arrayIndex, u16 value) override;
	u32 readWord(const Context_t context) override;
	void writeWord(const Context_t context, u32 value) override;

	/*
	Initalise register (initalise underlying register).
	*/
	void initalise() override;

private:
	/*
	Reference to the underlying Register16_t that the above read/write calls translate to.
	*/
	std::shared_ptr<Register16_t> mRegister16;
};