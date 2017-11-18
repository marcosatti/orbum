#pragma once

#include "Common/Types/Register/SizedDwordRegister.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"

#include "Resources/Gs/Crtc/RCrtc.hpp"

/// Graphics synthesizer (GS) resources.
class RGs
{
public:
	RGs();

	/// (P)CRTC resources.
	RCrtc crtc;

	/*
	GS privileged registers, defined on page 26 onwards of the EE Users Manual. All start from PS2 physical address 0x12000000 to 0x14000000.
	*/
	// 0x12000000.
	SizedDwordRegister pmode;
	SizedDwordRegister smode1;
	SizedDwordRegister smode2;
	SizedDwordRegister srfsh;
	SizedDwordRegister synch1;
	SizedDwordRegister synch2;
	SizedDwordRegister syncv;
	SizedDwordRegister dispfb1;
	SizedDwordRegister display1;
	SizedDwordRegister dispfb2;
	SizedDwordRegister display2;
	SizedDwordRegister extbuf;
	SizedDwordRegister extdata;
	SizedDwordRegister extwrite;
	SizedDwordRegister bgcolor;
	ArrayByteMemory    memory_00f0;

	// 0x12001000.
	SizedDwordRegister csr;
	SizedDwordRegister imr;
	ArrayByteMemory    memory_1020;
	SizedDwordRegister busdir;
	ArrayByteMemory    memory_1050;
	SizedDwordRegister siglblid;
	ArrayByteMemory    memory_1090;
	ArrayByteMemory    memory_1100;

	// 0x12002000.
	ArrayByteMemory memory_2000;
};

