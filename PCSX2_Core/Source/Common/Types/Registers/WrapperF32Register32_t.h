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

	~WrapperF32Register32_t();

	u8 readByte(u32 arrayIndex) override;
	void writeByte(u32 arrayIndex, u8 value) override;
	u16 readHword(u32 arrayIndex) override;
	void writeHword(u32 arrayIndex, u16 value) override;
	u32 readWord() override;
	void writeWord(u32 value) override;

private:
	/*
	Reference to the underlying FPRegister32_t that the above read/write calls translate to.
	*/
	const std::shared_ptr<FPRegister32_t> mFPRegister32;
};