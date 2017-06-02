cmake_minimum_required(VERSION 3.1)

project(pcsx2_frontend CXX)

include_directories(
	${CMAKE_SOURCE_DIR}/project/pcsx2_frontend/src 
	${CMAKE_SOURCE_DIR}/project/libpcsx2_core/libpcsx2_core/src 
)

set(PROJECT_LIBS
	pcsx2_core
)

set(COMMON_SRC_FILES
	src/PCSX2_Frontend.cpp
)

find_package(Threads)
add_executable(pcsx2_frontend ${COMMON_SRC_FILES})
target_link_libraries(pcsx2_frontend ${PROJECT_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Visual studio startup project
if (NOT (${CMAKE_VERSION} VERSION_LESS 3.6))
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT pcsx2_frontend)
endif()

# Install rules.
install(TARGETS pcsx2_frontend RUNTIME DESTINATION bin)