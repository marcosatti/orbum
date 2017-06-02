cmake_minimum_required(VERSION 3.1)

# Override default configuration options. Must be before 'project' to work.
set(CMAKE_CONFIGURATION_TYPES "Debug;Debug_Optimised;Release")

# Build configuration settings. Must be before 'project' to work.
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug_Optimised" CACHE STRING "Choose the type of build, options are: Debug Debug_Optimised Release.")
endif()

# macOS deployment target. Must be before 'project' to work.
if(APPLE AND NOT TARGET_IOS)
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version.")
endif()

# Add externals first to override any settings they change.
add_subdirectory(external)

# Add superproject.
project(pcsx2_rewrite CXX)

# Build flags for supported compilers.
if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
	# Compiler 
	set(CMAKE_CXX_FLAGS_DEBUG           "-g    ")
	set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED "-g -O3")
	set(CMAKE_CXX_FLAGS_RELEASE         "      ")
	# Linker
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG           "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE         "${CMAKE_EXE_LINKER_FLAGS}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	# Compiler 
	set(CMAKE_CXX_FLAGS_DEBUG           "-g    ")
	set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED "-g -O3")
	set(CMAKE_CXX_FLAGS_RELEASE         "      ")
	# Linker
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG           "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE         "${CMAKE_EXE_LINKER_FLAGS}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
	message(FATAL_ERROR "Implement me! (Intel)")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	# Compiler 
	set(CMAKE_CXX_FLAGS_DEBUG           "/MTd /Zi /Ob0 /Od /RTC1 /MP")
	set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED "/MTd /Zi /O2 /Ob2 /MP")
	set(CMAKE_CXX_FLAGS_RELEASE         "/MT /O2 /Ob2 /MP")
	# Linker
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG           "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE         "${CMAKE_EXE_LINKER_FLAGS}       ")
else()
	message(WARNING "Unknown compiler (assuming GNU): ${CMAKE_CXX_COMPILER_ID}")
	# Compiler 
	set(CMAKE_CXX_FLAGS_DEBUG           "-g    ")
	set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED "-g -O3")
	set(CMAKE_CXX_FLAGS_RELEASE         "      ")
	# Linker
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG           "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE         "${CMAKE_EXE_LINKER_FLAGS}")
endif()

# Additional build settings (common to all compilers).
set(CMAKE_CXX_FLAGS_DEBUG                  "${CMAKE_CXX_FLAGS_DEBUG}                  -DBUILD_DEBUG" CACHE STRING "Compiler flags for Debug build configuration."          )
set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED        "${CMAKE_CXX_FLAGS_DEBUG_OPTIMISED}        -DBUILD_DEBUG" CACHE STRING "Compiler flags for Debug_Optimised build configuration.")
set(CMAKE_CXX_FLAGS_RELEASE                "${CMAKE_CXX_FLAGS_RELEASE}                             " CACHE STRING "Compiler flags for Release build configuration."        )
set(CMAKE_EXE_LINKER_FLAGS_DEBUG           "${CMAKE_EXE_LINKER_FLAGS_DEBUG}                        " CACHE STRING "Linker flags for Debug build configuration."            )
set(CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "${CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED}              " CACHE STRING "Linker flags for Debug_Optimised build configuration."  )
set(CMAKE_EXE_LINKER_FLAGS_RELEASE         "${CMAKE_EXE_LINKER_FLAGS_RELEASE}                      " CACHE STRING "Linker flags for Release build configuration."          )

# Set install path (method used to work around gtest overriding).
set(INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE PATH "Install path.")
set(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX} CACHE INTERNAL "")

# Log build information.
message("Build configuration selected: ${CMAKE_BUILD_TYPE}, using compiler ${CMAKE_CXX_COMPILER_ID}.")
message("Install path: ${CMAKE_INSTALL_PREFIX}")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message("Compiler flags: ${CMAKE_CXX_FLAGS_DEBUG}")
	message("Linker flags: ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug_Optimised")
	message("Compiler flags: ${CMAKE_CXX_FLAGS_DEBUG_OPTIMISED}")
	message("Linker flags: ${CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	message("Compiler flags: ${CMAKE_CXX_FLAGS_RELEASE}")
	message("Linker flags: ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
endif()

# Add projects.
add_subdirectory(project)

# Visual studio startup project.
if (NOT (${CMAKE_VERSION} VERSION_LESS 3.6))
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT pcsx2_frontend)
endif()