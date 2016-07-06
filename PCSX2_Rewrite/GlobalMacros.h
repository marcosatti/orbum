#pragma once

/*
Enable inlineing of functions given that its not a debug build. If enabled for debug builds it makes it difficult to read stack traces etc due to the code not lining up in the debugger.
*/
#ifdef _DEBUG
#define INLINE
#else
#define INLINE __inline
#endif