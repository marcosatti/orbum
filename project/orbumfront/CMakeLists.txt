cmake_minimum_required(VERSION 3.1)

project(orbumfront CXX)

find_package(Threads)

include_directories(
	${CMAKE_SOURCE_DIR}/project/orbumfront/src 
	${CMAKE_SOURCE_DIR}/project/liborbum/src 
)

set(PROJECT_LIBS
	liborbum
)

set(COMMON_SRC_FILES
	src/OrbumFront.cpp
)

add_executable(orbumfront ${COMMON_SRC_FILES})

target_link_libraries(orbumfront ${CMAKE_THREAD_LIBS_INIT})