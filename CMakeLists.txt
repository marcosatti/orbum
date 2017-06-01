cmake_minimum_required(VERSION 3.6)

# macOS deployment target. Must be before 'project' to work.
if(APPLE AND NOT TARGET_IOS)
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
endif()

add_subdirectory(external)
project(pcsx2_rewrite)

# Build flags for supported compilers.
if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
	message(FATAL_ERROR "Implement me! (Clang)")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	message(FATAL_ERROR "Implement me! (GNU)")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
	message(FATAL_ERROR "Implement me! (Intel)")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG           "/MTd /Zi /Ob0 /Od /RTC1 /MP")
	set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED "/MTd /Zi /O2 /Ob2 /MP")
	set(CMAKE_CXX_FLAGS_RELEASE         "/MT /O2 /Ob2 /MP")
else()
	message(WARNING "Unknown compiler (assuming GNU): ${CMAKE_CXX_COMPILER_ID}")
	message(FATAL_ERROR "Implement me! (GNU)")
endif()

# Build type preprocessor definitions.
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG}           -DBUILD_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED "${CMAKE_CXX_FLAGS_DEBUG_OPTIMISED} -DBUILD_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE}                      ")

# Build configuration settings.
set(CMAKE_CONFIGURATION_TYPES "Debug;Debug_Optimised;Release")
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug_Optimised" CACHE STRING "Choose the type of build, options are: Debug Debug_Optimised Release" FORCE)
endif()
message("Build type selected: ${CMAKE_BUILD_TYPE}")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message("Build flags: ${CMAKE_CXX_FLAGS_DEBUG}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug_Optimised")
	message("Build flags: ${CMAKE_CXX_FLAGS_DEBUG_OPTIMISED}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	message("Build flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

add_subdirectory(libpcsx2_core)
add_subdirectory(pcsx2_frontend)