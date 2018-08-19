#include "Controller/Ee/Gif/CGif.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CGif::CGif(Core* core) :
    CController(core)
{
}

void CGif::handle_event(const ControllerEvent& event)
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
        throw std::runtime_error("CGif event handler not implemented - please fix!");
    }
    }
}

int CGif::time_to_ticks(const double time_us)
{
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_bias_gif);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "Gif ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

int CGif::time_step(const int ticks_available)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;
    auto& fifo_gif_path1 = r.fifo_gif_path1;
    auto& fifo_gif_path2 = r.fifo_gif_path2;
    auto& fifo_gif_path3 = r.fifo_gif_path3;

    // Prioritise paths by 1 -> 2 -> 3.
    // TODO: GIF code does not do path arbitration currently.
    // See EE Users Manual page 149. 
    DmaFifoQueue<>* paths[3] = {&fifo_gif_path1, &fifo_gif_path2, &fifo_gif_path3};

    for (auto& fifo : paths)
    {
        if (!fifo->has_read_available(NUMBER_BYTES_IN_QWORD))
            continue;

        uqword data;
        fifo->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_QWORD);

        if (!ctrl.transfer_started)
        {
            ctrl.transfer_started = true;
            handle_tag(Giftag(data));
        }
        else
        {
            handle_data(data);
        }

        if (ctrl.transfer_end_of_packet)
        {
            if (ctrl.transfer_data_count == ctrl.transfer_data_target)
                ctrl.transfer_started = false;
        }
    }

    return 1;
}

void CGif::handle_tag(const Giftag tag)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;

    ctrl.transfer_data_count = 0;
}

void CGif::handle_data(const uqword data)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;
    
    ctrl.transfer_data_count += 1;
}
