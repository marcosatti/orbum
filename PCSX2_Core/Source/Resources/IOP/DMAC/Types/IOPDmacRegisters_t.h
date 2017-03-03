#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/BitfieldRegister32_t.h"
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
		static constexpr u8 Priority0 = 0;
		static constexpr u8 Enable0 = 1;
		static constexpr u8 Priority1 = 2;
		static constexpr u8 Enable1 = 3;
		static constexpr u8 Priority2 = 4;
		static constexpr u8 Enable2 = 5;
		static constexpr u8 Priority3 = 6;
		static constexpr u8 Enable3 = 7;
		static constexpr u8 Priority4 = 8;
		static constexpr u8 Enable4 = 9;
		static constexpr u8 Priority5 = 10;
		static constexpr u8 Enable5 = 11;
		static constexpr u8 Priority6 = 12;
		static constexpr u8 Enable6 = 13;
		static constexpr u8 PriorityCPU = 14;
		static constexpr u8 EnableCPU = 15;

		static constexpr u8 CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { Enable0, Enable1, Enable2, Enable3, Enable4, Enable5, Enable6 };
	};

	IOPDmacRegister_PCR0_t(const char * mnemonic);
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
		static constexpr u8 IRM0 = 0;
		static constexpr u8 IRM1 = 1;
		static constexpr u8 IRM2 = 2;
		static constexpr u8 IRM3 = 3;
		static constexpr u8 IRM4 = 4;
		static constexpr u8 IRM5 = 5;
		static constexpr u8 IRM6 = 6;
		static constexpr u8 Error = 7;
		static constexpr u8 TCM0 = 8;
		static constexpr u8 TCM1 = 9;
		static constexpr u8 TCM2 = 10;
		static constexpr u8 TCM3 = 11;
		static constexpr u8 TCM4 = 12;
		static constexpr u8 TCM5 = 13;
		static constexpr u8 TCM6 = 14;
		static constexpr u8 MasterEnable = 15;
		static constexpr u8 TCI0 = 16;
		static constexpr u8 TCI1 = 17;
		static constexpr u8 TCI2 = 18;
		static constexpr u8 TCI3 = 19;
		static constexpr u8 TCI4 = 20;
		static constexpr u8 TCI5 = 21;
		static constexpr u8 TCI6 = 22;
		static constexpr u8 MasterInterrupt = 23;

		static constexpr u8 CHANNEL_IRM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { IRM0, IRM1, IRM2, IRM3, IRM4, IRM5, IRM6 };
		static constexpr u8 CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCI0, TCI1, TCI2, TCI3, TCI4, TCI5, TCI6 };
	};

	IOPDmacRegister_ICR0_t(const char * mnemonic);

	/*
	(IOP context) Reset any FL bits written to.
	*/
	void writeWord(const Context_t& context, u32 value) override;

	/*
	Returns if there is a pending interrupt that should be raised, and sets the master interrupt bit appropriately.
	*/
	bool isInterruptPending();
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
		static constexpr u8 Priority7 = 0;
		static constexpr u8 Enable7 = 1;
		static constexpr u8 Priority8 = 2;
		static constexpr u8 Enable8 = 3;
		static constexpr u8 Priority9 = 4;
		static constexpr u8 Enable9 = 5;
		static constexpr u8 Priority10 = 6;
		static constexpr u8 Enable10 = 7;
		static constexpr u8 Priority11 = 8;
		static constexpr u8 Enable11 = 9;
		static constexpr u8 Priority12 = 10;
		static constexpr u8 Enable12 = 11;
		static constexpr u8 Priority13 = 12;
		static constexpr u8 Enable13 = 13;


		static constexpr u8 CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { Enable7, Enable8, Enable9, Enable10, Enable11, Enable12, Enable13 };
	};

	IOPDmacRegister_PCR1_t(const char * mnemonic);
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
		static constexpr u8 IQE0 = 0;
		static constexpr u8 IQE1 = 1;
		static constexpr u8 IQE2 = 2;
		static constexpr u8 IQE3 = 3;
		static constexpr u8 IQE4 = 4;
		static constexpr u8 IQE5 = 5;
		static constexpr u8 IQE6 = 6;
		static constexpr u8 IQE7 = 7;
		static constexpr u8 IQE8 = 8;
		static constexpr u8 IQE9 = 9;
		static constexpr u8 IQE10 = 10;
		static constexpr u8 IQE11 = 11;
		static constexpr u8 IQE12 = 12;
		static constexpr u8 IQE13 = 13;
		static constexpr u8 TCM7 = 14;
		static constexpr u8 TCM8 = 15;
		static constexpr u8 TCM9 = 16;
		static constexpr u8 TCM10 = 17;
		static constexpr u8 TCM11 = 18;
		static constexpr u8 TCM12 = 19;
		static constexpr u8 TCM13 = 20;
		static constexpr u8 TCI7 = 21;
		static constexpr u8 TCI8 = 22;
		static constexpr u8 TCI9 = 23;
		static constexpr u8 TCI10 = 24;
		static constexpr u8 TCI11 = 25;
		static constexpr u8 TCI12 = 26;
		static constexpr u8 TCI13 = 27;

		static constexpr u8 CHANNEL_IQE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] = { IQE0, IQE1, IQE2, IQE3, IQE4, IQE5, IQE6, IQE7, IQE8, IQE9, IQE10, IQE11, IQE12, IQE13 };
		static constexpr u8 CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCI7, TCI8, TCI9, TCI10, TCI11, TCI12, TCI13 };
	};

	IOPDmacRegister_ICR1_t(const char * mnemonic, const std::shared_ptr<IOPDmacRegister_ICR0_t> & ICR0);

	/*
	(IOP context) Reset any FL bits written to.
	*/
	void writeWord(const Context_t& context, u32 value) override;

	/*
	Returns if there is a pending interrupt that should be raised, and sets the master interrupt bit in ICR0 appropriately.
	*/
	bool isInterruptPending();

private:
	/*
	Reference to the ICR0 register, see handleInterruptCheck() above.
	*/
	std::shared_ptr<IOPDmacRegister_ICR0_t> mICR0;
};