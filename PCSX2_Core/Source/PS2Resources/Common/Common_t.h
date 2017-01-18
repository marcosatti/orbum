#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubcategory.h"

class Register32_t;
class FIFOQueue_t;
class Sif2FIFOQueue_t;

/*
Contains common resources needed between the EE/GS/IOP.
*/
class Common_t : public PS2ResourcesSubcategory
{
public:
	explicit Common_t(const PS2Resources_t * PS2Resources);

	/*
	The SIF/SBUS resources (sub-system interface).
	Facilitates communication to and from the EE/IOP.
	No official documentation (for 99%), everything comes from PCSX2's code.
	For registers that are allocated in the EE and IOP physical memory space, the descriptions will say at which address for each.
	The PS2SDK also contains some information, ie: https://github.com/ps2dev/ps2sdk/blob/master/iop/kernel/include/sifman.h.
	*/
	std::shared_ptr<Register32_t> MSCOM;              // Register "MSCOM"              @ 0x1000F200 (EE) & 0x1D000000 (IOP). Main -> Sub-CPU command buffer.
	std::shared_ptr<Register32_t> SMCOM;              // Register "SMCOM"              @ 0x1000F210 (EE) & 0x1D000010 (IOP). Sub -> Main-CPU command buffer.
	std::shared_ptr<Register32_t> MSFLG;              // Register "MSFLAG"             @ 0x1000F220 (EE) & 0x1D000020 (IOP). Main -> Sub-CPU flag.
	std::shared_ptr<Register32_t> SMFLG;              // Register "SMFLAG"             @ 0x1000F230 (EE) & 0x1D000030 (IOP). Sub -> Main-CPU flag.
	std::shared_ptr<Register32_t> SBUS_REGISTER_F240; // Register "Undocumented: F240" @ 0x1000F240 (EE) & 0x1D000040 (IOP).
	std::shared_ptr<Register32_t> SBUS_REGISTER_F250; // Register "Undocumented: F250" @ 0x1000F250 (EE) & 0x1D000050 (IOP).
	std::shared_ptr<Register32_t> SBUS_REGISTER_F260; // Register "Undocumented: F260" @ 0x1000F260 (EE) & 0x1D000060 (IOP).
	std::shared_ptr<Register32_t> SBUS_REGISTER_F300; // Register "Undocumented: F300" @ 0x1000F300 (EE). // TODO: related to psx gpu, investigate (see PCSX2).
	std::shared_ptr<Register32_t> SBUS_REGISTER_F380; // Register "Undocumented: F380" @ 0x1000F380 (EE).

	/*
	FIFO Queue registers, attached to both the EE and IOP DMAC channels.
	SIF2 has a custom FIFO to trigger updates to the SBUS_REGISTER_F3000 defined above (dependency).
	*/
	std::shared_ptr<FIFOQueue_t>     FIFO_VIF0;
	std::shared_ptr<FIFOQueue_t>     FIFO_VIF1;
	std::shared_ptr<FIFOQueue_t>     FIFO_GIF;
	std::shared_ptr<FIFOQueue_t>     FIFO_fromIPU;
	std::shared_ptr<FIFOQueue_t>     FIFO_toIPU;
	std::shared_ptr<FIFOQueue_t>     FIFO_SIF0;
	std::shared_ptr<FIFOQueue_t>     FIFO_SIF1;
	std::shared_ptr<Sif2FIFOQueue_t> FIFO_SIF2;
	std::shared_ptr<FIFOQueue_t>     FIFO_DEBUG;
};

