cmake_minimum_required(VERSION 3.8)
project(
	s
	VERSION 0.1
	LANGUAGES C 
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
# set(CMAKE_C_FLAGS "-W -Wall -Werror -O2 -fPIC")

option(OPT_EXTRA_S2 "message_OPT_EXTRA_S2" ON)


set(target_cmake_package ON)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/project2.cmake)



add_target(
	name ${CMAKE_CURRENT_BINARY_DIR}/works_c_flags.cmake
	check -W -Wall -Werror -O2
	check_append CMAKE_C_FLAGS CMAKE_CXX_FLAGS
)
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

# message(STATUS "e: ${works_c_flags_O2}")
# message(FATAL_ERROR "e: ${works_c_flags}")
add_target(
	name ${CMAKE_BINARY_DIR}/include/cdef_.h
	# set cccname="prefix_suffix" ccc=ccb ccd="a;b;c d"
	check qsort usleep -lm -l [ -lpthread pthread_create ] # [ -luuid uuid_generate  ]
	# on fatal
)

# message(STATUS "${ccc}, ${cccname}, ${ccd}")

#[[ // coding
add_target(
	name curl
	repo # ${CMAKE_SOURCE_DIR}/cJSON-1.7.15.zip 
	# https://github.com/curl/curl/releases/download/curl-7_88_1/curl-7.88.1.tar.gz
  	http://127.0.0.1:8080/curl-7.88.1.tar.gz
	# https://github.com/curl/curl.git
	# curl.dll
)
]]



add_target(
	name stest
	link s1-static s2-shared
	install executable
	on test
)
#[[
add_library(sss SHARED)

set_target_properties(${_target_name} PROPERTIES
	IMPORTED_LOCATION_RELEASE a.exe
)
]]



target_final()

include(${PROJECT_SOURCE_DIR}/cmake/pack.cmake)


