# orbum
#### PS2 Emulator
An attempt at updating the PCSX2 codebase:

* Rewritten from the ground up, taking little sniplets of logic where possible.
* Clear codebase to make it easy to read & contribute.
* Cross-compilable, with no platform dependant code (mobile/ARM/etc targets possible).

I can only work on this in my spare time, so I am thankful for any help!

## Current status

Status as of 2017/10/13:
- Primary focus for now is on the IOP, will continue on the EE side after.
- Work started on the SIO/SIO2 (controllers and MC's).
- Work started on the VIFs and VUs, mostly just implementing instructions left.
- Work started on the SPU2 (DMA and IOP communication done, sound generation still to be done).
- No work done yet on the IPU, GIF and GSCore.
- Everything else not mentioned mostly done (EECore, IOPCore, etc). Interpreters only for now, dynarecs will not come for a while.

## Build Instructions
### General Information
CMake is used as the build system. Run the following command in a build subdirectory:
`cmake .. -DCMAKE_BUILD_TYPE RelWithDebInfo`

The project uses the following libraries as git submodules:
- Boost-Cmake.

## Running
`./orbumfront [override_workspace_path]`

A workspace folder should exist in the working directory, with scph10000.bin placed in workspace/bios/.
Other bios' are not currently supported or tested with.

## Licence

[GPL3](https://www.gnu.org/licenses/gpl-3.0.en.html)
