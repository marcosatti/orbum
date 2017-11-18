#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

class IopDmacChannel;

/// The IOP DMAC PCR0 register.
/// Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
/// Responsible for the master enable of the DMA channels and the priority.
/// Controls channels 0-6 and the IOPCore CPU.
/// The IOP CPU can not be disabled even though bit 31 is read/write (no effect). Priority still takes effect.
/// TODO: Currently within the emulator, the priority values are not used.
class IopDmacRegister_Pcr0 : public SizedWordRegister
{
public:
	static constexpr Bitfield PRIORITY_0   = Bitfield(0, 3);
	static constexpr Bitfield ENABLE_0     = Bitfield(3, 1);
	static constexpr Bitfield PRIORITY_1   = Bitfield(4, 3);
	static constexpr Bitfield ENABLE_1     = Bitfield(7, 1);
	static constexpr Bitfield PRIORITY_2   = Bitfield(8, 3);
	static constexpr Bitfield ENABLE_2     = Bitfield(11, 1);
	static constexpr Bitfield PRIORITY_3   = Bitfield(12, 3);
	static constexpr Bitfield ENABLE_3     = Bitfield(15, 1);
	static constexpr Bitfield PRIORITY_4   = Bitfield(16, 3);
	static constexpr Bitfield ENABLE_4     = Bitfield(19, 1);
	static constexpr Bitfield PRIORITY_5   = Bitfield(20, 3);
	static constexpr Bitfield ENABLE_5     = Bitfield(23, 1);
	static constexpr Bitfield PRIORITY_6   = Bitfield(24, 3);
	static constexpr Bitfield ENABLE_6     = Bitfield(27, 1);
	static constexpr Bitfield PRIORITY_CPU = Bitfield(28, 3);
	static constexpr Bitfield ENABLE_CPU   = Bitfield(31, 1);

	static constexpr Bitfield CHANNEL_PRIORITY_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { PRIORITY_0, PRIORITY_1, PRIORITY_2, PRIORITY_3, PRIORITY_4, PRIORITY_5, PRIORITY_6 };
	static constexpr Bitfield CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { ENABLE_0, ENABLE_1, ENABLE_2, ENABLE_3, ENABLE_4, ENABLE_5, ENABLE_6 };
};

/// The IOP DMAC ICR0 register.
/// Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
/// Responsible for controlling the interrupts for the DMA channels.
/// The IRM (individual request mask) bits control the condition on which the channels are interrupted. 0 = only interrupt when the WHOLE transfer has completed. 1 = interrupt when a block or linked-list entry has completed.
/// The Error bit is for when a bus error or memory error occurs (unused in the emulator).
/// The TCM (transfer complete mask) bits act as interrupt enables of the individual channels. 0 = no interrupt can occur from channel. 1 = interrupt can occur from channel, that also depends on the IRM bit condition.
/// The MasterEnable bit controls all channels. 0 = no interrupts can occur from channels (Error bit still triggers). 1 = interrupts from channels can occur.
/// The TCI (transfer complete interrupt) bits state which channels have completed transfer (read only, set by VM).
/// The MasterInterrupt bit is set upon any of the channels interrupting or error bit being set. Read only.
///
/// Note on scope lock: although the IOP and DMAC will never write to the same bit at the same time, there could be a race
/// condition where different bits are written to, causing an inconsistency.
class IopDmacRegister_Icr0 : public SizedWordRegister, public ScopeLock
{
public:
	static constexpr Bitfield IRM_0            = Bitfield(0, 1);
	static constexpr Bitfield IRM_1            = Bitfield(1, 1);
	static constexpr Bitfield IRM_2            = Bitfield(2, 1);
	static constexpr Bitfield IRM_3            = Bitfield(3, 1);
	static constexpr Bitfield IRM_4            = Bitfield(4, 1);
	static constexpr Bitfield IRM_5            = Bitfield(5, 1);
	static constexpr Bitfield IRM_6            = Bitfield(6, 1);
	static constexpr Bitfield ERROR            = Bitfield(15, 1);
	static constexpr Bitfield TCM_0            = Bitfield(16, 1);
	static constexpr Bitfield TCM_1            = Bitfield(17, 1);
	static constexpr Bitfield TCM_2            = Bitfield(18, 1);
	static constexpr Bitfield TCM_3            = Bitfield(19, 1);
	static constexpr Bitfield TCM_4            = Bitfield(20, 1);
	static constexpr Bitfield TCM_5            = Bitfield(21, 1);
	static constexpr Bitfield TCM_6            = Bitfield(22, 1);
	static constexpr Bitfield MASTER_ENABLE    = Bitfield(23, 1);
	static constexpr Bitfield TCI_0            = Bitfield(24, 1);
	static constexpr Bitfield TCI_1            = Bitfield(25, 1);
	static constexpr Bitfield TCI_2            = Bitfield(26, 1);
	static constexpr Bitfield TCI_3            = Bitfield(27, 1);
	static constexpr Bitfield TCI_4            = Bitfield(28, 1);
	static constexpr Bitfield TCI_5            = Bitfield(29, 1);
	static constexpr Bitfield TCI_6            = Bitfield(30, 1);
	static constexpr Bitfield MASTER_INTERRUPT = Bitfield(31, 1);

