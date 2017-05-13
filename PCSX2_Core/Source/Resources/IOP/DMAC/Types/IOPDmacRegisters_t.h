#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Register/BitfieldRegister32_t.h"
#include <memory>

/*
The IOP DMAC PCR0 register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
Responsible for the master enable of the DMA channels and the priority.
Controls channels 0-6 and the IOPCore CPU.
The IOP CPU can not be disabled even though bit 31 is read/write (no effect). Priority still takes effect.
TODO: Currently within the emulator, the priority values are not used.
*/
class IOPDmacRegister_PCR0_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int Priority0 = 0;
		static constexpr int Enable0 = 1;
		static constexpr int Priority1 = 2;
		static constexpr int Enable1 = 3;
		static constexpr int Priority2 = 4;
		static constexpr int Enable2 = 5;
		static constexpr int Priority3 = 6;
		static constexpr int Enable3 = 7;
		static constexpr int Priority4 = 8;
		static constexpr int Enable4 = 9;
		static constexpr int Priority5 = 10;
		static constexpr int Enable5 = 11;
		static constexpr int Priority6 = 12;
		static constexpr int Enable6 = 13;
		static constexpr int PriorityCPU = 14;
		static constexpr int EnableCPU = 15;

		static constexpr int CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { Enable0, Enable1, Enable2, Enable3, Enable4, Enable5, Enable6 };
	};

	IOPDmacRegister_PCR0_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The IOP DMAC ICR0 register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
Responsible for controlling the interrupts for the DMA channels.
The IRM (individual request mask) bits control the condition on which the channels are interrupted. 0 = only interrupt when the WHOLE transfer has completed. 1 = interrupt when a block or linked-list entry has completed.
The Error bit is for when a bus error or memory error occurs (unused in the emulator).
The TCM (transfer complete mask) bits act as interrupt enables of the individual channels. 0 = no interrupt can occur from channel. 1 = interrupt can occur from channel, that also depends on the IRM bit condition.
The MasterEnable bit controls all channels. 0 = no interrupts can occur from channels (Error bit still triggers). 1 = interrupts from channels can occur.
The TCI (transfer complete interrupt) bits state which channels have completed transfer (read only, set by VM).
The MasterInterrupt bit is set upon any of the channels interrupting or error bit being set. Read only.
*/
class IOPDmacRegister_ICR0_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int IRM0 = 0;
		static constexpr int IRM1 = 1;
		static constexpr int IRM2 = 2;
		static constexpr int IRM3 = 3;
		static constexpr int IRM4 = 4;
		static constexpr int IRM5 = 5;
		static constexpr int IRM6 = 6;
		static constexpr int Error = 7;
		static constexpr int TCM0 = 8;
		static constexpr int TCM1 = 9;
		static constexpr int TCM2 = 10;
		static constexpr int TCM3 = 11;
		static constexpr int TCM4 = 12;
		static constexpr int TCM5 = 13;
		static constexpr int TCM6 = 14;
		static constexpr int MasterEnable = 15;
		static constexpr int TCI0 = 16;
		static constexpr int TCI1 = 17;
		static constexpr int TCI2 = 18;
		static constexpr int TCI3 = 19;
		static constexpr int TCI4 = 20;
		static constexpr int TCI5 = 21;
		static constexpr int TCI6 = 22;
		static constexpr int MasterInterrupt = 23;

		static constexpr int CHANNEL_IRM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { IRM0, IRM1, IRM2, IRM3, IRM4, IRM5, IRM6 };
		static constexpr int CHANNEL_TCM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCM0, TCM1, TCM2, TCM3, TCM4, TCM5, TCM6 };
		static constexpr int CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCI0, TCI1, TCI2, TCI3, TCI4, TCI5, TCI6 };
	};

	IOPDmacRegister_ICR0_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	(IOP context) Reset any FL bits written to.
	*/
	void writeWord(const System_t context, const u32 value) override;

	/*
	Returns if there is a pending interrupt that should be raised, and sets the master interrupt bit appropriately.
	*/
	bool isInterruptPending(const System_t context);
};

