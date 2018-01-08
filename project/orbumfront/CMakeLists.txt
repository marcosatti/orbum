cmake_minimum_required(VERSION 3.8.2)

project(orbumfront CXX)

include_directories(
	${CMAKE_SOURCE_DIR}/project/orbumfront/src 
	${CMAKE_SOURCE_DIR}/project/liborbum/src 
)

set(COMMON_SRC_FILES
	src/OrbumFront.cpp
)

add_executable(orbumfront ${COMMON_SRC_FILES})

target_link_libraries(
	orbumfront PUBLIC
	${CMAKE_THREAD_LIBS_INIT}
	liborbum
)

# TODO: Sort out later into proper build configurations.
# Also disable MSVC non-safe copy warnings.
target_compile_definitions(
	orbumfront PUBLIC 
	"_SCL_SECURE_NO_WARNINGS"
	"BUILD_DEBUG"
)

target_include_directories(
	orbumfront PUBLIC
	"${CMAKE_SOURCE_DIR}/project/liborbum/src"
	"${CMAKE_SOURCE_DIR}/project/utilities/src"
)

install(
	TARGETS orbumfront 
	RUNTIME DESTINATION "bin"
)