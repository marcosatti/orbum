#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/EE/DMAC/EEDmac_s.h"

#include "Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Resources/EE/DMAC/Types/EEDMAtag_t.h"

void EEDmac_s::CHAIN_TAGID_UNKNOWN()
{
	throw std::runtime_error("EE DMAC chain mode called invalid tag ID");
}

void EEDmac_s::CHAIN_SRC_CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Calculate where the next tag will be. SPR flag unchanged within TADR register.
	u32 nextTagAddr = mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + (mDMAtag.getQWC() + 1) * 0x10;
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, nextTagAddr);
}

void EEDmac_s::CHAIN_SRC_NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Set next tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getSPR());
}

void EEDmac_s::CHAIN_SRC_REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag. SPR flag unchanged within TADR register.
	mChannel->TADR->increment(); 
}

void EEDmac_s::CHAIN_SRC_REFS()
{
	// Set stall control to on (STADR is updated within the main DMAC logic).
	mChannel->CHCR->mTagStallControl = true;

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->increment(); // SPR flag unchanged within TADR register.
}

void EEDmac_s::CHAIN_SRC_REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Not documented: REFE requires that TADR be incremented after ending. See PCSX2's "Hw.cpp".
	mChannel->TADR->increment();

	// Set channel exit state.
	mChannel->CHCR->mTagExit = true;
}

void EEDmac_s::CHAIN_SRC_CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, mDMAtag.getSPR());

	// Check for stack overflow, else push the stack. It is assumed that a stack overflow causes an exit (like underflow in 'ret').
	u32 ASP = mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::ASP);
	if (ASP >= 2)
	{
		mChannel->CHCR->mTagExit = true;
		log(Warning, "EE DMAC Channel %s had chain mode stack overflow! Exiting transfer. TADR has been changed.", mChannel->getChannelInfo()->mMnemonic);
	}
	else
	{
		mChannel->ASR[ASP]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
		mChannel->ASR[ASP]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
		mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::ASP, ASP + 1);
	}
}

void EEDmac_s::CHAIN_SRC_RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.

	// Check for stack underflow, else pop the stack.
	u32 ASP = mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::ASP);
	if (ASP == 0)
	{
		mChannel->CHCR->mTagExit = true;
		log(Warning, "EE DMAC Channel %s had chain mode stack underflow! Exiting transfer. TADR left unchanged.", mChannel->getChannelInfo()->mMnemonic);
	}
	else
	{
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->ASR[ASP]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR));
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->ASR[ASP]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR));
		mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::ASP, ASP - 1);
	}

	// In both cases, QWC following the tag is always performed.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
}

void EEDmac_s::CHAIN_SRC_END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Set channel exit state.
	mChannel->CHCR->mTagExit = true;
}

void EEDmac_s::CHAIN_DST_CNT()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac_s::CHAIN_DST_CNTS()
{
	// Set stall control to on (STADR is updated within the main DMAC logic).
	mChannel->CHCR->mTagStallControl = true;

	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac_s::CHAIN_DST_END()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and suspends transfer after completing.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->CHCR->mTagExit = true;
}