cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0069 NEW) # Link time optimization support

project(utilities CXX)

set(COMMON_SRC_FILES
	"${CMAKE_SOURCE_DIR}/utilities/src/Macros.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/TaskExecutor.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/Queues.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/EnumMap.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/Caches.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/Console.hpp"
	"${CMAKE_SOURCE_DIR}/utilities/src/Console.cpp"
)

add_library(utilities STATIC "${COMMON_SRC_FILES}")

target_sources(
	utilities
	PUBLIC 
		"${COMMON_SRC_FILES}"
)

target_include_directories(
	utilities 
	PUBLIC
		"${Boost_INCLUDE_DIR}"
		"${CMAKE_SOURCE_DIR}/utilities/src"
)
