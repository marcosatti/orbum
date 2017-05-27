cmake_minimum_required(VERSION 2.8)

# macOS deployment target needs to be set before 'project' to work
if(APPLE AND NOT TARGET_IOS)
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
endif()

project(PCSX2_Core)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
else()
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP")
endif()

if(ANDROID)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release"
		FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

if (NOT TARGET PCSX2_Core)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../PCSX2_Core
		${CMAKE_CURRENT_BINARY_DIR}/PCSX2_Core
	)
endif()
list(APPEND PROJECT_LIBS PCSX2_Core)

find_package(Threads REQUIRED)
if(CMAKE_THREAD_LIBS_INIT)
	list(APPEND PROJECT_LIBS "${CMAKE_THREAD_LIBS_INIT}")
endif()

add_definitions(-D_CONSOLE)

include_directories(../PCSX2_Core/src ./src)

set(COMMON_HEADER_FILES
)

set(COMMON_SRC_FILES
	src/PCSX2_Frontend.cpp
)

add_executable(PCSX2_Frontend ${COMMON_HEADER_FILES} ${COMMON_SRC_FILES})
target_link_libraries(PCSX2_Frontend ${PROJECT_LIBS})

if(THREADS_HAVE_PTHREAD_ARG)
		target_compile_options(PUBLIC PCSX2_Frontend "-pthread")
endif()
