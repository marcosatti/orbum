#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
The SIF resources (sub-system interface).
Facilitates communication to and from the EE/IOP. 
No official documentation (for 99%), everything comes from PCSX2's code.
For registers that are allocated in the EE and IOP physical memory space, the descriptions will say at which address for each.
The PS2SDK also contains some information, ie: https://github.com/ps2dev/ps2sdk/blob/master/iop/kernel/include/sifman.h.
*/

class Register32_t;
class ConstantRegister32_t;

class SIF_t : public PS2ResourcesSubobject
{
public:
	explicit SIF_t(const PS2Resources_t *const PS2Resources);

	/*
	SIF Registers.
	*/
	std::shared_ptr<Register32_t>         MSCOM;         // Register "MSCOM"              @ 0x1000F200 (EE) & 0x1D000000 (IOP). Main -> Sub-CPU command buffer.
	std::shared_ptr<Register32_t>         SMCOM;         // Register "SMCOM"              @ 0x1000F210 (EE) & 0x1D000010 (IOP). Sub -> Main-CPU command buffer.
	std::shared_ptr<Register32_t>         MSFLG;         // Register "MSFLAG"             @ 0x1000F220 (EE) & 0x1D000020 (IOP). Main -> Sub-CPU flag.
	std::shared_ptr<Register32_t>         SMFLG;         // Register "SMFLAG"             @ 0x1000F230 (EE) & 0x1D000030 (IOP). Sub -> Main-CPU flag.
	std::shared_ptr<ConstantRegister32_t> REGISTER_0060; // Register "Undocumented: 0060" @ 0x1D000060 (IOP).
};

