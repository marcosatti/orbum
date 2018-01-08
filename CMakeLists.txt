cmake_minimum_required(VERSION 3.1)

#if(APPLE and not TARGET_IOS)
#	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" cache string "Minimum OS X deployment version")
#endif()

project(orbum CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

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

add_subdirectory(external)
add_subdirectory(project)