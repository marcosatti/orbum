# PCSX2_rewrite

An attempt at updating the PCSX2 codebase with 3 primary objectives:

* Use OOP design practices (in C++) instead of the large C type programming currently in use.
* Document as much as possible. Currently there is very little documentation on most things.
* Get rid of the bloat accumulated over 10+ years (a lot of this will be done through the use of OOP).
* Able to be compiled on popular platforms, such as x86 and ARM (requires jitter's for specific architectures).

Initially I will be focusing on the core functionality of PCSX2 (ie: the PS2 code) with the following tasks in mind (not necessarily in order or complete):

1. Implementing the EE Core.
2. Implementing the VU's.
3. Implementing the GS.
4. Implementing the other components (IOP, DMAC etc).
5. Implement the overarching VM manager.
6. Get an interpreter version working.
7. Work on the recompiled approach.
8. Work on the GUI

This is a large undertaking, and I will have approx. 6 months to do most of the work in.

Not all of the old code and practices will be thrown away, a lot of it is still very useful, which will help with the work load.
Some parts will be a simple copy and paste job.

It will hold the same license as PCSX2, and I hope that eventually it will get remerged into the main project.

Marco.

## Current status

As of 2017/03/08:
- Main loop & VM (including timing of components and the host MMU) implemented. In a nutshell timing is achieved through letting everything run freely for (10us * clock speed), after which they are sync'd again.
- A multi threaded approach is being worked on, mostly just need to solve data race issues (ie: granularity of mutexes/locks, the code is already there).
- EE Core mostly implemented. No handling of the cache modes supported.
- EE Timers, INTC, DMAC, etc mostly implemented.
- IOP Core mostly implemented.
- IOP Timers, INTC, DMAC, etc mostly implemented. Notably the CDVD is not done yet.
- GS (Core) not implemented. CRTC is a work in progress, currently just triggers vblank and hblank stuff.
- VU's/VIF's structure implemented, system logic to follow (currently working on this).
- No input, sound, graphics yet. Will try to get a basic software graphics solution going before anything else.

Some debug data:
```
[Info] VM reset started...
[Info] VM resources initalised.
[Info] VM roms initalised.
[Info] VM systems initalised.
[Info] VM reset done.
[Debug] EE SIO Message: # Initialize memory (rev:3.17, ctm:393Mhz, cpuclk:295Mhz )
[Debug] EE SIO Message: # Total accessable memory size: 32 MB (B:2:8:0)
[Debug] EE SIO Message: # TLB spad=0 kernel=1:12 default=13:30 extended=31:38
[Debug] EE SIO Message: # Initialize Start.
[Debug] EE SIO Message: # Initialize GS ...
[Debug] EE SIO Message: # Initialize INTC ...
[Debug] EE SIO Message: # Initialize TIMER ...
[Debug] EE SIO Message: # Initialize DMAC ...
[Debug] EE SIO Message: # Initialize VU1 ...
[Debug] EE SIO Message: # Initialize VIF1 ...
[Debug] EE SIO Message: # Initialize GIF ...
[Debug] EE SIO Message: # Initialize VU0 ...
[Debug] EE SIO Message: # Initialize VIF0 ...
[Debug] EE SIO Message: # Initialize IPU ...
[Debug] EE SIO Message: # Initialize FPU ...
[Debug] EE SIO Message: # Initialize User Memory ...
[Debug] IOP: IOP Timer5 Compare Write u32, Value = 0x12000.
[Debug] IOP interrupt exception occurred @ cycle = 0x1B5B8A, PC = 0x00002ED0, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] TMR5
[Debug] IOP: IOP Timer5 Compare Write u32, Value = 0xFFFEE000.
[Debug] IOP interrupt exception occurred @ cycle = 0x1B8595, PC = 0x00001A94, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1B8781, PC = 0x00001A94, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1BDDE2, PC = 0x00002268, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1CB5BB, PC = 0x000040B0, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1D6C7D, PC = 0x000024C8, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1E301D, PC = 0x00017FEC, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1EF8DA, PC = 0x0000407C, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x1FCE11, PC = 0x0000407C, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x20A000, PC = 0x000177E4, BD = 1.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] EE SIO Message: # Initialize Scratch Pad ...
[Debug] EE SIO Message: # Initialize Done.
[Debug] EE SIO Message: 
[Debug] EE SIO Message: EE DECI2 Manager version 0.06 Dec 10 1999 17:48:37
[Debug] EE SIO Message:   CPUID=2e20, BoardID=0, ROMGEN=2000-0117, 32M
[Debug] EE SIO Message: 
[Debug] IOP interrupt exception occurred @ cycle = 0x216E4D, PC = 0x00002634, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x2233D0, PC = 0xA0003038, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x22F66B, PC = 0x00002F08, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x23BDF5, PC = 0x00002F2C, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x2486DB, PC = 0x00002DD0, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x255420, PC = 0x0000226C, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x261569, PC = 0x00002F2C, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x26E250, PC = 0x00002264, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x27A771, PC = 0x00002F04, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x288BA7, PC = 0x0000BA60, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x293527, PC = 0x00002268, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] EE tag (source chain mode) read on channel SIF1. Tag0 = 0x00000003, Tag1= 0x0001E340, TTE = 0.
[Debug] EE DMA tag info: QWC = 0x3, PCE = 0x0, ID = 0x0, IRQ = 0x0, ADDR = 0x1E340, SPR = 0x0.
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x00000008C0019500, valueHi = 0x0000000000000000 <- MemAddr = 0x0001E340
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x0000000000000014, valueHi = 0x0000000080000002 <- MemAddr = 0x0001E350
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x000000010008C240, valueHi = 0x2008C2C02008C240 <- MemAddr = 0x0001E360
[Debug] IOP tag (dest chain mode) read on channel SIF1. Tag0 = 0xC0019500, Tag1 = 0x00000008, XFER_EE_TAG = 1.
[Debug] IOP DMA tag info: Length = 0x8, IRQ = 0x1, ERT = 0x1, ADDR = 0x19500.
[Warning] IOP DMAC dest chain mode EE tag had size of zero - not sending.
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000014 -> MemAddr = 0x00019500
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000000 -> MemAddr = 0x00019504
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x80000002 -> MemAddr = 0x00019508
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000000 -> MemAddr = 0x0001950C
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x0008C240 -> MemAddr = 0x00019510
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000001 -> MemAddr = 0x00019514
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x2008C240 -> MemAddr = 0x00019518
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x2008C2C0 -> MemAddr = 0x0001951C
[Debug] EE tag (source chain mode) read on channel SIF1. Tag0 = 0x30000003, Tag1= 0x0001E340, TTE = 0.
[Debug] EE DMA tag info: QWC = 0x3, PCE = 0x0, ID = 0x3, IRQ = 0x0, ADDR = 0x1E340, SPR = 0x0.
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x00000008C0019500, valueHi = 0x0000000000000000 <- MemAddr = 0x0001E340
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x0000000000000014, valueHi = 0x0000000080000002 <- MemAddr = 0x0001E350
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x000000010008C240, valueHi = 0x2008C2C02008C240 <- MemAddr = 0x0001E360
[Debug] EE tag (source chain mode) read on channel SIF1. Tag0 = 0x00000002, Tag1= 0x0001E3C0, TTE = 0.
[Debug] EE DMA tag info: QWC = 0x2, PCE = 0x0, ID = 0x0, IRQ = 0x0, ADDR = 0x1E3C0, SPR = 0x0.
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x00000004C0019500, valueHi = 0x0000000000000000 <- MemAddr = 0x0001E3C0
[Debug] EE DMAC Write u128 channel SIF1, valueLo = 0x0000000000000010, valueHi = 0x0000000180000002 <- MemAddr = 0x0001E3D0
[Debug] IOP interrupt exception occurred @ cycle = 0x29A98F, PC = 0x00039334, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] DMA
[Debug] IOP tag (dest chain mode) read on channel SIF1. Tag0 = 0xC0019500, Tag1 = 0x00000008, XFER_EE_TAG = 1.
[Debug] IOP DMA tag info: Length = 0x8, IRQ = 0x1, ERT = 0x1, ADDR = 0x19500.
[Warning] IOP DMAC dest chain mode EE tag had size of zero - not sending.
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000014 -> MemAddr = 0x00019500
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000000 -> MemAddr = 0x00019504
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x80000002 -> MemAddr = 0x00019508
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000000 -> MemAddr = 0x0001950C
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x0008C240 -> MemAddr = 0x00019510
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000001 -> MemAddr = 0x00019514
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x2008C240 -> MemAddr = 0x00019518
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x2008C2C0 -> MemAddr = 0x0001951C
[Debug] IOP tag (dest chain mode) read on channel SIF1. Tag0 = 0xC0019500, Tag1 = 0x00000004, XFER_EE_TAG = 1.
[Debug] IOP DMA tag info: Length = 0x4, IRQ = 0x1, ERT = 0x1, ADDR = 0x19500.
[Warning] IOP DMAC dest chain mode EE tag had size of zero - not sending.
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000010 -> MemAddr = 0x00019500
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000000 -> MemAddr = 0x00019504
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x80000002 -> MemAddr = 0x00019508
[Debug] IOP DMAC Read u32 channel SIF1, value = 0x00000001 -> MemAddr = 0x0001950C
[Debug] IOP tag (source chain mode) read on channel SIF0. Tag0 = 0x80019770, Tag1= 0x00000006, XFER_EE_TAG = 1.
[Debug] IOP DMA tag info: Length = 0x6, IRQ = 0x0, ERT = 0x1, ADDR = 0x19770.
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000018 <- MemAddr = 0x00019770
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000000 <- MemAddr = 0x00019774
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x80000001 <- MemAddr = 0x00019778
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000000 <- MemAddr = 0x0001977C
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000000 <- MemAddr = 0x00019780
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000001 <- MemAddr = 0x00019784
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000000 <- MemAddr = 0x00019788
[Debug] IOP DMAC Write u32 channel SIF0, value = 0x00000000 <- MemAddr = 0x0001978C
[Debug] EE tag (dest chain mode) read on channel SIF0. Tag0 = 0x90000002, Tag1= 0x0008C240, TTE = 0.
[Debug] EE DMA tag info: QWC = 0x2, PCE = 0x0, ID = 0x1, IRQ = 0x1, ADDR = 0x8C240, SPR = 0x0.
[Debug] EE DMAC Read u128 channel SIF0, valueLo = 0x0000000000000018, valueHi = 0x0000000080000001 -> MemAddr = 0x0008C240
[Debug] EE DMAC Read u128 channel SIF0, valueLo = 0x0000000100000000, valueHi = 0x0000000000000000 -> MemAddr = 0x0008C250
[Warning] EE DMAC channel SIF0 had tag IRQ flag set - please verify what is meant to happen!
[Debug] EE interrupt exception occurred @ cycle = 0x14312CB, PC = 0x0008433C, BD = 1.
[Debug] Printing list of interrupt sources...
[Debug] DMAC
[Debug] IOP interrupt exception occurred @ cycle = 0x29B4AD, PC = 0x0000D610, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] DMA
[Debug] IOP interrupt exception occurred @ cycle = 0x2A2335, PC = 0x0003D970, BD = 1.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP: IOP Timer5 Compare Write u32, Value = 0x2D3545D.
[Debug] IOP interrupt exception occurred @ cycle = 0x2AC17C, PC = 0x0000AE94, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x2BAABD, PC = 0x0000AE94, BD = 0.
[Debug] Printing list of interrupt sources...
[Debug] VBLANK
[Debug] IOP interrupt exception occurred @ cycle = 0x2C93FF, PC = 0x0000AE98, BD = 1.
[Debug] Printing list of interrupt sources...
[Debug] EVBLANK

(EE and IOP are in a idle loop state awaiting interrupts.)
```
## Build Instructions

Currently, only compiling in x86-64 on Visual Studio 2017 is used. 
However, it should be ok to compile on any other system so far (platform independent code).
The only thing that may require a change is the f32 (float) definition, if the float type is not 32-bit.
See the solution file PCSX2_Rewrite.sln.

The project uses the following libraries as git submodules:
(you will need to 'git submodule init' etc, see https://chrisjean.com/git-submodules-adding-using-removing-and-updating/ for basic instructions).

- Google test library (only for PCSX2_Core_UnitTest, you can build the Core and Frontend projects without).