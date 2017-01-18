#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

class Register32_t;

/*
A custom FIFO for the SIF2 DMA interface to trigger updates to the Common->SBUS_REGISTER_F300 (magic values).
*/
class Sif2FIFOQueue_t : public FIFOQueue_t
{
public:
	explicit Sif2FIFOQueue_t(const size_t & maxSize, std::shared_ptr<Register32_t> & sbusF300);
	explicit Sif2FIFOQueue_t(const char * mnemonic, const size_t & maxSize, std::shared_ptr<Register32_t> & sbusF300);

	/*
	Trigger updates to the SBUS_F300 register (magic values).
	Based upon PCSX2's "sif2.cpp".
	*/
	u32 readWord(const Context_t& context) override;
	u128 readQword(const Context_t& context) override;
	void writeWord(const Context_t& context, const u32& data) override;
	void writeQword(const Context_t& context, const u128& data) override;

private:
	/*
	Reference to the SBUS_REGISTER_F300 register.
	*/
	std::shared_ptr<Register32_t> mSbusF300;

	/*
	Logic for updating the SBUS_F300 register.
	Checks for a full or empty FIFO queue and sets the appropriate magic value.
	*/
	void handleSBUSUpdate() const;
};