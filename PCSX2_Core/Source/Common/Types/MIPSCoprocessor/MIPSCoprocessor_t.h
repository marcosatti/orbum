#pragma once

/*
Represents a MIPS co-processor base class.
Functions listed here are common to all co-processors.
*/
class MIPSCoprocessor_t
{
public:
	MIPSCoprocessor_t();
	virtual ~MIPSCoprocessor_t();

	/*
	Checks if this coprocessor is usable. As the coprocessor can be used within different CPU's, it is left as virtual.
	*/
	virtual bool isCoprocessorUsable() const = 0;


	/*
	A virtual function which may be implemented as a way to initalise the coprocessor state.
	*/
	virtual void initalise();
};