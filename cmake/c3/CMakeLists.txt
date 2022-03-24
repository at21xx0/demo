cmake_minimum_required(VERSION 3.8 FATAL_ERROR) # 最小版本，小于报错

project(
	demo # 项目名称
	VERSION 1.0 # 可选 项目版本
	#LANGUAGES C CXX # 可选 项目语言
)

option(test_python_ "USE_PYTHON" ON)
option(test_more_ "test sqrt" OFF)

# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # 要求在windows上导出所有库符号

# C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# 根据GNU标准定义binary和library路径
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 编译完成时文件所在位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})


add_library(k1-static
	STATIC # [STATIC|SHARED|MOUDLE] 库类型，默认STATIC
	k1.c
	k1e.c
	# k1.h # 文件
	# EXCLUDE_FROM_ALL # 默认不会被编译
)

# STATIC 静态库 SHARED 动态库 OBJECT 一次性编译到目标文件，不生成动态库和静态库 MOUDLE 又为DSO组，不被链接，可做构建时的插件
# set(BUILD_SHARED_LIBS ON) # 默认SHARED	

target_include_directories(k1-static
	PUBLIC ${PROJECT_BINARY_DIR} # 编译目录（Makefile 目录）
	PUBLIC ${PROJECT_SOURCE_DIR} # 此CMake目录
	PUBLIC ${PROJECT_BINARY_DIR}/${INSTALL_INCLUDEDIR}
	# 可见性 PRIVATE INYERFACE PUBLIC
	# PRIVATE 私有，仅目标可见
	# INTERFACE 目标不可见，其他可见
	# PUBLIC 都可见
)

set_target_properties(k1-static
	PROPERTIES
		CXX_STANDARD 14 # 设置 CXX 标准
		CXX_STANDARD_REQUIRED ON # 需要
		CXX_EXTENSIONS OFF # CXX_EXTENSIONS 只启用 ISO C++ 标准的编译标志，而不实用特定编译器的扩展
		POSITION_INDEPENDENT_CODE 1 # 设置生成位置无关代码所需的编译器标志 # 防止一些编译器DSO 出现问题
		OUTPUT_NAME "k1" # 输出名称，如libk1.so
)


	

# this is only needed for older compilers
# but doesn't hurt either to have it
#add_library(k1-object OBJECT k1.c)


add_library(k1-shared
	SHARED
		$<TARGET_OBJECTS:k1-static> # 源文件与k1-static 相同
)
set_target_properties(k1-shared
	PROPERTIES
		OUTPUT_NAME "k1"
		POSITION_INDEPENDENT_CODE 1
)


# 设置默认编译器
# cmake -D CMAKE_CXX_COMPILER=clang++ （推荐）
# env CXX=clang++ cmake ..
# 如果必要，需要传递完整路径

# 查看 CMAKE_CXX_COMPILER 默认值
# cmake --system-information information.txt 

# CMAKE_<LANG>_COMPILER_LOADED <LANG>
# CMAKE_<LANG>_COMPILER_ID 编译器识别字符串
# CMAKE_COMPILER_IS_GNU<LANG>
# CMAKE_<LANG>_COMPIILER_VERSION
message(STATUS "CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")


# set(USE_LIBRARY ON) # 为USE_LIBRARY 赋值
# 真假多种表示 1 0 ON OFF YES NO ture false Y N 非零数 IGNORE NOTFOUND 空字符串 -NOTFOIHND

# message(STATUS "USE_LIBRARY: ${USE_LIBRARY}")

# 定义变量，显示提示信息，设置默认值[ON|OFF]
option(USE_LIBRARY "USE_LIBRARY 提示性信息" ON)
message(STATUS "cmake -DUSR_LIBRARY=${USE_LIBRARY}")

if(USE_LIBRARY)
	add_executable(d d.c)
	target_link_libraries(d k1-shared)
else()
	# 引入一个变量，_表示局部变量
	list(APPEND _sources $<TARGET_OBJECTS:k1-static> d.c)

	add_executable(d ${_sources})
endif()

include(CMakeDependentOption) # 使cmake_dependent_option() 可用

cmake_dependent_option( # 设置依赖，根据USE_LIBRARY设置USE_SHARED_LIBRARY的值
	USE_SHARED_LIBRARY "USE_SHARED_LIBRARY" ON
	USE_LIBRARY ON
)

message(STATUS "C++ compiler flags: ${CMAKE_CXX_FLAGS}")
list(APPEND flags "-fPIC" "-Wall")
if(NOT WIN32)
	# list(APPEND flags "-Wextra -Wpedantic") # 非Windows中
endif()
target_compile_options(d # 设置编译器参数
	PRIVATE ${flags}
	PRIVATE $<$<CONFIG:Debug>:${CMAKE_FLAGS_DEBUG}>
)
if(CMAKE_C_COMPILER_ID MATCHES GNU)
	list(APPEND CMAKE_CXX_FLAGS "-O2") # 优化级别 -O2
elseif(CMAKE_C_COMPILER_ID MATCHES Clang)
	list(APPEND CMAKE_CXX-FLAGS "-O2")
