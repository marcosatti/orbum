#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/GS/PCRTC/PCRTC_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/GS/GS_t.h"
#include "Resources/GS/PCRTC/PCRTC_t.h"

PCRTC_s::PCRTC_s(VM* vmMain) :
	VMSystem_s(vmMain)
{
	mPCRTC = getVM()->getResources()->GS->PCRTC;
	mClock = getVM()->getResources()->Clock;
	mEEINTC = getVM()->getResources()->EE->INTC;
	mIOPINTC = getVM()->getResources()->IOP->INTC;
}

PCRTC_s::~PCRTC_s()
{
}

void PCRTC_s::run(const double& time)
{
	// Create VM tick event.
	ClockEvent_t vmClockEvent =
	{
		ClockSource_t::PixelClock,
		time / 1.0e6 * mClock->getPixelClockSpeed()
	};
	mClockEventQueue.push(vmClockEvent);

	// Run through events.
	while (!mClockEventQueue.empty())
	{
		auto event = mClockEventQueue.front();
		mClockEventQueue.pop();

		while (event.mNumberTicks >= 1)
		{
			auto ticks = step(event);
			event.mNumberTicks -= ticks;
		}
	}
}

int PCRTC_s::step(const ClockEvent_t& event)
{
	static int col = 0;
	static int row = 0;

	if (col == -1)
	{
		// send hblank end
		// mPCRTC->mInHblank = false;
	}

	col++;

	if (col > 639)
	{
		col = -640;
		
		// send hblank start
		// mPCRTC->mInHblank = true;
		getVM()->getSystem(EETimers)->mClockEventQueue.push({ ClockSource_t::HBlank, 1 });
		getVM()->getSystem(IOPTimers)->mClockEventQueue.push({ ClockSource_t::HBlank, 1 });

		// send pixelclock event to IOPTimers (batch of 640*2)
		getVM()->getSystem(IOPTimers)->mClockEventQueue.push({ ClockSource_t::PixelClock, 640 * 2 });

		// copy scanline to host render.
		// getVM()->renderScanline(&raw_row_pixels);

		if (row == -1)
		{
			// send vblank end
			mEEINTC->STAT->setFieldValue(EEIntcRegister_STAT_t::Fields::VBOF, 1);
			mIOPINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::EVBLANK, 1);
			// mPCRTC->mInVblank = false;
		}

		row++;

		if (row > 223)
		{
			row = -224;

			// send vblank start
			mEEINTC->STAT->setFieldValue(EEIntcRegister_STAT_t::Fields::VBON, 1);
			mIOPINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::VBLANK, 1);
			// mPCRTC->mInVblank = true;

			// tell vm to render frame.
			// getVM()->renderFrame();
		}
	}

	return 1;
}
