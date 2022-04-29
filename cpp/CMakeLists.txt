cmake_minimum_required(VERSION 3.10)
project(
	t
	VERSION 0.1
	LANGUAGES C CXX 
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-W -Wall -Werror -O2 -fPIC")
set(CMAKE_C_FLAGS "-W -Wall -Werror -O2 -fPIC")

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/s/s/cmake/project2.cmake)

target_final()
