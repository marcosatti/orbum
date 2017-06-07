cmake_minimum_required(VERSION 3.1)

project(libpcsx2_core_test CXX)

include_directories(
	${CMAKE_SOURCE_DIR}/external/boost
	${CMAKE_SOURCE_DIR}/project/libpcsx2_core/libpcsx2_core_test/src 
	${CMAKE_SOURCE_DIR}/project/libpcsx2_core/libpcsx2_core/src 
)

link_directories(
	${CMAKE_SOURCE_DIR}/external/boost/stage/lib
)

set(PROJECT_LIBS
	pcsx2_core
)

set(COMMON_SRC_FILES
#	src/Main.cpp
#	src/Tests/Common/TEST_ByteMMU_t.cpp
	src/Tests/Common/TEST_MIPSInstruction_t.cpp
	src/Tests/Common/TEST_PrimativeTypes.cpp
#	src/Tests/EE/TEST_EECoreInterpreter_s.cpp
#	src/Tests/IOP/TEST_IOPCoreInterpreter_s.cpp
)

find_package(Threads)
add_executable(libpcsx2_core_test ${COMMON_SRC_FILES})
target_link_libraries(libpcsx2_core_test ${PROJECT_LIBS} ${CMAKE_THREAD_LIBS_INIT}) 

# Visual studio startup project
if (NOT (${CMAKE_VERSION} VERSION_LESS 3.6))
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT libpcsx2_core_test)
endif()

# Install rules.
install(TARGETS libpcsx2_core_test RUNTIME DESTINATION bin)

# libpcsx2_core testing.
enable_testing()
add_test(libpcsx2_core_test ${EXECUTABLE_OUTPUT_PATH}/libpcsx2_core_test)

