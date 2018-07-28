#include <boost/format.hpp>

#include "Controller/Ee/Dmac/CEeDmac.hpp"
#include "Core.hpp"
#include "Resources/Ee/Dmac/EeDmacChannelRegisters.hpp"
#include "Resources/Ee/Dmac/EeDmacChannels.hpp"

void CEeDmac::CHAIN_TAGID_UNKNOWN(EeDmacChannel& channel)
{
    throw std::runtime_error("EE DMAC chain mode called invalid tag ID");
}

void CEeDmac::CHAIN_SRC_CNT(EeDmacChannel& channel)
{
    // Transfers QWC qwords after the tag, and reads the next qword as the next tag.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Copy TADR + 0x10 into MADR.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + 0x10);
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR));

    // Calculate where the next tag will be. SPR flag unchanged within TADR register.
    uword next_tag_addr = channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + (channel.chcr->dma_tag.qwc() + 1) * 0x10;
    channel.tadr->insert_field(EeDmacChannelRegister_Addr::ADDR, next_tag_addr);
}

void CEeDmac::CHAIN_SRC_NEXT(EeDmacChannel& channel)
{
    // Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Copy TADR + 0x10 into MADR.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + 0x10);
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR));

    // Set next tag.
    channel.tadr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.tadr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());
}

void CEeDmac::CHAIN_SRC_REF(EeDmacChannel& channel)
{
    // Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Set MADR = tag.ADDR.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());

    // Set next qword as tag. SPR flag unchanged within TADR register.
    channel.tadr->offset(NUMBER_BYTES_IN_QWORD);
}

void CEeDmac::CHAIN_SRC_REFS(EeDmacChannel& channel)
{
    // Set stall control to on (STADR is updated within the main DMAC logic).
    channel.chcr->tag_stall = true;

    // Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Set MADR = tag.ADDR.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());

    // Set next qword as tag.
    channel.tadr->offset(NUMBER_BYTES_IN_QWORD); // SPR flag unchanged within TADR register.
}

void CEeDmac::CHAIN_SRC_REFE(EeDmacChannel& channel)
{
    // Transfers QWC qwords from ADDR, and suspends after packet transfer.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());

    // Not documented: REFE requires that TADR be incremented after ending. See PCSX2's "Hw.cpp".
    channel.tadr->offset(NUMBER_BYTES_IN_QWORD);

    // Set channel exit state.
    channel.chcr->tag_exit = true;
}

void CEeDmac::CHAIN_SRC_CALL(EeDmacChannel& channel)
{
    // Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + 0x10);
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR));
    channel.tadr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.tadr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());

    // Check for stack overflow, else push the stack. It is assumed that a stack overflow causes an exit (like underflow in 'ret').
    uword asp = channel.chcr->extract_field(EeDmacChannelRegister_Chcr::ASP);
    if (asp >= 2)
    {
        channel.chcr->tag_exit = true;
        BOOST_LOG(Core::get_logger()) << boost::format("EE DMAC Channel %d had chain mode stack overflow! Exiting transfer. TADR has been changed.")
                                             % (*channel.channel_id);
    }
    else
    {
        (*channel.asr)[asp].insert_field(EeDmacChannelRegister_Addr::ADDR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + 0x10);
        (*channel.asr)[asp].insert_field(EeDmacChannelRegister_Addr::SPR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR));
        channel.chcr->insert_field(EeDmacChannelRegister_Chcr::ASP, asp + 1);
    }
}

void CEeDmac::CHAIN_SRC_RET(EeDmacChannel& channel)
{
    // Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.

    // Check for stack underflow, else pop the stack.
    uword asp = channel.chcr->extract_field(EeDmacChannelRegister_Chcr::ASP);
    if (asp == 0)
    {
        channel.chcr->tag_exit = true;
        BOOST_LOG(Core::get_logger()) << boost::format("EE DMAC Channel %d had chain mode stack underflow! Exiting transfer. TADR left unchanged.")
                                             % (*channel.channel_id);
    }
    else
    {
        channel.tadr->insert_field(EeDmacChannelRegister_Addr::ADDR, (*channel.asr)[asp].extract_field(EeDmacChannelRegister_Addr::ADDR));
        channel.tadr->insert_field(EeDmacChannelRegister_Addr::ADDR, (*channel.asr)[asp].extract_field(EeDmacChannelRegister_Addr::SPR));
        channel.chcr->insert_field(EeDmacChannelRegister_Chcr::ASP, asp - 1);
    }

    // In both cases, QWC following the tag is always performed.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + 0x10);
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR));
}

void CEeDmac::CHAIN_SRC_END(EeDmacChannel& channel)
{
    // Transfers QWC qwords after tag, and suspends after packet transfer.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR) + 0x10);
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR));

    // Set channel exit state.
    channel.chcr->tag_exit = true;
}

void CEeDmac::CHAIN_DST_CNT(EeDmacChannel& channel)
{
    // Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Set MADR to tag values.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());
}

void CEeDmac::CHAIN_DST_CNTS(EeDmacChannel& channel)
{
    // Set stall control to on (STADR is updated within the main DMAC logic).
    channel.chcr->tag_stall = true;

    // Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Set MADR to tag values.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());
}

void CEeDmac::CHAIN_DST_END(EeDmacChannel& channel)
{
    // Transfers QWC qwords after the tag to tag.ADDR, and suspends transfer after completing.
    channel.qwc->write_uword(channel.chcr->dma_tag.qwc());

    // Set MADR to tag values.
    channel.madr->insert_field(EeDmacChannelRegister_Addr::ADDR, channel.chcr->dma_tag.addr());
    channel.madr->insert_field(EeDmacChannelRegister_Addr::SPR, channel.chcr->dma_tag.spr());
    channel.chcr->tag_exit = true;
}