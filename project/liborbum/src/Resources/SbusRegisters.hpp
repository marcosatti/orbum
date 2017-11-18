#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// TODO: all are covered with blanket scope locks - need to investigate what they are actually doing.
/// They are accessed infrequently anyway so probably doesn't matter.

/*
SBUS_MSCOM (F200) register.
Writes discarded for IOP.
*/
class SbusRegister_Mscom : public SizedWordRegister, public ScopeLock
{
public:
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};

/*
SBUS_MSFLG (F220) register.
Writes NOT AND (clears) or OR with the previous value.
*/
class SbusRegister_Msflg : public SizedWordRegister, public ScopeLock
{
public:
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};

/*
SBUS_SMFLG (F230) register.
Writes NOT AND (clears) or OR with the previous value.
*/
class SbusRegister_Smflg : public SizedWordRegister, public ScopeLock
{
public:
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};

/*
SBUS_F240 register.
Manipulates with magic values on reads and writes.
*/
class SbusRegister_F240 : public SizedWordRegister, public ScopeLock
{
public:
	uhword byte_bus_read_uhword(const BusContext context, const usize offset) override;
	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
	uword byte_bus_read_uword(const BusContext context, const usize offset) override;
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};

/*
SBUS_F300 register.
TODO: not currently implemented properly, throws runtime_error. See HwRead.cpp and sif2.cpp.
*/
class SbusRegister_F300 : public SizedWordRegister, public ScopeLock
{
public:
	uword byte_bus_read_uword(const BusContext context, const usize offset) override;
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};
