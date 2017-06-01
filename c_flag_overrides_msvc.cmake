if(MSVC)
	# Build with static runtime libraries.
	# See https://cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
	set(CMAKE_C_FLAGS_DEBUG_INIT          "/MTd /Zi /Ob0 /Od  /RTC1")
	set(CMAKE_C_FLAGS_MINSIZEREL_INIT     "/MT  /O1 /Ob1           ")
	set(CMAKE_C_FLAGS_RELEASE_INIT        "/MT  /O2 /Ob2           ")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "/MTd /Zi /O2  /Ob1      ")
endif()