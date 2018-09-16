#pragma once

#include <utility>

#include "Common/Types/Primitive.hpp"
#include "Controller/CController.hpp"
#include "Resources/Ee/Gif/Giftag.hpp"

/// GIF interface, controls data between the EE (EE Core, VPU1) to the GS.
class CGif : public CController
{
public:
    CGif(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    int time_step(const int ticks_available);

    /// Handle the initial processing of a GIFtag. For tag details, see EE Users
    /// manual page 151.
    /// Note: consumes 2 cycles when the PRE bit is set and FLG is set to packed 
    /// mode. (PRE handling is considered a single cycle.) See EE Users manual
    /// page 153 about this.
    int handle_tag(const Giftag tag);

    int handle_data_packed(const uqword data);

    /// Handle a GS primitive using the REGLIST processing method.
    /// Note: consumes 2 cycles (processes both 64-bit data strings at the same time).
    int handle_data_reglist(const uqword data);

    int handle_data_image(const uqword data);

    std::pair<size_t, SizedDwordRegister*> get_register_descriptor() const;
};
