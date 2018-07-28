#pragma once

#include "Common/Constants.hpp"
#include "Controller/CController.hpp"
#include "Resources/Ee/Dmac/EeDmacChannels.hpp"
#include "Resources/Ee/Dmac/EeDmatag.hpp"

class Core;

/// The EE DMAC system controls the execution of the EE DMAC and transfers through DMA.
/// The EE DMAC is synced to the BUSCLK clock source, and at most transfers a qword (a 128-bit data unit) every tick on slice and burst channels.
/// In a slice physical transfer mode, 8 qwords are transfered before the DMAC releases the bus to the CPU - it waits for a 'DMA request' command before continuing.
/// In a burst physical transfer mode, n qwords are transfered all at once - the CPU must wait for the DMAC to release the bus.
/// If transfering data from memory to a peripheral, it will wait until the data has been received (FIFO size is 0) before interrupting the EE Core.
/// See EE Users Manual page 41 onwards.
/// TODO: Not implemented:
///  - MFIFO handling.
///  - D_ENABLER/W handling.
///  - Cycle stealing.
class CEeDmac : public CController
{
public:
    CEeDmac(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    /// Check through the channels and initate data transfers.
    /// If a channel is enabled for transfer, data units (128-bit) are sent.
    int time_step(const int ticks_available);

    /////////////////////////////////
    // DMAC Logical Mode Functions //
    /////////////////////////////////

    /// Do a normal logical mode transfer through the specified DMA channel.
    bool transfer_normal(EeDmacChannel& channel);

    /// Do a chain logical mode transfer through the specified DMA channel.
    bool transfer_chain(EeDmacChannel& channel);

    /// Do a interleaved logical mode transfer through the specified DMA channel.
    bool transfer_interleaved(EeDmacChannel& channel);

    ///////////////////////////
    // DMAC Helper Functions //
    ///////////////////////////

    /// Checks if there is an DMA transfer interrupt pending, and handles the interrupting of the EE Core (through the INT1 line).
    /// See EE Core Users Manual page 73-75 for the EE Core details. Note that on page 75, there is a typo, where the INTx lines are mixed up on bits 10 and 11 (verified through running through bios code).
    void handle_interrupt_check();

    /// Transfers data units (128-bits) between mem <-> channel.
    /// Returns the number of data units transfered.
    /// On the condition that the channel FIFO is empty (source) or full (drain), returns 0.
    int transfer_data(EeDmacChannel& channel);

    /// Sets the DMAC and channel state for suspend conditions.
    void set_state_suspended(EeDmacChannel& channel);

    /// Sets the DMAC and channel state for failed transfer conditions.
    /// TODO: not yet implemented, throws runtime_error.
    void set_state_failed_transfer(EeDmacChannel& channel);

    //////////////////////////////////////////
    // Raw Memory Transfer Helper Functions //
    //////////////////////////////////////////

    /// Reads a qword from memory using the address given.
    /// spr_access controls if the read is through the EE main memory or the EE Core scratchpad.
    uqword read_qword_memory(const uptr address, const bool spr_access);

    /// Writes a qword to memory using the address given.
    /// spr_access controls if the write is through the EE main memory or the EE Core scratchpad.
    void write_qword_memory(const uptr address, const bool spr_access, const uqword data);

    ////////////////////////////////////
    // Stall Control Helper Functions //
    ////////////////////////////////////

    /// Returns if source stall control checks should occur, by checking the channel direction and D_CTRL.STS.
    bool is_source_stall_control_on(EeDmacChannel& channel);

    /// Returns if drain stall control checks should occur, by checking the channel direction and D_CTRL.STD.
    bool is_drain_stall_control_on(EeDmacChannel& channel);

    /// Returns true if MADR + 8 > STADR, which is the condition a drain channel stalls on with stall control.
    /// Callee is responsible for setting the D_STAT.SIS bit.
    /// TODO: According to the docs, "SIS bit doesn't change even if the transfer restarts"! PS2 OS sets it back to 0?
    bool is_drain_stall_control_waiting(EeDmacChannel& channel);

    /// Sets the DMAC STADR register to the current channel conditions.
    void set_dmac_stall_control_stadr(EeDmacChannel& channel);

    /// Sets the DMAC STAT.SISx bit to the current channel.
    void set_dmac_stall_control_sis();

    /////////////////////////////////
    // Chain Mode Helper Functions //
    /////////////////////////////////

    /// Sets the channel tag read from the TADR register.
    /// Also sets the CHCH.TAG field to bits 16-31 of the DMAtag read. If CHCR.TTE is set, transfers the tag.
    /// Returns if it was successful (true) or not (false) - use to determine if an early exit should occur (need to wait for more data).
    bool read_chain_source_tag(EeDmacChannel& channel);

    /// Sets the channel tag from the DMA queue.
    /// Also sets the CHCH.TAG field to bits 16-31 of the DMAtag read. If CHCR.TTE is set, transfers the tag.
    /// Returns if it was successful (true) or not (false) - use to determine if an early exit should occur (need to wait for more data).
    bool read_chain_dest_tag(EeDmacChannel& channel);

    /// Chain DMAtag handler functions. Consult page 59 - 61 of EE Users Manual.
    void CHAIN_TAGID_UNKNOWN(EeDmacChannel& channel);
    void CHAIN_SRC_CNT(EeDmacChannel& channel);
    void CHAIN_SRC_NEXT(EeDmacChannel& channel);
    void CHAIN_SRC_REF(EeDmacChannel& channel);
    void CHAIN_SRC_REFS(EeDmacChannel& channel);
    void CHAIN_SRC_REFE(EeDmacChannel& channel);
    void CHAIN_SRC_CALL(EeDmacChannel& channel);
    void CHAIN_SRC_RET(EeDmacChannel& channel);
    void CHAIN_SRC_END(EeDmacChannel& channel);
    void CHAIN_DST_CNT(EeDmacChannel& channel);
    void CHAIN_DST_CNTS(EeDmacChannel& channel);
    void CHAIN_DST_END(EeDmacChannel& channel);

    /// Static arrays needed to call the appropriate DMAtag handler function.
    /// There is one for source and destination chain modes. See page 60 and 61 of EE Users Manual for the list of applicable DMAtag instructions.
    void (CEeDmac::*SRC_CHAIN_INSTRUCTION_TABLE[Constants::EE::DMAC::NUMBER_CHAIN_INSTRUCTIONS])(EeDmacChannel& channel) =
        {
            &CEeDmac::CHAIN_SRC_REFE,
            &CEeDmac::CHAIN_SRC_CNT,
            &CEeDmac::CHAIN_SRC_NEXT,
            &CEeDmac::CHAIN_SRC_REF,
            &CEeDmac::CHAIN_SRC_REFS,
            &CEeDmac::CHAIN_SRC_CALL,
            &CEeDmac::CHAIN_SRC_RET,
            &CEeDmac::CHAIN_SRC_END};
    void (CEeDmac::*DST_CHAIN_INSTRUCTION_TABLE[Constants::EE::DMAC::NUMBER_CHAIN_INSTRUCTIONS])(EeDmacChannel& channel) =
        {
            &CEeDmac::CHAIN_DST_CNTS,
            &CEeDmac::CHAIN_DST_CNT,
            &CEeDmac::CHAIN_TAGID_UNKNOWN,
            &CEeDmac::CHAIN_TAGID_UNKNOWN,
            &CEeDmac::CHAIN_TAGID_UNKNOWN,
            &CEeDmac::CHAIN_TAGID_UNKNOWN,
            &CEeDmac::CHAIN_TAGID_UNKNOWN,
            &CEeDmac::CHAIN_DST_END,
        };
};