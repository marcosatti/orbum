#include <stdexcept>

#include <boost/format.hpp>

#include "Controller/Iop/Sio2/CSio2.hpp"

#include "Common/Constants.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"

using Direction = Sio2Register_Ctrl::Direction;

CSio2::CSio2(Core* core) :
    CController(core)
{
}

void CSio2::handle_event(const ControllerEvent& event)
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
        throw std::runtime_error("CSio2 event handler not implemented - please fix!");
    }
    }
}

int CSio2::time_to_ticks(const double time_us)
{
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::SIO2::SIO2_CLK_SPEED * core->get_options().system_bias_sio2);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "Sio2 ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

int CSio2::time_step(const int ticks_available)
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio2.ctrl;

    // Lock whole SIO2 operation while processing.
    auto _ctrl_lock = ctrl.scope_lock();

    handle_ctrl_check();

    handle_port_trasnfer();

    return 1;
}

void CSio2::handle_ctrl_check()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio2.ctrl;

    if (ctrl.write_latch && !ctrl.transfer_started)
    {
        // Reset SIO2 port state and start transfer.
        ctrl.transfer_port = 0;
        ctrl.transfer_port_count = 0;
        ctrl.transfer_started = true;
        ctrl.transfer_direction = ctrl.get_direction();

        // Perform SIO0 reset before initiating transfer if in the TX direction.
        if (ctrl.transfer_direction == Direction::TX)
            handle_sio0_reset();

        // Reset direction bits - they are write only (see register description).
        ctrl.insert_field(Sio2Register_Ctrl::DIRECTION, 0);

        BOOST_LOG(Core::get_logger()) << str(boost::format("~~~~~~ SIO2 ctrl set: %s direction") 
            % (ctrl.transfer_direction == Direction::TX ? "TX" : "RX"));

        ctrl.write_latch = false;
    }
}

void CSio2::handle_sio0_reset()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio0.ctrl;

    auto _lock = ctrl.scope_lock();
    ctrl.insert_field(Sio0Register_Ctrl::SIO_RESET, 1);
}

void CSio2::handle_port_trasnfer()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio2.ctrl;
    auto& ports = r.iop.sio2.ports;
    auto& port = ports[ctrl.transfer_port];

    if (!ctrl.transfer_started)
        return;

    auto _port_ctrl3_lock = port.ctrl_3->scope_lock();

    if (!port.ctrl_3->port_transfer_started)
    {
        static bool warned = false;

        if (!port.ctrl_3->write_latch)
        {
            if (!warned)
            {
                BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 TX/RX stalled: ctrl3 needs to be set by IOP first (write latch not set)";
                warned = true;
            }
            return;
        }

        warned = false;

        port.ctrl_3->port_transfer_started = true;
        port.ctrl_3->write_latch = false;
        BOOST_LOG(Core::get_logger()) << str(boost::format("~~~~~~ SIO2 TX port %d started") % ctrl.transfer_port);
    }

    switch (ctrl.transfer_direction)
    {
    case Direction::TX:
    {
        transfer_data_tx();
        break;
    }
    case Direction::RX:
    {
        transfer_data_rx();
        break;
    }
    default:
        throw std::runtime_error("Could not determine SIO2 transfer direction.");
    }

    // All data sent/received, stop transfering.
    if (ctrl.transfer_port == Constants::IOP::SIO2::NUMBER_PORTS)
    {
        if (ctrl.transfer_direction == Direction::RX)
        {
            BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 RX finished: raising irq";
            auto& intc_stat = r.iop.intc.stat;
            auto _intc_lock = intc_stat.scope_lock();
            intc_stat.insert_field(IopIntcRegister_Stat::SIO2, 1);
        }

        BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 TX or RX all ports finished";
        ctrl.transfer_started = false;
    }
}

void CSio2::transfer_data_tx()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio2.ctrl;
    auto& ports = r.iop.sio2.ports;
    auto& data_in = r.fifo_tosio2;
    auto& sio0_data = r.iop.sio0.data;
    auto& sio0_ctrl = r.iop.sio0.ctrl;
    auto& sio0_stat = r.iop.sio0.stat;

    auto& port = ports[ctrl.transfer_port];

    size_t cmd_length = port.ctrl_3->extract_field(Sio2PortRegister_Ctrl3::CMDLEN);

    // Send data to the SIO0.
    if (ctrl.transfer_port_count != cmd_length)
    {
        if (!sio0_stat.extract_field(Sio0Register_Stat::TX_RDY1))
        {
            BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 TX stalled: SIO0 stat.TX_RDY1 not set";
            return;
        }

        if (!data_in.has_read_available(1))
        {
            BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 TX stalled: no FIFO data";
            return;
        }

        // If it's the first byte, perform some initialisation.
        if (ctrl.transfer_port_count == 0)
        {
            // Set the SIO0 pad port first when the SIO0 is ready.
            if (!sio0_stat.extract_field(Sio0Register_Stat::TX_RDY2))
            {
                BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 TX stalled (init): SIO0 stat.TX_RDY2 not set";
                return;
            }

            uhword sio0_padport = port.ctrl_3->extract_field(Sio2PortRegister_Ctrl3::PADPORT);

            auto _sio0_ctrl_lock = sio0_ctrl.scope_lock();
            sio0_ctrl.insert_field(Sio0Register_Ctrl::PORT, sio0_padport);
        }

        ubyte data = data_in.read_ubyte();
        sio0_data.write_ubyte(data);
        ctrl.transfer_port_count += 1;
    }

    // Finished with this port, move on to next.
    if (ctrl.transfer_port_count == cmd_length)
    {
        BOOST_LOG(Core::get_logger()) << str(boost::format("~~~~~~ SIO2 TX port %d finished") % ctrl.transfer_port);
        ctrl.transfer_port += 1;
        ctrl.transfer_port_count = 0;
    }
}

void CSio2::transfer_data_rx()
{
    auto& r = core->get_resources();
    auto& ctrl = r.iop.sio2.ctrl;
    auto& ports = r.iop.sio2.ports;
    auto& data_out = r.fifo_fromsio2;
    auto& sio0_data = r.iop.sio0.data;
    auto& sio0_stat = r.iop.sio0.stat;

    auto& port = ports[ctrl.transfer_port];
    size_t response_length = port.ctrl_3->extract_field(Sio2PortRegister_Ctrl3::BUFSZ);

    // Receive data from the SIO0.
    if (ctrl.transfer_port_count != response_length)
    {
        if (!data_out.has_write_available(1))
        {
            BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 RX stalled: FIFO full";
            return;
        }

        if (!sio0_stat.extract_field(Sio0Register_Stat::RX_NONEMPTY))
        {
            BOOST_LOG(Core::get_logger()) << "~~~~~~ SIO2 RX stalled: SIO0 stat.RX_NONEMPTY not set";
            return;
        }

        ubyte data = sio0_data.read_ubyte();
        data_out.write_ubyte(data);
        ctrl.transfer_port_count += 1;
    }

    // Finished with this port, move on to next.
    if (ctrl.transfer_port_count == response_length)
    {
        BOOST_LOG(Core::get_logger()) << str(boost::format("~~~~~~ SIO2 RX port %d finished") % ctrl.transfer_port);
        port.ctrl_3->port_transfer_started = false;
        ctrl.transfer_port += 1;
        ctrl.transfer_port_count = 0;
    }
}