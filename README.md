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

As of 14/12/16:
- Main loop & VM (including timing of components and the host MMU) implemented.
- EE Core mostly implemented. No handling of the cache modes supported.
- EE Timers, INTC, DMAC, etc mostly implemented (structure and system logic).
- IOP Core mostly implemented.
- IOP Timers, INTC, DMAC, etc structure implemented, system logic not done.
- GS not implemented.
- VU's/VIF's structure implemented, system logic to follow.
- No input, sound, graphics yet. Will try to get a basic software graphics solution going before anything else.

Starting to see some promising debug messages :)
```
[DEBUG] (EECoreExceptionHandler.cpp, 49) EECoreExceptionHandler called! Type = EX_RESET
[DEBUG] (IOPCoreExceptionHandler.cpp, 48) IOPCoreExceptionHandler called! Type = EX_RESET
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize memory (rev:3.17, ctm:393Mhz, cpuclk:295Mhz )
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Total accessable memory size: 32 MB (B:2:8:0)
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # TLB spad=0 kernel=1:12 default=13:30 extended=31:38
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize Start.
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize GS ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize INTC ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize TIMER ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize DMAC ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize VU1 ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize VIF1 ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize GIF ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize VU0 ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize VIF0 ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize IPU ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize FPU ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize User Memory ...
[DEBUG] (IOPCoreExceptionHandler.cpp, 48) IOPCoreExceptionHandler called! Type = EX_SYSTEMCALL
[DEBUG] (IOPCoreExceptionHandler.cpp, 48) IOPCoreExceptionHandler called! Type = EX_SYSTEMCALL
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize Scratch Pad ...
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: # Initialize Done.
[DEBUG] (EERegisters_t.cpp, 28) SIO Message:
[DEBUG] (EERegisters_t.cpp, 28) SIO Message: EE DECI2 Manager version 0.06 Dec 10 1999 17:48:37
[DEBUG] (EERegisters_t.cpp, 28) SIO Message:   CPUID=2e20, BoardID=0, ROMGEN=2000-0117, 32M
[DEBUG] (EERegisters_t.cpp, 28) SIO Message:
(Crash in EE DMAC SIF0 channel implementation - complaining of a missing TADR register).
```
## Build Instructions

Currently, only compiling in x86-64 on Visual Studio 2015 (community edition, update 2 +) is tested. 
However, it should be ok to compile on any other system so far (platform independent code).
The only thing that may require a change is the f32 (float) definition, if the float type keyword in C++ is not 32-bit.
See the solution file PCSX2_Rewrite.sln.

The project uses the following libraries as git submodules:
(you will need to 'git submodule init' etc, see https://chrisjean.com/git-submodules-adding-using-removing-and-updating/ for basic instructions).

- Google test library (only for PCSX2_Core_UnitTest, you can build the Core and Frontend projects without)