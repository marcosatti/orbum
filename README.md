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
- Boost library.

The following commands should be enough to get going:
```
user@pc:/PCSX2_rewrite$ git submodule update --init
user@pc:/PCSX2_rewrite$ cd external/boost 
user@pc:/PCSX2_rewrite/external/boost$ git checkout boost-1.64.0 (do not use the master branch - it will most likely fail to build, use `git clean -d -x -ff` if you have already)
user@pc:/PCSX2_rewrite/external/boost$ git submodule update --init (clone the boost submodules)
user@pc:/PCSX2_rewrite/external/boost$ ./bootstrap.[bat|sh] && ./b2 headers && ./b2 address-model=[32|64 (used normally)] link=[shared|static (used normally)] runtime-link=[shared|static (used normally)]
```
Or, if you know what you're doing, create symlink(s) to already existing directories.

No support for big-endian architectures (yet), or when a float is not 32-bits wide (see the f32 typedef).
Both 32-bit and 64-bit architectures are supported, however only 64-bit is used by me.
See `libpcsx2_core/src/Common/Global/CompileOptions.h` for a list of debug options you can use.

### CMake Support
PCSX2_Rewrite includes CMake support for building under Linux, macOS and Windows.
Build configurations avaliable include Debug, Debug_Optimised (default), Release.
Example usage: 
```
user@pc:/PCSX2_rewrite$ cd build && cmake .. && cmake --build .
```

Use the CMake GUI to see and set the list of options available (or use the command line).
In order to support every platform/config, please do not use the CMAKE_* variables to change options.
Instead, use the USER_* cache variables are available to the user.
Any modifications done to the CMAKE_* versions will be overridden by the USER_* ones.
Sane defaults have been provided for most compilers, so you probably don't need to change this.

By default, the install target (ie: `make install`) will copy the relevant files to PCSX2_rewrite/lib and PCSX2_rewrite/bin, etc.
Although, there is probably no reason to use it right now.

## Suggested Workflow (Visual Studio Code)
I am using Visual Studio Code (cross-platform) with the following settings:
- Preconfigured workspace .vscode config files, for launching/debugging/CMake Tools, which is included in the repo.
- The "C/C++" (ms-vscode.cpptools), "CMake" (twxs.cmake) and "CMake Tools" (vector-of-bool.cmake-tools) extensions.
- CMake binary installed (at least version 3.7 for the server backend which is turned on by default).

You are able to build and debug the project directly through VS Code (using the CMake support).
Again, if you need to change any of the compiler/linker flags, you can do so through the USER_* CMake cache variables.

## Other IDE's
Unfortunately (for Windows users), the full Visual Studio does not work currently, even with the inbuilt CMake open folder support.
It currently does not support custom build configurations, and is a real PITA when it comes to setting your own CXX flags etc, so mostly just doesn't work at all.
I might try again in the future, of course if someone else gets it working perfectly with the current CMakeLists.txt let me know.

Qt Creater might work, I haven't tried it though. It does have inbuild CMake support, so the framework is there.

## Running
Running the emulator is done so through the pcsx2_frontend project: `./pcsx2_frontend`.
By default, it uses `./workspace` in the current directory as the working area, in which it will search for the bios, store log files and dump raw memory contents.
The first argument to pcsx2_frontend will change this path (eg: `./pcsx2_frontend ./workspace/`, you need the trailing slash).
You will require the scph10000.bin bios. Other bios' have not been tested but may work.