/*
The IOP DMAC1 PCR register.
Based off wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
Responsible for the master enable of the DMA channels and the priority.
Controls channels 7-13.
TODO: Currently within the emulator, the priority values are not used.
*/
class IOPDmacRegister_PCR1_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int Priority7 = 0;
		static constexpr int Enable7 = 1;
		static constexpr int Priority8 = 2;
		static constexpr int Enable8 = 3;
		static constexpr int Priority9 = 4;
		static constexpr int Enable9 = 5;
		static constexpr int Priority10 = 6;
		static constexpr int Enable10 = 7;
		static constexpr int Priority11 = 8;
		static constexpr int Enable11 = 9;
		static constexpr int Priority12 = 10;
		static constexpr int Enable12 = 11;
		static constexpr int Priority13 = 12;
		static constexpr int Enable13 = 13;


		static constexpr int CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { Enable7, Enable8, Enable9, Enable10, Enable11, Enable12, Enable13 };
	};

	IOPDmacRegister_PCR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The IOP DMAC ICR1 register.
Based off wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
Responsible for controlling the interrupts for the DMA channels.
The IQE (interrupt on tag event queue) bits control the condition on which channels in chain mode are interrupted. 0 = no interrupt when a tag IRQ is hit. 1 = interrupt when a tag IRQ is hit.
The TCM (transfer complete mask) bits act as interrupt enables of the individual channels. 0 = no interrupt can occur from channel. 1 = interrupt can occur from channel, that also depends on the IQE bit condition.
The TCI (transfer complete interrupt) bits state which channels have completed transfer (read only, set by VM).
This ICR register is a bit different, and depends on ICR0 - see the DMA docs for more information as there is a few subtle differences.
*/
class IOPDmacRegister_ICR1_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int IQE0 = 0;
		static constexpr int IQE1 = 1;
		static constexpr int IQE2 = 2;
		static constexpr int IQE3 = 3;
		static constexpr int IQE4 = 4;
		static constexpr int IQE5 = 5;
		static constexpr int IQE6 = 6;
		static constexpr int IQE7 = 7;
		static constexpr int IQE8 = 8;
		static constexpr int IQE9 = 9;
		static constexpr int IQE10 = 10;
		static constexpr int IQE11 = 11;
		static constexpr int IQE12 = 12;
		static constexpr int IQE13 = 13;
		static constexpr int TCM7 = 14;
		static constexpr int TCM8 = 15;
		static constexpr int TCM9 = 16;
		static constexpr int TCM10 = 17;
		static constexpr int TCM11 = 18;
		static constexpr int TCM12 = 19;
		static constexpr int TCM13 = 20;
		static constexpr int TCI7 = 21;
		static constexpr int TCI8 = 22;
		static constexpr int TCI9 = 23;
		static constexpr int TCI10 = 24;
		static constexpr int TCI11 = 25;
		static constexpr int TCI12 = 26;
		static constexpr int TCI13 = 27;

		static constexpr int CHANNEL_IQE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] = { IQE0, IQE1, IQE2, IQE3, IQE4, IQE5, IQE6, IQE7, IQE8, IQE9, IQE10, IQE11, IQE12, IQE13 };
		static constexpr int CHANNEL_TCM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCM7, TCM8, TCM9, TCM10, TCM11, TCM12, TCM13 };
		static constexpr int CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCI7, TCI8, TCI9, TCI10, TCI11, TCI12, TCI13 };
	};

	IOPDmacRegister_ICR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<IOPDmacRegister_ICR0_t> & ICR0);

	/*
	(IOP context) Reset any FL bits written to.
	*/
	void writeWord(const System_t context, const u32 value) override;

	/*
	Returns if there is a pending interrupt that should be raised, and sets the master interrupt bit in ICR0 appropriately.
	*/
	bool isInterruptPending(const System_t context);

private:
	/*
	Reference to the ICR0 register, see handleInterruptCheck() above.
	*/
	std::shared_ptr<IOPDmacRegister_ICR0_t> mICR0;
};