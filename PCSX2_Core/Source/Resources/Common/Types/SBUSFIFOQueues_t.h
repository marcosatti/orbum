#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/FIFOQueue/FIFOQueue32_t.h"

class SBUSRegister_F300_t;

/*
A custom FIFO for the SIF2 DMA interface to trigger updates to the Common->SBUS_REGISTER_F300 (magic values).
*/
class SBUSFIFOQueue_SIF2_t : public FIFOQueue32_t
{
public:
	SBUSFIFOQueue_SIF2_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxSize, const std::shared_ptr<SBUSRegister_F300_t> & sbusF300);

	/*
	Trigger updates to the SBUS_F300 register (magic values).
	Based upon PCSX2's "sif2.cpp".
	*/
	u32 readWord(const System_t context) override;
	u128 readQword(const System_t context) override;
	void writeWord(const System_t context, const u32 data) override;
	void writeQword(const System_t context, const u128 data) override;

private:
	/*
	Reference to the SBUS_F300 register.
	*/
	std::shared_ptr<SBUSRegister_F300_t> mSBUSF300;

	/*
	Logic for updating the SBUS_F300 register.
	Checks for a full or empty FIFO queue and sets the appropriate magic value.
	*/
	void handleSBUSUpdate(const System_t context) const;
};