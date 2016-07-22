#pragma once


/*
Enable the PCSX2_DEBUG token if a debug build configuration is detected
*/
#if defined(_DEBUG) || defined(_DEBUG_BUILD)
#define PCSX2_DEBUG
#endif

/*
Enable inlineing of functions given that its not a debug build. If enabled for debug builds it makes it difficult to read stack traces etc due to the code not lining up in the debugger.
*/
#if defined(PCSX2_DEBUG)
#define INLINE
#else
#define INLINE __inline
#endif