endif()
# 可设置 CMAKE_FLAGS CMAKE_FLAGS_DEBUG

target_compile_options(k1-static PRIVATE -O3)
# 较低的优化
list(APPEND sources_with_lower_optimization k1.c)
# 循环源文件，优化级别调到 -O2
foreach(_source IN LISTS sources_with_lower_optimization)
	set_source_files_properties(${_source}
		# 将属性设置为给定文件的传递值
		PROPERTIES
			COMPILE_FLAGS -O2
	)
	get_source_file_property(_flag ${_source} COMPILE_FLAGS) # 检索文件指定属性的值，存储在 _flag 中
	message(STATUS "Source ${_source} has the following extra COMPILE_FLAGS: ${_flag}")
endforeach()
# foreach(loop_var argq arg2 ...)
# foreach(loop_var range total) foreach(loop_var range start stop [step])
# foreach(loop_var IN LISTS [list1[...]])
# foreach(loop_var IN ITEMS [item1 [...]])

# 检测环境
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(STATUS "Configuring on/for Linux")
	target_compile_definitions(k1-static PUBLIC "IS_LINUX") # 定义宏
	add_definitions(-DIS_LINUX) # 在整个项目定义
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	message(STATUS "Configuring on/for macOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Configuring on/for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
	message(STATUS "Configuring on/for IBM AIX")
else()
	message(STATUS "Configuring on/for ${CMAKE_SYSTEM_NAME}")
endif()

add_executable(config config.c)
target_link_libraries(config k1-static)

target_compile_definitions(config PUBLIC "COMPILER_NAME=\"${CMAKE_CXX_COMPILER_ID}\"")
if(CMAKE_CXX_COMPILER_ID MATCHES Intel)
	target_compile_definitions(config PUBLIC "IS_INTEL_CXX_COMPILER")
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
	target_compile_definitions(config PUBLIC "IS_GNU_CXX_COMPILER")
elseif(CMAKE_CXX_COMPILER_ID MATCHES PGI)
	target_compile_definitions(config PUBLIC "IS_PGI_CXX_COMPILER")
elseif(CMAKE_CXX_COMPILER_ID MATCHES XL)
	target_compile_definitions(config PUBLIC "IS_XL_CXX_COMPILER")
endif()
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	# target_compile_definitions(d PUBLIC "IS_64_BIT_ARCH")
	message(STATUS "Target is 64 bits")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	message(STATUS "Target is 32 bits")
endif()
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i386")
	message(STATUS "i386 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i686")
	message(STATUS "i686 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
	message(STATUS "x86_64 architecture detected")
endif()
target_compile_definitions(d PUBLIC "ARCHITECTURE=${CMAKE_HOST_SYSTEM_PROCESSOR}")

target_include_directories(d PUBLIC ${PROJECT_BINARY_DIR} PUBLIC ${PROJECT_SOURCE_DIR} PUBLIC ${PROJECT_BINARY_DIR}/${INSTALL_INCLUDEDIR})
foreach(key IN ITEMS NUMBER_OF_LOGICAL_CORES NUMBER_OF_PHYSICAL_CORES TOTAL_VIRTUAL_MEMORY AVAILABLE_VIRTUAL_MEMORY TOTAL_PHYSICAL_MEMORY AVAILABLE_PHYSICAL_MEMORY IS_64BIT HAS_FPU HAS_MMX HAS_MMX_PLUS HAS_SSE HAS_SSE2 HAS_SSE_FP HAS_SSE_MMX HAS_AMD_3DNOW HAS_AMD_3DNOW_PLUS HAS_IA64 OS_NAME OS_RELEASE OS_VERSION OS_PLATFORM HOSTNAME) # FQDN PROCESSOR_NAME PROCESSOR_DESCRIPTION
	cmake_host_system_information(RESULT _${key} QUERY ${key})
	# message(STATUS "${key}: ${_${key}}")
endforeach()

include(CheckCXXCompilerFlag)
# 检查 -march=native 编译器标志是否工作
# 最好写在上面
check_cxx_compiler_flag("-march=native" _march_native_works) # 检查标志是否可用，可用时_march_native_works 为真
check_cxx_compiler_flag("-xHost" _xhost_works)
set(_CXX_FLAGS_)
if(_march_native_works)
	set(_CXX_FLAGS_ "-march=native")
elseif(_xhost_works)
	set(_CXX_FLAGS_ "-xHost")
endif()


if(test_python_)
	find_package(PythonInterp
	REQUIRED
	# 3.5
) # 找到Python解释器

	execute_process( # 执行程序
		COMMAND ${PYTHON_EXECUTABLE} "-c" "print('test')" # 命令
		RESULT_VARIABLE _status # 得到进程运行的结果。这要么是一个整数，表示执行成功，要么是一个带有错误条件的字符串。
		OUTPUT_VARIABLE _test # 标准输出
		# ERROR_VARIABLE # 标准错误
		ERROR_QUIET # 忽略标准错误
		# OUTPUT_QUIET # 忽略标准输出
		OUTPUT_STRIP_TRAILING_WHITESPACE # 删除运行命令的标准输出中的任何尾随空格
		# INPUT_FILE # 指定标准输入重定向的文件名
		# OUTPUT_FILE # 指定标准输出重定向的文件名
		# ERROR_FILE # 指定标准错误输出重定向的文件名
		# ERROR_STRIP_TRAILING_WHITESPACE # 可以删除运行命令的错误输出中的任何尾随空格。
	)
	message(STATUS "RESULT_BARIABLE is: ${_status}")
	message(STATUS "OUTPUT_VARIABLE is: ${_test}")
	# FindPythonInterp.cmake 附带cmake变量
	# PYTHONINTERP_FOUND 是否找到解释器
	# PYTHON_EXECUTABLE Python解释器到可执行文件的路径
	# PYTHON_VERSION_STRING Python解释器的完整版本信息
	# PYTHON_VERSION_MAJOR Python解释器的主要版本号
	# PYTHON_VERSION_MINOR Python解释器的次要版本号
	# PYTHON_VERSION_PATCH Python解释器的补丁版本号
	# 使用 cmake -D PYTHON_EXECUTABLE=/custom/location/python ..

	include(CMakePrintHelpers)
	cmake_print_variables(_status _test) # 便捷的打印 _status _test 两个变量
	find_package(PythonLibs
	${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} # 版本号
	EXACT # 限制CMake检测特定版本
	REQUIRED
	) # 找到Python头文件和库的模块，称谓 FindPythonLibs.cmake

	# find_package(Python COMPONENTS Interpreter Development REQUIRED)
	# cmake -D 可传入 PYTHON_INCLUDE_DIR PYTHON_LIBRARY

	execute_process(
		# 检查 Python requests 库版本
		COMMAND ${PYTHON_EXECUTABLE} "-c" "import requests; print(requests.__version__)"
		RESULT_VARIABLE _r_status
		OUTPUT_VARIABLE _r_version
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	if(NOT _r_status)
		set(REQUESTS_VERSION ${_r_version} STRING "Location of requests")
	endif()
	execute_process(
		COMMAND ${PYTHON_EXECUTABLE} "-c" "import re, requests" "print(re.compile('/__init.py.*').sub('',requests.__file__))"
		RESULT_VARIABLE _r_status
		OUTPUT_VARIABLE _r_location
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	include(FindPackageHandleStandardArgs)
	# 最后， FindPackageHandleStandardArgs 的CMake包以正确的格式设置 NumPy_FOUND 变量和输出信息
	find_package_handle_standard_args(requests
		FOUND_VAR REQUESTS_FOUND
		REQUIRED_VARS REQUESTS_VERSION
		VERSION_VAR _r_version
	)

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/use_numpy.py ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/use_numpy.py
	)
	# target_sources(pure-embedding PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py)

endif()
if(test_opm_)
	find_package(OpenMp REQUIRED)
	add_executable(opm_test opm_test.cpp)
	target_link_libraries(opm_test PUBLIC OpenMP::OpenMP_CXX)
	# ./opm_test 1000000000
endif()


find_package(PkgConfig REQUIRED QUIET)
# pkg_search_module(ZeroMQ REQUIRED IMPORT_TARGET libzeromq libzmq lib0mq)
# if(TARGET PkgConfig::ZeroMQ)
	# message(STATUS "Found ZeroMQ")
# endif()
# target_link_libraries(d PkgConfig::ZeroMQ)

pkg_search_module(UUID REQUIRED uuid IMPORTED_TARGET)
if(TARGET PkgConfig::UUID)
	message(STATUS "Found libuuid")
endif()
target_link_libraries(config ${UUID_LIBRARIES})
target_include_directories(config PRIVATE ${UUID_INCLUDE_DIRS})

# pkg_check_module(ffmpeg
	# REQUIRED
	# IMPORTED_TARGET libavcodec libavformat libavutil
# )
# target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::ffmpeg)






#	find
# find_file 在响应路径下查找命名文件 查找文件完整路径
# find_file ( <VAR> name | NAMES name1 [name2 ...] [HINTS [path | ENV var]... ] [PATHS [path | ENV var]... ] [PATH_SUFFIXES suffix1 [suffix2 ...]] [DOC "cache documentation string"] [NO_CACHE] [REQUIRED] [NO_DEFAULT_PATH] [NO_PACKAGE_ROOT_PATH] [NO_CMAKE_PATH] [NO_CMAKE_ENVIRONMENT_PATH] [NO_SYSTEM_ENVIRONMENT_PATH] [NO_CMAKE_SYSTEM_PATH] [CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH] )
find_file(
	k3_source # 变量名
	NAMES k3.h k3.hpp # 可能的文件名，支持多个
	PATHS ${PROJECT_SOURCE_DIR}/src/k3 # 寻找文件的路径
	# HINTS,PATHS 指定除默认路径外搜索路径
	# PATH_SUFFIIXES # 检查子目录
)
message(STATUS "k3_source: ${k3_source}")
# find_library 查找一个库文件
# find_package 从外部项目查找和加载设置
# find_path 查找包含指定文件的目录
# find_program 查找一个可执行程序

# find_program(CMAKE_1 NAMES cmake REQUIRED)
# message(STATUS "CMAKE_1: ${CMAKE_1}")

add_executable(demo_test ${PROJECT_SOURCE_DIR}/tests/demo_test.c)
target_link_libraries(demo_test k1-static)
target_include_directories(demo_test
	PUBLIC ${PROJECT_BINARY_DIR}
	PUBLIC ${PROJECT_SOURCE_DIR}
)

add_subdirectory(src) # 加载 src 文件夹下的CMakeLists.txt
add_subdirectory(tests)


# 测试
enable_testing()

add_test(
	NAME demo_test
	COMMAND $<TARGET_FILE:demo_test> test
	LABELS "quick" # 指定时间，quick long
)
add_test(
	NAME t2
	COMMAND $<TARGET_FILE:test2>
	LABELS "quick"
)
set_tests_properties(
	demo_test
	t2
	PROPERTIES
		FIXTURES_REQUIRED test_fixture
)

# catch2
# Google test

add_custom_target(
	src_pack
	ALL # 被添加到ALL目标中
	COMMAND ${CMAKE_COMMAND} -E tar czf ${PROJECT_BINARY_DIR}/src.tgz src
	# COMMAND ${CMAKE_COMMAND} -E rename src.tgz src.tar.gz
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} # 指定应该在哪个目录中执行命令。
	DEPENDS ${PROJECT_SOURCE_DIR}/src # 依赖
	COMMENT "Racking src.tgz"
)

add_custom_command(
	# add_custom_command 向目标添加规则，并通过执行命令输出
	OUTPUT ${PROJECT_BINARY_DIR}/d.tar.gz
	COMMAND ${CMAKE_COMMAND} -E tar czf d.tar.gz d
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	DEPENDS ${PROJECT_BINARY_DIR}/d
	COMMENT "Packing d"
	VERBATIM # 告诉CMake为生成器和平台生成正确的命令，从而确保完全独立。
)

# target_include_categories
# add_dependencies(target-name depend-target1 depend-target2 ...) # 定义target之间的依赖

add_custom_command(
	TARGET d
	PRE_BUILD COMMAND ${CMAKE_COMMAND} -E echo "d_PRE_BUILD" # PRE_BUILD 执行与目标相关的任何命令之前
	PRE_LINK COMMAND ${CMAKE_COMMAND} -E echo "d_PREV_LINK" # PRE_LINK 编译后，链接前
	POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo "d_POST_BUILD" # POST_BUILD 所有完成后
	COMMENT "%"
	VERBATIM
)

set(_scratch_dir ${CMAKE_CURRENT_BINARY_DIR}/try_compile) # 临时目录
try_compile(
	try_compile_1 # 名称
	${_scratch_dir}
	SOURCES ${PROJECT_SOURCE_DIR}/tests/try.c
	LINK_LIBRARIES k1-static
	INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}
)
message(STATUS "Result of try_compile: ${try_compile_1}")

include(CheckCXXSourceCompiles)
if(test_opm_)
	# 尝试编译
	file(READ ${CMAKE_CURRENT_SOURCE_DIR}/tests/taskloop.cpp _snippet)
set(CMAKE_REQUIRED_LIBRARIES OpenMP:OpenMP_CXX)
	# 可设置
	# CMAKE_REQUIRED_FLAGS 编译器标志
	# CMAKE_REQUIRED_DEFINITIONS 预编译宏
	# CMAKE_REQUIRED_INCLUDES 包含目录
	# CMAKE_REQUIRED_LIBRARIES 可执行目录能够链接的库列表
	check_cxx_source_compiles(
		"${_snippet}" # 尝试编译的代码
		omp_taskloop_test_2 # 结果
	)
	unset(CMAKE_REQUIRED_LIBRARIES)
	message(STATUS "Result of check_cxx_source_compiles: ${omp_taskloop_test_2}")
	# try_compile 和 check_cxx_source_compiles 都编译可执行文件，如果成功，前者输出变量，后者设置为TURE
endif()

# 检查 flag 正常
set(ASAN_FLAGS "-fsanitize=adress -fno-omit-frame-pointer") # 要检查的flag
set(CMAKE_REQUIRED_FLAGS ${ASAN_FLAGS})
check_cxx_compiler_flag(${ASAN_FLAGS} asan_works) # 
unset(CMAKE_REQUIRED_FLAGS)
if(asan_works)
	string(REPLACE " " ";" _asan_flags ${ASAN_FLAGS}) # 替换分隔符
	# _asan_flag 最后结果
endif()

include(CheckCSourceRuns)
include(CheckCXXSourceRuns) # CXX
set(_test_uuid
"
#include <stdio.h>
#include <uuid/uuid.h>

int main()
{
	uuid_t uuid;
	uuid_generate(uuid);
	return 0;
}
")
set(CMAKE_REQUIRED_LIBRARIES ${UUID_LIBRARIES}) # PkgConfig::UUID
check_c_source_runs("${_test_uuid}" _runs)
unset(CMAKE_REQUIRED_LIBRARIES)
if(NOT _runs)
	message(FATAL_ERROR "Connot run a simple C executable using libuuid!")
endif()

# 生成器表达式
# 逻辑表达式 $<condition:outcome>
# 信息表达式 $<inforation> $<information:input>
# 比如表达式 $<TARGET_PROPERTY:tgt,prop> ，将获得的信息是tgt目标上的prop属性
# 输出表达式，基本模式为 $<operation> 或 $<operation:input> ，如 -I$<JOIN:$<TARGET_PROPERTY:INCLUDE_DIRECTORIES>, -I>
# $<BUILD_INTERFACE>
# $<INSTALL_INTERFACE>

if(COMMAND whoami) # whoami 命令可用
	execute_process(
		COMMAND whoami
		TIMEOUT 1
		OUTPUT_VARIABLE _user_name
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	message(STATUS "_user_name: ${_user_name}")
endif()

# 新建文件夹
# file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)

if(EXISTS "${PROJECT_SOURCE_DIR}/VERSION")
	file(READ "${PROJECT_SOURCE_DIR}/VERSION" PROGRAM_VERSION) # 读取文件内容到变量
	string(STRIP "${PROGRAM_VERSION}" PROGRAM_VERSION)
else()
	message(FATAL_ERROR "File ${CMAKE_CURRENT_SOURCE_DIR}/VERSION not found")
endif()
configure_file(
	config.h.in # 输入文件，替换文件中CMake变量，如${PROJECT_VERSION} @PROJECT_VERSION@
	config.h # 输出文件，默认在 ${PROJECT_BINARY_DIR}
)




macro(message_test_1 _message_1)
	#math(EXPR num_macro_calls "{num_macro_calls} + 1")
	message(STATUS "${_message_1}")
	# set(_argn "${ARGN}")
	# 相当于 argc,  也可以直接ARG1
endmacro()
#set(num_macro_calls 0)
message_test_1("yyy")
message_test_1("yy2")
message_test_1("yy3")
#message_test_1("${num_macro_calls}")
# 这里函数与宏的不同在变量范围 函数是function(function_name arg1 ...) endfunction()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") # 添加路径，方便自定义cmake
include(colors) # ./cmake/colors.cmake
define_colors() # ./cmake/colors.cmake 中定义的宏
# if(_user_name STREQUAL "root")
function(func_test)
	set(options)
	set(oneValueArgs NAME)
	set(multiValueArgs DEPENDS SOURCES COMMAND)
	cmake_parse_arguments(func_test "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	message(STATUS "defining a test ...")
	message(STATUS "options: ${options}")
	message(STATUS "NAME: ${func_test_NAME}")
	message(STATUS "DEPENDS: ${func_test_DEPENDS}")
	message(STATUS "COMMAND: ${func_test_COMMAND}")
	message(STATUS "SOURCES: ${func_test_SOURCES}")
endfunction()
func_test(name NAME xxx COMMAND y SOURCES linear.cpp)
#[[
# 处理已弃用
macro(somemacro)
	message(DEPRECATION "somemacro is deprecated")
	_somemacro(${ARGV})
	endmacro()
]]

# 使用target_sources避免全局变量

# 超级构建模式

set_property(DIRECTORY PROPERTY EP_BASH ${CMAKE_BINARY_DIR}/subprojects)
# 为当前目录和底层目录设置 EP_BASH 目录属性

include(ExternalProject)
# tool 下是一个完整的cmake项目

ExternalProject_Add(
	${PROJECT_NAME}_tool
	SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/tool
  CMAKE_ARGS
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_C_STANDARD=${CMAKE_C_STANDARD}
    -DCMAKE_C_EXTENSIONS=${CMAKE_C_EXTENSIONS}
    -DCMAKE_C_STANDARD_REQUIRED=${CMAKE_C_STANDARD_REQUIRED}
  CMAKE_CACHE_ARGS
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
  BUILD_ALWAYS
    1
  INSTALL_COMMAND
    ""
)
# message(STATUS "EP_BASH: ${EP_BASH}")

# ExternalProject_Add_Step 附加命令在步骤
# ExternalProject_Add_StepTargets #允许将外部项目中的步骤定义为目标
# ExternalProject_Add_StepDependencies 依赖
#[[
# 构建依赖项 目录
set(STAGED_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/stage)
# list(APPEND BOOST_COMPONENTS_REQUIRED filesystem system)
ExternalProject_Add(boost_external
    URL
      https://sourceforge.net/projects/boost/files/boost/1.61.0/boost_1_61_0.zip
    URL_HASH
      SHA256=02d420e6908016d4ac74dfc712eec7d9616a7fc0da78b0a1b5b937536b2e01e8
    DOWNLOAD_NO_PROGRESS
      1
    UPDATE_COMMAND
      ""
    CONFIGURE_COMMAND
      <SOURCE_DIR>/bootstrap.sh
      --with-toolset=${_toolset}
      --prefix=${STAGED_INSTALL_PREFIX}/boost
      ${_bootstrap_select_libraries}
    BUILD_COMMAND
      <SOURCE_DIR>/b2 -q
           link=shared
           threading=multi
           variant=release
           toolset=${_toolset}
           ${_b2_select_libraries}
    LOG_BUILD
      1
    BUILD_IN_SOURCE
      1
    INSTALL_COMMAND
      <SOURCE_DIR>/b2 -q install
           link=shared
           threading=multi
           variant=release
           toolset=${_toolset}
           ${_b2_select_libraries}
    LOG_INSTALL
      1
    BUILD_BYPRODUCTS
      "${_build_byproducts}"
    )

  set(
    BOOST_ROOT ${STAGED_INSTALL_PREFIX}/boost
    CACHE PATH "Path to internally built Boost installation root"
    FORCE
    )
  set(
    BOOST_INCLUDEDIR ${BOOST_ROOT}/include
    CACHE PATH "Path to internally built Boost include directories"
    FORCE
    )
  set(
    BOOST_LIBRARYDIR ${BOOST_ROOT}/lib
    CACHE PATH "Path to internally built Boost library directories"
    FORCE
    )

  # Unset internal variables
  unset(_toolset)
  unset(_b2_needed_components)
  unset(_build_byproducts)
  unset(_b2_select_libraries)
  unset(_bootstrap_select_libraries)
]]

