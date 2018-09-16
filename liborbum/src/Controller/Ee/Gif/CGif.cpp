#include <algorithm>

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

    int cycles_consumed = 0;

    // Prioritise paths by 1 -> 2 -> 3.
    // TODO: GIF code does not do path arbitration currently.
    // See EE Users Manual page 149. 
    DmaFifoQueue<>* paths[3] = {&fifo_gif_path1, &fifo_gif_path2, &fifo_gif_path3};

    for (auto& fifo : paths)
    {
        // A GIFtag is always read before processing data.
        if (!ctrl.transfer_started)
        {
            if (!fifo->has_read_available(NUMBER_BYTES_IN_QWORD))
                continue;

            uqword data;
            fifo->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_QWORD);

            ctrl.transfer_started = true;

            cycles_consumed = handle_tag(Giftag(data));
        }
        else
        {
            switch (ctrl.tag.flg())
            {
            case Giftag::DataFormat::Packed:
            {
                if (!fifo->has_read_available(NUMBER_BYTES_IN_QWORD))
                    continue;

                uqword data;
                fifo->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_QWORD);

                cycles_consumed = handle_data_packed(data);
            }
            case Giftag::DataFormat::Reglist:
            {
                // TODO: maybe a weird situation can occur where there is only 
                // 1 dword available which should be processed first before 
                // attempting processing of other paths... Probably should make
                // this proper at some stage. Manual doesn't really say what to do...
                if (!fifo->has_read_available(NUMBER_BYTES_IN_QWORD))
                    continue;

                uqword data;
                fifo->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_QWORD);

                cycles_consumed = handle_data_reglist(data);
            }
            case Giftag::DataFormat::Image:
            case Giftag::DataFormat::Disabled:
            {
                if (!fifo->has_read_available(NUMBER_BYTES_IN_QWORD))
                    continue;

                uqword data;
                fifo->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_QWORD);

                cycles_consumed = handle_data_image(data);
            }
            default:
            {
                throw std::runtime_error("Unknown GIF data processing method");
            }
            }
        }

        if (ctrl.tag.eop())
        {
            throw std::runtime_error("End of GS packet reached - what do we do?");
        }

        // Do not process other paths if at least one path was successfully processed.
        if (cycles_consumed)
            break;
    }

    // At least 1 cycle is consumed always if no paths had data available for processing.
    return std::max(cycles_consumed, 1);
}

int CGif::handle_tag(const Giftag tag)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;

    ctrl.tag = tag;
    ctrl.transfer_register_count = 0;
    ctrl.transfer_loop_count = 0;

    // Initialise the RGBAQ.Q value on every tag read.
    // See EE Users manual page 153.
    ctrl.rgbaq_q = 1.0f;

    // Some special processing when the NLOOP field is non-zero 
    // "Values other than the EOP field are disregarded."
    // See EE Users Manual page 151.
    if (tag.nloop())
    {
        if (tag.flg() == Giftag::DataFormat::Packed)
        {
            // Output the packed PRIM data to GS if the PRE bit is set.
            if (tag.pre())
            {
                throw std::runtime_error("Sending GIFtag packed PRIM data not implemented yet");
                //uhword prim_value = tag.prim();
                //auto& prim = r.gs.prim;
                //prim.write_udword(prim_value);
            }
        }
    }

    // 1 cycle consumed for the tag, and 1 cycle for the handling of the PRIM data
    // (always done even if it's not used). See the descriptions of the transfer
    // modes in the EE Users Manual page 153, 159, 160.
    return 2;
}

