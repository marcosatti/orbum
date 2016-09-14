#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

using EECoreInstructionInfo_t = EECoreInstructionUtil::EECoreInstructionInfo_t;

/*
EECoreTimerHandler is responisble for updating any EECore timer related registers or functionality.
Note that it is impossible to emulate the exact precision of a real PS2, mostly because the CPU cycles are updated as total cycle values, not on each cycle.

The timers involved include:
 1. The COP0.Count register, which is updated every cpu clock cycle. In this case, it is updated each time an EECore instruction is executed with the 
     estimated amount of cycles it takes to complete. See EE Core Users Manual page 70.
 2. The COP0.Compare register, which signals an interrupt whenever COP0.Count >= COP0.Compare. The docs specify that an interrupt is raised when the 
     two values are equal, but this is impossible to get correct, so it is based on greater than or equal. See EE Core Users Manual page 72.
*/
class EECoreTimerHandler : public VMExecutionCoreComponent
{
public:
	explicit EECoreTimerHandler(const VMMain *const vmMain);

	// COP0.Count register functionality.
	void incrementCountTimer(const EECoreInstructionInfo_t *const EECoreInstructionInfo) const;

	// Check for any timer events.
	void checkTimerEvents() const;
};