# 支持 CONFIGURE_COMNAND BUILD_COMMAND等 <SOURCE_DIR>
# BUILD_IN_SOURCE true 内置构建
# TEST_AFTER_INSTALL 1
# LOG_INSTALL LOG_BUILD LOG_CONFIGURE


# string(REPLACE <match-string> <replace-string> <out-var> <input>...)

# string(REGEX REPLACE <match-string> <replace-string> <out-var> <input>...)

#[[
include(FetchContent)
FetchContent_Declare(cJSON GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git GIT_TAG release-1.7.15)
FetchContent_GetProperties(cJSON)
if(NOT cJSON_POPULATED)
	FetchContent_Populate(cJSON)
	add_subdirectory(${cJSON_SOURCE_DIR})
	add_subdirectory(${cJSON_BINARY_DIR})
endif()
]]

message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}") # 默认安装位置

# 构建类型
# Debug 没有优化情况下，带有调试符号构建库或可执行文件
# Release 用于构建的优化的库或可执行文件，不包含调试符号
# RelWithDebinfo 用于构建较少的优化库或者可执行文件，包含调试符号
# MinSizeRel 用于不增加目标代码大小优化方式，来构建库或可执行文
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE) # 设置默认构建类型
endif()
message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")
# 切换 cmake -D
# 也可以 cmake -D CMAKE_CONFIGURATION_TYPE="Release;Debug" 再 cmake --build . --config Release


