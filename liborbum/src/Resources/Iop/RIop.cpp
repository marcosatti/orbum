#include "Resources/Iop/RIop.hpp"

RIop::RIop() :
    bus(16),
    main_memory(Constants::IOP::IOPMemory::SIZE_IOP_MEMORY),
    parallel_port(Constants::IOP::ParallelPort::SIZE_PARALLEL_PORT)
{
}