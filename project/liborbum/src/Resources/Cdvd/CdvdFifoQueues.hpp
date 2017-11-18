#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/FifoQueue/SpscFifoQueue.hpp"

class CdvdRegister_Ns_Rdy_Din;

/*
CDVD extended SpscFifoQueue, used as the N/S command result FIFO's (N/S_DATA_OUT).
Upon reading or writing, it will check for the FIFO being empty, and set the NS_RDY_DIN->Ready register accordingly (magic values).
*/
class CdvdFifoQueue_Ns_Data_Out : public SpscFifoQueue, public ScopeLock
{
public:
	CdvdFifoQueue_Ns_Data_Out(const size_t size);

	/*
	Updates the Ready register upon reads/writes with magic values, based on if FIFO is empty.
	Scope locked for the entire duration.
	*/
	bool read_ubyte(ubyte & data) override;
	bool write_ubyte(const ubyte data) override;
	
	/*
	Reference to the NS_RDY_DIN register.
	*/
	CdvdRegister_Ns_Rdy_Din * ns_rdy_din;
};