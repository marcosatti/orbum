cmake_minimum_required(VERSION 2.8)

project(pcsx2_frontend)

include_directories(
	./src 
	../libpcsx2_core/libpcsx2_core/src
)

set(PROJECT_LIBS
	pcsx2_core
)

set(COMMON_SRC_FILES
	src/PCSX2_Frontend.cpp
)

add_executable(pcsx2_frontend ${COMMON_SRC_FILES})
target_link_libraries(pcsx2_frontend ${PROJECT_LIBS})
set_target_properties(pcsx2_frontend PROPERTIES CXX_STANDARD 11)
set_target_properties(pcsx2_frontend PROPERTIES CXX_STANDARD_REQUIRED ON)