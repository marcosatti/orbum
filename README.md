# PCSX2_rewrite

An attempt at updating the PCSX2 codebase with 3 primary objectives:

* Use OOP design practices (in C++) instead of the large C type programming currently in use.
* Document as much as possible. Currently there is very little documentation on most things.
* Get rid of the bloat accumulated over 10+ years (a lot of this will be done through the use of OOP).
* Able to be compiled on popular platforms, such as x86-64 and ARM (including dynarec cores).

It holds the same license as PCSX2 (GPL-2+).

I am employed full-time, so I can only work on this in my spare time.

Marco.

## Current status

Status as of 2017/05/21:
- Primary focus for now is on the IOP, will continue on the EE side after.
- Work started on the SIO/SIO2 (controllers and MC's).
- Work started on the VIFs and VUs, mostly just implementing instructions left.
- Work started on the SPU2 (DMA and IOP communication done, sound generation still to be done).
- No work done yet on the IPU, GIF and GSCore.
- Everything else not mentioned mostly done (EECore, IOPCore, etc). Interpreters only for now, dynarecs will not come for a while.
- Multithreaded VM works, but is not polished enough for use (race conditions not handled yet, but should be easy/medium to fix).

## Build Instructions
The project uses the following libraries as git submodules:
- Google test library (only for PCSX2_Core_UnitTest, you can build the Core and Frontend projects without).

The following command should be enough to get going:
```
marco@pc:/PCSX2_rewrite$ git submodule init && git submodule update
```
No support for big-endian architectures (yet), or when a float is not 32-bits wide (see the f32 typedef).
See `PCSX2_Core/src/Common/Global/CompileOptions.h` for a list of debug options you can use.

### Visual Studio 2017 (my primary environment)
```
Open the solution file and 'Build Solution'. 
Only the x64 platform is used by me, but any configuration should work.
```
### GCC
```
Typical build command:
marco@pc:/PCSX2_rewrite/PCSX2_Frontend$ g++ -std=c++14 -g -O3 -D_DEBUG -pthread -I../PCSX2_Core/src src/PCSX2_Frontend.cpp `find ../PCSX2_Core/src -name *.cpp` -o pcsx2_frontend
(No build script yet.)
```
### Clang/LLVM
```
Typical build command:
marco@pc:/PCSX2_rewrite/PCSX2_Frontend$ clang++-4.0 -std=c++1z -g -O3 -D_DEBUG -pthread -I../PCSX2_Core/src src/PCSX2_Frontend.cpp `find ../PCSX2_Core/src -name *.cpp` -o pcsx2_frontend
(Note the clang++4.0 and -std=c++1z option, using either clang 3.8 or the -std=c++14 option causes it to fail, a bug report has been submitted about this.)
(No build script yet.)
```