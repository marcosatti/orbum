

#include "VM/Systems/EE/DMAC/EEDmac_s.h"

#include "Resources/Ee/Dmac/EeDmacChannelRegisters.hpp"
#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Resources/EE/DMAC/Types/EeDmaTag.h"

void EEDmac_s::CHAIN_TAGID_UNKNOWN()
{
	throw std::runtime_error("EE DMAC chain mode called invalid tag ID");
}

void EEDmac_s::CHAIN_SRC_CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR));

	// Calculate where the next tag will be. SPR flag unchanged within TADR register.
	uword nextTagAddr = mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + (mDMAtag.getQWC() + 1) * 0x10;
	mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::ADDR, nextTagAddr);
}

void EEDmac_s::CHAIN_SRC_NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR));

	// Set next tag.
	mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::SPR, mDMAtag.getSPR());
}

void EEDmac_s::CHAIN_SRC_REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mDMAtag.getSPR());

	// Set next qword as tag. SPR flag unchanged within TADR register.
	mChannel->TADR->increment(); 
}

void EEDmac_s::CHAIN_SRC_REFS()
{
	// Set stall control to on (STADR is updated within the main DMAC logic).
	mChannel->CHCR->tag_stall = true;

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->increment(); // SPR flag unchanged within TADR register.
}

void EEDmac_s::CHAIN_SRC_REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	mChannel->QWC->write_uword(mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mDMAtag.getSPR());

	// Not documented: REFE requires that TADR be incremented after ending. See PCSX2's "Hw.cpp".
	mChannel->TADR->increment();

	// Set channel exit state.
	mChannel->CHCR->tag_exit = true;
}

void EEDmac_s::CHAIN_SRC_CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	mChannel->QWC->write_uword(mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR));
	mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::SPR, mDMAtag.getSPR());

	// Check for stack overflow, else push the stack. It is assumed that a stack overflow causes an exit (like underflow in 'ret').
	uword ASP = mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::ASP);
	if (ASP >= 2)
	{
		mChannel->CHCR->tag_exit = true;
		log(Warning, "EE DMAC Channel %s had chain mode stack overflow! Exiting transfer. TADR has been changed.", mChannel->getInfo()->mMnemonic);
	}
	else
	{
		mChannel->ASR[ASP]->setFieldValue(, EEDmacChannelRegister_ASR_t::ADDR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + 0x10);
		mChannel->ASR[ASP]->setFieldValue(, EEDmacChannelRegister_ASR_t::SPR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR));
		mChannel->CHCR->setFieldValue(, EeDmacChannelRegister_Chcr::ASP, ASP + 1);
	}
}

void EEDmac_s::CHAIN_SRC_RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.

	// Check for stack underflow, else pop the stack.
	uword ASP = mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::ASP);
	if (ASP == 0)
	{
		mChannel->CHCR->tag_exit = true;
		log(Warning, "EE DMAC Channel %s had chain mode stack underflow! Exiting transfer. TADR left unchanged.", mChannel->getInfo()->mMnemonic);
	}
	else
	{
		mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::ADDR, mChannel->ASR[ASP]->getFieldValue(, EEDmacChannelRegister_ASR_t::ADDR));
		mChannel->TADR->setFieldValue(, EEDmacChannelRegister_TADR_t::ADDR, mChannel->ASR[ASP]->getFieldValue(, EEDmacChannelRegister_ASR_t::SPR));
		mChannel->CHCR->setFieldValue(, EeDmacChannelRegister_Chcr::ASP, ASP - 1);
	}

	// In both cases, QWC following the tag is always performed.
	mChannel->QWC->write_uword(mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR));
}

void EEDmac_s::CHAIN_SRC_END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	mChannel->QWC->write_uword(mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR));

	// Set channel exit state.
	mChannel->CHCR->tag_exit = true;
}

void EEDmac_s::CHAIN_DST_CNT()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mDMAtag.getSPR());
}

void EEDmac_s::CHAIN_DST_CNTS()
{
	// Set stall control to on (STADR is updated within the main DMAC logic).
	mChannel->CHCR->tag_stall = true;

	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mDMAtag.getSPR());
}

void EEDmac_s::CHAIN_DST_END()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and suspends transfer after completing.
	mChannel->QWC->write_uword(mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(, EEDmacChannelRegister_MADR_t::SPR, mDMAtag.getSPR());
	mChannel->CHCR->tag_exit = true;
}