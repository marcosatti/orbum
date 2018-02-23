cmake_minimum_required(VERSION 3.8.2)

project(utilities CXX)

set(COMMON_SRC_FILES
	src/Macros.hpp
	src/TaskExecutor.hpp
	src/Queues.hpp
	src/EnumMap.hpp
)

add_library(utilities INTERFACE)
target_sources(utilities INTERFACE lib1.h)