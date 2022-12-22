cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(EagleCore VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_directory_property(ParentDirectory PARENT_DIRECTORY)

set(EAGLE_HEADERS
	include/EagleCore/Environment.hh
	include/EagleCore/ProcessTermination.hh
	)

set(EAGLE_SOURCES
	src/ProcessTermination.cc
	src/ProcessTerminationImpl.hh
	)

if(UNIX)
	list(APPEND
		EAGLE_SOURCES
		src/Unix/ProcessTerminationImplUnix.cc
		src/Unix/EnvironmentUnix.cc
		)
elseif(WIN32)
    list(APPEND
        EAGLE_SOURCES
        src/Win32/EnvironmentWin32.cc
        src/Win32/ProcessTerminationImplWin32.cc
        )
endif()

add_library(
	${PROJECT_NAME}
	STATIC
	${EAGLE_SOURCES}
	${EAGLE_HEADERS}
)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)
