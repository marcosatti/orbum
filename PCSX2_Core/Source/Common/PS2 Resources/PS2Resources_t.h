#pragma once

#include <memory>

#include "Common/PS2 Resources/EE/EE_t.h"
#include "Common/PS2 Resources/MainMemory/MainMemory_t.h"
#include "Common/PS2 Resources/BootROM/BootRom.h"

/*
TODO: finish writing documentation, and to create copy constructors for each of the elements.
PS2State_t delares all of the stateful resources attached to the PS2, such as the EE memory, GS memory and more.
All of the reads and writes to the PS2 system state will come to here.

You should only ever need to create an object of the PS2Resources_t type from which you can access everything,
which is ordered by components in the documentation groups, such as PS2Resources->PS2State->EE->EECore->R5900->GPR[1]->readWordU().

PS2State_t SHOULD NOT be allocated on the stack - this object hierarchy can get quite big (even without the memory allocated),
which is why it should be used on the heap. As such, you should create this object through std::shared_ptr (std::make_shared) or similar.
*/

class PS2Resources_t
{
public:

	// The EE structure.
	std::shared_ptr<EE_t> EE = std::make_shared<EE_t>();

	// Main Memory (32MB)
	std::shared_ptr<MainMemory_t> MainMemory = std::make_shared<MainMemory_t>();

	// Boot ROM (4MB)
	std::shared_ptr<BootROM_t> BootROM = std::make_shared<BootROM_t>();

private:

};
