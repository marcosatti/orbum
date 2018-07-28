#pragma once

#include "Resources/Cdvd/CdvdFifoQueues.hpp"
#include "Resources/Cdvd/CdvdNvrams.hpp"
#include "Resources/Cdvd/CdvdRegisters.hpp"
#include "Resources/Cdvd/CdvdRtc.hpp"

/// CD-ROM / DVD (CDVD) resources that is attached through the IOP.
/// No official documentation - everything comes from PCSX2. Thanks to everyone involved!
/// The registers are assigned to the 0x1F402000 -> 0x1F402FFF space.
/// Notes:
/// - Follows the psx-style cd-rom setup, such as from the no$psx docs (command register, with parameter and response fifo's).
/// - 2 types of command and fifo sets - the S_ and N_ sets.
/// - N_ set controls the raw cd-rom data?
/// - S_ set controls the mechacon?
/// - STATUS controls what the emulator is currently doing: ie: nothing, seeking, reading, etc.
///   This is set upon writing to the N_COMMAND register, where it also resets the INTR_STAT.CmdComplete bit. Use this in order to step the state within the emulator.
///   INTR_STAT.CmdComplete is set upon completion, and the IOP.INTC.CDROM bit is set.
/// - N_2005 needs to be set to 0x4E upon boot (ready), seems to use 0x40 after that, or 0x0 if not ready...
struct RCdvd
{
    RCdvd();

    /// CDVD Registers.
    CdvdRegister_Ns_Command n_command;
    CdvdRegister_Ns_Rdy_Din n_rdy_din;
    CdvdFifoQueue_Ns_Data_Out n_data_out;
    SizedByteRegister break_;
    SizedByteRegister intr_stat;
    SizedByteRegister status;
    SizedByteRegister tray_state;
    SizedByteRegister crt_minute;
    SizedByteRegister crt_second;
    SizedByteRegister crt_frame;
    SizedByteRegister type;
    SizedByteRegister register_2013;
    SizedByteRegister rsv;
    CdvdRegister_Ns_Command s_command;
    CdvdRegister_Ns_Rdy_Din s_rdy_din;
    CdvdFifoQueue_Ns_Data_Out s_data_out;
    SizedByteRegister key_20;
    SizedByteRegister key_21;
    SizedByteRegister key_22;
    SizedByteRegister key_23;
    SizedByteRegister key_24;
    SizedByteRegister key_28;
    SizedByteRegister key_29;
    SizedByteRegister key_2a;
    SizedByteRegister key_2b;
    SizedByteRegister key_2c;
    SizedByteRegister key_30;
    SizedByteRegister key_31;
    SizedByteRegister key_32;
    SizedByteRegister key_33;
    SizedByteRegister key_34;
    SizedByteRegister key_38;
    SizedByteRegister key_xor;
    SizedByteRegister dec_set;

    /// CDVD NVRAM state.
    /// TODO: Assumes the correct bios for now, change to be dynamic later.
    CdvdNvram_000 nvram;

    /// CDVD RTC state.
    CdvdRtc rtc;
};