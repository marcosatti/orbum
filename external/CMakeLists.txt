cmake_minimum_required(VERSION 3.1)
project(external CXX)

# Boost
set(BOOST_ROOT               "${CMAKE_SOURCE_DIR}/external/boost" CACHE STRING   "(External) Boost library root dir."                        )
set(BOOST_LIBRARYDIR         "${BOOST_ROOT}/stage/lib"            CACHE INTERNAL "(External) Boost compiled libraries dir."                  ) 
set(BOOST_INCLUDEDIR         "${BOOST_ROOT}"                      CACHE INTERNAL "(External) Boost include dir."                             )
set(Boost_USE_MULTITHREADED  ON                                   CACHE BOOL     "(External) Use Boost multithreaded libs."                  )
set(Boost_USE_STATIC_LIBS    ON                                   CACHE BOOL     "(External) Use Boost static libs."                         )
set(Boost_USE_STATIC_RUNTIME ON                                   CACHE BOOL     "(External) Use Boost static runtime linked libs."          )
set(Boost_USE_DEBUG_RUNTIME  ON                                   CACHE BOOL     "(External) Use Boost debug runtime linked (for MSVC) libs.")
