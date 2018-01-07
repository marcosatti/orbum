cmake_minimum_required(VERSION 3.1)

project(external CXX)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

#set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/external/boost")
#set(BOOST_ROOT "C:/Shared/Dev/Projects/boost_1_65_1")
find_package(Boost REQUIRED COMPONENTS log filesystem)

# Allow main projects to use 
set(Boost_FOUND ${Boost_FOUND} PARENT_SCOPE)
set(Boost_INCLUDE_DIRS "${Boost_INCLUDE_DIRS}" PARENT_SCOPE)
set(Boost_LIBRARIES "${Boost_LIBRARIES}" PARENT_SCOPE)