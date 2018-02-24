cmake_minimum_required(VERSION 3.8.2)

project(orbumfront CXX)

set(COMMON_SRC_FILES
	"${CMAKE_SOURCE_DIR}/project/orbumfront/src/OrbumFront.cpp"
)

add_executable(orbumfront "${COMMON_SRC_FILES}")

target_link_libraries(
	orbumfront 
	PUBLIC
		"${CMAKE_THREAD_LIBS_INIT}"
		utilities
		liborbum
)

# TODO: Sort out later into proper build configurations.
# Also disable MSVC non-safe copy warnings.
target_compile_definitions(
	orbumfront 
	PUBLIC 
		"_SCL_SECURE_NO_WARNINGS"
		"BUILD_DEBUG"
)

install(
	TARGETS orbumfront 
	RUNTIME DESTINATION "bin"
)