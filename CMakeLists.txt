cmake_minimum_required(VERSION 3.1)

#if(APPLE and not TARGET_IOS)
#	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" cache string "Minimum OS X deployment version.")
#endif()

project(orbum CXX)

set(BUILD_SHARED_LIBS on)

add_subdirectory(external)
add_subdirectory(project)

if(MSVC)
    add_compile_options("/MP")
endif()