cmake_minimum_required(VERSION 3.8.2)

project(utilities CXX)

set(COMMON_SRC_FILES
	"${CMAKE_SOURCE_DIR}/utilities/src/Macros.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/TaskExecutor.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/Queues.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/EnumMap.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/Caches.hpp"
)

add_library(utilities INTERFACE)

target_sources(
	utilities
	INTERFACE 
		"${COMMON_SRC_FILES}"
)

target_include_directories(
	utilities 
	INTERFACE
		"${Boost_INCLUDE_DIR}"
		"${CMAKE_SOURCE_DIR}/utilities/src"
)