	static constexpr Bitfield CHANNEL_IRM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { IRM_0, IRM_1, IRM_2, IRM_3, IRM_4, IRM_5, IRM_6 };
	static constexpr Bitfield CHANNEL_TCM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCM_0, TCM_1, TCM_2, TCM_3, TCM_4, TCM_5, TCM_6 };
	static constexpr Bitfield CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCI_0, TCI_1, TCI_2, TCI_3, TCI_4, TCI_5, TCI_6 };

	/// (IOP context) Reset any FL bits written to.
	/// Scope locked for entire duration.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

	/// Returns if there is a pending interrupt that should be raised, and sets the master interrupt bit appropriately.
	bool is_interrupt_pending_and_set_master();
};

/// The IOP DMAC1 PCR register.
/// Based off wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
/// Responsible for the master enable of the DMA channels and the priority.
/// Controls channels 7-13.
/// TODO: Currently within the emulator, the priority values are not used.
class IopDmacRegister_Pcr1 : public SizedWordRegister
{
public:
	static constexpr Bitfield PRIORITY_7  = Bitfield(0, 3);
	static constexpr Bitfield ENABLE_7    = Bitfield(3, 1);
	static constexpr Bitfield PRIORITY_8  = Bitfield(4, 3);
	static constexpr Bitfield ENABLE_8    = Bitfield(7, 1);
	static constexpr Bitfield PRIORITY_9  = Bitfield(8, 3);
	static constexpr Bitfield ENABLE_9    = Bitfield(11, 1);
	static constexpr Bitfield PRIORITY_10 = Bitfield(12, 3);
	static constexpr Bitfield ENABLE_10   = Bitfield(15, 1);
	static constexpr Bitfield PRIORITY_11 = Bitfield(16, 3);
	static constexpr Bitfield ENABLE_11   = Bitfield(19, 1);
	static constexpr Bitfield PRIORITY_12 = Bitfield(20, 3);
	static constexpr Bitfield ENABLE_12   = Bitfield(23, 1);
	static constexpr Bitfield PRIORITY_13 = Bitfield(24, 3);
	static constexpr Bitfield ENABLE_13   = Bitfield(27, 1);
		
	static constexpr Bitfield CHANNEL_PRIORITY_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { PRIORITY_7, PRIORITY_8, PRIORITY_9, PRIORITY_10, PRIORITY_11, PRIORITY_12, PRIORITY_13 };
	static constexpr Bitfield CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { ENABLE_7, ENABLE_8, ENABLE_9, ENABLE_10, ENABLE_11, ENABLE_12, ENABLE_13 };
};

/// The IOP DMAC ICR1 register.
/// Based off wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
/// Responsible for controlling the interrupts for the DMA channels.
/// The IQE (interrupt on tag event queue) bits control the condition on which channels in chain mode are interrupted. 0 = no interrupt when a tag IRQ is hit. 1 = interrupt when a tag IRQ is hit.
/// The TCM (transfer complete mask) bits act as interrupt enables of the individual channels. 0 = no interrupt can occur from channel. 1 = interrupt can occur from channel, that also depends on the IQE bit condition.
/// The TCI (transfer complete interrupt) bits state which channels have completed transfer (read only, set by VM).
/// This ICR register is a bit different, and depends on ICR0 - see the DMA docs for more information as there is a few subtle differences.
///
/// Note on scope lock: although the IOP and DMAC will never write to the same bit at the same time, there could be a race
/// condition where different bits are written to, causing an inconsistency.
class IopDmacRegister_Icr1 : public SizedWordRegister, public ScopeLock
{
public:
	static constexpr Bitfield IQE_0  = Bitfield(0, 1);
	static constexpr Bitfield IQE_1  = Bitfield(1, 1);
	static constexpr Bitfield IQE_2  = Bitfield(2, 1);
	static constexpr Bitfield IQE_3  = Bitfield(3, 1);
	static constexpr Bitfield IQE_4  = Bitfield(4, 1);
	static constexpr Bitfield IQE_5  = Bitfield(5, 1);
	static constexpr Bitfield IQE_6  = Bitfield(6, 1);
	static constexpr Bitfield IQE_7  = Bitfield(7, 1);
	static constexpr Bitfield IQE_8  = Bitfield(8, 1);
	static constexpr Bitfield IQE_9  = Bitfield(9, 1);
	static constexpr Bitfield IQE_10 = Bitfield(10, 1);
	static constexpr Bitfield IQE_11 = Bitfield(11, 1);
	static constexpr Bitfield IQE_12 = Bitfield(12, 1);
	static constexpr Bitfield IQE_13 = Bitfield(13, 1);
	static constexpr Bitfield TCM_7  = Bitfield(16, 1);
	static constexpr Bitfield TCM_8  = Bitfield(17, 1);
	static constexpr Bitfield TCM_9  = Bitfield(18, 1);
	static constexpr Bitfield TCM_10 = Bitfield(19, 1);
	static constexpr Bitfield TCM_11 = Bitfield(20, 1);
	static constexpr Bitfield TCM_12 = Bitfield(21, 1);
	static constexpr Bitfield TCM_13 = Bitfield(22, 1);
	static constexpr Bitfield TCI_7  = Bitfield(24, 1);
	static constexpr Bitfield TCI_8  = Bitfield(25, 1);
	static constexpr Bitfield TCI_9  = Bitfield(26, 1);
	static constexpr Bitfield TCI_10 = Bitfield(27, 1);
	static constexpr Bitfield TCI_11 = Bitfield(28, 1);
	static constexpr Bitfield TCI_12 = Bitfield(29, 1);
	static constexpr Bitfield TCI_13 = Bitfield(30, 1);

