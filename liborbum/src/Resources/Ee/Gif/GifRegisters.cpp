#include "Resources/Ee/Gif/GifRegisters.hpp"

GifRegister_Ctrl::GifRegister_Ctrl() :
    transfer_started(false),
    tag(),
    transfer_register_count(0),
    transfer_loop_count(0),
    rgbaq_q(1.0f)
{
}