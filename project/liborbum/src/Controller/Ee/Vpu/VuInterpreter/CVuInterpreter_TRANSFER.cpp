
#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/Register/SizedQwordRegister.hpp"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/Ee/Vpu/VuCores.hpp"

void VUInterpreter_s::MOVE()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MOVE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MOVE: Not implemented.");
#endif
}

void VUInterpreter_s::MFIR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MFIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MFIR: Not implemented.");
#endif
}

void VUInterpreter_s::MTIR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MTIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MTIR: Not implemented.");
#endif
}

void VUInterpreter_s::MR32()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MR32: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MR32: Not implemented.");
#endif
}

void VUInterpreter_s::LQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQ: Not implemented.");
#endif
}

void VUInterpreter_s::LQD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQD: Not implemented.");
#endif
}

void VUInterpreter_s::LQI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LQI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQI: Not implemented.");
#endif
}

void VUInterpreter_s::SQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQ: Not implemented.");
#endif
}

void VUInterpreter_s::SQD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQD: Not implemented.");
#endif
}

void VUInterpreter_s::SQI()
{
	// MEM(Ft) = Fs
	auto& source1Reg = mVUCore->VF[mVUInstruction.fs()];
	auto& source2Reg = mVUCore->VI[mVUInstruction.ft()]; // Mem Addr.
	auto& Mem = mVUCore->MMU;

	// Real address obtained by VI * 16.
	uword realPhysicalAddress = source2Reg->read_uhword() * 16;

	// 32-bit write for each dest subfield.
	if (mVUInstruction.test_dest_x()) Mem->write_uword(realPhysicalAddress, source1Reg->read_uword(0));
	if (mVUInstruction.test_dest_y()) Mem->write_uword(realPhysicalAddress + 4, source1Reg->read_uword(1));
	if (mVUInstruction.test_dest_z()) Mem->write_uword(realPhysicalAddress + 8, source1Reg->read_uword(2));
	if (mVUInstruction.test_dest_w()) Mem->write_uword(realPhysicalAddress + 12, source1Reg->read_uword(3));

	// Post increment.
	source2Reg->write_uhword(source2Reg->read_uhword() + 1);
}

void VUInterpreter_s::ILW()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ILW: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ILW: Not implemented.");
#endif
}

void VUInterpreter_s::ISW()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ISW: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISW: Not implemented.");
#endif
}

void VUInterpreter_s::ILWR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ILWR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ILWR: Not implemented.");
#endif
}

void VUInterpreter_s::ISWR()
{
	// MEM(Fs) = Ft.
	auto& source1Reg = mVUCore->VI[mVUInstruction.ft()]; // Data.
	auto& source2Reg = mVUCore->VI[mVUInstruction.fs()]; // Mem Addr.
	auto& Mem = mVUCore->MMU;

	// Real address obtained by VI * 16.
	uword realPhysicalAddress = source2Reg->read_uhword() * 16;

	// 32-bit write for each dest subfield. Upper 16-bits of VI[Ft] value is set to 0.
	if (mVUInstruction.test_dest_x()) Mem->write_uword(realPhysicalAddress, static_cast<uword>(source1Reg->read_uhword()));
	if (mVUInstruction.test_dest_y()) Mem->write_uword(realPhysicalAddress + 4, static_cast<uword>(source1Reg->read_uhword()));
	if (mVUInstruction.test_dest_z()) Mem->write_uword(realPhysicalAddress + 8, static_cast<uword>(source1Reg->read_uhword()));
	if (mVUInstruction.test_dest_w()) Mem->write_uword(realPhysicalAddress + 12, static_cast<uword>(source1Reg->read_uhword()));
}

void VUInterpreter_s::LOI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LOI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LOI: Not implemented.");
#endif
}

void VUInterpreter_s::MFP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MFP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MFP: Not implemented.");
#endif
}
