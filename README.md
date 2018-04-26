# orbum [![Travis CI Status](https://travis-ci.org/marco9999/orbum.svg?branch=master)](https://travis-ci.org/marco9999/orbum) [![AppVeyor Status](https://ci.appveyor.com/api/projects/status/github/marco9999/orbum?branch=master&svg=true)](https://ci.appveyor.com/project/marco9999/orbum)


#### PS2 Emulator
An attempt at updating the PCSX2 codebase:

* Rewritten from the ground up, taking a more organised structure.
* Clear codebase to make it easy to read & contribute.
* Cross-compilable, with no platform dependant code (mobile/ARM/etc targets possible).

I can only work on this in my spare time, so I am thankful for any help!

## Current status

Status as of 2018/1/1:
- Primary focus for now is on the IOP, will continue on the EE side after.
- Work started on the SIO/SIO2 (controllers and MC's).
- Work started on the VIFs and VUs, mostly just implementing instructions left.
- Work started on the SPU2 (DMA and IOP communication done, sound generation still to be done).
- No work done yet on the IPU, GIF and GSCore.
- Everything else not mentioned mostly done (EECore, IOPCore, etc). Interpreters only for now, dynarecs will not come for a while.

## Build Instructions
### General Information
CMake is used as the build system. 
The project uses the boost library as a dependency, which is configured by the CMake FindBoost module.

Run the following commands to invoke a build:

`mkdir build && cd build`

`cmake ..` optionally specifying `-DBOOST_ROOT={path}` depending on your environment.

`make` (or equivilant)

## Running
`./orbumfront`

The bios file scph10000.bin should be placed in `bios/`.
Other bios' are not currently supported or tested with.

Upon Ctrl-C, memory dumps will be placed in the `dumps/` folder.
Logging will save files to `logs/` (uses boost logging).

These folders should be placed relative to the executable.

## Licence

[GPL3](https://www.gnu.org/licenses/gpl-3.0.en.html)
