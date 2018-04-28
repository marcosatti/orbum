# CMake 3.8.2 is needed for C++17 support.
# CMake 3.9 is needed for LTO support.
cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0069 NEW) # Link time optimization support


#######################
# Pre-project options #
#######################
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" cache string "Minimum OS X deployment version")


project(orbum CXX)


###########
# Options #
###########
 
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS on)

set(CMAKE_POSITION_INDEPENDENT_CODE on)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_result)
if(ipo_result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION on)
endif()
        
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")


################
# Dependencies #
################

# Threads
find_package(Threads)

# Boost
add_definitions(-DBOOST_ALL_DYN_LINK)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS log filesystem)


###########
# Project #
###########

add_subdirectory(liborbum)
add_subdirectory(orbumfront)
add_subdirectory(utilities)


#########################
# Visual Studio Options #
#########################

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT orbumfront)
set_property(TARGET orbumfront PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
