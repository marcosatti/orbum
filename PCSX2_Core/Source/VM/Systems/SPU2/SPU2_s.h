#pragma once

#include "VM/Types/VMSystem_s.h"

class SPU2_t;

/*
SPU2 system logic.
2 steps involved:
 1. Check through the DMA channels, and send/recieve data as necessary.
 2. Process audio and play samples at 44.1 or 48.0 kHz.
*/
class SPU2_s : public VMSystem_s
{
public:
	SPU2_s(VM * vm);
	virtual ~SPU2_s() = default;

	/*
	Initalisation.
	*/
	void initalise() override;

	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Context resources needed.
	*/
	std::shared_ptr<SPU2_t> mSPU2;
};

