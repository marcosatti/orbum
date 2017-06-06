cmake_minimum_required(VERSION 3.1)

# Override default configuration options. Must be before 'project' to work.
set(CMAKE_CONFIGURATION_TYPES "Debug;Debug_Optimised;Release")

# macOS deployment target. Must be before 'project' to work.
if(APPLE AND NOT TARGET_IOS)
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version.")
endif()

# Declare superproject.
project(pcsx2_rewrite CXX)

# Add externals first to override any settings they change.
add_subdirectory(external)

# Build configuration settings.
set(USER_BUILD_TYPE "Debug_Optimised" CACHE STRING "Choose the type of build, options are: Debug Debug_Optimised Release.")
set_property(CACHE USER_BUILD_TYPE PROPERTY STRINGS "Debug;Debug_Optimised;Release")

# Build flags for supported compilers.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	# Clang bug: currently, as of clang++ 3.8, linking does not work due to a compiler bug.
	# Only Clang++ 4.0 and beyond works with the -std=c++1z flag.
	# See this bug report for details: https://bugs.llvm.org/show_bug.cgi?id=33098
	# Please notify us when this is fixed! 
	# Until this happens, the easist way to support different '-std' options in CMake is through here.
	# After this is fixed, look into going to set_target_properties(... CXX_STANDARD 14) or something.
	if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.0)
		message(FATAL_ERROR "Currently only Clang++ 4.0+ works due to a compiler bug. Please see inside the root CMakeLists.txt file for more details.")
	endif()
	# Compiler 
	set(USER_CXX_FLAGS_DEBUG           "-g -std=c++1z"     CACHE STRING "User CXX compiler flags (Debug)."          )
	set(USER_CXX_FLAGS_DEBUG_OPTIMISED "-g -Og -std=c++1z" CACHE STRING "User CXX compiler flags (Debug_Optimised).")
	set(USER_CXX_FLAGS_RELEASE         "-O3 -std=c++1z"    CACHE STRING "User CXX compiler flags (Release)."        )
	# Linker
	set(USER_EXE_LINKER_FLAGS_DEBUG           "" CACHE STRING "User CXX linker flags (Debug)."            )
	set(USER_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "" CACHE STRING "User CXX linker flags (Debug_Optimised)."  )
	set(USER_EXE_LINKER_FLAGS_RELEASE         "" CACHE STRING "User CXX linker flags (Release)."          )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	# Same bug as Clang above.
	if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 8.1.0)
		message(FATAL_ERROR "Currently only AppleClang++ 8.1.0+ works due to a compiler bug. Please see inside the root CMakeLists.txt file for more details.")
	endif()
	# Compiler 
	set(USER_CXX_FLAGS_DEBUG           "-g -std=c++1z"     CACHE STRING "User CXX compiler flags (Debug)."          )
	set(USER_CXX_FLAGS_DEBUG_OPTIMISED "-g -Og -std=c++1z" CACHE STRING "User CXX compiler flags (Debug_Optimised).")
	set(USER_CXX_FLAGS_RELEASE         "-O3 -std=c++1z"    CACHE STRING "User CXX compiler flags (Release)."        )
	# Linker
	set(USER_EXE_LINKER_FLAGS_DEBUG           "" CACHE STRING "User CXX linker flags (Debug)."            )
	set(USER_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "" CACHE STRING "User CXX linker flags (Debug_Optimised)."  )
	set(USER_EXE_LINKER_FLAGS_RELEASE         "" CACHE STRING "User CXX linker flags (Release)."          )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# Compiler 
	set(USER_CXX_FLAGS_DEBUG           "-g -std=c++14"     CACHE STRING "User CXX compiler flags (Debug)."          )
	set(USER_CXX_FLAGS_DEBUG_OPTIMISED "-g -Og -std=c++14" CACHE STRING "User CXX compiler flags (Debug_Optimised).")
	set(USER_CXX_FLAGS_RELEASE         "-O3 -std=c++14"    CACHE STRING "User CXX compiler flags (Release)."        )
	# Linker
	set(USER_EXE_LINKER_FLAGS_DEBUG           "" CACHE STRING "User CXX linker flags (Debug)."            )
	set(USER_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "" CACHE STRING "User CXX linker flags (Debug_Optimised)."  )
	set(USER_EXE_LINKER_FLAGS_RELEASE         "" CACHE STRING "User CXX linker flags (Release)."          )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	message(FATAL_ERROR "Implement me! (Intel)")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# Compiler 
	set(USER_CXX_FLAGS_DEBUG           "/MTd /Zi /RTC1 /MP /std=c++14 /D_SCL_SECURE_NO_WARNINGS" CACHE STRING "User CXX compiler flags (Debug)."          )
	set(USER_CXX_FLAGS_DEBUG_OPTIMISED "/MTd /Zi /O2 /MP /std=c++14 /D_SCL_SECURE_NO_WARNINGS"   CACHE STRING "User CXX compiler flags (Debug_Optimised).")
	set(USER_CXX_FLAGS_RELEASE         "/MT /O2 /MP /std=c++14 /D_SCL_SECURE_NO_WARNINGS"        CACHE STRING "User CXX compiler flags (Release)."        )
	# Linker
	set(USER_EXE_LINKER_FLAGS_DEBUG           "/DEBUG" CACHE STRING "User CXX linker flags (Debug)."          )
	set(USER_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "/DEBUG" CACHE STRING "User CXX linker flags (Debug_Optimised).")
	set(USER_EXE_LINKER_FLAGS_RELEASE         ""       CACHE STRING "User CXX linker flags (Release)."        )
else()
	message(FATAL_ERROR "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}, stopping.")
endif()

# Apply build settings.
set(CMAKE_BUILD_TYPE                       "${USER_BUILD_TYPE}"                       CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG                  "${USER_CXX_FLAGS_DEBUG}"                  CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG_OPTIMISED        "${USER_CXX_FLAGS_DEBUG_OPTIMISED}"        CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE                "${USER_CXX_FLAGS_RELEASE}"                CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG           "${USER_EXE_LINKER_FLAGS_DEBUG}"           CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG_OPTIMISED "${USER_EXE_LINKER_FLAGS_DEBUG_OPTIMISED}" CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE         "${USER_EXE_LINKER_FLAGS_RELEASE}"         CACHE INTERNAL "")

# Preprocessor defines.
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_definitions(-DBUILD_DEBUG)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug_Optimised")
	add_definitions(-DBUILD_DEBUG)
endif()

# Set install path.
set(USER_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "Install path.")
set(CMAKE_INSTALL_PREFIX "${USER_INSTALL_PREFIX}" CACHE INTERNAL "")

# Add projects.
add_subdirectory(project)

# Visual studio startup project.
if (NOT (${CMAKE_VERSION} VERSION_LESS 3.6))
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT pcsx2_frontend)
endif()