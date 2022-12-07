cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(EagleCore VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_directory_property(ParentDirectory PARENT_DIRECTORY)

set(EAGLE_HEADERS
	include/EagleCore/Environment.hh
	)

set(EAGLE_SOURCES)

if(UNIX)
	list(APPEND
		EAGLE_SOURCES
		src/Unix/EnvironmentUnix.cc
		)
endif()

add_library(
	${PROJECT_NAME}
	STATIC
	${EAGLE_SOURCES}
	${EAGLE_HEADERS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)
