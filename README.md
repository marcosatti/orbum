# orbum [![Travis CI Status](https://travis-ci.org/marco9999/orbum.svg?branch=master)](https://travis-ci.org/marco9999/orbum) [![AppVeyor Status](https://ci.appveyor.com/api/projects/status/github/marco9999/orbum?branch=master&svg=true)](https://ci.appveyor.com/project/marco9999/orbum)


#### PS2 Emulator
Based off PCSX2's codebase, this is a completely rewritten PS2 emulator. Only useful to developers for now.

I can only work on this in my spare time, so I am thankful for any help!

## Current status

Status as of 2018/08/06:
- Primary focus for now is on the GIF/VIF.
- Work started on the SPU2 (DMA and IOP communication done, sound generation still to be done).
- Work started on the SIO/SIO2 (controllers and MC's), IOP communication done.
- No work done yet on the IPU and GSCore.
- Everything else not mentioned mostly done (EECore, IOPCore, etc). Interpreters only for now, dynarecs will not come for a while.

## Build Instructions
### General Information
CMake is used as the build system. 

The project uses the following dependecies:
  - Boost library, which is configured by the CMake FindBoost module.
  - Cereal for serialization.

Run the following commands to invoke a build:

`git submodule update --init --recursive`

`mkdir build && cd build`

`cmake ..` optionally specifying `-DBOOST_ROOT={path}` depending on your environment.

`make` (or equivalent)

## Running
`./orbumfront`

Logging is always enabled and will save files to `logs/` (uses boost logging).

The bios file scph10000.bin should be placed in `bios/`.
Other bios' are not currently supported or tested with.

Upon Ctrl-C, a number of options will be presented:
  - A memory dump (binary) can be created that will be placed in the `dumps/` folder.
  - A save state (json/text readable) can be created that will dump the PS2 state for inspection. Uses the `saves/` folder.

## Licence

[GPL3](https://www.gnu.org/licenses/gpl-3.0.en.html)
