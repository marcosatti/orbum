#pragma once

#include <memory>

class SBUSRegister_MSCOM_t;
class SBUSRegister_MSFLG_t;
class SBUSRegister_SMFLG_t;
class SBUSRegister_F240_t;
class SBUSRegister_F300_t;
class Register32_t;
class ConstantRegister32_t;
class FIFOQueue32_t;
class SBUSFIFOQueue_SIF2_t;

/*
Contains common resources needed between the EE/GS/IOP.
*/
class Common_t
{
public:
	Common_t();

	/*
	The SBUS/SIF resources (sub-system interface).
	Facilitates communication to and from the EE/IOP.
	No official documentation (for 99%), everything comes from PCSX2's code.
	The PS2SDK also contains some information, ie: https://github.com/ps2dev/ps2sdk/blob/master/iop/kernel/include/sifman.h.
	*/
	std::shared_ptr<SBUSRegister_MSCOM_t> SBUS_MSCOM; // Register "MSCOM"              @ 0x1000F200 (EE) & 0x1D000000 (IOP). Main -> Sub-CPU command buffer.
	std::shared_ptr<Register32_t>         SBUS_SMCOM; // Register "SMCOM"              @ 0x1000F210 (EE) & 0x1D000010 (IOP). Sub -> Main-CPU command buffer.
	std::shared_ptr<SBUSRegister_MSFLG_t> SBUS_MSFLG; // Register "MSFLAG"             @ 0x1000F220 (EE) & 0x1D000020 (IOP). Main -> Sub-CPU flag. Writes OR with the previous value.
	std::shared_ptr<SBUSRegister_SMFLG_t> SBUS_SMFLG; // Register "SMFLAG"             @ 0x1000F230 (EE) & 0x1D000030 (IOP). Sub -> Main-CPU flag. Writes NOT AND (clears) with the previous value.
	std::shared_ptr<SBUSRegister_F240_t>  SBUS_F240;  // Register "Undocumented: F240" @ 0x1000F240 (EE) & 0x1D000040 (IOP). Manipulates reads/writes with magic values.
	std::shared_ptr<Register32_t>         SBUS_F250;  // Register "Undocumented: F250" @ 0x1000F250 (EE) & 0x1D000050 (IOP).
	std::shared_ptr<ConstantRegister32_t> SBUS_F260;  // Register "Undocumented: F260" @ 0x1000F260 (EE) & 0x1D000060 (IOP). Always set to 0.
	std::shared_ptr<SBUSRegister_F300_t>  SBUS_F300;  // Register "Undocumented: F300" @ 0x1000F300 (EE). // TODO: related to psx sif2/gpu? Investigate (see PCSX2).
	std::shared_ptr<Register32_t>         SBUS_F380;  // Register "Undocumented: F380" @ 0x1000F380 (EE).

	/*
	FIFO Queue registers, attached to both the EE and IOP DMAC channels.
	SIF2 has a custom FIFO to trigger updates to the SBUS_REGISTER_F3000 defined above (dependency).
	*/
	static constexpr int DEBUG_FIFO_SIZE = 4 * 128;
	std::shared_ptr<FIFOQueue32_t>          FIFO_VIF0;
	std::shared_ptr<FIFOQueue32_t>          FIFO_VIF1;
	std::shared_ptr<FIFOQueue32_t>          FIFO_GIF;
	std::shared_ptr<FIFOQueue32_t>          FIFO_fromIPU;
	std::shared_ptr<FIFOQueue32_t>          FIFO_toIPU;
	std::shared_ptr<FIFOQueue32_t>          FIFO_SIF0;
	std::shared_ptr<FIFOQueue32_t>          FIFO_SIF1;
	std::shared_ptr<SBUSFIFOQueue_SIF2_t>   FIFO_SIF2;
	std::shared_ptr<FIFOQueue32_t>          FIFO_fromMDEC;
	std::shared_ptr<FIFOQueue32_t>          FIFO_toMDEC;
	std::shared_ptr<FIFOQueue32_t>          FIFO_CDROM;
	std::shared_ptr<FIFOQueue32_t>          FIFO_SPU2C0;
	std::shared_ptr<FIFOQueue32_t>          FIFO_PIO;
	std::shared_ptr<FIFOQueue32_t>          FIFO_OTClear;
	std::shared_ptr<FIFOQueue32_t>          FIFO_SPU2C1;
	std::shared_ptr<FIFOQueue32_t>          FIFO_DEV9;
	std::shared_ptr<FIFOQueue32_t>          FIFO_fromSIO2;
	std::shared_ptr<FIFOQueue32_t>          FIFO_toSIO2;
};

