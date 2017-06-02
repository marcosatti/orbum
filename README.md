# PCSX2_rewrite

An attempt at updating the PCSX2 codebase with 3 primary objectives:

* Use OOP design practices (in C++) instead of the large C type programming currently in use.
* Document as much as possible. Currently there is very little documentation on most things.
* Get rid of the bloat accumulated over 10+ years (a lot of this will be done through the use of OOP).
* Able to be compiled on popular platforms, such as x86-64 and ARM (including dynarec cores).

It holds the same GPL-2+ license as PCSX2.

I can only work on this in my spare time, so I am thankful for any help!

Marco.

## Current status

Status as of 2017/06/02:
- Primary focus for now is on the IOP, will continue on the EE side after.
- Work started on the SIO/SIO2 (controllers and MC's).
- Work started on the VIFs and VUs, mostly just implementing instructions left.
- Work started on the SPU2 (DMA and IOP communication done, sound generation still to be done).
- No work done yet on the IPU, GIF and GSCore.
- Everything else not mentioned mostly done (EECore, IOPCore, etc). Interpreters only for now, dynarecs will not come for a while.
- Multithreaded VM works, but is not polished enough for use (race conditions not handled yet, but should be easy/medium to fix).

Some debug output:
```
[Info] VM reset started...
[Info] VM resources initialised.
[Info] VM roms initialised.
[Info] VM systems initialised.
[Info] VM system threads initialised.
[Info] VM reset done, now paused.
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
[Debug] EE SIO Message: # Initialize Scratch Pad ...
[Debug] EE SIO Message: # Initialize Done.
[Debug] EE SIO Message:
[Debug] EE SIO Message: EE DECI2 Manager version 0.06 Dec 10 1999 17:48:37
[Debug] EE SIO Message:   CPUID=2e20, BoardID=0, ROMGEN=2000-0117, 32M
...
[Debug] IOPCore interrupt exception occurred @ cycle = 0x7DE712, PC = 0x00018208, BD = 0. Printing interrupt sources:
[Debug] DMAC
[Debug] Printing IOP DMAC interrupt sources:
[Debug] SIF0
[Debug] IOPCore interrupt exception occurred @ cycle = 0x7E4FFD, PC = 0x0006C000, BD = 1. Printing interrupt sources:
[Debug] VBLANK
[Debug] EECore interrupt exception occurred @ cycle = 0x432ADF7, PC = 0x00081FD0, BD = 0. Printing interrupt sources:
[Debug] DMAC
[Debug] Printing EE DMAC interrupt sources:
[Debug] SIF0
[Debug] IOPCore interrupt exception occurred @ cycle = 0x7E841C, PC = 0x00019264, BD = 1. Printing interrupt sources:
[Debug] DMAC
[Debug] Printing IOP DMAC interrupt sources:
[Debug] SIF0
[Debug] EECore interrupt exception occurred @ cycle = 0x432CF49, PC = 0x00081FDC, BD = 1. Printing interrupt sources:
[Debug] DMAC
[Debug] Printing EE DMAC interrupt sources:
[Debug] SIF0
[Fatal] IOPCore: ByteMMU lookup failed (nullptr). Address (inc. offset) = 0x1F808270.
[Info] VM system threads destroyed.
[Info] VM systems destroyed.
[Info] VM resources destroyed.
[Info] VM stopped ok.
```

## Build Instructions
### General Information
The project uses the following libraries as git submodules:
- Google test library (only for PCSX2_Core_UnitTest, you can build the Core and Frontend projects without).

The following command should be enough to get going:
```
user@pc:/PCSX2_rewrite$ git submodule init && git submodule update
```
No support for big-endian architectures (yet), or when a float is not 32-bits wide (see the f32 typedef).
Both 32-bit and 64-bit architectures are supported, however only 64-bit is used by me.
See `PCSX2_Core/src/Common/Global/CompileOptions.h` for a list of debug options you can use.

### CMake Support
PCSX2_Rewrite includes CMake support for building under Linux, macOS and Windows.
Build configurations avaliable include Debug, Debug_Optimised (default), Release.
Example usage: 
```
user@pc:/PCSX2_rewrite$ cd build && cmake .. && cmake --build .
```

The CMake GUI is also supported and should probably be used in most cases.

By default, the install target (ie: `make install`) will copy the relevant files to PCSX2_rewrite/lib and PCSX2_rewrite/bin.

## Running
You will require the scph10000.bin bios. Other bios' have not been tested but may work.
Running the emulator will search for the bios in "./workspace".
