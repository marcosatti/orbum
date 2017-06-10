cmake_minimum_required(VERSION 3.1)

set(BOOST_DIR "${CMAKE_SOURCE_DIR}/external/boost" CACHE STRING "(External) Boost library location.")
set(Boost_INCLUDE_DIR "${BOOST_DIR}" CACHE INTERNAL "")
set(Boost_LIBRARY_DIR "${BOOST_DIR}/stage/lib" CACHE INTERNAL "")