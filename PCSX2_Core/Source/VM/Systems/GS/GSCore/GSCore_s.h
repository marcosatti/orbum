#pragma once

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Types/VMSystem_s.h"

#include "Resources/GS/GS_t.h"

/*
GS system logic.
*/
class GSCore_s : public VMSystem_s
{
public:
	explicit GSCore_s(VM * vm);
	virtual ~GSCore_s();

	/*
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<GS_t> mGS;
};