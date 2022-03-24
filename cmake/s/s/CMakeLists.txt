cmake_minimum_required(VERSION 3.10)
project(
	s
	VERSION 0.1
	LANGUAGES C 
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
include(${PROJECT_SOURCE_DIR}/cmake/project2.cmake)
set(CMAKE_C_FLAGS "-W -Wall")
add_target(name s1 on static)
add_target(name s2e on object)
add_target(
	name s2
	link s2e-object # 改成static需要安装
	install static shared
	on export
	public_header "${PROJECT_SOURCE_DIR}/src/include/s2.h;${PROJECT_BINARY_DIR}/include/s2Export.h"
)
add_target(name stest link s1-static s2-shared install executable)
if(UNIX)
	set(_dl "dl") # libdl.so
elseif(WIN32)
	# win32 平台代码没有写
endif()
add_target(name dlt link ${_dl} on executable)
#[[
# public 中安装了
add_target(
	files
		${PROJECT_SOURCE_DIR}/src/include/s2.h
		${PROJECT_BINARY_DIR}/include/s2Export.h
)
]]
target_install()
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
	NAME dlt
	COMMAND $<TARGET_FILE:dlt>
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