# 21

if(WIN32 AND NOT CYGWIN)
	set(DEF_INSTALL_CMAKEDIR CMake)
else()
	set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")


foreach(p LIB BIN INCLUDE CMAKE)
	file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path)
	message(STATUS "Installing ${p} components to ${_path}")
	unset(_path)
endforeach()



# 设置 rpath
file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})
if(APPLE)
	set(_rpath "@loader_path/${_rel}")
else()
	set(_rpath "\$ORIGIN/${_rel}")
endif()
file(TO_NATIVE_PATH "${_rpath}/${INSTALL_LIBDIR}" _RPATH)
set_target_properties(
	d
	PROPERTIES
		POSITION_INDEPENDENT_CODE 1
		SKIP_BUILD_RPATH OFF
		BUILD_WITH_INSTALL_RPATH OFF
		INSTALL_RPATH "${_RPATH}"
		INSTALL_RPATH_USE_LINK_PATH ON
		MAXOSX_RPATH ON
)
# set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) # 编译时加上RPATH
# set(CMAKS_SKIP_BUILD_RPATH FALSE) #跳过RPATH
# CKAKE_SKIP_INSTALL_RPATH
# INSTALL_RPATH_USE_LINK_PATH ON ：告诉CMake将链接器搜索路径附加到可执行文件的 RPATH 中。

