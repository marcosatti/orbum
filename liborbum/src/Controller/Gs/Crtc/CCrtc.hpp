#pragma once

#include "Controller/CController.hpp"

class Core;

/// PCRTC system logic.
/// http://psx-scene.com/forums/f291/gs-mode-selector-development-feedback-61808/
/// https://en.wikipedia.org/wiki/Phase-locked_loop
/// SCPH-39001 service manual.
/// TODO: I have no idea how this works, it is based of guessed logic and pixel clock speed from resX and fH.
///       Read through the GS mode selector docs above / general info on CRTC's.
class CCrtc : public CController
{
public:
    CCrtc(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    /// Steps through the CRTC, incrementing the number of pixels based on the CRTC configuration.
    /// When a row of pixels has been completed (scanline), copy's the row to the VM buffer and sends a HBlank clock event to EE/IOP Timers.
    /// When a whole frame/field has been completed, calls the VM render function and sends a VBlank start/end interrupt to the EE/IOP Intc.
    int time_step(const int ticks_available);
};