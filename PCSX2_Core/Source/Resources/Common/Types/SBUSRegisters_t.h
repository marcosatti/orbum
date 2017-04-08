#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"

/*
SBUS_MSCOM (F200) register.
Writes discarded for IOP.
*/
class SBUSRegister_MSCOM_t : public Register32_t
{
public:
	SBUSRegister_MSCOM_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
	void writeWord(const System_t context, u32 value) override;
};

/*
SBUS_MSFLG (F220) register.
Writes NOT AND (clears) or OR with the previous value.
*/
class SBUSRegister_MSFLG_t : public Register32_t
{
public:
	SBUSRegister_MSFLG_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
	void writeWord(const System_t context, u32 value) override;
};

/*
SBUS_SMFLG (F230) register.
Writes NOT AND (clears) or OR with the previous value.
*/
class SBUSRegister_SMFLG_t : public Register32_t
{
public:
	SBUSRegister_SMFLG_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
	void writeWord(const System_t context, u32 value) override;
};

/*
SBUS_F240 register.
Manipulates with magic values on reads and writes.
*/
class SBUSRegister_F240_t : public Register32_t
{
public:
	SBUSRegister_F240_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
	u16 readHword(const System_t context, size_t arrayIndex) override;
	u32 readWord(const System_t context) override;
	void writeHword(const System_t context, size_t arrayIndex, u16 value) override;
	void writeWord(const System_t context, u32 value) override;
};

/*
SBUS_F300 register.
TODO: not currently implemented properly, throws runtime_error. See HwRead.cpp and sif2.cpp.
*/
class SBUSRegister_F300_t : public Register32_t
{
public:
	SBUSRegister_F300_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
	u32 readWord(const System_t context) override;
	void writeWord(const System_t context, u32 value) override;
};
