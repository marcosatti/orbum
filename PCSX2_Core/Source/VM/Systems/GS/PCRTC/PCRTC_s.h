#pragma once

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Types/VMSystem_s.h"

class PCRTC_t;
class Clock_t;
class EEIntc_t;
class IOPIntc_t;

/*
PCRTC system logic.
http://psx-scene.com/forums/f291/gs-mode-selector-development-feedback-61808/
https://en.wikipedia.org/wiki/Phase-locked_loop
SCPH-39001 service manual.

I have no idea how this works, it is based of a guessed pixel clock speed from resX and fH.
See Clock_t for the caluclation.
*/
class PCRTC_s : public VMSystem_s
{
public:
	explicit PCRTC_s(VM * vmMain);
	virtual ~PCRTC_s();

	void run(const double & time) override;

	int step(const ClockEvent_t& event) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<PCRTC_t> mPCRTC;
	std::shared_ptr<Clock_t> mClock;
	std::shared_ptr<EEIntc_t> mEEINTC;
	std::shared_ptr<IOPIntc_t> mIOPINTC;
};