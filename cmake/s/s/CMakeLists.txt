cmake_minimum_required(VERSION 3.8)
project(
	s
	VERSION 0.1
	LANGUAGES C 
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-W -Wall -Werror -O2 -fPIC")

set(target_cmake_package ON)
include(${PROJECT_SOURCE_DIR}/cmake/project2.cmake)

add_target(
	name stest
	link s1-static s2-shared
	install executable
	on test
)

target_final()

include(${PROJECT_SOURCE_DIR}/cmake/pack.cmake)


