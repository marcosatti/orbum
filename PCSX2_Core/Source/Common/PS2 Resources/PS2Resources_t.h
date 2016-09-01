#pragma once

#include <memory>

#include "Common/PS2 Resources/EE/EE_t.h"
#include "Common/PS2 Resources/Types/PS2StorageObject/PS2StorageObject_t.h"

/*
TODO: finish writing documentation, and to create copy constructors for each of the elements.
PS2Resources_t delares all of the stateful resources attached to the PS2, such as the EE memory, GS memory and more.
All of the reads and writes to the PS2 system state will come to here.

You should only ever need to create an object of the PS2Resources_t type from which you can access everything,
which is ordered by components in the documentation groups, such as PS2Resources->PS2State->EE->EECore->R5900->GPR[1]->readWordU().

PS2State_t SHOULD NOT be allocated on the stack - this object hierarchy can get quite big (even without the memory allocated),
which is why it should be used on the heap. As such, you should create this object through std::shared_ptr (std::make_shared) or similar.

All Subobjects of this resources class should be extended from the PS2ResourcesSubobject interface - this is so they may inspect other resources
on function calls. An example of this is for the COP1 Registers, where all FPR activity (reads/writes) must check that COP1 is available first, 
by checking the COP0 Status register. Doing this allows for more cleaner and condensed code in the instruction implementations.
*/

class PS2Resources_t
{
public:

	// The EE structure.
	std::shared_ptr<EE_t> EE = std::make_shared<EE_t>(this);

	// Main Memory (32MB)
	std::shared_ptr<PS2StorageObject_t> MainMemory = std::make_shared<PS2StorageObject_t>(PS2Constants::MainMemory::SIZE_MAIN_MEMORY, "Main Memory", PS2Constants::MainMemory::PADDRESS_MAIN_MEMORY);

	// Boot ROM (4MB)
	std::shared_ptr<PS2StorageObject_t> BootROM = std::make_shared<PS2StorageObject_t>(PS2Constants::BootROM::SIZE_BOOT_ROM, "Boot ROM", PS2Constants::BootROM::SIZE_BOOT_ROM);

private:

};