int CGif::handle_data_packed(const uqword data)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;

    // Get the register descirptor.
    size_t register_descirptor = ctrl.tag.regs(ctrl.transfer_register_count);

    // Process the data given, and write to the GS register.
    // See EE Users Manual page 152 onwards for processing details.
    switch (register_descirptor)
    {
    case 0x0:
    {
        // PRIM
        constexpr Bitfield PRIM = Bitfield(0, 11);

        udword prim_value = PRIM.extract_from<udword>(data); 

        //auto& prim = r.gs.prim;
        //prim.write_udword(prim_value);
        break;
    }
    case 0x1:
    {
        // RGBAQ
        constexpr Bitfield R = Bitfield(0, 8);
        constexpr Bitfield G = Bitfield(32, 8);
        constexpr Bitfield B = Bitfield(64, 8);
        constexpr Bitfield A = Bitfield(96, 8);

        udword r_value = R.extract_from<udword>(data); 
        udword g_value = G.extract_from<udword>(data); 
        udword b_value = B.extract_from<udword>(data); 
        udword a_value = A.extract_from<udword>(data);
        udword q_value = *reinterpret_cast<udword*>(&ctrl.rgbaq_q);

        //auto& rgbaq = r.gs.rgbaq;
        //rgbaq.write_field(GsRegister_Rgbaq::R, r_value);
        //rgbaq.write_field(GsRegister_Rgbaq::G, g_value);
        //rgbaq.write_field(GsRegister_Rgbaq::B, b_value);
        //rgbaq.write_field(GsRegister_Rgbaq::A, a_value);
        //rgbaq.write_field(GsRegister_Rgbaq::Q, q_value);
        break;
    }
    case 0x2:
    {
        // ST
        constexpr Bitfield S = Bitfield(0, 32);
        constexpr Bitfield T = Bitfield(32, 32);
        constexpr Bitfield Q = Bitfield(64, 32);

        // Store the Q value internally, used when handling RGBAQ register descriptor (see above).
        uword q_value = Q.extract_from<uword>(data);
        ctrl.rgbaq_q = *reinterpret_cast<f32*>(&q_value);

        udword s_value = S.extract_from<udword>(data);
        udword t_value = T.extract_from<udword>(data);

        //auto& st = r.gs.st;
        //st.write_field(GsRegister_St::S, s_value);
        //st.write_field(GsRegister_St::T, t_value);
        break;
    }
    case 0x3:
    {
        // UV
        constexpr Bitfield U = Bitfield(0, 14);
        constexpr Bitfield V = Bitfield(32, 14);

        udword u_value = U.extract_from<udword>(data);
        udword v_value = V.extract_from<udword>(data);

        //auto& uv = r.gs.uv;
        //uv.write_field(GsRegister_Uv::U, u_value);
        //uv.write_field(GsRegister_Uv::V, v_value);
        break;
    }
    case 0x4:
    {
        // XYZF2/3
        constexpr Bitfield X = Bitfield(0, 16);
        constexpr Bitfield Y = Bitfield(32, 16);
        constexpr Bitfield Z = Bitfield(68, 24);
        constexpr Bitfield F = Bitfield(100, 8);
        constexpr Bitfield ADC = Bitfield(111, 1);

        udword x_value = X.extract_from<udword>(data);
        udword y_value = Y.extract_from<udword>(data);
        udword z_value = Z.extract_from<udword>(data);
        udword f_value = F.extract_from<udword>(data);
        udword adc_value = ADC.extract_from<udword>(data);

        //GsRegister_Xyzf * xyzf = adc_value ? &r.gs.xyzf2 : &r.gs.xyzf3;
        //xyzf->write_field(GsRegister_Xyzf::X, x_value);
        //xyzf->write_field(GsRegister_Xyzf::Y, y_value);
        //xyzf->write_field(GsRegister_Xyzf::Z, z_value);
        //xyzf->write_field(GsRegister_Xyzf::F, f_value);
        break;
    }
    case 0x5:
    {
        // XYZ2/3
        constexpr Bitfield X = Bitfield(0, 16);
        constexpr Bitfield Y = Bitfield(32, 16);
        constexpr Bitfield Z = Bitfield(64, 32);
        constexpr Bitfield ADC = Bitfield(111, 1);

        udword x_value = X.extract_from<udword>(data);
        udword y_value = Y.extract_from<udword>(data);
        udword z_value = Z.extract_from<udword>(data);
        udword adc_value = ADC.extract_from<udword>(data);

        //GsRegister_Xyzf * xyz = adc_value ? &r.gs.xyz2 : &r.gs.xyz3;
        //xyz->write_field(GsRegister_Xyzf::X, x_value);
        //xyz->write_field(GsRegister_Xyzf::Y, y_value);
        //xyz->write_field(GsRegister_Xyzf::Z, z_value);
        break;
    }
    case 0x6:
    {
        // TEX0_1
        //auto& tex0_1 = r.gs.tex0_1;
        //tex0_1.write_udword(data.lo);
        break;
    }
    case 0x7:
    {
        // TEX0_2
        //auto& tex0_2 = r.gs.tex0_2;
        //tex0_2.write_udword(data.lo);
        break;
    }
    case 0x8:
    {
        // CLAMP_1
        //auto& clamp_1 = r.gs.clamp_1;
        //clamp_1.write_udword(data.lo);
        break;
    }
    case 0x9:
    {
        // CLAMP_2
        //auto& clamp_2 = r.gs.clamp_2;
        //clamp_2.write_udword(data.lo);
        break;
    }
    case 0xA:
    {
        // FOG
        // TODO: Not sure if we need to extract the integral part? Wording a bit unclear.
        // See EE Users Manual page 155.
        constexpr Bitfield F = Bitfield(100, 8);

        udword f_value = F.extract_from<udword>(data);

        //auto& fog = r.gs.fog;
        //fog.write_field(GsRegister_Fog::F, f_value);
        break;
    }
    case 0xB:
    {
        // Reserved
        throw std::runtime_error("Reserved register descriptor read from GIFtag");
    }
    case 0xC:
    {
        // XYZF3
        //auto& xyzf3 = r.gs.xyzf3;
        //xyzf3.write_udword(data.lo);
        break;
    }
    case 0xD:
    {
        // XYZ3
        //auto& xyz3 = r.gs.xyz3;
        //xyz3.write_udword(data.lo);
        break;
    }
    case 0xE:
    {
        // A+D (packed address + data)
        constexpr Bitfield ADDR = Bitfield(64, 8);

        uptr addr_value = ADDR.extract_from<uptr>(data);
        udword data_value = data.lo;

        //r.gs.bus.write_udword(BusContext::Gif, addr_value, data_value);
        break;
    }
    case 0xF:
    {
        // NOP    
        break;
    }
    default:
    {
        throw std::runtime_error("Unknown register descriptor given");
    }
    }
    
    ctrl.transfer_register_count += 1;
    if (ctrl.transfer_register_count == ctrl.tag.nreg())
    {
        ctrl.transfer_register_count = 0;
        ctrl.transfer_loop_count += 1;
    }

    if (ctrl.transfer_loop_count == ctrl.tag.nloop())
        ctrl.transfer_started = false;

    return 1;
}

