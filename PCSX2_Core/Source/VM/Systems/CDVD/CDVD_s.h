#pragma once

#include "VM/Types/VMSystem_s.h"

class CDVD_t;

/*
CDVD handler logic.
*/
class CDVD_s : public VMSystem_s
{
public:
	CDVD_s(VM * vm);
	virtual ~CDVD_s() = default;

	/*
	Initalisation.
	*/
	void initalise() override;

	/*
	Checks the CDVD state for any actions to be performed, and steps through if needed.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<CDVD_t> mINTC;
};

