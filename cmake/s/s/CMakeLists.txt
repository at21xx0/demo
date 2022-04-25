cmake_minimum_required(VERSION 3.8)
project(
	s
	VERSION 0.1
	LANGUAGES C 
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-W -Wall -Werror -O2")
include(${PROJECT_SOURCE_DIR}/cmake/project2.cmake)
add_target(
	name stest
	link s1-static s2-shared
	install executable
)
target_final()

add_custom_target(
	stest-link
	ALL
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	DEPENDS ${PROJECT_BINARY_DIR}/stest
	COMMENT "link-target"
	VERBATIM
)
add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/stest
	COMMAND ${CMAKE_COMMAND} -E create_symlink bin/stest stest
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	DEPENDS $<TARGET_FILE:stest>
	COMMENT "create_symlink: stest"
)

include(${PROJECT_SOURCE_DIR}/cmake/pack.cmake)

enable_testing()
add_test(
	NAME dlt_test
	COMMAND $<TARGET_FILE:dlt>
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

