cmake_minimum_required(VERSION 3.1)

project(orbumfront CXX)

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
target_link_libraries(orbumfront PUBLIC "${PROJECT_LIBS}")

# Disable MSVC non-safe copy warnings.
target_compile_definitions(orbumfront PUBLIC "_SCL_SECURE_NO_WARNINGS")

# Sort out later into proper build configurations.
target_compile_definitions(orbumfront PUBLIC "BUILD_DEBUG")

target_include_directories(orbumfront PUBLIC "${CMAKE_SOURCE_DIR}/project/liborbum/src")
target_include_directories(orbumfront PUBLIC "${CMAKE_SOURCE_DIR}/project/utilities/src")

install(TARGETS orbumfront RUNTIME DESTINATION ".")