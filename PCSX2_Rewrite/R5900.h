#pragma once

#include "Globals.h"
#include "PS2Types.h"

class R5900_t {
public:
	/*
	The R5900 is the EE Core's CPU. It has been modified from a stock R5900 to include Sony specific instructions (multimedia instructions targeting 128-bit operations etc).
	It uses a little-endian configuration (bit 0 is always the LSB).
	*/

	// Register implementations.

	/*
	The R5900 general purpose registers (GPR's) are 128-bit long.
	The upper 64-bits are only used when specific instructions are run, such as using the EE Core specific multimedia instructions (parallel instructions). Example: PADDB.
	See EE Core Users Manual, pg 60.

	GPR defines the 32 GPR's contained within the R5900.
	This is implemented as the register numbers from r0 -> r31.

	From the EE Core Users Manual, r0 and r31 are reserved:
	- r0 is the zero register, meaning it is always set to a constant 0.
	- r31 is the link register used by the link and jump instructions. This is not to be used by other instructions.
	*/
	struct {
		Register128 r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;
	} GPR;

	/*
	The HI and LO registers. See EE Core Users manual, pg 60.
	These registers are used to hold the results of integer multiply and divide operations.
	They are 128-bit long.
	*/
	Register128 HI;      // The HI register. Divided into 2 64-bit segments: the upper 64-bits (HI1) and the lower 64-bits (HI0).
	Register128 LO;      // The LO register. Divided into 2 64-bit segments: the upper 64-bits (LO1) and the lower 64-bits (LO0).

	/*
	The Shift Amount (SA) register. See EE Core Users manual, pg 61.
	The SA register is used for holding funnel shift instruction results. See the EE Core instruction QFSRV for more details (SA is only used for this instruction).
	It is a 32-bit register.
	*/
	Register32 SA;

	/*
	The Program Counter (PC) register. See EE Core Users manual, pg 61.
	The PC has 3 states:
	1) During normal program execution, it will point to the current instruction and then get incremented by 4 when finished to move on to the next instruction.
	2) When a jump or branch instruction is encountered, it will point to the target address.
	3) When an exception occurs, the PC is changed to point to the exception vector address.
	It is a 32-bit register.
	*/
	Register32 PC;

	/*
	The opcode holder, used as a temporary holder for the current opcode.
	This is used in the translator and interpreter.
	Convenience funcions are also defined to access differnt parts of the opcode.
	*/
	u32 opcode;


private:
}; // class R5900