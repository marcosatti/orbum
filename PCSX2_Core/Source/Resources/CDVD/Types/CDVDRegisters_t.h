#pragma once

#include <memory>

#include "Common/Types/Register/Register8_t.h"

class FIFOQueue_t;

/*
CDVD Register N/S_COMMAND.
Sets an internal variable to true if there is a pending command to be processed.
*/
class CDVDRegister_NS_COMMAND_t : public Register8_t
{
public:
	CDVDRegister_NS_COMMAND_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Sets pending command to true.
	Throws error when it has already been set.
	*/
	void writeByte(const System_t context, const u8 value) override;

	/*
	Pending command.
	Set to true on write, cleared by the system logic when the command has been processed.
	*/
	bool mPendingCommand;
};

/*
CDVD register / FIFO queue hybrid "register".
Read: Register8_t: {N/S}_READY.
Write: FIFOQueue_t: {N/S}_DATA_IN.
*/
class CDVDRegister_NS_RDY_DIN_t : public Register8_t
{
public:
	CDVDRegister_NS_RDY_DIN_t(const char * mnemonic_READY, const char * mnemonic_DATA_IN, bool debugReads, bool debugWrites, const size_t fifoQueueSize);

	/*
	Redirect read/write calls to resources.
	*/
	u8 readByte(const System_t context) override;
	void writeByte(const System_t context, const u8 value) override;

	/*
	Resources.
	*/
	std::shared_ptr<Register8_t> READY;
	std::shared_ptr<FIFOQueue_t> DATA_IN;
};