	static constexpr Bitfield CHANNEL_IQE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] = { IQE_0, IQE_1, IQE_2, IQE_3, IQE_4, IQE_5, IQE_6, IQE_7, IQE_8, IQE_9, IQE_10, IQE_11, IQE_12, IQE_13 };
	static constexpr Bitfield CHANNEL_TCM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCM_7, TCM_8, TCM_9, TCM_10, TCM_11, TCM_12, TCM_13 };
	static constexpr Bitfield CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { TCI_7, TCI_8, TCI_9, TCI_10, TCI_11, TCI_12, TCI_13 };

	/// (IOP context) Reset any FL bits written to.
	/// Scope locked for entire duration.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

	/// Returns if there is a pending interrupt that should be raised, and sets the master interrupt bit in ICR0 appropriately.
	bool is_interrupt_pending_and_set_master();

	/// Reference to ICR0 register - see description.
	IopDmacRegister_Icr0 * icr0;
};

/// Wrapper class around the PCR 0 and 1 registers to provide one interface for all channels.
/// This uses the register functionality, and uses values internally in terms of uword's.
/// Provides functions for priority and enable status'.
/// TODO: CPU priority and enabling not implemented, just use PCR0 directly for now.
/// For more information, see the PCR0 and PCR1 registers above.
class IopDmacRegister_Pcrw
{
public:
	/// Returns the priority status for a channel.
	uword channel_priority(const IopDmacChannel * channel);
	// void set_channel_priority(const IopDmacChannel * channel, const uword value)

	/// Returns the enabled status for a channel.
	bool is_channel_enabled(const IopDmacChannel * channel);
	// void set_channel_enabled(const IopDmacChannel * channel, const bool value)

	/// PCR0 register.
	IopDmacRegister_Pcr0 * pcr0;

	/// PCR1 register.
	IopDmacRegister_Pcr1 * pcr1;
};

/// Wrapper class around the ICR 0 and 1 registers to provide one interface for all channels.
/// This uses the register functionality, and uses values internally in terms of uword's.
/// Provides:
///  - Get/set for IRM (individual request mask).
///  - Get/set for IQE (interrupt on tag event queue).
///  - Get/set for TCM (transfer complete mask).
///  - Get/set for TCI (transfer complete interrupt).
///  - Getting the interrupted status (checks for any channels that have interrupted).

/// For more information, see the ICR0 and ICR1 registers above.
class IopDmacRegister_Icrw
{
public:
	/// Gets or sets the IRM for a channel.
	/// Only channels 0 to 6 are valid for IRM.
	/// TODO: Not sure where the others are for 7 to 13...
	uword channel_irm(const IopDmacChannel * channel);
	void set_channel_irm(const IopDmacChannel * channel, const uword value);

	/// Gets or sets the IQE for a channel.
	uword channel_iqe(const IopDmacChannel * channel);
	void set_channel_iqe(const IopDmacChannel * channel, const uword value);

	/// Gets or sets the TCM for a channel.
	uword channel_tcm(const IopDmacChannel * channel);
	void set_channel_tcm(const IopDmacChannel * channel, const uword value);

	/// Gets or sets the TCI for a channel.
	uword channel_tci(const IopDmacChannel * channel);
	void set_channel_tci(const IopDmacChannel * channel, const uword value);

	/// Returns if any of the channels are in an interrupt pending state.
	/// Sets the master interrupt if either ICR register has an interrupt pending.
	bool is_interrupt_pending_and_set_master() const;

	/// ICR0 register.
	IopDmacRegister_Icr0 * icr0;

	/// ICR1 register.
	IopDmacRegister_Icr1 * icr1;
};
