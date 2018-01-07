cmake_minimum_required(VERSION 3.1)

project(liborbum CXX)

set(COMMON_SRC_FILES
	src/Utilities/Utilities.cpp
	src/Core.cpp
	src/Common/Types/Bus/ByteBus.cpp
	src/Common/Types/FifoQueue/FifoQueue.cpp
	src/Common/Types/Memory/ArrayByteMemory.cpp
	src/Common/Types/Memory/ArrayHwordMemory.cpp
	src/Common/Types/Memory/ByteMemory.cpp
	src/Common/Types/Memory/HwordMemory.cpp
	src/Common/Types/Register/ByteRegister.cpp
	src/Common/Types/Register/DwordRegister.cpp
	src/Common/Types/Register/HwordRegister.cpp
	src/Common/Types/Register/MapperHwordWordRegister.cpp
	src/Common/Types/Register/QwordRegister.cpp
	src/Common/Types/Register/SizedByteRegister.cpp
	src/Common/Types/Register/SizedDwordRegister.cpp
	src/Common/Types/Register/SizedHwordRegister.cpp
	src/Common/Types/Register/SizedQwordRegister.cpp
	src/Common/Types/Register/SizedWordRegister.cpp
	src/Common/Types/Register/WordRegister.cpp
	src/Resources/Cdvd/CdvdFifoQueues.cpp
	src/Resources/Cdvd/CdvdNvrams.cpp
	src/Resources/Cdvd/CdvdRegisters.cpp
	src/Resources/Cdvd/RCdvd.cpp
	src/Resources/Ee/Core/EeCoreCop0.cpp
	src/Resources/Ee/Core/EeCoreCop0Registers.cpp
	src/Resources/Ee/Core/EeCoreFpu.cpp
	src/Resources/Ee/Core/EeCoreFpuRegisters.cpp
	src/Resources/Ee/Core/EeCoreInstruction.cpp
	src/Resources/Ee/Core/EeCoreR5900.cpp
	src/Resources/Ee/Core/EeCoreTlb.cpp
	src/Resources/Ee/Core/REeCore.cpp
	src/Resources/Ee/Dmac/EeDmacChannelTable.cpp
	src/Resources/Ee/Dmac/EeDmacChannelRegisters.cpp
	src/Resources/Ee/Dmac/EeDmacRegisters.cpp
	src/Resources/Ee/Dmac/REeDmac.cpp
	src/Resources/Ee/EeRegisters.cpp
	src/Resources/Ee/Gif/RGif.cpp
	src/Resources/Ee/Intc/EeIntcRegisters.cpp
	src/Resources/Ee/Intc/REeIntc.cpp
	src/Resources/Ee/Ipu/RIpu.cpp
	src/Resources/Ee/REe.cpp
	src/Resources/Ee/Timers/EeTimersUnits.cpp
	src/Resources/Ee/Timers/EeTimersUnitRegisters.cpp
	src/Resources/Ee/Timers/REeTimers.cpp
	src/Resources/Ee/Vpu/Vif/RVif.cpp
	src/Resources/Ee/Vpu/Vif/VifcodeInstruction.cpp
	src/Resources/Ee/Vpu/Vif/VifUnits.cpp
	src/Resources/Ee/Vpu/Vif/VifUnitRegisters.cpp
	src/Resources/Ee/Vpu/Vu/RVu.cpp
	src/Resources/Ee/Vpu/Vu/VuUnitRegisters.cpp
	src/Resources/Ee/Vpu/Vu/VuUnits.cpp
	src/Resources/Ee/Vpu/Vu/VuVectorField.cpp
	src/Resources/Gs/RGs.cpp
	src/Resources/Iop/Core/IopCoreCop0.cpp
	src/Resources/Iop/Core/IopCoreCop0Registers.cpp
	src/Resources/Iop/Core/IopCoreInstruction.cpp
	src/Resources/Iop/Core/IopCoreR3000.cpp
	src/Resources/Iop/Core/RIopCore.cpp
	src/Resources/Iop/Dmac/IopDmacChannelRegisters.cpp
	src/Resources/Iop/Dmac/IopDmacRegisters.cpp
	src/Resources/Iop/Dmac/RIopDmac.cpp
	src/Resources/Iop/Intc/IopIntcRegisters.cpp
	src/Resources/Iop/RIop.cpp
	src/Resources/Iop/Sio2/RSio2.cpp
	src/Resources/Iop/Sio2/Sio2Registers.cpp
	src/Resources/Iop/Timers/IopTimersUnitRegisters.cpp
	src/Resources/Iop/Timers/IopTimersUnits.cpp
	src/Resources/Iop/Timers/RIopTimers.cpp
	src/Resources/RResources.cpp
	src/Resources/SbusFifoQueues.cpp
	src/Resources/SbusRegisters.cpp
	src/Resources/Spu2/RSpu2.cpp
	src/Resources/Spu2/Spu2CoreRegisters.cpp
	src/Resources/Spu2/Spu2Cores.cpp
	src/Resources/Spu2/Spu2CoreTable.cpp
	src/Resources/Spu2/Spu2Registers.cpp
	src/Controller/Gs/Crtc/CCrtc.cpp
	src/Controller/Gs/Core/CGsCore.cpp
	src/Controller/Cdvd/CCdvd.cpp
	src/Controller/Cdvd/CCdvd_SCMD.cpp
	src/Controller/Spu2/CSpu2.cpp
	src/Controller/Iop/Core/Interpreter/CIopCoreInterpreter.cpp
	src/Controller/Iop/Core/Interpreter/CIopCoreInterpreter_ALU.cpp
	src/Controller/Iop/Core/Interpreter/CIopCoreInterpreter_BRANCH_JUMP.cpp
	src/Controller/Iop/Core/Interpreter/CIopCoreInterpreter_LOAD_STORE_MEM.cpp
	src/Controller/Iop/Core/Interpreter/CIopCoreInterpreter_OTHERS.cpp
	src/Controller/Iop/Core/Interpreter/CIopCoreInterpreter_SPECIAL_TRANSFER.cpp
	src/Controller/Iop/Dmac/CIopDmac.cpp
	src/Controller/Iop/Intc/CIopIntc.cpp
	src/Controller/Iop/Timers/CIopTimers.cpp
	src/Controller/Iop/Sio0/CSio0.cpp
	src/Controller/Iop/Sio2/CSio2.cpp
	src/Controller/Ee/Vpu/Vif/CVif.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_CONVERT.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_EFU.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_FLAG.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_FLOAT.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_INTEGER.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_OTHER.cpp
	src/Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter_TRANSFER.cpp
	src/Controller/Ee/Ipu/CIpu.cpp
	src/Controller/Ee/Gif/CGif.cpp
	src/Controller/Ee/Intc/CEeIntc.cpp
	src/Controller/Ee/Timers/CEeTimers.cpp
	src/Controller/Ee/Dmac/CEeDmac.cpp
	src/Controller/Ee/Dmac/CEeDmac_CHAIN.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_ALU_OTHERS.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_BREAK_TRAP.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_CALL.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_COMPARE.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_COND_BRANCH_JUMP.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_COP2.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_DFC.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_FLOAT.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_INTEGER_ADD_SUB.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_INTEGER_MULT_ADD.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_INTEGER_MULT_DIV.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_LOAD_MEM.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_LOGICAL.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_MIN_MAX.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_OTHERS.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_REG_TRANSFER.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_REORDERING.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_SHIFT.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_SPECIAL_TRANSFER.cpp
	src/Controller/Ee/Core/Interpreter/CEeCoreInterpreter_STORE_MEM.cpp
)

add_library(liborbum ${COMMON_SRC_FILES})

# TODO: Sort out later into proper build configurations.
# Also disable MSVC non-safe copy warnings.
target_compile_definitions(
	liborbum PUBLIC 
	 "_SCL_SECURE_NO_WARNINGS"
	"BUILD_DEBUG"
)

target_include_directories(
	liborbum PUBLIC
	"${Boost_INCLUDE_DIR}"
	"${CMAKE_SOURCE_DIR}/project/liborbum/src"
	"${CMAKE_SOURCE_DIR}/project/utilities/src"
)

target_link_libraries(
	liborbum 
	${Boost_LIBRARIES}
)

install(
	TARGETS liborbum 
	ARCHIVE DESTINATION "lib/static"
	LIBRARY DESTINATION "lib"
)
