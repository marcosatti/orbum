#include <boost/format.hpp>

#include "Controller/Iop/Sio0/CSio0.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CSio0::CSio0(Core* core) :
    CController(core)
{
}

void CSio0::handle_event(const ControllerEvent& event)
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
        throw std::runtime_error("CSio0 event handler not implemented - please fix!");
    }
    }
}

int CSio0::time_to_ticks(const double time_us)
{
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::SIO0::SIO0_CLK_SPEED * core->get_options().system_bias_sio0);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "Sio0 ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

int CSio0::time_step(const int ticks_available)
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio0.ctrl;

    // CTRL locked for entire duration.
    auto _ctrl_lock = ctrl.scope_lock();

    handle_reset_check();
    handle_irq_check();
    handle_transfer();

    return 1;
}

void CSio0::handle_reset_check()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio0.ctrl;
    auto& stat = r.iop.sio0.stat;
    auto& data = r.iop.sio0.data;

    auto _stat_lock = stat.scope_lock();

    // Perform SIO0 reset (all relevant bits and FIFO).
    if (ctrl.extract_field(Sio0Register_Ctrl::SIO_RESET))
    {
        ctrl.insert_field(Sio0Register_Ctrl::RESET_IRQ, 0);
        stat.insert_field(Sio0Register_Stat::IRQ, 0);

        data.initialise();

        // Now ready to transmit data.
        // TODO: not totally correct...
        stat.insert_field(Sio0Register_Stat::TX_RDY1, 1);
        ctrl.insert_field(Sio0Register_Ctrl::SIO_RESET, 0);
    }
}

void CSio0::handle_irq_check()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio0.ctrl;
    auto& stat = r.iop.sio0.stat;

    auto _ctrl_lock = ctrl.scope_lock();
    auto _stat_lock = stat.scope_lock();

    // Reset IRQ bit if it has been acknowledged by IOP.
    if (ctrl.extract_field(Sio0Register_Ctrl::RESET_IRQ))
    {
        stat.insert_field(Sio0Register_Stat::IRQ, 0);
        ctrl.insert_field(Sio0Register_Ctrl::RESET_IRQ, 0);
    }

    // Raise IRQ on the ACK line going high (if enabled).
    if (ctrl.extract_field(Sio0Register_Ctrl::ACK_INT_EN) && stat.extract_field(Sio0Register_Stat::DSR))
        stat.insert_field(Sio0Register_Stat::IRQ, 1);

    // Raise IOP INTC IRQ if requested.
    if (stat.extract_field(Sio0Register_Stat::IRQ))
    {
        auto _stat_lock = r.iop.intc.stat.scope_lock();
        r.iop.intc.stat.insert_field(IopIntcRegister_Stat::SIO0, 1);
    }
}
void CSio0::handle_transfer()
{
    auto& r = core->get_resources();
    auto& command_queue = r.iop.sio0.data.command_queue;
    auto& response_queue = r.iop.sio0.data.response_queue;
    auto& stat = r.iop.sio0.stat;

    // Sequential command/response action.

    // Check there is data to send first, TX_RDY2 changes depending on this.
    if (!command_queue.has_read_available(1))
    {
        stat.insert_field(Sio0Register_Stat::TX_RDY2, 1);
        return;
    }

    if (!response_queue.has_write_available(1))
        return;

    ubyte cmd = command_queue.read_ubyte();

    // TODO: properly implement, for now just send back 0x00 for all commands received.
    response_queue.write_ubyte(0);

    auto _stat_lock = stat.scope_lock();
    stat.insert_field(Sio0Register_Stat::RX_NONEMPTY, 1);
}
