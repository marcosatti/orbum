#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/ScopeLock.hpp"
#include "Resources/Ee/Dmac/EeDmatag.hpp"

/// The DMAC D_CHCR register, aka channel control register.
/// Register should be scope locked by the DMAC controller.
/// TODO: some of the tag variables might be redundant when also considering the TAG bits - look into,
///       but to future self: it was messy, things didn't map 1-to-1.
class EeDmacChannelRegister_Chcr : public SizedWordRegister, public ScopeLock
{
public:
    enum class Direction
    {
        // Ordered according to CHCR.DIR. Relative to FIFO's perspective.
        FROM = 0,
        TO = 1
    };

    enum class LogicalMode
    {
        // Ordered according to CHCR.MOD.
        NORMAL = 0,
        CHAIN = 1,
        INTERLEAVED = 2
    };

    static constexpr Bitfield DIR = Bitfield(0, 1);
    static constexpr Bitfield MOD = Bitfield(2, 2);
    static constexpr Bitfield ASP = Bitfield(4, 2);
    static constexpr Bitfield TTE = Bitfield(6, 1);
    static constexpr Bitfield TIE = Bitfield(7, 1);
    static constexpr Bitfield STR = Bitfield(8, 1);
    static constexpr Bitfield TAG = Bitfield(16, 16);

    EeDmacChannelRegister_Chcr();

    /// Returns the channel runtime logical mode its operating in.
    LogicalMode get_logical_mode();

    /// Returns the runtime direction. Useful for channels where it can be either way.
    Direction get_direction();

    /// Resets the flags below when STR = 1 is written.
    void write_uword(const uword value) override;

    /// Scope locked for entire duration.
    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

    /// DMA started flag. Used to indicate if a DMA transfer is in progress, in order for the DMAC to perform some initial and final checks.
    /// An example of the DMAC using this is to check for an initial invalid transfer length.
    /// Reset to false upon writing to this register.
    bool dma_started;

    /// Tag exit flag. Within DMAC logic, set to true when an exit tag is encountered, and use to check whether to exit from a DMA transfer.
    /// Reset to false upon writing to this register.
    bool tag_exit;

    /// Tag stall control flag. Within DMAC logic, set to true when an stall control tag is encountered, and use to check whether to update STADR or skip a cycle.
    /// Reset to false upon writing to this register.
    bool tag_stall;

    /// Tag IRQ flag. Within DMAC logic, set this to true when the IRQ flag is set, and use to check whether to interrupt on finishing the tag transfer.
    /// Reset to false upon writing to this register.
    bool tag_irq;

    /// DMAtag holder, contains the current dma tag read, set by the DMAC.
    /// TODO: might be a way to omit this and just use the upper 16-bits, but for now extra information is required.
    EeDmatag dma_tag;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            cereal::base_class<SizedWordRegister>(this),
            CEREAL_NVP(dma_started),
            CEREAL_NVP(tag_exit),
            CEREAL_NVP(tag_stall),
            CEREAL_NVP(tag_irq),
            CEREAL_NVP(dma_tag),
        );
    }
};

/// DMAC ADDR (made up) register, used by the MADR, TADR and ASR registers.
/// Contains the DMA transfer address and scratchpad access bit.
class EeDmacChannelRegister_Addr : public SizedWordRegister
{
public:
    static constexpr Bitfield ADDR = Bitfield(0, 31);
    static constexpr Bitfield SPR = Bitfield(31, 1);
};

/// A base EE TO DMAC D_CHCR register, aka channel control register.
/// Sets the constant direction (TO) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
class EeDmacChannelRegister_Chcr_To : public EeDmacChannelRegister_Chcr
{
public:
    /// Upon writes, sets the correct direction (TO).
    void write_uword(const uword value) override;
};

/// A base EE FROM DMAC D_CHCR register, aka channel control register.
/// Sets the constant direction (FROM) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
class EeDmacChannelRegister_Chcr_From : public EeDmacChannelRegister_Chcr
{
public:
    /// Upon writes, sets the correct direction (FROM).
    void write_uword(const uword value) override;
};

/// The SIF0 DMAC D_CHCR register, aka channel control register.
/// SIF0 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
/// As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
/// TODO: Look into properly RE'ing the SBUS.
class EeDmacChannelRegister_Chcr_Sif0 : public EeDmacChannelRegister_Chcr_From
{
public:
    EeDmacChannelRegister_Chcr_Sif0();

    /// Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
    /// See PCSX2's "sif0.cpp".
    void write_uword(const uword value) override;

    /// Reference to the SBUS_F240 register.
    SizedWordRegister* sbus_f240;

private:
    /// Contains logic for updating the SBUS registers.
    /// One function for ending a transfer - a starting function should never be called as this is fixed in the FROM direction.
    void handle_sbus_update_finish() const;
};

/// The SIF1 DMAC D_CHCR register, aka channel control register.
/// SIF1 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
/// As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
/// TODO: Look into properly RE'ing the SBUS.
class EeDmacChannelRegister_Chcr_Sif1 : public EeDmacChannelRegister_Chcr_To
{
public:
    EeDmacChannelRegister_Chcr_Sif1();

    /// Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
    /// See PCSX2's "sif1.cpp".
    void write_uword(const uword value) override;

    /// Reference to the SBUS_F240 register.
    SizedWordRegister* sbus_f240;

private:
    /// Contains logic for updating the SBUS registers.
    /// One function for starting a transfer - a ending function should never be called as this is fixed in the TO direction.
    void handle_sbus_update_start() const;
};

/// The SIF2 DMAC D_CHCR register, aka channel control register.
/// SIF2 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
/// As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
/// TODO: Look into properly RE'ing the SBUS.
class EeDmacChannelRegister_Chcr_Sif2 : public EeDmacChannelRegister_Chcr
{
public:
    EeDmacChannelRegister_Chcr_Sif2();

    /// Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required. See PCSX2's "sif2.cpp".
    void write_uword(const uword value) override;

    /// Reference to the SBUS_F240 register.
    SizedWordRegister* sbus_f240;

private:
    /// Contains logic for updating the SBUS registers.
    /// One function for starting a transfer, and ending a transfer.
    void handle_sbus_update_start() const;
    void handle_sbus_update_finish() const;
};
