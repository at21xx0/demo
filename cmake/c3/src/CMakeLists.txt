

set(_k2_srcs
	${CMAKE_CURRENT_BINARY_DIR}/k2/k2.c
	${CMAKE_CURRENT_BINARY_DIR}/k2/k2.h
)
message(STATUS "src/CMakeLists.txt CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
# 中间体
add_custom_target( # 在目标中执行定制命令
	k2_wrapper
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${_k2_srcs}
	COMMENT "Intermediate k2_wrappers target"
	VERBATIM
)
add_custom_command(
	OUTPUT ${_k2_srcs}
	COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/src/k2.tar.gz
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${PROJECT_SOURCE_DIR}/src/k2.tar.gz
	COMMENT "Unpacking k2.tar.gz wrappers for libk2"
)

add_library(k2 STATIC "")
target_sources(k2 PRIVATE ${_k2_srcs})


# file(GLOB _k3_srcs k3/*.c k3/*.h)
