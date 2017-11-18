#pragma once



#include "VM/VM.h"
#include "VM/Types/VMSystem_t.h"

class RCrtc;
class Events_t;
class REeIntc;
class RIopIntc;

/*
PCRTC system logic.
http://psx-scene.com/forums/f291/gs-mode-selector-development-feedback-61808/
https://en.wikipedia.org/wiki/Phase-locked_loop
SCPH-39001 service manual.

TODO: I have no idea how this works, it is based of guessed logic and pixel clock speed from resX and fH. Read through the GS mode selector docs above / general info on CRTC's.
*/
class CRTC_s : public VMSystem_t
{
public:
	CRTC_s(VM * vm);
	virtual ~CRTC_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the CRTC, incrementing the number of pixels based on the CRTC configuration.
	When a row of pixels has been completed (scanline), copy's the row to the VM buffer and sends a HBlank clock event to EE/IOP Timers.
	When a whole frame/field has been completed, calls the VM render function and sends a VBlank start/end interrupt to the EE/IOP Intc.
	*/
	int step(const Event_t & event) override;

	/*
	Resources.
	*/
	RCrtc mCRTC;
	Events_t mEvents;
	REeIntc mEEINTC;
	RIopIntc mIOPINTC;
};