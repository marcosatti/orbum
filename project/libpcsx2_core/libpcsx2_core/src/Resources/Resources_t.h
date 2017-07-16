#pragma once

#include <memory>

class Events_t;
class EE_t;
class GS_t;
class IOP_t;
class SPU2_t;
class SIO2_t;
class CDVD_t;
class Common_t;

/*
TODO: finish writing documentation, and to create copy constructors for each of the elements (looking into saving/restoring the state).
Resources_t delares all of the stateful resources attached to the PS2, such as the EE memory, GS memory and more.
All of the reads and writes to the PS2 system state will come to here.

The structure of Resources_t is defined as a hierarchy of 'components', with the components defined in the Types subfolder within each 'category'.
Categories are loosely based off the chapters in the EE Users Manual.
There is no hard definition of what is a component and what is a category, although rule of thumb you shouldn't make a component too big to understand.
User is to make a judgement, just be sure to make clear your intentions.
As an example, the EE & DMAC is defined as a category, and inside is the DMAC channel components and common registers.

The naming convention is based off the component. For cases where for example the EE and IOP share component names,
the source files are prefixed with EE or IOP.

You should only ever need to create an object of the Resources_t type from which you can access everything,
which is ordered by components in the documentation groups, such as Resources->EE->EECore->R5900->GPR[1]->readWord().

If you can't initialise a component due to a dependency, put the initialisation in the Resources_t constructor instead.

In order to reduce compile times, try to use forward delarations where possible.
*/
class Resources_t
{
public:
	Resources_t();

	/*
	The Events class, used to control timing accross components.
	*/
	std::shared_ptr<Events_t> Events;

	/*
	Common resources structure (shared between EE, GS and/or IOP).
	*/
	std::shared_ptr<Common_t> Common;

	/*
	The GS structure.
	*/
	std::shared_ptr<GS_t> GS;

	/* 
	The EE structure.
	*/
	std::shared_ptr<EE_t> EE;

	/*
	The IOP structure.
	*/
	std::shared_ptr<IOP_t> IOP;

	/*
	CD-ROM / DVD Drive resources (CDVD).
	*/
	std::shared_ptr<CDVD_t> CDVD;

	/*
	SPU2 Resources.
	*/
	std::shared_ptr<SPU2_t> SPU2;

private:
	/*
	Post initialisation functions.
	Initialises any resources that are dependant on another.
	*/
	void postInit_EE() const;
	void postInit_EE_DMAC() const;
	void postInit_EE_VPU_VU() const;
	void postInit_IOP() const;
	void postInit_IOP_DMAC() const;
	void postInit_SPU2() const;
};
