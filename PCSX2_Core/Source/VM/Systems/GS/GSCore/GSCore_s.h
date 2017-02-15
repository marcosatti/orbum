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
	explicit GSCore_s(VM * vmMain);
	virtual ~GSCore_s();

	void run(const double & time) override;

	/*
	*/
	int step(const ClockEvent_t& event) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<GS_t> mGS;
};