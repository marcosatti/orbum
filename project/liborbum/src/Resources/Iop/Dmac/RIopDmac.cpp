#include "Resources/Iop/Dmac/RIopDmac.hpp"

RIopDmac::RIopDmac() :
	channel_frommdec(0),
	channel_tomdec(1),
	channel_sif2(2),
	channel_cdvd(3),
	channel_spu2c0(4),
	channel_pio(5),
	channel_otclear(6),
	channel_spu2c1(7),
	channel_dev9(8),
	channel_sif0(9),
	channel_sif1(10),
	channel_fromsio2(11),
	channel_tosio2(12),
	channels{nullptr}
{
}
