#include "Resources/Ee/Gif/GifRegisters.hpp"

GifRegister_Ctrl::GifRegister_Ctrl() :
    transfer_started(false),
    transfer_data_target(0),
    transfer_data_count(0),
    transfer_end_of_packet(false)
{
}