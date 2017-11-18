

#include "VM/Systems/GS/CRTC/CRTC_s.h"

#include "Resources/RResources.hpp"
#include "Resources/Events/Events_t.h"
#include "Resources/Ee/REe.hpp"
#include "Resources/Ee/Intc/REeIntc.hpp"
#include "Resources/Ee/Intc/EeIntcRegisters.hpp"
#include "Resources/IOP/IOP_t.h"
#include "Resources/Iop/Intc/RIopIntc.hpp"
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
			mEEINTC->STAT->setFieldValue(, EeIntcRegister_Stat::VBOF, 1);
			mIOPINTC->STAT->setFieldValue(, IOPIntcRegister_STAT_t::EVBLANK, 1);
			// mCRTC->mInVBlank = false;
		}

		row++;

		if (row > 223)
		{
			row = -224;

			// Send VBlank start.
			mEEINTC->STAT->setFieldValue(, EeIntcRegister_Stat::VBON, 1);
			mIOPINTC->STAT->setFieldValue(, IOPIntcRegister_STAT_t::VBLANK, 1);
			// mCRTC->mInVBlank = true;

			// Tell VM to render frame.
			// getVM()->renderFrame();
		}
	}

	return 1;
}
