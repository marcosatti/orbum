#include "Resources/Spu2/RSpu2.hpp"

RSpu2::RSpu2() :
    core_0(0),
    core_1(1),
    cores{nullptr},
    main_memory(Constants::SIZE_2MB),
    memory_0346(0xBA),
    memory_0746(0x1A),
    memory_07b0(0x10),
    memory_07ce(0x32)
{
}