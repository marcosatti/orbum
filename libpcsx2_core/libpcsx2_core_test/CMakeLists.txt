cmake_minimum_required(VERSION 2.8)

project(libpcsx2_core_test)

include_directories(
	./src 
	../libpcsx2_core/src 
	../../external/googletest/googletest/include
)

set(PROJECT_LIBS
	gtest
	pcsx2_core
)

set(COMMON_SRC_FILES
	src/Main.cpp
	src/Tests/Common/TEST_ByteMMU_t.cpp
	src/Tests/Common/TEST_MIPSInstruction_t.cpp
	src/Tests/Common/TEST_PrimativeTypes.cpp
	src/Tests/EE/TEST_EECoreInterpreter_s.cpp
	src/Tests/IOP/TEST_IOPCoreInterpreter_s.cpp
)

add_executable(libpcsx2_core_test ${COMMON_SRC_FILES})
target_link_libraries(libpcsx2_core_test ${PROJECT_LIBS}) 
set_target_properties(libpcsx2_core_test PROPERTIES CXX_STANDARD 14)
set_target_properties(libpcsx2_core_test PROPERTIES CXX_STANDARD_REQUIRED ON)
