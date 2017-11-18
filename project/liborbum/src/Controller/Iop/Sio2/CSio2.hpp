#pragma once

#include "VM/Types/VMSystem_t.h"

class SIO2_t;
class RIopIntc;

/*
SIO2 system logic.
TODO: Fill in.
*/
class SIO2_s : public VMSystem_t
{
public:
	SIO2_s(VM * vm);
	virtual ~SIO2_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the SIO2 state, performing the following tasks:
	*/
	int step(const Event_t & event) override;

	/*
	Context resources needed.
	*/
	SIO2_t mSIO2;
	RIopIntc mINTC;

};

