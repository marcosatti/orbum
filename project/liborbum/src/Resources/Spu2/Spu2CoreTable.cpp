#include "Resources/Spu2/Spu2CoreTable.hpp"
#include "Resources/Spu2/Spu2Cores.hpp"

constexpr Spu2CoreTable::Spu2CoreInfo Spu2CoreTable::SPU2_STATIC_INFO[Constants::SPU2::NUMBER_CORES];

const Spu2CoreTable::Spu2CoreInfo * Spu2CoreTable::get_static_info(const Spu2Core_Base * channel)
{
	return &SPU2_STATIC_INFO[channel->core_id]; 
}