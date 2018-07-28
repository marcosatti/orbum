#include <stdexcept>

#include <boost/format.hpp>

#include "Common/Options.hpp"
#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"

void CIopCoreInterpreter::BREAK(const IopCoreInstruction inst)
{
    // EXCEPTION(BREAKPOINT)
    handle_exception(IopCoreException::EX_BREAK);
}

void CIopCoreInterpreter::SYSCALL(const IopCoreInstruction inst)
{
    auto& r = core->get_resources();

#if DEBUG_LOG_IOP_SYSCALLS
    // Debug print the syscall mnemonic.
    // The convention is to store the syscall number in register $v0 ($2), then use the syscall instruction (the 'code' field within the syscall instruction is apparently unused).
    // When the syscall number is loaded into $v0, it is done so through
    //   ADDIU $v0, $0, number.
    // The IOP OS only defines handlers for syscall numbers 0 -> ??? (? total). TODO: figure out number of syscalls.
    int index = static_cast<int>(r.iop.core.r3000.gpr[2]->read_ubyte(0));
    BOOST_LOG(Core::get_logger()) << boost::format("IOPCore Syscall, number %d @ cycle = 0x%llX.")
                                         % index
                                         % DEBUG_LOOP_COUNTER;
#endif

    // EXCEPTION(SYSCALL)
    handle_exception(IopCoreException::EX_SYSTEMCALL);
}

void CIopCoreInterpreter::TLBP(const IopCoreInstruction inst)
{
    throw std::runtime_error("IOP TLB instructions not implemented.");
}

void CIopCoreInterpreter::TLBR(const IopCoreInstruction inst)
{
    throw std::runtime_error("IOP TLB instructions not implemented.");
}

void CIopCoreInterpreter::TLBWI(const IopCoreInstruction inst)
{
    throw std::runtime_error("IOP TLB instructions not implemented.");
}

void CIopCoreInterpreter::TLBWR(const IopCoreInstruction inst)
{
    throw std::runtime_error("IOP TLB instructions not implemented.");
}

void CIopCoreInterpreter::LWC2(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::SWC2(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::CFC0(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::CTC0(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::RFE(const IopCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Pop the COP0.Status exception state.
    r.iop.core.cop0.status.pop_exception_stack();

    // Force a flush of all irq lines - we could be in the state
    // where the IOP core is the only component left running, and
    // the next loop could cause an errornous interrupt to occur.
    // Since all components are constantly updating their interrupt
    // status, we don't really loose out on anything. RFE should
    // be the last instruction executed before interrupts can occur
    // again.
    r.iop.core.cop0.cause.clear_all_irq();

    // Flush translation caches (context change).
    translation_cache_data.flush();
    translation_cache_inst.flush();
}

void CIopCoreInterpreter::RTPS(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::NCLIP(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::OP(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::DPCS(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::INTPL(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::MVMVA(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::NCDS(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::CDP(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::NCDT(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::NCCS(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::CC(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::NCS(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::NCT(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::SQR(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::DCPL(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::DPCT(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::AVSZ3(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::AVSZ4(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::RTPT(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::GPF(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::GPL(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::MFC2(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::CFC2(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::MTC2(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}

void CIopCoreInterpreter::CTC2(const IopCoreInstruction inst)
{
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 opcode encountered (%s)!") % __FILENAME__ % __LINE__ % __FUNCTION__;
#endif
}
