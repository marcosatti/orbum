#include "Common/Global/Globals.h"

#include "VM/Systems/GS/CRTC/CRTC_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Events/Events_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/GS/GS_t.h"
#include "Resources/GS/CRTC/CRTC_t.h"

CRTC_s::CRTC_s(VM * vm) :
	VMSystem_t(vm, Context_t::CRTC)
{
	mCRTC = getVM()->getResources()->GS->CRTC;
	mEvents = getVM()->getResources()->Events;
	mEEINTC = getVM()->getResources()->EE->INTC;
	mIOPINTC = getVM()->getResources()->IOP->INTC;
}

void CRTC_s::initialise()
{
}

int CRTC_s::step(const Event_t & event)
{
	static int col = 0;
	static int row = 0;

	if (col == -1)
	{
		// Send HBlank end.
		// mCRTC->mInHBlank = false;
	}

	col++;

	if (col > 639)
	{
		col = -640;
		
		// Send HBlank start.
		// mCRTC->mInHblank = true;
		mEvents->addEvent(Context_t::EETimers, Event_t(Event_t::Source::HBlank, 1));
		mEvents->addEvent(Context_t::IOPTimers, Event_t(Event_t::Source::HBlank, 1));

		// Copy scanline to host render.
		// getVM()->renderScanline(&raw_row_pixels);

		if (row == -1)
		{
			// Send VBlank end.
			mEEINTC->STAT->setFieldValue(getContext(), EEIntcRegister_STAT_t::Fields::VBOF, 1);
			mIOPINTC->STAT->setFieldValue(getContext(), IOPIntcRegister_STAT_t::Fields::EVBLANK, 1);
			// mCRTC->mInVBlank = false;
		}

		row++;

		if (row > 223)
		{
			row = -224;

			// Send VBlank start.
			mEEINTC->STAT->setFieldValue(getContext(), EEIntcRegister_STAT_t::Fields::VBON, 1);
			mIOPINTC->STAT->setFieldValue(getContext(), IOPIntcRegister_STAT_t::Fields::VBLANK, 1);
			// mCRTC->mInVBlank = true;

			// Tell VM to render frame.
			// getVM()->renderFrame();
		}
	}

	return 1;
}