# MAXCOSX_RPATH ON 这将动态库的install_name 部分(目录)设置为macOS上的 @rpath


include(GenerateExportHeader)
set(_export_name "k1")
generate_export_header(
	k1-shared
	BASE_NAME "${_export_name}" # BASE_NAME 设置生成头文件和宏的名称
	EXPORT_MACRO_NAME "${_export_name}_EXPORT"
	EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/${_export_name}Export.h" # 设置导出头文件的名称
	DEPRECATED_MACRO_NAME "${_export_name}_DEPRECATED" # 设置导出宏的名称
	NO_EXPORT_MACRO_NAME "${_export_name}_NO_EXPORT" # NO_EXPORT_MACRO_NAME 设置不导出宏的名字
	STATIC_DEFINE "${_export_name}_STATIC_DEFINE" # 用于定义宏的名称
	NO_DEPRECATED_MACRO_NAME "${_export_name}_NO_DEPRECATED"
	DEFINE_NO_DEPRECATED # 指示CMake生成预处理代码
)

set_target_properties(
	k1-static
	PROPERTIES
		POSITION_INDEPENDENT_CODE 1
		# VISIBILITY_INLINES_HIDEN 1 # 隐藏内联函数的符号
		ARCHIVE_OUTPUT_NAME "k1"
		DEBUG_POSTFIX "_sd"
		RELEASE_POSTFIX "_s"
		# PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/k1.h;${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/${_export_name}Export.h"
)

