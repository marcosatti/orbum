#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"

/*
SIO2 CTRL Register.
TODO: notes so far:
    - Bit 0 is a reset SIO2 or SIO flag in TX/RX direction (?). Cleared once reset complete.
    - PCSX2 probably not proper - doesn't seem right that things like this exist: "sio2.ctrl &= ~1;"

*/
class SIO2Register_CTRL_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int Reset = 0;
	};

	SIO2Register_CTRL_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Sets pending command to true.
	Throws error when it has already been set.
	*/
	void writeWord(const Context_t context, const u32 value) override;

	/*
	Pending command.
	Set to true on write, cleared by the system logic when the command has been processed.
	*/
	bool mPendingCommand;
};