int CGif::handle_data_reglist(const uqword data)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;

    udword datas[] = { data.lo, data.hi };
    for (auto& data : datas)
    {
        // Get the register descirptor.
        size_t register_descirptor = ctrl.tag.regs(ctrl.transfer_register_count);

        // Write data directly to the GS register.
        // See EE Users Manual page 159 onwards for processing details.
        switch (register_descirptor)
        {
        case 0x0:
        {
            // PRIM
            //auto& prim = r.gs.prim;
            //prim.write_udword(data);
            break;
        }
        case 0x1:
        {
            // RGBAQ
            //auto& rgbaq = r.gs.rgbaq;
            //rgbaq.write_udword(data);
            break;
        }
        case 0x2:
        {
            // ST
            //auto& st = r.gs.st;
            //st.write_udword(data);
            break;
        }
        case 0x3:
        {
            // UV
            //auto& uv = r.gs.uv;
            //uv.write_udword(data);
            break;
        }
        case 0x4:
        {
            // XYZF2
            //auto& xyzf2 = r.gs.xyzf2;
            //xyzf2.write_udword(data);
            break;
        }
        case 0x5:
        {
            // XYZ2
            //auto& xyz2 = r.gs.xyz2;
            //xyz2.write_udword(data);
            break;
        }
        case 0x6:
        {
            // TEX0_1
            //auto& tex0_1 = r.gs.tex0_1;
            //tex0_1.write_udword(data);
            break;
        }
        case 0x7:
        {
            // TEX0_2
            //auto& tex0_2 = r.gs.tex0_2;
            //tex0_2.write_udword(data);
            break;
        }
        case 0x8:
        {
            // CLAMP_1
            //auto& clamp_1 = r.gs.clamp_1;
            //clamp_1.write_udword(data);
            break;
        }
        case 0x9:
        {
            // CLAMP_2
            //auto& clamp_2 = r.gs.clamp_2;
            //clamp_2.write_udword(data);
            break;
        }
        case 0xA:
        {
            // FOG
            //auto& fog = r.gs.fog;
            //fog.write_udword(data);
            break;
        }
        case 0xB:
        {
            // Reserved
            throw std::runtime_error("Reserved register descriptor read from GIFtag");
        }
        case 0xC:
        {
            // XYZF3
            //auto& xyzf3 = r.gs.xyzf3;
            //xyzf3.write_udword(data);
            break;
        }
        case 0xD:
        {
            // XYZ3
            //auto& xyz3 = r.gs.xyz3;
            //xyz3.write_udword(data);
            break;
        }
        case 0xE:
        {
            // A+D (packed address + data)
            // No-op for REGLIST mode. See EE Users Manual page 159.
            break;
        }
        case 0xF:
        {
            // NOP    
            break;
        }
        default:
        {
            throw std::runtime_error("Unknown register descriptor given");
        }
        }

        ctrl.transfer_register_count += 1;
        if (ctrl.transfer_register_count == ctrl.tag.nreg())
        {
            ctrl.transfer_register_count = 0;
            ctrl.transfer_loop_count += 1;
        }

        if (ctrl.transfer_loop_count == ctrl.tag.nloop())
        {
            ctrl.transfer_started = false;
            break;
        }
    }
    
    // Although not stated, I'm gussing the GIF consumes an extra cycle even when
    // NREGS is odd (ie: upper 64-bits of last qword of data discarded).
    return 2;
}

int CGif::handle_data_image(const uqword data)
{
    auto& r = core->get_resources();
    auto& ctrl = r.ee.gif.ctrl;
    //auto& hwreg = r.gs.hwreg;

    udword datas[] = { data.lo, data.hi };
    for (auto& data : datas)
    {
        // Data is output sequentially to the HWREG transfer register of the GS.
        // See EE Users manual page 160.
        //hwreg.write_udword(data);
    }

    ctrl.transfer_loop_count += 1;
    if (ctrl.transfer_loop_count == ctrl.tag.nloop())
        ctrl.transfer_started = false;

    return 1;
}
