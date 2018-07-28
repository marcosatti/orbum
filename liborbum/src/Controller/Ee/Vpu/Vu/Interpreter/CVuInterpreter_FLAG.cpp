#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"

void CVuInterpreter::FSAND(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FSAND: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FSAND: Not implemented.");
#endif
}

void CVuInterpreter::FSEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FSEQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FSEQ: Not implemented.");
#endif
}

void CVuInterpreter::FSOR(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FSOR: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FSOR: Not implemented.");
#endif
}

void CVuInterpreter::FSSET(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FSSET: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FSSET: Not implemented.");
#endif
}

void CVuInterpreter::FMAND(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FMAND: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FMAND: Not implemented.");
#endif
}

void CVuInterpreter::FMEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FMEQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FMEQ: Not implemented.");
#endif
}

void CVuInterpreter::FMOR(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FMOR: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FMOR: Not implemented.");
#endif
}

void CVuInterpreter::FCAND(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FCAND: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FCAND: Not implemented.");
#endif
}

void CVuInterpreter::FCEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FCEQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FCEQ: Not implemented.");
#endif
}

void CVuInterpreter::FCOR(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FCOR: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FCOR: Not implemented.");
#endif
}

void CVuInterpreter::FCSET(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FCSET: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FCSET: Not implemented.");
#endif
}

void CVuInterpreter::FCGET(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Implement.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) FCGET: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("FCGET: Not implemented.");
#endif
}
