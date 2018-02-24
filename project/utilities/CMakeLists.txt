cmake_minimum_required(VERSION 3.8.2)

project(utilities CXX)

set(COMMON_SRC_FILES
	"${CMAKE_SOURCE_DIR}/project/utilities/src/Macros.hpp"
	"${CMAKE_SOURCE_DIR}/project/utilities/src/TaskExecutor.hpp"
	"${CMAKE_SOURCE_DIR}/project/utilities/src/Queues.hpp"
	"${CMAKE_SOURCE_DIR}/project/utilities/src/EnumMap.hpp"
)

add_library(utilities STATIC ${COMMON_SRC_FILES})

# Allow Visual Studio to recognise this as a project.
set_target_properties(
	utilities
	PROPERTIES 
		LINKER_LANGUAGE CXX
)

target_include_directories(
	utilities 
	PUBLIC
		"${CMAKE_SOURCE_DIR}/project/utilities/src"
)