cmake_minimum_required(VERSION 3.8.2)

#if(APPLE and not TARGET_IOS)
#	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" cache string "Minimum OS X deployment version")
#endif()

project(orbum CXX)


###########
# Options #
###########

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")
set(BUILD_SHARED_LIBS on)
        
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()


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