set_target_properties(
	k1-shared
	PROPERTIES
		POSITION_INDEPENENT_CODE 1
		CXX_VISIBILITY_PRESET hidden # 隐藏所有符号
		SOVERSION ${PROJECT_VERSION_MAJOR}
		OUTPUT_NAME "k1"
		DEBUG_POSTFIX "_d" # DEBUG时后缀
		# PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/k1.h;${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/${_export_name}.h"
		MACOSX_RPATH ON
)



include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
	${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
)
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
	DESTINATION ${INSTALL_CMAKEDIR}
)
install(
	TARGETS
		d demo_test k1-static k1-shared
	ARCHIVE
		DESTINATION ${INSTALL_LIBDIR} # 默认相对于 CMAKE_INSTALL_PREFIX
		COMPONENT lib
	RUNTIME
		DESTINATION ${INSTALL_BINDIR}
		COMPONENT bin
	LIBRARY
		DESTINATION ${INSTALL_LIBDIR}
		COMPONENT lib
	PUBLIC_HEADER
		DESTINATION ${INSTALL_INCLUDEDIR}
		COMPONENT dev
)
install(
	FILES
		${PROJECT_SOURCE_DIR}/k1.h
		"${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/${_export_name}Export.h"
	DESTINATION ${INSTALL_INCLUDEDIR}/${_export_name}
)

# PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP... WORLD... SETUID SETGID
# EXCLUDE_FROM_ALL 排除指定文件
# RENAME 安装单个文件时重命名
# install(TARGETS targets... [EXPORT <export-name>] [ARCHIVE|LIBRARY|RUTIME|OBJECTS|FRAMEWORK|BUNDLE|PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE] [DESTINATION <dir>] [PERMISSIONS permissions...] [CONFIGURATIONS [Debug|Release|...]] [COMPONENT <component>] [NAMELINK_COMPONENT <component>] [OPTIONAL] [EXECLUDE_FROM_ALL] [NAMELINK_ONLY|NAMELINK_SKIP] [...] [INCLUDES DESTINATION [<dir> ...]])



set(CPACK_PACKAGE_NAME "${PROJECT_NAME}") # 
set(CPACK_PACKAGE_VENDOR "Provider") # 提供商
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md") # 描述文件
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "README.md") # 描述
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE") # 许可文件
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}") # 从发布的包中安装时，安装位置
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_BINARY_DIR};.git;.gitignore") # 打包source 时忽略的文件
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ") # 列出了源码归档的打包生成器
set(CPACK_GENERATOR "ZIP;TGZ") # 二进制存档生成器
if(UNIX)
	if(CMAKE_SYSTEM_NAME MATCHES Linux)
		list(APPEND CPACK_GENERATOR "DEB")
		set(CPACK_DEBIAN_PACKAGE_MAINTAINER "maintainer")
		set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
		set(CPACK_DEBIAN_PACKAGE_DEPENDS "uuid-dev")

		list(APPEND CPACK_GENERATOR "RPM")
		set(CPACK_RPM_PACKAGE_RELEASE "1")
		# set(CPACK_RPM_PACKAGE_LICENSE "MIT")
		set(CPACK_RPM_PACKAGE_REQUIRES "uuid-dev")
	endif()
endif()
if(WIN32 OR MINGW)
	list(APPEND CPACK_GENERATOR "NSIS")
	set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_NSIS_CONTACT "contact") # maintainer
	set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
