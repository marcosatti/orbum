cmake_minimum_required(VERSION 3.1)

project(external CXX)

set(BOOST_ROOT "C:/Shared/Dev/Projects/boost_1_66_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS log filesystem)
set(Boost_FOUND ${Boost_FOUND} PARENT_SCOPE)
set(Boost_INCLUDE_DIRS "${Boost_INCLUDE_DIRS}" PARENT_SCOPE)
set(Boost_LIBRARIES "${Boost_LIBRARIES}" PARENT_SCOPE)
