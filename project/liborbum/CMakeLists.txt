cmake_minimum_required(VERSION 3.1)

project(liborbum CXX)

set(COMMON_SRC_FILES
	src/Common/Log.cpp
	src/Common/Types/Bus/ByteBus.cpp
	src/Common/Types/FifoQueue/FifoQueue.cpp
	src/Common/Types/FifoQueue/SpscFifoQueue.cpp
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
	src/Resources/Ee/Core/EeCoreInstructionTable.cpp
	src/Resources/Ee/Core/EeCoreR5900.cpp
	src/Resources/Ee/Core/EeCoreTlb.cpp
	src/Resources/Ee/Core/REeCore.cpp
	src/Resources/Ee/Dmac/EeDmacChannelRegisters.cpp
	src/Resources/Ee/Dmac/EeDmacRegisters.cpp
	src/Resources/Ee/Dmac/REeDmac.cpp
	src/Resources/Ee/EeRegisters.cpp
	src/Resources/Ee/Gif/RGif.cpp
	src/Resources/Ee/Intc/EeIntcRegisters.cpp
	src/Resources/Ee/Intc/REeIntc.cpp
	src/Resources/Ee/Ipu/RIpu.cpp
	src/Resources/Ee/REe.cpp
	src/Resources/Ee/Timers/EeTimersUnitRegisters.cpp
	src/Resources/Ee/Timers/REeTimers.cpp
	src/Resources/Ee/Vpu/RVpu.cpp
	src/Resources/Ee/Vpu/VifcodeInstruction.cpp
	src/Resources/Ee/Vpu/VifcodeInstructionTable.cpp
	src/Resources/Ee/Vpu/VifCores.cpp
	src/Resources/Ee/Vpu/VuCoreRegisters.cpp
	src/Resources/Ee/Vpu/VuCores.cpp
	src/Resources/Ee/Vpu/VuVectorField.cpp
	src/Resources/Gs/RGs.cpp
	src/Resources/Iop/Core/IopCoreCop0.cpp
	src/Resources/Iop/Core/IopCoreCop0Registers.cpp
	src/Resources/Iop/Core/IopCoreInstruction.cpp
	src/Resources/Iop/Core/IopCoreInstructionTable.cpp
	src/Resources/Iop/Core/IopCoreR3000.cpp
	src/Resources/Iop/Core/RIopCore.cpp
	src/Resources/Iop/Dmac/IopDmacChannelRegisters.cpp
	src/Resources/Iop/Dmac/IopDmacRegisters.cpp
	src/Resources/Iop/Dmac/RIopDmac.cpp
	src/Resources/Iop/Intc/IopIntcRegisters.cpp
	src/Resources/Iop/RIop.cpp
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
)

add_library(liborbum ${COMMON_SRC_FILES})

# Disable MSVC non-safe copy warnings.
target_compile_definitions(liborbum PUBLIC "_SCL_SECURE_NO_WARNINGS")
# Sort out later into proper build configurations.
target_compile_definitions(liborbum PUBLIC "BUILD_DEBUG")

target_include_directories(liborbum PUBLIC "${CMAKE_SOURCE_DIR}/project/liborbum/src")
target_link_libraries(liborbum PUBLIC Boost::boost)
target_link_libraries(liborbum PUBLIC Boost::log)