endif()
if(APPLE)
	list(APPEND CPACK_GENERATOR "Bundle")
	set(CPACK_BUNDLE_NAME "${PROJECT_NAME}")
	configure_file(${PROJECT_SOURCE_DIR}/cmake/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/Info.plist @ONLY)
	set(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
	set(CPACK_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/cmake/coffee.icns)
endif()
message(STATUS "CPack generators: ${CPACK_GENERATOR}")

include(CPack) # 

add_test(
	NAME install_test
	COMMAND ${CMAKE_COMMAND} --build . --target install
	LABELS "long"
)
add_test(
	NAME package_source_test
	COMMAND ${CMAKE_COMMAND} --build . --target package_source
	LABELS "long"
)
add_test(
	NAME package_test
	COMMAND ${CMAKE_COMMAND} --build . --target package
	LABELS "long"
)
add_test(
	NAME config_test
	COMMAND $<TARGET_FILE:config>
	LABELS "quick"
)

# CMAKE_CURRENT_LIST_FILE # 调用变量的 CMakeLists.txt 路径
# CMAKE_CURRENT_LIST_LINE # 调用变量所在行

# aux_source_list(${PROJECT_SOURCE_DIR}/src/k3 _var_srcs) # 查找文件夹下所有文件，保存至变量_var_srcs中
# exec_program(ls ARGS "*.c" OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)

#FILE
# file(WRITE filename "Some text ...") # 写文件
# file(APPEND filename "Some text ...") # 追加
# file(READ filename variable) # 读文件，保存到变量中
# file(REMOVE [directory] ...) # 删除文件(夹)
# file(REMOVE_RECURSE [directory] ...) # 删除文件(夹)，递归
# file(GLOB variable [RELATIVE path] [globbing expression_r_rs]...) # 根据表达式找到文件
# file(GLOB _k3_srcs k3/*.c)
# file(GLOB_RECURSE variable [RELATIVE path] [globbing expression_r_rs]...)
# file(MAKE_DIRECTORY [directory] ...) # 新建文件夹
# file(RELATIVE_PATH variable directory file) # 
# file(TO_CMAKE_PATH path result)
# file(TO_NATIVE_PATH path result)
# file(DOWNLOAD "http://www.baidu.com" ${CMAKE_CURRENT_SOURCE_DIR}/index.html SHOW_PROGRESS)
# file(SIZE <file_name> <outvar>)
# file(<MD5|SHA1|SHA224|SHA256|SHA384|SHA512> filenamevariable)

# include(xxx OPTIONAL) # 文件不存在也不会报错

# find_library(_cjson cjson)

# if(EXISTS [dir|file]) # 文件夹或文件存在时
# if(file1 IS_NEWER_THAN file2) # file1 比 file2 新，或者有一个文件不存在
# if(IS_DIRECTORY dir) # 
# if(variable MATCHES regex)
# if(string MATCHES "rin") # 例子
# if(<variable|string> <LESS|GREATER|EQUAL> number) # 比较
# if(<variable|string> <STRLESS|STRGREATER|STREQUAL> string)
# while(1)
	message(STATUS "STATUS")
# endwhile()
# set(CMAKE_DEBUG_POSTFIX "d") # Debug 后缀

if(test_more_)
	if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		include(CheckSymbolExists)
		set(CMAKE_REQUIRED_LIBRARIES "m")
		# check_symbol_exists("log" "math.h" HAVE_LOG)
		check_symbol_exists("sqrt" "math.h" HAVE_SQRT)
		# target_compile_definitions(d PRIVATE "HAVE_SQRT")
		unset(CheckSymbolExists)
	endif()
	# 平台检查
	include(CheckTypeSize)
	include(CheckFunctionExists)
	include(CheckIncludeFiles)
	include(CheckLibraryExists)
	# 类型
	foreach(_type IN ITEMS char int long size_t)
		check_type_size("${_type}" _sizeof_${_type})
		# message(STATUS "sizeof ${_type}: ${_sizeof_${_type}}")
	endforeach()
	# 函数
	foreach(_function IN ITEMS
			fchdir fchown fchmod fsync getcwd getpseudotty getpwent getpwnam getpwuid getrlimit gettimeofday getwd lstat memset mkdtemp nanosleep opendir putenv qsort readlink select setenv getpgid setpgid setsid sigaltstack sigstack sigset sigsetjmp sigaction sigprocmask sigvec strcasecmp strerror strftime stricmp strncasecmp strnicmp strpbrk strtol towlower towupper iswupper usleep utime utimes mblen ftruncate
)
		string(TOUPPER "${_function}" _function_uppercase)
		check_function_exists(${_function} HAVE_${_function_uppercase})
	endforeach()
	# 特定函数
	check_library_exists(uuid uuid_generate "" HAVE_UUID_GENERATE)
	if(NOT HAVE_UUID_GENERATE)
		message(STATUS "Not found uuid_generate")
	endif()
	foreach(_header IN ITEMS
			setjmp.h dirent.h stdint.h stdlib.h string.h sys/select.h sys/utsname.h termcap.h fcntl.h sgtty.h sys/ioctl.h sys/time.h sys/types.h termio.h iconv.h inttypes.h langinfo.h math.h unistd.h stropts.h errno.h sys/resource.h sys/systeminfo.h locale.h sys/stream.h termios.h libc.h sys/statfs.h poll.h sys/poll.h pwd.h utime.h sys/param.h libintl.h libgen.h util/debug.h util/msg18n.h frame.h sys/acl.h sys/access.h sys/sysinfo.h wchar.h wctype.h
	)
		string(TOUPPER "${_header}" _header_uppercase)
		string(REPLACE "/" "_" _header_normalized "${_header_uppercase}")
		string(REPLACE "." "_" _header_normalized "${_header_normalized}")
		check_include_files(${_header} HAVE_${_header_normalized})
	endforeach()
	#[[
	# 然后，我们将CMake选项从转换为预处理定义:
	string(TOUPPER "${FEATURES}" _features_upper)
	set(FEAT_${_features_upper} 1)
	set(FEAT_NETBEANS_INTG ${ENABLE_NETBEANS})
	set(FEAT_JOB_CHANNEL ${ENABLE_CHANNEL})
	set(FEAT_TERMINAL ${ENABLE_TERMINAL})
	]]

endif()




