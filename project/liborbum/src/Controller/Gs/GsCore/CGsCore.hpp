#pragma once



#include "VM/VM.h"
#include "VM/Types/VMSystem_t.h"

#include "Resources/GS/RGs.h"

/*
GS system logic.
*/
class GSCore_s : public VMSystem_t
{
public:
	GSCore_s(VM * vm);
	virtual ~GSCore_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the GSCore state, and renders graphics.
	*/
	int step(const Event_t & event) override;

	/*
	Resources.
	*/
	RGs mGS;
};