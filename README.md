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

As of 24/09/16:
- Main loop & VM (including timing of components and the host MMU) implemented.
- EE Core mostly implemented (including the PS2 MMU). No handling of the cache modes supported.
- EE Timers and INTC implemented, DMAC to follow and anything else.
- GS not implemented.
- VU's not implemented.

Interpreter currently runs correct (using scph10000.bin as bios) up until DEBUG_PC_BREAKPOINT = 0x9fc43070 (EE Core PC), where DEBUG_LOOP_BREAKPOINT = 0xE79894 (number of EE Core emulation loops, see source code).
This is done by checking against PCSX2's EE Core registers.

## Build Instructions

Currently, only compiling on Visual Studio 2015 (community edition, update 2 +) is supported. Both x86-32 and x86-64 supported currently.
See the solution file PCSX2_Rewrite.sln.

The project uses the following libraries as git submodules:
(you will need to 'git submodule init' etc, see https://chrisjean.com/git-submodules-adding-using-removing-and-updating/ for basic instructions).

- Google test library (only for PCSX2_Core_UnitTest)