#pragma once

#include <memory>

class SBUSRegister_MSCOM_t;
class SBUSRegister_MSFLG_t;
class SBUSRegister_SMFLG_t;
class SBUSRegister_F240_t;
class SBUSRegister_F300_t;
class Register32_t;
class ConstantRegister32_t;
class FIFOQueue_t;
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
	std::shared_ptr<SBUSRegister_MSCOM_t> SBUS_MSCOM; // Main -> Sub-CPU command buffer.
	std::shared_ptr<Register32_t>         SBUS_SMCOM; // Sub -> Main-CPU command buffer.
	std::shared_ptr<SBUSRegister_MSFLG_t> SBUS_MSFLG; // Writes OR with the previous value.
	std::shared_ptr<SBUSRegister_SMFLG_t> SBUS_SMFLG; // Writes NOT AND (clears) with the previous value.
	std::shared_ptr<SBUSRegister_F240_t>  SBUS_F240;  // Manipulates reads/writes with magic values.
	std::shared_ptr<Register32_t>         SBUS_F250;  
	std::shared_ptr<ConstantRegister32_t> SBUS_F260;  // Always set to 0.
	std::shared_ptr<SBUSRegister_F300_t>  SBUS_F300;  // TODO: related to psx sif2/gpu? Investigate (see PCSX2).
	std::shared_ptr<Register32_t>         SBUS_F380;  

	/*
	FIFO Queue registers, attached to both the EE and IOP DMAC channels.
	SIF2 has a custom FIFO to trigger updates to the SBUS_REGISTER_F3000 defined above (dependency).
	*/
	static constexpr int DEBUG_FIFO_SIZE = 4 * 128 * 16;
	std::shared_ptr<FIFOQueue_t>          FIFO_VIF0;
	std::shared_ptr<FIFOQueue_t>          FIFO_VIF1;
	std::shared_ptr<FIFOQueue_t>          FIFO_GIF;
	std::shared_ptr<FIFOQueue_t>          FIFO_fromIPU;
	std::shared_ptr<FIFOQueue_t>          FIFO_toIPU;
	std::shared_ptr<FIFOQueue_t>          FIFO_SIF0;
	std::shared_ptr<FIFOQueue_t>          FIFO_SIF1;
	std::shared_ptr<SBUSFIFOQueue_SIF2_t> FIFO_SIF2;
	std::shared_ptr<FIFOQueue_t>          FIFO_fromMDEC;
	std::shared_ptr<FIFOQueue_t>          FIFO_toMDEC;
	std::shared_ptr<FIFOQueue_t>          FIFO_CDROM;
	std::shared_ptr<FIFOQueue_t>          FIFO_SPU2C0;
	std::shared_ptr<FIFOQueue_t>          FIFO_PIO;
	std::shared_ptr<FIFOQueue_t>          FIFO_OTClear;
	std::shared_ptr<FIFOQueue_t>          FIFO_SPU2C1;
	std::shared_ptr<FIFOQueue_t>          FIFO_DEV9;
	std::shared_ptr<FIFOQueue_t>          FIFO_fromSIO2;
	std::shared_ptr<FIFOQueue_t>          FIFO_toSIO2;
};

