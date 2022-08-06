cmake_minimum_required(VERSION 3.10)
project(
	dev
	VERSION 0.1
	LANGUAGES C CXX
)

set(CMAKE_C_FLAGS "-W -Wall -Werror -O2")
set(CMAKE_CXX_FLAGS "-W -Wall -Werror -O2")

include(${PROJECT_SOURCE_DIR}/../cmake/s/s/cmake/project2.cmake)

target_final()


