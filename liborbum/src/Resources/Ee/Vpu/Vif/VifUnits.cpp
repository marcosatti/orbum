#include "Resources/Ee/Vpu/Vif/VifUnits.hpp"

VifUnit_Base::VifUnit_Base(const int core_id) :
    core_id(core_id),
    dma_fifo_queue(nullptr)
{
}
