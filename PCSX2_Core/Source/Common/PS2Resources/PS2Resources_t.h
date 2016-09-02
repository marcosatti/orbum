#pragma once

#include <memory>

/*
TODO: finish writing documentation, and to create copy constructors for each of the elements.
PS2Resources_t delares all of the stateful resources attached to the PS2, such as the EE memory, GS memory and more.
All of the reads and writes to the PS2 system state will come to here.

You should only ever need to create an object of the PS2Resources_t type from which you can access everything,
which is ordered by components in the documentation groups, such as PS2Resources->PS2State->EE->EECore->R5900->GPR[1]->readWordU().

PS2State_t SHOULD NOT be allocated on the stack - this object hierarchy can get quite big (even without the memory allocated),
which is why it should be used on the heap. As such, you should create this object through std::shared_ptr (std::make_shared) or similar.

Subobjects of this resources class should be extended from the PS2ResourcesSubobject interface if required - this is so they may inspect other resources
on function calls. An example of this is for some R5900 registers (ie: LinkRegister), where they can set other registers automatically.

Note: In order to reduce compile times, try to define the subobjects in cpp files, and use forward delarations where possible (this applies to every object defined in this hierarchy).
*/

class EE_t;
class PS2StorageObject_t;

class PS2Resources_t
{
public:
	explicit PS2Resources_t();

	// The EE structure.
	std::shared_ptr<EE_t> EE;

	// Main Memory (32MB)
	std::shared_ptr<PS2StorageObject_t> MainMemory;

	// Boot ROM (4MB)
	std::shared_ptr<PS2StorageObject_t> BootROM;

private:

};
