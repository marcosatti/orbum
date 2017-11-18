#include "Resources/Spu2/Spu2Cores.hpp"
#include "Resources/Spu2/Spu2CoreTable.hpp"

Spu2Core_Base::Spu2Core_Base(const int core_id) :
	core_id(core_id)
{
}

const Spu2CoreTable::Spu2CoreInfo * Spu2Core_Base::get_static_info() const
{
	return Spu2CoreTable::get_static_info(this);
}