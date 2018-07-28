#include "Controller/Ee/Ipu/CIpu.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CIpu::CIpu(Core* core) :
    CController(core)
{
}

void CIpu::handle_event(const ControllerEvent& event)
{
    switch (event.type)
    {
    case ControllerEvent::Type::Time:
    {
        int ticks_remaining = time_to_ticks(event.data.time_us);
        while (ticks_remaining > 0)
            ticks_remaining -= time_step(ticks_remaining);
        break;
    }
    default:
    {
        throw std::runtime_error("CIpu event handler not implemented - please fix!");
    }
    }
}

int CIpu::time_to_ticks(const double time_us)
{
    // TODO: find out for sure.
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_bias_ipu);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "Ipu ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

int CIpu::time_step(const int ticks_available)
{
    // Not yet implemented.
    return ticks_available;
}