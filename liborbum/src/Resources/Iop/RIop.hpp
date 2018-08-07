#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Core/RIopCore.hpp"
#include "Resources/Iop/Dmac/RIopDmac.hpp"
#include "Resources/Iop/Intc/RIopIntc.hpp"
#include "Resources/Iop/Sio0/RSio0.hpp"
#include "Resources/Iop/Sio2/RSio2.hpp"
#include "Resources/Iop/Timers/RIopTimers.hpp"

/// Describes the IOP, also known as the subsystem (interfaced through the SIF).
/// Used for I/O operations as well as the PS1 mode. There is no official documentation -
/// some online resources exist for the PS1 which can help with certain parts, but
/// otherwise it has been reversed engineered. Big props to PCSX2 and No$PSX docs -
/// most of the implementation is based off their work.
class RIop
{
public:
    RIop();

    /// Sub resources.
    RIopCore core;
    RIopDmac dmac;
    RIopIntc intc;
    RIopTimers timers;
    RSio0 sio0;
    RSio2 sio2;

    /// The IOP physical memory space.
    ByteBus<uptr> bus;

    /// IOP Main Memory (2MB).
    ArrayByteMemory main_memory;

    /// IOP Parallel Port IO (64KB).
    ArrayByteMemory parallel_port;

    /// IOP misc memory/registers.
    SizedWordRegister hw_ssbus_spd_addr;
    SizedWordRegister hw_ssbus_pio_addr;
    SizedWordRegister hw_ssbus_spd_delay;
    SizedWordRegister hw_ssbus_dev1_delay;
    SizedWordRegister hw_ssbus_rom_delay;
    SizedWordRegister hw_ssbus_spu_delay;
    SizedWordRegister hw_ssbus_dev5_delay;
    SizedWordRegister hw_ssbus_pio_delay;
    SizedWordRegister hw_ssbus_com_delay;
    SizedWordRegister hw_ram_size;
    SizedWordRegister hw_ssbus_dev1_addr;
    SizedWordRegister hw_ssbus_spu_addr;
    SizedWordRegister hw_ssbus_dev5_addr;
    SizedWordRegister hw_ssbus_spu1_addr;
    SizedWordRegister hw_ssbus_dev9_addr3;
    SizedWordRegister hw_ssbus_spu1_delay;
    SizedWordRegister hw_ssbus_dev9_delay2;
    SizedWordRegister hw_ssbus_dev9_delay3;
    SizedWordRegister hw_ssbus_dev9_delay1;
    SizedWordRegister hw_icfg;
    SizedWordRegister register_1470;
    SizedWordRegister register_1560;
    SizedWordRegister register_1564;
    SizedWordRegister register_1568;
    SizedWordRegister register_15f0;
    SizedWordRegister register_2070;
    SizedWordRegister register_3800;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(core),
            CEREAL_NVP(dmac),
            CEREAL_NVP(intc),
            CEREAL_NVP(timers),
            CEREAL_NVP(sio0),
            CEREAL_NVP(sio2),
            CEREAL_NVP(main_memory),
            CEREAL_NVP(parallel_port),
            CEREAL_NVP(hw_ssbus_spd_addr),
            CEREAL_NVP(hw_ssbus_pio_addr),
            CEREAL_NVP(hw_ssbus_spd_delay),
            CEREAL_NVP(hw_ssbus_dev1_delay),
            CEREAL_NVP(hw_ssbus_rom_delay),
            CEREAL_NVP(hw_ssbus_spu_delay),
            CEREAL_NVP(hw_ssbus_dev5_delay),
            CEREAL_NVP(hw_ssbus_pio_delay),
            CEREAL_NVP(hw_ssbus_com_delay),
            CEREAL_NVP(hw_ram_size),
            CEREAL_NVP(hw_ssbus_dev1_addr),
            CEREAL_NVP(hw_ssbus_spu_addr),
            CEREAL_NVP(hw_ssbus_dev5_addr),
            CEREAL_NVP(hw_ssbus_spu1_addr),
            CEREAL_NVP(hw_ssbus_dev9_addr3),
            CEREAL_NVP(hw_ssbus_spu1_delay),
            CEREAL_NVP(hw_ssbus_dev9_delay2),
            CEREAL_NVP(hw_ssbus_dev9_delay3),
            CEREAL_NVP(hw_ssbus_dev9_delay1),
            CEREAL_NVP(hw_icfg),
            CEREAL_NVP(register_1470),
            CEREAL_NVP(register_1560),
            CEREAL_NVP(register_1564),
            CEREAL_NVP(register_1568),
            CEREAL_NVP(register_15f0),
            CEREAL_NVP(register_2070),
            CEREAL_NVP(register_3800)
        );
    }
};
